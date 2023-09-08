#include "CResWave.h"

#include "CUtil.h"
#include "music/adecode.h"

typedef struct FileReaderContext {
    unsigned char* bytes;
    unsigned char* current_bytes;
    int size;
} FileReaderContext;

static int FileReader(void* data, void* buffer, int size);

// 0x77E6C0
CResWave::CResWave()
{
    m_bParsed = FALSE;
    m_bCompressed = FALSE;
    m_nWaveNormalSize = 0;
    m_nWaveCompressedSize = 0;
    m_pWaveData = NULL;
    m_pWaveFormatEx = NULL;
}

// 0x77E710
CResWave::~CResWave()
{
}

// 0x77E790
void* CResWave::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        Parse(pData);

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x77E810
LPWAVEFORMATEX CResWave::GetWaveFormatPtr()
{
    if (m_bParsed) {
        return m_pWaveFormatEx;
    } else {
        return NULL;
    }
}

// 0x77E820
DWORD CResWave::GetWaveSize()
{
    if (m_bParsed) {
        return m_nWaveNormalSize;
    } else {
        return 0;
    }
}

// 0x77E830
int CResWave::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_nWaveNormalSize = 0;
        m_nWaveCompressedSize = 0;
        m_pWaveData = NULL;

        if (m_bCompressed) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
            // __LINE__: 866
            UTIL_ASSERT(m_pWaveFormatEx != NULL);
            delete m_pWaveFormatEx;
        }

        m_pWaveFormatEx = NULL;
    }
    return rc;
}

// NOTE: Inlined in `CResWave::Demand`.
BOOL CResWave::Parse(void* pData)
{
    m_pWaveFormatEx = NULL;
    m_pWaveData = NULL;
    m_nWaveNormalSize = 0;
    m_nWaveCompressedSize = 0;

    if (memcmp(pData, "WAVC", 4) == 0) {
        m_bCompressed = TRUE;
        m_bParsed = ParseCompressedWave(pData);
    } else if (memcmp(pData, "RIFF", 4) == 0) {
        m_bCompressed = FALSE;
        m_bParsed = ParseNormalWave(pData);
    } else {
        m_bParsed = FALSE;
    }

    return m_bParsed;
}

// 0x77E8A0
BOOL CResWave::ParseNormalWave(void* pData)
{
    BYTE* pBytes = reinterpret_cast<BYTE*>(pData);

    if (memcmp(pBytes, "RIFF", 4) != 0) {
        return FALSE;
    }

    if (memcmp(pBytes + 8, "WAVE", 4) != 0) {
        return FALSE;
    }

    BYTE* pCurr = pBytes + 12;
    BYTE* pEnd = pBytes + *reinterpret_cast<DWORD*>(pBytes + 4);
    while (pCurr < pEnd) {
        DWORD dwType = *reinterpret_cast<DWORD*>(pCurr);
        DWORD dwLength = *reinterpret_cast<DWORD*>(pCurr + 4);
        if (memcmp(&dwType, "data", 4) == 0) {
            if (m_pWaveData == NULL) {
                m_pWaveData = pCurr + 8;
                m_nWaveNormalSize = dwLength;
                m_nWaveCompressedSize = dwLength;

                if (m_pWaveFormatEx != NULL) {
                    return TRUE;
                }
            }
        } else if (memcmp(&dwType, "fmt ", 4) == 0) {
            if (m_pWaveFormatEx == NULL) {
                if (dwLength < sizeof(WAVEFORMAT)) {
                    return FALSE;
                }

                m_pWaveFormatEx = reinterpret_cast<LPWAVEFORMATEX>(pCurr + 8);

                if (m_pWaveData != NULL) {
                    return TRUE;
                }
            }
        }

        // TODO: Unclear.
        pCurr += (dwLength + 1) & ~1;
    }

    return FALSE;
}

// 0x77E940
BOOL CResWave::ParseCompressedWave(void* pData)
{
    BYTE* pBytes = reinterpret_cast<BYTE*>(pData);

    if (memcmp(pBytes, "WAVC", 4) != 0) {
        return FALSE;
    }

    if (memcmp(pBytes + 4, "V1.0", 4) != 0) {
        return FALSE;
    }

    DWORD nNormalSize = *reinterpret_cast<DWORD*>(pBytes + 8);
    DWORD nCompressedSize = *reinterpret_cast<DWORD*>(pBytes + 12);
    DWORD nOffset = *reinterpret_cast<DWORD*>(pBytes + 16);
    WORD nChannels = *reinterpret_cast<WORD*>(pBytes + 20);
    WORD nBitsPerSample = *reinterpret_cast<WORD*>(pBytes + 22);
    WORD nSamplesPerSec = *reinterpret_cast<WORD*>(pBytes + 24);

    m_pWaveFormatEx = new WAVEFORMATEX();

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 1085
    UTIL_ASSERT(m_pWaveFormatEx != NULL);

    m_pWaveFormatEx->wFormatTag = WAVE_FORMAT_PCM;
    m_pWaveFormatEx->nChannels = nChannels;
    m_pWaveFormatEx->nSamplesPerSec = nSamplesPerSec;
    m_pWaveFormatEx->nBlockAlign = nChannels * nBitsPerSample / 8;
    m_pWaveFormatEx->nAvgBytesPerSec = m_pWaveFormatEx->nSamplesPerSec * m_pWaveFormatEx->nBlockAlign;
    m_pWaveFormatEx->wBitsPerSample = nBitsPerSample;
    m_pWaveFormatEx->cbSize = 0;

    m_nWaveNormalSize = nNormalSize;
    m_nWaveCompressedSize = nCompressedSize;
    m_pWaveData = pBytes + nOffset;

    return TRUE;
}

// 0x77EA60
int CResWave::CopyWaveData(BYTE* pWaveData)
{
    INT nBytesRead = 0;

    if (m_pWaveData == NULL) {
        return FALSE;
    }

    if (m_bCompressed) {
        FileReaderContext ctx;
        ctx.bytes = m_pWaveData;
        ctx.current_bytes = m_pWaveData;
        ctx.size = m_nWaveCompressedSize;

        int channels;
        int sampleRate;
        int sampleCount;
        AudioDecoder* audioDecoder = Create_AudioDecoder(FileReader,
            &ctx,
            &channels,
            &sampleRate,
            &sampleCount);
        if (audioDecoder != NULL) {
            int bytesRead;
            while ((bytesRead = AudioDecoder_Read(audioDecoder, pWaveData, m_nWaveNormalSize)) != 0) {
                pWaveData += bytesRead;
                nBytesRead += bytesRead;
            }

            AudioDecoder_Close(audioDecoder);
        }
    } else {
        memcpy(pWaveData, m_pWaveData, m_nWaveNormalSize);
    }

    return nBytesRead;
}

// 0x77EB30
int FileReader(void* data, void* buffer, int size)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 1129
    UTIL_ASSERT(data != NULL);

    FileReaderContext* ctx = reinterpret_cast<FileReaderContext*>(data);

    if (ctx->bytes + ctx->size - ctx->current_bytes < size) {
        size = ctx->bytes + ctx->size - ctx->current_bytes;
    }

    memcpy(buffer, ctx->current_bytes, size);
    ctx->current_bytes += size;

    return size;
}

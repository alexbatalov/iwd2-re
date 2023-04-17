#include "CResWave.h"

#include "CUtil.h"

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

    if (*reinterpret_cast<DWORD*>(pData) == 'WAVC') {
        m_bCompressed = TRUE;
        m_bParsed = ParseCompressedWave(pData);
    } else if (*reinterpret_cast<DWORD*>(pData) == 'RIFF') {
        m_bCompressed = FALSE;
        m_bParsed = ParseNormalWave(pData);
    } else {
        m_bParsed = FALSE;
    }

    return m_bParsed;
}

// 0x77E790
BOOL CResWave::ParseNormalWave(void* pData)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x77E940
BOOL CResWave::ParseCompressedWave(void* pData)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x77EA60
BOOL CResWave::CopyWaveData(BYTE* pWaveData)
{
    if (m_pWaveData == NULL) {
        return FALSE;
    }

    if (m_bCompressed) {
        // TODO: Incomplete.
    } else {
        memcpy(pWaveData, m_pWaveData, m_nWaveNormalSize);
    }

    // TODO: Not sure what exactly is returned.
    return TRUE;
}

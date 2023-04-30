#include "CResCell.h"

#include "CUtil.h"

// 0x77F3F0
CResCell::CResCell()
{
    m_bParsed = FALSE;
    m_pBamHeader = NULL;
    m_pBamHeaderCopy = NULL;
    m_pFrames = NULL;
    m_pSequences = NULL;
    m_pFrameList = NULL;
    m_nFrameListSize = 0;
    m_pPalette = NULL;
    m_bParsing = FALSE;
    field_18 = 1;
    field_7E = 1;
}

// 0x77F450
CResCell::~CResCell()
{
    ResRefChange();
}

// 0x77F4E0
void* CResCell::Demand()
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

// 0x77F520
FRAMEENTRY* CResCell::GetFrame(WORD nSequence, WORD nFrame, BOOL bDoubleSize)
{
    if (m_pFrameList == NULL) {
        return NULL;
    }

    if (m_pSequences == NULL) {
        return NULL;
    }

    if (m_pFrames == NULL) {
        return NULL;
    }

    WORD nIndex = m_pFrameList[nFrame + m_pSequences[nSequence].nStartingFrame];
    if (nIndex == -1) {
        return NULL;
    }

    if (!bDoubleSize) {
        return &(m_pFrames[nIndex]);
    }

    m_doubleSizeFrameEntry = m_pFrames[nIndex];
    m_doubleSizeFrameEntry.nCenterX *= 2;
    m_doubleSizeFrameEntry.nCenterY *= 2;
    m_doubleSizeFrameEntry.nWidth *= 2;
    m_doubleSizeFrameEntry.nHeight *= 2;
    return &m_doubleSizeFrameEntry;
}

// 0x77F5C0
BOOL CResCell::GetCompressed(FRAMEENTRY* pFrame, BOOL bDoubleSize)
{
    if (pFrame == NULL) {
        return FALSE;
    }

    if (bDoubleSize) {
        return FALSE;
    }

    return (pFrame->nOffset & 0x80000000) != 0x80000000;
}

// 0x77F5F0
BYTE* CResCell::GetFrameData(FRAMEENTRY* pFrame, BOOL bDoubleSize)
{
    if (!m_bParsed) {
        return NULL;
    }

    if (pFrame == NULL) {
        return FALSE;
    }

    if (!bDoubleSize) {
        return reinterpret_cast<BYTE*>(m_pBamHeader) + (pFrame->nOffset & 0x7FFFFFFF);
    }

    if (m_pDimmKeyTableEntry->resRef == g_pChitin->cVideo.field_114
        && m_pDimmKeyTableEntry->nResType == g_pChitin->cVideo.field_11C
        && pFrame->nOffset == g_pChitin->cVideo.field_11E) {
        return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
    }

    g_pChitin->cVideo.field_114 = m_pDimmKeyTableEntry->resRef;
    g_pChitin->cVideo.field_11C = m_pDimmKeyTableEntry->nResType;
    g_pChitin->cVideo.field_11E = pFrame->nOffset;
    g_pChitin->cVideo.SetDoubleSizeData(pFrame->nHeight * pFrame->nWidth);

    BYTE* pFrameData = reinterpret_cast<BYTE*>(m_pBamHeader) + (pFrame->nOffset & 0x7FFFFFFF);
    BYTE* pDoubleSizeFrameData = reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);

    WORD nWidth = pFrame->nWidth / 2;
    WORD nHeight = pFrame->nHeight / 2;
    WORD nOffset = pFrame->nWidth;

    // NOTE: Why it uses `m_pBamHeaderCopy` instead of `m_pBamHeader`?
    BYTE nTransparentColor = m_pBamHeaderCopy->nTransparentColor;

    if ((pFrame->nOffset & 0x80000000) == 0x80000000) {
        for (WORD y = 0; y < nHeight; y++) {
            for (WORD x = 0; x < nWidth; x++) {
                BYTE nColor = *pFrameData++;
                pDoubleSizeFrameData[0] = nColor;
                pDoubleSizeFrameData[nOffset] = nColor;
                pDoubleSizeFrameData[1] = nColor;
                pDoubleSizeFrameData[nOffset + 1] = nColor;
                pDoubleSizeFrameData += 2;
            }
            pDoubleSizeFrameData += nOffset;
        }
    } else {
        memset(pDoubleSizeFrameData, nTransparentColor, pFrame->nHeight * pFrame->nWidth);

        WORD nRunLength = 0;
        int pos = 0;
        for (WORD y = 0; y < nHeight; y++) {
            WORD nRemainingWidth = nWidth;
            while (nRemainingWidth != 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos] + 1;
                    }

                    if (nRemainingWidth == nRunLength) {
                        pos += 2;

                        pDoubleSizeFrameData += 2 * nRemainingWidth;
                        nRunLength = 0;
                        nRemainingWidth = 0;
                    } else if (nRemainingWidth > nRunLength) {
                        pos += 2;

                        pDoubleSizeFrameData += 2 * nRunLength;
                        nRemainingWidth -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pDoubleSizeFrameData += 2 * nRemainingWidth;
                        nRunLength -= nRemainingWidth;
                        nRemainingWidth = 0;
                    }
                } else {
                    pos++;

                    pDoubleSizeFrameData[0] = nColor;
                    pDoubleSizeFrameData[nOffset] = nColor;
                    pDoubleSizeFrameData[1] = nColor;
                    pDoubleSizeFrameData[nOffset + 1] = nColor;
                    pDoubleSizeFrameData += 2;
                    nRemainingWidth--;
                }
            }
            pDoubleSizeFrameData += nOffset;
        }
    }

    return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
}

// 0x77F820
int CResCell::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pBamHeader = NULL;

        if (!field_7E) {
            m_pBamHeaderCopy = NULL;
            m_pFrames = NULL;
            m_pSequences = NULL;
            m_pFrameList = NULL;
        }

        m_pPalette = NULL;
    }
    return rc;
}

// 0x77F860
void CResCell::ResRefChange()
{
    if (field_7E) {
        CSingleLock lock(&field_20, FALSE);
        lock.Lock(INFINITE);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 2846
        UTIL_ASSERT(!m_bParsing);

        if (m_pFrames != NULL) {
            delete m_pFrames;
            m_pFrames = NULL;
        }

        if (m_pSequences != NULL) {
            delete m_pSequences;
            m_pSequences = NULL;
        }

        if (m_pFrameList != NULL) {
            delete m_pFrameList;
            m_pFrameList = NULL;
        }

        m_nFrameListSize = 0;

        if (m_pBamHeaderCopy != NULL) {
            delete m_pBamHeaderCopy;
            m_pBamHeaderCopy = NULL;
        }

        lock.Unlock();
    }
}

// 0x77F940
BOOL CResCell::Parse(void* pData)
{
    if (pData == NULL) {
        return m_bParsed;
    }

    BAMHEADER* pBamHeader = reinterpret_cast<BAMHEADER*>(pData);
    if (memcmp(&(pBamHeader->nFileType), "BAM ", 4) != 0 || memcmp(&(pBamHeader->nFileVersion), "V1  ", 4) != 0) {
        return FALSE;
    }

    if (!field_7E) {
        m_pBamHeader = pBamHeader;
        m_pFrames = reinterpret_cast<FRAMEENTRY*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nTableOffset);
        m_pSequences = reinterpret_cast<SEQUENCEENTRY*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nTableOffset + sizeof(FRAMEENTRY) * pBamHeader->nFrames);
        m_pFrameList = reinterpret_cast<WORD*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nFrameListOffset);
        m_pPalette = reinterpret_cast<RGBQUAD*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nPaletteOffset);
        m_bParsed = TRUE;
        return m_bParsed;
    }

    CSingleLock lock(&field_20, FALSE);
    lock.Lock(INFINITE);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 2924
    UTIL_ASSERT(pBamHeader->nTableOffset < m_nResSizeActual);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 2925
    UTIL_ASSERT(!m_bParsing);

    m_bParsing = TRUE;

    FRAMEENTRY* pFrames = reinterpret_cast<FRAMEENTRY*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nTableOffset);
    do {
        if (m_pFrames != NULL) {
            if (m_pBamHeaderCopy->nFrames == pBamHeader->nFrames) {
                // FIXME: Looks like a bug, it compares number of frames to save
                // a couple of ticks on delete/new calls, but does not copy
                // actual contents.
                break;
            }

            delete m_pFrames;
        }

        m_pFrames = new FRAMEENTRY[pBamHeader->nFrames];

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 2935
        UTIL_ASSERT(m_pFrames != NULL);

        memcpy(m_pFrames, pFrames, sizeof(FRAMEENTRY) * pBamHeader->nFrames);
    } while (0);

    SEQUENCEENTRY* pSequences = reinterpret_cast<SEQUENCEENTRY*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nTableOffset + sizeof(FRAMEENTRY) * pBamHeader->nFrames);
    do {
        if (m_pSequences != NULL) {
            if (m_pBamHeaderCopy->nSequences == pBamHeader->nSequences) {
                // FIXME: Looks like a bug, just like the above.
                break;
            }

            delete m_pSequences;
        }

        m_pSequences = new SEQUENCEENTRY[pBamHeader->nSequences];

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 2946
        UTIL_ASSERT(m_pSequences != NULL);

        memcpy(m_pSequences, pSequences, sizeof(SEQUENCEENTRY) * pBamHeader->nSequences);
    } while (0);

    WORD nFrameListSize = 0;
    for (BYTE nSequence = 0; nSequence < pBamHeader->nSequences; nSequence++) {
        nFrameListSize += pSequences[nSequence].nFrames;
    }

    WORD* pFrameList = reinterpret_cast<WORD*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nFrameListOffset);
    do {
        if (m_pFrameList != NULL) {
            if (m_nFrameListSize == nFrameListSize) {
                // FIXME: Looks like a bug, just like the above.
                break;
            }

            delete m_pFrameList;
        }

        m_pFrameList = new WORD[nFrameListSize];

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 2962
        UTIL_ASSERT(m_pFrameList != NULL);

        m_nFrameListSize = nFrameListSize;

        memcpy(m_pFrameList, pFrameList, sizeof(WORD) * nFrameListSize);
    } while (0);

    if (m_pBamHeaderCopy == NULL) {
        m_pBamHeaderCopy = new BAMHEADER;

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 2971
        UTIL_ASSERT(m_pFrameList != NULL);
    }

    memcpy(m_pBamHeaderCopy, pBamHeader, sizeof(BAMHEADER));

    m_pBamHeader = pBamHeader;
    m_pPalette = reinterpret_cast<RGBQUAD*>(reinterpret_cast<unsigned char*>(pData) + pBamHeader->nPaletteOffset);

    m_bParsed = TRUE;
    m_bParsing = FALSE;

    lock.Unlock();

    return m_bParsed;
}

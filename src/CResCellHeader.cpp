#include "CResCellHeader.h"

#include "CUtil.h"

// 0x77FC80
CResCellHeader::CResCellHeader()
{
    m_bParsed = FALSE;
    m_pBamHeader = NULL;
    m_pBamHeaderCopy = NULL;
    m_pFrames = NULL;
    m_pSequences = NULL;
    m_pFrameList = NULL;
    m_nFrameListSize = 0;
    m_bParsing = FALSE;
}

// 0x77FCD0
CResCellHeader::~CResCellHeader()
{
    ResRefChange();
}

// 0x77FD60
void* CResCellHeader::Demand()
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

// 0x77FDA0
FRAMEENTRY* CResCellHeader::GetFrame(WORD nSequence, WORD nFrame, BOOL bDoubleSize)
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

// 0x77FE40
int CResCellHeader::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pBamHeader = NULL;
    }
    return rc;
}

// 0x77FE70
void CResCellHeader::ResRefChange()
{
    CSingleLock lock(&field_20, FALSE);
    lock.Lock(INFINITE);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 3201
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

// 0x77FF50
BOOL CResCellHeader::Parse(void* pData)
{
    if (pData == NULL) {
        return m_bParsed;
    }

    BAMHEADER* pBamHeader = reinterpret_cast<BAMHEADER*>(pData);
    if (pBamHeader->nFileType != 'BAH ' || pBamHeader->nFileVersion != 'V1  ') {
        return FALSE;
    }

    CSingleLock lock(&field_20, FALSE);
    lock.Lock(INFINITE);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 3269
    UTIL_ASSERT(pBamHeader->nTableOffset < m_nResSizeActual);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
    // __LINE__: 3270
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
        // __LINE__: 3280
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
        // __LINE__: 3291
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
        // __LINE__: 3307
        UTIL_ASSERT(m_pFrameList != NULL);

        m_nFrameListSize = nFrameListSize;

        memcpy(m_pFrameList, pFrameList, sizeof(WORD) * nFrameListSize);
    } while (0);

    if (m_pBamHeaderCopy == NULL) {
        m_pBamHeaderCopy = new BAMHEADER;

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 3316
        UTIL_ASSERT(m_pFrameList != NULL);
    }

    memcpy(m_pBamHeaderCopy, pBamHeader, sizeof(BAMHEADER));

    m_pBamHeader = pBamHeader;

    m_bParsed = TRUE;
    m_bParsing = FALSE;

    lock.Unlock();

    return m_bParsed;
}

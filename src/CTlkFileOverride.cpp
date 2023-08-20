#include "CTlkFileOverride.h"

#include "CTlkTable.h"
#include "CUtil.h"

// 0x85DD72
const WORD CTlkFileOverride::ENTRY_HAVE_TEXT = 0x1;

// 0x85DD74
const WORD CTlkFileOverride::ENTRY_HAVE_SOUND = 0x2;

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CTlkFileOverrideTextEntry::CTlkFileOverrideTextEntry()
{
    m_nNextFreeOffset = 0;
    m_nPrevOffset = -1;
    memset(m_text, 0, 512);
    m_nNextOffset = -1;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined in `CTlkTable::CTlkTable`.
CTlkFileOverrideText::CTlkFileOverrideText()
{
    m_bOpen = FALSE;
}

// 0x7B62A0
DWORD CTlkFileOverrideText::AddString(const CString& sString)
{
    DWORD nNextOffset = -1;
    CTlkFileOverrideTextEntry entry;
    BOOL bStringOffsetSet = FALSE;
    INT nStringPos = 0;
    INT nChunkPos;
    DWORD nPrevOffset = -1;
    INT nParts = sString.GetLength() / 512 + 1;

    Seek(0, SeekPosition::begin);
    Read(&m_nNextFreeOffset, 4);

    DWORD nNextFreeOffset = m_nNextFreeOffset;
    DWORD nStringOffset = nNextFreeOffset;
    DWORD nCurrOffset;

    for (int chunk = 0; chunk < nParts; chunk++) {
        if (nNextFreeOffset == -1) {
            Seek(0, SeekPosition::begin);
            nCurrOffset = static_cast<DWORD>(Seek(0, SeekPosition::end));

            if (!bStringOffsetSet) {
                bStringOffsetSet = TRUE;
                nStringOffset = nCurrOffset;
            }

            nNextOffset = nCurrOffset + sizeof(CTlkFileOverrideTextEntry);
        } else {
            bStringOffsetSet = TRUE;

            nCurrOffset = nNextFreeOffset;
            Seek(nCurrOffset, SeekPosition::begin);

            UINT nBytesRead = Read(&entry, sizeof(CTlkFileOverrideTextEntry));
            nNextOffset = entry.m_nNextOffset;
            if (nNextOffset == -1) {
                Seek(0, SeekPosition::begin);
                nNextOffset = static_cast<DWORD>(Seek(0, SeekPosition::end));
                if (nBytesRead == 0) {
                    nNextOffset += sizeof(CTlkFileOverrideTextEntry);
                }
            }

            Seek(nNextFreeOffset, SeekPosition::begin);
            nNextFreeOffset = entry.m_nNextOffset;
        }

        memset(entry.m_text, 0, 512);

        nChunkPos = 0;
        while (nStringPos < sString.GetLength() && nChunkPos < 512) {
            entry.m_text[nChunkPos] = sString[nStringPos];
            nChunkPos++;
            nStringPos++;
        }

        entry.m_nPrevOffset = nPrevOffset;

        if (chunk == nParts - 1) {
            nNextOffset = -1;
        }

        entry.m_nNextOffset = nNextOffset;

        Seek(nCurrOffset, SeekPosition::begin);
        Write(&entry, sizeof(CTlkFileOverrideTextEntry));

        nPrevOffset = nCurrOffset;
    }

    m_nNextFreeOffset = nNextOffset;

    Seek(0, SeekPosition::begin);
    Write(&m_nNextFreeOffset, 4);

    return nStringOffset;
}

// 0x7B6500
void CTlkFileOverrideText::RemoveString(DWORD nOffset)
{
    CTlkFileOverrideTextEntry entry;
    DWORD nCurrOffset = nOffset;
    DWORD nPrevOffset = nOffset;

    Seek(0, SeekPosition::begin);
    Read(&m_nNextFreeOffset, 4);

    while (nCurrOffset != -1) {
        nPrevOffset = nCurrOffset;

        Seek(nCurrOffset, SeekPosition::begin);
        Read(&entry, sizeof(CTlkFileOverrideTextEntry));

        nCurrOffset = entry.m_nNextOffset;
        memset(entry.m_text, 0, 512);

        Seek(nPrevOffset, SeekPosition::begin);
        Write(&entry, sizeof(CTlkFileOverrideTextEntry));
    }

    entry.m_nNextOffset = m_nNextFreeOffset;
    Seek(nPrevOffset, SeekPosition::begin);
    Write(&entry, sizeof(CTlkFileOverrideTextEntry));

    m_nNextFreeOffset = nOffset;
    Seek(0, SeekPosition::begin);
    Write(&m_nNextFreeOffset, 4);
}

// 0x7B6650
void CTlkFileOverrideText::GetString(DWORD nOffset, CString& sString)
{
    CString sTemp;
    char buffer[513];
    CTlkFileOverrideTextEntry entry;

    while (nOffset != -1) {
        DWORD nPrevOffset = nOffset;

        Seek(nOffset, SeekPosition::begin);
        Read(&entry, sizeof(entry));

        nOffset = entry.m_nNextOffset;

        buffer[512] = '\0';
        memcpy(buffer, entry.m_text, 512);

        sTemp += buffer;
    }

    sTemp.TrimRight();
    sString = sTemp;
}

// -----------------------------------------------------------------------------

// #binary-identical
// 0x7B5CA0
CTlkFileOverrideHeader::CTlkFileOverrideHeader()
{
    memset(&m_header, 0, sizeof(m_header));

    m_bOpen = FALSE;

    m_nEntryCount = 60;
    m_ppEntries = new CTlkFileOverrideHeaderEntry*[m_nEntryCount];

    for (int k = 0; k < m_nEntryCount; k++) {
        m_ppEntries[k] = 0;
    }
}

// #binary-identical
// 0x7B5D50
CTlkFileOverrideHeader::~CTlkFileOverrideHeader()
{
    if (m_ppEntries != NULL) {
        for (int k = 0; k < m_nEntryCount; k++) {
            if (m_ppEntries[k] != NULL) {
                delete m_ppEntries[k];
            }
        }

        delete m_ppEntries;
        m_ppEntries = NULL;
    }
}

// 0x7B5DE0
BOOLEAN CTlkFileOverrideHeader::Unmarshal()
{
    int index;
    UINT nBytesRead;

    Seek(0, SeekPosition::begin);

    nBytesRead = Read(&m_header, sizeof(CTlkFileOverrideHeaderFileHeader));
    if (nBytesRead != 0) {
        if (nBytesRead != sizeof(CTlkFileOverrideHeaderFileHeader)) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTblOverride.cpp
            // __LINE__: 933
            UTIL_ASSERT(FALSE);
        }

        if (memcmp(&(m_header.nFileType), "TLK ", 4) != 0) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTblOverride.cpp
            // __LINE__: 942
            UTIL_ASSERT(FALSE);
        }

        INT nNewEntryCount = 150 * m_header.nEntryCount / 100;
        if (nNewEntryCount <= 150) {
            nNewEntryCount = 150;
        }

        if (m_ppEntries != NULL) {
            for (index = 0; index < m_nEntryCount; index++) {
                if (m_ppEntries[index] != NULL) {
                    delete m_ppEntries[index];
                }
            }

            delete m_ppEntries;
            m_ppEntries = NULL;
        }

        m_nEntryCount = nNewEntryCount;
        m_ppEntries = new CTlkFileOverrideHeaderEntry*[m_nEntryCount];

        for (index = 0; index < m_nEntryCount; index++) {
            m_ppEntries[index] = NULL;
        }

        // NOTE: Signed compare.
        for (index = 0; index < static_cast<int>(m_header.nEntryCount); index++) {
            if (sizeof(CTlkFileOverrideHeaderEntry) * index + sizeof(CTlkFileOverrideHeaderFileHeader) > GetLength()) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTblOverride.cpp
                // __LINE__: 970
                UTIL_ASSERT_MSG(FALSE, "Corrupt Override file");
            }

            Seek(sizeof(CTlkFileOverrideHeaderEntry) * index + sizeof(CTlkFileOverrideHeaderFileHeader), SeekPosition::begin);

            CTlkFileOverrideHeaderEntry* pKey = new CTlkFileOverrideHeaderEntry;
            nBytesRead = Read(pKey, sizeof(CTlkFileOverrideHeaderEntry));
            if (nBytesRead != sizeof(CTlkFileOverrideHeaderEntry)) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTblOverride.cpp
                // __LINE__: 996
                UTIL_ASSERT_MSG(FALSE, "Corrupt Override file");
            }

            AddKey(pKey);
        }
    } else {
        if (m_ppEntries != NULL) {
            for (index = 0; index < m_nEntryCount; index++) {
                if (m_ppEntries[index] != NULL) {
                    delete m_ppEntries[index];
                }
            }

            delete m_ppEntries;
            m_ppEntries = NULL;
        }

        m_nEntryCount = 150;
        m_ppEntries = new CTlkFileOverrideHeaderEntry*[m_nEntryCount];

        for (index = 0; index < m_nEntryCount; index++) {
            m_ppEntries[index] = NULL;
        }
    }

    return FALSE;
}

// 0x7B6070
BOOL CTlkFileOverrideHeader::AddKey(CTlkFileOverrideHeaderEntry* pKey)
{
    BOOL bDone = FALSE;
    INT nIndex = pKey->strId % m_nEntryCount;
    while (!bDone) {
        if (m_ppEntries[nIndex] == NULL) {
            m_ppEntries[nIndex] = pKey;
            return TRUE;
        }

        if (m_ppEntries[nIndex]->strId == pKey->strId || (pKey->dwFlags & 0x8000) != 0) {
            delete m_ppEntries[nIndex];
            m_ppEntries[nIndex] = pKey;
            return TRUE;
        }

        nIndex++;
        if (nIndex >= m_nEntryCount) {
            nIndex = 0;
        }

        if (nIndex == pKey->strId % m_nEntryCount) {
            bDone = TRUE;
        }
    }

    CTlkFileOverrideHeaderEntry** ppNewKeys = new CTlkFileOverrideHeaderEntry*[m_nEntryCount + 1];

    for (nIndex = 0; nIndex < m_nEntryCount; nIndex++) {
        ppNewKeys[nIndex] = m_ppEntries[nIndex];
    }

    ppNewKeys[m_nEntryCount] = pKey;

    delete m_ppEntries;
    m_ppEntries = ppNewKeys;

    // FIXME: Returns `FALSE` which is correct for this bugged implementation
    // since `m_nEntryCount` is not incremented, which means `FindKey` will
    // never iterate far enough to check for it.

    return FALSE;
}

// 0x7B6140
CTlkFileOverrideHeaderEntry* CTlkFileOverrideHeader::FindKey(DWORD strId)
{
    BOOL bDone = FALSE;
    INT nIndex = strId % m_nEntryCount;
    while (!bDone) {
        if (m_ppEntries[nIndex] == NULL) {
            break;
        }

        if (m_ppEntries[nIndex]->strId == strId) {
            if ((m_ppEntries[nIndex]->dwFlags & 0x8000) == 0) {
                return m_ppEntries[nIndex];
            } else {
                return NULL;
            }
        }

        nIndex++;
        if (nIndex >= m_nEntryCount) {
            nIndex = 0;
        }

        if (nIndex == strId % m_nEntryCount) {
            bDone = TRUE;
        }
    }

    return NULL;
}

// 0x7B6190
void CTlkFileOverrideHeader::Marshal()
{
    Seek(0, SeekPosition::begin);

    int writtenEntries = 0;
    int writtenBytes = 0;

    for (int index = 0; index < m_nEntryCount; index++) {
        if (m_ppEntries[index] != NULL) {
            Seek(sizeof(CTlkFileOverrideHeaderEntry) * writtenEntries + sizeof(CTlkFileOverrideHeaderFileHeader), SeekPosition::begin);
            Write(m_ppEntries[index], sizeof(CTlkFileOverrideHeaderEntry));
            writtenEntries++;
            writtenBytes += sizeof(CTlkFileOverrideHeaderEntry);
        }
    }

    Seek(0, SeekPosition::begin);
    m_header.nEntryCount = writtenEntries;
    memcpy(&(m_header.nFileType), "TLK ", 4);
    Write(&m_header, sizeof(CTlkFileOverrideHeaderFileHeader));
    SetLength(writtenBytes + sizeof(CTlkFileOverrideHeaderFileHeader));
}

// -----------------------------------------------------------------------------

// 0x7B5690
BOOLEAN CTlkFileOverride::Fetch(DWORD strId, STR_RES& strRes)
{
    if (!m_header.m_bOpen || !m_text.m_bOpen) {
        return FALSE;
    }

    CTlkFileOverrideHeaderEntry* pKey = m_header.FindKey(strId);
    if (pKey == NULL) {
        return FALSE;
    }

    if ((pKey->dwFlags & ENTRY_HAVE_SOUND) != 0) {
        strRes.cSound.SetResRef(CResRef(pKey->sndResRef), TRUE, TRUE);
        strRes.cSound.m_nPitchVariance = pKey->pitchVariance;
        strRes.cSound.m_nVolumeVariance = pKey->volumeVariance;
    } else {
        strRes.cSound.SetResRef(CResRef(""), TRUE, TRUE);
        strRes.cSound.m_nPitchVariance = pKey->pitchVariance;
        strRes.cSound.m_nVolumeVariance = pKey->volumeVariance;
    }

    if ((pKey->dwFlags & ENTRY_HAVE_TEXT) != 0) {
        m_text.GetString(pKey->offsetToStr, strRes.szText);
    }

    return TRUE;
}

// 0x7B58D0
void CTlkFileOverride::AddUserEntry(DWORD strId, STR_RES& strRes)
{
    if (m_header.m_bOpen && m_text.m_bOpen) {
        if (m_header.FindKey(strId) != NULL) {
            // NOTE: Uninline.
            Remove(strId);
        }

        CTlkFileOverrideHeaderEntry* pKey = new CTlkFileOverrideHeaderEntry;
        pKey->strId = strId;
        pKey->dwFlags = 0;

        if (strRes.szText != "") {
            pKey->dwFlags |= ENTRY_HAVE_TEXT;
        }

        if (strRes.cSound.GetResRef() != "") {
            pKey->dwFlags |= ENTRY_HAVE_SOUND;
        }

        strRes.cSound.GetResRef().GetResRef(pKey->sndResRef);

        pKey->volumeVariance = strRes.cSound.m_nVolumeVariance;
        pKey->pitchVariance = strRes.cSound.m_nPitchVariance;

        if (strRes.szText != "") {
            pKey->offsetToStr = m_text.AddString(strRes.szText);
        }

        m_header.AddKey(pKey);
    }
}

// 0x7B5A00
void CTlkFileOverride::Remove(DWORD strId)
{
    if (m_header.m_bOpen && m_text.m_bOpen) {
        CTlkFileOverrideHeaderEntry* pExistingKey = m_header.FindKey(strId);
        if (pExistingKey != NULL) {
            pExistingKey->dwFlags |= 0x8000;

            if ((pExistingKey->dwFlags & ENTRY_HAVE_TEXT) != 0) {
                m_text.RemoveString(pExistingKey->offsetToStr);
            }
        }
    }
}

// 0x7B5A50
void CTlkFileOverride::Open(const CString& sHeaderFileName, const CString& sTextFileName)
{
    m_header.m_bOpen = m_header.Open(sHeaderFileName, CFile::OpenFlags::modeReadWrite | CFile::OpenFlags::modeCreate | CFile::OpenFlags::modeNoTruncate, NULL);
    if (m_header.m_bOpen) {
        m_header.Unmarshal();

        m_text.m_bOpen = m_text.Open(sTextFileName, CFile::OpenFlags::modeReadWrite | CFile::OpenFlags::modeCreate | CFile::OpenFlags::modeNoTruncate, NULL);
    } else {
        m_text.m_bOpen = FALSE;
    }
}

// 0x7B5B00
void CTlkFileOverride::Save()
{
    if (m_header.m_bOpen) {
        m_header.Marshal();
    }
}

// 0x7B5B10
DWORD CTlkFileOverride::Add(const CString& sText)
{
    DWORD strId = 2999999;
    do {
        strId++;
    } while (m_header.FindKey(strId) != NULL);

    CTlkFileOverrideHeaderEntry* pKey = new CTlkFileOverrideHeaderEntry;
    pKey->volumeVariance = 0;
    pKey->pitchVariance = 0;
    pKey->offsetToStr = 0;
    pKey->dwFlags = ENTRY_HAVE_TEXT;

    if (m_header.m_bOpen && m_text.m_bOpen) {
        if (m_header.FindKey(strId) != NULL) {
            // NOTE: Uninline.
            Remove(strId);
        }

        // NOTE: Looks like inlining.
        CTlkFileOverrideHeaderEntry* pCopy = new CTlkFileOverrideHeaderEntry;
        memcpy(pCopy, pKey, sizeof(CTlkFileOverrideHeaderEntry));

        if (sText != "") {
            pCopy->offsetToStr = m_text.AddString(sText);
        }

        pCopy->strId = strId;
        m_header.AddKey(pCopy);
    }

    delete pKey;

    return strId;
}

// 0x7B5C30
void CTlkFileOverride::CloseFiles()
{
    if (m_header.m_bOpen) {
        m_header.Close();
        m_header.m_bOpen = FALSE;
    }

    if (m_text.m_bOpen) {
        m_text.Close();
        m_text.m_bOpen = FALSE;
    }
}

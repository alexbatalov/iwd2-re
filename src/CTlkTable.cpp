#include "CTlkTable.h"

#include "CUtil.h"

// 0x85DD64
const DWORD CTlkTable::dword_85DD64 = 0xFF000000;

// 0x85DD68
const BYTE CTlkTable::byte_85DD68 = 24;

// 0x85DD6C
const DWORD CTlkTable::dword_85DD6C = 0x00FFFFFF;

// NOTE: Probably static in `CTlkTable`.
//
// 0x8FB954
unsigned char byte_8FB954;

// 0x8FB955
BOOLEAN CTlkTable::STRREF_ON;

// NOTE: Inlined in `CTlkTable::AddTlkFile`.
CTlkFile::CTlkFile()
{
    memset(&m_header, 0, sizeof(TLK_FILE_HEADER));
    m_bOpened = FALSE;
}

// #binary-identical
// 0x793DB0
CTlkTable::CTlkTable()
{
    field_A4 = 0;
    field_58 = byte_8FB954;
}

// 0x793E90
BOOL CTlkTable::OpenOverride(const CString& a1, const CString& a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x793EB0
CTlkTable::~CTlkTable()
{
    POSITION pos;
    USHORT key;
    CTlkFile* pFile;
    CString sToken;
    CString sValue;

    pos = m_mapTlkFiles.GetStartPosition();
    while (pos != NULL) {
        m_mapTlkFiles.GetNextAssoc(pos, key, pFile);
        if (pFile != NULL) {
            if (pFile->m_bOpened) {
                // NOTE: Uninline.
                CloseFile((key >> 8) & 0xFF, key & 0xFF);
            }

            if (pFile != NULL) {
                delete pFile;
            }

            m_mapTlkFiles.RemoveKey(key);
        }
    }

    pos = m_mapTokens.GetStartPosition();
    while (pos != NULL) {
        m_mapTokens.GetNextAssoc(pos, sToken, sValue);
        m_mapTokens.RemoveKey(sToken);
    }
}

// 0x7940C0
BOOL CTlkTable::AddTlkFile(const CString& filePath, BYTE a3, BYTE a4, BOOLEAN bOpen)
{
    CTlkFile* pFile = new CTlkFile();
    pFile->SetFilePath(filePath);

    USHORT key = (a4 << 8) | a3;
    m_mapTlkFiles[key] = pFile;

    if (bOpen) {
        return OpenFile(a3, a4);
    }

    return TRUE;
}

// 0x7941D0
BOOLEAN CTlkTable::Fetch(DWORD dwStrId, STR_RES& strRes)
{
    CSingleLock lock(&field_38, FALSE);
    lock.Lock(INFINITE);

    CString sText;

    if (dwStrId == -1 || ((dwStrId & dword_85DD64) >> byte_85DD68) == 255) {
        strRes.szText = "";
        strRes.cSound.SetResRef(CResRef(""), FALSE, TRUE);
        strRes.cSound.m_nPitchVariance = 0;
        strRes.cSound.m_nVolumeVariance = 0;

        lock.Unlock();
        return TRUE;
    }

    if (m_override.Fetch(dwStrId, strRes)) {
        lock.Unlock();
        return TRUE;
    }

    CTlkFile* pFile;
    USHORT key = (field_58 << 8) | ((dwStrId & dword_85DD64) >> byte_85DD68);
    if (!m_mapTlkFiles.Lookup(key, pFile) || !pFile->m_bOpened) {
        strRes.szText = "";
        strRes.cSound.SetResRef(CResRef(""), FALSE, TRUE);
        strRes.cSound.m_nPitchVariance = 0;
        strRes.cSound.m_nVolumeVariance = 0;

        lock.Unlock();
        return FALSE;
    }

    size_t nEntryOffset = sizeof(STR_RES_HEADER) * (dwStrId & dword_85DD6C) + sizeof(TLK_FILE_HEADER);
    if (nEntryOffset > pFile->GetLength()) {
        // NOTE: `strRes` is not reset.
        lock.Unlock();
        return FALSE;
    }

    pFile->Seek(nEntryOffset, CFile::SeekPosition::begin);

    STR_RES_HEADER strResHeader;
    if (pFile->Read(&strResHeader, sizeof(strResHeader)) != sizeof(strResHeader)) {
        // NOTE: `strRes` is not reset.
        lock.Unlock();
        return FALSE;
    }

    if ((strResHeader.wFlags & 0x2) != 0) {
        strRes.cSound.SetResRef(CResRef(strResHeader.sndResRef), FALSE, TRUE);
        strRes.cSound.m_nPitchVariance = strResHeader.pitchVariance;
        strRes.cSound.m_nVolumeVariance = strResHeader.volumeVariance;
    } else {
        strRes.cSound.SetResRef(CResRef(""), FALSE, TRUE);
        strRes.cSound.m_nPitchVariance = 0;
        strRes.cSound.m_nVolumeVariance = 0;
    }

    if ((strResHeader.wFlags & 0x1) != 0) {
        size_t nStringOffset = pFile->m_header.nStrEntriesOffset + strResHeader.offsetToStr;
        if (nStringOffset > pFile->GetLength()) {
            strRes.szText = "";
            strRes.cSound.SetResRef(CResRef(""), FALSE, TRUE);
            strRes.cSound.m_nPitchVariance = 0;
            strRes.cSound.m_nVolumeVariance = 0;

            lock.Unlock();
            return FALSE;
        }

        pFile->Seek(nStringOffset, CFile::SeekPosition::begin);

        UINT nRead = pFile->Read(sText.GetBuffer(strResHeader.strSize), strResHeader.strSize);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTbl.cpp
        // __LINE__: 536
        UTIL_ASSERT_MSG(nRead == strResHeader.strSize, "Invalid strref passed to talk table fetch");

        sText.ReleaseBuffer(nRead);

        ParseStr(sText);

        if (STRREF_ON) {
            CString sFormatted;
            sFormatted.Format("%ld : %s", dwStrId & dword_85DD64, sText);
            sText = sFormatted;
        }

        strRes.szText = sText;
    } else {
        strRes.szText.Empty();
    }

    lock.Unlock();
    return TRUE;
}

// 0x794190
BOOL CTlkTable::CloseFile(BYTE a2, BYTE a3)
{
    CTlkFile* pFile;

    USHORT key = (a3 << 8) | a2;
    if (!m_mapTlkFiles.Lookup(key, pFile)) {
        return FALSE;
    }

    if (pFile->m_bOpened) {
        pFile->Close();
        pFile->m_bOpened = FALSE;
    }

    return TRUE;
}

// 0x794930
BOOL CTlkTable::OpenFile(BYTE a2, BYTE a3)
{
    CTlkFile* pFile;

    USHORT key = (a3 << 8) | a2;
    if (!m_mapTlkFiles.Lookup(key, pFile)) {
        return FALSE;
    }

    if (pFile->m_bOpened) {
        return TRUE;
    }

    if (!pFile->Open(pFile->GetFilePath(), CFile::OpenFlags::modeRead | CFile::OpenFlags::shareDenyWrite)) {
        return FALSE;
    }

    pFile->Seek(0, CFile::SeekPosition::begin);

    if (pFile->Read(&(pFile->m_header), sizeof(TLK_FILE_HEADER)) != sizeof(TLK_FILE_HEADER)) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTbl.cpp
        // __LINE__: 90
        UTIL_ASSERT(FALSE);
    }

    if (memcmp(&(pFile->m_header.nFileType), "TLK ", 4) != 0) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTbl.cpp
        // __LINE__: 97
        UTIL_ASSERT(FALSE);
    }

    pFile->m_bOpened = TRUE;

    return TRUE;
}

// 0x794A50
void CTlkTable::ParseStr(CString& sText)
{
    CString sValue;

    for (int nIndex = 0; nIndex < sText.GetLength(); nIndex++) {
        // NOTE: Looks unused.
        GetSystemDefaultLangID();

        if (IsDBCSLeadByte(sText[nIndex])) {
            nIndex++;
            continue;
        }

        switch (sText[nIndex]) {
        case '\r':
            sText = sText.Left(nIndex)
                + sText.Right(sText.GetLength() - nIndex - 1);
            break;
        case '<':
            if (1) {
                int nStart = nIndex;
                if (sText[nIndex + 1] == '<') {
                    nStart++;
                }

                int nEnd = sText.Right(sText.GetLength() - nStart).Find('>');
                if (nEnd != -1) {
                    CString sToken = sText.Mid(nStart + 1, nEnd - 1);
                    CUtil::TrimLeft(sToken);
                    CUtil::TrimRight(sToken);

                    m_mapTokens.Lookup(sToken, sValue);

                    if (sText.GetLength() > nEnd + nIndex + 1
                        && sText[nEnd + nIndex + 1] == '>') {
                        nEnd++;
                    }

                    sText = sText.Left(nIndex)
                        + sValue
                        + sText.Right(sText.GetLength() - nStart - nEnd - 1);

                    nIndex += sValue.GetLength();
                }
            }
            break;
        case '[':
            if (1) {
                int nEnd = sText.Find(']', nIndex);
                if (nEnd != -1) {
                    sText = sText.Left(nIndex)
                        + sText.Right(sText.GetLength() - nEnd - 1);
                }
            }
            break;
        case '\\':
            sText = sText.Left(nIndex)
                + sText.Right(sText.GetLength() - nIndex - 1);
            break;
        }
    }

    if (sText.GetLength() != 0 && sText[sText.GetLength() - 1] == '\n') {
        sText = sText.Left(sText.GetLength() - 1);
    }
}

// NOTE: Inlined.
void CTlkTable::SetToken(const CString& sKey, const CString& sValue)
{
    m_mapTokens.SetAt(sKey, sValue);
}

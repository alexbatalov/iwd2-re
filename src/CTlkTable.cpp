#include "CTlkTable.h"

#include "CUtil.h"

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

// 0x793EB0
CTlkTable::~CTlkTable()
{
    // TODO: Incomplete.
}

// 0x7940C0
BOOL CTlkTable::AddTlkFile(const CString& filePath, BYTE a3, BYTE a4, BOOLEAN a5)
{
    CTlkFile* pFile = new CTlkFile();
    pFile->SetFilePath(filePath);

    USHORT key = (a4 << 8) | a3;
    field_0[key] = pFile;

    if (a5) {
        return OpenFile(a3, a4);
    }

    return TRUE;
}

// 0x7941D0
BOOLEAN CTlkTable::Fetch(DWORD dwStrId, STR_RES& strRes)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x794190
BOOL CTlkTable::CloseFile(BYTE a2, BYTE a3)
{
    CTlkFile* pFile;

    USHORT key = (a3 << 8) | a2;
    if (!field_0.Lookup(key, pFile)) {
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
    if (!field_0.Lookup(key, pFile)) {
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

    if (pFile->m_header.nFileType != 'TLK ') {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChTlkTbl.cpp
        // __LINE__: 97
        UTIL_ASSERT(FALSE);
    }

    pFile->m_bOpened = TRUE;

    return TRUE;
}

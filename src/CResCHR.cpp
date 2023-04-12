#include "CResCHR.h"

#include "CUtil.h"

// 0x402220
CResCHR::CResCHR()
{
    m_bParsed = FALSE;
}

// 0x402260
CResCHR::~CResCHR()
{
}

// 0x402270
void* CResCHR::Demand()
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

// 0x4022B0
int CResCHR::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
    }
    return rc;
}

// 0x4022E0
BOOL CResCHR::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    EXPORT_CHARACTER_HEADER* header = reinterpret_cast<EXPORT_CHARACTER_HEADER*>(pData);
    if (header->nFileType != 'CHR ') {
        // NOTE: Looks like deviation from similar `Parse` methods.
        return FALSE;
    }

    if (memcmp(pData, "CHR V2.2", 8) != 0) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 2182
        // FIXME: Typo in extension, should be "CHR".
        UTIL_ASSERT_MSG(FALSE, CString("Character file version isn't ") + CString("CHR V2.2") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".CRE"));
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

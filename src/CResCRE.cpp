#include "CResCRE.h"

#include "CUtil.h"

// 0x401EC0
CResCRE::CResCRE()
{
    m_bParsed = FALSE;
}

// 0x401F00
CResCRE::~CResCRE()
{
}

// 0x401F10
void* CResCRE::Demand()
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

// 0x401F50
BOOL CResCRE::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    CREATURE_HEADER* header = reinterpret_cast<CREATURE_HEADER*>(pData);
    if (header->nFileType != 'CRE ') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1967
        UTIL_ASSERT_MSG(FALSE, CString("Creature file has invalid header (!CRE ): ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".CRE"));
    }

    if (header->nFileVersion != 'V2.2' && header->nFileVersion != 'V2.0') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1981
        UTIL_ASSERT_MSG(FALSE, CString("Creature file version isn't ") + CString("V2.2") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".CRE"));
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

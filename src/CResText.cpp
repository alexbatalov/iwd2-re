#include "CResText.h"

#include "CCrypt.h"

// 0x780800
CResText::CResText()
{
    m_bParsed = FALSE;
    field_54 = 0;
}

// 0x780850
CResText::~CResText()
{
}

// 0x7808E0
void* CResText::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        // NOTE: Uninline.
        Parse(pData);

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// NOTE: Inlined in `CResText::Demand`.
BOOL CResText::Parse(void* pData)
{
    m_string = ParseText(pData);

    // TODO: Not sure where it is actually set.
    return m_bParsed;
}

// 0x780970
CString CResText::ParseText(void* pData)
{
    CString cString;
    CCrypt cCrypt;

    if (pData != NULL) {
        INT nTmpSize = m_nResSizeActual;
        cCrypt.DecryptText(reinterpret_cast<CHAR*>(pData), nTmpSize);
        cString = CString(reinterpret_cast<CHAR*>(pData), nTmpSize);
    } else {
        cString = "";
    }

    return cString;
}

// 0x780A40
int CResText::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
    }
    return rc;
}

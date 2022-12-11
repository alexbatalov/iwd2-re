#include "CRes.h"

#include "CChitin.h"

// #binary-identical
// 0x77E250
CRes::CRes()
{
    m_pCurrentListPos = NULL;
    field_40 = 0;
    m_nID = 0;
    field_44 = 0;
    field_14 = 0;
    field_1C = 0;
    m_pData = NULL;
    m_pDimmKeyTableEntry = NULL;
    m_pCurrentList = NULL;
    field_18 = 0;
    dwFlags = 0;
}

// #binary-identical
// 0x77E2F0
CRes::~CRes()
{
    field_1C = 0;
    g_pChitin->cDimm.Dump(this, 1, 0);
}

// 0x78E6E0
BOOL CRes::OnResourceFreed()
{
    return FALSE;
}

// 0x78E730
void CRes::OnResourceServiced()
{
}

// #guess
// 0x4010C0
int CRes::GetFixedResourceSize()
{
    return -1;
}

// 0x78E6E0
int CRes::GetFixedResourceDataOffset()
{
    return 0;
}

// #binary-identical
// 0x77E370
int CRes::CancelRequest()
{
    return g_pChitin->cDimm.CancelRequest(this);
}

// 0x77E520
int CRes::Dump(int a2)
{
    field_1C = 0;
    return g_pChitin->cDimm.Dump(this, a2, 0);
}

// 0x77E550
int CRes::GetDemands()
{
    return field_40;
}

// 0x77E560
RESID CRes::GetID()
{
    return m_nID;
}

// 0x77E570
CResRef CRes::GetResRef()
{
    CResRef resRef;

    if (m_pDimmKeyTableEntry != NULL && !m_pDimmKeyTableEntry->resRef.IsValid()) {
        resRef = m_pDimmKeyTableEntry->resRef;
    } else {
        resRef = "";
    }

    return resRef;
}

// #guess
// 0x77E5D0
USHORT CRes::GetType()
{
    if (m_pDimmKeyTableEntry != NULL) {
        return m_pDimmKeyTableEntry->field_12;
    }

    return 0xFFFF;
}

// 0x77E5F0
int CRes::Release()
{
    return g_pChitin->cDimm.Release(this);
}

// 0x77E610
int CRes::Request()
{
    return g_pChitin->cDimm.Request(this);
}

// 0x77E630
void CRes::SetID(RESID nNewID)
{
    if (m_nID != 0) {
        field_1C = 0;
        g_pChitin->cDimm.Dump(this, 0, 0);
        m_nID = nNewID;
    } else {
        m_nID = nNewID;
    }
}

// 0x77E670
void CRes::SetPriority(unsigned int nNewPriority)
{
    g_pChitin->cDimm.SetNewPriority(this, nNewPriority);
}

// 0x77E690
BOOL CRes::Write(const CString& sFilePath, LPVOID lpBuf, DWORD dwSize)
{
    return g_pChitin->cDimm.WriteResourceWithData(sFilePath, this, lpBuf, dwSize);
}

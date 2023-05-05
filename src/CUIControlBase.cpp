#include "CUIControlBase.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x84C89C
const BYTE CUIControlBase::byte_84C89C = 0;

// 0x84C89D
const BYTE CUIControlBase::byte_84C89D = 1;

// 0x84C89E
const BYTE CUIControlBase::byte_84C89E = 2;

// 0x4D23B0
CUIControlBase::CUIControlBase(CUIPanel* pPanel, UI_CONTROL* controlInfo, int a4)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUI.cpp
    // __LINE__: 104
    UTIL_ASSERT(controlInfo != NULL);

    field_4 = 0;

    m_pPanel = pPanel;
    m_nID = controlInfo->nID;

    if (pPanel->m_pManager->m_bDoubleSize) {
        m_nX = controlInfo->x * 2;
        m_nY = controlInfo->y * 2;
        m_nWidth = controlInfo->nWidth * 2;
        m_nHeight = controlInfo->nHeight * 2;
    } else {
        m_nX = controlInfo->x;
        m_nY = controlInfo->y;
        m_nWidth = controlInfo->nWidth;
        m_nHeight = controlInfo->nHeight;
    }

    m_bActive = TRUE;

    field_22.SetRect(0, 0, 0, 0);

    m_nToolTipStrRef = -1;
    m_nSecondaryToolTipStrRef = -1;
    m_nTertiaryToolTipStrRef = -1;
    field_36 = a4;
    field_20 = 0;
    m_bInactiveRender = FALSE;
    m_bToolTipActive = FALSE;
    m_nToolTipHotKeyIndex1 = -1;
    m_nToolTipHotKeyIndex2 = -1;
    m_sKey = "";

    if ((controlInfo->nType & 0x100) != 0) {
        m_bNeedAsyncUpdate = TRUE;
        m_pPanel->m_bNeedAsyncUpdate = TRUE;
    } else {
        m_bNeedAsyncUpdate = FALSE;
    }
}

// 0x4D2590
CUIControlBase::~CUIControlBase()
{
}

// 0x4D24E0
void CUIControlBase::SetActive(BOOLEAN bActive)
{
    m_bActive = bActive;
}

// 0x4D24F0
BOOL CUIControlBase::IsOverPixel(const CPoint& pt)
{
    return TRUE;
}

// 0x78E730
void CUIControlBase::KillFocus()
{
}

// 0x78E730
void CUIControlBase::SetFocus()
{
}

// 0x778900
void CUIControlBase::OnMouseMove(CPoint pt)
{
}

// 0x4051C0
BOOL CUIControlBase::OnLButtonDown(CPoint pt)
{
    return FALSE;
}

// 0x778900
void CUIControlBase::OnLButtonUp(CPoint pt)
{
}

// 0x4051C0
BOOL CUIControlBase::OnLButtonDblClk(CPoint pt)
{
    return FALSE;
}

// 0x4051C0
BOOL CUIControlBase::OnRButtonDown(CPoint pt)
{
    return FALSE;
}

// 0x778900
void CUIControlBase::OnRButtonUp(CPoint pt)
{
}

// 0x799E60
void CUIControlBase::OnKeyDown(short nKey)
{
}

// 0x4D25B0
void CUIControlBase::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_bActive || m_bInactiveRender) {
        if (bInside) {
            if (m_bActive || m_bInactiveRender) {
                if (m_pPanel->m_bActive) {
                    if (!m_bToolTipActive || g_pBaldurChitin->m_pObjectCursor->m_nCurrentCursor != 101) {
                        if (m_pPanel->m_pManager->field_76
                            || (g_pBaldurChitin->m_pObjectGame->m_cOptions.m_nTooltips != INT_MAX
                                && m_pPanel->m_pManager->field_1C >= g_pBaldurChitin->m_pObjectGame->m_cOptions.m_nTooltips)) {
                            ActivateToolTip();
                            m_bToolTipActive = TRUE;
                        }
                    }
                }
            }
        }
    }
}

// 0x4D2500
int CUIControlBase::GetToolTipStrRef()
{
    return m_nToolTipStrRef;
}

// #guess
// 0x4D2510
int CUIControlBase::GetSecondaryToolTipStrRef()
{
    return m_nSecondaryToolTipStrRef;
}

// #guess
// 0x45B4B0
int CUIControlBase::GetTertiaryToolTipStrRef()
{
    return m_nTertiaryToolTipStrRef;
}

// 0x4D2520
void CUIControlBase::ResetToolTip()
{
    m_bToolTipActive = FALSE;
}

// 0x4D26C0
void CUIControlBase::SetToolTipStrRef(STRREF strRef, STRREF secondaryStrRef, STRREF tertiaryStrRef)
{
    m_nToolTipStrRef = strRef;
    m_nSecondaryToolTipStrRef = secondaryStrRef;
    m_nTertiaryToolTipStrRef = tertiaryStrRef;

    if (strRef == -1) {
        SetToolTipHotKey(0xFFFF, 0xFFFF, CString(""));
    }
}

// 0x4D2530
void CUIControlBase::SetToolTipHotKey(USHORT nHotKeyIndex1, USHORT nHotKeyIndex2, const CString& sKey)
{
    m_nToolTipHotKeyIndex1 = nHotKeyIndex1;
    m_nToolTipHotKeyIndex2 = nHotKeyIndex2;
    m_sKey = sKey;
}

// 0x4D2640
void CUIControlBase::ActivateToolTip()
{
    g_pBaldurChitin->GetObjectCursor()->SetToolTip(m_nToolTipStrRef,
        this,
        m_nToolTipHotKeyIndex1,
        m_nToolTipHotKeyIndex2,
        m_sKey,
        m_nSecondaryToolTipStrRef,
        m_nTertiaryToolTipStrRef);
}

// 0x78E730
void CUIControlBase::func_54()
{
}

// 0x4D2560
BOOL CUIControlBase::GetInactiveRender()
{
    return m_bInactiveRender;
}

void CUIControlBase::SetInactiveRender(BOOL bInactiveRender)
{
    m_bInactiveRender = bInactiveRender;
}

// 0x78E6E0
BOOL CUIControlBase::NeedRender()
{
    return FALSE;
}

// 0x77AB80
void CUIControlBase::SetNeedAsyncUpdate()
{
    m_bNeedAsyncUpdate = TRUE;
    m_pPanel->m_bNeedAsyncUpdate = TRUE;
}

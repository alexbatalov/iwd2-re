#include "CUIControlTextDisplay.h"

#include "CBaldurChitin.h"
#include "CUIControlScrollBar.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x8D7608
const CString CUIControlTextDisplay::DEFAULT_LABEL_SUFFIX("- ");

// 0x4E1A90
CUIControlTextDisplay::CUIControlTextDisplay(CUIPanel* pPanel, UI_CONTROL_TEXTDISPLAY* pControlInfo, BOOLEAN a3)
    : CUIControlBase(pPanel, &(pControlInfo->base), 1)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 5365
    UTIL_ASSERT(pPanel != NULL && pControlInfo != NULL);

    m_posTopString = NULL;
    m_nRenderCount = 0;
    field_A68 = 256;
    field_A6C = 0;
    field_5A = 0;
    m_nScrollBarID = pControlInfo->nScrollBarID;
    m_rgbHighlightColor = RGB(255, 255, 255);
    m_posHighlightedItem = NULL;
    m_sLabelSuffix = DEFAULT_LABEL_SUFFIX;
    field_AB4 = 0;
    field_5C = 0;

    if (a3) {
        m_plstStrings = new CTypedPtrList<CPtrList, CDisplayString*>();
    } else {
        m_plstStrings = NULL;
    }

    field_AB6 = a3;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 5391
    UTIL_ASSERT(pControlInfo->refTextFont[0] != 0);

    m_rgbLabelColor = pControlInfo->nLabelColor;
    m_rgbTextColor = pControlInfo->nTextColor;
    m_rgbBackgroundColor = pControlInfo->nBackgroundColor;

    m_textFont.SetResRef(CResRef(pControlInfo->refTextFont), m_pPanel->m_pManager->m_bDoubleSize, TRUE);

    if (m_rgbTextColor == m_rgbBackgroundColor) {
        field_AAF = TRUE;
    } else {
        m_textFont.SetColor(m_rgbTextColor, m_rgbBackgroundColor, FALSE);
        field_AAF = FALSE;
    }

    if (pControlInfo->refLabelFont[0] != 0) {
        m_labelFont.SetResRef(CResRef(pControlInfo->refLabelFont), m_pPanel->m_pManager->m_bDoubleSize, TRUE);

        if (m_rgbLabelColor == m_rgbBackgroundColor) {
            field_AAE = TRUE;
        } else {
            m_labelFont.SetColor(m_rgbLabelColor, m_rgbBackgroundColor, FALSE);
            field_AAE = FALSE;
        }
    }

    field_A62 = 0;

    CVidFont& font = m_textFont.GetFontHeight(FALSE) > m_labelFont.GetFontHeight(FALSE)
        ? m_textFont
        : m_labelFont;
    m_nFontHeight = font.GetFontHeight(FALSE);
    field_A64 = 0;
    field_A65 = 0;
    field_A66 = 0;
    field_A67 = 0;
    SetNeedAsyncUpdate();
    field_AB7 = 1;
    field_A6A = m_nHeight / m_nFontHeight;
}

// 0x4E1D50
BOOL CUIControlTextDisplay::NeedRender()
{
    return (m_bActive || m_bInactiveRender)
        && m_nRenderCount > 0
        && m_posTopString != NULL;
}

// 0x4E1DA0
CUIControlTextDisplay::~CUIControlTextDisplay()
{
    if (field_AB6) {
        POSITION pos = m_plstStrings->GetHeadPosition();
        while (pos != NULL) {
            CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
            if (pDisplayString != NULL) {
                delete pDisplayString;
            }
        }

        m_plstStrings->RemoveAll();

        delete m_plstStrings;
    }

    if (m_textFont.pRes != NULL) {
        m_textFont.pRes->CancelRequest();
    }

    if (m_labelFont.pRes != NULL) {
        m_labelFont.pRes->CancelRequest();
    }
}

// 0x4E1ED0
void CUIControlTextDisplay::SetActive(BOOLEAN bActive)
{
    m_bActive = bActive;

    if (bActive) {
        m_textFont.RegisterFont();
    } else {
        m_textFont.Unload();
    }
}

// 0x4E20F0
POSITION CUIControlTextDisplay::DisplayString(const CString& sLabel, const CString& sString, COLORREF rgbLabelColor, COLORREF rgbTextColor, LONG lMarker, BOOLEAN a6, BOOLEAN bTrim)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 5643
    UTIL_ASSERT(m_plstStrings != NULL);

    if (field_A6C >= field_A68) {
        RemoveString(m_plstStrings->GetHeadPosition());
    }

    SHORT nOldCount = m_plstStrings->GetCount();

    POSITION posTopString;
    SHORT v1 = ParseAndInsertStringAfter(m_plstStrings->GetTailPosition(),
        sLabel,
        sString,
        rgbLabelColor,
        rgbTextColor,
        lMarker,
        posTopString,
        bTrim);

    if (a6 || nOldCount == 0) {
        m_posTopString = posTopString;
        field_5A = m_plstStrings->GetCount() - v1;

        // NOTE: Uninline.
        AdjustScrollBar();
    } else {
        if (m_nScrollBarID == -1
            || !static_cast<CUIControlScrollBar*>(m_pPanel->GetControl(m_nScrollBarID))->field_146) {
            if (m_plstStrings->GetCount() - field_5A > field_A6A) {
                field_5A = max(nOldCount - field_A6A, 0);

                // NOTE: Uninline.
                AdjustScrollBar();

                m_posTopString = m_plstStrings->FindIndex(max(field_A6A, 0));
                if (m_posTopString == NULL) {
                    m_posTopString = m_plstStrings->GetTailPosition();
                }

                field_A65 = min(v1, field_A6A);
            }
        }
    }

    field_A6C++;
    field_A62 = 0;
    field_A64 = 0;

    CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
        CSize(m_nWidth, m_nHeight));
    m_pPanel->InvalidateRect(&rDirty);
    InvalidateRect();

    return posTopString;
}

// 0x4E22F0
void CUIControlTextDisplay::AdjustScrollBar()
{
    if (m_nScrollBarID != -1) {
        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(m_pPanel->GetControl(m_nScrollBarID));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_5A, m_plstStrings->GetCount(), field_A6A);
    }
}

// 0x4E23A0
void CUIControlTextDisplay::HighlightItem(POSITION posBossItem)
{
    if (posBossItem != m_posHighlightedItem) {
        if (posBossItem == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
            // __LINE__: 5816
            UTIL_ASSERT(FALSE);
        }

        POSITION pos = posBossItem;
        while (pos != NULL) {
            CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
            if (pDisplayString->GetBossPos() != posBossItem) {
                break;
            }

            m_rgbLabelColorBeforeHighlight = pDisplayString->m_rgbLabelColor;
            m_rgbTextColorBeforeHighlight = pDisplayString->m_rgbTextColor;
            pDisplayString->m_rgbLabelColor = m_rgbHighlightColor;
            pDisplayString->m_rgbTextColor = m_rgbHighlightColor;
        }

        m_posHighlightedItem = posBossItem;
        InvalidateRect();
    }
}

// 0x4E2420
void CUIControlTextDisplay::UnHighlightItem()
{
    if (m_posHighlightedItem != NULL) {
        POSITION pos = m_posHighlightedItem;
        while (pos != NULL) {
            CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
            if (pDisplayString->GetBossPos() != m_posHighlightedItem) {
                break;
            }

            pDisplayString->m_rgbLabelColor = m_rgbLabelColorBeforeHighlight;
            pDisplayString->m_rgbTextColor = m_rgbTextColorBeforeHighlight;
        }

        m_posHighlightedItem = NULL;
        InvalidateRect();
    }
}

// 0x4E2480
INT CUIControlTextDisplay::GetNumLines(POSITION posBossItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 5909
    UTIL_ASSERT(m_plstStrings->GetAt(posBossItem)->GetBossPos() == posBossItem);

    return m_plstStrings->GetAt(posBossItem)->GetNumLines();
}

// 0x4E24C0
void CUIControlTextDisplay::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount = CBaldurChitin::RENDER_COUNT;
        lock.Unlock();
    }
}

// 0x4E2550
void CUIControlTextDisplay::OnButtonLClick(CPoint ptMouseClick)
{
    ptMouseClick.y -= m_nY;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 6047
    UTIL_ASSERT(ptMouseClick.y >= 0);

    if (m_plstStrings != NULL) {
        INT nIndex = field_5A + (ptMouseClick.y + field_A62) / m_nFontHeight;
        if (nIndex < m_plstStrings->GetCount()) {
            OnItemSelected(m_plstStrings->GetAt(m_plstStrings->FindIndex(nIndex))->GetMarker());
        }
    }
}

// 0x4E25D0
BOOL CUIControlTextDisplay::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    m_pPanel->m_pManager->SetCapture(this, FALSE);

    return TRUE;
}

// 0x4E2600
void CUIControlTextDisplay::OnLButtonUp(CPoint pt)
{
    if (m_posHighlightedItem != NULL) {
        UnHighlightItem();
    }

    if (m_bActive) {
        if (pt.x >= m_nX && pt.x <= m_nX + m_nWidth
            && pt.y >= m_nY && pt.y <= m_nY + m_nHeight) {
            OnButtonLClick(pt);
        }
    }
}

// 0x4E2660
void CUIControlTextDisplay::OnMouseMove(CPoint pt)
{
    CPoint ptMouseClick = pt;
    ptMouseClick.y -= m_nY;

    if (m_bActive) {
        // NOTE: Original code is slightly different.
        BOOL bHighlighted = FALSE;

        if (pt.x >= m_nX && pt.x <= m_nX + m_nWidth
            && pt.y >= m_nY && pt.y <= m_nY + m_nHeight) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
            // __LINE__: 6168
            UTIL_ASSERT(ptMouseClick.y >= 0);

            if (m_plstStrings != NULL) {
                INT nIndex = field_5A + (ptMouseClick.y + field_A62) / m_nFontHeight;
                if (nIndex >= 0 && nIndex < m_plstStrings->GetCount()) {
                    CDisplayString* pDisplayString = m_plstStrings->GetAt(m_plstStrings->FindIndex(nIndex));
                    if (pDisplayString->m_lMarker != -1) {
                        UnHighlightItem();
                        HighlightItem(pDisplayString->GetBossPos());
                        bHighlighted = TRUE;
                    }
                }
            }
        }

        if (!bHighlighted) {
            if (m_posHighlightedItem != NULL) {
                UnHighlightItem();
            }
        }
    }
}

// 0x4E2790
void CUIControlTextDisplay::OnScroll(SHORT a1, SHORT a2)
{
    SHORT nOldIndex = field_5A;
    // TODO: Odd code, check.
    field_5A = max(m_plstStrings->GetCount() - field_A6A, 0) * a1 / a2;
    if (nOldIndex != field_5A) {
        m_posTopString = m_plstStrings->FindIndex(field_5A);

        CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
            CSize(m_nWidth, m_nHeight));
        m_pPanel->InvalidateRect(&rDirty);
        InvalidateRect();
    }
}

// 0x4E2830
void CUIControlTextDisplay::OnScrollDown()
{
    field_A64 = 0;
    if (field_5A < m_plstStrings->GetCount() - field_A6A) {
        if (field_A65) {
            field_A67 = 1;
        } else {
            field_A65 = 1;
        }
    }
}

// 0x4E2870
void CUIControlTextDisplay::OnScrollUp()
{
    field_A65 = 0;
    if (m_posTopString != m_plstStrings->GetHeadPosition() || field_A62) {
        if (field_A64) {
            field_A66 = 1;
        } else {
            field_A64 = 1;
        }
    }
}

// 0x4E28B0
void CUIControlTextDisplay::OnPageDown(DWORD a1)
{
    if (m_plstStrings->GetCount() > field_A6A) {
        SHORT nOldIndex = field_5A;
        // TODO: Check casts.
        SHORT v1 = static_cast<SHORT> min(a1, static_cast<DWORD>(field_A6A - 1));
        field_5A = max(field_5A + v1, m_plstStrings->GetCount() - field_A6A);
        if (nOldIndex != field_5A) {
            m_posTopString = m_plstStrings->FindIndex(field_5A);

            CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
                CSize(m_nWidth, m_nHeight));
            m_pPanel->InvalidateRect(&rDirty);
            InvalidateRect();
        }
    }

    // NOTE: Uninline.
    AdjustScrollBar();
}

// 0x4E2A00
void CUIControlTextDisplay::OnPageUp(DWORD a1)
{
    if (!m_plstStrings->IsEmpty()) {
        SHORT nOldIndex = field_5A;
        // TODO: Check casts.
        SHORT v1 = static_cast<SHORT> min(a1, static_cast<DWORD>(field_A6A - 1));
        field_5A = max(field_5A - v1, 0);
        if (nOldIndex != field_5A) {
            m_posTopString = m_plstStrings->FindIndex(field_5A);

            CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
                CSize(m_nWidth, m_nHeight));
            m_pPanel->InvalidateRect(&rDirty);
            InvalidateRect();
        }
    }

    // NOTE: Uninline.
    AdjustScrollBar();
}

// 0x4E2B50
void CUIControlTextDisplay::RemoveAll()
{
    CSingleLock lock(&field_A8E, FALSE);
    lock.Lock(INFINITE);

    POSITION pos = m_plstStrings->GetHeadPosition();
    while (pos != NULL) {
        CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
        if (pDisplayString != NULL) {
            delete pDisplayString;
        }
    }
    m_plstStrings->RemoveAll();

    lock.Unlock();

    CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
        CSize(m_nWidth, m_nHeight));
    m_pPanel->InvalidateRect(&rDirty);
    InvalidateRect();
}

// 0x4E2C60
void CUIControlTextDisplay::RemoveString(POSITION posBoss)
{
    CSingleLock lock(&field_A8E, FALSE);

    if (posBoss == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
        // __LINE__: 6478
        UTIL_ASSERT(FALSE);
    }

    lock.Lock(INFINITE);

    POSITION pos = posBoss;
    while (pos != NULL) {
        POSITION currentPos = pos;
        CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
        if (pDisplayString->GetBossPos() != posBoss) {
            break;
        }

        if (currentPos == m_posTopString) {
            m_posTopString = pos;
        }

        if (pDisplayString != NULL) {
            delete pDisplayString;
        }
    }

    field_A6C--;

    if (!m_plstStrings->IsEmpty()) {
        if (m_posTopString == NULL) {
            m_posTopString = m_plstStrings->GetTailPosition();
        }

        INT nIndex = 0;
        POSITION pos = m_plstStrings->GetHeadPosition();
        while (pos != NULL) {
            if (pos == m_posTopString) {
                break;
            }

            m_plstStrings->GetNext(pos);
            nIndex++;
        }

        field_5A = nIndex;

        // NOTE: Uninline.
        AdjustScrollBar();
    } else {
        m_posTopString = NULL;
        field_5A = 0;
        field_5C = 0;
    }

    lock.Unlock();

    CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
        CSize(m_nWidth, m_nHeight));
    m_pPanel->InvalidateRect(&rDirty);
    InvalidateRect();

    if (posBoss == m_posHighlightedItem) {
        m_posHighlightedItem = NULL;
    }
}

// 0x4E2E20
SHORT CUIControlTextDisplay::ParseAndInsertStringAfter(POSITION posInsertAfter, const CString& sLabel, const CString& sString, COLORREF rgbLabelColor, COLORREF rgbTextColor, LONG lMarker, POSITION& posBoss, BOOLEAN bTrim)
{
    SHORT nNumLines = 0;
    CDisplayString* pLastDisplayString = NULL;
    CString sStrings[2];
    SHORT nOffset = 3 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    CString sLabelCopy(sLabel);
    CString sStringCopy(sString);

    posBoss = NULL;

    m_textFont.pRes->Demand();
    m_labelFont.pRes->Demand();

    if (bTrim) {
        CUtil::TrimLeft(sStringCopy);
        CUtil::TrimRight(sStringCopy);
    }

    if (!sLabelCopy.IsEmpty()) {
        sLabelCopy += m_sLabelSuffix;

        if (field_AB7) {
            nOffset += m_labelFont.GetStringLength(sLabelCopy, TRUE);
        } else {
            sStringCopy = "\n" + sStringCopy;
        }
    }

    if (sStringCopy.IsEmpty()) {
        CDisplayString* pDisplayString = new CDisplayString();
        pDisplayString->m_sLabel = sLabelCopy;
        pDisplayString->m_sString = sStringCopy;
        pDisplayString->m_lMarker = lMarker;
        pDisplayString->m_rgbLabelColor = rgbLabelColor;
        pDisplayString->m_rgbTextColor = rgbTextColor;
        pDisplayString->m_nNumLines = 0;
        pDisplayString->m_nOffset = nOffset;
        pDisplayString->m_nLine = nNumLines++;

        posBoss = m_plstStrings->InsertAfter(posInsertAfter, pDisplayString);
        pDisplayString->m_posBoss = posBoss;

        pLastDisplayString = pDisplayString;
    }

    while (!sStringCopy.IsEmpty()) {
        if (field_AB4 != 0 && nNumLines >= field_AB4) {
            nOffset = 3 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        }

        SHORT nStrings = CUtil::SplitString(&m_textFont,
            sStringCopy,
            m_nWidth - 3 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1) - nOffset,
            2,
            sStrings,
            FALSE,
            TRUE,
            FALSE,
            -1);
        if (nStrings == 0) {
            break;
        }

        CDisplayString* pDisplayString = new CDisplayString();
        pDisplayString->m_sLabel = sLabelCopy;
        pDisplayString->m_sString = sStrings[0];
        pDisplayString->m_lMarker = lMarker;
        pDisplayString->m_rgbLabelColor = rgbLabelColor;
        pDisplayString->m_rgbTextColor = rgbTextColor;
        pDisplayString->m_nNumLines = 0;
        pDisplayString->m_nOffset = nOffset;
        pDisplayString->m_nLine = nNumLines;

        BOOL bFirstLine = nNumLines == 0;
        nNumLines++;
        if (bFirstLine) {
            posInsertAfter = m_plstStrings->InsertAfter(posInsertAfter, pDisplayString);
            posBoss = posInsertAfter;
            pDisplayString->m_posBoss = posBoss;

            pLastDisplayString = pDisplayString;
        } else {
            posInsertAfter = m_plstStrings->InsertAfter(posInsertAfter, pDisplayString);
        }

        pDisplayString->m_posBoss = posBoss;
        sStringCopy = sStrings[1];
    }

    if (pLastDisplayString != NULL) {
        pLastDisplayString->m_nNumLines = nNumLines;
    }

    m_textFont.pRes->Release();
    m_labelFont.pRes->Release();

    return nNumLines;
}

// 0x4E31C0
BOOL CUIControlTextDisplay::Render(BOOL bForce)
{
    // FIXME: Unused.
    CString v1;
    CString v2;
    CString v3;

    CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());

    CSingleLock renderLock(&field_A8E, FALSE);

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_posTopString == NULL) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    m_textFont.pRes->Demand();
    m_labelFont.pRes->Demand();

    COLORREF rgbCurrentLabelColor = m_labelFont.m_rgbForegroundColor;
    COLORREF rgbCurrentTextColor = m_textFont.m_rgbForegroundColor;

    CVidFont& font = m_textFont.GetBaseLineHeight(TRUE) > m_labelFont.GetBaseLineHeight(TRUE)
        ? m_textFont
        : m_labelFont;
    SHORT nBaseLineHeight = font.GetBaseLineHeight(TRUE);

    CRect rFrame(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
        CSize(m_nWidth, m_nHeight));

    CRect rDirtyFrame;
    rDirtyFrame.IntersectRect(rFrame, field_22);

    if (!pVidInf->BKLock(rDirtyFrame)) {
        m_textFont.pRes->Release();
        m_labelFont.pRes->Release();
        return FALSE;
    }

    CPoint pt = rFrame.TopLeft() - rDirtyFrame.TopLeft();

    CRect rClip = rDirtyFrame;
    rClip.OffsetRect(-rDirtyFrame.left, -rDirtyFrame.top);

    pt.y += field_A62;

    POSITION pos = m_posTopString;
    POSITION posBoss = m_plstStrings->GetAt(m_posTopString)->GetBossPos();

    if (m_posTopString != posBoss) {
        CDisplayString* pDisplayString = m_plstStrings->GetAt(posBoss);
        if (!pDisplayString->m_sLabel.IsEmpty()) {
            if (rgbCurrentLabelColor != pDisplayString->m_rgbLabelColor) {
                if (!field_AAE
                    || (g_pChitin->m_sFontName.Compare("") != 0
                        && m_labelFont.GetResRef() != "STATES2")) {
                    rgbCurrentLabelColor = pDisplayString->m_rgbLabelColor;
                    m_labelFont.SetColor(rgbCurrentLabelColor, m_rgbBackgroundColor, FALSE);
                }
            }

            // FIXME: Font has been demanded, but passes `FALSE`.
            pVidInf->BKTextOut(&m_labelFont,
                pDisplayString->m_sLabel,
                pt.x + 3 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1),
                pt.y - pDisplayString->m_nLine * m_nFontHeight + nBaseLineHeight,
                rClip,
                0,
                FALSE);
        }
    }

    if (pt.y < rClip.bottom) {
        while (pos != NULL) {
            CDisplayString* pDisplayString = m_plstStrings->GetAt(pos);
            if (pDisplayString->GetBossPos() != posBoss) {
                break;
            }

            if (!pDisplayString->m_sLabel.IsEmpty()) {
                if (rgbCurrentLabelColor != pDisplayString->m_rgbLabelColor) {
                    if (!field_AAE
                        || (g_pChitin->m_sFontName.Compare("") != 0
                            && m_labelFont.GetResRef() != "STATES2")) {
                        rgbCurrentLabelColor = pDisplayString->m_rgbLabelColor;
                        m_labelFont.SetColor(rgbCurrentLabelColor, m_rgbBackgroundColor, FALSE);
                    }
                }

                // FIXME: Font has been demanded, but passes `FALSE`.
                pVidInf->BKTextOut(&m_labelFont,
                    pDisplayString->m_sLabel,
                    pt.x + 3 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1),
                    pt.y - pDisplayString->m_nLine * m_nFontHeight + nBaseLineHeight,
                    rClip,
                    0,
                    FALSE);
            }

            if (rgbCurrentTextColor != pDisplayString->m_rgbTextColor) {
                if (!field_AAE
                    || (g_pChitin->m_sFontName.Compare("") != 0
                        && m_textFont.GetResRef() != "STATES2")) {
                    rgbCurrentTextColor = pDisplayString->m_rgbTextColor;
                    m_textFont.SetColor(rgbCurrentTextColor, m_rgbBackgroundColor, FALSE);
                }
            }

            // FIXME: Font has been demanded, but passes `FALSE`.
            pVidInf->BKTextOut(&m_textFont,
                pDisplayString->GetString(),
                pt.x + pDisplayString->m_nOffset,
                pt.y + nBaseLineHeight,
                rClip,
                0,
                FALSE);

            m_plstStrings->GetNext(pos);
            pt.y += m_nFontHeight;
        }
    }

    renderLock.Unlock();

    m_textFont.pRes->Release();
    m_labelFont.pRes->Release();

    pVidInf->BKUnlock();

    return TRUE;
}

// 0x4E3720
void CUIControlTextDisplay::SetItemMarker(POSITION posBossItem, LONG lMarker)
{
    if (posBossItem == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
        // __LINE__: 6839
        UTIL_ASSERT(FALSE);
    }

    POSITION pos = posBossItem;
    while (pos != NULL) {
        CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
        if (pDisplayString->GetBossPos() != posBossItem) {
            break;
        }

        pDisplayString->m_lMarker = lMarker;
    }
}

// 0x4E3770
void CUIControlTextDisplay::SetItemTextColor(POSITION posBossItem, COLORREF rgbColor)
{
    if (field_AAF) {
        if (g_pChitin->m_sFontName.Compare("") == 0
            || m_labelFont.GetResRef() == "STATES2") {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
            // __LINE__: 6947
            UTIL_ASSERT(FALSE);
        }
    }

    if (posBossItem == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
        // __LINE__: 6953
        UTIL_ASSERT(FALSE);
    }

    if (posBossItem == m_posHighlightedItem) {
        m_rgbTextColorBeforeHighlight = rgbColor;
    } else {
        POSITION pos = posBossItem;
        while (pos != NULL) {
            CDisplayString* pDisplayString = m_plstStrings->GetNext(pos);
            if (pDisplayString->GetBossPos() != posBossItem) {
                break;
            }

            pDisplayString->m_rgbTextColor = rgbColor;
        }

        CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
            CSize(m_nWidth, m_nHeight));
        m_pPanel->InvalidateRect(&rDirty);
        InvalidateRect();
    }
}

// 0x4E3880
void CUIControlTextDisplay::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CUIControlBase::TimerAsynchronousUpdate(bInside);

    if (m_bActive) {
        if (m_posHighlightedItem != NULL && !bInside) {
            UnHighlightItem();
        }

        if (field_A65 != 0 || field_A67) {
            if (field_5A < m_plstStrings->GetCount() - field_A6A) {
                if (field_A62 > -m_nFontHeight) {
                    field_A62 -= 3;
                    if (field_A62 <= -m_nFontHeight) {
                        if (field_A65 != 0) {
                            field_A65--;
                            m_plstStrings->GetNext(m_posTopString);
                            field_5A++;

                            // NOTE: Uninline.
                            AdjustScrollBar();

                            if (field_A67 && field_5A < m_plstStrings->GetCount() - field_A6A) {
                                field_A62 += m_nFontHeight;
                            } else {
                                field_A62 = 0;
                            }
                        } else {
                            field_A62 = -m_nFontHeight;
                        }
                    }
                } else {
                    field_A62 = 0;
                    m_plstStrings->GetNext(m_posTopString);
                    field_5A++;

                    // NOTE: Uninline.
                    AdjustScrollBar();
                }

                CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
                    CSize(m_nWidth, m_nHeight));
                m_pPanel->InvalidateRect(&rDirty);
                InvalidateRect();
            } else {
                field_A65 = 0;
                field_A67 = 0;
            }
        } else if (field_A64 != 0 || field_A66) {
            if (m_posTopString != m_plstStrings->GetHeadPosition()) {
                if (field_A62 < 0) {
                    field_A62 += 3;
                    if (field_A62 >= 0) {
                        if (field_A64 != 0) {
                            field_A64--;
                        }

                        if (field_A64 != 0 || field_A66) {
                            field_A62 -= m_nFontHeight;
                            m_plstStrings->GetPrev(m_posTopString);
                            field_5A--;

                            // NOTE: Uninline.
                            AdjustScrollBar();
                        } else {
                            field_A62 = 0;
                        }
                    }
                } else {
                    field_A62 = -m_nFontHeight;
                    m_plstStrings->GetPrev(m_posTopString);
                    field_5A--;

                    // NOTE: Uninline.
                    AdjustScrollBar();
                }

                CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
                    CSize(m_nWidth, m_nHeight));
                m_pPanel->InvalidateRect(&rDirty);
                InvalidateRect();
            } else {
                if (field_A62 > 0) {
                    field_A64 = 0;
                    field_A66 = 0;
                } else {
                    field_A62 += 3;
                    if (field_A62 > 0) {
                        field_A62 = 0;
                    }

                    CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
                        CSize(m_nWidth, m_nHeight));
                    m_pPanel->InvalidateRect(&rDirty);
                    InvalidateRect();
                }
            }
        }
    }
}

// 0x4E3CA0
void CUIControlTextDisplay::SetTopString(POSITION posTopString)
{
    if (posTopString != NULL) {
        m_posTopString = posTopString;

        INT nIndex = 0;

        POSITION pos = m_plstStrings->GetHeadPosition();
        while (pos != NULL) {
            if (pos == posTopString) {
                break;
            }

            m_plstStrings->GetNext(pos);
            nIndex++;
        }

        field_5A = nIndex;

        // NOTE: Uninline.
        AdjustScrollBar();

        CRect rDirty(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
            CSize(m_nWidth, m_nHeight));
        m_pPanel->InvalidateRect(&rDirty);
        InvalidateRect();

        field_A65 = 0;
        field_A64 = 0;
    }
}

// 0x4E3D60
void CUIControlTextDisplay::ScrollToBottom()
{
    if (field_A6A < m_plstStrings->GetCount()) {
        POSITION posTopString = m_plstStrings->FindIndex(m_plstStrings->GetCount() - field_A6A);
        // NOTE: Uninline.
        SetTopString(posTopString);
    }
}

// 0x4E3E30
POSITION CUIControlTextDisplay::GetBossPosition(INT nIndex)
{
    return m_plstStrings->GetAt(m_plstStrings->FindIndex(nIndex))->GetBossPos();
}

// 0x4E3E50
void CUIControlTextDisplay::GetString(INT nIndex, CString& sString)
{
    sString = m_plstStrings->GetAt(m_plstStrings->FindIndex(nIndex))->GetString();
}

// 0x4E3E70
BOOLEAN CUIControlTextDisplay::GetItem(INT nItemIndex, CString& sLabel, CString& sString)
{
    // NOTE: Uninline.
    POSITION posBossItem = GetItemBossPosition(nItemIndex);

    if (posBossItem == NULL) {
        sString = "";
        sLabel = "";
        return FALSE;
    }

    sLabel = m_plstStrings->GetAt(posBossItem)->GetLabel();
    sLabel = sLabel.Left(sLabel.GetLength() - m_sLabelSuffix.GetLength());

    sString = m_plstStrings->GetAt(posBossItem)->GetString();

    POSITION pos = posBossItem;
    m_plstStrings->GetNext(pos);

    // TODO: Loop looks odd, might be broken. Check.
    INT nLine = 0;
    if (m_plstStrings->GetAt(posBossItem)->GetNumLines() - 1 > 0) {
        CDisplayString* pDisplayString;
        do {
            pDisplayString = m_plstStrings->GetNext(pos);
            sString += " ";
            sString += m_plstStrings->GetAt(pos)->GetString();
            nLine++;
        } while (nLine < pDisplayString->GetNumLines() - 1);
    }

    return TRUE;
}

// 0x4E3F80
BOOLEAN CUIControlTextDisplay::GetItemTextColor(INT nItemIndex, COLORREF& rgbColor)
{
    // NOTE: Uninline.
    POSITION posBossItem = GetItemBossPosition(nItemIndex);

    if (posBossItem == NULL) {
        rgbColor = RGB(255, 255, 255);
        return FALSE;
    }

    rgbColor = m_plstStrings->GetAt(posBossItem)->GetTextColor();
    return TRUE;
}

// 0x4E3FD0
POSITION CUIControlTextDisplay::GetItemBossPosition(INT nItemIndex)
{
    INT nCurr = 0;

    POSITION pos = m_plstStrings->GetHeadPosition();
    while (pos != NULL) {
        CDisplayString* pDisplayString = m_plstStrings->GetAt(pos);
        if (pDisplayString->GetBossPos() == pos) {
            if (++nCurr > nItemIndex) {
                return pos;
            }
        }

        m_plstStrings->GetNext(pos);
    }

    return NULL;
}

// 0x799E60
void CUIControlTextDisplay::OnItemSelected(LONG lMarker)
{
}

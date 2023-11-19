#include "CInfCursor.h"

#include "CBaldurChitin.h"
#include "CUIControlBase.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x596C10
CInfCursor::CInfCursor()
{
    m_bVisible = FALSE;
    field_9F2 = 0;
    field_9EE = 0;
    field_A02 = NULL;
    m_nDirection = 0;
    m_nState = 0;
    bAnimatingCustom = 0;
    m_nCurrentCursor = -1;
}

// 0x596CD0
CInfCursor::~CInfCursor()
{
}

// 0x596DB0
void CInfCursor::CursorUpdate(CVidMode* pVidMode)
{
    if (pVidMode == NULL) {
        return;
    }

    if (g_pBaldurChitin->field_1932) {
        return;
    }

    if (m_bVisible) {
        switch (m_nCurrentCursor) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
        case 12:
        case 14:
        case 16:
        case 18:
        case 20:
        case 22:
        case 24:
        case 26:
        case 28:
        case 30:
        case 32:
        case 34:
        case 36:
        case 38:
        case 40:
        case 42:
        case 44:
        case 46:
            if (m_nState) {
                m_vcCursors.SequenceSet(m_nCurrentCursor + 1);
            } else {
                m_vcCursors.SequenceSet(m_nCurrentCursor);
            }

            m_vcArrow.FrameAdvance();

            g_pBaldurChitin->m_bPointerUpdated = FALSE;
            break;
        case 100:
            // NOTE: Uninline.
            SetScrollArrowDirection();
            m_vcArrow.FrameAdvance();

            g_pBaldurChitin->m_bPointerUpdated = FALSE;
            break;
        case 101:
            m_vcToolTip.FrameAdvance();

            g_pBaldurChitin->m_bPointerUpdated = FALSE;
            break;
        case 102:
            if (m_vcCustom.pRes == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfCursor.cpp
                // __LINE__:
                UTIL_ASSERT(FALSE);
            }

            if (bAnimatingCustom) {
                m_vcCustom.FrameAdvance();
                g_pBaldurChitin->m_bPointerUpdated = FALSE;
            }

            break;
        default:
            pVidMode->SetPointer(NULL, FALSE, -1);
            break;
        }
    } else {
        pVidMode->SetPointer(NULL, FALSE, -1);
        pVidMode->m_bPointerEnabled = FALSE;
    }
}

// 0x596FF0
CVidCell* CInfCursor::GetCurrentCursor()
{
    switch (m_nCurrentCursor) {
    case 100:
        return &m_vcArrow;
    case 101:
        return &m_vcToolTip;
    case 102:
        return &m_vcCustom;
    }

    return &m_vcCursors;
}

// 0x597020
void CInfCursor::Initialize()
{
    // NOTE: Uninline.
    m_vcArrow.SetResRef(CResRef("CURSARW"), FALSE, TRUE, TRUE);

    // NOTE: Uninline.
    m_vcCursors.SetResRef(CResRef("CURSORS"), FALSE, TRUE, TRUE);

    // NOTE: Uninline.
    m_vcToolTip.SetResRef(CResRef("TOOLTIP"), FALSE, TRUE, TRUE);

    m_vcToolTip.Initialize();

    m_bVisible = TRUE;
}

// 0x5972E0
void CInfCursor::SetCursor(INT nNewCursor, BOOLEAN bForce)
{
    CVidMode* pVidMode = g_pBaldurChitin->GetCurrentVideoMode();

    // NOTE: Uninline.
    SetGreyScale(FALSE);

    if (bForce || m_nCurrentCursor != nNewCursor) {
        switch (nNewCursor) {
        case 100:
            SetScrollArrowDirection();

            if (pVidMode->GetPointer() != &m_vcArrow) {
                if (pVidMode->GetPointer() == &m_vcToolTip) {
                    if (field_A02 != NULL) {
                        field_A02->ResetToolTip();
                        field_A02 = NULL;
                    }
                }

                m_vcArrow.FrameSet(0);
                pVidMode->SetPointer(&m_vcArrow, TRUE, -1);
            }
            break;
        case 101:
            if (pVidMode->GetPointer() != &m_vcToolTip) {
                m_vcToolTip.field_5E2 = 3;
                m_vcToolTip.field_5DA = 0;
                m_vcToolTip.field_5DC = 0;

                CSize size1;
                m_vcToolTip.GetFrameSize(1, 0, size1, FALSE);

                CSize size2;
                m_vcToolTip.GetFrameSize(2, m_vcToolTip.field_5DC, size2, FALSE);

                // TODO: Check cast.
                m_vcToolTip.field_5DE = static_cast<short>((size1.cx / 2) + (size2.cx / 2));
                m_vcToolTip.field_5E2 = 0;

                pVidMode->SetPointer(&m_vcToolTip, TRUE, -1);
                pVidMode->m_bPointerEnabled = TRUE;
                g_pBaldurChitin->m_bPointerUpdated = FALSE;
            }
            break;
        case 102:
            if (pVidMode->GetPointer() != &m_vcCustom) {
                if (pVidMode->GetPointer() == &m_vcToolTip) {
                    if (field_A02 != NULL) {
                        field_A02->ResetToolTip();
                        field_A02 = NULL;
                    }
                }

                pVidMode->SetPointer(&m_vcCustom, bAnimatingCustom, -1);
                g_pBaldurChitin->m_bPointerUpdated = FALSE;
            }
            break;
        default:
            if (pVidMode->GetPointer() != &m_vcCursors) {
                if (pVidMode->GetPointer() == &m_vcToolTip) {
                    if (field_A02 != NULL) {
                        field_A02->ResetToolTip();
                        field_A02 = NULL;
                    }
                }

                m_vcCursors.FrameSet(0);

                pVidMode->SetPointer(&m_vcCursors, 0, -1);
                pVidMode->m_bPointerEnabled = TRUE;
                g_pBaldurChitin->m_bPointerUpdated = FALSE;
            }
            break;
        }

        m_nCurrentCursor = nNewCursor;
    }
}

// 0x597610
void CInfCursor::SetGreyScale(BOOLEAN bGreyScale)
{
    if (bGreyScale) {
        // NOTE: Uninline.
        CVidCell* vc = GetCurrentCursor();
        vc->SetTintColor(RGB(180, 180, 180));

        g_pBaldurChitin->GetCurrentVideoMode()->m_dwCursorRenderFlags |= 0xA0000;
    } else {
        // NOTE: Uninline.
        CVidCell* vc = GetCurrentCursor();
        vc->SetTintColor(RGB(255, 255, 255));

        g_pBaldurChitin->GetCurrentVideoMode()->m_dwCursorRenderFlags &= ~0xA0000;
    }
}

// FIXME: `toolTipRef` should not be reference.
//
// 0x5976E0
void CInfCursor::SetToolTip(const STRREF& toolTipRef, CUIControlBase* pControl, const CString& sExtraText)
{
    // TODO: Incomplete.
}

// 0x597740
void CInfCursor::SetToolTip(STRREF nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, STRREF nSecondaryStrRef, STRREF nTertiaryStrRef)
{
    // TODO: Incomplete.
}

// 0x597C50
INT CInfCursor::SetCustomCursor(CResRef customResRef, BOOLEAN bAnimating, INT nPointerNumber)
{
    INT nOldCursor = m_nCurrentCursor;

    GetCurrentCursor()->SetTintColor(RGB(255, 255, 255));
    g_pBaldurChitin->GetCurrentVideoMode()->m_dwCursorRenderFlags &= ~0xA0000;
    m_nCurrentCursor = 102;
    bAnimatingCustom = bAnimating;
    m_vcCustom.SequenceSet(0);

    if (g_pBaldurChitin->GetCurrentVideoMode()->GetPointer() != &m_vcCustom
        || m_vcCustom.GetResRef() != customResRef
        || g_pBaldurChitin->GetCurrentVideoMode()->GetPointerNumber() != nPointerNumber) {
        if (g_pBaldurChitin->GetCurrentVideoMode()->GetPointer() == &m_vcToolTip) {
            if (field_A02 != NULL) {
                field_A02->ResetToolTip();
                field_A02 = NULL;
            }
        }

        if (g_pBaldurChitin->GetCurrentVideoMode()->SetPointer(&m_vcCustom, customResRef, bAnimatingCustom, nPointerNumber)) {
            g_pBaldurChitin->m_bPointerUpdated = FALSE;
        } else {
            g_pBaldurChitin->GetCurrentVideoMode()->SetPointer(&m_vcCustom,
                CResRef("NOICON"),
                bAnimatingCustom,
                nPointerNumber);
            SetCursor(0, FALSE);
        }
    }

    return nOldCursor;
}

// NOTE: Inlined.
void CInfCursor::SetScrollArrowDirection()
{
    switch (m_nDirection) {
    case 0:
        m_vcArrow.SequenceSet(2);
        break;
    case 1:
        m_vcArrow.SequenceSet(1);
        break;
    case 2:
        m_vcArrow.SequenceSet(0);
        break;
    case 3:
        m_vcArrow.SequenceSet(7);
        break;
    case 4:
        m_vcArrow.SequenceSet(6);
        break;
    case 5:
        m_vcArrow.SequenceSet(5);
        break;
    case 6:
        m_vcArrow.SequenceSet(4);
        break;
    default:
        m_vcArrow.SequenceSet(3);
        break;
    }
}

// 0x597E20
CInfToolTip::CInfToolTip()
{
    field_5DA = 0;
    field_5DC = 0;
    field_5DE = 0;
    field_5E0 = 0;
    field_5E2 = 0;
    field_5E4 = 0;
    field_5E6 = 0;
    field_5E8 = 0;
    field_5EA = 0;
}

// 0x597EE0
void CInfToolTip::Initialize()
{
    SequenceSet(0);
    field_5E2 = 2;

    m_font.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_font.SetColor(RGB(255, 255, 255), RGB(14, 14, 14), TRUE);
    field_5E4 = 256;
    field_5DA = 0;
    field_5DC = 0;

    CSize size1;
    GetFrameSize(1, 0, size1, FALSE);

    CSize size2;
    GetFrameSize(2, 0, size2, FALSE);

    // TODO: Check cast.
    field_5DE = static_cast<short>((size2.cx / 2) + (size1.cx / 2));
    field_5E0 = field_5DE;

    field_5E8 = GetSequenceLength(1, FALSE);
    field_5E6 = 0;
    field_5EA = GetSequenceLength(2, FALSE);
}

// 0x597FD0
BOOL CInfToolTip::FrameAdvance()
{
    CSize frameSize1;
    CSize frameSize2;

    switch (field_5E2) {
    case 0:
        field_5DA++;
        if (field_5DA >= field_5E8) {
            field_5DA = 0;
        }

        field_5DC++;
        if (field_5DC >= field_5EA) {
            field_5DC = 0;
        }

        field_5DE += 8;

        GetFrameSize(1, field_5DA, frameSize1, FALSE);
        GetFrameSize(2, field_5DC, frameSize2, FALSE);

        field_5DE = field_5E6 + static_cast<SHORT>(frameSize1.cx / 2 + frameSize2.cx / 2);
        field_5E2 = 2;
    case 1:
        field_5DA--;
        if (field_5DA < 0) {
            field_5DA = 0;
        }

        field_5DC--;
        if (field_5DC < 0) {
            field_5DC = 0;
        }

        field_5DE--;

        GetFrameSize(1, field_5DA, frameSize1, FALSE);
        GetFrameSize(2, field_5DC, frameSize2, FALSE);

        if (field_5DE <= frameSize1.cx / 2 + frameSize2.cx / 2) {
            field_5E2 = 3;
        }

        break;
    case 2:
        GetFrameSize(1, field_5DA, frameSize1, FALSE);
        GetFrameSize(2, field_5DC, frameSize2, FALSE);

        field_5DE = field_5E6 + static_cast<SHORT>(frameSize1.cx / 2 + frameSize2.cx / 2);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfCursor.cpp
        // __LINE__: 884
        UTIL_ASSERT(FALSE);
    }

    return TRUE;
}

// 0x5981D0
BOOL CInfToolTip::GetFrame()
{
    // NOTE: Original code is slightly different. There is some inlining, not
    // sure which.
    BAMHEADER* pHeader = pRes->m_bCacheHeader
        ? pRes->m_pBamHeaderCopy
        : pRes->m_pBamHeader;

    SHORT nSequences = pHeader->nSequences;
    if (nSequences == 0) {
        nSequences = 256;
    }

    if (m_nCurrentSequence >= nSequences) {
        m_nCurrentSequence = 0;
    }

    SHORT nFrames = pRes->m_pSequences[m_nCurrentSequence].nFrames;
    if (m_nCurrentFrame >= nFrames) {
        if (field_C8 != 0) {
            m_nCurrentFrame = 0;
        } else {
            m_nCurrentFrame--;
        }
    }

    if (m_nCurrentFrame < 0) {
        if (field_C8 != 0) {
            m_nCurrentFrame = nFrames - 1;
        } else {
            m_nCurrentFrame = 0;
        }
    }

    m_pFrame = pRes->GetFrame(m_nCurrentSequence, m_nCurrentFrame, m_bDoubleSize);

    return m_pFrame != NULL;
}

// 0x598940
void CInfToolTip::SetTextRef(const STRREF& textRef, const CString& sExtra)
{
    STR_RES strRes;
    BYTE nLine;
    BYTE nLines;

    field_5E6 = 0;

    for (int index = 0; index < 2; index++) {
        field_5EC[index] = "";
    }

    CSize size1;
    GetFrameSize(1, field_5DA, size1, TRUE);

    CSize size2;
    GetFrameSize(2, field_5DC, size2, TRUE);

    WORD nMaxWidth = static_cast<WORD>(field_5E4 - size2.cx - size1.cx);

    m_font.GetRes()->Demand();

    if (sExtra != "") {
        if (textRef != -1 && g_pBaldurChitin->GetTlkTable().Fetch(textRef, strRes)) {
            field_5EC[0] = strRes.szText;
            CUtil::TrimRight(field_5EC[0]);
            nLines = CUtil::SplitString(&m_font,
                sExtra,
                nMaxWidth - 8,
                1,
                &(field_5EC[1]),
                FALSE,
                TRUE,
                TRUE,
                -1);
        } else {
            int pos = CUtil::Find(sExtra, '\n', 0);
            if (pos != -1) {
                field_5EC[0] = sExtra.Left(pos);
                CUtil::TrimRight(field_5EC[0]);
                nLines = CUtil::SplitString(&m_font,
                    sExtra.Mid(pos + 1),
                    nMaxWidth - 8,
                    1,
                    &(field_5EC[1]),
                    FALSE,
                    TRUE,
                    TRUE,
                    -1);
            } else {
                nLines = CUtil::SplitString(&m_font,
                    sExtra.Mid(pos + 1),
                    nMaxWidth - 8,
                    2,
                    field_5EC,
                    FALSE,
                    TRUE,
                    TRUE,
                    -1);
            }
        }

        if (nLines > 0) {
            CUtil::TrimRight(field_5EC[nLines - 1]);
            for (nLine = 0; nLine < nLines; nLine++) {
                LONG nLineWidth = m_font.GetStringLength(field_5EC[nLine], TRUE);
                if (nLineWidth > field_5E6) {
                    field_5E6 = static_cast<SHORT>(nLineWidth);
                }
            }
        }

        m_font.GetRes()->Release();

        field_5E6 = min(field_5E6 + 8, nMaxWidth);
    } else {
        if (textRef != -1 && g_pBaldurChitin->GetTlkTable().Fetch(textRef, strRes)) {
            nLines = CUtil::SplitString(&m_font,
                strRes.szText,
                nMaxWidth - 8,
                2,
                field_5EC,
                FALSE,
                TRUE,
                TRUE,
                -1);
            if (nLines > 0) {
                CUtil::TrimRight(field_5EC[nLines - 1]);
                for (nLine = 0; nLine < nLines; nLine++) {
                    LONG nLineWidth = m_font.GetStringLength(field_5EC[nLine], TRUE);
                    if (nLineWidth > field_5E6) {
                        field_5E6 = static_cast<SHORT>(nLineWidth);
                    }
                }
            }

            m_font.GetRes()->Release();

            field_5E6 = min(field_5E6 + 8, nMaxWidth);
        } else {
            m_font.GetRes()->Release();
        }
    }
}

// 0x598D30
void CInfToolTip::SetTextRef(CString sExtra, const STRREF& textRef1, const STRREF& textRef2, const STRREF& textRef3)
{
    STR_RES strRes1;
    STR_RES strRes2;

    if (textRef1 != -1) {
        field_5E6 = 0;

        for (int index = 0; index < 2; index++) {
            field_5EC[index] = "";
        }

        CSize size1;
        GetFrameSize(1, field_5DA, size1, TRUE);

        CSize size2;
        GetFrameSize(2, field_5DC, size2, TRUE);

        WORD nMaxWidth = static_cast<WORD>(field_5E4 - size2.cx - size1.cx);

        m_font.GetRes()->Demand();

        if (g_pBaldurChitin->GetTlkTable().Fetch(textRef1, strRes1)) {
            if (textRef2 != -1) {
                if (g_pBaldurChitin->GetTlkTable().Fetch(textRef2, strRes2)) {
                    strRes1.szText = strRes2.szText + strRes1.szText;
                }
            }

            if (textRef3 != -1) {
                if (g_pBaldurChitin->GetTlkTable().Fetch(textRef3, strRes2)) {
                    strRes1.szText = strRes1.szText + strRes2.szText;
                }
            }

            strRes1.szText = strRes1.szText + sExtra;

            BYTE nLines = CUtil::SplitString(&m_font,
                strRes1.szText,
                nMaxWidth - 8,
                2,
                field_5EC,
                FALSE,
                TRUE,
                TRUE,
                -1);
            if (nLines > 0) {
                CUtil::TrimRight(field_5EC[nLines - 1]);
                for (BYTE nLine = 0; nLine < nLines; nLine++) {
                    field_5E6 = max(static_cast<SHORT>(m_font.GetStringLength(field_5EC[nLine], TRUE)), field_5E6);
                }
            }

            m_font.GetRes()->Release();
            field_5E6 = min(field_5E6 + 8, nMaxWidth);
        }
    }
}

// 0x5990F0
void CInfToolTip::StoreBackground(INT nFrom, INT nTo, INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfCursor.cpp
    // __LINE__: 1471
    UTIL_ASSERT(pRes != NULL);

    m_nCurrentSequence = 0;
    m_nCurrentFrame = 0;

    if (pRes->Demand() == NULL) {
        // NOTE: rStorage is not nullified like in the overload below.
        return;
    }

    // NOTE: Static dispatch.
    if (!GetFrame()) {
        pRes->Release();
        return;
    }

    CSize size2;
    GetFrameSize(2, field_5DC, size2, TRUE);

    CSize size1;
    GetFrameSize(1, field_5DA, size1, TRUE);

    field_5E0 = field_5DE;

    rStorage.left = max(min(max(x - field_5DE / 2 - size1.cx / 2, rClip.left),
                            rClip.right - field_5DE - size1.cx - size2.cx / 2),
        rClip.left);
    rStorage.top = max(min(max(y - m_pFrame->nCenterY, rClip.top),
                           rClip.bottom - m_pFrame->nHeight),
        rClip.top);
    rStorage.right = rStorage.left + size1.cx + size2.cx / 2 + field_5E0;
    rStorage.bottom = rStorage.top + m_pFrame->nHeight;

    if (rStorage.left < rClip.left) {
        rStorage.left = rClip.left;
    }

    if (rStorage.top < rClip.top) {
        rStorage.top = rClip.top;
    }

    if (rStorage.right >= rClip.right) {
        rStorage.right = rClip.right;
    }

    if (rStorage.bottom >= rClip.bottom) {
        rStorage.bottom = rClip.bottom;
    }

    do {
        HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(g_pChitin->GetCurrentVideoMode()->pSurfaces[nTo],
            0,
            0,
            g_pChitin->GetCurrentVideoMode()->pSurfaces[nFrom],
            &rStorage,
            DDBLTFAST_WAIT);
        g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
        if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
            break;
        }
    } while (!g_pChitin->field_1932);

    pRes->Release();
    m_pFrame = NULL;
}

// 0x599360
void CInfToolTip::StoreBackground(INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfCursor.cpp
    // __LINE__: 1560
    UTIL_ASSERT(pRes != NULL);

    m_nCurrentSequence = 0;
    m_nCurrentFrame = 0;

    if (pRes->Demand() == NULL) {
        rStorage.SetRect(0, 0, 0, 0);
        return;
    }

    // NOTE: Static dispatch.
    if (!GetFrame()) {
        pRes->Release();
        return;
    }

    CSize size2;
    GetFrameSize(2, field_5DC, size2, TRUE);

    CSize size1;
    GetFrameSize(1, field_5DA, size1, TRUE);

    field_5E0 = field_5DE;

    rStorage.left = max(min(max(x - field_5DE / 2 - size1.cx / 2, rClip.left),
                            rClip.right - field_5DE - size1.cx - size2.cx / 2),
        rClip.left);
    rStorage.top = max(min(max(y - m_pFrame->nCenterY, rClip.top),
                           rClip.bottom - m_pFrame->nHeight),
        rClip.top);
    rStorage.right = rStorage.left + size1.cx + size2.cx / 2 + field_5E0;
    rStorage.bottom = rStorage.top + m_pFrame->nHeight;

    if (rStorage.left < rClip.left) {
        rStorage.left = rClip.left;
    }

    if (rStorage.top < rClip.top) {
        rStorage.top = rClip.top;
    }

    if (rStorage.right >= rClip.right) {
        rStorage.right = rClip.right;
    }

    if (rStorage.bottom >= rClip.bottom) {
        rStorage.bottom = rClip.bottom;
    }

    pRes->Release();
    m_pFrame = NULL;
}

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
    field_9FA = 0;
    m_nState = 0;
    field_A06 = 0;
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

            g_pBaldurChitin->field_1902 = 0;
            break;
        case 100:
            // NOTE: Uninline.
            SetScrollArrowDirection();
            m_vcArrow.FrameAdvance();

            g_pBaldurChitin->field_1902 = 0;
            break;
        case 101:
            m_vcToolTip.FrameAdvance();

            g_pBaldurChitin->field_1902 = 0;
            break;
        case 102:
            if (m_vcCustom.pRes == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfCursor.cpp
                // __LINE__:
                UTIL_ASSERT(FALSE);
            }

            if (field_A06) {
                m_vcCustom.FrameAdvance();
                g_pBaldurChitin->field_1902 = 0;
            }

            break;
        default:
            pVidMode->SetPointer(NULL, FALSE, -1);
            break;
        }
    } else {
        pVidMode->SetPointer(NULL, FALSE, -1);
        pVidMode->field_D4 = FALSE;
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
    CResRef arrowResRef("CURSARW");
    m_vcArrow.SetResRef(arrowResRef, TRUE, TRUE);
    m_vcArrow.m_header.SetResRef(arrowResRef, TRUE, FALSE);

    if (m_vcArrow.pRes != NULL) {
        m_vcArrow.pRes->field_7E = m_vcArrow.m_header.GetResRef() == "";
    }

    m_vcArrow.m_bDoubleSize = FALSE;

    CResRef cursorsResRef("CURSORS");
    m_vcCursors.SetResRef(cursorsResRef, TRUE, TRUE);
    m_vcCursors.m_header.SetResRef(cursorsResRef, TRUE, FALSE);

    if (m_vcCursors.pRes != NULL) {
        m_vcCursors.pRes->field_7E = m_vcCursors.m_header.GetResRef() == "";
    }

    m_vcCursors.m_bDoubleSize = FALSE;

    CResRef toolTipResRef("TOOLTIP");
    m_vcToolTip.SetResRef(toolTipResRef, TRUE, TRUE);
    m_vcToolTip.m_header.SetResRef(toolTipResRef, TRUE, FALSE);

    if (m_vcToolTip.pRes != NULL) {
        m_vcToolTip.pRes->field_7E = m_vcToolTip.m_header.GetResRef() == "";
    }

    m_vcToolTip.m_bDoubleSize = FALSE;

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

                m_vcToolTip.field_5DE = (size1.cx / 2) + (size2.cx / 2);
                m_vcToolTip.field_5E2 = 0;

                pVidMode->SetPointer(&m_vcToolTip, TRUE, -1);
                pVidMode->field_D4 = 1;
                g_pBaldurChitin->field_1902 = 0;
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

                pVidMode->SetPointer(&m_vcCustom, field_A06, -1);
                g_pBaldurChitin->field_1902 = 0;
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

                pVidMode->SetPointer(&m_vcCustom, 0, -1);
                pVidMode->field_D4 = 1;
                g_pBaldurChitin->field_1902 = 0;
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

        g_pBaldurChitin->GetCurrentVideoMode()->field_C |= 0xA0000;
    } else {
        // NOTE: Uninline.
        CVidCell* vc = GetCurrentCursor();
        vc->SetTintColor(RGB(255, 255, 255));

        g_pBaldurChitin->GetCurrentVideoMode()->field_C &= ~0xA0000;
    }
}

// 0x597740
void CInfCursor::SetToolTip(STRREF nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, STRREF nSecondaryStrRef, STRREF nTertiaryStrRef)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CInfCursor::SetScrollArrowDirection()
{
    switch (field_9FA) {
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

    field_5DE = (size2.cx / 2) + (size1.cx / 2);
    field_5E0 = field_5DE;

    field_5E8 = GetSequenceLength(1, FALSE);
    field_5E6 = 0;
    field_5EA = GetSequenceLength(2, FALSE);
}

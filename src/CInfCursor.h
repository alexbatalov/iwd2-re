#ifndef CINFCURSOR_H_
#define CINFCURSOR_H_

#include "BalDataTypes.h"
#include "CSound.h"
#include "CVidCell.h"
#include "CVidFont.h"

class CUIControlBase;
class CVidMode;

class CInfToolTip : public CVidCell {
public:
    CInfToolTip();
    BOOL FrameAdvance() override;

    void Initialize();

    // NOTE: This function is not override of parent's `GetFrame`. I'm not sure
    // if it's a bug or it is intentional.
    BOOL GetFrame();

    /* 00DA */ CVidFont m_font;
    /* 05DA */ short field_5DA;
    /* 05DC */ short field_5DC;
    /* 05DE */ short field_5DE;
    /* 05E0 */ short field_5E0;
    /* 05E2 */ short field_5E2;
    /* 05E4 */ short field_5E4;
    /* 05E6 */ short field_5E6;
    /* 05E8 */ short field_5E8;
    /* 05EA */ short field_5EA;
    /* 05EC */ CString field_5EC[2];
    /* 05F4 */ CSound field_5F4;
};

class CInfCursor {
public:
    CInfCursor();
    ~CInfCursor();
    void CursorUpdate(CVidMode* pVidMode);
    CVidCell* GetCurrentCursor();
    void Initialize();
    void SetCursor(INT nNewCursor, BOOLEAN bForce);
    void SetGreyScale(BOOLEAN bGreyScale);
    void SetToolTip(const STRREF& toolTipRef, CUIControlBase* pControl, const CString& sExtraText);
    void SetToolTip(STRREF nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, STRREF nSecondaryStrRef, STRREF nTertiaryStrRef);
    INT SetCustomCursor(CResRef customResRef, BOOLEAN bAnimating, INT nPointerNumber);
    void SetScrollArrowDirection();

    /* 0000 */ BOOL m_bVisible;
    /* 0108 */ CVidCell m_vcCursors;
    /* 01E2 */ CVidCell m_vcArrow;
    /* 02BC */ CVidCell m_vcCustom;
    /* 0396 */ CInfToolTip m_vcToolTip;
    /* 09EE */ int field_9EE;
    /* 09F2 */ int field_9F2;
    /* 09F6 */ int m_nCurrentCursor;
    /* 09FA */ int field_9FA;
    /* 09FE */ int m_nState;
    /* 0A02 */ CUIControlBase* field_A02;
    /* 0A06 */ BOOLEAN bAnimatingCustom;
};

#endif /* CINFCURSOR_H_ */

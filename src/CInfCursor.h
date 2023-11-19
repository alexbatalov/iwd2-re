#ifndef CINFCURSOR_H_
#define CINFCURSOR_H_

#include "BalDataTypes.h"
#include "CSound.h"
#include "CVidCell.h"
#include "CVidFont.h"

class CUIControlBase;
class CVidInf;
class CVidMode;

class CInfToolTip : public CVidCell {
public:
    CInfToolTip();
    BOOL FrameAdvance() override;
    /* 0008 */ BOOL Render(INT nSurface, int x, int y, const CRect& rClip, CVidPoly* pClipPoly, int nPolys, DWORD dwFlags, int nTransVal) override;
    /* 0010 */ void StoreBackground(INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered) override;
    /* 0014 */ void StoreBackground(INT nFrom, INT nTo, INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered) override;

    void Initialize();

    // NOTE: This function is not override of parent's `GetFrame`. I'm not sure
    // if it's a bug or it is intentional.
    BOOL GetFrame();
    void RenderText(CVidInf* pVidInf, INT x, int a4, const CRect& rFXClip, DWORD dwFlags, SHORT nMaxWidth);
    void SetTextRef(const STRREF& textRef, const CString& sExtra);
    void SetTextRef(CString sExtra, const STRREF& textRef1, const STRREF& textRef2, const STRREF& textRef3);

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
    void SetToolTip(const STRREF& nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, const STRREF& nSecondaryStrRef, const STRREF& nTertiaryStrRef);
    INT SetCustomCursor(CResRef customResRef, BOOLEAN bAnimating, INT nPointerNumber);
    void SetScrollArrowDirection();

    /* 0000 */ BOOL m_bVisible;
    /* 0108 */ CVidCell m_vcCursors;
    /* 01E2 */ CVidCell m_vcArrow;
    /* 02BC */ CVidCell m_vcCustom;
    /* 0396 */ CInfToolTip m_vcToolTip;
    /* 09EE */ int field_9EE;
    /* 09F2 */ int field_9F2;
    /* 09F6 */ INT m_nCurrentCursor;
    /* 09FA */ INT m_nDirection;
    /* 09FE */ INT m_nState;
    /* 0A02 */ CUIControlBase* field_A02;
    /* 0A06 */ BOOLEAN bAnimatingCustom;
};

#endif /* CINFCURSOR_H_ */

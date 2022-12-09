#ifndef CHVIDFONT_H_
#define CHVIDFONT_H_

#include "mfc.h"

#include "CResRef.h"
#include "CVidCell.h"

class CVidFont : public CVidCell {
public:
    CVidFont();
    ~CVidFont();
    void SetColor(COLORREF color, int a3, int a4);
    void SetResRef(const CResRef& cNewResRef, int a3, int a4);
    int RegisterFont();
    void Unload();
    void TextOut3d(const CString& sText, int a3, int a4, const CRect& rect, int a6, int a7);

    /* 04DA */ HFONT m_hFont;
    /* 04DE */ int field_4DE;
    /* 04E2 */ int field_4E2;
    /* 04E6 */ short field_4E6;
    /* 04E8 */ short field_4E8;
    /* 04EA */ short field_4EA;
    /* 04EC */ int field_4EC;
    /* 04F0 */ int field_4F0;
    /* 04F4 */ int field_4F4;
    /* 04F8 */ int field_4F8;
    /* 04FC */ int field_4FC;
};

#endif /* CHVIDFONT_H_ */

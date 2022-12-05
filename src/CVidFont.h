#ifndef CHVIDFONT_H_
#define CHVIDFONT_H_

#include "mfc.h"

class CVidFont {
public:
    CVidFont();
    ~CVidFont();
    void SetColor(COLORREF color, int a3, int a4);
    void TextOut3d(const CString& sText, int a3, int a4, const CRect& rect, int a6, int a7);
};

#endif /* CHVIDFONT_H_ */

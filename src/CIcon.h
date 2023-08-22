#ifndef CICON_H_
#define CICON_H_

#include "mfc.h"

class CResRef;

class CIcon {
public:
    static const CPoint LAST_DIGIT_OFFSET;
    static const CPoint FIRST_DIGIT_OFFSET;
    static const CSize ICON_SIZE_SM;
    static const CSize ICON_SIZE_LG;

    static void RenderIcon(int a1, const CPoint& pos, const CSize& size, const CRect& rBoundingBox, const CResRef& cResIcon, BOOL bDoubleSize, DWORD dwFlags, WORD wCount, BOOL bForceCount, WORD wSecondCount, BOOL bForceSecondCount, COLORREF rgbTint);
};

#endif /* CICON_H_ */

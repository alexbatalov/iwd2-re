#ifndef CVIDIMAGE_H_
#define CVIDIMAGE_H_

#include "CVidPalette.h"

class CVidImage {
public:
    CVidImage();
    ~CVidImage();

    /* 0004 */ CVidPalette m_cPalette;
};

#endif /* CVIDIMAGE_H_ */

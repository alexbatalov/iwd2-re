#ifndef CVIDCELL_H_
#define CVIDCELL_H_

#include "CResCell.h"
#include "CResCellHeader.h"
#include "CVidImage.h"

class CVidCell : public CVidImage, public CResHelper<CResCell, 1000> {
public:
    CVidCell();
    ~CVidCell();

    // NOTE: Force this class to have vftable. Remove once real virtual methods
    // are identified.
    virtual void Dummy() { }

    /* 00B4 */ CResHelper<CResCellHeader, 1100> field_B4;
    /* 00C4 */ short field_C4;
    /* 00C6 */ short field_C6;
    /* 00C8 */ int field_C8;
    /* 00CC */ int field_CC;
    /* 00D0 */ int field_D0;
    /* 00D4 */ unsigned char field_D4;
    /* 00D6 */ int field_D6;
};

#endif /* CVIDCELL_H_ */

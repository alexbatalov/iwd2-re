#ifndef CRESINFTILE_H_
#define CRESINFTILE_H_

#include "CResTile.h"

class CResInfTile : public CResTile {
public:
    CResInfTile(BOOLEAN a1, BOOLEAN a2);
    ~CResInfTile() override;

    /* 0064 */ int m_nVRamTile;
    /* 0068 */ int field_68;
    /* 006C */ CResTile* m_pDualTileRes;
    /* 0070 */ unsigned char m_nVRamFlags;
};

#endif /* CRESINFTILE_H_ */

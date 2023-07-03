#ifndef CINFTILESET_H_
#define CINFTILESET_H_

#include "CVidImage.h"

class CResInfTile;
class CVRamPool;

class CInfTileSet {
public:
    CInfTileSet();
    ~CInfTileSet();

    int AttachToVRam(int nTile);
    int DetachFromVRam(int nTile);

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ CVidTile m_cVidTile;
    /* 00B0 */ CVRamPool* m_pVRamPool;
    /* 00B4 */ CResInfTile** m_pResTiles;
    /* 00B8 */ int m_nTiles;
};

#endif /* CINFTILESET_H_ */

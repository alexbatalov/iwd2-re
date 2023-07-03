#ifndef CVRAMPOOL_H_
#define CVRAMPOOL_H_

#include "mfc.h"

#include <ddraw.h>

class CInfTileSet;
class CVidMode;

typedef struct TileDefinition {
    /* 0000 */ int nTile;
    /* 0004 */ int nRefCount;
    /* 0008 */ CInfTileSet* pTileSet;
} TileDefinition;

class CVRamPool {
public:
    CVRamPool();
    ~CVRamPool();

    BOOL AttachSurfaces(CVidMode* pVidMode);
    void ClearAll();
    BOOL DetachSurfaces();
    void InvalidateAll();

    int AssociateTile(CInfTileSet* pTileSet, int nTile);
    BOOL EmptyTile(int nVTile);

    int m_nVTiles;
    IDirectDrawSurface** m_pSurfaces;
    TileDefinition* m_pTileDefs;
};

#endif /* CVRAMPOOL_H_ */

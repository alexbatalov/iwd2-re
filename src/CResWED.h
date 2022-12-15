#ifndef CRESWED_H_
#define CRESWED_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResWED : public CRes {
public:
    CResWED::CResWED();
    CResWED::~CResWED();
    void* Demand();
    ULONG GetNumTiledObjects();
    WORD* GetScreenPolyData();
    WED_LAYERHEADER* GetLayerHeader(UINT nLayer);
    WED_TILEDATA* GetTileData(UINT nLayer, int nXTile, int nYTile);
    WED_TILEDATA* GetTileData(UINT nLayer, int nTile);
    WED_TILEDOBJECT* GetTiledObject(USHORT nTile);
    WED_TILEDOBJECT* GetTiledObjects();
    WORD* GetTiledObjectList();
    WORD* GetTileList(UINT nLayer);
    int Release();
    BOOL Parse(void* pData);

    /* 0050 */ WED_WEDHEADER* m_pHeader;
    /* 0054 */ WED_LAYERHEADER* m_pLayers;
    /* 0058 */ WED_POLYHEADER* m_pPolyHeader;
    /* 005C */ WED_SCREENSECTIONLIST* m_pScreenSectionList;
    /* 0060 */ WED_POLYLIST* m_pPolyList;
    /* 0064 */ WED_POLYPOINT* m_pPolyPoints;
    /* 0068 */ BOOL m_bParsed;
};

#endif /* CRESWED_H_ */

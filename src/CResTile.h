#ifndef CRESTILE_H_
#define CRESTILE_H_

#include "CRes.h"
#include "CResRef.h"

class CResTile : public CRes {
public:
    CResTile();
    /* 0004 */ ~CResTile() override;
    /* 0014 */ int GetFixedResourceSize() override;
    /* 0018 */ int GetFixedResourceDataOffset() override;
    /* 001C */ CResRef GetResRef() override;
    /* 0020 */ USHORT GetType() override;
    BYTE* GetTileData();
    int GetTileSize();
    void* Demand();
    int Release();
    BOOL Parse(void* pData);

    /* 0050 */ RGBQUAD* m_pPalette;
    /* 0054 */ BYTE* m_pTileData;
    /* 0058 */ CResRef field_58;
    /* 0060 */ BOOL m_bParsed;
};

#endif /* CRESTILE_H_ */

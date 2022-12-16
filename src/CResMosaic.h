#ifndef CRESMOSAIC_H_
#define CRESMOSAIC_H_

#include "mfc.h"

#include "ChDataTypes.h"
#include "CRes.h"

class CResMosaic : public CRes {
public:
    CResMosaic();
    /* 0004 */ ~CResMosaic() override;
    WORD GetMosaicWidth(BOOL a2);
    WORD GetMosaicHeight(BOOL a2);
    WORD GetTileSize(BOOL a2);
    RGBQUAD* GetTilePalette(UINT nTile);
    void* Demand();
    int Release();
    BOOL Parse(void* pData);

    MOSAICHEADER* m_pHeader;
    RGBQUAD* m_pPalettes;
    BYTE* m_pTileData;
    DWORD* m_pOffsets;
    BOOL m_bParsed;
};

#endif /* CRESMOSAIC_H_ */

#ifndef CRESMOSAIC_H_
#define CRESMOSAIC_H_

#include "mfc.h"

#include "CRes.h"
#include "ChDataTypes.h"

class CResMosaic : public CRes {
public:
    CResMosaic();
    /* 0004 */ ~CResMosaic() override;
    WORD GetMosaicWidth(BOOL bDoubleSize);
    WORD GetMosaicHeight(BOOL bDoubleSize);
    WORD GetTileSize(BOOL bDoubleSize);
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

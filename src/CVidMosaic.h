#ifndef CVIDMOSAIC_H_
#define CVIDMOSAIC_H_

#include "CResMosaic.h"
#include "CVidImage.h"

class CVidMosaic : public CVidImage, public CResHelper<CResMosaic, 1004> {
public:
    typedef BOOL (CVidMosaic::*BltMosFunc)(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags);

    CVidMosaic();
    ~CVidMosaic();
    void GetSize(CSize& frameSize, BOOL bDemanded);
    BOOL Render(INT nSurface, int x, int y, const CRect& rMosaic, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL BltFromFX(LPDIRECTDRAWSURFACE pSurface, int x, int y, const CSize& size, const CRect& rClip, DWORD dwFlags);
    BOOL BltMos8To16(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags);
    BOOL BltMos8To24(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags);
    BOOL BltMos8To32(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags);
    int GetTileNumber(int x, int y);

    BOOL Render3d(int x, int y, const CRect& rMosaic, const CRect& rClip, DWORD dwFlags);

    /* 00B0 */ BOOL m_bDoubleSize;
};

#endif /* CVIDMOSAIC_H_ */

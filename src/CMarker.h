#ifndef CMARKER_H_
#define CMARKER_H_

#include "mfc.h"

#include "CVidMode.h"

class CGameSprite;
class CInfinity;

class CMarker {
public:
    static const BYTE RECTICLE;
    static const BYTE ELLIPSE;
    static const COLORREF PC_COLOR;
    static const COLORREF PC_NONECONTROLED_COLOR;
    static const COLORREF PC_NONECONTROLED_SELECTED_COLOR;
    static const COLORREF ENEMY_COLOR;
    static const COLORREF NEUTRAL_COLOR;
    static const COLORREF PC_SELECTED_COLOR;
    static const COLORREF TALKING_COLOR;
    static const COLORREF PC_MORALE_FAILURE_COLOR;
    static const SHORT PICKED_FLASH_PERIOD;
    static const BYTE RECTICLE_DEST_SIZE;
    static const BYTE RECTICLE_MAX_STRETCH;
    static const BYTE RECTICLE_XCTROFFSET;
    static const BYTE RECTICLE_XGAP;

    CMarker();
    void AsynchronousUpdate(CGameSprite* pSprite);
    void Render(CVidMode* pVidMode, INT nSurface, CGameSprite* pSprite);
    void Render(CVidMode* pVidMode, INT nSurface, CInfinity* pInfinity, const CPoint& dest, LONG nXSize, LONG nYSize);
    BYTE SetType(BYTE nType);

    /* 0000 */ BYTE m_type;
    /* 0002 */ SHORT m_nRecticleCounter;
    /* 0004 */ BYTE m_nRecticleForceRender;
    /* 0005 */ BYTE m_nRecticleForceRenderTarget;
    /* 0006 */ COLORREF m_rgbColor;
    /* 000A */ CVIDMODE_RECTICLE_DESCRIPTION m_recticleDesc;
    /* 0022 */ BOOLEAN m_bTalking;
};

#endif /* CMARKER_H_ */

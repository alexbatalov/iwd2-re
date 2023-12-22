#ifndef CBLOOD_H_
#define CBLOOD_H_

#include "mfc.h"

#define CBLOOD_NUM_COLORS 3

class CGameArea;
class CParticle;
class CVidMode;

class CBlood {
public:
    static const BYTE NUM_COLORS;
    static const COLORREF RGB_COLOR1;
    static const COLORREF RGB_COLOR2;
    static const COLORREF RGB_COLOR3;
    static const USHORT SQUIRT_HIGH;
    static const USHORT SQUIRT_MEDIUM;
    static const USHORT SQUIRT_LOW;
    static const USHORT GUSH_HIGH;
    static const USHORT GUSH_MEDIUM;
    static const USHORT GUSH_LOW;
    static const USHORT PULSATING_ARTERY;
    static const USHORT EXPLODING_DEATH;
    static const SHORT STREAM_LENGTH;
    static const SHORT SQUIRT_STREAMS;
    static const SHORT FULL_VELOCITY;
    static const SHORT GUSH_HEIGHT_VELOCITY;
    static const SHORT SQUIRT_HEIGHT_VELOCITY;
    static const SHORT VELOCITY_INC;
    static const SHORT SPLASH_LENGTH;
    static const SHORT SQUIRT_LIFESPAN;
    static const USHORT NUM_EFFECTS;

    CBlood(CGameArea* pArea, LONG nX, LONG nY, LONG nZ, SHORT nDirection, USHORT nType, LONG nCharacterHeight);
    ~CBlood();
    BOOLEAN AsynchronousUpdate();
    void Render(CVidMode* pVidMode, INT nSurface);
    void CalcBoundingRect();
    void GenerateExplodingBlood(LONG nX, LONG nY, LONG nZ);
    void GenerateParticles();

    BOOL BloodLeft() { return !m_particleList.IsEmpty() || !m_lstSplashParticles.IsEmpty(); }
    SHORT GetDirection() { return m_nDirection; }

    /* 0000 */ CGameArea* m_pArea;
    /* 0004 */ CTypedPtrList<CPtrList, CParticle*> m_particleList;
    /* 0020 */ CTypedPtrList<CPtrList, CParticle*> m_lstSplashParticles;
    /* 003C */ CPoint m_refPoint;
    /* 0044 */ CPoint m_pos;
    /* 004C */ LONG m_posZ;
    /* 0050 */ SHORT m_nTimeStamp;
    /* 0052 */ COLORREF m_aColors[CBLOOD_NUM_COLORS];
    /* 005E */ CRect m_rBounding;
    /* 006E */ SHORT m_nDirection;
    /* 0070 */ USHORT m_particleType;
    /* 0072 */ USHORT m_bloodType;
    /* 0074 */ LONG m_nCharHeight;
    /* 0078 */ BOOLEAN m_bLeavePool;
};

#endif /* CBLOOD_H_ */

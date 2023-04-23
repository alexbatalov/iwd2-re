#ifndef CPARTICLE_H_
#define CPARTICLE_H_

#include "mfc.h"

struct CPARTICLE_POINT {
    LONG x;
    LONG y;
    LONG z;
};

class CParticle {
public:
    static const USHORT CONNECT;
    static const USHORT DOTS;
    static const USHORT BLOB;
    static const USHORT RESOLUTION_INC;
    static const USHORT GRAVITY;
    static const WORD CONSTANT_VELOCITY;
    static const WORD NORMAL_VELOCITY;
    static const BYTE AIRBORN;
    static const BYTE GROUNDED;
    static const BYTE DEAD;
    static const LONG LIFESPAN_INFINITE;

    CParticle();
    CParticle(LONG posX, LONG posY, LONG posZ, LONG velX, LONG velY, LONG velZ, COLORREF rgbInitColor, SHORT nTailLength, LONG nGravity, WORD wType);
    CParticle(const CParticle& particle);
    BYTE AsynchronousUpdate();
    void Render(LPVOID pSurface, LONG lPitch, const CRect& rClipRect, USHORT nFlag, USHORT nBlobSize);
    void RenderBlob32(DWORD* pSurface, LONG lPitch, LONG lX, LONG lY, const CRect& rClipRect, USHORT nFlag, DWORD dwColor);
    void Render3d(const CRect& rClipRect, const CRect& rLockedRect, USHORT nFlag, USHORT nBlobSize);

    SHORT m_nTimeStamp;
    SHORT m_nTailLength;
    SHORT m_nRenderTime;
    COLORREF m_rgbColor;
    WORD m_wType;
    LONG m_nLifeSpan;
    BOOLEAN m_bTag;
    BYTE _padding;
    CPARTICLE_POINT m_pos;
    CPARTICLE_POINT m_vel;
    LONG m_nGravity;
};

#endif /* CPARTICLE_H_ */

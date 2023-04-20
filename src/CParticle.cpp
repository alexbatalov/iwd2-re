#include "CParticle.h"

// 0x85EB60
const USHORT CParticle::CONNECT = 0;

// 0x85EB62
const USHORT CParticle::DOTS = 1;

// 0x85EB64
const USHORT CParticle::BLOB = 2;

// 0x85EB66
const USHORT CParticle::RESOLUTION_INC = 10;

// 0x85EB68
const USHORT CParticle::GRAVITY = 1024;

// 0x85EB6A
const WORD CParticle::CONSTANT_VELOCITY = 1;

// 0x85EB6C
const WORD CParticle::NORMAL_VELOCITY = 2;

// 0x85EB6E
const BYTE CParticle::AIRBORN = 0;

// 0x85EB6F
const BYTE CParticle::GROUNDED = 1;

// 0x85EB70
const BYTE CParticle::DEAD = 2;

// 0x85EB74
const LONG CParticle::LIFESPAN_INFINITE = LONG_MAX;

// 0x7C3500
CParticle::CParticle()
{
    m_pos.x = 0;
    m_pos.y = 0;
    m_pos.z = -1;
    m_vel.x = 0;
    m_vel.y = 0;
    m_vel.z = 0;
    m_nTimeStamp = 0;
    m_nTailLength = 0;
    m_nRenderTime = 0;
    m_bTag = FALSE;
    m_nGravity = GRAVITY;
    m_wType = BLOB;
    m_nLifeSpan = LIFESPAN_INFINITE;
    m_rgbColor = 0;
}

// 0x7C3540
CParticle::CParticle(LONG posX, LONG posY, LONG posZ, LONG velX, LONG velY, LONG velZ, COLORREF rgbInitColor, SHORT nTailLength, LONG nGravity, WORD wType)
{
    m_pos.x = posX;
    m_pos.y = posY;
    m_pos.z = posZ;
    m_vel.x = velX;
    m_vel.y = velY;
    m_vel.z = velZ;
    m_rgbColor = rgbInitColor;
    m_nTimeStamp = 0;
    m_nRenderTime = 0;
    m_nTailLength = nTailLength;
    m_bTag = FALSE;
    m_nGravity = nGravity;
    m_wType = wType;
    m_nLifeSpan = LIFESPAN_INFINITE;
}

// 0x7C35B0
CParticle::CParticle(const CParticle& particle)
{
    m_pos = particle.m_pos;
    m_vel = particle.m_vel;
    m_rgbColor = particle.m_rgbColor;
    m_nTimeStamp = particle.m_nTimeStamp;
    m_nRenderTime = particle.m_nRenderTime;
    m_bTag = FALSE;
    m_nGravity = particle.m_nGravity;
    m_wType = particle.m_wType;
    m_nLifeSpan = particle.m_nLifeSpan;
}

// 0x7C3620
BYTE CParticle::AsynchronousUpdate()
{
    LONG nTmpZVel = 0;

    if (m_nLifeSpan--) {
        if ((m_wType & 0x1) != 0) {
            m_pos.z = max(m_pos.z - m_nGravity, 0);
        } else {
            nTmpZVel = m_vel.z - m_nGravity;
            m_pos.z = max(m_pos.z + nTmpZVel, 0);
        }

        if (m_pos.z > 0) {
            m_nTimeStamp++;
            m_pos.x += m_vel.x;
            m_pos.y += m_vel.y;
            m_vel.z = nTmpZVel;
            return AIRBORN;
        } else {
            if (m_nTailLength != 0) {
                m_nTailLength--;
                return GROUNDED;
            }
        }
    }

    return DEAD;
}

// 0x7C36A0
void CParticle::Render(LPVOID pSurface, LONG lPitch, const CRect& rClipRect, USHORT nFlag, USHORT nBlobSize)
{
    // TODO: Incomplete.
}

// 0x7C3FD0
void CParticle::RenderBlob32(DWORD* pSurface, LONG lPitch, LONG lX, LONG lY, const CRect& rClipRect, USHORT nFlag, DWORD color)
{
    CRect rBlob;
    rBlob.left = 0;
    rBlob.top = 0;
    rBlob.right = rClipRect.right - rClipRect.left;
    rBlob.bottom = rClipRect.bottom - rClipRect.top;

    CPoint pt1;
    pt1.x = lX - rClipRect.left;
    pt1.y = lY - rClipRect.top + 1;
    if (rBlob.PtInRect(pt1)) {
        pSurface[pt1.x + lPitch * pt1.y] = color;
    }

    CPoint pt2;
    pt2.x = lX - rClipRect.left + 1;
    pt2.y = lY - rClipRect.top;
    if (rBlob.PtInRect(pt2)) {
        pSurface[pt2.x + lPitch * pt2.y] = color;
    }

    CPoint pt3;
    pt3.x = lX - rClipRect.left - 1;
    pt3.y = lY - rClipRect.top;
    if (rBlob.PtInRect(pt3)) {
        pSurface[pt3.x + lPitch * pt3.y] = color;
    }

    CPoint pt4;
    pt4.x = lX - rClipRect.left;
    pt4.y = lY - rClipRect.top - 1;
    if (rBlob.PtInRect(pt4)) {
        pSurface[pt4.x + lPitch * pt4.y] = color;
    }
}

// 0x7CC340
void CParticle::Render3d(const CRect& rClipRect, const CRect& rLockedRect, USHORT nFlag, USHORT nBlobSize)
{
    // TODO: Incomplete.
}

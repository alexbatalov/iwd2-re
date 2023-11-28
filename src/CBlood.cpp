#include "CBlood.h"

#include "CParticle.h"

// 0x84D5AC
const BYTE CBlood::NUM_COLORS = CBLOOD_NUM_COLORS;

// 0x84D5B0
const COLORREF CBlood::RGB_COLOR1 = RGB(109, 36, 0);

// 0x84D5B4
const COLORREF CBlood::RGB_COLOR2 = RGB(159, 42, 0);

// 0x84D5B8
const COLORREF CBlood::RGB_COLOR3 = RGB(180, 50, 15);

// 0x84D5BC
const USHORT CBlood::SQUIRT_HIGH = 0;

// 0x84D5BE
const USHORT CBlood::SQUIRT_MEDIUM = 1;

// 0x84D5C0
const USHORT CBlood::SQUIRT_LOW = 2;

// 0x84D5C2
const USHORT CBlood::GUSH_HIGH = 3;

// 0x84D5C4
const USHORT CBlood::GUSH_MEDIUM = 4;

// 0x84D5C6
const USHORT CBlood::GUSH_LOW = 5;

// 0x84D5C8
const USHORT CBlood::PULSATING_ARTERY = 6;

// 0x84D5CA
const USHORT CBlood::EXPLODING_DEATH = 7;

// 0x84D5CC
const SHORT CBlood::STREAM_LENGTH = 5;

// 0x84D5CE
const SHORT CBlood::SQUIRT_STREAMS = 20;

// 0x84D5D0
const SHORT CBlood::FULL_VELOCITY = 3000;

// 0x84D5D2
const SHORT CBlood::GUSH_HEIGHT_VELOCITY = 4000;

// 0x84D5D4
const SHORT CBlood::SQUIRT_HEIGHT_VELOCITY = 8000;

// 0x84D5D6
const SHORT CBlood::VELOCITY_INC = 100;

// 0x84D5D8
const SHORT CBlood::SPLASH_LENGTH = 2;

// 0x84D5DA
const SHORT CBlood::SQUIRT_LIFESPAN = 15;

// 0x84D5DC
const USHORT CBlood::NUM_EFFECTS = 8;

// 0x5195B0
CBlood::CBlood(CGameArea* pArea, LONG nX, LONG nY, LONG nZ, SHORT nDirection, USHORT nType, LONG nCharacterHeight)
{
    m_pArea = pArea;
    m_pos.x = nX;
    m_pos.y = nY;
    m_posZ = nZ;
    m_nCharHeight = nCharacterHeight;
    m_nDirection = nDirection;
    m_nTimeStamp = 0;
    m_aColors[0] = RGB_COLOR1;
    m_aColors[1] = RGB_COLOR2;
    m_aColors[2] = RGB_COLOR3;
    m_particleType = CParticle::CONNECT;
    m_bloodType = nType;
    m_bLeavePool = TRUE;
    CalcBoundingRect();
    GenerateParticles();
}

// 0x519680
CBlood::~CBlood()
{
    POSITION pos;

    pos = m_lstSplashParticles.GetHeadPosition();
    while (pos != NULL) {
        delete m_lstSplashParticles.GetNext(pos);
    }
    m_lstSplashParticles.RemoveAll();

    pos = m_particleList.GetHeadPosition();
    while (pos != NULL) {
        delete m_particleList.GetNext(pos);
    }
    m_particleList.RemoveAll();
}

// 0x519740
void CBlood::AsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x519920
void CBlood::Render(CVidMode* pVidMode, INT nSurface)
{
    // TODO: Incomplete.
}

// 0x519C40
void CBlood::CalcBoundingRect()
{
    // TODO: Incomplete.
}

// 0x51A2A0
void CBlood::GenerateExplodingBlood(LONG nX, LONG nY, LONG nZ)
{
    // TODO: Incomplete.
}

// 0x51A500
void CBlood::GenerateParticles()
{
    // TODO: Incomplete.
}

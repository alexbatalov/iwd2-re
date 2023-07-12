#ifndef CGAMEANIMATIONTYPE_H_
#define CGAMEANIMATIONTYPE_H_

#include "mfc.h"

#include "CVidBitmap.h"

typedef struct {
    SHORT x;
    SHORT y;
} NECK_POINTS;

class CGameAnimationType {
public:
    static const CString ROUND_BASE;

    static BOOL MIRROR_BAM;

    CGameAnimationType();
    /* 0000 */ virtual ~CGameAnimationType();
    /* 0004 */ virtual void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 0008 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);
    /* 000C */ virtual void ChangeDirection(SHORT nDirection);
    /* 0024 */ virtual void GetAnimationResRef(CString& resRef, BYTE range);
    /* 0030 */ virtual WORD GetCastFrame();
    /* 0034 */ virtual BYTE GetColorBlood();
    /* 0038 */ virtual BYTE GetColorChunks();
    /* 0040 */ virtual BYTE GetMoveScale();
    /* 0044 */ virtual void SetMoveScale(BYTE scale);
    /* 0048 */ virtual void ResetMoveScale();
    /* 004C */ virtual BYTE GetMoveScaleDefault();
    /* 0050 */ virtual NECK_POINTS GetNeckOffsets(SHORT nDirection);
    /* 0054 */ virtual const CRect& GetEllipseRect();
    /* 005C */ virtual BYTE GetPersonalSpace();
    /* 0060 */ virtual const char* GetSndArmor();
    /* 0064 */ virtual const char* GetSndDeath();
    /* 0068 */ virtual const char* GetSndReady();
    /* 0070 */ virtual const char* GetSndWalk(SHORT a1);
    /* 0074 */ virtual DWORD GetSndWalkFreq();
    /* 00B0 */ virtual void CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 00B4 */ virtual void SetNeckOffsets(SHORT Sx, SHORT Sy, SHORT SWx, SHORT SWy, SHORT Wx, SHORT Wy, SHORT NWx, SHORT NWy, SHORT Nx, SHORT Ny, SHORT NEx, SHORT NEy, SHORT Ex, SHORT Ey, SHORT SEx, SHORT SEy);
    /* 00C4 */ virtual SHORT GetCastHeight();

    /* 0004 */ USHORT m_animationID;
    /* 0006 */ BYTE m_moveScale;
    /* 0007 */ BYTE m_moveScaleCurrent;
    /* 0008 */ CRect m_rEllipse;
    /* 0018 */ BYTE m_colorBlood;
    /* 0019 */ BYTE m_colorChunks;
    /* 001A */ DWORD m_nSndFreq;
    /* 001E */ const char* m_pSndDeath;
    /* 0022 */ NECK_POINTS m_neckOffsets[8];
    /* 0042 */ CVidBitmap m_combatRounds[5];
    /* 03E4 */ BYTE m_personalSpace;
    /* 03E6 */ WORD m_castFrame;
    /* 03E8 */ unsigned char field_3E8;
    /* 03FB */ unsigned char field_3FB;
    /* 03FC */ unsigned char field_3FC;
};

#endif /* CGAMEANIMATIONTYPE_H_ */

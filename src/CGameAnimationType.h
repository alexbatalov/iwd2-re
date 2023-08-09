#ifndef CGAMEANIMATIONTYPE_H_
#define CGAMEANIMATIONTYPE_H_

#include "mfc.h"

#include "CVidBitmap.h"

typedef struct {
    SHORT x;
    SHORT y;
} NECK_POINTS;

class CInfinity;
class CVidMode;

class CGameAnimationType {
public:
    static const CString ROUND_BASE;

    static BOOL MIRROR_BAM;

    static CGameAnimationType* SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing);

    CGameAnimationType();
    /* 0000 */ virtual ~CGameAnimationType();
    /* 0004 */ virtual void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 0008 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);
    /* 000C */ virtual void ChangeDirection(SHORT nDirection);
    /* 0020 */ virtual CVidPalette* GetAnimationPalette(BYTE range);
    /* 0024 */ virtual void GetAnimationResRef(CString& resRef, BYTE range);
    /* 0028 */ virtual BOOLEAN CanLieDown();
    /* 002C */ virtual BOOLEAN DetectedByInfravision();
    /* 0030 */ virtual WORD GetCastFrame();
    /* 0034 */ virtual BYTE GetColorBlood();
    /* 0038 */ virtual BYTE GetColorChunks();
    /* 003C */ virtual BYTE GetListType();
    /* 0040 */ virtual BYTE GetMoveScale();
    /* 0044 */ virtual void SetMoveScale(BYTE scale);
    /* 0048 */ virtual void ResetMoveScale();
    /* 004C */ virtual BYTE GetMoveScaleDefault();
    /* 0050 */ virtual NECK_POINTS GetNeckOffsets(SHORT nDirection);
    /* 0054 */ virtual const CRect& GetEllipseRect();
    /* 0058 */ virtual BOOL GetPathSmooth();
    /* 005C */ virtual BYTE GetPersonalSpace();
    /* 0060 */ virtual const char* GetSndArmor();
    /* 0064 */ virtual const char* GetSndDeath();
    /* 0068 */ virtual const char* GetSndReady();
    /* 006C */ virtual const char* GetSndWalk(SHORT a1);
    /* 0070 */ virtual DWORD GetSndWalkFreq();
    /* 0074 */ virtual BOOL IsFalseColor();
    /* 0078 */ virtual BOOL IsInvulnerable();
    /* 007C */ virtual BOOL IsMirroring();
    /* 0080 */ virtual BOOL IsBeginningOfSequence();
    /* 0084 */ virtual BOOL IsEndOfSequence();
    /* 0088 */ virtual void IncrementFrame();
    /* 008C */ virtual void DecrementFrame();
    /* 0090 */ virtual void Render(CInfinity* pInfinity, CVidMode* pVidMode, int a3, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency);
    /* 0094 */ virtual void ClearColorEffects(BYTE colorRange);
    /* 0098 */ virtual void ClearColorEffectsAll();
    /* 009C */ virtual void SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength);
    /* 00A0 */ virtual void SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength);
    /* 00A4 */ virtual void SetColorRange(BYTE colorRange, BYTE rangeValue);
    /* 00A8 */ virtual void SetColorRangeAll(BYTE rangeValue);
    /* 00AC */ virtual SHORT SetSequence(SHORT nSequence);
    /* 00B0 */ virtual void CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 00B4 */ virtual void SetNeckOffsets(SHORT Sx, SHORT Sy, SHORT SWx, SHORT SWy, SHORT Wx, SHORT Wy, SHORT NWx, SHORT NWy, SHORT Nx, SHORT Ny, SHORT NEx, SHORT NEy, SHORT Ex, SHORT Ey, SHORT SEx, SHORT SEy);
    /* 00B8 */ virtual BYTE GetAttackFrameType(BYTE numAttacks, BYTE speedFactor, BYTE combatFrame);
    /* 00BC */ virtual BOOL GetAboveGround();
    /* 00C0 */ virtual SHORT GetAwakePlayInReverse();
    /* 00C4 */ virtual SHORT GetCastHeight();
    /* 00C8 */ virtual SHORT GetCurrentFrame();
    /* 00CC */ virtual BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame);
    /* 00D0 */ virtual BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet);

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
    /* 03E9 */ char m_walkRef[9];
    /* 03E8 */ unsigned char field_3E8;
    /* 03FB */ unsigned char field_3FB;
    /* 03FC */ unsigned char field_3FC;
};

#endif /* CGAMEANIMATIONTYPE_H_ */

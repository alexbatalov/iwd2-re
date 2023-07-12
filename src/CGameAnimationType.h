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
    static BOOL MIRROR_BAM;

    /* 0000 */ virtual ~CGameAnimationType();
    /* 0008 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);
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

    /* 0004 */ USHORT m_animationID;
    /* 0006 */ BYTE m_moveScale;
    /* 0007 */ BYTE m_moveScaleCurrent;
    /* 0008 */ CRect m_rEllipse;
    /* 0018 */ BYTE m_colorBlood;
    /* 0019 */ BYTE m_colorChunks;
    /* 001E */ const char* m_pSndDeath;
    /* 0022 */ NECK_POINTS m_neckOffsets[8];
    /* 0042 */ CVidBitmap m_combatRounds[5];
    /* 03E4 */ BYTE m_personalSpace;
    /* 03E6 */ WORD m_castFrame;
};

#endif /* CGAMEANIMATIONTYPE_H_ */

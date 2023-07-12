#ifndef CGAMEANIMATIONTYPE_H_
#define CGAMEANIMATIONTYPE_H_

#include "mfc.h"

#include "CVidBitmap.h"

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

    /* 0004 */ USHORT m_animationID;
    /* 0007 */ BYTE m_moveScaleCurrent;
    /* 0018 */ BYTE m_colorBlood;
    /* 0019 */ BYTE m_colorChunks;
    /* 0042 */ CVidBitmap m_combatRounds[5];
    /* 03E6 */ WORD m_castFrame;
};

#endif /* CGAMEANIMATIONTYPE_H_ */

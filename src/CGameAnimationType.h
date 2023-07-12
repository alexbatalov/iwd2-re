#ifndef CGAMEANIMATIONTYPE_H_
#define CGAMEANIMATIONTYPE_H_

#include "mfc.h"

#include "CVidBitmap.h"

class CGameAnimationType {
public:
    static BOOL MIRROR_BAM;

    /* 0000 */ virtual ~CGameAnimationType();
    /* 0008 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);

    /* 0004 */ USHORT m_animationID;
    /* 0042 */ CVidBitmap m_combatRounds[5];
};

#endif /* CGAMEANIMATIONTYPE_H_ */

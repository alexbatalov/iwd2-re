#ifndef CGAMEANIMATIONTYPEFLYING_H_
#define CGAMEANIMATIONTYPEFLYING_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeFlying : public CGameAnimationType {
public:
    CGameAnimationTypeFlying(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeFlying() override;

    /* 03FE */ CVidCell* m_currentVidCell;
    /* 0402 */ CVidCell* m_currentVidCellBase;
    /* 0406 */ CVidCell m_g1VidCellBase;
    /* 04E0 */ CVidPalette m_charPalette;
    /* 0504 */ SHORT m_currentBamSequence;
    /* 0506 */ SHORT m_currentBamDirection;
    /* 0508 */ BOOL m_falseColor;
    /* 050C */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEFLYING_H_ */

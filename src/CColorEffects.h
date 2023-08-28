#ifndef CCOLOREFFECTS_H_
#define CCOLOREFFECTS_H_

#include "mfc.h"

class CGameSprite;

class CColorRange {
public:
    CColorRange();

    /* 0000 */ BYTE m_range;
    /* 0001 */ BYTE m_color;
};

class CColorEffect {
public:
    CColorEffect();

    /* 0000 */ BYTE m_effectType;
    /* 0001 */ BYTE m_range;
    /* 0002 */ COLORREF m_tintColor;
    /* 0006 */ BYTE m_periodLength;
};

class CColorRanges : public CTypedPtrList<CPtrList, CColorRange*> {
public:
    CColorRanges();
    ~CColorRanges() override;
    void ClearAll();
    ULONG Marshal(BYTE** ppData);
    void Unmarshal(BYTE* pData, ULONG size);
    CColorRanges& operator=(const CColorRanges& other);
    void Apply(CGameSprite* pSprite);
};

class CColorEffects : public CTypedPtrList<CPtrList, CColorEffect*> {
public:
    CColorEffects();
    ~CColorEffects() override;
    void ClearAll();
    ULONG Marshal(BYTE** ppData);
    void Unmarshal(BYTE* pData, ULONG size);
    CColorEffects& operator=(const CColorEffects& other);
    void Apply(CGameSprite* pSprite);
};

#endif /* CCOLOREFFECTS_H_ */

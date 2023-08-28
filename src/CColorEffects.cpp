#include "CColorEffects.h"

#include "CGameSprite.h"
#include "CUtil.h"

// NOTE: Inlined.
CColorRange::CColorRange()
{
    m_range = 0;
    m_color = 0;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CColorEffect::CColorEffect()
{
    m_effectType = -1;
    m_range = 0;
    m_tintColor = 0;
    m_periodLength = 1;
}

// -----------------------------------------------------------------------------

// 0x448430
CColorRanges::CColorRanges()
{
}

// 0x443730
CColorRanges::~CColorRanges()
{
    ClearAll();
}

// 0x4E71B0
void CColorRanges::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CColorRange* pColorRange = GetNext(pos);
        delete pColorRange;
    }
    RemoveAll();
}

// 0x442E50
ULONG CColorRanges::Marshal(BYTE** ppData)
{
    *ppData = NULL;

    LONG nSize = sizeof(CColorRange) * GetCount();

    // NOTE: Signed compare.
    if (nSize > 0) {
        BYTE* pData = new BYTE[nSize];
        int offset = 0;

        POSITION pos = GetHeadPosition();
        while (pos != NULL) {
            CColorRange* pColorEffect = GetNext(pos);

            pData[offset] = pColorEffect->m_range;
            pData[offset + 1] = pColorEffect->m_color;

            offset += sizeof(CColorRange);
        }

        *ppData = pData;
    }

    return nSize;
}

// 0x442EA0
void CColorRanges::Unmarshal(BYTE* pData, ULONG nSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CColorEffects.cpp
    // __LINE__: 170
    UTIL_ASSERT(nSize % sizeof(CColorRange) == 0);

    int count = nSize / sizeof(CColorRange);
    int offset = 0;

    for (int index = 0; index < count; index++) {
        CColorRange* pColorRange = new CColorRange;
        pColorRange->m_range = pData[offset];
        pColorRange->m_color = pData[offset + 1];
        AddTail(pColorRange);

        offset += sizeof(CColorRange);
    }
}

// 0x442F10
CColorRanges& CColorRanges::operator=(const CColorRanges& other)
{
    // NOTE: Uninline.
    ClearAll();

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CColorRange* pColorRange = other.GetNext(pos);

        CColorRange* pCopy = new CColorRange;
        pCopy->m_range = pColorRange->m_range;
        pCopy->m_color = pColorRange->m_color;

        AddTail(pCopy);
    }

    return *this;
}

// 0x442F90
void CColorRanges::Apply(CGameSprite* pSprite)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CColorRange* pColorRange = GetNext(pos);

        if (pColorRange->m_range != -1) {
            // NOTE: Uninline.
            pSprite->GetAnimation()->SetColorRange(pColorRange->m_range,
                pColorRange->m_color);
        } else {
            // NOTE: Uninline.
            pSprite->GetAnimation()->SetColorRangeAll(pColorRange->m_color);
        }
    }
}

// -----------------------------------------------------------------------------

// 0x448450
CColorEffects::CColorEffects()
{
}

// 0x4437A0
CColorEffects::~CColorEffects()
{
    ClearAll();
}

// 0x4E71B0
void CColorEffects::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CColorEffect* pColorEffect = GetNext(pos);
        delete pColorEffect;
    }
    RemoveAll();
}

// 0x443050
ULONG CColorEffects::Marshal(BYTE** ppData)
{
    *ppData = NULL;

    LONG nSize = sizeof(CColorEffect) * GetCount();

    // NOTE: Signed compare.
    if (nSize > 0) {
        BYTE* pData = new BYTE[nSize];
        int offset = 0;

        POSITION pos = GetHeadPosition();
        while (pos != NULL) {
            CColorEffect* pColorEffect = GetNext(pos);

            pData[offset] = pColorEffect->m_effectType;
            pData[offset + 1] = pColorEffect->m_range;
            *reinterpret_cast<COLORREF*>(&(pData[offset + 2])) = pColorEffect->m_tintColor;
            pData[offset + 6] = pColorEffect->m_periodLength;

            offset += sizeof(CColorEffect);
        }

        *ppData = pData;
    }

    return nSize;
}

// 0x4430A0
void CColorEffects::Unmarshal(BYTE* pData, ULONG nSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CColorEffects.cpp
    // __LINE__: 365
    UTIL_ASSERT(nSize % sizeof(CColorEffect) == 0);

    int count = nSize / sizeof(CColorEffect);
    int offset = 0;

    for (int index = 0; index < count; index++) {
        CColorEffect* pColorEffect = new CColorEffect;
        pColorEffect->m_effectType = pData[offset];
        pColorEffect->m_range = pData[offset + 1];
        pColorEffect->m_tintColor = *reinterpret_cast<COLORREF*>(&(pData[offset + 2]));
        pColorEffect->m_periodLength = pData[offset + 6];
        AddTail(pColorEffect);

        offset += sizeof(CColorEffect);
    }
}

// 0x443130
CColorEffects& CColorEffects::operator=(const CColorEffects& other)
{
    // NOTE: Uninline.
    ClearAll();

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CColorEffect* pColorEffect = other.GetNext(pos);

        CColorEffect* pCopy = new CColorEffect;
        pCopy->m_effectType = pColorEffect->m_effectType;
        pCopy->m_range = pColorEffect->m_range;
        pCopy->m_tintColor = pColorEffect->m_tintColor;
        pCopy->m_periodLength = pColorEffect->m_periodLength;

        AddTail(pCopy);
    }

    return *this;
}

// 0x4431C0
void CColorEffects::Apply(CGameSprite* pSprite)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CColorEffect* pColorEffect = GetNext(pos);

        if (pColorEffect->m_range != -1) {
            // NOTE: Uninline.
            pSprite->GetAnimation()->SetColorEffect(pColorEffect->m_effectType,
                pColorEffect->m_range,
                pColorEffect->m_tintColor,
                pColorEffect->m_periodLength);
        } else {
            // NOTE: Uninline.
            pSprite->GetAnimation()->SetColorEffectAll(pColorEffect->m_effectType,
                pColorEffect->m_tintColor,
                pColorEffect->m_periodLength);
        }
    }
}

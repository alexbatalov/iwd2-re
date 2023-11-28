#include "IcewindCVisualEffect.h"

// 0x586A40
IcewindCVisualEffect::IcewindCVisualEffect()
{
    field_0 = FALSE;
    field_1 = TRUE;
    field_2 = FALSE;
    field_3 = FALSE;
    m_nTransValue = 0;
    m_dwFlags = 0x20000;
}

// 0x586A60
void IcewindCVisualEffect::sub_586A60(BOOLEAN a1)
{
    if (a1 == TRUE) {
        field_0 = TRUE;
        m_dwFlags |= 0x10000;
    } else {
        field_0 = FALSE;
        m_dwFlags &= ~0x10000;
    }
}

// 0x586A90
void IcewindCVisualEffect::sub_586A90(BOOLEAN a1)
{
    if (a1 == TRUE) {
        field_1 = TRUE;
        m_dwFlags |= 0x200;
    } else {
        field_1 = FALSE;
        m_dwFlags &= ~0x200;
    }
}

// 0x586AC0
void IcewindCVisualEffect::sub_586AC0(BOOLEAN a1, INT nTransValue)
{
    if (a1 == TRUE) {
        field_3 = TRUE;
        m_nTransValue = nTransValue;
        m_dwFlags |= 0x2;
    } else {
        field_3 = FALSE;
        m_nTransValue = 0;
        m_dwFlags &= ~0x2;
    }
}

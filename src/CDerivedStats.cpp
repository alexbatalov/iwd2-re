#include "CDerivedStats.h"

#include "CUtil.h"

// 0x443B30
CDerivedStats::CDerivedStats()
{
    // TODO: Incomplete.
}

// 0x4464E0
CDerivedStats& CDerivedStats::operator+=(const CDerivedStats& other)
{
    field_4 += other.field_4;
    field_6 += other.field_6;
    field_8 += other.field_8;
    field_A += other.field_A;
    field_C += other.field_C;
    field_E += other.field_E;
    field_10 += other.field_10;
    field_12 += other.field_12;
    field_14 += other.field_14;
    field_16 += other.field_16;
    field_18 += other.field_18;
    field_1A += other.field_1A;
    field_1C += other.field_1C;
    field_1E += other.field_1E;
    field_20 += other.field_20;
    field_22 += other.field_22;
    field_24 += other.field_24;
    field_26 += other.field_26;
    field_28 += other.field_28;
    field_2A += other.field_2A;
    field_2C += other.field_2C;
    field_2E += other.field_2E;
    field_30 += other.field_30;
    field_32 += other.field_32;
    field_34 += other.field_34;
    field_36 += other.field_36;
    field_B8 += other.field_B8;
    field_38 += other.field_38;
    field_3A += other.field_3A;
    field_3C += other.field_3C;
    m_nLevel += other.m_nLevel;
    m_nSTR += other.m_nSTR;
    m_nINT += other.m_nINT;
    m_nWIS += other.m_nWIS;
    m_nDEX += other.m_nDEX;
    field_5C += other.field_5C;
    field_5E += other.field_5E;
    field_60 += other.field_60;
    field_64 += other.field_64;
    field_68 += other.field_68;
    field_6C += other.field_6C;
    field_70 += other.field_70;
    field_74 += other.field_74;
    field_6C += other.field_6C;
    field_86 += other.field_86;
    field_88 += other.field_88;
    field_8A += other.field_8A;
    field_8C += other.field_8C;
    field_8E += other.field_8E;
    field_90 += other.field_90;
    field_92 += other.field_92;
    field_94 += other.field_94;
    field_96 |= other.field_96;
    field_9A |= other.field_9A;
    field_B2 += other.field_B2;
    field_9E |= other.field_9E;
    field_A6 += other.field_A6;
    field_AA += other.field_AA;

    // TODO: Incomplete (unclear loop).

    field_10C |= other.field_10C;
    field_E8 += other.field_E8;
    field_AE |= other.field_AE;
    field_184 |= other.field_184;
    field_110 += other.field_110;
    field_112 += other.field_112;
    field_114 += other.field_114;
    field_116 += other.field_116;
    field_118 += other.field_118;
    field_11A += other.field_11A;
    field_11C += other.field_11C;
    field_11E += other.field_11E;
    field_120 += other.field_120;
    field_122 += other.field_122;
    field_124 += other.field_124;
    field_128 += other.field_128;
    field_12C += other.field_12C;
    field_130 += other.field_130;
    field_134 += other.field_134;
    field_138 += other.field_138;
    field_13C += other.field_13C;
    field_140 += other.field_140;

    // TODO: Incomplete (unclear loop).

    CheckLimits();

    return *this;
}

// 0x4468F0
void CDerivedStats::CheckLimits()
{
    // TODO: Incomplete.
}

// 0x446DD0
LONG CDerivedStats::GetAtOffset(SHORT offset)
{
    switch (offset) {
    case 1:
        return field_4;
    case 2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1323
        UTIL_ASSERT_MSG(FALSE, "armor class not available -rjf");
    case 3:
        return field_E;
    case 4:
        return field_10;
    case 5:
        return field_12;
    case 6:
        return field_14;
    case 7:
        return field_18;
    case 8:
        return field_1A;
    case 9:
        return field_1C;
    case 10:
        return field_1E;
    case 11:
        return field_20;
    case 12:
        return field_144[8];
    case 14:
        return field_22;
    case 15:
        return field_24;
    case 16:
        return field_26;
    case 17:
        return field_28;
    case 18:
        return field_2A;
    case 19:
        return field_2C;
    case 20:
        return field_2E;
    case 21:
        return field_30;
    case 22:
        return field_32;
    case 23:
        return field_34;
    case 24:
        return field_36;
    case 25:
        return field_144[0];
    case 26:
        return field_144[10];
    case 27:
        return field_144[9];
    case 28:
        return field_144[12];
    case 29:
        return field_144[11];
    case 30:
        return field_38;
    case 31:
        return field_3A;
    case 32:
        return field_3C;
    case 33:
        return field_144[15];
    case 34:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1397
        UTIL_ASSERT(FALSE);
    case 35:
        return field_52;
    case 36:
        return m_nSTR;
    case 37:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1412
        UTIL_ASSERT(FALSE);
    case 38:
        return m_nINT;
    case 39:
        return m_nWIS;
    case 40:
        return m_nDEX;
    case 41:
        return field_5C;
    case 42:
        return field_5E;
    case 43:
        return field_60;
    case 44:
        return field_64;
    case 45:
        return field_68;
    case 46:
        return field_6C;
    case 47:
        return field_70;
    case 48:
        return field_74;
    case 49:
        return field_76;
    case 50:
        return field_86;
    case 51:
        return field_88;
    case 52:
        return field_8A;
    case 53:
        return field_8C;
    case 54:
        return field_8E;
    case 55:
        return field_90;
    case 56:
        return field_92;
    case 57:
        return field_94;
    case 58:
        return field_96;
    case 59:
        return field_9A;
    case 60:
        return field_B2;
    case 61:
        return field_9E;
    case 68:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1400
        UTIL_ASSERT(FALSE);
    case 69:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1403
        UTIL_ASSERT(FALSE);
    case 70:
        return field_AE;
    case 71:
        return field_B4;
    case 72:
        return field_B6;
    case 73:
        return field_B8;
    case 74:
        return field_BA;
    case 75:
        return field_BC;
    case 76:
        return field_C0;
    case 77:
        return field_C4;
    case 78:
        return field_C6;
    case 79:
        return field_C8;
    case 80:
        return field_CA;
    case 81:
        return field_CC;
    case 82:
        return field_D0;
    case 83:
        return field_D4;
    case 84:
        return field_D8;
    case 85:
        return field_DC;
    case 86:
        return field_E0;
    case 87:
        return field_E4;
    case 88:
        return field_E8;
    case 89:
        return field_A2;
    case 90:
        return field_144[6];
    case 91:
        return field_A6;
    case 92:
        return field_AA;
    case 93:
        return field_3E;
    case 94:
        return field_144[14];
    case 95:
        return m_nLevel;
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
        return GetClassLevel(offset - 95);
    case 107:
        return 1984;
    default:
        return 0;
    }
}

// 0x447390
int CDerivedStats::sub_447390()
{
    return field_64;
}

// 0x4473A0
unsigned char CDerivedStats::sub_4473A0()
{
    return m_nLevel;
}

// 0x4473B0
DWORD CDerivedStats::GetSorcererWizardLevel()
{
    DWORD dwArcaneClassesMask = m_classMask & (CLASSMASK_SORCERER | CLASSMASK_WIZARD);
    DWORD dwCurrentClassMask = 1;
    DWORD nLevel = 0;

    if (dwArcaneClassesMask != 0) {
        for (int index = 0; index < CAIOBJECT_CLASS_MAX; index++) {
            if (dwCurrentClassMask > (CLASSMASK_SORCERER | CLASSMASK_WIZARD)) {
                break;
            }

            if ((dwArcaneClassesMask & dwCurrentClassMask) != 0) {
                nLevel += m_nClassLevels[index];
            }

            dwCurrentClassMask <<= 1;
        }
    }

    return nLevel;
}

// 0x4473F0
DWORD CDerivedStats::GetBardMonkRogueLevel()
{
    DWORD dwArcaneClassesMask = m_classMask & (CLASSMASK_BARD | CLASSMASK_MONK | CLASSMASK_ROGUE);
    DWORD dwCurrentClassMask = 1;
    DWORD nLevel = 0;

    if (dwArcaneClassesMask != 0) {
        for (int index = 0; index < CAIOBJECT_CLASS_MAX; index++) {
            if (dwCurrentClassMask > (CLASSMASK_BARD | CLASSMASK_MONK | CLASSMASK_ROGUE)) {
                break;
            }

            if ((dwArcaneClassesMask & dwCurrentClassMask) != 0) {
                nLevel += m_nClassLevels[index];
            }

            dwCurrentClassMask <<= 1;
        }
    }

    return nLevel;
}

// 0x447940
BOOL CDerivedStats::HasClassMask(INT iClassType)
{
    return (iClassType & m_classMask) != 0;
}

// 0x447990
DWORD CDerivedStats::GetClassLevel(int iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2070
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2071
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_nClassLevels[iClassType - 1];
}

// 0x4479E0
void CDerivedStats::SetClassLevel(INT iClassType, INT nLevel)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2087
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2088
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    BYTE nOldLevel = m_nClassLevels[iClassType - 1];
    m_nClassLevels[iClassType - 1] = nLevel;
    m_nLevel += nLevel - nOldLevel;

    if (nLevel != 0) {
        m_classMask |= 1 << (iClassType - 1);
    } else {
        m_classMask &= ~(1 << (iClassType - 1));
    }
}

// 0x447A70
BOOL CDerivedStats::HasClass(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2121
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2122
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_nClassLevels[iClassType - 1] != 0;
}

// 0x447AD0
INT CDerivedStats::GetBestClass()
{
    int nBestClassLevel = 0;
    int nBestClass = 0;
    for (int nClass = 0; nClass < CAIOBJECT_CLASS_MAX; nClass++) {
        if (nBestClassLevel < m_nClassLevels[nClass]) {
            nBestClassLevel = m_nClassLevels[nClass];
            nBestClass = nClass;
        }
    }

    return nBestClass + 1;
}

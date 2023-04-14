#include "CAIObjectType.h"

#include "CUtil.h"

// 0x847D40
const int CAIObjectType::INSTANCE_NOT_SPRITE = 0x80000000;

// 0x847D44
const BYTE CAIObjectType::SPECIALCASE_MYSELF[5] = {
    1,
    0,
    0,
    0,
    0,
};

// 0x8C7748
const CAIObjectType CAIObjectType::ANYONE(0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0);

// 0x8C7688
const CAIObjectType CAIObjectType::ANYTHING(EA_ANYTHING, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0);

// 0x8C7708
const CAIObjectType CAIObjectType::NOONE(255, 255, 255, 255, 255, 255, 255, 255, -1, 0, 0);

// 0x8C76C8
const CAIObjectType CAIObjectType::NOT_SPRITE(EA_INANIMATE, 255, 255, 255, 255, 255, 255, 255, INSTANCE_NOT_SPRITE, 0, 0);

// 0x8C7788
const CAIObjectType CAIObjectType::OBJECT_MYSELF(0, 0, 0, 0, 0, 0, 0, 0, -1, SPECIALCASE_MYSELF, CString(""), 0, 0);

// NOTE: Inlined.
CAIObjectType::CAIObjectType(const CAIObjectType& type)
{
    Set(type);
}

// 0x40AD00
CAIObjectType::CAIObjectType(BYTE nEnemyAlly, BYTE nGeneral, BYTE nRace, BYTE nSubRace, BYTE nClass, BYTE nSpecific, BYTE nGender, BYTE nAlignment, int nInstance, const BYTE* SpecialCase, const CString& sName, BYTE nAvClass, int nClassMask)
{
    m_nRace = nRace;
    m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_NONE;
    m_nRadius = 0;
    m_nEnemyAlly = nEnemyAlly;
    m_nGeneral = nGeneral;
    m_nSubRace = nSubRace;
    if (m_nSubRace == -1) {
        m_nSubRace = 0;
    }
    m_nGender = nGender;
    m_nSpecific = nSpecific;
    m_nClass = nClass;
    m_nAlignment = nAlignment;
    m_nAvClass = nAvClass;
    if (m_nAvClass == 0) {
        m_nAvClass = nClass;
    }
    m_nClassMask = nClassMask;
    m_nInstance = nInstance;

    if (SpecialCase != NULL) {
        m_SpecialCase[0] = SpecialCase[0];
        m_SpecialCase[1] = SpecialCase[1];
        m_SpecialCase[2] = SpecialCase[2];
        m_SpecialCase[3] = SpecialCase[3];
        m_SpecialCase[4] = SpecialCase[4];
    } else {
        m_SpecialCase[0] = 0;
        m_SpecialCase[1] = 0;
        m_SpecialCase[2] = 0;
        m_SpecialCase[3] = 0;
        m_SpecialCase[4] = 0;
    }

    m_sName = sName;

    if (m_nClassMask == 0) {
        switch (m_nClass) {
        case C_BARBARIAN:
            m_nClassMask = CLASSMASK_BARBARIAN;
            break;
        case C_BARD:
            m_nClassMask = CLASSMASK_BARD;
            break;
        case C_CLERIC:
            m_nClassMask = CLASSMASK_CLERIC;
            break;
        case C_DRUID:
            m_nClassMask = CLASSMASK_DRUID;
            break;
        case C_FIGHTER:
            m_nClassMask = CLASSMASK_FIGHTER;
            break;
        case C_MONK:
            m_nClassMask = CLASSMASK_MONK;
            break;
        case C_PALADIN:
            m_nClassMask = CLASSMASK_PALADIN;
            break;
        case C_RANGER:
            m_nClassMask = CLASSMASK_RANGER;
            break;
        case C_ROGUE:
            m_nClassMask = CLASSMASK_ROGUE;
            break;
        case C_SORCERER:
            m_nClassMask = CLASSMASK_SORCERER;
            break;
        case C_WIZARD:
            m_nClassMask = CLASSMASK_WIZARD;
            break;
        }
    }
}

// 0x40AE80
CAIObjectType::CAIObjectType(BYTE nEnemyAlly, BYTE nGeneral, BYTE nRace, BYTE nSubRace, BYTE nClass, BYTE nSpecific, BYTE nGender, BYTE nAlignment, int nInstance, BYTE nAvClass, int nClassMask)
{
    m_nRace = nRace;
    m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_NONE;
    m_nEnemyAlly = nEnemyAlly;
    m_nGeneral = nGeneral;
    m_nSubRace = nSubRace;
    if (m_nSubRace == -1) {
        m_nSubRace = 0;
    }
    m_nGender = nGender;
    m_nSpecific = nSpecific;
    m_nClass = nClass;
    m_nAlignment = nAlignment;
    m_nAvClass = nAvClass;
    if (m_nAvClass == 0) {
        m_nAvClass = nClass;
    }
    m_nClassMask = nClassMask;
    m_nInstance = nInstance;

    m_SpecialCase[0] = 0;
    m_SpecialCase[1] = 0;
    m_SpecialCase[2] = 0;
    m_SpecialCase[3] = 0;
    m_SpecialCase[4] = 0;

    m_sName = "";

    if (m_nClassMask == 0) {
        switch (m_nClass) {
        case C_BARBARIAN:
            m_nClassMask = CLASSMASK_BARBARIAN;
            break;
        case C_BARD:
            m_nClassMask = CLASSMASK_BARD;
            break;
        case C_CLERIC:
            m_nClassMask = CLASSMASK_CLERIC;
            break;
        case C_DRUID:
            m_nClassMask = CLASSMASK_DRUID;
            break;
        case C_FIGHTER:
            m_nClassMask = CLASSMASK_FIGHTER;
            break;
        case C_MONK:
            m_nClassMask = CLASSMASK_MONK;
            break;
        case C_PALADIN:
            m_nClassMask = CLASSMASK_PALADIN;
            break;
        case C_RANGER:
            m_nClassMask = CLASSMASK_RANGER;
            break;
        case C_ROGUE:
            m_nClassMask = CLASSMASK_ROGUE;
            break;
        case C_SORCERER:
            m_nClassMask = CLASSMASK_SORCERER;
            break;
        case C_WIZARD:
            m_nClassMask = CLASSMASK_WIZARD;
            break;
        }
    }
}

// NOTE: Odd location.
//
// 0x6F2D70
CAIObjectType::~CAIObjectType()
{
}

// 0x40B6E0
void CAIObjectType::Set(const CAIObjectType& type)
{
    m_nEnemyAlly = type.m_nEnemyAlly;
    m_nGeneral = type.m_nGeneral;
    m_nRace = type.m_nRace;
    m_nSubRace = type.m_nSubRace;
    if (m_nSubRace == -1) {
        m_nSubRace = 0;
    }
    m_nClass = type.m_nClass;
    m_nSpecific = type.m_nSpecific;
    m_nGender = type.m_nGender;
    m_nAlignment = type.m_nAlignment;
    m_nInstance = type.m_nInstance;
    m_nAvClass = type.m_nAvClass;
    m_nClassMask = type.m_nClassMask;

    m_SpecialCase[0] = type.m_SpecialCase[0];
    m_SpecialCase[1] = type.m_SpecialCase[1];
    m_SpecialCase[2] = type.m_SpecialCase[2];
    m_SpecialCase[3] = type.m_SpecialCase[3];
    m_SpecialCase[4] = type.m_SpecialCase[4];

    m_nLocationType = type.m_nLocationType;
    switch (m_nLocationType) {
    case CAIOBJECTTYPE_LOCATION_TYPE_RECT:
        m_rect = type.m_rect;
        break;
    case CAIOBJECTTYPE_LOCATION_TYPE_POINT:
        m_ptCenter = type.m_ptCenter;
        m_nRadius = type.m_nRadius;
        break;
    }

    if (m_nClassMask == 0) {
        switch (m_nClass) {
        case C_BARBARIAN:
            m_nClassMask = CLASSMASK_BARBARIAN;
            break;
        case C_BARD:
            m_nClassMask = CLASSMASK_BARD;
            break;
        case C_CLERIC:
            m_nClassMask = CLASSMASK_CLERIC;
            break;
        case C_DRUID:
            m_nClassMask = CLASSMASK_DRUID;
            break;
        case C_FIGHTER:
            m_nClassMask = CLASSMASK_FIGHTER;
            break;
        case C_MONK:
            m_nClassMask = CLASSMASK_MONK;
            break;
        case C_PALADIN:
            m_nClassMask = CLASSMASK_PALADIN;
            break;
        case C_RANGER:
            m_nClassMask = CLASSMASK_RANGER;
            break;
        case C_ROGUE:
            m_nClassMask = CLASSMASK_ROGUE;
            break;
        case C_SORCERER:
            m_nClassMask = CLASSMASK_SORCERER;
            break;
        case C_WIZARD:
            m_nClassMask = CLASSMASK_WIZARD;
            break;
        }
    }

    m_sName = type.m_sName;
}

// 0x40CAC0
CString CAIObjectType::GetName() const
{
    return m_sName;
}

// 0x40CC40
BOOL CAIObjectType::Equal(const CAIObjectType& type) const
{
    return m_nEnemyAlly == type.m_nEnemyAlly
        && m_nGeneral == type.m_nGeneral
        && m_nRace == type.m_nRace
        && m_nSubRace == type.m_nSubRace
        && m_nClassMask == type.m_nClassMask
        && m_nSpecific == type.m_nSpecific
        && m_nAlignment == type.m_nAlignment
        && m_nGender == type.m_nGender
        && m_nInstance == type.m_nInstance;
}

// 0x40D430
void CAIObjectType::SetSpecialCase(const BYTE* SpecialCase)
{
    for (int index = 0; index < 5; index++) {
        m_SpecialCase[index] = SpecialCase[index];
    }
}

// 0x40D700
BOOL CAIObjectType::IsEnemyOf(const CAIObjectType& type) const
{
    if (type.m_nEnemyAlly <= EA_GOODCUTOFF && m_nEnemyAlly >= EA_EVILCUTOFF) {
        return TRUE;
    }

    if (m_nEnemyAlly <= EA_GOODCUTOFF && type.m_nEnemyAlly >= EA_EVILCUTOFF) {
        return TRUE;
    }

    return FALSE;
}

// 0x40D730
CAIObjectType CAIObjectType::GetEnemyOf() const
{
    CAIObjectType enemy(ANYONE);
    if (m_nEnemyAlly <= EA_GOODCUTOFF) {
        enemy.m_nEnemyAlly = EA_EVILCUTOFF;
    } else if (m_nEnemyAlly >= EA_EVILCUTOFF) {
        enemy.m_nEnemyAlly = EA_GOODCUTOFF;
    } else {
        enemy.m_nEnemyAlly = EA_EVILCUTOFF;
    }
    return enemy;
}

// 0x40D7E0
BOOL CAIObjectType::IsClassValid(BYTE nClass) const
{
    if (nClass == 0) {
        CString sError;
        sError.Format("CAIObjectType::IsClassValid() - '%s' has no classes set.", GetName());
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CAIObjectType.cpp
        // __LINE__: 2818
        UTIL_ASSERT_MSG(FALSE, sError);
    }

    return (m_nClassMask & (1 << (nClass - 1))) != 0;
}

// 0x40D8A0
BOOL CAIObjectType::sub_40D8A0(const CPoint& pt) const
{
    if (m_ptCenter == pt) {
        return TRUE;
    }

    if (m_nRadius > 0) {
        if ((m_ptCenter.x - pt.x) * (m_ptCenter.x - pt.x) + (m_ptCenter.y - pt.y) * (m_ptCenter.y - pt.y) <= m_nRadius * m_nRadius) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x40D900
BOOL CAIObjectType::sub_40D900(const CPoint& pt) const
{
    return PtInRect(m_rect, pt);
}

// 0x40D920
BOOL CAIObjectType::sub_40D920(const CPoint& pt) const
{
    // NOTE: Jump table at 0x40BA04.
    switch (m_nLocationType) {
    case CAIOBJECTTYPE_LOCATION_TYPE_POINT:
        return sub_40D8A0(pt);
    case CAIOBJECTTYPE_LOCATION_TYPE_RECT:
        return sub_40D900(pt);
    default:
        return TRUE;
    }
}

// 0x40D940
void CAIObjectType::SetCenter(const CPoint& pt)
{
    m_ptCenter = pt;
    m_nRadius = 0;
    m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_POINT;
}

// 0x40D960
void CAIObjectType::SetRect(const CRect& rect)
{
    m_rect = rect;
    m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_RECT;
}

// 0x40D990
void CAIObjectType::AddClass(BYTE nClass)
{
    switch (nClass) {
    case C_BARBARIAN:
        m_nClassMask |= CLASSMASK_BARBARIAN;
        break;
    case C_BARD:
        m_nClassMask |= CLASSMASK_BARD;
        break;
    case C_CLERIC:
        m_nClassMask |= CLASSMASK_CLERIC;
        break;
    case C_DRUID:
        m_nClassMask |= CLASSMASK_DRUID;
        break;
    case C_FIGHTER:
        m_nClassMask |= CLASSMASK_FIGHTER;
        break;
    case C_MONK:
        m_nClassMask |= CLASSMASK_MONK;
        break;
    case C_PALADIN:
        m_nClassMask |= CLASSMASK_PALADIN;
        break;
    case C_RANGER:
        m_nClassMask |= CLASSMASK_RANGER;
        break;
    case C_ROGUE:
        m_nClassMask |= CLASSMASK_ROGUE;
        break;
    case C_SORCERER:
        m_nClassMask |= CLASSMASK_SORCERER;
        break;
    case C_WIZARD:
        m_nClassMask |= CLASSMASK_WIZARD;
        break;
    }
}

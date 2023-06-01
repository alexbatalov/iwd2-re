#include "CAIObjectType.h"

#include "CGameAIBase.h"
#include "CUtil.h"

// 0x847C34
const BYTE CAIObjectType::EA_ALL = CAIOBJECTTYPE_EA_ALL;

// 0x847C35
const BYTE CAIObjectType::EA_PC = CAIOBJECTTYPE_EA_PC;

// 0x847C36
const BYTE CAIObjectType::EA_FAMILIAR = CAIOBJECTTYPE_EA_FAMILIAR;

// 0x847C37
const BYTE CAIObjectType::EA_ALLY = CAIOBJECTTYPE_EA_ALLY;

// 0x847C38
const BYTE CAIObjectType::EA_CONTROLLED = CAIOBJECTTYPE_EA_CONTROLLED;

// 0x847C39
const BYTE CAIObjectType::EA_CHARMED = CAIOBJECTTYPE_EA_CHARMED;

// 0x847C3A
const BYTE CAIObjectType::EA_0x847C3A = CAIOBJECTTYPE_EA_0X847C3A;

// 0x847C3B
const BYTE CAIObjectType::EA_GOODCUTOFF = CAIOBJECTTYPE_EA_GOODCUTOFF;

// 0x847C3C
const BYTE CAIObjectType::EA_CONTROLCUTOFF = CAIOBJECTTYPE_EA_CONTROLCUTOFF;

// 0x847C3D
const BYTE CAIObjectType::EA_NOTGOOD = CAIOBJECTTYPE_EA_NOTGOOD;

// 0x847C3E
const BYTE CAIObjectType::EA_NEUTRAL = CAIOBJECTTYPE_EA_NEUTRAL;

// 0x847C3F
const BYTE CAIObjectType::EA_NOTEVIL = CAIOBJECTTYPE_EA_NOTEVIL;

// 0x847C40
const BYTE CAIObjectType::EA_ENEMY = CAIOBJECTTYPE_EA_ENEMY;

// 0x847C41
const BYTE CAIObjectType::EA_CHARMED_PC = CAIOBJECTTYPE_EA_CHARMED_PC;

// 0x847C42
const BYTE CAIObjectType::EA_EVILCUTOFF = CAIOBJECTTYPE_EA_EVILCUTOFF;

// 0x847C43
const BYTE CAIObjectType::EA_ARENAPC = CAIOBJECTTYPE_EA_ARENAPC;

// 0x847C44
const BYTE CAIObjectType::EA_INANIMATE = CAIOBJECTTYPE_EA_INANIMATE;

// 0x847C45
const BYTE CAIObjectType::EA_ANYTHING = CAIOBJECTTYPE_EA_ANYTHING;

// 0x847C5B
const BYTE CAIObjectType::R_HUMAN = CAIOBJECTTYPE_R_HUMAN;

// 0x847C5C
const BYTE CAIObjectType::R_ELF = CAIOBJECTTYPE_R_ELF;

// 0x847C5D
const BYTE CAIObjectType::R_HALF_ELF = CAIOBJECTTYPE_R_HALF_ELF;

// 0x847C5E
const BYTE CAIObjectType::R_DWARF = CAIOBJECTTYPE_R_DWARF;

// 0x847C5F
const BYTE CAIObjectType::R_HALFLING = CAIOBJECTTYPE_R_HALFLING;

// 0x847C60
const BYTE CAIObjectType::R_GNOME = CAIOBJECTTYPE_R_GNOME;

// 0x847C61
const BYTE CAIObjectType::R_HALF_ORC = CAIOBJECTTYPE_R_HALF_ORC;

// 0x847C62
const BYTE CAIObjectType::R_ANKHEG = CAIOBJECTTYPE_R_ANKHEG;

// 0x847C63
const BYTE CAIObjectType::R_BASILISK = CAIOBJECTTYPE_R_BASILISK;

// 0x847C64
const BYTE CAIObjectType::R_BEAR = CAIOBJECTTYPE_R_BEAR;

// 0x847C65
const BYTE CAIObjectType::R_CARRIONCRAWLER = CAIOBJECTTYPE_R_CARRIONCRAWLER;

// 0x847C66
const BYTE CAIObjectType::R_DOG = CAIOBJECTTYPE_R_DOG;

// 0x847C67
const BYTE CAIObjectType::R_DOPPLEGANGER = CAIOBJECTTYPE_R_DOPPLEGANGER;

// 0x847C68
const BYTE CAIObjectType::R_ETTERCAP = CAIOBJECTTYPE_R_ETTERCAP;

// 0x847C69
const BYTE CAIObjectType::R_GHOUL = CAIOBJECTTYPE_R_GHOUL;

// 0x847C6A
const BYTE CAIObjectType::R_GIBBERLING = CAIOBJECTTYPE_R_GIBBERLING;

// 0x847C6B
const BYTE CAIObjectType::R_GNOLL = CAIOBJECTTYPE_R_GNOLL;

// 0x847C6C
const BYTE CAIObjectType::R_HOBGOBLIN = CAIOBJECTTYPE_R_HOBGOBLIN;

// 0x847C6D
const BYTE CAIObjectType::R_KOBOLD = CAIOBJECTTYPE_R_KOBOLD;

// 0x847C6E
const BYTE CAIObjectType::R_OGRE = CAIOBJECTTYPE_R_OGRE;

// 0x847C6F
const BYTE CAIObjectType::R_SKELETON = CAIOBJECTTYPE_R_SKELETON;

// 0x847C70
const BYTE CAIObjectType::R_SPIDER = CAIOBJECTTYPE_R_SPIDER;

// 0x847C71
const BYTE CAIObjectType::R_WOLF = CAIOBJECTTYPE_R_WOLF;

// 0x847C72
const BYTE CAIObjectType::R_WYVERN = CAIOBJECTTYPE_R_WYVERN;

// 0x847C73
const BYTE CAIObjectType::R_SLIME = CAIOBJECTTYPE_R_SLIME;

// 0x847C74
const BYTE CAIObjectType::R_FAIRY = CAIOBJECTTYPE_R_FAIRY;

// 0x847C75
const BYTE CAIObjectType::R_BEETLE = CAIOBJECTTYPE_R_BEETLE;

// 0x847C76
const BYTE CAIObjectType::R_CARRION_CRAWLER = CAIOBJECTTYPE_R_CARRION_CRAWLER;

// 0x847C77
const BYTE CAIObjectType::R_ELEMENTAL = CAIOBJECTTYPE_R_ELEMENTAL;

// 0x847C78
const BYTE CAIObjectType::R_GIANT = CAIOBJECTTYPE_R_GIANT;

// 0x847C79
const BYTE CAIObjectType::R_DRAKE = CAIOBJECTTYPE_R_DRAKE;

// 0x847C7A
const BYTE CAIObjectType::R_GOBLIN = CAIOBJECTTYPE_R_GOBLIN;

// 0x847C7B
const BYTE CAIObjectType::R_GOLEM = CAIOBJECTTYPE_R_GOLEM;

// 0x847C7C
const BYTE CAIObjectType::R_LIZARDMAN = CAIOBJECTTYPE_R_LIZARDMAN;

// 0x847C7D
const BYTE CAIObjectType::R_MANTICORE = CAIOBJECTTYPE_R_MANTICORE;

// 0x847C7E
const BYTE CAIObjectType::R_MYCONID = CAIOBJECTTYPE_R_MYCONID;

// 0x847C7F
const BYTE CAIObjectType::R_ORC = CAIOBJECTTYPE_R_ORC;

// 0x847C80
const BYTE CAIObjectType::R_SALAMANDER = CAIOBJECTTYPE_R_SALAMANDER;

// 0x847C81
const BYTE CAIObjectType::R_SHRIEKER = CAIOBJECTTYPE_R_SHRIEKER;

// 0x847C82
const BYTE CAIObjectType::R_SVIRFNEBLIN = CAIOBJECTTYPE_R_SVIRFNEBLIN;

// 0x847C83
const BYTE CAIObjectType::R_TANARI = CAIOBJECTTYPE_R_TANARI;

// 0x847C84
const BYTE CAIObjectType::R_TROLL = CAIOBJECTTYPE_R_TROLL;

// 0x847C85
const BYTE CAIObjectType::R_UMBERHULK = CAIOBJECTTYPE_R_UMBERHULK;

// 0x847C86
const BYTE CAIObjectType::R_UNDEAD = CAIOBJECTTYPE_R_UNDEAD;

// 0x847C87
const BYTE CAIObjectType::R_YUANTI = CAIOBJECTTYPE_R_YUANTI;

// 0x847C88
const BYTE CAIObjectType::R_HARPY = CAIOBJECTTYPE_R_HARPY;

// 0x847C89
const BYTE CAIObjectType::R_DJINNI = CAIOBJECTTYPE_R_DJINNI;

// 0x847C8A
const BYTE CAIObjectType::R_SHAMBLING_MOUND = CAIOBJECTTYPE_R_SHAMBLING_MOUND;

// 0x847C8B
const BYTE CAIObjectType::R_BEHOLDER = CAIOBJECTTYPE_R_BEHOLDER;

// 0x847C8C
const BYTE CAIObjectType::R_RAKSHASA = CAIOBJECTTYPE_R_RAKSHASA;

// 0x847C8D
const BYTE CAIObjectType::R_BUGBEAR = CAIOBJECTTYPE_R_BUGBEAR;

// 0x847C8E
const BYTE CAIObjectType::R_DRIDER = CAIOBJECTTYPE_R_DRIDER;

// 0x847C8F
const BYTE CAIObjectType::R_HOOK_HORROR = CAIOBJECTTYPE_R_HOOK_HORROR;

// 0x847C90
const BYTE CAIObjectType::R_SHAPESHIFTER = CAIOBJECTTYPE_R_SHAPESHIFTER;

// 0x847C91
const BYTE CAIObjectType::R_WILLOWISP = CAIOBJECTTYPE_R_WILLOWISP;

// 0x847C92
const BYTE CAIObjectType::R_OTYUGH = CAIOBJECTTYPE_R_OTYUGH;

// 0x847C93
const BYTE CAIObjectType::R_NO_RACE = CAIOBJECTTYPE_R_NO_RACE;

// 0x847C94
const BYTE CAIObjectType::R_DEMONIC = CAIOBJECTTYPE_R_DEMONIC;

// 0x847C95
const BYTE CAIObjectType::R_LYCANTHROPE = CAIOBJECTTYPE_R_LYCANTHROPE;

// 0x847C96
const BYTE CAIObjectType::R_SWORD = CAIOBJECTTYPE_R_SWORD;

// 0x847C97
const BYTE CAIObjectType::R_BOW = CAIOBJECTTYPE_R_BOW;

// 0x847C98
const BYTE CAIObjectType::R_XBOW = CAIOBJECTTYPE_R_XBOW;

// 0x847C99
const BYTE CAIObjectType::R_STAFF = CAIOBJECTTYPE_R_STAFF;

// 0x847C9A
const BYTE CAIObjectType::R_SLING = CAIOBJECTTYPE_R_SLING;

// 0x847C9B
const BYTE CAIObjectType::R_MACE = CAIOBJECTTYPE_R_MACE;

// 0x847C9C
const BYTE CAIObjectType::R_DAGGER = CAIOBJECTTYPE_R_DAGGER;

// 0x847C9D
const BYTE CAIObjectType::R_SPEAR = CAIOBJECTTYPE_R_SPEAR;

// 0x847C9E
const BYTE CAIObjectType::R_FIST = CAIOBJECTTYPE_R_FIST;

// 0x847C9F
const BYTE CAIObjectType::R_HAMMER = CAIOBJECTTYPE_R_HAMMER;

// 0x847CA0
const BYTE CAIObjectType::R_MORNINGSTAR = CAIOBJECTTYPE_R_MORNINGSTAR;

// 0x847CA1
const BYTE CAIObjectType::R_ROBES = CAIOBJECTTYPE_R_ROBES;

// 0x847CA2
const BYTE CAIObjectType::R_LEATHER = CAIOBJECTTYPE_R_LEATHER;

// 0x847CA3
const BYTE CAIObjectType::R_CHAIN = CAIOBJECTTYPE_R_CHAIN;

// 0x847CA4
const BYTE CAIObjectType::R_PLATE = CAIOBJECTTYPE_R_PLATE;

// 0x847CA5
const BYTE CAIObjectType::C_BARBARIAN = CAIOBJECTTYPE_C_BARBARIAN;

// 0x847CA6
const BYTE CAIObjectType::C_BARD = CAIOBJECTTYPE_C_BARD;

// 0x847CA7
const BYTE CAIObjectType::C_CLERIC = CAIOBJECTTYPE_C_CLERIC;

// 0x847CA8
const BYTE CAIObjectType::C_DRUID = CAIOBJECTTYPE_C_DRUID;

// 0x847CA9
const BYTE CAIObjectType::C_FIGHTER = CAIOBJECTTYPE_C_FIGHTER;

// 0x847CAA
const BYTE CAIObjectType::C_MONK = CAIOBJECTTYPE_C_MONK;

// 0x847CAB
const BYTE CAIObjectType::C_PALADIN = CAIOBJECTTYPE_C_PALADIN;

// 0x847CAC
const BYTE CAIObjectType::C_RANGER = CAIOBJECTTYPE_C_RANGER;

// 0x847CAD
const BYTE CAIObjectType::C_ROGUE = CAIOBJECTTYPE_C_ROGUE;

// 0x847CAE
const BYTE CAIObjectType::C_SORCERER = CAIOBJECTTYPE_C_SORCERER;

// 0x847CAF
const BYTE CAIObjectType::C_WIZARD = CAIOBJECTTYPE_C_WIZARD;

// 0x847CF2
const BYTE CAIObjectType::SEX_MALE = CAIOBJECTTYPE_SEX_MALE;

// 0x847CF3
const BYTE CAIObjectType::SEX_FEMALE = CAIOBJECTTYPE_SEX_FEMALE;

// 0x847CF8
const BYTE CAIObjectType::LAWFUL_GOOD = CAIOBJECTTYPE_LAWFUL_GOOD;

// 0x847CF9
const BYTE CAIObjectType::LAWFUL_NEUTRAL = CAIOBJECTTYPE_LAWFUL_NEUTRAL;

// 0x847CFA
const BYTE CAIObjectType::LAWFUL_EVIL = CAIOBJECTTYPE_LAWFUL_EVIL;

// 0x847CFB
const BYTE CAIObjectType::NEUTRAL_GOOD = CAIOBJECTTYPE_NEUTRAL_GOOD;

// 0x847CFC
const BYTE CAIObjectType::NEUTRAL = CAIOBJECTTYPE_NEUTRAL;

// 0x847CFD
const BYTE CAIObjectType::NEUTRAL_EVIL = CAIOBJECTTYPE_NEUTRAL_EVIL;

// 0x847CFE
const BYTE CAIObjectType::CHAOTIC_GOOD = CAIOBJECTTYPE_CHAOTIC_GOOD;

// 0x847CFF
const BYTE CAIObjectType::CHAOTIC_NEUTRAL = CAIOBJECTTYPE_CHAOTIC_NEUTRAL;

// 0x847D00
const BYTE CAIObjectType::CHAOTIC_EVIL = CAIOBJECTTYPE_CHAOTIC_EVIL;

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

// 0x40AFE0
BOOL CAIObjectType::OfType(const CAIObjectType& type, BOOL bCheckForNonSprites, BOOL bNoNonSprites) const
{
    if (Equal(NOONE)) {
        return Equal(type);
    }

    if (Equal(ANYONE)) {
        if (Equal(NOT_SPRITE) && !bCheckForNonSprites) {
            return FALSE;
        }
    }

    if (Equal(NOT_SPRITE) && bNoNonSprites) {
        return FALSE;
    }

    // TODO: Incomplete.

    return TRUE;
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

// 0x40B880
void CAIObjectType::Decode(CGameAIBase* caller)
{
    // TODO: Incomplete.
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

// 0x40D450
void CAIObjectType::Read(CString sData)
{
    // TODO: Incomplete.
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

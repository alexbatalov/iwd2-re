#include "CAIObjectType.h"

#include "CAIUtil.h"
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

// 0x847C46
const BYTE CAIObjectType::G_HUMANOID = CAIOBJECTTYPE_G_HUMANOID;

// 0x847C47
const BYTE CAIObjectType::G_ANIMAL = CAIOBJECTTYPE_G_ANIMAL;

// 0x847C48
const BYTE CAIObjectType::G_DEAD = CAIOBJECTTYPE_G_DEAD;

// 0x847C49
const BYTE CAIObjectType::G_UNDEAD = CAIOBJECTTYPE_G_UNDEAD;

// 0x847C4A
const BYTE CAIObjectType::G_GIANTHUMANOID = CAIOBJECTTYPE_G_GIANTHUMANOID;

// 0x847C4B
const BYTE CAIObjectType::G_FROZEN = CAIOBJECTTYPE_G_FROZEN;

// 0x847C4C
const BYTE CAIObjectType::G_MONSTER = CAIOBJECTTYPE_G_MONSTER;

// 0x847C4D
const BYTE CAIObjectType::G_WEAPON = CAIOBJECTTYPE_G_WEAPON;

// 0x847C4E
const BYTE CAIObjectType::G_ARMOR = CAIOBJECTTYPE_G_ARMOR;

// 0x847C4F
const BYTE CAIObjectType::G_AMULET = CAIOBJECTTYPE_G_AMULET;

// 0x847C50
const BYTE CAIObjectType::G_BELT = CAIOBJECTTYPE_G_BELT;

// 0x847C51
const BYTE CAIObjectType::G_BOOTS = CAIOBJECTTYPE_G_BOOTS;

// 0x847C52
const BYTE CAIObjectType::G_AMMO = CAIOBJECTTYPE_G_AMMO;

// 0x847C53
const BYTE CAIObjectType::G_GENERAL_ITEM = CAIOBJECTTYPE_G_GENERAL_ITEM;

// 0x847C54
const BYTE CAIObjectType::G_HELMET = CAIOBJECTTYPE_G_HELMET;

// 0x847C55
const BYTE CAIObjectType::G_KEY = CAIOBJECTTYPE_G_KEY;

// 0x847C56
const BYTE CAIObjectType::G_POTION = CAIOBJECTTYPE_G_POTION;

// 0x847C57
const BYTE CAIObjectType::G_RING = CAIOBJECTTYPE_G_RING;

// 0x847C58
const BYTE CAIObjectType::G_SCROLL = CAIOBJECTTYPE_G_SCROLL;

// 0x847C59
const BYTE CAIObjectType::G_SHIELD = CAIOBJECTTYPE_G_SHIELD;

// 0x847C5A
const BYTE CAIObjectType::G_GLOVES = CAIOBJECTTYPE_G_GLOVES;

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

    if (type.m_nEnemyAlly != EA_ALL
        && type.m_nEnemyAlly != EA_ANYTHING
        && m_nEnemyAlly != type.m_nEnemyAlly) {
        if (type.m_nEnemyAlly == EA_ALLY) {
            if (m_nEnemyAlly > EA_GOODCUTOFF) {
                return FALSE;
            }
        } else if (type.m_nEnemyAlly == EA_ENEMY) {
            if (m_nEnemyAlly < EA_EVILCUTOFF) {
                return FALSE;
            }
        } else if ((type.m_nEnemyAlly != EA_GOODCUTOFF || m_nEnemyAlly > EA_GOODCUTOFF)
            && (type.m_nEnemyAlly != EA_EVILCUTOFF || m_nEnemyAlly < EA_EVILCUTOFF)
            && (type.m_nEnemyAlly != EA_NOTGOOD || m_nEnemyAlly < EA_NOTGOOD)
            && (type.m_nEnemyAlly != EA_NOTEVIL || m_nEnemyAlly > EA_NOTEVIL)) {
            return FALSE;
        }
    }

    if (type.m_nGeneral != 0 && m_nGeneral != type.m_nGeneral) {
        return FALSE;
    }

    if (type.m_nRace != 0 && m_nRace != type.m_nRace) {
        return FALSE;
    }

    if (type.m_nSubRace != 0 && m_nSubRace != type.m_nSubRace) {
        return FALSE;
    }

    if (type.m_nClass != 0 && m_nClass != type.m_nClass) {
        switch (type.m_nClass) {
        case CAIOBJECTTYPE_C_BARBARIAN:
            if ((m_nClassMask & CLASSMASK_BARBARIAN) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_BARD:
            if ((m_nClassMask & CLASSMASK_BARD) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_CLERIC:
            if ((m_nClassMask & CLASSMASK_CLERIC) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_DRUID:
            if ((m_nClassMask & CLASSMASK_DRUID) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_FIGHTER:
            if ((m_nClassMask & CLASSMASK_FIGHTER) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_MONK:
            if ((m_nClassMask & CLASSMASK_MONK) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_PALADIN:
            if ((m_nClassMask & CLASSMASK_PALADIN) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_RANGER:
            if ((m_nClassMask & CLASSMASK_RANGER) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_ROGUE:
            if ((m_nClassMask & CLASSMASK_ROGUE) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_SORCERER:
            if ((m_nClassMask & CLASSMASK_SORCERER) == 0) {
                return FALSE;
            }
            break;
        case CAIOBJECTTYPE_C_WIZARD:
            if ((m_nClassMask & CLASSMASK_WIZARD) == 0) {
                return FALSE;
            }
            break;
        }
    }

    if (type.m_nClassMask != 0 && (type.m_nClassMask & m_nClassMask) == 0) {
        return FALSE;
    }

    if (type.m_nSpecific != 0 && m_nSpecific != type.m_nSpecific) {
        return FALSE;
    }

    if (type.m_nGender != 0 && m_nGender != type.m_nGender) {
        return FALSE;
    }

    if (type.m_nAlignment != 0 && m_nAlignment != type.m_nAlignment) {
        // TODO: Add constants.
        switch (type.m_nAlignment) {
        case 1:
            if ((m_nAlignment & 0xF) != 1) {
                return FALSE;
            }
            break;
        case 2:
            if ((m_nAlignment & 0xF) != 2) {
                return FALSE;
            }
            break;
        case 3:
            if ((m_nAlignment & 0xF) != 3) {
                return FALSE;
            }
            break;
        case 16:
            if ((m_nAlignment & 0xF0) != 16) {
                return FALSE;
            }
            break;
        case 32:
            if ((m_nAlignment & 0xF0) != 32) {
                return FALSE;
            }
            break;
        case 48:
            if ((m_nAlignment & 0xF0) != 48) {
                return FALSE;
            }
            break;
        }
    }

    if (type.m_nInstance != -1
        && m_nInstance != type.m_nInstance
        && m_sName != type.m_sName) {
        return FALSE;
    }

    // NOTE: Original code is slightly different.
    CString sThisName(m_sName);
    CString sOtherName(type.m_sName);
    CString sTemp;
    int pos;

    sTemp = "";
    for (pos = 0; pos < sOtherName.GetLength(); pos++) {
        if (sOtherName[pos] != ' ') {
            sTemp += sOtherName[pos];
        }
    }
    sOtherName = sTemp;

    sTemp = "";
    for (pos = 0; pos < sThisName.GetLength(); pos++) {
        if (sThisName[pos] != ' ') {
            sTemp += sThisName[pos];
        }
    }
    sThisName = sTemp;

    if (type.m_sName != "" && sThisName != sOtherName) {
        return FALSE;
    }

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
    CString v1;
    LONG nEnemyAlly;
    LONG nGeneral;
    LONG nRace;
    LONG nClass;
    LONG nSpecific;
    LONG nGender;
    LONG nAlignment;
    LONG nSubRace;
    LONG nSpecialCase[5];

    int x = -1;
    int y = -1;
    int width = -1;
    int height = -1;

    sscanf(sData,
        "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld [%d.%d.%d.%d]",
        &nEnemyAlly,
        &nGeneral,
        &nRace,
        &nClass,
        &nSpecific,
        &nGender,
        &nAlignment,
        &nSubRace,
        &(nSpecialCase[0]),
        &(nSpecialCase[1]),
        &(nSpecialCase[2]),
        &(nSpecialCase[3]),
        &(nSpecialCase[4]),
        &x,
        &y,
        &width,
        &height);

    m_nRace = static_cast<BYTE>(nRace);
    m_nEnemyAlly = static_cast<BYTE>(nEnemyAlly);
    m_nGender = static_cast<BYTE>(nGender);
    m_nGeneral = static_cast<BYTE>(nGeneral);
    m_nClass = static_cast<BYTE>(nClass);
    m_nSpecific = static_cast<BYTE>(nSpecific);
    m_nAlignment = static_cast<BYTE>(nAlignment);

    m_nSubRace = static_cast<BYTE>(nSubRace);
    if (m_nSubRace == -1) {
        m_nSubRace = 0;
    }

    m_SpecialCase[0] = static_cast<BYTE>(nSpecialCase[0]);
    m_SpecialCase[1] = static_cast<BYTE>(nSpecialCase[1]);
    m_SpecialCase[2] = static_cast<BYTE>(nSpecialCase[2]);
    m_SpecialCase[3] = static_cast<BYTE>(nSpecialCase[3]);
    m_SpecialCase[4] = static_cast<BYTE>(nSpecialCase[4]);

    if (height > 0) {
        CRect r;
        r.left = x;
        r.top = 4 * y / 3;
        r.right = width;
        r.bottom = 4 * height / 3;
        r.NormalizeRect();

        m_rect = r;
        m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_RECT;
    } else if (x > 0 && y > 0) {
        m_ptCenter.x = x;
        m_ptCenter.y = 4 * y / 3;
        m_nRadius = width;
        m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_POINT;
    } else {
        m_nLocationType = CAIOBJECTTYPE_LOCATION_TYPE_NONE;
    }

    CString sName = CAIUtil::ReadBetween(sData, CString('"'));
    if (sName.GetLength() > 0) {
        m_sName = sName;
    }

    int nAvClass;
    int nClassMask;
    sscanf(sData,
        "%d %d",
        &nAvClass,
        &nClassMask);

    m_nClassMask = nClassMask;
    m_nAvClass = static_cast<BYTE>(nAvClass);
    m_nInstance = -1;
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

// 0x7ACD60
void CAIObjectType::SetRadius(int radius)
{
    m_nRadius = radius;
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

// 0x45B680
BYTE CAIObjectType::GetEnemyAlly() const
{
    return m_nEnemyAlly;
}

// 0x45B390
BYTE CAIObjectType::GetGeneral() const
{
    return m_nGeneral;
}

// 0x45B3A0
BYTE CAIObjectType::GetRace() const
{
    return m_nRace;
}

// 0x45B3B0
BYTE CAIObjectType::GetClass() const
{
    return m_nClass;
}

// 0x45B3C0
BYTE CAIObjectType::GetSpecific() const
{
    return m_nSpecific;
}

// 0x45B3D0
BYTE CAIObjectType::GetGender() const
{
    return m_nGender;
}

// 0x45B3E0
BYTE CAIObjectType::GetAlignment() const
{
    return m_nAlignment;
}

// 0x45B3F0
void CAIObjectType::SetEnemyAlly(BYTE nEnemyAlly)
{
    m_nEnemyAlly = nEnemyAlly;
}

// 0x45B400
void CAIObjectType::SetGeneral(BYTE nGeneral)
{
    m_nGeneral = nGeneral;
}

// 0x45B410
void CAIObjectType::SetRace(BYTE nRace)
{
    m_nRace = nRace;
}

// 0x45B420
void CAIObjectType::SetSpecific(BYTE nSpecific)
{
    m_nSpecific = nSpecific;
}

// 0x45B430
void CAIObjectType::SetGender(BYTE nGender)
{
    m_nGender = nGender;
}

// 0x45B440
void CAIObjectType::SetAlignment(BYTE nAlignment)
{
    m_nAlignment = nAlignment;
}

// 0x45B450
void CAIObjectType::SetName(const CString& sName)
{
    m_sName = sName;
}

// 0x45B460
int CAIObjectType::GetInstance() const
{
    return m_nInstance;
}

// 0x45B470
void CAIObjectType::SetInstance(int nInstance)
{
    m_nInstance = nInstance;
}

// 0x45B480
void CAIObjectType::SetClass(BYTE nClass)
{
    m_nClass = nClass;
}

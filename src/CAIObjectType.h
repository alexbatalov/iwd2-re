#ifndef CAIOBJECTTYPE_H_
#define CAIOBJECTTYPE_H_

#include "mfc.h"

#define CLASSMASK_BARBARIAN 0x00000001
#define CLASSMASK_BARD 0x00000002
#define CLASSMASK_CLERIC 0x00000004
#define CLASSMASK_DRUID 0x00000008
#define CLASSMASK_FIGHTER 0x00000010
#define CLASSMASK_MONK 0x00000020
#define CLASSMASK_PALADIN 0x00000040
#define CLASSMASK_RANGER 0x00000080
#define CLASSMASK_ROGUE 0x00000100
#define CLASSMASK_SORCERER 0x00000200
#define CLASSMASK_WIZARD 0x00000400

#define SPECMASK_CLERIC_ILMATER 0x8000
#define SPECMASK_CLERIC_LATHANDER 0x10000
#define SPECMASK_CLERIC_SELUNE 0x20000
#define SPECMASK_CLERIC_HELM 0x40000
#define SPECMASK_CLERIC_OGHMA 0x80000
#define SPECMASK_CLERIC_TEMPUS 0x100000
#define SPECMASK_CLERIC_BANE 0x200000
#define SPECMASK_CLERIC_MASK 0x400000
#define SPECMASK_CLERIC_TALOS 0x800000

#define SPECMASK_MONK_OLD_ORDER 0x8
#define SPECMASK_MONK_BROKEN_ONES 0x10
#define SPECMASK_MONK_DARK_MOON 0x20

#define SPECMASK_PALADIN_ILMATER 0x1
#define SPECMASK_PALADIN_HELM 0x2
#define SPECMASK_PALADIN_MYSTRA 0x4

#define SPECMASK_WIZARD_ABJURER 0x40
#define SPECMASK_WIZARD_CONJURER 0x80
#define SPECMASK_WIZARD_DIVINER 0x100
#define SPECMASK_WIZARD_ENCHANTER 0x200
#define SPECMASK_WIZARD_ILLUSIONIST 0x400
#define SPECMASK_WIZARD_EVOKER 0x800
#define SPECMASK_WIZARD_NECROMANCER 0x1000
#define SPECMASK_WIZARD_TRANSMUTER 0x2000
#define SPECMASK_WIZARD_UNIVERSAL 0x4000

#define SPECMASK_CLERIC             \
    (SPECMASK_CLERIC_ILMATER        \
        | SPECMASK_CLERIC_LATHANDER \
        | SPECMASK_CLERIC_SELUNE    \
        | SPECMASK_CLERIC_HELM      \
        | SPECMASK_CLERIC_OGHMA     \
        | SPECMASK_CLERIC_TEMPUS    \
        | SPECMASK_CLERIC_BANE      \
        | SPECMASK_CLERIC_MASK      \
        | SPECMASK_CLERIC_TALOS)

#define SPECMASK_MONK               \
    (SPECMASK_MONK_OLD_ORDER        \
        | SPECMASK_MONK_BROKEN_ONES \
        | SPECMASK_MONK_DARK_MOON)

#define SPECMASK_PALADIN        \
    (SPECMASK_PALADIN_ILMATER   \
        | SPECMASK_PALADIN_HELM \
        | SPECMASK_PALADIN_MYSTRA)

#define SPECMASK_WIZARD               \
    (SPECMASK_WIZARD_ABJURER          \
        | SPECMASK_WIZARD_CONJURER    \
        | SPECMASK_WIZARD_DIVINER     \
        | SPECMASK_WIZARD_ENCHANTER   \
        | SPECMASK_WIZARD_ILLUSIONIST \
        | SPECMASK_WIZARD_EVOKER      \
        | SPECMASK_WIZARD_NECROMANCER \
        | SPECMASK_WIZARD_TRANSMUTER  \
        | SPECMASK_WIZARD_UNIVERSAL)

#define CAIOBJECTTYPE_LOCATION_TYPE_NONE 0
#define CAIOBJECTTYPE_LOCATION_TYPE_POINT 1
#define CAIOBJECTTYPE_LOCATION_TYPE_RECT 2

#define CAIOBJECTTYPE_EA_ALL 0
#define CAIOBJECTTYPE_EA_PC 2
#define CAIOBJECTTYPE_EA_FAMILIAR 3
#define CAIOBJECTTYPE_EA_ALLY 4
#define CAIOBJECTTYPE_EA_CONTROLLED 5
#define CAIOBJECTTYPE_EA_CHARMED 6
#define CAIOBJECTTYPE_EA_0X847C3A 7
#define CAIOBJECTTYPE_EA_GOODCUTOFF 30
#define CAIOBJECTTYPE_EA_CONTROLCUTOFF 15
#define CAIOBJECTTYPE_EA_NOTGOOD 31
#define CAIOBJECTTYPE_EA_NEUTRAL 128
#define CAIOBJECTTYPE_EA_NOTEVIL 199
#define CAIOBJECTTYPE_EA_ENEMY 255
#define CAIOBJECTTYPE_EA_CHARMED_PC 254
#define CAIOBJECTTYPE_EA_EVILCUTOFF 200
#define CAIOBJECTTYPE_EA_ARENAPC 253
#define CAIOBJECTTYPE_EA_INANIMATE 127
#define CAIOBJECTTYPE_EA_ANYTHING 126

#define CAIOBJECTTYPE_G_HUMANOID 1
#define CAIOBJECTTYPE_G_ANIMAL 2
#define CAIOBJECTTYPE_G_DEAD 3
#define CAIOBJECTTYPE_G_UNDEAD 4
#define CAIOBJECTTYPE_G_GIANTHUMANOID 5
#define CAIOBJECTTYPE_G_FROZEN 6
#define CAIOBJECTTYPE_G_MONSTER 255
#define CAIOBJECTTYPE_G_WEAPON 101
#define CAIOBJECTTYPE_G_ARMOR 102
#define CAIOBJECTTYPE_G_AMULET 103
#define CAIOBJECTTYPE_G_BELT 104
#define CAIOBJECTTYPE_G_BOOTS 105
#define CAIOBJECTTYPE_G_AMMO 106
#define CAIOBJECTTYPE_G_GENERAL_ITEM 0
#define CAIOBJECTTYPE_G_HELMET 107
#define CAIOBJECTTYPE_G_KEY 108
#define CAIOBJECTTYPE_G_POTION 109
#define CAIOBJECTTYPE_G_RING 110
#define CAIOBJECTTYPE_G_SCROLL 111
#define CAIOBJECTTYPE_G_SHIELD 112
#define CAIOBJECTTYPE_G_GLOVES 113

#define CAIOBJECTTYPE_R_HUMAN 1
#define CAIOBJECTTYPE_R_ELF 2
#define CAIOBJECTTYPE_R_HALF_ELF 3
#define CAIOBJECTTYPE_R_DWARF 4
#define CAIOBJECTTYPE_R_HALFLING 5
#define CAIOBJECTTYPE_R_GNOME 6
#define CAIOBJECTTYPE_R_HALF_ORC 7
#define CAIOBJECTTYPE_R_ANKHEG 101
#define CAIOBJECTTYPE_R_BASILISK 102
#define CAIOBJECTTYPE_R_BEAR 103
#define CAIOBJECTTYPE_R_CARRIONCRAWLER 104
#define CAIOBJECTTYPE_R_DOG 105
#define CAIOBJECTTYPE_R_DOPPLEGANGER 106
#define CAIOBJECTTYPE_R_ETTERCAP 107
#define CAIOBJECTTYPE_R_GHOUL 108
#define CAIOBJECTTYPE_R_GIBBERLING 109
#define CAIOBJECTTYPE_R_GNOLL 110
#define CAIOBJECTTYPE_R_HOBGOBLIN 111
#define CAIOBJECTTYPE_R_KOBOLD 112
#define CAIOBJECTTYPE_R_OGRE 113
#define CAIOBJECTTYPE_R_SKELETON 115
#define CAIOBJECTTYPE_R_SPIDER 116
#define CAIOBJECTTYPE_R_WOLF 117
#define CAIOBJECTTYPE_R_WYVERN 118
#define CAIOBJECTTYPE_R_SLIME 119
#define CAIOBJECTTYPE_R_FAIRY 120
#define CAIOBJECTTYPE_R_BEETLE 150
#define CAIOBJECTTYPE_R_CARRION_CRAWLER 151
#define CAIOBJECTTYPE_R_ELEMENTAL 152
#define CAIOBJECTTYPE_R_GIANT 153
#define CAIOBJECTTYPE_R_DRAKE 154
#define CAIOBJECTTYPE_R_GOBLIN 155
#define CAIOBJECTTYPE_R_GOLEM 156
#define CAIOBJECTTYPE_R_LIZARDMAN 157
#define CAIOBJECTTYPE_R_MANTICORE 158
#define CAIOBJECTTYPE_R_MYCONID 159
#define CAIOBJECTTYPE_R_ORC 160
#define CAIOBJECTTYPE_R_SALAMANDER 161
#define CAIOBJECTTYPE_R_SHRIEKER 162
#define CAIOBJECTTYPE_R_SVIRFNEBLIN 163
#define CAIOBJECTTYPE_R_TANARI 164
#define CAIOBJECTTYPE_R_TROLL 165
#define CAIOBJECTTYPE_R_UMBERHULK 166
#define CAIOBJECTTYPE_R_UNDEAD 167
#define CAIOBJECTTYPE_R_YUANTI 168
#define CAIOBJECTTYPE_R_HARPY 174
#define CAIOBJECTTYPE_R_DJINNI 175
#define CAIOBJECTTYPE_R_SHAMBLING_MOUND 176
#define CAIOBJECTTYPE_R_BEHOLDER 177
#define CAIOBJECTTYPE_R_RAKSHASA 178
#define CAIOBJECTTYPE_R_BUGBEAR 180
#define CAIOBJECTTYPE_R_DRIDER 182
#define CAIOBJECTTYPE_R_HOOK_HORROR 181
#define CAIOBJECTTYPE_R_SHAPESHIFTER 191
#define CAIOBJECTTYPE_R_WILLOWISP 192
#define CAIOBJECTTYPE_R_OTYUGH 193
#define CAIOBJECTTYPE_R_NO_RACE 255
#define CAIOBJECTTYPE_R_DEMONIC 121
#define CAIOBJECTTYPE_R_LYCANTHROPE 122
#define CAIOBJECTTYPE_R_SWORD 201
#define CAIOBJECTTYPE_R_BOW 202
#define CAIOBJECTTYPE_R_XBOW 203
#define CAIOBJECTTYPE_R_STAFF 204
#define CAIOBJECTTYPE_R_SLING 205
#define CAIOBJECTTYPE_R_MACE 206
#define CAIOBJECTTYPE_R_DAGGER 207
#define CAIOBJECTTYPE_R_SPEAR 208
#define CAIOBJECTTYPE_R_FIST 209
#define CAIOBJECTTYPE_R_HAMMER 210
#define CAIOBJECTTYPE_R_MORNINGSTAR 211
#define CAIOBJECTTYPE_R_ROBES 212
#define CAIOBJECTTYPE_R_LEATHER 213
#define CAIOBJECTTYPE_R_CHAIN 214
#define CAIOBJECTTYPE_R_PLATE 215

#define CAIOBJECTTYPE_R_184 184

#define CAIOBJECTTYPE_SUBRACE_PURERACE 0
#define CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR 1
#define CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING 2
#define CAIOBJECTTYPE_SUBRACE_ELF_DROW 1
#define CAIOBJECTTYPE_SUBRACE_ELF_WILD 2
#define CAIOBJECTTYPE_SUBRACE_DWARF_GOLD 1
#define CAIOBJECTTYPE_SUBRACE_DWARF_GRAY 2
#define CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART 1
#define CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE 2
#define CAIOBJECTTYPE_SUBRACE_GNOME_DEEP 1

#define CAIOBJECTTYPE_C_BARBARIAN 1
#define CAIOBJECTTYPE_C_BARD 2
#define CAIOBJECTTYPE_C_CLERIC 3
#define CAIOBJECTTYPE_C_DRUID 4
#define CAIOBJECTTYPE_C_FIGHTER 5
#define CAIOBJECTTYPE_C_MONK 6
#define CAIOBJECTTYPE_C_PALADIN 7
#define CAIOBJECTTYPE_C_RANGER 8
#define CAIOBJECTTYPE_C_ROGUE 9
#define CAIOBJECTTYPE_C_SORCERER 10
#define CAIOBJECTTYPE_C_WIZARD 11

#define CAIOBJECTTYPE_SEX_MALE 1
#define CAIOBJECTTYPE_SEX_FEMALE 2

#define CAIOBJECTTYPE_LAWFUL_GOOD 0x11
#define CAIOBJECTTYPE_LAWFUL_NEUTRAL 0x12
#define CAIOBJECTTYPE_LAWFUL_EVIL 0x13
#define CAIOBJECTTYPE_NEUTRAL_GOOD 0x21
#define CAIOBJECTTYPE_NEUTRAL 0x22
#define CAIOBJECTTYPE_NEUTRAL_EVIL 0x23
#define CAIOBJECTTYPE_CHAOTIC_GOOD 0x31
#define CAIOBJECTTYPE_CHAOTIC_NEUTRAL 0x32
#define CAIOBJECTTYPE_CHAOTIC_EVIL 0x33

// Seen in `CDerivedStats::GetClassLevel` assertion. Not sure if it belongs
// here.
#define CAIOBJECT_CLASS_MAX 11

class CGameAIBase;
class CGameObject;

class CAIObjectType {
public:
    static const BYTE EA_ALL;
    static const BYTE EA_PC;
    static const BYTE EA_FAMILIAR;
    static const BYTE EA_ALLY;
    static const BYTE EA_CONTROLLED;
    static const BYTE EA_CHARMED;
    static const BYTE EA_0x847C3A;
    static const BYTE EA_GOODCUTOFF;
    static const BYTE EA_CONTROLCUTOFF;
    static const BYTE EA_NOTGOOD;
    static const BYTE EA_NEUTRAL;
    static const BYTE EA_NOTEVIL;
    static const BYTE EA_ENEMY;
    static const BYTE EA_CHARMED_PC;
    static const BYTE EA_EVILCUTOFF;
    static const BYTE EA_ARENAPC;
    static const BYTE EA_INANIMATE;
    static const BYTE EA_ANYTHING;

    static const BYTE G_HUMANOID;
    static const BYTE G_ANIMAL;
    static const BYTE G_DEAD;
    static const BYTE G_UNDEAD;
    static const BYTE G_GIANTHUMANOID;
    static const BYTE G_FROZEN;
    static const BYTE G_MONSTER;
    static const BYTE G_WEAPON;
    static const BYTE G_ARMOR;
    static const BYTE G_AMULET;
    static const BYTE G_BELT;
    static const BYTE G_BOOTS;
    static const BYTE G_AMMO;
    static const BYTE G_GENERAL_ITEM;
    static const BYTE G_HELMET;
    static const BYTE G_KEY;
    static const BYTE G_POTION;
    static const BYTE G_RING;
    static const BYTE G_SCROLL;
    static const BYTE G_SHIELD;
    static const BYTE G_GLOVES;

    static const BYTE R_HUMAN;
    static const BYTE R_ELF;
    static const BYTE R_HALF_ELF;
    static const BYTE R_DWARF;
    static const BYTE R_HALFLING;
    static const BYTE R_GNOME;
    static const BYTE R_HALF_ORC;
    static const BYTE R_ANKHEG;
    static const BYTE R_BASILISK;
    static const BYTE R_BEAR;
    static const BYTE R_CARRIONCRAWLER;
    static const BYTE R_DOG;
    static const BYTE R_DOPPLEGANGER;
    static const BYTE R_ETTERCAP;
    static const BYTE R_GHOUL;
    static const BYTE R_GIBBERLING;
    static const BYTE R_GNOLL;
    static const BYTE R_HOBGOBLIN;
    static const BYTE R_KOBOLD;
    static const BYTE R_OGRE;
    static const BYTE R_SKELETON;
    static const BYTE R_SPIDER;
    static const BYTE R_WOLF;
    static const BYTE R_WYVERN;
    static const BYTE R_SLIME;
    static const BYTE R_FAIRY;
    static const BYTE R_BEETLE;
    static const BYTE R_CARRION_CRAWLER;
    static const BYTE R_ELEMENTAL;
    static const BYTE R_GIANT;
    static const BYTE R_DRAKE;
    static const BYTE R_GOBLIN;
    static const BYTE R_GOLEM;
    static const BYTE R_LIZARDMAN;
    static const BYTE R_MANTICORE;
    static const BYTE R_MYCONID;
    static const BYTE R_ORC;
    static const BYTE R_SALAMANDER;
    static const BYTE R_SHRIEKER;
    static const BYTE R_SVIRFNEBLIN;
    static const BYTE R_TANARI;
    static const BYTE R_TROLL;
    static const BYTE R_UMBERHULK;
    static const BYTE R_UNDEAD;
    static const BYTE R_YUANTI;
    static const BYTE R_HARPY;
    static const BYTE R_DJINNI;
    static const BYTE R_SHAMBLING_MOUND;
    static const BYTE R_BEHOLDER;
    static const BYTE R_RAKSHASA;
    static const BYTE R_BUGBEAR;
    static const BYTE R_DRIDER;
    static const BYTE R_HOOK_HORROR;
    static const BYTE R_SHAPESHIFTER;
    static const BYTE R_WILLOWISP;
    static const BYTE R_OTYUGH;
    static const BYTE R_NO_RACE;
    static const BYTE R_DEMONIC;
    static const BYTE R_LYCANTHROPE;
    static const BYTE R_SWORD;
    static const BYTE R_BOW;
    static const BYTE R_XBOW;
    static const BYTE R_STAFF;
    static const BYTE R_SLING;
    static const BYTE R_MACE;
    static const BYTE R_DAGGER;
    static const BYTE R_SPEAR;
    static const BYTE R_FIST;
    static const BYTE R_HAMMER;
    static const BYTE R_MORNINGSTAR;
    static const BYTE R_ROBES;
    static const BYTE R_LEATHER;
    static const BYTE R_CHAIN;
    static const BYTE R_PLATE;

    static const BYTE C_BARBARIAN;
    static const BYTE C_BARD;
    static const BYTE C_CLERIC;
    static const BYTE C_DRUID;
    static const BYTE C_FIGHTER;
    static const BYTE C_MONK;
    static const BYTE C_PALADIN;
    static const BYTE C_RANGER;
    static const BYTE C_ROGUE;
    static const BYTE C_SORCERER;
    static const BYTE C_WIZARD;

    static const BYTE SEX_MALE;
    static const BYTE SEX_FEMALE;

    static const BYTE LAWFUL_GOOD;
    static const BYTE LAWFUL_NEUTRAL;
    static const BYTE LAWFUL_EVIL;
    static const BYTE NEUTRAL_GOOD;
    static const BYTE NEUTRAL;
    static const BYTE NEUTRAL_EVIL;
    static const BYTE CHAOTIC_GOOD;
    static const BYTE CHAOTIC_NEUTRAL;
    static const BYTE CHAOTIC_EVIL;

    static const int INSTANCE_NOT_SPRITE;
    static const BYTE SPECIALCASE_MYSELF[5];
    static const CAIObjectType ANYONE;
    static const CAIObjectType ANYTHING;
    static const CAIObjectType NOONE;
    static const CAIObjectType NOT_SPRITE;
    static const CAIObjectType OBJECT_MYSELF;

    CAIObjectType(const CAIObjectType& type);
    CAIObjectType(BYTE nEnemyAlly, BYTE nGeneral, BYTE nRace, BYTE nSubRace, BYTE nClass, BYTE nSpecific, BYTE nGender, BYTE nAlignment, int nInstance, const BYTE* SpecialCase, const CString& sName, BYTE nAvClass, int nClassMask);
    CAIObjectType(BYTE nEnemyAlly = 0, BYTE nGeneral = 0, BYTE nRace = 0, BYTE nSubRace = 0, BYTE nClass = 0, BYTE nSpecific = 0, BYTE nGender = 0, BYTE nAlignment = 0, int nInstance = -1, BYTE nAvClass = 0, int nClassMask = 0);
    ~CAIObjectType();
    BOOL OfType(const CAIObjectType& type, BOOL bCheckForNonSprites, BOOL bNoNonSprites) const;
    void Set(const CAIObjectType& type);
    void Decode(CGameAIBase* caller);
    CString GetName() const;
    CGameObject* sub_40CB20(CGameAIBase* caller, BYTE type, BOOL checkBackList) const;
    BOOL Equal(const CAIObjectType& type) const;
    CGameObject* sub_40CCA0(CGameAIBase* caller, BOOL checkBackList) const;
    BOOL sub_40CD80(CGameAIBase* caller, CPoint& pt, INT& nRadius) const;
    LONG sub_40CED0(CGameAIBase* caller, BOOL checkBackList) const;
    CGameObject* sub_40D050(CGameAIBase* caller, BYTE type, BOOL checkBackList) const;
    CGameObject* sub_40D0F0(CGameAIBase* caller, BOOL checkBackList) const;
    void SetSpecialCase(const BYTE* SpecialCase);
    void Read(CString sData);
    BOOL IsEnemyOf(const CAIObjectType& type) const;
    CAIObjectType GetEnemyOf() const;
    BOOL IsClassValid(BYTE nClass) const;
    void AddClass(BYTE nClass);
    BOOL sub_40D8A0(const CPoint& pt) const;
    BOOL sub_40D900(const CPoint& pt) const;
    BOOL sub_40D920(const CPoint& pt) const;
    void SetCenter(const CPoint& pt);
    void SetRadius(int radius);
    void SetRect(const CRect& rect);
    BYTE GetEnemyAlly() const;
    BYTE GetGeneral() const;
    BYTE GetRace() const;
    BYTE GetClass() const;
    BYTE GetSpecific() const;
    BYTE GetGender() const;
    BYTE GetAlignment() const;
    void SetEnemyAlly(BYTE nEnemyAlly);
    void SetGeneral(BYTE nGeneral);
    void SetRace(BYTE nRace);
    void SetSpecific(BYTE nSpecific);
    void SetGender(BYTE nGender);
    void SetAlignment(BYTE nAlignment);
    void SetName(const CString& sName);
    int GetInstance() const;
    void SetInstance(int nInstance);
    void SetClass(BYTE nClass);

    /* 0000 */ CString m_sName;
    /* 0004 */ BYTE m_nEnemyAlly;
    /* 0005 */ BYTE m_nGeneral;
    /* 0006 */ BYTE m_nRace;
    /* 0007 */ BYTE m_nSubRace;
    /* 0008 */ BYTE m_nClass;
    /* 000A */ int m_nInstance;
    /* 000E */ BYTE m_SpecialCase[5];
    /* 0013 */ BYTE m_nSpecific;
    /* 0014 */ BYTE m_nGender;
    /* 0015 */ BYTE m_nAlignment;
    /* 0016 */ BYTE m_nAvClass;
    /* 0018 */ int m_nClassMask;
    /* 001C */ int m_nLocationType;
    /* 0020 */ CPoint m_ptCenter;
    /* 0028 */ int m_nRadius;
    /* 002C */ CRect m_rect;
};

#endif /* CAIOBJECTTYPE_H_ */

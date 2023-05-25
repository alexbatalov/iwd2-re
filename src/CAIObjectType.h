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

#define CAIOBJECTTYPE_R_HUMAN 1
#define CAIOBJECTTYPE_R_ELF 2
#define CAIOBJECTTYPE_R_HALF_ELF 3
#define CAIOBJECTTYPE_R_DWARF 4
#define CAIOBJECTTYPE_R_HALFLING 5
#define CAIOBJECTTYPE_R_GNOME 6
#define CAIOBJECTTYPE_R_HALF_ORC 7

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

    static const BYTE R_HUMAN;
    static const BYTE R_ELF;
    static const BYTE R_HALF_ELF;
    static const BYTE R_DWARF;
    static const BYTE R_HALFLING;
    static const BYTE R_GNOME;
    static const BYTE R_HALF_ORC;

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
    CString GetName() const;
    BOOL Equal(const CAIObjectType& type) const;
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
    void SetRect(const CRect& rect);

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
    /* 0008 */ int m_nClassMask;
    /* 001C */ int m_nLocationType;
    /* 0020 */ CPoint m_ptCenter;
    /* 0028 */ int m_nRadius;
    /* 002C */ CRect m_rect;
};

#endif /* CAIOBJECTTYPE_H_ */

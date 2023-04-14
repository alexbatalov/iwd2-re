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

class CAIObjectType {
public:
    /* 0x847C34 */ static const BYTE EA_ALL = 0;
    /* 0x847C35 */ static const BYTE EA_PC = 2;
    /* 0x847C36 */ static const BYTE EA_FAMILIAR = 3;
    /* 0x847C37 */ static const BYTE EA_ALLY = 4;
    /* 0x847C38 */ static const BYTE EA_CONTROLLED = 5;
    /* 0x847C39 */ static const BYTE EA_CHARMED = 6;
    /* 0x847C3A */ static const BYTE EA_0x847C3A = 7;
    /* 0x847C3B */ static const BYTE EA_GOODCUTOFF = 30;
    /* 0x847C3C */ static const BYTE EA_CONTROLCUTOFF = 15;
    /* 0x847C3D */ static const BYTE EA_NOTGOOD = 31;
    /* 0x847C3E */ static const BYTE EA_NEUTRAL = 128;
    /* 0x847C3F */ static const BYTE EA_NOTEVIL = 199;
    /* 0x847C40 */ static const BYTE EA_ENEMY = 255;
    /* 0x847C41 */ static const BYTE EA_CHARMED_PC = 254;
    /* 0x847C42 */ static const BYTE EA_EVILCUTOFF = 200;
    /* 0x847C43 */ static const BYTE EA_ARENAPC = 253;
    /* 0x847C44 */ static const BYTE EA_INANIMATE = 127;
    /* 0x847C45 */ static const BYTE EA_ANYTHING = 126;

    /* 0x847C5B */ static const BYTE R_HUMAN = 1;
    /* 0x847C5C */ static const BYTE R_ELF = 2;
    /* 0x847C5D */ static const BYTE R_HALF_ELF = 3;
    /* 0x847C5E */ static const BYTE R_DWARF = 4;
    /* 0x847C5F */ static const BYTE R_HALFLING = 5;
    /* 0x847C60 */ static const BYTE R_GNOME = 6;
    /* 0x847C61 */ static const BYTE R_HALF_ORC = 7;

    /* 0x847CA5 */ static const BYTE C_BARBARIAN = 1;
    /* 0x847CA6 */ static const BYTE C_BARD = 2;
    /* 0x847CA7 */ static const BYTE C_CLERIC = 3;
    /* 0x847CA8 */ static const BYTE C_DRUID = 4;
    /* 0x847CA9 */ static const BYTE C_FIGHTER = 5;
    /* 0x847CAA */ static const BYTE C_MONK = 6;
    /* 0x847CAB */ static const BYTE C_PALADIN = 7;
    /* 0x847CAC */ static const BYTE C_RANGER = 8;
    /* 0x847CAD */ static const BYTE C_ROGUE = 9;
    /* 0x847CAE */ static const BYTE C_SORCERER = 10;
    /* 0x847CAF */ static const BYTE C_WIZARD = 11;

    /* 0x847CF2 */ static const BYTE SEX_MALE = 1;
    /* 0x847CF3 */ static const BYTE SEX_FEMALE = 2;

    /* 0x847CF8 */ static const BYTE LAWFUL_GOOD = 0x11;
    /* 0x847CF9 */ static const BYTE LAWFUL_NEUTRAL = 0x12;
    /* 0x847CFA */ static const BYTE LAWFUL_EVIL = 0x13;
    /* 0x847CFB */ static const BYTE NEUTRAL_GOOD = 0x21;
    /* 0x847CFC */ static const BYTE NEUTRAL = 0x22;
    /* 0x847CFD */ static const BYTE NEUTRAL_EVIL = 0x23;
    /* 0x847CFE */ static const BYTE CHAOTIC_GOOD = 0x31;
    /* 0x847CFF */ static const BYTE CHAOTIC_NEUTRAL = 0x32;
    /* 0x847D00 */ static const BYTE CHAOTIC_EVIL = 0x33;

    static const int INSTANCE_NOT_SPRITE;
    static const BYTE SPECIALCASE_MYSELF[5];
    static const CAIObjectType ANYONE;
    static const CAIObjectType ANYTHING;
    static const CAIObjectType NOONE;
    static const CAIObjectType NOT_SPRITE;
    static const CAIObjectType OBJECT_MYSELF;

    CAIObjectType(const CAIObjectType& type);
    CAIObjectType(BYTE nEnemyAlly, BYTE nGeneral, BYTE nRace, BYTE nSubRace, BYTE nClass, BYTE nSpecific, BYTE nGender, BYTE nAlignment, int nInstance, const BYTE* SpecialCase, const CString& sName, BYTE nAvClass, int nClassMask);
    CAIObjectType(BYTE nEnemyAlly, BYTE nGeneral, BYTE nRace, BYTE nSubRace, BYTE nClass, BYTE nSpecific, BYTE nGender, BYTE nAlignment, int nInstance, BYTE nAvClass, int nClassMask);
    ~CAIObjectType();
    void Set(const CAIObjectType& type);
    CString GetName() const;
    BOOL Equal(const CAIObjectType& type) const;
    void SetSpecialCase(const BYTE* SpecialCase);
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

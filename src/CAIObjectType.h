#ifndef CAIOBJECTTYPE_H_
#define CAIOBJECTTYPE_H_

#include "mfc.h"

class CAIObjectType {
public:
    /* 0x847C5B */ static const BYTE CAIObjectType::R_HUMAN = 1;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_ELF = 2;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_HALF_ELF = 3;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_DWARF = 4;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_HALFLING = 5;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_GNOME = 6;
    /* 0x847C5B */ static const BYTE CAIObjectType::R_HALF_ORC = 7;

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
};

#endif /* CAIOBJECTTYPE_H_ */

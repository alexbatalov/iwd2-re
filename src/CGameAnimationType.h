#ifndef CGAMEANIMATIONTYPE_H_
#define CGAMEANIMATIONTYPE_H_

#include "mfc.h"

#include "CVidBitmap.h"

#define ANIM_DEATH_KNIGHT 0x2300
#define ANIM_STATIC_NOBLE_MAN_CHAIR 0x4000
#define ANIM_STATIC_NOBLE_MAN_MATTE 0x4002
#define ANIM_STATIC_NOBLE_WOMAN_CHAIR 0x4010
#define ANIM_STATIC_NOBLE_WOMAN_MATTE 0x4012
#define ANIM_STATIC_PEASANT_MAN_CHAIR 0x4100
#define ANIM_STATIC_PEASANT_MAN_STOOL 0x4101
#define ANIM_STATIC_PEASANT_MAN_MATTE 0x4102
#define ANIM_STATIC_PEASANT_WOMAN_CHAIR 0x4110
#define ANIM_STATIC_PEASANT_WOMAN_MATTE 0x4112
#define ANIM_STATIC_HUMANCLERIC_MAN_CHAIR 0x4200
#define ANIM_SLEEPING_MAN_HUMAN 0x4400
#define ANIM_SLEEPING_WOMAN_HUMAN 0x4410
#define ANIM_SLEEPING_FAT_MAN_HUMAN 0x4500
#define ANIM_SLEEPING_DWARF 0x4600
#define ANIM_SLEEPING_MAN_ELF 0x4700
#define ANIM_SLEEPING_WOMAN_ELF 0x4710
#define ANIM_SLEEPING_MAN_HALFLING 0x4800
#define ANIM_CLERIC_MALE_HUMAN 0x6000
#define ANIM_CLERIC_MALE_ELF 0x6001
#define ANIM_CLERIC_MALE_DWARF 0x6002
#define ANIM_CLERIC_MALE_HALFLING 0x6003
#define ANIM_CLERIC_MALE_GNOME 0x6004
#define ANIM_CLERIC_MALE_HALFORC 0x6005
#define ANIM_CLERIC_FEMALE_HUMAN 0x6010
#define ANIM_CLERIC_FEMALE_ELF 0x6011
#define ANIM_CLERIC_FEMALE_DWARF 0x6012
#define ANIM_CLERIC_FEMALE_HALFLING 0x6013
#define ANIM_CLERIC_FEMALE_GNOME 0x6014
#define ANIM_CLERIC_FEMALE_HALFORC 0x6015
#define ANIM_FIGHTER_MALE_HUMAN 0x6100
#define ANIM_FIGHTER_MALE_ELF 0x6101
#define ANIM_FIGHTER_MALE_DWARF 0x6102
#define ANIM_FIGHTER_MALE_HALFLING 0x6103
#define ANIM_FIGHTER_MALE_GNOME 0x6104
#define ANIM_FIGHTER_MALE_HALFORC 0x6105
#define ANIM_FIGHTER_FEMALE_HUMAN 0x6110
#define ANIM_FIGHTER_FEMALE_ELF 0x6111
#define ANIM_FIGHTER_FEMALE_DWARF 0x6112
#define ANIM_FIGHTER_FEMALE_HALFLING 0x6113
#define ANIM_FIGHTER_FEMALE_GNOME 0x6114
#define ANIM_FIGHTER_FEMALE_HALFORC 0x6115
#define ANIM_MAGE_MALE_HUMAN 0x6200
#define ANIM_MAGE_MALE_ELF 0x6201
#define ANIM_MAGE_MALE_DWARF 0x6202
#define ANIM_MAGE_MALE_GNOME 0x6204
#define ANIM_MAGE_MALE_HALFORC 0x6205
#define ANIM_MAGE_FEMALE_HUMAN 0x6210
#define ANIM_MAGE_FEMALE_ELF 0x6211
#define ANIM_MAGE_FEMALE_DWARF 0x6212
#define ANIM_MAGE_FEMALE_GNOME 0x6214
#define ANIM_MAGE_FEMALE_HALFORC 0x6215
#define ANIM_THIEF_MALE_HUMAN 0x6300
#define ANIM_THIEF_MALE_ELF 0x6301
#define ANIM_THIEF_MALE_DWARF 0x6302
#define ANIM_THIEF_MALE_HALFLING 0x6303
#define ANIM_THIEF_MALE_GNOME 0x6304
#define ANIM_THIEF_MALE_HALFORC 0x6305
#define ANIM_THIEF_FEMALE_HUMAN 0x6310
#define ANIM_THIEF_FEMALE_ELF 0x6311
#define ANIM_THIEF_FEMALE_DWARF 0x6312
#define ANIM_THIEF_FEMALE_HALFLING 0x6313
#define ANIM_THIEF_FEMALE_GNOME 0x6314
#define ANIM_THIEF_FEMALE_HALFORC 0x6315
#define ANIM_MONK_MALE_HUMAN 0x6500
#define ANIM_MONK_FEMALE_HUMAN 0x6510
#define ANIM_MONK 0x6402
#define ANIM_SKELETON 0x6403
#define ANIM_DOOM_GUARD 0x6405
#define ANIM_BEAR_BLACK 0x7200
#define ANIM_BEAR_BROWN 0x7201
#define ANIM_BEAR_CAVE 0x7202
#define ANIM_BEAR_POLAR 0x7203
#define ANIM_SPIDER_GIANT 0x7A00
#define ANIM_SPIDER_HUGE 0x7A01
#define ANIM_SPIDER_PHASE 0x7A02
#define ANIM_SPIDER_SWORD 0x7A03
#define ANIM_SPIDER_WRAITH 0x7A04
#define ANIM_WOLF 0x7B00
#define ANIM_WOLF_WINTER 0x7B03
#define ANIM_WEREWOLF 0x7E00
#define ANIM_WEREWOLF_GREATER 0x7E01
#define ANIM_OGRE 0x9000
#define ANIM_CARRION_CRAWLER 0xA100
#define ANIM_COW 0xB000
#define ANIM_STATIC_BEGGAR_MAN 0xB200
#define ANIM_STATIC_HARLOT_WOMAN 0xB210
#define ANIM_STATIC_BOY 0xB300
#define ANIM_STATIC_GIRL 0xB310
#define ANIM_STATIC_FAT_MAN 0xB400
#define ANIM_STATIC_FAT_WOMAN 0xB410
#define ANIM_STATIC_PEASANT_MAN 0xB500
#define ANIM_STATIC_PEASANT_WOMAN 0xB510
#define ANIM_STATIC_NOBLE_MAN 0xB600
#define ANIM_STATIC_NOBLE_WOMAN 0xB610
#define ANIM_STATIC_SLAVE 0xB700
#define ANIM_BAT_INSIDE 0xC000
#define ANIM_CAT 0xC100
#define ANIM_CHICKEN 0xC200
#define ANIM_RAT 0xC300
#define ANIM_SQUIRREL 0xC400
#define ANIM_BAT_OUTSIDE 0xC500
#define ANIM_BEGGAR_MAN 0xC600
#define ANIM_HARLOT_WOMAN 0xC610
#define ANIM_BOY 0xC700
#define ANIM_GIRL 0xC710
#define ANIM_FAT_MAN 0xC800
#define ANIM_FAT_WOMAN 0xC810
#define ANIM_PEASANT_MAN 0xC900
#define ANIM_PEASANT_WOMAN 0xC910
#define ANIM_NOBLE_MAN 0xCA00
#define ANIM_NOBLE_WOMAN 0xCA10
#define ANIM_SLAVE 0xCB00
#define ANIM_EAGLE 0xD000
#define ANIM_VULTURE 0xD200
#define ANIM_BIRD 0xD300
#define ANIM_BIRD_INSIDE 0xD400
#define ANIM_BEETLE 0xE000
#define ANIM_BEETLE 0xE000
#define ANIM_BEETLE_BOMBADIER 0xE012
#define ANIM_BEETLE_BORING 0xE022
#define ANIM_BEETLE_FIRE 0xE038
#define ANIM_BEETLE_RHINOCEROUS 0xE048
#define ANIM_CYCLOPS 0xE108
#define ANIM_ETTIN 0xE118
#define ANIM_GIANT_FIRE 0xF308
#define ANIM_GIANT_FROST 0xE138
#define ANIM_VERBEEG 0xE148
#define ANIM_ELEMENTAL_EARTH 0xE218
#define ANIM_ELEMENTAL_FIRE 0xE228
#define ANIM_ELEMENTAL_WATER 0xE238
#define ANIM_GHOUL 0xE308
#define ANIM_GHOUL_2 0xE318
#define ANIM_WIGHT 0xE329
#define ANIM_ZOMBIE 0xE338
#define ANIM_ZOMBIE_2 0xE348
#define ANIM_WIGHT_2 0xE359
#define ANIM_WIGHT_3 0xE369
#define ANIM_MUMMY 0xE388
#define ANIM_MUMMY_HISTACHII 0xE39C
#define ANIM_GOBLIN_W_AXE 0xE408
#define ANIM_GOBLIN_W_BOW 0xE412
#define ANIM_GOBLIN_ELITE_W_AXE 0xE428
#define ANIM_GOBLIN_ELITE_W_BOW 0xE432
#define ANIM_SVIRFNEBLIN 0xE449
#define ANIM_GOLEM_IRON 0xE51D
#define ANIM_SKELETON_BONEGUARD 0xE62C
#define ANIM_MINOTAUR 0xE708
#define ANIM_TROLL 0xE718
#define ANIM_TROLL_ICE 0xE728
#define ANIM_TROLL_SNOW 0xE738
#define ANIM_UMBER_HULK 0xE759
#define ANIM_TUNDRA_YETI 0xE76C
#define ANIM_ORC_W_AXE 0xE818
#define ANIM_ORC_W_BOW 0xE822
#define ANIM_ORC_ELITE_W_AXE 0xE838
#define ANIM_ORC_ELITE_W_BOW 0xE842
#define ANIM_ORC_SHAMAN 0xE859
#define ANIM_OROG 0xE868
#define ANIM_OROG_ELITE 0xE878
#define ANIM_OROG_CHIEFTAN 0xE888
#define ANIM_LIZARD_MAN_KING 0xE899
#define ANIM_YUAN_TI_PRIEST 0xE8A1
#define ANIM_SHADOW 0xE908
#define ANIM_GHOST 0xE928
#define ANIM_ANIMATED_PLATE 0xEB08
#define ANIM_ANIMATED_PLATE_2 0xEB18
#define ANIM_ANIMATED_PLATE_3 0xEB28
#define ANIM_BELHIFET 0xEB39
#define ANIM_BELHIFET_PRIEST 0xEB49
#define ANIM_LICH_LARREL 0xEB79
#define ANIM_MYCONID_RED 0xEB99
#define ANIM_MYCONID_BLUE 0xEBA9
#define ANIM_SHRIEKER 0xEBB1
#define ANIM_TANARI 0xEBCD
#define ANIM_SALAMANDER 0xEBD8
#define ANIM_SALAMANDER_FROST 0xEBE8
#define ANIM_SKELETON_ARMORED 0xF008
#define ANIM_YUAN_TI 0xF10E
#define ANIM_YUAN_TI_ELITE 0xF11E
#define ANIM_SKELETON_TATTERED 0xF019
#define ANIM_LIZARD_MAN_2H 0xF209
#define ANIM_LIZARD_MAN_1H 0xF218
#define ANIM_ARUNDEL 0xEBF1
#define ANIM_CREEPING_DOOM 0xEA20
#define ANIM_LICH_WHITE 0xEB69
#define ANIM_SVIRVNEBLIN_NOAXE 0xE459
#define ANIM_BARBARIAN_1 0xF77A
#define ANIM_BARBARIAN_2 0xF78A
#define ANIM_BARBARIAN_3 0xF798
#define ANIM_BARBARIAN_SHAMAN_1 0xE771
#define ANIM_BARBARIAN_SHAMAN_2 0xE781
#define ANIM_BARBARIAN_SHAMAN_3 0xE791
#define ANIM_BARBARIAN_ICASARACHT 0xE7AC
#define ANIM_CORNUGON 0xED09
#define ANIM_DRAGON_WHITE 0xEC0B
#define ANIM_DROWNED_DEAD 0xE3A8
#define ANIM_GLABREZU 0xED19
#define ANIM_GOLEM_ICE 0xE528
#define ANIM_REMORHAZ 0xE050
#define ANIM_SAHUAGIN 0xF40B
#define ANIM_SAHUAGIN_LARGE 0xF41B
#define ANIM_SEER 0xEB51
#define ANIM_ELEMENTAL_SHAMBLING_MOUND 0x7302
#define ANIM_TROLL_SCRAG 0xE7E8
#define ANIM_UMBER_HULK_VODYANOI 0xE7F9
#define ANIM_WAILING_VIRGIN 0xE3BB
#define ANIM_WATER_WEIRD 0xE252
#define ANIM_WIGHT_BARROW 0xF029
#define ANIM_WYVERN 0xA000
#define ANIM_WYVERN_BIG_WHITE 0x1001
#define ANIM_DOG_WILD 0x7400
#define ANIM_DOG_WAR 0x7401
#define ANIM_DOG_MOON 0x7402
#define ANIM_HARPY 0xE249
#define ANIM_BEHOLDER 0x7F02
#define ANIM_RAKSHASA 0x7F10
#define ANIM_SLIME_GREEN 0x7900
#define ANIM_SLIME_OLIVE 0x7901
#define ANIM_SLIME_MUSTARD 0x7902
#define ANIM_SLIME_OCHRE 0x7903
#define ANIM_DEER 0x7F18
#define ANIM_DJINNI 0x7F05
#define ANIM_DJINNI_LEGS 0x7F06
#define ANIM_DOPPLEGANGER 0x7500
#define ANIM_DOPPLEGANGER_GREATER 0x7501
#define ANIM_DRAGON_BLACK 0x1201
#define ANIM_ELEMENTAL_AIR 0x7320
#define ANIM_ELEMENTAL_AIR_SMALL 0x7321
#define ANIM_ELEMENTAL_FIRE_BG2 0x7310
#define ANIM_ETTERCAP 0x7600
#define ANIM_GNOLL 0x8000
#define ANIM_GOLEM_CLAY 0x7F07
#define ANIM_GOLEM_IRON_BG2 0x7F04
#define ANIM_GREATCAT_PANTHER 0x7F0A
#define ANIM_GREATCAT_LEOPARD 0x7F0B
#define ANIM_HOBGOBLIN 0x8100
#define ANIM_IMP 0x7F03
#define ANIM_MINDFLAYER 0x7F01
#define ANIM_OGRE_HALF 0x7000
#define ANIM_OTYUGH 0x7F08
#define ANIM_RAVER 0x7F2E
#define ANIM_SLAYER 0x7F32
#define ANIM_SNAKE 0x7F13
#define ANIM_SPIDER_SMALL 0x7F2F
#define ANIM_ABISHAI_WHITE 0xE7C9
#define ANIM_BOAR_ARCTIC 0xE7B8
#define ANIM_BUGBEAR 0xE8C8
#define ANIM_BUGBEAR_CAPTAIN 0xE8E8
#define ANIM_CHIMERA 0xEC33
#define ANIM_DARKTREE 0xE278
#define ANIM_DRAGON_WHITE_BABY 0xEC0B
#define ANIM_DRIDER_MALE 0xF50B
#define ANIM_DRIDER_FEMALE 0xF51B
#define ANIM_DROW 0x7F27
#define ANIM_DROW_FEMALE 0x7F29
#define ANIM_ELEMENTAL_WATER_SMALL 0xE298
#define ANIM_FEYR 0xE269
#define ANIM_FEYR_GREATER 0xE289
#define ANIM_GIANT_FOMORIAN 0xE15A
#define ANIM_GOBLIN_CAPTAIN 0xE498
#define ANIM_GOBLIN_SHAMAN 0xE479
#define ANIM_GOBLIN_WORG 0xE468
#define ANIM_GOBLIN_WORG_CAPTAIN 0xE488
#define ANIM_HALFDRAGON_BLACK 0xEC4B
#define ANIM_HALFDRAGON_RED 0xEC5B
#define ANIM_HOOK_HORROR 0xE068
#define ANIM_INVISIBLE_TINY 0xEFE3
#define ANIM_INVISIBLE_SMALL 0xEFA3
#define ANIM_INVISIBLE_MEDIUM 0xEFB3
#define ANIM_INVISIBLE_LARGE 0xEFC3
#define ANIM_INVISIBLE_GIANT 0xEFD3
#define ANIM_INVISIBLE_HUGE 0xEFF3
#define ANIM_ISAIR 0xEF0D
#define ANIM_KEG_1 0xEF50
#define ANIM_KEG_2 0xEF60
#define ANIM_KEG_3 0xEF70
#define ANIM_LEMURE 0xED28
#define ANIM_MADAE 0xEF1D
#define ANIM_MALARITE 0xE7D9
#define ANIM_ORC_W_AXE_UNDEAD 0xE808
#define ANIM_ORC_SHAMAN_UNDEAD 0xE8F9
#define ANIM_OROG_SHAMAN 0xE8D9
#define ANIM_SHENRICAL 0xEC2B
#define ANIM_WEREBADGER 0xEE08
#define ANIM_WERERAT 0xEE18
#define ANIM_WORG 0xEF28
#define ANIM_WILL_O_WISP 0xEF91
#define ANIM_YUAN_TI_HALF 0xE8B9
#define ANIM_TYPE_NUM 289

typedef struct {
    SHORT x;
    SHORT y;
} NECK_POINTS;

class CInfinity;
class CVidMode;

class CGameAnimationType {
public:
    static const CString ROUND_BASE;

    static BOOL MIRROR_BAM;

    static CGameAnimationType* SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing);

    CGameAnimationType();
    /* 0000 */ virtual ~CGameAnimationType();
    /* 0004 */ virtual void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 0008 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);
    /* 000C */ virtual void ChangeDirection(SHORT nDirection);
    /* 0010 */ virtual void EquipArmor(CHAR armorLevel, BYTE* colorRangeValues);
    /* 0020 */ virtual CVidPalette* GetAnimationPalette(BYTE range);
    /* 0024 */ virtual void GetAnimationResRef(CString& resRef, BYTE range);
    /* 0028 */ virtual BOOLEAN CanLieDown();
    /* 002C */ virtual BOOLEAN DetectedByInfravision();
    /* 0030 */ virtual WORD GetCastFrame();
    /* 0034 */ virtual BYTE GetColorBlood();
    /* 0038 */ virtual BYTE GetColorChunks();
    /* 003C */ virtual BYTE GetListType();
    /* 0040 */ virtual BYTE GetMoveScale();
    /* 0044 */ virtual void SetMoveScale(BYTE scale);
    /* 0048 */ virtual void ResetMoveScale();
    /* 004C */ virtual BYTE GetMoveScaleDefault();
    /* 0050 */ virtual NECK_POINTS GetNeckOffsets(SHORT nDirection);
    /* 0054 */ virtual const CRect& GetEllipseRect();
    /* 0058 */ virtual BOOL GetPathSmooth();
    /* 005C */ virtual BYTE GetPersonalSpace();
    /* 0060 */ virtual const char* GetSndArmor();
    /* 0064 */ virtual const char* GetSndDeath();
    /* 0068 */ virtual const char* GetSndReady();
    /* 006C */ virtual const char* GetSndWalk(SHORT a1);
    /* 0070 */ virtual DWORD GetSndWalkFreq();
    /* 0074 */ virtual BOOL IsFalseColor();
    /* 0078 */ virtual BOOL IsInvulnerable();
    /* 007C */ virtual BOOL IsMirroring();
    /* 0080 */ virtual BOOL IsBeginningOfSequence();
    /* 0084 */ virtual BOOL IsEndOfSequence();
    /* 0088 */ virtual void IncrementFrame();
    /* 008C */ virtual void DecrementFrame();
    /* 0090 */ virtual void Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency);
    /* 0094 */ virtual void ClearColorEffects(BYTE colorRange);
    /* 0098 */ virtual void ClearColorEffectsAll();
    /* 009C */ virtual void SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength);
    /* 00A0 */ virtual void SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength);
    /* 00A4 */ virtual void SetColorRange(BYTE colorRange, BYTE rangeValue);
    /* 00A8 */ virtual void SetColorRangeAll(BYTE rangeValue);
    /* 00AC */ virtual SHORT SetSequence(SHORT nSequence);
    /* 00B0 */ virtual void CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ);
    /* 00B4 */ virtual void SetNeckOffsets(SHORT Sx, SHORT Sy, SHORT SWx, SHORT SWy, SHORT Wx, SHORT Wy, SHORT NWx, SHORT NWy, SHORT Nx, SHORT Ny, SHORT NEx, SHORT NEy, SHORT Ex, SHORT Ey, SHORT SEx, SHORT SEy);
    /* 00B8 */ virtual BYTE GetAttackFrameType(BYTE numAttacks, BYTE speedFactor, BYTE combatFrame);
    /* 00BC */ virtual BOOL GetAboveGround();
    /* 00C0 */ virtual SHORT GetAwakePlayInReverse();
    /* 00C4 */ virtual SHORT GetCastHeight();
    /* 00C8 */ virtual SHORT GetCurrentFrame();
    /* 00CC */ virtual BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame);
    /* 00D0 */ virtual BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet);

    /* 0004 */ USHORT m_animationID;
    /* 0006 */ BYTE m_moveScale;
    /* 0007 */ BYTE m_moveScaleCurrent;
    /* 0008 */ CRect m_rEllipse;
    /* 0018 */ BYTE m_colorBlood;
    /* 0019 */ BYTE m_colorChunks;
    /* 001A */ DWORD m_nSndFreq;
    /* 001E */ const char* m_pSndDeath;
    /* 0022 */ NECK_POINTS m_neckOffsets[8];
    /* 0042 */ CVidBitmap m_combatRounds[5];
    /* 03E4 */ BYTE m_personalSpace;
    /* 03E6 */ WORD m_castFrame;
    /* 03E9 */ char m_walkRef[9];
    /* 03E8 */ unsigned char field_3E8;
    /* 03FB */ unsigned char field_3FB;
    /* 03FC */ unsigned char field_3FC;
};

#endif /* CGAMEANIMATIONTYPE_H_ */

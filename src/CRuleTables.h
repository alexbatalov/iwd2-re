#ifndef CRULETABLES_H_
#define CRULETABLES_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "C2DArray.h"
#include "CAIIdList.h"

class CAIObjectType;
class CCreatureFileHeader;
class CDerivedStats;
class CGameSprite;
class CItem;

class CRuleTables {
public:
    static const DWORD TIME_RESTING;
    static const DWORD TIME_TRAVELLING;
    static const CString REACTION_MOD_CHARISMA;
    static const CString REACTION_MOD_REPUTATION;
    static const CString REPUTATION_MOD;
    static const CString NO_DECODE_LIST;
    static const CString PROFICIENCY_SLOTS;
    static const CString PROFICIENCY_SLOTS_MAX;
    static const CString FEATS;
    static const CString SKILLS;
    static const CString SKILLCOST;
    static const CString SKILLPTS;
    static const CString SKILL_POINTS_RACE;
    static const CString SKILL_POINTS_DEX;
    static const CString SKILLCLS;
    static const CString SKILL_POINTS_BARD;
    static const CString SKILLSKD;
    static const CString SKILL_POINTS_RANGER;
    static const CString ABILITY_RACE_REQ;
    static const CString ABILITY_RACE_ADJ;
    static const CString ABILITY_CLASS_REQ;
    static const CString MONCRATE;
    static const CString SAVE_PRIEST;
    static const CString SAVE_WARRIOR;
    static const CString SAVE_WIZARD;
    static const CString SAVE_ROGUE;
    static const CString SAVE_BARD;
    static const CString SAVE_DWARF_HALFLING;
    static const CString SAVE_GNOME;
    static const CString SAVE_MONK;
    static const CString SAVE_RACE;
    static const CString HP_WARRIOR;
    static const CString HP_WIZARD;
    static const CString HP_PRIEST;
    static const CString HP_ROGUE;
    static const CString HP_BARBARIAN;
    static const CString HP_CON_BONUS;
    static const CString HP_MONK;
    static const CString STARTING_GOLD;
    static const CString STARTING_XP;
    static const CString THAC0;
    static const CString MAX_SPELLS_BONUS;
    static const CString MAX_SPELLS_BARD;
    static const CString MAX_SPELLS_CLERIC;
    static const CString MAX_SPELLS_DRUID;
    static const CString MAX_SPELLS_PALADIN;
    static const CString MAX_SPELLS_RANGER;
    static const CString MAX_SPELLS_SORCERER;
    static const CString MAX_SPELLS_WIZARD;
    static const CString KNOWN_SPELLS_BARD;
    static const CString KNOWN_SPELLS_SORCERER;
    static const CString MAX_DRUID_SHAPESHIFTS;
    static const CString BACKSTAB_MULTIPLIER;
    static const CString EXPERIENCE_LEVELS;
    static const CString LAY_ON_HANDS_AMOUNT;
    static const CString INSTANT_ACTIONS;
    static const CString MONSTER_SUMMON_1;
    static const CString MONSTER_SUMMON_2;
    static const CString MONSTER_SUMMON_3;
    static const CString ANIMAL_SUMMON_1;
    static const CString ANIMAL_SUMMON_2;
    static const CString STRENGTH_MODIFIERS;
    static const CString INTOXICATION_MODIFIERS;
    static const CString FATIGUE_MODIFIERS;
    static const CString EFFECT_TEXT;
    static const CString PLAYER_INTERACTION;
    static const CString NUM_SPELLS;
    static const CString TOOLTIPS;
    static const CString START_AREA_FILE;
    static const CString START_POS_FILE;
    static const CString SPARKLE_COLOR_FILE;
    static const CString MONTHS;
    static const CString YEARS;
    static const CString POST_DIALOG;
    static const CString CHARACTER_SOUNDS;
    static const CString RT_NORM;
    static const CString RT_FURY;
    static const CString INTERACTION_DIALOG;
    static const CString INTELLIGENCE_MODIFIERS;
    static const CString DONATE_RUMOR;
    static const CString CLASWEAP;
    static const CString AREA_LINKAGE_CACHING;
    static const CString CACHE_VALIDATION;
    static const CString SCRIPT_DESCRIPTION;
    static const CString CHARACTER_STATE_DESCRIPTION;
    static const CString MASTER_AREA;
    static const CString MOVIE_DESCRIPTION;
    static const CString SPELL_DESCRIPTION;
    static const CString BOUNTY_CHANCE;
    static const CString NPC_LEVEL;
    static const CString DEATH_SOUNDS;
    static const CString ALIGNMENT;
    static const CString REPUTATION_STORE_MOD;
    static const CString REPUTATION_START;
    static const CString WEAPON_SPECIALIZATION;
    static const CString WEAPON_ATTACKS;
    static const CString LORE;
    static const CString LORE_BONUS;
    static const CString CHARISMA_STORE_MOD;
    static const CString RAISE_DEAD_COST;
    static const CString HAPPINESS;
    static const CString REPUTATION_DESCRIPTION;
    static const CString PORTRAIT_REPLACEMENT;
    static const CString INTOXICATION;
    static const CString CUSTOM_SOUND;
    static const CString EXCLUSIVE_ITEMS;
    static const CString CHASE_ACTIONS;
    static const CString VEF_PROJECTILES;
    static const CString FEATLVL;
    static const CString FEATCLAS;
    static const CString HELP01;
    static const CString HELP02;
    static const CString HELP03;
    static const CString HELP04;
    static const CString KIT_TABLE;
    static const CString KIT_LIST;
    static const CString SR_TABLE;
    static const CString SR_LIST;
    static const CString RACERSMD;
    static const CString RACESPAB;
    static const CString ENCMOD;
    static const CString CLSSRSMD;
    static const CString QSLOTS;
    static const CString SPONCAST;
    static const CString BARBARIAN;
    static const CString BARD;
    static const CString CLERIC;
    static const CString DRUID;
    static const CString FIGHTER;
    static const CString MONK;
    static const CString PALADIN;
    static const CString RANGER;
    static const CString ROGUE;
    static const CString SORCERER;
    static const CString WIZARD;
    static const CString CLERIC_ILMATER;
    static const CString CLERIC_LATHANDER;
    static const CString CLERIC_SELUNE;
    static const CString CLERIC_HELM;
    static const CString CLERIC_OGHMA;
    static const CString CLERIC_TEMPUS;
    static const CString CLERIC_BANE;
    static const CString CLERIC_MASK;
    static const CString CLERIC_TALOS;
    static const CString MONK_BROKEN_ONES;
    static const CString MONK_OLD_ORDER;
    static const CString MONK_DARK_MOON;
    static const CString PALADIN_ILMATER;
    static const CString PALADIN_HELM;
    static const CString PALADIN_MYSTRA;
    static const CString WIZARD_ABJURER;
    static const CString WIZARD_CONJURER;
    static const CString WIZARD_DIVINER;
    static const CString WIZARD_ENCHANTER;
    static const CString WIZARD_EVOKER;
    static const CString WIZARD_ILLUSIONIST;
    static const CString WIZARD_NECROMANCER;
    static const CString WIZARD_TRANSMUTER;
    static const CString WARRIOR;
    static const CString PRIEST;
    static const CString HUMAN;
    static const CString DWARF;
    static const CString GNOME;
    static const CString ELF;
    static const CString HALF_ELF;
    static const CString HALFLING;
    static const CString HALF_ORC;
    static const CString HUMAN_AASIMAR;
    static const CString HUMAN_TIEFLING;
    static const CString ELF_DROW;
    static const CString ELF_WILD;
    static const CString DWARF_GOLD;
    static const CString DWARF_GRAY;
    static const CString HALFLING_STRONGHEART;
    static const CString HALFLING_GHOSTWISE;
    static const CString GNOME_DEEP;
    static const CString LAWFUL_GOOD;
    static const CString LAWFUL_NEUTRAL;
    static const CString LAWFUL_EVIL;
    static const CString NEUTRAL_GOOD;
    static const CString NEUTRAL;
    static const CString NEUTRAL_EVIL;
    static const CString CHAOTIC_GOOD;
    static const CString CHAOTIC_NEUTRAL;
    static const CString CHAOTIC_EVIL;
    static const CString FIRST_LEVEL;
    static const CString RATE;
    static const CString BASE;
    static const CString PICK_POCKETS;
    static const CString OPEN_LOCKS;
    static const CString FIND_TRAPS;
    static const CString STEALTH;
    static const CString MOVE_SILENTLY;
    static const CString HIDE_IN_SHADOWS;
    static const CString USE_MAGIC_DEVICE;
    static const CString MIN_STR;
    static const CString MIN_DEX;
    static const CString MIN_CON;
    static const CString MIN_INT;
    static const CString MIN_WIS;
    static const CString MIN_CHR;
    static const CString MAX_STR;
    static const CString MAX_DEX;
    static const CString MAX_CON;
    static const CString MAX_INT;
    static const CString MAX_WIS;
    static const CString MAX_CHR;
    static const CString MOD_STR;
    static const CString MOD_DEX;
    static const CString MOD_CON;
    static const CString MOD_INT;
    static const CString MOD_WIS;
    static const CString MOD_CHR;
    static const CString FORTITUDE;
    static const CString REFLEX;
    static const CString WILL;
    static const CString SIDES;
    static const CString ROLLS;
    static const CString MODIFIER;
    static const CString OTHER;
    static const CString MIN_ROLL;
    static const CString MULTIPLIER;
    static const CString BONUS_PER_LEVEL;
    static const CString EFFECT_NAME;
    static const CString STRREF_STR;
    static const CString START_AREA;
    static const CString START_XPOS;
    static const CString START_YPOS;
    static const CString START_AREA_EXPANSION;
    static const CString START_XPOS_EXPANSION;
    static const CString START_YPOS_EXPANSION;
    static const CString VALUE;
    static const CString START_ROT_EXPANSION;
    static const CString START_ROT;
    static const CString SWITCH;
    static const CString DEFAULT;
    static const CString RACE;
    static const CString CLASS;
    static const CString REPUTATION;
    static const CString NONE;
    static const CString GOOD_REPUTATION;
    static const CString BAD_REPUTATION;
    static const CString GOOD_POWER;
    static const CString BAD_POWER;
    static const CString PLAYERINTERACTION_INSULT;
    static const CString PLAYERINTERACTION_COMPLIMENT;
    static const CString PLAYERINTERACTION_SPECIAL;
    static const CString PLAYERINTERACTION_EXTERNALFILE;
    static const CString DAYS;
    static const CString NAME;
    static const CString STARTTIME;
    static const CString STARTYEAR;
    static const CString NORMALDAYMONTHFORMAT;
    static const CString SPECIALDAYMONTHFORMAT;
    static const CString POST_DIALOG_FILE;
    static const CString JOIN_DIALOG_FILE;
    static const CString MALE;
    static const CString FEMALE;
    static const CString INTERACTION_FILE;
    static const CString TOKEN_CLASS;
    static const CString TOKEN_LEVEL;
    static const CString TOKEN_EXPERIENCE;
    static const CString TOKEN_NEXTLEVEL;
    static const CString XPPENALTY;
    static const CString TOKEN_SCRIPT;
    static const CString CASTSPELL;
    static const CString CLASS_ABILITIES_BARBARIAN;
    static const CString CLASS_ABILITIES_BARD;
    static const CString CLASS_ABILITIES_CLERIC_TRUE;
    static const CString CLASS_ABILITIES_CLERIC_ILMATER;
    static const CString CLASS_ABILITIES_CLERIC_LATHANDER;
    static const CString CLASS_ABILITIES_CLERIC_SELUNE;
    static const CString CLASS_ABILITIES_CLERIC_HELM;
    static const CString CLASS_ABILITIES_CLERIC_OGHMA;
    static const CString CLASS_ABILITIES_CLERIC_TEMPUS;
    static const CString CLASS_ABILITIES_CLERIC_BANE;
    static const CString CLASS_ABILITIES_CLERIC_MASK;
    static const CString CLASS_ABILITIES_CLERIC_TALOS;
    static const CString CLASS_ABILITIES_DRUID;
    static const CString CLASS_ABILITIES_FIGHTER;
    static const CString CLASS_ABILITIES_MONK;
    static const CString CLASS_ABILITIES_PALADIN;
    static const CString CLASS_ABILITIES_RANGER;
    static const CString CLASS_ABILITIES_ROGUE;
    static const CString CLASS_ABILITIES_WIZARD;
    static const CString CLABMA02;
    static const CString CLABMA06;
    static const CString CLABMA05;
    static const CString CLABMA07;
    static const CString CLABMA09;
    static const CString CLABMA08;
    static const CString CLABMA03;
    static const CString CLABMA04;
    static const CString CLASS_ABILITIES_SORCERER;
    static const CString AUTOMATIC_SPELL_PICKER;
    static const CString LOADING_HINTS;
    static const CString DUAL_CLASS_ALLOWED;
    static const CString BAATFGT;
    static const CString BAATNFG;
    static const CString BAATMAG;
    static const CString BAATMKU;
    static const CString LISTSPLL;
    static const CString LISTDOMN;
    static const CString LISTINNT;
    static const CString LISTSONG;
    static const CString LISTSHAP;
    static const CString CREHIDEM;
    static const CString CRELIGHT;
    static const CString ITEMTEXT;
    static const CString ITEMABIL;
    static const CString TRAPSAVE;
    static const CString SPPR;
    static const CString SPWI;
    static const CString SPIN;
    static const CString SPWI110;
    static const CString BOW;
    static const CString CROSSBOW;
    static const CString MISSILE;
    static const CString AXE;
    static const CString CLUBMACE;
    static const CString DAGGER;
    static const CString POLEARMS;
    static const CString FLAIL;
    static const CString HAMMER;
    static const CString QUARTER_STAFF;
    static const CString GREAT_SWORD;
    static const CString LARGE_SWORD;
    static const CString SMALL_BLADE;
    static const CString TWO_WEAPON;
    static const CString TWO_HANDED;
    static const CString WEAPON_SHIELD;
    static const CString SINGLE_WEAPON;
    static const CString TITLE;
    static const CString CUSTOM;
    static const CString DESCRIPTION;
    static const CString DEATH_SOUND_ENABLED;
    static const CString FIRE;
    static const CString COLD;
    static const CString ELEC;
    static const CString ACID;
    static const CString SPELL;
    static const CString MAGIC_FIRE;
    static const CString MAGIC_COLD;
    static const CString SLASHING;
    static const CString BLUDGEONING;
    static const CString PIERCING;
    static const CString SPECIAL_ABILITIES_FILE;
    static const CString MOD_XP;
    static const CString ENCUMBRANCE_MOD_PERCENT;
    static const CString TOKEN_MAGESCHOOL;
    static const CString TOKEN_FIGHTERTYPE;
    static const CString DLGINST;
    static const CString SCRINST;

    CRuleTables();
    ~CRuleTables();
    INT GetTrapSenseBonus(CDerivedStats& DStats) const;
    const CString GetRaceString(BYTE nRace, BYTE nSubRace) const;
    const CString GetAlignmentString(BYTE nAlignment) const;
    const CString GetClassString(BYTE nClass, DWORD nSpecialist) const;
    STRREF GetClassSuffixStringRef(BYTE nClass) const;
    STRREF GetClassBeyondCastingAbilityStringRef(BYTE nClass) const;
    STRREF GetClassDescriptionStringRef(BYTE nClass, DWORD nSpecialist) const;
    INT GetAbilityScoreModifier(INT nScore) const;
    int sub_542560(unsigned short a1, unsigned short a2) const;
    void sub_5425E0(const CAIObjectType& typeAI, int a2, BYTE& a3, BYTE& a4, BYTE& a5, BYTE& a6, BYTE& a7, BYTE& a8) const;
    INT FindSavingThrow(CDerivedStats& stats, const CString& sSavingThrow) const;
    INT GetSavingThrow(const CAIObjectType& typeAI, CDerivedStats& DStats, BYTE nCON, const CString& sSavingThrow) const;
    INT GetStartingGold(CGameSprite* pSprite) const;
    INT GetStartingExperiencePoints(CGameSprite* pSprite) const;
    void GetStartArea(CResRef& cResArea, CPoint& ptView) const;
    CPoint GetStartPoint(INT nCharacterSlot) const;
    int GetStartRotation(INT nCharacterSlot) const;
    CList<STRREF, STRREF>* GetChapterText(const CResRef& cResText, BYTE nChapter) const;
    void GetClassStringLower(BYTE nClass, DWORD a2, DWORD a3, CString& sClass, int a5) const;
    void GetClassStringMixed(BYTE nClass, DWORD nSpecialist, DWORD dwFlags, CString& sClass, int a5) const;
    void GetCharacterStateDescription(INT nState, CString& sDescription) const;
    void GetMovieDescription(const CString& sMovie, CString& sDescription) const;
    void GetSpellDescription(const CString& sSpell, CString& sDescription) const;
    SHORT GetLayOnHandsAmount(const CAIObjectType& typeAI, CDerivedStats& DStats) const;
    INT GetLathanderRenewalAmount(const CAIObjectType& typeAI, CDerivedStats& DStats) const;
    BOOL IsValidAlignment(BYTE nClass, BYTE nAlignment, DWORD nSpecialist) const;
    BOOL IsUsableByAlignment(DWORD dwNotUsableBy, BYTE nAlignment) const;
    BYTE GetStartingReputation(BYTE nAlignment) const;
    void AdjustStoreMarkup(BYTE nCHR, SHORT nReputation, DWORD& dwMarkup) const;
    DWORD GetXPCap() const;
    BOOL IsValidSubRace(BYTE nRace, BYTE nSubRace) const;
    void GetRaceStringMixed(BYTE nRace, CString& sClass, BYTE nSubRace) const;
    void GetClassStringGameSpy(BYTE nClass, DWORD nSpecialist, CString& sClass) const;
    INT GetRaiseDeadCost(const CAIObjectType& type, CDerivedStats& DStats) const;
    DWORD GetReputationDescription(SHORT nReputation) const;
    void GetIntoxicationInfo(BYTE nCON, INT& nIntoxicationRate, INT& nRecoveryRate, INT& nIntoxicationCap) const;
    BOOL GetCustomSound(CString& sName, BYTE nSoundId) const;
    void GetAlignmentStringMixed(BYTE nAlignment, CString& sAlignment) const;
    void GetGenderStringMixed(BYTE nGender, CString& sGender) const;
    BOOL IsItemExclusive(CItem* pItem) const;
    BOOL Is3DSound(int nSoundChannel) const;
    float GetSoundReverbMix(int nSoundChannel, int nReverb) const;
    int GetSoundEnvironment(EAXPRESET& preset, int nReverb) const;
    BYTE MapCharacterSpecializationToSchool(WORD nSpecialistMage) const;
    DWORD GetFeatName(DWORD id) const;
    DWORD GetFeatId(DWORD index) const;
    DWORD GetFeatDescription(DWORD id) const;
    DWORD GetSkillName(DWORD id) const;
    DWORD GetSkillId(DWORD index) const;
    DWORD GetSkillDescription(DWORD id) const;
    INT GetLoadingHint(INT nHintNumber) const;
    INT GetNumLoadingHints() const;
    const C2DArray* GetClassAbilityTable(BYTE nClass, DWORD nSpecialist) const;
    BOOLEAN IsHatedRace(BYTE nRace, const CCreatureFileHeader& BStats) const;

    /* 0000 */ C2DArray m_tReactionModCharisma;
    /* 0024 */ C2DArray m_tReactionModReputation;
    /* 0048 */ C2DArray m_tReputationMod;
    /* 006C */ CAIIdList m_lNoDecodeList;
    /* 00AC */ C2DArray m_tFeats;
    /* 00D0 */ C2DArray m_tSkills;
    /* 00F4 */ C2DArray m_tSkillPointsRace;
    /* 0118 */ C2DArray m_tSkillPointsDex;
    /* 013C */ C2DArray m_tSkillPointsBard;
    /* 0160 */ C2DArray m_tSkillPointsRanger;
    /* 0184 */ C2DArray m_tAbilityRaceReq;
    /* 01A8 */ C2DArray m_tAbilityRaceAdj;
    /* 01CC */ C2DArray m_tAbilityClassReq;
    /* 01F0 */ C2DArray m_tMoncRate;
    /* 0214 */ C2DArray m_tSavingThrowPriest;
    /* 0238 */ C2DArray m_tSavingThrowWarrior;
    /* 025C */ C2DArray m_tSavingThrowWizard;
    /* 0280 */ C2DArray m_tSavingThrowRogue;
    /* 02A4 */ C2DArray m_tSavingThrowBard;
    /* 02C8 */ C2DArray m_tSavingThrowMonk;
    /* 02EC */ C2DArray m_tSavingThrowRace;
    /* 0310 */ C2DArray m_tHitPointsWarrior;
    /* 0334 */ C2DArray m_tHitPointsWizard;
    /* 0358 */ C2DArray m_tHitPointsPriest;
    /* 037C */ C2DArray m_tHitPointsRogue;
    /* 03A0 */ C2DArray m_tHitPointsBarbarian;
    /* 03C4 */ C2DArray m_tHitPointsMonk;
    /* 03E8 */ C2DArray m_tStartingGold;
    /* 040C */ C2DArray m_tStartingExperiencePoints;
    /* 0430 */ C2DArray m_tTHAC0;
    /* 0454 */ C2DArray m_tMaxSpellsBard;
    /* 0478 */ C2DArray m_tMaxSpellsCleric;
    /* 049C */ C2DArray m_tMaxSpellsDruid;
    /* 04C0 */ C2DArray m_tMaxSpellsPaladin;
    /* 04E4 */ C2DArray m_tMaxSpellsRanger;
    /* 0508 */ C2DArray m_tMaxSpellsSorcerer;
    /* 052C */ C2DArray m_tMaxSpellsWizard;
    /* 0550 */ C2DArray m_tKnownSpellsBard;
    /* 0574 */ C2DArray m_tKnownSpellsSorcerer;
    /* 0598 */ C2DArray m_tMaxDruidShapeshifts;
    /* 05BC */ C2DArray m_tMaxSpellsBonus;
    /* 05E0 */ C2DArray m_tBackstabMultiplier;
    /* 0604 */ C2DArray m_tExperienceLevels;
    /* 0628 */ C2DArray m_tLayOnHandsAmount;
    /* 064C */ C2DArray field_64C;
    /* 0670 */ C2DArray field_670;
    /* 0694 */ C2DArray field_694;
    /* 06B8 */ C2DArray field_6B8;
    /* 06Dc */ C2DArray field_6DC;
    /* 0700 */ C2DArray m_tStrengthMod;
    /* 0724 */ C2DArray m_tIntoxicationMod;
    /* 0748 */ C2DArray m_tFatigueMod;
    /* 076C */ C2DArray m_tEffectText;
    /* 0790 */ C2DArray field_790;
    /* 07B4 */ C2DArray m_tNumSpells;
    /* 07D8 */ C2DArray m_tToolTips;
    /* 07FC */ C2DArray m_tStartArea;
    /* 0820 */ C2DArray m_tStartPos;
    /* 0844 */ C2DArray m_tSparkleColors;
    /* 0868 */ C2DArray m_tMonths;
    /* 088C */ C2DArray m_tYears;
    /* 08B0 */ C2DArray m_tPostDialog;
    /* 08D4 */ C2DArray m_tCharacterSounds;
    /* 08F8 */ C2DArray m_tRtNorm;
    /* 091C */ C2DArray m_tRtFury;
    /* 0940 */ C2DArray field_940;
    /* 0964 */ C2DArray m_tIntelligenceMod;
    /* 0988 */ C2DArray m_tDonateRumor;
    /* 09AC */ C2DArray m_tClassWeapon;
    /* 09D0 */ C2DArray m_tAreaLinkageCaching;
    /* 09F4 */ C2DArray m_tCacheValidation;
    /* 0A18 */ C2DArray m_tScriptDescription;
    /* 0A3C */ C2DArray m_tCharacterStateDescription;
    /* 0A60 */ C2DArray m_tMasterArea;
    /* 0A84 */ C2DArray m_tMovieDescription;
    /* 0AA8 */ C2DArray m_tSpellDescription;
    /* 0ACC */ C2DArray field_ACC;
    /* 0AF0 */ C2DArray field_AF0;
    /* 0B14 */ C2DArray field_B14;
    /* 0B38 */ C2DArray m_tAlignment;
    /* 0B5C */ C2DArray m_tReputationStoreMod;
    /* 0B80 */ C2DArray m_tReputationStart;
    /* 0BA4 */ C2DArray m_tWeaponSpecialization;
    /* 0BC8 */ C2DArray m_tWeaponAttacks;
    /* 0BEC */ C2DArray m_tLore;
    /* 0C10 */ C2DArray m_tCharismaStoreMod;
    /* 0C34 */ C2DArray m_tRaiseDeadCost;
    /* 0C58 */ C2DArray m_tHappiness;
    /* 0C7C */ C2DArray m_tReputationDescription;
    /* 0CA0 */ C2DArray field_CA0;
    /* 0CC4 */ C2DArray m_tIntoxication;
    /* 0CE8 */ C2DArray m_tCustomSound;
    /* 0D0C */ C2DArray m_tExclusiveItems;
    /* 0D30 */ C2DArray m_tFeatClass;
    /* 0D54 */ C2DArray m_tFeatLevel;
    /* 0D78 */ C2DArray m_tSkillCosts;
    /* 0D9C */ C2DArray m_tSkillPoints;
    /* 0DC0 */ C2DArray m_tSoundChannel;
    /* 0DE4 */ C2DArray m_tReverb;
    /* 0E08 */ CAIIdList m_lEAXEnvironment;
    /* 0E48 */ CAIIdList field_E48;
    /* 0E88 */ CAIIdList field_E88;
    /* 0EC8 */ C2DArray m_tMonsterSummon1;
    /* 0EEC */ C2DArray m_tMonsterSummon2;
    /* 0F10 */ C2DArray m_tMonsterSummon3;
    /* 0F34 */ C2DArray m_tMonsterSummon4;
    /* 0F58 */ C2DArray m_tMonsterSummon5;
    /* 0F7C */ C2DArray m_tMonsterSummon6;
    /* 0FA0 */ C2DArray m_tMonsterSummonMalavon;
    /* 0FC4 */ C2DArray m_tMonsterSummon7;
    /* 0FE8 */ C2DArray m_tAnimalSummon1;
    /* 100C */ C2DArray m_tAnimalSummon2;
    /* 1030 */ C2DArray m_tAnimalSummon3;
    /* 1054 */ C2DArray m_tSMonste;
    /* 1078 */ C2DArray m_tDSMonste;
    /* 109C */ C2DArray m_tShades;
    /* 10C0 */ C2DArray m_tADead;
    /* 10E4 */ C2DArray m_tADeadL;
    /* 1108 */ C2DArray m_tGInsect;
    /* 112C */ C2DArray m_tCDoom;
    /* 1150 */ C2DArray m_tCFElemW;
    /* 1174 */ C2DArray m_tCEElemW;
    /* 1198 */ C2DArray m_tCEElemM;
    /* 11BC */ C2DArray m_tCWElemW;
    /* 11E0 */ C2DArray m_tCFElemP;
    /* 1204 */ C2DArray m_tCEElemP;
    /* 1228 */ C2DArray field_1228;
    /* 124C */ C2DArray m_tSShadow;
    /* 1270 */ C2DArray m_tIStalke;
    /* 1294 */ C2DArray m_tSLizard;
    /* 12B8 */ C2DArray m_tSTrolls;
    /* 12DC */ C2DArray m_tCharStr;
    /* 1300 */ C2DArray m_tTracking;
    /* 1324 */ C2DArray m_tKitList;
    /* 1348 */ C2DArray m_tSrTable;
    /* 136C */ C2DArray m_tSrList;
    /* 1390 */ C2DArray m_tRaceRsMd;
    /* 13B4 */ C2DArray m_tRaceSpAb;
    /* 13D8 */ C2DArray m_tEncMod;
    /* 13FC */ C2DArray m_tClassRsMd;
    /* 1420 */ C2DArray m_tQuickSlots;
    /* 1444 */ C2DArray m_tSpontaneousCasting;
    /* 1468 */ C2DArray m_tClassAbilitiesBarbarian;
    /* 148C */ C2DArray m_tClassAbilitiesBard;
    /* 14B0 */ C2DArray m_tClassAbilitiesClericTrue;
    /* 14D4 */ C2DArray m_tClassAbilitiesClericIlmater;
    /* 14F8 */ C2DArray m_tClassAbilitiesClericLathander;
    /* 151C */ C2DArray m_tClassAbilitiesClericSelune;
    /* 1540 */ C2DArray m_tClassAbilitiesClericHelm;
    /* 1564 */ C2DArray m_tClassAbilitiesClericOghma;
    /* 1588 */ C2DArray m_tClassAbilitiesClericTempus;
    /* 15AC */ C2DArray m_tClassAbilitiesClericBane;
    /* 15D0 */ C2DArray m_tClassAbilitiesClericMask;
    /* 15F4 */ C2DArray m_tClassAbilitiesClericTalos;
    /* 1618 */ C2DArray m_tClassAbilitiesDruid;
    /* 163C */ C2DArray m_tClassAbilitiesFighter;
    /* 1660 */ C2DArray m_tClassAbilitiesMonk;
    /* 1684 */ C2DArray m_tClassAbilitiesPaladin;
    /* 16A8 */ C2DArray m_tClassAbilitiesRanger;
    /* 16CC */ C2DArray m_tClassAbilitiesRogue;
    /* 16F0 */ C2DArray m_tClassAbilitiesSorcerer;
    /* 1714 */ C2DArray m_tClassAbilitiesWizard;
    /* 1738 */ C2DArray field_1738;
    /* 175C */ C2DArray field_175C;
    /* 1780 */ C2DArray field_1780;
    /* 17A4 */ C2DArray field_17A4;
    /* 17C8 */ C2DArray field_17C8;
    /* 17EC */ C2DArray field_17EC;
    /* 1810 */ C2DArray field_1810;
    /* 1834 */ C2DArray field_1834;
    /* 1858 */ C2DArray m_tSpellAutomaticPicker;
    /* 187C */ C2DArray m_tLoadingHints;
    /* 18A0 */ C2DArray m_tBAATFGT;
    /* 18C4 */ C2DArray m_tBAATNFG;
    /* 18E8 */ C2DArray m_tBAATMAG;
    /* 190C */ C2DArray m_tBAATMKU;
    /* 1930 */ C2DArray m_tCREHIDEM;
    /* 1954 */ C2DArray m_tCRELIGHT;
    /* 1978 */ C2DArray m_tItemText;
    /* 199C */ C2DArray m_tItemAbility;
    /* 19C0 */ C2DArray m_tTrapSave;
    /* 19E4 */ CAIIdList m_lInstantActions;
    /* 1A24 */ C2DArray m_tAreaLoad;
    /* 1A48 */ CAIIdList m_lDLGINST;
    /* 1A88 */ CAIIdList m_lSCRINST;
    /* 1AC8 */ C2DArray m_tHelp01;
    /* 1AEC */ C2DArray m_tHelp02;
    /* 1B10 */ C2DArray m_tHelp03;
    /* 1B34 */ C2DArray m_tHelp04;
};

#endif /* CRULETABLES_H_ */

#ifndef CRULETABLES_H_
#define CRULETABLES_H_

#include "mfc.h"

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
    static const CString CLABFI05;
    static const CString CLABBA01;
    static const CString CLABPR01;
    static const CString CLABCL01;
    static const CString CLABCL02;
    static const CString CLABCL03;
    static const CString CLABCL04;
    static const CString CLABCL05;
    static const CString CLABCL06;
    static const CString CLABCL07;
    static const CString CLABCL08;
    static const CString CLABCL09;
    static const CString CLABDR01;
    static const CString CLABFI01;
    static const CString CLABMO01;
    static const CString CLABPA01;
    static const CString CLABRN01;
    static const CString CLABTH01;
    static const CString CLABMA01;
    static const CString CLABMA02;
    static const CString CLABMA06;
    static const CString CLABMA05;
    static const CString CLABMA07;
    static const CString CLABMA09;
    static const CString CLABMA08;
    static const CString CLABMA03;
    static const CString CLABMA04;
    static const CString CLABSR01;
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
};

#endif /* CRULETABLES_H_ */

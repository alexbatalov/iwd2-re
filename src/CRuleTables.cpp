#include "CRuleTables.h"

#include "CTimerWorld.h"

// 0x8DF018
const DWORD CRuleTables::TIME_RESTING = 8
    * CTimerWorld::TIMESCALE_MSEC_PER_SEC
    * CTimerWorld::TIMESCALE_SEC_PER_MIN
    * CTimerWorld::TIMESCALE_MIN_PER_HOUR;

// 0x8DF11C
const DWORD CRuleTables::TIME_TRAVELLING = 4
    * CTimerWorld::TIMESCALE_MSEC_PER_SEC
    * CTimerWorld::TIMESCALE_SEC_PER_MIN
    * CTimerWorld::TIMESCALE_MIN_PER_HOUR;

// 0x8DEFEC
const CString CRuleTables::REACTION_MOD_CHARISMA("RModCHR");

// 0x8DE9CC
const CString CRuleTables::REACTION_MOD_REPUTATION("RModRep");

// 0x8DE9D4
const CString CRuleTables::REPUTATION_MOD("Reputati");

// 0x8DEFD8
const CString CRuleTables::NO_DECODE_LIST("NoDecode");

// 0x8DEE48
const CString CRuleTables::PROFICIENCY_SLOTS("Profs");

// 0x8DEE9C
const CString CRuleTables::PROFICIENCY_SLOTS_MAX("ProfsMax");

// #guess
// 0x8DF228
const CString CRuleTables::FEATS("Feats");

// #guess
// 0x8DEF34
const CString CRuleTables::SKILLS("Skills");

// #guess
// 0x8DF2B8
const CString CRuleTables::SKILLCOST("SkilCost");

// #guess
// 0x8DF224
const CString CRuleTables::SKILLPTS("SkillPts");

// 0x8DE9BC
const CString CRuleTables::SKILL_POINTS_RACE("SKillRac");

// 0x8DE8D4
const CString CRuleTables::SKILL_POINTS_DEX("SkillDex");

// #guess
// 0x8DF240
const CString CRuleTables::SKILLCLS("SKillCls");

// 0x8DEEC0
const CString CRuleTables::SKILL_POINTS_BARD("SkillBrd");

// #guess
// 0x8DEF84
const CString CRuleTables::SKILLSKD("SkillSkd");

// 0x8DF2B4
const CString CRuleTables::SKILL_POINTS_RANGER("SkillRng");

// 0x8DEFA8
const CString CRuleTables::ABILITY_RACE_REQ("AbRaceRq");

// 0x8DF0EC
const CString CRuleTables::ABILITY_RACE_ADJ("AbRaceAd");

// 0x8DE9F0
const CString CRuleTables::ABILITY_CLASS_REQ("AbClasRq");

// #guess
// 0x8DEE28
const CString CRuleTables::MONCRATE("MoncRate");

// 0x8DF0A8
const CString CRuleTables::SAVE_PRIEST("SavePrs");

// 0x8DF1DC
const CString CRuleTables::SAVE_WARRIOR("SaveWar");

// 0x8DF270
const CString CRuleTables::SAVE_WIZARD("SaveWiz");

// 0x8DE910
const CString CRuleTables::SAVE_ROGUE("SaveRog");

// #guess
// 0x8DF1E4
const CString CRuleTables::SAVE_BARD("SaveBrd");

// 0x8DF248
const CString CRuleTables::SAVE_DWARF_HALFLING("SaveCnDH");

// 0x8DF140
const CString CRuleTables::SAVE_GNOME("SaveCnG");

// 0x8DEE38
const CString CRuleTables::SAVE_MONK("SaveMONK");

// #guess
// 0x8DF1EC
const CString CRuleTables::SAVE_RACE("SaveRace");

// #guess
// 0x8DE980
const CString CRuleTables::HP_WARRIOR("HPWar");

// #guess
// 0x8DF0CC
const CString CRuleTables::HP_WIZARD("HPWiz");

// #guess
// 0x8DE954
const CString CRuleTables::HP_PRIEST("HPPrs");

// #guess
// 0x8DF0D4
const CString CRuleTables::HP_ROGUE("HPRog");

// #guess
// 0x8DF1D0
const CString CRuleTables::HP_BARBARIAN("HPBarb");

// 0x8DF090
const CString CRuleTables::HP_CON_BONUS("HPCONBon");

// #guess
// 0x8DF118
const CString CRuleTables::HP_MONK("HPMONK");

// 0x8DEFB0
const CString CRuleTables::STARTING_GOLD("StrtGold");

// #guess
// 0x8DF24C
const CString CRuleTables::STARTING_XP("StrtXP");

// 0x8DF04C
const CString CRuleTables::THAC0("THAC0");

// #guess
// 0x8DF28C
const CString CRuleTables::MAX_SPELLS_BONUS("MxSplBon");

// #guess
// 0x8DF1B8
const CString CRuleTables::MAX_SPELLS_BARD("MxSplBrd");

// #guess
// 0x8DE99C
const CString CRuleTables::MAX_SPELLS_CLERIC("MxSplClr");

// #guess
// 0x8DF064
const CString CRuleTables::MAX_SPELLS_DRUID("MxSplDrd");

// #guess
// 0x8DF23C
const CString CRuleTables::MAX_SPELLS_PALADIN("MxSplPal");

// #guess
// 0x8DF1E0
const CString CRuleTables::MAX_SPELLS_RANGER("MxSplRgr");

// #guess
// 0x8DEEB4
const CString CRuleTables::MAX_SPELLS_SORCERER("MxSplSor");

// #guess
// 0x8DF0D8
const CString CRuleTables::MAX_SPELLS_WIZARD("MxSplWiz");

// #guess
// 0x8DF110
const CString CRuleTables::KNOWN_SPELLS_BARD("SplBrdKn");

// 0x8DF010
const CString CRuleTables::KNOWN_SPELLS_SORCERER("SplSrcKn");

// #guess
// 0x8DF158
const CString CRuleTables::MAX_DRUID_SHAPESHIFTS("MxDrdShp");

// 0x8DF184
const CString CRuleTables::BACKSTAB_MULTIPLIER("Backstab");

// 0x8DF008
const CString CRuleTables::EXPERIENCE_LEVELS("XPLevel");

// 0x8DF1A8
const CString CRuleTables::LAY_ON_HANDS_AMOUNT("LayHands");

// 0x8DE8E8
const CString CRuleTables::INSTANT_ACTIONS("Instant");

// 0x8DF238
const CString CRuleTables::MONSTER_SUMMON_1("MONSUM01");

// 0x8DE9B0
const CString CRuleTables::MONSTER_SUMMON_2("MONSUM02");

// 0x8DE988
const CString CRuleTables::MONSTER_SUMMON_3("MONSUM03");

// 0x8DF294
const CString CRuleTables::ANIMAL_SUMMON_1("ANISUM01");

// 0x8DF0E8
const CString CRuleTables::ANIMAL_SUMMON_2("ANISUM02");

// 0x8DE9D0
const CString CRuleTables::STRENGTH_MODIFIERS("STRMOD");

// 0x8DF0B0
const CString CRuleTables::INTOXICATION_MODIFIERS("INTOXMOD");

// 0x8DF038
const CString CRuleTables::FATIGUE_MODIFIERS("FATIGMOD");

// 0x8DF08C
const CString CRuleTables::EFFECT_TEXT("EFFTEXT");

// 0x8DF1A4
const CString CRuleTables::PLAYER_INTERACTION("INTERACT");

// 0x8DF060
const CString CRuleTables::NUM_SPELLS("SPELLS");

// 0x8DEEF4
const CString CRuleTables::TOOLTIPS("TOOLTIP");

// 0x8DEE3C
const CString CRuleTables::START_AREA_FILE("STARTARE");

// 0x8DF26C
const CString CRuleTables::START_POS_FILE("STARTPOS");

// 0x8DE9C8
const CString CRuleTables::SPARKLE_COLOR_FILE("SPRKLCLR");

// 0x8DF290
const CString CRuleTables::MONTHS("MONTHS");

// 0x8DE8A8
const CString CRuleTables::YEARS("YEARS");

// 0x8DE8F8
const CString CRuleTables::POST_DIALOG("PDIALOG");

// 0x8DEE60
const CString CRuleTables::CHARACTER_SOUNDS("CHARSND");

// #guess
// 0x8DF0C8
const CString CRuleTables::RT_NORM("RT_NORM");

// #guess
// 0x8DEF14
const CString CRuleTables::RT_FURY("RT_FURY");

// 0x8DF234
const CString CRuleTables::INTERACTION_DIALOG("INTERDIA");

// 0x8DF100
const CString CRuleTables::INTELLIGENCE_MODIFIERS("INTMOD");

// 0x8DF034
const CString CRuleTables::DONATE_RUMOR("DONARUMR");

// #guess
// 0x8DEFA0
const CString CRuleTables::CLASWEAP("CLASWEAP");

// 0x8DEE18
const CString CRuleTables::AREA_LINKAGE_CACHING("AREALINK");

// 0x8DF114
const CString CRuleTables::CACHE_VALIDATION("CACHVALD");

// 0x8DE8E0
const CString CRuleTables::SCRIPT_DESCRIPTION("ScrpDesc");

// 0x8DE900
const CString CRuleTables::CHARACTER_STATE_DESCRIPTION("StatDesc");

// 0x8DEF44
const CString CRuleTables::MASTER_AREA("MastArea");

// 0x8DEF28
const CString CRuleTables::MOVIE_DESCRIPTION("MoviDesc");

// 0x8DEDFC
const CString CRuleTables::SPELL_DESCRIPTION("SpelDesc");

// 0x8DF0C4
const CString CRuleTables::BOUNTY_CHANCE("BntyChnc");

// 0x8DE9F4
const CString CRuleTables::NPC_LEVEL("NPCLevel");

// 0x8DF0F0
const CString CRuleTables::DEATH_SOUNDS("Death");

// 0x8DF078
const CString CRuleTables::ALIGNMENT("Alignmnt");

// 0x8DF160
const CString CRuleTables::REPUTATION_STORE_MOD("REPMODST");

// 0x8DF254
const CString CRuleTables::REPUTATION_START("repstart");

// 0x8DF14C
const CString CRuleTables::WEAPON_SPECIALIZATION("WSPECIAL");

// 0x8DE974
const CString CRuleTables::WEAPON_ATTACKS("WSPATCK");

// 0x8DF048
const CString CRuleTables::LORE("Lore");

// 0x8DE904
const CString CRuleTables::LORE_BONUS("LoreBon");

// 0x8DEE74
const CString CRuleTables::CHARISMA_STORE_MOD("CHRMODS");

// 0x8DF19C
const CString CRuleTables::RAISE_DEAD_COST("RaisDead");

// 0x8DE8CC
const CString CRuleTables::HAPPINESS("HAPPY");

// 0x8DF1CC
const CString CRuleTables::REPUTATION_DESCRIPTION("RepTxt");

// 0x8DF1AC
const CString CRuleTables::PORTRAIT_REPLACEMENT("Portrait");

// 0x8DEE10
const CString CRuleTables::INTOXICATION("IntoxCON");

// 0x8DEF1C
const CString CRuleTables::CUSTOM_SOUND("CSOUND");

// 0x8DF1E8
const CString CRuleTables::EXCLUSIVE_ITEMS("itemexcl");

// 0x8DF198
const CString CRuleTables::CHASE_ACTIONS("CHASE");

// 0x8DE9E4
const CString CRuleTables::VEF_PROJECTILES("VEFProj");

// #guess
// 0x8DF070
const CString CRuleTables::FEATLVL("FeatLvl");

// #guess
// 0x8DF1FC
const CString CRuleTables::FEATCLAS("FeatClas");

// #guess
// 0x8DF180
const CString CRuleTables::HELP01("Help01");

// #guess
// 0x8DEFF8
const CString CRuleTables::HELP02("Help02");

// #guess
// 0x8DE914
const CString CRuleTables::HELP03("Help03");

// #guess
// 0x8DEE78
const CString CRuleTables::HELP04("Help04");

// 0x8DE8F4
const CString CRuleTables::KIT_TABLE("KitTable");

// 0x8DEE00
const CString CRuleTables::KIT_LIST("KitList");

// #guess
// 0x8DF1F8
const CString CRuleTables::SR_TABLE("SRTable");

// #guess
// 0x8DEFA4
const CString CRuleTables::SR_LIST("SRList");

// #guess
// 0x8DF130
const CString CRuleTables::RACERSMD("RaceRsMd");

// #guess
// 0x8DE948
const CString CRuleTables::RACESPAB("RaceSpAb");

// #guess
// 0x8DEFD0
const CString CRuleTables::ENCMOD("EncMod");

// #guess
// 0x8DE930
const CString CRuleTables::CLSSRSMD("ClssRsMd");

// #guess
// 0x8DE95C
const CString CRuleTables::QSLOTS("QSLOTS");

// #guess
// 0x8DF230
const CString CRuleTables::SPONCAST("SPONCAST");

// 0x8DE8D0
const CString CRuleTables::BARBARIAN("BARBARIAN");

// 0x8DE8AC
const CString CRuleTables::BARD("BARD");

// 0x8DEE20
const CString CRuleTables::CLERIC("CLERIC");

// 0x8DF210
const CString CRuleTables::DRUID("DRUID");

// 0x8DEF4C
const CString CRuleTables::FIGHTER("FIGHTER");

// 0x8DF054
const CString CRuleTables::MONK("MONK");

// 0x8DEEC8
const CString CRuleTables::PALADIN("PALADIN");

// 0x8DEFD4
const CString CRuleTables::RANGER("RANGER");

// 0x8DEE40
const CString CRuleTables::ROGUE("ROGUE");

// 0x8DEEEC
const CString CRuleTables::SORCERER("SORCERER");

// 0x8DEE50
const CString CRuleTables::WIZARD("WIZARD");

// 0x8DF004
const CString CRuleTables::CLERIC_ILMATER("CLERIC_ILMATER");

// 0x8DE8B8
const CString CRuleTables::CLERIC_LATHANDER("CLERIC_LATHANDER");

// 0x8DE920
const CString CRuleTables::CLERIC_SELUNE("CLERIC_SELUNE");

// 0x8DF204
const CString CRuleTables::CLERIC_HELM("CLERIC_HELM");

// 0x8DE938
const CString CRuleTables::CLERIC_OGHMA("CLERIC_OGHMA");

// 0x8DF044
const CString CRuleTables::CLERIC_TEMPUS("CLERIC_TEMPUS");

// 0x8DF0FC
const CString CRuleTables::CLERIC_BANE("CLERIC_BANE");

// 0x8DF144
const CString CRuleTables::CLERIC_MASK("CLERIC_MASK");

// 0x8DE8BC
const CString CRuleTables::CLERIC_TALOS("CLERIC_TALOS");

// 0x8DE970
const CString CRuleTables::MONK_BROKEN_ONES("MONK_BROKEN_ONES");

// 0x8DEF70
const CString CRuleTables::MONK_OLD_ORDER("MONK_OLD_ORDER");

// 0x8DEE54
const CString CRuleTables::MONK_DARK_MOON("MONK_DARK_MOON");

// 0x8DEE0C
const CString CRuleTables::PALADIN_ILMATER("PALADIN_ILMATER");

// 0x8DF1C4
const CString CRuleTables::PALADIN_HELM("PALADIN_HELM");

// 0x8DF18C
const CString CRuleTables::PALADIN_MYSTRA("PALADIN_MYSTRA");

// 0x8DF164
const CString CRuleTables::WIZARD_ABJURER("WIZARD_ABJURER");

// 0x8DEF3C
const CString CRuleTables::WIZARD_CONJURER("WIZARD_CONJURER");

// 0x8DE908
const CString CRuleTables::WIZARD_DIVINER("WIZARD_DIVINER");

// 0x8DE97C
const CString CRuleTables::WIZARD_ENCHANTER("WIZARD_ENCHANTER");

// 0x8DF050
const CString CRuleTables::WIZARD_EVOKER("WIZARD_EVOKER");

// 0x8DF1F4
const CString CRuleTables::WIZARD_ILLUSIONIST("WIZARD_ILLUSIONIST");

// 0x8DF2BC
const CString CRuleTables::WIZARD_NECROMANCER("WIZARD_NECROMANCER");

// 0x8DE9E0
const CString CRuleTables::WIZARD_TRANSMUTER("WIZARD_TRANSMUTER");

// 0x8DF028
const CString CRuleTables::WARRIOR("WARRIOR");

// 0x8DE8EC
const CString CRuleTables::PRIEST("PRIEST");

// 0x8DEF74
const CString CRuleTables::HUMAN("HUMAN");

// 0x8DF1BC
const CString CRuleTables::DWARF("DWARF");

// 0x8DF2A8
const CString CRuleTables::GNOME("GNOME");

// 0x8DF03C
const CString CRuleTables::ELF("ELF");

// 0x8DE964
const CString CRuleTables::HALF_ELF("HALF_ELF");

// 0x8DF220
const CString CRuleTables::HALFLING("HALFLING");

// 0x8DE8C4
const CString CRuleTables::HALF_ORC("HALF_ORC");

// 0x8DE958
const CString CRuleTables::HUMAN_AASIMAR("HUMAN_AASIMAR");

// 0x8DE9D8
const CString CRuleTables::HUMAN_TIEFLING("HUMAN_TIEFLING");

// 0x8DF09C
const CString CRuleTables::ELF_DROW("ELF_DROW");

// 0x8DEE84
const CString CRuleTables::ELF_WILD("ELF_WILD");

// 0x8DF108
const CString CRuleTables::DWARF_GOLD("DWARF_GOLD");

// 0x8DE92C
const CString CRuleTables::DWARF_GRAY("DWARF_GRAY");

// 0x8DF0C0
const CString CRuleTables::HALFLING_STRONGHEART("HALFLING_STRONGHEART");

// 0x8DF200
const CString CRuleTables::HALFLING_GHOSTWISE("HALFLING_GHOSTWISE");

// 0x8DF170
const CString CRuleTables::GNOME_DEEP("GNOME_DEEP");

// 0x8DEEA0
const CString CRuleTables::LAWFUL_GOOD("L_G");

// 0x8DEF98
const CString CRuleTables::LAWFUL_NEUTRAL("L_N");

// 0x8DE990
const CString CRuleTables::LAWFUL_EVIL("L_E");

// 0x8DEE98
const CString CRuleTables::NEUTRAL_GOOD("N_G");

// 0x8DEEDC
const CString CRuleTables::NEUTRAL("N_N");

// 0x8DEEC4
const CString CRuleTables::NEUTRAL_EVIL("N_E");

// 0x8DF13C
const CString CRuleTables::CHAOTIC_GOOD("C_G");

// 0x8DEE08
const CString CRuleTables::CHAOTIC_NEUTRAL("C_N");

// 0x8DE9B4
const CString CRuleTables::CHAOTIC_EVIL("C_E");

// 0x8DF20C
const CString CRuleTables::FIRST_LEVEL("FIRST_LEVEL");

// 0x8DEFFC
const CString CRuleTables::RATE("RATE");

// #guess
// 0x8DF024
const CString CRuleTables::BASE("BASE");

// 0x8DF244
const CString CRuleTables::PICK_POCKETS("PICK_POCKETS");

// 0x8DE9AC
const CString CRuleTables::OPEN_LOCKS("OPEN_LOCKS");

// 0x8DE93C
const CString CRuleTables::FIND_TRAPS("FIND_TRAPS");

// #guess
// 0x8DE9A8
const CString CRuleTables::STEALTH("STEALTH");

// 0x8DF134
const CString CRuleTables::MOVE_SILENTLY("MOVE_SILENTLY");

// 0x8DF084
const CString CRuleTables::HIDE_IN_SHADOWS("HIDE_IN_SHADOWS");

// #guess
// 0x8DF068
const CString CRuleTables::USE_MAGIC_DEVICE("USE_MAGIC_DEVICE");

// 0x8DF12C
const CString CRuleTables::MIN_STR("MIN_STR");

// 0x8DF194
const CString CRuleTables::MIN_DEX("MIN_DEX");

// 0x8DF0E0
const CString CRuleTables::MIN_CON("MIN_CON");

// 0x8DEE70
const CString CRuleTables::MIN_INT("MIN_INT");

// 0x8DE96C
const CString CRuleTables::MIN_WIS("MIN_WIS");

// 0x8DEFF4
const CString CRuleTables::MIN_CHR("MIN_CHR");

// 0x8DF1B4
const CString CRuleTables::MAX_STR("MAX_STR");

// 0x8DF000
const CString CRuleTables::MAX_DEX("MAX_DEX");

// 0x8DEF7C
const CString CRuleTables::MAX_CON("MAX_CON");

// 0x8DF22C
const CString CRuleTables::MAX_INT("MAX_INT");

// 0x8DF00C
const CString CRuleTables::MAX_WIS("MAX_WIS");

// 0x8DF0E4
const CString CRuleTables::MAX_CHR("MAX_CHR");

// 0x8DF128
const CString CRuleTables::MOD_STR("MOD_STR");

// 0x8DF25C
const CString CRuleTables::MOD_DEX("MOD_DEX");

// 0x8DE91C
const CString CRuleTables::MOD_CON("MOD_CON");

// 0x8DF080
const CString CRuleTables::MOD_INT("MOD_INT");

// 0x8DF138
const CString CRuleTables::MOD_WIS("MOD_WIS");

// 0x8DEE8C
const CString CRuleTables::MOD_CHR("MOD_CHR");

// #guess
// 0x8DF258
const CString CRuleTables::FORTITUDE("FORTITUDE");

// #guess
// 0x8DF0B8
const CString CRuleTables::REFLEX("REFLEX");

// #guess
// 0x8DEE80
const CString CRuleTables::WILL("WILL");

// 0x8DEE58
const CString CRuleTables::SIDES("SIDES");

// 0x8DF150
const CString CRuleTables::ROLLS("ROLLS");

// 0x8DF094
const CString CRuleTables::MODIFIER("MODIFIER");

// 0x8DEE24
const CString CRuleTables::OTHER("OTHER");

// 0x8DF040
const CString CRuleTables::MIN_ROLL("MIN_ROLL");

// 0x8DE994
const CString CRuleTables::MULTIPLIER("MULTIPLIER");

// #guess
// 0x8DF2B0
const CString CRuleTables::BONUS_PER_LEVEL("BONUS_PER_LEVEL");

// 0x8DEE5C
const CString CRuleTables::EFFECT_NAME("EFFECT_NAME");

// 0x8DF27C
const CString CRuleTables::STRREF_STR("STRREF");

// 0x8DF0B4
const CString CRuleTables::START_AREA("START_AREA");

// 0x8DE984
const CString CRuleTables::START_XPOS("START_XPOS");

// 0x8DF264
const CString CRuleTables::START_YPOS("START_YPOS");

// #guess
// 0x8DF278
const CString CRuleTables::START_AREA_EXPANSION("START_AREA_EXPANSION");

// #guess
// 0x8DEF40
const CString CRuleTables::START_XPOS_EXPANSION("START_XPOS_EXPANSION");

// #guess
// 0x8DEE34
const CString CRuleTables::START_YPOS_EXPANSION("START_YPOS_EXPANSION");

// 0x8DF2C0
const CString CRuleTables::VALUE("VALUE");

// #guess
// 0x8DF0AC
const CString CRuleTables::START_ROT_EXPANSION("START_ROT_EXPANSION");

// #guess
// 0x8DE960
const CString CRuleTables::START_ROT("START_ROT");

// 0x8DF218
const CString CRuleTables::SWITCH("SWITCH");

// 0x8DF260
const CString CRuleTables::DEFAULT("DEFAULT");

// 0x8DF208
const CString CRuleTables::RACE("RACE");

// 0x8DF1D4
const CString CRuleTables::CLASS("CLASS");

// 0x8DE9C4
const CString CRuleTables::REPUTATION("REPUTATION");

// 0x8DF0D0
const CString CRuleTables::NONE("NONE");

// 0x8DEE14
const CString CRuleTables::GOOD_REPUTATION("GOOD_REPUTATION");

// 0x8DE9E8
const CString CRuleTables::BAD_REPUTATION("BAD_REPUTATION");

// 0x8DEF24
const CString CRuleTables::GOOD_POWER("GOOD_POWER");

// 0x8DF288
const CString CRuleTables::BAD_POWER("BAD_POWER");

// 0x8DF01C
const CString CRuleTables::PLAYERINTERACTION_INSULT("i");

// 0x8DEFBC
const CString CRuleTables::PLAYERINTERACTION_COMPLIMENT("c");

// 0x8DE8D8
const CString CRuleTables::PLAYERINTERACTION_SPECIAL("s");

// 0x8DF1D8
const CString CRuleTables::PLAYERINTERACTION_EXTERNALFILE("*");

// 0x8DE98C
const CString CRuleTables::DAYS("DAYS");

// 0x8DF178
const CString CRuleTables::NAME("NAME");

// 0x8DF0F8
const CString CRuleTables::STARTTIME("STARTTIME");

// 0x8DEE64
const CString CRuleTables::STARTYEAR("STARTYEAR");

// 0x8DE8B4
const CString CRuleTables::NORMALDAYMONTHFORMAT("NORMALDAYMONTHFORMAT");

// 0x8DF250
const CString CRuleTables::SPECIALDAYMONTHFORMAT("SPECIALDAYMONTHFORMAT");

// 0x8DE978
const CString CRuleTables::POST_DIALOG_FILE("POST_DIALOG_FILE");

// 0x8DF098
const CString CRuleTables::JOIN_DIALOG_FILE("JOIN_DIALOG_FILE");

// 0x8DF030
const CString CRuleTables::MALE("MALE");

// 0x8DF0A4
const CString CRuleTables::FEMALE("FEMALE");

// 0x8DE918
const CString CRuleTables::INTERACTION_FILE("FILE");

// 0x8DEEFC
const CString CRuleTables::TOKEN_CLASS("CLASS");

// 0x8DF124
const CString CRuleTables::TOKEN_LEVEL("LEVEL");

// 0x8DE998
const CString CRuleTables::TOKEN_EXPERIENCE("EXPERIENCE");

// 0x8DE934
const CString CRuleTables::TOKEN_NEXTLEVEL("NEXTLEVEL");

// #guess
// 0x8DEEB8
const CString CRuleTables::XPPENALTY("XPPENALTY");

// 0x8DF0A0
const CString CRuleTables::TOKEN_SCRIPT("script");

// #guess
// 0x8DE8B0
const CString CRuleTables::CASTSPELL("CASTSPELL");

// #guess
// 0x8DF2AC
const CString CRuleTables::CLABFI05("CLABFI05");

// #guess
// 0x8DF21C
const CString CRuleTables::CLABBA01("CLABBA01");

// #guess
// 0x8DEF8C
const CString CRuleTables::CLABPR01("CLABPR01");

// #guess
// 0x8DE950
const CString CRuleTables::CLABCL01("CLABCL01");

// #guess
// 0x8DEE68
const CString CRuleTables::CLABCL02("CLABCL02");

// #guess
// 0x8DF274
const CString CRuleTables::CLABCL03("CLABCL03");

// #guess
// 0x8DEDF8
const CString CRuleTables::CLABCL04("CLABCL04");

// #guess
// 0x8DF1F0
const CString CRuleTables::CLABCL05("CLABCL05");

// #guess
// 0x8DEEE4
const CString CRuleTables::CLABCL06("CLABCL06");

// #guess
// 0x8DF06C
const CString CRuleTables::CLABCL07("CLABCL07");

// #guess
// 0x8DF284
const CString CRuleTables::CLABCL08("CLABCL08");

// #guess
// 0x8DF188
const CString CRuleTables::CLABCL09("CLABCL09");

// #guess
// 0x8DE8DC
const CString CRuleTables::CLABDR01("CLABDR01");

// #guess
// 0x8DE9B8
const CString CRuleTables::CLABFI01("CLABFI01");

// #guess
// 0x8DF268
const CString CRuleTables::CLABMO01("CLABMO01");

// #guess
// 0x8DE9A0
const CString CRuleTables::CLABPA01("CLABPA01");

// #guess
// 0x8DEE2C
const CString CRuleTables::CLABRN01("CLABRN01");

// #guess
// 0x8DEFE8
const CString CRuleTables::CLABTH01("CLABTH01");

// #guess
// 0x8DF0DC
const CString CRuleTables::CLABMA01("CLABMA01");

// #guess
// 0x8DEF04
const CString CRuleTables::CLABMA02("CLABMA02");

// #guess
// 0x8DE8F0
const CString CRuleTables::CLABMA06("CLABMA06");

// #guess
// 0x8DF214
const CString CRuleTables::CLABMA05("CLABMA05");

// #guess
// 0x8DE940
const CString CRuleTables::CLABMA07("CLABMA07");

// #guess
// 0x8DF16C
const CString CRuleTables::CLABMA09("CLABMA09");

// #guess
// 0x8DEE4C
const CString CRuleTables::CLABMA08("CLABMA08");

// #guess
// 0x8DEEA8
const CString CRuleTables::CLABMA03("CLABMA03");

// #guess
// 0x8DF02C
const CString CRuleTables::CLABMA04("CLABMA04");

// #guess
// 0x8DEED4
const CString CRuleTables::CLABSR01("CLABSR01");

// 0x8DF020
const CString CRuleTables::AUTOMATIC_SPELL_PICKER("SplAutoP");

// 0x8DF088
const CString CRuleTables::LOADING_HINTS("LoadHint");

// 0x8DF280
const CString CRuleTables::DUAL_CLASS_ALLOWED("DualClas");

// #guess
// 0x8DF2A0
const CString CRuleTables::BAATFGT("BAATFGT");

// #guess
// 0x8DF1B0
const CString CRuleTables::BAATNFG("BAATNFG");

// #guess
// 0x8DEED8
const CString CRuleTables::BAATMAG("BAATMAG");

// #guess
// 0x8DEE7C
const CString CRuleTables::BAATMKU("BAATMKU");

// #guess
// 0x8DE8FC
const CString CRuleTables::LISTSPLL("LISTSPLL");

// #guess
// 0x8DE9EC
const CString CRuleTables::LISTDOMN("LISTDOMN");

// #guess
// 0x8DF168
const CString CRuleTables::LISTINNT("LISTINNT");

// #guess
// 0x8DF298
const CString CRuleTables::LISTSONG("LISTSONG");

// #guess
// 0x8DEE04
const CString CRuleTables::LISTSHAP("LISTSHAP");

// #guess
// 0x8DEF94
const CString CRuleTables::CREHIDEM("CREHIDEM");

// #guess
// 0x8DEE94
const CString CRuleTables::CRELIGHT("CRELIGHT");

// #guess
// 0x8DEE1C
const CString CRuleTables::ITEMTEXT("ITEMTEXT");

// #guess
// 0x8DE9DC
const CString CRuleTables::ITEMABIL("ITEMABIL");

// #guess
// 0x8DF1C0
const CString CRuleTables::TRAPSAVE("TRAPSAVE");

// #guess
// 0x8DEF54
const CString CRuleTables::SPPR("SPPR");

// #guess
// 0x8DF074
const CString CRuleTables::SPWI("SPWI");

// #guess
// 0x8DF154
const CString CRuleTables::SPIN("SPIN");

// #guess
// 0x8DEFB4
const CString CRuleTables::SPWI110("SPWI110");

// #guess
// 0x8DF15C
const CString CRuleTables::BOW("BOW");

// #guess
// 0x8DF17C
const CString CRuleTables::CROSSBOW("CROSSBOW");

// #guess
// 0x8DEE88
const CString CRuleTables::MISSILE("MISSILE");

// #guess
// 0x8DF174
const CString CRuleTables::AXE("AXE");

// #guess
// 0x8DF29C
const CString CRuleTables::CLUBMACE("CLUBMACE");

// #guess
// 0x8DEF64
const CString CRuleTables::DAGGER("DAGGER");

// #guess
// 0x8DE90C
const CString CRuleTables::POLEARMS("POLEARMS");

// #guess
// 0x8DEF18
const CString CRuleTables::FLAIL("FLAIL");

// #guess
// 0x8DE944
const CString CRuleTables::HAMMER("HAMMER");

// #guess
// 0x8DF1A0
const CString CRuleTables::QUARTER_STAFF("QUARTER_STAFF");

// #guess
// 0x8DF014
const CString CRuleTables::GREAT_SWORD("GREAT_SWORD");

// #guess
// 0x8DEF2C
const CString CRuleTables::LARGE_SWORD("LARGE_SWORD");

// #guess
// 0x8DF2A4
const CString CRuleTables::SMALL_BLADE("SMALL_BLADE");

// #guess
// 0x8DE924
const CString CRuleTables::TWO_WEAPON("TWO_WEAPON");

// #guess
// 0x8DE968
const CString CRuleTables::TWO_HANDED("TWO_HANDED");

// #guess
// 0x8DF0F4
const CString CRuleTables::WEAPON_SHIELD("WEAPON_SHIELD");

// #guess
// 0x8DEE6C
const CString CRuleTables::SINGLE_WEAPON("SINGLE_WEAPON");

// 0x8DE9A4
const CString CRuleTables::TITLE("TITLE");

// 0x8DE9C0
const CString CRuleTables::CUSTOM("CUSTOM");

// 0x8DF1C8
const CString CRuleTables::DESCRIPTION("DESCRIPTION");

// 0x8DF05C
const CString CRuleTables::DEATH_SOUND_ENABLED("1");

// #guess
// 0x8DF120
const CString CRuleTables::FIRE("FIRE");

// #guess
// 0x8DEE30
const CString CRuleTables::COLD("COLD");

// #guess
// 0x8DF10C
const CString CRuleTables::ELEC("ELEC");

// #guess
// 0x8DEFF0
const CString CRuleTables::ACID("ACID");

// 0x8DF07C
const CString CRuleTables::SPELL("SPELL");

// #guess
// 0x8DEF10
const CString CRuleTables::MAGIC_FIRE("MAGIC_FIRE");

// #guess
// 0x8DF190
const CString CRuleTables::MAGIC_COLD("MAGIC_COLD");

// #guess
// 0x8DE8E4
const CString CRuleTables::SLASHING("SLASHING");

// #guess
// 0x8DE8C0
const CString CRuleTables::BLUDGEONING("BLUDGEONING");

// #guess
// 0x8DF0BC
const CString CRuleTables::PIERCING("PIERCING");

// #guess
// 0x8DEF6C
const CString CRuleTables::SPECIAL_ABILITIES_FILE("SPECIAL_ABILITIES_FILE");

// #guess
// 0x8DEFC0
const CString CRuleTables::MOD_XP("MOD_XP");

// #guess
// 0x8DEFC8
const CString CRuleTables::ENCUMBRANCE_MOD_PERCENT("ENCUMBRANCE_MOD_PERCENT");

// 0x8DEEAC
const CString CRuleTables::TOKEN_MAGESCHOOL("MAGESCHOOL");

// 0x8DEE44
const CString CRuleTables::TOKEN_FIGHTERTYPE("FIGHTERTYPE");

// #guess
// 0x8DEFE0
const CString CRuleTables::DLGINST("DLGINST");

// #guess
// 0x8DEF5C
const CString CRuleTables::SCRINST("SCRINST");

// NOTE: This function is somewhat strange. It's first half uses inlined
// `C2DArray` constructor, while the second half calls `0x5402E0` to initialize
// tables. The same goes for destructor below (destructor at `0x426500` is
// oddly placed between `CBaldurChitin` implementation). This is definitely not
// a coincedence, but I'm not sure how replicate that.
//
// 0x53CB60
CRuleTables::CRuleTables()
{
    m_tReactionModCharisma.Load(CResRef(REACTION_MOD_CHARISMA));
    m_tReactionModReputation.Load(CResRef(REACTION_MOD_REPUTATION));
    m_tReputationMod.Load(CResRef(REPUTATION_MOD));
    m_lNoDecodeList.LoadList(CResRef(NO_DECODE_LIST), FALSE);
    m_tFeats.Load(CResRef(FEATS));
    m_tSkills.Load(CResRef(SKILLS));
    m_tSkillPointsRace.Load(CResRef(SKILL_POINTS_RACE));
    m_tSkillPointsDex.Load(CResRef(SKILL_POINTS_DEX));
    m_tSkillPointsBard.Load(CResRef(SKILL_POINTS_BARD));
    m_tSkillPointsRanger.Load(CResRef(SKILL_POINTS_RANGER));
    m_tAbilityRaceReq.Load(CResRef(ABILITY_RACE_REQ));
    m_tAbilityRaceAdj.Load(CResRef(ABILITY_RACE_ADJ));
    m_tAbilityClassReq.Load(CResRef(ABILITY_CLASS_REQ));
    m_tMoncRate.Load(CResRef(MONCRATE));
    m_tSavingThrowPriest.Load(CResRef(SAVE_PRIEST));
    m_tSavingThrowWarrior.Load(CResRef(SAVE_WARRIOR));
    m_tSavingThrowWizard.Load(CResRef(SAVE_WIZARD));
    m_tSavingThrowRogue.Load(CResRef(SAVE_ROGUE));
    m_tSavingThrowBard.Load(CResRef(SAVE_BARD));
    m_tSavingThrowMonk.Load(CResRef(SAVE_MONK));
    m_tSavingThrowRace.Load(CResRef(SAVE_RACE));
    m_tHitPointsWarrior.Load(CResRef(HP_WARRIOR));
    m_tHitPointsWizard.Load(CResRef(HP_WIZARD));
    m_tHitPointsPriest.Load(CResRef(HP_PRIEST));
    m_tHitPointsRogue.Load(CResRef(HP_ROGUE));
    m_tHitPointsBarbarian.Load(CResRef(HP_BARBARIAN));
    m_tHitPointsMonk.Load(CResRef(HP_MONK));
    m_tStartingGold.Load(CResRef(STARTING_GOLD));
    m_tStartingExperiencePoints.Load(CResRef(STARTING_XP));
    m_tTHAC0.Load(CResRef(THAC0));
    m_tMaxSpellsBonus.Load(CResRef(MAX_SPELLS_BONUS));
    m_tMaxSpellsBard.Load(CResRef(MAX_SPELLS_BARD));
    m_tMaxSpellsCleric.Load(CResRef(MAX_SPELLS_CLERIC));
    m_tMaxSpellsDruid.Load(CResRef(MAX_SPELLS_DRUID));
    m_tMaxSpellsPaladin.Load(CResRef(MAX_SPELLS_PALADIN));
    m_tMaxSpellsRanger.Load(CResRef(MAX_SPELLS_RANGER));
    m_tMaxSpellsSorcerer.Load(CResRef(MAX_SPELLS_SORCERER));
    m_tMaxSpellsWizard.Load(CResRef(MAX_SPELLS_WIZARD));
    m_tKnownSpellsSorcerer.Load(CResRef(KNOWN_SPELLS_SORCERER));
    m_tKnownSpellsBard.Load(CResRef(KNOWN_SPELLS_BARD));
    m_tMaxDruidShapeshifts.Load(CResRef(MAX_DRUID_SHAPESHIFTS));
    m_tBackstabMultiplier.Load(CResRef(BACKSTAB_MULTIPLIER));
    m_tExperienceLevels.Load(CResRef(EXPERIENCE_LEVELS));
    m_tLayOnHandsAmount.Load(CResRef(LAY_ON_HANDS_AMOUNT));
    m_lInstantActions.LoadList(CResRef(INSTANT_ACTIONS), TRUE);

    // NOTE: Looks like there are no separate constants for some tables. At
    // least they are defenitely not `CString` instances.

    m_tMonsterSummon1.Load(CResRef("MSummo1"));
    m_tMonsterSummon2.Load(CResRef("MSummo2"));
    m_tMonsterSummon3.Load(CResRef("MSummo3"));
    m_tMonsterSummon4.Load(CResRef("MSummo4"));
    m_tMonsterSummon5.Load(CResRef("MSummo5"));
    m_tMonsterSummon6.Load(CResRef("MSummo6"));
    m_tMonsterSummonMalavon.Load(CResRef("MSummoM"));
    m_tMonsterSummon7.Load(CResRef("MSummo7"));
    m_tAnimalSummon1.Load(CResRef("ASummo1"));
    m_tAnimalSummon2.Load(CResRef("ASummo2"));
    m_tAnimalSummon3.Load(CResRef("ASummo3"));
    m_tSMonste.Load(CResRef("SMonste"));
    m_tDSMonste.Load(CResRef("DSMonste"));
    m_tShades.Load(CResRef("Shades"));
    m_tADead.Load(CResRef("aDead"));
    m_tADeadL.Load(CResRef("ADeadL"));
    m_tGInsect.Load(CResRef("GInsect"));
    m_tCDoom.Load(CResRef("CDoom"));
    m_tCFElemW.Load(CResRef("CFElemW"));
    m_tCEElemW.Load(CResRef("CEElemW"));
    m_tCEElemM.Load(CResRef("CEElemM"));
    m_tCWElemW.Load(CResRef("CWElemW"));
    m_tCFElemP.Load(CResRef("CFElemP"));
    m_tCEElemP.Load(CResRef("CEElemP"));
    m_tSShadow.Load(CResRef("SShadow"));
    m_tIStalke.Load(CResRef("IStalke"));
    m_tSTrolls.Load(CResRef("STrolls"));

    m_tStrengthMod.Load(CResRef(STRENGTH_MODIFIERS));
    m_tIntoxicationMod.Load(CResRef(INTOXICATION_MODIFIERS));
    m_tFatigueMod.Load(CResRef(FATIGUE_MODIFIERS));
    m_tEffectText.Load(CResRef(EFFECT_TEXT));
    m_tNumSpells.Load(CResRef(NUM_SPELLS));
    m_tToolTips.Load(CResRef(TOOLTIPS));
    m_tStartArea.Load(CResRef(START_AREA_FILE));
    m_tStartPos.Load(CResRef(START_POS_FILE));
    m_tSparkleColors.Load(CResRef(SPARKLE_COLOR_FILE));
    m_tYears.Load(CResRef(YEARS));
    m_tMonths.Load(CResRef(MONTHS));
    m_tPostDialog.Load(CResRef(POST_DIALOG));
    m_tCharacterSounds.Load(CResRef(CHARACTER_SOUNDS));
    m_tRtNorm.Load(CResRef(RT_NORM));
    m_tRtFury.Load(CResRef(RT_FURY));
    m_tIntelligenceMod.Load(CResRef(INTELLIGENCE_MODIFIERS));
    m_tDonateRumor.Load(CResRef(DONATE_RUMOR));
    m_tClassWeapon.Load(CResRef(CLASWEAP));
    m_tAreaLinkageCaching.Load(CResRef(AREA_LINKAGE_CACHING));
    m_tCacheValidation.Load(CResRef(CACHE_VALIDATION));
    m_tScriptDescription.Load(CResRef(SCRIPT_DESCRIPTION));
    m_tCharacterStateDescription.Load(CResRef(CHARACTER_STATE_DESCRIPTION));
    m_tMasterArea.Load(CResRef(MASTER_AREA));
    m_tMovieDescription.Load(CResRef(MOVIE_DESCRIPTION));
    m_tSpellDescription.Load(CResRef(SPELL_DESCRIPTION));
    m_tAlignment.Load(CResRef(ALIGNMENT));
    m_tReputationStoreMod.Load(CResRef(REPUTATION_STORE_MOD));
    m_tReputationStart.Load(CResRef(REPUTATION_START));
    m_tWeaponSpecialization.Load(CResRef(WEAPON_SPECIALIZATION));
    m_tWeaponAttacks.Load(CResRef(WEAPON_ATTACKS));
    m_tLore.Load(CResRef(LORE));
    m_tCharismaStoreMod.Load(CResRef(CHARISMA_STORE_MOD));
    m_tRaiseDeadCost.Load(CResRef(RAISE_DEAD_COST));
    m_tHappiness.Load(CResRef(HAPPINESS));
    m_tReputationDescription.Load(CResRef(REPUTATION_DESCRIPTION));
    m_tIntoxication.Load(CResRef(INTOXICATION));
    m_tCustomSound.Load(CResRef(CUSTOM_SOUND));
    m_tExclusiveItems.Load(CResRef(EXCLUSIVE_ITEMS));
    m_tFeatClass.Load(CResRef(FEATCLAS));
    m_tFeatLevel.Load(CResRef(FEATLVL));
    m_tSkillCosts.Load(CResRef(SKILLCOST));
    m_tSkillPoints.Load(CResRef(SKILLPTS));
    m_tSoundChannel.Load(CResRef("SNDCHANN"));
    m_tReverb.Load(CResRef("REVERB"));
    m_lEAXENVIR.LoadList(CResRef("EAXENVIR"), FALSE);
    m_tCharStr.Load(CResRef("CHARSTR"));
    m_tTracking.Load(CResRef("TRACKING"));
    m_tKitList.Load(CResRef(KIT_LIST));
    m_tSrTable.Load(CResRef(SR_TABLE));
    m_tSrList.Load(CResRef(SR_LIST));
    m_tRaceRsMd.Load(CResRef(RACERSMD));
    m_tRaceSpAb.Load(CResRef(RACESPAB));
    m_tEncMod.Load(CResRef(ENCMOD));
    m_tClassRsMd.Load(CResRef(CLSSRSMD));
    m_tQuickSlots.Load(CResRef(QSLOTS));
    m_tSpontaneousCasting.Load(CResRef(SPONCAST));
    m_tCLABFI05.Load(CResRef(CLABFI05));
    m_tCLABBA01.Load(CResRef(CLABBA01));
    m_tCLABPR01.Load(CResRef(CLABPR01));
    m_tCLABCL01.Load(CResRef(CLABCL01));
    m_tCLABCL02.Load(CResRef(CLABCL02));
    m_tCLABCL03.Load(CResRef(CLABCL03));
    m_tCLABCL04.Load(CResRef(CLABCL04));
    m_tCLABCL05.Load(CResRef(CLABCL05));
    m_tCLABCL06.Load(CResRef(CLABCL06));
    m_tCLABCL07.Load(CResRef(CLABCL07));
    m_tCLABCL08.Load(CResRef(CLABCL08));
    m_tCLABCL09.Load(CResRef(CLABCL09));
    m_tCLABDR01.Load(CResRef(CLABDR01));
    m_tCLABFI01.Load(CResRef(CLABFI01));
    m_tCLABMO01.Load(CResRef(CLABMO01));
    m_tCLABPA01.Load(CResRef(CLABPA01));
    m_tCLABRN01.Load(CResRef(CLABRN01));
    m_tCLABTH01.Load(CResRef(CLABTH01));
    m_tCLABSR01.Load(CResRef(CLABSR01));
    m_tCLABMA01.Load(CResRef(CLABMA01));
    m_tSpellAutomaticPicker.Load(CResRef(AUTOMATIC_SPELL_PICKER));
    m_tLoadingHints.Load(CResRef(LOADING_HINTS));
    m_tBAATFGT.Load(CResRef(BAATFGT));
    m_tBAATNFG.Load(CResRef(BAATNFG));
    m_tBAATMAG.Load(CResRef(BAATMAG));
    m_tBAATMKU.Load(CResRef(BAATMKU));
    m_lDLGINST.LoadList(CResRef(DLGINST), TRUE);
    m_lSCRINST.LoadList(CResRef(SCRINST), TRUE);
    m_tCREHIDEM.Load(CResRef(CREHIDEM));
    m_tCRELIGHT.Load(CResRef(CRELIGHT));
    m_tItemText.Load(CResRef(ITEMTEXT));
    m_tItemAbility.Load(CResRef(ITEMABIL));
    m_tTrapSave.Load(CResRef(TRAPSAVE));
    m_tAreaLoad.Load(CResRef("AREALOAD"));
    m_tHelp01.Load(CResRef(HELP01));
    m_tHelp02.Load(CResRef(HELP02));
    m_tHelp03.Load(CResRef(HELP03));
    m_tHelp04.Load(CResRef(HELP04));
}

// NOTE: See constructor for some oddities in this function. Destructor itself
// is completely synthesized.
//
// 0x540330
CRuleTables::~CRuleTables()
{
}

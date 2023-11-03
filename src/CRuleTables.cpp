#include "CRuleTables.h"

#include "CAIObjectType.h"
#include "CBaldurChitin.h"
#include "CDerivedStats.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CTimerWorld.h"
#include "CUtil.h"

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

// 0x8DF2AC
const CString CRuleTables::CLASS_ABILITIES_BARBARIAN("CLABFI05");

// 0x8DF21C
const CString CRuleTables::CLASS_ABILITIES_BARD("CLABBA01");

// 0x8DEF8C
const CString CRuleTables::CLASS_ABILITIES_CLERIC_TRUE("CLABPR01");

// 0x8DE950
const CString CRuleTables::CLASS_ABILITIES_CLERIC_ILMATER("CLABCL01");

// 0x8DEE68
const CString CRuleTables::CLASS_ABILITIES_CLERIC_LATHANDER("CLABCL02");

// 0x8DF274
const CString CRuleTables::CLASS_ABILITIES_CLERIC_SELUNE("CLABCL03");

// 0x8DEDF8
const CString CRuleTables::CLASS_ABILITIES_CLERIC_HELM("CLABCL04");

// 0x8DF1F0
const CString CRuleTables::CLASS_ABILITIES_CLERIC_OGHMA("CLABCL05");

// 0x8DEEE4
const CString CRuleTables::CLASS_ABILITIES_CLERIC_TEMPUS("CLABCL06");

// 0x8DF06C
const CString CRuleTables::CLASS_ABILITIES_CLERIC_BANE("CLABCL07");

// 0x8DF284
const CString CRuleTables::CLASS_ABILITIES_CLERIC_MASK("CLABCL08");

// 0x8DF188
const CString CRuleTables::CLASS_ABILITIES_CLERIC_TALOS("CLABCL09");

// 0x8DE8DC
const CString CRuleTables::CLASS_ABILITIES_DRUID("CLABDR01");

// 0x8DE9B8
const CString CRuleTables::CLASS_ABILITIES_FIGHTER("CLABFI01");

// 0x8DF268
const CString CRuleTables::CLASS_ABILITIES_MONK("CLABMO01");

// 0x8DE9A0
const CString CRuleTables::CLASS_ABILITIES_PALADIN("CLABPA01");

// 0x8DEE2C
const CString CRuleTables::CLASS_ABILITIES_RANGER("CLABRN01");

// 0x8DEFE8
const CString CRuleTables::CLASS_ABILITIES_ROGUE("CLABTH01");

// 0x8DF0DC
const CString CRuleTables::CLASS_ABILITIES_WIZARD("CLABMA01");

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

// 0x8DEED4
const CString CRuleTables::CLASS_ABILITIES_SORCERER("CLABSR01");

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
    m_lEAXEnvironment.LoadList(CResRef("EAXENVIR"), FALSE);
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
    m_tClassAbilitiesBarbarian.Load(CResRef(CLASS_ABILITIES_BARBARIAN));
    m_tClassAbilitiesBard.Load(CResRef(CLASS_ABILITIES_BARD));
    m_tClassAbilitiesClericTrue.Load(CResRef(CLASS_ABILITIES_CLERIC_TRUE));
    m_tClassAbilitiesClericIlmater.Load(CResRef(CLASS_ABILITIES_CLERIC_ILMATER));
    m_tClassAbilitiesClericLathander.Load(CResRef(CLASS_ABILITIES_CLERIC_LATHANDER));
    m_tClassAbilitiesClericSelune.Load(CResRef(CLASS_ABILITIES_CLERIC_SELUNE));
    m_tClassAbilitiesClericHelm.Load(CResRef(CLASS_ABILITIES_CLERIC_HELM));
    m_tClassAbilitiesClericOghma.Load(CResRef(CLASS_ABILITIES_CLERIC_OGHMA));
    m_tClassAbilitiesClericTempus.Load(CResRef(CLASS_ABILITIES_CLERIC_TEMPUS));
    m_tClassAbilitiesClericBane.Load(CResRef(CLASS_ABILITIES_CLERIC_BANE));
    m_tClassAbilitiesClericMask.Load(CResRef(CLASS_ABILITIES_CLERIC_MASK));
    m_tClassAbilitiesClericTalos.Load(CResRef(CLASS_ABILITIES_CLERIC_TALOS));
    m_tClassAbilitiesDruid.Load(CResRef(CLASS_ABILITIES_DRUID));
    m_tClassAbilitiesFighter.Load(CResRef(CLASS_ABILITIES_FIGHTER));
    m_tClassAbilitiesMonk.Load(CResRef(CLASS_ABILITIES_MONK));
    m_tClassAbilitiesPaladin.Load(CResRef(CLASS_ABILITIES_PALADIN));
    m_tClassAbilitiesRanger.Load(CResRef(CLASS_ABILITIES_RANGER));
    m_tClassAbilitiesRogue.Load(CResRef(CLASS_ABILITIES_ROGUE));
    m_tClassAbilitiesSorcerer.Load(CResRef(CLASS_ABILITIES_SORCERER));
    m_tClassAbilitiesWizard.Load(CResRef(CLASS_ABILITIES_WIZARD));
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

// Returns `TRUE` if item appears in `itemabil.2da` which contains a list of
// item resrefs for which the engine should validate minimum level and
// ability requirements.
//
// 0x541840
BOOL CRuleTables::ShouldCheckItemRequirements(CItem* pItem) const
{
    CPoint ptLocation(0, 0);
    CString sResRef = pItem->GetResRef().GetResRefStr();

    if (m_tItemAbility.Find(sResRef, ptLocation, TRUE) == TRUE) {
        return TRUE;
    }

    return FALSE;
}

// 0x5418E0
INT CRuleTables::GetTrapSenseBonus(CDerivedStats& DStats) const
{
    INT nBonus = 0;
    CPoint pt(0, 0);
    for (int iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        pt.y = DStats.GetClassLevel(iClassType) - 1;
        pt.x = iClassType - 1;
        nBonus += m_tTrapSave.GetAtLong(pt);
    }
    return nBonus;
}

// 0x541940
const CString CRuleTables::GetRaceString(BYTE nRace, BYTE nSubRace) const
{
    switch (nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (nSubRace) {
        case 0:
            return HUMAN;
        case 1:
            return HUMAN_AASIMAR;
        case 2:
            return HUMAN_TIEFLING;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1062
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_ELF:
        switch (nSubRace) {
        case 0:
            return ELF;
        case 1:
            return ELF_DROW;
        case 2:
            return ELF_WILD;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1080
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_HALF_ELF:
        switch (nSubRace) {
        case 0:
            return HALF_ELF;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1086
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_DWARF:
        switch (nSubRace) {
        case 0:
            return DWARF;
        case 1:
            return DWARF_GOLD;
        case 2:
            return DWARF_GRAY;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1103
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_HALFLING:
        switch (nSubRace) {
        case 0:
            return HALFLING;
        case 1:
            return HALFLING_STRONGHEART;
        case 2:
            return HALFLING_GHOSTWISE;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1121
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_GNOME:
        switch (nSubRace) {
        case 0:
            return GNOME;
        case 1:
            return GNOME_DEEP;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1136
        UTIL_ASSERT(FALSE);
    case CAIOBJECTTYPE_R_HALF_ORC:
        switch (nSubRace) {
        case 0:
            return HALF_ORC;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 1142
        UTIL_ASSERT(FALSE);
    }

    return CString("");
}

// 0x541C20
const CString CRuleTables::GetAlignmentString(BYTE nAlignment) const
{
    switch (nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_GOOD:
        return LAWFUL_GOOD;
    case CAIOBJECTTYPE_LAWFUL_NEUTRAL:
        return LAWFUL_NEUTRAL;
    case CAIOBJECTTYPE_LAWFUL_EVIL:
        return LAWFUL_EVIL;
    case CAIOBJECTTYPE_NEUTRAL_GOOD:
        return NEUTRAL_GOOD;
    case CAIOBJECTTYPE_NEUTRAL:
        return NEUTRAL;
    case CAIOBJECTTYPE_NEUTRAL_EVIL:
        return NEUTRAL_EVIL;
    case CAIOBJECTTYPE_CHAOTIC_GOOD:
        return CHAOTIC_GOOD;
    case CAIOBJECTTYPE_CHAOTIC_NEUTRAL:
        return CHAOTIC_NEUTRAL;
    case CAIOBJECTTYPE_CHAOTIC_EVIL:
        return CHAOTIC_EVIL;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
    // __LINE__: 1354
    UTIL_ASSERT(FALSE);
}

// 0x541DA0
const CString CRuleTables::GetClassString(BYTE nClass, DWORD nSpecialist) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        return BARBARIAN;
    case CAIOBJECTTYPE_C_BARD:
        return BARD;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nSpecialist & SPECMASK_CLERIC) {
        case SPECMASK_CLERIC_ILMATER:
            return CLERIC_ILMATER;
        case SPECMASK_CLERIC_LATHANDER:
            return CLERIC_LATHANDER;
        case SPECMASK_CLERIC_SELUNE:
            return CLERIC_SELUNE;
        case SPECMASK_CLERIC_HELM:
            return CLERIC_HELM;
        case SPECMASK_CLERIC_OGHMA:
            return CLERIC_OGHMA;
        case SPECMASK_CLERIC_TEMPUS:
            return CLERIC_TEMPUS;
        case SPECMASK_CLERIC_BANE:
            return CLERIC_BANE;
        case SPECMASK_CLERIC_MASK:
            return CLERIC_MASK;
        case SPECMASK_CLERIC_TALOS:
            return CLERIC_TALOS;
        }

        return CLERIC;
    case CAIOBJECTTYPE_C_DRUID:
        return DRUID;
    case CAIOBJECTTYPE_C_FIGHTER:
        return FIGHTER;
    case CAIOBJECTTYPE_C_MONK:
        switch (nSpecialist & SPECMASK_MONK) {
        case SPECMASK_MONK_OLD_ORDER:
            return MONK_OLD_ORDER;
        case SPECMASK_MONK_BROKEN_ONES:
            return MONK_BROKEN_ONES;
        case SPECMASK_MONK_DARK_MOON:
            return MONK_DARK_MOON;
        }

        return MONK;
    case CAIOBJECTTYPE_C_PALADIN:
        switch (nSpecialist & SPECMASK_PALADIN) {
        case SPECMASK_PALADIN_ILMATER:
            return PALADIN_ILMATER;
        case SPECMASK_PALADIN_HELM:
            return PALADIN_HELM;
        case SPECMASK_PALADIN_MYSTRA:
            return PALADIN_MYSTRA;
        }

        return PALADIN;
    case CAIOBJECTTYPE_C_RANGER:
        return RANGER;
    case CAIOBJECTTYPE_C_ROGUE:
        return ROGUE;
    case CAIOBJECTTYPE_C_SORCERER:
        return SORCERER;
    case CAIOBJECTTYPE_C_WIZARD:
        switch (nSpecialist & SPECMASK_WIZARD) {
        case SPECMASK_WIZARD_ABJURER:
            return WIZARD_ABJURER;
        case SPECMASK_WIZARD_CONJURER:
            return WIZARD_CONJURER;
        case SPECMASK_WIZARD_DIVINER:
            return WIZARD_DIVINER;
        case SPECMASK_WIZARD_ENCHANTER:
            return WIZARD_ENCHANTER;
        case SPECMASK_WIZARD_ILLUSIONIST:
            return WIZARD_ILLUSIONIST;
        case SPECMASK_WIZARD_EVOKER:
            return WIZARD_EVOKER;
        case SPECMASK_WIZARD_NECROMANCER:
            return WIZARD_NECROMANCER;
        case SPECMASK_WIZARD_TRANSMUTER:
            return WIZARD_TRANSMUTER;
        }
        return WIZARD;
    }

    return CString("");
}

// TODO: Figure out when it is actually used, maybe needs a better name.
//
// 0x5421F0
STRREF CRuleTables::GetClassSuffixStringRef(BYTE nClass) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
        // " - Bard "
        return 39734;
    case CAIOBJECTTYPE_C_CLERIC:
        // " - Cleric "
        return 39736;
    case CAIOBJECTTYPE_C_DRUID:
        // " - Druid "
        return 39737;
    case CAIOBJECTTYPE_C_PALADIN:
        // " - Paladin "
        return 39738;
    case CAIOBJECTTYPE_C_RANGER:
        // " - Ranger "
        return 39739;
    case CAIOBJECTTYPE_C_SORCERER:
        // " - Sorcerer "
        return 39740;
    case CAIOBJECTTYPE_C_WIZARD:
        // " - Wizard "
        return 39741;
    }

    return -1;
}

// TODO: Definitely needs a better name.
//
// 0x542270
STRREF CRuleTables::GetClassBeyondCastingAbilityStringRef(BYTE nClass) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
        // " Beyond Bard Casting Ability"
        return 39804;
    case CAIOBJECTTYPE_C_CLERIC:
        // " Beyond Cleric Casting Ability"
        return 39806;
    case CAIOBJECTTYPE_C_DRUID:
        // " Beyond Druid Casting Ability"
        return 39807;
    case CAIOBJECTTYPE_C_PALADIN:
        // " Beyond Paladin Casting Ability"
        return 39808;
    case CAIOBJECTTYPE_C_RANGER:
        // " Beyond Ranger Casting Ability"
        return 39809;
    case CAIOBJECTTYPE_C_SORCERER:
        // " Beyond Sorcerer Casting Ability"
        return 39810;
    case CAIOBJECTTYPE_C_WIZARD:
        // " Beyond Wizard Casting Ability"
        return 39811;
    }

    return -1;
}

// 0x5422F0
STRREF CRuleTables::GetClassDescriptionStringRef(BYTE nClass, DWORD nSpecialist) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        // BARBARIAN
        return 37;
    case CAIOBJECTTYPE_C_BARD:
        // BARD
        return 9562;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nSpecialist & SPECMASK_CLERIC) {
        case SPECMASK_CLERIC_ILMATER:
            // PAINBEARER OF ILMATER
            return 38118;
        case SPECMASK_CLERIC_LATHANDER:
            // MORNINGLORD OF LATHANDER
            return 38119;
        case SPECMASK_CLERIC_SELUNE:
            // SILVERSTAR OF SELUNE
            return 38120;
        case SPECMASK_CLERIC_HELM:
            // WATCHER OF HELM
            return 38121;
        case SPECMASK_CLERIC_OGHMA:
            // LOREKEEPER OF OGHMA
            return 38122;
        case SPECMASK_CLERIC_TEMPUS:
            // BATTLEGUARD OF TEMPUS
            return 38123;
        case SPECMASK_CLERIC_BANE:
            // DREADMASTER OF BANE
            return 38124;
        case SPECMASK_CLERIC_MASK:
            // DEMARCH OF MASK
            return 38125;
        case SPECMASK_CLERIC_TALOS:
            // STORMLORD OF TALOS
            return 38126;
        }

        // CLERIC
        return 9559;
    case CAIOBJECTTYPE_C_DRUID:
        // DRUID
        return 9560;
    case CAIOBJECTTYPE_C_FIGHTER:
        // FIGHTER
        return 9556;
    case CAIOBJECTTYPE_C_MONK:
        switch (nSpecialist & SPECMASK_MONK) {
        case SPECMASK_MONK_OLD_ORDER:
            // MONK OF THE OLD ORDER
            return 39410;
        case SPECMASK_MONK_BROKEN_ONES:
            // MONK OF THE BROKEN ONES
            return 39411;
        case SPECMASK_MONK_DARK_MOON:
            // MONK OF THE DARK MOON
            return 39412;
        }

        // MONK
        return 36;
    case CAIOBJECTTYPE_C_PALADIN:
        switch (nSpecialist & SPECMASK_PALADIN) {
        case SPECMASK_PALADIN_ILMATER:
            // PALADIN OF ILMATER
            return 39407;
        case SPECMASK_PALADIN_HELM:
            // PALADIN OF HELM
            return 39408;
        case SPECMASK_PALADIN_MYSTRA:
            // PALADIN OF MYSTRA
            return 39409;
        }

        // PALADIN
        return 9558;
    case CAIOBJECTTYPE_C_RANGER:
        // RANGER
        return 9557;
    case CAIOBJECTTYPE_C_ROGUE:
        // ROGUE
        return 9561;
    case CAIOBJECTTYPE_C_SORCERER:
        // SORCERER
        return 35;
    case CAIOBJECTTYPE_C_WIZARD:
        switch (nSpecialist & SPECMASK_WIZARD) {
        case SPECMASK_WIZARD_ABJURER:
            // ABJURER
            return 9564;
        case SPECMASK_WIZARD_CONJURER:
            // CONJURER
            return 9565;
        case SPECMASK_WIZARD_DIVINER:
            // DIVINER
            return 9566;
        case SPECMASK_WIZARD_ENCHANTER:
            // ENCHANTER
            return 9567;
        case SPECMASK_WIZARD_ILLUSIONIST:
            // ILLUSIONIST
            return 9568;
        case SPECMASK_WIZARD_EVOKER:
            // EVOKER
            return 9569;
        case SPECMASK_WIZARD_NECROMANCER:
            // NECROMANCER
            return 9570;
        case SPECMASK_WIZARD_TRANSMUTER:
            // TRANSMUTER
            return 9571;
        }

        // WIZARD
        return 9563;
    }

    return -1;
}

// 0x542510
INT CRuleTables::GetAbilityScoreModifier(INT nScore) const
{
    float fScore;
    if (nScore < 10) {
        fScore = static_cast<float>(nScore) - 1.0f;
    } else {
        fScore = static_cast<float>(nScore);
    }
    return static_cast<INT>((fScore - 10.0f) / 2.0f);
}

// 0x542560
int CRuleTables::sub_542560(unsigned short a1, unsigned short a2) const
{
    if (a1 == 0) {
        return 0;
    }

    if (a2 == 0) {
        a2 = 1;
    }

    return atol(m_tMoncRate.GetAt(CPoint(a1 - 1, a2 - 1)));
}

// 0x5425E0
void CRuleTables::GetBaseSkillPoints(const CAIObjectType& typeAI, CDerivedStats& DStats, BYTE& nPickPockets, BYTE& nOpenLocks, BYTE& nFindTraps, BYTE& nMoveSilently, BYTE& nHide, BYTE& nUseMagicDevice) const
{
    nPickPockets = 0x80;
    nOpenLocks = 0x80;
    nFindTraps = 0x80;
    nMoveSilently = 0x80;
    nHide = 0x80;
    nUseMagicDevice = 0x80;
}

// 0x542610
INT CRuleTables::FindSavingThrow(CDerivedStats& DStats, const CString& sSavingThrow) const
{

    CString sLevel;
    int nLevel;
    INT nSavingThrow = 0;

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_BARBARIAN);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWarrior.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_BARD);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowBard.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowPriest.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_DRUID);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowPriest.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_FIGHTER);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWarrior.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_MONK);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowMonk.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWarrior.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWarrior.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_ROGUE);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowRogue.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_SORCERER);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWizard.GetAt(sSavingThrow, sLevel));
    }

    nLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_WIZARD);
    if (nLevel != 0) {
        sLevel.Format("%d", nLevel);
        nSavingThrow += atol(m_tSavingThrowWizard.GetAt(sSavingThrow, sLevel));
    }

    return nSavingThrow;
}

// 0x5429B0
INT CRuleTables::GetSavingThrow(const CAIObjectType& typeAI, CDerivedStats& DStats, BYTE nCON, const CString& sSavingThrow) const
{
    INT nSavingThrow = FindSavingThrow(DStats, sSavingThrow);

    CString sRace = GetRaceString(typeAI.m_nRace, typeAI.m_nSubRace);
    nSavingThrow += atol(m_tSavingThrowRace.GetAt(sSavingThrow, sRace));

    nSavingThrow = min(nSavingThrow, 40);
    nSavingThrow = max(nSavingThrow, -40);
    return nSavingThrow;
}

// 0x542FA0
INT CRuleTables::GetStartingHitPoints(const CAIObjectType& typeAI, CDerivedStats& DStats, BYTE nCON) const
{
    // TODO: Incomplete.

    return 0;
}

// 0x542FE0
INT CRuleTables::GetStartingGold(CGameSprite* pSprite) const
{
    INT nGold = 0;

    INT nBestClass = pSprite->m_derivedStats.GetBestClass();
    CString sBestClass = GetClassString(nBestClass, 0);

    INT nSides = atol(m_tStartingGold.GetAt(SIDES, sBestClass));
    INT nRolls = atol(m_tStartingGold.GetAt(ROLLS, sBestClass));
    INT nModifier = atol(m_tStartingGold.GetAt(MODIFIER, sBestClass));
    INT nMultiplier = atol(m_tStartingGold.GetAt(MULTIPLIER, sBestClass));

    while (nRolls > 0) {
        nGold += nModifier + rand() % nSides + 1;
        nRolls--;
    }

    nGold *= nMultiplier;

    DWORD nBestClassLevel = pSprite->m_derivedStats.GetClassLevel(nBestClass);
    if (nBestClassLevel > 1) {
        nGold += atol(m_tStartingGold.GetAt(BONUS_PER_LEVEL, sBestClass)) * (nBestClassLevel - 1);
    }

    return nGold;
}

// 0x543140
INT CRuleTables::GetStartingExperiencePoints(CGameSprite* pSprite) const
{
    CString sRace = GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    return atol(m_tStartingExperiencePoints.GetAt(VALUE, sRace));
}

// 0x5431E0
INT CRuleTables::GetMaxKnownSpells(const BYTE& nClass, const CAIObjectType& typeAI, CDerivedStats& DStats, DWORD nSpecialization, UINT nSpellLevel, INT& nBonus) const
{
    CString sSpellLevel;
    CString sClassLevel;
    CString sAbility;

    sSpellLevel.Format("%d", nSpellLevel);

    nBonus = 0;
    INT nMaxSpells = 0;
    INT nValue;

    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
    case CAIOBJECTTYPE_C_SORCERER:
        sAbility.Format("%d", DStats.m_nCHR);
        break;
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        sAbility.Format("%d", DStats.m_nWIS);
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        sAbility.Format("%d", DStats.m_nINT);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 2886
        UTIL_ASSERT(FALSE);
    }

    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
        if ((typeAI.m_nClassMask & CLASSMASK_BARD) != 0) {
            sClassLevel.Format("%d", DStats.GetClassLevel(CAIOBJECTTYPE_C_BARD));
            nValue = atol(m_tMaxSpellsBard.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        if ((typeAI.m_nClassMask & CLASSMASK_CLERIC) != 0) {
            // NOTE: Unusual case - uses `GetClassMaskLevel` instead of
            // `GetClassLevel` in other branches.
            sClassLevel.Format("%d", DStats.GetClassMaskLevel(CLASSMASK_CLERIC));
            nValue = atol(m_tMaxSpellsCleric.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_DRUID:
        if ((typeAI.m_nClassMask & CLASSMASK_DRUID) != 0) {
            // NOTE: Unusual case - uses `GetClassMaskLevel` instead of
            // `GetClassLevel` in other branches.
            sClassLevel.Format("%d", DStats.GetClassMaskLevel(CLASSMASK_DRUID));
            nValue = atol(m_tMaxSpellsDruid.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        if ((typeAI.m_nClassMask & CLASSMASK_PALADIN) != 0) {
            sClassLevel.Format("%d", DStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN));
            nValue = atol(m_tMaxSpellsPaladin.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_RANGER:
        if ((typeAI.m_nClassMask & CLASSMASK_RANGER) != 0) {
            sClassLevel.Format("%d", DStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER));
            nValue = atol(m_tMaxSpellsRanger.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        if ((typeAI.m_nClassMask & CLASSMASK_SORCERER) != 0) {
            sClassLevel.Format("%d", DStats.GetClassLevel(CAIOBJECTTYPE_C_SORCERER));
            nValue = atol(m_tMaxSpellsSorcerer.GetAt(sSpellLevel, sClassLevel));
            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        if ((typeAI.m_nClassMask & CLASSMASK_WIZARD) != 0) {
            sClassLevel.Format("%d", DStats.GetClassLevel(CAIOBJECTTYPE_C_WIZARD));
            nValue = atol(m_tMaxSpellsWizard.GetAt(sSpellLevel, sClassLevel));

            if ((nSpecialization & SPECMASK_WIZARD_UNIVERSAL) == 0 && nValue > 0) {
                nValue++;
            }

            if (nValue > nBonus) {
                nMaxSpells = nValue;
                nBonus = 0;

                if (nValue > 0) {
                    nBonus = atol(m_tMaxSpellsBonus.GetAt(sSpellLevel, sAbility));
                }
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 3043
        UTIL_ASSERT(FALSE);
    }

    return nMaxSpells;
}

// 0x543770
INT CRuleTables::GetMaxDruidShapeshifts(CCreatureFileHeader& BStats, INT nLevel) const
{
    INT nShapeshifts = 0;

    if (BStats.m_druidLevel != 0) {
        nShapeshifts = atol(m_tMaxDruidShapeshifts.GetAt(CPoint(nLevel - 1, 0)));

        if (nShapeshifts != 0) {
            nShapeshifts += BStats.m_featExtraShapeshifting;
        }
    }

    return nShapeshifts;
}

// 0x5437E0
void CRuleTables::GetNextLevel(BYTE nClass, CDerivedStats& DStats, CGameSprite* pSprite) const
{
    int v1 = DStats.m_nLevel;
    int v2 = DStats.GetXP();
    int v3 = 0;

    if (pSprite != NULL && v2 != 0) {
        v3 = pSprite->GetEffectiveCharacterLevel() - v1;
    }

    int xp;
    do {
        v1++;
        xp = atol(m_tExperienceLevels.GetAt(CPoint(v1 + v3 - 1, 0)));
    } while (v2 >= xp && xp != -1);

    BYTE nClassLevel = static_cast<BYTE>(DStats.GetClassLevel(nClass));

    v1--;
    if (v1 >= 30) {
        v1 = 30;
    }

    DStats.SetClassLevel(nClass, nClassLevel + (v1 - DStats.m_nLevel));
}

// NOTE: Even though `xplevel.2da` contains entries for all classes, only
// `FIGHTER` is used to determine XP progression. This is leftover from earlier
// 2E games where every class has it's own progression.
//
// 0x5438D0
DWORD CRuleTables::GetNextLevelXP(BYTE nLevel) const
{
    CString sClassName;

    sClassName = GetClassString(CAIOBJECTTYPE_C_FIGHTER, 0);

    char szLevel[80];
    sprintf(szLevel, "%d", nLevel);

    return atol(m_tExperienceLevels.GetAt(CString(szLevel), sClassName));
}

// 0x5439B0
void CRuleTables::GetStartArea(CResRef& cResArea, CPoint& ptView) const
{
    if (g_pBaldurChitin->GetObjectGame()->m_bExpansion == TRUE) {
        cResArea = m_tStartArea.GetAt(VALUE, START_AREA_EXPANSION);
        ptView.x = atol(m_tStartArea.GetAt(VALUE, START_XPOS_EXPANSION));
        ptView.y = atol(m_tStartArea.GetAt(VALUE, START_YPOS_EXPANSION));
    } else {
        cResArea = m_tStartArea.GetAt(VALUE, START_AREA);
        ptView.x = atol(m_tStartArea.GetAt(VALUE, START_XPOS));
        ptView.y = atol(m_tStartArea.GetAt(VALUE, START_YPOS));
    }
}

// 0x543A90
CPoint CRuleTables::GetStartPoint(INT nCharacterSlot) const
{
    CPoint ptStart;
    CString sSlot;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
    // __LINE__: 3320
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    sSlot.Format("%d", nCharacterSlot + 1);

    if (g_pBaldurChitin->GetObjectGame()->m_bExpansion == TRUE) {
        ptStart.x = atol(m_tStartPos.GetAt(sSlot, START_XPOS_EXPANSION));
        ptStart.y = atol(m_tStartPos.GetAt(sSlot, START_YPOS_EXPANSION));
    } else {
        ptStart.x = atol(m_tStartPos.GetAt(sSlot, START_XPOS));
        ptStart.y = atol(m_tStartPos.GetAt(sSlot, START_YPOS));
    }

    return ptStart;
}

// 0x543BB0
int CRuleTables::GetStartRotation(INT nCharacterSlot) const
{
    int rotation;
    CString sSlot;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
    // __LINE__: 3346
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    sSlot.Format("%d", nCharacterSlot + 1);

    if (g_pBaldurChitin->GetObjectGame()->m_bExpansion == TRUE) {
        rotation = atol(m_tStartPos.GetAt(sSlot, START_ROT_EXPANSION));
    } else {
        rotation = atol(m_tStartPos.GetAt(sSlot, START_ROT));
    }

    return rotation;
}

// 0x543C80
CList<STRREF, STRREF>* CRuleTables::GetChapterText(const CResRef& cResText, BYTE nChapter) const
{
    C2DArray tText;
    tText.Load(cResText);

    CList<STRREF, STRREF>* pTextList = new CList<STRREF, STRREF>();

    if (nChapter == -1) {
        // NOTE: Uninline.
        nChapter = g_pBaldurChitin->GetObjectGame()->GetCurrentChapter();
    }

    pTextList->AddTail(tText.GetAtLong(CPoint(0, nChapter + 1)));
    pTextList->AddTail(tText.GetAtLong(CPoint(1, nChapter + 1)));

    return pTextList;
}

// 0x543EB0
void CRuleTables::GetClassStringLower(BYTE nClass, DWORD nSpecialist, DWORD dwFlags, CString& sClass, int a5) const
{
    STR_RES strRes;

    STRREF strMageSchool;
    switch (nSpecialist & SPECMASK_WIZARD) {
    case SPECMASK_WIZARD_ABJURER:
        strMageSchool = 597; // "Abjurer"
        break;
    case SPECMASK_WIZARD_CONJURER:
        strMageSchool = 2179; // "Conjurer"
        break;
    case SPECMASK_WIZARD_DIVINER:
        strMageSchool = 2846; // "Diviner"
        break;
    case SPECMASK_WIZARD_ENCHANTER:
        strMageSchool = 2861; // "Enchanter"
        break;
    case SPECMASK_WIZARD_ILLUSIONIST:
        strMageSchool = 2862; // "Illusionist"
        break;
    case SPECMASK_WIZARD_EVOKER:
        strMageSchool = 3015; // "Evoker"
        break;
    case SPECMASK_WIZARD_NECROMANCER:
        strMageSchool = 12744; // "Necromancer"
        break;
    case SPECMASK_WIZARD_TRANSMUTER:
        strMageSchool = 12745; // "Transmuter"
        break;
    case SPECMASK_WIZARD_UNIVERSAL:
        strMageSchool = 18039; // "Wizard"
        break;
    default:
        strMageSchool = -1;
        break;
    }

    if (strMageSchool != -1) {
        g_pBaldurChitin->GetTlkTable().Fetch(strMageSchool, strRes);
        g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_MAGESCHOOL, strRes.szText);
    }

    STRREF strFighterType;
    if ((dwFlags & 0x200) != 0) {
        strFighterType = 10367; // "fallen paladin"
    } else if ((dwFlags & 0x400) != 0) {
        strFighterType = 10365; // "fallen ranger"
    } else {
        strFighterType = 10086; // "Fighter"
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strFighterType, strRes);
    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_FIGHTERTYPE, strRes.szText);

    STRREF strClass;
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        strClass = 31; // "Barbarian"
        break;
    case CAIOBJECTTYPE_C_BARD:
        strClass = 7206; // "Bard"
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        strClass = 7204; // "Cleric"
        break;
    case CAIOBJECTTYPE_C_DRUID:
        strClass = 7210; // "Druid"
        break;
    case CAIOBJECTTYPE_C_FIGHTER:
        strClass = 7201; // "<FIGHTERTYPE>"
        break;
    case CAIOBJECTTYPE_C_MONK:
        strClass = 30; // "Monk"
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        strClass = 7217; // "Paladin"
        break;
    case CAIOBJECTTYPE_C_RANGER:
        strClass = 7200; // "Ranger"
        break;
    case CAIOBJECTTYPE_C_ROGUE:
        strClass = 7202; // "Rogue"
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        strClass = 29; // "Sorcerer"
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        strClass = 7203; // "<MAGESCHOOL>"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 3690
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strClass, strRes);
    sClass = strRes.szText;
}

// 0x544120
void CRuleTables::GetClassStringMixed(BYTE nClass, DWORD nSpecialist, DWORD dwFlags, CString& sClass, int a5) const
{
    STR_RES strRes;

    STRREF strMageSchool;
    switch (nSpecialist & SPECMASK_WIZARD) {
    case SPECMASK_WIZARD_ABJURER:
        strMageSchool = 502; // "Abjurer"
        break;
    case SPECMASK_WIZARD_CONJURER:
        strMageSchool = 504; // "Conjurer"
        break;
    case SPECMASK_WIZARD_DIVINER:
        strMageSchool = 2012; // "Diviner"
        break;
    case SPECMASK_WIZARD_ENCHANTER:
        strMageSchool = 2022; // "Enchanter"
        break;
    case SPECMASK_WIZARD_ILLUSIONIST:
        strMageSchool = 12785; // "Illusionist"
        break;
    case SPECMASK_WIZARD_EVOKER:
        strMageSchool = 12786; // "Evoker"
        break;
    case SPECMASK_WIZARD_NECROMANCER:
        strMageSchool = 12787; // "Necromancer"
        break;
    case SPECMASK_WIZARD_TRANSMUTER:
        strMageSchool = 12788; // "Transmuter"
        break;
    case SPECMASK_WIZARD_UNIVERSAL:
        strMageSchool = 9987; // "Wizard"
        break;
    default:
        strMageSchool = -1;
        break;
    }

    if (strMageSchool != -1) {
        g_pBaldurChitin->GetTlkTable().Fetch(strMageSchool, strRes);
        g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_MAGESCHOOL, strRes.szText);
    }

    STRREF strFighterType;
    if ((dwFlags & 0x200) != 0) {
        strFighterType = 10371; // "Fallen Paladin"
    } else if ((dwFlags & 0x400) != 0) {
        strFighterType = 10369; // "Fallen Ranger"
    } else {
        switch (nClass) {
        case CAIOBJECTTYPE_C_BARBARIAN:
            strFighterType = 16799; // "Fighter"
            break;
        default:
            strFighterType = 34; // "Barbarian"
            break;
        }
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strFighterType, strRes);
    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_FIGHTERTYPE, strRes.szText);

    STRREF strClass;
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        strClass = 34; // "Barbarian"
        break;
    case CAIOBJECTTYPE_C_BARD:
        strClass = 1083; // "Bard"
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nSpecialist & SPECMASK_CLERIC) {
        case SPECMASK_CLERIC_ILMATER:
            strClass = 38097; // "Painbearer of Ilmater"
            break;
        case SPECMASK_CLERIC_LATHANDER:
            strClass = 38098; // "Morninglord of Lathander"
            break;
        case SPECMASK_CLERIC_SELUNE:
            strClass = 38099; // "Silverstar of Selune"
            break;
        case SPECMASK_CLERIC_HELM:
            strClass = 38100; // "Watcher of Helm"
            break;
        case SPECMASK_CLERIC_OGHMA:
            strClass = 38101; // "Lorekeeper of Oghma"
            break;
        case SPECMASK_CLERIC_TEMPUS:
            strClass = 38102; // "Battleguard of Tempus"
            break;
        case SPECMASK_CLERIC_BANE:
            strClass = 38103; // "Dreadmaster of Bane"
            break;
        case SPECMASK_CLERIC_MASK:
            strClass = 38106; // "Demarch of Mask"
            break;
        case SPECMASK_CLERIC_TALOS:
            strClass = 38107; // "Stormlord of Talos"
            break;
        default:
            strClass = 1079; // "Cleric"
            break;
        }
        break;
    case CAIOBJECTTYPE_C_DRUID:
        strClass = 1080; // "Druid"
        break;
    case CAIOBJECTTYPE_C_FIGHTER:
        strClass = 1076; // "<FIGHTERTYPE>"
        break;
    case CAIOBJECTTYPE_C_MONK:
        switch (nSpecialist & SPECMASK_MONK) {
        case SPECMASK_MONK_OLD_ORDER:
            strClass = 36877; // "Monk of the Old Order"
            break;
        case SPECMASK_MONK_BROKEN_ONES:
            strClass = 36878; // "Monk of the Broken Ones"
            break;
        case SPECMASK_MONK_DARK_MOON:
            strClass = 36879; // "Monk of the Dark Moon"
            break;
        default:
            strClass = 33; // "Monk"
            break;
        }
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        if ((dwFlags & 0x200) != 0) {
            strClass = 10371; // "Fallen Paladin"
        } else {
            switch (nSpecialist & SPECMASK_PALADIN) {
            case SPECMASK_PALADIN_ILMATER:
                strClass = 36875; // "Paladin of Ilmater"
                break;
            case SPECMASK_PALADIN_HELM:
                strClass = 36872; // "Paladin of Helm"
                break;
            case SPECMASK_PALADIN_MYSTRA:
                strClass = 36873; // "Paladin of Mystra"
                break;
            default:
                strClass = 1078; // "Paladin"
                break;
            }
        }
        break;
    case CAIOBJECTTYPE_C_RANGER:
        if ((dwFlags & 0x400) != 0) {
            strClass = 10369; // "Fallen Ranger"
        } else {
            strClass = 1077; // "Ranger"
        }
        break;
    case CAIOBJECTTYPE_C_ROGUE:
        strClass = 1082; // "Rogue"
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        if (a5 != 0) {
            strClass = 32; // "Sorcerer"
        } else {
            strClass = 40352; // "Sorceress"
        }
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        strClass = 1081; // "<MAGESCHOOL>"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 3926
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strClass, strRes);
    sClass = strRes.szText;
}

// 0x544500
void CRuleTables::GetScriptDescription(const CString& sScript, CString& sTitle, CString& sDescription) const
{
    CString sName(sScript);
    DWORD strTitle;
    DWORD strDescription;
    STR_RES strRes;

    strTitle = atol(m_tScriptDescription.GetAt(TITLE, sName));

    // TODO: Might be an error - obtains TITLE once again instead of DESCRIPTION
    // as seen below.
    strDescription = atol(m_tScriptDescription.GetAt(TITLE, sName));

    if (strTitle == -1 || strDescription == -1) {
        sName = CUSTOM;
    }

    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_SCRIPT, sScript);

    strTitle = atol(m_tScriptDescription.GetAt(TITLE, sName));
    g_pBaldurChitin->GetTlkTable().Fetch(strTitle, strRes);
    sTitle = strRes.szText;

    strDescription = atol(m_tScriptDescription.GetAt(DESCRIPTION, sName));
    g_pBaldurChitin->GetTlkTable().Fetch(strDescription, strRes);
    sDescription = strRes.szText;
}

// 0x5446B0
void CRuleTables::GetCharacterStateDescription(INT nState, CString& sDescription) const
{
    STR_RES strRes;
    DWORD strDescription;
    CString sState;

    sState.Format("%d", nState);
    strDescription = atol(m_tCharacterStateDescription.GetAt(DESCRIPTION, sState));
    g_pBaldurChitin->GetTlkTable().Fetch(strDescription, strRes);
    sDescription = strRes.szText;
}

// 0x5447B0
void CRuleTables::GetMovieDescription(const CString& sMovie, CString& sDescription) const
{
    STR_RES strRes;
    DWORD strDescription;

    strDescription = atol(m_tMovieDescription.GetAt(DESCRIPTION, sMovie));
    g_pBaldurChitin->GetTlkTable().Fetch(strDescription, strRes);
    sDescription = strRes.szText;
}

// 0x544870
void CRuleTables::GetSpellDescription(const CString& sSpell, CString& sDescription) const
{
    STR_RES strRes;
    DWORD strDescription;

    strDescription = atol(m_tSpellDescription.GetAt(DESCRIPTION, sSpell));
    g_pBaldurChitin->GetTlkTable().Fetch(strDescription, strRes);
    sDescription = strRes.szText;
}

// 0x544930
SHORT CRuleTables::GetLayOnHandsAmount(const CAIObjectType& typeAI, CDerivedStats& DStats) const
{
    if ((DStats.m_classMask & CLASSMASK_PALADIN) == 0) {
        return 0;
    }

    DWORD nPaladinLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN);

    // TODO: Check casts.
    float v1 = DStats.m_nCHR < 10
        ? static_cast<float>(DStats.m_nCHR) - 1.0f
        : static_cast<float>(DStats.m_nCHR);
    float v2 = (v1 - 10.0f) / 2.0f;
    if (static_cast<int>(v2) >= 1) {
        nPaladinLevel *= static_cast<int>(v2);
    }

    return static_cast<SHORT>(nPaladinLevel);
}

// 0x5449F0
INT CRuleTables::GetWholenessOfBodyAmount(const CAIObjectType& typeAI, CDerivedStats& DStats) const
{
    if ((typeAI.m_nClassMask & CLASSMASK_MONK) == 0) {
        return 0;
    }

    INT nMonkLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_MONK);
    if (nMonkLevel < 7) {
        return 0;
    }

    return 2 * nMonkLevel;
}

// 0x544A20
INT CRuleTables::GetLathanderRenewalAmount(const CAIObjectType& typeAI, CDerivedStats& DStats) const
{
    if ((typeAI.m_nClassMask & CLASSMASK_CLERIC) == 0) {
        return 0;
    }

    if ((DStats.m_nSpecialization & SPECMASK_CLERIC_LATHANDER) == 0) {
        return 0;
    }

    INT nClericLevel = DStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC);
    if (nClericLevel < 1) {
        return 0;
    }

    return 2 * nClericLevel;
}

// 0x544A60
BOOL CRuleTables::IsValidAlignment(BYTE nClass, BYTE nAlignment, DWORD nSpecialist) const
{
    CString sClass = GetClassString(nClass, nSpecialist);
    CString sAlignment = GetAlignmentString(nAlignment);
    return atol(m_tAlignment.GetAt(sAlignment, sClass));
}

// 0x544B10
BOOL CRuleTables::IsUsableByAlignment(DWORD dwNotUsableBy, BYTE nAlignment) const
{
    if ((dwNotUsableBy & 0x4000) != 0) {
        if (nAlignment == CAIObjectType::CHAOTIC_GOOD
            || nAlignment == CAIObjectType::NEUTRAL_GOOD
            || nAlignment == CAIObjectType::LAWFUL_GOOD) {
            return FALSE;
        }
    }

    if ((dwNotUsableBy & 0x8000) != 0) {
        if (nAlignment == CAIObjectType::CHAOTIC_NEUTRAL
            || nAlignment == CAIObjectType::NEUTRAL
            || nAlignment == CAIObjectType::LAWFUL_NEUTRAL) {
            return FALSE;
        }
    }

    if ((dwNotUsableBy & 0x2000) != 0) {
        if (nAlignment == CAIObjectType::CHAOTIC_EVIL
            || nAlignment == CAIObjectType::NEUTRAL_EVIL
            || nAlignment == CAIObjectType::LAWFUL_EVIL) {
            return FALSE;
        }
    }

    if ((dwNotUsableBy & 0x10000) != 0) {
        if (nAlignment == CAIObjectType::LAWFUL_GOOD
            || nAlignment == CAIObjectType::LAWFUL_NEUTRAL
            || nAlignment == CAIObjectType::LAWFUL_EVIL) {
            return FALSE;
        }
    }

    if ((dwNotUsableBy & 0x20000) != 0) {
        if (nAlignment == CAIObjectType::NEUTRAL_GOOD
            || nAlignment == CAIObjectType::NEUTRAL
            || nAlignment == CAIObjectType::NEUTRAL_EVIL) {
            return FALSE;
        }
    }

    if ((dwNotUsableBy & 0x1000) != 0) {
        if (nAlignment == CAIObjectType::CHAOTIC_GOOD
            || nAlignment == CAIObjectType::CHAOTIC_NEUTRAL
            || nAlignment == CAIObjectType::CHAOTIC_EVIL) {
            return FALSE;
        }
    }

    return TRUE;
}

// 0x544BF0
BYTE CRuleTables::GetStartingReputation(BYTE nAlignment) const
{
    CString sAlignment = GetAlignmentString(nAlignment);
    // TODO: Check cast.
    return static_cast<BYTE>(atol(m_tReputationStart.GetAt(VALUE, sAlignment)));
}

// 0x544C80
void CRuleTables::AdjustStoreMarkup(BYTE nCHR, SHORT nReputation, DWORD& dwMarkup) const
{
    INT nRepMod = atol(m_tReputationStoreMod.GetAt(CPoint(nReputation - 1, 0)));
    INT nCHRMod = atol(m_tCharismaStoreMod.GetAt(CPoint(nCHR - 1, 0)));
    dwMarkup = dwMarkup * (nRepMod + nCHRMod) / 100;
}

// #guess
// 0x544C70
DWORD CRuleTables::GetXPCap() const
{
    return 528000;
}

// 0x544D20
BOOL CRuleTables::IsValidSubRace(BYTE nRace, BYTE nSubRace) const
{
    switch (nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE
            || nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR
            || nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING;
    case CAIOBJECTTYPE_R_ELF:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE
            || nSubRace == CAIOBJECTTYPE_SUBRACE_ELF_DROW
            || nSubRace == CAIOBJECTTYPE_SUBRACE_ELF_WILD;
    case CAIOBJECTTYPE_R_HALF_ELF:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE;
    case CAIOBJECTTYPE_R_DWARF:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE
            || nSubRace == CAIOBJECTTYPE_SUBRACE_DWARF_GOLD
            || nSubRace == CAIOBJECTTYPE_SUBRACE_DWARF_GRAY;
    case CAIOBJECTTYPE_R_HALFLING:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE
            || nSubRace == CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART
            || nSubRace == CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE;
    case CAIOBJECTTYPE_R_GNOME:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE
            || nSubRace == CAIOBJECTTYPE_SUBRACE_GNOME_DEEP;
    case CAIOBJECTTYPE_R_HALF_ORC:
        return nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE;
    default:
        return FALSE;
    }
}

// 0x544DB0
void CRuleTables::GetRaceStringMixed(BYTE nRace, CString& sRace, BYTE nSubRace) const
{
    STR_RES strRes;

    STRREF strRace;
    switch (nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            strRace = 1096; // "Human"
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
            strRace = 5377; // "Aasimar"
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            strRace = 5378; // "Tiefling"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
            // __LINE__: 5130
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            strRace = 1097; // "Moon Elf"
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            strRace = 5379; // "Drow"
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_WILD:
            strRace = 5380; // "Wild Elf"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
            // __LINE__: 5151
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ELF:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 5157
        UTIL_ASSERT(nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE);

        strRace = 1098; // "Half-Elf"
        break;
    case CAIOBJECTTYPE_R_DWARF:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            strRace = 1100; // "Shield Dwarf"
            break;
        case CAIOBJECTTYPE_SUBRACE_DWARF_GOLD:
            strRace = 5381; // "Gold Dwarf"
            break;
        case CAIOBJECTTYPE_SUBRACE_DWARF_GRAY:
            strRace = 5382; // "Gray Dwarf"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
            // __LINE__: 5178
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            strRace = 5374; // "Lightfoot Halfling"
            break;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART:
            strRace = 5383; // "Strongheart Halfling"
            break;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE:
            strRace = 5384; // "Ghostwise Halfling"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
            // __LINE__: 5178
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            strRace = 1099; // "Rock Gnome"
            break;
        case CAIOBJECTTYPE_SUBRACE_GNOME_DEEP:
            strRace = 5385; // "Deep Gnome"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
            // __LINE__: 5216
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 5222
        UTIL_ASSERT(nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE);

        strRace = 23; // "Half-Orc"
        break;
    default:
        strRace = -1;
        break;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strRace, strRes);
    sRace = strRes.szText;
}

// 0x545080
void CRuleTables::GetClassStringGameSpy(BYTE nClass, DWORD nSpecialist, CString& sClass) const
{
    STR_RES strRes;
    DWORD strClass;

    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        // "Barbarian"
        strClass = 10;
        break;
    case CAIOBJECTTYPE_C_BARD:
        // "Bard"
        strClass = 10179;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        // "Cleric"
        strClass = 10177;
        break;
    case CAIOBJECTTYPE_C_DRUID:
        // "Druid"
        strClass = 10186;
        break;
    case CAIOBJECTTYPE_C_FIGHTER:
        // "Fighter"
        strClass = 10174;
        break;
    case CAIOBJECTTYPE_C_MONK:
        // "Monk"
        strClass = 39;
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        // "Paladin"
        strClass = 10194;
        break;
    case CAIOBJECTTYPE_C_RANGER:
        // "Ranger"
        strClass = 10173;
        break;
    case CAIOBJECTTYPE_C_ROGUE:
        // "Thief"
        strClass = 10175;
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        // "Sorcerer"
        strClass = 38;
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        // "Wizard"
        strClass = 10176;
        break;
    default:
        strClass = -1;
        break;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strClass, strRes);
    sClass = strRes.szText;
}

// 0x5451B0
int CRuleTables::GetRaiseDeadCost(const CAIObjectType& type, CDerivedStats& DStats) const
{
    return atol(m_tRaiseDeadCost.GetAt(CPoint(0, DStats.m_nLevel - 1)));
}

// 0x5452C0
DWORD CRuleTables::GetReputationDescription(SHORT nReputation) const
{
    return atol(m_tReputationDescription.GetAt(CPoint(0, nReputation)));
}

// 0x545310
void CRuleTables::GetIntoxicationInfo(BYTE nCON, INT& nIntoxicationRate, INT& nRecoveryRate, INT& nIntoxicationCap) const
{
    nIntoxicationRate = atol(m_tReputationDescription.GetAt(CPoint(0, nCON - 1)));
    nRecoveryRate = atol(m_tReputationDescription.GetAt(CPoint(1, nCON - 1)));
    nIntoxicationCap = atol(m_tReputationDescription.GetAt(CPoint(2, nCON - 1)));
}

// 0x5453F0
BOOL CRuleTables::GetCustomSound(CString& sName, BYTE nSoundId) const
{
    CString temp;
    LONG value;

    value = m_tCustomSound.GetAtLong(CPoint(0, nSoundId));
    if (value < 10) {
        sName.Format("0%d", value);
    } else {
        sName.Format("%d", value);
    }

    return value;
}

// 0x545490
void CRuleTables::GetAlignmentStringMixed(BYTE nAlignment, CString& sAlignment) const
{
    DWORD dwStrId;
    STR_RES strRes;

    switch (nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_GOOD:
        // "Lawful Good"
        dwStrId = 1102;
        break;
    case CAIOBJECTTYPE_LAWFUL_NEUTRAL:
        // "Lawful Neutral"
        dwStrId = 1104;
        break;
    case CAIOBJECTTYPE_LAWFUL_EVIL:
        // "Lawful Evil"
        dwStrId = 1103;
        break;
    case CAIOBJECTTYPE_NEUTRAL_GOOD:
        // "Neutral Good"
        dwStrId = 1105;
        break;
    case CAIOBJECTTYPE_NEUTRAL:
        // "True Neutral"
        dwStrId = 1106;
        break;
    case CAIOBJECTTYPE_NEUTRAL_EVIL:
        // "Neutral Evil"
        dwStrId = 1107;
        break;
    case CAIOBJECTTYPE_CHAOTIC_GOOD:
        // "Chaotic Good"
        dwStrId = 1108;
        break;
    case CAIOBJECTTYPE_CHAOTIC_NEUTRAL:
        // "Chaotic Neutral"
        dwStrId = 1109;
        break;
    case CAIOBJECTTYPE_CHAOTIC_EVIL:
        // "Chaotic Evil"
        dwStrId = 1110;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 5529
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    sAlignment = strRes.szText;
}

// 0x5455F0
void CRuleTables::GetGenderStringMixed(BYTE nGender, CString& sGender) const
{
    DWORD dwStrId;
    STR_RES strRes;

    switch (nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        // "Male"
        dwStrId = 1050;
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        // "Female"
        dwStrId = 1051;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 5575
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    sGender = strRes.szText;
}

// 0x545720
INT CRuleTables::GetNumQuickWeaponSlots(BYTE nClass) const
{
    return 8;
}

// 0x545730
BOOL CRuleTables::IsItemExclusive(CItem* pItem) const
{
    BOOL bExclusive = FALSE;

    if (pItem != NULL) {
        CString sResRef;
        pItem->GetResRef().CopyToString(sResRef);

        bExclusive = atol(m_tExclusiveItems.GetAt(VALUE, sResRef));
    }

    return bExclusive;
}

// 0x5457C0
BOOL CRuleTables::Is3DSound(int nSoundChannel) const
{
    return m_tSoundChannel.GetAtLong(CPoint(1, nSoundChannel));
}

// 0x5457F0
float CRuleTables::GetSoundReverbMix(int nSoundChannel, int nReverb) const
{
    // TODO: Check casts.
    float v1 = static_cast<float>(atof(m_tSoundChannel.GetAt(CPoint(2, nSoundChannel))));
    float v2 = static_cast<float>(atof(m_tReverb.GetAt(CPoint(4, nReverb))));
    return v1 * v2;
}

// 0x545890
int CRuleTables::GetSoundEnvironment(EAXPRESET& preset, int nReverb) const
{
    int nPreset = nReverb % m_tReverb.GetWidth();

    CString sEnvironment = m_tReverb.GetAt(CPoint(0, nPreset));

    // TODO: Check casts.
    preset.fVolume = static_cast<float>(atof(m_tReverb.GetAt(CPoint(1, nPreset))));
    preset.fDecayTime = static_cast<float>(atof(m_tReverb.GetAt(CPoint(2, nPreset))));
    preset.fDaming = static_cast<float>(atof(m_tReverb.GetAt(CPoint(3, nPreset))));

    CAIId* id = m_lEAXEnvironment.Find(sEnvironment, TRUE);
    if (id != NULL) {
        preset.dwEnvironment = id->m_id;
    }

    return nPreset;
}

// 0x545A10
BYTE CRuleTables::MapCharacterSpecializationToSchool(WORD nSpecialistMage) const
{
    switch (nSpecialistMage & SPECMASK_WIZARD) {
    case SPECMASK_WIZARD_ABJURER:
        return 1;
    case SPECMASK_WIZARD_CONJURER:
        return 2;
    case SPECMASK_WIZARD_DIVINER:
        return 3;
    case SPECMASK_WIZARD_ENCHANTER:
        return 4;
    case SPECMASK_WIZARD_ILLUSIONIST:
        return 5;
    case SPECMASK_WIZARD_EVOKER:
        return 6;
    case SPECMASK_WIZARD_NECROMANCER:
        return 7;
    case SPECMASK_WIZARD_TRANSMUTER:
        return 8;
    case SPECMASK_WIZARD_UNIVERSAL:
        return 9;
    }

    return 0;
}

// 0x545A90
DWORD CRuleTables::GetFeatName(DWORD id) const
{
    for (SHORT nIndex = 0; nIndex < m_tFeats.GetHeight(); nIndex++) {
        if (GetFeatId(nIndex) == id) {
            const CString& sValue = m_tFeats.GetAt(CPoint(1, nIndex));
            DWORD str;
            sscanf(sValue, "%d", &str);
            return str != 0 ? str : -1;
        }
    }

    return -1;
}

// 0x545B70
DWORD CRuleTables::GetFeatId(DWORD index) const
{
    const CString& sValue = m_tFeats.GetAt(CPoint(0, index));
    DWORD id;
    sscanf(sValue, "%d", &id);
    return id;
}

// 0x545BC0
DWORD CRuleTables::GetFeatDescription(DWORD id) const
{
    for (SHORT nIndex = 0; nIndex < m_tFeats.GetHeight(); nIndex++) {
        if (GetFeatId(nIndex) == id) {
            const CString& sValue = m_tFeats.GetAt(CPoint(2, nIndex));
            DWORD str;
            sscanf(sValue, "%d", &str);
            return str != 0 ? str : -1;
        }
    }

    return -1;
}

// 0x545CA0
DWORD CRuleTables::GetSkillName(DWORD id) const
{
    for (SHORT nIndex = 0; nIndex < m_tSkills.GetHeight(); nIndex++) {
        if (GetSkillId(nIndex) == id) {
            const CString& sValue = m_tSkills.GetAt(CPoint(1, nIndex));
            DWORD str;
            sscanf(sValue, "%d", &str);
            return str != 0 ? str : -1;
        }
    }

    return -1;
}

// 0x545D80
DWORD CRuleTables::GetSkillId(DWORD index) const
{
    const CString& sValue = m_tSkills.GetAt(CPoint(0, index));
    DWORD id;
    sscanf(sValue, "%d", &id);
    return id;
}

// 0x545DD0
DWORD CRuleTables::GetSkillDescription(DWORD id) const
{
    for (SHORT nIndex = 0; nIndex < m_tSkills.GetHeight(); nIndex++) {
        if (GetSkillId(nIndex) == id) {
            const CString& sValue = m_tSkills.GetAt(CPoint(2, nIndex));
            DWORD str;
            sscanf(sValue, "%d", &str);
            return str != 0 ? str : -1;
        }
    }

    return -1;
}

// 0x545FD0
INT CRuleTables::GetLoadingHint(INT nHintNumber) const
{
    return atol(m_tLoadingHints.GetAt(CPoint(0, nHintNumber)));
}

// 0x546020
INT CRuleTables::GetNumLoadingHints() const
{
    return m_tLoadingHints.GetHeight() - 1;
}

// 0x546030
const C2DArray* CRuleTables::GetClassAbilityTable(BYTE nClass, DWORD nSpecialist) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        return &m_tClassAbilitiesBarbarian;
    case CAIOBJECTTYPE_C_BARD:
        return &m_tClassAbilitiesBard;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nSpecialist & SPECMASK_CLERIC) {
        case SPECMASK_CLERIC_ILMATER:
            return &m_tClassAbilitiesClericIlmater;
        case SPECMASK_CLERIC_LATHANDER:
            return &m_tClassAbilitiesClericLathander;
        case SPECMASK_CLERIC_SELUNE:
            return &m_tClassAbilitiesClericSelune;
        case SPECMASK_CLERIC_HELM:
            return &m_tClassAbilitiesClericHelm;
        case SPECMASK_CLERIC_OGHMA:
            return &m_tClassAbilitiesClericOghma;
        case SPECMASK_CLERIC_TEMPUS:
            return &m_tClassAbilitiesClericTempus;
        case SPECMASK_CLERIC_BANE:
            return &m_tClassAbilitiesClericBane;
        case SPECMASK_CLERIC_MASK:
            return &m_tClassAbilitiesClericMask;
        case SPECMASK_CLERIC_TALOS:
            return &m_tClassAbilitiesClericTalos;
        }

        return &m_tClassAbilitiesClericTrue;
    case CAIOBJECTTYPE_C_DRUID:
        return &m_tClassAbilitiesDruid;
    case CAIOBJECTTYPE_C_FIGHTER:
        return &m_tClassAbilitiesFighter;
    case CAIOBJECTTYPE_C_MONK:
        return &m_tClassAbilitiesMonk;
    case CAIOBJECTTYPE_C_PALADIN:
        return &m_tClassAbilitiesPaladin;
    case CAIOBJECTTYPE_C_RANGER:
        return &m_tClassAbilitiesRanger;
    case CAIOBJECTTYPE_C_ROGUE:
        return &m_tClassAbilitiesRogue;
    case CAIOBJECTTYPE_C_SORCERER:
        return &m_tClassAbilitiesSorcerer;
    case CAIOBJECTTYPE_C_WIZARD:
        return &m_tClassAbilitiesWizard;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
    // __LINE__: 6354
    UTIL_ASSERT_MSG(FALSE, "GetClassAbilityTable Being  called incorrectly");
}

// 0x546680
STRREF CRuleTables::GetSpeechStringRef(CString& sSoundSet, INT nSpeech) const
{
    if (sSoundSet.IsEmpty()) {
        return -1;
    }

    if (nSpeech < 0 || nSpeech > 42) {
        return -1;
    }

    CPoint ptLocation;
    m_tCharStr.Find(sSoundSet, ptLocation, TRUE);

    if (ptLocation.y == -1) {
        return -1;
    }

    ptLocation.x = nSpeech;

    return m_tCharStr.GetAtLong(ptLocation);
}

// 0x546800
BOOLEAN CRuleTables::IsHatedRace(const CAIObjectType& typeAI, const CCreatureFileHeader& BStats) const
{
    for (int index = 0; index < MAX_HATED_RACES; index++) {
        if (typeAI.m_nRace == BStats.m_favoredEnemies[index]) {
            return TRUE;
        }
    }

    return FALSE;
}

// FIXME: For unknown reason `nRace` is passed as a pointer.
//
// 0x546830
BOOLEAN CRuleTables::IsHatedRace(BYTE& nRace, const CCreatureFileHeader& BStats) const
{
    for (int index = 0; index < MAX_HATED_RACES; index++) {
        if (BStats.m_favoredEnemies[index] == nRace) {
            return TRUE;
        }
    }

    return FALSE;
}

// FIXME: For unknown reason `nRace` is passed as a pointer.
//
// 0x546860
INT CRuleTables::GetHatedRaceBonus(BYTE& nRace, const CCreatureFileHeader& BStats) const
{
    BOOLEAN bFound = FALSE;
    INT nFavoredEnemyIndex = 0;
    INT nCnt;

    for (nCnt = 0; nCnt < MAX_HATED_RACES; nCnt++) {
        if (BStats.m_favoredEnemies[nCnt] == CAIObjectType::R_NO_RACE) {
            break;
        }

        if (BStats.m_favoredEnemies[nCnt] == nRace) {
            bFound = TRUE;
            nFavoredEnemyIndex = nCnt;
        }
    }

    if (bFound != TRUE) {
        return 0;
    }

    return nCnt - nFavoredEnemyIndex;
}

// 0x546AA0
INT CRuleTables::GetEncumbranceMod(CGameSprite* pSprite) const
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
    // __LINE__: 6712
    UTIL_ASSERT(pSprite != NULL);

    const CAIObjectType& typeAI = pSprite->GetAIType();

    CString sClass = GetClassString(typeAI.m_nClass, 0);

    INT nEncMod = atol(m_tEncMod.GetAt(ENCUMBRANCE_MOD_PERCENT, sClass)) + 100;

    if (pSprite->sub_763150(CGAMESPRITE_FEAT_STRONG_BACK)) {
        nEncMod += 50;
    }

    return nEncMod;
}

// 0x546B60
void CRuleTables::sub_546B60(CGameSprite* pSprite, int& a2, int& a3, int& a4, BOOL a5) const
{
    // TODO: Incomplete.
}

// FIXME: For unknown reason `nClass` and `nLevel` params are passed as
// pointers.
//
// 0x547130
DWORD CRuleTables::GetMaxSpellLevel(const BYTE& nClass, const UINT& nLevel) const
{
    switch (nClass) {
    case 0:
    case CAIOBJECTTYPE_C_BARBARIAN:
    case CAIOBJECTTYPE_C_FIGHTER:
    case CAIOBJECTTYPE_C_MONK:
    case CAIOBJECTTYPE_C_ROGUE:
        return 0;
    }

    const C2DArray* tMaxSpells;
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
        tMaxSpells = &m_tMaxSpellsBard;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        tMaxSpells = &m_tMaxSpellsCleric;
        break;
    case CAIOBJECTTYPE_C_DRUID:
        tMaxSpells = &m_tMaxSpellsDruid;
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        tMaxSpells = &m_tMaxSpellsPaladin;
        break;
    case CAIOBJECTTYPE_C_RANGER:
        tMaxSpells = &m_tMaxSpellsRanger;
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        tMaxSpells = &m_tMaxSpellsSorcerer;
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        tMaxSpells = &m_tMaxSpellsWizard;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CRuleTables.cpp
        // __LINE__: 7049
        UTIL_ASSERT(FALSE);
    }

    INT nSpellLevel;
    for (nSpellLevel = 0; nSpellLevel < 9; nSpellLevel++) {
        // FIXME: Should be outside of the loop (prevent ctor/dtor on every
        // iteration).
        CString sSpellLevel(" ");

        // FIXME: Should be outside of the loop (never change, see below).
        CString sClassLevel(" ");

        sSpellLevel.Format("%d", nSpellLevel + 1);
        sClassLevel.Format("%d", nLevel);

        if (atol(tMaxSpells->GetAt(sSpellLevel, sClassLevel)) == 0) {
            break;
        }
    }

    return nSpellLevel;
}

// 0x5472E0
BYTE CRuleTables::GetSpecializationIndex(BYTE nClass, DWORD nSpecialization) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nSpecialization & SPECMASK_CLERIC) {
        case SPECMASK_CLERIC_ILMATER:
            return 1;
        case SPECMASK_CLERIC_LATHANDER:
            return 2;
        case SPECMASK_CLERIC_SELUNE:
            return 3;
        case SPECMASK_CLERIC_HELM:
            return 4;
        case SPECMASK_CLERIC_OGHMA:
            return 5;
        case SPECMASK_CLERIC_TEMPUS:
            return 6;
        case SPECMASK_CLERIC_BANE:
            return 7;
        case SPECMASK_CLERIC_MASK:
            return 8;
        case SPECMASK_CLERIC_TALOS:
            return 9;
        }
        break;
    case CAIOBJECTTYPE_C_MONK:
        switch (nSpecialization & SPECMASK_MONK) {
        case SPECMASK_MONK_OLD_ORDER:
            return 1;
        case SPECMASK_MONK_BROKEN_ONES:
            return 2;
        case SPECMASK_MONK_DARK_MOON:
            return 3;
        }
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        switch (nSpecialization & SPECMASK_PALADIN) {
        case SPECMASK_PALADIN_ILMATER:
            return 1;
        case SPECMASK_PALADIN_HELM:
            return 2;
        case SPECMASK_PALADIN_MYSTRA:
            return 3;
        }
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        switch (nSpecialization & SPECMASK_WIZARD) {
        case SPECMASK_WIZARD_ABJURER:
            return 1;
        case SPECMASK_WIZARD_CONJURER:
            return 2;
        case SPECMASK_WIZARD_DIVINER:
            return 3;
        case SPECMASK_WIZARD_ENCHANTER:
            return 4;
        case SPECMASK_WIZARD_ILLUSIONIST:
            return 5;
        case SPECMASK_WIZARD_EVOKER:
            return 6;
        case SPECMASK_WIZARD_NECROMANCER:
            return 7;
        case SPECMASK_WIZARD_TRANSMUTER:
            return 8;
        case SPECMASK_WIZARD_UNIVERSAL:
            return 9;
        }
        break;
    }

    return 0;
}

// 0x547470
DWORD CRuleTables::GetSpecializationMask(BYTE nClass, BYTE nIndex) const
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_CLERIC:
        switch (nIndex) {
        case 1:
            return SPECMASK_CLERIC_ILMATER;
        case 2:
            return SPECMASK_CLERIC_LATHANDER;
        case 3:
            return SPECMASK_CLERIC_SELUNE;
        case 4:
            return SPECMASK_CLERIC_HELM;
        case 5:
            return SPECMASK_CLERIC_OGHMA;
        case 6:
            return SPECMASK_CLERIC_TEMPUS;
        case 7:
            return SPECMASK_CLERIC_BANE;
        case 8:
            return SPECMASK_CLERIC_MASK;
        case 9:
            return SPECMASK_CLERIC_TALOS;
        }
        break;
    case CAIOBJECTTYPE_C_MONK:
        switch (nIndex) {
        case 1:
            return SPECMASK_MONK_OLD_ORDER;
        case 2:
            return SPECMASK_MONK_BROKEN_ONES;
        case 3:
            return SPECMASK_MONK_DARK_MOON;
        }
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        switch (nIndex) {
        case 1:
            return SPECMASK_PALADIN_ILMATER;
        case 2:
            return SPECMASK_PALADIN_HELM;
        case 3:
            return SPECMASK_PALADIN_MYSTRA;
        }
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        switch (nIndex) {
        case 1:
            return SPECMASK_WIZARD_ABJURER;
        case 2:
            return SPECMASK_WIZARD_CONJURER;
        case 3:
            return SPECMASK_WIZARD_DIVINER;
        case 4:
            return SPECMASK_WIZARD_ENCHANTER;
        case 5:
            return SPECMASK_WIZARD_ILLUSIONIST;
        case 6:
            return SPECMASK_WIZARD_EVOKER;
        case 7:
            return SPECMASK_WIZARD_NECROMANCER;
        case 8:
            return SPECMASK_WIZARD_TRANSMUTER;
        case 9:
            return SPECMASK_WIZARD_UNIVERSAL;
        }
        break;
    }

    return 0;
}

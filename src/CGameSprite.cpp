#include "CGameSprite.h"

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CBlood.h"
#include "CGameAnimationType.h"
#include "CGameArea.h"
#include "CGameButtonList.h"
#include "CGameContainer.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CPathSearch.h"
#include "CProjectile.h"
#include "CScreenCharacter.h"
#include "CScreenCreateChar.h"
#include "CScreenInventory.h"
#include "CScreenMap.h"
#include "CScreenWorld.h"
#include "CSpawn.h"
#include "CSpell.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVariableHash.h"
#include "CVidInf.h"
#include "Icewind586B70.h"
#include "IcewindCGameEffects.h"
#include "IcewindCVisualEffect.h"
#include "IcewindMisc.h"

// 0x85BB38
const BYTE CGameSprite::DIR_S = 0;

// 0x85BB39
const BYTE CGameSprite::DIR_SW = 2;

// 0x85BB3A
const BYTE CGameSprite::DIR_W = 4;

// 0x85BB3B
const BYTE CGameSprite::DIR_NW = 6;

// 0x85BB3C
const BYTE CGameSprite::DIR_N = 8;

// 0x85BB3D
const BYTE CGameSprite::DIR_NE = 10;

// 0x85BB3E
const BYTE CGameSprite::DIR_E = 12;

// 0x85BB3F
const BYTE CGameSprite::DIR_SE = 14;

// 0x85BB40
const BYTE CGameSprite::DIR_SSW = 1;

// 0x85BB41
const BYTE CGameSprite::DIR_SWW = 3;

// 0x85BB42
const BYTE CGameSprite::DIR_NWW = 5;

// 0x85BB43
const BYTE CGameSprite::DIR_NNW = 7;

// 0x85BB44
const BYTE CGameSprite::DIR_NNE = 9;

// 0x85BB45
const BYTE CGameSprite::DIR_NEE = 11;

// 0x85BB46
const BYTE CGameSprite::DIR_SEE = 13;

// 0x85BB47
const BYTE CGameSprite::DIR_SSE = 15;

// 0x85BB48
const BYTE CGameSprite::NUM_DIR = 16;

// 0x85BB6A
const BYTE CGameSprite::SOUND_DYING = 7;

// 0x85BB6C
const BYTE CGameSprite::SOUND_SELECT = 9;

// 0x85BB6E
const BYTE CGameSprite::SOUND_SELECT_ACTION = 11;

// 0x85BB70
const BYTE CGameSprite::SOUND_REACT_TO_DEATH = 13;

// 0x85BB74
const SHORT CGameSprite::EXACT_SCALE = 10;

// 0x85BB9A
const SHORT CGameSprite::READY_COUNT = 75;

// 0x85BB9C
const SHORT CGameSprite::USER_OVERRIDE_COUNT = 75;

// 0x85BBB0
const BYTE CGameSprite::SEQ_ATTACK = CGAMESPRITE_SEQ_ATTACK;

// 0x85BBB1
const BYTE CGameSprite::SEQ_AWAKE = CGAMESPRITE_SEQ_AWAKE;

// 0x85BBB2
const BYTE CGameSprite::SEQ_CAST = CGAMESPRITE_SEQ_CAST;

// 0x85BBB3
const BYTE CGameSprite::SEQ_CONJURE = CGAMESPRITE_SEQ_CONJURE;

// 0x85BBB4
const BYTE CGameSprite::SEQ_DAMAGE = CGAMESPRITE_SEQ_DAMAGE;

// 0x85BBB5
const BYTE CGameSprite::SEQ_DIE = CGAMESPRITE_SEQ_DIE;

// 0x85BBB6
const BYTE CGameSprite::SEQ_EMERGE = CGAMESPRITE_SEQ_EMERGE;

// 0x85BBB7
const BYTE CGameSprite::SEQ_HEAD_TURN = CGAMESPRITE_SEQ_HEAD_TURN;

// 0x85BBB8
const BYTE CGameSprite::SEQ_HIDE = CGAMESPRITE_SEQ_HIDE;

// 0x85BBB9
const BYTE CGameSprite::SEQ_READY = CGAMESPRITE_SEQ_READY;

// 0x85BBBA
const BYTE CGameSprite::SEQ_SHOOT = CGAMESPRITE_SEQ_SHOOT;

// 0x85BBBB
const BYTE CGameSprite::SEQ_SLEEP = CGAMESPRITE_SEQ_SLEEP;

// 0x85BBBC
const BYTE CGameSprite::SEQ_TWITCH = CGAMESPRITE_SEQ_TWITCH;

// 0x85BBBD
const BYTE CGameSprite::SEQ_WALK = CGAMESPRITE_SEQ_WALK;

// 0x85BBBE
const BYTE CGameSprite::SEQ_ATTACK_SLASH = CGAMESPRITE_SEQ_ATTACK_SLASH;

// 0x85BBBF
const BYTE CGameSprite::SEQ_ATTACK_BACKSLASH = CGAMESPRITE_SEQ_ATTACK_BACKSLASH;

// 0x85BBC0
const BYTE CGameSprite::SEQ_ATTACK_JAB = CGAMESPRITE_SEQ_ATTACK_JAB;

// 0x85BBD0
const ITEM_ABILITY CGameSprite::DEFAULT_ATTACK = {
    1, // type
    1, // quickSlotType
    0, // largeDamageDice
    { 0 }, // quickSlotIcon
    1, // actionType
    1, // actionCount
    1, // range
    0, // launcherType
    0, // largeDamageDiceCount
    0, // speedFactor
    0, // largeDamageDiceBonus
    0, // thac0Bonus
    2, // damageDice
    9, // school
    1, // damageDiceCount
    0, // secondaryType
    0, // damageDiceBonus
    2, // damageType
    0, // effectCount
    0, // startingEffect
    WORD_MAX, // maxUsageCount
    0, // usageFlags
    0, // abilityFlags
    0, // missileType
    { 0 }, // attackProbability
};

// 0x85BCA0
const LONG CGameSprite::STANDARD_VERBAL_CONSTANT_LENGTH = 300;

// 0x85C09C
const SHORT CGameSprite::FLY_RIGHT = -1;

// 0x85C09E
const SHORT CGameSprite::FLY_LEFT = 1;

// 0x85C0A0
const SHORT CGameSprite::FLY_RADIUS_RANDOM = 0x380;

// 0x85C0A2
const SHORT CGameSprite::FLY_RADIUS_BASE = 0x80;

// 0x85C0A4
const SHORT CGameSprite::FLY_0 = 0;

// 0x85C0A6
const SHORT CGameSprite::FLY_90 = 1;

// 0x85C0A8
const SHORT CGameSprite::FLY_180 = 2;

// 0x85C0AA
const SHORT CGameSprite::FLY_270 = 3;

// 0x85C0AC
const SHORT CGameSprite::FLY_360 = 4;

// 0x85C0B4
const WORD CGameSprite::FEEDBACK_BACKSTAB = 1;

// 0x85C0B6
const WORD CGameSprite::FEEDBACK_CRITICALHIT = 2;

// 0x85C0B8
const WORD CGameSprite::FEEDBACK_CRITICALMISS = 3;

// 0x85C0BA
const WORD CGameSprite::FEEDBACK_TOHIT = 4;

// 0x85C0BC
const WORD CGameSprite::FEEDBACK_SPELL = 5;

// 0x85C0BE
const WORD CGameSprite::FEEDBACK_ATTACKS = 6;

// 0x85C0C0
const WORD CGameSprite::FEEDBACK_MODAL = 7;

// 0x85C0C2
const WORD CGameSprite::FEEDBACK_LOCKPICKSUCCEEDED = 8;

// 0x85C0C4
const WORD CGameSprite::FEEDBACK_LOCKPICKFAILED = 9;

// 0x85C0C6
const WORD CGameSprite::FEEDBACK_TRAPDISARMED = 10;

// 0x85C0C8
const WORD CGameSprite::FEEDBACK_TRAPDETECTED = 11;

// 0x85C0CA
const WORD CGameSprite::FEEDBACK_ITEMCURSED = 12;

// 0x85C0CC
const WORD CGameSprite::FEEDBACK_HIDEFAILED = 13;

// 0x85C0CE
const WORD CGameSprite::FEEDBACK_TOOHEAVY_SLOWED = 14;

// 0x85C0D0
const WORD CGameSprite::FEEDBACK_TOOHEAVY_STOPPED = 15;

// 0x85C0D2
const WORD CGameSprite::FEEDBACK_16 = 16;

// 0x85C0D4
const WORD CGameSprite::FEEDBACK_HIDESUCCEEDED = 17;

// 0x85C0D6
const WORD CGameSprite::FEEDBACK_MORALEFAILURE_PANIC = 18;

// 0x85C0D8
const WORD CGameSprite::FEEDBACK_MORALEFAILURE_RUN = 19;

// 0x85C0DA
const WORD CGameSprite::FEEDBACK_MORALEFAILURE_BERSERK = 20;

// 0x85C0DC
const WORD CGameSprite::FEEDBACK_LEVELUP = 21;

// 0x85C0DE
const WORD CGameSprite::FEEDBACK_SPELLFAILED_INDOORS = 22;

// 0x85C0E0
const WORD CGameSprite::FEEDBACK_LEAVING_SHADOWS = 23;

// 0x85C0E2
const WORD CGameSprite::FEEDBACK_BASHDOORSUCCEEDED = 24;

// 0x85C0E4
const WORD CGameSprite::FEEDBACK_BASHDOORFAILED = 25;

// 0x85C0E6
const WORD CGameSprite::FEEDBACK_BASHCHESTSUCCEEDED = 26;

// 0x85C0E8
const WORD CGameSprite::FEEDBACK_BASHCHESTFAILED = 27;

// 0x85C0EA
const WORD CGameSprite::FEEDBACK_BACKSTAB_UNUSABLE_WEAPON = 28;

// 0x85C0EC
const WORD CGameSprite::FEEDBACK_29 = 29;

// 0x85C0EE
const WORD CGameSprite::FEEDBACK_PICKPOCKETFAILED_ARMOR = 30;

// 0x85C0F0
const WORD CGameSprite::FEEDBACK_PICKPOCKETFAILED_HOSTILE = 31;

// 0x85C0F2
const WORD CGameSprite::FEEDBACK_PICKPOCKETFAILED_SKILL = 32;

// 0x85C0F4
const WORD CGameSprite::FEEDBACK_PICKPOCKETFAILED_NOITEMS = 33;

// 0x85C0F6
const WORD CGameSprite::FEEDBACK_PICKPOCKETFAILED_INVENTORYFULL = 34;

// 0x85C0F8
const WORD CGameSprite::FEEDBACK_PICKPOCKETSUCCEEDED = 35;

// 0x85C0FA
const WORD CGameSprite::FEEDBACK_GAINEDSPECIALABILITY = 36;

// 0x85C0FC
const WORD CGameSprite::FEEDBACK_IMMUNE_TO_WEAPON = 37;

// 0x85C0FE
const WORD CGameSprite::FEEDBACK_CHARACTER_CONTROL_SEIZURE = 38;

// 0x85C100
const WORD CGameSprite::FEEDBACK_TRAPDISARMEDFAILED = 39;

// 0x85C102
const WORD CGameSprite::FEEDBACK_CRITICALHITAVOIDED = 40;

// 0x85C104
const WORD CGameSprite::FEEDBACK_AURA_CLEANSED = 41;

// 0x85C106
const WORD CGameSprite::FEEDBACK_ITEM_DROPPED_FULL = 48;

// 0x85C108
const WORD CGameSprite::FEEDBACK_LOCK_UNPICKABLE = 49;

// 0x85C10A
const WORD CGameSprite::FEEDBACK_TOOMANYSUMMONED = 50;

// 0x85C10C
const WORD CGameSprite::FEEDBACK_SILENCED = 51;

// 0x85C10E
const WORD CGameSprite::FEEDBACK_CRIPPLINGSTRIKESUCCEEDED = 52;

// 0x85C110
const WORD CGameSprite::FEEDBACK_SNEAK_UNUSABLE_WEAPON = 53;

// 0x85C112
const WORD CGameSprite::FEEDBACK_EFFECTSEVADED = 54;

// 0x85C114
const WORD CGameSprite::FEEDBACK_SPELLFAILED_DISRUPTED = 55;

// 0x85C116
const WORD CGameSprite::FEEDBACK_GAINEDBARDSONG = 56;

// 0x85C118
const WORD CGameSprite::FEEDBACK_STATICCHARGEEND = 57;

// 0x85C11A
const WORD CGameSprite::FEEDBACK_IMMUNE_TO_RESOURCE = 58;

// 0x85C11C
const WORD CGameSprite::FEEDBACK_LEAVEFAILED_INVENTORY = 59;

// 0x85C11E
const WORD CGameSprite::FEEDBACK_BACKSTAB_AVOIDED = 60;

// 0x85C120
const WORD CGameSprite::FEEDBACK_SPELLFAILED_CASTFAILURE = 61;

// 0x85C122
const WORD CGameSprite::FEEDBACK_62 = 62;

// 0x85C124
const WORD CGameSprite::FEEDBACK_63 = 63;

// 0x85C126
const WORD CGameSprite::FEEDBACK_CRIPPLINGSTRIKEFAILED = 64;

// 0x85C128
const WORD CGameSprite::FEEDBACK_USEMAGICDEVICEFAILED = 65;

// 0x85C12A
const WORD CGameSprite::FEEDBACK_USEMAGICDEVICESUCCEEDED = 66;

// 0x85C12C
const WORD CGameSprite::FEEDBACK_SEARCHSTART = 67;

// 0x85C12E
const WORD CGameSprite::FEEDBACK_SEARCHEND = 68;

// 0x85C130
const WORD CGameSprite::FEEDBACK_69 = 69;

// 0x85C132
const WORD CGameSprite::FEEDBACK_TURNUNDEADEND = 70;

// 0x85C134
const WORD CGameSprite::FEEDBACK_71 = 71;

// 0x85C136
const WORD CGameSprite::FEEDBACK_BATTLESONGSTART = 72;

// 0x85C138
const WORD CGameSprite::FEEDBACK_BATTLESONGEND = 73;

// 0x85C13A
const WORD CGameSprite::FEEDBACK_ARTERIALSTRIKESUCCEEDED = 75;

// 0x85C13C
const WORD CGameSprite::FEEDBACK_HAMSTRINGSUCCEEDED = 76;

// 0x85C13E
const WORD CGameSprite::FEEDBACK_HEROICINSPIRATION = 80;

// 0x85C140
const WORD CGameSprite::FEEDBACK_TARGETCONCEALED = 81;

// 0x85C142
const WORD CGameSprite::FEEDBACK_UNCANNYDODGESUCCEEDED = 82;

// 0x85C144
const WORD CGameSprite::FEEDBACK_ROLL = 83;

// 0x85C146
const WORD CGameSprite::FEEDBACK_SPELLFAILURE_CONCENTRATION = 84;

// 0x85C148
const WORD CGameSprite::FEEDBACK_SPONTANEOUSCASTING = 85;

// 0x85C14A
const WORD CGameSprite::FEEDBACK_TOGGLEFEAT = 86;

// 0x85C14C
const WORD CGameSprite::FEEDBACK_CLEAVE = 87;

// 0x85C14E
const WORD CGameSprite::FEEDBACK_LINGERINGSONG = 88;

// 0x85C150
const WORD CGameSprite::FEEDBACK_89 = 89;

// 0x85C152
const WORD CGameSprite::FEEDBACK_CALLLIGHTNINGEND = 90;

// 0x85C154
const WORD CGameSprite::FEEDBACK_MAGICALWEAPONINUSE = 91;

// 0x85C156
const WORD CGameSprite::FEEDBACK_LEAVEFAILED_LEVELUP = 92;

// 0x85C158
const WORD CGameSprite::FEEDBACK_LEAVEFAILED_STORE = 93;

// 0x8F94B8
const CPoint CGameSprite::PORTRAIT_ICON_SIZE(10, 10);

// 0x8F93F8
const CResRef CGameSprite::SPIN110("SPIN110");

// 0x8F92A0
const CResRef CGameSprite::SPIN111("SPIN111");

// 0x8F9328
const CResRef CGameSprite::SPIN107("SPIN107");

// 0x8F93E8
const CResRef CGameSprite::SPIN141("SPIN141");

// 0x8F92D0
const CResRef CGameSprite::SPIN142("SPIN142");

// 0x8F9468
const CResRef CGameSprite::SPIN143("SPIN143");

// 0x8F92C8
const CResRef CGameSprite::SPIN244("SPIN244");

// 0x8F94A0
const CResRef CGameSprite::SPIN245("SPIN245");

// 0x8F9488
const CResRef CGameSprite::SPIN246("SPIN246");

// 0x8F8E60
const CResRef CGameSprite::SPIN108("SPIN108");

// 0x8F92E0
const CResRef CGameSprite::SPIN109("SPIN109");

// 0x8F92B8
const CResRef CGameSprite::SPIN120("SPIN120");

// 0x8F9298
const CResRef CGameSprite::SPIN121("SPIN121");

// 0x8F9320
const CResRef CGameSprite::SPIN125("SPIN125");

// 0x8F9330
const CResRef CGameSprite::SPIN139("SPIN139");

// 0x8F9478
const CResRef CGameSprite::SPIN152("SPIN152");

// 0x8F9338
const CResRef CGameSprite::SPIN275("SPIN275");

// 0x8F8E70
const CResRef CGameSprite::SPIN276("SPIN276");

// 0x8F92F8
const CResRef CGameSprite::SPIN277("SPIN277");

// 0x8F92E8
const CResRef CGameSprite::SPIN278("SPIN278");

// 0x8F93D0
const CResRef CGameSprite::SPIN279("SPIN279");

// 0x8F8E18
const CResRef CGameSprite::SPIN970("SPIN970");

// 0x8F94B0
const CResRef CGameSprite::SPIN197("SPIN197");

// 0x8F8E90
const CResRef CGameSprite::SPPR327("SPPR327");

// 0x8F94D0
const CResRef CGameSprite::SPPR328("SPPR328");

// 0x8F92A8
const CResRef CGameSprite::SPPR429("SPPR429");

// 0x8F9460
const CResRef CGameSprite::SPIN198("SPIN198");

// 0x8F9448
const CResRef CGameSprite::SPIN199("SPIN199");

// 0x8F9300
const CResRef CGameSprite::SPIN200("SPIN200");

// 0x8F8E30
const CResRef CGameSprite::SPIN243("SPIN243");

// 0x8F9438
const CResRef CGameSprite::SPIN201("SPIN201");

// 0x8F9308
const CResRef CGameSprite::SPIN202("SPIN202");

// 0x8F8E28
const CResRef CGameSprite::SPIN203("SPIN203");

// 0x8F9418
const CResRef CGameSprite::SPIN247("SPIN247");

// 0x8F9348
const CResRef CGameSprite::SPIN204("SPIN204");

// 0x8F9490
const CResRef CGameSprite::SPIN205("SPIN205");

// 0x8F92B0
const CResRef CGameSprite::SPIN206("SPIN206");

// 0x8F9458
const CResRef CGameSprite::SPIN207("SPIN207");

// 0x8F9470
const CResRef CGameSprite::SPIN208("SPIN208");

// 0x8F9498
const CResRef CGameSprite::SPIN209("SPIN209");

// 0x8F8E88
const CResRef CGameSprite::SPIN210("SPIN210");

// 0x8F94C0
const CResRef CGameSprite::SPIN231("SPIN231");

// 0x8F94A8
const CResRef CGameSprite::SPIN191("SPIN191");

// 0x8F8E48
const CResRef CGameSprite::SPIN211("SPIN211");

// 0x8F8E78
const CResRef CGameSprite::SPIN212("SPIN212");

// 0x8F8E40
const CResRef CGameSprite::SPIN213("SPIN213");

// 0x8F9428
const CResRef CGameSprite::SPIN214("SPIN214");

// 0x8F8E58
const CResRef CGameSprite::SPIN215("SPIN215");

// 0x8F94E8
const CResRef CGameSprite::SPIN216("SPIN216");

// 0x8F92C0
const CResRef CGameSprite::SPIN217("SPIN217");

// 0x8F9400
const CResRef CGameSprite::SPIN218("SPIN218");

// 0x8F9310
const CResRef CGameSprite::SPIN229("SPIN229");

// 0x8F94D8
const CResRef CGameSprite::SPIN232("SPIN232");

// 0x8F93E0
const CResRef CGameSprite::SPIN233("SPIN233");

// 0x8F8E68
const CResRef CGameSprite::SPIN234("SPIN234");

// 0x8F93D8
const CResRef CGameSprite::SPIN235("SPIN235");

// 0x8F9410
const CResRef CGameSprite::SPIN236("SPIN236");

// 0x8F8E20
const CResRef CGameSprite::SPIN260("SPIN260");

// 0x8F9340
const CString CGameSprite::FA("FA_");

// 0x8F9430
const CString CGameSprite::GA("GA_");

// 0x8F94E0
const CString CGameSprite::RA("RA_");

// 0x8F94C8
const CString CGameSprite::AP("AP_");

// 0x8F9480
const CResRef CGameSprite::SPWI110("SPWI110");

// 0x8F9408
const CResRef CGameSprite::SPIN122("SPIN122");

// 0x8F93F0
const CResRef CGameSprite::SPIN285("SPIN285");

// 0x8F9924
const CString CGameSprite::TOKEN_SPECIALABILITY("SPECIALABILITYNAME");

// 0x8F9350
BYTE CGameSprite::STATICBUFFER[STATICBUFFERSIZE_CGAMESPRITE];

// 0x8F950C
BOOLEAN CGameSprite::SHOW_CHARACTER_HP;

// 0x8F950D
BOOLEAN CGameSprite::GRAVITY_IS_DOWN;

// 0x8B85E0
INT CGameSprite::m_bRollFeedbackEnabled = -1;

// 0x8F9A18
CAIAction CGameSprite::m_aiDoAction;

// 0x6EF990
CGameSprite::CGameSprite(BYTE* pCreature, LONG creatureSize, int a3, WORD type, DWORD expirationTime, WORD huntingRange, WORD followRange, DWORD timeOfDayVisible, CPoint startPos, WORD facing)
    : m_portraitIconVidCell(CResRef("STATES"), g_pBaldurChitin->field_4A28)
{
    int index;

    field_7540 = 0;
    field_7544 = 0;
    m_spriteEffectSequenceLength = 0;
    m_spriteEffectBaseIntensity = 0;
    m_spriteEffectRandomIntensity = 0;
    m_bEscapingArea = 0;
    m_nSndWalk = 0;
    m_currSndWalk = 0;
    m_effectExtendDirection = 0;
    m_animationRunning = FALSE;
    m_posZDelta = 0;
    m_circleFacing = 0;
    m_radius = 0;
    m_fDirectionOffset = 0.0;
    m_skipDeltaDirection = 0;
    m_deltaDirection = 0;
    m_walkBackwards = FALSE;
    m_turningAbout = FALSE;
    m_bInCasting = FALSE;
    m_moveCount = 0;
    m_curDest.x = 0;
    m_curDest.y = 0;
    m_posLastVisMapEntry.x = 0;
    m_posLastVisMapEntry.y = 0;
    m_nCommandPause = 0;
    field_557A = 0;
    field_557E = 0;
    field_558E = 0;
    field_559E = 0;
    field_55A0 = 0;
    m_speedFactor = 0;
    m_lastActionID = 0;
    field_560E = 0;
    field_5610 = 0;
    field_5618 = 0;
    field_561C = 0;
    m_noActionCount = 0;
    field_5630 = 0;
    field_5632 = 0;
    field_5636 = 0;
    field_7118 = 0;
    field_711C = 0;
    m_firstActionSound = FALSE;
    m_bForceVisualEffects = FALSE;
    m_currentActionId = 0;
    field_72A8 = 0;
    m_bInUnmarshal = FALSE;
    field_72D6 = 0;
    field_72DE = 0;
    field_7532 = 0;
    field_7536 = 0;
    field_9D08 = 0;
    field_9D0C = 0;
    field_9D10 = 0;
    m_objectType = TYPE_SPRITE;
    m_resRef = "";
    m_fCircleChange = 0.0;
    m_fCurrCircleChange = 1.0;
    m_bGlobal = FALSE;
    m_posExact.x = 0;
    m_posExact.y = 0;
    m_posDelta.x = 0;
    m_posDelta.y = 0;
    m_posDest.x = 0;
    m_posDest.y = 0;
    m_posOld.x = 0;
    m_posOld.y = 0;
    field_536A = 0;
    field_536E = 0;
    m_nSequence = -1;
    m_nNewDirection = facing & 0xF;
    m_nDirection = facing & 0xF;
    m_pPath = 0;
    m_nPath = 0;
    m_currPath = 0;
    m_pathSearchInvalidDest = FALSE;
    m_selectedSound = 17;
    field_53D2 = 0;
    m_currentSearchRequest = 0;
    m_lastCharacterCount = 0;
    m_sequenceTest = FALSE;
    m_removeFromArea = FALSE;
    m_talkingCounter = 0;
    m_moveToFrontQueue = 0;
    m_moveToBackQueue = 0;
    m_curResponseNum = -1;
    m_curResponseSetNum = -1;
    m_curScriptNum = -1;
    m_curAction = CAIAction::NULL_ACTION;
    m_interrupt = FALSE;
    m_endOfDamageSeq = FALSE;
    m_inFormation = FALSE;
    m_lastRGBColor = 0x8000;
    m_bVisibilityUpdated = TRUE;
    m_targetId = CGameObjectArray::INVALID_INDEX;
    m_targetPoint.x = -1;
    m_targetPoint.y = -1;
    m_targetAreaSize = 0;
    m_destMarker.SetType(CMarker::RECTICLE);
    field_72E2 = CGameObjectArray::INVALID_INDEX;
    m_typeAI.Set(CAIObjectType::ANYONE);
    m_liveTypeAI.Set(CAIObjectType::ANYONE);
    m_startTypeAI.Set(CAIObjectType::ANYONE);
    m_overrideScript = 0;
    m_special1Script = 0;
    m_teamScript = 0;
    m_special2Script = 0;
    m_combatScript = 0;
    m_special3Script = 0;
    m_movementScript = NULL;
    m_followLeader = FALSE;
    m_followLeaderAdditive = FALSE;
    m_followLeaderNext = CGameObjectArray::INVALID_INDEX;
    m_followStart = 0;
    m_userCommandPause = 0;
    m_recoilFrame = 0;
    field_561E = 0;
    field_44A = 0;
    field_54C = 0;
    field_560C = 0;
    field_5616 = 0;
    field_5612 = 0;
    field_5614 = 0;
    m_castCounter = -1;
    m_bStartedCasting = FALSE;
    m_attackFrame = -2;
    field_72A2 = 0;
    m_bAllowEffectListCall = TRUE;
    field_72AA = 0;
    m_bForceVisualEffects = FALSE;
    field_5582 = 0;
    field_9D14 = 0;
    field_9D15 = 0;
    m_hasColorEffects = FALSE;
    m_hasColorRangeEffects = FALSE;
    field_5640 = 0;
    m_groupPosition = 0;
    m_groupMove = 0;
    field_562C = 0;
    m_curProjectile = 0;
    m_curSpell = 0;
    m_curItem = 0;
    m_nNumberOfTimesTalkedTo = 0;
    m_bSeenPartyBefore = 0;
    field_710A = 0;
    field_710C = 0;
    field_710E = 0;
    field_7110 = 0x7FFF;
    m_moraleFailure = FALSE;
    m_nHappiness = 0;
    m_bHappinessChanged = FALSE;
    m_bDeleteOnRemove = TRUE;
    m_lastRegenerationTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;

    CButtonData buttonData;

    for (index = 0; index < 8; index++) {
        m_quickWeapons[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        m_quickSpells[index] = buttonData;
    }

    for (index = 0; index < 3; index++) {
        m_quickItems[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        m_quickInnates[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        m_quickSongs[index] = buttonData;
    }

    field_70F6 = rand() % 20 + 1;
    field_70F7 = rand() % 20 + 1;
    field_70F8 = rand() % 20 + 1;
    field_70F9 = rand() % 20 + 1;
    field_70FA = rand() % 100;
    field_55F2 = 0;
    field_55F6 = 0;
    field_55FA = 0;
    field_55FE = 0;
    field_5602 = 0;

    for (index = 0; index < 20; index++) {
        field_55A2[index] = -65538;
    }

    memset(m_nNumberOfTimesInteractedWith, 0, sizeof(m_nNumberOfTimesInteractedWith));

    field_54B8 = 0;
    field_54A8 = 0;
    m_bBumped = FALSE;
    m_ptBumpedFrom.x = -1;
    m_ptBumpedFrom.y = -1;
    m_bVisibleMonster = FALSE;
    m_bSelected = FALSE;
    m_bInfravisionOn = FALSE;
    m_bPortraitUpdate = FALSE;
    m_nBloodFlashAmount = 0;
    m_nDamageLocatorTime = 0;
    m_nDamageLocatorColor = 0x1E1EFF;
    m_bBloodFlashOn = 0;
    field_53E6 = 0;
    m_nTwitches = 0;

    // NOTE: See `CGameArea` note on default terrain tables.
    memcpy(m_terrainTable, DEFAULT_TERRAIN_TABLE, 16);
    memcpy(m_visibleTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);
    memcpy(m_flightTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);

    if (g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id, this, INFINITE) == CGameObjectArray::SUCCESS) {
        m_pSpriteEffectArray = NULL;
        m_pSpriteEffectArrayPosition = NULL;
        m_spriteEffectDuration = 0;
        m_spriteEffectFlags = 0;
        field_5304 = 0;
        m_doBounce = 3;
        m_nModalState = 0;
        field_4C54[0] = 0;
        field_4C54[1] = 0;
        field_4C54[2] = 0;
        field_4C54[3] = 0;
        field_4C54[4] = 0;
        m_nWeaponSet = 0;

        field_7548[IWD_VFX_SANCTUARY].SetResRef(CResRef("SanctuC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_ENTANGLE].SetResRef(CResRef("EntangC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_MINOR_GLOBE_OF_INVULNERABILITY].SetResRef(CResRef("MGoInvC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SHIELD].SetResRef(CResRef("ShieldC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_GREASE].SetResRef(CResRef("GreaseC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_WEB].SetResRef(CResRef("WebC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_GLOBE_OF_INVULNERABILITY].SetResRef(CResRef("GoInvuC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SHROUD_OF_FLAME].SetResRef(CResRef("SoFlamC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_ANTIMAGIC_MISSILE].SetResRef(CResRef("AMShelC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_OTILUKES_RESILIENT_SPHERE].SetResRef(CResRef("ORSpheC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_PROTECTION_FROM_MISSILES].SetResRef(CResRef("PFNMisC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_CLOAK_OF_FEAR].SetResRef(CResRef("CoFearC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_ENTROPY_SHIELD].SetResRef(CResRef("EShielC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_FIRE_AURA].SetResRef(CResRef("FiAuraC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_FROST_AURA].SetResRef(CResRef("FrAuraC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_INSECT_PLAGUE].SetResRef(CResRef("IPlaguC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_STORM_SHELL].SetResRef(CResRef("SShellC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SHIELD_OF_LATHANDER].SetResRef(CResRef("SoLatC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SHIELD_OF_LATHANDER_2].SetResRef(CResRef("SoLatC2"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_GREATER_SHIELD_OF_LATHANDER].SetResRef(CResRef("GSoLaC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_GREATER_SHIELD_OF_LATHANDER_2].SetResRef(CResRef("GSoLaC2"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SEVEN_EYES].SetResRef(CResRef("SEyesC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_SEVEN_EYES_2].SetResRef(CResRef("SEyesC2"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_FIRE_SHIELD_RED].SetResRef(CResRef("FShiRC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_28].SetResRef(CResRef("FShiRC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_FIRE_SHIELD_BLUE].SetResRef(CResRef("FShiBC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_29].SetResRef(CResRef("FShiBC1"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_DEATH_ARMOR].SetResRef(CResRef("DArmorC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_TORTOISE_SHELL].SetResRef(CResRef("TShellC"), FALSE, TRUE, TRUE);
        field_7548[IWD_VFX_WISP].SetResRef(CResRef("Wisp"), FALSE, TRUE, TRUE);

        field_9088[IWD_VFX_GLOBE_OF_INVULNERABILITY].SetResRef(CResRef("AFT_M05"), TRUE, TRUE);
        field_9088[IWD_VFX_SHROUD_OF_FLAME].SetResRef(CResRef("MISC_01C"), TRUE, TRUE);
        field_9088[IWD_VFX_ANTIMAGIC_MISSILE].SetResRef(CResRef("AFT_M04"), TRUE, TRUE);
        field_9088[IWD_VFX_OTILUKES_RESILIENT_SPHERE].SetResRef(CResRef("AFT_M03"), TRUE, TRUE);
        field_9088[IWD_VFX_PROTECTION_FROM_MISSILES].SetResRef(CResRef("AFT_M01"), TRUE, TRUE);
        field_9088[IWD_VFX_CLOAK_OF_FEAR].SetResRef(CResRef("AFT_P02"), TRUE, TRUE);
        field_9088[IWD_VFX_ENTROPY_SHIELD].SetResRef(CResRef("AFT_P03"), TRUE, TRUE);
        field_9088[IWD_VFX_STORM_SHELL].SetResRef(CResRef("AFT_P25"), TRUE, TRUE);
        field_9088[IWD_VFX_SHIELD_OF_LATHANDER].SetResRef(CResRef("AFT_P20"), TRUE, TRUE);
        field_9088[IWD_VFX_GREATER_SHIELD_OF_LATHANDER].SetResRef(CResRef("AFT_P26"), TRUE, TRUE);
        field_9088[IWD_VFX_SANCTUARY].SetResRef(CResRef("AFT_P01"), TRUE, TRUE);
        field_9088[IWD_VFX_MINOR_GLOBE_OF_INVULNERABILITY].SetResRef(CResRef("AFT_M02"), TRUE, TRUE);
        field_9088[IWD_VFX_SHIELD].SetResRef(CResRef("EFF_M11C"), TRUE, TRUE);

        m_type = type;
        m_expirationTime = expirationTime;
        m_huntingRange = huntingRange;
        m_followRange = followRange;
        m_posStart = startPos;
        m_timeOfDayVisible = timeOfDayVisible;
        m_active = (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->GetCurrentHour() & 1) != 0;
        m_activeAI = TRUE;
        m_activeImprisonment = TRUE;

        memset(&m_baseStats, 0, sizeof(m_baseStats));

        m_pDialogData = NULL;
        m_nDialogData = 0;
        m_dialogWait = 0;
        m_dialogWaitTarget = CGameObjectArray::INVALID_INDEX;
        m_bAllowDialogInterrupt = TRUE;
        field_56E4 = "";
        m_talkingRenderCount = 0;
        m_clearAIOnRemoveFromArea = TRUE;

        if (m_portraitIconVidCell.pRes != NULL) {
            m_portraitIconVidCell.pRes->Request();
        }

        field_722A = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
        m_interactingWith.Set(CAIObjectType::NOONE);
        m_nHPCONBonusTotalOld = 0;
        m_bHPCONBonusTotalUpdate = TRUE;
        m_modalCounter = 0;
        m_bHiding = FALSE;
        m_secondarySounds = "";

        memset(field_725A, 0, sizeof(field_725A));

        field_727E = 0;
        m_pLocalVariables = new CVariableHash(16);
        m_internalButtonList = NULL;

        SleepEx(10, FALSE);
        Unmarshal(pCreature, creatureSize, facing, a3);
        SleepEx(10, FALSE);
        UnmarshalScripts();
        SleepEx(10, FALSE);

        // NOTE: Inlining as `STR_RES` object is immediately destroyed.
        if (1) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_name, strRes);
            m_sName = strRes.szText;
        }

        // NOTE: Uninline.
        FetchCommonStrings();

        for (index = 0; index < 2; index++) {
            m_sndWalk[index].m_nVolumeVariance = 50;
        }

        m_currSndArmor = 0;
        m_sndArmor[m_currSndArmor].m_nVolumeVariance = 50;
        m_animationRunning = (m_baseStats.m_animationType & 0xF000) != 0;
        m_triggerId = CGameObjectArray::INVALID_INDEX;
        field_562C = TRUE;
        m_firstCall = FALSE;
        m_berserkActive = FALSE;
        m_attackSoundDeadzone = 0;
        m_nTempSelectedWeapon = m_equipment.m_selectedWeapon;
        m_nTempSelectedWeaponAbility = static_cast<BYTE>(m_equipment.m_selectedWeaponAbility);

        SetSequence(SEQ_HEAD_TURN);
        CheckLoadState();

        m_bLevelUp = FALSE;
        m_nUnselectableCounter = 0;

        // NOTE: Uninline.
        m_inControlLastTime = InControl();

        m_nStealthGreyOut = 0;
        m_baseStats.m_flags &= ~0x80000000;

        INT bonusNew = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetHPCONBonusTotal(m_typeAI,
            m_derivedStats,
            static_cast<BYTE>(m_derivedStats.m_nCON));
        if (bonusNew > m_nHPCONBonusTotalOld) {
            if ((m_derivedStats.m_generalState & (STATE_DEAD | STATE_FROZEN_DEATH | STATE_STONE_DEATH)) == 0) {
                m_baseStats.m_hitPoints += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
            } else {
                m_baseStats.m_hitPoints = 0;
            }
            m_derivedStats.m_nMaxHitPoints += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
            m_baseStats.m_maxHitPointsBase += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
        } else if (bonusNew < m_nHPCONBonusTotalOld) {
            // NOTE: The code in this branch looks exactly the same as above. It
            // might be different in earlier games.
            if ((m_derivedStats.m_generalState & (STATE_DEAD | STATE_FROZEN_DEATH | STATE_STONE_DEATH)) == 0) {
                m_baseStats.m_hitPoints += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
            } else {
                m_baseStats.m_hitPoints = 0;
            }
            m_derivedStats.m_nMaxHitPoints += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
            m_baseStats.m_maxHitPointsBase += static_cast<SHORT>(bonusNew) - static_cast<SHORT>(m_nHPCONBonusTotalOld);
        }
        m_nHPCONBonusTotalOld = bonusNew;
        m_bHPCONBonusTotalUpdate = FALSE;
        m_derivedStats.m_nMaxHitPoints = max(m_derivedStats.m_nMaxHitPoints, m_derivedStats.m_nLevel);

        if (m_baseStats.m_hitPoints <= 0
            && (m_derivedStats.m_generalState & STATE_DEAD) == 0
            && (m_derivedStats.m_generalState & (STATE_STONE_DEATH | STATE_FROZEN_DEATH)) == 0
            && (m_baseStats.m_generalState & STATE_DEAD) != 0) {
            m_derivedStats.m_generalState |= STATE_DEAD;
        }

        field_7282 = -1;
        field_7283 = -1;
        field_7284 = -1;
        field_728E = -1;
        m_bPlayedEncumberedStopped = 0;
        m_bPlayedEncumberedSlowed = 0;
        field_72A0 = 0;
        m_nBounceCounter = 0;
        field_7106 = 0;

        sub_7204C0();

        field_70EE = 0;
        field_7430 = 0;
        field_70F2 = 0;
        if (IcewindMisc::IsLarge(this) == TRUE) {
            field_7548[IWD_VFX_OTILUKES_RESILIENT_SPHERE].SetResRef(CResRef("ORSpheB"), FALSE, TRUE, TRUE);
        }

        field_753A = 0;
        field_753C = 0;
    } else {
        // FIXME: Does not look cool.
        delete this;
    }
}

// 0x6F2990
BOOL CGameSprite::DoesIntersect(CRect r)
{
    r.InflateRect(0, 0, 1, 1);

    CRect rEllipse = m_animation.GetEllipseRect();
    rEllipse.OffsetRect(m_pos);

    CRect rIntersection;
    rIntersection.IntersectRect(r, rEllipse);

    return !rIntersection.IsRectNull();
}

// 0x6F2A90
BOOL CGameSprite::IsOver(const CPoint& pt)
{
    if (m_active
        && m_activeAI
        && m_activeImprisonment
        && Animate()
        && m_baseStats.field_294 == 0
        && (m_typeAI.GetEnemyAlly() <= CAIObjectType::EA_GOODCUTOFF
            || (m_derivedStats.m_generalState & STATE_INVISIBLE) == 0
            || (m_baseStats.field_2FC & 0x1) != 0)) {
        const CRect& rEllipse = m_animation.GetEllipseRect();
        CPoint ptRelative(pt.x - m_pos.x, pt.y - m_pos.y);
        return rEllipse.PtInRect(ptRelative);
    } else {
        return FALSE;
    }
}

// 0x6F2B50
const BYTE* CGameSprite::GetVisibleTerrainTable()
{
    return m_visibleTerrainTable;
}

// 0x6F2B60
BOOL CGameSprite::OnSearchMap()
{
    return ((m_listType == LIST_FRONT || (m_derivedStats.m_generalState & STATE_SLEEPING) != 0))
        && m_pArea != NULL
        && m_pos.x >= 0
        && m_pos.y >= 0;
}

// 0x6F2B90
void CGameSprite::SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart)
{
    m_typeAI.Set(typeAI);

    if (updateLive) {
        m_liveTypeAI.Set(typeAI);
    }

    if (updateStart) {
        m_startTypeAI.Set(typeAI);
    }
}

// 0x6F2BD0
void CGameSprite::ResetAITypeLive()
{
    m_typeAI.m_nGeneral = m_liveTypeAI.m_nGeneral;
    m_startTypeAI.m_nGeneral = m_liveTypeAI.m_nGeneral;
}

// 0x6F2BF0
void CGameSprite::ResetAIType()
{
    m_typeAI.Set(m_startTypeAI);

    BYTE prev = m_liveTypeAI.m_nGeneral;
    m_liveTypeAI.Set(m_startTypeAI);
    m_liveTypeAI.m_nGeneral = prev;
}

// 0x6F2C50
LONG CGameSprite::GetTargetId()
{
    return m_targetId;
}

// 0x6F2C60
const BYTE* CGameSprite::GetTerrainTable()
{
    return m_terrainTable;
}

// 0x6F2C70
BOOL CGameSprite::GetCanSeeInvisible()
{
    return m_curAction.m_actionID == CAIAction::DIALOGUE
        || m_curAction.m_actionID == CAIAction::STARTDIALOG
        || m_curAction.m_actionID == CAIAction::STARTDIALOGUENOSET
        || m_derivedStats.m_bSeeInvisible
        || (m_baseStats.m_flags & 0x10000) != 0;
}

// 0x6F40F0
void CGameSprite::AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType)
{
    BOOLEAN v1 = FALSE;

    CGameObject::AddToArea(pNewArea, pos, posZ, listType);
    m_posExact.x = m_pos.x << 10;
    m_posExact.y = (m_pos.y << 12) / 3;
    m_posOld = m_pos;
    field_562C = 1;

    if (m_active && m_activeAI && m_activeImprisonment) {
        CheckIfVisible();
    }

    switch (listType) {
    case CGAMEOBJECT_LIST_FRONT:
        if (m_active
            && m_activeAI
            && m_activeImprisonment
            && (m_derivedStats.m_generalState & STATE_DEAD) == 0) {
            // NOTE: Uninline.
            pNewArea->AddToMarkers(m_id);

            m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                            m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                m_typeAI.GetEnemyAlly(),
                m_animation.GetPersonalSpace(),
                field_54A8,
                field_7430);
        }
        break;
    case CGAMEOBJECT_LIST_BACK:
        if (m_active && m_activeAI && m_activeImprisonment) {
            pNewArea->IncrHeightDynamic(m_pos);
        }
        break;
    case CGAMEOBJECT_LIST_FLIGHT:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 1528
        UTIL_ASSERT(FALSE);
    }

    SetFootstepChannel();

    if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0) {
        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
            || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1) {
            char* pSndReady = m_animation.GetSndReady();
            if (*pSndReady != '\0') {
                m_sndReady.SetResRef(CResRef(pSndReady), TRUE, TRUE);
                delete pSndReady;
                m_sndReady.SetLoopingFlag(1);
                m_sndReady.Play(m_pos.x, m_pos.y, m_posZ, FALSE);
            }
        }
    }

    m_currentArea = pNewArea->m_resRef;

    if (m_bGlobal) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 1548
        UTIL_ASSERT(pGame != NULL);

        if (pGame->GetCharacterPortraitNum(m_id) != -1
            && Animate()) {
            m_posLastVisMapEntry = pos;
            pNewArea->m_visibility.AddCharacter(m_posLastVisMapEntry,
                m_id,
                m_visibleTerrainTable);
            if (pNewArea->m_nCharacters != -1) {
                pNewArea->m_nCharacters++;
            } else {
                pNewArea->m_nCharacters = 1;
            }
        }
    } else if (m_type == 1) {
        pNewArea->m_nRandomMonster++;
    }

    if (!g_pBaldurChitin->GetObjectGame()->m_bInLoadGame
        && !g_pBaldurChitin->GetObjectGame()->m_bInLoadArea
        && !g_pBaldurChitin->GetObjectGame()->m_bInAreaTransition
        && !g_pBaldurChitin->GetBaldurMessage()->m_bInOnObjectAdd) {
        BYTE* pData = STATICBUFFER;
        DWORD dwSize;
        MarshalMessage(&pData, &dwSize);
        g_pBaldurChitin->GetBaldurMessage()->ObjectAdd(m_id, GetObjectType(), pData, dwSize);

        if (InControl()
            && g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            m_cLastSpriteUpdate.Initialize(TRUE);
            CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }

        v1 = TRUE;
    }

    if (m_pArea == NULL) {
        // FIXME: Unused.
        CString sText("Sprite ");
        if (m_sName.GetLength() != 0) {
            sText += m_sName;
        } else {
            sText += "Unknown";
        }
        sText += " has a NULL m_pArea member in AddToArea() function!";
    }

    if (pNewArea != NULL) {
        if (g_pBaldurChitin->GetObjectGame()->m_bInLoadGame
            && pNewArea->mpSpawner->m_bInSpawn == TRUE
            && !v1) {
            BYTE* pData = STATICBUFFER;
            DWORD dwSize;
            MarshalMessage(&pData, &dwSize);
            g_pBaldurChitin->GetBaldurMessage()->ObjectAdd(m_id, GetObjectType(), pData, dwSize);
        }
    }

    if (m_baseStats.field_294) {
        m_baseStats.field_294 = FALSE;
        sub_75F3D0(1);
        if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            CMessage* message = new CMessage90(m_id, m_id, 1);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
    }

    if (m_baseStats.field_2F8) {
        m_removeFromArea = TRUE;
    }

    if (!m_baseStats.field_2E2) {
        sub_75F240();
        m_baseStats.field_2E2 = TRUE;
    }

    Icewind586B70::Instance()->sub_586FC0(this);
}

// 0x6F47F0
void CGameSprite::RemoveReplacementFromArea()
{
    if (m_pArea != NULL) {
        m_sndReady.Stop();
        DropSearchRequest();
        if (m_bInfravisionOn) {
            m_bInfravisionOn = FALSE;
            m_pArea->m_nInfravision--;
        }

        if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1) {
            if (!g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC || InControl()) {
                if (Animate()) {
                    m_pArea->m_visibility.RemoveCharacter(m_pos,
                        m_id,
                        m_visibleTerrainTable);
                }

                if (m_pArea->m_nCharacters != -1) {
                    m_pArea->m_nCharacters--;
                }
            }
        }

        ClearStoredPaths();

        if (m_pPath != NULL) {
            delete m_pPath;
            m_pPath = NULL;
        }

        if (m_clearAIOnRemoveFromArea) {
            ClearAI(TRUE);
        }

        m_nNewDirection = m_nDirection;
        g_pBaldurChitin->GetObjectGame()->RemoveCharacterFromAllies(m_id);

        switch (m_listType) {
        case CGAMEOBJECT_LIST_FRONT:
            if (m_active
                && m_activeAI
                && m_activeImprisonment) {
                if ((m_derivedStats.m_generalState & STATE_DEAD) == 0) {
                    // NOTE: Uninline.
                    m_pArea->RemoveFromMarkers(m_id);
                }

                m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                   m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
            }
            break;
        case CGAMEOBJECT_LIST_BACK:
            if (m_active
                && m_activeAI
                && m_activeImprisonment) {
                if ((m_derivedStats.m_generalState & STATE_SLEEPING) != 0) {
                    // NOTE: Uninline.
                    m_pArea->RemoveFromMarkers(m_id);

                    m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                       m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                        m_typeAI.GetEnemyAlly(),
                        m_animation.GetPersonalSpace(),
                        field_54A8,
                        field_7430);
                } else {
                    m_pArea->DecrHeightDynamic(m_pos);
                }
            }
            break;
        case CGAMEOBJECT_LIST_FLIGHT:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 1773
            UTIL_ASSERT(FALSE);
        }

        if (m_bGlobal) {
            m_pArea = NULL;
            m_pos.x = -1;
            m_pos.y = -1;
            m_posZ = 0;
        } else {
            if (m_type == 1) {
                m_pArea->m_nRandomMonster--;
            }

            CGameObject::RemoveFromArea();

            BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
                CGameObjectArray::THREAD_ASYNCH,
                NULL,
                INFINITE);
            if (rc != CGameObjectArray::SUCCESS) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 1783
                UTIL_ASSERT(FALSE);
            }

            delete this;
        }
    }
}

// 0x6F4B90
void CGameSprite::RemoveFromArea()
{
    if (m_pArea != NULL) {
        POSITION pos = m_lstBlood.GetHeadPosition();
        while (pos != NULL) {
            CBlood* pBlood = m_lstBlood.GetNext(pos);
            delete pBlood;
        }
        m_lstBlood.RemoveAll();

        m_sndReady.Stop();
        DropSearchRequest();

        if (m_bBumped) {
            m_ptBumpedFrom.x = -1;
            m_ptBumpedFrom.y = -1;
            m_bBumped = FALSE;
        }

        if (m_bVisibleMonster) {
            m_pArea->m_nVisibleMonster--;
            m_bVisibleMonster = FALSE;
        }

        if (m_bInfravisionOn) {
            m_pArea->m_nInfravision--;
            m_bInfravisionOn = FALSE;
        }

        if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1) {
            if (!g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC || InControl()) {
                if (Animate()) {
                    m_pArea->m_visibility.RemoveCharacter(m_pos,
                        m_id,
                        m_visibleTerrainTable);
                }

                if (m_pArea->m_nCharacters != -1) {
                    m_pArea->m_nCharacters--;
                }
            }
        }

        ClearStoredPaths();

        if (m_pPath != NULL) {
            delete m_pPath;
            m_pPath = NULL;
        }

        if (m_clearAIOnRemoveFromArea) {
            ClearAI(TRUE);
        }

        m_nNewDirection = m_nDirection;
        g_pBaldurChitin->GetObjectGame()->RemoveCharacterFromAllies(m_id);

        switch (m_listType) {
        case CGAMEOBJECT_LIST_FRONT:
            if (m_active
                && m_activeAI
                && m_activeImprisonment) {
                if ((m_derivedStats.m_generalState & STATE_DEAD) == 0) {
                    // NOTE: Uninline.
                    m_pArea->RemoveFromMarkers(m_id);
                }

                m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                   m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
            }
            break;
        case CGAMEOBJECT_LIST_BACK:
            if (m_active
                && m_activeAI
                && m_activeImprisonment) {
                if ((m_derivedStats.m_generalState & STATE_SLEEPING) != 0) {
                    // NOTE: Uninline.
                    m_pArea->RemoveFromMarkers(m_id);

                    m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                       m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                        m_typeAI.GetEnemyAlly(),
                        m_animation.GetPersonalSpace(),
                        field_54A8,
                        field_7430);
                } else {
                    m_pArea->DecrHeightDynamic(m_pos);
                }
            }
            break;
        case CGAMEOBJECT_LIST_FLIGHT:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 1922
            UTIL_ASSERT(FALSE);
        }

        if (m_bGlobal) {
            CPoint pos(m_pos);

            CGameObject::RemoveFromArea();

            if (InControl() && g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                if (!g_pBaldurChitin->GetObjectGame()->m_bInDestroyGame
                    && !g_pBaldurChitin->GetObjectGame()->m_bInAreaTransition) {
                    m_cLastSpriteUpdate.Initialize(TRUE);

                    CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }
            }

            m_pos = pos;
        } else {
            if (m_type == 1) {
                m_pArea->m_nRandomMonster--;
            }

            CGameObject::RemoveFromArea();

            if (m_bDeleteOnRemove) {
                BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
                    CGameObjectArray::THREAD_ASYNCH,
                    NULL,
                    INFINITE);
                if (rc != CGameObjectArray::SUCCESS) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                    // __LINE__: 1934
                    UTIL_ASSERT(FALSE);
                }

                delete this;
            }
        }
    }
}

// 0x6F5FF0
void CGameSprite::AIUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (m_inControlLastTime != InControl()) {
        JumpToPoint(m_pos, TRUE);
    }

    m_inControlLastTime = InControl();

    if (pGame->GetWorldTimer()->m_active) {
        if ((m_baseStats.m_generalState & STATE_FADE_OUT) != 0) {
            if (static_cast<int>(m_baseStats.field_2F9 + m_baseStats.m_fadeSpeed) > 255) {
                m_baseStats.m_generalState &= ~STATE_FADE_OUT;
                m_derivedStats.m_generalState &= ~STATE_FADE_OUT;
                m_baseStats.field_2F9 = -1;
            } else {
                m_baseStats.field_2F9 += m_baseStats.m_fadeSpeed;
            }
        } else if ((m_baseStats.m_generalState & STATE_FADE_IN) != 0) {
            if (static_cast<int>(m_baseStats.field_2F9 - m_baseStats.m_fadeSpeed) < 0) {
                m_baseStats.m_generalState &= ~STATE_FADE_IN;
                m_derivedStats.m_generalState &= ~STATE_FADE_IN;
                m_baseStats.field_2F9 = -1;
            } else {
                m_baseStats.field_2F9 -= m_baseStats.m_fadeSpeed;
            }
        }

        field_70F6 = rand() % 20 + 1;
        field_70F7 = rand() % 20 + 1;
        field_70F8 = rand() % 20 + 1;
        field_70F9 = rand() % 20 + 1;
        field_70FA = rand() % 100;

        if (m_nBounceCounter <= 0) {
            m_nBounceCounter = 25;
            m_lBounceList.Process(this);
        }
        m_nBounceCounter--;

        if (m_nStealthGreyOut > 0) {
            m_nStealthGreyOut--;

            if (g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter() == pGame->GetCharacterPortraitNum(m_id)) {
                INT nState = pGame->GetButtonArray()->m_nState;
                if (nState != 102
                    && nState != 101
                    && nState != 104
                    && nState != 103
                    && nState != 105
                    && nState != 112
                    && nState != 115
                    && nState != 116
                    && nState != 117
                    && nState != 118
                    && nState != 119
                    && nState != 120
                    && nState != 121
                    && nState != 122
                    && nState != 123
                    && nState != 106) {
                    pGame->GetButtonArray()->ResetState();
                }
            }

            if (m_nStealthGreyOut == 0) {
                if (g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter() == pGame->GetCharacterPortraitNum(m_id)) {
                    INT nState = pGame->GetButtonArray()->m_nState;
                    if (nState != 102
                        && nState != 101
                        && nState != 104
                        && nState != 103
                        && nState != 105
                        && nState != 112
                        && nState != 115
                        && nState != 116
                        && nState != 117
                        && nState != 118
                        && nState != 119
                        && nState != 120
                        && nState != 121
                        && nState != 122
                        && nState != 123
                        && nState != 106) {
                        pGame->GetButtonArray()->UpdateState();
                    }
                }
            }
        }

        if (m_attackSoundDeadzone > 0) {
            m_attackSoundDeadzone--;
        }

        if (m_expirationTime < pGame->GetWorldTimer()->m_gameTime
            && (!m_active || m_canBeSeen <= 0)) {
            RemoveFromArea();
            return;
        }

        if (m_active) {
            if (((m_timeOfDayVisible >> pGame->GetWorldTimer()->GetCurrentHour()) & 0x1) == 0
                && m_canBeSeen <= 0) {
                m_active = FALSE;
                if (m_pPath != NULL) {
                    delete m_pPath;
                    m_pPath = NULL;
                }

                DropSearchRequest();

                switch (m_listType) {
                case CGAMEOBJECT_LIST_FRONT:
                    if ((m_derivedStats.m_generalState & STATE_DEAD) == 0) {
                        // NOTE: Uninline.
                        m_pArea->RemoveFromMarkers(m_id);
                    }

                    m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                       m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                        m_typeAI.GetEnemyAlly(),
                        m_animation.GetPersonalSpace(),
                        field_54A8,
                        field_7430);
                    break;
                case CGAMEOBJECT_LIST_BACK:
                    if ((m_derivedStats.m_generalState & STATE_SLEEPING) != 0) {
                        // NOTE: Uninline.
                        m_pArea->RemoveFromMarkers(m_id);

                        m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                           m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                            m_typeAI.GetEnemyAlly(),
                            m_animation.GetPersonalSpace(),
                            field_54A8,
                            field_7430);
                    } else {
                        m_pArea->IncrHeightDynamic(m_pos);
                    }
                    break;
                case CGAMEOBJECT_LIST_FLIGHT:
                    break;
                default:
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                    // __LINE__: 2424
                    UTIL_ASSERT(FALSE);
                }
            }
        } else {
            if (((m_timeOfDayVisible >> pGame->GetWorldTimer()->GetCurrentHour()) & 0x1) != 0) {
                if (m_canBeSeen > 0) {
                    m_canBeSeen--;
                    if (m_canBeSeen == 0) {
                        if (m_bVisibleMonster) {
                            m_bVisibleMonster = FALSE;
                            m_pArea->m_nVisibleMonster--;
                        }
                    }
                }

                if ((pGame->GetWorldTimer()->m_gameTime & VISIBLE_DELAY) == (m_id & VISIBLE_DELAY)) {
                    CheckIfVisible();
                }

                if (m_canBeSeen <= 0) {
                    m_active = TRUE;

                    switch (m_listType) {
                    case CGAMEOBJECT_LIST_FRONT:
                        if (m_baseStats.field_294 != TRUE) {
                            if ((m_derivedStats.m_generalState & STATE_DEAD) == 0) {
                                // NOTE: Uninline.
                                m_pArea->AddToMarkers(m_id);
                            }

                            m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                            m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                                m_typeAI.GetEnemyAlly(),
                                m_animation.GetPersonalSpace(),
                                field_54A8,
                                field_7430);

                            JumpToPoint(m_pos, TRUE);
                        }
                        break;
                    case CGAMEOBJECT_LIST_BACK:
                        if (m_baseStats.field_294 != TRUE) {
                            if ((m_derivedStats.m_generalState & STATE_SLEEPING) != 0) {
                                m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                                m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                                    m_typeAI.GetEnemyAlly(),
                                    m_animation.GetPersonalSpace(),
                                    field_54A8,
                                    field_7430);

                                // NOTE: Uninline.
                                m_pArea->AddToMarkers(m_id);

                                JumpToPoint(m_pos, TRUE);
                            } else {
                                m_pArea->IncrHeightDynamic(m_pos);
                            }
                        }
                        break;
                    case CGAMEOBJECT_LIST_FLIGHT:
                        break;
                    default:
                        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                        // __LINE__: 2488
                        UTIL_ASSERT(FALSE);
                    }
                }
            }
        }
    }

    if ((m_derivedStats.m_generalState & STATE_HELPLESS) == 0
        || (m_derivedStats.m_generalState & STATE_SLEEPING) != 0) {
        if ((m_derivedStats.m_generalState & STATE_DEAD) == 0 || m_nSequence == SEQ_DIE) {
            m_animationRunning = TRUE;
        }
    } else {
        m_animationRunning = FALSE;
    }

    if (m_AIInhibitor) {
        return;
    }

    if (pGame->GetCharacterPortraitNum(m_id) != CGameObjectArray::INVALID_INDEX
        && (m_derivedStats.m_generalState & STATE_DEAD) == 0) {
        if ((m_typeAI.GetRace() == CAIOBJECTTYPE_R_ELF
                && m_typeAI.GetSubRace() == CAIOBJECTTYPE_SUBRACE_ELF_DROW)
            || (m_typeAI.GetRace() == CAIOBJECTTYPE_R_DWARF
                && m_typeAI.GetSubRace() == CAIOBJECTTYPE_SUBRACE_DWARF_GRAY)) {
            if ((pGame->GetWorldTimer()->IsDay() || pGame->GetWorldTimer()->IsDawn())
                && m_pArea != NULL
                && (m_pArea->GetHeader()->m_areaType & 0x1) != 0
                && (m_pArea->GetHeader()->m_areaType & 0x2) != 0
                && (m_pArea->GetHeader()->m_areaType & 0x40) == 0) {
                // NOTE: Uninline.
                AddPortraitIcon(137);

                if (InControl() && !m_timedEffectList.IsTypeOnList(ICEWIND_CGAMEEFFECT_DAYBLINDNESS)) {
                    ITEM_EFFECT effect;
                    CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_DAYBLINDNESS);

                    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
                        GetPos(),
                        m_id,
                        CPoint(-1, -1));

                    CMessage* message = new CMessageAddEffect(pEffect, m_id, m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }
            } else {
                if (InControl() && m_timedEffectList.IsTypeOnList(ICEWIND_CGAMEEFFECT_DAYBLINDNESS)) {
                    m_timedEffectList.RemoveAllOfType(this,
                        ICEWIND_CGAMEEFFECT_DAYBLINDNESS,
                        m_timedEffectList.GetPosCurrent(),
                        -1);
                }
            }
        }
    }

    ProcessAI();

    if (m_bSendSpriteUpdate == TRUE) {
        CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        m_bSendSpriteUpdate = FALSE;
    }

    if (m_talkingCounter > 0) {
        m_talkingCounter--;
    }

    if (m_removeFromArea) {
        if (m_bSelected) {
            Unselect();
            pGame->SelectToolbar();
        }
        RemoveFromArea();
        return;
    }

    if (m_pArea == NULL || m_baseStats.field_294 == TRUE) {
        return;
    }

    if (m_pArea->m_iPicked == m_id) {
        m_bPortraitUpdate = TRUE;
        pGame->UpdatePortrait(pGame->GetCharacterPortraitNum(m_id), 1);
    } else if (m_bPortraitUpdate) {
        m_bPortraitUpdate = FALSE;
        pGame->UpdatePortrait(pGame->GetCharacterPortraitNum(m_id), 1);
    }

    m_marker.AsynchronousUpdate(this);

    if (Orderable(FALSE)
        && (m_bSelected || m_id == m_pArea->m_iPicked)
        && m_targetPoint.x != -1) {
        m_destMarker.AsynchronousUpdate(this);
    }

    if (((m_pArea->GetInfinity()->m_areaType & 0x20) != 0
            || ((m_pArea->GetInfinity()->m_areaType & 0x2) != 0
                && pGame->GetWorldTimer()->IsNight()))
        && m_bSelected
        && pGame->GetCharacterPortraitNum(m_id) != -1
        && (pGame->GetOptions()->m_bDarkvision
            || pGame->GetGroup()->GetCount() == 1)
        && (m_derivedStats.m_generalState & STATE_SLEEPING) == 0
        && (m_derivedStats.m_generalState & STATE_INFRAVISION) != 0) {
        CPoint pt;
        pt.x = m_pos.x;
        pt.y = m_pos.y + m_posZ + m_pArea->GetHeightOffset(m_pos, m_listType);
        COLORREF rgbTintColor = m_pArea->GetTintColor(pt, m_listType);
        BYTE v3 = static_cast<BYTE>((299 * GetRValue(CInfinity::RGB_NIGHT_COLOR) + 587 * GetGValue(CInfinity::RGB_NIGHT_COLOR) + 114 * GetBValue(CInfinity::RGB_NIGHT_COLOR)) / 2550);
        BYTE v4;
        if ((m_pArea->GetInfinity()->m_areaType & 0x2) == 0
            || ((m_pArea->GetInfinity()->m_areaType & 0x40) != 0
                && (m_pArea->GetInfinity()->m_renderDayNightCode & 0x2) != 0)) {
            v4 = static_cast<BYTE>((299 * GetRValue(rgbTintColor) + 587 * GetGValue(rgbTintColor) + 114 * GetBValue(rgbTintColor)) / 2550);
        } else {
            // TODO: Unclear math (merging global tint with area tint).
            v4 = 0;
        }

        if (v4 > v3) {
            if (m_bInfravisionOn) {
                m_bInfravisionOn = FALSE;
                m_pArea->m_nInfravision--;
            }
        } else {
            if (!m_bInfravisionOn) {
                m_bInfravisionOn = TRUE;
                m_pArea->m_nInfravision++;
            }
        }
    } else {
        if (m_bInfravisionOn) {
            m_bInfravisionOn = FALSE;
            m_pArea->m_nInfravision--;
        }
    }

    if (!pGame->GetWorldTimer()->m_active) {
        if (m_active
            && m_activeAI
            && m_activeImprisonment
            && m_lastCharacterCount != m_pArea->m_nCharacters) {
            CheckIfVisible();
        }
        m_lastCharacterCount = m_pArea->m_nCharacters;
        return;
    }

    BOOL v1 = sub_6FB440();
    if (v1 != field_54A8
        && Animate()
        && !m_baseStats.field_294) {
        if (!v1) {
            m_bBumped = FALSE;
            m_ptBumpedFrom.x = -1;
            m_ptBumpedFrom.y = -1;
        }

        m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                           m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
            m_typeAI.GetEnemyAlly(),
            m_animation.GetPersonalSpace(),
            field_54A8,
            field_7430);

        field_54A8 = v1;

        m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                        m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
            m_typeAI.GetEnemyAlly(),
            m_animation.GetPersonalSpace(),
            field_54A8,
            field_7430);
    }

    if (m_bBumped && !m_baseStats.field_294) {
        m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                           m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
            m_typeAI.GetEnemyAlly(),
            m_animation.GetPersonalSpace(),
            field_54A8,
            field_7430);

        SHORT nTableIndex;
        if (m_pArea->m_search.GetCost(m_ptBumpedFrom, GetTerrainTable(), m_animation.GetPersonalSpace(), nTableIndex, TRUE) != CPathSearch::COST_IMPASSABLE) {
            m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                            m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                m_typeAI.GetEnemyAlly(),
                m_animation.GetPersonalSpace(),
                field_54A8,
                field_7430);
            JumpToPoint(CPoint(m_ptBumpedFrom.x * CPathSearch::GRID_SQUARE_SIZEX + CPathSearch::GRID_SQUARE_SIZEX / 2,
                            m_ptBumpedFrom.y * CPathSearch::GRID_SQUARE_SIZEY + CPathSearch::GRID_SQUARE_SIZEY / 2),
                TRUE);
            m_bBumped = FALSE;
            m_ptBumpedFrom.x = -1;
            m_ptBumpedFrom.y = -1;
        } else {
            if (!m_baseStats.field_294) {
                m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
            }
        }
    }

    if (m_nBloodFlashAmount > 0) {
        m_nBloodFlashAmount -= 5;
        if (m_nBloodFlashAmount < 0) {
            m_nBloodFlashAmount = 0;
        }
        pGame->UpdatePortrait(pGame->GetCharacterPortraitNum(m_id), 1);
    }

    if (m_nDamageLocatorTime > 0) {
        ULONG nQuarterPeriod = CMarker::PICKED_FLASH_PERIOD / 4;
        ULONG nAsyncCounter = g_pBaldurChitin->nAUCounter % CMarker::PICKED_FLASH_PERIOD;
        COLORREF rgbDamageColor = RGB(255, 30, 30);
        BYTE red;
        BYTE green;
        BYTE blue;

        // TODO: Check, probably wrong.
        if (nAsyncCounter < nQuarterPeriod) {
            red = static_cast<BYTE>(nAsyncCounter * GetRValue(rgbDamageColor) / nQuarterPeriod);
            green = static_cast<BYTE>(nAsyncCounter * GetGValue(rgbDamageColor) / nQuarterPeriod);
            blue = static_cast<BYTE>(nAsyncCounter * GetBValue(rgbDamageColor) / nQuarterPeriod);
        } else if (nAsyncCounter < nQuarterPeriod * 2) {
            nAsyncCounter -= nQuarterPeriod;
            red = static_cast<BYTE>(GetRValue(rgbDamageColor) + nAsyncCounter * (255 - GetRValue(rgbDamageColor)) / nQuarterPeriod);
            green = static_cast<BYTE>(GetGValue(rgbDamageColor) + nAsyncCounter * (255 - GetGValue(rgbDamageColor)) / nQuarterPeriod);
            blue = static_cast<BYTE>(GetBValue(rgbDamageColor) + nAsyncCounter * (255 - GetBValue(rgbDamageColor)) / nQuarterPeriod);
        } else if (nAsyncCounter < nQuarterPeriod * 3) {
            nAsyncCounter -= nQuarterPeriod * 2;
            red = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetRValue(rgbDamageColor)) / nQuarterPeriod);
            green = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetGValue(rgbDamageColor)) / nQuarterPeriod);
            blue = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetBValue(rgbDamageColor)) / nQuarterPeriod);
        } else {
            nAsyncCounter -= nQuarterPeriod * 3;
            red = static_cast<BYTE>(GetRValue(rgbDamageColor) - nAsyncCounter * GetRValue(rgbDamageColor) / nQuarterPeriod);
            green = static_cast<BYTE>(GetGValue(rgbDamageColor) - nAsyncCounter * GetGValue(rgbDamageColor) / nQuarterPeriod);
            blue = static_cast<BYTE>(GetBValue(rgbDamageColor) - nAsyncCounter * GetBValue(rgbDamageColor) / nQuarterPeriod);
        }

        m_nDamageLocatorColor = RGB(red, green, blue);

        m_nDamageLocatorTime--;
    }

    if (!m_lstBlood.IsEmpty()) {
        POSITION pos = m_lstBlood.GetHeadPosition();
        while (pos != NULL) {
            POSITION posOld = pos;
            CBlood* pBlood = m_lstBlood.GetNext(pos);
            if (!pBlood->AsynchronousUpdate()) {
                m_lstBlood.RemoveAt(posOld);
                delete pBlood;
            }
        }
    }

    if (m_AISpeed == AI_SPEED_SLOWED) {
        if (m_active
            && m_activeAI
            && m_activeImprisonment
            && ((pGame->GetWorldTimer()->m_gameTime / 2) & VISIBLE_DELAY) == ((m_id / 2) & VISIBLE_DELAY)) {
            CheckIfVisible();
        }
    } else {
        if (m_active
            && m_activeAI
            && m_activeImprisonment
            && (pGame->GetWorldTimer()->m_gameTime & VISIBLE_DELAY) == (m_id & VISIBLE_DELAY)) {
            CheckIfVisible();
        }
    }

    m_lastCharacterCount = m_pArea->m_nCharacters;

    if (m_canBeSeen > 0) {
        m_canBeSeen--;
        if (m_canBeSeen == 0) {
            if (m_bVisibleMonster) {
                m_bVisibleMonster = FALSE;
                m_pArea->m_nVisibleMonster--;
            }
        }
    }

    UpdateSpriteEffect();

    if (m_animationRunning) {
        if (m_posZ < 0) {
            m_posZ -= m_posZDelta;
            m_posZDelta--;
            if (m_posZ >= 0) {
                m_posZ = 0;
                if (m_doBounce > 0) {
                    m_posZ = -1;
                    m_posZDelta = m_doBounce * (rand() % 3 + 1);
                    m_doBounce--;
                } else {
                    m_animationRunning = FALSE;
                }
            }
        }

        if (m_active) {
            if (pGame->m_nTimeStop == 0 || pGame->m_nTimeStopCaster == m_id) {
                ChangeDirection();
                if (m_nSequence == CGAMESPRITE_SEQ_ATTACK
                    || m_nSequence == CGAMESPRITE_SEQ_SHOOT
                    || m_nSequence == CGAMESPRITE_SEQ_ATTACK_SLASH
                    || m_nSequence == CGAMESPRITE_SEQ_ATTACK_BACKSLASH
                    || m_nSequence == CGAMESPRITE_SEQ_ATTACK_JAB) {
                    SHORT lSlot;
                    CItem* pItem = m_equipment.m_items[m_equipment.m_selectedWeapon];
                    pItem->Demand();
                    sub_756930(pItem, GetLauncher(pItem->GetAbility(m_equipment.m_selectedWeaponAbility), lSlot));
                    pItem->Release();
                }
                switch (m_nSequence) {
                case CGAMESPRITE_SEQ_ATTACK:
                    if (m_animation.IsEndOfSequence()) {
                        SetSequence(CGAMESPRITE_SEQ_READY);
                    } else {
                        if (m_animation.GetCurrentFrame() == field_740C) {
                            CSound cSound;
                            cSound.SetResRef(field_7408, TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(3, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_AWAKE:
                    if (m_animation.GetAnimationId() < 0xE000) {
                        if (m_animation.IsBeginningOfSequence()) {
                            // NOTE: Uninline.
                            SetIdleSequence();
                        } else {
                            m_animation.DecrementFrame();
                        }
                    } else {
                        if (m_animation.IsEndOfSequence()) {
                            // NOTE: Uninline.
                            SetIdleSequence();
                        } else {
                            m_animation.IncrementFrame();
                        }
                    }
                    break;
                case CGAMESPRITE_SEQ_CAST:
                    if (m_animation.IsEndOfSequence()) {
                        SetSequence(GetIdleSequence());
                    } else {
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_CONJURE:
                    m_animation.IncrementFrame();
                    break;
                case CGAMESPRITE_SEQ_DAMAGE:
                    if (m_animation.IsBeginningOfSequence()) {
                        CString animationResRef;
                        m_animation.GetAnimationResRef(animationResRef, CGameAnimationType::RANGE_BODY);
                        if (animationResRef == "MWAV") {
                            CGameEffect* pEffect = IcewindMisc::CreateEffectVisualSpellHit(this, 99, 1, 0);
                            AddEffect(pEffect, EFFECT_LIST_TIMED, TRUE, TRUE);
                        }
                    }
                    if (m_animation.IsEndOfSequence()) {
                        m_endOfDamageSeq = TRUE;
                        if (m_pPath != NULL) {
                            SetSequence(CGAMESPRITE_SEQ_WALK);
                        } else {
                            // NOTE: Uninline.
                            SetIdleSequence();
                        }
                    } else {
                        if (field_70FD
                            && m_animation.GetCurrentFrame() == field_7414) {
                            CSound cSound;
                            cSound.SetResRef(CResRef(field_7410), TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_DIE:
                    if (m_animation.IsBeginningOfSequence()) {
                        CString animationResRef;
                        m_animation.GetAnimationResRef(animationResRef, CGameAnimationType::RANGE_BODY);
                        if (animationResRef == "MWAV") {
                            CGameEffect* pEffect = IcewindMisc::CreateEffectVisualSpellHit(this, 97, 1, 0);
                            AddEffect(pEffect, EFFECT_LIST_TIMED, TRUE, TRUE);
                        }
                    }
                    if (m_animation.IsBeginningOfSequence()
                        && field_70FE
                        && !field_7398.IsEmpty()) {
                        INT nIndex = rand() % field_7398.GetCount();
                        POSITION pos = field_7398.GetHeadPosition();
                        while (pos != NULL && nIndex != 0) {
                            nIndex--;
                            field_7398.GetNext(pos);
                        }
                        CGameSpriteSoundEntry& pEntry = field_7398.GetAt(pos);
                        field_7418 = pEntry.field_0;
                        field_741C = pEntry.field_4;
                    }
                    if (m_animation.IsBeginningOfSequence()
                        && field_7101
                        && !field_73EC.IsEmpty()) {
                        INT nIndex = rand() % field_73EC.GetCount();
                        POSITION pos = field_73EC.GetHeadPosition();
                        while (pos != NULL && nIndex != 0) {
                            nIndex--;
                            field_73EC.GetNext(pos);
                        }
                        CGameSpriteSoundEntry& pEntry = field_73EC.GetAt(pos);
                        field_7428 = pEntry.field_0;
                        field_742C = pEntry.field_4;
                    }
                    if (field_1C != 0) {
                        pGame->GetObjectArray()->Delete(field_1C,
                            CGameObjectArray::THREAD_ASYNCH,
                            NULL,
                            INFINITE);
                        field_1C = 0;
                    }
                    m_nSequence = CGAMESPRITE_SEQ_DIE;
                    if (m_animation.IsEndOfSequence()) {
                        if (m_bBloodFlashOn == TRUE) {
                            m_bBloodFlashOn = FALSE;
                            m_nBloodFlashAmount = 128;
                            m_nDamageLocatorTime = 128;
                            pGame->UpdatePortrait(pGame->GetCharacterPortraitNum(m_id), 1);
                        }
                        m_nTwitches = rand() % 4 + rand() % 4;
                        SetSequence(CGAMESPRITE_SEQ_TWITCH);
                    } else {
                        if (field_70FE
                            && m_animation.GetCurrentFrame() == field_741C) {
                            CSound cSound;
                            cSound.SetResRef(CResRef(field_7418), TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                        if (field_7101
                            && m_animation.GetCurrentFrame() == field_742C) {
                            CSound cSound;
                            cSound.SetResRef(CResRef(field_7428), TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_HEAD_TURN:
                case CGAMESPRITE_SEQ_READY:
                    if (m_dialogWait <= 0
                        || m_typeAI.GetEnemyAlly() >= CAIObjectType::EA_EVILCUTOFF
                        || !m_bAllowDialogInterrupt
                        || m_derivedStats.m_bIgnoreDialogPause) {
                        AIUpdateWalk();
                    }

                    // NOTE: Uninline.
                    SetIdleSequence();

                    if (m_animation.IsBeginningOfSequence()
                        && field_70FF
                        && m_nSequence == CGAMESPRITE_SEQ_HEAD_TURN
                        && !field_73B4.IsEmpty()) {
                        INT nIndex = rand() % field_73B4.GetCount();
                        POSITION pos = field_73B4.GetHeadPosition();
                        while (pos != NULL && nIndex != 0) {
                            nIndex--;
                            field_73B4.GetNext(pos);
                        }
                        CGameSpriteSoundEntry& pEntry = field_73B4.GetAt(pos);
                        field_7420 = pEntry.field_0;
                        field_7424 = pEntry.field_4;
                    }
                    if (pGame->GetVisibleArea() == m_pArea
                        && field_70FF
                        && m_animation.GetCurrentFrame() == field_7424
                        && m_nSequence == CGAMESPRITE_SEQ_HEAD_TURN
                        && !m_baseStats.field_294) {
                        if (m_animation.GetCurrentFrame() == field_740C) {
                            CSound cSound;
                            cSound.SetResRef(field_7420, TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(13, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                    }
                    m_animation.IncrementFrame();
                    break;
                case CGAMESPRITE_SEQ_SHOOT:
                    if (m_animation.IsEndOfSequence()) {
                        // NOTE: Uninline.
                        SetIdleSequence();
                    } else {
                        if (m_animation.GetCurrentFrame() == field_740C) {
                            CSound cSound;
                            cSound.SetResRef(field_7408, TRUE, TRUE);
                            cSound.m_nPitchVariance = 5;
                            cSound.m_nVolumeVariance = 20;
                            cSound.SetChannel(3, reinterpret_cast<DWORD>(m_pArea));
                            if (!cSound.GetLooping()) {
                                cSound.SetFireForget(TRUE);
                            }
                            cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
                        }
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_TWITCH:
                    if (field_1C != 0) {
                        pGame->GetObjectArray()->Delete(field_1C,
                            CGameObjectArray::THREAD_ASYNCH,
                            NULL,
                            INFINITE);
                        field_1C = 0;
                    }
                    if (m_nTwitches != 0) {
                        if (m_animation.IsEndOfSequence()) {
                            if (rand() % 10 == 0) {
                                m_nTwitches--;
                            }
                        } else {
                            m_animation.IncrementFrame();
                        }
                    } else {
                        if ((pGame->GetCharacterPortraitNum(m_id) != -1
                                && (m_derivedStats.m_generalState & STATE_DEAD) != 0)
                            || (pGame->GetCharacterPortraitNum(m_id) != -1
                                && (m_derivedStats.m_generalState & STATE_STONE_DEATH) != 0)) {
                            if (InControl()) {
                                RemoveFromArea();
                                if (m_pArea->m_nCharacters == 0) {
                                    pGame->SelectCharacter(pGame->GetProtagonist(), FALSE);
                                    pGame->SelectToolbar();
                                    if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->GetScreenWorld()
                                        && g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter() == pGame->GetCharacterPortraitNum(m_id)) {
                                        g_pBaldurChitin->GetActiveEngine()->OnPortraitLClick(pGame->GetCharacterPortraitNum(pGame->GetProtagonist()));
                                    }
                                }
                            }
                        }
                    }
                    break;
                case CGAMESPRITE_SEQ_WALK:
                    AIUpdateFly();

                    if (m_dialogWait > 0
                        && m_typeAI.GetEnemyAlly() < CAIObjectType::EA_EVILCUTOFF
                        && m_bAllowDialogInterrupt
                        && !m_derivedStats.m_bIgnoreDialogPause) {
                        if (m_nSequence != GetIdleSequence()) {
                            CMessage* message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()),
                                m_id,
                                m_id);
                            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                        }
                    } else {
                        AIUpdateWalk();
                    }

                    if (m_walkBackwards || m_turningAbout) {
                        m_animation.DecrementFrame();
                    } else {
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_EMERGE:
                    if (m_animation.IsEndOfSequence()) {
                        // NOTE: Uninline.
                        SetIdleSequence();
                    } else {
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_HIDE:
                    if (m_animation.IsEndOfSequence()) {
                        // NOTE: Uninline.
                        SetIdleSequence();
                    } else {
                        m_animation.IncrementFrame();
                    }
                    break;
                case CGAMESPRITE_SEQ_SLEEP:
                    if (field_1C != 0) {
                        pGame->GetObjectArray()->Delete(field_1C,
                            CGameObjectArray::THREAD_ASYNCH,
                            NULL,
                            INFINITE);
                        field_1C = 0;
                    }
                    m_nSequence = CGAMESPRITE_SEQ_SLEEP;
                    if (m_animation.IsEndOfSequence()) {
                        if (m_bBloodFlashOn == TRUE) {
                            m_bBloodFlashOn = FALSE;
                            m_nBloodFlashAmount = 128;
                            m_nDamageLocatorTime = 128;
                            pGame->UpdatePortrait(pGame->GetCharacterPortraitNum(m_id), 1);
                        }
                        m_nTwitches = 0;
                    } else {
                        m_animation.IncrementFrame();
                    }
                    break;
                default:
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                    // __LINE__: 3274
                    UTIL_ASSERT(FALSE);
                }

                if (pGame->GetCharacterPortraitNum(m_id) != CGameObjectArray::INVALID_INDEX) {
                    if ((m_derivedStats.m_generalState & STATE_DEAD) == 0
                        && m_typeAI.GetRace() == CAIOBJECTTYPE_R_GNOME
                        && m_typeAI.GetSubRace() == CAIOBJECTTYPE_SUBRACE_GNOME_DEEP) {
                        if (InControl()
                            && (m_baseStats.m_generalState & STATE_NONDETECTION) == 0) {
                            ITEM_EFFECT effect;
                            CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_NONDETECTION);

                            CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
                                GetPos(),
                                m_id,
                                CPoint(-1, -1));

                            CMessage* message = new CMessageAddEffect(pEffect,
                                m_id,
                                m_id);
                            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                        }

                        // NOTE: Uninline.
                        AddPortraitIcon(31);
                    }

                    BOOL bHavePaladinNearby = FALSE;
                    for (SHORT nPortrait = 0; nPortrait < pGame->GetNumCharacters() && !bHavePaladinNearby; nPortrait++) {
                        LONG nCharacterId = pGame->GetCharacterId(nPortrait);

                        if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
                            CGameSprite* pPaladin;

                            BYTE rc;
                            do {
                                rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                                    CGameObjectArray::THREAD_ASYNCH,
                                    reinterpret_cast<CGameObject**>(&pPaladin),
                                    INFINITE);
                            } while (rc != CGameObjectArray::SUCCESS);

                            CPoint ptPaladinPos = pPaladin->GetPos();
                            CPoint ptPos = GetPos();
                            INT nPaladinLevel = pPaladin->GetDerivedStats()->GetClassLevel(CAIOBJECTTYPE_C_PALADIN);
                            BOOL bPaladinAnimate = pPaladin->Animate();
                            BOOL bAnimate = Animate();

                            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                                CGameObjectArray::THREAD_ASYNCH,
                                INFINITE);

                            if (bPaladinAnimate
                                && bAnimate
                                && nPaladinLevel >= 2
                                && (ptPos.x - ptPaladinPos.x) * (ptPos.x - ptPaladinPos.x) + (ptPos.y - ptPaladinPos.y) * (ptPos.y - ptPaladinPos.y) <= 10000) {
                                bHavePaladinNearby = TRUE;
                            }
                        }
                    }

                    if (bHavePaladinNearby == TRUE) {
                        // NOTE: Uninline.
                        AddPortraitIcon(67);
                    } else {
                        // NOTE: Uninline.
                        RemovePortraitIcon(67);
                    }
                }
            }
        }
    }
}

// 0x6F2D80
CGameSprite::~CGameSprite()
{
    POSITION pos;

    pos = m_lstBlood.GetHeadPosition();
    while (pos != NULL) {
        CBlood* blood = m_lstBlood.GetNext(pos);
        if (blood != NULL) {
            delete blood;
        }
    }
    m_lstBlood.RemoveAll();

    pos = m_equipedEffectList.GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* effect = m_equipedEffectList.GetNext(pos);
        if (effect != NULL) {
            delete effect;
        }
    }
    m_equipedEffectList.RemoveAll();

    pos = m_timedEffectList.GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* effect = m_timedEffectList.GetNext(pos);
        if (effect != NULL) {
            delete effect;
        }
    }
    m_timedEffectList.RemoveAll();

    pos = m_persistantEffects.GetHeadPosition();
    while (pos != NULL) {
        CPersistantEffect* effect = m_persistantEffects.GetNext(pos);
        if (effect != NULL) {
            delete effect;
        }
    }
    m_persistantEffects.RemoveAll();

    ClearStoredPaths();

    // NOTE: Uninline.
    DropPath();

    if (m_currentSearchRequest != NULL) {
        delete m_currentSearchRequest;
    }

    if (m_curProjectile != NULL) {
        delete m_curProjectile;
    }
    m_curProjectile = NULL;

    if (m_pSpriteEffectArray != NULL) {
        delete m_pSpriteEffectArray;
        delete m_pSpriteEffectArrayPosition;
    }

    if (m_curSpell != NULL) {
        delete m_curSpell;
        m_curSpell = NULL;
    }

    if (m_curItem != NULL) {
        m_curItem = NULL;
    }

    if (m_pLocalVariables != NULL) {
        delete m_pLocalVariables;
    }

    m_portraitIconVidCell.CancelRequest();

    ClearMarshal(FALSE);
}

// 0x6F3A30
void CGameSprite::AddBlood(SHORT nHeight, SHORT nDirection, SHORT nType)
{
    if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nGoreOption == 0) {
        if (nType != CBlood::EXPLODING_DEATH) {
            StartSpriteEffect(0, static_cast<BYTE>(nType), 0, 1);
        }
    } else {
        if (nType == CBlood::EXPLODING_DEATH) {
            CRect rFx;
            CPoint ptReference;

            // NOTE: Uninline.
            m_animation.CalculateFxRect(rFx, ptReference, m_posZ);

            CBlood* pBlood = new CBlood(m_pArea,
                m_pos.x,
                m_pos.y,
                5 * rFx.Height() / 10,
                nDirection,
                nType,
                rFx.Height());
            m_lstBlood.AddTail(pBlood);
        } else {
            StartSpriteEffect(0, static_cast<BYTE>(nType), 0, 1);
        }
    }
}

// 0x6F9040
void CGameSprite::AIUpdateWalk()
{
    CSingleLock pathLock(&(g_pBaldurChitin->GetObjectGame()->field_1B58), FALSE);
    CMessage* message;

    if (m_pPath == NULL && m_currentSearchRequest != NULL) {
        pathLock.Lock(INFINITE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 3435
        UTIL_ASSERT(m_currentSearchRequest->m_serviceState != CSearchRequest::STATE_STALE);

        if (m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_WAITING) {
            if (m_currentSearchRequest->m_collisionDelay > 1) {
                m_currentSearchRequest--;
                pathLock.Unlock();
                return;
            }

            if (m_currentSearchRequest->m_collisionDelay == 1) {
                m_currentSearchRequest->m_collisionDelay = 0;
                if (m_currentSearchRequest->m_frontList == CSearchRequest::LIST_FRONT) {
                    g_pBaldurChitin->GetObjectGame()->m_searchRequests.AddTail(m_currentSearchRequest);
                    g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty = FALSE;
                } else {
                    g_pBaldurChitin->GetObjectGame()->m_searchRequestsBack.AddTail(m_currentSearchRequest);
                }
                ReleaseSemaphore(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, 1, NULL);
                pathLock.Unlock();
                return;
            }
        }

        if (m_currentSearchRequest->m_frontList == CSearchRequest::LIST_BACK_PROMOTE
            && m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_WAITING) {
            m_currentSearchRequest->m_serviceState = CSearchRequest::STATE_STALE;
            m_currentSearchRequest = new CSearchRequest(*m_currentSearchRequest);
            pathLock.Unlock();
            if (m_currentSearchRequest != NULL) {
                SetTarget(m_currentSearchRequest, FALSE, CSearchRequest::LIST_FRONT);
            } else {
                SetSequence(CGAMESPRITE_SEQ_HEAD_TURN);
            }
            return;
        }

        if (m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_ERROR
            || m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_NO_TARGET) {
            if (m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_NO_TARGET) {
                m_pathSearchInvalidDest = TRUE;
            }
            pathLock.Unlock();
            delete m_currentSearchRequest;
            m_currentSearchRequest = NULL;
            SetSequence(CGAMESPRITE_SEQ_HEAD_TURN);
            return;
        }

        if (m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_DONE) {
            LONG* pPath = m_currentSearchRequest->m_pPath;
            SHORT nPath = m_currentSearchRequest->m_nPath;

            m_currentSearchRequest->m_pPath = NULL;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 3490
            UTIL_ASSERT(nPath > 0 && pPath != NULL);

            CPoint pt(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                m_pos.y / CPathSearch::GRID_SQUARE_SIZEY);
            message = new CMessageSetPath(CPathSearch::PointToPosition(&pt),
                pPath,
                nPath,
                TRUE,
                m_curDest,
                m_id,
                m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

            if (m_currentSearchRequest->m_searchRc != 0 || nPath == 1) {
                delete m_currentSearchRequest;
                m_currentSearchRequest = NULL;

                if (nPath == 1) {
                    pathLock.Unlock();

                    message = new CMessageDropPath(m_id, m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

                    if (m_nSequence != GetIdleSequence()) {
                        message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()),
                            m_id,
                            m_id);
                        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                    }

                    delete pPath;
                    return;
                }
            } else {
                // NOTE: Uninline.
                CPathSearch::PositionToPoint(pPath[nPath - 1], &(m_currentSearchRequest->m_sourcePt));
                SetTarget(m_currentSearchRequest, FALSE, CSearchRequest::LIST_BACK_PROMOTE);
            }

            SetSequence(CGAMESPRITE_SEQ_WALK);
            InitializeWalkingSound();

            if (m_followLeader) {
                g_pBaldurChitin->GetObjectGame()->GetGroup()->HandleFollowPath(pPath,
                    nPath,
                    m_curDest,
                    m_pos,
                    m_followLeaderAdditive);
                m_followLeader = FALSE;
                m_followLeaderAdditive = FALSE;
            }

            if (m_followLeaderNext != CGameObjectArray::INVALID_INDEX) {
                message = new CMessageStartFollow(m_id, m_followLeaderNext);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                m_followLeaderNext = CGameObjectArray::INVALID_INDEX;
            }

            delete pPath;
        }

        pathLock.Unlock();

        if (m_pPath == NULL) {
            return;
        }
    }

    if ((m_posDest.x / 8 == (m_pos.x + 4) / 8 && m_posDest.y / 6 == (m_pos.y + 3) / 6)
        || (m_pos.y - m_posDest.y) * (m_pos.y - m_posDest.y) + (m_pos.x - m_posDest.x) * (m_pos.x - m_posDest.x) >= (m_posOld.y - m_posDest.y) * (m_posOld.y - m_posDest.y) + (m_posOld.x - m_posDest.x) * (m_posOld.x - m_posDest.x)) {
        if (m_currPath == m_nPath) {
            delete m_pPath;
            m_pPath = NULL;

            // NOTE: Uninline.
            SetIdleSequence();

            if (!m_bVisibilityUpdated) {
                m_pArea->m_visibility.UpDate(m_posLastVisMapEntry,
                    m_pos,
                    m_id,
                    m_visibleTerrainTable);
                m_posLastVisMapEntry = m_pos;
                m_bVisibilityUpdated = TRUE;
            }
            return;
        }
    }

    CPoint goal;
    CPathSearch::PositionToPoint(m_pPath[m_currPath++], &goal);
    m_posDest.x = goal.x * CPathSearch::GRID_SQUARE_SIZEX + CPathSearch::GRID_SQUARE_SIZEX / 2;
    m_posDest.y = goal.y * CPathSearch::GRID_SQUARE_SIZEY + CPathSearch::GRID_SQUARE_SIZEY / 2;

    int scale = static_cast<int>(sqrt((m_posDest.x - m_pos.x) * (m_posDest.x - m_pos.x) + (m_posDest.y - 4 * m_pos.y / 3) * (m_posDest.y - 4 * m_pos.y / 3)) + 0.5);
    if (scale == 0) {
        // NOTE: Uninline.
        DropPath();

        // NOTE: Uninline.
        SetIdleSequence();

        return;
    }

    if (m_animation.GetMoveScale() > 8) {
        if (scale >= m_animation.GetMoveScale()) {
            scale = (scale + m_animation.GetMoveScale() / 2) / m_animation.GetMoveScale();
        } else {
            scale = 1;
        }

        m_posDelta.x = ((m_animation.GetMoveScale() * (m_posDest.x - m_pos.x)) << EXACT_SCALE) / scale;
        m_posDelta.y = ((m_animation.GetMoveScale() * (m_posDest.y - m_pos.y)) << EXACT_SCALE) / scale;
    } else {
        m_posDelta.x = ((m_animation.GetMoveScale() * (m_posDest.x - m_pos.x)) << EXACT_SCALE) / scale;
        m_posDelta.y = ((m_animation.GetMoveScale() * (m_posDest.y - m_pos.y)) << EXACT_SCALE) / scale;
    }

    SetDirection(m_posDest);

    m_turningAbout = !m_walkBackwards
        && abs(m_nNewDirection - m_nDirection) >= 5
        && abs(m_nNewDirection - m_nDirection) <= 8;

    SetSequence(CGAMESPRITE_SEQ_WALK);

    CPoint posExactOld(m_posExact);

    m_posExact += m_posDelta;
    m_posOld = m_pos;
    m_pos.x = m_posExact.x >> EXACT_SCALE;
    m_pos.y = (3 * m_posExact.y / 4) >> EXACT_SCALE;

    CPoint ptOldSearch(m_posOld.x / CPathSearch::GRID_SQUARE_SIZEX,
        m_posOld.y / CPathSearch::GRID_SQUARE_SIZEY);
    CPoint ptSearch(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
        m_pos.y / CPathSearch::GRID_SQUARE_SIZEY);

    if (ptOldSearch == ptSearch
        || m_animation.GetListType() == LIST_FLIGHT) {
        if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0
            && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
                || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1)
            && m_pArea == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()) {
            INT nSndWalk = m_nSndWalk % m_animation.GetSndWalkFreq();
            m_nSndWalk++;

            if (nSndWalk == 0) {
                BYTE currSndWalk = m_currSndWalk;
                m_currSndWalk = (m_currSndWalk + 1) % 2;

                CPoint ear;
                LONG earZ;
                g_pBaldurChitin->cSoundMixer.GetListenPosition(ear, earZ);

                m_sndWalk[m_currSndWalk].Stop();
                m_sndWalk[m_currSndWalk].SetResRef(m_sndWalk[currSndWalk].GetResRef(), TRUE, TRUE);

                LONG priority = max(99 - 99 * ((ear.y - m_pos.y) * (ear.y - m_pos.y) / 144 + (ear.x - m_pos.x) * (ear.x - m_pos.x) / 256) / 6400, 0);
                m_sndWalk[m_currSndWalk].SetPriority(static_cast<BYTE>(priority));

                m_sndWalk[m_currSndWalk].Play(m_pos.x, m_pos.y, m_posZ, FALSE);
            }
        }

        m_sndSpriteEffect.SetCoordinates(m_pos.x, m_pos.y, m_posZ);
        m_sndReady.SetCoordinates(m_pos.x, m_pos.y, m_posZ);
    } else {
        m_pArea->m_search.RemoveObject(ptOldSearch,
            m_typeAI.GetEnemyAlly(),
            m_animation.GetPersonalSpace(),
            field_54A8,
            field_7430);

        if (InControl()
            && m_pArea->m_search.GetMobileCost(ptSearch, m_terrainTable, m_animation.GetPersonalSpace(), TRUE) == CPathSearch::COST_IMPASSABLE
            && !ClearBumpPath(ptOldSearch, ptSearch)) {
            if (!m_baseStats.field_294) {
                m_pArea->m_search.AddObject(ptOldSearch,
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);

                m_posExact = posExactOld;
                m_pos = m_posOld;

                if (m_currentSearchRequest != NULL) {
                    pathLock.Lock(INFINITE);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                    // __LINE__: 3776
                    UTIL_ASSERT(m_currentSearchRequest->m_serviceState != CSearchRequest::STATE_STALE);

                    if ((m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_WAITING
                            && m_currentSearchRequest->m_collisionDelay == 0)
                        || m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_PROCESSING) {
                        m_currentSearchRequest->m_serviceState = CSearchRequest::STATE_STALE;
                        m_currentSearchRequest = new CSearchRequest(*m_currentSearchRequest);
                        if (m_currentSearchRequest != NULL) {
                            SetTarget(m_currentSearchRequest, TRUE, CSearchRequest::LIST_FRONT);
                        } else {
                            SetSequence(CGAMESPRITE_SEQ_HEAD_TURN);
                        }
                    } else {
                        if (m_currentSearchRequest->m_pPath != NULL) {
                            delete m_currentSearchRequest->m_pPath;
                            m_currentSearchRequest->m_pPath = NULL;
                        }
                        SetTarget(m_currentSearchRequest, TRUE, CSearchRequest::LIST_FRONT);
                    }

                    pathLock.Unlock();
                } else {
                    CPoint pt;
                    CPathSearch::PositionToPoint(m_pPath[m_nPath - 1], &pt);
                    SetTarget(CPoint(pt.x * CPathSearch::GRID_SQUARE_SIZEX + CPathSearch::GRID_SQUARE_SIZEX / 2,
                                  pt.y * CPathSearch::GRID_SQUARE_SIZEY + CPathSearch::GRID_SQUARE_SIZEY / 2),
                        TRUE);
                }
            }
        } else {
            if (!m_baseStats.field_294) {
                m_pArea->m_search.AddObject(ptSearch,
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
            }

            char* pSndWalk = m_animation.GetSndWalk(m_pArea->m_search.GetTableIndex(ptOldSearch));
            if (pSndWalk != NULL) {
                m_sndWalk[m_currSndWalk].SetResRef(CResRef(pSndWalk), TRUE, TRUE);

                if (*pSndWalk != '\0') {
                    delete pSndWalk;
                }
            }

            if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0
                && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
                    || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1)
                && m_pArea == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()) {
                INT nSndWalk = m_nSndWalk % m_animation.GetSndWalkFreq();
                m_nSndWalk++;

                if (nSndWalk == 0) {
                    BYTE currSndWalk = m_currSndWalk;
                    m_currSndWalk = (m_currSndWalk + 1) % 2;

                    CPoint ear;
                    LONG earZ;
                    g_pBaldurChitin->cSoundMixer.GetListenPosition(ear, earZ);

                    m_sndWalk[m_currSndWalk].Stop();
                    m_sndWalk[m_currSndWalk].SetResRef(m_sndWalk[currSndWalk].GetResRef(), TRUE, TRUE);

                    LONG priority = max(99 - 99 * ((ear.y - m_pos.y) * (ear.y - m_pos.y) / 144 + (ear.x - m_pos.x) * (ear.x - m_pos.x) / 256) / 6400, 0);
                    m_sndWalk[m_currSndWalk].SetPriority(static_cast<BYTE>(priority));

                    m_sndWalk[m_currSndWalk].Play(m_pos.x, m_pos.y, m_posZ, FALSE);
                }
            }

            m_sndSpriteEffect.SetCoordinates(m_pos.x, m_pos.y, m_posZ);
            m_sndReady.SetCoordinates(m_pos.x, m_pos.y, m_posZ);
        }
    }

    if ((m_posLastVisMapEntry.x / CVisibilityMap::SQUARE_SIZEX != m_pos.x / CVisibilityMap::SQUARE_SIZEX
            || m_posLastVisMapEntry.y / CVisibilityMap::SQUARE_SIZEY != m_pos.y / CVisibilityMap::SQUARE_SIZEY)
        && g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1
        && (!g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC || InControl())) {
        SHORT nTableIndex;
        if (m_pArea->m_search.GetLOSCost(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX, m_pos.y / CPathSearch::GRID_SQUARE_SIZEY), m_terrainTable, nTableIndex, FALSE) != CPathSearch::COST_IMPASSABLE) {
            m_pArea->m_visibility.UpDate(m_posLastVisMapEntry,
                m_pos,
                m_id,
                m_visibleTerrainTable);
            m_posLastVisMapEntry = m_pos;
            m_bVisibilityUpdated = TRUE;
            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineMap) {
                SHORT nPortrait = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id);
                CUIControlButtonMapAreaMap* pMap = static_cast<CUIControlButtonMapAreaMap*>(g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2)->GetControl(2));
                pMap->field_7DA |= 1 << nPortrait;
            }
        } else {
            m_bVisibilityUpdated = FALSE;
        }
    }
}

// 0x6FA810
void CGameSprite::SetPath(LONG* pPath, SHORT nPath)
{
    CPoint start;
    CPoint goal;

    // NOTE: Uninline.
    DropPath();

    m_nPath = nPath;
    m_pPath = pPath;
    m_currPath = 1;
    m_posDest.x = m_pos.x + 4;
    m_posDest.y = m_pos.y + 3;

    // NOTE: Uninline.
    CPathSearch::PositionToPoint(m_pPath[0], &start);

    // NOTE: Uninline.
    CPathSearch::PositionToPoint(m_pPath[nPath - 1], &goal);

    if (abs(goal.x - start.x) <= 4 && abs(goal.y - start.y <= 4) && nPath <= 4) {
        m_walkBackwards = TRUE;
    }

    SetSequence(CGAMESPRITE_SEQ_WALK);
}

// 0x6FA900
BOOL CGameSprite::ClearBumpPath(const CPoint& start, const CPoint& goal)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x6FB440
BOOL CGameSprite::sub_6FB440()
{
    if (!InControl()) {
        return FALSE;
    }

    if (m_animation.GetMoveScale() == 0
        || m_typeAI.GetEnemyAlly() == CAIObjectType::EA_ENEMY
        || !Animate()) {
        return FALSE;
    }

    if (m_typeAI.GetEnemyAlly() > CAIObjectType::EA_GOODCUTOFF
        || m_curAction.m_actionID != CAIAction::NO_ACTION) {
        // 0x8F94F0
        static SHORT word_8F94F0[] = {
            CAIAction::RANDOMWALK,
            CAIAction::RANDOMWALKCONTINUOUS,
            CAIAction::WAIT,
            CAIAction::FACE,
            CAIAction::ATTACK,
            CAIAction::GROUPATTACK,
            CAIAction::ATTACKNOSOUND,
            CAIAction::ATTACKONEROUND,
            CAIAction::ATTACKREEVALUATE,
        };

        // 0x8F9504
        static SHORT word_8F9504[] = {
            CAIAction::RANDOMWALK,
            CAIAction::RANDOMWALKCONTINUOUS,
            CAIAction::WAIT,
            CAIAction::FACE,
        };

        WORD wType = 0;
        CItem* pItem = m_equipment.m_items[m_equipment.m_selectedWeapon];
        if (pItem != NULL) {
            pItem->Demand();
            const ITEM_ABILITY* ability = pItem->GetAbility(m_equipment.m_selectedWeaponAbility);
            if (ability != NULL) {
                wType = ability->type;
            }
            pItem->Release();
        }

        if (wType == 4 || wType == 2) {
            for (int index = 0; index < sizeof(word_8F94F0) / sizeof(word_8F94F0[0]); index++) {
                if (word_8F94F0[index] == m_curAction.m_actionID) {
                    return TRUE;
                }
            }
            return FALSE;
        } else {
            for (int index = 0; index < sizeof(word_8F9504) / sizeof(word_8F9504[0]); index++) {
                if (word_8F9504[index] == m_curAction.m_actionID) {
                    return TRUE;
                }
            }
            return FALSE;
        }
    }

    return TRUE;
}

// 0x6FB630
void CGameSprite::AIUpdateFly()
{
    if (m_fCurrCircleChange < m_fCircleChange) {
        double fCurrCircleChange = min(m_fCircleChange, m_fCurrCircleChange + 1.0);

        if (m_circleFacing != 0) {
            double fAngle = static_cast<double>(m_animation.GetMoveScale())
                    * static_cast<double>(m_circleFacing)
                    * fCurrCircleChange
                    / static_cast<double>(m_radius)
                + m_fDirectionOffset;

            m_pos.x = m_posOld.x + static_cast<LONG>(cos(fAngle) * static_cast<double>(m_radius));
            m_pos.y = m_posOld.y - static_cast<LONG>(sin(fAngle) * static_cast<double>(m_radius) * 3.0 / 4.0);

            if (m_circleFacing == FLY_LEFT) {
                if (m_pos != m_posOld) {
                    SetDirection((GetDirection(CPoint(m_pos.x, 4 * m_pos.y / 3),
                                      CPoint(m_posOld.x, 4 * m_posOld.y / 3))
                                     + 4)
                        % 16);
                } else {
                    SetDirection(m_nNewDirection);
                }
            } else {
                if (m_pos != m_posOld) {
                    SetDirection((GetDirection(CPoint(m_pos.x, 4 * m_pos.y / 3),
                                      CPoint(m_posOld.x, 4 * m_posOld.y / 3))
                                     + 12)
                        % 16);
                } else {
                    SetDirection(m_nNewDirection);
                }
            }
        } else {
            switch (m_nDirection) {
            case 0:
                m_pos.y = m_posOld.y + static_cast<LONG>(static_cast<double>(m_radius) * fCurrCircleChange / m_fCircleChange * 3.0 / 4.0);
                break;
            case 4:
                m_pos.x = m_posOld.x - static_cast<LONG>(static_cast<double>(m_radius) * fCurrCircleChange / m_fCircleChange);
                break;
            case 8:
                m_pos.y = m_posOld.y - static_cast<LONG>(static_cast<double>(m_radius) * fCurrCircleChange / m_fCircleChange * 3.0 / 4.0);
                break;
            case 12:
                m_pos.x = m_posOld.x + static_cast<LONG>(static_cast<double>(m_radius) * fCurrCircleChange / m_fCircleChange);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 4554
                UTIL_ASSERT(FALSE);
            }
        }

        m_fCurrCircleChange += 1.0;
        if (m_fCurrCircleChange >= m_fCircleChange) {
            SetSequence(SEQ_READY);
        }
    }
}

// 0x6FBA50
void CGameSprite::GetNextWaypoint(CPoint* pt)
{
    if (m_pPath != NULL) {
        CPathSearch::PositionToPoint(m_pPath[m_currPath - 1], pt);

        pt->x *= CPathSearch::GRID_SQUARE_SIZEX;
        pt->x += CPathSearch::GRID_SQUARE_SIZEX / 2;

        pt->y *= CPathSearch::GRID_SQUARE_SIZEY;
        pt->y += CPathSearch::GRID_SQUARE_SIZEY / 2;
    } else {
        *pt = m_pos;
    }
}

// 0x6FBAD0
void CGameSprite::ChangeDirection()
{
    if (m_nNewDirection == m_nDirection) {
        return;
    }

    if (m_skipDeltaDirection > 0) {
        m_skipDeltaDirection -= 2;
        if (m_skipDeltaDirection <= 1) {
            m_nDirection = (m_nDirection + 2 * m_deltaDirection + 16) % 16;
        }
    }

    m_nDirection = (m_nDirection + m_deltaDirection + 16) % 16;
    if (m_nNewDirection != m_nDirection) {
        m_nDirection = (m_nDirection + m_deltaDirection + 16) % 16;
    }

    m_animation.ChangeDirection(m_nDirection);

    if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0
        && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
            || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1)
        && m_pArea == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()) {
        m_currSndArmor = 0;
        m_sndArmor[m_currSndArmor].Stop();

        // NOTE: Uninline.
        char* sndArmor = m_animation.GetSndArmor();

        if (sndArmor[0] != '\0') {
            // NOTE: Uninline.
            m_sndArmor[m_currSndArmor].SetResRef(CResRef(sndArmor), TRUE, TRUE);
            delete sndArmor;

            CPoint ear;
            LONG earZ;
            g_pBaldurChitin->cSoundMixer.GetListenPosition(ear, earZ);

            LONG priority = max(99 - 99 * ((ear.y - m_pos.y) * (ear.y - m_pos.y) / 144 + (ear.x - m_pos.x) * (ear.x - m_pos.x) / 256) / 6400, 0);
            m_sndArmor[m_currSndArmor].SetPriority(static_cast<BYTE>(priority));

            m_sndArmor[m_currSndArmor].Play(m_pos.x, m_pos.y, m_posZ, FALSE);
        }
    }
}

// 0x6FBF10
void CGameSprite::CheckIfVisible()
{
    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1
        || m_animation.GetListType() == LIST_FLIGHT) {
        if (Animate()) {
            m_canBeSeen = 4 * (VISIBLE_DELAY + 1);
            return;
        }
    }

    for (SHORT nPortrait = 0; nPortrait < g_pBaldurChitin->GetObjectGame()->GetNumCharacters(); nPortrait++) {
        CGameSprite* pSprite;

        BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if (pSprite->GetArea() == m_pArea
                && pSprite->Animate()
                && m_pArea->CheckLOS(m_pos, pSprite->GetPos(), m_visibleTerrainTable, TRUE)) {
                if (!m_bVisibleMonster
                    && m_typeAI.GetEnemyAlly() >= CAIObjectType::EA_EVILCUTOFF
                    && Animate()
                    && ((m_derivedStats.m_generalState & STATE_INVISIBLE) == 0 || (m_baseStats.field_2FC & 0x1) != 0)
                    && !m_baseStats.field_294
                    && (m_baseStats.m_flags & 0x8000) == 0) {
                    if (m_pArea->m_nVisibleMonster == 0) {
                        AutoPause(0x200);
                    }

                    m_bVisibleMonster = TRUE;
                    m_pArea->m_nVisibleMonster++;
                }

                if (m_canBeSeen == 0) {
                    CAITrigger becameVisible(CAITRIGGER_BECAMEVISIBLE, 0);
                    m_bSeenPartyBefore = TRUE;
                    CMessage* message = new CMessageSetTrigger(becameVisible, m_id, pSprite->GetId());
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }

                m_canBeSeen = 4 * (VISIBLE_DELAY + 1);

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);

                break;
            } else {
                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }
}

// 0x6FF2F0
void CGameSprite::DropPath()
{
    if (m_pPath != NULL) {
        delete m_pPath;
        m_pPath = NULL;
    }
}

// 0x6FF320
void CGameSprite::DropSearchRequest()
{
    if (m_currentSearchRequest != NULL) {
        CSingleLock searchLock(&(g_pBaldurChitin->GetObjectGame()->field_1B58), TRUE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 5590
        UTIL_ASSERT(m_currentSearchRequest->m_serviceState != CSearchRequest::STATE_STALE);

        if ((m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_WAITING
                && m_currentSearchRequest->m_collisionDelay == 0)
            || m_currentSearchRequest->m_serviceState == CSearchRequest::STATE_PROCESSING) {
            m_currentSearchRequest->m_serviceState = CSearchRequest::STATE_STALE;
        } else {
            delete m_currentSearchRequest;
        }

        m_currentSearchRequest = NULL;

        searchLock.Unlock();
    }
}

// 0x6FF410
BOOL CGameSprite::MoveToBack()
{
    if (m_animation.CanLieDown()) {
        if (m_listType == LIST_BACK) {
            if ((m_derivedStats.m_generalState & STATE_SLEEPING) == 0) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 5669
                UTIL_ASSERT(FALSE);
            }

            // NOTE: Uninline.
            m_pArea->RemoveFromMarkers(m_id);

            m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                               m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                m_typeAI.GetEnemyAlly(),
                m_animation.GetPersonalSpace(),
                field_54A8,
                field_7430);
            m_pArea->IncrHeightDynamic(m_pos);
            m_derivedStats.m_generalState &= ~STATE_SLEEPING;
            return FALSE;
        }

        if (m_posVertList != NULL) {
            m_pArea->RemoveObject(m_posVertList, m_listType, m_id);
            m_posVertList = NULL;

            if ((m_derivedStats.m_generalState & STATE_DEAD) != 0) {
                // NOTE: Uninline.
                m_pArea->RemoveFromMarkers(m_id);

                m_pArea->m_search.RemoveObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                   m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
                m_pArea->IncrHeightDynamic(m_pos);
            }

            m_listType = LIST_BACK;
            m_pArea->AddObject(m_id, LIST_BACK);
            return TRUE;
        }

        if (m_moveToFrontQueue > 0) {
            m_moveToFrontQueue--;
        } else {
            m_moveToBackQueue++;
        }
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_DEAD) != 0) {
        // NOTE: Uninline.
        m_pArea->RemoveFromMarkers(m_id);
    }
    return TRUE;
}

// 0x6FF6D0
BOOL CGameSprite::MoveToFront()
{
    if (m_animation.CanLieDown()) {
        if (m_listType == LIST_FRONT) {
            return FALSE;
        }

        if (m_posVertList != NULL) {
            m_pArea->RemoveObject(m_posVertList, m_listType, m_id);
            m_posVertList = NULL;

            if ((m_derivedStats.m_generalState & STATE_SLEEPING) == 0) {
                // NOTE: Uninline.
                m_pArea->AddToMarkers(m_id);

                m_pArea->m_search.AddObject(CPoint(m_pos.x / CPathSearch::GRID_SQUARE_SIZEX,
                                                m_pos.y / CPathSearch::GRID_SQUARE_SIZEY),
                    m_typeAI.GetEnemyAlly(),
                    m_animation.GetPersonalSpace(),
                    field_54A8,
                    field_7430);
                m_pArea->DecrHeightDynamic(m_pos);
            }

            m_listType = LIST_FRONT;
            m_pArea->AddObject(m_id, LIST_FRONT);
            return TRUE;
        }

        if (m_moveToBackQueue > 0) {
            m_moveToBackQueue--;
        } else {
            m_moveToFrontQueue++;
        }
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_SLEEPING) == 0) {
        // NOTE: Uninline.
        m_pArea->AddToMarkers(m_id);
    }
    return TRUE;
}

// 0x6FF8A0
void CGameSprite::OnActionButton(const CPoint& pt)
{
    if (m_canBeSeen > 0) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
        CAIGroup* pGroup = pGame->GetGroup();
        CAIAction action1;
        CAIAction action2;
        CAIObjectType targetType(0, 0, 0, 0, 0, 0, 0, 0, m_id, 0, 0);

        switch (pGame->GetState()) {
        case 0:
            if (pGame->GetCharacterPortraitNum(m_id) != -1
                || pGame->IsAlly(m_id)
                || pGame->IsFamiliar(m_id)) {
                if (!pGame->GetGameSave()->field_1AC || InControl()) {
                    if (InControl()) {
                        // NOTE: Uninline.
                        pGame->SetLastTarget(CGameObjectArray::INVALID_INDEX);

                        if (!m_moraleFailure) {
                            if (!g_pBaldurChitin->GetScreenWorld()->GetCtrlKey()
                                && !g_pBaldurChitin->GetScreenWorld()->GetShiftKey()) {
                                pGame->UnselectAll();
                            }
                            pGame->SelectCharacter(m_id, !m_bSelected);
                            pGame->SelectToolbar();
                        }
                    } else {
                        if (pGroup->GetCount() > 0
                            && m_pArea == pGame->GetVisibleArea()) {
                            action1 = CAIAction(CAIAction::MOVETOOBJECTFOLLOW,
                                targetType,
                                0,
                                0,
                                0);
                            pGroup->GroupAction(action1, TRUE, NULL);
                        } else {
                            pGame->UnselectAll();
                            pGame->GetVisibleArea()->m_bPicked = FALSE;
                            pGame->GetVisibleArea()->m_iPicked = CGameObjectArray::INVALID_INDEX;
                            pGame->GetVisibleArea()->m_nToolTip = 0;
                            pGame->GetVisibleArea()->OnDeactivation();
                            pGame->m_visibleArea = m_pArea->m_id;
                            pGame->GetVisibleArea()->OnActivation();
                        }
                    }
                }
            } else {
                if (pGroup->GetCount() > 0) {
                    if (pGroup->m_groupChanged
                        || pGame->m_lastTarget != m_id
                        || m_typeAI.GetEnemyAlly() < CAIObjectType::EA_EVILCUTOFF) {
                        if (m_typeAI.GetEnemyAlly() < CAIObjectType::EA_EVILCUTOFF) {
                            if (pGroup->IsPartyLeader() && (~m_baseStats.m_flags & STATE_DISEASED) != 0) {
                                CMessage* message = new CMessageSetDialogWait(140,
                                    pGroup->GetGroupLeader(),
                                    m_id,
                                    m_id);
                                g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                            }
                        } else {
                            pGroup->m_groupChanged = FALSE;

                            // NOTE: Uninline.
                            pGame->SetLastTarget(m_id);

                            pGroup->GroupSetTarget(m_id);
                        }
                    } else if (pGame->field_38A6) {
                        if (m_typeAI.GetEnemyAlly() >= CAIObjectType::EA_EVILCUTOFF) {
                            pGroup->m_groupChanged = FALSE;

                            // NOTE: Uninline.
                            pGame->SetLastTarget(m_id);

                            pGroup->GroupSetTarget(m_id);
                        }
                        pGame->field_38A6 = FALSE;
                    }
                } else {
                    // NOTE: Uninline.
                    pGame->SetLastTarget(CGameObjectArray::INVALID_INDEX);

                    PlaySound(9, TRUE, FALSE, FALSE);
                }
            }
            break;
        case 2:
            // NOTE: Uninline.
            pGame->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            switch (pGame->GetIconIndex()) {
            case 12:
                if (!m_bSelected || pGroup->GetCount() != 1) {
                    pGroup->GroupSetTarget(m_id);
                    pGame->SetState(0);
                    pGame->GetButtonArray()->SetSelectedButton(100);
                    pGame->GetButtonArray()->UpdateState();
                }
                break;
            case 18:
                if (pGroup->IsPartyLeader()) {
                    CMessage* message = new CMessageSetDialogWait(150,
                        pGroup->GetGroupLeader(),
                        m_id,
                        m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

                    action2 = CAIAction(CAIAction::PLAYERDIALOG,
                        targetType,
                        0,
                        0,
                        0);
                    pGroup->GroupAction(action1, TRUE, &action2);

                    pGame->SetState(0);
                    pGame->GetButtonArray()->SetSelectedButton(100);
                    pGame->GetButtonArray()->UpdateState();
                }
                break;
            case 20:
            case -1:
                pGame->UseMagicOnGround(m_id);

                pGame->SetState(0);
                pGame->GetButtonArray()->SetSelectedButton(100);
                pGame->GetButtonArray()->UpdateState();
                break;
            case 36:
            case 40:
                if (!m_bSelected) {
                    SHORT nPortrait = g_pBaldurChitin->GetScreenWorld()->GetSelectedCharacter();
                    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

                    CGameSprite* pSprite;

                    BYTE rc;
                    do {
                        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            reinterpret_cast<CGameObject**>(&pSprite),
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        BYTE nPickPockets = pSprite->GetBaseStats()->m_skills[CGAMESPRITE_SKILL_PICK_POCKET];

                        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);

                        if (nPickPockets == 0) {
                            break;
                        }
                    }

                    action2 = CAIAction(CAIAction::PICKPOCKETS,
                        targetType,
                        0,
                        0,
                        0);
                    pGroup->GroupAction(action1, TRUE, &action2);

                    pGame->SetState(0);
                    pGame->GetButtonArray()->SetSelectedButton(100);
                    pGame->GetButtonArray()->UpdateState();
                }
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 5921
                UTIL_ASSERT(FALSE);
            }
            break;
        case 3:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 5951
            UTIL_ASSERT(FALSE);
        }
    } else {
        CGameObject::OnActionButton(pt);
    }
}

// 0x700BB0
void CGameSprite::OnFormationButton(const CPoint& pt)
{
    if (m_canBeSeen > 0) {
        PlaySound(9, 1, 0, 1);
    } else {
        CGameObject::OnFormationButton(pt);
    }
}

// 0x700BE0
void CGameSprite::OnLightningStrike()
{
    CRect rView;
    rView.left = m_pArea->GetInfinity()->nNewX;
    rView.top = m_pArea->GetInfinity()->nNewY;
    rView.right = m_pArea->GetInfinity()->nNewX + m_pArea->GetInfinity()->rViewPort.Width();
    rView.bottom = m_pArea->GetInfinity()->nNewY + m_pArea->GetInfinity()->rViewPort.Height();

    BYTE nProb = 30;

    if (rView.PtInRect(m_pos)) {
        CItem* pItem = m_equipment.m_items[CGameSpriteEquipment::SLOT_ARMOR];
        if (pItem != NULL) {
            WORD animType = pItem->GetAnimationType();
            if (static_cast<BYTE>(animType) != 87) {
                switch (static_cast<BYTE>(animType >> 8)) {
                case 51:
                    nProb += 35;
                    break;
                case 52:
                    nProb += 40;
                    break;
                }
            }
        }

        if (rand() % 100 < nProb) {
            CAIAction strike(CAIAction::REALLYFORCESPELL, CPoint(-1, -1), 0, -1);
            strike.m_acteeID.Set(m_typeAI);
            strike.SetString1(CString("SpWi938"));

            CMessage* message = new CMessageAddAction(strike, m_pArea->m_nAIIndex, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
    }
}

// 0x700F20
void CGameSprite::MakeGlobal()
{
    if (!m_bGlobal) {
        m_bGlobal = TRUE;

        g_pBaldurChitin->GetObjectGame()->m_lstGlobalCreatures.AddTail(reinterpret_cast<int*>(m_id));

        CVariable v;
        v.SetName(CString(GetScriptName()));
        v.m_intValue = m_id;
        g_pBaldurChitin->GetObjectGame()->GetNamedCreatures()->AddKey(v);
    }
}

// 0x700FE0
SHORT CGameSprite::GetNumSounds(SHORT nOffset, SHORT nMaxNum)
{
    SHORT nSounds = 0;

    if (m_secondarySounds == "") {
        for (INT nIndex = 0; nIndex < nMaxNum; nIndex++) {
            if (m_baseStats.m_speech[nOffset + nIndex] == -1) {
                break;
            }

            nSounds++;
        }
    } else {
        nSounds = nMaxNum;
    }

    return nSounds;
}

// 0x7010A0
BOOL CGameSprite::CanSpeak(BOOL ignoreDeath, BOOL ignoreSilence)
{
    if (!m_active || !m_activeAI || !m_activeImprisonment) {
        return FALSE;
    }

    if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_cutScene == TRUE) {
        return TRUE;
    }

    if (!ignoreSilence && (m_derivedStats.m_generalState & STATE_SILENCED) != 0) {
        return FALSE;
    }

    USHORT animationType = m_animation.GetAnimationId();

    if ((m_derivedStats.m_generalState & STATE_SLEEPING) != 0
        && ((animationType & 0xF000) != 0x4000 || animationType < 0x4400)) {
        return FALSE;
    }

    if (!ignoreDeath
        && ((m_derivedStats.m_generalState & STATE_DEAD) != 0
            || (m_derivedStats.m_generalState & STATE_STONE_DEATH) != 0
            || (m_derivedStats.m_generalState & STATE_FROZEN_DEATH) != 0)) {
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_HELPLESS) != 0) {
        return FALSE;
    }

    if (m_derivedStats.m_spellStates.test(SPLSTATE_HELD)
        || m_derivedStats.m_spellStates.test(SPLSTATE_HOPELESSNESS)
        || m_derivedStats.m_spellStates.test(SPLSTATE_OTILUKES_RESILIENT_SPHERE)) {
        return FALSE;
    }

    if (g_pBaldurChitin->GetObjectGame()->m_nTimeStop != 0
        && g_pBaldurChitin->GetObjectGame()->m_nTimeStopCaster != m_id) {
        return FALSE;
    }

    if (!m_bAllowDialogInterrupt) {
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_CHARMED) != 0) {
        return FALSE;
    }

    return TRUE;
}

// 0x7011E0
void CGameSprite::PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption)
{
    // TODO: Incomplete.
}

// 0x702900
void CGameSprite::VerbalConstant(LONG verbalConstant)
{
    STR_RES strRes;

    // NOTE: Uninline.
    BYTE channel = GetChannel();

    if (CanSpeak(verbalConstant >= 36 && verbalConstant < 38, FALSE)
        && verbalConstant >= 0 && verbalConstant < 64) {
        g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[verbalConstant], strRes);
        COLORREF nameColor = CVidPalette::RANGE_COLORS[m_baseStats.m_colors[CVIDPALETTE_RANGE_MAIN_CLOTH]];
        if (m_secondarySounds != "") {
            CString sSoundName;
            CString sSoundSetName;
            LONG nNumber = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetCustomSound(sSoundName, static_cast<BYTE>(verbalConstant));
            m_secondarySounds.CopyToString(sSoundSetName);
            sSoundName.TrimLeft();
            sSoundName.TrimRight();
            sSoundName = sSoundSetName + sSoundName;

            strRes.cSound.SetResRef(CResRef(sSoundName), TRUE, TRUE);
        }

        strRes.szText.TrimLeft();

        BOOL show = g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bSubtitles != FALSE;
        if (strRes.cSound.GetRes() == NULL) {
            show = TRUE;
        }

        if (m_typeAI.GetEnemyAlly() == CAIObjectType::EA_PC) {
            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                if (strRes.cSound.Play(FALSE)) {
                    m_talkingCounter = min(strRes.cSound.GetPlayTime() / 66, STANDARD_VERBAL_CONSTANT_LENGTH);
                }
            }

            CString sText;
            sText = strRes.szText;
            if (sText != "" && show) {
                g_pBaldurChitin->GetScreenWorld()->DisplayText(m_sName,
                    sText,
                    nameColor,
                    RGB(160, 200, 215),
                    -1,
                    FALSE);
            }
        } else {
            if (!strRes.cSound.GetLooping()) {
                strRes.cSound.SetFireForget(TRUE);
            }
            if (strRes.cSound.Play(FALSE)) {
                m_talkingCounter = min(strRes.cSound.GetPlayTime() / 66, STANDARD_VERBAL_CONSTANT_LENGTH);
            }

            CString sText;
            sText = strRes.szText;
            if (sText != "" && show) {
                g_pBaldurChitin->GetScreenWorld()->DisplayText(m_sName,
                    sText,
                    nameColor,
                    RGB(160, 200, 215),
                    -1,
                    FALSE);
            }
        }
    }
}

// 0x702E60
LONG CGameSprite::GetLength(LONG verbalConstant)
{
    STR_RES strRes;

    if (verbalConstant < 0 || verbalConstant >= 64) {
        return 0;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[verbalConstant], strRes);

    if (m_secondarySounds != "") {
        CString sSoundName;
        CString sSoundSetName;
        LONG nNumber = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetCustomSound(sSoundName, static_cast<BYTE>(verbalConstant));
        m_secondarySounds.CopyToString(sSoundSetName);
        sSoundName.TrimLeft();
        sSoundName.TrimRight();
        sSoundName = sSoundSetName + sSoundName;

        if (nNumber == 0
            || g_pBaldurChitin->cDimm.m_cKeyTable.FindKey(CResRef(sSoundName), 4, TRUE) != NULL) {
            strRes.cSound.SetResRef(CResRef(sSoundName), TRUE, TRUE);
        }
    }

    // FIXME: Calls `GetPlayTime` twice.
    return min(strRes.cSound.GetPlayTime() / 33, 300);
}

// 0x703170
BOOL CGameSprite::IsSpellSchool(BYTE spellSchool)
{
    return ((GetSpecialization() & SPECMASK_WIZARD_ABJURER) != 0 && spellSchool == 1)
        || ((GetSpecialization() & SPECMASK_WIZARD_CONJURER) != 0 && spellSchool == 2)
        || ((GetSpecialization() & SPECMASK_WIZARD_DIVINER) != 0 && spellSchool == 3)
        || ((GetSpecialization() & SPECMASK_WIZARD_ENCHANTER) != 0 && spellSchool == 4)
        || ((GetSpecialization() & SPECMASK_WIZARD_ILLUSIONIST) != 0 && spellSchool == 5)
        || ((GetSpecialization() & SPECMASK_WIZARD_EVOKER) != 0 && spellSchool == 6)
        || ((GetSpecialization() & SPECMASK_WIZARD_NECROMANCER) != 0 && spellSchool == 7)
        || ((GetSpecialization() & SPECMASK_WIZARD_TRANSMUTER) != 0 && spellSchool == 8)
        || ((GetSpecialization() & SPECMASK_WIZARD_UNIVERSAL) != 0 && spellSchool == 9);
}

// 0x703270
void CGameSprite::SetFootstepChannel()
{
    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1) {
        for (int index = 0; index < 2; index++) {
            m_sndWalk[index].SetChannel(19, reinterpret_cast<DWORD>(m_pArea));
            m_sndArmor[index].SetChannel(20, reinterpret_cast<DWORD>(m_pArea));
        }
        m_sndReady.SetChannel(19, reinterpret_cast<DWORD>(m_pArea));
        m_sndDeath.SetChannel(15, reinterpret_cast<DWORD>(m_pArea));
    } else {
        for (int index = 0; index < 2; index++) {
            m_sndWalk[index].SetChannel(18, reinterpret_cast<DWORD>(m_pArea));
            m_sndArmor[index].SetChannel(20, reinterpret_cast<DWORD>(m_pArea));
        }
        m_sndReady.SetChannel(18, reinterpret_cast<DWORD>(m_pArea));
        m_sndDeath.SetChannel(15, reinterpret_cast<DWORD>(m_pArea));
    }
}

// 0x703330
BYTE CGameSprite::GetSound(BYTE soundID)
{
    // NOTE: Unused.
    STR_RES strRes;

    SHORT nNumSounds;
    BYTE nSound;

    switch (soundID) {
    case 2:
        nNumSounds = GetNumSounds(7, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 7;
        } else {
            nSound = 7;
        }
        break;
    case 3:
        nNumSounds = GetNumSounds(9, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 9;
        } else {
            nSound = 9;
        }
        break;
    case 4:
        nNumSounds = GetNumSounds(11, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 11;
        } else {
            nSound = 11;
        }
        break;
    case 5:
        nNumSounds = GetNumSounds(2, 5);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 2;
        } else {
            nSound = 2;
        }
        break;
    case 6:
        nNumSounds = GetNumSounds(33, 3);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 33;
        } else {
            nSound = 33;
        }
        break;
    case 7:
        nNumSounds = GetNumSounds(36, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 36;
        } else {
            nSound = 36;
        }
        break;
    case 8:
        nNumSounds = GetNumSounds(13, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 13;
        } else {
            nSound = 13;
        }
        break;
    case 9:
        if (field_710C > 8) {
            nSound = field_710E + 29;
            field_710E++;
            if (field_710E >= GetNumSounds(29, 4)) {
                field_710E = 0;
            }
            field_710A = 0;
            field_710C = 0;
        } else {
            nNumSounds = GetNumSounds(15, 7);
            if (nNumSounds > 0) {
                nSound = field_710A % nNumSounds;
            } else {
                nSound = 0;
            }
            field_710A++;
            field_710C++;
        }
        break;
    case 10:
        nNumSounds = GetNumSounds(15, 7);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 15;
        } else {
            nSound = 15;
        }
        break;
    case 11:
        nNumSounds = GetNumSounds(22, 7);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 22;
        } else {
            nSound = 22;
        }
        break;
    case 12:
        nNumSounds = GetNumSounds(29, 4);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 29;
        } else {
            nSound = 29;
        }
        break;
    case 13:
        nNumSounds = GetNumSounds(38, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 38;
        } else {
            nSound = 38;
        }
        break;
    case 14:
        nNumSounds = GetNumSounds(40, 4);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 40;
        } else {
            nSound = 40;
        }
        break;
    case 15:
        // FIXME: Not sure if it can overrun `m_speech` and treat `m_biography`
        // as sound?
        nNumSounds = GetNumSounds(44, 20);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 44;
        } else {
            nSound = 44;
        }
        break;
    case 16:
        nNumSounds = GetNumSounds(40, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 40;
        } else {
            nSound = 40;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 7658
        UTIL_ASSERT(FALSE);
    }

    return nSound;
}

// 0x703700
void CGameSprite::Render(CGameArea* pArea, CVidMode* pVidMode, INT nSurface)
{
    BOOLEAN bDithered = FALSE;
    BOOLEAN bFadeOut = FALSE;
    DWORD dwRenderFlags = 0x20000;
    CVisibilityMap* pVisibility;
    COLORREF rgbTint;
    COLORREF rgbGlobalTint;
    BYTE transparency;
    CSearchBitmap* pSearch;
    CRect rFX;
    CRect rGCBounds;
    CRect rViewRect;
    CPoint ptReference;
    CPoint newPos;
    POSITION bloodLstPos;
    CBlood* pBlood;
    SHORT nBloodDir;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 7687
    UTIL_ASSERT(pVidMode != NULL);

    if (m_active
        && m_activeAI
        && m_activeImprisonment
        && ((m_derivedStats.m_generalState & STATE_DEAD) != 0
            || m_canBeSeen > 0)
        && m_pArea == pArea
        && (m_typeAI.GetEnemyAlly() <= CAIObjectType::EA_CONTROLCUTOFF
            || (m_derivedStats.m_generalState & STATE_INVISIBLE) == 0)
        && m_baseStats.field_294 != 1
        && m_baseStats.m_animationType != 0) {
        pSearch = &(m_pArea->m_search);
        pVisibility = &(m_pArea->m_visibility);

        newPos.x = min(max(m_pos.x, 0), m_pArea->GetInfinity()->nAreaX - 1);
        newPos.y = min(max(m_pos.y, 0), m_pArea->GetInfinity()->nAreaY - 1);

        if (pVisibility->IsTileExplored(pVisibility->PointToTile(newPos))) {
            if (m_canBeSeen < VISIBLE_DELAY + 1
                || !pVisibility->IsTileVisible(pVisibility->PointToTile(newPos))) {
                bFadeOut = TRUE;
            }

            rViewRect.left = m_pArea->GetInfinity()->nCurrentX;
            rViewRect.top = m_pArea->GetInfinity()->nCurrentY;
            rViewRect.right = rViewRect.left + m_pArea->GetInfinity()->rViewPort.Width();
            rViewRect.bottom = rViewRect.top + m_pArea->GetInfinity()->rViewPort.Height();

            if (!m_lstBlood.IsEmpty()) {
                bloodLstPos = m_lstBlood.GetHeadPosition();
                while (bloodLstPos != NULL) {
                    pBlood = m_lstBlood.GetNext(bloodLstPos);
                    nBloodDir = pBlood->GetDirection();
                    if (pBlood->BloodLeft()
                        && nBloodDir >= 4
                        && nBloodDir <= 12) {
                        pBlood->Render(pVidMode, nSurface);
                    }
                }
            }

            // NOTE: Uninline.
            m_animation.CalculateFxRect(rFX, ptReference, m_posZ);

            if (m_id == m_pArea->m_iPicked
                || g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bAlwaysDither
                || g_pBaldurChitin->GetObjectGame()->m_bForceDither) {
                bDithered = TRUE;
            }

            rgbTint = m_pArea->GetTintColor(CPoint(m_pos.x, m_pos.y + m_posZ),
                m_listType);

            if (m_pArea->m_nInfravision
                && m_animation.DetectedByInfravision()
                && Animate()) {
                if ((m_pArea->GetInfinity()->m_areaType & 0x2) != 0
                    && ((m_pArea->GetInfinity()->m_areaType & 0x40) == 0
                        || (m_pArea->GetInfinity()->m_renderDayNightCode & 0x2) == 0)) {
                    rgbGlobalTint = g_pBaldurChitin->GetCurrentVideoMode()->GetGlobalTintColor();
                } else {
                    rgbGlobalTint = RGB(255, 255, 255);
                }

                if (GetRValue(rgbTint) * GetRValue(rgbGlobalTint) / 255 > GetRValue(CInfinity::RGB_NIGHT_COLOR)
                    || GetGValue(rgbTint) * GetGValue(rgbGlobalTint) / 255 > GetGValue(CInfinity::RGB_NIGHT_COLOR)
                    || GetBValue(rgbTint) * GetBValue(rgbGlobalTint) / 255 > GetBValue(CInfinity::RGB_NIGHT_COLOR)) {
                    if ((m_pArea->GetInfinity()->m_areaType & 0x2) != 0
                        && ((m_pArea->GetInfinity()->m_areaType & 0x40) == 0
                            || (m_pArea->GetInfinity()->m_renderDayNightCode & 0x2) == 0)) {
                        dwRenderFlags |= 0x10000;
                    }
                } else {
                    rgbTint = RGB(200, 200, 200);
                }
            } else {
                if ((m_pArea->GetInfinity()->m_areaType & 0x2) != 0
                    && ((m_pArea->GetInfinity()->m_areaType & 0x40) == 0
                        || (m_pArea->GetInfinity()->m_renderDayNightCode & 0x2) == 0)) {
                    dwRenderFlags |= 0x10000;
                }
            }

            transparency = 0;

            if (m_derivedStats.m_visualEffects[IWD_VFX_BLUR]) {
                transparency = 180;
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_INVISIBILITY]) {
                transparency = static_cast<BYTE>(abs(g_pBaldurChitin->nAUCounter % 80 - 40)) + 140;
            }

            // NOTE: Unsigned compare.
            if (m_derivedStats.m_nTranslucent > 0 && transparency < static_cast<BYTE>(m_derivedStats.m_nTranslucent)) {
                transparency = static_cast<BYTE>(m_derivedStats.m_nTranslucent);
            }

            if (m_derivedStats.m_nMirrorImages > 0) {
                if (transparency < 96) {
                    transparency = 96;
                }
            }

            if (m_baseStats.field_2F9 > 0 && transparency < m_baseStats.field_2F9) {
                transparency = m_baseStats.field_2F9;
            }

            if (m_derivedStats.m_nMirrorImages > 0) {
                if (m_derivedStats.m_nMirrorImages > 2) {
                    RenderMirrorImage(2,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 4) {
                    RenderMirrorImage(4,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 6) {
                    RenderMirrorImage(6,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 0) {
                    RenderMirrorImage(0,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 1) {
                    RenderMirrorImage(1,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }
            }

            IcewindCVisualEffect vfx;
            vfx.sub_586A90(TRUE);

            if (m_derivedStats.m_visualEffects[IWD_VFX_GREASE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_GREASE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SHIELD_OF_LATHANDER_2]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SHIELD_OF_LATHANDER_2]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_GREATER_SHIELD_OF_LATHANDER_2]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_GREATER_SHIELD_OF_LATHANDER_2]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SEVEN_EYES_2]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SEVEN_EYES_2]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_28]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_28]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_29]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_29]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_BLUR]
                && m_pos != m_posOld) {
                LONG dx = (m_pos.x - m_posOld.x) / 2;
                LONG dy = (m_pos.y - m_posOld.y) / 2;
                for (int cnt = 0; cnt < 4; cnt++) {
                    m_animation.CalculateGCBoundsRect(rGCBounds,
                        newPos,
                        ptReference,
                        m_posZ,
                        rFX.Width(),
                        rFX.Height());

                    if (!IsRectEmpty(rViewRect & rGCBounds)) {
                        m_animation.Render(m_pArea->GetInfinity(),
                            pVidMode,
                            nSurface,
                            rFX,
                            newPos,
                            ptReference,
                            dwRenderFlags,
                            rgbTint,
                            rGCBounds,
                            bDithered,
                            bFadeOut,
                            m_posZ,
                            transparency);
                    }

                    newPos.x -= dx;
                    newPos.y -= dy;
                }
            } else {
                m_animation.CalculateGCBoundsRect(rGCBounds,
                    newPos,
                    ptReference,
                    m_posZ,
                    rFX.Width(),
                    rFX.Height());

                if (!IsRectEmpty(rViewRect & rGCBounds)) {
                    m_animation.Render(m_pArea->GetInfinity(),
                        pVidMode,
                        nSurface,
                        rFX,
                        newPos,
                        ptReference,
                        dwRenderFlags,
                        rgbTint,
                        rGCBounds,
                        bDithered,
                        bFadeOut,
                        m_posZ,
                        transparency);
                }
            }

            if (m_derivedStats.m_nMirrorImages > 0) {
                if (m_derivedStats.m_nMirrorImages > 7) {
                    RenderMirrorImage(7,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 5) {
                    RenderMirrorImage(5,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }

                if (m_derivedStats.m_nMirrorImages > 3) {
                    RenderMirrorImage(3,
                        rFX,
                        rGCBounds,
                        rViewRect,
                        ptReference,
                        pSearch,
                        pVisibility,
                        pVidMode,
                        nSurface,
                        rgbTint,
                        bDithered,
                        bFadeOut,
                        dwRenderFlags);
                }
            }

            RenderSpriteEffect(pVidMode, nSurface);

            if (m_derivedStats.m_visualEffects[IWD_VFX_ENTANGLE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_ENTANGLE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_WEB]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_WEB]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SHROUD_OF_FLAME]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SHROUD_OF_FLAME]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_ANTIMAGIC_MISSILE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_ANTIMAGIC_MISSILE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_OTILUKES_RESILIENT_SPHERE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_OTILUKES_RESILIENT_SPHERE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_PROTECTION_FROM_MISSILES]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_PROTECTION_FROM_MISSILES]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_CLOAK_OF_FEAR]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_CLOAK_OF_FEAR]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_ENTROPY_SHIELD]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_ENTROPY_SHIELD]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_FIRE_AURA]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_FIRE_AURA]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_FROST_AURA]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_FROST_AURA]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SANCTUARY]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SANCTUARY]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_GLOBE_OF_INVULNERABILITY]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_GLOBE_OF_INVULNERABILITY]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_INSECT_PLAGUE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_INSECT_PLAGUE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_STORM_SHELL]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_STORM_SHELL]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SHIELD_OF_LATHANDER]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SHIELD_OF_LATHANDER]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_GREATER_SHIELD_OF_LATHANDER]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_GREATER_SHIELD_OF_LATHANDER]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SEVEN_EYES]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SEVEN_EYES]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_MINOR_GLOBE_OF_INVULNERABILITY]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_MINOR_GLOBE_OF_INVULNERABILITY]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_SHIELD]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_SHIELD]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_FIRE_SHIELD_RED]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_FIRE_SHIELD_RED]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_FIRE_SHIELD_BLUE]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_FIRE_SHIELD_BLUE]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_TORTOISE_SHELL]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_TORTOISE_SHELL]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_DEATH_ARMOR]) {
                vfx.sub_586A90(FALSE);
                vfx.sub_586AC0(TRUE, 192);
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_DEATH_ARMOR]),
                    vfx);
            }

            if (m_derivedStats.m_visualEffects[IWD_VFX_WISP]) {
                RenderSpriteCover(pVidMode,
                    nSurface,
                    &(field_7548[IWD_VFX_WISP]),
                    vfx);
            }

            if (!m_lstBlood.IsEmpty()) {
                bloodLstPos = m_lstBlood.GetHeadPosition();
                while (bloodLstPos != NULL) {
                    CBlood* blood = m_lstBlood.GetNext(bloodLstPos);
                    pBlood = m_lstBlood.GetNext(bloodLstPos);
                    nBloodDir = pBlood->GetDirection();
                    if (pBlood->BloodLeft()
                        && (nBloodDir < 4 || nBloodDir > 12)) {
                        pBlood->Render(pVidMode, nSurface);
                    }
                }
            }
        }
    }
}

// 0x704770
void CGameSprite::RenderMarkers(CVidMode* pVidMode, INT nSurface)
{
    CPoint pt;
    pt.x = min(max(m_pos.x, 0), m_pArea->GetInfinity()->nAreaX - 1);
    pt.y = min(max(m_pos.y, 0), m_pArea->GetInfinity()->nAreaY - 1);

    if (m_pArea->m_visibility.IsTileExplored(m_pArea->m_visibility.PointToTile(pt))
        && (m_typeAI.m_nEnemyAlly <= CAIObjectType::EA_CONTROLCUTOFF
            || (m_derivedStats.m_generalState & STATE_INVISIBLE) == 0
            || (m_baseStats.field_2FC & 0x1) != 0)
        && m_baseStats.field_294 != 1) {
        DWORD level = g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nGuiFeedbackLevel;
        if (g_pBaldurChitin->GetScreenWorld()->field_14A) {
            level = 5;
        }
        if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_cutScene) {
            level = 1;
        }

        BOOLEAN dialogTalker = FALSE;
        if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_mode == 386
            || g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_mode == 1282) {
            CRect rViewPort(m_pArea->GetInfinity()->rViewPort);

            INT x;
            INT y;
            m_pArea->GetInfinity()->GetViewPosition(x, y);

            if (abs(GetPos().x - (x + rViewPort.Width() / 2)) < 16
                && abs(GetPos().y - (y + rViewPort.Height() / 2)) < 12) {
                dialogTalker = TRUE;
            }
        }

        switch (level) {
        case 1:
            if (m_talkingCounter > 0
                || dialogTalker
                || m_id == m_pArea->m_iPicked
                || m_id == m_pArea->m_iPickedTarget
                || m_marker.m_nRecticleForceRenderTarget != 0) {
                m_marker.Render(pVidMode, nSurface, this);
            }

            if (m_id == m_pArea->m_iPicked
                || m_id == m_pArea->m_iPickedTarget
                || m_marker.m_nRecticleForceRender != 0
                || m_groupMove) {
                if (Orderable(FALSE) && m_targetPoint.x != -1) {
                    m_destMarker.Render(pVidMode,
                        nSurface,
                        m_pArea->GetInfinity(),
                        m_targetPoint,
                        CMarker::RECTICLE_DEST_SIZE,
                        3 * CMarker::RECTICLE_DEST_SIZE / 4);
                }
            }
            break;
        case 2:
            if (m_bSelected
                || m_id == m_pArea->m_iPicked
                || m_id == m_pArea->m_iPickedTarget
                || m_marker.m_nRecticleForceRender != 0) {
                m_marker.Render(pVidMode, nSurface, this);

                if (Orderable(FALSE) && m_targetPoint.x != -1) {
                    m_destMarker.Render(pVidMode,
                        nSurface,
                        m_pArea->GetInfinity(),
                        m_targetPoint,
                        CMarker::RECTICLE_DEST_SIZE,
                        3 * CMarker::RECTICLE_DEST_SIZE / 4);
                }
            } else if (m_talkingCounter > 0) {
                m_marker.Render(pVidMode, nSurface, this);
            }
            break;
        case 3:
            if (Orderable(FALSE)
                || m_id == m_pArea->m_iPicked
                || m_id == m_pArea->m_iPickedTarget
                || m_marker.m_nRecticleForceRender != 0) {
                m_marker.Render(pVidMode, nSurface, this);

                if (Orderable(FALSE)
                    && (m_bSelected
                        || m_id == m_pArea->m_iPicked
                        || m_id == m_pArea->m_iPickedTarget)
                    && m_targetPoint.x != -1) {
                    m_destMarker.Render(pVidMode,
                        nSurface,
                        m_pArea->GetInfinity(),
                        m_targetPoint,
                        CMarker::RECTICLE_DEST_SIZE,
                        3 * CMarker::RECTICLE_DEST_SIZE / 4);
                }
            } else if (m_talkingCounter > 0) {
                m_marker.Render(pVidMode, nSurface, this);
            }
            break;
        case 4:
            if (Orderable(FALSE)
                || m_marker.m_type == CMarker::RECTICLE
                || m_id == m_pArea->m_iPicked
                || m_id == m_pArea->m_iPickedTarget) {
                m_marker.Render(pVidMode, nSurface, this);

                if (Orderable(FALSE)
                    && (m_bSelected
                        || m_id == m_pArea->m_iPicked
                        || m_id == m_pArea->m_iPickedTarget)
                    && m_targetPoint.x != -1) {
                    m_destMarker.Render(pVidMode,
                        nSurface,
                        m_pArea->GetInfinity(),
                        m_targetPoint,
                        CMarker::RECTICLE_DEST_SIZE,
                        3 * CMarker::RECTICLE_DEST_SIZE / 4);
                }
            } else if (m_talkingCounter > 0) {
                m_marker.Render(pVidMode, nSurface, this);
            }
            break;
        case 5:
            m_marker.Render(pVidMode, nSurface, this);

            if (Orderable(FALSE)
                && (m_bSelected
                    || m_id == m_pArea->m_iPicked
                    || m_id == m_pArea->m_iPickedTarget)
                && m_targetPoint.x != -1) {
                m_destMarker.Render(pVidMode,
                    nSurface,
                    m_pArea->GetInfinity(),
                    m_targetPoint,
                    CMarker::RECTICLE_DEST_SIZE,
                    3 * CMarker::RECTICLE_DEST_SIZE / 4);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 8300
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x704D40
void CGameSprite::RenderPortrait(const CPoint& cpRenderPosition, const CSize& szControl, BOOL bPressed, BOOL reorderHighlight, BOOL selectFromMarker, const CRect& rClip, BOOL bDoubleSize)
{
    BOOL bDead = FALSE;

    if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC
        && !InControl()) {
        return;
    }

    m_vbPortraitSmall.SetResRef(CResRef(m_baseStats.m_portraitSmall), TRUE, FALSE);
    m_vbPortraitSmall.m_bDoubleSize = bDoubleSize;

    if (CResRef(m_baseStats.m_portraitSmall) == "") {
        m_vbPortraitSmall.SetResRef(CResRef(CInfGame::SILHOUETTE_PORTRAIT_SM), TRUE, FALSE);
        m_vbPortraitSmall.m_bDoubleSize = bDoubleSize;
    }

    if (CResRef(m_baseStats.m_portraitSmall) != "" && m_vbPortraitSmall.GetRes() == NULL) {
        m_vbPortraitSmall.SetResRef(CResRef(CInfGame::SILHOUETTE_PORTRAIT_SM), TRUE, FALSE);
        m_vbPortraitSmall.m_bDoubleSize = bDoubleSize;
    }

    if (m_vbPortraitSmall.GetBitCount(FALSE) != 24
        && m_vbPortraitSmall.GetBitCount(FALSE) != 8) {
        m_vbPortraitSmall.SetResRef(CResRef(CInfGame::SILHOUETTE_PORTRAIT_SM), TRUE, TRUE);
        m_vbPortraitSmall.m_bDoubleSize = bDoubleSize;
    }

    INT nScale = bDoubleSize ? 2 : 1;

    CRect r1(cpRenderPosition.x,
        cpRenderPosition.y,
        cpRenderPosition.x + 44 * nScale,
        cpRenderPosition.y + 44 * nScale);

    INT v1;
    if (m_derivedStats.m_spellStates[SPLSTATE_SUPPRESS_HP_INFO]) {
        v1 = 42 * nScale;
    } else {
        v1 = 42 * nScale * (m_derivedStats.m_nMaxHitPoints - m_baseStats.m_hitPoints) / m_derivedStats.m_nMaxHitPoints;
    }

    if (m_baseStats.m_hitPoints <= 0) {
        bDead = TRUE;
    }

    COLORREF rgbColor;
    if (selectFromMarker) {
        if ((m_pArea != NULL && m_id == m_pArea->m_iPicked)
            || m_talkingCounter > 0) {
            rgbColor = m_marker.m_rgbColor;
        } else {
            rgbColor = CMarker::PC_SELECTED_COLOR;
            if (!m_bSelected) {
                rgbColor = RGB(0, 0, 0);
            }
        }
    } else {
        if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineMap) {
            rgbColor = GetMapScreenColor();
        } else {
            if (InControl() && m_nUnselectableCounter == 0) {
                rgbColor = CMarker::PC_SELECTED_COLOR;
            } else {
                rgbColor = CMarker::PC_NONECONTROLED_SELECTED_COLOR;
            }
            if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter()) {
                rgbColor = RGB(0, 0, 0);
            }
        }
    }

    INT v2 = 42 * nScale;

    CRect r2(cpRenderPosition.x + 2 * nScale,
        cpRenderPosition.y + 2 * nScale,
        cpRenderPosition.x + 2 * nScale + 42 * nScale,
        cpRenderPosition.y + 2 * nScale + 42 * nScale);
    CRect r3(r2);

    if (bDead) {
        m_vbPortraitSmall.SetTintColor(RGB(180, 180, 180));
        m_vbPortraitSmall.RenderDirect(CVIDINF_SURFACE_BACK,
            r2.left,
            r2.top,
            r2 & rClip,
            0xA0000,
            FALSE);
    } else {
        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nOldPortraitHealth == TRUE) {
            if (m_bBloodFlashOn) {
                m_vbPortraitSmall.SetTintColor(RGB(120 + static_cast<BYTE>(m_nBloodFlashAmount), 30, 30));
                m_vbPortraitSmall.RenderDirect(CVIDINF_SURFACE_BACK,
                    r2.left,
                    r2.top,
                    r2 & rClip,
                    0x20000,
                    FALSE);
            } else {
                if (field_53E6) {
                    m_vbPortraitSmall.SetTintColor(RGB(50, 255, 50));
                } else {
                    m_vbPortraitSmall.SetTintColor(RGB(120, 30, 30));
                }
                m_vbPortraitSmall.RenderDirect(CVIDINF_SURFACE_BACK,
                    r2.left,
                    r2.top,
                    r2 & rClip,
                    0x20000,
                    FALSE);
            }
        }
    }

    if (!GRAVITY_IS_DOWN
        && g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nOldPortraitHealth == TRUE) {
        r2.bottom = r2.top + v2 - v1;
    }

    if (!bDead) {
        m_vbPortraitSmall.SetTintColor(RGB(255, 255, 255));

        if (GRAVITY_IS_DOWN) {
            CRect r3(rClip);

            if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nOldPortraitHealth == TRUE) {
                r3.top = r2.bottom + v1 - v2;
            }

            m_vbPortraitSmall.RenderDirect(CVIDINF_SURFACE_BACK,
                r2.left,
                r2.top,
                r2 & r3,
                0x20000,
                FALSE);
        } else {
            m_vbPortraitSmall.RenderDirect(CVIDINF_SURFACE_BACK,
                r2.left,
                r2.top,
                r2 & r2,
                0x20000,
                FALSE);
        }
    }

    CRect rLineClip(rClip);
    if (rgbColor != 0) {
        r1.right++;
        rLineClip.right++;

        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.left,
            r1.top,
            r1.left,
            r1.bottom,
            CVIDINF_SURFACE_BACK,
            rLineClip & r1,
            rgbColor);

        if (rLineClip.bottom != r1.bottom) {
            g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.left,
                r1.bottom,
                r1.right,
                r1.bottom,
                CVIDINF_SURFACE_BACK,
                rLineClip & r1,
                rgbColor);
        }

        if (rLineClip.right != r1.right) {
            g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.right,
                r1.bottom,
                r1.right,
                r1.top,
                CVIDINF_SURFACE_BACK,
                rLineClip & r1,
                rgbColor);
        }

        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.right,
            r1.top,
            r1.left,
            r1.top,
            CVIDINF_SURFACE_BACK,
            rLineClip & r1,
            rgbColor);
    }

    if (reorderHighlight) {
        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.left,
            r1.top,
            r1.left,
            r1.bottom,
            CVIDINF_SURFACE_BACK,
            r1 & rLineClip,
            RGB(255, 255, 0));

        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.left,
            r1.bottom,
            r1.right,
            r1.bottom,
            CVIDINF_SURFACE_BACK,
            r1 & rLineClip,
            RGB(255, 255, 0));

        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.right,
            r1.bottom,
            r1.right,
            r1.top,
            CVIDINF_SURFACE_BACK,
            r1 & rLineClip,
            RGB(255, 255, 0));

        g_pBaldurChitin->GetCurrentVideoMode()->DrawLine(r1.right,
            r1.top,
            r1.left,
            r1.top,
            CVIDINF_SURFACE_BACK,
            r1 & rLineClip,
            RGB(255, 255, 0));
    }

    CPoint ptIcon(r3.left, r3.bottom);
    POSITION pos = m_portraitIcons.GetHeadPosition();
    while (pos != NULL) {
        SHORT nIcon = static_cast<SHORT>(reinterpret_cast<INT>(m_portraitIcons.GetNext(pos)));
        if (nIcon < m_portraitIconVidCell.GetNumberSequences(FALSE)) {
            m_portraitIconVidCell.SequenceSet(nIcon + 65);
            m_portraitIconVidCell.FrameSet(0);
            m_portraitIconVidCell.Render(CVIDINF_SURFACE_BACK,
                ptIcon.x,
                ptIcon.y,
                r3 & rClip,
                NULL,
                0,
                0,
                -1);
            ptIcon.x += PORTRAIT_ICON_SIZE.x * nScale;
            if (ptIcon.x > r3.right - PORTRAIT_ICON_SIZE.x * nScale) {
                ptIcon.x = r3.left;
                ptIcon.y -= PORTRAIT_ICON_SIZE.y * nScale;
            }
        }
    }

    CVidFont font;
    if (!bDead) {
        if (SHOW_CHARACTER_HP) {
            font.SetResRef(CResRef("NUMFONT"), bDoubleSize, TRUE);
            font.SequenceSet(0);
            if (font.GetRes()->Demand() != NULL) {
                // 0x85BD4C
                static const INT HEALTH_VALUE[4] = {
                    100,
                    75,
                    50,
                    25,
                };

                // 0x85BD5C
                static const COLORREF HEALTH_COLOR[4] = {
                    RGB(255, 255, 255),
                    RGB(0, 250, 0),
                    RGB(255, 255, 0),
                    RGB(255, 128, 0),
                };

                CString sHealth;
                INT iHealthPercent = 100 * m_baseStats.m_hitPoints / m_derivedStats.m_nMaxHitPoints;
                COLORREF rgbColor;

                for (int index = 0; index < 4; index++) {
                    if (iHealthPercent >= HEALTH_VALUE[index]) {
                        rgbColor = HEALTH_COLOR[index];
                        break;
                    }
                }

                if (m_derivedStats.m_spellStates[SPLSTATE_SUPPRESS_HP_INFO]) {
                    sHealth.Format("%c/%c", '-', '-');
                    rgbColor = RGB(255, 0, 0);
                } else {
                    sHealth.Format("%d/%d", m_baseStats.m_hitPoints, m_derivedStats.m_nMaxHitPoints);
                }

                if (m_baseStats.m_hitPoints == 0) {
                    rgbColor = RGB(128, 128, 128);
                }

                font.SetColor(rgbColor, RGB(0, 0, 0), TRUE);
                font.TextOut(sHealth,
                    r3.left,
                    cpRenderPosition.y + font.GetFontHeight(FALSE),
                    rClip,
                    CVIDINF_SURFACE_BACK);
                font.GetRes()->Release();
            }
        }
    }

    if (m_bLevelUp) {
        m_portraitIconVidCell.SequenceSet(254);
        m_portraitIconVidCell.FrameSet(0);
        m_portraitIconVidCell.Render(CVIDINF_SURFACE_BACK,
            r3.right - PORTRAIT_ICON_SIZE.x * nScale,
            r3.top + PORTRAIT_ICON_SIZE.y * nScale,
            r3 & rClip,
            NULL,
            0,
            0,
            -1);
    }
}

// 0x705AD0
void CGameSprite::RenderToMapScreen(const CRect& rClipBase, const CPoint& ptCharPos)
{
    CRect rClip(rClipBase);
    INT nScale = g_pBaldurChitin->field_4A28 ? 2 : 1;
    if (!g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC
        || InControl()) {
        if (!IcewindMisc::IsDead(this)) {
            CPoint center;
            CSize axes;
            COLORREF rgbColor;

            center.x = nScale * (4 * ptCharPos.x / 32) - rClip.left;
            center.y = nScale * (4 * ptCharPos.y / 32) - rClip.top;
            rClip.OffsetRect(-rClip.left, -rClip.top);

            axes.cx = GetAnimation()->GetPersonalSpace();
            if (!g_pBaldurChitin->field_4A28) {
                axes.cx = max(axes.cx - 2, 3);
            }
            axes.cy = 3 * GetAnimation()->GetPersonalSpace() / 4;

            rgbColor = g_pBaldurChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(GetMapScreenColor());

            static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode())->BKRenderEllipse(center, axes, rClip, rgbColor);
        }
    }
}

// 0x705CC0
COLORREF CGameSprite::GetMapScreenColor()
{
    COLORREF rgbColor;
    BYTE enemyAlly = m_liveTypeAI.GetEnemyAlly();
    if (enemyAlly == CAIObjectType::EA_PC
        || enemyAlly == CAIObjectType::EA_FAMILIAR
        || enemyAlly == CAIObjectType::EA_ALLY
        || enemyAlly == CAIObjectType::EA_0x847C3A
        || enemyAlly == CAIObjectType::EA_CONTROLLED
        || enemyAlly == CAIObjectType::EA_GOODCUTOFF) {
        if (m_moraleFailure) {
            rgbColor = CMarker::PC_MORALE_FAILURE_COLOR;
        } else if (InControl() && m_nUnselectableCounter == 0) {
            if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter()) {
                rgbColor = CMarker::PC_SELECTED_COLOR;
            } else {
                rgbColor = CMarker::PC_COLOR;
            }
        } else {
            if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter()) {
                rgbColor = CMarker::PC_NONECONTROLED_SELECTED_COLOR;
            } else {
                rgbColor = CMarker::PC_NONECONTROLED_COLOR;
            }
        }
    } else if (enemyAlly == CAIObjectType::EA_ENEMY
        || enemyAlly == CAIObjectType::EA_CHARMED_PC) {
        rgbColor = CMarker::ENEMY_COLOR;
    } else if (enemyAlly == CAIObjectType::EA_NEUTRAL) {
        rgbColor = CMarker::NEUTRAL_COLOR;
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 8754
        UTIL_ASSERT(FALSE);
    }

    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->GetActiveEngine()->GetPickedCharacter()) {
        ULONG nQuarterPeriod = CMarker::PICKED_FLASH_PERIOD / 4;
        ULONG nAsyncCounter = g_pBaldurChitin->nAUCounter % CMarker::PICKED_FLASH_PERIOD;
        BYTE red;
        BYTE green;
        BYTE blue;

        if (nAsyncCounter < nQuarterPeriod) {
            red = static_cast<BYTE>(nAsyncCounter * GetRValue(rgbColor) / nQuarterPeriod);
            green = static_cast<BYTE>(nAsyncCounter * GetGValue(rgbColor) / nQuarterPeriod);
            blue = static_cast<BYTE>(nAsyncCounter * GetBValue(rgbColor) / nQuarterPeriod);
        } else if (nAsyncCounter < nQuarterPeriod * 2) {
            nAsyncCounter -= nQuarterPeriod;
            red = static_cast<BYTE>(GetRValue(rgbColor) + nAsyncCounter * (255 - GetRValue(rgbColor)) / nQuarterPeriod);
            green = static_cast<BYTE>(GetGValue(rgbColor) + nAsyncCounter * (255 - GetGValue(rgbColor)) / nQuarterPeriod);
            blue = static_cast<BYTE>(GetBValue(rgbColor) + nAsyncCounter * (255 - GetBValue(rgbColor)) / nQuarterPeriod);
        } else if (nAsyncCounter < nQuarterPeriod * 3) {
            nAsyncCounter -= nQuarterPeriod * 2;
            red = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetRValue(rgbColor)) / nQuarterPeriod);
            green = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetGValue(rgbColor)) / nQuarterPeriod);
            blue = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetBValue(rgbColor)) / nQuarterPeriod);
        } else {
            nAsyncCounter -= nQuarterPeriod * 3;
            red = static_cast<BYTE>(GetRValue(rgbColor) - nAsyncCounter * GetRValue(rgbColor) / nQuarterPeriod);
            green = static_cast<BYTE>(GetGValue(rgbColor) - nAsyncCounter * GetGValue(rgbColor) / nQuarterPeriod);
            blue = static_cast<BYTE>(GetBValue(rgbColor) - nAsyncCounter * GetBValue(rgbColor) / nQuarterPeriod);
        }

        rgbColor = RGB(red, green, blue);
    }

    return rgbColor;
}

// 0x705FD0
void CGameSprite::Select()
{
    m_bSelected = TRUE;
    m_firstActionSound = TRUE;
    m_pArea->m_pGame->GetGroup()->Add(this);
    if (m_targetId != CGameObjectArray::INVALID_INDEX && Orderable(FALSE)) {
        CGameObject* pObject;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                static_cast<CGameSprite*>(pObject)->m_marker.SetType(CMarker::RECTICLE);
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x7060C0
void CGameSprite::Unselect()
{
    CGameSprite* pSprite = NULL;

    m_bSelected = FALSE;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_id,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite != NULL) {
            g_pBaldurChitin->GetObjectGame()->GetGroup()->Remove(pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_id,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        if (m_targetId != CGameObjectArray::INVALID_INDEX && Orderable(FALSE)) {
            CGameObject* pObject;

            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                    static_cast<CGameSprite*>(pObject)->m_marker.SetType(CMarker::ELLIPSE);
                }

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }
}

// 0x706220
void CGameSprite::SetCursor(LONG nToolTip)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (m_canBeSeen > 0) {
        switch (pGame->GetState()) {
        case 0:
            // NOTE: Unsigned compare.
            if (static_cast<DWORD>(nToolTip) < static_cast<DWORD>(pGame->GetOptions()->m_nTooltips)) {
                if (pGame->GetGroup()->GetCount() != 0) {
                    if ((pGame->GetCharacterPortraitNum(m_id) != -1
                            || pGame->IsAlly(m_id)
                            || pGame->IsFamiliar(m_id)
                            || m_typeAI.GetEnemyAlly() <= CAIObjectType::EA_CONTROLCUTOFF)
                        && (!g_pBaldurChitin->GetObjectGame()->GetGameSave()->field_1AC || InControl())) {
                        if (InControl()) {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                        } else {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(46, FALSE);
                        }
                    } else {
                        if (m_typeAI.GetEnemyAlly() < CAIObjectType::EA_EVILCUTOFF) {
                            if (pGame->GetGroup()->IsPartyLeader()) {
                                if ((m_baseStats.m_flags & 0x80000) != 0) {
                                    g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                                } else {
                                    g_pBaldurChitin->GetObjectCursor()->SetCursor(18, FALSE);
                                }
                            } else {
                                g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                            }
                        } else {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(12, FALSE);
                        }
                    }
                } else {
                    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                }
            } else {
                SetCharacterToolTip(NULL);
            }
            break;
        case 1:
            if (pGame->GetIconIndex() != -1) {
                g_pBaldurChitin->GetObjectCursor()->SetCursor(pGame->GetIconIndex(), FALSE);
            } else {
                g_pBaldurChitin->GetObjectCursor()->SetCursor(20, FALSE);
            }
            break;
        case 2:
            switch (pGame->GetIconIndex()) {
            case 12:
                g_pBaldurChitin->GetObjectCursor()->SetCursor(12, FALSE);
                if (m_bSelected && pGame->GetGroup()->GetCount() == 1) {
                    g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                }
                break;
            case 18:
                g_pBaldurChitin->GetObjectCursor()->SetCursor(18, FALSE);
                if (!pGame->GetGroup()->IsPartyLeader()) {
                    g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                }
                break;
            case 36:
            case 40:
                if (1) {
                    g_pBaldurChitin->GetObjectCursor()->SetCursor(40, FALSE);
                    if (m_bSelected) {
                        g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                    }

                    SHORT nPortrait = g_pBaldurChitin->GetScreenWorld()->GetSelectedCharacter();
                    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

                    CGameSprite* pSprite;

                    BYTE rc;
                    do {
                        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            reinterpret_cast<CGameObject**>(&pSprite),
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        if (pSprite->m_baseStats.m_skills[CGAMESPRITE_SKILL_PICK_POCKET] == 0) {
                            g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                                CGameObjectArray::THREAD_ASYNCH,
                                INFINITE);
                        }
                    }
                }
                break;
            case 255:
                g_pBaldurChitin->GetObjectCursor()->SetCursor(20, FALSE);
                break;
            default:
                g_pBaldurChitin->GetObjectCursor()->SetCursor(pGame->GetIconIndex(), FALSE);
                break;
            }
        case 3:
            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 9053
            UTIL_ASSERT(FALSE);
        }
    } else {
        CGameObject::SetCursor(nToolTip);
    }
}

// 0x706720
void CGameSprite::SetCharacterToolTip(CUIControlBase* pControl)
{
    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1) {
        if (m_baseStats.m_name != -1) {
            CString sHitPoints;
            if (!m_derivedStats.m_spellStates[SPLSTATE_SUPPRESS_HP_INFO]) {
                sHitPoints.Format("%d/%d",
                    m_baseStats.m_hitPoints,
                    m_derivedStats.m_nMaxHitPoints);
            } else {
                sHitPoints.Format("%c/%c", '?', '?');
            }
            g_pBaldurChitin->GetObjectCursor()->SetToolTip(m_baseStats.m_name,
                pControl,
                sHitPoints);
        } else {
            CString sHitPoints;
            if (!m_derivedStats.m_spellStates[SPLSTATE_SUPPRESS_HP_INFO]) {
                sHitPoints.Format("%s\n%d/%d",
                    (LPCSTR)m_sName,
                    m_baseStats.m_hitPoints,
                    m_derivedStats.m_nMaxHitPoints);
            } else {
                sHitPoints.Format("%s\n%c/%c", (LPCSTR)m_sName, '?', '?');
            }
            g_pBaldurChitin->GetObjectCursor()->SetToolTip(m_baseStats.m_name,
                pControl,
                sHitPoints);
        }
    } else {
        BOOLEAN bReturn = FALSE;
        STR_RES strRes;
        if ((m_baseStats.m_flags & 0x1000) == 0) {
            if (m_typeAI.GetEnemyAlly() >= CAIObjectType::EA_EVILCUTOFF
                || m_typeAI.GetEnemyAlly() <= CAIObjectType::EA_GOODCUTOFF) {
                if (m_baseStats.m_hitPoints == m_derivedStats.m_nMaxHitPoints) {
                    bReturn = g_pBaldurChitin->GetTlkTable().Fetch(2943, strRes);
                } else {
                    INT nHealthPercent = 100 * m_baseStats.m_hitPoints / m_derivedStats.m_nMaxHitPoints;
                    if (nHealthPercent > 75) {
                        bReturn = g_pBaldurChitin->GetTlkTable().Fetch(2944, strRes);
                    } else if (nHealthPercent > 50) {
                        bReturn = g_pBaldurChitin->GetTlkTable().Fetch(2945, strRes);
                    } else if (nHealthPercent > 25) {
                        bReturn = g_pBaldurChitin->GetTlkTable().Fetch(2946, strRes);
                    } else {
                        bReturn = g_pBaldurChitin->GetTlkTable().Fetch(2947, strRes);
                    }
                }
            }
        }

        if ((m_baseStats.m_flags & 0x1) != 0) {
            if (m_baseStats.m_name != -1) {
                g_pBaldurChitin->GetObjectCursor()->SetToolTip(m_baseStats.m_name,
                    NULL,
                    strRes.szText);
            } else {
                if (bReturn) {
                    g_pBaldurChitin->GetObjectCursor()->SetToolTip(-1,
                        NULL,
                        m_sName + "\n" + strRes.szText);
                } else {
                    g_pBaldurChitin->GetObjectCursor()->SetToolTip(-1,
                        NULL,
                        m_sName);
                }
            }
        } else if (m_baseStats.m_apparentName != -1) {
            g_pBaldurChitin->GetObjectCursor()->SetToolTip(m_baseStats.m_apparentName,
                NULL,
                strRes.szText);
        } else {
            if (bReturn) {
                g_pBaldurChitin->GetObjectCursor()->SetToolTip(-1,
                    NULL,
                    m_sName + "\n" + strRes.szText);
            } else {
                g_pBaldurChitin->GetObjectCursor()->SetToolTip(-1,
                    NULL,
                    m_sName + "\n" + strRes.szText);
            }
        }
    }
}

// 0x706B40
void CGameSprite::SetDirection(const CPoint& posDest)
{
    if (m_pos == posDest) {
        // NOTE: Uninline.
        SetDirection(m_nNewDirection);
    } else {
        // NOTE: Uninline.
        SetDirection(GetDirection(posDest));
    }
}

// 0x706C80
void CGameSprite::SetDirection(SHORT direction)
{
    m_nNewDirection = direction;
    m_deltaDirection = direction > m_nDirection ? 1 : -1;

    if (direction - m_nDirection > 8 || direction - m_nDirection <= -8) {
        // FIXME: Same value?
        m_deltaDirection = direction > m_nDirection ? 1 : -1;
    }

    if (abs(direction - m_nDirection) == 8) {
        m_skipDeltaDirection = 4;
    } else {
        m_skipDeltaDirection = 0;
    }

    if (m_nSequence == CGAMESPRITE_SEQ_WALK && m_walkBackwards) {
        if (abs(direction - m_nDirection) == 8) {
            m_nNewDirection = (direction + 8) % 16;
            m_deltaDirection = -m_deltaDirection;
        } else {
            m_walkBackwards = FALSE;
        }
    }
}

// 0x706F80
void CGameSprite::SetFacing(SHORT direction)
{
    m_nDirection = direction;
    m_nNewDirection = direction;

    // NOTE: Uninline.
    GetAnimation()->ChangeDirection(direction);

    if (m_derivedStats.m_visualEffects[IWD_VFX_BLUR]) {
        InitBlur();
    }
}

// 0x706FE0
void CGameSprite::InitBlur()
{
    m_posOld = m_pos;

    if (m_nDirection >= 2 && m_nDirection <= 7) {
        // NOTE: Uninline.
        m_posOld.x += GetAnimation()->GetMoveScale();
    } else if (m_nDirection >= 10) {
        // NOTE: Uninline.
        m_posOld.x -= GetAnimation()->GetMoveScale();
    }

    if (m_nDirection <= 3 || m_nDirection >= 14) {
        // NOTE: Uninline.
        m_posOld.y -= 3 * GetAnimation()->GetMoveScale() / 4;
    } else if (m_nDirection >= 6 && m_nDirection <= 11) {
        // NOTE: Uninline.
        m_posOld.y += 3 * GetAnimation()->GetMoveScale() / 4;
    }
}

// 0x707170
void CGameSprite::SetIdleSequence()
{
    // NOTE: Uninline.
    SHORT nIdleSequence = GetIdleSequence();

    // NOTE: Uninline.
    BOOL bIsEndOfSequence = m_animation.IsEndOfSequence();

    if (m_nSequence != nIdleSequence || bIsEndOfSequence) {
        SetSequence(nIdleSequence);
    }
}

// 0x7071F0
SHORT CGameSprite::GetIdleSequence()
{
    if (m_pArea != NULL
        && m_pArea->m_bAreaLoaded
        && g_pBaldurChitin->GetObjectGame()->sub_5AC0A0(m_pArea)) {
        return 7; // SEQ_READY
    } else {
        return 6; // SEQ_HEAD_TURN
    }
}

// 0x707230
void CGameSprite::SetSequence(SHORT nSequence)
{
    if (nSequence == SEQ_WALK) {
        // NOTE: Uninline.
        if (m_animation.GetMoveScale() == 0) {
            return;
        }
    }

    if (m_nSequence == nSequence) {
        // NOTE: Uninline.
        if (m_nSequence != GetIdleSequence()) {
            return;
        }
    }

    if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0
        && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
            || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1)
        && m_nSequence != nSequence
        && m_pArea == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()
        && m_pArea != NULL) {
        m_currSndArmor = 0;
        m_sndArmor[m_currSndArmor].Stop();

        // NOTE: Uninline.
        char* sndArmor = m_animation.GetSndArmor();

        if (sndArmor[0] != '\0') {
            // NOTE: Uninline.
            m_sndArmor[m_currSndArmor].SetResRef(CResRef(sndArmor), TRUE, TRUE);
            delete sndArmor;

            CPoint ear;
            LONG earZ;
            g_pBaldurChitin->cSoundMixer.GetListenPosition(ear, earZ);

            LONG priority = max(99 - 99 * ((ear.y - m_pos.y) * (ear.y - m_pos.y) / 144 + (ear.x - m_pos.x) * (ear.x - m_pos.x) / 256) / 6400, 0);
            m_sndArmor[m_currSndArmor].SetPriority(static_cast<BYTE>(priority));

            m_sndArmor[m_currSndArmor].Play(m_pos.x, m_pos.y, m_posZ, FALSE);
        }
    }

    if ((m_derivedStats.m_generalState & STATE_SILENCED) == 0
        && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bFootStepsSounds
            || g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1)
        && m_nSequence != nSequence
        && m_pArea == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()
        && m_pArea != NULL
        && nSequence != SEQ_DIE
        && nSequence != SEQ_SLEEP
        && nSequence != SEQ_TWITCH
        && nSequence != SEQ_WALK
        && nSequence != SEQ_AWAKE) {
        if (!m_sndReady.IsSoundPlaying()) {
            // NOTE: Uninline.
            char* sndReady = m_animation.GetSndReady();

            if (sndReady[0] != '\0') {
                // NOTE: Uninline.
                m_sndReady.SetResRef(CResRef(sndReady), TRUE, TRUE);

                delete sndReady;

                m_sndReady.SetLoopingFlag(1);
                m_sndReady.Play(m_pos.x, m_pos.y, m_posZ, FALSE);
            }
        }
    } else {
        m_sndReady.Stop();
    }

    SHORT nDirection = m_nDirection & 0xFE;
    CItem* curWeapon;
    const ITEM_ABILITY* curAttack;

    switch (nSequence) {
    case SEQ_ATTACK:
        curWeapon = m_equipment.m_items[m_equipment.m_selectedWeapon];
        if (curWeapon != NULL) {
            curWeapon->Demand();
            curAttack = curWeapon->GetAbility(m_equipment.m_selectedWeaponAbility);
        } else {
            SelectWeaponAbility(CGameSpriteEquipment::SLOT_FIST, 0, 0, 1);
            curAttack = &DEFAULT_ATTACK;
        }

        if (curAttack == NULL) {
            curAttack = &DEFAULT_ATTACK;
        }

        if (curAttack->type != 2) {
            LONG totalProb = 0;
            LONG prob = rand() % 100 + 1;
            for (int index = 0; index < 6 && prob > totalProb; index++) {
                totalProb += curAttack->attackProbability[index];
                if (prob <= totalProb) {
                    switch (index) {
                    case 0:
                        nSequence = SEQ_ATTACK_SLASH;
                        break;
                    case 1:
                        nSequence = SEQ_ATTACK_BACKSLASH;
                        break;
                    case 2:
                        nSequence = SEQ_ATTACK_JAB;
                        break;
                    default:
                        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                        // __LINE__: 9748
                        UTIL_ASSERT(FALSE);
                    }
                    break;
                }
            }
        } else {
            nSequence = SEQ_SHOOT;
        }

        if (curWeapon != NULL) {
            curWeapon->Release();
        }

        if (nSequence == SEQ_HEAD_TURN) {
            // NOTE: Uninline.
            nSequence = GetIdleSequence();
        }
        break;
    case SEQ_DAMAGE:
        m_nBloodFlashAmount = 128;
        m_nDamageLocatorTime = 128;
        m_bBloodFlashOn = TRUE;
        g_pBaldurChitin->GetObjectGame()->UpdatePortrait(g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id), 1);
        break;
    case SEQ_TWITCH:
        m_nTwitches = 0;
        break;
    case SEQ_WALK:
        nDirection = m_nDirection;
        break;
    }

    if (nSequence != SEQ_DIE || m_nSequence != SEQ_SLEEP) {
        // NOTE: Uninline.
        m_nSequence = m_animation.SetSequence(nSequence);
    }

    if (m_nNewDirection == m_nDirection) {
        m_nDirection = nDirection;
        m_nNewDirection = nDirection;
    } else {
        m_nDirection = nDirection;
    }
}

// 0x707980
void CGameSprite::SetTarget(const CPoint& target, BOOL collisionPath)
{
    m_pathSearchInvalidDest = FALSE;
    if (m_pPath != NULL) {
        delete m_pPath;
        m_pPath = NULL;
    }

    DropSearchRequest();

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && InControl()) {
        CMessage* message = new CMessageDropPath(m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE, CMessage::BROADCAST_OTHERS);
    }

    m_currentSearchRequest = new CSearchRequest();
    if (m_currentSearchRequest != NULL) {
        m_currentSearchRequest->m_searchBitmap = &(m_pArea->m_search);

        if (m_animation.GetListType() == LIST_FLIGHT) {
            memcpy(m_currentSearchRequest->m_terrainTable, m_flightTerrainTable, sizeof(m_currentSearchRequest->m_terrainTable));
        } else {
            memcpy(m_currentSearchRequest->m_terrainTable, m_terrainTable, sizeof(m_currentSearchRequest->m_terrainTable));
        }

        m_currentSearchRequest->m_collisionSearch = collisionPath;
        if (collisionPath) {
            m_currentSearchRequest->m_collisionDelay = rand() % 15;
        } else {
            m_currentSearchRequest->m_collisionDelay = 0;
        }
        m_currentSearchRequest->m_removeSelf = m_animation.GetListType() != LIST_FLIGHT;
        m_currentSearchRequest->m_pathSmooth = m_animation.GetPathSmooth();
        m_currentSearchRequest->m_sourceId = m_id;
        m_currentSearchRequest->m_nTargetPoints = 1;
        m_currentSearchRequest->m_targetPoints = new POINT[m_currentSearchRequest->m_nTargetPoints];
        if (m_currentSearchRequest->m_targetPoints) {
            m_currentSearchRequest->m_targetPoints[0] = target;
            if (m_currentSearchRequest->m_collisionDelay == 0) {
                CSingleLock lock(&(g_pBaldurChitin->GetObjectGame()->field_1B58), TRUE);
                g_pBaldurChitin->GetObjectGame()->m_searchRequests.AddTail(m_currentSearchRequest);
                g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty = FALSE;
                ReleaseSemaphore(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, 1, NULL);
                lock.Unlock();
            }

            // NOTE: Uninline.
            SetIdleSequence();
        } else {
            delete m_currentSearchRequest;
            m_currentSearchRequest = NULL;
        }
    }
}

// 0x707D40
void CGameSprite::SetTarget(CSearchRequest* pSearchRequest, BOOL collisionPath, BYTE frontList)
{
    m_pathSearchInvalidDest = FALSE;
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && InControl()) {
        CMessage* message = new CMessageDropPath(m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE, CMessage::BROADCAST_OTHERS);
    }

    if (frontList == CSearchRequest::LIST_FRONT) {
        if (m_pPath != NULL) {
            delete m_pPath;
            m_pPath = NULL;
        }
    }

    if (m_currentSearchRequest != pSearchRequest) {
        DropSearchRequest();
    }
    m_currentSearchRequest = pSearchRequest;

    m_currentSearchRequest->m_serviceState = CSearchRequest::STATE_WAITING;
    m_currentSearchRequest->m_collisionSearch = collisionPath;
    if (collisionPath) {
        m_currentSearchRequest->m_collisionDelay = rand() % 15;
    } else {
        m_currentSearchRequest->m_collisionDelay = 0;
    }
    m_currentSearchRequest->m_removeSelf = pSearchRequest->m_removeSelf;
    m_currentSearchRequest->m_frontList = frontList;

    if (!m_currentSearchRequest->m_collisionDelay) {
        CSingleLock lock(&(g_pBaldurChitin->GetObjectGame()->field_1B58), TRUE);
        if (frontList == CSearchRequest::LIST_FRONT) {
            g_pBaldurChitin->GetObjectGame()->m_searchRequests.AddTail(m_currentSearchRequest);
            g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty = FALSE;
        } else {
            g_pBaldurChitin->GetObjectGame()->m_searchRequestsBack.AddTail(m_currentSearchRequest);
        }
        ReleaseSemaphore(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, 1, NULL);
        lock.Unlock();
    }

    // NOTE: Uninline.
    SetIdleSequence();
}

// 0x707FB0
void CGameSprite::SetTargetFly(BYTE circleType, BYTE facing, LONG radius)
{
    m_pathSearchInvalidDest = FALSE;
    if (m_pPath != NULL) {
        delete m_pPath;
        m_pPath = NULL;
    }

    DropSearchRequest();

    m_radius = static_cast<SHORT>(radius);
    m_circleFacing = facing;
    m_fCurrCircleChange = 0.0;
    m_posOld = m_pos;
    m_turningAbout = FALSE;
    m_walkBackwards = FALSE;
    SetSequence(CGAMESPRITE_SEQ_WALK);

    if (circleType == FLY_0) {
        m_circleFacing = 0;
        m_fCircleChange = static_cast<double>(m_radius / m_animation.GetMoveScale());
    } else {
        m_fCircleChange = static_cast<double>(m_radius) * static_cast<double>(circleType) * 3.1415926535 / static_cast<double>(m_animation.GetMoveScale()) / 2.0;

        switch (abs(4 * ((m_nDirection + 2) / 4))) {
        case 0:
            m_posOld.x += m_radius * m_circleFacing;
            break;
        case 4:
            m_posOld.y += 3 * m_radius * m_circleFacing / 4;
            break;
        case 8:
            m_posOld.x -= m_radius * m_circleFacing;
            break;
        case 12:
            m_posOld.y -= 3 * m_radius * m_circleFacing / 4;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 10009
            UTIL_ASSERT(FALSE);
        }

        m_fDirectionOffset = static_cast<double>(8 - m_nDirection) * 3.1415926535 / 8.0;
        if (m_circleFacing == FLY_RIGHT) {
            m_fDirectionOffset += 3.1415926535;
        }
    }
}

// 0x708280
void CGameSprite::StartSpriteEffect(BYTE spriteEffect, BYTE intensityLevel, BYTE effectDuration, BOOLEAN a4)
{
    m_spriteEffectDuration = 0;
    if (m_pSpriteEffectArray != NULL) {
        delete m_pSpriteEffectArray;
        m_pSpriteEffectArray = NULL;
        delete m_pSpriteEffectArrayPosition;
        m_pSpriteEffectArrayPosition = NULL;
    }

    switch (spriteEffect) {
    case 0:
        field_5304 = 0;
        m_spriteEffectFlags = 0;

        if (m_animation.GetColorBlood() != 255) {
            m_spriteSplashPalette.SetRange(0,
                m_animation.GetColorBlood(),
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            m_spriteSplashVidCell.SetPalette(m_spriteSplashPalette);
            if (intensityLevel == CBlood::GUSH_LOW) {
                m_spriteSplashVidCell.SetResRef(CResRef("BLOODS"), FALSE, TRUE, TRUE);
            } else if (intensityLevel == CBlood::GUSH_MEDIUM) {
                m_spriteSplashVidCell.SetResRef(CResRef("BLOODM"), FALSE, TRUE, TRUE);
            } else if (intensityLevel == CBlood::GUSH_HIGH
                || intensityLevel == CBlood::EXPLODING_DEATH) {
                m_spriteSplashVidCell.SetResRef(CResRef("BLOODL"), FALSE, TRUE, TRUE);
            } else if (intensityLevel == CBlood::PULSATING_ARTERY) {
                m_spriteSplashVidCell.SetResRef(CResRef("BLOODCR"), FALSE, TRUE, TRUE);
            } else {
                m_spriteEffectDuration = 0;
                return;
            }

            m_spriteSplashVidCell.SequenceSet(0);
            m_spriteSplashVidCell.FrameSet(0);
            m_spriteEffectSequenceLength = 1;
            m_spriteEffectBaseIntensity = 0;
            m_spriteEffectRandomIntensity = 1;
        } else {
            m_spriteEffectDuration = 0;
            return;
        }
        break;
    case 1:
        if (a4 == TRUE) {
            AddEffect(IcewindMisc::CreateEffectVisualSpellHit(this, 0x3F, 10, 0),
                EFFECT_LIST_TIMED,
                TRUE,
                TRUE);
        }
        m_spriteEffectFlags = 0x200;
        m_spriteEffectVidCell.SetResRef(CResRef("FireL"), FALSE, TRUE, TRUE);
        m_spriteEffectVidCell.SequenceSet(0);
        m_spriteEffectSequenceNumber = 1;
        m_spriteEffectSequenceLength = m_spriteEffectVidCell.GetSequenceLength(m_spriteEffectVidCell.m_nCurrentSequence, FALSE);
        m_effectExtendDirection = 1;
        switch (intensityLevel) {
        case 0:
            m_spriteEffectBaseIntensity = -2;
            m_spriteEffectRandomIntensity = 4;
            break;
        case 1:
            m_spriteEffectBaseIntensity = -1;
            m_spriteEffectRandomIntensity = 3;
            break;
        case 2:
            m_spriteEffectBaseIntensity = 0;
            m_spriteEffectRandomIntensity = 2;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 10204
            UTIL_ASSERT(FALSE);
        }
        break;
    case 2:
        if (a4 == TRUE) {
            AddEffect(IcewindMisc::CreateEffectVisualSpellHit(this, 0x41, 10, 0),
                EFFECT_LIST_TIMED,
                TRUE,
                TRUE);
        }
        m_spriteEffectFlags = 0x200;
        m_spriteEffectVidCell.SetResRef(CResRef("ElectrL"), FALSE, TRUE, TRUE);
        m_spriteEffectVidCell.SequenceSet(0);
        m_spriteEffectSequenceNumber = static_cast<BYTE>(m_spriteEffectVidCell.GetNumberSequences(FALSE));
        m_spriteEffectSequenceLength = m_spriteEffectVidCell.GetSequenceLength(m_spriteEffectVidCell.m_nCurrentSequence, FALSE);
        m_effectExtendDirection = 0;
        switch (intensityLevel) {
        case 0:
            m_spriteEffectBaseIntensity = -2;
            m_spriteEffectRandomIntensity = 4;
            break;
        case 1:
            m_spriteEffectBaseIntensity = -1;
            m_spriteEffectRandomIntensity = 3;
            break;
        case 2:
            m_spriteEffectBaseIntensity = 0;
            m_spriteEffectRandomIntensity = 2;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 10259
            UTIL_ASSERT(FALSE);
        }
        break;
    case 3:
        if (a4 == TRUE) {
            AddEffect(IcewindMisc::CreateEffectVisualSpellHit(this, 0x40, 10, 0),
                EFFECT_LIST_TIMED,
                TRUE,
                TRUE);
        }
        m_spriteEffectFlags = 0x200;
        m_spriteEffectVidCell.SetResRef(CResRef("ColdL"), FALSE, TRUE, TRUE);
        m_spriteEffectVidCell.SequenceSet(0);
        m_spriteEffectSequenceNumber = 1;
        m_spriteEffectSequenceLength = m_spriteEffectVidCell.GetSequenceLength(m_spriteEffectVidCell.m_nCurrentSequence, FALSE);
        m_effectExtendDirection = 1;
        m_spriteEffectBaseIntensity = 0;
        m_spriteEffectBaseIntensity = 1;
        break;
    case 4:
        if (a4 == TRUE) {
            AddEffect(IcewindMisc::CreateEffectVisualSpellHit(this, 0x42, 10, 0),
                EFFECT_LIST_TIMED,
                TRUE,
                TRUE);
        }
        m_spriteEffectFlags = 0x200;
        m_spriteEffectVidCell.SetResRef(CResRef("None"), FALSE, TRUE, TRUE);
        m_spriteEffectVidCell.SequenceSet(0);
        m_spriteEffectSequenceNumber = static_cast<BYTE>(m_spriteEffectVidCell.GetNumberSequences(FALSE));
        m_spriteEffectSequenceLength = m_spriteEffectVidCell.GetSequenceLength(m_spriteEffectVidCell.m_nCurrentSequence, FALSE);
        m_effectExtendDirection = 0;
        // FIXME: `m_spriteEffectBaseIntensity` and `m_spriteEffectRandomIntensity` not initialized.
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 10324
        UTIL_ASSERT(FALSE);
    }

    int cnt = m_spriteEffectSequenceLength * (m_spriteEffectBaseIntensity + m_spriteEffectRandomIntensity - 1);
    if (m_spriteEffectSequenceLength * (m_spriteEffectBaseIntensity + m_spriteEffectRandomIntensity - 1) > 0) {
        m_pSpriteEffectArray = new USHORT[cnt];
        if (m_pSpriteEffectArray != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 10332
            UTIL_ASSERT(FALSE);
        }

        m_pSpriteEffectArrayPosition = new POINT[cnt];
        if (m_pSpriteEffectArrayPosition != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 10338
            UTIL_ASSERT(FALSE);
        }

        memset(m_pSpriteEffectArray, 0xFF, sizeof(USHORT) * cnt);
    }

    m_spriteEffectDuration = m_spriteEffectSequenceLength + effectDuration + 9;
    m_animation.CalculateFxRect(m_rSpriteEffectFX, m_ptSpriteEffectReference, m_posZ);
}

// 0x708D50
void CGameSprite::RenderSpriteCover(CVidMode* pVidMode, INT nSurface, CVidCell* pVidCell, const IcewindCVisualEffect& vfx)
{
    CRect rFX;
    CSize objectSize;
    CRect rGCBounds;
    CPoint newPos;
    CPoint ptReference;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 10436
    UTIL_ASSERT(pVidMode != NULL);

    DWORD dwRenderFlags = vfx.m_dwFlags;

    BOOLEAN bDithered = m_id == m_pArea->m_iPicked
        || g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bAlwaysDither
        || g_pBaldurChitin->GetObjectGame()->m_bForceDither;

    pVidCell->GetCurrentCenterPoint(ptReference, FALSE);
    pVidCell->GetCurrentFrameSize(objectSize, FALSE);

    rFX.SetRect(0, 0, objectSize.cx, objectSize.cy);

    newPos.x = m_pos.x;
    newPos.y = m_pArea->GetHeightOffset(m_pos, m_listType) + m_pos.y + 1;

    if (vfx.field_1 == TRUE || vfx.field_3 == TRUE) {
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK | 0x2;
    } else {
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL | 0x1;
    }

    m_pArea->GetInfinity()->FXPrep(rFX,
        dwRenderFlags,
        nSurface,
        newPos,
        ptReference);

    if (m_pArea->GetInfinity()->FXLock(rFX, dwRenderFlags)) {
        m_pArea->GetInfinity()->FXRender(pVidCell,
            ptReference.x,
            ptReference.y,
            vfx.m_dwFlags,
            vfx.m_nTransValue);

        rGCBounds.left = newPos.x - ptReference.x;
        rGCBounds.top = newPos.y + m_posZ - ptReference.y;
        rGCBounds.right = rGCBounds.left + rFX.Width();
        rGCBounds.bottom = rGCBounds.top + rFX.Height() - m_posZ;
        m_pArea->GetInfinity()->FXRenderClippingPolys(newPos.x,
            newPos.y - m_posZ,
            m_posZ,
            CPoint(ptReference.x, ptReference.y + m_posZ),
            rGCBounds,
            bDithered,
            FALSE);

        m_pArea->GetInfinity()->FXUnlock(dwRenderFlags, NULL, CPoint(0, 0));
        m_pArea->GetInfinity()->FXBltFrom(nSurface,
            rFX,
            newPos.x,
            newPos.y + m_posZ,
            ptReference.x,
            ptReference.y,
            vfx.m_dwFlags | 0x1);
    }
}

// 0x708FC0
void CGameSprite::RenderDamageArrow(CGameArea* pArea, CVidMode* pVidMode, INT nSurface)
{
    // TODO: Incomplete.
}

// 0x7093E0
void CGameSprite::RenderSpriteEffect(CVidMode* pVidMode, INT nSurface)
{
    // TODO: Incomplete.
}

// 0x709B60
void CGameSprite::UpdateSpriteEffect()
{
    SHORT nSequence;
    SHORT nNumberSequences;

    for (INT nIndex = 0; nIndex < 32; nIndex++) {
        if (!m_derivedStats.m_visualEffects[nIndex]) {
            if (nIndex == IWD_VFX_ENTANGLE
                || nIndex == IWD_VFX_WEB
                || nIndex == IWD_VFX_CLOAK_OF_FEAR) {
                field_7548[nIndex].SequenceSet(0);
                field_7548[nIndex].FrameSet(0);
            }

            if (nIndex == IWD_VFX_FIRE_SHIELD_RED
                || nIndex == IWD_VFX_FIRE_SHIELD_BLUE) {
                field_7548[nIndex].SequenceSet(0);
                field_7548[nIndex].FrameSet(0);
            }

            if (nIndex == IWD_VFX_28
                || nIndex == IWD_VFX_29) {
                field_7548[nIndex].SequenceSet(1);
                field_7548[nIndex].FrameSet(0);
            }
        }

        if (m_derivedStats.m_visualEffects[nIndex]
            && nIndex != IWD_VFX_INVISIBILITY
            && nIndex != IWD_VFX_BLUR) {
            switch (nIndex) {
            case IWD_VFX_SHROUD_OF_FLAME:
                if (field_7548[nIndex].IsEndOfSequence(FALSE)) {
                    m_sndSpriteEffect.Stop();
                    m_sndSpriteEffect.SetResRef(CResRef("MISC_01C"), TRUE, TRUE);
                    m_sndSpriteEffect.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                    m_sndSpriteEffect.Play(m_pos.x, m_pos.y, 0, FALSE);

                    nNumberSequences = field_7548[nIndex].GetNumberSequences(FALSE);
                    if (nNumberSequences != 0) {
                        field_7548[nIndex].SequenceSet(rand() % nNumberSequences);
                    } else {
                        field_7548[nIndex].SequenceSet(0);
                    }
                } else {
                    field_7548[nIndex].FrameAdvance();
                }
                break;
            case IWD_VFX_FIRE_SHIELD_RED:
            case IWD_VFX_FIRE_SHIELD_BLUE:
                if (field_7548[nIndex].IsEndOfSequence(FALSE)) {
                    field_7548[nIndex].SequenceSet(2);
                } else {
                    field_7548[nIndex].FrameAdvance();
                }
                break;
            case IWD_VFX_28:
            case IWD_VFX_29:
                if (field_7548[nIndex].IsEndOfSequence(FALSE)) {
                    field_7548[nIndex].SequenceSet(3);
                } else {
                    field_7548[nIndex].FrameAdvance();
                }
                break;
            case IWD_VFX_ENTANGLE:
            case IWD_VFX_WEB:
            case IWD_VFX_CLOAK_OF_FEAR:
                if (field_7548[nIndex].IsEndOfSequence(FALSE)) {
                    nSequence = field_7548[nIndex].GetCurrentSequenceId() + 1;
                    nNumberSequences = field_7548[nIndex].GetNumberSequences(FALSE);
                    if (nSequence >= nNumberSequences) {
                        nSequence--;
                    }
                    field_7548[nIndex].SequenceSet(nSequence);
                } else {
                    field_7548[nIndex].FrameAdvance();
                }
                break;
            case IWD_VFX_SEVEN_EYES:
                nSequence = 0;
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_THE_MIND]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_THE_SWORD]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_THE_MAGE]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_VENOM]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_THE_SPIRIT]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_FORTITUDE]) {
                    nSequence++;
                }
                if (!m_derivedStats.m_spellStates[SPLSTATE_EYE_OF_STONE]) {
                    nSequence++;
                }
                if (!field_9088[IWD_VFX_SEVEN_EYES].IsSoundPlaying()) {
                    if (nSequence == 7) {
                        field_9088[IWD_VFX_SEVEN_EYES].Stop();
                    } else {
                        if (nSequence >= 5) {
                            field_9088[IWD_VFX_SEVEN_EYES].SetResRef(CResRef("AFT_M17"), TRUE, TRUE);
                        } else if (nSequence >= 2) {
                            field_9088[IWD_VFX_SEVEN_EYES].SetResRef(CResRef("AFT_M16"), TRUE, TRUE);
                        } else {
                            field_9088[IWD_VFX_SEVEN_EYES].SetResRef(CResRef("AFT_M15"), TRUE, TRUE);
                        }
                        field_9088[IWD_VFX_SEVEN_EYES].SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                        field_9088[IWD_VFX_SEVEN_EYES].Play(m_pos.x, m_pos.y, 0, FALSE);
                    }
                }
                field_7548[IWD_VFX_SEVEN_EYES].SequenceSet(nSequence);
                field_7548[IWD_VFX_SEVEN_EYES_2].SequenceSet(nSequence);
                if (field_7548[IWD_VFX_SEVEN_EYES].IsEndOfSequence(FALSE)) {
                    field_7548[IWD_VFX_SEVEN_EYES].FrameSet(0);
                    field_7548[IWD_VFX_SEVEN_EYES_2].FrameSet(0);
                } else {
                    field_7548[IWD_VFX_SEVEN_EYES].FrameAdvance();
                    field_7548[IWD_VFX_SEVEN_EYES_2].FrameAdvance();
                }
                break;
            case IWD_VFX_SEVEN_EYES_2:
                break;
            default:
                if (!field_9088[nIndex].IsSoundPlaying()) {
                    field_9088[nIndex].SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                    field_9088[nIndex].Play(m_pos.x, m_pos.y, 0, FALSE);
                }
                if (field_7548[nIndex].IsEndOfSequence(FALSE)) {
                    nNumberSequences = field_7548[nIndex].GetNumberSequences(FALSE);
                    if (nNumberSequences != 0) {
                        field_7548[nIndex].SequenceSet(rand() % nNumberSequences);
                    } else {
                        field_7548[nIndex].SequenceSet(0);
                    }
                } else {
                    field_7548[nIndex].FrameAdvance();
                }
            }
        }
    }

    if (m_spriteEffectDuration != 0) {
        if (m_spriteSplashVidCell.IsEndOfSequence(FALSE)) {
            if (m_pSpriteEffectArray != NULL) {
                CRect rFx;
                CPoint ptReference;
                m_animation.CalculateFxRect(rFx, ptReference, m_posZ);

                for (BYTE nIndex = 0; nIndex < m_spriteEffectSequenceLength; nIndex++) {
                    if ((g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime / 2) % m_spriteEffectSequenceLength == nIndex) {
                        BYTE intensity = m_spriteEffectBaseIntensity + m_spriteEffectRandomIntensity - 1;
                        memset(&(m_pSpriteEffectArray[intensity]),
                            -1,
                            sizeof(USHORT) * (intensity));
                        // TODO: Incomplete.
                    } else {
                        BYTE intensity = m_spriteEffectBaseIntensity + m_spriteEffectRandomIntensity - 1;

                        // TODO: Incomplete.
                    }
                }
            }
        } else {
            m_spriteSplashVidCell.FrameAdvance();
        }
        m_spriteEffectDuration--;
    } else {
        if (m_pSpriteEffectArray != NULL) {
            delete m_pSpriteEffectArray;
            m_pSpriteEffectArray = NULL;
            delete m_pSpriteEffectArrayPosition;
            m_pSpriteEffectArrayPosition = NULL;
        }
    }
}

// 0x70AE20
void CGameSprite::ClearMarshal(BOOL unequip)
{
    UINT nClass;
    UINT nLevel;
    POSITION pos;
    CGameEffect* nodeEffect;

    for (nClass = 0; nClass < CSPELLLIST_NUM_CLASSES; nClass++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            m_spells.m_spellsByClass[nClass].m_lists[nLevel].m_List.clear();
        }
        m_spells.m_spellsByClass[nClass].m_nHighestLevel = 0;
    }

    for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        if (m_domainSpells.m_lists[nLevel].m_List.size() > 0) {
            m_domainSpells.m_lists[nLevel].m_List.clear();
            m_domainSpells.m_lists[nLevel].field_14 = 0;
            m_domainSpells.m_lists[nLevel].field_18 = 0;
        }
    }
    m_domainSpells.m_nHighestLevel = 0;

    if (m_innateSpells.m_List.size() > 0) {
        m_innateSpells.m_List.clear();
        m_innateSpells.field_14 = 0;
        m_innateSpells.field_18 = 0;
    }

    if (m_songs.m_List.size() > 0) {
        m_songs.m_List.clear();
        m_songs.field_14 = 0;
        m_songs.field_18 = 0;
    }

    if (m_shapeshifts.m_List.size() > 0) {
        m_shapeshifts.m_List.clear();
        m_shapeshifts.field_14 = 0;
        m_shapeshifts.field_18 = 0;
    }

    // NOTE: Uninline.
    m_equipment.SetSpritePointer(this);

    m_equipment.ClearMarshal(unequip);

    memset(&m_baseStats, 0, sizeof(m_baseStats));

    pos = m_timedEffectList.GetHeadPosition();
    while (pos != NULL) {
        nodeEffect = m_timedEffectList.GetNext(pos);
        delete nodeEffect;
    }

    pos = m_equipedEffectList.GetHeadPosition();
    while (pos != NULL) {
        nodeEffect = m_equipedEffectList.GetNext(pos);
        delete nodeEffect;
    }

    if (m_pDialogData != NULL) {
        delete m_pDialogData;
        m_pDialogData = NULL;
        m_nDialogData = 0;
    }
}

// 0x70AFD0
void CGameSprite::Marshal(CAreaFileCreature** pCreature)
{
    BOOL areaMove = FALSE;

    if (m_pArea == NULL) {
        m_pArea = g_pBaldurChitin->GetObjectGame()->m_pGameAreaMaster;
        m_pos.x = 0;
        m_pos.y = 0;
        areaMove = TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 11809
    UTIL_ASSERT(pCreature != NULL);

    m_baseStats.m_flags &= ~0x80000000;

    *pCreature = new CAreaFileCreature();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 11817
    UTIL_ASSERT(*pCreature != NULL);

    // FIXME: Redundant, memset is a part of constructor.
    memset(*pCreature, 0, sizeof(CAreaFileCreature));

    if (m_pos.x < -100) {
        m_pos.x = -100;
        m_fCircleChange = 0.0;
        m_fCurrCircleChange = 1.0;
    } else if (m_pos.x > m_pArea->GetInfinity()->nAreaX + 100) {
        m_pos.x = m_pArea->GetInfinity()->nAreaX + 100;
        m_fCircleChange = 0.0;
        m_fCurrCircleChange = 1.0;
    }

    if (m_pos.y < -100) {
        m_pos.y = -100;
        m_fCircleChange = 0.0;
        m_fCurrCircleChange = 1.0;
    } else if (m_pos.y > m_pArea->GetInfinity()->nAreaY + 100) {
        m_pos.y = m_pArea->GetInfinity()->nAreaY + 100;
        m_fCircleChange = 0.0;
        m_fCurrCircleChange = 1.0;
    }

    (*pCreature)->m_posX = static_cast<WORD>(m_pos.x);
    (*pCreature)->m_posY = static_cast<WORD>(m_pos.y);
    (*pCreature)->m_startingPosX = static_cast<WORD>(m_posStart.x);
    (*pCreature)->m_startingPosY = static_cast<WORD>(m_posStart.y);
    (*pCreature)->m_type = m_type;
    (*pCreature)->m_expirationTime = m_expirationTime != -1
        ? m_expirationTime / CTimerWorld::TIMESCALE_MSEC_PER_SEC
        : -1;
    (*pCreature)->m_huntingRange = m_huntingRange;
    (*pCreature)->m_followRange = m_followRange;
    (*pCreature)->m_timeOfDayVisible = m_timeOfDayVisible;

    BYTE* creatureData;
    LONG creatureSize;
    Marshal(&creatureData, &creatureSize, &((*pCreature)->m_facing), TRUE, TRUE);

    // FIXME: Unsafe x64 conversion.
    (*pCreature)->m_creatureOffset = reinterpret_cast<DWORD>(creatureData);
    (*pCreature)->m_creatureSize = creatureSize;

    (*pCreature)->m_numberTimesTalkedTo = m_nNumberOfTimesTalkedTo;

    strncpy((*pCreature)->m_scriptName, m_scriptName, SCRIPTNAME_SIZE);

    if (m_overrideScript != NULL) {
        // NOTE: Uninline.
        m_overrideScript->m_cResRef.GetResRef((*pCreature)->m_overrideScriptOverride);
    }

    if (m_special3Script != NULL) {
        // NOTE: Uninline.
        m_special3Script->m_cResRef.GetResRef((*pCreature)->m_special3ScriptOverride);
    }

    if (m_special2Script != NULL) {
        // NOTE: Uninline.
        m_special2Script->m_cResRef.GetResRef((*pCreature)->m_special2ScriptOverride);
    }

    if (m_combatScript != NULL) {
        // NOTE: Uninline.
        m_combatScript->m_cResRef.GetResRef((*pCreature)->m_combatScriptOverride);
    }

    if (m_movementScript != NULL) {
        // NOTE: Uninline.
        m_movementScript->m_cResRef.GetResRef((*pCreature)->m_movementScriptOverride);
    }

    if (m_teamScript != NULL) {
        // NOTE: Uninline.
        m_teamScript->m_cResRef.GetResRef((*pCreature)->m_teamScriptOverride);
    }

    if (m_special1Script != NULL) {
        // NOTE: Uninline.
        m_special1Script->m_cResRef.GetResRef((*pCreature)->m_special1ScriptOverride);
    }

    if (areaMove) {
        m_pArea = NULL;
    }
}

// 0x70B2F0
void CGameSprite::Marshal(BYTE** pCreature, LONG* creatureSize, WORD* facing, BOOLEAN a4, BOOLEAN a5)
{
    UTIL_ASSERT(pCreature != NULL && creatureSize != NULL && facing != NULL);

    // TODO: Incomplete.
}

// 0x70BEE0
void CGameSprite::Marshal(CSavedGamePartyCreature& partyCreature, BOOLEAN bNetworkMessage)
{
    DWORD nIndex;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 12226
    UTIL_ASSERT(m_bGlobal);

    partyCreature.m_wFlags = 0;

    if (m_bSelected) {
        partyCreature.m_wFlags |= 0x1;
    }

    if (bNetworkMessage == TRUE) {
        partyCreature.m_wFlags |= 0x8000;
    }

    partyCreature.m_portraitId = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id);

    memset(partyCreature.m_creatureResRef, 0, RESREF_SIZE);

    BYTE* pCreature;
    LONG nCreatureSize;
    WORD facing;
    Marshal(&pCreature, &nCreatureSize, &facing, TRUE, TRUE);

    // FIXME: Unsafe x64 conversion.
    partyCreature.m_creatureOffset = reinterpret_cast<DWORD>(pCreature);
    partyCreature.m_creatureSize = nCreatureSize;
    partyCreature.m_creatureFacing = facing;

    BOOLEAN v1 = FALSE;
    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        if (g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(nCharacterSlot) == m_id) {
            v1 = TRUE;
            break;
        }
    }

    if (m_pArea != NULL) {
        m_pArea->m_resRef.GetResRef(partyCreature.m_areaName);

        INT x;
        INT y;
        m_pArea->GetInfinity()->GetViewPosition(x, y);
        partyCreature.m_posViewX = static_cast<WORD>(x);
        partyCreature.m_posViewY = static_cast<WORD>(y);
    } else {
        if (v1 == TRUE) {
            CResRef sBlankResRef;
            sBlankResRef = "NO_AREA";

            partyCreature.m_wFlags |= 0x8000;
            sBlankResRef.GetResRef(partyCreature.m_areaName);
        } else {
            m_currentArea.GetResRef(partyCreature.m_areaName);
        }

        partyCreature.m_posViewX = 0;
        partyCreature.m_posViewY = 0;
    }

    partyCreature.m_posX = static_cast<WORD>(m_pos.x);
    partyCreature.m_posY = static_cast<WORD>(m_pos.y);
    partyCreature.m_nModalState = m_nModalState;

    for (nIndex = 0; nIndex < 5; nIndex++) {
        partyCreature.field_28A[nIndex] = field_4C54[nIndex];
    }

    partyCreature.m_nWeaponSet = m_nWeaponSet;

    for (nIndex = 0; nIndex < 8; nIndex++) {
        partyCreature.m_quickWeaponsItemNum[nIndex] = m_quickWeapons[nIndex].m_abilityId.m_itemNum;
        partyCreature.m_quickWeaponsAbilityNum[nIndex] = m_quickWeapons[nIndex].m_abilityId.m_abilityNum;
        partyCreature.field_2A7[nIndex] = field_3D3A[nIndex];
    }

    for (nIndex = 0; nIndex < 9; nIndex++) {
        m_quickSpells[nIndex].m_abilityId.m_res.GetResRef(partyCreature.m_quickSpellsSpellId[nIndex]);
        partyCreature.m_quickSpellsClass[nIndex] = m_quickSpells[nIndex].m_abilityId.m_nClass;
        partyCreature.field_280[nIndex] = m_quickSpells[nIndex].m_abilityId.field_1D;
        partyCreature.field_29E[nIndex] = static_cast<unsigned char>(m_quickSpells[nIndex].m_abilityId.field_1E);
    }

    for (nIndex = 0; nIndex < 3; nIndex++) {
        partyCreature.m_quickItemsItemNum[nIndex] = m_quickItems[nIndex].m_abilityId.m_itemNum;
        partyCreature.m_quickItemsAbilityNum[nIndex] = m_quickItems[nIndex].m_abilityId.m_abilityNum;
    }

    for (nIndex = 0; nIndex < 9; nIndex++) {
        m_quickInnates[nIndex].m_abilityId.m_res.GetResRef(partyCreature.m_quickInnatesSpellId[nIndex]);
    }

    for (nIndex = 0; nIndex < 9; nIndex++) {
        m_quickSongs[nIndex].m_abilityId.m_res.GetResRef(partyCreature.m_quickSongsSpellId[nIndex]);
    }

    for (nIndex = 0; nIndex < 9; nIndex++) {
        partyCreature.field_19A[nIndex] = field_3D14[nIndex];
    }

    partyCreature.m_nLastSpellbookClassIndex = m_nLastSpellbookClassIndex;
    partyCreature.m_nLastSpellbookSpellLevel = m_nLastSpellbookSpellLevel;
    partyCreature.m_nLastSong = m_nLastSong;
    partyCreature.m_strStrongestKillName = m_cGameStats.m_strStrongestKillName;
    partyCreature.m_nStrongestKillXPValue = m_cGameStats.m_nStrongestKillXPValue;
    partyCreature.m_nPreviousTimeWithParty = m_cGameStats.m_nPreviousTimeWithParty;
    partyCreature.m_nJoinPartyTime = m_cGameStats.m_nJoinPartyTime;
    partyCreature.m_bWithParty = m_cGameStats.m_bWithParty;
    partyCreature.m_nChapterKillsXPValue = m_cGameStats.m_nChapterKillsXPValue;
    partyCreature.m_nChapterKillsNumber = m_cGameStats.m_nChapterKillsNumber;
    partyCreature.m_nGameKillsXPValue = m_cGameStats.m_nGameKillsXPValue;
    partyCreature.m_nGameKillsNumber = m_cGameStats.m_nGameKillsNumber;

    for (nIndex = 0; nIndex < 4; nIndex++) {
        m_cGameStats.m_pSpellStats[nIndex].m_cResRef.GetResRef(partyCreature.m_lSpellStatsName[nIndex]);
        partyCreature.m_lSpellStatsCount[nIndex] = m_cGameStats.m_pSpellStats[nIndex].m_nTimesUsed;
    }

    for (nIndex = 0; nIndex < 4; nIndex++) {
        m_cGameStats.m_pWeaponStats[nIndex].m_cResRef.GetResRef(partyCreature.m_lWeaponStatsName[nIndex]);
        partyCreature.m_lWeaponStatsCount[nIndex] = m_cGameStats.m_pWeaponStats[nIndex].m_nTimesUsed;
    }

    partyCreature.m_nHappiness = m_nHappiness;

    for (nIndex = 0; nIndex < 24; nIndex++) {
        partyCreature.m_nNumberOfTimesInteractedWith[nIndex] = m_nNumberOfTimesInteractedWith[nIndex];
    }

    if (m_baseStats.m_name == -1) {
        strncpy(partyCreature.m_name, (LPCSTR)m_sName, SCRIPTNAME_SIZE);
    } else {
        partyCreature.m_name[0] = '\0';
    }

    partyCreature.m_nNumberOfTimesTalkedTo = m_nNumberOfTimesTalkedTo;
    m_secondarySounds.GetResRef(partyCreature.m_secondarySounds);
    memcpy(partyCreature.field_25E, field_725A, 32);
}

// 0x70C3F0
void CGameSprite::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    CResRef spriteResRef;
    CString sSpriteString;
    BYTE nSpriteStringLength;
    CResRef areaResRef;
    CString sAreaString;
    BYTE nAreaStringLength;
    CPoint pos;
    BYTE enemyAlly;
    DWORD cnt;

    spriteResRef = m_resRef;
    spriteResRef.CopyToString(sSpriteString);
    nSpriteStringLength = static_cast<BYTE>(sSpriteString.GetLength());

    areaResRef = m_pArea->m_resRef;
    areaResRef.CopyToString(sAreaString);
    nAreaStringLength = static_cast<BYTE>(sAreaString.GetLength());

    pos = GetPos();
    enemyAlly = m_startTypeAI.GetEnemyAlly();

    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 12428
    UTIL_ASSERT(nAreaStringLength != 0);

    *dwSize = sizeof(BYTE)
        + nSpriteStringLength
        + sizeof(BYTE)
        + nAreaStringLength
        + sizeof(LONG)
        + sizeof(LONG)
        + sizeof(BYTE);

    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 12440
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE_CGAMESPRITE);

    cnt = 0;

    *reinterpret_cast<BYTE*>(*pData + cnt) = nSpriteStringLength;
    cnt += sizeof(BYTE);

    memcpy(*pData + cnt, sSpriteString.GetBuffer(nSpriteStringLength), nSpriteStringLength);
    cnt += nSpriteStringLength;

    *reinterpret_cast<BYTE*>(*pData + cnt) = nAreaStringLength;
    cnt += sizeof(BYTE);

    memcpy(*pData + cnt, sSpriteString.GetBuffer(nAreaStringLength), nAreaStringLength);
    cnt += nAreaStringLength;

    *reinterpret_cast<LONG*>(*pData + cnt) = pos.x;
    cnt += sizeof(LONG);

    *reinterpret_cast<LONG*>(*pData + cnt) = pos.y;
    cnt += sizeof(LONG);

    *reinterpret_cast<BYTE*>(*pData + cnt) = enemyAlly;
    cnt += sizeof(BYTE);

    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 12481
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x70C600
void CGameSprite::Unmarshal(CSavedGamePartyCreature* pCreature, BOOLEAN bPartyMember, BOOLEAN bProgressBarInPlace)
{
    DWORD nIndex;

    m_bInUnmarshal = TRUE;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    m_bGlobal = TRUE;
    m_currentArea = pCreature->m_areaName;

    // NOTE: Uninline.
    SetFacing(static_cast<SHORT>(pCreature->m_creatureFacing));

    m_nModalState = static_cast<BYTE>(pCreature->m_nModalState);

    for (nIndex = 0; nIndex < 5; nIndex++) {
        field_4C54[nIndex] = pCreature->field_28A[nIndex];
    }

    sub_726570();

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_QUICK_WEAPONS22; nIndex++) {
        InitQuickItemData(pCreature->m_quickWeaponsItemNum[nIndex],
            pCreature->m_quickWeaponsAbilityNum[nIndex],
            pCreature->field_2A7[nIndex],
            m_quickWeapons[nIndex]);

        // NOTE: Uninline.
        SetQuickWeapon(static_cast<BYTE>(nIndex), pCreature->field_2A7[nIndex]);
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_QUICK_SPELLS22; nIndex++) {
        if (pCreature->m_quickSpellsClass[nIndex] != 0) {
            InitQuickSpellData(CResRef(pCreature->m_quickSpellsSpellId[nIndex]),
                1,
                m_quickSpells[nIndex],
                pCreature->m_quickSpellsClass[nIndex],
                pCreature->field_280[nIndex],
                pCreature->field_29E[nIndex]);
        }
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_QUICK_ITEMS22; nIndex++) {
        InitQuickItemData(pCreature->m_quickItemsItemNum[nIndex],
            pCreature->m_quickItemsAbilityNum[nIndex],
            0,
            m_quickItems[nIndex]);
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_QUICK_ABILITIES22; nIndex++) {
        InitQuickSpellData(CResRef(pCreature->m_quickInnatesSpellId[nIndex]),
            2,
            m_quickInnates[nIndex],
            0,
            0,
            0);
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_QUICK_SONGS22; nIndex++) {
        InitQuickSpellData(CResRef(pCreature->m_quickSongsSpellId[nIndex]),
            3,
            m_quickSongs[nIndex],
            0,
            0,
            0);
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_CUSTOM_BUTTONS22; nIndex++) {
        field_3D14[nIndex] = pCreature->field_19A[nIndex];
    }

    m_nLastSpellbookClassIndex = pCreature->m_nLastSpellbookClassIndex;
    m_nLastSpellbookSpellLevel = pCreature->m_nLastSpellbookSpellLevel;
    m_nLastSong = pCreature->m_nLastSong;

    m_nNumberOfTimesTalkedTo = pCreature->m_nNumberOfTimesTalkedTo;
    m_nHappiness = pCreature->m_nHappiness;

    for (nIndex = 0; nIndex < 24; nIndex++) {
        m_nNumberOfTimesInteractedWith[nIndex] = pCreature->m_nNumberOfTimesInteractedWith[nIndex];
    }

    if (pCreature->m_strStrongestKillName == 0) {
        pCreature->m_strStrongestKillName = -1;
    }

    m_cGameStats.m_strStrongestKillName = pCreature->m_strStrongestKillName;
    m_cGameStats.m_nStrongestKillXPValue = pCreature->m_nStrongestKillXPValue;
    m_cGameStats.m_nPreviousTimeWithParty = pCreature->m_nPreviousTimeWithParty;
    m_cGameStats.m_nJoinPartyTime = pCreature->m_nJoinPartyTime;
    m_cGameStats.m_bWithParty = pCreature->m_bWithParty;
    m_cGameStats.m_nChapterKillsXPValue = pCreature->m_nChapterKillsXPValue;
    m_cGameStats.m_nChapterKillsNumber = pCreature->m_nChapterKillsNumber;
    m_cGameStats.m_nGameKillsXPValue = pCreature->m_nGameKillsXPValue;
    m_cGameStats.m_nGameKillsNumber = pCreature->m_nGameKillsNumber;

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_STATS_SPELLS; nIndex++) {
        m_cGameStats.SetSpellStats(static_cast<BYTE>(nIndex),
            pCreature->m_lSpellStatsName[nIndex],
            pCreature->m_lSpellStatsCount[nIndex]);
    }

    for (nIndex = 0; nIndex < CGAMESAVECHARACTER_NUM_STATS_WEAPONS; nIndex++) {
        m_cGameStats.SetWeaponStats(static_cast<BYTE>(nIndex),
            pCreature->m_lWeaponStatsName[nIndex],
            pCreature->m_lWeaponStatsCount[nIndex]);
    }

    m_secondarySounds = pCreature->m_secondarySounds;
    memcpy(field_725A, pCreature->field_25E, sizeof(field_725A));

    CString sPath = g_pBaldurChitin->GetObjectGame()->GetDirSounds() + field_725A + '\\';
    g_pBaldurChitin->cDimm.AddToDirectoryList(sPath, TRUE);

    if (bPartyMember) {
        CString areaName;
        m_currentArea.CopyToString(areaName);

        CGameArea* pArea;
        if ((pCreature->m_wFlags & 0x8000) == 0) {
            pArea = pGame->LoadArea(areaName,
                255,
                FALSE,
                bProgressBarInPlace);
            if (pArea == NULL) {
                return;
            }

            pArea->GetInfinity()->SetViewPosition(pCreature->m_posViewX,
                pCreature->m_posViewY,
                TRUE);
        } else {
            if (bProgressBarInPlace) {
                g_pChitin->cProgressBar.AddActionTarget(-static_cast<LONG>(CInfGame::PROGRESSBAR_CACHING_ADDITIONAL));
            }
        }

        if (pGame->m_bInLoadGame == TRUE) {
            pGame->AddCharacterToParty(m_id, pCreature->m_portraitId);
        }

        CPoint pos;
        pos.x = pCreature->m_posX != -1 ? pCreature->m_posX : -1;
        pos.y = pCreature->m_posY != -1 ? pCreature->m_posY : -1;

        if ((pCreature->m_wFlags & 0x8000) == 0) {
            if ((m_baseStats.m_generalState & STATE_DEAD) != 0
                && GetAnimation()->CanLieDown()) {
                AddToArea(pArea, pos, 0, LIST_BACK);
            } else {
                AddToArea(pArea, pos, 0, LIST_FRONT);
            }

            if ((pCreature->m_wFlags & 0x1) != 0) {
                pGame->SelectCharacter(m_id, FALSE);
            }
        }

        if (m_baseStats.m_name == -1) {
            m_sName = pCreature->m_name;
        }

        if (m_baseStats.m_resistMagicBase < 0) {
            m_baseStats.m_resistMagicBase = 0;
        } else if (m_baseStats.m_resistMagicBase > 50) {
            m_baseStats.m_resistMagicBase = 50;
        }

        sub_71E760(m_derivedStats, TRUE);

        for (UINT nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
            for (UINT nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
                BYTE nClass = g_pBaldurChitin->GetObjectGame()->GetSpellcasterClass(nClassIndex);

                INT nBonus;
                INT nMaxSpells = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetMaxKnownSpells(nClass,
                    m_startTypeAI,
                    m_derivedStats,
                    m_baseStats.m_specialization,
                    nLevel + 1,
                    nBonus);

                // __FILE__: .\Include\ObjCreature.h
                // __LINE__: 1751
                UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

                m_spells.m_spellsByClass[nClassIndex].m_lists[nLevel].field_14 = nMaxSpells + nBonus;
            }
        }
    } else {
        m_pos.x = pCreature->m_posX;
        m_pos.y = pCreature->m_posY;
        if (m_baseStats.m_name == -1) {
            m_sName = pCreature->m_name;
        }
    }

    sub_726810(pCreature->m_nWeaponSet);

    INT nDruidLevel = m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_DRUID);
    if (nDruidLevel > 0) {
        INT nMaxShapeshifts = pGame->GetRuleTables().GetMaxDruidShapeshifts(m_baseStats, nDruidLevel) - m_shapeshifts.field_14;
        if (nMaxShapeshifts) {
            sub_724C40(nMaxShapeshifts);
            m_shapeshifts.sub_725D30(nMaxShapeshifts, FALSE);
        }
    }

    m_bInUnmarshal = FALSE;
}

// 0x70CF90
void CGameSprite::Unmarshal(BYTE* pCreature, LONG creatureSize, WORD facing, int a4)
{
    CCreatureFileOffsets* offsets;

    m_bInUnmarshal = TRUE;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 12738
    UTIL_ASSERT(pCreature != NULL);

    BOOL bNeedUpgrade = FALSE;
    BOOL bAlloced = FALSE;
    if (memcmp(pCreature, "CRE V2.2", 8) != 0) {
        bNeedUpgrade = TRUE;
    }

    if (bNeedUpgrade) {
        // TODO: Incomplete.
    }

    ClearMarshal(TRUE);
    creatureSize -= 900;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 12812
    UTIL_ASSERT(creatureSize > 0);

    memcpy(&m_baseStats, pCreature + 8, sizeof(m_baseStats));

    if (m_baseStats.m_scriptTeam[0] == 0xFF) {
        memcpy(m_baseStats.m_scriptTeam, "None", strlen("None") + 1);
    }

    if (m_baseStats.m_scriptSpecial1[0] == 0xFF) {
        memcpy(m_baseStats.m_scriptSpecial1, "None", strlen("None") + 1);
    }

    STR_RES nameRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_name, nameRes);

    for (BYTE nRange = 0; nRange < 7; nRange++) {
        if (m_baseStats.m_colors[nRange] == 0xFF) {
            m_baseStats.m_colors[nRange] = 0;
        }
    }

    // NOTE: Uninline.
    GetAnimation()->SetAnimationType(m_baseStats.m_animationType, m_baseStats.m_colors, facing);

    if (GetAnimation()->GetListType() == LIST_FLIGHT) {
        // NOTE: Uninline.
        SetFacing(4 * ((facing + 2) / 4));
    }

    m_vbPortraitSmall.SetResRef(CResRef(m_baseStats.m_portraitSmall), TRUE, TRUE);
    m_vbPortraitSmall.m_bDoubleSize = FALSE;

    offsets = reinterpret_cast<CCreatureFileOffsets*>(pCreature + 900);
    creatureSize -= sizeof(CCreatureFileOffsets);

    if (m_baseStats.m_subrace == -1) {
        m_baseStats.m_subrace = 0;
    }

    if (offsets->m_class == 0 || offsets->m_class == -1) {
        offsets->m_class = CAIOBJECTTYPE_C_FIGHTER;
        offsets->m_avClass = CAIOBJECTTYPE_C_FIGHTER;
        offsets->m_classMask = CLASSMASK_FIGHTER;
    }

    m_derivedStats.m_classMask = 0;
    for (INT iClassType = 1; iClassType <= 11; iClassType++) {
        INT nLevel = GetClassLevel(iClassType);
        if (nLevel > 0) {
            m_derivedStats.SetClassLevel(iClassType, nLevel);
        }
    }

    SetAIType(CAIObjectType(offsets->m_enemyAlly,
                  offsets->m_general,
                  offsets->m_race,
                  m_baseStats.m_subrace,
                  offsets->m_class,
                  offsets->m_specifics,
                  offsets->m_gender,
                  offsets->m_alignment,
                  m_id,
                  offsets->m_specialCase,
                  CString(offsets->m_name),
                  offsets->m_avClass,
                  offsets->m_classMask),
        TRUE, TRUE);

    if ((m_baseStats.m_generalState & STATE_DEAD) != 0) {
        m_startTypeAI.m_nGeneral = CAIObjectType::G_DEAD;
        m_typeAI.m_nGeneral = CAIObjectType::G_DEAD;
    }

    strncpy(m_scriptName, offsets->m_name, SCRIPTNAME_SIZE);

    if (m_baseStats.m_attackBase == 0) {
        int v1;
        int v2;
        int v3;
        g_pBaldurChitin->GetObjectGame()->GetRuleTables().sub_546B60(this,
            v1,
            v2,
            v3,
            FALSE);
        m_baseStats.m_attackBase = v1;
    }

    if (m_baseStats.m_numberOfAttacksBase == 0) {
        int v1;
        int v2;
        int v3;
        g_pBaldurChitin->GetObjectGame()->GetRuleTables().sub_546B60(this,
            v1,
            v2,
            v3,
            FALSE);
        m_baseStats.m_numberOfAttacksBase = v2;
    }

    m_typeAI.m_nSubRace = m_baseStats.m_subrace;
    m_startTypeAI.m_nSubRace = m_baseStats.m_subrace;
    m_liveTypeAI.m_nSubRace = m_baseStats.m_subrace;

    if (m_baseStats.m_effectVersion == 0) {
        m_timedEffectList.Unmarshal(pCreature + offsets->m_effectListOffset,
            sizeof(ITEM_EFFECT) * offsets->m_effectListCount,
            this,
            0);
        creatureSize -= sizeof(ITEM_EFFECT) * offsets->m_effectListCount;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 12914
        UTIL_ASSERT(creatureSize > 0);
    } else {
        m_timedEffectList.Unmarshal(pCreature + offsets->m_effectListOffset,
            sizeof(CGameEffectBase) * offsets->m_effectListCount,
            this,
            1);
        creatureSize -= sizeof(CGameEffectBase) * offsets->m_effectListCount;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 12920
        UTIL_ASSERT(creatureSize > 0);
    }

    m_equipment.Unmarshal(reinterpret_cast<CCreatureFileEquipment*>(pCreature + offsets->m_equipmentListOffset),
        reinterpret_cast<CCreatureFileItem*>(pCreature + offsets->m_itemListOffset),
        offsets->m_itemListCount,
        this);
    creatureSize -= sizeof(CCreatureFileEquipment) + sizeof(CCreatureFileItem) * offsets->m_itemListCount;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 12925
    UTIL_ASSERT(creatureSize > 0);

    if (IcewindMisc::IsPC(this)) {
        if (m_equipment.m_selectedWeapon >= 43) {
            m_nWeaponSet = (m_equipment.m_selectedWeapon - 43) / 2;
        }
        sub_726810(m_nWeaponSet);
    }

    for (INT buttonNum = 0; buttonNum < g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetNumQuickWeaponSlots(m_typeAI.m_nClass); buttonNum++) {
        INT abilityNum = buttonNum + 43 == m_equipment.m_selectedWeapon
            ? m_equipment.m_selectedWeaponAbility
            : 0;

        CGameButtonList* buttons = GetItemUsages(buttonNum + 43, TRUE, abilityNum);
        if (!buttons->IsEmpty()) {
            // NOTE: Uninline.
            SetQuickWeapon(static_cast<BYTE>(buttonNum), *buttons->GetHead());

            while (!buttons->IsEmpty()) {
                delete buttons->RemoveHead();
            }
        }
        delete buttons;
    }

    CCreatureFileSpell* pSpell = new CCreatureFileSpell();
    DWORD nOffset;
    DWORD nIndex;
    UINT nClass;
    UINT nLevel;

    for (nClass = 0; nClass < CSPELLLIST_NUM_CLASSES; nClass++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            nOffset = offsets->m_spellListOffset[nClass][nLevel];
            for (nIndex = 0; nIndex < offsets->m_spellListCount[nClass][nLevel]; nIndex++) {
                *pSpell = *reinterpret_cast<CCreatureFileSpell*>(pCreature + nOffset);
                nOffset += sizeof(CCreatureFileSpell);

                const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(pSpell->field_0);
                if (memcmp(resRef.GetResRef(), "**", strlen("**")) == 0) {
                    CString sError;
                    sError.Format("*** %s has OBSOLETE DOMAIN SPELL FILE: %s.\n",
                        m_scriptName,
                        (LPCSTR)resRef.GetResRefStr());
                } else {
                    // NOTE: Uninline.
                    m_spells.Get(nClass)->Add(pSpell->field_0,
                        nLevel,
                        pSpell->field_4,
                        pSpell->field_8,
                        pSpell->field_C);
                }
            }
            creatureSize -= sizeof(CCreatureFileSpell) * offsets->m_spellListCount[nClass][nLevel];

            // NOTE: There are some inlining.

            m_spells.m_spellsByClass[nClass].m_lists[nLevel].field_14 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
            nOffset += sizeof(unsigned int);
            creatureSize -= sizeof(unsigned int);

            m_spells.m_spellsByClass[nClass].m_lists[nLevel].field_18 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
            nOffset += sizeof(unsigned int);
            creatureSize -= sizeof(unsigned int);
        }
    }

    for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        nOffset = offsets->m_domainListOffset[nLevel];
        for (nIndex = 0; nIndex < offsets->m_domainListCount[nLevel]; nIndex++) {
            *pSpell = *reinterpret_cast<CCreatureFileSpell*>(pCreature + nOffset);
            nOffset += sizeof(CCreatureFileSpell);

            const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(pSpell->field_0);
            if (memcmp(resRef.GetResRef(), "**", strlen("**")) == 0) {
                CString sError;
                sError.Format("*** %s has OBSOLETE DOMAIN SPELL FILE: %s.\n",
                    m_scriptName,
                    (LPCSTR)resRef.GetResRefStr());
            } else {
                // NOTE: Uninline.
                m_domainSpells.Add(pSpell->field_0,
                    nLevel,
                    pSpell->field_4,
                    pSpell->field_8,
                    pSpell->field_C);
            }
        }
        creatureSize -= sizeof(CCreatureFileSpell) * offsets->m_domainListCount[nLevel];

        m_domainSpells.m_lists[nLevel].field_14 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
        nOffset += sizeof(unsigned int);
        creatureSize -= sizeof(unsigned int);

        m_domainSpells.m_lists[nLevel].field_18 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
        nOffset += sizeof(unsigned int);
        creatureSize -= sizeof(unsigned int);
    }

    nOffset = offsets->m_innateListOffset;
    for (nIndex = 0; nIndex < offsets->m_innateListCount; nIndex++) {
        *pSpell = *reinterpret_cast<CCreatureFileSpell*>(pCreature + nOffset);
        nOffset += sizeof(CCreatureFileSpell);

        const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Get(pSpell->field_0);
        if (memcmp(resRef.GetResRef(), "**", strlen("**")) == 0) {
            CString sError;
            sError.Format("*** %s has OBSOLETE INNATE SPELL FILE: %s.\n",
                m_scriptName,
                (LPCSTR)resRef.GetResRefStr());
        } else {
            m_innateSpells.Add(pSpell->field_0,
                pSpell->field_4,
                pSpell->field_8,
                pSpell->field_C);
        }
    }
    creatureSize -= sizeof(CCreatureFileSpell) * offsets->m_innateListCount;

    m_innateSpells.field_14 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    m_innateSpells.field_18 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    nOffset = offsets->m_songListOffset;
    for (nIndex = 0; nIndex < offsets->m_songListCount; nIndex++) {
        *pSpell = *reinterpret_cast<CCreatureFileSpell*>(pCreature + nOffset);
        nOffset += sizeof(CCreatureFileSpell);

        const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->GetMasterSongLookup().Get(pSpell->field_0);
        if (memcmp(resRef.GetResRef(), "**", strlen("**")) == 0) {
            CString sError;
            sError.Format("*** %s has OBSOLETE SONG FILE: %s.\n",
                m_scriptName,
                (LPCSTR)resRef.GetResRefStr());
        } else {
            m_songs.Add(pSpell->field_0,
                pSpell->field_4,
                pSpell->field_8,
                pSpell->field_C);
        }
    }
    creatureSize -= sizeof(CCreatureFileSpell) * offsets->m_songListCount;

    m_songs.field_14 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    m_songs.field_18 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    nOffset = offsets->m_shapeListOffset;
    for (nIndex = 0; nIndex < offsets->m_shapeListCount; nIndex++) {
        *pSpell = *reinterpret_cast<CCreatureFileSpell*>(pCreature + nOffset);
        nOffset += sizeof(CCreatureFileSpell);

        const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->GetShapeshifts()->Get(pSpell->field_0);
        if (memcmp(resRef.GetResRef(), "**", strlen("**")) == 0) {
            CString sError;
            sError.Format("*** %s has OBSOLETE SHAPESHIFT FILE: %s.\n",
                m_scriptName,
                (LPCSTR)resRef.GetResRefStr());
        } else {
            m_shapeshifts.Add(pSpell->field_0,
                pSpell->field_4,
                pSpell->field_8,
                pSpell->field_C);
        }
    }
    creatureSize -= sizeof(CCreatureFileSpell) * offsets->m_shapeListCount;

    m_shapeshifts.field_14 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    m_shapeshifts.field_18 = *reinterpret_cast<unsigned int*>(pCreature + nOffset);
    nOffset += sizeof(unsigned int);
    creatureSize -= sizeof(unsigned int);

    delete pSpell;

    for (BYTE nHatedRaceIndex = 0; nHatedRaceIndex < 8; nHatedRaceIndex++) {
        if (m_baseStats.m_favoredEnemies[nHatedRaceIndex] == 0) {
            m_baseStats.m_favoredEnemies[nHatedRaceIndex] = CAIObjectType::R_NO_RACE;
        }
    }

    m_derivedStats.Reload(this, &m_baseStats, &m_spells, &m_domainSpells);
    m_bInUnmarshal = FALSE;

    if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nNightmareMode == TRUE
        && (m_baseStats.field_2FB & 0x1) == 0
        && a4 == NULL) {
        BOOL bIncreaseStats = FALSE;
        if (m_type == 2) {
            m_baseStats.m_hitPoints = 2 * (m_baseStats.m_hitPoints + 10);
            m_baseStats.m_maxHitPointsBase = 2 * (m_baseStats.m_maxHitPointsBase + 10);
            bIncreaseStats = TRUE;
        } else {
            if (offsets->m_enemyAlly > CAIObjectType::EA_GOODCUTOFF) {
                m_baseStats.m_hitPoints = 3 * (m_baseStats.m_hitPoints + 80);
                m_baseStats.m_maxHitPointsBase = 3 * (m_baseStats.m_maxHitPointsBase + 80);
                bIncreaseStats = TRUE;
            }
        }

        if (bIncreaseStats) {
            // NOTE: Uninline.
            BYTE moveScale = GetAnimation()->GetMoveScale();

            // NOTE: Uninline.
            GetAnimation()->SetMoveScale(static_cast<BYTE>(static_cast<float>(moveScale) * 1.3f + 1.0f));

            if (m_baseStats.m_gold != 0) {
                m_baseStats.m_gold += 75;
            }

            for (INT iClassType = 1; iClassType <= 11; iClassType++) {
                INT nLevel = GetClassLevel(iClassType);
                if (nLevel > 0) {
                    SetClassLevel(iClassType, min(nLevel + 12, 30));
                }
            }

            m_baseStats.m_STRBase += 10;
            m_baseStats.m_INTBase += 10;
            m_baseStats.m_WISBase += 10;
            m_baseStats.m_DEXBase += 10;
            m_baseStats.m_CONBase += 10;
            m_baseStats.m_CHRBase += 10;
            m_baseStats.field_252 += 10;
            m_baseStats.field_2FB |= 0x1;
        }
    }

    m_baseStats.field_2FC &= ~0x1;
    m_dialog = offsets->m_dialog;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 13227
    UTIL_ASSERT(creatureSize == 0);

    m_derivedStats.Reload(this, &m_baseStats, &m_spells, &m_domainSpells);
    m_tempStats = m_derivedStats;
    m_bonusStats.BonusInit();

    if (bAlloced) {
        delete pCreature;
    }
}

// 0x70E750
void CGameSprite::UnmarshalScripts()
{
    CString sFileName;

    sFileName = m_baseStats.m_scriptOverRide;
    if (sFileName != "") {
        m_overrideScript = new CAIScript(CResRef(sFileName));
        if (m_overrideScript->IsEmpty()) {
            delete m_overrideScript;
            m_overrideScript = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptSpecial1;
    if (sFileName != "") {
        m_special1Script = new CAIScript(CResRef(sFileName));
        if (m_special1Script->IsEmpty()) {
            delete m_special1Script;
            m_special1Script = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptTeam;
    if (sFileName != "") {
        m_teamScript = new CAIScript(CResRef(sFileName));
        if (m_teamScript->IsEmpty()) {
            delete m_teamScript;
            m_teamScript = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptSpecial2;
    if (sFileName != "") {
        m_special2Script = new CAIScript;
        m_special2Script->Read(CResRef(sFileName), g_pBaldurChitin->GetObjectGame()->m_bPlayerScriptStyle);
        if (m_special2Script->IsEmpty()) {
            delete m_special2Script;
            m_special2Script = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptCombat;
    if (sFileName != "") {
        m_combatScript = new CAIScript(CResRef(sFileName));
        if (m_combatScript->IsEmpty()) {
            delete m_combatScript;
            m_combatScript = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptSpecial3;
    if (sFileName != "") {
        m_special3Script = new CAIScript(CResRef(sFileName));
        if (m_special3Script->IsEmpty()) {
            delete m_special3Script;
            m_special3Script = NULL;
        }
    }

    sFileName = m_baseStats.m_scriptMovement;
    if (sFileName != "") {
        m_movementScript = new CAIScript(CResRef(sFileName));
        if (m_movementScript->IsEmpty()) {
            delete m_movementScript;
            m_movementScript = NULL;
        }
    }
}

// 0x70EC00
void CGameSprite::FetchCommonStrings()
{
    int index;

    for (index = 0; index < 3; index++) {
        g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[33 + index],
            m_speech[33 + index]);
    }

    for (index = 0; index < 7; index++) {
        g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[15 + index],
            m_speech[15 + index]);
    }
}

// 0x70EC70
void CGameSprite::LoadAreaInformation(CAreaFileCreature* pCreature)
{
    m_nNumberOfTimesTalkedTo = pCreature->m_numberTimesTalkedTo;

    CString tempRes;

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_dialogOverride), RESREF_SIZE);
    if (tempRes != "") {
        m_dialog = tempRes;
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_overrideScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptOverRide);
        SetScript(0, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_special3ScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptSpecial3);
        SetScript(5, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_special2ScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptSpecial2);
        SetScript(3, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_combatScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptCombat);
        SetScript(4, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_movementScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptMovement);
        SetScript(6, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_teamScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptTeam);
        SetScript(2, pScript);
    }

    tempRes = CString(reinterpret_cast<char*>(pCreature->m_special1ScriptOverride), RESREF_SIZE);
    tempRes.TrimLeft();
    if (tempRes != "") {
        CAIScript* pScript = new CAIScript(CResRef(tempRes));

        CResRef(tempRes).GetResRef(m_baseStats.m_scriptSpecial1);
        SetScript(1, pScript);
    }

    memcpy(m_scriptName, pCreature->m_scriptName, SCRIPTNAME_SIZE);
}

// 0x70F270
BYTE CGameSprite::GetChannel()
{
    SHORT nPortraitNum = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id);
    if (nPortraitNum != -1) {
        return nPortraitNum + 7;
    }
    return 13;
}

// 0x70F2A0
void CGameSprite::RenderMirrorImage(INT placement, CRect& rFX, CRect& rGCBounds, CRect& rViewRect, CPoint& ptReference, CSearchBitmap* pSearch, CVisibilityMap* pVisibility, CVidMode* pVidMode, INT nSurface, COLORREF& rgbTint, BOOLEAN& bDithered, BOOLEAN& bFadeOut, DWORD& dwRenderFlags)
{
    // 0x8B7308
    static int mirrorImagePlacementX[] = {
        -25,
        25,
        0,
        0,
        -18,
        18,
        18,
        -18,
    };

    // 0x8B7328
    static int mirrorImagePlacementY[] = {
        0,
        0,
        -25,
        25,
        -18,
        18,
        -18,
        18,
    };

    CPoint mirrorPos;
    CPoint mirrorSquare;
    SHORT searchSquareCode;
    CPoint pos;

    pos.x = m_pos.x + mirrorImagePlacementX[placement];
    pos.y = m_pos.y += mirrorImagePlacementY[placement];
    pos.y += m_pArea->GetHeightOffset(pos, m_listType);

    m_animation.CalculateGCBoundsRect(rGCBounds,
        pos,
        ptReference,
        m_posZ,
        rFX.Width(),
        rFX.Height());

    if (!IsRectEmpty(rViewRect & rGCBounds)) {
        mirrorPos.x = max(pos.x, m_pArea->GetInfinity()->nAreaX - 1) / CPathSearch::GRID_SQUARE_SIZEX;
        mirrorPos.y = max(pos.y, m_pArea->GetInfinity()->nAreaY - 1) / CPathSearch::GRID_SQUARE_SIZEY;
        if ((pSearch->GetLOSCost(mirrorPos, m_terrainTable, searchSquareCode, FALSE) != CPathSearch::COST_IMPASSABLE
                || searchSquareCode == 14)
            && pVisibility->IsTileExplored(pVisibility->PointToTile(mirrorPos))) {
            m_animation.Render(m_pArea->GetInfinity(),
                pVidMode,
                nSurface,
                rFX,
                mirrorPos,
                ptReference,
                dwRenderFlags | 0x2,
                rgbTint,
                rGCBounds,
                bDithered,
                bFadeOut,
                m_posZ,
                96);
        }
    }
}

// 0x713FE0
void CGameSprite::GetSelectedWeaponButton(CButtonData& cButtonData)
{
    const CRuleTables& rule = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    cButtonData.m_icon = "NOICON";
    cButtonData.m_count = 0;
    cButtonData.m_abilityId.m_itemType = 2;
    cButtonData.m_abilityId.m_itemNum = 10;
    cButtonData.m_abilityId.m_abilityNum = 1;
    cButtonData.m_abilityId.field_10 = -1;

    CItem* pItem = m_equipment.m_items[m_nTempSelectedWeapon];
    if (pItem != NULL) {
        pItem->Demand();
        ITEM_ABILITY* pAbility = pItem->GetAbility(m_nTempSelectedWeaponAbility);
        if (pAbility != NULL) {
            cButtonData.m_icon = CString(pAbility->quickSlotIcon);
            cButtonData.m_abilityId.m_itemNum = m_nTempSelectedWeapon;
            cButtonData.m_abilityId.m_itemType = 2;
            cButtonData.m_abilityId.m_abilityNum = m_nTempSelectedWeaponAbility;
            cButtonData.m_abilityId.field_10 = rule.GetItemAbilityDescription(pItem->cResRef,
                m_nTempSelectedWeaponAbility);
            if (cButtonData.m_abilityId.field_10 == -1) {
                cButtonData.m_abilityId.field_10 = pItem->GetGenericName();
            }

            cButtonData.m_count = 0;
            if (pItem->GetMaxStackable() > 1) {
                cButtonData.m_count = pItem->GetUsageCount(m_nTempSelectedWeaponAbility);
            }
        }
        pItem->Release();
    }
}

// 0x714130
void CGameSprite::GetWeaponButton(BYTE nButtonNum, CButtonData& cButtonData)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 15766
    UTIL_ASSERT_MSG(nButtonNum < CCREATUREFILEEQUIPMENT21_WEAPON_NUM, "Invalid button number.");

    const CRuleTables& rule = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    cButtonData.m_icon = "";
    cButtonData.m_count = 0;
    cButtonData.m_abilityId.m_itemType = 2;
    cButtonData.m_abilityId.m_itemNum = 10;
    cButtonData.m_abilityId.m_abilityNum = 1;
    cButtonData.m_abilityId.field_10 = -1;

    CItem* pItem = m_equipment.m_items[nButtonNum + 43];
    if (pItem != NULL) {
        pItem->Demand();
        ITEM_ABILITY* pAbility = pItem->GetAbility(field_3D3A[nButtonNum]);
        if (pAbility != NULL) {
            cButtonData.m_icon = CString(pAbility->quickSlotIcon);
            cButtonData.m_abilityId.m_itemType = 2;
            cButtonData.m_abilityId.m_itemNum = nButtonNum + 43;
            cButtonData.m_abilityId.m_abilityNum = field_3D3A[nButtonNum];
            cButtonData.m_abilityId.field_10 = rule.GetItemAbilityDescription(pItem->cResRef,
                field_3D3A[nButtonNum]);
            if (cButtonData.m_abilityId.field_10 == -1) {
                cButtonData.m_abilityId.field_10 = pItem->GetGenericName();
            }

            cButtonData.m_count = 0;
            if (pItem->GetMaxStackable() > 1) {
                cButtonData.m_count = pItem->GetUsageCount(field_3D3A[nButtonNum]);
            }
        }
        pItem->Release();
    }
}

// 0x7142D0
void CGameSprite::SetSelectedWeaponButton(SHORT buttonNum)
{
    if (m_equipment.m_items[42] != NULL) {
        g_pBaldurChitin->GetObjectGame()->SetState(2);
        g_pBaldurChitin->GetObjectGame()->SetIconIndex(12);
        g_pBaldurChitin->GetObjectGame()->m_iconResRef = "";
        g_pBaldurChitin->GetObjectGame()->field_38A6 = 1;
    } else {
        g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

        SHORT itemNum = m_quickWeapons[buttonNum].m_abilityId.m_itemNum;
        SHORT abilityNum = m_quickWeapons[buttonNum].m_abilityId.m_abilityNum;
        if (itemNum != -1 && abilityNum != -1) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE_: 15877
            m_nTempSelectedWeapon = static_cast<BYTE>(itemNum);
            m_nTempSelectedWeaponAbility = static_cast<BYTE>(abilityNum);
            SelectWeaponAbility(static_cast<BYTE>(itemNum),
                static_cast<BYTE>(abilityNum),
                0,
                1);
            m_interrupt = TRUE;
            if (m_equipment.m_selectedWeapon == itemNum) {
                g_pBaldurChitin->GetObjectGame()->SetState(2);
                g_pBaldurChitin->GetObjectGame()->SetIconIndex(12);
                g_pBaldurChitin->GetObjectGame()->m_iconResRef = "";
            }
            g_pBaldurChitin->GetObjectGame()->field_38A6 = 1;
        }
    }
}

// 0x714410
void CGameSprite::InitQuickSpellData(CResRef resRef, BYTE type, CButtonData& cButtonData, BYTE nClass, BYTE a5, BYTE nKitIndex)
{
    CSpell cSpell;
    cSpell.SetResRef(resRef, TRUE, TRUE);
    BYTE count = 0;

    if (!resRef.IsValid()) {
        return;
    }

    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->m_shapeshifts.Find(resRef, nID) == TRUE) {
        type = 4;
    }

    UINT v1 = 0;
    UINT v2 = 0;
    UINT nClassIndex;

    switch (type) {
    case 1:
        if (!g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, v1)) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15953
            UTIL_ASSERT(FALSE);
        }

        nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

        if (nKitIndex != 0) {
            if (nClass == CAIOBJECTTYPE_C_CLERIC) {
                BOOLEAN bFound = FALSE;
                for (UINT nLevel = 0; nLevel < m_domainSpells.m_nHighestLevel; nLevel++) {
                    if (!bFound) {
                        break;
                    }

                    if (m_domainSpells.Find(v1, nLevel, v2) == TRUE) {
                        bFound = TRUE;
                        count += m_domainSpells.m_lists[nLevel].Get(v2)->field_8;
                    }
                }
            }
        } else {
            BOOLEAN bFound = FALSE;
            for (UINT nLevel = 0; nLevel < m_spells.m_spellsByClass[nClass].m_nHighestLevel; nLevel++) {
                if (!bFound) {
                    break;
                }

                if (m_spells.m_spellsByClass[nClass].Find(v1, nLevel, v2) == TRUE) {
                    bFound = TRUE;
                    count += m_spells.m_spellsByClass[nClass].m_lists[nLevel].Get(v2)->field_8;
                }
            }
        }
        break;
    case 2:
        if (!g_pBaldurChitin->GetObjectGame()->m_innateSpells.Find(resRef, v1)) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15994
            UTIL_ASSERT(FALSE);
        }

        if (m_innateSpells.Find(v1, v2) == TRUE) {
            count += m_innateSpells.Get(v2)->field_8;
        }
        break;
    case 3:
        if (!g_pBaldurChitin->GetObjectGame()->m_songs.Find(resRef, v1)) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 16012
            UTIL_ASSERT(FALSE);
        }

        if (m_songs.Find(v1, v2) == TRUE) {
            count += m_songs.Get(v2)->field_8;
        }
        break;
    case 4:
        if (!g_pBaldurChitin->GetObjectGame()->m_shapeshifts.Find(resRef, v1)) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 16030
            UTIL_ASSERT(FALSE);
        }

        if (m_shapeshifts.Find(v1, v2) == TRUE) {
            count += m_shapeshifts.Get(v2)->field_8;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 16044
        UTIL_ASSERT(FALSE);
    }

    DWORD nSpecialization = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetSpecializationMask(nClass, nKitIndex);
    cSpell.Demand();

    SHORT nCasterLevel = GetCasterLevel(&cSpell, nClass, nSpecialization);
    if (nCasterLevel <= 1) {
        nCasterLevel = 1;
    }

    SPELL_ABILITY* pBestAbility = NULL;
    for (INT abilityNum = 0; abilityNum < cSpell.GetAbilityCount(); abilityNum++) {
        if (cSpell.GetAbility(abilityNum)->minCasterLevel > nCasterLevel) {
            break;
        }

        // FIXME: Calls `GetAbility` one more time.
        pBestAbility = cSpell.GetAbility(abilityNum);
    }

    if (pBestAbility != NULL) {
        cButtonData.m_icon = CString(pBestAbility->quickSlotIcon);
        cButtonData.m_name = cSpell.GetGenericName();
        cButtonData.m_abilityId.m_itemType = 1;
        cButtonData.m_abilityId.m_targetType = pBestAbility->actionType;
        cButtonData.m_abilityId.field_1D = a5;
        cButtonData.m_abilityId.m_nClass = nClass;
        cButtonData.m_abilityId.field_1E = nKitIndex;
        cButtonData.m_abilityId.field_10 = cSpell.GetGenericName();

        if (type == 1) {
            cButtonData.m_abilityId.field_18 = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetClassSuffixStringRef(nClass);
            if (!CanCast(nClass, 0, &cSpell)) {
                cButtonData.m_bDisabled = TRUE;
                cButtonData.m_abilityId.field_18 = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetClassBeyondCastingAbilityStringRef(nClass);
            }
        }

        cButtonData.m_count = count;

        if (count == 0) {
            cButtonData.m_bDisabled = TRUE;
        }

        if (type == 2) {
            if (resRef == CGameSprite::SPIN277) {
                cButtonData.m_bDisplayCount = FALSE;
                cButtonData.m_count = 0;

                if (!sub_763150(CGAMESPRITE_FEAT_ARTERIAL_STRIKE)) {
                    cButtonData.m_bDisabled = TRUE;
                }
            } else if (resRef == CGameSprite::SPIN278) {
                cButtonData.m_bDisplayCount = FALSE;
                cButtonData.m_count = 0;

                if (!sub_763150(CGAMESPRITE_FEAT_HAMSTRING)) {
                    cButtonData.m_bDisabled = TRUE;
                }
            } else if (resRef == CGameSprite::SPIN279) {
                cButtonData.m_bDisplayCount = FALSE;
                cButtonData.m_count = 0;

                if (!sub_763150(CGAMESPRITE_FEAT_RAPID_SHOT)) {
                    cButtonData.m_bDisabled = TRUE;
                }
            }
        }
    }

    cSpell.Release();
}

// 0x714DB0
void CGameSprite::InitQuickItemData(SHORT itemNum, SHORT abilityNum, int a3, CButtonData& cButtonData)
{
    const CRuleTables& cRule = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    if (itemNum != -1 && abilityNum != -1) {
        CItem* pItem = m_equipment.m_items[itemNum];
        if (pItem != NULL) {
            pItem->Demand();

            ITEM_ABILITY* ability = pItem->GetAbility(abilityNum);
            if (ability != NULL) {
                if (ability->type != 4
                    && (ability->type != 2 || CheckLauncherType(ability, NULL))) {
                    cButtonData.m_icon = CString(ability->quickSlotIcon);
                    cButtonData.m_name = pItem->GetGenericName();
                    cButtonData.m_abilityId.m_itemNum = itemNum;
                    cButtonData.m_abilityId.m_abilityNum = abilityNum;
                    cButtonData.m_abilityId.m_targetType = ability->actionType;
                    cButtonData.m_abilityId.field_10 = cRule.GetItemAbilityDescription(pItem->GetResRef(), abilityNum);
                    if (cButtonData.m_abilityId.field_10 == -1) {
                        cButtonData.m_abilityId.field_10 = pItem->GetGenericName();
                    }
                    cButtonData.m_count = 0;
                    if (pItem->GetMaxStackable() > 1
                        || pItem->GetMaxUsageCount(abilityNum) > 0) {
                        cButtonData.m_count = pItem->GetUsageCount(abilityNum);
                    }

                    SHORT launcherSlot;
                    CItem* pLauncher = GetLauncher(ability, launcherSlot);
                    if (pLauncher != NULL) {
                        cButtonData.m_launcherIcon = pLauncher->GetItemIcon();
                        cButtonData.m_launcherName = pLauncher->GetGenericName();
                    }
                }
            }

            pItem->Release();
        }
    }
}

// 0x716540
CGameButtonList* CGameSprite::GetSongsButtonList()
{
    CGameButtonList* buttons = new CGameButtonList();
    RESREF resRef;

    for (size_t index = 0; index < m_songs.m_List.size(); index++) {
        // NOTE: Uninline.
        CGameSpriteSpellListEntry* entry = m_songs.Get(index);

        // NOTE: Uninline.
        g_pBaldurChitin->GetObjectGame()->GetMasterSongLookup().Get(entry->m_nID).GetResRef(resRef);

        buttons->AddTail(IcewindMisc::CreateButtonData(resRef));
    }

    return buttons;
}

// NOTE: This function correctly accepts `nClass` by value (as opposed by to
// many others which passes `nClass` as a reference for unknown reason).
//
// 0x7166D0
BOOLEAN CGameSprite::CanCast(BYTE nClass, DWORD nSpecialization, CSpell* pSpell)
{
    INT nValue = 0;
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
    case CAIOBJECTTYPE_C_FIGHTER:
    case CAIOBJECTTYPE_C_MONK:
    case CAIOBJECTTYPE_C_ROGUE:
        return FALSE;
    case CAIOBJECTTYPE_C_BARD:
    case CAIOBJECTTYPE_C_SORCERER:
        nValue = m_derivedStats.m_nCHR;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        nValue = m_derivedStats.m_nWIS;
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        nValue = m_derivedStats.m_nINT;
        break;
    }

    INT nLevel = g_pBaldurChitin->GetObjectGame()->GetSpellLevel(pSpell->GetResRef(), nClass, nSpecialization);
    return nLevel < CSPELLLIST_MAX_LEVELS && nValue >= nLevel + 11;
}

// 0x717620
CGameButtonList* CGameSprite::GetInternalButtonList()
{
    CGameButtonList* buttons = new CGameButtonList();

    if (m_internalButtonList != NULL) {
        POSITION pos = m_internalButtonList->GetHeadPosition();
        while (pos != NULL) {
            CButtonData* node = m_internalButtonList->GetNext(pos);
            CButtonData* copy = new CButtonData();
            *copy = *node;
            buttons->AddTail(copy);
        }

        // FIXME: Meaninless memory leak.
        new CButtonData();
    }

    return buttons;
}

// 0x717850
CGameButtonList* CGameSprite::GetItemUsages(SHORT slotNum, WORD buttonType, SHORT abilityNum)
{
    const CRuleTables& cRule = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CGameButtonList* buttons = new CGameButtonList();

    // FIXME: Unused.
    STR_RES strRes;

    if (slotNum >= 51) {
        return buttons;
    }

    if (buttonType == 1 && m_equipment.m_items[42] != NULL) {
        if (slotNum == 43) {
            delete buttons;
            return GetItemUsages(42, 1, 0);
        }

        if (slotNum > 43) {
            return buttons;
        }
    }

    CItem* pItem = m_equipment.m_items[slotNum];
    if (pItem == NULL) {
        return buttons;
    }

    if (slotNum == 43
        || slotNum == 45
        || slotNum == 47
        || slotNum == 49) {
        if ((pItem->GetFlagsFile() & 0x2) != 0) {
            if (m_equipment.m_items[slotNum + 1] != NULL) {
                return buttons;
            }
        }
    }

    pItem->Demand();

    INT nStart = abilityNum;
    INT nEnd;
    if (abilityNum == -1) {
        nStart = 0;
        if (pItem->GetItemType() == 11) {
            nEnd = 1;
        } else {
            nEnd = pItem->GetAbilityCount();
        }
    } else {
        nEnd = abilityNum + 1;
    }

    for (INT nAbility = nStart; nAbility < nEnd; nAbility++) {
        const ITEM_ABILITY* curAbility = pItem->GetAbility(nAbility);
        if (curAbility == NULL) {
            continue;
        }

        if ((curAbility->type & 0x100) != 0 && (pItem->m_flags & 0x1) == 0) {
            continue;
        }

        if ((curAbility->type & 0x200) != 0 && (pItem->m_flags & 0x1) != 0) {
            continue;
        }

        if (curAbility->quickSlotType == buttonType && (curAbility->type & 0xFF) != 4) {
            if ((curAbility->type & 0xFF) != 2 || CheckLauncherType(curAbility, NULL)) {
                CButtonData* pButtonData = new CButtonData();
                pButtonData->m_icon = CString(curAbility->quickSlotIcon);
                pButtonData->m_name = pItem->GetGenericName();
                pButtonData->m_abilityId.m_itemType = 2;
                pButtonData->m_abilityId.m_itemNum = slotNum;
                pButtonData->m_abilityId.m_abilityNum = nAbility;
                pButtonData->m_abilityId.m_targetType = curAbility->actionType;
                pButtonData->m_abilityId.field_10 = cRule.GetItemAbilityDescription(pItem->GetResRef(), nAbility);
                if (pButtonData->m_abilityId.field_10 == -1) {
                    pButtonData->m_abilityId.field_10 = pItem->GetGenericName();
                }
                pButtonData->m_count = 0;
                if (pItem->GetMaxStackable() > 1 || pItem->GetMaxUsageCount(nAbility) > 0) {
                    pButtonData->m_count = pItem->GetUsageCount(nAbility);
                }

                SHORT launcherSlot;
                CItem* pLauncher = GetLauncher(curAbility, launcherSlot);
                if (pLauncher != NULL) {
                    pButtonData->m_launcherIcon = pLauncher->GetItemIcon();
                    pButtonData->m_launcherName = pLauncher->GetGenericName();
                }

                buttons->AddTail(pButtonData);
            }
        } else {
            if ((curAbility->type & 0xFF) == 4) {
                for (INT ammoSlotNum = 11; ammoSlotNum < 15; ammoSlotNum++) {
                    CItem* pAmmo = m_equipment.m_items[ammoSlotNum];
                    if (pAmmo == NULL) {
                        continue;
                    }

                    pAmmo->Demand();

                    for (INT nAmmoAbility = nStart; nAmmoAbility < nEnd; nAmmoAbility++) {
                        const ITEM_ABILITY* curAmmoAbility = pAmmo->GetAbility(nAmmoAbility);
                        if (curAmmoAbility != NULL
                            && curAmmoAbility->quickSlotType == buttonType
                            && (curAmmoAbility->type & 0xFF) != 4
                            && CheckLauncherType(curAmmoAbility, pItem)) {
                            CButtonData* pButtonData = new CButtonData();
                            pButtonData->m_icon = CString(curAmmoAbility->quickSlotIcon);
                            pButtonData->m_name = pAmmo->GetGenericName();
                            pButtonData->m_count = pAmmo->GetUsageCount(nAmmoAbility);
                            pButtonData->m_abilityId.m_itemType = 2;
                            pButtonData->m_abilityId.m_itemNum = ammoSlotNum;
                            pButtonData->m_abilityId.m_abilityNum = nAmmoAbility;
                            pButtonData->m_abilityId.m_targetType = curAmmoAbility->actionType;
                            if (curAmmoAbility->maxUsageCount == 0) {
                                pButtonData->m_bDisplayCount = FALSE;
                            }
                            pButtonData->m_abilityId.field_10 = cRule.GetItemAbilityDescription(pAmmo->GetResRef(), nAmmoAbility);
                            if (pButtonData->m_abilityId.field_10 == -1) {
                                pButtonData->m_abilityId.field_10 = pAmmo->GetGenericName();
                            }
                            pButtonData->m_launcherIcon = pItem->GetItemIcon();
                            pButtonData->m_launcherName = pItem->GetGenericName();

                            buttons->AddTail(pButtonData);
                        }
                    }

                    pAmmo->Release();
                }
            }
        }
    }

    pItem->Release();

    return buttons;
}

// 0x718650
CItem* CGameSprite::GetLauncher(const ITEM_ABILITY* ability, SHORT& launcherSlot)
{
    int index;
    launcherSlot = 0;

    if (ability == NULL || ability->type != 2) {
        return NULL;
    }

    switch (ability->launcherType) {
    case 1:
        launcherSlot = 2 * m_nWeaponSet + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 15) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 15) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    case 2:
        launcherSlot = 2 * m_nWeaponSet + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 27) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 27) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    case 3:
        launcherSlot = 2 * m_nWeaponSet + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 18) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 18) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    }

    return NULL;
}

// 0x7187E0
SHORT CGameSprite::GetLauncherSlot(SHORT slotNum, SHORT abilityNum)
{
    int index;

    CItem* pItem = m_equipment.m_items[slotNum];
    if (pItem == NULL) {
        return -1;
    }

    pItem->Demand();

    ITEM_ABILITY* ability = pItem->GetAbility(abilityNum);
    if (ability == NULL || ability->type != 2) {
        pItem->Release();
        return -1;
    }

    switch (ability->launcherType) {
    case 1:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 15) {
            pItem->Release();
            return 2 * m_nWeaponSet + 43;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 15) {
                pItem->Release();
                return 43 + index;
            }
        }
        break;
    case 2:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 27) {
            pItem->Release();
            return 2 * m_nWeaponSet + 43;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 27) {
                pItem->Release();
                return 43 + index;
            }
        }
        break;
    case 3:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 18) {
            pItem->Release();
            return 2 * m_nWeaponSet + 43;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 18) {
                pItem->Release();
                return 43 + index;
            }
        }
        break;
    }

    pItem->Release();
    return -1;
}

// 0x718980
BOOL CGameSprite::CheckLauncherType(const ITEM_ABILITY* ability, CItem* pLauncher)
{
    int index;

    if (pLauncher != NULL) {
        switch (ability->launcherType) {
        case 1:
            return pLauncher->GetItemType() == 15;
        case 2:
            return pLauncher->GetItemType() == 27;
        case 3:
            return pLauncher->GetItemType() == 18;
        default:
            return FALSE;
        }
    }

    switch (ability->launcherType) {
    case 0:
        return TRUE;
    case 1:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 15) {
            return TRUE;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 15) {
                return TRUE;
            }
        }
        break;
    case 2:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 27) {
            return TRUE;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 27) {
                return TRUE;
            }
        }
        break;
    case 3:
        if (m_equipment.m_items[2 * m_nWeaponSet + 43] != NULL
            && m_equipment.m_items[2 * m_nWeaponSet + 43]->GetItemType() == 18) {
            return TRUE;
        }
        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 18) {
                return TRUE;
            }
        }
        break;
    }
    return FALSE;
}

// 0x718B30
BOOL CGameSprite::ReadyCursor()
{
    switch (m_currentUseButton.m_abilityId.m_targetType) {
    case 1:
        g_pBaldurChitin->GetObjectGame()->SetState(2);
        g_pBaldurChitin->GetObjectGame()->SetIconIndex(20);
        g_pBaldurChitin->GetObjectGame()->m_iconResRef = "";
        return TRUE;
    case 2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 18306
        UTIL_ASSERT(FALSE);
    case 3:
        g_pBaldurChitin->GetObjectGame()->SetState(2);
        g_pBaldurChitin->GetObjectGame()->SetIconIndex(20);
        g_pBaldurChitin->GetObjectGame()->m_iconResRef = "";
        return TRUE;
    case 4:
        g_pBaldurChitin->GetObjectGame()->SetState(1);
        g_pBaldurChitin->GetObjectGame()->SetIconIndex(20);
        g_pBaldurChitin->GetObjectGame()->m_iconResRef = "";
        return TRUE;
    case 5:
    case 6:
        g_pBaldurChitin->GetObjectGame()->SetState(0);
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->SetSelectedButton(100);
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->UpdateState();
        return FALSE;
    default:
        return TRUE;
    }
}

// 0x718CE0
void CGameSprite::ReadySpell(SHORT buttonNum, INT nType, BOOLEAN firstCall)
{
    switch (nType) {
    case 2:
        m_currentUseButton = m_quickSpells[buttonNum];
        break;
    case 4:
        m_currentUseButton = m_quickInnates[buttonNum];
        break;
    case 6:
        m_currentUseButton = m_quickSongs[buttonNum];
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 18354
        UTIL_ASSERT(FALSE);
    }

    CAIAction action;
    CString string;
    BOOL cursor = ReadyCursor();

    if (!firstCall && !cursor) {
        switch (m_currentUseButton.m_abilityId.m_targetType) {
        case 5:
            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            m_currentUseButton.m_abilityId.m_res.CopyToString(string);
            action = CAIAction(CAIAction::SPELL,
                m_typeAI,
                string,
                0,
                m_currentUseButton.m_abilityId.m_nClass | (m_currentUseButton.m_abilityId.field_1E << 8));
            action.m_specificID3 = m_currentUseButton.m_abilityId.field_1D;
            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 6:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 18385
            UTIL_ASSERT(FALSE);
            break;
        }
    }
}

// 0x719860
void CGameSprite::ReadyItem(SHORT buttonNum, BOOLEAN firstCall)
{
    m_currentUseButton = m_quickItems[buttonNum];

    CAIAction action;
    CString string;
    BOOL cursor = ReadyCursor();

    if (!firstCall && !cursor) {
        switch (m_currentUseButton.m_abilityId.m_targetType) {
        case 5:
            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            // FIXME: Unused.
            m_currentUseButton.m_abilityId.m_res.CopyToString(string);

            // NOTE: Uninline.
            action = CAIAction(CAIAction::USEITEM,
                m_typeAI,
                m_currentUseButton.m_abilityId.m_itemNum,
                m_currentUseButton.m_abilityId.m_abilityNum,
                0);

            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 6:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 18538
            UTIL_ASSERT(FALSE);
            break;
        }
    }
}

// FIXME: `buttonData` should be reference.
//
// 0x719CA0
void CGameSprite::ReadyOffInternalList(CButtonData buttonData, BOOLEAN firstCall)
{
    m_currentUseButton = buttonData;

    CAIAction action;
    CString string;
    BOOL cursor = ReadyCursor();

    if (!firstCall && !cursor) {
        switch (m_currentUseButton.m_abilityId.m_targetType) {
        case 5:
            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            // FIXME: Unused.
            m_currentUseButton.m_abilityId.m_res.CopyToString(string);

            // NOTE: Uninline.
            action = CAIAction(CAIAction::USEITEM,
                m_typeAI,
                m_currentUseButton.m_abilityId.m_itemNum,
                m_currentUseButton.m_abilityId.m_abilityNum,
                0);

            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 6:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 18593
            UTIL_ASSERT(FALSE);
            break;
        }
    }
}

// FIXME: `buttonData` should be reference.
//
// 0x71A0E0
void CGameSprite::sub_71A0E0(CButtonData buttonData, BOOLEAN firstCall)
{
    m_currentUseButton = buttonData;

    CAIAction action;
    CString string;
    BOOL cursor = ReadyCursor();

    if (!firstCall && !cursor) {
        switch (m_currentUseButton.m_abilityId.m_targetType) {
        case 5:
            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            m_currentUseButton.m_abilityId.m_res.CopyToString(string);

            // NOTE: Uninline.
            action = CAIAction(CAIAction::SPELL,
                m_typeAI,
                string,
                0,
                m_currentUseButton.m_abilityId.m_nClass | (m_currentUseButton.m_abilityId.field_1E << 8));

            action.m_specificID3 = m_currentUseButton.m_abilityId.field_1D;
            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 6:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 16649
            UTIL_ASSERT(FALSE);
            break;
        }
    }
}

// FIXME: `buttonData` should be reference.
//
// 0x71A550
void CGameSprite::sub_71A550(CButtonData buttonData, BOOLEAN firstCall)
{
    m_currentUseButton = buttonData;

    CAIAction action;
    CString string;
    BOOL cursor = ReadyCursor();

    if (!firstCall && !cursor) {
        switch (m_currentUseButton.m_abilityId.m_itemType) {
        case 3:
            m_castCounter = -1;

            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            m_currentUseButton.m_abilityId.m_res.CopyToString(string);

            // NOTE: Uninline.
            action = CAIAction(CAIAction::SPELL,
                m_typeAI,
                string,
                0,
                m_currentUseButton.m_abilityId.m_nClass | (m_currentUseButton.m_abilityId.field_1E << 8));

            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 4:
            // FIXME: One time is usually enough.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);

            m_currentUseButton.m_abilityId.m_res.CopyToString(string);

            // NOTE: This call is not inlined (see above).
            action = CAIAction(CAIAction::SPELL,
                m_typeAI,
                string,
                0,
                m_currentUseButton.m_abilityId.m_nClass | (m_currentUseButton.m_abilityId.field_1E << 8));
            action.m_specificID3 = m_currentUseButton.m_abilityId.field_1D;
            ClearActions(FALSE);
            m_userCommandPause = 75;
            m_triggerId = CGameObjectArray::INVALID_INDEX;
            AddAction(action);
            m_interrupt = TRUE;
            break;
        case 5:
            // NOTE: For unknown reason the first call of `SetLastTarget` is
            // inlined, but the second is not.
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetObjectGame()->SetLastTarget(CGameObjectArray::INVALID_INDEX);
            FireSpell(m_currentUseButton.m_abilityId.m_res, this);
            break;
        }
    }
}

// 0x71B3B0
void CGameSprite::CheckToolTipItem(BYTE buttonNum)
{
    SHORT nItemNum = m_quickItems[buttonNum].m_abilityId.m_itemNum;
    if (nItemNum != -1) {
        CItem* pItem = m_equipment.m_items[nItemNum];
        if (pItem != NULL) {
            // FIXME: Calls `GetGenericName` twice.
            m_quickItems[nItemNum].m_name = pItem->GetGenericName();
            m_quickItems[nItemNum].m_abilityId.field_10 = pItem->GetGenericName();
        }
    }
}

// 0x71B400
CItem* CGameSprite::GetQuickItem(BYTE buttonNum)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 18909
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_ITEMS21);

    SHORT nItemNum = m_quickItems[buttonNum].m_abilityId.m_itemNum;
    if (nItemNum != -1) {
        return m_equipment.m_items[nItemNum];
    } else {
        return NULL;
    }
}

// 0x71B460
void CGameSprite::UnequipAll(BOOL animationOnly)
{
    if (m_equipment.m_items[6] != NULL) {
        m_equipment.m_items[6]->Unequip(this, 6, TRUE, animationOnly);
    }

    if (m_equipment.m_items[1] != NULL) {
        m_equipment.m_items[1]->Unequip(this, 1, TRUE, animationOnly);
    }

    if (m_equipment.m_items[5] != NULL) {
        m_equipment.m_items[5]->Unequip(this, 5, TRUE, animationOnly);
    }

    if (m_equipment.m_items[7] != NULL) {
        m_equipment.m_items[7]->Unequip(this, 7, TRUE, animationOnly);
    }

    if (m_equipment.m_items[8] != NULL) {
        m_equipment.m_items[8]->Unequip(this, 8, TRUE, animationOnly);
    }

    if (m_equipment.m_items[0] != NULL) {
        m_equipment.m_items[0]->Unequip(this, 0, TRUE, animationOnly);
    }

    if (m_equipment.m_items[2] != NULL) {
        m_equipment.m_items[2]->Unequip(this, 2, TRUE, animationOnly);
    }

    if (m_equipment.m_items[3] != NULL) {
        m_equipment.m_items[3]->Unequip(this, 3, TRUE, animationOnly);
    }

    if (m_equipment.m_items[4] != NULL) {
        m_equipment.m_items[4]->Unequip(this, 4, TRUE, animationOnly);
    }

    BYTE nIndex = 2 * (m_nWeaponSet + 22);
    if (m_equipment.m_items[nIndex] != NULL) {
        m_equipment.m_items[nIndex]->Unequip(this, nIndex, TRUE, animationOnly);
    }

    if (m_equipment.m_items[m_equipment.m_selectedWeapon] != NULL) {
        m_equipment.m_items[m_equipment.m_selectedWeapon]->Unequip(this, nIndex, TRUE, animationOnly);

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Demand();
        ITEM_ABILITY* pAbility = m_equipment.m_items[m_equipment.m_selectedWeapon]->GetAbility(m_equipment.m_selectedWeaponAbility);

        SHORT lSlot;
        CItem* pLauncher = GetLauncher(pAbility, lSlot);
        if (pLauncher != NULL) {
            pLauncher->Unequip(this, lSlot, TRUE, animationOnly);
        }

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Release();
    }
}

// 0x71B5E0
void CGameSprite::EquipAll(BOOL animationOnly)
{
    if (m_equipment.m_items[6] != NULL) {
        m_equipment.m_items[6]->Unequip(this, 6, TRUE, animationOnly);
    }

    if (m_equipment.m_items[1] != NULL) {
        m_equipment.m_items[1]->Unequip(this, 1, TRUE, animationOnly);
    }

    if (m_equipment.m_items[5] != NULL) {
        m_equipment.m_items[5]->Unequip(this, 5, TRUE, animationOnly);
    }

    if (m_equipment.m_items[7] != NULL) {
        m_equipment.m_items[7]->Unequip(this, 7, TRUE, animationOnly);
    }

    if (m_equipment.m_items[8] != NULL) {
        m_equipment.m_items[8]->Unequip(this, 8, TRUE, animationOnly);
    }

    if (m_equipment.m_items[0] != NULL) {
        m_equipment.m_items[0]->Unequip(this, 0, TRUE, animationOnly);
    }

    if (m_equipment.m_items[2] != NULL) {
        m_equipment.m_items[2]->Unequip(this, 2, TRUE, animationOnly);
    }

    if (m_equipment.m_items[3] != NULL) {
        m_equipment.m_items[3]->Unequip(this, 3, TRUE, animationOnly);
    }

    if (m_equipment.m_items[4] != NULL) {
        m_equipment.m_items[4]->Unequip(this, 4, TRUE, animationOnly);
    }

    BOOL v1 = FALSE;
    BYTE v2 = 2 * m_nWeaponSet + 43;
    if (m_equipment.m_selectedWeapon == v2) {
        v1 = TRUE;
    }

    if (m_equipment.m_items[m_equipment.m_selectedWeapon] != NULL) {
        m_equipment.m_items[m_equipment.m_selectedWeapon]->Equip(this, m_equipment.m_selectedWeapon, animationOnly);

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Demand();

        ITEM_ABILITY* pAbility = m_equipment.m_items[m_equipment.m_selectedWeapon]->GetAbility(m_equipment.m_selectedWeaponAbility);

        SHORT lSlot;
        CItem* pLauncher = GetLauncher(pAbility, lSlot);
        if (pLauncher != NULL) {
            pLauncher->Equip(this, lSlot, animationOnly);

            if (lSlot == v2) {
                v1 = TRUE;
            }
        }
    }

    BYTE v3 = 2 * (m_nWeaponSet + 22);
    if (m_equipment.m_items[v3] != NULL && v1 == TRUE) {
        m_equipment.m_items[v3]->Equip(this, v3, animationOnly);
    }
}

// 0x71B770
void CGameSprite::Equip(SHORT slotNum)
{
    if (slotNum <= 51) {
        if (m_equipment.m_items[slotNum] != NULL) {
            if (slotNum >= 0 && slotNum <= 8) {
                m_equipment.m_items[slotNum]->Equip(this, slotNum, FALSE);
            }
        }
    }
}

// 0x71B7A0
void CGameSprite::Unequip(SHORT slotNum)
{
    if (slotNum <= 51) {
        if (m_equipment.m_items[slotNum] != NULL) {
            switch (slotNum) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 43:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
                if (slotNum == m_equipment.m_selectedWeapon) {
                    m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);

                    m_equipment.m_items[slotNum]->Demand();

                    ITEM_ABILITY* pAbility = m_equipment.m_items[slotNum]->GetAbility(m_equipment.m_selectedWeaponAbility);

                    SHORT lSlot;
                    CItem* pLauncher = GetLauncher(pAbility, lSlot);
                    if (pLauncher != NULL) {
                        pLauncher->Unequip(this, slotNum, TRUE, FALSE);
                    }

                    m_equipment.m_items[slotNum]->Release();

                    SelectWeaponAbility(10, 0, 0, 1);
                } else {
                    m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);
                }
                break;
            }
        }
    }
}

// 0x71B8D0
SHORT CGameSprite::GetTurnUndeadLevel()
{
    DWORD nLevel = m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC);

    // FIXME: Calculates paladin class twice.
    if (m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) > 2) {
        nLevel += m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) - 2;
    }

    return static_cast<SHORT>(nLevel);
}

// 0x71B910
SHORT CGameSprite::GetBackstabDamageMultiplier()
{
    if (!m_typeAI.IsClassValid(CAIObjectType::C_ROGUE)) {
        return 0;
    }

    // NOTE: Uninline.
    CDerivedStats* DStats = GetActiveStats();

    INT nLevel = DStats->GetBardMonkRogueLevel();
    return static_cast<SHORT>(atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tBackstabMultiplier.GetAt(CPoint(nLevel, 0))));
}

// 0x71B9A0
SHORT CGameSprite::GetLayOnHandsAmount()
{
    return g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetLayOnHandsAmount(m_typeAI, m_derivedStats);
}

// 0x71B9C0
void CGameSprite::AddSpecialAbility(const CResRef& cResInnateSpell, BOOL feedBack)
{
    // TODO: Incomplete.
}

// 0x71BC60
void CGameSprite::RemoveSpecialAbility(const CResRef& cResInnateSpell)
{
    // TODO: Incomplete.
}

// 0x71BE80
void CGameSprite::CheckLoadState()
{
    if (m_baseStats.m_generalState == 0) {
        return;
    }

    if ((m_baseStats.m_generalState & STATE_DEAD) != 0) {
        SetSequence(SEQ_TWITCH);
    }

    if ((m_baseStats.m_generalState & STATE_FLAME_DEATH) != 0) {
        GetAnimation()->SetColorEffectAll(0, RGB(75, 75, 75), 1);
    }

    if ((m_baseStats.m_generalState & STATE_STONE_DEATH) != 0) {
        m_animationRunning = FALSE;
        if (GetAnimation()->IsFalseColor()) {
            m_hasColorRangeEffects = TRUE;

            for (BYTE range = 0; range < 7; range++) {
                CColorRange* pColorRange = new CColorRange();
                pColorRange->m_range = range;
                pColorRange->m_color = CVidPalette::STONE;
                m_derivedStats.m_appliedColorRanges.AddTail(pColorRange);

                GetAnimation()->SetColorRange(range, CVidPalette::STONE);
            }
        }
    }

    if ((m_baseStats.m_generalState & STATE_FROZEN_DEATH) != 0) {
        m_animationRunning = FALSE;
        if (GetAnimation()->IsFalseColor()) {
            m_hasColorRangeEffects = TRUE;

            for (BYTE range = 0; range < 7; range++) {
                CColorRange* pColorRange = new CColorRange();
                pColorRange->m_range = range;
                pColorRange->m_color = CVidPalette::ICE;
                m_derivedStats.m_appliedColorRanges.AddTail(pColorRange);

                GetAnimation()->SetColorRange(range, CVidPalette::ICE);
            }
        }
    }
}

// 0x71C0A0
INT CGameSprite::GetNumQuickWeaponSlots()
{
    return g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetNumQuickWeaponSlots(m_typeAI.m_nClass);
}

// 0x71D310
SHORT CGameSprite::FindItemPersonal(const CString& sName, int number, BOOL restrictToEquiped)
{
    CString sMutableName(sName);
    sMutableName.MakeUpper();

    SHORT end = 51;
    if (restrictToEquiped) {
        end = 18;
    }

    for (SHORT slot = 0; slot < end; slot++) {
        if (m_equipment.m_items[slot] != NULL
            && m_equipment.m_items[slot]->cResRef == sName) {
            if (number > 0) {
                number--;
            } else {
                return slot;
            }
        }
    }

    return 0;
}

// 0x71D3D0
SHORT CGameSprite::CountItemPersonal(const CString& sName)
{
    SHORT number = 0;

    CString sMutableName(sName);
    sMutableName.MakeUpper();

    for (SHORT slot = 0; slot < 51; slot++) {
        if (m_equipment.m_items[slot] != NULL
            && m_equipment.m_items[slot]->cResRef == sName) {
            if (m_equipment.m_items[slot]->GetMaxStackable() > 1) {
                number += m_equipment.m_items[slot]->GetUsageCount(0);
            } else {
                number++;
            }
        }
    }

    return number;
}

// 0x71D480
DWORD CGameSprite::GetCarriedWeight()
{
    DWORD weight = 0;

    for (int index = 0; index < 51; index++) {
        if (m_equipment.m_items[index] != NULL) {
            weight += m_equipment.m_items[index]->GetWeight();
        }
    }

    return weight;
}

// 0x71D4B0
void CGameSprite::GetQuickWeapon(BYTE buttonNum, CButtonData& buttonData)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 20520
    UTIL_ASSERT_MSG(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_WEAPONS22, "Trying to access illegal quick weapon slot");

    if (m_equipment.m_items[42] != NULL) {
        CGameButtonList* buttons = GetItemUsages(42, 1, 0);
        if (!buttons->IsEmpty()) {
            CButtonData* node = buttons->RemoveHead();
            if (node != NULL) {
                buttonData = *node;
                delete node;
            }
            while (!buttons->IsEmpty()) {
                delete buttons->RemoveHead();
            }
        }
        delete buttons;
    }

    buttonData = m_quickWeapons[buttonNum];

    if (buttonNum == 0
        || buttonNum == 2
        || buttonNum == 4
        || buttonNum == 6) {
        CItem* pItem = m_equipment.m_items[buttonNum + 44];
        if (pItem != NULL) {
            // FIXME: Calls `GetItemType` four times.
            if (pItem->GetItemType() == 47
                || pItem->GetItemType() == 53
                || pItem->GetItemType() == 49
                || pItem->GetItemType() == 41) {
                if (buttonData.m_abilityId.m_itemNum == -1
                    || buttonData.m_abilityId.m_itemNum == 10) {
                    CGameButtonList* buttons = GetItemUsages(10, 1, 0);
                    CButtonData* node = buttons->RemoveHead();
                    if (node != NULL) {
                        buttonData = *node;
                        m_quickWeapons[buttonNum] = *node;
                        delete node;
                    }
                    while (!buttons->IsEmpty()) {
                        delete buttons->RemoveHead();
                    }
                    delete buttons;
                }
            }
        } else if (buttonData.m_abilityId.m_itemNum == -1) {
            if (buttonData.m_abilityId.m_itemNum == -1
                || buttonData.m_abilityId.m_itemNum == 10) {
                CGameButtonList* buttons = GetItemUsages(10, 1, 0);
                CButtonData* node = buttons->RemoveHead();
                if (node != NULL) {
                    buttonData = *node;
                    m_quickWeapons[buttonNum] = *node;
                    delete node;
                }
                while (!buttons->IsEmpty()) {
                    delete buttons->RemoveHead();
                }
                delete buttons;
            }
        }
    } else {
        CItem* pItem = m_equipment.m_items[buttonNum + 43];
        if (pItem != NULL) {
            // FIXME: Calls `GetItemType` four times.
            if (pItem->GetItemType() == 47
                || pItem->GetItemType() == 53
                || pItem->GetItemType() == 49
                || pItem->GetItemType() == 41) {
                buttonData.m_icon = pItem->GetItemIcon();
                buttonData.m_name = pItem->GetGenericName();
                buttonData.m_abilityId.m_itemType = 2;
                buttonData.m_abilityId.m_itemNum = buttonNum + 43;
                buttonData.m_abilityId.m_targetType = -1;
                buttonData.m_abilityId.field_10 = pItem->GetGenericName();
            }
        }
    }
}

// 0x71DAB0
void CGameSprite::SetScript(SHORT level, CAIScript* script)
{
    // FIXME: Unused.
    CString v1;

    switch (level) {
    case 0:
        if (m_overrideScript != NULL) {
            delete m_overrideScript;
            m_overrideScript = NULL;
        }

        m_overrideScript = script;
        m_overrideScript->m_cResRef.GetResRef(m_baseStats.m_scriptOverRide);
        break;
    case 1:
        if (m_special1Script != NULL) {
            delete m_special1Script;
            m_special1Script = NULL;
        }
        m_special1Script = script;
        // FIXME: Probably missing copying resref to `m_baseStats`.
        break;
    case 2:
        if (m_teamScript != NULL) {
            delete m_teamScript;
            m_teamScript = NULL;
        }

        m_teamScript = script;
        m_teamScript->m_cResRef.GetResRef(m_baseStats.m_scriptTeam);
        break;
    case 3:
        if (m_special2Script != NULL) {
            delete m_special2Script;
            m_special2Script = NULL;
        }
        m_special2Script = script;
        m_special2Script->m_cResRef.GetResRef(m_baseStats.m_scriptSpecial2);
        break;
    case 4:
        if (m_combatScript != NULL) {
            delete m_combatScript;
            m_combatScript = NULL;
        }
        m_combatScript = script;
        m_combatScript->m_cResRef.GetResRef(m_baseStats.m_scriptCombat);
        break;
    case 5:
        if (m_special3Script != NULL) {
            delete m_special3Script;
            m_special3Script = NULL;
        }
        m_special3Script = script;
        m_special3Script->m_cResRef.GetResRef(m_baseStats.m_scriptSpecial3);
        break;
    case 6:
        if (m_movementScript != NULL) {
            delete m_movementScript;
            m_movementScript = NULL;
        }
        m_movementScript = script;
        m_movementScript->m_cResRef.GetResRef(m_baseStats.m_scriptMovement);
        break;
    }
}

// 0x71DD20
void CGameSprite::InitializeWalkingSound()
{
    m_nSndWalk = 0;
    m_currSndWalk = 0;

    // NOTE: Uninline.
    char* pSndWalk = m_animation.GetSndWalk(m_pArea->m_search.GetTableIndex(m_pos));
    if (pSndWalk != NULL) {
        m_sndWalk[m_currSndWalk].SetResRef(CResRef(pSndWalk), TRUE, TRUE);
        if (pSndWalk[0] != '\0') {
            delete pSndWalk;
        }
    } else {
        m_sndWalk[m_currSndWalk].SetResRef(CResRef(""), TRUE, TRUE);
    }
}

// 0x71DFB0
void CGameSprite::AutoPause(DWORD type)
{
    COLORREF nameColor;
    STRREF strPause;

    if (type == 256
        || (type == 128 && g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bAutoPauseOnTrap)
        || (type & g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nAutoPauseState) != 0) {
        if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) != -1
            || g_pBaldurChitin->GetObjectGame()->IsAlly(m_id)
            || g_pBaldurChitin->GetObjectGame()->IsFamiliar(m_id)) {
            nameColor = CVidPalette::RANGE_COLORS[m_baseStats.m_colors[CVIDPALETTE_RANGE_MAIN_CLOTH]];
            if (g_pChitin->cNetwork.GetSessionOpen()
                || g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->GetScreenWorld()) {
                switch (type) {
                case 0x1:
                    strPause = 17113; // "Auto-Paused: Weapon Unusable"
                    break;
                case 0x2:
                    strPause = 17114; // "Auto-Paused: Attacked"
                    break;
                case 0x4:
                    strPause = 17115; // "Auto-Paused: Hit"
                    break;
                case 0x8:
                    strPause = 17116; // "Auto-Paused: Badly Wounded"
                    break;
                case 0x10:
                    strPause = 17117; // "Auto-Paused: Dead"
                    break;
                case 0x20:
                    strPause = 17118; // "Auto-Paused: Target Gone"
                    break;
                case 0x40:
                    strPause = 10014; // "Auto-Paused: Round End"
                    break;
                case 0x80:
                    strPause = 18559; // "Trap Detected"
                    break;
                case 0x100:
                    strPause = 7666; // "Auto-Paused: Scripted"
                    break;
                case 0x200:
                    strPause = 23516; // "Enemy Sighted"
                    break;
                case 0x400:
                    strPause = 26310; // "Spell Cast"
                    break;
                default:
                    strPause = 17324; // "Auto-Paused: Unknown Reason"
                    break;
                }
            } else {
                strPause = 17324; // "Auto-Paused: Unknown Reason"
            }

            CScreenWorld* pWorld = g_pBaldurChitin->GetScreenWorld();
            pWorld->m_autoPauseColor = nameColor;
            pWorld->m_autoPauseId = m_id;
            pWorld->m_autoPauseRef = strPause;
            pWorld->m_autoPauseName = GetNameRef();
        }
    }
}

// 0x71E1B0
void CGameSprite::PlayDialogSound(CGameSprite* pNPC)
{
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        CMessage* message = new CMessagePlaySound(SOUND_SELECT,
            TRUE,
            TRUE,
            m_id,
            pNPC->GetId());
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    } else {
        PlaySound(SOUND_SELECT, TRUE, TRUE, FALSE);
    }
}

// 0x71E9F0
void CGameSprite::AddKnownDivineSpells(const BYTE& nClass)
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 21545
        UTIL_ASSERT(FALSE);
    }

    if ((nClass == CAIOBJECTTYPE_C_CLERIC && m_startTypeAI.IsClassValid(CAIOBJECTTYPE_C_CLERIC) != 0)
        || (nClass == CAIOBJECTTYPE_C_DRUID && m_startTypeAI.IsClassValid(CAIOBJECTTYPE_C_DRUID) != 0)
        || (nClass == CAIOBJECTTYPE_C_PALADIN && m_startTypeAI.IsClassValid(CAIOBJECTTYPE_C_PALADIN) != 0)
        || (nClass == CAIOBJECTTYPE_C_RANGER && m_startTypeAI.IsClassValid(CAIOBJECTTYPE_C_RANGER) != 0)) {
        // NOTE: Original code is slightly different (full of inlined
        // functions).
        UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);
        CGroupedSpellList* pGameSpells = &(g_pBaldurChitin->GetObjectGame()->m_spellsByClass[nClassIndex]);

        // NOTE: Uninline.
        CGameSpriteGroupedSpellList* pSpriteSpells = GetSpells(nClass);

        CResRef resRef;

        UINT nClassLevel = m_derivedStats.GetClassLevel(nClass);
        UINT nMaxSpellLevel = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetMaxSpellLevel(nClass, nClassLevel);

        for (UINT nLevel = 0; nLevel < nMaxSpellLevel; nLevel++) {
            for (UINT nIndex = 0; nIndex < pGameSpells->m_lists[nLevel].m_nCount; nIndex++) {
                // NOTE: Uninline.
                UINT nID = pGameSpells->m_lists[nLevel].Get(nIndex);

                UINT temp;
                if (!pSpriteSpells->m_lists[nLevel].Find(nID, temp)) {
                    // NOTE: Uninline.
                    resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID);

                    CSpell cSpell;
                    cSpell.SetResRef(resRef, TRUE, TRUE);

                    DWORD dwClassFlags;
                    switch (nClass) {
                    case CAIOBJECTTYPE_C_CLERIC:
                    case CAIOBJECTTYPE_C_PALADIN:
                        dwClassFlags = 0x40000000;
                        break;
                    case CAIOBJECTTYPE_C_DRUID:
                    case CAIOBJECTTYPE_C_RANGER:
                        dwClassFlags = 0x80000000;
                        break;
                    default:
                        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                        // __LINE__: 21606
                        UTIL_ASSERT(FALSE);
                    }

                    if (cSpell.pRes != NULL) {
                        // FIXME: Calls `GetNotUsableBy` many times.
                        if ((cSpell.GetNotUsableBy() & dwClassFlags) != 0) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x4) != 0
                            && IcewindMisc::IsGood(this)) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x2) != 0
                            && IcewindMisc::IsEvil(this)) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x8) != 0
                            && !IcewindMisc::IsGood(this)
                            && !IcewindMisc::IsEvil(this)) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x10) != 0
                            && IcewindMisc::IsLawful(this)) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x1) != 0
                            && IcewindMisc::IsChaotic(this)) {
                            continue;
                        }

                        if ((cSpell.GetNotUsableBy() & 0x20) != 0
                            && !IcewindMisc::IsLawful(this)
                            && !IcewindMisc::IsChaotic(this)) {
                            continue;
                        }

                        // NOTE: Uninline.
                        bool bResult = AddKnownSpell(nClass, nLevel, resRef, 0, 0, 0);

                        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                        // __LINE__: 21648
                        UTIL_ASSERT(bResult == true);
                    }
                }
            }
        }
    }
}

// 0x71F170
void CGameSprite::DisplayTextRef(STRREF nameRef, STRREF textRef, COLORREF nameColor, COLORREF textColor)
{
    STR_RES strResName;
    STR_RES strResText;
    CString name;

    if (nameRef >= -7 && nameRef != -1) {
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(-2 - nameRef);

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            name = pSprite->GetName();

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    } else {
        g_pBaldurChitin->GetTlkTable().Fetch(nameRef, strResName);
        name = strResName.szText;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(textRef, strResText);
    if (strResText.cSound.GetRes() != NULL) {
        if (!strResText.cSound.GetLooping()) {
            strResText.cSound.SetFireForget(TRUE);
        }
        strResText.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
        strResText.cSound.Play(GetPos().x, GetPos().y, 0, FALSE);
    }

    strResText.szText.TrimLeft();
    strResText.szText.TrimRight();
    if (strResText.szText != "") {
        g_pBaldurChitin->GetScreenWorld()->DisplayText(name,
            strResText.szText,
            nameColor,
            textColor,
            -1,
            FALSE);
    }
}

// 0x71FBA0
void CGameSprite::GetNumInventoryPersonalSlots(INT& nUsedSlots, INT& nTotalSlots)
{
    nTotalSlots = CScreenInventory::PERSONAL_INVENTORY_SIZE;
    nUsedSlots = 0;

    for (int index = 0; index < nTotalSlots; index++) {
        if (m_equipment.m_items[index + 18] != NULL) {
            nUsedSlots++;
        }
    }
}

// 0x71FC00
void CGameSprite::SetModalState(BYTE modalState, BOOL bUpdateToolbar)
{
    // TODO: Incomplete.
}

// 0x7202E0
BOOL CGameSprite::sub_7202E0()
{
    if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_cutScene) {
        return FALSE;
    } else {
        return (m_curAction.m_internalFlags & 0x1) == 0;
    }
}

// 0x720310
void CGameSprite::CheckSequence(BYTE& sequence)
{
    // TODO: Incomplete.
}

// 0x7204C0
void CGameSprite::sub_7204C0()
{
    CString animationResRef;
    CMemINI* pINI = &(g_pBaldurChitin->GetObjectGame()->m_INISounds);
    CMemINIValue* pValue;

    // NOTE: Uninline.
    m_animation.GetAnimationResRef(animationResRef, CGameAnimationType::RANGE_BODY);

    field_70FB = FALSE;
    field_70FC = FALSE;
    field_70FD = FALSE;
    field_70FE = FALSE;
    field_70FF = FALSE;
    field_7100 = FALSE;
    field_7101 = FALSE;

    pValue = pINI->GetFast(animationResRef, CString("att1"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_70FB = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("att1frame")));

        pValue = pINI->GetFast(animationResRef, CString("att2"));
        if (pValue != NULL && pValue->GetValue() != "") {
            sub_720B50(pValue, pINI->GetFast(animationResRef, CString("att2frame")));
        }

        pValue = pINI->GetFast(animationResRef, CString("att3"));
        if (pValue != NULL && pValue->GetValue() != "") {
            sub_720B50(pValue, pINI->GetFast(animationResRef, CString("att3frame")));
        }

        pValue = pINI->GetFast(animationResRef, CString("att4"));
        if (pValue != NULL && pValue->GetValue() != "") {
            sub_720B50(pValue, pINI->GetFast(animationResRef, CString("att4frame")));
        }
    }

    pValue = pINI->GetFast(animationResRef, CString("btlcry"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_70FC = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("btlcryframe")));
    }

    pValue = pINI->GetFast(animationResRef, CString("damage"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_70FD = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("damageframe")));
    }

    pValue = pINI->GetFast(animationResRef, CString("death"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_70FE = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("deathframe")));
    }

    pValue = pINI->GetFast(animationResRef, CString("fidget"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_70FF = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("fidgetframe")));
    }

    pValue = pINI->GetFast(animationResRef, CString("selected"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_7100 = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("selectedframe")));
    }

    pValue = pINI->GetFast(animationResRef, CString("fall"));
    if (pValue != NULL && pValue->GetValue() != "") {
        field_7101 = TRUE;
        sub_720B50(pValue, pINI->GetFast(animationResRef, CString("fallframe")));
    }
}

// 0x720B50
void CGameSprite::sub_720B50(CMemINIValue* a1, CMemINIValue* a2)
{
    CString v1;
    CString v2;
    CString v3(a1->GetValue());
    CString v4;
    if (a2 != NULL) {
        v4 = a2->GetValue();
    }
    CGameSpriteSoundEntry entry;
    INT pos1;
    INT pos2;

    if (v3[v3.GetLength() - 1] != ',') {
        v3 += ',';
    }

    if (v4 != "" && v4[v4.GetLength() - 1] != ',') {
        v4 += ',';
    }

    if (a1->GetName() == "att1") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_72F0.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "att2") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_730C.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "att3") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_7328.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "att4") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_7344.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "btlcry") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_7360.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "damage") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_737C.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "death") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_7398.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "fidget") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_73B4.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "selected") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_73D0.AddTail(entry);
            }
        }
    }

    if (a1->GetName() == "fall") {
        while (1) {
            v1 = "";
            v2 = "";
            entry.field_0 = "";
            entry.field_4 = 0;

            if (v3.IsEmpty()) {
                break;
            }

            pos1 = v3.FindOneOf(",");
            if (!v4.IsEmpty()) {
                pos2 = v4.FindOneOf(",");
            }

            if (pos1 >= 0) {
                v1 = v3.Left(pos1);
                v3 = v3.Right(v3.GetLength() - pos1 - 1);
                v3.TrimRight();
                v3.TrimLeft();
                v1.TrimRight();
                v1.TrimLeft();
            }

            if (pos2 >= 0) {
                v2 = v4.Left(pos2);
                v4 = v4.Right(v4.GetLength() - pos2 - 1);
                v4.TrimRight();
                v4.TrimLeft();
                v2.TrimRight();
                v2.TrimLeft();
            }

            if (!v1.IsEmpty()) {
                entry.field_0 = v1;
                if (!v2.IsEmpty()) {
                    entry.field_4 = atoi(v2);
                } else {
                    entry.field_4 = 0;
                }
                field_73EC.AddTail(entry);
            }
        }
    }
}

// 0x722530
SHORT CGameSprite::FindItemBags(const CString& sName, LONG number, BOOL checkForIdentified)
{
    CString sMutableName(sName);
    sMutableName.MakeUpper();

    if (number <= 1) {
        number = 1;
    }

    for (SHORT slot = 0; slot < 51; slot++) {
        CItem* pItem = m_equipment.m_items[slot];
        if (pItem != NULL && pItem->GetItemType() == 58) {
            number -= g_pBaldurChitin->GetObjectGame()->FindItemInStore(pItem->GetResRef(),
                CResRef(sMutableName),
                checkForIdentified);
            if (number <= 0) {
                return slot;
            }
        }
    }

    return -1;
}

// 0x722610
SHORT CGameSprite::TakeItemBags(const CString& sName, LONG number, SHORT slotNum)
{
    CString sMutableName(sName);
    sMutableName.MakeUpper();

    SHORT numTaken = 0;
    if (slotNum != -1) {
        CItem* pItem = m_equipment.m_items[slotNum];
        if (pItem != NULL
            && pItem->GetItemType() == 58) {
            numTaken = g_pBaldurChitin->GetObjectGame()->TakeItemFromStore(pItem->GetResRef(),
                CResRef(sName),
                number);
        }
    } else {
        for (SHORT slot = 0; slot < 51; slot++) {
            CItem* pItem = m_equipment.m_items[slot];
            if (pItem != NULL && pItem->GetItemType() == 58) {
                numTaken += g_pBaldurChitin->GetObjectGame()->TakeItemFromStore(pItem->GetResRef(),
                    CResRef(sName),
                    number);
                if (number - numTaken <= 0) {
                    break;
                }
            }
        }
    }
    return numTaken;
}

// Returns `TRUE` if object contains quest items or containers (such as potion
// bags). See STREF #26585.
//
// 0x723350
BOOL CGameSprite::HaveUnexportableItems()
{
    for (INT nSlot = 0; nSlot < 51; nSlot++) {
        CItem* pItem = m_equipment.m_items[nSlot];
        if (pItem != NULL) {
            if (pItem->GetItemType() == 58
                || (pItem->GetFlagsFile() & 0x800) != 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

// 0x723390
void CGameSprite::SetMonkAbilities()
{
    if (GetAIType().IsClassValid(CAIObjectType::C_MONK)) {
        if (m_equipment.m_selectedWeapon == 10) {
            if (m_equipment.m_items[10] != NULL) {
                m_equipment.m_items[10]->Unequip(this, 10, FALSE, FALSE);
            }
        }

        if (m_equipment.m_items[10] != NULL) {
            delete m_equipment.m_items[10];
        }

        // NOTE: Uninline.
        CDerivedStats* pStats = GetActiveStats();

        CItem* pItem;
        switch (pStats->GetClassLevel(CAIOBJECTTYPE_C_MONK)) {
        case 1:
        case 2:
        case 3:
            pItem = new CItem(CResRef("00MFIST1"), 0, 0, 0, 0, 0);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            pItem = new CItem(CResRef("00MFIST2"), 0, 0, 0, 0, 0);
            break;
        case 8:
        case 9:
            pItem = new CItem(CResRef("00MFIST3"), 0, 0, 0, 0, 0);
            break;
        case 10:
        case 11:
            pItem = new CItem(CResRef("00MFIST4"), 0, 0, 0, 0, 0);
            break;
        case 12:
            pItem = new CItem(CResRef("00MFIST5"), 0, 0, 0, 0, 0);
            break;
        case 13:
        case 14:
        case 15:
            pItem = new CItem(CResRef("00MFIST6"), 0, 0, 0, 0, 0);
            break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            pItem = new CItem(CResRef("00MFIST7"), 0, 0, 0, 0, 0);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            pItem = new CItem(CResRef("00MFIST8"), 0, 0, 0, 0, 0);
            break;
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            pItem = new CItem(CResRef("00MFIST9"), 0, 0, 0, 0, 0);
            break;
        default:
            pItem = new CItem(CResRef("00MFIST1"), 0, 0, 0, 0, 0);
            break;
        }

        m_equipment.m_items[10] = pItem;

        if (m_equipment.m_selectedWeapon == 10) {
            m_equipment.m_items[10]->Equip(this, 10, FALSE);
        }
    }
}

// 0x7238A0
LONG CGameSprite::GetLevel()
{
    return m_derivedStats.GetAtOffset(STAT_CLASSLEVELSUM);
}

// 0x723B20
void CGameSpriteLastUpdate::Initialize(BOOL bFullUpdateRequired)
{
    // TODO: Incomplete.
}

// 0x723BF0
void CGameSprite::sub_723BF0(BOOLEAN a1, BOOLEAN a2)
{
    // TODO: Incomplete.
}

// 0x723CC0
INT CGameSprite::GetAC()
{
    // TODO: Incomplete.

    return 0;
}

// 0x723F60
INT CGameSprite::sub_723F60()
{
    // TODO: Incomplete.

    return 0;
}

// 0x72DE60
void CGameSprite::sub_72DE60()
{
    // TODO: Incomplete.
}

// 0x71E760
void CGameSprite::sub_71E760(CDerivedStats& DStats, int a2)
{
    // TODO: Incomplete.
}

// 0x71F6E0
int CGameSprite::sub_71F6E0()
{
    int v1;

    switch (m_typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
    case CAIOBJECTTYPE_C_FIGHTER:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        v1 = 10;
        break;
    case CAIOBJECTTYPE_C_BARD:
    case CAIOBJECTTYPE_C_MONK:
    case CAIOBJECTTYPE_C_ROGUE:
        v1 = 15;
        break;
    default:
        v1 = 5;
        break;
    }

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_ELF:
        v1 += 20;
        break;
    case CAIOBJECTTYPE_R_DWARF:
        v1 += 10;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        v1 += 5;
        break;
    }

    if (m_nModalState == 2) {
        v1 = 100;
    }

    return v1;
}

// 0x71F760
const CString& CGameSprite::GetName()
{
    if (m_baseStats.m_name != -1) {
        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_name, strRes);
        m_sName = strRes.szText;
    }

    return m_sName;
}

// 0x71F820
STRREF CGameSprite::GetNameRef()
{
    STRREF strName = m_baseStats.m_name;

    if (strName == -1) {
        SHORT nSlot = g_pBaldurChitin->GetObjectGame()->GetCharacterSlotFromId(m_id);
        if (nSlot < 0) {
            nSlot = 0;
        }

        strName = -2 - nSlot;
    }

    return strName;
}

// 0x728270
void CGameSprite::PlaySound(const CResRef& res)
{
    CSound cSound;

    CMessage* message = new CMessagePlaySoundRef(res, m_id, m_id);
    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

    cSound.SetResRef(res, TRUE, TRUE);

    if (cSound.m_nLooping == 0) {
        cSound.SetFireForget(TRUE);
    }

    cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
    cSound.Play(GetPos().x, GetPos().y, 0, FALSE);
}

// 0x728460
BOOL CGameSprite::Orderable(BOOL bIgnoreControl)
{
    if (!bIgnoreControl && !InControl()) {
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_DEAD) != 0) {
        return FALSE;
    }

    if (m_nUnselectableCounter > 0) {
        return FALSE;
    }

    if (m_typeAI.GetEnemyAlly() > CAIObjectType::EA_CONTROLCUTOFF) {
        return FALSE;
    }

    if (m_moraleFailure) {
        return FALSE;
    }

    if ((m_derivedStats.m_generalState & STATE_STONE_DEATH) != 0
        || (m_derivedStats.m_generalState & STATE_FROZEN_DEATH) != 0
        || (m_derivedStats.m_generalState & STATE_HELPLESS) != 0
        || (m_derivedStats.m_generalState & STATE_STUNNED) != 0
        || (m_derivedStats.m_generalState & STATE_PANIC) != 0
        || ((m_derivedStats.m_generalState & STATE_BERSERK) != 0
            && m_berserkActive)
        || m_derivedStats.m_spellStates[SPLSTATE_ANIMAL_RAGE]
        || (m_derivedStats.m_generalState & STATE_SLEEPING) != 0
        || ((m_derivedStats.m_generalState & STATE_CHARMED) != 0
            && m_typeAI.GetEnemyAlly() != CAIObjectType::EA_0x847C3A
            && m_typeAI.GetEnemyAlly() != CAIObjectType::EA_CONTROLLED)
        || (m_derivedStats.m_generalState & STATE_FEEBLEMINDED) != 0
        || (m_derivedStats.m_generalState & STATE_CONFUSED) != 0) {
        return FALSE;
    }

    if (g_pBaldurChitin->GetObjectGame()->m_nTimeStop != 0
        && g_pBaldurChitin->GetObjectGame()->m_nTimeStopCaster != m_id) {
        return FALSE;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_179]) {
        return FALSE;
    }

    return TRUE;
}

// 0x728560
BOOL CGameSprite::Animate()
{
    return (~m_derivedStats.m_generalState >> 11) & 0x1;
}

// 0x728570
DWORD CGameSprite::GetSpecialization()
{
    return m_baseStats.m_specialization;
}

// 0x728BC0
void CGameSprite::ResolveInstants(BOOL dropNonInstants)
{
    if (m_moveToFrontQueue > 0) {
        m_moveToFrontQueue--;
        MoveToFront();
    }

    if (m_moveToBackQueue > 0) {
        m_moveToBackQueue--;
        MoveToBack();
    }

    if (m_castCounter > -1) {
        m_castCounter++;
        if (m_castCounter >= 100 && !m_bInCasting) {
            m_castCounter = -1;
        }
    }

    if (m_attackFrame > -2) {
        m_attackFrame++;
        if (m_attackFrame >= 100) {
            m_attackFrame = -2;
        }
    }

    if (((m_derivedStats.m_generalState & STATE_DEAD) == 0
            && (m_derivedStats.m_generalState & STATE_SLEEPING) == 0)
        || ((g_pChitin->cNetwork.GetSessionOpen() != TRUE || m_curAction.GetActionID() != CAIACTION_LEAVEAREALUA)
            && g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_lInstantActions.Find(m_curAction.GetActionID()) != NULL)) {
        m_typeAI.SetInstance(m_id);
        m_liveTypeAI.SetInstance(m_id);
        m_startTypeAI.SetInstance(m_id);

        if (Orderable(FALSE) && m_curAction.GetActionID() != 0) {
            g_pBaldurChitin->GetScreenWorld()->m_bored = FALSE;
            g_pBaldurChitin->GetScreenWorld()->m_boredCount = 0;
        }

        SHORT actionReturn = ExecuteAction();
        if (m_curAction.GetActionID() != CAIACTION_ATTACK) {
            m_lastActionID = m_curAction.GetActionID();
        }

        if (actionReturn == ACTION_DONE
            || actionReturn == ACTION_ERROR
            || actionReturn == ACTION_STOPPED) {
            SetCurrAction(GetNextAction(m_aiDoAction));
            if (m_curAction.GetActionID() == CAIAction::NO_ACTION) {
                m_curResponseNum = -1;
                m_curResponseSetNum = -1;
                m_curScriptNum = -1;
            }
        } else if (m_interrupt
            && actionReturn == ACTION_INTERRUPTABLE
            && (m_baseStats.m_flags & 0x80000000) == 0) {
            if (m_pPath != NULL) {
                CMessage* message = new CMessageDropPath(m_id, m_id);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
            }
            m_actionCount++;
            SetCurrAction(GetNextAction(m_aiDoAction));
            m_interrupt = FALSE;
        } else {
            m_actionCount++;
        }

        if (dropNonInstants
            && !m_sequenceTest
            && m_noActionCount > READY_COUNT
            && m_nSequence != SEQ_TWITCH
            && m_nSequence != SEQ_DIE
            && m_nSequence != SEQ_SLEEP
            && m_nSequence != SEQ_DAMAGE) {
            if (m_pPath != NULL || GetVertListType() == LIST_FLIGHT) {
                if (m_nSequence != SEQ_WALK) {
                    CMessage* message = new CMessageSetSequence(SEQ_WALK, m_id, m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }
            } else {
                if (m_nSequence != GetIdleSequence()) {
                    CMessage* message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()), m_id, m_id);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }
            }
        }

        field_5582 = 0;
        field_9D14 = 0;
        field_9D15 = 0;
    }
}

// 0x72B670
void CGameSprite::ResolvePausedAction(const CAIAction* curAction, POSITION pos)
{
    CGameObject* pObject;
    BYTE rc;

    if (m_groupMove) {
        return;
    }

    ResolveTargetPoint(curAction, pos);

    if (curAction->GetActionID() == 23
        && m_targetId != CGameObjectArray::INVALID_INDEX) {
        if (m_bSelected && Orderable(FALSE)) {
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc != CGameObjectArray::SUCCESS) {
                return;
            }

            if (pObject->GetObjectType() == TYPE_SPRITE) {
                static_cast<CGameSprite*>(pObject)->m_marker.SetType(CMarker::ELLIPSE);
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
        m_targetId = CGameObjectArray::INVALID_INDEX;
    } else if (curAction->GetActionID() == 27
        && m_targetId != CGameObjectArray::INVALID_INDEX) {
        if (m_bSelected && Orderable(FALSE)) {
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc != CGameObjectArray::SUCCESS) {
                return;
            }

            if (pObject->GetObjectType() == TYPE_SPRITE) {
                static_cast<CGameSprite*>(pObject)->m_marker.SetType(CMarker::ELLIPSE);
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }
}

// NOTE: Assembly is tail-call optimized.
//
// 0x72B870
void CGameSprite::ResolveTargetPoint(const CAIAction* curAction, POSITION pos)
{
    CAIAction* workAction;

    switch (curAction->GetActionID()) {
    case 23:
    case 88:
        if (pos != NULL) {
            workAction = m_queuedActions.GetNext(pos);
            switch (workAction->GetActionID()) {
            case 23:
            case 88:
                ResolveTargetPoint(workAction, pos);
                break;
            default:
                if (!m_groupMove) {
                    m_targetPoint = curAction->m_dest;
                }
                break;
            }
        } else {
            m_targetPoint = curAction->m_dest;
        }
        break;
    case 27:
        m_targetPoint = curAction->m_dest;
        break;
    case 83:
    case 84:
        if (pos != NULL) {
            workAction = m_queuedActions.GetNext(pos);
            ResolveTargetPoint(workAction, pos);
        } else {
            m_targetPoint.x = -1;
            m_targetPoint.y = -1;
        }
        break;
    default:
        m_targetPoint.x = -1;
        m_targetPoint.y = -1;
        break;
    }
}

// 0x72DE60
BOOL CGameSprite::ProcessEffectList()
{
    // TODO: Incomplete.

    // NOTE: This functions is huge. The next function call is necessary to
    // move on with character editor.
    HandleEffects();

    return FALSE;
}

// 0x733290
void CGameSprite::ClearStoredPaths()
{
    POSITION pos = m_pPathTemp.GetHeadPosition();
    while (pos != NULL) {
        int* node = m_pPathTemp.GetNext(pos);
        delete node;
    }

    m_pPathTemp.RemoveAll();
    m_nPathTemp.RemoveAll();
}

// 0x7332D0
void CGameSprite::ClearDialogActions()
{
    SHORT actionID = m_curAction.m_actionID;
    if (actionID == 8
        || actionID == 137
        || actionID == 139
        || actionID == 198) {
        SetCurrAction(CAIAction::NULL_ACTION);

        CMessageDropPath* pMessage = new CMessageDropPath(m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }
}

// 0x7337D0
void CGameSprite::ClearAI(BOOLEAN bSetSequence)
{
    ClearActions(FALSE);
    ClearTriggers();
    SetCurrAction(CAIAction::NULL_ACTION);

    if (bSetSequence) {
        if (m_nSequence != GetIdleSequence()
            && m_nSequence != SEQ_TWITCH
            && m_nSequence != SEQ_SLEEP
            && m_nSequence != SEQ_DIE) {
            if (GetVertListType() != LIST_FLIGHT) {
                CMessage* pMessage = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()),
                    m_id,
                    m_id);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
            }
        }
    }
}

// 0x734550
BOOL CGameSprite::HandleEffects()
{
    BOOL bRetry;
    BOOL v1;
    BOOL v2;

    do {
        bRetry = FALSE;

        m_derivedStats.Reload(this, &m_baseStats, &m_spells, &m_domainSpells);
        m_derivedStats.m_nTurnUndeadLevel = GetTurnUndeadLevel();
        m_derivedStats.m_nBackstabDamageMultiplier = GetBackstabDamageMultiplier();
        m_derivedStats.m_nLayOnHandsAmount = GetLayOnHandsAmount();

        ResetAIType();

        m_activeImprisonment = TRUE;

        // TODO: Incomplete.
        v1 = FALSE;
        v2 = FALSE;
    } while (bRetry);

    return v1 && v2;
}

// 0x7349A0
void CGameSprite::FeedBack(WORD nFeedBackId, LONG a3, LONG a4, LONG a5, LONG a6, LONG a7, LONG a8)
{
    COLORREF rgbNameColor = CVidPalette::RANGE_COLORS[m_baseStats.m_colors[CVIDPALETTE_RANGE_MAIN_CLOTH]];
    CString v1;
    CString v2;

    switch (nFeedBackId) {
    case FEEDBACK_BACKSTAB:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            STRREF strBackstabDamage;
            switch (m_derivedStats.m_nBackstabDamageMultiplier) {
            case 1:
                strBackstabDamage = 32110; // "Backstab Normal Damage"
                break;
            case 2:
                strBackstabDamage = 16471; // "Backstab Double Damage"
                break;
            case 3:
                strBackstabDamage = 16472; // "Backstab Triple Damage"
                break;
            case 4:
                strBackstabDamage = 16473; // "Backstab Quadruple Damage"
                break;
            case 5:
                strBackstabDamage = 16474; // "Backstab Quintuple Damage"
                break;
            case 6:
                strBackstabDamage = 16475; // "Backstab Sextuple Damage"
                break;
            default:
                strBackstabDamage = -1;
                break;
            }

            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                strBackstabDamage,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_CRITICALHIT:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            if (a3 != 0) {
                STR_RES strRes;
                CString sText;
                g_pBaldurChitin->GetTlkTable().Fetch(16462, strRes); // "Critical Hit!"
                sText.Format("%s (%+d)", strRes.szText, a3);
                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            } else {
                g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                    16462, // "Critical Hit!"
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_CRITICALMISS:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                16463, // "Critical Miss!"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_TOHIT:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x1) != 0) {
            CString sText1;
            CString sText2;
            sText2.Format("%d ", a8);

            if (a7 > 0) {
                STR_RES strRes;
                g_pBaldurChitin->GetTlkTable().Fetch(733, strRes); // "Off Hand"
                sText2 += "(" + strRes.szText + ")";
            }

            if (a5 > 0) {
                sText1.Format(": %d + %d = %d", a3, a5, a3 + a5);
            } else if (a5 < 0) {
                sText1.Format(": %d - %d = %d", a3, -a5, a3 + a5);
            } else {
                sText1.Format(": %d", a3);
            }

            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(14643, strRes); // "Attack Roll "

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes.szText != "") {
                sText1 = strRes.szText + " " + sText2 + sText1;
            }

            if (a3 == 1) {
                g_pBaldurChitin->GetTlkTable().Fetch(16463, strRes); // "Critical Miss!"
            } else {
                if (a4 != 0) {
                    g_pBaldurChitin->GetTlkTable().Fetch(16460, strRes); // "Hit"
                } else {
                    g_pBaldurChitin->GetTlkTable().Fetch(16461, strRes); // "Miss"
                }
            }

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes.szText != "") {
                sText1 += " : " + strRes.szText;
            }

            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText1,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_SPELL:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x4) != 0) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(16464, strRes); // "Casts"

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes.szText != "") {
                v1 = strRes.szText;
            }

            g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }
        }
        break;
    case FEEDBACK_ATTACKS:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x4) != 0) {
            STR_RES strRes1;
            g_pBaldurChitin->GetTlkTable().Fetch(16465, strRes1); // "Attacks"

            if (strRes1.cSound.GetRes() != NULL) {
                if (!strRes1.cSound.GetLooping()) {
                    strRes1.cSound.SetFireForget(TRUE);
                }
                strRes1.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes1.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes1.szText != "") {
                v1 = strRes1.szText;
            }

            CString sName;
            STR_RES strRes2;
            if (a6 >= -7 && a6 != -1) {
                LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(-2 - a6);

                CGameSprite* pSprite;

                BYTE rc;
                do {
                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        reinterpret_cast<CGameObject**>(&pSprite),
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc == CGameObjectArray::SUCCESS) {
                    sName = pSprite->GetName();
                    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            } else {
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes2);
                sName = strRes2.szText;
            }

            if (sName != "") {
                v1 += " " + sName;
            }

            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                v1,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_MODAL:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x4) != 0) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes.szText != "") {
                v1 = strRes.szText;
            }

            if (a3 != 0) {
                g_pBaldurChitin->GetTlkTable().Fetch(16469, strRes); // "On"
            } else {
                g_pBaldurChitin->GetTlkTable().Fetch(16470, strRes); // "Off"
            }

            if (strRes.cSound.GetRes() != NULL) {
                if (!strRes.cSound.GetLooping()) {
                    strRes.cSound.SetFireForget(TRUE);
                }
                strRes.cSound.SetChannel(14, reinterpret_cast<DWORD>(m_pArea));
                strRes.cSound.Play(m_pos.x, m_pos.y, 0, FALSE);
            }

            if (strRes.szText != "") {
                v1 += strRes.szText;
            }

            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                v1,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_LOCKPICKSUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                16517, // "Lock Pick Succeeded"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_LOCKPICKFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                16518, // "Lock Pick Failed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TRAPDISARMED:
        PlaySound(CResRef("ACT_09"));
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                16520, // "Trap Disarmed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TRAPDETECTED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                16519, // "Trap Detected"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_ITEMCURSED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                16304, // "Item Cursed!"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_HIDEFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                17120, // "Hide Failed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TOOHEAVY_SLOWED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (m_bPlayedEncumberedSlowed || a3 == 1) {
                g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                    19503, // "Encumbered: Slowed"
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_TOOHEAVY_STOPPED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (m_bPlayedEncumberedStopped || a3 == 1) {
                g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                    19504, // "Encumbered: Can not move"
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_16:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                a6,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_HIDESUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                19944, // "Hide Succeeded"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_MORALEFAILURE_PANIC:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                20568, // "Morale Failure: Panic"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_MORALEFAILURE_RUN:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                20569, // "Morale Failure: Running"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_MORALEFAILURE_BERSERK:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                20570, // "Morale Failure: Berserk"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_LEVELUP:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            17119, //  "Level Up"
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_SPELLFAILED_INDOORS:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            9744, // "Spell Failed: Indoors"
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_LEAVING_SHADOWS:
        PlaySound(CResRef("ACT_07"));
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                4188, // "Leaving Shadows"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BASHDOORSUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                9915, // "You have successfully forced the door open!"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BASHDOORFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                9913, // "You have failed to force the door."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BASHCHESTSUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                9916, // "You have successfully forced the lock open!"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BASHCHESTFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                9914, // "You have failed to force the lock."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BACKSTAB_UNUSABLE_WEAPON:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            DisplayTextRef(GetNameRef(),
                10013, // "Your weapon is unsuitable for backstab."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_PICKPOCKETFAILED_ARMOR:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                10067, // "Pick Pocket Disabled Due To Armor"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_PICKPOCKETFAILED_HOSTILE:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                10068, // "Cannot pick pocket hostile creatures"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_PICKPOCKETFAILED_SKILL:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                10069, // "Pick Pocket Failed"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_PICKPOCKETFAILED_NOITEMS:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                18297, // "Pick Pocket Succeeded -- Target Had Nothing to Steal"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_PICKPOCKETFAILED_INVENTORYFULL:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                10071, // "Inventory Full"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_PICKPOCKETSUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                10072, // "Pick Pocket Succeeded"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_GAINEDSPECIALABILITY:
        if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCreateChar) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
            g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_SPECIALABILITY, strRes.szText);
            g_pBaldurChitin->GetTlkTable().Fetch(10514, strRes); // "Gained Special Ability: <SPECIALABILITYNAME>"
            g_pBaldurChitin->m_pEngineWorld->DisplayText(GetName(),
                strRes.szText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                FALSE);
            if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCharacter) {
                g_pBaldurChitin->GetActiveEngine()->PlayGUISound(CResRef("GAM_11"));
            }
        }
        break;
    case FEEDBACK_IMMUNE_TO_WEAPON:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                11025, // "Weapon Ineffective."
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_CHARACTER_CONTROL_SEIZURE:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            20679, // "Timeout: Server Assumed Control Of Character"
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_TRAPDISARMEDFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                1608, // "Trap Not Disarmed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_CRITICALHITAVOIDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x1) != 0) {
            CString sText1;
            CString sText2;
            STR_RES strRes;
            sText2.Format("%d ", a8);

            if (a7 > 0) {
                g_pBaldurChitin->GetTlkTable().Fetch(733, strRes); // "Off Hand"
                sText2 += "(" + strRes.szText + ")";
            }

            if (a5 > 0) {
                sText1.Format(": %d + %d = %d", a3, a5, a3 + a5);
            } else if (a5 < 0) {
                sText1.Format(": %d - %d = %d", a3, -a5, a3 + a5);
            } else {
                sText1.Format(": %d", a3);
            }

            g_pBaldurChitin->GetTlkTable().Fetch(39874, strRes); // "Critical Threat Roll"

            if (strRes.szText != "") {
                sText1 = strRes.szText + " " + sText2 + sText1;
            }

            if (a4 != 0) {
                g_pBaldurChitin->GetTlkTable().Fetch(16462, strRes); // "Critical Hit!"
            } else {
                g_pBaldurChitin->GetTlkTable().Fetch(33752, strRes); // "Failed!"
            }

            if (strRes.szText != "") {
                sText1 += " : " + strRes.szText;
            }

            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText1,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);

            if (a4 != 0) {
                PlaySound(16, TRUE, FALSE, FALSE);
            }
        }
        break;
    case FEEDBACK_AURA_CLEANSED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                23797, // "Aura Cleansed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_ITEM_DROPPED_FULL:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                10959, // "Inventory Full: The item has been dropped."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_LOCK_UNPICKABLE:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                23169, // "The mechanism that operates this does not have a conventional lock, and may be warded against simple spells."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TOOMANYSUMMONED:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            18955, // "Summoning Limit Reached"
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_SILENCED:
        DisplayTextRef(GetNameRef(),
            21298, // "Bard Song Silenced"
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_CRIPPLINGSTRIKESUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            STR_RES strRes;
            CString sText;
            g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
            sText.Format(strRes.szText, a3);
            if (sub_763150(CGAMESPRITE_FEAT_CRIPPLING_STRIKE)) {
                g_pBaldurChitin->GetTlkTable().Fetch(25070, strRes); // " with Crippling Strike (-1 Str)"
                sText.Format(strRes.szText, a3);
            }
            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_SNEAK_UNUSABLE_WEAPON:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                24899, // "Weapon is unsuitable for sneak attack"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_EFFECTSEVADED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            STRREF strEvasion;
            if (a6 != -1) {
                strEvasion = 25368; // "Evades effects from <RESOURCE>"

                STR_RES strRes;
                CString sText;
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
                g_pBaldurChitin->GetTlkTable().SetToken(CString("RESOURCE"), strRes.szText);
            } else {
                strEvasion = 25369; // "Evades effects"
            }

            STR_RES strRes;
            CString sText;
            g_pBaldurChitin->GetTlkTable().Fetch(strEvasion, strRes);
            sText = strRes.szText;
            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_SPELLFAILED_DISRUPTED:
        DisplayTextRef(GetNameRef(),
            14796, // "Spell Disrupted"
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_GAINEDBARDSONG:
        if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCreateChar) {
            STR_RES strRes;
            CString sText;
            g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
            g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_SPECIALABILITY, strRes.szText);
            g_pBaldurChitin->GetTlkTable().Fetch(26320, strRes); // "Gained Bard Song: <SPECIALABILITYNAME>"
            g_pBaldurChitin->m_pEngineWorld->DisplayText(GetName(),
                sText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                FALSE);
        }
        if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCharacter) {
            g_pBaldurChitin->GetActiveEngine()->PlayGUISound(CResRef("GAM_11"));
        }
        break;
    case FEEDBACK_STATICCHARGEEND:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                26518, // "Static charge buildup dissipates harmlessly."
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_IMMUNE_TO_RESOURCE:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            if (a6 != -1) {
                STR_RES strRes;
                CString sText;
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
                g_pBaldurChitin->GetTlkTable().SetToken(CString("RESOURCE"), strRes.szText);
                g_pBaldurChitin->GetTlkTable().Fetch(26818, strRes); // "Unaffected by effects from <RESOURCE>"
                sText.Format("%s (%+d)", strRes.szText, a3);
                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_LEAVEFAILED_INVENTORY:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            26826, // "Cannot leave area while remote player is in inventory screen."
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_BACKSTAB_AVOIDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                121, // "The backstab seems to have failed."
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_SPELLFAILED_CASTFAILURE:
        DisplayTextRef(GetNameRef(),
            10453, // "Casting Failure"
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_62:
        DisplayTextRef(GetNameRef(),
            18352, // "Blinks out of existence and attack fails"
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_63:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                18353, // "Blinks out of existence and avoids an attack"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_CRIPPLINGSTRIKEFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                18759, // "The crippling strike seems to have failed."
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_USEMAGICDEVICEFAILED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                24197, // "Use Magic Device Failed"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_USEMAGICDEVICESUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                24198, // "Use Magic Device Succeeded"
                rgbNameColor,
                RGB(215, 215, 190));
        }
    case FEEDBACK_SEARCHSTART:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                25085, // "Searching..."
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_SEARCHEND:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                25090, // "Stopped Searching"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TURNUNDEADEND:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                25136, // "Stopped Turning Undead"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_BATTLESONGSTART:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (a6 != 0) {
                STR_RES strRes1;
                STR_RES strRes2;
                CString sText;

                g_pBaldurChitin->GetTlkTable().Fetch(25138, strRes1); // "Singing Battlesong"
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes2);
                sText.Format("%s: %s", strRes1.szText, strRes2.szText);

                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_BATTLESONGEND:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                25141, // "Stopped Singing Battlesong"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_ARTERIALSTRIKESUCCEEDED:
        DisplayTextRef(GetNameRef(),
            37673, // "Arterial Strike feat was used successfully to cause a bleeding wound."
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_HAMSTRINGSUCCEEDED:
        DisplayTextRef(GetNameRef(),
            37675, // "Hamstring feat was used successfully to hinder your opponent's movement by 50%."
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_HEROICINSPIRATION:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            DisplayTextRef(GetNameRef(),
                24196, // "Heroic Inspiration"
                rgbNameColor,
                RGB(215, 215, 190));
        }
        break;
    case FEEDBACK_TARGETCONCEALED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x1) != 0) {
            STR_RES strRes;
            CString sText;
            g_pBaldurChitin->GetTlkTable().Fetch(37668, strRes); // "Missed <TARGETNAME> due to concealment."
            sText.Format("%s (%+d)", strRes.szText, a3);
            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_UNCANNYDODGESUCCEEDED:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                39308, // "Uncanny Dodge prevented flank attack."
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_ROLL:
        if (m_bRollFeedbackEnabled == -1) {
            if (GetPrivateProfileIntA("Program Options", "EnableRollFeedback", 0, g_pBaldurChitin->GetIniFileName()) != 0) {
                m_bRollFeedbackEnabled = 1;
            } else {
                m_bRollFeedbackEnabled = 0;
            }
        }

        if (m_bRollFeedbackEnabled != 0) {
            if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
                STR_RES strRes;
                CString sText;
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
                sText.Format(strRes.szText, a3, a4, a5, a7, a8);
                g_pBaldurChitin->m_pEngineWorld->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    FALSE);
                if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCharacter) {
                    g_pBaldurChitin->GetActiveEngine()->PlayGUISound(CResRef("GAM_11"));
                }
            }
        }
        break;
    case FEEDBACK_SPELLFAILURE_CONCENTRATION:
        DisplayTextRef(GetNameRef(),
            39265, // Spell disrupted because caster failed concentration check required due to of nearness of enemies."
            rgbNameColor,
            RGB(215, 215, 190));
        break;
    case FEEDBACK_SPONTANEOUSCASTING:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (a6 != 0) {
                STR_RES strRes1;
                STR_RES strRes2;
                CString sText;

                g_pBaldurChitin->GetTlkTable().Fetch(39742, strRes1); // "Spontaneous Casting"
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes2);
                sText.Format("%s: %s", strRes1.szText, strRes2.szText);

                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_TOGGLEFEAT:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (a6 != 0) {
                STR_RES strRes1;
                STR_RES strRes2;
                CString sText;

                // 39853: "Stopped Using Feat"
                // 39823: "Using Feat"
                g_pBaldurChitin->GetTlkTable().Fetch(a3 == 1 ? 39853 : 39823, strRes1);
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes2);

                if (a4 > 0) {
                    sText.Format("%s: %s %d", strRes1.szText, strRes2.szText, a4);
                } else {
                    sText.Format("%s: %s", strRes1.szText, strRes2.szText);
                }

                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_CLEAVE:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x4) != 0) {
            STR_RES strRes;
            CString sText;
            g_pBaldurChitin->GetTlkTable().Fetch(39846, strRes); // "Cleave feat adds another level %d attack."
            sText.Format("%s (%+d)", strRes.szText, a3);
            g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                sText,
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_LINGERINGSONG:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (a6 != 0) {
                STR_RES strRes1;
                STR_RES strRes2;
                CString sText;

                g_pBaldurChitin->GetTlkTable().Fetch(39881, strRes1); // "Using Feat: Lingering Song"
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes2);
                sText.Format("%s: %s", strRes1.szText, strRes2.szText);

                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_89:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            if (a6 != 0) {
                STR_RES strRes;
                CString sText(" ");
                g_pBaldurChitin->GetTlkTable().Fetch(a6, strRes);
                sText.Format("%s", strRes.szText);
                g_pBaldurChitin->GetBaldurMessage()->DisplayText(GetName(),
                    sText,
                    rgbNameColor,
                    RGB(215, 215, 190),
                    -1,
                    m_id,
                    m_id);
            }
        }
        break;
    case FEEDBACK_CALLLIGHTNINGEND:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x2) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                41008, // "Call Lightning buildup dissipates harmlessly"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_MAGICALWEAPONINUSE:
        if ((g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x10) != 0) {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
                10141, // "Magical weapon in use"
                rgbNameColor,
                RGB(215, 215, 190),
                -1,
                m_id,
                m_id);
        }
        break;
    case FEEDBACK_LEAVEFAILED_LEVELUP:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            41398, // "Cannot leave area while remote player is in the level up screen."
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    case FEEDBACK_LEAVEFAILED_STORE:
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(GetNameRef(),
            41400, // "Cannot leave area while remote player is in the store screen."
            rgbNameColor,
            RGB(215, 215, 190),
            -1,
            m_id,
            m_id);
        break;
    }
}

// 0x737910
BOOLEAN CGameSprite::sub_737910(BOOL a1)
{
    if (!a1
        && m_equipment.m_items[m_equipment.m_selectedWeapon] != NULL
        && (m_equipment.m_items[m_equipment.m_selectedWeapon]->GetFlagsFile() & 0x10) != 0) {
        m_equipment.m_items[m_equipment.m_selectedWeapon]->m_flags |= 0x1;
        return FALSE;
    }

    if ((m_equipment.m_selectedWeapon == 43
            || m_equipment.m_selectedWeapon == 45
            || m_equipment.m_selectedWeapon == 47
            || m_equipment.m_selectedWeapon == 49)
        && m_equipment.m_items[m_equipment.m_selectedWeapon + 1] != NULL
        && (m_equipment.m_items[m_equipment.m_selectedWeapon + 1]->GetFlagsFile() & 0x10) != 0) {
        m_equipment.m_items[m_equipment.m_selectedWeapon + 1]->m_flags |= 0x1;
        return FALSE;
    }

    return TRUE;
}

// 0x73B740
SHORT CGameSprite::GetCriticalHitBonus()
{
    SHORT nCriticalHitBonus = m_derivedStats.m_nCriticalHitBonus;
    if (sub_763150(CGAMESPRITE_FEAT_IMPROVED_CRITICAL)) {
        nCriticalHitBonus++;
    }
    return nCriticalHitBonus;
}

// 0x73C6A0
SHORT CGameSprite::sub_73C6A0(CGameSprite* target, CItem* curWeapon, const ITEM_ABILITY* curAttack)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9840
    UTIL_ASSERT(target != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9841
    UTIL_ASSERT(curWeapon != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9842
    UTIL_ASSERT(curAttack != NULL);

    SHORT mod = 0;

    switch (curAttack->damageType) {
    case 1:
        mod += target->GetDerivedStats()->m_nACPiercingMod;
        break;
    case 2:
        mod += target->GetDerivedStats()->m_nACCrushingMod;
        break;
    case 3:
        mod += target->GetDerivedStats()->m_nACSlashingMod;
        break;
    case 4:
        mod += target->GetDerivedStats()->m_nACMissileMod;
        mod += target->GetDerivedStats()->m_nACPiercingMod;
        break;
    case 5:
        mod += target->GetDerivedStats()->m_nACCrushingMod;
        break;
    case 6:
        mod += max(target->GetDerivedStats()->m_nACPiercingMod, target->GetDerivedStats()->m_nACCrushingMod);
        break;
    case 7:
        mod += max(target->GetDerivedStats()->m_nACPiercingMod, target->GetDerivedStats()->m_nACSlashingMod);
        break;
    case 8:
        mod += max(target->GetDerivedStats()->m_nACCrushingMod, target->GetDerivedStats()->m_nACSlashingMod);
        break;
    case 9:
        mod += target->GetDerivedStats()->m_nACMissileMod;
        mod += target->GetDerivedStats()->m_nACCrushingMod;
        break;
    }

    return mod;
}

// 0x73C7E0
SHORT CGameSprite::sub_73C7E0()
{
    SHORT mod = 0;

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_DWARF
        && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_DWARF_GRAY) {
        if (m_pArea != NULL
            && (m_pArea->GetHeader()->m_areaType & 0x1) != 0
            && (m_pArea->GetHeader()->m_areaType & 0x2) != 0
            && (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDay()
                || g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDawn())) {
            mod -= 2;
        }
    }

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_ELF
        && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_ELF_DROW) {
        if (m_pArea != NULL
            && (m_pArea->GetHeader()->m_areaType & 0x1) != 0
            && (m_pArea->GetHeader()->m_areaType & 0x2) != 0
            && (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDay()
                || g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDawn())) {
            mod -= 1;
        }
    }

    return mod;
}

// 0x73C8C0
SHORT CGameSprite::sub_73C8C0(CGameSprite* target)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9925
    UTIL_ASSERT(target != NULL);

    SHORT mod = 0;

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_DWARF) {
        if (m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_DWARF_GOLD
            && IcewindMisc::IsAberration(target) == TRUE) {
            mod++;
        } else {
            switch (target->m_typeAI.GetRace()) {
            case CAIOBJECTTYPE_R_HOBGOBLIN:
            case CAIOBJECTTYPE_R_GOBLIN:
            case CAIOBJECTTYPE_R_ORC:
            case CAIOBJECTTYPE_R_BUGBEAR:
                mod++;
                break;
            }
        }
    }

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_GNOME) {
        switch (target->m_typeAI.GetRace()) {
        case CAIOBJECTTYPE_R_HOBGOBLIN:
        case CAIOBJECTTYPE_R_KOBOLD:
        case CAIOBJECTTYPE_R_GOBLIN:
        case CAIOBJECTTYPE_R_BUGBEAR:
            mod++;
            break;
        }
    }

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_GIANT
        || m_typeAI.GetRace() == CAIOBJECTTYPE_R_OGRE) {
        if ((target->m_typeAI.GetRace() == CAIOBJECTTYPE_R_GNOME
                && target->m_typeAI.m_nSubRace != CAIOBJECTTYPE_SUBRACE_DWARF_GOLD)
            || target->m_typeAI.GetRace() == CAIOBJECTTYPE_R_DWARF) {
            mod -= 4;
        }
    }

    return mod;
}

// 0x73CA20
SHORT CGameSprite::sub_73CA20(CItem* curWeapon, const ITEM_ABILITY* curAttack)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9988
    UTIL_ASSERT(curWeapon != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 9989
    UTIL_ASSERT(curAttack != NULL);

    SHORT mod = 0;

    if (m_typeAI.GetRace() == CAIOBJECTTYPE_R_HALFLING
        && curAttack->type == 2) {
        switch (curWeapon->GetItemType()) {
        case 14:
        case 16:
        case 21:
        case 24:
        case 25:
        case 29:
            mod++;
            break;
        }
    }

    return mod;
}

// 0x73CAD0
SHORT CGameSprite::sub_73CAD0()
{
    return 0;
}

// 0x73CAE0
SHORT CGameSprite::sub_73CAE0(CItem* curWeapon, const ITEM_ABILITY* curAttack)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 10073
    UTIL_ASSERT(curAttack != NULL);

    return 0;
}

// 0x73CB10
SHORT CGameSprite::sub_73CB10(CItem* curWeapon, const ITEM_ABILITY* curAttack)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 10083
    UTIL_ASSERT(curWeapon != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 10084
    UTIL_ASSERT(curAttack != NULL);

    const CRuleTables& cRule = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    if (curAttack->type == 2 || curAttack->type == 4) {
        return cRule.GetAbilityScoreModifier(m_derivedStats.m_nDEX);
    }

    WORD itemType = curWeapon->GetItemType();
    INT mod = cRule.GetAbilityScoreModifier(m_derivedStats.m_nSTR);

    if (sub_763150(CGAMESPRITE_FEAT_WEAPON_FINESSE)
        && (itemType == 19 || itemType == 16)) {
        INT nDEXMod = cRule.GetAbilityScoreModifier(m_derivedStats.m_nDEX);
        if (mod < nDEXMod) {
            mod = nDEXMod;
        }
    }

    if (sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK)
        && sub_726270(CGAMESPRITE_FEAT_POWER_ATTACK) > 0) {
        mod -= sub_726270(CGAMESPRITE_FEAT_POWER_ATTACK);
    }

    if (sub_763150(CGAMESPRITE_FEAT_EXPERTISE)
        && sub_726270(CGAMESPRITE_FEAT_EXPERTISE) > 0) {
        mod -= sub_726270(CGAMESPRITE_FEAT_EXPERTISE);
    }

    return static_cast<SHORT>(mod);
}

// 0x73CC40
SHORT CGameSprite::sub_73CC40(CItem* curWeapon, const ITEM_ABILITY* curAttack)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 10144
    UTIL_ASSERT(curWeapon != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 10145
    UTIL_ASSERT(curAttack != NULL);

    SHORT mod = 0;

    if (curAttack->thac0Bonus != SHORT_MAX) {
        mod += curAttack->thac0Bonus;
    }

    if (curAttack->type == 2 || curAttack->type == 4) {
        mod += m_derivedStats.m_nMissileTHAC0Bonus;
    }

    SHORT lSlot;
    CItem* pLauncher = GetLauncher(curAttack, lSlot);
    if (pLauncher != NULL) {
        pLauncher->Demand();
        const ITEM_ABILITY* ability = pLauncher->GetAbility(0);
        if (ability != NULL) {
            mod += ability->thac0Bonus;
        }
        pLauncher->Release();
    }

    return mod;
}

// 0x73D420
SHORT CGameSprite::sub_73D420()
{
    SHORT mod = 0;

    if ((m_derivedStats.m_generalState & STATE_BERSERK) != 0) {
        mod += 2;
    }

    mod += m_derivedStats.m_nTHAC0;

    return mod;
}

// 0x73D440
SHORT CGameSprite::sub_73D440(CItem* curWeapon)
{
    SHORT mod = 0;
    switch (curWeapon->GetItemType()) {
    case 0:
    case 28:
        mod++;
        break;
    case 15:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_BOW));
        break;
    case 16:
    case 19:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE));
        break;
    case 17:
    case 22:
    case 44:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_MACE));
        break;
    case 18:
    case 24:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_MISSILE));
        break;
    case 20:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_LARGESWORD));
        break;
    case 21:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_HAMMER));
        break;
    case 23:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_FLAIL));
        break;
    case 25:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_AXE));
        break;
    case 26:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF));
        break;
    case 27:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_CROSSBOW));
        break;
    case 29:
    case 30:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_POLEARM));
        break;
    case 57:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_GREATSWORD));
        break;
    case 69:
        mod = static_cast<SHORT>(GetFeatValue(CGAMESPRITE_FEAT_EXOTIC_BASTARD));
        break;
    }

    if (mod < 0) {
        mod = 0;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_TENSERS_TRANSFORMATION] && mod == 0) {
        mod = 1;
    }

    return mod;
}

// 0x73F560
SHORT CGameSprite::MoveToPoint()
{
    LONG x = m_curAction.m_dest.x;
    LONG y = m_curAction.m_dest.y;
    if (m_curAction.GetActionID() == CAIAction::TIMEDMOVETOPOINT) {
        LONG n = m_curAction.m_specificID - 1;
        if (n < 1) {
            m_curAction.m_actionID = CAIAction::JUMPTOPOINT;
            return JumpToPoint(m_curAction.m_dest, TRUE);
        }
        m_curAction.m_specificID = n;
    }

    if (m_derivedStats.m_nEncumberance == 2) {
        FeedBack(FEEDBACK_TOOHEAVY_STOPPED, 0, 0, 0, -1, 0, 0);
        return ACTION_ERROR;
    }

    if (x == -1) {
        x = m_posStart.x;
    } else if (x == -2) {
        x = m_baseStats.field_2E4;
    }

    if (y == -1) {
        y = m_posStart.y;
    } else if (y == -2) {
        y = m_baseStats.field_2E6;
    }

    if (x / CPathSearch::GRID_SQUARE_SIZEX == m_pos.x / CPathSearch::GRID_SQUARE_SIZEX
        && y / CPathSearch::GRID_SQUARE_SIZEY == m_pos.y / CPathSearch::GRID_SQUARE_SIZEY) {
        return ACTION_DONE;
    }

    if (x < 0
        || x >= m_pArea->GetInfinity()->nAreaX
        || y < 0
        || y >= m_pArea->GetInfinity()->nAreaY) {
        return ACTION_ERROR;
    }

    if (m_pPath == NULL
        && m_currentSearchRequest == NULL
        && m_actionCount > 0
        && m_curAction.m_specificID != CAIAction::BACKGROUND) {
        m_curAction.m_specificID2++;
        if (m_curAction.m_specificID2 > 4) {
            return ACTION_ERROR;
        }

        SHORT searchSquareCode;
        if (m_pArea->m_search.GetLOSCost(CPoint(x / CPathSearch::GRID_SQUARE_SIZEX, y / CPathSearch::GRID_SQUARE_SIZEY), m_terrainTable, searchSquareCode, FALSE) == CPathSearch::COST_IMPASSABLE) {
            return ACTION_ERROR;
        }

        m_curDest.x = x;
        m_curDest.y = y;

        if (!m_interrupt) {
            if (m_curAction.GetActionID() == CAIAction::MOVETOPOINTNORECTICLE) {
                CAIAction action(CAIAction::MOVETOPOINTNORECTICLE,
                    CPoint(x, y),
                    m_curAction.m_specificID,
                    m_curAction.m_specificID2);
                AddAction(action);
            } else {
                CAIAction action(CAIAction::MOVETOPOINT,
                    CPoint(x, y),
                    m_curAction.m_specificID,
                    m_curAction.m_specificID2);
                AddAction(action);
            }

            CAIAction action(CAIAction::SMALLWAIT,
                CPoint(-1, -1),
                rand() % 8 + 1,
                -1);
            AddAction(action);
        }

        return ACTION_DONE;
    }

    if (m_pPath == NULL
        && m_currentSearchRequest == NULL
        && m_actionCount > 0
        && m_curAction.m_specificID == CAIAction::BACKGROUND) {
        return ACTION_ERROR;
    }

    if (x != m_curDest.x || y != m_bPlayedEncumberedStopped) {
        m_curDest.x = x;
        m_curDest.y = y;

        CSearchRequest* pSearchRequest = new CSearchRequest();
        if (pSearchRequest == NULL) {
            return ACTION_ERROR;
        }

        pSearchRequest->m_searchBitmap = &(m_pArea->m_search);
        if (m_animation.GetListType() == LIST_FLIGHT) {
            memcpy(pSearchRequest->m_terrainTable, m_flightTerrainTable, sizeof(m_flightTerrainTable));
        } else {
            memcpy(pSearchRequest->m_terrainTable, m_terrainTable, sizeof(m_terrainTable));
        }

        pSearchRequest->m_removeSelf = m_animation.GetListType() != LIST_FLIGHT;
        pSearchRequest->m_pathSmooth = m_animation.GetPathSmooth();
        pSearchRequest->m_sourceId = m_id;
        pSearchRequest->m_nTargetPoints = 1;
        pSearchRequest->m_exclusiveTargetPoints = TRUE;

        pSearchRequest->m_targetPoints = new POINT[pSearchRequest->m_nTargetPoints];
        if (pSearchRequest->m_targetPoints == NULL) {
            delete pSearchRequest;
            return ACTION_ERROR;
        }

        if (m_pArea->m_pGame->GetGroup()->InList(m_id)) {
            pSearchRequest->m_nPartyIds = m_pArea->m_pGame->GetGroup()->GetCount();
            pSearchRequest->m_partyIds = m_pArea->m_pGame->GetGroup()->GetGroupList();
        }

        pSearchRequest->m_targetPoints[0] = m_curDest;
        pSearchRequest->m_sourceSide = m_typeAI.GetEnemyAlly();

        if (m_curAction.m_specificID == CAIAction::BACKGROUND) {
            pSearchRequest->m_frontList = 2;
            pSearchRequest->m_minNodesBack = 110;
            pSearchRequest->m_sourcePt.x = m_pos.x / CPathSearch::GRID_SQUARE_SIZEX;
            pSearchRequest->m_sourcePt.y = m_pos.y / CPathSearch::GRID_SQUARE_SIZEY;
            pSearchRequest->m_maxNodesBack = CSearchRequest::MINNODESBACK;
            SetTarget(pSearchRequest, FALSE, LIST_FLIGHT);
        } else {
            SetTarget(pSearchRequest, FALSE, LIST_FRONT);
        }
    }

    if (m_curAction.GetActionID() == 207) {
        return ACTION_NORMAL;
    }

    return ACTION_INTERRUPTABLE;
}

// 0x7446F0
SHORT CGameSprite::OneSwing()
{
    SHORT returnValue = ACTION_NORMAL;
    CMessage* message;

    if (m_attackFrame == 0) {
        m_speedFactor = 5;
        m_speedFactor += rand() % 6;
        m_speedFactor -= 3;
        if (m_speedFactor < 0) {
            m_speedFactor = 0;
        } else if (m_speedFactor > 10) {
            m_speedFactor = 10;
        }
    }

    BYTE frameType;
    if (m_derivedStats.m_nNumberOfAttacks > 0) {
        frameType = m_animation.GetAttackFrameType(static_cast<BYTE>(m_derivedStats.m_nNumberOfAttacks),
            static_cast<BYTE>(m_speedFactor),
            static_cast<BYTE>(m_attackFrame));
    } else {
        frameType = 0;
    }

    switch (frameType) {
    case 0:
        if (m_nSequence == GetIdleSequence()) {
            message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()), m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
        returnValue = ACTION_INTERRUPTABLE;
        break;
    case 6:
        if (m_nSequence != SEQ_ATTACK) {
            message = new CMessageSetSequence(SEQ_ATTACK, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
        break;
    case 7:
        if (m_nSequence != SEQ_ATTACK) {
            message = new CMessageSetSequence(SEQ_ATTACK, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
        returnValue = ACTION_NORMAL;
        break;
    case 9:
        if (m_nSequence != SEQ_ATTACK) {
            message = new CMessageSetSequence(SEQ_ATTACK, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
        returnValue = ACTION_NORMAL;
        break;
    case 15:
        returnValue = ACTION_DONE;
        break;
    }

    return returnValue;
}

// 0x7449D0
SHORT CGameSprite::Recoil()
{
    CMessage* message;

    if (m_recoilFrame == 0 && m_baseStats.m_hitPoints == 0) {
        m_endOfDamageSeq = FALSE;
        m_recoilFrame = 0;
        return ACTION_DONE;
    }

    if (m_nSequence != SEQ_DAMAGE) {
        message = new CMessageSetSequence(SEQ_DAMAGE, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    }

    m_recoilFrame++;
    if (!m_endOfDamageSeq) {
        return ACTION_NORMAL;
    }

    m_endOfDamageSeq = FALSE;
    m_recoilFrame = 0;

    message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()), m_id, m_id);
    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

    return ACTION_DONE;
}

// 0x744B20
SHORT CGameSprite::PlayDead()
{
    CMessage* message;

    if (m_nSequence != SEQ_DIE || m_nSequence != SEQ_TWITCH) {
        message = new CMessageSetSequence(SEQ_DIE, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    }

    if (m_actionCount == 0) {
        PlaySound(SOUND_DYING, TRUE, FALSE, FALSE);
    }

    if (m_curAction.m_specificID > 0) {
        m_curAction.m_specificID--;
        return ACTION_NORMAL;
    }

    message = new CMessageSetSequence(SEQ_AWAKE, m_id, m_id);
    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

    return ACTION_DONE;
}

// 0x745950
SHORT CGameSprite::JumpToPoint(CPoint dest, BOOL spriteUpdate)
{
    // TODO: Incomplete.

    return ACTION_DONE;
}

// 0x7462D0
SHORT CGameSprite::Face()
{
    SetDirection(static_cast<SHORT>(m_curAction.m_specificID));

    if (m_pos.x != -1 || m_pos.y != -1 || m_pArea != NULL) {
        if (InControl()) {
            CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
    }

    return ACTION_DONE;
}

// 0x746390
SHORT CGameSprite::FaceObject(CGameAIBase* pObject)
{
    if (pObject == NULL) {
        return ACTION_ERROR;
    }

    SetDirection(GetDirection(pObject->GetPos()));

    if (m_pos.x != -1 || m_pos.y != -1 || m_pArea != NULL) {
        if (InControl()) {
            CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
    }

    return ACTION_DONE;
}

// 0x751CD0
SHORT CGameSprite::LeaveParty()
{
    // TODO: Incomplete.

    return ACTION_DONE;
}

// 0x74F6D0
void CGameSprite::MoveGlobal(const CString& sArea, const CPoint& ptStart)
{
    // TODO: Incomplete.
}

// 0x74FC50
SHORT CGameSprite::GroupAttack(CGameSprite* pTarget)
{
    if (pTarget == NULL
        || !pTarget->m_active
        || !pTarget->m_activeAI
        || !pTarget->m_activeImprisonment) {
        return ACTION_DONE;
    }

    if (m_interrupt) {
        return ACTION_INTERRUPTABLE;
    }

    CAIObjectType typeAI(GetAIType());
    typeAI.SetName(CString(""));
    typeAI.SetInstance(-1);
    m_curAction.m_acteeID.Set(typeAI);
    AddAction(m_curAction);
    AddAction(CAIAction(CAIAction::ATTACK, m_curAction.m_acteeID, 0, 0, 0));

    return ACTION_DONE;
}

// 0x750DA0
SHORT CGameSprite::Enemy()
{
    m_typeAI.SetEnemyAlly(CAIObjectType::EA_ENEMY);
    m_liveTypeAI.SetEnemyAlly(CAIObjectType::EA_ENEMY);
    m_startTypeAI.SetEnemyAlly(CAIObjectType::EA_ENEMY);

    if (InControl()) {
        CMessage* message = new CMessageSpriteUpdate(this, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    }

    m_equipedEffectList.RemoveAllOfType(this, CGAMEEFFECT_CHARM, m_equipedEffectList.m_posCurrent, -1);
    m_equipedEffectList.RemoveAllOfType(this, ICEWIND_CGAMEEFFECT_CHARM, m_equipedEffectList.m_posCurrent, -1);
    m_timedEffectList.RemoveAllOfType(this, CGAMEEFFECT_CHARM, m_timedEffectList.m_posCurrent, -1);
    m_timedEffectList.RemoveAllOfType(this, ICEWIND_CGAMEEFFECT_CHARM, m_timedEffectList.m_posCurrent, -1);
    m_timedEffectList.RemoveAllOfType(this, CGAMEEFFECT_SETAISCRIPT, m_timedEffectList.m_posCurrent, -1);
    m_equipedEffectList.RemoveAllOfType(this, CGAMEEFFECT_SETAISCRIPT, m_equipedEffectList.m_posCurrent, -1);
    g_pBaldurChitin->GetObjectGame()->RemoveCharacterFromAllies(m_id);
    g_pBaldurChitin->GetObjectGame()->RemoveCharacterFromFamiliars(m_id);

    return ACTION_DONE;
}

// 0x754870
SHORT CGameSprite::SetDialog()
{
    m_dialog = m_curAction.GetString1();

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        CMessage* message = new CMessageSetDialogResRef(CResRef(m_curAction.GetString1()), m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    }

    return ACTION_DONE;
}

// 0x74F830
void CGameSprite::SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4)
{
    // TODO: Incomplete.
}

// 0x756930
void CGameSprite::sub_756930(CItem* pItem, CItem* pLauncher)
{
    // TODO: Incomplete.
}

// 0x7579C0
SHORT CGameSprite::EquipItem()
{
    SHORT slot = FindItemPersonal(m_curAction.GetString1(), 0, FALSE);
    if (slot == -1) {
        return ACTION_ERROR;
    }

    if (m_curAction.GetSpecifics()) {
        m_equipment.m_items[slot]->Equip(this, slot, FALSE);
    } else {
        m_equipment.m_items[slot]->Unequip(this, slot, TRUE, FALSE);
    }

    return ACTION_DONE;
}

// 0x757A80
SHORT CGameSprite::FindTraps()
{
    if (!m_typeAI.IsClassValid(CAIObjectType::C_ROGUE)
        || !m_typeAI.IsClassValid(CAIObjectType::C_MONK)) {
        return ACTION_ERROR;
    }

    SetModalState(2, TRUE);
    ClearActions(FALSE);

    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->m_pEngineWorld->GetSelectedCharacter()) {
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->m_nSelectedButton = 100;
        g_pBaldurChitin->GetObjectGame()->SetState(0);
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->UpdateButtons();
    }

    return ACTION_DONE;
}

// 0x758440
SHORT CGameSprite::Panic()
{
    CMessage* message;

    if (m_actionCount == 0) {
        message = new CMessageDropPath(m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

        message = new CMessageSetSequence(static_cast<BYTE>(GetIdleSequence()),
            m_id,
            m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
    }

    CAIAction randomWalk(CAIAction::RANDOMWALK, CPoint(-1, -1), 0, -1);
    AddAction(randomWalk);

    return ACTION_DONE;
}

// 0x75A3F0
SHORT CGameSprite::Turn()
{
    if (!m_typeAI.IsClassValid(CAIObjectType::C_CLERIC)
        || !m_typeAI.IsClassValid(CAIObjectType::C_PALADIN)) {
        return ACTION_ERROR;
    }

    SetModalState(4, TRUE);
    ClearActions(FALSE);

    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->m_pEngineWorld->GetSelectedCharacter()) {
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->m_nSelectedButton = 100;
        g_pBaldurChitin->GetObjectGame()->SetState(0);
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->UpdateButtons();
    }

    return ACTION_DONE;
}

// 0x75DFD0
SHORT CGameSprite::EquipMostDamagingMelee()
{
    return ACTION_ERROR;
}

// 0x75E880
const CAIObjectType& CGameSprite::GetLiveAIType()
{
    return m_liveTypeAI;
}

// 0x75E940
SHORT CGameSprite::GetCasterLevel(CSpell* pSpell, BYTE nClass, DWORD nSpecialization)
{
    // NOTE: Unsigned compare below in the loop.
    UINT nLevel = 1;
    UINT nBestCasterLevel = 0;

    if (pSpell == NULL) {
        if (nClass != 0 || nSpecialization != 0) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26119
            UTIL_ASSERT(pSpell != NULL);
        }
        return 1;
    }

    if (pSpell->GetCasterType() == 4) {
        if (pSpell->GetResRef() == "SPIN263") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_TALOS;
        } else if (pSpell->GetResRef() == "SPIN264") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_TEMPUS;
        } else if (pSpell->GetResRef() == "SPIN265"
            || pSpell->GetResRef() == "SPIN266") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_HELM;
        } else if (pSpell->GetResRef() == "SPIN267"
            || pSpell->GetResRef() == "SPIN270") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_ILMATER;
        } else if (pSpell->GetResRef() == "SPIN268"
            || pSpell->GetResRef() == "SPIN269") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_SELUNE;
        } else if (pSpell->GetResRef() == "SPIN271") {
            nClass = CAIOBJECTTYPE_C_CLERIC;
            nSpecialization = SPECMASK_CLERIC_LATHANDER;
        } else {
            nBestCasterLevel = m_derivedStats.GetLevel();
            if (nBestCasterLevel == 0) {
                nBestCasterLevel = 1;
            }
            return static_cast<SHORT>(nBestCasterLevel);
        }
    } else {
        switch (nClass) {
        case CAIOBJECTTYPE_C_BARBARIAN:
        case CAIOBJECTTYPE_C_FIGHTER:
        case CAIOBJECTTYPE_C_MONK:
        case CAIOBJECTTYPE_C_ROGUE:
            return static_cast<SHORT>(m_derivedStats.GetClassLevel(GetAIType().m_nClass));
        }
    }

    UINT nStart = 0;
    UINT nEnd = CSPELLLIST_NUM_CLASSES;

    if (nClass != 0) {
        nStart = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);
        nEnd = nStart + 1;
    }

    for (UINT nClassIndex = nStart; nClassIndex < nEnd; nClassIndex++) {
        nClass = g_pBaldurChitin->GetObjectGame()->GetSpellcasterClass(nStart);
        switch (nClass) {
        case CAIOBJECTTYPE_C_BARD:
        case CAIOBJECTTYPE_C_DRUID:
        case CAIOBJECTTYPE_C_SORCERER:
        case CAIOBJECTTYPE_C_WIZARD:
            nLevel = m_derivedStats.GetClassLevel(nClass);
            break;
        case CAIOBJECTTYPE_C_CLERIC:
            nLevel = m_derivedStats.GetClassLevel(nClass);
            if (nSpecialization != 0) {
                nLevel++;
            }
            break;
        case CAIOBJECTTYPE_C_PALADIN:
        case CAIOBJECTTYPE_C_RANGER:
            nLevel = m_derivedStats.GetClassLevel(nClass);
            if (nLevel >= 4) {
                nLevel /= 2;
            } else {
                nLevel = 0;
            }
            break;
        }

        // NOTE: Unsigned compare.
        if (nLevel > nBestCasterLevel) {
            nBestCasterLevel = nLevel;
        }
    }

    if (nBestCasterLevel == 0) {
        nBestCasterLevel = m_derivedStats.GetClassLevel(GetAIType().m_nClass);
    }
    if (nBestCasterLevel == 0) {
        nBestCasterLevel = 1;
    }
    return static_cast<SHORT>(nBestCasterLevel);
}

// 0x75F240
SHORT CGameSprite::sub_75F240()
{
    m_baseStats.field_2E4 = static_cast<SHORT>(m_pos.x);
    m_baseStats.field_2E6 = static_cast<SHORT>(m_pos.y);
    m_baseStats.field_2E8 = m_nDirection;
    return ACTION_DONE;
}

// 0x75F3D0
SHORT CGameSprite::sub_75F3D0(int a1)
{
    // TODO: Incomplete.

    return ACTION_ERROR;
}

// 0x75F800
SHORT CGameSprite::SetAtOffset(DWORD stat, DWORD value, BOOL modify)
{
    switch (stat) {
    case STAT_MAXHITPOINTS:
        if (modify == TRUE) {
            m_baseStats.m_maxHitPointsBase += static_cast<SHORT>(value);
            m_derivedStats.m_nMaxHitPoints += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_maxHitPointsBase = static_cast<SHORT>(value);
            m_derivedStats.m_nMaxHitPoints = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_ARMORCLASS:
        if (modify == TRUE) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26506
            UTIL_ASSERT_MSG(FALSE, "this option is no longer available -rjf");
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26513
            UTIL_ASSERT_MSG(FALSE, "this option is no longer available -rjf");
        }
    case STAT_ACBLUDGEONINGMOD:
        if (modify == TRUE) {
            m_baseStats.m_armorClassCrushingAdjustment += static_cast<SHORT>(value);
            m_derivedStats.m_nACCrushingMod += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_armorClassCrushingAdjustment = static_cast<SHORT>(value);
            m_derivedStats.m_nACCrushingMod = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_ACMISSILEMOD:
        if (modify == TRUE) {
            m_baseStats.m_armorClassMissileAdjustment += static_cast<SHORT>(value);
            m_derivedStats.m_nACMissileMod += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_armorClassMissileAdjustment = static_cast<SHORT>(value);
            m_derivedStats.m_nACMissileMod = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_ACPIERCINGMOD:
        if (modify == TRUE) {
            m_baseStats.m_armorClassPiercingAdjustment += static_cast<SHORT>(value);
            m_derivedStats.m_nACPiercingMod += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_armorClassPiercingAdjustment = static_cast<SHORT>(value);
            m_derivedStats.m_nACPiercingMod = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_ACSLASHINGMOD:
        if (modify == TRUE) {
            m_baseStats.m_armorClassSlashingAdjustment += static_cast<SHORT>(value);
            m_derivedStats.m_nACSlashingMod += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_armorClassSlashingAdjustment = static_cast<SHORT>(value);
            m_derivedStats.m_nACSlashingMod = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_THAC0:
        if (modify == TRUE) {
            m_baseStats.m_attackBase += static_cast<BYTE>(value);
            m_derivedStats.m_nTHAC0 += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_attackBase = static_cast<BYTE>(value);
            m_derivedStats.m_nTHAC0 = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_NUMBEROFATTACKS:
        if (modify == TRUE) {
            m_baseStats.m_numberOfAttacksBase += static_cast<BYTE>(value);
            m_derivedStats.m_nNumberOfAttacks += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_numberOfAttacksBase = static_cast<BYTE>(value);
            m_derivedStats.m_nNumberOfAttacks = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SAVEFORTITUDE:
        if (modify == TRUE) {
            m_baseStats.m_saveVSFortitudeBase += static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSFortitude += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_saveVSFortitudeBase = static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSFortitude = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SAVEREFLEX:
        if (modify == TRUE) {
            m_baseStats.m_saveVSReflexBase += static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSReflex += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_saveVSReflexBase = static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSReflex = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SAVEWILL:
        if (modify == TRUE) {
            m_baseStats.m_saveVSWillBase += static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSWill += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_saveVSWillBase = static_cast<BYTE>(value);
            m_derivedStats.m_nSaveVSWill = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_KNOWLEDGEARCANA:
    case STAT_13:
        return 1;
    case STAT_RESISTFIRE:
        if (modify == TRUE) {
            m_baseStats.m_resistFireBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistFire += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistFireBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistFire = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTCOLD:
        if (modify == TRUE) {
            m_baseStats.m_resistColdBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistCold += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistColdBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistCold = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTELECTRICITY:
        if (modify == TRUE) {
            m_baseStats.m_resistElectricityBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistElectricity += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistElectricityBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistElectricity = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTACID:
        if (modify == TRUE) {
            m_baseStats.m_resistAcidBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistAcid += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistAcidBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistAcid = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTMAGIC:
        if (modify == TRUE) {
            m_baseStats.m_resistMagicBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistMagic += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistMagicBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistMagic = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTMAGICFIRE:
        if (modify == TRUE) {
            m_baseStats.m_resistMagicFireBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistMagicFire += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistMagicFireBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistMagicFire = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTMAGICCOLD:
        if (modify == TRUE) {
            m_baseStats.m_resistMagicColdBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistMagicCold += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistMagicColdBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistMagicCold = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTSLASHING:
        if (modify == TRUE) {
            m_baseStats.m_resistSlashingBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistSlashing += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistSlashingBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistSlashing = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTBLUDGEONING:
        if (modify == TRUE) {
            m_baseStats.m_resistCrushingBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistCrushing += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistCrushingBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistCrushing = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTPIERCING:
        if (modify == TRUE) {
            m_baseStats.m_resistPiercingBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistPiercing += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistPiercingBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistPiercing = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTMISSILE:
        if (modify == TRUE) {
            m_baseStats.m_resistMissileBase += static_cast<signed char>(value);
            m_derivedStats.m_nResistMissile += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_resistMissileBase = static_cast<signed char>(value);
            m_derivedStats.m_nResistMissile = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_ALCHEMY:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_ALCHEMY] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_ALCHEMY] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_ALCHEMY] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_ALCHEMY] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_LOCKPICKING:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_OPEN_LOCK] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_OPEN_LOCK] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_OPEN_LOCK] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_OPEN_LOCK] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_MOVESILENTLY:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_MOVE_SILENTLY] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_MOVE_SILENTLY] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_MOVE_SILENTLY] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_MOVE_SILENTLY] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_TRAPS:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_SEARCH] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_SEARCH] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_SEARCH] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_SEARCH] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_PICKPOCKET:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_PICK_POCKET] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_PICK_POCKET] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_PICK_POCKET] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_PICK_POCKET] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_FATIGUE:
        if (modify == TRUE) {
            m_baseStats.m_fatigue += static_cast<BYTE>(value);
            m_derivedStats.m_nFatigue += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_fatigue = static_cast<BYTE>(value);
            m_derivedStats.m_nFatigue = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_INTOXICATION:
        if (modify == TRUE) {
            m_baseStats.m_intoxication += static_cast<BYTE>(value);
            // FIXME: Looks like a bug - should be `m_nIntoxication`.
            m_derivedStats.m_nFatigue += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_intoxication = static_cast<BYTE>(value);
            // FIXME: Looks like a bug - should be `m_nIntoxication`.
            m_derivedStats.m_nFatigue = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_LUCK:
        if (modify == TRUE) {
            m_baseStats.m_luckBase += static_cast<BYTE>(value);
            m_derivedStats.m_nLuck += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_luckBase = static_cast<BYTE>(value);
            m_derivedStats.m_nLuck = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_TRACKING:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_WILDERNESS_LORE] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_WILDERNESS_LORE] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_WILDERNESS_LORE] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_WILDERNESS_LORE] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_LEVEL:
        if (modify == TRUE) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26891
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26897
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        }
    case STAT_SEX:
        if (modify == TRUE) {
            m_baseStats.m_sex += static_cast<BYTE>(value);
            m_derivedStats.m_nSex += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_sex = static_cast<BYTE>(value);
            m_derivedStats.m_nSex = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_STR:
        if (modify == TRUE) {
            m_baseStats.m_STRBase += static_cast<BYTE>(value);
            m_derivedStats.m_nSTR += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_STRBase = static_cast<BYTE>(value);
            m_derivedStats.m_nSTR = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_STREXTRA:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 26969
        UTIL_ASSERT(FALSE);
    case STAT_INT:
        if (modify == TRUE) {
            m_baseStats.m_INTBase += static_cast<BYTE>(value);
            m_derivedStats.m_nINT += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_INTBase = static_cast<BYTE>(value);
            m_derivedStats.m_nINT = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_WIS:
        if (modify == TRUE) {
            m_baseStats.m_WISBase += static_cast<BYTE>(value);
            m_derivedStats.m_nWIS += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_WISBase = static_cast<BYTE>(value);
            m_derivedStats.m_nWIS = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_DEX:
        if (modify == TRUE) {
            m_baseStats.m_DEXBase += static_cast<BYTE>(value);
            m_derivedStats.m_nDEX += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_DEXBase = static_cast<BYTE>(value);
            m_derivedStats.m_nDEX = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_CON:
        if (modify == TRUE) {
            m_baseStats.m_CONBase += static_cast<BYTE>(value);
            m_derivedStats.m_nCON += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_CONBase = static_cast<BYTE>(value);
            m_derivedStats.m_nCON = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_CHR:
        if (modify == TRUE) {
            m_baseStats.m_CHRBase += static_cast<BYTE>(value);
            m_derivedStats.m_nCHR += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_CHRBase = static_cast<BYTE>(value);
            m_derivedStats.m_nCHR = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_XPVALUE:
        if (modify == TRUE) {
            m_baseStats.m_xpValue += value;
            m_derivedStats.m_nXPValue += value;
        } else {
            m_baseStats.m_xpValue = value;
            m_derivedStats.m_nXPValue = value;
        }
        return 1;
    case STAT_XP:
        if (modify == TRUE) {
            m_baseStats.m_xp += value;
            m_derivedStats.m_nXP += value;
        } else {
            m_baseStats.m_xp = value;
            m_derivedStats.m_nXP = value;
        }
        return 1;
    case STAT_GOLD:
        if (modify == TRUE) {
            m_baseStats.m_gold += value;
            m_derivedStats.m_nGold += value;
        } else {
            m_baseStats.m_gold = value;
            m_derivedStats.m_nGold = value;
        }
        return 1;
    case STAT_MORALEBREAK:
        if (modify == TRUE) {
            m_baseStats.m_moraleBreak += static_cast<BYTE>(value);
            m_derivedStats.m_nMoraleBreak += value;
        } else {
            m_baseStats.m_moraleBreak = static_cast<BYTE>(value);
            m_derivedStats.m_nMoraleBreak = value;
        }
        return 1;
    case STAT_MORALERECOVERYTIME:
        if (modify == TRUE) {
            m_baseStats.m_moraleRecoveryTime += static_cast<WORD>(value);
            m_derivedStats.m_nMoraleRecoveryTime += value;
        } else {
            m_baseStats.m_moraleRecoveryTime = static_cast<WORD>(value);
            m_derivedStats.m_nMoraleRecoveryTime = value;
        }
        return 1;
    case STAT_REPUTATION:
        if (modify == TRUE) {
            m_baseStats.m_reputation += static_cast<BYTE>(value);
            m_derivedStats.m_nReputation += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_reputation = static_cast<BYTE>(value);
            m_derivedStats.m_nReputation = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_HATEDRACE:
        if (modify == TRUE) {
            m_baseStats.m_favoredEnemies[0] += static_cast<BYTE>(value);
            m_derivedStats.m_favoredEnemies[0] += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_favoredEnemies[0] = static_cast<BYTE>(value);
            m_derivedStats.m_favoredEnemies[0] = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_DAMAGEBONUS:
        if (modify == TRUE) {
            m_derivedStats.m_nDamageBonus += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nDamageBonus = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SPELLFAILUREMAGE:
        if (modify == TRUE) {
            m_derivedStats.m_nSpellFailureArcane += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nSpellFailureArcane = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SPELLFAILUREPRIEST:
        if (modify == TRUE) {
            m_derivedStats.m_nSpellFailureDivine += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nSpellFailureDivine = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SPELLDURATIONMODMAGE:
        if (modify == TRUE) {
            m_derivedStats.m_nSpellDurationModMage += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nSpellDurationModMage = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SPELLDURATIONMODPRIEST:
        if (modify == TRUE) {
            m_derivedStats.m_nSpellDurationModPriest += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nSpellDurationModPriest = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_TURNUNDEADLEVEL:
        if (modify == TRUE) {
            m_baseStats.m_turnUndeadLevel += static_cast<BYTE>(value);
            m_derivedStats.m_nTurnUndeadLevel += static_cast<SHORT>(value);
        } else {
            m_baseStats.m_turnUndeadLevel = static_cast<BYTE>(value);
            m_derivedStats.m_nTurnUndeadLevel = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_BACKSTABDAMAGEMULTIPLIER:
        if (modify == TRUE) {
            m_derivedStats.m_nBackstabDamageMultiplier += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nBackstabDamageMultiplier = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_LAYONHANDSAMOUNT:
        if (modify == TRUE) {
            m_derivedStats.m_nLayOnHandsAmount += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nLayOnHandsAmount = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_TRANSLUCENT:
        if (modify == TRUE) {
            m_derivedStats.m_nTranslucent += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nTranslucent = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_LEVEL2:
        if (modify == TRUE) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26905
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26911
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        }
    case STAT_LEVEL3:
        if (modify == TRUE) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 29919
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 26925
            UTIL_ASSERT_MSG(FALSE, "Scripts and dialogs may no longer set Class Levels");
        }
    case STAT_ENCUMBERANCE:
        if (modify == TRUE) {
            m_derivedStats.m_nEncumberance += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nEncumberance = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_MISSILETHAC0BONUS:
        if (modify == TRUE) {
            m_derivedStats.m_nMissileTHAC0Bonus += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nMissileTHAC0Bonus = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_MAGICDAMAGERESISTANCE:
        if (modify == TRUE) {
            m_derivedStats.m_nMagicDamageResistance += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nMagicDamageResistance = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_RESISTPOISON:
        if (modify == TRUE) {
            m_derivedStats.m_nResistPoison += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nResistPoison = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_MENTALSPEED:
        if (modify == TRUE) {
            m_derivedStats.m_nMentalSpeed += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nMentalSpeed = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_PHYSICALSPEED:
        if (modify == TRUE) {
            m_derivedStats.m_nPhysicalSpeed += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nPhysicalSpeed = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_CASTINGLEVELBONUSMAGE:
        if (modify == TRUE) {
            m_derivedStats.m_nCastingLevelBonusMage += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nCastingLevelBonusMage = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_CASTINGLEVELBONUSCLERIC:
        if (modify == TRUE) {
            m_derivedStats.m_nCastingLevelBonusCleric += static_cast<SHORT>(value);
        } else {
            m_derivedStats.m_nCastingLevelBonusCleric = static_cast<SHORT>(value);
        }
        return 1;
    case STAT_SEEINVISIBLE:
        if (modify == TRUE) {
            m_derivedStats.m_bSeeInvisible += value;
        } else {
            m_derivedStats.m_bSeeInvisible = value;
        }
        return 1;
    case STAT_IGNOREDIALOGPAUSE:
        if (modify == TRUE) {
            m_derivedStats.m_bIgnoreDialogPause += value;
        } else {
            m_derivedStats.m_bIgnoreDialogPause = value;
        }
        return 1;
    case STAT_MINHITPOINTS:
        if (modify == TRUE) {
            m_derivedStats.m_nMinHitPoints += value;
        } else {
            m_derivedStats.m_nMinHitPoints = value;
        }
        return 1;
    case STAT_THAC0BONUSRIGHT:
        if (modify == TRUE) {
            m_derivedStats.m_THAC0BonusRight += value;
        } else {
            m_derivedStats.m_THAC0BonusRight = value;
        }
        return 1;
    case STAT_THAC0BONUSLEFT:
        if (modify == TRUE) {
            m_derivedStats.m_THAC0BonusLeft += value;
        } else {
            m_derivedStats.m_THAC0BonusLeft = value;
        }
        return 1;
    case STAT_DAMAGEBONUSRIGHT:
        if (modify == TRUE) {
            m_derivedStats.m_DamageBonusRight += value;
        } else {
            m_derivedStats.m_DamageBonusRight = value;
        }
        return 1;
    case STAT_DAMAGEBONUSLEFT:
        if (modify == TRUE) {
            m_derivedStats.m_DamageBonusLeft += value;
        } else {
            m_derivedStats.m_DamageBonusLeft = value;
        }
        return 1;
    case STAT_HIDEINSHADOWS:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_HIDE] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_HIDE] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_HIDE] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_HIDE] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_MOVESILENTLYMTPBONUS:
        if (modify == TRUE) {
            m_derivedStats.m_nMoveSilentlyMTPBonus += value;
        } else {
            m_derivedStats.m_nMoveSilentlyMTPBonus = value;
        }
        return 1;
    case STAT_HIDEINSHADOWSMTPBONUS:
        if (modify == TRUE) {
            m_derivedStats.m_nHideInShadowsMTPBonus += value;
        } else {
            m_derivedStats.m_nHideInShadowsMTPBonus = value;
        }
        return 1;
    case STAT_SUBRACE:
        if (modify == TRUE) {
            m_baseStats.m_subrace += static_cast<BYTE>(value);
            m_derivedStats.m_nSubRace += value;
        } else {
            m_baseStats.m_subrace = static_cast<BYTE>(value);
            m_derivedStats.m_nSubRace = value;
        }
        return 1;
    case STAT_USEMAGICDEVICE:
        if (modify == TRUE) {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_USE_MAGIC_DEVICE] += static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_USE_MAGIC_DEVICE] += static_cast<BYTE>(value);
        } else {
            m_baseStats.m_skills[CGAMESPRITE_SKILL_USE_MAGIC_DEVICE] = static_cast<BYTE>(value);
            m_derivedStats.m_nSkills[CGAMESPRITE_SKILL_USE_MAGIC_DEVICE] = static_cast<BYTE>(value);
        }
        return 1;
    case STAT_CLASSLEVELBARBARIAN:
    case STAT_CLASSLEVELBARD:
    case STAT_CLASSLEVELCLERIC:
    case STAT_CLASSLEVELDRUID:
    case STAT_CLASSLEVELFIGHTER:
    case STAT_CLASSLEVELMONK:
    case STAT_CLASSLEVELPALADIN:
    case STAT_CLASSLEVELRANGER:
    case STAT_CLASSLEVELROGUE:
    case STAT_CLASSLEVELSORCERER:
    case STAT_CLASSLEVELWIZARD:
        if (modify == TRUE) {
            m_derivedStats.SetClassLevel(stat - STAT_CLASSLEVELSUM,
                m_derivedStats.GetClassLevel(stat - STAT_CLASSLEVELSUM) + value);
            SetClassLevel(stat - STAT_CLASSLEVELSUM,
                GetClassLevel(stat - STAT_CLASSLEVELSUM) + value);
        } else {
            m_derivedStats.SetClassLevel(stat - STAT_CLASSLEVELSUM, value);
            SetClassLevel(stat - STAT_CLASSLEVELSUM, value);
        }
        return 1;
    case STAT_PREVENTAISLOWDOWN:
        if (modify == TRUE) {
            m_derivedStats.m_bPreventAISlowDown += value;
        } else {
            m_derivedStats.m_bPreventAISlowDown = value;
        }
        return 1;
    }

    return 0;
}

// 0x761470
SHORT CGameSprite::ForceHide(CGameSprite* pSprite)
{
    if (m_bHiding) {
        return ACTION_DONE;
    }

    if (g_pBaldurChitin->GetObjectGame()->GetState() != 0) {
        return ACTION_DONE;
    }

    SetModalState(3, TRUE);
    g_pBaldurChitin->GetObjectGame()->GetButtonArray()->SetSelectedButton(5);

    if (!m_bHiding && !m_baseStats.field_294) {
        PlaySound(CResRef("ACT_07"));
    }

    if (!m_baseStats.field_294) {
        FeedBack(FEEDBACK_HIDESUCCEEDED,
            0,
            0,
            0,
            -1,
            0,
            0);
    }

    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_INVISIBLE);
    effect.durationType = 0x100;
    effect.dwFlags = 0;
    effect.effectAmount = 1;
    effect.duration = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime + 300;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        m_pos,
        m_id,
        CPoint(-1, -1));

    CMessage* message = new CMessageAddEffect(pEffect, m_id, m_id);
    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

    m_modalCounter = 0;
    m_bHiding = TRUE;

    return ACTION_DONE;
}

// 0x7615F0
SHORT CGameSprite::sub_7615F0(int a1)
{
    if (a1 == 0) {
        m_pArea->m_visibility.SetAreaVisible(FALSE);
        a1 = CVisibilityMap::EXPLORED_RANGE_3;
    }

    m_pArea->m_visibility.field_E = static_cast<short>(a1);
    m_pArea->m_visibility.field_10 = static_cast<short>(3 * a1 / 4);
    m_pArea->m_visibility.sub_5518A0();

    return ACTION_DONE;
}

// 0x761650
void CGameSprite::sub_761650()
{
    // TODO: Incomplete.
}

// 0x7618E0
SHORT CGameSprite::DropItem(CItem* pItem)
{
    if (pItem == NULL) {
        return ACTION_ERROR;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    LONG iContainer = pGame->GetGroundPile(m_id);
    if (iContainer == CGameObjectArray::INVALID_INDEX) {
        return ACTION_ERROR;
    }

    CGameContainer* pContainer;

    BYTE rc = pGame->GetObjectArray()->GetDeny(iContainer,
        CGameObjectArray::THREAD_ASYNCH,
        reinterpret_cast<CGameObject**>(&pContainer),
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        return ACTION_ERROR;
    }

    if ((pItem->GetFlagsFile() & 0x4) != 0) {
        pContainer->PlaceItemInBlankSlot(pItem, 1, SHORT_MAX);
    }

    pGame->GetObjectArray()->ReleaseDeny(iContainer,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    return ACTION_DONE;
}

// 0x761990
void CGameSprite::sub_761990()
{
    m_timedEffectList.RemoveAllEffectsIgnoreMoreThenPermanent(NULL, FALSE, FALSE, 0, 0);
    UnequipAll(FALSE);
    EquipAll(FALSE);
}

// 0x7619C0
SHORT CGameSprite::PlayBardSong()
{
    if ((GetAIType().m_nClassMask & CLASSMASK_BARD) == 0) {
        return ACTION_ERROR;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (pGame->GetButtonArray()->m_nState == 113) {
        return ACTION_DONE;
    }

    BYTE nSong = static_cast<BYTE>(m_curAction.m_specificID);
    if (nSong >= pGame->GetMasterSongLookup().m_nCount) {
        return ACTION_ERROR;
    }

    m_nLastSong = nSong;
    SetModalState(1, TRUE);
    ClearActions(FALSE);

    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == g_pBaldurChitin->GetScreenWorld()->GetSelectedCharacter()) {
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->SetSelectedButton(100);
        g_pBaldurChitin->GetObjectGame()->SetState(0);
        g_pBaldurChitin->GetObjectGame()->GetButtonArray()->UpdateButtons();
    }

    return ACTION_DONE;
}

// 0x762740
BOOL CGameSprite::HasClassMask(DWORD dwMask)
{
    return (dwMask & GetAIType().m_nClassMask) != 0;
}

// 0x762760
INT CGameSprite::GetClassLevel(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28701
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28702
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_baseStats.m_classLevels[iClassType - 1];
}

// 0x7627C0
void CGameSprite::SetClassLevel(INT iClassType, INT nLevel)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28718
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28719
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    m_baseStats.m_characterLevel += static_cast<BYTE>(nLevel) - m_baseStats.m_classLevels[iClassType];
    m_baseStats.m_classLevels[iClassType - 1] = static_cast<BYTE>(nLevel);
}

// 0x762830
BOOL CGameSprite::HasClassLevel(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28739
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28740
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_baseStats.m_classLevels[iClassType - 1] != 0;
}

// 0x762890
void CGameSprite::SetFeatValue(UINT nFeatNumber, INT iFeatValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28756
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if (iFeatValue > 0) {
        m_baseStats.m_feats[nFeatNumber >> 5] |= 1 << (nFeatNumber & 0x1F);
    } else {
        m_baseStats.m_feats[nFeatNumber >> 5] &= ~(1 << (nFeatNumber & 0x1F));
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28774
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE);

        m_baseStats.m_featArmorProficiency = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28781
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE);

        m_baseStats.m_featArmoredArcana = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_CLEAVE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28781
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE);

        m_baseStats.m_featCleave = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28795
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featBastardSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28802
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE);

        m_baseStats.m_featExtraRage = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28809
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE);

        m_baseStats.m_featExtraShapeshifting = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28816
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE);

        m_baseStats.m_featExtraSmiting = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28823
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE);

        m_baseStats.m_featExtraTurning = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28830
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featAxe = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28837
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featBow = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28844
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featFlail = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28851
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featGreatSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28858
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featHammer = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28865
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featLargeSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28872
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featPolearm = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28879
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featCrossbow = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28886
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featMace = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28893
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featMissile = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28890
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featQuarterStaff = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28897
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featSmallBlade = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28914
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE);

        m_baseStats.m_featFocusEnchantment = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28921
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE);

        m_baseStats.m_featFocusEvocation = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28928
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE);

        m_baseStats.m_featFocusNecromancy = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28935
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE);

        m_baseStats.m_featFocusTransmutation = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28942
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE);

        m_baseStats.m_featSpellPenetration = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28949
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL);

        m_baseStats.m_featToughness = iFeatValue;
        break;
    }
}

// 0x762E20
INT CGameSprite::GetFeatValue(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28968
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) == 0) {
        return 0;
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return m_baseStats.m_featArmorProficiency;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_baseStats.m_featArmoredArcana;
    case CGAMESPRITE_FEAT_CLEAVE:
        return m_baseStats.m_featCleave;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return m_baseStats.m_featBastardSword;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_featExtraRage;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_featExtraShapeshifting;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_featExtraSmiting;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_featExtraTurning;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return m_baseStats.m_featAxe;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return m_baseStats.m_featBow;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return m_baseStats.m_featFlail;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return m_baseStats.m_featGreatSword;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return m_baseStats.m_featHammer;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return m_baseStats.m_featLargeSword;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return m_baseStats.m_featPolearm;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return m_baseStats.m_featCrossbow;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return m_baseStats.m_featMace;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return m_baseStats.m_featMissile;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return m_baseStats.m_featQuarterStaff;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return m_baseStats.m_featSmallBlade;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return m_baseStats.m_featFocusEnchantment;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return m_baseStats.m_featFocusEvocation;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return m_baseStats.m_featFocusNecromancy;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return m_baseStats.m_featFocusTransmutation;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return m_baseStats.m_featSpellPenetration;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return m_baseStats.m_featToughness;
    }
    return 1;
}

// 0x7630A0
INT CGameSprite::GetMaxFeatValue(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29126
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE;
    case CGAMESPRITE_FEAT_CLEAVE:
        return CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL;
    }

    return 1;
}

// 0x763150
BOOL CGameSprite::sub_763150(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29278
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) == 0) {
        return 0;
    }

    if (nFeatNumber == CGAMESPRITE_FEAT_CLEAVE) {
        if (m_derivedStats.m_nSTR >= 13) {
            if (sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK)) {
                INT nValue = GetFeatValue(CGAMESPRITE_FEAT_CLEAVE);
                if (nValue == 1 || nValue == 2) {
                    if (m_baseStats.m_attackBase >= 4) {
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }

    return sub_763200(nFeatNumber, 0);
}

// 0x763200
BOOL CGameSprite::sub_763200(UINT nFeatNumber, INT a2)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29333
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    SHORT nSTR = m_derivedStats.m_nSTR;
    SHORT nDEX = m_derivedStats.m_nDEX;
    SHORT nINT = m_derivedStats.m_nINT;
    SHORT nWIS = m_derivedStats.m_nWIS;

    if (a2 == 1) {
        nSTR = m_baseStats.m_STRBase;
        nDEX = m_baseStats.m_DEXBase;
        nINT = m_baseStats.m_INTBase;
        nWIS = m_baseStats.m_WISBase;
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_AEGIS_OF_RIME:
    case CGAMESPRITE_FEAT_AQUA_MORTIS:
    case CGAMESPRITE_FEAT_SCION_OF_STORMS:
    case CGAMESPRITE_FEAT_SPIRIT_OF_FLAME:
        return (m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_BARD) >= 11
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_DRUID) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_WIZARD) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) >= 15
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER) >= 15
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER) >= 8)
            && m_derivedStats.m_nSkills[13] >= 10;
    case CGAMESPRITE_FEAT_AMBIDEXTERITY:
        return nDEX >= 15;
    case CGAMESPRITE_FEAT_ARMOR_PROF:
    case CGAMESPRITE_FEAT_BLIND_FIGHT:
    case CGAMESPRITE_FEAT_COURTEOUS_MAGOCRACY:
    case CGAMESPRITE_FEAT_DASH:
    case CGAMESPRITE_FEAT_DISCIPLINE:
    case CGAMESPRITE_FEAT_FORESTER:
    case CGAMESPRITE_FEAT_GREAT_FORTITUDE:
    case CGAMESPRITE_FEAT_IMPROVED_INITIATIVE:
    case CGAMESPRITE_FEAT_IRON_WILL:
    case CGAMESPRITE_FEAT_LIGHTNING_REFLEXES:
    case CGAMESPRITE_FEAT_PRECISE_SHOT:
    case CGAMESPRITE_FEAT_SHIELD_PROF:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
    case CGAMESPRITE_FEAT_STRONG_BACK:
    case CGAMESPRITE_FEAT_TOUGHNESS:
    case CGAMESPRITE_FEAT_TWO_WEAPON_FIGHTING:
        return TRUE;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD);
    case CGAMESPRITE_FEAT_ARTERIAL_STRIKE:
        return m_baseStats.m_rogueLevel > 0 && m_baseStats.m_attackBase >= 4;
    case CGAMESPRITE_FEAT_BULLHEADED:
        return m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
            || m_typeAI.m_nRace == CAIOBJECTTYPE_R_DWARF;
    case CGAMESPRITE_FEAT_CLEAVE:
        if (!(nSTR >= 13 && sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK))) {
            return FALSE;
        }

        if (GetFeatValue(CGAMESPRITE_FEAT_CLEAVE) >= 1) {
            return m_baseStats.m_attackBase >= 4;
        }

        return TRUE;
    case CGAMESPRITE_FEAT_COMBAT_CASTING:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD)
            || m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_CRIPPLING_STRIKE:
        return m_baseStats.m_rogueLevel >= 10;
    case CGAMESPRITE_FEAT_DEFLECT_ARROWS:
    case CGAMESPRITE_FEAT_DODGE:
    case CGAMESPRITE_FEAT_RAPID_SHOT:
        return nDEX >= 13;
    case CGAMESPRITE_FEAT_DIRTY_FIGHTING:
        return nDEX >= 13 && m_baseStats.m_attackBase >= 2;
    case CGAMESPRITE_FEAT_ENVENOM_WEAPON:
        return m_baseStats.m_rogueLevel > 0
            && m_baseStats.m_skills[CGAMESPRITE_SKILL_ALCHEMY] >= 8;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return GetFeatValue(CGAMESPRITE_FEAT_EXOTIC_BASTARD) != 2
            || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_EXPERTISE:
        return nINT >= 13;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_barbarianLevel > 0;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_druidLevel >= 3;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_paladinLevel >= 2;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_paladinLevel >= 3
            || m_baseStats.m_clericLevel > 0;
    case CGAMESPRITE_FEAT_FIENDSLAYER:
        return (GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_LARGESWORD) >= 2
                   || GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_GREATSWORD) >= 2)
            && m_baseStats.m_paladinLevel >= 3;
    case CGAMESPRITE_FEAT_HAMSTRING:
        return m_baseStats.m_rogueLevel >= 3;
    case CGAMESPRITE_FEAT_HERETICS_BANE:
        return m_baseStats.m_attackBase >= 4
            && m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_HEROIC_INSPIRATION:
        return m_baseStats.m_barbarianLevel > 0
            || m_baseStats.m_barbarianLevel > 0
            || m_baseStats.m_paladinLevel > 0;
    case CGAMESPRITE_FEAT_IMPROVED_CRITICAL:
        return m_baseStats.m_attackBase >= 8;
    case CGAMESPRITE_FEAT_IMPROVED_EVASION:
        return m_baseStats.m_rogueLevel >= 10
            || m_baseStats.m_monkLevel >= 9;
    case CGAMESPRITE_FEAT_IMPROVED_TURNING:
        return m_baseStats.m_clericLevel > 0
            || m_baseStats.m_paladinLevel >= 3;
    case CGAMESPRITE_FEAT_LINGERING_SONG:
        return m_baseStats.m_bardLevel > 0;
    case CGAMESPRITE_FEAT_LUCK_OF_HEROES:
        return m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return GetFeatValue(nFeatNumber) != 3 || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_MAXIMIZED_ATTACKS:
        if (1) {
            INT nWeaponSpecializations = 0;
            for (INT nFeatNumber = CGAMESPRITE_FEAT_MARTIAL_AXE; nFeatNumber <= CGAMESPRITE_FEAT_MARTIAL_POLEARM; nFeatNumber++) {
                if (GetFeatValue(nFeatNumber) == 3) {
                    nWeaponSpecializations++;
                }
            }

            if (GetFeatValue(CGAMESPRITE_FEAT_EXOTIC_BASTARD) == 3) {
                nWeaponSpecializations++;
            }

            if (nWeaponSpecializations < 2) {
                for (INT nFeatNumber = CGAMESPRITE_FEAT_SIMPLE_CROSSBOW; nFeatNumber <= CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE; nFeatNumber++) {
                    if (GetFeatValue(nFeatNumber) == 3) {
                        nWeaponSpecializations++;
                    }
                }
            }

            return nWeaponSpecializations >= 2
                && m_baseStats.m_skills[CGAMESPRITE_SKILL_CONCENTRATION] >= 4;
        }
    case CGAMESPRITE_FEAT_MERCANTILE_BACKGROUND:
        // TODO: Incomplete.
        return FALSE;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return GetFeatValue(nFeatNumber) != 3 || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_SNAKE_BLOOD:
        // TODO: Incomplete.
        return FALSE;
    case CGAMESPRITE_FEAT_STUNNING_FIST:
        return (nDEX >= 13 && nWIS >= 13 && m_baseStats.m_attackBase >= 8)
            || m_baseStats.m_monkLevel > 0;
    case CGAMESPRITE_FEAT_SUBVOCAL_CASTING:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD)
            || m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_WEAPON_FINESSE:
        return GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE)
            && m_baseStats.m_attackBase >= 1;
    case CGAMESPRITE_FEAT_WILDSHAPE_BOAR:
    case CGAMESPRITE_FEAT_WILDSHAPE_PANTHER:
        return m_baseStats.m_druidLevel >= 5;
    case CGAMESPRITE_FEAT_WILDSHAPE_SHAMBLER:
        return m_baseStats.m_druidLevel >= 8;
    }

    return FALSE;
}

// 0x763A40
BOOL CGameSprite::sub_763A40(UINT nFeatNumber, INT a2)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29873
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return m_baseStats.m_featArmorProficiency < CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_baseStats.m_featArmoredArcana < CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_CLEAVE:
        return m_baseStats.m_featCleave < CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return m_baseStats.m_featBastardSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_featExtraRage < CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_featExtraShapeshifting < CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_featExtraSmiting < CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_featExtraTurning < CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return (m_baseStats.m_featAxe != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featAxe < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return (m_baseStats.m_featBow != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featBow < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return (m_baseStats.m_featFlail != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featFlail < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return (m_baseStats.m_featGreatSword != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featGreatSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return (m_baseStats.m_featHammer != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featHammer < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return (m_baseStats.m_featLargeSword != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featLargeSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return (m_baseStats.m_featPolearm != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featPolearm < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return (m_baseStats.m_featCrossbow != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featCrossbow < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return (m_baseStats.m_featMace != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featMace < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return (m_baseStats.m_featMissile != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featMissile < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return (m_baseStats.m_featQuarterStaff != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featQuarterStaff < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return (m_baseStats.m_featSmallBlade != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featSmallBlade < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return m_baseStats.m_featFocusEnchantment < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return m_baseStats.m_featFocusEvocation < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return m_baseStats.m_featFocusNecromancy < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return m_baseStats.m_featFocusTransmutation < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return m_baseStats.m_featSpellPenetration < CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return m_baseStats.m_featToughness < CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL
            && sub_763200(nFeatNumber, 1);
    }

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) != 0) {
        return FALSE;
    }

    if (a2) {
        return sub_763200(nFeatNumber, 1);
    }

    return TRUE;
}

// 0x763CB0
int CGameSprite::GetExtraFeats(BYTE nClass)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int classLevel = m_derivedStats.GetClassLevel(nClass);

    int feats = atol(ruleTables.m_tFeatLevel.GetAt(CPoint(0, m_derivedStats.m_nLevel - 1)));
    feats += atol(ruleTables.m_tFeatClass.GetAt(CPoint(nClass - 1, classLevel - 1)));

    if (m_derivedStats.m_nLevel == 1) {
        if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
            && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE) {
            feats++;
        } else if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HALFLING
            && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART) {
            feats++;
        }
    }

    return feats;
}

// 0x763DA0
int CGameSprite::GetExtraSkillPoints(BYTE nClass)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int sp = atol(ruleTables.m_tSkillPoints.GetAt(CPoint(nClass - 1, 0)));

    sp += ruleTables.GetAbilityScoreModifier(m_baseStats.m_INTBase);

    if (sp < 1) {
        sp = 1;
    }

    if (m_derivedStats.m_nLevel == 1) {
        sp *= 4;
    }

    if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
        && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE) {
        if (m_derivedStats.m_nLevel == 1) {
            sp++;
        }
        sp++;
    }

    return sp;
}

// 0x764270
void CGameSprite::SetSkillValue(UINT iSkillNumber, INT iSkillValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30424
    UTIL_ASSERT(iSkillValue >= 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30425
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    m_baseStats.m_skills[iSkillNumber] = static_cast<BYTE>(iSkillValue);
}

// 0x7642D0
INT CGameSprite::GetSkillValue(UINT iSkillNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30444
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    return m_baseStats.m_skills[iSkillNumber];
}

// 0x764310
INT CGameSprite::GetSkillCost(UINT iSkillNumber, BYTE nClass)
{
    INT iClassType;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30463
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int v1 = 0;
    int v2 = 0;
    int v3 = 0;

    // A way to bypass condition below without `goto`. Need a better
    // understanding of the calculations to get rid of it.
    // TODO: Review calculations.
    bool check = true;

    for (iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        if (m_derivedStats.HasClass(iClassType)) {
            INT nCost = atol(ruleTables.m_tSkillCosts.GetAt(CPoint(iClassType - 1, iSkillNumber)));
            if (nCost == 1) {
                v3 = 1;
                if (iClassType == nClass) {
                    v2 = 1;
                    check = false;
                    break;
                }

                if (v1 > 0) {
                    check = false;
                    break;
                }
            } else if (nCost == 2) {
                if (v3 == 0) {
                    v3 = 2;
                }

                if (iClassType == nClass) {
                    v2 = 2;
                    v1 = 2;
                }
            } else if (nCost > 2) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
                // __LINE__: 30508
                UTIL_ASSERT_MSG(FALSE, "Invalid Skill Cost (not 0, 1 or 2) in SKILCOST.2DA");
            }
        }
    }

    if (check) {
        if (v1 <= 0) {
            return v1;
        }
    }

    INT nLevels = 0;
    for (iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        INT nLevel = m_derivedStats.GetClassLevel(iClassType);
        if (nLevel > 0) {
            INT nCost = atol(ruleTables.m_tSkillCosts.GetAt(CPoint(iClassType - 1, iSkillNumber)));
            if (nCost > 0) {
                nLevels += nLevel;
            }
        }
    }

    if (m_baseStats.m_skills[iSkillNumber] < (nLevels + 3) / v3) {
        return v2;
    }

    return 0;
}

// 0x764520
INT CGameSprite::GetEffectiveCharacterLevel()
{
    INT nLevel = m_derivedStats.m_nLevel;

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            nLevel += 1;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            nLevel += 2;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_DWARF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_DWARF_GRAY:
            nLevel += 2;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_GNOME_DEEP:
            nLevel += 3;
            break;
        }
        break;
    }

    return nLevel;
}

// 0x764590
INT CGameSprite::GetRacialFavoredClass(DWORD& nSpecialization)
{
    INT iClass;

    nSpecialization = 0;

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            iClass = m_derivedStats.GetBestClass();
            if (m_derivedStats.m_nLevel == 0) {
                iClass = CAIOBJECTTYPE_C_FIGHTER;
            }
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
            iClass = CAIOBJECTTYPE_C_PALADIN;
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            iClass = CAIOBJECTTYPE_C_ROGUE;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            iClass = CAIOBJECTTYPE_C_WIZARD;
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            switch (m_typeAI.m_nGender) {
            case CAIOBJECTTYPE_SEX_MALE:
                iClass = CAIOBJECTTYPE_C_WIZARD;
                break;
            case CAIOBJECTTYPE_SEX_FEMALE:
                iClass = CAIOBJECTTYPE_C_CLERIC;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
                // __LINE__: 30684
                UTIL_ASSERT_MSG(FALSE, "Character has no gender");
            }
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_WILD:
            iClass = CAIOBJECTTYPE_C_SORCERER;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ELF:
        iClass = m_derivedStats.GetBestClass();
        if (m_derivedStats.m_nLevel == 0) {
            iClass = CAIOBJECTTYPE_C_FIGHTER;
        }
        break;
    case CAIOBJECTTYPE_R_DWARF:
        iClass = CAIOBJECTTYPE_C_FIGHTER;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
        case CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART:
            iClass = CAIOBJECTTYPE_C_ROGUE;
            break;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE:
            // TODO: This does not look right.
            iClass = CAIOBJECTTYPE_C_BARBARIAN;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        iClass = CAIOBJECTTYPE_C_WIZARD;
        nSpecialization = 0x400; // WIZARD_ILLUSIONIST
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        iClass = CAIOBJECTTYPE_C_BARBARIAN;
        break;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30733
    UTIL_ASSERT_MSG(iClass != 0, "GetRacialFavoredClass() returned 0!");

    return iClass;
}

// 0x7646E0
INT CGameSprite::GetMulticlassingPenalty()
{
    if (m_derivedStats.m_nLevel == 0) {
        return 0;
    }

    DWORD nSpecialization = 0;
    INT iExcludedRacialClass = 0;
    INT iRacialFavoredClass = GetRacialFavoredClass(nSpecialization);
    INT iBestClass = m_derivedStats.GetBestClass();

    if (iRacialFavoredClass == iBestClass
        && (nSpecialization == 0
            || (m_baseStats.m_specialization & nSpecialization) != 0)) {
        if (m_derivedStats.GetClassLevel(iBestClass) == m_derivedStats.m_nLevel) {
            // Means there is no multiclassing.
            return 0;
        }

        iExcludedRacialClass = iRacialFavoredClass;
        iBestClass = 0;
        for (INT iClass = 1; iClass <= CAIOBJECT_CLASS_MAX; iClass++) {
            if (iClass != iRacialFavoredClass) {
                if (m_derivedStats.GetClassLevel(iClass) != 0) {
                    if (iBestClass == 0
                        || m_derivedStats.GetClassLevel(iClass) > m_derivedStats.GetClassLevel(iBestClass)) {
                        iBestClass = iClass;
                    }
                }
            }
        }
    }

    INT nBestClassLevel = m_derivedStats.GetClassLevel(iBestClass);
    if (nBestClassLevel <= 2) {
        return 0;
    }

    INT nPenalty = 0;
    for (INT iClass = 1; iClass <= CAIOBJECT_CLASS_MAX; iClass++) {
        if (iClass != iExcludedRacialClass && iClass != iBestClass) {
            INT nClassLevel = m_derivedStats.GetClassLevel(iClass);
            if (nClassLevel != 0) {
                if (nBestClassLevel - nClassLevel > 1
                    && iClass != iRacialFavoredClass) {
                    nPenalty += 20;
                }
            }
        }
    }

    // 100% penalty, really?
    if (nPenalty > 100) {
        nPenalty = 100;
    }

    return nPenalty;
}

// 0x765BD0
void CGameSprite::SetColorRange(BYTE rangeValue)
{
    m_hasColorRangeEffects = TRUE;

    // NOTE: Uninline.
    m_animation.SetColorRangeAll(rangeValue);

    CColorRange* pColorRange = new CColorRange();
    pColorRange->m_range = -1;
    pColorRange->m_color = rangeValue;
    m_derivedStats.m_appliedColorRanges.AddTail(pColorRange);
}

// 0x765C50
void CGameSprite::DisplayFeats(CUIControlTextDisplay* pText)
{
    CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31489
    UTIL_ASSERT(pText != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31490
    UTIL_ASSERT(pEngine != NULL);

    for (int index = 0; index < CGAMESPRITE_FEAT_NUMFEATS; index++) {
        UINT nFeatNumber = ruleTables.GetFeatId(index);
        INT nFeatRank = GetFeatValue(nFeatNumber);
        if (nFeatRank > 0) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 29233
            UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

            if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) != 0) {
                switch (nFeatNumber) {
                case CGAMESPRITE_FEAT_ARMOR_PROF:
                case CGAMESPRITE_FEAT_ARMORED_ARCANA:
                case CGAMESPRITE_FEAT_CLEAVE:
                case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
                case CGAMESPRITE_FEAT_EXTRA_RAGE:
                case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
                case CGAMESPRITE_FEAT_EXTRA_SMITING:
                case CGAMESPRITE_FEAT_EXTRA_TURNING:
                case CGAMESPRITE_FEAT_MARTIAL_AXE:
                case CGAMESPRITE_FEAT_MARTIAL_BOW:
                case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
                case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
                case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
                case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
                case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
                case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
                case CGAMESPRITE_FEAT_SIMPLE_MACE:
                case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
                case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
                case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
                case CGAMESPRITE_FEAT_SPELL_PENETRATION:
                case CGAMESPRITE_FEAT_TOUGHNESS:
                    CBaldurEngine::UpdateText(pText,
                        "%s: %d",
                        (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)),
                        nFeatRank);
                    break;
                default:
                    CBaldurEngine::UpdateText(pText,
                        "%s",
                        (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)));
                    break;
                }
            } else {
                CBaldurEngine::UpdateText(pText,
                    "%s",
                    (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)));
            }
        }
    }
}

// 0x765E40
void CGameSprite::DisplaySkills(CUIControlTextDisplay* pText)
{
    CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31521
    UTIL_ASSERT(pText != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31522
    UTIL_ASSERT(pEngine != NULL);

    for (int index = 0; index < CGAMESPRITE_SKILL_NUMSKILLS; index++) {
        INT nSkillId = ruleTables.GetSkillId(index);
        if (m_baseStats.m_skills[nSkillId] == m_derivedStats.m_nSkills[nSkillId]) {
            if (m_derivedStats.m_nSkills[nSkillId] != 0) {
                CBaldurEngine::UpdateText(pText,
                    "%s: %d",
                    (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetSkillName(nSkillId)),
                    m_derivedStats.m_nSkills[nSkillId]);
            }
        } else {
            CBaldurEngine::UpdateText(pText,
                "%s: %d (%d)",
                (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetSkillName(nSkillId)),
                m_derivedStats.m_nSkills[nSkillId],
                m_baseStats.m_skills[nSkillId]);
        }
    }
}

// 0x766140
SHORT CGameSprite::JumpToArea(CString areaName, const CPoint& dest, SHORT facingDirection, SHORT delay)
{
    // TODO: Incomplete.

    return ACTION_ERROR;
}

// 0x766380
void CGameSprite::MoveOntoArea(CGameArea* pArea, const CPoint& dest, SHORT facingDirection)
{
    // TODO: Incomplete.
}

// 0x42FDC0
void CGameSprite::SetResRef(const CResRef& resRef)
{
    m_resRef = resRef;
}

// 0x453160
void CGameSprite::sub_453160(int a1)
{
    m_bHiding = a1;
}

// 0x453170
int CGameSprite::sub_453170()
{
    return m_bHiding;
}

// 0x453180
SHORT CGameSprite::GetSequence()
{
    return m_nSequence;
}

// 0x453190
CCreatureFileHeader* CGameSprite::GetBaseStats()
{
    return &m_baseStats;
}

// 0x4531A0
CDerivedStats* CGameSprite::GetDerivedStats()
{
    return &m_derivedStats;
}

// 0x4531B0
void CGameSprite::sub_4531B0()
{
    field_562C = 1;
}

// 0x4531C0
CGameEffectList* CGameSprite::GetEquipedEffectList()
{
    return &m_equipedEffectList;
}

// 0x4531D0
CGameEffectList* CGameSprite::GetTimedEffectList()
{
    return &m_timedEffectList;
}

// 0x4531E0
void CGameSprite::SetStealthGreyOut(LONG greyOut)
{
    m_nStealthGreyOut = greyOut;
}

// 0x4AEF20
void CGameSprite::AddPortraitIcon(int icon)
{
    if (m_portraitIcons.Find(reinterpret_cast<int*>(icon), 0) == NULL) {
        m_portraitIcons.AddTail(reinterpret_cast<int*>(icon));
    }
}

// NOTE: Inlined.
void CGameSprite::RemovePortraitIcon(int icon)
{
    POSITION pos = m_portraitIcons.Find(reinterpret_cast<int*>(icon), 0);
    if (pos != NULL) {
        m_portraitIcons.RemoveAt(pos);
    }
}

// 0x5F6810
CGameSpriteSpellList* CGameSprite::GetInnateSpells()
{
    return &m_innateSpells;
}

// 0x5F6820
CGameSpriteSpellList* CGameSprite::GetSongs()
{
    return &m_songs;
}

// 0x58FED0
CGameSpriteSpellList* CGameSprite::GetShapeshifts()
{
    return &m_shapeshifts;
}

// 0x5940D0
DWORD CGameSprite::sub_5940D0()
{
    return m_baseStats.m_specialization;
}

// 0x5940E0
INT CGameSprite::sub_5940E0(BYTE buttonNum)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2028
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_CUSTOM_BUTTONS22);

    return field_3D14[buttonNum];
}

// 0x594120
void CGameSprite::sub_594120(BYTE buttonNum, int a2)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2036
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_CUSTOM_BUTTONS22);

    field_3D14[buttonNum] = a2;
}

// 0x594160
BYTE CGameSprite::GetModalState()
{
    return m_nModalState;
}

// 0x45B710
int CGameSprite::sub_45B710()
{
    return field_70F2;
}

// 0x706D50
SHORT CGameSprite::GetDirection(const CPoint& target)
{
    if (m_pos == target) {
        return m_nNewDirection;
    }

    CPoint ptStart(m_pos.x, 4 * m_pos.y / 3);
    CPoint ptTarget(target.x, 4 * target.y / 3);
    return GetDirection(ptStart, ptTarget);
}

// 0x45B720
SHORT CGameSprite::GetDirection()
{
    return m_nDirection;
}

// 0x706DD0
SHORT CGameSprite::GetDirection(const CPoint& ptStart, const CPoint& ptTarget)
{
    LONG dx;
    LONG dy;

    if (ptStart == ptTarget) {
        return 0;
    }

    if (ptTarget.y < ptStart.y) {
        if (ptTarget.x < ptStart.x) {
            dx = ptStart.x - ptTarget.y;
            dy = ptStart.y - ptTarget.y;

            if (27 * dy <= 6 * dx) {
                return 4;
            } else if (27 * dy <= 16 * dx) {
                return 6;
            } else if (24 * dy <= 38 * dx) {
                return 6;
            } else if (7 * dy <= 38 * dx) {
                return 7;
            } else {
                return 8;
            }
        } else {
            dx = ptTarget.x - ptStart.x;
            dy = ptStart.y - ptTarget.y;

            if (27 * dy <= 6 * dx) {
                return 12;
            } else if (27 * dy <= 16 * dx) {
                return 11;
            } else if (24 * dy <= 38 * dx) {
                return 10;
            } else if (7 * dy <= 38 * dx) {
                return 9;
            } else {
                return 8;
            }
        }
    } else {
        if (ptTarget.x < ptStart.x) {
            dx = ptStart.x - ptTarget.x;
            dy = ptTarget.y - ptStart.y;

            if (27 * dy <= 6 * dx) {
                return 4;
            } else if (27 * dy <= 16 * dx) {
                return 3;
            } else if (24 * dy <= 38 * dx) {
                return 2;
            } else if (7 * dy <= 38 * dx) {
                return 1;
            } else {
                return 0;
            }
        } else {
            dx = ptTarget.x - ptStart.x;
            dy = ptTarget.y - ptStart.y;

            if (27 * dy <= 6 * dx) {
                return 12;
            } else if (27 * dy <= 16 * dx) {
                return 13;
            } else if (24 * dy <= 38 * dx) {
                return 14;
            } else if (7 * dy <= 38 * dx) {
                return 15;
            } else {
                return 0;
            }
        }
    }
}

// 0x45B730
CGameAnimation* CGameSprite::GetAnimation()
{
    return &m_animation;
}

// 0x45B740
CGameSpriteEquipment* CGameSprite::GetEquipment()
{
    return &m_equipment;
}

// 0x45B750
SHORT CGameSprite::GetHappiness()
{
    return m_nHappiness;
}

// 0x45B760
BOOL CGameSprite::GetActive()
{
    return m_active;
}

// 0x45B770
CVariableHash* CGameSprite::GetLocalVariables()
{
    return m_pLocalVariables;
}

// 0x724010
INT CGameSprite::sub_724010(INT a1)
{
    CItem* pItem = m_equipment.m_items[1];
    if (pItem == NULL) {
        return 1;
    }

    switch (pItem->GetItemType()) {
    case 60:
        return min(6, a1);
    case 61:
        return min(5, a1);
    case 62:
        return min(2, a1);
    case 63:
    case 64:
        return min(0, a1);
    case 65:
        return min(1, a1);
    case 66:
        return min(4, a1);
    case 68:
        return min(3, a1);
    default:
        return a1;
    }
}

// 0x7240A0
INT CGameSprite::sub_7240A0()
{
    CItem* pItem = m_equipment.m_items[1];
    if (pItem == NULL) {
        return 0;
    }

    INT v1 = 0;

    INT nItemType = pItem->GetItemType();
    INT nFeatValue = GetFeatValue(CGAMESPRITE_FEAT_ARMOR_PROF);
    switch (nItemType) {
    case 60:
        if (nFeatValue >= 1) {
            return v1;
        }
        return 0;
    case 61:
        if (nFeatValue >= 1) {
            return v1;
        }
        v1 = -1;
        break;
    case 62:
        if (nFeatValue >= 2) {
            return v1;
        }
        v1 = -5;
        break;
    case 63:
    case 64:
        if (nFeatValue >= 3) {
            return v1;
        }
        v1 = -7;
        break;
    case 65:
        if (nFeatValue >= 3) {
            return v1;
        }
        v1 = -6;
        break;
    case 66:
        if (nFeatValue >= 2) {
            return v1;
        }
        v1 = -3;
        break;
    case 68:
        if (nFeatValue >= 3) {
            return v1;
        }
        v1 = -4;
        break;
    default:
        return v1;
    }

    if ((pItem->m_flags & 0x8) != 0) {
        v1++;
    }

    return v1;
}

// 0x724170
INT CGameSprite::sub_724170()
{
    INT nSlot = 2 * (m_nWeaponSet + 22);
    CItem* pItem = m_equipment.m_items[nSlot];
    if (pItem == NULL) {
        return 0;
    }

    INT v1 = 0;

    INT nItemType = pItem->GetItemType();
    if (GetFeatValue(CGAMESPRITE_FEAT_SHIELD_PROF) < 1) {
        switch (nItemType) {
        case 41:
            if (pItem->GetResRef() != CResRef("00BARD04")
                && pItem->GetResRef() != CResRef("00HFBD04")) {
                v1 = -1;
                if ((pItem->m_flags & 0x8) != 0) {
                    v1++;
                }
            }
            break;
        case 47:
        case 49:
            v1 = -2;
            if ((pItem->m_flags & 0x8) != 0) {
                v1++;
            }
            break;
        case 53:
            v1 = -1;
            if ((pItem->m_flags & 0x8) != 0) {
                v1++;
            }
            break;
        }
    }

    return v1;
}

// 0x724270
INT CGameSprite::sub_724270()
{
    INT nSlot = 2 * (m_nWeaponSet + 22);
    CItem* pItem = m_equipment.m_items[nSlot];
    if (pItem == NULL) {
        return 0;
    }

    switch (pItem->GetItemType()) {
    case 41:
        if (pItem->GetResRef() != CResRef("00BARD04")
            && pItem->GetResRef() != CResRef("00HFBD04")) {
            return 5;
        }
        return 0;
    case 47:
        return 50;
    case 49:
        return 15;
    case 53:
        return 5;
    default:
        return 0;
    }
}

// 0x724360
INT CGameSprite::sub_724360()
{
    CItem* pItem = m_equipment.m_items[1];
    if (pItem == NULL) {
        return 0;
    }

    switch (pItem->GetItemType()) {
    case 60:
        return 10;
    case 61:
        return 15;
    case 62:
        return 30;
    case 63:
    case 64:
        return 40;
    case 65:
        return 35;
    case 66:
        return 20;
    case 68:
        return 25;
    default:
        return 0;
    }
}

// 0x7243F0
BOOL CGameSprite::CheckAranceFailure(INT nRoll)
{
    INT nFailureChance = sub_724430();

    if (nRoll >= nFailureChance) {
        return FALSE;
    }

    // "Spell Failure check: Roll d100 %d vs. Spell failure chance %d"
    FeedBack(83, nRoll, nFailureChance, 0, 40955, 0, 0);

    return TRUE;
}

// 0x724430
int CGameSprite::sub_724430()
{
    INT nMod = 0;

    if (m_derivedStats.m_spellStates[SPLSTATE_MENTAL_DOMINATION]) {
        nMod = 100;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_BLINK]) {
        nMod += 20;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_DEAFENED]) {
        nMod += 20;
    }

    INT nFailureChance = m_derivedStats.m_nSpellFailureArcane
        + nMod
        + sub_724360()
        + sub_724270();

    if (sub_763150(CGAMESPRITE_FEAT_ARMORED_ARCANA)) {
        nFailureChance -= 5 * GetFeatValue(CGAMESPRITE_FEAT_ARMORED_ARCANA);
    }

    if (nFailureChance > 100) {
        nFailureChance = 100;
    } else if (nFailureChance < 0) {
        nFailureChance = 0;
    }

    return nFailureChance;
}

// 0x724540
BOOL CGameSprite::CheckDivineFailure(INT nRoll)
{
    INT nMod = 0;

    if (m_derivedStats.m_spellStates[SPLSTATE_MENTAL_DOMINATION]) {
        nMod = 100;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_BLINK]) {
        nMod += 20;
    }

    if (m_derivedStats.m_spellStates[SPLSTATE_DEAFENED]) {
        nMod += 20;
    }

    INT nFailureChance = m_derivedStats.m_nSpellFailureDivine + nMod;
    if (nFailureChance > 100) {
        nFailureChance = 100;
    } else if (nFailureChance < 0) {
        nFailureChance = 0;
    }

    if (nRoll >= nFailureChance) {
        return FALSE;
    }

    // "Spell Failure check: Roll d100 %d vs. Spell failure chance %d"
    FeedBack(FEEDBACK_ROLL, nRoll, nFailureChance, 0, 40955, 0, 0);

    return TRUE;
}

// 0x7245D0
BOOLEAN CGameSprite::sub_7245D0()
{
    return m_derivedStats.m_spellStates[SPLSTATE_HELD]
        || m_derivedStats.m_spellStates[SPLSTATE_HOPELESSNESS]
        || m_derivedStats.m_spellStates[SPLSTATE_OTILUKES_RESILIENT_SPHERE];
}

// 0x7245F0
INT CGameSprite::GetNextHatedRacesSlot()
{
    INT nIndex;

    for (nIndex = 0; nIndex < MAX_HATED_RACES; nIndex++) {
        if (m_baseStats.m_favoredEnemies[nIndex] == CAIObjectType::R_NO_RACE) {
            break;
        }
    }

    return nIndex;
}

// 0x724610
void CGameSprite::ResetQuickSlots()
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    INT nClass = m_derivedStats.GetBestClass() - 1;

    for (int nSlot = 0; nSlot < CGAMESAVECHARACTER_NUM_CUSTOM_BUTTONS22; nSlot++) {
        if (field_3D14[nSlot] == 0) {
            field_3D14[nSlot] = atol(ruleTables.m_tQuickSlots.GetAt(CPoint(nSlot, nClass)));
        }
    }
}

// 0x724690
BOOL CGameSprite::sub_724690(SHORT a1)
{
    CItem* pItem = m_equipment.m_items[1];
    if (pItem == NULL) {
        return FALSE;
    }

    WORD nItemType = pItem->GetItemType();
    switch (a1) {
    case 0:
        switch (nItemType) {
        case 67:
            return TRUE;
        }
        break;
    case 1:
        switch (nItemType) {
        case 60:
        case 61:
            return TRUE;
        }
        break;
    case 2:
        switch (nItemType) {
        case 62:
        case 66:
        case 68:
            return TRUE;
        }
        break;
    case 3:
        switch (nItemType) {
        case 63:
        case 64:
        case 65:
            return TRUE;
        }
        break;
    }

    return FALSE;
}

// FIXME: `nClass` should not be reference.
//
// 0x724730
CGameSpriteGroupedSpellList* CGameSprite::GetSpells(const BYTE& nClass)
{
    UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25826
    UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

    return &(m_spells.m_spellsByClass[nClassIndex]);
}

// FIXME: `nClass` should not be reference.
// FIXME: `nLevel` should not be reference.
//
// 0x724790
CGameSpriteSpellList* CGameSprite::GetSpellsAtLevel(const BYTE& nClass, const UINT& nLevel)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25835
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25838
    UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 2521
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    return &(m_spells.m_spellsByClass[nClassIndex].m_lists[nLevel]);
}

// 0x724840
UINT CGameSprite::GetNumSpells()
{
    UINT nCount = 0;

    for (int index = 0; index < CSPELLLIST_NUM_CLASSES; index++) {
        // NOTE: Uninline.
        nCount += m_spells.m_spellsByClass[index].GetNumSpells();
    }

    // NOTE: Uninline.
    nCount += m_domainSpells.GetNumSpells();

    return nCount;
}

// 0x724900
BOOLEAN CGameSprite::sub_724900()
{
    DWORD dwClassMask = GetAIType().m_nClassMask;

    return (dwClassMask & (CLASSMASK_BARD | CLASSMASK_CLERIC | CLASSMASK_DRUID | CLASSMASK_PALADIN | CLASSMASK_RANGER)) != 0
        || (dwClassMask & (CLASSMASK_SORCERER | CLASSMASK_WIZARD)) != 0;
}

// 0x724920
BOOLEAN CGameSprite::sub_724920()
{
    return (GetAIType().m_nClassMask & CLASSMASK_BARD) != 0;
}

// FIXME: Review references (latter params unclear).
//
// 0x724930
BOOLEAN CGameSprite::AddKnownSpell(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5, const unsigned int& a6)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25936
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    CGameSpriteGroupedSpellList* pSpellsByLevel = m_spells.Get(nClassIndex);

    // NOTE: Uninline.
    return pSpellsByLevel->Add(nID, nSpellLevel, a4, a5, a6);
}

// 0x724A40
BOOLEAN CGameSprite::AddDomainSpell(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25954
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    m_domainSpells.Add(nID, nSpellLevel, a3, a4, a5);

    return TRUE;
}

// 0x724B10
BOOLEAN CGameSprite::AddInnateSpell(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    m_innateSpells.Add(nID, a2, a3, a4);

    return TRUE;
}

// 0x724B70
BOOLEAN CGameSprite::AddSong(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetMasterSongLookup().Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    m_songs.Add(nID, a2, a3, a4);

    return TRUE;
}

// 0x724BD0
BOOLEAN CGameSprite::AddShapeshift(const CResRef& resRef, const unsigned int& a2)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetShapeshifts()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    m_shapeshifts.Add(nID, 0, 0, a2);

    return TRUE;
}

// 0x724C40
BOOLEAN CGameSprite::sub_724C40(const unsigned int& a1)
{
    m_shapeshifts.field_14 += a1;

    for (UINT nIndex = 0; nIndex < m_shapeshifts.m_List.size(); nIndex++) {
        CGameSpriteSpellListEntry* pEntry = m_shapeshifts.Get(nIndex);

        m_shapeshifts.Add(pEntry->m_nID,
            m_shapeshifts.field_14 - pEntry->field_4,
            0,
            0);
    }

    return FALSE;
}

// 0x724D30
BOOLEAN CGameSprite::RemoveKnownSpell(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5, const unsigned int& a6)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 25954
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

    UINT nID;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    CGameSpriteGroupedSpellList* pSpellsByLevel = m_spells.Get(nClassIndex);

    return pSpellsByLevel->Remove(nID, nSpellLevel, a4, a5, a6);
}

// 0x724E00
BOOLEAN CGameSprite::RemoveDomainSpell(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26073
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    if (!m_derivedStats.HasClass(CAIOBJECTTYPE_C_CLERIC)) {
        return FALSE;
    }

    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    return m_domainSpells.Remove(nID, nSpellLevel, a3, a4, a5);
}

// 0x724EA0
BOOLEAN CGameSprite::RemoveInnateSpell(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    return m_innateSpells.Remove(nID, a2, a3, a4);
}

// 0x724F00
BOOLEAN CGameSprite::RemoveSong(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetMasterSongLookup().Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    return m_songs.Remove(nID, a2, a3, a4);
}

// 0x724F60
BOOLEAN CGameSprite::RemoveShapeshift(const CResRef& resRef)
{
    UINT nID = 0;
    if (g_pBaldurChitin->GetObjectGame()->GetShapeshifts()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    return m_shapeshifts.Remove(nID, 1, 0, 0);
}

// 0x724FD0
BOOLEAN CGameSprite::sub_724FD0(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26177
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    UINT nClassIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterIndex(nClass);

    UINT nID;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    CGameSpriteGroupedSpellList* pSpellsByLevel = m_spells.Get(nClassIndex);

    // NOTE: Uninline.
    return pSpellsByLevel->sub_7260B0(nID, nSpellLevel, a4, a5);
}

// 0x725110
BOOLEAN CGameSprite::sub_725110(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26211
    UTIL_ASSERT(nSpellLevel < CSPELLLIST_MAX_LEVELS);

    UINT nID;
    if (g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    CGameSpriteSpellList* pList = m_domainSpells.GetSpellsAtLevel(nSpellLevel);

    // NOTE: Uninline.
    return pList->sub_725CC0(nID, a4, a5);
}

// 0x725210
BOOLEAN CGameSprite::sub_725210(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3)
{
    UINT nID;
    if (g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    return m_innateSpells.sub_725C50(nID, a2, a3);
}

// 0x725270
BOOLEAN CGameSprite::sub_725270(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3)
{
    UINT nID;
    if (g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Find(resRef, nID) != TRUE) {
        return FALSE;
    }

    // NOTE: Uninline.
    return m_innateSpells.sub_725CC0(nID, a2, a3);
}

// FIXME: `dwClassMask` should not be reference.
//
// 0x725330
BOOLEAN CGameSprite::sub_725330(const CResRef& resRef, const DWORD& dwClassMask, UINT nLevel, BOOLEAN a4)
{
    BOOLEAN v1 = FALSE;
    UINT nStartLevel = 0;
    UINT nEndLevel = 9;

    if (nLevel < CSPELLLIST_MAX_LEVELS) {
        nStartLevel = nLevel;
        nStartLevel = nLevel + 1;
    }

    UINT nID;
    if (!g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID)) {
        return FALSE;
    }

    for (UINT nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        if (v1) {
            break;
        }

        if ((g_pBaldurChitin->GetObjectGame()->GetSpellcasterClassMask(nClassIndex) & dwClassMask) != 0) {
            for (UINT nCurrLevel = nStartLevel; nCurrLevel < nEndLevel; nCurrLevel++) {
                if (v1) {
                    break;
                }

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 26902
                UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 26903
                UTIL_ASSERT(nCurrLevel < CSPELLLIST_MAX_LEVELS);

                UINT nIndex = 0;
                v1 = m_spells.m_spellsByClass[nClassIndex].m_lists[nCurrLevel].Find(nID, nIndex);
                if (v1 == TRUE && a4 == TRUE) {
                    // __FILE__: .\Include\FileFormat.h
                    // __LINE__: 2565
                    UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

                    // NOTE: Uninline.
                    v1 = m_spells.m_spellsByClass[nClassIndex].m_lists[nCurrLevel].CheckF8(nIndex);
                }
            }
        }
    }

    if (!v1) {
        if ((dwClassMask & CLASSMASK_CLERIC) == CLASSMASK_CLERIC) {
            for (UINT nCurrLevel = nStartLevel; nCurrLevel < nEndLevel; nCurrLevel++) {
                if (v1) {
                    break;
                }

                UINT nIndex = 0;

                // NOTE: Uninline.
                v1 = m_domainSpells.Find(nID, nStartLevel, nIndex);
                if (v1 == TRUE && a4 == TRUE) {
                    // NOTE: Uninline.
                    v1 = m_innateSpells.CheckF8(nIndex);
                }
            }
        }
    }

    return v1;
}

// 0x7256B0
BOOLEAN CGameSprite::sub_7256B0(const CResRef& resRef, const UINT& nLevel, BOOLEAN a3)
{
    BOOLEAN v1 = FALSE;
    UINT nStartLevel = 0;
    UINT nEndLevel = 9;

    if (nLevel < CSPELLLIST_MAX_LEVELS) {
        nStartLevel = nLevel;
        // TODO: Looks odd, should it be `nLevel + 1` as in the function above
        // (0x725330) to check only one specific level?
        nEndLevel = nLevel - 1;
    }

    UINT nID;
    if (!g_pBaldurChitin->GetObjectGame()->m_spells.Find(resRef, nID)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 26395
        UTIL_ASSERT(FALSE);
    }

    for (UINT nCurrLevel = nStartLevel; nCurrLevel < nEndLevel; nCurrLevel++) {
        if (v1) {
            break;
        }

        UINT nIndex;

        // NOTE: Uninline.
        v1 = m_domainSpells.Find(nID, nStartLevel, nIndex);
        if (v1 == TRUE && a3 == TRUE) {
            // NOTE: Uninline.
            v1 = m_innateSpells.CheckF8(nIndex);
        }
    }

    return v1;
}

// 0x725840
BOOLEAN CGameSprite::sub_725840(const CResRef& resRef, BOOLEAN a2)
{
    UINT nID;
    if (!g_pBaldurChitin->GetObjectGame()->GetInnateSpells()->Find(resRef, nID)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 26420
        UTIL_ASSERT(FALSE);
    }

    UINT nIndex;
    BOOLEAN v1 = m_innateSpells.Find(nID, nIndex);

    if (v1 && a2 == TRUE) {
        v1 = m_innateSpells.CheckF8(nIndex);
    }

    return v1;
}

// 0x726270
INT CGameSprite::sub_726270(UINT nFeatNumber)
{
    INT v1 = 0;
    if (sub_763150(nFeatNumber)) {
        switch (nFeatNumber) {
        case CGAMESPRITE_FEAT_ARTERIAL_STRIKE:
            v1 = field_4C54[2];
            break;
        case CGAMESPRITE_FEAT_EXPERTISE:
            v1 = field_4C54[0];
            break;
        case CGAMESPRITE_FEAT_HAMSTRING:
            v1 = field_4C54[3];
            break;
        case CGAMESPRITE_FEAT_POWER_ATTACK:
            v1 = field_4C54[1];
            break;
        case CGAMESPRITE_FEAT_RAPID_SHOT:
            v1 = field_4C54[4];
            break;
        }
    }
    return v1;
}

// 0x726330
void CGameSprite::sub_726330(UINT nFeatNumber, INT nValue)
{
    if (sub_763150(nFeatNumber)) {
        switch (nFeatNumber) {
        case CGAMESPRITE_FEAT_ARTERIAL_STRIKE:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26976
            UTIL_ASSERT_MSG(nValue >= 0, "Invalid feat level.");

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26977
            UTIL_ASSERT_MSG(nValue <= 1, "Invalid feat level.");

            field_4C54[2] = nValue;
            field_4C54[3] = 0;
            break;
        case CGAMESPRITE_FEAT_EXPERTISE:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26962
            UTIL_ASSERT_MSG(nValue >= 0, "Invalid feat level.");

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26963
            UTIL_ASSERT_MSG(nValue <= MAX_SELECTABLE_FEAT_USE_LEVELS, "Invalid feat level.");

            field_4C54[0] = nValue;
            field_4C54[1] = 0;
            break;
        case CGAMESPRITE_FEAT_HAMSTRING:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26983
            UTIL_ASSERT_MSG(nValue >= 0, "Invalid feat level.");

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26984
            UTIL_ASSERT_MSG(nValue <= 1, "Invalid feat level.");

            field_4C54[3] = nValue;
            field_4C54[2] = 0;
            break;
        case CGAMESPRITE_FEAT_POWER_ATTACK:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26969
            UTIL_ASSERT_MSG(nValue >= 0, "Invalid feat level.");

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26970
            UTIL_ASSERT_MSG(nValue <= MAX_SELECTABLE_FEAT_USE_LEVELS, "Invalid feat level.");

            field_4C54[1] = nValue;
            field_4C54[0] = 0;
            break;
        case CGAMESPRITE_FEAT_RAPID_SHOT:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26990
            UTIL_ASSERT_MSG(nValue >= 0, "Invalid feat level.");

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 269991
            UTIL_ASSERT_MSG(nValue <= 1, "Invalid feat level.");

            field_4C54[4] = nValue;
            break;
        }
    }
}

// 0x726570
void CGameSprite::sub_726570()
{
    ITEM_EFFECT effect;
    CGameEffect* pEffect;
    CMessageAddEffect* pMessage;

    if (field_4C54[1] > 0) {
        CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_FEATPOWERATTACK);
        pEffect = CGameEffect::DecodeEffect(&effect, m_pos, m_id, CPoint(-1, -1));
        pMessage = new CMessageAddEffect(pEffect, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }

    if (field_4C54[0] > 0) {
        CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_FEATEXPERTISE);
        pEffect = CGameEffect::DecodeEffect(&effect, m_pos, m_id, CPoint(-1, -1));
        pMessage = new CMessageAddEffect(pEffect, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }

    if (field_4C54[2] > 0) {
        CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_FEATARTERIALSTRIKE);
        pEffect = CGameEffect::DecodeEffect(&effect, m_pos, m_id, CPoint(-1, -1));
        pMessage = new CMessageAddEffect(pEffect, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }

    if (field_4C54[3] > 0) {
        CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_FEATHAMSTRING);
        pEffect = CGameEffect::DecodeEffect(&effect, m_pos, m_id, CPoint(-1, -1));
        pMessage = new CMessageAddEffect(pEffect, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }

    if (field_4C54[4] > 0) {
        CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_FEATRAPIDSHOT);
        pEffect = CGameEffect::DecodeEffect(&effect, m_pos, m_id, CPoint(-1, -1));
        pMessage = new CMessageAddEffect(pEffect, m_id, m_id);
        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }
}

// 0x726800
INT CGameSprite::sub_726800()
{
    return 2 * m_nWeaponSet + 44;
}

// 0x726810
void CGameSprite::sub_726810(BYTE nWeaponSet)
{
    // TODO: Incomplete.
}

// 0x58FEE0
BYTE CGameSprite::GetLastSong()
{
    return m_nLastSong;
}

// NOTE: Inlined.
void CGameSprite::GetQuickItem(BYTE buttonNum, CButtonData& buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2022
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_ITEMS22);

    CheckToolTipItem(buttonNum);

    buttonData = m_quickItems[buttonNum];
}

// NOTE: Inlined.
void CGameSprite::GetQuickSpell(BYTE buttonNum, CButtonData& buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2023
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_SPELLS22);

    buttonData = m_quickSpells[buttonNum];
}

// NOTE: Inlined.
void CGameSprite::GetQuickAbility(BYTE buttonNum, CButtonData& buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2024
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_ABILITIES22);

    buttonData = m_quickInnates[buttonNum];
}

// NOTE: Inlined.
void CGameSprite::GetQuickSong(BYTE buttonNum, CButtonData& buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2025
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_SONGS22);

    buttonData = m_quickSongs[buttonNum];
}

// FIXME: `buttonData` should be reference.
//
// NOTE: Inlined.
void CGameSprite::SetQuickWeapon(BYTE buttonNum, CButtonData buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2030
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_WEAPONS22);

    m_quickWeapons[buttonNum] = buttonData;
}

// NOTE: Inlined.
void CGameSprite::SetQuickWeapon(BYTE buttonNum, BYTE index)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2031
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_WEAPONS22);

    field_3D3A[buttonNum] = index;
}

// FIXME: `buttonData` should be reference.
//
// NOTE: Inlined.
void CGameSprite::SetQuickItem(BYTE buttonNum, CButtonData buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2032
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_ITEMS22);

    m_quickItems[buttonNum] = buttonData;
}

// FIXME: `buttonData` should be reference.
//
// NOTE: Inlined.
void CGameSprite::SetQuickSpell(BYTE buttonNum, CButtonData buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2033
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_SPELLS22);

    m_quickSpells[buttonNum] = buttonData;
}

// FIXME: `buttonData` should be reference.
//
// NOTE: Inlined.
void CGameSprite::SetQuickAbility(BYTE buttonNum, CButtonData buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2034
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_ABILITIES22);

    m_quickInnates[buttonNum] = buttonData;
}

// FIXME: `buttonData` should be reference.
//
// NOTE: Inlined.
void CGameSprite::SetQuickSong(BYTE buttonNum, CButtonData buttonData)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 2035
    UTIL_ASSERT(buttonNum < CGAMESAVECHARACTER_NUM_QUICK_SONGS22);

    m_quickSongs[buttonNum] = buttonData;
}

// NOTE: Inlined.
CDerivedStats* CGameSprite::GetActiveStats()
{
    if (m_bAllowEffectListCall) {
        return &m_derivedStats;
    } else {
        return &m_tempStats;
    }
}

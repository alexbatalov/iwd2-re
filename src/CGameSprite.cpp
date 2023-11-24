#include "CGameSprite.h"

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CGameArea.h"
#include "CGameButtonList.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenCharacter.h"
#include "CScreenCreateChar.h"
#include "CScreenInventory.h"
#include "CScreenWorld.h"
#include "CSpell.h"
#include "CUtil.h"
#include "CVariableHash.h"
#include "IcewindCGameEffects.h"
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

// 0x85BB6C
const BYTE CGameSprite::SOUND_SELECT = 9;

// 0x85BB6E
const BYTE CGameSprite::SOUND_SELECT_ACTION = 11;

// 0x85BB70
const BYTE CGameSprite::SOUND_REACT_TO_DEATH = 13;

// 0x85BB74
const SHORT CGameSprite::EXACT_SCALE = 10;

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

// 0x85BCA0
const LONG CGameSprite::STANDARD_VERBAL_CONSTANT_LENGTH = 300;

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

// 0x8F950C
BOOLEAN CGameSprite::SHOW_CHARACTER_HP;

// 0x8F950D
BOOLEAN CGameSprite::GRAVITY_IS_DOWN;

// 0x8B85E0
INT CGameSprite::m_bRollFeedbackEnabled = -1;

// 0x6EF990
CGameSprite::CGameSprite(BYTE* pCreature, LONG creatureSize, int a3, WORD type, DWORD expirationTime, WORD huntingRange, WORD followRange, DWORD timeOfDayVisible, CPoint startPos, WORD facing)
{
    int index;

    field_7540 = 0;
    field_7544 = 0;
    field_5101 = 0;
    field_5102 = 0;
    field_5103 = 0;
    m_bEscapingArea = 0;
    field_4D32 = 0;
    field_4DFE = 0;
    field_5320 = 0;
    m_animationRunning = FALSE;
    field_5326 = 0;
    field_533E = 0;
    field_533C = 0;
    field_5340 = 0;
    field_5344 = 0;
    m_skipDeltaDirection = 0;
    m_deltaDirection = 0;
    m_walkBackwards = 0;
    field_53C6 = 0;
    field_54EE = 0;
    field_54F4 = 0;
    field_556E = 0;
    field_5572 = 0;
    m_posLastVisMapEntry.x = 0;
    m_posLastVisMapEntry.y = 0;
    m_nCommandPause = 0;
    field_557A = 0;
    field_557E = 0;
    field_558E = 0;
    field_559E = 0;
    field_55A0 = 0;
    field_5604 = 0;
    field_5606 = 0;
    field_560E = 0;
    field_5610 = 0;
    field_5618 = 0;
    field_561C = 0;
    field_5624 = 0;
    field_5630 = 0;
    field_5632 = 0;
    field_5636 = 0;
    field_7118 = 0;
    field_711C = 0;
    m_firstActionSound = FALSE;
    field_7292 = 0;
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
    field_532C = 0;
    field_5330 = 0;
    field_5334 = 0;
    field_5338 = 1.875;
    m_bGlobal = FALSE;
    field_534A = 0;
    field_534E = 0;
    field_5352 = 0;
    field_5356 = 0;
    m_posDest.x = 0;
    m_posDest.y = 0;
    field_5362.x = 0;
    field_5362.y = 0;
    field_536A = 0;
    field_536E = 0;
    m_nSequence = -1;
    m_nNewDirection = facing & 0xF;
    m_nDirection = facing & 0xF;
    m_pPath = 0;
    m_nPath = 0;
    m_currPath = 0;
    field_53CE = 0;
    field_54F2 = 17;
    field_53D2 = 0;
    m_currentSearchRequest = 0;
    field_4BB4 = 0;
    field_56EC = 0;
    m_removeFromArea = FALSE;
    m_talkingCounter = 0;
    field_54F6 = 0;
    field_54F8 = 0;
    m_curResponseNum = -1;
    m_curResponseSetNum = -1;
    m_curScriptNum = -1;
    m_curAction = CAIAction::NULL_ACTION;
    m_interrupt = FALSE;
    field_5608 = 0;
    m_inFormation = FALSE;
    m_lastRGBColor = 0x8000;
    m_bVisibilityUpdated = TRUE;
    m_targetId = (int)CGameObjectArray::INVALID_INDEX;
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
    field_54BC = 0;
    field_54C0 = 0;
    field_54C4 = (int)CGameObjectArray::INVALID_INDEX;
    m_followStart = 0;
    m_userCommandPause = 0;
    field_5620 = 0;
    field_561E = 0;
    field_44A = 0;
    field_54C = 0;
    field_560C = 0;
    field_5616 = 0;
    field_5612 = 0;
    field_5614 = 0;
    field_54E8 = -1;
    field_54EA = 0;
    field_5622 = -2;
    field_72A2 = 0;
    m_bAllowEffectListCall = TRUE;
    field_72AA = 0;
    field_7292 = 0;
    field_5582 = 0;
    field_9D14 = 0;
    field_9D15 = 0;
    m_hasColorEffects = FALSE;
    m_hasColorRangeEffects = FALSE;
    field_5640 = 0;
    m_groupPosition = 0;
    m_groupMove = 0;
    field_562C = 0;
    field_5592 = 0;
    field_5596 = 0;
    field_559A = 0;
    m_nNumberOfTimesTalkedTo = 0;
    field_4FF8 = 0;
    field_710A = 0;
    field_710C = 0;
    field_710E = 0;
    field_7110 = 0x7FFF;
    m_moraleFailure = FALSE;
    m_nHappiness = 0;
    m_bHappinessChanged = FALSE;
    field_72AE = 1;
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
    field_54AC = 0;
    field_54B0 = -1;
    field_54B4 = -1;
    field_54A4 = 0;
    m_bSelected = FALSE;
    field_50BA = 0;
    field_50B6 = 0;
    field_53DA = 0;
    field_53DC = 0;
    field_53DE = 0x1E1EFF;
    field_53E2 = 0;
    field_53E6 = 0;
    field_50FE = 0;

    // NOTE: See `CGameArea` note on default terrain tables.
    memcpy(m_terrainTable, DEFAULT_TERRAIN_TABLE, 16);
    memcpy(m_visibleTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);
    memcpy(m_flightTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);

    if (g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id, this, INFINITE) == CGameObjectArray::SUCCESS) {
        m_pSpriteEffectArray = NULL;
        m_pSpriteEffectArrayPosition = NULL;
        m_spriteEffectDuration = 0;
        field_5202 = 0;
        field_5304 = 0;
        field_532A = 3;
        m_nModalState = 0;
        field_4C54[0] = 0;
        field_4C54[1] = 0;
        field_4C54[2] = 0;
        field_4C54[3] = 0;
        field_4C54[4] = 0;
        m_nWeaponSet = 0;

        field_7548[0].SetResRef(CResRef("SanctuC"), FALSE, TRUE, TRUE);
        field_7548[1].SetResRef(CResRef("EntangC"), FALSE, TRUE, TRUE);
        field_7548[6].SetResRef(CResRef("MGoInvC"), FALSE, TRUE, TRUE);
        field_7548[3].SetResRef(CResRef("ShieldC"), FALSE, TRUE, TRUE);
        field_7548[4].SetResRef(CResRef("GreaseC"), FALSE, TRUE, TRUE);
        field_7548[5].SetResRef(CResRef("WebC"), FALSE, TRUE, TRUE);
        field_7548[7].SetResRef(CResRef("GoInvuC"), FALSE, TRUE, TRUE);
        field_7548[8].SetResRef(CResRef("SoFlamC"), FALSE, TRUE, TRUE);
        field_7548[9].SetResRef(CResRef("AMShelC"), FALSE, TRUE, TRUE);
        field_7548[10].SetResRef(CResRef("ORSpheC"), FALSE, TRUE, TRUE);
        field_7548[11].SetResRef(CResRef("PFNMisC"), FALSE, TRUE, TRUE);
        field_7548[12].SetResRef(CResRef("CoFearC"), FALSE, TRUE, TRUE);
        field_7548[13].SetResRef(CResRef("EShielC"), FALSE, TRUE, TRUE);
        field_7548[14].SetResRef(CResRef("FiAuraC"), FALSE, TRUE, TRUE);
        field_7548[15].SetResRef(CResRef("FrAuraC"), FALSE, TRUE, TRUE);
        field_7548[16].SetResRef(CResRef("IPlaguC"), FALSE, TRUE, TRUE);
        field_7548[17].SetResRef(CResRef("SShellC"), FALSE, TRUE, TRUE);
        field_7548[18].SetResRef(CResRef("SoLatC1"), FALSE, TRUE, TRUE);
        field_7548[19].SetResRef(CResRef("SoLatC2"), FALSE, TRUE, TRUE);
        field_7548[20].SetResRef(CResRef("GSoLaC1"), FALSE, TRUE, TRUE);
        field_7548[21].SetResRef(CResRef("GSoLaC2"), FALSE, TRUE, TRUE);
        field_7548[22].SetResRef(CResRef("SEyesC1"), FALSE, TRUE, TRUE);
        field_7548[23].SetResRef(CResRef("SEyesC2"), FALSE, TRUE, TRUE);
        field_7548[26].SetResRef(CResRef("FShiRC1"), FALSE, TRUE, TRUE);
        field_7548[28].SetResRef(CResRef("FShiRC1"), FALSE, TRUE, TRUE);
        field_7548[27].SetResRef(CResRef("FShiBC1"), FALSE, TRUE, TRUE);
        field_7548[29].SetResRef(CResRef("FShiBC1"), FALSE, TRUE, TRUE);
        field_7548[31].SetResRef(CResRef("DArmorC"), FALSE, TRUE, TRUE);
        field_7548[30].SetResRef(CResRef("TShellC"), FALSE, TRUE, TRUE);
        field_7548[2].SetResRef(CResRef("Wisp"), FALSE, TRUE, TRUE);

        field_9088[7].SetResRef(CResRef("AFT_M05"), TRUE, TRUE);
        field_9088[8].SetResRef(CResRef("MISC_01C"), TRUE, TRUE);
        field_9088[9].SetResRef(CResRef("AFT_M04"), TRUE, TRUE);
        field_9088[10].SetResRef(CResRef("AFT_M03"), TRUE, TRUE);
        field_9088[11].SetResRef(CResRef("AFT_M01"), TRUE, TRUE);
        field_9088[12].SetResRef(CResRef("AFT_P02"), TRUE, TRUE);
        field_9088[13].SetResRef(CResRef("AFT_P03"), TRUE, TRUE);
        field_9088[17].SetResRef(CResRef("AFT_P25"), TRUE, TRUE);
        field_9088[18].SetResRef(CResRef("AFT_P20"), TRUE, TRUE);
        field_9088[20].SetResRef(CResRef("AFT_P26"), TRUE, TRUE);
        field_9088[0].SetResRef(CResRef("AFT_P01"), TRUE, TRUE);
        field_9088[6].SetResRef(CResRef("AFT_M02"), TRUE, TRUE);
        field_9088[3].SetResRef(CResRef("EFF_M11C"), TRUE, TRUE);

        m_type = type;
        m_expirationTime = expirationTime;
        m_huntingRange = huntingRange;
        m_followRange = followRange;
        m_posStart = startPos;
        m_timeOfDayVisible = timeOfDayVisible;

        m_activeAI = TRUE;
        m_activeImprisonment = TRUE;

        memset(&m_baseStats, 0, sizeof(m_baseStats));

        m_pDialogData = NULL;
        m_nDialogData = 0;
        m_dialogWait = 0;
        m_dialogWaitTarget = CGameObjectArray::INVALID_INDEX;
        field_724C = 1;
        field_56E4 = "";
        m_talkingRenderCount = 0;
        field_711E = 1;

        if (m_portraitIconVidCell.pRes != NULL) {
            m_portraitIconVidCell.pRes->Request();
        }

        field_722A = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
        m_interactingWith.Set(CAIObjectType::NOONE);
        field_7234 = 0;
        field_7238 = 1;
        field_723C = 0;
        field_7240 = 0;
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

        // TODO: Incomplete(0x6F2552).
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

// 0x6F2B50
const BYTE* CGameSprite::GetVisibleTerrainTable()
{
    return m_visibleTerrainTable;
}

// 0x
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
    // TODO: Incomplete.
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

// 0x7011E0
void CGameSprite::PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption)
{
    // TODO: Incomplete.
}

// 0x702900
void CGameSprite::VerbalConstant(LONG verbalConstant)
{
    // TODO: Incomplete.
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

// 0x704770
void CGameSprite::RenderMarkers(CVidMode* pVidMode, int a2)
{
    // TODO: Incomplete.
}

// 0x704D40
void CGameSprite::RenderPortrait(const CPoint& cpRenderPosition, const CSize& szControl, BOOL bPressed, BOOL reorderHighlight, BOOL selectFromMarker, const CRect& rClip, BOOL bDoubleSize)
{
    // TODO: Incomplete.
}

// 0x705AD0
void CGameSprite::RenderToMapScreen(const CRect& rClipBase, const CPoint& ptCharPos)
{
    // TODO: Incomplete.
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
        } while (rc == CGameObjectArray::SHARED || CGameObjectArray::DENIED);

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
    } while (rc == CGameObjectArray::SHARED || CGameObjectArray::DENIED);

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
            } while (rc == CGameObjectArray::SHARED || CGameObjectArray::DENIED);

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

// 0x706720
void CGameSprite::SetCharacterToolTip(CUIControlBase* pControl)
{
    // TODO: Incomplete.
}

// 0x706B40
void CGameSprite::SetDirection(const CPoint& posDest)
{
    // TODO: Incomplete.
}

// 0x706C80
void CGameSprite::SetDirection(SHORT direction)
{
    // TODO: Incomplete.
}

// 0x706F80
void CGameSprite::sub_706F80(SHORT direction)
{
    m_nDirection = direction;
    m_nNewDirection = direction;

    // NOTE: Uninline.
    GetAnimation()->ChangeDirection(direction);

    if (m_derivedStats.m_visualEffects[IWD_VFX_BLUR]) {
        sub_706FE0();
    }
}

// 0x706FE0
void CGameSprite::sub_706FE0()
{
    field_5362 = m_pos;

    if (m_nDirection >= 2 && m_nDirection <= 7) {
        // NOTE: Uninline.
        field_5362.x += GetAnimation()->GetMoveScale();
    } else if (m_nDirection >= 10) {
        // NOTE: Uninline.
        field_5362.x -= GetAnimation()->GetMoveScale();
    }

    if (m_nDirection <= 3 || m_nDirection >= 14) {
        // NOTE: Uninline.
        field_5362.y -= 3 * GetAnimation()->GetMoveScale() / 4;
    } else if (m_nDirection >= 6 && m_nDirection <= 11) {
        // NOTE: Uninline.
        field_5362.y += 3 * GetAnimation()->GetMoveScale() / 4;
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
    // TODO: Incomplete.
}

// 0x708FC0
void CGameSprite::RenderDamageArrow(CGameArea* pArea, CVidMode* pVidMode, INT nSurface)
{
    // TODO: Incomplete.
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

// 0x70C600
void CGameSprite::Unmarshal(CSavedGamePartyCreature* pCreature, BOOLEAN bPartyMember, BOOLEAN bProgressBarInPlace)
{
    DWORD nIndex;

    m_bInUnmarshal = TRUE;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    m_bGlobal = TRUE;
    m_currentArea = pCreature->m_areaName;

    // NOTE: Uninline.
    sub_706F80(static_cast<SHORT>(pCreature->m_creatureFacing));

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
    // TODO: Incomplete.

    memcpy(&m_baseStats, pCreature + 8, sizeof(m_baseStats));

    m_animation.SetAnimationType(m_baseStats.m_animationType, m_baseStats.m_colors, facing);
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
            field_54E8 = -1;

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
            sub_467C50(m_currentUseButton.m_abilityId.m_res, this);
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
}

// 0x728460
BOOL CGameSprite::Orderable(BOOL bIgnoreControl)
{
    // TODO: Incomplete.

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

// 0x751CD0
SHORT CGameSprite::LeaveParty()
{
    // TODO: Incomplete.

    return ACTION_DONE;
}

// 0x74F830
void CGameSprite::SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4)
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

// 0x761650
void CGameSprite::sub_761650()
{
    // TODO: Incomplete.
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
    // __LINE__: 28719
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
    field_7240 = a1;
}

// 0x453170
int CGameSprite::sub_453170()
{
    return field_7240;
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
void CGameSprite::sub_4531E0(int a1)
{
    field_727A = a1;
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

// 0x45B720
SHORT CGameSprite::GetDirection()
{
    return m_nDirection;
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

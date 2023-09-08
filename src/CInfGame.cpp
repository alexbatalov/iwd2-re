#include "CInfGame.h"

#include <process.h>

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CBaldurProjector.h"
#include "CGameAIGame.h"
#include "CGameArea.h"
#include "CGameObject.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CItem.h"
#include "CScreenCharacter.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenMap.h"
#include "CScreenMultiPlayer.h"
#include "CScreenOptions.h"
#include "CScreenSave.h"
#include "CScreenSinglePlayer.h"
#include "CScreenSpellbook.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CSearchBitmap.h"
#include "CStore.h"
#include "CUIControlBase.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define FIFTY_THREE 53

// 0x851884
const SHORT CInfGame::KILL_INNOCENT = 0;

// 0x851886
const SHORT CInfGame::INJURE_INNOCENT = 1;

// 0x851888
const SHORT CInfGame::STEAL = 2;

// 0x85188A
const SHORT CInfGame::KILL_FIST = 3;

// 0x85188C
const SHORT CInfGame::MONEY_CHURCH = 4;

// 0x85188E
const SHORT CInfGame::MONEY_BEGGAR = 5;

// 0x851890
const SHORT CInfGame::MAGIC_CHURCH = 6;

// 0x851892
const SHORT CInfGame::KILL_EVIL = 7;

// 0x851894
const SHORT CInfGame::BASE_CHURCH = 8;

// 0x851896
const SHORT CInfGame::REPUTATION_MULTIPLIER = 10;

// 0x8518BE
const SHORT CInfGame::FEEDBACK_GOLD = 1;

// 0x8AFC50
static const char* off_8AFC50[FIFTY_THREE] = {
    "Inventory",
    "Character Record",
    "Return to Game",
    "Journal",
    "Map",
    "Spellbook",
    "Options",
    "Character Arbitration",
    "Guard / Protect",
    "Turn Undead",
    "Battle Song",
    "Cast Spell",
    "Use Item",
    "Dialog",
    "Thieving",
    "Stealth",
    "Trap Detection",
    "Group Stop",
    "Group Attack",
    "Special Abilities",
    "Equip Melee Weapon",
    "Equip Range Weapon",
    "Quick Load",
    "Hide Interface",
    "Chat Window",
    "Location",
    "Quick Save",
    "Toggle AI",
    "Toggle Interface",
    "Rest",
    "Toggle Portrait HP",
    "Formation",
    "Multiselect 1-2",
    "Multiselect 3-4",
    "Multiselect 5-6",
    "Multiselect 1-3",
    "Multiselect 4-6",
    "Multiselect All",
    "Quick Spell Slot1",
    "Quick Spell Slot2",
    "Quick Spell Slot3",
    "Quick Weapon Slot1",
    "Quick Weapon Slot2",
    "Quick Weapon Slot3",
    "Quick Weapon Slot4",
    "Quick Item Slot1",
    "Quick Item Slot2",
    "Quick Item Slot3",
    "Quick Formation Slot1",
    "Quick Formation Slot2",
    "Quick Formation Slot3",
    "Quick Formation Slot4",
    "Quick Formation Slot5",
};

// 0x8AFD24
static const char* off_8AFD24[FIFTY_THREE] = {
    "I",
    "R",
    "G",
    "J",
    "M",
    "S",
    "O",
    "C",
    "",
    "",
    "",
    "",
    "",
    "D",
    "",
    "",
    "",
    "",
    "",
    "V",
    "",
    "",
    "L",
    "H",
    "T",
    "X",
    "Q",
    "A",
    "Y",
    "Z",
    ".",
    "F",
    "7",
    "8",
    "9",
    "0",
    "-",
    "=",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

// 0x8B4F84
static const char* off_8B4F84[] = {
    "SPPR101",
    "SPPR102",
    "SPPR103",
    "SPPR105",
    "SPPR106",
    "SPPR107",
    "SPPR108",
    "SPPR109",
    "SPPR110",
    "SPPR111",
    "SPPR112",
    "SPPR113",
    "SPPR114",
    "SPPR115",
    "SPPR116",
    "SPPR117",
    "SPPR201",
    "SPPR202",
    "SPPR203",
    "SPPR204",
    "SPPR205",
    "SPPR206",
    "SPPR207",
    "SPPR208",
    "SPPR210",
    "SPPR211",
    "SPPR212",
    "SPPR213",
    "SPPR214",
    "SPPR215",
    "SPPR216",
    "SPPR217",
    "SPPR218",
    "SPPR219",
    "SPPR220",
    "SPPR221",
    "SPPR222",
    "SPPR301",
    "SPPR302",
    "SPPR303",
    "SPPR304",
    "SPPR305",
    "SPPR306",
    "SPPR307",
    "SPPR308",
    "SPPR309",
    "SPPR310",
    "SPPR311",
    "SPPR312",
    "SPPR313",
    "SPPR314",
    "SPPR315",
    "SPPR316",
    "SPPR318",
    "SPPR319",
    "SPPR320",
    "SPPR322",
    "SPPR323",
    "SPPR324",
    "SPPR325",
    "SPPR326",
    "SPPR327",
    "SPPR328",
    "SPPR401",
    "SPPR402",
    "SPPR403",
    "SPPR404",
    "SPPR405",
    "SPPR406",
    "SPPR407",
    "SPPR408",
    "SPPR409",
    "SPPR410",
    "SPPR411",
    "SPPR414",
    "SPPR415",
    "SPPR416",
    "SPPR417",
    "SPPR418",
    "SPPR420",
    "SPPR422",
    "SPPR423",
    "SPPR424",
    "SPPR425",
    "SPPR426",
    "SPPR427",
    "SPPR428",
    "SPPR429",
    "SPPR501",
    "SPPR502",
    "SPPR503",
    "SPPR504",
    "SPPR507",
    "SPPR508",
    "SPPR510",
    "SPPR511",
    "SPPR512",
    "SPPR513",
    "SPPR514",
    "SPPR515",
    "SPPR516",
    "SPPR517",
    "SPPR518",
    "SPPR519",
    "SPPR520",
    "SPPR521",
    "SPPR522",
    "SPPR523",
    "SPPR524",
    "SPPR602",
    "SPPR605",
    "SPPR606",
    "SPPR607",
    "SPPR608",
    "SPPR609",
    "SPPR610",
    "SPPR611",
    "SPPR612",
    "SPPR613",
    "SPPR614",
    "SPPR615",
    "SPPR616",
    "SPPR702",
    "SPPR704",
    "SPPR705",
    "SPPR707",
    "SPPR709",
    "SPPR712",
    "SPPR714",
    "SPPR715",
    "SPPR716",
    "SPPR717",
    "SPPR718",
    "SPPR719",
    "SPPR720",
    "SPPR721",
    "SPPR722",
    "SPPR723",
    "SPPR724",
    "SPPR725",
    "SPPR726",
    "SPPR727",
    "SPPR728",
    "SPPR729",
    "SPWI101",
    "SPWI102",
    "SPWI103",
    "SPWI104",
    "SPWI105",
    "SPWI107",
    "SPWI108",
    "SPWI112",
    "SPWI113",
    "SPWI114",
    "SPWI115",
    "SPWI116",
    "SPWI117",
    "SPWI118",
    "SPWI119",
    "SPWI120",
    "SPWI121",
    "SPWI122",
    "SPWI201",
    "SPWI203",
    "SPWI205",
    "SPWI206",
    "SPWI207",
    "SPWI209",
    "SPWI210",
    "SPWI211",
    "SPWI212",
    "SPWI213",
    "SPWI214",
    "SPWI215",
    "SPWI217",
    "SPWI218",
    "SPWI219",
    "SPWI220",
    "SPWI221",
    "SPWI222",
    "SPWI223",
    "SPWI224",
    "SPWI225",
    "SPWI226",
    "SPWI227",
    "SPWI228",
    "SPWI302",
    "SPWI303",
    "SPWI304",
    "SPWI305",
    "SPWI306",
    "SPWI308",
    "SPWI309",
    "SPWI310",
    "SPWI311",
    "SPWI312",
    "SPWI313",
    "SPWI314",
    "SPWI316",
    "SPWI317",
    "SPWI318",
    "SPWI319",
    "SPWI320",
    "SPWI321",
    "SPWI322",
    "SPWI323",
    "SPWI401",
    "SPWI402",
    "SPWI404",
    "SPWI405",
    "SPWI406",
    "SPWI407",
    "SPWI408",
    "SPWI410",
    "SPWI411",
    "SPWI412",
    "SPWI413",
    "SPWI414",
    "SPWI417",
    "SPWI418",
    "SPWI419",
    "SPWI420",
    "SPWI421",
    "SPWI422",
    "SPWI423",
    "SPWI424",
    "SPWI425",
    "SPWI426",
    "SPWI427",
    "SPWI428",
    "SPWI501",
    "SPWI503",
    "SPWI504",
    "SPWI505",
    "SPWI507",
    "SPWI508",
    "SPWI509",
    "SPWI510",
    "SPWI511",
    "SPWI512",
    "SPWI513",
    "SPWI514",
    "SPWI515",
    "SPWI516",
    "SPWI517",
    "SPWI518",
    "SPWI519",
    "SPWI520",
    "SPWI521",
    "SPWI522",
    "SPWI523",
    "SPWI524",
    "SPWI525",
    "SPWI526",
    "SPWI601",
    "SPWI603",
    "SPWI605",
    "SPWI606",
    "SPWI607",
    "SPWI608",
    "SPWI609",
    "SPWI610",
    "SPWI611",
    "SPWI612",
    "SPWI613",
    "SPWI614",
    "SPWI615",
    "SPWI616",
    "SPWI617",
    "SPWI618",
    "SPWI619",
    "SPWI620",
    "SPWI621",
    "SPWI622",
    "SPWI623",
    "SPWI624",
    "SPWI626",
    "SPWI627",
    "SPWI628",
    "SPWI629",
    "SPWI630",
    "SPWI702",
    "SPWI703",
    "SPWI704",
    "SPWI705",
    "SPWI706",
    "SPWI707",
    "SPWI708",
    "SPWI709",
    "SPWI710",
    "SPWI711",
    "SPWI712",
    "SPWI713",
    "SPWI714",
    "SPWI715",
    "SPWI716",
    "SPWI717",
    "SPWI718",
    "SPWI719",
    "SPWI802",
    "SPWI803",
    "SPWI804",
    "SPWI805",
    "SPWI806",
    "SPWI807",
    "SPWI808",
    "SPWI809",
    "SPWI810",
    "SPWI902",
    "SPWI903",
    "SPWI905",
    "SPWI906",
    "SPWI907",
    "SPWI908",
    "SPWI909",
    "SPWI910",
    "SPWI911",
    NULL,
    NULL,
};

// 0x8ABA24
static char byte_8ABA24[CINFGAME_SPECIAL_SYMBOLS] = {
    ';',
    '=',
    ',',
    '-',
    '.',
    '/',
    '`',
    '[',
    '\\',
    ']',
    '\'',
    '\0',
};

// 0x8ABA3C
static BYTE byte_8ABA3C[CINFGAME_SPECIAL_SYMBOLS] = {
    VK_OEM_1,
    VK_OEM_PLUS,
    VK_OEM_COMMA,
    VK_OEM_MINUS,
    VK_OEM_PERIOD,
    VK_OEM_2,
    VK_OEM_3,
    VK_OEM_4,
    VK_OEM_5,
    VK_OEM_6,
    VK_OEM_7,
    0,
};

// 0x8E707C
const CString CInfGame::FOGOWAR_RESREF("FOGOWAR");

// 0x8E74AC
const CString CInfGame::SAVE_OBJECT_LIST_NAME("SVTRIOBJ");

// 0x8E74F4
const CString CInfGame::CHAPTER_GLOBAL("CHAPTER");

// 0x8E74E8
const CString CInfGame::TOKEN_CURRENT_CHAPTER("CurrentChapter");

// 0x8E7510
const CString CInfGame::TOKEN_CHARACTER("CHARNAME");

// 0x8E7498
const CString CInfGame::TOKEN_GABBER("GABBER");

// 0x8E7064
const CString CInfGame::TOKEN_SIRMAAM("PROTAGONIST_SIRMAAM");

// 0x8E7084
const CString CInfGame::TOKEN_GIRLBOY("PROTAGONIST_GIRLBOY");

// 0x8E74FC
const CString CInfGame::TOKEN_BROTHERSISTER("PROTAGONIST_BROTHERSISTER");

// 0x8E7060
const CString CInfGame::TOKEN_LADYLORD("PROTAGONIST_LADYLORD");

// 0x8E7520
const CString CInfGame::TOKEN_MALEFEMALE("PROTAGONIST_MALEFEMALE");

// 0x8E7518
const CString CInfGame::TOKEN_HESHE("PROTAGONIST_HESHE");

// 0x8E7504
const CString CInfGame::TOKEN_HISHER("PROTAGONIST_HISHER");

// 0x8E74DC
const CString CInfGame::TOKEN_RACE("PROTAGONIST_RACE");

// 0x8E74D0
const CString CInfGame::TOKEN_HIMHER("PROTAGONIST_HIMHER");

// 0x8E7074
const CString CInfGame::TOKEN_MANWOMAN("PROTAGONIST_MANWOMAN");

// 0x8E74C4
const CString CInfGame::TOKEN_GABBER_SIRMAAM("SIRMAAM");

// 0x8E7070
const CString CInfGame::TOKEN_GABBER_GIRLBOY("GIRLBOY");

// 0x8E74E4
const CString CInfGame::TOKEN_GABBER_BROTHERSISTER("BROTHERSISTER");

// 0x8E7088
const CString CInfGame::TOKEN_GABBER_LADYLORD("LADYLORD");

// 0x8E7080
const CString CInfGame::TOKEN_GABBER_MALEFEMALE("MALEFEMALE");

// 0x8E751C
const CString CInfGame::TOKEN_GABBER_HESHE("HESHE");

// 0x8E74EC
const CString CInfGame::TOKEN_GABBER_HISHER("HISHER");

// 0x8E708C
const CString CInfGame::TOKEN_GABBER_RACE("RACE");

// 0x8E74C8
const CString CInfGame::TOKEN_GABBER_HIMHER("HIMHER");

// 0x8E74F0
const CString CInfGame::TOKEN_GABBER_MANWOMAN("MANWOMAN");

// 0x8E7494
const CString CInfGame::TOKEN_PLAYER1("PLAYER1");

// 0x8E74BC
const CString CInfGame::TOKEN_PLAYER2("PLAYER2");

// 0x8E7490
const CString CInfGame::TOKEN_PLAYER3("PLAYER3");

// 0x8E74A4
const CString CInfGame::TOKEN_PLAYER4("PLAYER4");

// 0x8E74C0
const CString CInfGame::TOKEN_PLAYER5("PLAYER5");

// 0x8E749C
const CString CInfGame::TOKEN_PLAYER6("PLAYER6");

// 0x8E74D8
const CString CInfGame::TOKEN_SURFACE_UNDERDARK("SURFACE_UNDERDARK");

// 0x8E74D4
const CString CInfGame::AUTO_SAVE_NAME("000000000-Auto-Save");

// 0x8E7508
const CString CInfGame::QUICK_SAVE_NAME("000000002-Quick-Save");

// 0x8E750C
const CString CInfGame::QUICK_SAVE_BACKUP_NAME("000000001-Quick-Save-Backup");

// 0x8E706C
const CString CInfGame::SILHOUETTE_PORTRAIT_SM("noportsm");

// 0x8E705C
const CString CInfGame::SILHOUETTE_PORTRAIT_LG("noportlg");

// 0x8E7524
BOOL CInfGame::dword_8E7524;

// 0x8E752C
int CInfGame::dword_8E752C;

// 0x59CC30
CInfGame::CInfGame()
    : m_rgbMasterBitmap(CResRef("MPALETTE"), FALSE, 24)
{
    m_nCharacters = 0;
    for (INT nIndex = 0; nIndex < CINFGAME_MAXCHARACTERS; nIndex++) {
        m_characters[nIndex] = CGameObjectArray::INVALID_INDEX;
        m_characterPortraits[nIndex] = CGameObjectArray::INVALID_INDEX;
    }

    m_tempCursor = 4;
    m_visibleArea = 0;
    memset(m_gameAreas, 0, sizeof(m_gameAreas));
    m_pGameAreaMaster = NULL;
    // TODO: Incomplete.

    m_sSaveDir = ".\\save\\";
    m_sMultiplayerSaveDir = ".\\mpsave\\";
    m_sTempDir = ".\\temp\\";
    m_sTempSaveDir = ".\\tempsave\\";
    m_sScriptsDir = ".\\scripts\\";
    m_sPortraitsDir = ".\\portraits\\";
    m_sSoundsDir = ".\\sounds\\";
    m_sCharactersDir = ".\\characters\\";

    if (!g_pChitin->cDimm.DirectoryRemoveFiles(m_sTempDir)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 2608
        UTIL_ASSERT_MSG(FALSE, "Problems removing files from Temp directory, delete the directory and try again");
    }

    if (!g_pChitin->cDimm.DirectoryRemoveFiles(m_sTempSaveDir)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 2608
        UTIL_ASSERT_MSG(FALSE, "Problems removing files from TempSave directory, delete the directory and try again");
    }

    g_pChitin->cDimm.AddToDirectoryList(m_sScriptsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sSoundsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sPortraitsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sCharactersDir, TRUE);

    // TODO: Incomplete.

    m_hSearchThread = CreateSemaphoreA(NULL, 0, 1, NULL);
    if (m_hSearchThread != NULL) {
        // TODO: Incomplete.

        C2DArray tSpells;
        tSpells.Load(CResRef(CRuleTables::LISTSPLL));
        m_spells.Load(tSpells, 7);

        for (unsigned int spellcasterClassIndex = 0; spellcasterClassIndex < 7; spellcasterClassIndex++) {
            m_spellsByClass[spellcasterClassIndex].Load(tSpells,
                spellcasterClassIndex,
                7,
                NULL);
        }

        C2DArray tDomainSpells;
        tDomainSpells.Load(CResRef(CRuleTables::LISTDOMN));

        for (unsigned int domainIndex = 0; domainIndex < 9; domainIndex++) {
            m_spellsByDomain[domainIndex].Load(tDomainSpells,
                domainIndex,
                9,
                &m_spells);
        }

        C2DArray tInnateSpells;
        tInnateSpells.Load(CResRef(CRuleTables::LISTINNT));
        m_innateSpells.Load(tInnateSpells, 0);

        C2DArray tSongs;
        tSongs.Load(CResRef(CRuleTables::LISTSONG));
        m_songs.Load(tSongs, 0);

        C2DArray tShapeshifts;
        tShapeshifts.Load(CResRef(CRuleTables::LISTSHAP));
        m_shapeshifts.Load(tShapeshifts, 0);

        // TODO: Incomplete (spells validation).
    }
}

// 0x59ECB0
CInfGame::~CInfGame()
{
    // TODO: Incomplete.
}

// 0x59F500
void CInfGame::StartSearchThread()
{
    if (_beginthread(SearchThreadMain, 0, NULL) == -1) {
        CloseHandle(m_hSearchThread);
        m_hSearchThread = NULL;
    }
}

// 0x59F540
void CInfGame::InitGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace)
{
    m_cVRamPool.AttachSurfaces(g_pBaldurChitin->GetCurrentVideoMode());

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::AREA_TRANSITION, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::CHAR_RECORDS, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::DIALOG, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::GROUP_POOL, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::LEADER, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::MODIFY_CHARS, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::PAUSING, TRUE);
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::PURCHASING, TRUE);
    }

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        m_singlePlayerPermissions.SetSinglePermission(CGamePermission::LEADER, TRUE);
    }

    LoadKeymap();
    LoadOptions();

    g_pBaldurChitin->EnginesGameInit();

    m_cButtonArray.SetState(CInfButtonArray::STATE_NONE, 0);

    g_pBaldurChitin->GetCurrentVideoMode()->rgbGlobalTint = RGB(255, 255, 255);

    m_worldTime.m_gameTime = CTimerWorld::TIME_DAY + 1;
    m_worldTime.CheckForTriggerEventPast();

    g_pBaldurChitin->GetTlkTable().Fetch(16484, field_4814);
    g_pBaldurChitin->GetTlkTable().Fetch(15307, field_487C);

    for (BYTE nIndex = 0; nIndex < 6; nIndex++) {
        EnablePortrait(nIndex, FALSE);
    }

    field_43DC = 0;

    for (int slot = 0; slot < 100; slot++) {
        m_groupInventory[slot] = NULL;
    }

    field_43E2 = -1;
    field_43E6 = 0;
    field_4B84 = "";
    field_4B88 = "";
    field_4B8C = "";
    field_4B90 = "";

    m_pGameAreaMaster = NULL;
    field_4A8E = 1;
    field_4A8F = 1;
    field_4AB2 = 0;
    m_bGameLoaded = TRUE;

    m_allies.RemoveAll();
    m_familiars.RemoveAll();

    memset(field_38E0, 0, sizeof(field_38E0));

    field_4204 = 0;

    m_cJournal.ClearAllEntries();

    m_variables.Resize(2048);
    m_namedCreatures.Resize(2048);
    m_variables.ClearAll();
    m_namedCreatures.ClearAll();

    m_entanglePalette.SetType(CVidPalette::TYPE_RANGE);
    m_entanglePalette.SetRange(0, 54, m_rgbMasterBitmap);

    m_webHoldPalette.SetType(CVidPalette::TYPE_RANGE);
    m_webHoldPalette.SetRange(0, 65, m_rgbMasterBitmap);

    sub_5A0160();

    field_4AFC = 0;

    m_cMoveList.ClearAll();
    m_cLimboList.ClearAll();

    CGameAIGame* pAIGame = new CGameAIGame();
    CAIScript* pScript = new CAIScript(CResRef("BALDUR"));

    // NOTE: Uninline.
    pAIGame->SetDefaultScript(pScript);

    m_nAIIndex = pAIGame->m_id;
    m_nTimeStop = 0;
    m_nTimeStopCaster = -1;

    if (!g_pChitin->cDimm.DirectoryRemoveFiles(m_sTempDir)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 3213
        UTIL_ASSERT_MSG(FALSE, "Could not clean out Temp directory");
    }

    if (!g_pChitin->cDimm.DirectoryRemoveFiles(m_sTempSaveDir)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 3215
        UTIL_ASSERT_MSG(FALSE, "Could not clean out TempSave directory");
    }

    // TODO: Use loop.
    memset(m_aServerStore, 0, sizeof(m_aServerStore));
    memset(m_nServerStoreDemands, 0, sizeof(m_nServerStoreDemands));

    dword_8E752C = 0;

    ResetMultiPlayerPermissions();
}

// 0x59F9A0
void CInfGame::BeginListManipulation(CGameArea* pArea)
{
    if (pArea != NULL) {
        EnterCriticalSection(&(pArea->field_214));
        pArea->SetListManipulationThreadId(GetCurrentThreadId());
    }
}

// 0x59F9D0
INT CInfGame::EndListManipulation(CGameArea* pArea)
{
    INT nCounter = 0;

    if (pArea != NULL) {
        nCounter = pArea->SetListManipulationThreadId(0);
        LeaveCriticalSection(&(pArea->field_214));
    }

    return nCounter;
}

// 0x59FA00
void CInfGame::sub_59FA00(BOOL a1)
{
    // TODO: Incomplete.
}

// 0x59FB50
void CInfGame::DestroyGame(unsigned char a1, unsigned char a2)
{
    // TODO: Incomplete.
}

// 0x5A0160
void CInfGame::sub_5A0160()
{
    // TODO: Incomplete.
}

// 0x5A0F50
LONG CInfGame::ImportCharacter(const CString& sFileName, INT nIndex)
{
    // TODO: Incomplete.

    return 0;
}

// 0x5A1A80
CString CInfGame::GetDirSounds()
{
    return m_sSoundsDir;
}

// 0x5A1AB0
void CInfGame::CharacterExport(LONG nCharacterId, CString sFileName)
{
    // TODO: Incomplete.
}

// 0x5AC110
BOOLEAN CInfGame::CanSaveGame(STRREF& strError, unsigned char a2, unsigned char a3)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5AC430
BOOL CInfGame::SaveGame(unsigned char a1, unsigned char a2, unsigned char a3)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5A9680
void CInfGame::ProgressBarCallback(DWORD dwSize, BOOLEAN bInitialize)
{
    if (bInitialize == TRUE) {
        m_dwLastProgressRenderTickCount = GetTickCount() - 250;
        m_dwLastProgressMsgTickCount = GetTickCount() - 5000;
    }

    g_pChitin->cProgressBar.m_nActionProgress += dwSize;

    if (GetTickCount() - m_dwLastProgressMsgTickCount >= 1000) {
        m_dwLastProgressMsgTickCount = GetTickCount();

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            g_pBaldurChitin->GetBaldurMessage()->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
                g_pChitin->cProgressBar.m_nActionTarget,
                g_pChitin->cProgressBar.m_bWaiting,
                g_pChitin->cProgressBar.m_nWaitingReason,
                g_pChitin->cProgressBar.m_bTimeoutVisible,
                g_pChitin->cProgressBar.m_nSecondsToTimeout);
        }
    }

    if (GetTickCount() - m_dwLastProgressRenderTickCount >= 250) {
        m_dwLastProgressRenderTickCount = GetTickCount();

        g_pChitin->m_bDisplayStale = TRUE;
        g_pChitin->cDimm.field_0 = 1;
        g_pChitin->cDimm.field_4 = 1;
        SleepEx(25, TRUE);

        sub_59FA00(FALSE);
    }
}

// 0x5A9780
char CInfGame::sub_5A9780(BYTE nKey)
{
    if (nKey >= 'A' && nKey <= 'Z') {
        return static_cast<char>(nKey);
    }

    if (nKey >= '0' && nKey <= '9') {
        return static_cast<char>(nKey);
    }

    for (int sym = 0; sym < CINFGAME_SPECIAL_SYMBOLS; sym++) {
        if (byte_8ABA3C[sym] == nKey) {
            return byte_8ABA24[sym];
        }
    }

    return -1;
}

// 0x5A97D0
BYTE CInfGame::sub_5A97D0(char ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return static_cast<BYTE>(ch - 32);
    }

    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<BYTE>(ch);
    }

    if (ch >= '0' && ch <= '9') {
        return static_cast<BYTE>(ch);
    }

    for (int sym = 0; sym < CINFGAME_SPECIAL_SYMBOLS; sym++) {
        if (byte_8ABA24[sym] == ch) {
            return byte_8ABA3C[sym];
        }
    }

    return -1;
}

// 0x5A9830
BYTE CInfGame::sub_5A9830(int index)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 7779
    UTIL_ASSERT(index >= 0 && index < CINFGAME_KEYMAP_SIZE);

    if (index >= FIFTY_THREE) {
        return 0;
    }

    // NOTE: Uninline.
    return sub_5A97D0(off_8AFD24[index][0]);
}

// 0x5A98F0
void CInfGame::LoadKeymap()
{
    CString sKey;

    memset(m_pKeymap, 0, sizeof(m_pKeymap));
    memset(m_pKeymapFlags, 0, sizeof(m_pKeymapFlags));

    // NOTE: Unsigned compare in both loops.
    WORD index;
    for (index = 0; index < FIFTY_THREE; index++) {
        char* buffer = sKey.GetBuffer(128);
        GetPrivateProfileStringA("Keymap",
            off_8AFC50[index],
            off_8AFD24[index],
            buffer,
            128,
            ".\\Keymap.ini");
        sKey.ReleaseBuffer();
        LoadKey(sKey, index);
    }

    for (; index < CINFGAME_KEYMAP_SIZE; index++) {
        char* buffer = sKey.GetBuffer(128);
        if (index >= 199) {
            GetPrivateProfileStringA("Wizard Spells",
                off_8B4F84[index - FIFTY_THREE],
                "",
                buffer,
                128,
                ".\\Keymap.ini");
        } else {
            GetPrivateProfileStringA("Priest Spells",
                off_8B4F84[index - FIFTY_THREE],
                "",
                buffer,
                128,
                ".\\Keymap.ini");
        }
        sKey.ReleaseBuffer();
        LoadKey(sKey, index);
    }
}

// 0x5A9A30
void CInfGame::LoadKey(const CString& sKey, SHORT index)
{
    INT nOffset = 0;
    if (sKey.GetLength() > 0) {
        if (sKey.Find("CTRL-") == 0
            || sKey.Find("ctrl-") == 0
            || sKey.Find("Ctrl-") == 0) {
            nOffset = strlen("CTRL-");
            m_pKeymapFlags[index] = 1;
        }

        if (sKey[nOffset] >= 'a' && sKey[nOffset] <= 'z') {
            m_pKeymap[index] = sKey[nOffset] - 32;
        } else {
            m_pKeymap[index] = sKey[nOffset];

            for (int sym = 0; sym < CINFGAME_SPECIAL_SYMBOLS; sym++) {
                if (byte_8ABA24[sym] == sKey[nOffset]) {
                    m_pKeymap[index] = byte_8ABA3C[sym];
                    break;
                }
            }
        }
    }
}

// 0x5A9B00
void CInfGame::SetKey(INT nIndex, BYTE nKey, BYTE nKeyFlag)
{
    if (nIndex >= 0 && nIndex < CINFGAME_KEYMAP_SIZE) {
        m_pKeymap[nIndex] = nKey;
        m_pKeymapFlags[nIndex] = nKeyFlag;

        for (int sym = 0; sym < CINFGAME_SPECIAL_SYMBOLS; sym++) {
            if (byte_8ABA3C[sym] == nKey) {
                nKey = byte_8ABA24[sym];
                break;
            }
        }

        if (nIndex < FIFTY_THREE) {
            char buffer[16];
            sprintf(buffer, "%s%c", nKeyFlag ? "CTRL-" : "", nKey);
            WritePrivateProfileStringA("Keymap",
                off_8AFC50[nIndex],
                buffer,
                ".\\Keymap.ini");
        }
    }
}

// 0x5A9BA0
void CInfGame::LoadOptions()
{
    m_cOptions.m_nTilesPrecachePercent = GetPrivateProfileIntA("Game Options",
        "Tiles Precache Percent",
        100,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nTilesPrecachePercent > 100) {
        m_cOptions.m_nTilesPrecachePercent = 100;
    }

    m_cOptions.m_bDuplicateFloatingText = GetPrivateProfileIntA("Game Options",
        "Duplicate Floating Text",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bTranslucentBlts = GetPrivateProfileIntA("Game Options",
        "Translucent Blts",
        1,
        g_pBaldurChitin->GetIniFileName());
    CInfinity::TRANSLUCENT_BLTS_ON = m_cOptions.m_bTranslucentBlts;
    CVidCell::TRANSLUCENT_BLTS_ON = m_cOptions.m_bTranslucentBlts;

    m_cOptions.m_bMaxHP = GetPrivateProfileIntA("Game Options",
        "Maximum HP",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bAutoPauseOnTrap = GetPrivateProfileIntA("Game Options",
        "Pause On Trap",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.field_AC = 0;

    m_cOptions.m_bEnvironmentalAudio = GetPrivateProfileIntA("Game Options",
        "Environmental Audio",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bCheatsEnabled = GetPrivateProfileIntA("Game Options",
        "Cheats",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.field_4 = GetPrivateProfileIntA("Game Options",
        "Grant 2000",
        0,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.field_4) {
        m_cOptions.m_bGore = GetPrivateProfileIntA("Game Options",
            "Chucknomitron",
            0,
            g_pBaldurChitin->GetIniFileName());
    } else {
        m_cOptions.m_bGore = FALSE;
    }

    m_cOptions.m_bFootStepsSounds = GetPrivateProfileIntA("Game Options",
        "Footsteps",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_nMouseScrollSpeed = GetPrivateProfileIntA("Game Options",
        "Mouse Scroll Speed",
        28,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nMouseScrollSpeed < 6 || m_cOptions.m_nMouseScrollSpeed > 50) {
        m_cOptions.m_nMouseScrollSpeed = 28;
    }

    m_cOptions.m_nGuiFeedbackLevel = GetPrivateProfileIntA("Game Options",
        "GUI Feedback Level",
        5,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nGuiFeedbackLevel != 0 || m_cOptions.m_nGuiFeedbackLevel > 5) {
        m_cOptions.m_nGuiFeedbackLevel = 5;
    }

    m_cOptions.m_nLocatorFeedbackLevel = GetPrivateProfileIntA("Game Options",
        "Locator Feedback Level",
        5,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nLocatorFeedbackLevel != 0 || m_cOptions.m_nLocatorFeedbackLevel > 5) {
        m_cOptions.m_nLocatorFeedbackLevel = 5;
    }

    m_cOptions.m_nBoredTime = GetPrivateProfileIntA("Game Options",
        "Bored Timeout",
        CScreenWorld::BORED_TIME,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nBoredTime == 0 || m_cOptions.m_nBoredTime > CScreenWorld::BORED_TIME) {
        m_cOptions.m_nBoredTime = CScreenWorld::BORED_TIME;
    }

    m_cOptions.m_bAlwaysDither = GetPrivateProfileIntA("Game Options",
        "Always Dither",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bSubtitles = GetPrivateProfileIntA("Game Options",
        "Subtitles",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_nKeyboardScrollSpeed = GetPrivateProfileIntA("Game Options",
        "Keyboard Scroll Speed",
        36,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nKeyboardScrollSpeed < 18 || m_cOptions.m_nKeyboardScrollSpeed > 150) {
        m_cOptions.m_nKeyboardScrollSpeed = 36;
    }

    m_cOptions.m_nCommandSoundsFrequency = GetPrivateProfileIntA("Game Options",
        "Command Sounds Frequency",
        2,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nCommandSoundsFrequency == 0 || m_cOptions.m_nCommandSoundsFrequency > 3) {
        m_cOptions.m_nCommandSoundsFrequency = 2;
    }

    m_cOptions.m_nSelectionSoundsFrequency = GetPrivateProfileIntA("Game Options",
        "Selection Sounds Frequency",
        3,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nSelectionSoundsFrequency == 0 || m_cOptions.m_nSelectionSoundsFrequency > 3) {
        m_cOptions.m_nSelectionSoundsFrequency = 3;
    }

    m_cOptions.m_nEffectTextLevel = GetPrivateProfileIntA("Game Options",
        "Effect Text Level",
        62,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bDarkvision = GetPrivateProfileIntA("Game Options",
        "Darkvision",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bWeatherEnabled = GetPrivateProfileIntA("Game Options",
        "Weather",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_nTutorialState = GetPrivateProfileIntA("Game Options",
        "Tutorial State",
        1,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nTutorialState > 1) {
        m_cOptions.m_nTutorialState = 1;
    }

    m_cOptions.m_bAttackSounds = GetPrivateProfileIntA("Game Options",
        "Attack Sounds",
        1,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_bAttackSounds > 1) {
        m_cOptions.m_bAttackSounds = 1;
    }

    m_cOptions.m_nAutoPauseState = GetPrivateProfileIntA("Game Options",
        "Auto Pause State",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bAutoPauseCenter = GetPrivateProfileIntA("Game Options",
        "Auto Pause Center",
        1,
        g_pBaldurChitin->GetIniFileName());

    if (g_pBaldurChitin->cNetwork.GetSessionHosting() == TRUE) {
        m_cOptions.m_nDifficultyLevel = GetPrivateProfileIntA("Game Options",
            "Difficulty Level",
            3,
            g_pBaldurChitin->GetIniFileName());

        if (m_cOptions.m_nDifficultyLevel < 1 || m_cOptions.m_nDifficultyLevel > 5) {
            m_cOptions.m_nDifficultyLevel = 3;
        }

        switch (m_cOptions.m_nDifficultyLevel) {
        case 1:
            m_cOptions.m_nDifficultyMultiplier = -50;
            break;
        case 2:
            m_cOptions.m_nDifficultyMultiplier = -25;
            break;
        case 3:
            m_cOptions.m_nDifficultyMultiplier = 0;
            break;
        case 4:
            m_cOptions.m_nDifficultyMultiplier = 50;
            break;
        case 5:
            m_cOptions.m_nDifficultyMultiplier = 100;
            break;
        }

        m_cOptions.m_nMPDifficultyMultiplier = m_cOptions.m_nDifficultyMultiplier;
        m_nDifficultyLevel = -1;
    } else {
        m_nDifficultyLevel = GetPrivateProfileIntA("Game Options",
            "Difficulty Level",
            3,
            g_pBaldurChitin->GetIniFileName());

        // NOTE: Difficulty level is not normalized to 1..5 range as in the
        // code path above.

        m_cOptions.m_nDifficultyLevel = m_nDifficultyLevel;
    }

    m_cOptions.m_bQuickItemMapping = GetPrivateProfileIntA("Game Options",
        "Quick Item Mapping",
        1,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_bQuickItemMapping > 1) {
        m_cOptions.m_bQuickItemMapping = 1;
    }

    m_cOptions.m_bTerrainHugging = GetPrivateProfileIntA("Game Options",
        "Terrain Hugging",
        0,
        g_pBaldurChitin->GetIniFileName());

    CGameSprite::SHOW_CHARACTER_HP = GetPrivateProfileIntA("Game Options",
        "Show Character HP",
        0,
        g_pBaldurChitin->GetIniFileName());

    CGameSprite::GRAVITY_IS_DOWN = GetPrivateProfileIntA("Game Options",
        "Gravity Is Down",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bShowQuestXP = GetPrivateProfileIntA("Game Options",
        "Show Quest XP",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bStaticAnimations = GetPrivateProfileIntA("Game Options",
        "Static Animations",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bCriticalHitScreenShake = GetPrivateProfileIntA("Game Options",
        "Critical Hit Screen Shake",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_bSuppressExtraDifficultyDamage = GetPrivateProfileIntA("Game Options",
        "Suppress Extra Difficulty Damage",
        0,
        g_pBaldurChitin->GetIniFileName());

    if (!g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        g_pBaldurChitin->m_cBaldurMessage.DemandSettingsNightmareMode(FALSE);
    }

    m_cOptions.m_nDefaultCharGenPointsPool = GetPrivateProfileIntA("Game Options",
        "DefaultCharGenPointsPool",
        16,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nDefaultCharGenPointsPool < 10 || m_cOptions.m_nDefaultCharGenPointsPool > 108) {
        m_cOptions.m_nDefaultCharGenPointsPool = 16;
    }

    m_cOptions.m_nDefaultCharGenPoints = GetPrivateProfileIntA("Game Options",
        "DefaultCharGenPoints",
        10,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nDefaultCharGenPoints < 3 || m_cOptions.m_nDefaultCharGenPoints > 18) {
        m_cOptions.m_nDefaultCharGenPoints = 10;
    }

    m_cOptions.m_bHotkeysOnToolTips = GetPrivateProfileIntA("Game Options",
        "Hotkeys On Tooltips",
        1,
        g_pBaldurChitin->GetIniFileName());

    g_pBaldurChitin->m_cBaldurMessage.SetSignalDefaultSecondsToTimeout();

    m_cOptions.m_bAllScreenShake = GetPrivateProfileIntA("Game Options",
        "All Screen Shake",
        1,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_nOldPortraitHealth = GetPrivateProfileIntA("Game Options",
        "Old Portrait Health",
        0,
        g_pBaldurChitin->GetIniFileName());

    m_cOptions.m_nHitPointBarSequence = GetPrivateProfileIntA("Game Options",
        "Hit Point Bar Sequence",
        0,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nHitPointBarSequence < 0 || m_cOptions.m_nHitPointBarSequence > 5) {
        m_cOptions.m_nHitPointBarSequence = 0;
    }
}

// 0x5AA350
void CInfGame::SaveOptions()
{
    CString sValue;

    sValue.Format("%d", m_cOptions.m_bFootStepsSounds);
    WritePrivateProfileStringA("Game Options", "Footsteps", sValue, g_pBaldurChitin->GetIniFileName());

    if ((!g_pChitin->cNetwork.GetSessionOpen() || g_pChitin->cNetwork.GetSessionHosting())
        && m_cOptions.field_4 != 0) {
        sValue.Format("%d", m_cOptions.field_4);
        WritePrivateProfileStringA("Game Options", "Grant 2000", sValue, g_pBaldurChitin->GetIniFileName());

        sValue.Format("%d", m_cOptions.m_bGore);
        WritePrivateProfileStringA("Game Options", "Chucknomitron", sValue, g_pBaldurChitin->GetIniFileName());
    }

    sValue.Format("%d", m_cOptions.m_nMouseScrollSpeed);
    WritePrivateProfileStringA("Game Options", "Mouse Scroll Speed", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nGuiFeedbackLevel);
    WritePrivateProfileStringA("Game Options", "GUI Feedback Level", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nLocatorFeedbackLevel);
    WritePrivateProfileStringA("Game Options", "Locator Feedback Level", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nBoredTime);
    WritePrivateProfileStringA("Game Options", "Bored Timeout", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bAlwaysDither);
    WritePrivateProfileStringA("Game Options", "Always Dither", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bSubtitles);
    WritePrivateProfileStringA("Game Options", "Subtitles", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nKeyboardScrollSpeed);
    WritePrivateProfileStringA("Game Options", "Keyboard Scroll Speed", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nCommandSoundsFrequency);
    WritePrivateProfileStringA("Game Options", "Command Sounds Frequency", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nSelectionSoundsFrequency);
    WritePrivateProfileStringA("Game Options", "Selection Sounds Frequency", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nEffectTextLevel);
    WritePrivateProfileStringA("Game Options", "Effect Text Level", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bDarkvision);
    WritePrivateProfileStringA("Game Options", "Darkvision", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bWeatherEnabled);
    WritePrivateProfileStringA("Game Options", "Weather", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nTutorialState);
    WritePrivateProfileStringA("Game Options", "Tutorial State", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bAttackSounds);
    WritePrivateProfileStringA("Game Options", "Attack Sounds", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nAutoPauseState);
    WritePrivateProfileStringA("Game Options", "Auto Pause State", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bAutoPauseCenter);
    WritePrivateProfileStringA("Game Options", "Auto Pause Center", sValue, g_pBaldurChitin->GetIniFileName());

    if (m_nDifficultyLevel == -1) {
        sValue.Format("%d", m_cOptions.m_nDifficultyLevel);
    } else {
        sValue.Format("%d", m_nDifficultyLevel);
    }

    WritePrivateProfileStringA("Game Options", "Difficulty Level", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bQuickItemMapping);
    WritePrivateProfileStringA("Game Options", "Quick Item Mapping", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bEnvironmentalAudio);
    WritePrivateProfileStringA("Game Options", "Environmental Audio", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bTerrainHugging);
    WritePrivateProfileStringA("Game Options", "Terrain Hugging", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bStaticAnimations);
    WritePrivateProfileStringA("Game Options", "Static Animations", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bTranslucentBlts);
    WritePrivateProfileStringA("Game Options", "Translucent Blts", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bMaxHP);
    WritePrivateProfileStringA("Game Options", "Maximum HP", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bAutoPauseOnTrap);
    WritePrivateProfileStringA("Game Options", "Pause On Trap", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", CGameSprite::SHOW_CHARACTER_HP);
    WritePrivateProfileStringA("Game Options", "Show Character HP", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bShowQuestXP);
    WritePrivateProfileStringA("Game Options", "Show Quest XP", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", g_pBaldurChitin->field_1A0);
    WritePrivateProfileStringA("Program Options", "Double Byte Character Support", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bCriticalHitScreenShake);
    WritePrivateProfileStringA("Game Options", "Critical Hit Screen Shake", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bHotkeysOnToolTips);
    WritePrivateProfileStringA("Game Options", "Hotkeys On Tooltips", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bDuplicateFloatingText);
    WritePrivateProfileStringA("Game Options", "Duplicate Floating Text", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nTilesPrecachePercent);
    WritePrivateProfileStringA("Game Options", "Tiles Precache Percent", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bSuppressExtraDifficultyDamage);
    WritePrivateProfileStringA("Game Options", "Suppress Extra Difficulty Damage", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_bAllScreenShake);
    WritePrivateProfileStringA("Game Options", "All Screen Shake", sValue, g_pBaldurChitin->GetIniFileName());

    sValue.Format("%d", m_cOptions.m_nHitPointBarSequence);
    WritePrivateProfileStringA("Game Options", "Hit Point Bar Sequence", sValue, g_pBaldurChitin->GetIniFileName());
}

// 0x5AAC30
void CInfGame::LoadMultiPlayerPermissions()
{
    if (!g_pBaldurChitin->cNetwork.GetSessionOpen()
        || !g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        return;
    }

    CMultiplayerSettings* pSettings = GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 8323
    UTIL_ASSERT(pSettings != NULL);

    CString sPermissions;
    CString sDefault("");

    GetPrivateProfileStringA("Multiplayer",
        "Default Permissions",
        sDefault,
        sPermissions.GetBuffer(10),
        10,
        g_pBaldurChitin->GetIniFileName());
    sPermissions.ReleaseBuffer(-1);

    if (sPermissions.GetLength() == 8) {
        BOOL bPurchasing = sPermissions[0] == '1';
        BOOL bAreaTransition = sPermissions[1] == '1';
        BOOL bDialog = sPermissions[2] == '1';
        BOOL bCharRecords = sPermissions[3] == '1';
        BOOL bPausing = sPermissions[4] == '1';
        BOOL bGroupPool = sPermissions[5] == '1';
        BOOL bLeader = sPermissions[6] == '1';
        BOOL bModifyChars = sPermissions[7] == '1';

        pSettings->SetPermission(-1,
            CGamePermission::PURCHASING,
            bPurchasing,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::AREA_TRANSITION,
            bAreaTransition,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::DIALOG,
            bDialog,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::CHAR_RECORDS,
            bCharRecords,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::PAUSING,
            bPausing,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::GROUP_POOL,
            bGroupPool,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::LEADER,
            bLeader,
            TRUE);
        pSettings->SetPermission(-1,
            CGamePermission::MODIFY_CHARS,
            bModifyChars,
            TRUE);
    }

    INT nRestrictStore = GetPrivateProfileIntA("Multiplayer",
        "Restrict Stores",
        0,
        g_pBaldurChitin->GetIniFileName());
    pSettings->SetRestrictStoreOption(nRestrictStore != 0);

    BYTE nImportingBitField = static_cast<BYTE>(GetPrivateProfileIntA("Multiplayer",
        "Import Character",
        CMultiplayerSettings::IMPORT_ALL,
        g_pBaldurChitin->GetIniFileName()));
    pSettings->SetImportingCharacterOption(nImportingBitField);
}

// 0x5AAEC0
void CInfGame::SaveMultiPlayerPermissions()
{
    if (!g_pBaldurChitin->cNetwork.GetSessionOpen()
        || !g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        return;
    }

    CMultiplayerSettings* pSettings = GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 3290
    UTIL_ASSERT(pSettings != NULL);

    BOOL bPurchasing = pSettings->GetPermission(-1, CGamePermission::PURCHASING);
    BOOL bAreaTransition = pSettings->GetPermission(-1, CGamePermission::AREA_TRANSITION);
    BOOL bDialog = pSettings->GetPermission(-1, CGamePermission::DIALOG);
    BOOL bCharRecords = pSettings->GetPermission(-1, CGamePermission::CHAR_RECORDS);
    BOOL bPausing = pSettings->GetPermission(-1, CGamePermission::PAUSING);
    BOOL bGroupPool = pSettings->GetPermission(-1, CGamePermission::GROUP_POOL);
    BOOL bLeader = pSettings->GetPermission(-1, CGamePermission::LEADER);
    BOOL bModifyChars = pSettings->GetPermission(-1, CGamePermission::MODIFY_CHARS);

    CString sPermissions("00000000");
    sPermissions.SetAt(0, bPurchasing + '0');
    sPermissions.SetAt(1, bAreaTransition + '0');
    sPermissions.SetAt(2, bDialog + '0');
    sPermissions.SetAt(3, bCharRecords + '0');
    sPermissions.SetAt(4, bPausing + '0');
    sPermissions.SetAt(5, bGroupPool + '0');
    sPermissions.SetAt(6, bLeader + '0');
    sPermissions.SetAt(7, bModifyChars + '0');

    WritePrivateProfileStringA("Multiplayer",
        "Default Permissions",
        sPermissions,
        g_pBaldurChitin->GetIniFileName());

    CString sTemp;

    sTemp.Format("%d", pSettings->m_bRestrictStoreOption);
    WritePrivateProfileStringA("Multiplayer",
        "Restrict Stores",
        sTemp,
        g_pBaldurChitin->GetIniFileName());

    sTemp.Format("%d", pSettings->m_nImportingBitField);
    WritePrivateProfileStringA("Multiplayer",
        "Import Character",
        sTemp,
        g_pBaldurChitin->GetIniFileName());
}

// 0x5AB190
void CInfGame::LoadGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace)
{
    // TODO: Incomplete.
}

// 0x5ABA20
void CInfGame::NewGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace)
{
    if (!bProgressBarInPlace && bProgressBarRequired == TRUE) {
        sub_59FA00(TRUE);

        g_pChitin->SetProgressBar(TRUE,
            9889,
            0,
            0,
            FALSE,
            0,
            FALSE,
            0,
            FALSE,
            FALSE,
            255);
        g_pChitin->cProgressBar.m_nActionProgress = 0;
        g_pChitin->cProgressBar.m_nActionTarget = 8000000;
        g_pChitin->cProgressBar.m_bDisableMinibars = TRUE;
    }

    if (bProgressBarInPlace || bProgressBarRequired) {
        g_pChitin->cProgressBar.AddActionTarget(625000);
    }

    m_bInLoadGame = TRUE;

    BOOL bMusicThreadPriorityChanged = FALSE;
    int nMusicThreadPriority = GetThreadPriority(g_pChitin->m_hMusicThread);

    if (GetPrivateProfileIntA("Program Options", "Volume Music", 0, g_pChitin->GetIniFileName())) {
        bMusicThreadPriorityChanged = SetThreadPriority(g_pChitin->m_hMusicThread, 15);
    }

    g_pBaldurChitin->GetTlkTable().m_override.CloseFiles();

    if (g_pChitin->cDimm.DirectoryRemoveFiles(CString(".\\mpsave\\default\\"))) {
        g_pChitin->cDimm.m_cKeyTable.RescanEverything();
    }

    InitGame(FALSE, FALSE);

    if (bProgressBarInPlace || bProgressBarRequired) {
        ProgressBarCallback(156250, FALSE);
    }

    CVariable chapter;
    chapter.SetName(CHAPTER_GLOBAL);
    m_variables.AddKey(chapter);

    m_bFromNewGame = TRUE;

    g_pChitin->cDimm.AddToDirectoryList(m_sScriptsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sSoundsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sPortraitsDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sCharactersDir, TRUE);
    g_pChitin->cDimm.AddToDirectoryList(m_sTempDir, TRUE);

    g_pBaldurChitin->GetTlkTable().OpenOverride(CString("temp/default.toh"), CString("temp/default.tot"));

    if (bProgressBarInPlace || bProgressBarRequired) {
        ProgressBarCallback(156250, FALSE);
    }

    m_cWorldMap.SetResRef(CResRef("WORLDMAP"));

    // TODO: Incomplete.

    m_cOptions.m_nNightmareMode = GetPrivateProfileIntA("Game Options",
        "Nightmare Mode",
        0,
        g_pBaldurChitin->GetIniFileName());

    if (m_cOptions.m_nNightmareMode == 1 && m_cOptions.m_nDifficultyLevel != 5) {
        m_cOptions.m_nDifficultyLevel = 5;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 8769
    UTIL_ASSERT(m_nCharacters == 0);

    m_bAnotherPlayerJoinedGame = FALSE;

    m_sSaveGame = "default";
    CScreenCharacter::SAVE_NAME = "default";

    m_bInLoadGame = FALSE;

    if (bMusicThreadPriorityChanged == TRUE) {
        SetThreadPriority(g_pChitin->m_hMusicThread, nMusicThreadPriority);
    }

    if (bProgressBarInPlace || bProgressBarRequired) {
        ProgressBarCallback(156250, FALSE);
    }

    if (!bProgressBarInPlace && bProgressBarRequired == TRUE) {
        g_pChitin->cProgressBar.m_nActionProgress = g_pChitin->cProgressBar.m_nActionTarget;
        g_pChitin->cProgressBar.m_bDisableMinibars = TRUE;
        g_pChitin->m_bDisplayStale = TRUE;

        sub_59FA00(TRUE);

        g_pChitin->SetProgressBar(FALSE,
            0,
            0,
            0,
            FALSE,
            0,
            FALSE,
            0,
            FALSE,
            FALSE,
            255);
    }

    m_nReputation = -10;
}

// 0x5AC0A0
BOOLEAN CInfGame::sub_5AC0A0(CGameArea* pArea)
{
    if (!m_bInLoadGame
        && pArea != NULL
        && pArea->m_bAreaLoaded) {
        return pArea->field_B16;
    } else {
        return FALSE;
    }
}

// 0x5AC0D0
void CInfGame::sub_5AC0D0()
{
    STRREF strError;

    for (int index = 0; index < CINFGAME_MAX_AREAS; index++) {
        if (m_gameAreas[index] != NULL && m_gameAreas[index]->m_bAreaLoaded) {
            m_gameAreas[index]->field_B16 = !m_gameAreas[index]->CanSaveGame(strError);
        }
    }
}

// 0x5ADC90
void CInfGame::DemandServerStore(const CResRef& store, BOOL bSaveToDisk)
{
    int cnt;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 9987
    UTIL_ASSERT(g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting());

    for (cnt = 0; cnt < 12; cnt++) {
        if (m_aServerStore[cnt] != NULL
            && store == m_aServerStore[cnt]->m_resRef) {
            if (bSaveToDisk) {
                m_aServerStore[cnt]->Marshal(m_sTempDir);
            }

            m_nServerStoreDemands[cnt]++;

            return;
        }
    }

    for (cnt = 0; cnt < 12; cnt++) {
        if (m_aServerStore[cnt] == NULL) {
            m_aServerStore[cnt] = new CStore(store);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 10007
            UTIL_ASSERT(m_aServerStore[cnt] != NULL);

            if (m_aServerStore[cnt]->m_resRef == "") {
                delete m_aServerStore[cnt];
                m_aServerStore[cnt] = NULL;
            } else {
                m_nServerStoreDemands[cnt] = 1;
            }

            return;
        }
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 10019
    UTIL_ASSERT(FALSE);
}

// 0x5ADE90
void CInfGame::ReleaseServerStore(const CResRef& store)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 10042
    UTIL_ASSERT(g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting());

    for (int cnt = 0; cnt < 12; cnt++) {
        if (m_aServerStore[cnt] != NULL
            && store == m_aServerStore[cnt]->m_resRef) {
            m_nServerStoreDemands[cnt]--;

            if (m_nServerStoreDemands[cnt] == 0) {
                m_aServerStore[cnt]->Marshal(m_sTempDir);

                delete m_aServerStore[cnt];

                m_aServerStore[cnt] = NULL;
            }
        }
    }
}

// 0x5ADF60
CStore* CInfGame::GetServerStore(const CResRef& store)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 10079
    UTIL_ASSERT(g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting());

    for (int cnt = 0; cnt < 12; cnt++) {
        if (m_aServerStore[cnt] != NULL
            && store == m_aServerStore[cnt]->m_resRef) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 10084
            UTIL_ASSERT(m_nServerStoreDemands[cnt] > 0);

            return m_aServerStore[cnt];
        }
    }

    return NULL;
}

// 0x5AF360
void CInfGame::UpdatePortrait(SHORT nPortrait, DWORD dwPanelId)
{
    if (nPortrait != -1) {
        CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
        if (pEngine != g_pBaldurChitin->m_pEngineProjector
            && pEngine != g_pBaldurChitin->m_pEngineMultiPlayer
            && pEngine != g_pBaldurChitin->m_pEngineSinglePlayer
            && pEngine != g_pBaldurChitin->m_pEngineWorldMap
            && pEngine != g_pBaldurChitin->m_pEngineSave) {
            CUIManager* pManager = pEngine->GetManager();
            CUIPanel* pPanel = pManager->GetPanel(dwPanelId);
            if (pPanel != NULL) {
                CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                if (pControl != NULL) {
                    pControl->InvalidateRect();
                }
            } else {
                // NOTE: Obtaining active engine second time, probably some
                // inlining. Looks similar to `CBaldurEngine::OnPortraitLClick`.
                CUIManager* pManager = g_pBaldurChitin->GetActiveEngine()->GetManager();
                CUIPanel* pPanel = pManager->GetPanel(1);
                if (pPanel != NULL) {
                    CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                    if (pControl != NULL) {
                        pControl->InvalidateRect();
                    }
                }
            }
        }
    }
}

// 0x5AF420
void CInfGame::sub_5AF420(SHORT nPortrait, DWORD dwPanelId)
{
    if (nPortrait != -1) {
        CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
        if (pEngine != g_pBaldurChitin->m_pEngineProjector
            && pEngine != g_pBaldurChitin->m_pEngineMultiPlayer
            && pEngine != g_pBaldurChitin->m_pEngineSinglePlayer
            && pEngine != g_pBaldurChitin->m_pEngineWorldMap
            && pEngine != g_pBaldurChitin->m_pEngineSave) {
            CUIManager* pManager = pEngine->GetManager();
            CUIPanel* pPanel = pManager->GetPanel(dwPanelId);
            if (pPanel != NULL) {
                CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                if (pControl != NULL) {
                    pControl->func_54();
                }
            } else {
                CUIManager* pManager = g_pBaldurChitin->GetActiveEngine()->GetManager();
                CUIPanel* pPanel = pManager->GetPanel(1);
                if (pPanel != NULL) {
                    CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                    if (pControl != NULL) {
                        pControl->func_54();
                    }
                }
            }
        }
    }
}

// 0x5AF4E0
SHORT CInfGame::GetCharacterPortraitNum(LONG nCharacterId)
{
    if (nCharacterId != -1) {
        for (SHORT nPortrait = 0; nPortrait < 6; nPortrait++) {
            if (m_characterPortraits[nPortrait] == nCharacterId) {
                return nPortrait;
            }
        }
    }

    return -1;
}

// 0x5AF510
SHORT CInfGame::GetFixedOrderCharacterPortraitNum(LONG nCharacterId)
{
    if (nCharacterId != -1) {
        for (SHORT nPortrait = 0; nPortrait < 6; nPortrait++) {
            if (m_characters[nPortrait] == nCharacterId) {
                return nPortrait;
            }
        }
    }

    return -1;
}

// 0x5AF700
void CInfGame::RemoveFamiliarResRef(const CResRef& resRef, BYTE nAlignment, BYTE nLevel)
{
    if (nAlignment < 9 && nLevel < 9) {
        POSITION pos = m_familiarResRefs[nAlignment][nLevel].GetHeadPosition();
        while (pos != NULL) {
            POSITION curr = pos;
            CResRef* pResRef = m_familiarResRefs[nAlignment][nLevel].GetNext(pos);
            if (*pResRef == resRef) {
                m_familiarResRefs[nAlignment][nLevel].RemoveAt(curr);
                break;
            }
        }
    }
}

// 0x5AF7F0
void CInfGame::WorldEngineActivated(CVidMode* pVidMode)
{
    m_nState = 0;
    m_cButtonArray.m_nSelectedButton = 100;
    m_cVRamPool.DetachSurfaces();
    m_cVRamPool.AttachSurfaces(pVidMode);
    m_gameAreas[m_visibleArea]->OnActivation();
    m_cButtonArray.ResetState();
}

// 0x5AF850
void CInfGame::WorldEngineDeactivated()
{
    if (m_gameAreas[m_visibleArea] != NULL) {
        m_gameAreas[m_visibleArea]->OnDeactivation();
    }
}

// 0x5AF870
void CInfGame::OnPortraitLClick(DWORD id)
{
    // TODO: Incomplete.
}

// 0x5AFCB0
void CInfGame::OnPortraitLDblClick(DWORD id)
{
    // TODO: Incomplete.
}

// 0x5AFD90
void CInfGame::EnablePortrait(BYTE nControlId, BOOL bEnable)
{
    g_pBaldurChitin->m_pEngineCharacter->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineInventory->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineJournal->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineMap->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineOptions->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineSpellbook->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineStore->EnablePortrait(1, nControlId, bEnable);
    g_pBaldurChitin->m_pEngineWorld->EnablePortrait(1, nControlId, bEnable);
}

// 0x5AFE60
BOOLEAN CInfGame::ExtendedDayNightAreaActive()
{
    for (int index = 0; index < CINFGAME_MAX_AREAS; index++) {
        if ((m_gameAreas[index]->m_header.m_areaType & 0x40) != 0) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x5AFE90
void CInfGame::UpdatePortraitToolTip(DWORD dwControlId, STRREF dwStrId)
{
    CUIManager* pManager;
    CUIPanel* pPanel;
    CUIControlBase* pControl;

    pManager = g_pBaldurChitin->m_pEngineCharacter->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineInventory->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineJournal->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineMap->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineOptions->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineSpellbook->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineStore->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);

    pManager = g_pBaldurChitin->m_pEngineWorld->GetManager();
    pPanel = pManager->GetPanel(1);
    pControl = pPanel->GetControl(dwControlId);
    pControl->SetToolTipStrRef(dwStrId, -1, -1);
}

// FIXME: Use reference instead of object instance.
//
// 0x5B7510
CGameArea* CInfGame::GetArea(CString sName)
{
    for (int index = 0; index < CINFGAME_MAX_AREAS; index++) {
        if (m_gameAreas[index] != NULL) {
            if (m_gameAreas[index]->m_resRef == sName) {
                return m_gameAreas[index];
            }
        }
    }

    return NULL;
}

// 0x68DE70
CGameArea* CInfGame::GetArea(SHORT nArea)
{
    // __FILE__: .\Include\InfGame.h
    // __LINE__: 1416
    UTIL_ASSERT(nArea < CINFGAME_MAX_AREAS);

    return m_gameAreas[nArea];
}

// 0x5BACE0
SHORT CInfGame::GetNumQuickWeaponSlots(SHORT nPortrait)
{
    SHORT nSlots;

    // NOTE: Uninline.
    LONG nCharacterId = GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = m_cObjectArray.GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        nSlots = static_cast<SHORT>(pSprite->GetNumQuickWeaponSlots());
    } else {
        nSlots = 0;
    }

    m_cObjectArray.ReleaseShare(nCharacterId,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    return nSlots;
}

// 0x5BB800
BOOL CInfGame::Is3DSound(int nSoundChannel)
{
    return m_ruleTables.Is3DSound(nSoundChannel);
}

// 0x5BB810
float CInfGame::GetSoundReverbMix(int nSoundChannel, int nReverb)
{
    return m_ruleTables.GetSoundReverbMix(nSoundChannel, nReverb);
}

// 0x5BB830
CResRef CInfGame::GetAnimationBam(SHORT nPortrait, BYTE range)
{
    CString sResRef;

    // NOTE: Uninline.
    LONG nCharacterId = GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = m_cObjectArray.GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        return CResRef("");
    }

    pSprite->GetAnimation()->GetAnimationResRef(sResRef, range);

    m_cObjectArray.ReleaseShare(nCharacterId,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    return CResRef(sResRef);
}

// 0x5BB960
BYTE CInfGame::GetFrameRate()
{
    return static_cast<BYTE>(g_pBaldurChitin->GetActiveEngine()->pVidMode->field_94);
}

// 0x5BE900
void CInfGame::SynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x5C0520
CStringList* CInfGame::GetSaveGames()
{
    CStringList* pList = new CStringList();

    CString sFileName;

    WIN32_FIND_DATAA ffd;
    HANDLE hFindFile = FindFirstFileA(GetDirSaveRoot() + "*.*", &ffd);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            sFileName = ffd.cFileName;
            if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0
                && sFileName != "."
                && sFileName != ".."
                && SaveGameExists(sFileName)) {
                POSITION pos = pList->GetHeadPosition();
                while (pos != NULL) {
                    if (sFileName < pList->GetAt(pos)) {
                        break;
                    }
                    pList->GetNext(pos);
                }

                if (pos != NULL) {
                    pList->InsertBefore(pos, sFileName);
                } else {
                    pList->AddTail(sFileName);
                }
            }
        } while (FindNextFileA(hFindFile, &ffd));

        FindClose(hFindFile);
    }

    return pList;
}

// 0x5C0730
BOOL CInfGame::DeleteSaveGame(const CString& sFileName)
{
    CString sDirectoryName = GetDirSaveRoot() + sFileName;

    CFileStatus cFileStatus;
    if (!CFile::GetStatus(sDirectoryName, cFileStatus)) {
        return FALSE;
    }

    sDirectoryName += "\\";
    if (!g_pChitin->cDimm.DirectoryRemoveFiles(sDirectoryName)) {
        return FALSE;
    }

    WIN32_FIND_DATAA ffd;
    HANDLE hFindFile = FindFirstFileA(sDirectoryName + "*.*", &ffd);
    if (hFindFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    do {
        if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 || ffd.cFileName[0] != '.') {
            FindClose(hFindFile);
            return FALSE;
        }
    } while (FindNextFileA(hFindFile, &ffd));

    FindClose(hFindFile);

    return RemoveDirectoryA(sDirectoryName);
}

// 0x5C0890
BOOL CInfGame::SaveGameExists(const CString& sSaveGame)
{
    CString sFileName = GetDirSaveRoot() + sSaveGame + "\\ICEWIND2.GAM";

    HANDLE hFile = CreateFileA(sFileName,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    // NOTE: Original code is slightly different (conditions inverted).
    BOOL bSuccess = FALSE;
    if (hFile != INVALID_HANDLE_VALUE) {
        unsigned char signature[8];
        DWORD dwBytesRead;
        ReadFile(hFile, signature, sizeof(signature), &dwBytesRead, NULL);
        if (dwBytesRead == sizeof(signature)
            && memcmp(signature, "GAMEV2.2", sizeof(signature)) == 0) {
            bSuccess = TRUE;
        }

        CloseHandle(hFile);
    }

    return bSuccess;
}

// 0x5C0EA0
void CInfGame::ApplyVolumeSliders(BOOLEAN a2)
{
    g_pBaldurChitin->cSoundMixer.SetMusicVolume(m_cOptions.m_nVolumeMusic);

    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(0, m_cOptions.m_nVolumeVoices);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(1, m_cOptions.m_nVolumeAmbients);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(2, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(3, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(4, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(5, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(2, m_cOptions.m_nVolumeVoices);

    for (int k = 7; k < 13; k++) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(k, m_cOptions.m_nVolumeVoices);
    }

    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(13, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(14, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(15, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(20, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(18, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(19, m_cOptions.m_nVolumeSFX);

    if (a2 == TRUE) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(16, m_cOptions.m_nVolumeAmbients);
        g_pBaldurChitin->cSoundMixer.SetChannelVolumeFast(17, m_cOptions.m_nVolumeAmbients);
    }

    g_pBaldurChitin->cSoundMixer.UpdateSoundList();
}

// 0x5BD4E0
BOOL CInfGame::SetCharacterSlot(INT nCharacterSlot, LONG nCharacterId)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 15670
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    if (m_characters[nCharacterSlot] != -1) {
        return FALSE;
    }

    m_characters[nCharacterSlot] = nCharacterId;

    return TRUE;
}

// 0x5BD530
BOOL CInfGame::ClearCharacterSlot(INT nCharacterSlot)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5BD650
LONG CInfGame::GetCharacterSlot(INT nCharacterSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 15787
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    return m_characters[nCharacterSlot];
}

// 0x5BD690
INT CInfGame::GetCharacterSlotFromId(LONG nCharacterId)
{
    for (int index = 0; index < CINFGAME_MAXCHARACTERS; index++) {
        if (m_characters[index] == nCharacterId) {
            return index;
        }
    }

    return -1;
}

// 0x5BD9D0
BOOL CInfGame::AddCharacterToAllies(LONG nCharacterId)
{
    // NOTE: Uninline.
    if (GetCharacterPortraitNum(nCharacterId) != -1) {
        return FALSE;
    }

    if (m_allies.Find(reinterpret_cast<int*>(nCharacterId)) != NULL) {
        return FALSE;
    }

    if (m_familiars.Find(reinterpret_cast<int*>(nCharacterId)) != NULL) {
        return FALSE;
    }

    m_allies.AddTail(reinterpret_cast<int*>(nCharacterId));

    return TRUE;
}

// 0x5BDA50
BOOL CInfGame::RemoveCharacterFromAllies(LONG nCharacterId)
{
    POSITION pos = m_allies.Find(reinterpret_cast<int*>(nCharacterId));
    if (pos == NULL) {
        return FALSE;
    }

    m_allies.RemoveAt(pos);

    // FIXME: What for?
    if (m_allies.GetCount() == 0) {
        m_allies.RemoveAll();
    }

    return TRUE;
}

// 0x5BDAA0
BOOL CInfGame::AddCharacterToFamiliars(LONG nCharacterId)
{
    // NOTE: Uninline.
    if (GetCharacterPortraitNum(nCharacterId) != -1) {
        return FALSE;
    }

    if (m_allies.Find(reinterpret_cast<int*>(nCharacterId)) != NULL) {
        return FALSE;
    }

    if (m_familiars.Find(reinterpret_cast<int*>(nCharacterId)) != NULL) {
        return FALSE;
    }

    m_familiars.AddTail(reinterpret_cast<int*>(nCharacterId));

    return TRUE;
}

// 0x5BDB20
BOOL CInfGame::RemoveCharacterFromFamiliars(LONG nCharacterId)
{
    POSITION pos = m_familiars.Find(reinterpret_cast<int*>(nCharacterId));
    if (pos == NULL) {
        return FALSE;
    }

    m_familiars.RemoveAt(pos);

    // FIXME: What for?
    if (m_familiars.GetCount() == 0) {
        m_familiars.RemoveAll();
    }

    return TRUE;
}

// 0x5BDB70
DWORD CInfGame::GetScrollSpeed()
{
    if (m_gameAreas[m_visibleArea]->m_nKeyScrollState != 0) {
        return m_cOptions.m_nKeyboardScrollSpeed;
    } else {
        return m_cOptions.m_nMouseScrollSpeed;
    }
}

// 0x5BDC00
void CInfGame::ReputationAdjustment(SHORT reputationAdjustment, BOOL set)
{
    // TODO: Incomplete.
}

// 0x5BDF80
void CInfGame::ChangeReputation(SHORT eventCode)
{
    LONG repMod = atol(m_ruleTables.m_tReputationMod.GetAt(CPoint(eventCode, m_nReputation / REPUTATION_MULTIPLIER - 1)));
    ReputationAdjustment(static_cast<SHORT>(repMod), FALSE);
}

// 0x5BF4B0
void CInfGame::AddDisposableItem(CItem* pItem)
{
    if (pItem != NULL) {
        CSingleLock disposableItemsLock(&m_disposableItemsCritSect, FALSE);
        disposableItemsLock.Lock(INFINITE);

        m_lDisposableItems.AddTail(pItem);

        disposableItemsLock.Unlock();
    }
}

// 0x5BF540
void CInfGame::DestroyDisposableItems()
{
    if (m_lDisposableItems.GetCount() > 0) {
        CSingleLock disposableItemsLock(&m_disposableItemsCritSect, FALSE);
        disposableItemsLock.Lock(INFINITE);

        POSITION pos = m_lDisposableItems.GetHeadPosition();
        while (pos != NULL) {
            CItem* pItem = m_lDisposableItems.GetAt(pos);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 16931
            UTIL_ASSERT(pItem != NULL);

            delete pItem;

            // NOTE: Meaningless.
            m_lDisposableItems.SetAt(pos, NULL);

            m_lDisposableItems.GetNext(pos);
        }

        m_lDisposableItems.RemoveAll();

        disposableItemsLock.Unlock();
    }
}

// 0x5BF610
void CInfGame::AddPartyGold(LONG dwAddPartyGold)
{
    if (dwAddPartyGold != 0) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            CMessagePartyGold* pMessage = new CMessagePartyGold(FALSE,
                TRUE,
                dwAddPartyGold,
                CGameObjectArray::INVALID_INDEX,
                CGameObjectArray::INVALID_INDEX);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        } else {
            if (dwAddPartyGold >= 0 || static_cast<DWORD>(-dwAddPartyGold) <= m_nPartyGold) {
                m_nPartyGold += dwAddPartyGold;
            } else {
                m_nPartyGold = 0;
            }
        }
    }
}

// 0x5BF6A0
void CInfGame::sub_5BF6A0(int a1)
{
    // TODO: Incomplete.
}

// 0x5C04F0
BOOLEAN CInfGame::FindAreaID(DWORD nAreaId)
{
    for (int index = 0; index < CINFGAME_MAX_AREAS; index++) {
        if (m_gameAreas[index] != NULL) {
            if (m_gameAreas[index]->m_nInitialAreaId == nAreaId) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

// 0x5C09C0
CString CInfGame::GetDirSaveRoot()
{
    CString sResolvedFileName;
    CString sFileName;

    sFileName = m_sMultiplayerSaveDir;
    if (!g_pBaldurChitin->lAliases.ResolveFileName(sFileName, sResolvedFileName)) {
        sResolvedFileName = sFileName;
    }

    return sResolvedFileName;
}

// 0x5C0A80
CString CInfGame::GetDirSave()
{
    return m_sMultiplayerSaveDir + m_sSaveGame + "\\";
}

// 0x5C2280
CStringList* CInfGame::GetScripts()
{
    CStringList* pList = new CStringList();

    CString sFileName;
    CString sPattern;
    CString sTemp;

    sPattern = GetDirScripts() + "*.*";

    INT nCount = 0;
    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            sFileName = findFileData.cFileName;
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0
                && sFileName != "."
                && sFileName != "..") {
                sFileName = sFileName.SpanExcluding(".");
                if (sFileName.GetLength() <= 8) {
                    if (nCount >= 16383) {
                        break;
                    }

                    sFileName.MakeUpper();

                    POSITION pos = pList->GetHeadPosition();
                    while (pos != NULL) {
                        sTemp = pList->GetAt(pos);
                        if (sFileName == sTemp) {
                            break;
                        }

                        if (sFileName < pList->GetAt(pos)) {
                            pList->InsertBefore(pos, sFileName);
                            nCount++;
                            break;
                        }

                        pList->GetNext(pos);
                    }

                    if (pos == NULL) {
                        pList->AddTail(sFileName);
                        nCount++;
                    }
                }
            }
        } while (FindNextFileA(hFindFile, &findFileData));
        FindClose(hFindFile);
    }

    return pList;
}

// 0x5C24C0
CString CInfGame::GetDirScripts()
{
    return m_sScriptsDir;
}

// 0x5C24F0
void CInfGame::StartCharacterTerminationSequence()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if (pGame->field_43E2 == 322) {
        pGame->field_43E2 = -1;
    }

    pGame->field_43E6 = 0;

    if (g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineWorld) {
        g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
    }

    g_pBaldurChitin->m_pEngineWorld->m_bGameOverPanel = TRUE;
}

// 0x5C2570
void CInfGame::ReadyCharacterTerminationSequence(int a1, int a2)
{
    if (!field_43D8) {
        // FIXME: What for (this function is not static as
        // `StartCharacterTerminationSequence`).
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        pGame->field_43E2 = 322;
        pGame->field_43E6 = 1;

        g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);

        pGame->m_tempCursor = 4;
        pGame->m_gameAreas[pGame->m_visibleArea]->m_nScrollState = 0;
        pGame->field_4AFC = 150;

        g_pBaldurChitin->m_pEngineWorld->field_10F0 = a1;
        g_pBaldurChitin->m_pEngineWorld->field_10F4 = a2;
    }
}

// 0x5C2630
void CInfGame::FeedBack(SHORT feedBackId, LONG value, BOOLEAN a3)
{
    // TODO: Incomplete.
}

// 0x5C3210
CString CInfGame::GetDirPortraits()
{
    return m_sPortraitsDir;
}

// 0x5C3510
CString CInfGame::GetDirCharacters()
{
    return m_sCharactersDir;
}

// 0x5C1090
BYTE CInfGame::GetCharactersControlled()
{
    BYTE bControlled = 0;
    CGameObject* pObject;

    for (SHORT nIndex = 0; nIndex < m_nCharacters; nIndex++) {
        LONG id = m_characterPortraits[nIndex];

        BYTE rc;
        do {
            // NOTE: Using global. Implying inlined static function.
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(id,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                bControlled |= 1 << nIndex;
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(id,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    return bControlled;
}

// 0x5C1160
BOOLEAN CInfGame::RestParty(int a2, unsigned char a3)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5C1E30
BOOL CInfGame::CanRestParty(STRREF& strError, unsigned char a2, unsigned char a3, unsigned char a4)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5C3010
CStringList* CInfGame::GetPortraits()
{
    CStringList* pList = new CStringList();

    CString sFileName;
    CString sPattern;
    CString sTemp;

    sPattern = GetDirPortraits() + "*.BMP";

    INT nCount = 0;
    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            sFileName = findFileData.cFileName;
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                sFileName = sFileName.SpanExcluding(".");
                if (sFileName.GetLength() <= 8) {
                    if (nCount >= 32767) {
                        break;
                    }

                    POSITION pos = pList->GetHeadPosition();
                    while (pos != NULL) {
                        sTemp = pList->GetAt(pos);
                        if (sFileName == sTemp) {
                            break;
                        }

                        if (sFileName < pList->GetAt(pos)) {
                            pList->InsertBefore(pos, sFileName);
                            nCount++;
                            break;
                        }

                        pList->GetNext(pos);
                    }

                    if (pos == NULL) {
                        pList->AddTail(sFileName);
                        nCount++;
                    }
                }
            }
        } while (FindNextFileA(hFindFile, &findFileData));
        FindClose(hFindFile);
    }

    return pList;
}

// 0x5C3240
CStringList* CInfGame::GetImportCharacters()
{
    CStringList* pList = new CStringList();

    CString sFileName;
    CString sPattern;
    CString sTemp;

    sPattern = GetDirCharacters() + "*.chr";

    INT nCount = 0;
    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            sFileName = findFileData.cFileName;
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                sFileName = sFileName.SpanExcluding(".");
                if (sFileName.GetLength() <= 8) {
                    if (nCount >= 32767) {
                        break;
                    }

                    FILE* stream = fopen(GetDirCharacters() + findFileData.cFileName, "rb");
                    if (stream != NULL) {
                        unsigned char data[8];
                        size_t bytesRead = fread(data, 1, sizeof(data), stream);
                        fclose(stream);

                        if (bytesRead == 8 && memcmp(data, "CHR V2.2", 8) == 0) {
                            sFileName.MakeUpper();

                            POSITION pos = pList->GetHeadPosition();
                            while (pos != NULL) {
                                sTemp = pList->GetAt(pos);
                                if (sFileName == sTemp) {
                                    break;
                                }

                                if (sFileName < pList->GetAt(pos)) {
                                    pList->InsertBefore(pos, sFileName);
                                    nCount++;
                                    break;
                                }

                                pList->GetNext(pos);
                            }

                            if (pos == NULL) {
                                pList->AddTail(sFileName);
                                nCount++;
                            }
                        }
                    }
                }
            }
        } while (FindNextFileA(hFindFile, &findFileData));
        FindClose(hFindFile);
    }

    return pList;
}

// 0x5C3540
CStringList* CInfGame::GetSounds()
{
    CStringList* pList = new CStringList();

    CString sSoundSetDirName;
    CString sPattern;
    CString sTemp;

    sPattern = GetDirSounds() + "*";
    INT nCount = 0;

    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            sSoundSetDirName = findFileData.cFileName;
            if (sSoundSetDirName != "."
                && sSoundSetDirName != ".."
                && (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
                sSoundSetDirName.MakeUpper();

                INT nLength = sSoundSetDirName.GetLength();
                if (nLength > 0 && nLength < 32) {
                    if (nCount >= 32766) {
                        break;
                    }

                    POSITION pos = pList->GetHeadPosition();
                    while (pos != NULL) {
                        sTemp = pList->GetAt(pos);
                        if (sSoundSetDirName == sTemp) {
                            break;
                        }

                        if (sSoundSetDirName < pList->GetAt(pos)) {
                            pList->InsertBefore(pos, sSoundSetDirName);
                            nCount++;
                            break;
                        }

                        pList->GetNext(pos);
                    }

                    if (pos == NULL) {
                        pList->AddTail(sSoundSetDirName);
                        nCount++;
                    }
                }
            }
        } while (FindNextFileA(hFindFile, &findFileData));
        FindClose(hFindFile);
    }

    return pList;
}

// 0x5C72D0
BOOLEAN CInfGame::GetGameSpyCharacterInformation(INT nCharacterSlot, CString& sName, CString& sRace, CString& sClass, CString& sLevel)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CString sTemp;

    LONG nCharacterId = GetFixedOrderCharacterId(nCharacterSlot);

    if (nCharacterId == CGameObjectArray::INVALID_INDEX) {
        return FALSE;
    }

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = m_cObjectArray.GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        return FALSE;
    }

    BYTE nClass = pSprite->m_derivedStats.GetBestClass();

    sName = pSprite->GetName();
    ruleTables.GetRaceStringMixed(pSprite->m_liveTypeAI.m_nRace, sClass, 0);
    ruleTables.GetClassStringGameSpy(nClass, pSprite->m_baseStats.m_specialization, sClass);

    sTemp.Format("/%d", pSprite->m_derivedStats.m_nLevel);
    sLevel += sTemp;

    m_cObjectArray.ReleaseDeny(nCharacterId,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    return TRUE;
}

// 0x5C76B0
void CInfGame::MultiplayerSetCharacterCreationLocation()
{
    CResRef areaResRef;
    CString sAreaString;
    BOOLEAN bValueSet = FALSE;

    for (BYTE nIndex = 0; nIndex < 6; nIndex++) {
        if (bValueSet) {
            break;
        }

        // NOTE: Uninline `GetFixedOrderCharacterId`.
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetFixedOrderCharacterId(nIndex);

        if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                CGameArea* pArea = pSprite->GetArea();
                if (pArea != NULL) {
                    areaResRef = pArea->m_resRef;
                    areaResRef.CopyToString(sAreaString);

                    CPoint ptStart = pSprite->GetPos();
                    g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetCharacterCreationLocation(sAreaString,
                        ptStart);

                    bValueSet = TRUE;

                    // TODO: Probably wrong, object released only when area is
                    // not null.
                    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }
        }
    }
}

// 0x5C93E0
INT CInfGame::sub_5C93E0()
{
    INT nCount = 0;

    for (SHORT nPortrait = 0; nPortrait < m_nCharacters; nPortrait++) {
        LONG nCharacterId = GetCharacterId(nPortrait);

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pSprite->field_70F2 == 1) {
                nCount++;
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    return nCount;
}

// NOTE: Somewhat broken version of `LoadMultiPlayerPermissions`.
//
// 0x5C9490
void CInfGame::ResetMultiPlayerPermissions()
{
    if (!g_pBaldurChitin->cNetwork.GetSessionOpen()
        || !g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        return;
    }

    CMultiplayerSettings* pSettings = GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 22952
    UTIL_ASSERT(pSettings != NULL);

    CString sPermissions;
    CString sDefault("");

    GetPrivateProfileStringA("Multiplayer",
        "Default Permissions",
        sDefault,
        sPermissions.GetBuffer(10),
        10,
        g_pBaldurChitin->GetIniFileName());
    sPermissions.ReleaseBuffer(-1);

    if (sPermissions.GetLength() == 8) {
        BOOL bPurchasing = sPermissions[0] == '1';
        BOOL bAreaTransition = sPermissions[1] == '1';
        BOOL bDialog = sPermissions[2] == '1';
        BOOL bCharRecords = sPermissions[3] == '1';
        BOOL bPausing = sPermissions[4] == '1';
        BOOL bGroupPool = sPermissions[5] == '1';
        BOOL bLeader = sPermissions[6] == '1';
        BOOL bModifyChars = sPermissions[7] == '1';

        // FIXME: Individual permission values are used as player slots. So
        // depending on the value appropriate permission is set either on
        // player 0 or 1.

        pSettings->SetPermission(bPurchasing,
            CGamePermission::PURCHASING,
            bPurchasing,
            TRUE);
        pSettings->SetPermission(bAreaTransition,
            CGamePermission::AREA_TRANSITION,
            bAreaTransition,
            TRUE);
        pSettings->SetPermission(bDialog,
            CGamePermission::DIALOG,
            bDialog,
            TRUE);
        pSettings->SetPermission(bCharRecords,
            CGamePermission::CHAR_RECORDS,
            bCharRecords,
            TRUE);
        pSettings->SetPermission(bPausing,
            CGamePermission::PAUSING,
            bPausing,
            TRUE);
        pSettings->SetPermission(bGroupPool,
            CGamePermission::GROUP_POOL,
            bGroupPool,
            TRUE);
        pSettings->SetPermission(bLeader,
            CGamePermission::LEADER,
            bLeader,
            TRUE);
        pSettings->SetPermission(bModifyChars,
            CGamePermission::MODIFY_CHARS,
            bModifyChars,
            TRUE);
    }

    INT nRestrictStore = GetPrivateProfileIntA("Multiplayer",
        "Restrict Stores",
        0,
        g_pBaldurChitin->GetIniFileName());
    pSettings->SetRestrictStoreOption(nRestrictStore != 0);

    BYTE nImportingBitField = static_cast<BYTE>(GetPrivateProfileIntA("Multiplayer",
        "Import Character",
        CMultiplayerSettings::IMPORT_ALL,
        g_pBaldurChitin->GetIniFileName()));
    pSettings->SetImportingCharacterOption(nImportingBitField);
}

// NOTE: Unclear why `nClass` is passed as pointer.
// TODO: Move to `CRuleTables`.
//
// 0x5CA5D0
UINT CInfGame::GetSpellcasterIndex(const BYTE& nClass)
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARD:
        return 0;
    case CAIOBJECTTYPE_C_CLERIC:
        return 1;
    case CAIOBJECTTYPE_C_DRUID:
        return 2;
    case CAIOBJECTTYPE_C_PALADIN:
        return 3;
    case CAIOBJECTTYPE_C_RANGER:
        return 4;
    case CAIOBJECTTYPE_C_SORCERER:
        return 5;
    case CAIOBJECTTYPE_C_WIZARD:
        return 6;
    }

    CString sError;
    sError.Format("Invalid spell caster index: %d", nClass);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23583
    UTIL_ASSERT_MSG(FALSE, sError);
}

// NOTE: Unclear why `nList` is passed as pointer.
// TODO: Move to `CRuleTables`.
//
// 0x5CA730
BYTE CInfGame::GetSpellcasterClass(const UINT& nIndex)
{
    switch (nIndex) {
    case 0:
        return CAIOBJECTTYPE_C_BARD;
    case 1:
        return CAIOBJECTTYPE_C_CLERIC;
    case 2:
        return CAIOBJECTTYPE_C_DRUID;
    case 3:
        return CAIOBJECTTYPE_C_PALADIN;
    case 4:
        return CAIOBJECTTYPE_C_RANGER;
    case 5:
        return CAIOBJECTTYPE_C_SORCERER;
    case 6:
        return CAIOBJECTTYPE_C_WIZARD;
    }

    CString sError;
    sError.Format("Invalid spell caster class: %d", nIndex);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23624
    UTIL_ASSERT_MSG(FALSE, sError);
}

// NOTE: Unclear why `nIndex` is passed as pointer.
// TODO: Move to `CRuleTables`.
//
// 0x5CA870
DWORD CInfGame::GetSpellcasterClassMask(const UINT& nIndex)
{
    switch (nIndex) {
    case 0:
        return CLASSMASK_BARD;
    case 1:
        return CLASSMASK_CLERIC;
    case 2:
        return CLASSMASK_DRUID;
    case 3:
        return CLASSMASK_PALADIN;
    case 4:
        return CLASSMASK_RANGER;
    case 5:
        return CLASSMASK_SORCERER;
    case 6:
        return CLASSMASK_WIZARD;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23663
    UTIL_ASSERT_MSG(FALSE, "Invalid spell caster class mask");
}

// NOTE: Unclear why `a1` is passed as pointer.
// TODO: Move to `CRuleTables`.
//
// 0x5CA910
UINT CInfGame::GetSpellcasterDomainIndex(const DWORD& nSpecialization)
{
    if ((nSpecialization & SPECMASK_CLERIC_ILMATER) != 0) {
        return 0;
    } else if ((nSpecialization & SPECMASK_CLERIC_LATHANDER) != 0) {
        return 1;
    } else if ((nSpecialization & SPECMASK_CLERIC_SELUNE) != 0) {
        return 2;
    } else if ((nSpecialization & SPECMASK_CLERIC_HELM) != 0) {
        return 3;
    } else if ((nSpecialization & SPECMASK_CLERIC_OGHMA) != 0) {
        return 4;
    } else if ((nSpecialization & SPECMASK_CLERIC_TEMPUS) != 0) {
        return 5;
    } else if ((nSpecialization & SPECMASK_CLERIC_BANE) != 0) {
        return 6;
    } else if ((nSpecialization & SPECMASK_CLERIC_MASK) != 0) {
        return 7;
    } else if ((nSpecialization & SPECMASK_CLERIC_TALOS) != 0) {
        return 8;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23714
    UTIL_ASSERT_MSG(FALSE, "Invalid spell caster domain index");
}

// 0x5CA9E0
DWORD CInfGame::GetClassMask(const BYTE& nClass)
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        return CLASSMASK_BARBARIAN;
    case CAIOBJECTTYPE_C_BARD:
        return CLASSMASK_BARD;
    case CAIOBJECTTYPE_C_CLERIC:
        return CLASSMASK_CLERIC;
    case CAIOBJECTTYPE_C_DRUID:
        return CLASSMASK_DRUID;
    case CAIOBJECTTYPE_C_FIGHTER:
        return CLASSMASK_FIGHTER;
    case CAIOBJECTTYPE_C_MONK:
        return CLASSMASK_MONK;
    case CAIOBJECTTYPE_C_PALADIN:
        return CLASSMASK_PALADIN;
    case CAIOBJECTTYPE_C_RANGER:
        return CLASSMASK_RANGER;
    case CAIOBJECTTYPE_C_ROGUE:
        return CLASSMASK_ROGUE;
    case CAIOBJECTTYPE_C_SORCERER:
        return CLASSMASK_SORCERER;
    case CAIOBJECTTYPE_C_WIZARD:
        return CLASSMASK_WIZARD;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23834
    UTIL_ASSERT_MSG(FALSE, "CInfGame::GetClassMask() - Invalid class mask!");
}

// 0x5CAAD0
BYTE CInfGame::GetSpellType(const CResRef& resRef)
{
    UINT nID;

    // NOTE: Uninline.
    if (m_songs.Find(resRef, nID)) {
        return 3;
    }

    // NOTE: Uninline.
    if (m_shapeshifts.Find(resRef, nID)) {
        return 4;
    }

    if (m_innateSpells.Find(resRef, nID)) {
        return 2;
    }

    if (m_spells.Find(resRef, nID)) {
        return 1;
    }

    CString sError(" ");
    sError.Format("*** Invalid spell: %s\n", (LPCSTR)resRef.GetResRefStr());

    // TODO: Report error.

    return 0;
}

// 0x5CADF0
void CInfGame::sub_5CADF0()
{
    // FIXME: What for?
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    for (SHORT nPortrait = 0; nPortrait < m_nCharacters; nPortrait++) {
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
            if ((pSprite->m_baseStats.m_generalState & STATE_DEAD) == 0
                && (pSprite->m_derivedStats.m_generalState & STATE_DEAD) == 0) {
                pSprite->field_9D15 = 1;
            }

            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// NOTE: Odd location.
//
// 0x428620
INT CInfGame::GetCurrentChapter()
{
    CVariable* pVar = GetVariables()->FindKey(CHAPTER_GLOBAL);
    if (pVar != NULL) {
        return pVar->m_intValue;
    }
    return 0;
}

// NOTE: Odd location
//
// 0x435110
void CInfGame::SetCurrentChapter(INT nChapter)
{
    CVariable* pVar = GetVariables()->FindKey(CHAPTER_GLOBAL);
    if (pVar != NULL) {
        pVar->m_intValue = nChapter;
    }
}

// 0x452FD0
CInfButtonArray* CInfGame::GetButtonArray()
{
    return &m_cButtonArray;
}

// 0x452FE0
LONG CInfGame::GetCharacterId(SHORT nPortrait)
{
    if (nPortrait < m_nCharacters) {
        return m_characterPortraits[nPortrait];
    }

    return CGameObjectArray::INVALID_INDEX;
}

// 0x453010
CTimerWorld* CInfGame::GetWorldTimer()
{
    return &m_worldTime;
}

// 0x453020
SHORT CInfGame::GetNumCharacters()
{
    return m_nCharacters;
}

// 0x453030
CGameObjectArray* CInfGame::GetObjectArray()
{
    return &m_cObjectArray;
}

// 0x453040
CGameArea* CInfGame::GetVisibleArea()
{
    return m_gameAreas[m_visibleArea];
}

// 0x453060
CMultiplayerSettings* CInfGame::GetMultiplayerSettings()
{
    return &m_multiplayerSettings;
}

// 0x439A70
CGameJournal* CInfGame::GetJournal()
{
    return &m_cJournal;
}

// 0x475DB0
CAIGroup* CInfGame::GetGroup()
{
    return &m_group;
}

// 0x4286A0
CVariableHash* CInfGame::GetVariables()
{
    return &m_variables;
}

// 0x6E4E80
CVidBitmap* CInfGame::GetMasterBitmap()
{
    return &m_rgbMasterBitmap;
}

// NOTE: Inlined.
LONG CInfGame::GetFixedOrderCharacterId(SHORT nSlot)
{
    if (nSlot < 6) {
        return m_characters[nSlot];
    }

    return CGameObjectArray::INVALID_INDEX;
}

// 0x40CAE0
CNamedCreatureVariableHash* CInfGame::GetNamedCreatures()
{
    return &m_namedCreatures;
}

// 0x68C010
void CInfGame::SetTempCursor(BYTE tempCursor)
{
    m_tempCursor = tempCursor;
}

// 0x45B630
CGameOptions* CInfGame::GetOptions()
{
    return &m_cOptions;
}

// 0x594070
SHORT CInfGame::GetState()
{
    return m_nState;
}

// 0x594080
void CInfGame::SetState(SHORT nState)
{
    m_nState = nState;
}

// 0x594090
BYTE CInfGame::GetIconIndex()
{
    return m_iconIndex;
}

// 0x5940A0
void CInfGame::SetIconIndex(BYTE iconIndex)
{
    m_iconIndex = iconIndex;
    m_iconResRef = "";
}

// 0x58FEC0
CSpellResRefList* CInfGame::GetSongs()
{
    return &m_songs;
}

// 0x5F67F0
CSpellResRefList* CInfGame::GetInnateSpells()
{
    return &m_innateSpells;
}

// 0x5F6800
CSpellResRefList* CInfGame::GetShapeshifts()
{
    return &m_innateSpells;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CSpellResRefList::CSpellResRefList()
{
    m_pList = NULL;
    m_nCount = 0;
}

// NOTE: Inlined.
CSpellResRefList::~CSpellResRefList()
{
    if (m_pList != NULL) {
        delete m_pList;
    }
    m_nCount = 0;
}

// FIXME: `nResRefColumn` should not be reference.
//
// 0x5C9FD0
void CSpellResRefList::Load(const C2DArray& Table, const INT& nResRefColumn)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23354
    UTIL_ASSERT(Table.GetWidth() > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23355
    UTIL_ASSERT(Table.GetHeight() > 0);

    // FIXME: Uses unsigned compare.
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23356
    UTIL_ASSERT(nResRefColumn < Table.GetWidth());

    if (m_pList != NULL) {
        delete m_pList;
        m_nCount = 0;
    }

    m_pList = new CResRef[Table.GetHeight()];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23369
    UTIL_ASSERT(m_pList != NULL);

    for (int index = 0; index < Table.GetHeight(); index++) {
        m_pList[index] = Table.GetAt(CPoint(nResRefColumn, index));
    }

    m_nCount = Table.GetHeight();
}

// 0x5CA160
bool CSpellResRefList::Find(const CResRef& resRef, UINT& nID)
{
    for (UINT nIndex = 0; nIndex < m_nCount; nIndex++) {
        if (m_pList[nIndex] == resRef) {
            nID = nIndex;
            return true;
        }
    }

    nID = 0;
    return false;
}

// FIXME: `nIndex` should not be reference.
// TODO: Is it `operator[]`?
//
// 0x5F6790
const CResRef& CSpellResRefList::Get(UINT& nIndex)
{
    // __FILE__: .\Include\InfGame.h
    // __LINE__: 652
    UTIL_ASSERT(nIndex < m_nCount);

    // __FILE__: .\Include\InfGame.h
    // __LINE__: 653
    UTIL_ASSERT(m_pList != NULL);

    return m_pList[nIndex];
}

// -----------------------------------------------------------------------------

// 0x59EB90
CSpellList::CSpellList()
{
    m_pList = NULL;
    m_nCount = 0;
}

// 0x59EBA0
CSpellList::~CSpellList()
{
    if (m_pList != NULL) {
        delete m_pList;
    }
    m_nCount = 0;
}

// 0x5CA1B0
void CSpellList::Load(const std::vector<CSpellListEntry>& spells)
{
    if (spells.empty()) {
        return;
    }

    size_t size = spells.size();
    if (size == 0) {
        return;
    }

    m_pList = new CSpellListEntry[size];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23430
    UTIL_ASSERT(m_pList != NULL);

    for (size_t index = 0; index < size; index++) {
        m_pList[index] = spells[index];
    }

    m_nCount = size;
}

// 0x5CA250
bool CSpellList::GetSpellLevel(const UINT& nID, UINT& nLevel)
{
    for (UINT nIndex = 0; nIndex < m_nCount; nIndex++) {
        if (m_pList[nIndex].m_nID == nID) {
            nLevel = m_pList[nIndex].m_nLevel;
            return true;
        }
    }

    nLevel = 0;
    return false;
}

// TODO: Is it `operator[]`?
//
// NOTE: Inlined.
UINT CSpellList::Get(UINT nIndex)
{
    // __FILE__: .\Include\InfGame.h
    // __LINE__: 724
    UTIL_ASSERT(nIndex < m_nCount);

    // __FILE__: .\Include\InfGame.h
    // __LINE__: 725
    UTIL_ASSERT(m_pList != NULL);

    return m_pList[nIndex].m_nID;
}

// -----------------------------------------------------------------------------

// 0x59EB60
CGroupedSpellList::CGroupedSpellList()
{
    m_nHighestLevel = 0;
}

// 0x59ECA0
CGroupedSpellList::~CGroupedSpellList()
{
}

// FIXME: `nClassColumn` should not be reference.
// FIXME: `nResRefColumn` should not be reference.
//
// 0x5CA2A0
void CGroupedSpellList::Load(const C2DArray& Table, const INT& nClassColumn, const INT& nResRefColumn, CSpellResRefList* pSpells)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23495
    UTIL_ASSERT(Table.GetWidth() > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23496
    UTIL_ASSERT(Table.GetHeight() > 0);

    // FIXME: Uses unsigned compare.
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23497
    UTIL_ASSERT(nClassColumn < Table.GetWidth());

    // FIXME: Uses unsigned compare.
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 23498
    UTIL_ASSERT(nResRefColumn < Table.GetWidth());

    std::vector<CSpellListEntry> lists[9];

    for (int index = 0; index < Table.GetHeight(); index++) {
        int nLevel = atol(Table.GetAt(CPoint(nClassColumn, index)));
        UINT nID = index;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 23509
        UTIL_ASSERT(nLevel <= CSPELLLIST_MAX_LEVELS);

        CString sName = Table.GetAt(CPoint(nResRefColumn, index));
        CResRef resRef(sName);

        sName = sName.Left(strlen("**"));
        if (nLevel > 0 && sName != "**") {
            if (pSpells != NULL) {
                bool result = pSpells->Find(resRef, nID);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                // __LINE__: 23524
                UTIL_ASSERT(result == true);
            }

            CSpellListEntry entry;
            entry.m_nID = nID;
            entry.m_nLevel = nLevel;
            lists[nLevel - 1].push_back(entry);
        }
    }

    // NOTE: Unsigned compare, implying `m_nHighestLevel` is also unsigned.
    for (UINT nLevel = 1; nLevel <= CSPELLLIST_MAX_LEVELS; nLevel++) {
        if (lists[nLevel - 1].size() != 0) {
            m_lists[nLevel - 1].Load(lists[nLevel - 1]);

            if (nLevel > m_nHighestLevel) {
                m_nHighestLevel = nLevel;
            }
        }
    }
}

// -----------------------------------------------------------------------------

// 0x5C7AC0
void* CGameFile::GetData()
{
    if (pRes != NULL) {
        return pRes->Demand();
    } else {
        return NULL;
    }
}

// 0x5C7AD0
DWORD CGameFile::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

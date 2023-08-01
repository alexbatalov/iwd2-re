#include "CInfGame.h"

#include <process.h>

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CBaldurProjector.h"
#include "CGameArea.h"
#include "CGameObject.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfinity.h"
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
#include "CUIControlBase.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define FIFTY_THREE 53

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

// 0x59CC30
CInfGame::CInfGame()
{
    field_1BA1 = 4;
    m_visibleArea = 0;
    memset(m_gameAreas, 0, sizeof(m_gameAreas));
    m_pGameAreaMaster = NULL;
    // TODO: Incomplete.
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

// 0x5AC110
BOOLEAN CInfGame::CanSaveGame(STRREF& strError, unsigned char a2, unsigned char a3)
{
    // TODO: Incomplete.

    return FALSE;
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
                off_8B4F84[index],
                "",
                buffer,
                128,
                ".\\Keymap.ini");
        } else {
            GetPrivateProfileStringA("Priest Spells",
                off_8B4F84[index],
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
    // TODO: Incomplete.
}

// 0x5AB190
void CInfGame::LoadGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace)
{
    // TODO: Incomplete.
}

// 0x5ABA20
void CInfGame::NewGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace)
{
    // TODO: Incomplete.
}

// 0x5AF360
void CInfGame::UpdatePortrait(SHORT nPortrait, DWORD dwPanelId)
{
    if (nPortrait != -1) {
        CBaldurEngine* pEngine = static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine);
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
                CUIManager* pManager = static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->GetManager();
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
    for (int index = 0; index < 12; index++) {
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
    for (int index = 0; index < 12; index++) {
        if (m_gameAreas[index] != NULL) {
            if (m_gameAreas[index]->m_resRef == sName) {
                return m_gameAreas[index];
            }
        }
    }

    return NULL;
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

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(0, m_cOptions.m_nVolumeVoices);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(1, m_cOptions.m_nVolumeAmbients);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(3, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(4, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(5, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeVoices);

    for (int k = 7; k < 13; k++) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(k, m_cOptions.m_nVolumeVoices);
    }

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(13, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(14, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(15, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(20, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(18, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(19, m_cOptions.m_nVolumeSFX);

    if (a2 == TRUE) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, m_cOptions.m_nVolumeAmbients);
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, m_cOptions.m_nVolumeAmbients);
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

// 0x5BF6A0
void CInfGame::sub_5BF6A0(int a1)
{
    // TODO: Incomplete.
}

// 0x5C04F0
BOOLEAN CInfGame::FindAreaID(DWORD nAreaId)
{
    for (int index = 0; index < 12; index++) {
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

    sFileName = field_4228;
    if (!g_pBaldurChitin->lAliases.ResolveFileName(sFileName, sResolvedFileName)) {
        sResolvedFileName = sFileName;
    }

    return sResolvedFileName;
}

// 0x5C0A80
CString CInfGame::GetDirSave()
{
    return field_4228 + field_4220 + "\\";
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

    if (g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineWorld) {
        g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
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

        pGame->field_1BA1 = 4;
        pGame->m_gameAreas[pGame->m_visibleArea]->m_nScrollState = 0;
        pGame->field_4AFC = 150;

        g_pBaldurChitin->m_pEngineWorld->field_10F0 = a1;
        g_pBaldurChitin->m_pEngineWorld->field_10F4 = a2;
    }
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

    // TODO: Incomplete.

    return pList;
}

// 0x5C3240
CStringList* CInfGame::GetImportCharacters()
{
    CStringList* pList = new CStringList();

    // TODO: Incomplete.

    return pList;
}

// 0x5C3540
CStringList* CInfGame::GetSounds()
{
    CStringList* pList = new CStringList();

    // TODO: Incomplete.

    return pList;
}

// 0x5C76B0
void CInfGame::MultiplayerSetCharacterCreationLocation()
{
    // TODO: Incomplete.
}

// NOTE: Unclear why `nClass` is passed as pointer.
// TODO: Move to `CRuleTables`.
//
// 0x5CA5D0
INT CInfGame::GetSpellcasterIndex(BYTE& nClass)
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
BYTE CInfGame::GetSpellcasterClass(INT& nIndex)
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
DWORD CInfGame::GetSpellcasterClassMask(INT& nIndex)
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

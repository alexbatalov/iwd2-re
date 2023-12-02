#include "CBaldurChitin.h"

#include "CBaldurProjector.h"
#include "CDungeonMaster.h"
#include "CGameAnimationType.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CInfinity.h"
#include "CResArea.h"
#include "CResCHR.h"
#include "CResCRE.h"
#include "CResDLG.h"
#include "CResEffect.h"
#include "CResGame.h"
#include "CResItem.h"
#include "CResSpell.h"
#include "CResStore.h"
#include "CResText.h"
#include "CResUI.h"
#include "CResWED.h"
#include "CResWorldMap.h"
#include "CScreenChapter.h"
#include "CScreenCharacter.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenKeymaps.h"
#include "CScreenLoad.h"
#include "CScreenMap.h"
#include "CScreenMovies.h"
#include "CScreenMultiPlayer.h"
#include "CScreenOptions.h"
#include "CScreenSave.h"
#include "CScreenSinglePlayer.h"
#include "CScreenSpellbook.h"
#include "CScreenStart.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CSearchBitmap.h"
#include "CSoundChannel.h"
#include "CUtil.h"
#include "resource.h"

#define FILE_NAME ".\\Icewind2.ini"
#define PROGRAM_OPTIONS_SECTION_KEY "Program Options"
#define FONT_NAME_KEY "Font Name"
#define DOUBLE_BYTE_CHARACTER_SUPPORT_KEY "Double Byte Character Support"
#define SIXTEEN_BIT_TEXTURES_KEY "16Bit Textures"
#define FULL_SCREEN_KEY "Full Screen"
#define DISPLAY_FREQUENCY_KEY "Display Frequency"
#define RESOLUTION_KEY "Resolution"
#define SCREEN_POSITION_X_KEY "Screen Position X"
#define SCREEN_POSITION_Y_KEY "Screen Position Y"
#define SOFT_BLT_KEY "SoftBlt"
#define SOFT_BLT_FAST_KEY "SoftBltFast"
#define SOFT_MIRROR_BLT_KEY "SoftMirrorBlt"
#define SOFT_SRC_KEY_BLT_KEY "SoftSrcKeyBlt"
#define SOFT_SRC_KEY_BLT_FAST_KEY "SoftSrcKeyBltFast"
#define USE_MIRROR_FX_KEY "Use Mirror FX"
#define STRREF_ON_KEY "Strref On"
#define BITS_PER_PIXEL_KEY "BitsPerPixel"
#define FIRST_RUN_KEY "First Run"
#define IS_3D_ACCELERATED "3D Acceleration"
#define MAXIMUM_FRAME_RATE_KEY "Maximum Frame Rate"
#define PATH_SEARCH_NODES_KEY "Path Search Nodes"
#define TOOLTIPS_KEY "Tooltips"
#define TRANSLUCENT_SHADOWS_KEY "Translucent Shadows"
#define SPRITE_MIRROR_KEY "Sprite Mirror"
#define GAMMA_CORRECTION_KEY "Gamma Correction"
#define BRIGHTNESS_CORRECTION_KEY "Brightness Correction"
#define BACKWARDS_COMPATIBLE_3D_KEY "Backwards Compatible 3d"
#define VOLUME_MOVIE_KEY "Volume Movie"
#define VOLUME_MUSIC_KEY "Volume Music"
#define VOLUME_VOICES_KEY "Volume Voices"
#define VOLUME_AMBIENTS_KEY "Volume Ambients"
#define VOLUME_SFX_KEY "Volume SFX"
#define DISPLAY_MOVIE_SUBTITLES_KEY "Display Movie Subtitles"
#define SHADED_SELECTION_BOX_KEY "Shaded Selection Box"
#define SINGLE_MEDIA_KEY "Single Media"
#define AI_THREAD_PRIORITY_KEY "AI Thread Priority"
#define NT_SMOOTH_SOUND_KEY "NT Smooth Sound"
#define MUSIC_THREAD_PRIORITY_KEY "Music Thread Priority"

#define MAX_MUSIC_POSITIONS 64

CChitin* g_pChitin;
CBaldurChitin* g_pBaldurChitin;

// 0x847F50
const GUID CBaldurChitin::GUID_BALDUR_GATE = { 0x588C135F, 0x0B15, 0x4A02, { 0x8F, 0x2D, 0x04, 0x69, 0x7B, 0xE2, 0x90, 0x4E } };

// 0x847F64
const DWORD CBaldurChitin::MINIMUM_DRIVE_SPACE = 5000000;

// 0x847F68
const DWORD CBaldurChitin::MINIMUM_DRIVE_SECTORS = 1500;

// 0x847F6C
const COLORREF CBaldurChitin::TEXTDISPLAY_COLOR_SELECT = RGB(255, 102, 0);

// 0x847F70
const COLORREF CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT = RGB(255, 183, 0);

// #guess
// 0x85DE3C
const USHORT CBaldurChitin::DEFAULT_SCREEN_WIDTH = 800;

// #guess
// 0x85DE3E
const USHORT CBaldurChitin::DEFAULT_SCREEN_HEIGHT = 600;

// NOTE: Probably static in `CBaldurChitin`.
//
// 0x8BA28C
unsigned char byte_8BA28C = 1;

// 0x8C8CA0
CString CBaldurChitin::CHUI_GUIEXT("");

// 0x8CB200
const CString CBaldurChitin::BALDUR_GAMESPY_GAMENAME("iwd2");

// 0x8CD358
const CString CBaldurChitin::BALDUR_GAMESPY_CODE1("]s{=$b");

// 0x8CD440
const CString CBaldurChitin::BALDUR_GAMESPY_CODE2("^@FH?2");

// 0x8CD340
const CString CBaldurChitin::BALDUR_GAMESPY_CODE3("Si8F5s");

// 0x8CB1A8
const CString CBaldurChitin::BALDUR_GAMESPY_CODE4("_0#9fJ");

// #guess
// 0x8CB238
CString CBaldurChitin::OVERRIDE_DIR_NAME(".\\override\\");

// 0x8CD308
const CString CBaldurChitin::PRINTSCREEN_FILE_NAME("iwd2");

// 0x8CD43C
const CString CBaldurChitin::ICON_RES_ID("IDI_GAMEICON");

// 0x8CF478
CHAR* CBaldurChitin::SONGS[100];

// 0x421E40
CBaldurChitin::CBaldurChitin()
{
    m_pObjectCursor = NULL;
    m_pEngineDM = NULL;
    m_pEngineProjector = NULL;
    m_pEngineCharacter = NULL;
    m_pEngineCreateChar = NULL;
    m_pEngineInventory = NULL;
    m_pEngineJournal = NULL;
    m_pEngineLoad = NULL;
    m_pEngineMap = NULL;
    m_pEngineOptions = NULL;
    m_pEngineSave = NULL;
    m_pEngineSpellbook = NULL;
    m_pEngineStart = NULL;
    m_pEngineWorld = NULL;
    m_pEngineStore = NULL;
    m_pEngineMultiPlayer = NULL;
    m_pEngineSinglePlayer = NULL;
    m_pEngineConnection = NULL;
    m_pEngineWorldMap = NULL;
    m_pEngineChapter = NULL;
    m_pEngineMovies = NULL;
    m_pEngineKeymaps = NULL;
    m_pObjectGame = NULL;
    m_bFontRectOutline = FALSE;
    m_bIsAutoStarting = 1;

    GetPrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FONT_NAME_KEY,
        "",
        m_sFontName.GetBuffer(128),
        128,
        FILE_NAME);
    m_sFontName.ReleaseBuffer();

    field_1A0 = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DOUBLE_BYTE_CHARACTER_SUPPORT_KEY,
        0,
        FILE_NAME);
    if (field_1A0 != 0) {
        if (m_sFontName.Compare("") == 0) {
            switch (PRIMARYLANGID(GetSystemDefaultLangID())) {
            case LANG_CHINESE:
                switch (SUBLANGID(GetSystemDefaultLangID())) {
                case SUBLANG_CHINESE_TRADITIONAL:
                    m_sFontName = "\xB7\x73\xB2\xD3\xA9\xFA\xC5\xE9";
                    break;
                case SUBLANG_CHINESE_SIMPLIFIED:
                    m_sFontName = "\xCB\xCe\xCC\xE5";
                    break;
                }
                break;
            case LANG_JAPANESE:
                m_sFontName = "\x82\x6C\x82\x72\x20\x82\x6F\x83\x53\x83\x56\x83\x62\x83\x4E";
                break;
            case LANG_KOREAN:
                m_sFontName = "\xB1\xBC\xB8\xB2\xC3\xBC";
                break;
            }
        }
    }

    field_1A4 = field_1A0;

    // NOTE: Result is unused. Probably empty condition.
    m_sFontName.Compare("");

    field_2F4 = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SIXTEEN_BIT_TEXTURES_KEY,
        0,
        FILE_NAME);

    m_bFullscreen = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        FULL_SCREEN_KEY,
        TRUE,
        FILE_NAME);

    if (CUtil::GetCurrentBitsPerPixels() < 16) {
        m_bFullscreen = TRUE;
        field_E4 = 1;
    }

    m_nNextFullscreen = m_bFullscreen;

    CVideo::FPS = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_FREQUENCY_KEY,
        60,
        FILE_NAME);

    if (CVideo::FPS < 60) {
        CVideo::FPS = 60;
    }

    // NOTE: Original code simply sets `m_bIs3dAccelerated` to `FALSE`. In order
    // to ease testing 3D implementation this value is loaded from settings.
    cVideo.m_bIs3dAccelerated = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        IS_3D_ACCELERATED,
        FALSE,
        FILE_NAME);

    memset(m_aBorderPanels, 0, sizeof(m_aBorderPanels));
    field_4A24 = 1;

    CVideo::SCREENWIDTH = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        RESOLUTION_KEY,
        800,
        FILE_NAME);

    if (CVideo::SCREENWIDTH >= GetSystemMetrics(SM_CXFULLSCREEN)) {
        field_E4 = 1;
        m_nNextFullscreen = TRUE;
        m_bFullscreen = TRUE;
    }

    field_4A28 = 0;
    field_4A2C = 0;

    INT nLogicalScreenWidth;
    INT nLogicalScreenHeight;

    switch (CVideo::SCREENWIDTH) {
    case 2048:
        CInfinity::stru_8E7538.left = 0;
        CInfinity::stru_8E7538.top = 0;
        CInfinity::stru_8E7538.right = 960;
        CInfinity::stru_8E7538.bottom = 658;

        CInfinity::stru_8E7548.left = 0;
        CInfinity::stru_8E7548.top = 0;
        CInfinity::stru_8E7548.right = 2048;
        CInfinity::stru_8E7548.bottom = 1536;

        CInfinity::stru_8E7958.left = 0;
        CInfinity::stru_8E7958.top = 0;
        CInfinity::stru_8E7958.right = 2048;
        CInfinity::stru_8E7958.bottom = 968;

        CInfinity::stru_8E7988.left = 0;
        CInfinity::stru_8E7988.top = 0;
        CInfinity::stru_8E7988.right = 2048;
        CInfinity::stru_8E7988.bottom = 1258;

        CInfinity::stru_8E79A8.left = 256;
        CInfinity::stru_8E79A8.top = 150;
        CInfinity::stru_8E79A8.right = 768;
        CInfinity::stru_8E79A8.bottom = 534;

        CInfinity::stru_8E79B8.left = 0;
        CInfinity::stru_8E79B8.top = 0;
        CInfinity::stru_8E79B8.right = 2048;
        CInfinity::stru_8E79B8.bottom = 1202;

        CInfinity::stru_8E79C8.left = 0;
        CInfinity::stru_8E79C8.top = 0;
        CInfinity::stru_8E79C8.right = 2048;
        CInfinity::stru_8E79C8.bottom = 1416;

        CInfinity::stru_8E79E0.left = 0;
        CInfinity::stru_8E79E0.top = 0;
        CInfinity::stru_8E79E0.right = 2048;
        CInfinity::stru_8E79E0.bottom = 1322;

        CInfinity::stru_8E79F8.left = 0;
        CInfinity::stru_8E79F8.top = 0;
        CInfinity::stru_8E79F8.right = 2048;
        CInfinity::stru_8E79F8.bottom = 1288;

        CInfinity::stru_8E7A10.left = 0;
        CInfinity::stru_8E7A10.top = 0;
        CInfinity::stru_8E7A10.right = 960;
        CInfinity::stru_8E7A10.bottom = 522;

        CVideo::SCREENHEIGHT = 1536;
        CHUI_GUIEXT = "10";
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[0].refMosaic), "STON10L", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[1].refMosaic), "STON10R", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[2].refMosaic), "STON10T", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[3].refMosaic), "STON10B", RESREF_SIZE);

        field_4A2C = 1;
        field_4A28 = 1;

        nLogicalScreenWidth = 1024;
        nLogicalScreenHeight = 768;
        break;
    case 1600:
        CInfinity::stru_8E7538.left = 0;
        CInfinity::stru_8E7538.top = 0;
        CInfinity::stru_8E7538.right = 736;
        CInfinity::stru_8E7538.bottom = 490;

        CInfinity::stru_8E7548.left = 0;
        CInfinity::stru_8E7548.top = 0;
        CInfinity::stru_8E7548.right = 1600;
        CInfinity::stru_8E7548.bottom = 1200;

        CInfinity::stru_8E7958.left = 0;
        CInfinity::stru_8E7958.top = 0;
        CInfinity::stru_8E7958.right = 1600;
        CInfinity::stru_8E7958.bottom = 632;

        CInfinity::stru_8E7988.left = 0;
        CInfinity::stru_8E7988.top = 0;
        CInfinity::stru_8E7988.right = 1600;
        CInfinity::stru_8E7988.bottom = 922;

        CInfinity::stru_8E79A8.left = 544;
        CInfinity::stru_8E79A8.top = 366;
        CInfinity::stru_8E79A8.right = 1056;
        CInfinity::stru_8E79A8.bottom = 750;

        CInfinity::stru_8E79B8.left = 0;
        CInfinity::stru_8E79B8.top = 0;
        CInfinity::stru_8E79B8.right = 1600;
        CInfinity::stru_8E79B8.bottom = 866;

        CInfinity::stru_8E79C8.left = 0;
        CInfinity::stru_8E79C8.top = 0;
        CInfinity::stru_8E79C8.right = 1600;
        CInfinity::stru_8E79C8.bottom = 1080;

        CInfinity::stru_8E79E0.left = 0;
        CInfinity::stru_8E79E0.top = 0;
        CInfinity::stru_8E79E0.right = 1600;
        CInfinity::stru_8E79E0.bottom = 986;

        CInfinity::stru_8E79F8.left = 0;
        CInfinity::stru_8E79F8.top = 0;
        CInfinity::stru_8E79F8.right = 1600;
        CInfinity::stru_8E79F8.bottom = 952;

        CInfinity::stru_8E7A10.left = 0;
        CInfinity::stru_8E7A10.top = 0;
        CInfinity::stru_8E7A10.right = 736;
        CInfinity::stru_8E7A10.bottom = 354;

        CVideo::SCREENHEIGHT = 1200;
        CHUI_GUIEXT = "08";

        field_4A2C = 1;
        field_4A28 = 1;

        nLogicalScreenWidth = 800;
        nLogicalScreenHeight = 600;
        break;
    case 1024:
        CInfinity::stru_8E7538.left = 0;
        CInfinity::stru_8E7538.top = 0;
        CInfinity::stru_8E7538.right = 960;
        CInfinity::stru_8E7538.bottom = 658;

        CInfinity::stru_8E7548.left = 0;
        CInfinity::stru_8E7548.top = 0;
        CInfinity::stru_8E7548.right = 1024;
        CInfinity::stru_8E7548.bottom = 768;

        CInfinity::stru_8E7958.left = 0;
        CInfinity::stru_8E7958.top = 0;
        CInfinity::stru_8E7958.right = 1024;
        CInfinity::stru_8E7958.bottom = 484;

        CInfinity::stru_8E7988.left = 0;
        CInfinity::stru_8E7988.top = 0;
        CInfinity::stru_8E7988.right = 1024;
        CInfinity::stru_8E7988.bottom = 629;

        CInfinity::stru_8E79A8.left = 256;
        CInfinity::stru_8E79A8.top = 150;
        CInfinity::stru_8E79A8.right = 768;
        CInfinity::stru_8E79A8.bottom = 534;

        CInfinity::stru_8E79B8.left = 0;
        CInfinity::stru_8E79B8.top = 0;
        CInfinity::stru_8E79B8.right = 1024;
        CInfinity::stru_8E79B8.bottom = 601;

        CInfinity::stru_8E79C8.left = 0;
        CInfinity::stru_8E79C8.top = 0;
        CInfinity::stru_8E79C8.right = 1024;
        CInfinity::stru_8E79C8.bottom = 708;

        CInfinity::stru_8E79E0.left = 0;
        CInfinity::stru_8E79E0.top = 0;
        CInfinity::stru_8E79E0.right = 1024;
        CInfinity::stru_8E79E0.bottom = 661;

        CInfinity::stru_8E79F8.left = 0;
        CInfinity::stru_8E79F8.top = 0;
        CInfinity::stru_8E79F8.right = 1024;
        CInfinity::stru_8E79F8.bottom = 644;

        CInfinity::stru_8E7A10.left = 0;
        CInfinity::stru_8E7A10.top = 0;
        CInfinity::stru_8E7A10.right = 960;
        CInfinity::stru_8E7A10.bottom = 522;

        CVideo::SCREENHEIGHT = 768;
        CHUI_GUIEXT = "10";
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[0].refMosaic), "STON10L", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[1].refMosaic), "STON10R", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[2].refMosaic), "STON10T", RESREF_SIZE);
        strncpy(reinterpret_cast<char*>(m_aBorderPanels[3].refMosaic), "STON10B", RESREF_SIZE);

        nLogicalScreenWidth = 1024;
        nLogicalScreenHeight = 768;
        break;
    case 800:
    default:
        CInfinity::stru_8E7538.left = 0;
        CInfinity::stru_8E7538.top = 0;
        CInfinity::stru_8E7538.right = 736;
        CInfinity::stru_8E7538.bottom = 490;

        CInfinity::stru_8E7548.left = 0;
        CInfinity::stru_8E7548.top = 0;
        CInfinity::stru_8E7548.right = 800;
        CInfinity::stru_8E7548.bottom = 600;

        CInfinity::stru_8E7958.left = 0;
        CInfinity::stru_8E7958.top = 0;
        CInfinity::stru_8E7958.right = 800;
        CInfinity::stru_8E7958.bottom = 316;

        CInfinity::stru_8E7988.left = 0;
        CInfinity::stru_8E7988.top = 0;
        CInfinity::stru_8E7988.right = 800;
        CInfinity::stru_8E7988.bottom = 461;

        CInfinity::stru_8E79A8.left = 144;
        CInfinity::stru_8E79A8.top = 66;
        CInfinity::stru_8E79A8.right = 656;
        CInfinity::stru_8E79A8.bottom = 450;

        CInfinity::stru_8E79B8.left = 0;
        CInfinity::stru_8E79B8.top = 0;
        CInfinity::stru_8E79B8.right = 800;
        CInfinity::stru_8E79B8.bottom = 433;

        CInfinity::stru_8E79C8.left = 0;
        CInfinity::stru_8E79C8.top = 0;
        CInfinity::stru_8E79C8.right = 800;
        CInfinity::stru_8E79C8.bottom = 540;

        CInfinity::stru_8E79E0.left = 0;
        CInfinity::stru_8E79E0.top = 0;
        CInfinity::stru_8E79E0.right = 800;
        CInfinity::stru_8E79E0.bottom = 493;

        CInfinity::stru_8E79F8.left = 0;
        CInfinity::stru_8E79F8.top = 0;
        CInfinity::stru_8E79F8.right = 800;
        CInfinity::stru_8E79F8.bottom = 476;

        CInfinity::stru_8E7A10.left = 0;
        CInfinity::stru_8E7A10.top = 0;
        CInfinity::stru_8E7A10.right = 736;
        CInfinity::stru_8E7A10.bottom = 354;

        CVideo::SCREENHEIGHT = 600;
        CHUI_GUIEXT = "08";

        nLogicalScreenWidth = 800;
        nLogicalScreenHeight = 600;
        break;
    }

    CVidMode::word_8BA320 = static_cast<SHORT>(3 * (((CInfinity::stru_8E7548.right - CInfinity::stru_8E7548.left + 63) / 64 + 1) * ((CInfinity::stru_8E7548.bottom - CInfinity::stru_8E7548.top + 63) / 64 + 1)) / 2);

    // Left.
    m_aBorderPanels[0].nPanelID = -5;
    m_aBorderPanels[0].x = 0;
    m_aBorderPanels[0].y = 0;
    m_aBorderPanels[0].nWidth = (nLogicalScreenWidth - DEFAULT_SCREEN_WIDTH) / 2;
    m_aBorderPanels[0].nHeight = nLogicalScreenHeight;
    m_aBorderPanels[0].nType = 1;

    // Right.
    m_aBorderPanels[1].nPanelID = -4;
    m_aBorderPanels[1].x = m_aBorderPanels[0].nWidth + DEFAULT_SCREEN_WIDTH;
    m_aBorderPanels[1].y = 0;
    m_aBorderPanels[1].nWidth = (nLogicalScreenWidth - DEFAULT_SCREEN_WIDTH) / 2;
    m_aBorderPanels[1].nHeight = nLogicalScreenHeight;
    m_aBorderPanels[1].nType = 1;

    // Top.
    m_aBorderPanels[2].nPanelID = -3;
    m_aBorderPanels[2].x = m_aBorderPanels[0].nWidth;
    m_aBorderPanels[2].y = 0;
    m_aBorderPanels[2].nWidth = DEFAULT_SCREEN_WIDTH;
    m_aBorderPanels[2].nHeight = (nLogicalScreenHeight - DEFAULT_SCREEN_HEIGHT) / 2;
    m_aBorderPanels[2].nType = 1;

    // Bottom.
    m_aBorderPanels[3].nPanelID = -2;
    m_aBorderPanels[3].x = m_aBorderPanels[0].nWidth;
    m_aBorderPanels[3].y = m_aBorderPanels[2].nHeight + DEFAULT_SCREEN_HEIGHT;
    m_aBorderPanels[3].nWidth = DEFAULT_SCREEN_WIDTH;
    m_aBorderPanels[3].nHeight = (nLogicalScreenHeight - DEFAULT_SCREEN_HEIGHT) / 2;
    m_aBorderPanels[3].nType = 1;

    m_ptScreen.x = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SCREEN_POSITION_X_KEY,
        (GetSystemMetrics(SM_CXFULLSCREEN) - CVideo::SCREENWIDTH) / 2,
        FILE_NAME);
    m_ptScreen.y = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SCREEN_POSITION_Y_KEY,
        (GetSystemMetrics(SM_CYFULLSCREEN) - CVideo::SCREENHEIGHT) / 2,
        FILE_NAME);

    m_dwCloseConfirmationFlags = 0x124;
    m_dwCloseConfirmationStrId = 20186;
    field_49AA = 0;
    field_49AB = 0;
    field_49B0 = 0;
    field_49B1 = 0;

    cVideo.cVidBlitter.m_bSoftBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftBltFast = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftMirrorBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftSrcKeyBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftSrcKeyBltFast = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    m_bUseMirrorFX = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        USE_MIRROR_FX_KEY,
        TRUE,
        FILE_NAME);

    CTlkTable::STRREF_ON = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        STRREF_ON_KEY,
        FALSE,
        FILE_NAME);

    g_pBaldurChitin = this;
    g_pChitin = this;

    m_cCachingStatus.Init();
    m_cSwitchingCDStatus.Init();

    g_pChitin->field_2EC = field_4A28;
    field_4F38 = 0;
    field_4F3C = 0;
}

// 0x422EB0
CBaldurChitin::~CBaldurChitin()
{
    if (CTlkTable::STRREF_ON) {
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            STRREF_ON_KEY,
            "1",
            FILE_NAME);
    } else {
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            STRREF_ON_KEY,
            "0",
            FILE_NAME);
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FIRST_RUN_KEY,
        "1",
        FILE_NAME);

    m_cTlkTable.CloseFile(0, byte_8FB954);
    m_cTlkTable.CloseFile(0, byte_8BA28C);

    if (m_pObjectGame != NULL) {
        delete m_pObjectGame;
        m_pObjectGame = NULL;
    }

    if (m_pEngineChapter != NULL) {
        delete m_pEngineChapter;
        m_pEngineChapter = NULL;
    }

    if (m_pEngineWorld != NULL) {
        delete m_pEngineWorld;
        m_pEngineWorld = NULL;
    }

    if (m_pEngineStore != NULL) {
        delete m_pEngineStore;
        m_pEngineStore = NULL;
    }

    if (m_pEngineWorldMap != NULL) {
        delete m_pEngineWorldMap;
        m_pEngineWorldMap = NULL;
    }

    if (m_pEngineConnection != NULL) {
        delete m_pEngineConnection;
        m_pEngineConnection = NULL;
    }

    if (m_pEngineMultiPlayer != NULL) {
        delete m_pEngineMultiPlayer;
        m_pEngineMultiPlayer = NULL;
    }

    if (m_pEngineSinglePlayer != NULL) {
        delete m_pEngineSinglePlayer;
        m_pEngineSinglePlayer = NULL;
    }

    if (m_pEngineStart != NULL) {
        delete m_pEngineStart;
        m_pEngineStart = NULL;
    }

    if (m_pEngineSpellbook != NULL) {
        delete m_pEngineSpellbook;
        m_pEngineSpellbook = NULL;
    }

    if (m_pEngineSave != NULL) {
        delete m_pEngineSave;
        m_pEngineSave = NULL;
    }

    if (m_pEngineOptions != NULL) {
        delete m_pEngineOptions;
        m_pEngineOptions = NULL;
    }

    if (m_pEngineMap != NULL) {
        delete m_pEngineMap;
        m_pEngineMap = NULL;
    }

    if (m_pEngineLoad != NULL) {
        delete m_pEngineLoad;
        m_pEngineLoad = NULL;
    }

    if (m_pEngineJournal != NULL) {
        delete m_pEngineJournal;
        m_pEngineJournal = NULL;
    }

    if (m_pEngineInventory != NULL) {
        delete m_pEngineInventory;
        m_pEngineInventory = NULL;
    }

    if (m_pEngineCreateChar != NULL) {
        delete m_pEngineCreateChar;
        m_pEngineCreateChar = NULL;
    }

    if (m_pEngineCharacter != NULL) {
        delete m_pEngineCharacter;
        m_pEngineCharacter = NULL;
    }

    if (m_pEngineProjector != NULL) {
        delete m_pEngineProjector;
        m_pEngineProjector = NULL;
    }

    if (m_pEngineDM != NULL) {
        delete m_pEngineDM;
        m_pEngineDM = NULL;
    }

    if (m_pEngineMovies != NULL) {
        delete m_pEngineMovies;
        m_pEngineMovies = NULL;
    }

    if (m_pEngineKeymaps != NULL) {
        delete m_pEngineKeymaps;
        m_pEngineKeymaps = NULL;
    }

    if (m_pObjectCursor != NULL) {
        delete m_pObjectCursor;
        m_pObjectCursor = NULL;
    }

    if (m_pMusicPositions != NULL) {
        delete m_pMusicPositions;
        m_pMusicPositions = NULL;
    }
}

// 0x423210
CRes* CBaldurChitin::AllocResObject(int nType)
{
    switch (nType) {
    case 1001:
        return new CResWED();
    case 1002:
        return new CResUI();
    case 1005:
        return new CResItem();
    case 1006:
        return new CResSpell();
    case 1007:
        return new CResText();
    case 1008:
        return new CResText();
    case 1009:
        return new CResCRE();
    case 1010:
        return new CResArea();
    case 1011:
        return new CResDLG();
    case 1012:
        return new CResText();
    case 1013:
        return new CResGame();
    case 1014:
        return new CResStore();
    case 1015:
        return new CResWorldMap();
    case 1016:
        return new CResEffect();
    case 1017:
        return new CResText();
    case 1018:
        return new CResCHR();
    default:
        return CChitin::AllocResObject(nType);
    }
}

// 0x4237A0
void CBaldurChitin::AsynchronousUpdate(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    if (!m_bReInitializing) {
        m_cMessageHandler.AsynchronousUpdate();
    }

    CChitin::AsynchronousUpdate(nTimerID, uMsg, dwUser, dw1, dw2);

    if (!m_bReInitializing) {
        m_cMessageHandler.PostAsynchronousUpdate();
    }
}

// 0x423800
void CBaldurChitin::Init(HINSTANCE hInstance)
{
    CString maleURI;
    CString femaleURI;
    CString path;
    BOOLEAN bOpened;

    m_pMusicPositions = new CMusicPosition[MAX_MUSIC_POSITIONS];
    for (int k = 0; k < MAX_MUSIC_POSITIONS; k++) {
        m_pMusicPositions[k].m_areaResRef = "XXXXXXXX";
        m_pMusicPositions[k].m_nSong = -1;
        m_pMusicPositions[k].m_nSection = 0;
        m_pMusicPositions[k].m_nPosition = 0;
    }

    g_pChitin->cDimm.AddToDirectoryList(OVERRIDE_DIR_NAME, FALSE);

    InitResources();

    m_pObjectCursor = new CInfCursor();

    m_pEngineDM = new CDungeonMaster();
    m_pEngineProjector = new CBaldurProjector();
    m_pEngineCharacter = new CScreenCharacter();
    m_pEngineCreateChar = new CScreenCreateChar();
    m_pEngineInventory = new CScreenInventory();
    m_pEngineJournal = new CScreenJournal();
    m_pEngineLoad = new CScreenLoad();
    m_pEngineMap = new CScreenMap();
    m_pEngineOptions = new CScreenOptions();
    m_pEngineSave = new CScreenSave();
    m_pEngineSpellbook = new CScreenSpellbook();
    m_pEngineStart = new CScreenStart();
    m_pEngineWorld = new CScreenWorld();
    m_pEngineStore = new CScreenStore();
    m_pEngineMultiPlayer = new CScreenMultiPlayer();
    m_pEngineSinglePlayer = new CScreenSinglePlayer();
    m_pEngineConnection = new CScreenConnection();
    m_pEngineWorldMap = new CScreenWorldMap();
    m_pEngineChapter = new CScreenChapter();
    m_pEngineMovies = new CScreenMovies();
    m_pEngineKeymaps = new CScreenKeymaps();

    m_pObjectGame = new CInfGame();
    m_pObjectGame->StartSearchThread();

    m_pStartingEngine = m_pEngineDM;

    AddEngine(m_pEngineDM);
    AddEngine(m_pEngineProjector);
    AddEngine(m_pEngineCharacter);
    AddEngine(m_pEngineCreateChar);
    AddEngine(m_pEngineInventory);
    AddEngine(m_pEngineJournal);
    AddEngine(m_pEngineLoad);
    AddEngine(m_pEngineMap);
    AddEngine(m_pEngineOptions);
    AddEngine(m_pEngineSave);
    AddEngine(m_pEngineSpellbook);
    AddEngine(m_pEngineStart);
    AddEngine(m_pEngineWorld);
    AddEngine(m_pEngineStore);
    AddEngine(m_pEngineMultiPlayer);
    AddEngine(m_pEngineSinglePlayer);
    AddEngine(m_pEngineConnection);
    AddEngine(m_pEngineWorldMap);
    AddEngine(m_pEngineChapter);
    AddEngine(m_pEngineMovies);
    AddEngine(m_pEngineKeymaps);

    maleURI = "hd0:\\dialog.tlk";
    femaleURI = "hd0:\\dialogf.tlk";
    path = "";

    if (lAliases.ResolveFileName(femaleURI, path) == TRUE) {
        CFileStatus fileStatus;
        if (CFile::GetStatus(path, fileStatus)) {
            bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8BA28C, TRUE);
            if (bOpened) {
                if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                    bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, TRUE);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                    // __LINE__: 1148
                    UTIL_ASSERT(bOpened);
                }
            } else {
                byte_8BA28C = byte_8FB954;
                if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                    bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, TRUE);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                    // __LINE__: 1158
                    UTIL_ASSERT(bOpened);
                }
            }
        } else {
            byte_8BA28C = byte_8FB954;
            if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, TRUE);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                // __LINE__: 1169
                UTIL_ASSERT(bOpened);
            }
        }
    } else {
        byte_8BA28C = byte_8FB954;
        if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
            bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, TRUE);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
            // __LINE__: 1181
            UTIL_ASSERT(bOpened);
        }
    }

    if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
        CGameAnimationType::MIRROR_BAM = 1;
    }
}

// 0x424180
void CBaldurChitin::MessageThreadMain(void* userInfo)
{
    RegisterThread();

    while (!m_bExitMessageThread) {
        INT nMillis;
        while (!m_bExitMessageThread) {
            if (g_pChitin->cNetwork.GetSessionOpen()
                && g_pChitin->cNetwork.m_idLocalPlayer != 0) {
                break;
            }

            nMillis = 1000;
            SleepEx(nMillis, FALSE);
        }

        while (!m_bExitMessageThread) {
            if (nMillis < 0) {
                break;
            }

            nMillis = g_pChitin->cNetwork.ThreadLoop();
            if (nMillis > 0) {
                SleepEx(nMillis, FALSE);
            }
        }
    }
}

// 0x424220
void CBaldurChitin::MusicThreadMain(void* userInfo)
{
    RegisterThread();

    while (!m_bExitMusicThread) {
        g_pChitin->cSoundMixer.UpdateMusic();
        SleepEx(25, FALSE);
    }
}

// 0x424260
void CBaldurChitin::RSThreadMain(void* userInfo)
{
    RegisterThread();

    while (!m_bExitRSThread) {
        cDimm.Update();

        if (!m_bExitRSThread) {
            SuspendThread(m_hRSThread);
        }
    }
}

// 0x4242B0
void CBaldurChitin::MainAIThread(void* userInfo)
{
    // NOTE: Not sure if the next two are static to this function. They are not
    // initialized and only used in this function.

    // 0x8CF6E0
    static DWORD dword_8CF6E0;

    // 0x8CF6E4
    static DWORD dword_8CF6E4;

    RegisterThread();

    INT nAIThreadPriority = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY, AI_THREAD_PRIORITY_KEY, 15, g_pChitin->GetIniFileName());
    if (nAIThreadPriority < 0 || (nAIThreadPriority > 2 && nAIThreadPriority != 15)) {
        nAIThreadPriority = 15;

        CString sValue;
        sValue.Format("%d", nAIThreadPriority);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY, AI_THREAD_PRIORITY_KEY, sValue, g_pChitin->GetIniFileName());
    }

    SetThreadPriority(GetCurrentThread(), nAIThreadPriority);

    if (!g_pChitin->field_1A28) {
        g_pChitin->field_1A28 = 1;

        if (g_pChitin->dwPlatformId == VER_PLATFORM_WIN32_NT) {
            if (GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY, NT_SMOOTH_SOUND_KEY, 1, g_pChitin->GetIniFileName()) != 0) {
                SetThreadPriority(GetCurrentThread(), 2);
            }
        }
    }

    INT nMusicThreadPriority = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY, MUSIC_THREAD_PRIORITY_KEY, 15, g_pChitin->GetIniFileName());
    if (nMusicThreadPriority < 0 || (nMusicThreadPriority > 2 && nMusicThreadPriority != 15)) {
        nMusicThreadPriority = 15;

        CString sValue;
        sValue.Format("%d", nMusicThreadPriority);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY, MUSIC_THREAD_PRIORITY_KEY, sValue, g_pChitin->GetIniFileName());
    }

    SetThreadPriority(m_hMusicThread, nMusicThreadPriority);

    int v1 = 0;
    while (!m_bExitMainAIThread) {
        if (g_pBaldurChitin->pActiveEngine == g_pBaldurChitin->m_pEngineProjector) {
            if (v1++ == 10) {
                v1 = 0;
                if (WaitForSingleObject(m_eventTimer, 100) == WAIT_ABANDONED) {
                    return;
                }

                ResetEvent(m_eventTimer);
            }
        } else {
            if (WaitForSingleObject(m_eventTimer, 100) == WAIT_ABANDONED) {
                return;
            }

            if (m_nRenderPerSec >= 15 || m_nAIPerSec <= 24) {
                if (field_19C != 0) {
                    field_19C = max(field_19C - 1, 0);
                    if (field_19C != 0) {
                        SleepEx(field_19C, FALSE);
                    }
                }
            } else {
                if (field_19C < 30) {
                    field_19C += 5;
                }
                SleepEx(field_19C, FALSE);
            }

            ResetEvent(m_eventTimer);

            DWORD nTickCount = GetTickCount();
            dword_8CF6E4 = nTickCount - dword_8CF6E0;
            if (dword_8CF6E4 < 1000 / TIMER_UPDATES_PER_SECOND - 10) {
                continue;
            }

            dword_8CF6E0 = nTickCount;
        }

        if (g_pChitin->m_bAIStale == TRUE) {
            g_pChitin->m_bInAsynchronousUpdate = TRUE;
            g_pChitin->AsynchronousUpdate(0, 0, 0, 0, 0);
            g_pChitin->m_bInAsynchronousUpdate = FALSE;
            g_pChitin->m_bDisplayStale = TRUE;
        }

        if (m_bExitMainAIThread) {
            SuspendThread(m_hMainAIThread);
        }
    }
}

// 0x422B80
DWORD CBaldurChitin::GetIDSInvalidVideoMode()
{
    return IDS_INVALID_VIDEO_MODE;
}

// 0x422B90
DWORD CBaldurChitin::GetIDSOpenGLDll()
{
    return IDS_OPENGLL_DLL;
}

// 0x422BA0
DWORD CBaldurChitin::GetIDSExclusiveMode()
{
    return IDS_EXSLUSIVE_MODE;
}

// 0x49FC40
DWORD CBaldurChitin::GetIDSChoosePixelFormat()
{
    return IDS_CHOOSE_PIXEL_FORMAT;
}

// 0x422BB0
DWORD CBaldurChitin::GetIDSSetPixelFormat()
{
    return IDS_SET_PIXEL_FORMAT;
}

// 0x422BC0
DWORD CBaldurChitin::GetIDSSetGameResolution()
{
    return IDS_SET_GAME_RESOLUTION;
}

// 0x422BD0
DWORD CBaldurChitin::GetIDSSetGameBitDepth()
{
    return IDS_SET_GAME_BIT_DEPTH;
}

// 0x422BE0
DWORD CBaldurChitin::GetIDSBadDeskTopBitDepth()
{
    return IDS_BAD_DESKTOP_BIT_DEPTH;
}

// 0x422BF0
DWORD CBaldurChitin::GetIDSWindowsFonts()
{
    return IDS_WINDOWS_FONTS;
}

// 0x422C00
const CString& CBaldurChitin::GetIconRes()
{
    return ICON_RES_ID;
}

// 0x422C10
void CBaldurChitin::GetScreenShotFilePrefix(CString& szGameFileName)
{
    szGameFileName = PRINTSCREEN_FILE_NAME;
}

// 0x422C30
void CBaldurChitin::SetProgressBarActivateEngine(BOOL bValue)
{
    m_cCachingStatus.m_bActivateEngine = bValue;
}

// 0x422C40
void CBaldurChitin::SetCDSwitchActivateEngine(BOOL bValue)
{
    m_cSwitchingCDStatus.m_bActivateEngine = bValue;
}

// 0x424610
void CBaldurChitin::TranslateType(int nType, CString& sRes)
{
    switch (nType) {
    case 1001:
        sRes = "WED";
        break;
    case 1002:
        sRes = "CHU";
        break;
    case 1005:
        sRes = "ITM";
        break;
    case 1006:
        sRes = "SPL";
        break;
    case 1007:
        sRes = "BCS";
        break;
    case 1008:
        sRes = "IDS";
        break;
    case 1009:
        sRes = "CRE";
        break;
    case 1010:
        sRes = "ARE";
        break;
    case 1011:
        sRes = "DLG";
        break;
    case 1012:
        sRes = "2DA";
        break;
    case 1013:
        sRes = "GAM";
        break;
    case 1014:
        sRes = "STO";
        break;
    case 1015:
        sRes = "WMP";
        break;
    case 1016:
        sRes = "EFF";
        break;
    case 1017:
        sRes = "BS";
        break;
    case 1018:
        sRes = "CHR";
        break;
    case 1019:
        sRes = "VVC";
        break;
    case 1020:
        sRes = "VEF";
        break;
    case 1022:
        sRes = "RES";
        break;
    case 2050:
        sRes = "INI";
        break;
    default:
        CChitin::TranslateType(nType, sRes);
    }
}

// 0x424800
int CBaldurChitin::TranslateType(const CString& sRes)
{
    if (sRes.CompareNoCase("WED") == 0) {
        return 1001;
    } else if (sRes.CompareNoCase("CHU") == 0) {
        return 1002;
    } else if (sRes.CompareNoCase("ITM") == 0) {
        return 1005;
    } else if (sRes.CompareNoCase("SPL") == 0) {
        return 1006;
    } else if (sRes.CompareNoCase("BCS") == 0) {
        return 1007;
    } else if (sRes.CompareNoCase("IDS") == 0) {
        return 1008;
    } else if (sRes.CompareNoCase("CRE") == 0) {
        return 1009;
    } else if (sRes.CompareNoCase("ARE") == 0) {
        return 1010;
    } else if (sRes.CompareNoCase("DLG") == 0) {
        return 1011;
    } else if (sRes.CompareNoCase("2DA") == 0) {
        return 1012;
    } else if (sRes.CompareNoCase("GAM") == 0) {
        return 1013;
    } else if (sRes.CompareNoCase("STO") == 0) {
        return 1014;
    } else if (sRes.CompareNoCase("WMP") == 0) {
        return 1015;
    } else if (sRes.CompareNoCase("EFF") == 0) {
        return 1016;
    } else if (sRes.CompareNoCase("BS") == 0) {
        return 1017;
    } else if (sRes.CompareNoCase("CHR") == 0) {
        return 1018;
    } else if (sRes.CompareNoCase("VVC") == 0) {
        return 1019;
    } else if (sRes.CompareNoCase("VEF") == 0) {
        return 1020;
    } else if (sRes.CompareNoCase("RES") == 0) {
        return 1022;
    } else if (sRes.CompareNoCase("INI") == 0) {
        return 2050;
    } else {
        return CChitin::TranslateType(sRes);
    }
}

// 0x424A70
void CBaldurChitin::OnAltTab(HWND hWnd, BOOL a2)
{
    CChitin::OnAltTab(hWnd, a2);
}

// 0x424A90
BOOL CBaldurChitin::InitializeServices(HWND hWnd)
{
    return CChitin::InitializeServices(hWnd);
}

// 0x424AA0
BOOLEAN CBaldurChitin::FlipFullScreenMode(BOOLEAN bSave)
{
    BOOLEAN bWasFullscreen = m_bFullscreen;

    // NOTE: Uninline.
    CChitin::FlipFullScreenMode(bSave);

    if (bSave) {
        if (bWasFullscreen) {
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                FULL_SCREEN_KEY,
                "0",
                GetIniFileName());
        } else {
            CString sValue;

            sValue.Format("%d", m_ptScreen.x);
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                SCREEN_POSITION_X_KEY,
                sValue,
                GetIniFileName());

            sValue.Format("%d", m_ptScreen.y);
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                SCREEN_POSITION_Y_KEY,
                sValue,
                GetIniFileName());

            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                FULL_SCREEN_KEY,
                "1",
                GetIniFileName());
        }
    }

    return m_bFullscreen;
}

// 0x424BD0
void CBaldurChitin::SetSoftSrcKeyBltFast(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftSrcKeyBltFast = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424C20
void CBaldurChitin::SetSoftBltFast(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftBltFast = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424C70
void CBaldurChitin::SetSoftSrcKeyBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftSrcKeyBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424CC0
void CBaldurChitin::SetSoftBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424D10
void CBaldurChitin::SetSoftMirrorBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftMirrorBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424D60
void CBaldurChitin::ShutDown(int nLineNumber, const char* szFileName, const char* text)
{
    if (nLineNumber == -1) {
        SaveOptions();
    }
    CChitin::ShutDown(nLineNumber, szFileName, text);
}

// 0x422D00
BOOL CBaldurChitin::Is3DSound(int nSoundChannel)
{
    if (m_pObjectGame != NULL) {
        return m_pObjectGame->Is3DSound(nSoundChannel);
    }

    return FALSE;
}

// 0x422D20
float CBaldurChitin::GetSoundReverbMix(int nSoundChannel, int nReverb)
{
    if (m_pObjectGame != NULL) {
        return m_pObjectGame->GetSoundReverbMix(nSoundChannel, nReverb);
    }

    return 0.0;
}

// 0x422D70
BOOL CBaldurChitin::GetEAXActive()
{
    if (m_pObjectGame != NULL) {
        return m_pObjectGame->GetOptions()->m_bEnvironmentalAudio;
    }

    return FALSE;
}

// 0x422D90
int CBaldurChitin::GetSoundEnvironment(EAXPRESET& preset, int environment)
{
    if (m_pObjectGame != NULL) {
        return m_pObjectGame->GetRuleTables().GetSoundEnvironment(preset, environment);
    }

    return EAX_ENVIRONMENT_GENERIC;
}

// 0x422DC0
void CBaldurChitin::GetGameSpyGameName(CString& sGameSpyName)
{
    sGameSpyName = BALDUR_GAMESPY_GAMENAME;
}

// #guess
// 0x422DE0
const char* CBaldurChitin::GetIniFileName()
{
    return ".\\Icewind2.ini";
}

// 0x422DF0
const char* CBaldurChitin::GetKeyFileName()
{
    return ".\\Chitin.key";
}

// #guess
// 0x422E00
const char* CBaldurChitin::GetLogFileName()
{
    return ".\\Icewind2.log";
}

// #guess
// 0x422E10
const char* CBaldurChitin::GetErrFileName()
{
    return ".\\Icewind2.err";
}

// 0x422E20
BYTE CBaldurChitin::GetNumberSoundChannels()
{
    return 21;
}

// 0x422E30
LONG CBaldurChitin::GetMovieVolume()
{
    // NOTE: Looks odd, generated binary does not match.
    LONG v1 = m_pObjectGame->GetOptions()->m_nVolumeMovie - 100;
    return -(v1 * v1);
}

// 0x422E70
void CBaldurChitin::UnloadFonts()
{
    field_4A34.Unload();
    CVidFont::UnloadAllFonts();
}

// 0x422E80
void CBaldurChitin::RedrawScreen()
{
    if (pActiveEngine != NULL) {
        static_cast<CBaldurEngine*>(pActiveEngine)->GetManager()->InvalidateRect(NULL);
    }
}

// 0x422EA0
void CBaldurChitin::SetRenderCount(BYTE nCount)
{
    CUIManager::RENDER_COUNT = nCount;
}

// 0x422E50
void CBaldurChitin::SetSoundVolumes()
{
    if (m_pObjectGame != NULL) {
        m_pObjectGame->ApplyVolumeSliders(TRUE);
    }
}

// 0x424D90
void CBaldurChitin::LoadOptions()
{
    CGameOptions* pOptions = m_pObjectGame->GetOptions();

    pOptions->m_nTooltips = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        TOOLTIPS_KEY,
        30,
        GetIniFileName());

    pOptions->m_bTranslucentShadows = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        TRANSLUCENT_SHADOWS_KEY,
        1,
        GetIniFileName());

    CVidCell::TRANSLUCENT_SHADOWS_ON = pOptions->m_bTranslucentShadows;

    if (pOptions->m_nTooltips > 99 && pOptions->m_nTooltips != INT_MAX) {
        pOptions->m_nTooltips = 30;
    }

    BYTE nGammaCorrection = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        GAMMA_CORRECTION_KEY,
        0,
        GetIniFileName());
    if (nGammaCorrection < 0 || nGammaCorrection > 5) {
        nGammaCorrection = 0;
    }

    cVideo.m_pVidModes[0]->m_nGammaCorrection = nGammaCorrection;

    BYTE nBrightnessCorrection = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BRIGHTNESS_CORRECTION_KEY,
        0,
        GetIniFileName());
    if (nBrightnessCorrection < 0 || nBrightnessCorrection > 40) {
        nBrightnessCorrection = 0;
    }

    cVideo.m_pVidModes[0]->m_nBrightnessCorrection = nBrightnessCorrection;

    cVideo.field_13A = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BACKWARDS_COMPATIBLE_3D_KEY,
        0,
        GetIniFileName());

    CGameAnimationType::MIRROR_BAM = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SPRITE_MIRROR_KEY,
        CGameAnimationType::MIRROR_BAM,
        GetIniFileName());

    pOptions->m_nVolumeMovie = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MOVIE_KEY,
        85,
        GetIniFileName());
    if (pOptions->m_nVolumeMovie > 100) {
        pOptions->m_nVolumeMovie = 85;
    }

    pOptions->m_nVolumeMusic = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MUSIC_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeMusic > 100) {
        pOptions->m_nVolumeMusic = 100;
    }

    pOptions->m_nVolumeVoices = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_VOICES_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeVoices > 100) {
        pOptions->m_nVolumeVoices = 100;
    }

    pOptions->m_nVolumeAmbients = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_AMBIENTS_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeAmbients > 100) {
        pOptions->m_nVolumeAmbients = 100;
    }

    pOptions->m_nVolumeSFX = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_SFX_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeSFX > 100) {
        pOptions->m_nVolumeSFX = 100;
    }

    m_pObjectGame->ApplyVolumeSliders(TRUE);

    pOptions->m_nShadedSelectionBox = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SHADED_SELECTION_BOX_KEY,
        0,
        GetIniFileName());
    if (pOptions->m_nShadedSelectionBox != 0 && pOptions->m_nShadedSelectionBox != 1) {
        pOptions->m_nShadedSelectionBox = 0;
    }

    pOptions->m_bDisplayMovieSubtitles = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_MOVIE_SUBTITLES_KEY,
        0,
        GetIniFileName());

    g_pChitin->field_1C4C = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SINGLE_MEDIA_KEY,
        0,
        GetIniFileName());
}

// 0x424FF0
void CBaldurChitin::PreLoadFonts()
{
    field_4A34.SetResRef(CResRef("NORMAL"), 0, 1);
    field_4A34.SetColor(0xFFFFFF, 0, 0);
    field_4A34.RegisterFont();
}

// 0x425040
void CBaldurChitin::SaveOptions()
{
    CGameOptions* pOptions = m_pObjectGame->GetOptions();
    CString sString;

    if (m_bFullscreen) {
        SaveBitsPerPixel(cVideo.m_nBpp);
    } else {
        RECT rect;
        GetWindowRect(GetWnd()->GetSafeHwnd(), &rect);

        m_ptScreen.x = rect.left;
        m_ptScreen.y = rect.top;

        sString.Format("%d", m_ptScreen.x);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            SCREEN_POSITION_X_KEY,
            sString,
            GetIniFileName());

        sString.Format("%d", m_ptScreen.y);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            SCREEN_POSITION_Y_KEY,
            sString,
            GetIniFileName());
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FONT_NAME_KEY,
        m_sFontName,
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DOUBLE_BYTE_CHARACTER_SUPPORT_KEY,
        field_1A0 ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        IS_3D_ACCELERATED,
        cVideo.m_bIs3dAccelerated ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SIXTEEN_BIT_TEXTURES_KEY,
        field_2F4 ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", CVideo::FPS);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_FREQUENCY_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CVideo::SCREENWIDTH);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        RESOLUTION_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CChitin::TIMER_UPDATES_PER_SECOND);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        MAXIMUM_FRAME_RATE_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CSearchRequest::MAXNODES);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        PATH_SEARCH_NODES_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nTooltips);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        TOOLTIPS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_bTranslucentShadows);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        TRANSLUCENT_SHADOWS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CGameAnimationType::MIRROR_BAM);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SPRITE_MIRROR_KEY,
        sString,
        GetIniFileName());

    if (CVidMode::bInitialized) {
        sString.Format("%d", GetCurrentVideoMode()->m_nGammaCorrection);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            GAMMA_CORRECTION_KEY,
            sString,
            GetIniFileName());

        sString.Format("%d", GetCurrentVideoMode()->m_nBrightnessCorrection);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BRIGHTNESS_CORRECTION_KEY,
            sString,
            GetIniFileName());
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        BACKWARDS_COMPATIBLE_3D_KEY,
        cVideo.field_13A ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeMovie);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MOVIE_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeMusic);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MUSIC_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeVoices);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_VOICES_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeAmbients);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_AMBIENTS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeSFX);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_SFX_KEY,
        sString,
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        cVideo.cVidBlitter.m_bSoftSrcKeyBltFast ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        cVideo.cVidBlitter.m_bSoftBltFast ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftSrcKeyBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftMirrorBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_MOVIE_SUBTITLES_KEY,
        pOptions->m_bDisplayMovieSubtitles ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", pOptions->m_nShadedSelectionBox);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SHADED_SELECTION_BOX_KEY,
        sString,
        GetIniFileName());
}

// 0x425680
void CBaldurChitin::SaveBitsPerPixel(USHORT nBpp)
{
    switch (nBpp) {
    case 16:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "16",
            GetIniFileName());
        break;
    case 24:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "24",
            GetIniFileName());
        break;
    case 32:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "32",
            GetIniFileName());
        break;
    }
}

// 0x425710
void CBaldurChitin::SetProgressBar(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
    if (bEnabled == TRUE) {
        g_pChitin->cProgressBar.m_bProgressBarActivated = TRUE;
        g_pChitin->cProgressBar.m_bTravelActive = bTravel;
    }

    m_cCachingStatus.Update(bEnabled,
        nProgressBarCaption,
        nBytesCopied,
        nTotalBytes,
        bTravel,
        nParchmentCaption,
        bWaiting,
        nWaitingReason,
        bDisplayMinibars,
        bTimeoutCounter,
        nSecondsToTimeout);

    if (bEnabled == FALSE) {
        g_pChitin->cProgressBar.Initialize();
        g_pChitin->cProgressBar.m_bProgressBarActivated = FALSE;
        g_pChitin->cProgressBar.m_bTravelActive = bTravel;
    }
}

// 0x4257B0
void CBaldurChitin::BroadcastMultiplayerProgressBarInfo()
{
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        g_pBaldurChitin->GetBaldurMessage()->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
            g_pChitin->cProgressBar.m_nActionTarget,
            g_pChitin->cProgressBar.m_bWaiting,
            g_pChitin->cProgressBar.m_nWaitingReason,
            g_pChitin->cProgressBar.m_bTimeoutVisible,
            g_pChitin->cProgressBar.m_nSecondsToTimeout);
    }
}

// 0x425800
void CBaldurChitin::SetCDSwitchStatus(BOOLEAN a1, BOOLEAN a2, BYTE a3, const CString& a4, BOOLEAN a5, BOOLEAN a6, BOOLEAN a7)
{
    m_cSwitchingCDStatus.Update(a1, a2, a3, a4, a5, a6, a7);
}

// 0x425840
void CBaldurChitin::OnMultiplayerSessionClose()
{
    g_pChitin->cGameSpy.sub_4D1EC0(1);
    g_pChitin->cGameSpy.sub_4D2310();

    BOOL bEnabled = GetPrivateProfileIntA("RogerWilco",
        "Enabled",
        0,
        g_pBaldurChitin->GetIniFileName());

    if (bEnabled) {
        // NOTE: Unused.
        INT nServiceProviderType;
        g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.GetServiceProvider(), nServiceProviderType);
    }

    m_cBaldurMessage.m_bPlayerShutdown = TRUE;
}

// 0x4258C0
void CBaldurChitin::OnMultiplayerSessionToClose()
{
    m_cBaldurMessage.m_bMultiplayerSessionShutdown = TRUE;
}

// 0x4258D0
void CBaldurChitin::OnMultiplayerSessionOpen(CString& sJoinedGame, CString& sDroppedGame, CString& sLeftGame)
{
    STR_RES strRes;
    INT nServiceProviderType;

    // FIXME: Why use globals?
    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.m_nServiceProvider, nServiceProviderType);
        if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
            BOOL bGameSpyEnabled = GetPrivateProfileIntA("GameSpy",
                "Enabled",
                0,
                g_pBaldurChitin->GetIniFileName());
            if (bGameSpyEnabled) {
                g_pBaldurChitin->cGameSpy.sub_4D2060();
            }
        }
    }

    BOOL bRogerWilcoEnabled = GetPrivateProfileIntA("RogerWilco",
        "Enabled",
        0,
        g_pBaldurChitin->GetIniFileName());
    if (bRogerWilcoEnabled == TRUE) {
        g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.m_nServiceProvider, nServiceProviderType);
        if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP
            && g_pChitin->cNetwork.GetSessionHosting() != TRUE) {
            CString v1;
            g_pChitin->cNetwork.sub_7A73D0(v1);
            if (v1 != "") {
                // NOTE: Unused.
            }
        }
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(10236, strRes);
    sJoinedGame = strRes.szText;

    g_pBaldurChitin->m_cTlkTable.Fetch(10245, strRes);
    sDroppedGame = strRes.szText;

    g_pBaldurChitin->m_cTlkTable.Fetch(10246, strRes);
    sLeftGame = strRes.szText;

    m_cBaldurMessage.m_cChatBuffer.ClearMessages();

    if (m_pEngineWorld != NULL) {
        m_pEngineWorld->ClearChatMessages();
    }

    if (m_pEngineMultiPlayer != NULL) {
        m_pEngineMultiPlayer->ClearChatMessages();
    }

    if (m_pEngineWorldMap != NULL) {
        m_pEngineWorldMap->ClearChatMessages();
    }
}

// 0x422C60
BOOL CBaldurChitin::FontRectOutline()
{
    return m_bFontRectOutline;
}

// 0x422C90
DWORD CBaldurChitin::GetCloseConfirmationFlags()
{
    return m_dwCloseConfirmationFlags;
}

// 0x422CA0
void CBaldurChitin::GetCloseConfirmationStr(CString& sString)
{
    sString = CBaldurEngine::FetchString(m_dwCloseConfirmationStrId);
}

// 0x422C60
UINT CBaldurChitin::GetSavedBitsPerPixel()
{
    return GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BITS_PER_PIXEL_KEY,
        CVideo::word_85DE2C,
        GetIniFileName());
}

// 0x425BD0
void CBaldurChitin::ClearChatMessages()
{
    m_cBaldurMessage.m_cChatBuffer.ClearMessages();

    if (m_pEngineWorld != NULL) {
        m_pEngineWorld->ClearChatMessages();
    }

    if (m_pEngineMultiPlayer != NULL) {
        m_pEngineMultiPlayer->ClearChatMessages();
    }

    if (m_pEngineWorldMap != NULL) {
        m_pEngineWorldMap->ClearChatMessages();
    }
}

// 0x425C10
void CBaldurChitin::OnMultiplayerPlayerJoin(PLAYER_ID playerID, const CString& sPlayerName)
{
    // TODO: Incomplete.
}

// 0x425CA0
CBaldurMessage* CBaldurChitin::GetBaldurMessage()
{
    return &m_cBaldurMessage;
}

// 0x425CB0
void CBaldurChitin::OnMultiplayerPlayerVisible(PLAYER_ID playerID)
{
    if (g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting()) {
        if (m_pObjectGame != NULL) {
            INT nSlot = g_pChitin->cNetwork.FindPlayerLocationByID(playerID, FALSE);
            if (nSlot >= 0 && nSlot < CMultiplayerSettings::MAX_PLAYERS) {
                m_pObjectGame->m_multiplayerSettings.ResetPermissionsForPlayer(nSlot, FALSE);
            }
        }
    }
}

// 0x425D10
void CBaldurChitin::OnMultiplayerPlayerLeave(PLAYER_ID playerID, const CString& sPlayerName)
{
    INT nLocation;
    INT nHostLocation;

    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            nHostLocation = g_pChitin->cNetwork.m_nLocalPlayer;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
            // __LINE__: 2725
            UTIL_ASSERT_MSG(nHostLocation != -1,
                "CBaldurChitin::OnMultiplayerLeave: Can't find host player slot!\n");

            nLocation = g_pChitin->cNetwork.FindPlayerLocationByID(playerID, FALSE);
            if (nLocation != -1) {
                CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();
                pSettings->ResetPermissionsForPlayer(nLocation, FALSE);
                pSettings->OnDropPlayer(playerID);
                m_cBaldurMessage.SendFullSettingsToClients(CString(""));
                m_cBaldurMessage.AddDroppedPlayer(playerID);
            }
        } else {
            if (g_pChitin->cNetwork.FindPlayerLocationByID(playerID, FALSE) != -1) {
                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->OnDropPlayer(playerID);
            }
        }
    }
}

// 0x425E60
BOOL CBaldurChitin::MessageCallback(BYTE* pData, DWORD dwSize)
{
    return GetMessageHandler()->ImportantMessage(pData, dwSize);
}

// 0x425FB0
void CBaldurChitin::SynchronousUpdate()
{
    CChitin::SynchronousUpdate();
}

// 0x425FC0
void CBaldurChitin::OnMixerInitialize()
{
    CResRef musicResRef;
    musicResRef = "music";

    C2DArray tMusic;
    CString sFileName;

    tMusic.Load(musicResRef);

    INT nNumSongs = 0;
    for (INT nRow = 0; nRow < tMusic.GetHeight(); nRow++) {
        if (tMusic.GetAt(CPoint(0, nRow)) == "*") {
            break;
        }

        nNumSongs++;
    }

    // NOTE: Original code is slightly different.
    for (INT nSong = 0; nSong < nNumSongs && nSong < 100; nSong++) {
        sFileName = tMusic.GetAt(CPoint(0, nSong));
        if (sFileName == "*") {
            sFileName = "";
        }

        SONGS[nSong] = new CHAR[sFileName.GetLength() + 1];
        if (SONGS[nSong] == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
            // __LINE__: 2946
            UTIL_ASSERT_MSG(FALSE, "Problem loading songs from music.2da into the songs list!");
        }

        memcpy(SONGS[nSong], sFileName.GetBuffer(), sFileName.GetLength());
        sFileName.ReleaseBuffer();

        SONGS[nSong][sFileName.GetLength()] = '\0';
    }

    CString sMusicPath("");
    if (lAliases.ResolveFileName(CString("hd0:\\music"), sMusicPath) == TRUE) {
        DWORD dwAttrs = GetFileAttributesA(sMusicPath);
        if (dwAttrs != -1 && (dwAttrs & FILE_ATTRIBUTE_DIRECTORY) != 0) {
            cSoundMixer.SetMusicPath(sMusicPath);
        }
    }

    cSoundMixer.SetMusicSongs(nNumSongs, SONGS);

    C2DArray tChannels;
    tChannels.Load(CResRef("SNDCHANN"));

    cSoundMixer.SetPanRange(1024);

    for (UINT nChannel = 0; nChannel < 21; nChannel++) {
        CSoundChannel* pChannel = static_cast<CSoundChannel*>(cSoundMixer.m_aChannels.GetAt(nChannel));
        if ((nChannel < 6 || nChannel >= 13) && nChannel != 0) {
            pChannel->SetType(0);
        } else {
            pChannel->SetType(3);
        }

        pChannel->SetVolumeInit(tChannels.GetAtLong(CPoint(0, nChannel)));
    }

    if (g_pBaldurChitin->pActiveEngine == g_pBaldurChitin->m_pEngineChapter) {
        g_pBaldurChitin->m_pEngineChapter->OnMixerInitialize();
    }

    // NOTE: Original code is slightly different.
    for (INT nSong = 0; nSong < 100; nSong++) {
        delete SONGS[nSong];
    }
}

// 0x426600
CStringList* CBaldurChitin::GetPlayedMovies()
{
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind;
    char buffer[4096];

    CStringList* pStringList = new CStringList();

    // NOTE: Original code is slightly different, but does the same thing.
    CString sMovieName;
    CString sResolvedFileName;
    CString sFileName;

    GetPrivateProfileStringA("Movies", NULL, "", buffer, sizeof(buffer), GetIniFileName());

    char* pch = buffer;
    while (*pch != '\0') {
        sMovieName = pch;
        BOOL bFound = FALSE;

        sFileName = "hd0:\\override\\";
        sFileName += sMovieName;
        sFileName += ".mve";

        if (g_pChitin->lAliases.ResolveFileName(sFileName, sResolvedFileName) == TRUE) {
            hFind = FindFirstFileA(sResolvedFileName, &findFileData);
            if (hFind != INVALID_HANDLE_VALUE) {
                bFound = TRUE;
                FindClose(hFind);
            }
        }

        if (!bFound) {
            sFileName = "hd0:\\data\\";
            sFileName += sMovieName;
            sFileName += ".mve";

            if (g_pChitin->lAliases.ResolveFileName(sFileName, sResolvedFileName) == TRUE) {
                hFind = FindFirstFileA(sResolvedFileName, &findFileData);
                if (hFind != INVALID_HANDLE_VALUE) {
                    bFound = TRUE;
                    FindClose(hFind);
                }
            }

            if (!bFound) {
                sFileName = "cd2:\\data\\";
                sFileName += sMovieName;
                sFileName += ".mve";

                if (g_pChitin->lAliases.ResolveFileName(sFileName, sResolvedFileName) == TRUE) {
                    hFind = FindFirstFileA(sResolvedFileName, &findFileData);
                    if (hFind != INVALID_HANDLE_VALUE) {
                        bFound = TRUE;
                        FindClose(hFind);
                    }
                }
            }
        }

        if (GetPrivateProfileIntA("Movies", sMovieName, 0, GetIniFileName()) > 0 && bFound) {
            pStringList->AddTail(sMovieName);
        }

        pch += strlen(pch) + 1;
    }

    return pStringList;
}

// 0x4268F0
void CBaldurChitin::AddPlayedMovie(const CResRef& cResMovie)
{
    CString sRes;
    cResMovie.CopyToString(sRes);
    WritePrivateProfileStringA("Movies", sRes, "1", GetIniFileName());
}

// 0x426970
void CBaldurChitin::GetGameSpyCode(CString& sGameSpyCode)
{
    sGameSpyCode = "";

    for (int k = 0; k < 6; k++) {
        sGameSpyCode += static_cast<char>(CBaldurChitin::BALDUR_GAMESPY_CODE1[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE2[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE3[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE4[k]);
    }
}

// 0x4269C0
void CBaldurChitin::GetPanicCDStrings(CString& sMediaRemoved, CString& sPlaceCD, CString& sInDrive)
{
    sMediaRemoved = CBaldurEngine::FetchString(20714);
    sPlaceCD = CBaldurEngine::FetchString(20715);
    sInDrive = CBaldurEngine::FetchString(20716);
}

// 0x426B20
BOOLEAN CBaldurChitin::DetectBaldurCD()
{
    // NOTE: This function simply returns 1, but it's asm looks like a hack
    // likely performed by GOG to bypass CD check.
    return TRUE;
}

// 0x426DC0
CString CBaldurChitin::GetFirstCDRomDrive()
{
    CString sDrive;

    DWORD nDrives = GetLogicalDrives();

    for (BYTE nDrive = 0; nDrive < 32; nDrive++) {
        if (field_49B1) {
            sDrive = "";
            break;
        }

        if (((1 << nDrive) & nDrives) != 0) {
            sDrive.Format("%c:\\", nDrive + 'A');
            if (GetDriveTypeA(sDrive.GetBuffer(sDrive.GetLength())) == DRIVE_CDROM) {
                break;
            }
        }
    }

    return sDrive;
}

// 0x426EC0
WORD CBaldurChitin::GetMultiplayerDirectPlayPort()
{
    return GetPrivateProfileIntA("Multiplayer", "Port", 0, GetIniFileName());
}

// 0x426EE0
WORD CBaldurChitin::GetMultiplayerGameSpyPort()
{
    if (GetPrivateProfileIntA("GameSpy", "Enabled", 0, GetIniFileName()) != 1) {
        return 0;
    }

    return GetPrivateProfileIntA("GameSpy", "Port", 0, GetIniFileName());
}

// 0x4D26B0
CInfCursor* CBaldurChitin::GetObjectCursor()
{
    return m_pObjectCursor;
}

// 0x40CB10
CInfGame* CBaldurChitin::GetObjectGame()
{
    return m_pObjectGame;
}

// 0x4286B0
void CBaldurChitin::AddMusicPosition(CResRef cResRef, INT nSong)
{
    if (m_pMusicPositions != NULL
        && cResRef != "XXXXXXXX"
        && nSong > 0
        && g_pBaldurChitin->cSoundMixer.GetSongPlaying() == nSong) {
        INT nSection = g_pBaldurChitin->cSoundMixer.GetSectionPlaying();
        if (nSection >= 0) {
            INT nIndex = 0;
            while (nIndex < MAX_MUSIC_POSITIONS - 1) {
                if (m_pMusicPositions[nIndex].m_areaResRef == cResRef) {
                    break;
                }
                nIndex++;
            }

            while (nIndex > 0) {
                m_pMusicPositions[nIndex] = m_pMusicPositions[nIndex - 1];
                nIndex--;
            }

            m_pMusicPositions[0].m_areaResRef = cResRef;
            m_pMusicPositions[0].m_nSong = nSong;
            m_pMusicPositions[0].m_nSection = nSection;
            m_pMusicPositions[0].m_nPosition = g_pBaldurChitin->cSoundMixer.GetMusicPosition();
        }
    }
}

// 0x428820
BOOL CBaldurChitin::GetMusicPosition(CResRef cResRef, INT nSong, INT& nSection, INT& nPosition)
{
    if (m_pMusicPositions == NULL) {
        return FALSE;
    }

    INT nIndex = 0;
    while (nIndex < MAX_MUSIC_POSITIONS) {
        if (m_pMusicPositions[nIndex].m_nSong != -1
            && m_pMusicPositions[nIndex].m_areaResRef == cResRef) {
            if (m_pMusicPositions[nIndex].m_nSong == nSong) {
                nSection = m_pMusicPositions[nIndex].m_nSection;
                nPosition = m_pMusicPositions[nIndex].m_nPosition;
                return TRUE;
            }

            m_pMusicPositions[nIndex].m_nSong = 0;
            m_pMusicPositions[nIndex].m_nSection = -1;
            break;
        }
        nIndex++;
    }

    nSection = 0;
    nPosition = -1;
    return FALSE;
}

// 0x4288E0
BOOL CBaldurChitin::RemoveMusicPosition(CResRef cResRef, INT nSong)
{
    if (m_pMusicPositions == NULL) {
        return FALSE;
    }

    INT nIndex = 0;
    while (nIndex < MAX_MUSIC_POSITIONS) {
        if (m_pMusicPositions[nIndex].m_areaResRef == cResRef && m_pMusicPositions[nIndex].m_nSong == nSong) {
            while (nIndex < MAX_MUSIC_POSITIONS - 1) {
                m_pMusicPositions[nIndex] = m_pMusicPositions[nIndex + 1];
                nIndex++;
            }

            m_pMusicPositions[nIndex].m_areaResRef = "XXXXXXXX";
            m_pMusicPositions[nIndex].m_nSong = -1;
            m_pMusicPositions[nIndex].m_nSection = 0;
            m_pMusicPositions[nIndex].m_nPosition = 0;

            return TRUE;
        }
        nIndex++;
    }

    return FALSE;
}

// 0x438550
CScreenWorld* CBaldurChitin::GetScreenWorld()
{
    return m_pEngineWorld;
}

// 0x4537C0
CBaldurEngine* CBaldurChitin::GetActiveEngine()
{
    return static_cast<CBaldurEngine*>(pActiveEngine);
}

// 0x4537D0
CTlkTable& CBaldurChitin::GetTlkTable()
{
    return m_cTlkTable;
}

// 0x4537E0
CMessageHandler* CBaldurChitin::GetMessageHandler()
{
    return &m_cMessageHandler;
}

// 0x58FEF0
BOOL CBaldurChitin::GetDoubleSize()
{
    return field_4A2C;
}

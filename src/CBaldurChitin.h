#ifndef CBALDURCHITIN_H_
#define CBALDURCHITIN_H_

#include <afxwin.h>

#include "CBaldurMessage.h"
#include "CCacheStatus.h"
#include "CChitin.h"
#include "CMessageHandler.h"
#include "CSwitchCDStatus.h"
#include "CTlkTable.h"
#include "CVidFont.h"

extern unsigned char byte_8BA28C;

class CBaldurProjector;
class CDungeonMaster;
class CInfCursor;
class CInfGame;
class CScreenChapter;
class CScreenCharacter;
class CScreenConnection;
class CScreenCreateChar;
class CScreenInventory;
class CScreenJournal;
class CScreenKeymaps;
class CScreenLoad;
class CScreenMap;
class CScreenMovies;
class CScreenMultiPlayer;
class CScreenOptions;
class CScreenSave;
class CScreenSinglePlayer;
class CScreenSpellbook;
class CScreenStart;
class CScreenStore;
class CScreenWorld;
class CScreenWorldMap;

class CBaldurChitin : public CChitin {
public:
    // TODO: Some kind of layout info.
    struct S49B4 {
        /* 0000 */ int field_0;
        /* 0004 */ short field_4;
        /* 0006 */ short field_6;
        /* 0008 */ short field_8;
        /* 000A */ short field_A;
        /* 000C */ short field_C;
        /* 0010 */ char field_10[8];
    };

    // TODO: Something sound-related.
    struct S4F40 {
        CResRef cResRef;
        int field_8;
        int field_C;
        int field_10;
    };

    static const USHORT DEFAULT_SCREEN_WIDTH;
    static const USHORT DEFAULT_SCREEN_HEIGHT;

    static short word_8BA320;
    static CString string_8C8CA0;
    static const CString BALDUR_GAMESPY_GAMENAME;
    static const CString BALDUR_GAMESPY_CODE1;
    static const CString BALDUR_GAMESPY_CODE2;
    static const CString BALDUR_GAMESPY_CODE3;
    static const CString BALDUR_GAMESPY_CODE4;
    static CString OVERRIDE_DIR_NAME;
    static const CString PRINTSCREEN_FILE_NAME;
    static const CString ICON_RES_ID;
    static RECT stru_8E7538;
    static RECT stru_8E7548;
    static RECT stru_8E7958;
    static RECT stru_8E7988;
    static RECT stru_8E79A8;
    static RECT stru_8E79B8;
    static RECT stru_8E79C8;
    static RECT stru_8E79E0;
    static RECT stru_8E79F8;
    static RECT stru_8E7A10;
    static BOOL SPRITE_MIRROR;

    CBaldurChitin();
    ~CBaldurChitin();
    void Init(HINSTANCE hInstance);
    void SaveOptions();
    void SetSoftSrcKeyBltFast(BOOLEAN a2, BOOLEAN a3);
    void SetSoftBltFast(BOOLEAN a2, BOOLEAN a3);
    void SetSoftSrcKeyBlt(BOOLEAN a2, BOOLEAN a3);
    void SetSoftBlt(BOOLEAN a2, BOOLEAN a3);
    void SetSoftMirrorBlt(BOOLEAN a2, BOOLEAN a3);
    void ClearChatMessages();
    CBaldurMessage* GetBaldurMessage();
    void AddPlayedMovie(const CResRef& cResMovie);

    /* 0000 */ void SynchronousUpdate();
    /* 0008 */ DWORD GetIDSInvalidVideoMode();
    /* 000C */ DWORD GetIDSOpenGLDll();
    /* 0010 */ DWORD GetIDSExclusiveMode();
    /* 0014 */ DWORD GetIDSChoosePixelFormat();
    /* 0018 */ DWORD GetIDSSetPixelFormat();
    /* 001C */ DWORD GetIDSSetGameResolution();
    /* 0020 */ DWORD GetIDSSetGameBitDepth();
    /* 0024 */ DWORD GetIDSBadDeskTopBitDepth();
    /* 0028 */ DWORD GetIDSWindowsFonts();
    /* 002C */ void MessageThreadMain(void* userInfo);
    /* 0030 */ void RSThreadMain(void* userInfo);
    /* 0034 */ void MainAIThread(void* userInfo);
    /* 0038 */ void MusicThreadMain(void* userInfo);
    /* 0040 */ const CString& GetIconRes();
    /* 0044 */ virtual void GetScreenShotFilePrefix(CString& szGameFileName);
    /* 0058 */ BOOL InitializeServices(HWND hWnd);
    /* 009C */ void ShutDown(int nLineNumber, const char* szFileName, const char* text);
    /* 00A0 */ const char* GetConfigFileName();
    /* 00A4 */ const char* GetKeyFileName();
    /* 00A8 */ const char* GetLogFileName();
    /* 00A8 */ const char* GetErrorFileName();
    /* 00B0 */ void SaveBitsPerPixel(USHORT nBpp);
    /* 00B4 */ UINT GetSavedBitsPerPixel();
    /* 00B8 */ BYTE GetNumberSoundChannels();
    /* 00C0 */ void LoadOptions();
    /* 00D0 */ WORD GetMultiplayerGameSpyPort();
    /* 00D4 */ WORD GetMultiplayerDirectPlayPort();
    /* 00EC */ void GetGameSpyGameName(CString& sGameSpyName);
    /* 00F0 */ void GetGameSpyCode(CString& sGameSpyCode);

    /* 1C50 */ CInfCursor* m_pObjectCursor;
    /* 1C54 */ CInfGame* m_pObjectGame;
    /* 1C58 */ CDungeonMaster* m_pEngineDM;
    /* 1C5C */ CBaldurProjector* m_pEngineProjector;
    /* 1C60 */ CScreenCharacter* m_pEngineCharacter;
    /* 1C64 */ CScreenCreateChar* m_pEngineCreateChar;
    /* 1C68 */ CScreenInventory* m_pEngineInventory;
    /* 1C6C */ CScreenJournal* m_pEngineJournal;
    /* 1C70 */ CScreenLoad* m_pEngineLoad;
    /* 1C74 */ CScreenMap* m_pEngineMap;
    /* 1C78 */ CScreenOptions* m_pEngineOptions;
    /* 1C7C */ CScreenSave* m_pEngineSave;
    /* 1C80 */ CScreenSpellbook* m_pEngineSpellbook;
    /* 1C84 */ CScreenStart* m_pEngineStart;
    /* 1C88 */ CScreenWorld* m_pEngineWorld;
    /* 1C8C */ CScreenStore* m_pEngineStore;
    /* 1C90 */ CScreenMultiPlayer* m_pEngineMultiPlayer;
    /* 1C94 */ CScreenSinglePlayer* m_pEngineSinglePlayer;
    /* 1C98 */ CScreenConnection* m_pEngineConnection;
    /* 1C9C */ CScreenWorldMap* m_pEngineWorldMap;
    /* 1CA0 */ CScreenChapter* m_pEngineChapter;
    /* 1CA4 */ CScreenMovies* m_pEngineMovies;
    /* 1CA8 */ CScreenKeymaps* m_pEngineKeymaps;
    /* 1CAC */ CTlkTable m_cTlkTable;
    /* 1D52 */ CCacheStatus m_cCachingStatus;
    /* 3970 */ CSwitchCDStatus m_cSwitchingCDStatus; // #guess
    /* 4888 */ CBaldurMessage m_cBaldurMessage;
    /* 4980 */ CMessageHandler m_cMessageHandler;
    /* 499E */ int field_499E;
    /* 49A2 */ int field_49A2;
    /* 49A6 */ int field_49A6;
    /* 49AA */ unsigned char field_49AA;
    /* 49AB */ unsigned char field_49AB;
    /* 49B0 */ unsigned char field_49B0;
    /* 49B1 */ unsigned char field_49B1;
    /* 49AC */ CString field_49AC;
    /* 49B2 */ unsigned char field_49B2;
    /* 49B4 */ S49B4 field_49B4[4];
    /* 4A24 */ int field_4A24;
    /* 4A28 */ int field_4A28;
    /* 4A2C */ int field_4A2C;
    /* 4A34 */ CVidFont field_4A34;
    /* 4F38 */ int field_4F38;
    /* 4F3C */ int field_4F3C;
    /* 4F40 */ S4F40* field_4F40;
};

extern CBaldurChitin* g_pBaldurChitin;

#endif /* CBALDURCHITIN_H_ */

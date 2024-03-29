#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

#include "CGameDialog.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlScrollBar.h"
#include "CVidCell.h"
#include "CVidFont.h"
#include "CWeather.h"

#define CSCREENWORLD_VIRTUAL_KEYS 92

class CAIObjectType;
class CDeathSound;
class CGameSprite;
class CUIControlTextDisplay;

class CScreenWorld : public CBaldurEngine {
public:
    static const LONG BORED_TIME;
    static int dword_8F85BC;

    CScreenWorld();
    /* 0004 */ ~CScreenWorld() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0038 */ BOOL GetCtrlKey() override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0048 */ BOOL CheckSystemKeyMenu() override;
    /* 004C */ void SetSystemKeyMenu(BOOL bValue) override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 005C */ BOOL GetMenuKey() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 008C */ void OnRButtonDblClk(CPoint pt) override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00D0 */ int GetSelectedCharacter() override;
    /* 00E8 */ void UpdateContainerStatus(LONG nContainerId, SHORT nSlotNum) override;
    /* 00F0 */ void OnRestButtonClick() override;
    /* 0104 */ void CancelEngine() override;
    /* 010C */ void UpdatePartyGoldStatus() override;
    /* 0110 */ void GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture) override;
    /* 0114 */ void SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture) override;

    void StartScroll(CPoint dest, SHORT speed);
    void AsynchronousUpdate(BOOL bActiveEngine);
    BOOL TogglePauseGame(char a2, char a3, int a4);
    BOOLEAN ReadyMovie(const CResRef& res, BOOLEAN bForcedFromServer);
    BOOLEAN ReadyEndCredits(BOOLEAN bForcedFromServer);
    void EndDialog(BOOLEAN bForceExecution, BOOLEAN fullEnd);
    void MoveToArea(CString areaName);
    void SaveScreen();
    void SetCurrentXP(DWORD dwCurrentXP);
    void AddGold(DWORD dwGold);
    void StopContainer();
    void CancelPopup();
    void StartCommand();
    void StopCommand();
    void StartStore(const CAIObjectType& cAIProprietor, const CAIObjectType& cAICustomer, CResRef cResStore, BOOLEAN bInitiate);
    void StopStore();
    CRect GetNewViewSize();
    void HandleAmbiance();
    void StartDeathReaction(const CString& sName);
    void HandleDeathReaction();
    POSITION DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, BOOLEAN bMoveToTop);
    POSITION DisplayText(const CString& sName, const CString& sText, LONG lMarker, BOOLEAN bMoveToTop);
    void RemoveText(POSITION pos);
    void SetItemMarker(POSITION pos, LONG lMarker);
    void ClearChatMessages();
    void HideInterface();
    void UnhideInterface();
    void SetNewViewSize(CRect newViewSize, BOOL bForceViewSize);
    void StartDeath();
    void StopDeath();
    DWORD GetPanel_21_7();
    DWORD GetPanel_22_0();
    DWORD GetPanel_21_0();
    DWORD GetPanel_19_0();
    void SetPendingChapterChange(BYTE nChapter, BYTE* szChapterResRef);
    void SetPendingMovie(BYTE* szMovieResRef);
    void StartSaveGameMultiplayerHost();
    void StartMovieMultiplayerHost(BYTE* cMovieResRef);
    void SetPendingMapWorld(PLAYER_ID idController, SHORT facingDirection);
    void StartMapWorldMultiplayerHost(PLAYER_ID idController, SHORT facingDirection);
    void SetPendingReformParty();
    void StartReformPartyMultiplayerHost();
    void SetPendingRest(INT nHP, BOOLEAN bRenting, BOOLEAN bMovie);
    void StartRestMultiplayerHost(INT nHP, BOOLEAN bRenting, BOOLEAN bMovie);
    void CheckEndOfHardPause();
    void sub_693710();
    void CheckEndOfMultiplayerSynch();
    void DeleteAreaMultiplayer();
    void DeleteArea(CGameArea* pArea);
    void CopyChatEditBox(CUIPanel* pFrom, CUIPanel* pTo);
    void LeaveAreaLuaPanic(CPoint ptLocation, SHORT nDirection, CString sAreaName, CString sParchment);
    void SetDialogTokens(CGameSprite* pCharacter);
    void sub_695570(BOOL bActive, BOOL bInvalidate);
    void sub_695650(BOOL bEnable);
    void EnableKeyRepeat();
    void DisableKeyRepeat();
    void SetLeaveAreaLuaPanicData(CPoint ptValue, SHORT nValue, CString sValue1, CString sValue2);
    BOOL sub_453780();
    void sub_453790(BOOL bEnabled);
    CGameDialogSprite* GetInternalLoadedDialog();

    void CompressTime(DWORD deltaTime) { m_deltaTime = deltaTime; }

    void CheckPanelInputMode(DWORD dwPanelId, DWORD dwinputModeMask);
    INT GetNumContainerRows(LONG nContainer);
    INT GetNumGroupRows();

    /* 0106 */ CRITICAL_SECTION field_106;
    /* 011E */ int field_11E;
    /* 0122 */ LONG m_boredCount;
    /* 0126 */ BOOL m_bored;
    /* 012A */ BOOL m_playerShutdown;
    /* 012E */ BOOL m_bShiftKeyDown;
    /* 0132 */ BOOL m_bMenuKeyDown;
    /* 0136 */ BOOL m_bCtrlKeyDown;
    /* 013A */ BOOL m_bCapsLockKeyOn;
    /* 013E */ BOOLEAN m_bPaused;
    /* 0142 */ BOOL field_142;
    /* 0146 */ BOOL m_bHardPaused;
    /* 014A */ int field_14A;
    /* 014E */ int field_14E;
    /* 0152 */ BOOL m_bPausedBeforePickParty;
    /* 0156 */ int field_156;
    /* 015A */ int field_15A;
    /* 015C */ unsigned char field_15C;
    /* 015D */ unsigned char field_15D;
    /* 015E */ short field_15E;
    /* 0160 */ unsigned char field_160;
    /* 0162 */ short field_162;
    /* 0164 */ int field_164;
    /* 0168 */ CVidFont field_168;
    /* 0668 */ CVidFont field_668;
    /* 0B68 */ CKeyInfo m_pVirtualKeys[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0E48 */ BYTE m_pVirtualKeysFlags[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0EA4 */ int field_EA4;
    /* 0EA8 */ CUIControlTextDisplay* m_pActiveDialogDisplay;
    /* 0EAC */ CUIControlTextDisplay* m_pActiveChatDisplay;
    /* 0EB0 */ CGameDialogSprite m_internalLoadedDialog;
    /* 0F22 */ CRect m_newViewSize;
    /* 0F32 */ BOOL m_bForceViewSize;
    /* 0F36 */ BYTE m_waitingOnResize;
    /* 0F37 */ unsigned char field_F37;
    /* 0F3C */ INT m_nTopContainerRow;
    /* 0F40 */ INT m_nTopGroupRow;
    /* 0F44 */ unsigned char field_F44;
    /* 0F46 */ CWeather m_weather;
    /* 10AE */ LONG m_scrollLockId;
    /* 10B2 */ short field_10B2;
    /* 10B4 */ int field_10B4;
    /* 10B8 */ LONG m_interactionIndex;
    /* 10BC */ LONG m_interactionTarget;
    /* 10C0 */ CString field_10C0;
    /* 10C4 */ int field_10C4;
    /* 10C8 */ int field_10C8;
    /* 10CC */ int field_10CC;
    /* 10D0 */ LONG field_10D0;
    /* 10D4 */ BOOLEAN m_bSetNightOnActivate;
    /* 10D5 */ BOOLEAN m_bSetDayOnActivate;
    /* 10D6 */ BOOL m_ambianceForce;
    /* 10D8 */ int field_10D8;
    /* 10DA */ DWORD m_deltaTime;
    /* 10DE */ INT m_nChatMessageCount;
    /* 10E2 */ CResRef m_movie;
    /* 10EA */ BOOLEAN m_bInControlOfDialog;
    /* 10EB */ BOOLEAN m_bInControlOfStore;
    /* 10EC */ BOOL m_bGameOverPanel;
    /* 10F0 */ int field_10F0;
    /* 10F4 */ int field_10F4;
    /* 10F8 */ LONG m_autoPauseId;
    /* 10FC */ STRREF m_autoPauseRef;
    /* 1100 */ COLORREF m_autoPauseColor;
    /* 1104 */ STRREF m_autoPauseName;
    /* 1108 */ int field_1108;
    /* 110C */ int field_110C;
    /* 1138 */ INT m_nPickPartyNumCharacters;
    /* 114C */ int field_114C;
    /* 1150 */ unsigned char field_1150;
    /* 1151 */ BOOLEAN m_bEndMajorEventListenToJoin;
    /* 1152 */ BOOLEAN m_bEndMajorEventPauseStatus;
    /* 1153 */ BOOLEAN m_bChapterTransitionPending;
    /* 1154 */ INT m_nChapterTransition;
    /* 1158 */ RESREF m_szChapterTransitionResRef;
    /* 1160 */ BOOLEAN m_bMoviePending;
    /* 1161 */ RESREF m_szMovieResRef;
    /* 1169 */ BOOLEAN m_bPendingMapWorld;
    /* 116A */ PLAYER_ID m_idPendingMapWorldController;
    /* 116E */ SHORT m_nPendingMapWorldDirection;
    /* 1170 */ BOOLEAN m_bRestPending;
    /* 1171 */ BOOLEAN m_bRestRenting;
    /* 1172 */ INT m_nRestHP;
    /* 1176 */ BOOLEAN m_bRestMovie;
    /* 1178 */ LONG m_nBattleCryTimeOut;
    /* 117C */ CTypedPtrList<CPtrList, CDeathSound*> m_deathSoundList;
    /* 1198 */ LONG m_nPartySizeCheckStartDelay;
    /* 119C */ BOOLEAN m_bPlayEndCredits;
    /* 119D */ BOOLEAN field_119D;
    /* 119E */ BOOLEAN m_bPendingReformParty;
    /* 119F */ BOOLEAN m_bLeaveAreaLuaPanicPending;
    /* 11A0 */ ULONG m_ulLeaveAreaLuaPanicTimer;
    /* 11A4 */ CPoint m_ptLeaveAreaLuaPanicLocation;
    /* 11AC */ SHORT m_nLeaveAreaLuaPanicDirection;
    /* 11AE */ CString m_sLeaveAreaLuaPanicAreaName;
    /* 11B2 */ CString m_sLeaveAreaLuaPanicParchment;
    /* 11B6 */ int field_11B6;
    /* 11BA */ DWORD field_11BA;
    /* 11BE */ int field_11BE;
    /* 11C2 */ LONG m_lastAmbiance;
    /* 11C6 */ INT m_comingOutOfDialog;
    /* 11CA */ BYTE m_nAutoHideInterface;
    /* 11CC */ INT m_nAutoUnhideInterface;
    /* 11D0 */ CRect field_11D0;
    /* 11F0 */ int field_11F0;
    /* 11F4 */ int field_11F4;
    /* 11F8 */ int field_11F8;
    /* 1200 */ LONG m_nBlackOutCountDown;
    /* 1204 */ unsigned char field_1204;
};

class CUIControlButtonWorldContainerSlot : public CUIControlButton {
public:
    CUIControlButtonWorldContainerSlot(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldContainerSlot() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonDialog : public CUIControlButton {
public:
    CUIControlButtonDialog(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonDialog() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarWorldContainer : public CUIControlScrollBar {
public:
    CUIControlScrollBarWorldContainer(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarWorldContainer();
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;

    void UpdateScrollBar();
    void InvalidateSlots();
};

class CUIControlButtonWorldContainerIcon : public CUIControlButton {
public:
    CUIControlButtonWorldContainerIcon(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldContainerIcon() override;
    BOOL Render(BOOL bForce) override;

    /* 0666 */ CResRef m_resRef;
};

class CUIControlButtonWorldContainerClose : public CUIControlButton {
public:
    CUIControlButtonWorldContainerClose(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldContainerClose() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonClock : public CUIControlButton3State {
public:
    CUIControlButtonClock(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonClock() override;
    void TimerAsynchronousUpdate(BOOLEAN bInside) override;
    void ActivateToolTip() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint) override;

    /* 066E */ CVidCell m_vcGear;
    /* 0748 */ CVidCell field_748;
};

class CUIControlButtonWorldDeathLoad : public CUIControlButton {
public:
    CUIControlButtonWorldDeathLoad(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldDeathLoad() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonWorldDeathQuit : public CUIControlButton {
public:
    CUIControlButtonWorldDeathQuit(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldDeathQuit() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENWORLD_H_ */

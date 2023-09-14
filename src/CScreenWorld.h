#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CVidCell.h"
#include "CWeather.h"

#define CSCREENWORLD_VIRTUAL_KEYS 92

class CAIObjectType;
class CGameSprite;
class CUIControlTextDisplay;

class CScreenWorld : public CBaldurEngine {
public:
    static const LONG BORED_TIME;

    CScreenWorld();
    /* 0004 */ ~CScreenWorld() override;
    /* 0018 */ void EngineDeactivated() override;
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
    /* 00F0 */ void OnRestButtonClick() override;

    void StartScroll(CPoint dest, SHORT speed);
    void AsynchronousUpdate(BOOL bActiveEngine);
    BOOL TogglePauseGame(char a2, char a3, int a4);
    BOOLEAN ReadyMovie(const CResRef& movieResRef, BOOLEAN bForcedFromServer);
    BOOLEAN ReadyEndCredits(BOOLEAN bForcedFromServer);
    void EndDialog(BOOLEAN bForceExecution, BOOLEAN fullEnd);
    void SetCurrentXP(DWORD dwCurrentXP);
    void AddGold(DWORD dwGold);
    void StopContainer();
    void StartStore(const CAIObjectType& cAIProprietor, const CAIObjectType& cAICustomer, CResRef cResStore, BOOLEAN bInitiate);
    void StopStore();
    void DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, BOOLEAN bMoveToTop);
    void DisplayText(const CString& sName, const CString& sText, LONG lMarker, BOOLEAN bMoveToTop);
    void RemoveText(POSITION pos);
    void SetItemMarker(POSITION pos, LONG lMarker);
    void ClearChatMessages();
    void HideInterface();
    void UnhideInterface();
    void StopDeath();
    void SetPendingChapterChange(BYTE nChapter, BYTE* szChapterResRef);
    void SetPendingMovie(BYTE* szMovieResRef);
    void StartSaveGameMultiplayerHost();
    void StartMovieMultiplayerHost(BYTE* cMovieResRef);
    void SetPendingMapWorld(PLAYER_ID idController, SHORT facingDirection);
    void StartMapWorldMultiplayerHost(PLAYER_ID idController, SHORT facingDirection);
    void SetPendingReformParty();
    void StartReformPartyMultiplayerHost();
    void SetPendingRest(INT nHP, BOOLEAN bRenting, BOOLEAN bMovie);
    void CheckEndOfHardPause();
    void SetDialogTokens(CGameSprite* pCharacter);
    void EnableKeyRepeat();
    void DisableKeyRepeat();

    void CompressTime(DWORD deltaTime) { m_deltaTime = deltaTime; }

    /* 012E */ BOOL m_bShiftKeyDown;
    /* 0132 */ BOOL m_bMenuKeyDown;
    /* 0136 */ BOOL m_bCtrlKeyDown;
    /* 013A */ BOOL m_bCapsLockKeyOn;
    /* 013E */ BOOLEAN m_bPaused;
    /* 0146 */ BOOL m_bHardPaused;
    /* 0152 */ BOOL m_bPausedBeforePickParty;
    /* 0B68 */ CKeyInfo m_pVirtualKeys[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0E48 */ BYTE m_pVirtualKeysFlags[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0EA4 */ int field_EA4;
    /* 0EA8 */ CUIControlTextDisplay* field_EA8;
    /* 0EE0 */ LONG field_EE0;
    /* 0EF0 */ int field_EF0;
    /* 0F04 */ unsigned char field_F04;
    /* 0F46 */ CWeather m_weather;
    /* 10B2 */ short field_10B2;
    /* 10B4 */ int field_10B4;
    /* 10D4 */ BOOLEAN m_bSetNightOnActivate;
    /* 10D5 */ BOOLEAN m_bSetDayOnActivate;
    /* 10DA */ DWORD m_deltaTime;
    /* 10DE */ int field_10DE;
    /* 10E2 */ CResRef m_movie;
    /* 10EB */ BOOLEAN m_bInControlOfStore;
    /* 10EC */ BOOL m_bGameOverPanel;
    /* 10F0 */ int field_10F0;
    /* 10F4 */ int field_10F4;
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
    /* 119C */ BOOLEAN m_bPlayEndCredits;
    /* 119D */ BOOLEAN field_119D;
    /* 119E */ BOOLEAN m_bPendingReformParty;
    /* 11BA */ DWORD field_11BA;
    /* 11CA */ BYTE m_nAutoHideInterface;
    /* 11CC */ INT m_nAutoUnhideInterface;
    /* 1204 */ unsigned char field_1204;
};

class CUIControlButtonDialog : public CUIControlButton {
public:
    CUIControlButtonDialog(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonDialog() override;
    void OnLButtonClick(CPoint pt) override;
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

#include "CScreenConnection.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CScreenStart.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F375C
const CString CScreenConnection::TOKEN_SERVERVERSION("SERVERVERSION");

// 0x8F3748
const CString CScreenConnection::TOKEN_CLIENTVERSION("CLIENTVERSION");

// 0x8F3768
int CScreenConnection::dword_8F3768;

// 0x5F9BB0
CScreenConnection::CScreenConnection()
{
    // TODO: Incomplete.
}

// 0x5FA8B0
void CScreenConnection::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x6717F0
SHORT CScreenConnection::GetNumVirtualKeys()
{
    return CSCREENCONNECTION_VIRTUAL_KEYS;
}

// 0x5FA8D0
CKeyInfo* CScreenConnection::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x5FA8D0
BYTE* CScreenConnection::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x5FA910
CScreenConnection::~CScreenConnection()
{
}

// 0x5FAD80
void CScreenConnection::EngineDeactivated()
{
    field_4C0.Unload();
    field_9C0.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    if (dword_8F3768 == 2) {
        dword_8F3768 = 1;
    }
}

// 0x5FB280
void CScreenConnection::OnLButtonDblClk(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            m_cUIManager.OnLButtonDblClk(pt);
        }
    }
}

// 0x5FB2B0
void CScreenConnection::OnLButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
            m_cUIManager.OnLButtonDown(pt);
        }
    }
}

// 0x5FB2F0
void CScreenConnection::OnLButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
            m_cUIManager.OnLButtonUp(pt);
        }
    }
}

// 0x5FB330
void CScreenConnection::OnMouseMove(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            m_cUIManager.OnMouseMove(pt);
        }
    }
}

// 0x5FB360
void CScreenConnection::OnRButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
            m_cUIManager.OnRButtonDown(pt);
        }
    }
}

// 0x5FB3A0
void CScreenConnection::OnRButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
            m_cUIManager.OnRButtonUp(pt);
        }
    }
}

// 0x5FC6F0
void CScreenConnection::SummonPopup(DWORD nID)
{
    // TODO: Incomplete.
}

// 0x5FC850
void CScreenConnection::DismissPopup()
{
    // TODO: Incomplete.
}

// 0x5FCA00
void CScreenConnection::sub_5FCA00(int a1)
{
    // TODO: Incomplete.
}

// 0x5FDB20
void CScreenConnection::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x5FE930
void CScreenConnection::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x600770
void CScreenConnection::StartConnection(BOOLEAN bDirectPlayLobby)
{
    m_bAllowInput = TRUE;
    m_nProtocol = 0;
    if (bDirectPlayLobby) {
        m_bDirectPlayLobby = bDirectPlayLobby;
    } else {
        m_nEnumServiceProvidersCountDown = 2;
        m_bStartedCountDown = 0;
        m_bEliminateInitialize = TRUE;
        m_dwLastSessionRefresh = GetTickCount();
    }

    if (g_pBaldurChitin->m_bIsAutoStarting) {
        m_bAllowInput = FALSE;
    }
}

// 0x6024A0
void CScreenConnection::sub_6024A0()
{
    CSingleLock lock(&(m_cUIManager.field_36));
    lock.Lock();
    DismissPopup();
    lock.Unlock();

    g_pBaldurChitin->cNetwork.CloseSession(TRUE);

    g_pBaldurChitin->m_pEngineStart->field_140 = 0;
    SelectEngine(g_pBaldurChitin->m_pEngineStart);
}

// 0x602550
void CScreenConnection::CancelEngine()
{
    while (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();
        switch (pPanel->m_nID) {
        case 19:
        case 21:
            DismissPopup();
            break;
        default:
            OnCancelButtonClick();
            break;
        }
    }
}

// 0x602590
CUIControlButtonConnectionGameMode::CUIControlButtonConnectionGameMode(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15413, strRes); // "Single Player"
    SetText(strRes.szText);
}

// 0x602680
CUIControlButtonConnectionGameMode::~CUIControlButtonConnectionGameMode()
{
}

// 0x602720
void CUIControlButtonConnectionGameMode::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7173
    UTIL_ASSERT(pConnection != NULL);

    CUIManager* pManager = pConnection->GetManager();
    CSingleLock lock(&(pManager->field_36), TRUE);
    pConnection->SummonPopup(1);
    lock.Unlock();
}

// 0x6027D0
CUIControlButtonConnectionQuitGame::CUIControlButtonConnectionQuitGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13731, strRes); // "Quit Game"
    SetText(strRes.szText);
}

// 0x6028C0
CUIControlButtonConnectionQuitGame::~CUIControlButtonConnectionQuitGame()
{
}

// 0x602960
void CUIControlButtonConnectionQuitGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x602A90
CUIControlButtonConnectionNewGame::CUIControlButtonConnectionNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13963, strRes); // "New Game"
    SetText(strRes.szText);
}

// 0x602B80
CUIControlButtonConnectionNewGame::~CUIControlButtonConnectionNewGame()
{
}

// 0x602C20
void CUIControlButtonConnectionNewGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x602E10
CUIControlButtonConnectionQuickLoad::CUIControlButtonConnectionQuickLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(33508, strRes); // "Quick Load"
    SetText(strRes.szText);
}

// 0x602F00
CUIControlButtonConnectionQuickLoad::~CUIControlButtonConnectionQuickLoad()
{
}

// 0x602FA0
void CUIControlButtonConnectionQuickLoad::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7434
    UTIL_ASSERT(pConnection != NULL);

    pConnection->sub_5FCA00(1);
}

// 0x602FE0
CUIControlButtonConnectionLoadGame::CUIControlButtonConnectionLoadGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13729, strRes); // "Load Game"
    SetText(strRes.szText);
}

// 0x6030D0
CUIControlButtonConnectionLoadGame::~CUIControlButtonConnectionLoadGame()
{
}

// 0x603170
void CUIControlButtonConnectionLoadGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x603380
CUIControlButtonConnectionJoinGame::CUIControlButtonConnectionJoinGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13964, strRes); // "Join Game"
    SetText(strRes.szText);
}

// 0x603470
CUIControlButtonConnectionJoinGame::~CUIControlButtonConnectionJoinGame()
{
}

// 0x603510
void CUIControlButtonConnectionJoinGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7620
    UTIL_ASSERT(pConnection != NULL);

    if (g_pChitin->cNetwork.field_1C && g_pBaldurChitin->cDimm.cResCache.field_11C < 175000000) {
        pConnection->field_49E = 2;
        pConnection->m_popupText = 20692;
        pConnection->m_popupButtonText1 = 11973;
        pConnection->SummonPopup(20);
    } else {
        CSingleLock lock(&(m_pPanel->m_pManager->field_36), TRUE);
        pConnection->field_49E = 7;
        pConnection->m_popupText = 20624;
        pConnection->m_popupButtonText1 = 20625;
        pConnection->m_popupButtonText2 = 13727;
        pConnection->SummonPopup(22);
        lock.Unlock();
    }
}

// 0x603750
CUIControlButtonConnectionPopupDone::CUIControlButtonConnectionPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes); // "Done"
    SetText(strRes.szText);
}

// 0x603840
CUIControlButtonConnectionPopupDone::~CUIControlButtonConnectionPopupDone()
{
}

// 0x6038E0
void CUIControlButtonConnectionPopupDone::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7836
    UTIL_ASSERT(pConnection != NULL);

    pConnection->OnDoneButtonClick();
}

// 0x603920
CUIControlButtonConnectionPopupCancel::CUIControlButtonConnectionPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes); // "Cancel"
    SetText(strRes.szText);
}

// 0x603A10
CUIControlButtonConnectionPopupCancel::~CUIControlButtonConnectionPopupCancel()
{
}

// 0x603AB0
void CUIControlButtonConnectionPopupCancel::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7836
    UTIL_ASSERT(pConnection != NULL);

    pConnection->OnCancelButtonClick();
}

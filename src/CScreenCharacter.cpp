#include "CScreenCharacter.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenCreateChar.h"
#include "CScreenWorld.h"
#include "CUIControlFactory.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F3324
const CString CScreenCharacter::TOKEN_SPELLLEVEL("SPELLLEVEL");

// 0x8F3320
const CString CScreenCharacter::TOKEN_WEAPONNAME("WEAPONNAME");

// 0x8F333C
const CString CScreenCharacter::TOKEN_NUMBER("number");

// 0x8F332C
const CString CScreenCharacter::TOKEN_MINIMUM("MINIMUM");

// 0x8F3334
const CString CScreenCharacter::TOKEN_MAXIMUM("MAXIMUM");

// 0x5D5220
CScreenCharacter::CScreenCharacter()
{
    // TODO: Incomplete.
}

// 0x5D63B0
CScreenCharacter::~CScreenCharacter()
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenCharacter::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x5D62F0
void CScreenCharacter::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x5D6300
BOOL CScreenCharacter::GetShiftKey()
{
    return field_1B8 && m_bShiftKeyDown;
}

// 0x5D6320
void CScreenCharacter::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x5D6330
BOOL CScreenCharacter::CheckSystemKeyShift()
{
    return field_1B8;
}

// 0x5D6340
void CScreenCharacter::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x5D6350
BOOL CScreenCharacter::GetCapsLockKey()
{
    return field_1B8 && m_bCapsLockKeyOn;
}

// 0x5D6330
BOOL CScreenCharacter::CheckSystemKeyCapsLock()
{
    return field_1B8;
}

// 0x699600
SHORT CScreenCharacter::GetNumVirtualKeys()
{
    return CSCREENCHARACTER_VIRTUAL_KEYS;
}

// 0x5D6370
CKeyInfo* CScreenCharacter::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x5D6380
BYTE* CScreenCharacter::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x5D6A80
void CScreenCharacter::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    if (m_cUIManager.m_bInitialized) {
        if (GetTopPopup() == NULL) {
            UpdateMainPanel(FALSE);
        }

        UpdateCursorShape(0);
        CheckEnablePortaits(1);
        CheckEnableLeftPanel();
        g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x5D6BC0
void CScreenCharacter::EngineDeactivated()
{
    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            }
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
        field_1B8 = FALSE;
    }
}

// 0x5D7B80
CString CScreenCharacter::GetCurrentPortrait(CGameSprite* pSprite)
{
    switch (pSprite->m_startTypeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        return CString(CScreenCreateChar::MALE_PORTRAITS[m_nCurrentPortrait]);
    case CAIOBJECTTYPE_SEX_FEMALE:
        return CString(CScreenCreateChar::FEMALE_PORTRAITS[m_nCurrentPortrait]);
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 1767
        UTIL_ASSERT(FALSE);
    }
}

// 0x5D7E30
void CScreenCharacter::ResetCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1961
    UTIL_ASSERT(pGame != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1964
    UTIL_ASSERT(m_pPortraits == NULL);

    m_pPortraits = pGame->GetPortraits();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1966
    UTIL_ASSERT(m_pPortraits != NULL);

    field_80A = -1;
    field_806 = -1;
    UpdatePortraitList(pPanel, 3, -1);
    UpdatePortraitList(pPanel, 2, field_806);

    CUIControlButtonCharacterPortrait* pPortrait;

    pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1976
    UTIL_ASSERT(pPortrait != NULL);

    pPortrait->SetPortrait(CResRef(""));

    pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1979
    UTIL_ASSERT(pPortrait != NULL);

    pPortrait->SetPortrait(CResRef(""));

}

// 0x5D8190
void CScreenCharacter::UpdatePortraitList(CUIPanel* pPanel, DWORD dwControlId, INT nSelected)
{
    CString sPortrait;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2079
    UTIL_ASSERT(m_pPortraits != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2080
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwControlId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2082
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;
    pText->field_A68 = 32767;

    INT nIndex = 0;
    POSITION pos = m_pPortraits->GetHeadPosition();
    while (pos != NULL) {
        COLORREF rgbTextColor = CBaldurChitin::TEXTDISPLAY_COLOR_SELECT;
        if (nSelected != nIndex) {
            rgbTextColor = pText->m_rgbTextColor;
        }

        sPortrait = m_pPortraits->GetAt(pos);
        pText->DisplayString(CString(""),
            sPortrait,
            pText->m_rgbLabelColor,
            rgbTextColor,
            nIndex,
            FALSE,
            TRUE);

        m_pPortraits->GetNext(pos);
        nIndex++;
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));
}

// 0x5DBDE0
void CScreenCharacter::UpdateMainPanel(BOOL bCharacterChanged)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
CUIPanel* CScreenCharacter::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x5E6840
void CScreenCharacter::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9357
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9359
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

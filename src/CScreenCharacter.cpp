#include "CScreenCharacter.h"

#include "CAIObjectType.h"
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

// 0x5D7C10
void CScreenCharacter::ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sPortrait;

    m_nCurrentPortrait = 0;
    sPortrait = GetCurrentPortrait(pSprite);

    m_cResPortraitSmall = sPortrait + "S";
    m_cResPortraitLarge = sPortrait + "L";
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

// 0x5D8490
void CScreenCharacter::ResetClassPanel(CGameSprite* pSprite, int a2)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(6);

    DWORD name;
    DWORD description;
    switch (m_nClass) {
    case CAIOBJECTTYPE_C_WIZARD:
        name = 1081; // "<MAGESCHOOL>"
        description = 10942;
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        name = 1078; // "Paladin"
        description = 9558;
        break;
    case CAIOBJECTTYPE_C_MONK:
        name = 33; // "Monk"
        description = 36;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        name = 1079; // "Cleric"
        description = 9559;
        break;
    }

    UpdateLabel(pPanel, 0x10000000, "%s", FetchString(name));
    UpdateHelp(pPanel->m_nID, 13, description);
}

// 0x5D8570
void CScreenCharacter::ResetExportPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(13);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2372
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2374
    UTIL_ASSERT(pGame != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2377
    UTIL_ASSERT(m_pCharacters == NULL);

    m_pCharacters = pGame->GetImportCharacters();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2379
    UTIL_ASSERT(m_pCharacters != NULL);

    m_nCharacterIndex = -1;
    UpdateCharacterList(pPanel, 0, m_nCharacterIndex);

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(6));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2387
    UTIL_ASSERT(pEdit != NULL);

    pEdit->SetText(CString(""));

    UpdateHelp(pPanel->m_nID, 2, 10962);
}

// 0x5D8680
void CScreenCharacter::UpdateCharacterList(CUIPanel* pPanel, DWORD dwTextId, INT nSelected)
{
    CString sFileName;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2423
    UTIL_ASSERT(m_pCharacters != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2424
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2426
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;
    pText->field_A68 = 32767;

    INT nIndex = 0;
    POSITION pos = m_pCharacters->GetHeadPosition();
    while (pos != NULL) {
        COLORREF rgbTextColor = CBaldurChitin::TEXTDISPLAY_COLOR_SELECT;
        if (nSelected != nIndex) {
            rgbTextColor = pText->m_rgbTextColor;
        }

        sFileName = m_pCharacters->GetAt(pos);

        pText->DisplayString(CString(""),
            sFileName,
            pText->m_rgbLabelColor,
            rgbTextColor,
            nIndex,
            FALSE,
            TRUE);

        m_pCharacters->GetNext(pos);
        nIndex++;
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));
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

// 0x5DBB20
void CScreenCharacter::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 4222
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 4223
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 4224
    UTIL_ASSERT(pRightPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }

    pMainPanel->SetEnabled(bEnable);
    pLeftPanel->SetEnabled(bEnable);
    pRightPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    CheckEnablePortaits(1);
    CheckEnableLeftPanel();
}

// NOTE: Duplicate of `CScreenCreateChar::GetRangerHatedRaceStrref`.
//
// 0x5DBC80
STRREF CScreenCharacter::GetRangerHatedRaceStrref(BYTE nRace)
{
    STRREF strRace;
    switch (nRace) {
    case CAIOBJECTTYPE_R_OGRE:
        strRace = 15975;
        break;
    case CAIOBJECTTYPE_R_WYVERN:
        strRace = 37617;
        break;
    case CAIOBJECTTYPE_R_GIANT:
        strRace = 3279;
        break;
    case CAIOBJECTTYPE_R_GOBLIN:
        strRace = 3280;
        break;
    case CAIOBJECTTYPE_R_LIZARDMAN:
        strRace = 3281;
        break;
    case CAIOBJECTTYPE_R_ORC:
        strRace = 3282;
        break;
    case CAIOBJECTTYPE_R_SALAMANDER:
        strRace = 3290;
        break;
    case CAIOBJECTTYPE_R_TROLL:
        strRace = 3288;
        break;
    case CAIOBJECTTYPE_R_UMBERHULK:
        strRace = 3289;
        break;
    case CAIOBJECTTYPE_R_UNDEAD:
        strRace = 3285;
        break;
    case CAIOBJECTTYPE_R_YUANTI:
        strRace = 30850;
        break;
    case CAIOBJECTTYPE_R_HARPY:
        strRace = 37616;
        break;
    case CAIOBJECTTYPE_R_BUGBEAR:
        strRace = 28367;
        break;
    case CAIOBJECTTYPE_R_HOOK_HORROR:
        strRace = 37606;
        break;
    case CAIOBJECTTYPE_R_DRIDER:
        strRace = 37607;
        break;
    case CAIOBJECTTYPE_R_SHAPESHIFTER:
        strRace = 37605;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 4439
        UTIL_ASSERT(FALSE);
    }
    return strRace;
}

// 0x5DBDE0
void CScreenCharacter::UpdateMainPanel(BOOL bCharacterChanged)
{
    // TODO: Incomplete.
}

// 0x5E0880
void CScreenCharacter::ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite, int a3)
{
    // TODO: Incomplete.
}

// 0x5E0B20
void CScreenCharacter::UpdatePopupPanel(DWORD dwPanelId, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x5E0E50
CUIPanel* CScreenCharacter::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenCharacter::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Inlined.
void CScreenCharacter::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 6446
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// 0x5E0E70
void CScreenCharacter::SummonPopup(DWORD dwPopupId, CGameSprite* pSprite, int a3)
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
        field_1B8 = FALSE;
    }

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 6771
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 6777
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);

    ResetPopupPanel(pPanel->m_nID, pSprite, a3);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    EnablePopupPanel(pPanel->m_nID, TRUE);

    UpdatePopupPanel(pPanel->m_nID, pSprite);
}

// 0x5E1DF0
void CScreenCharacter::DismissPopup(CGameSprite* pSprite)
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        // NOTE: Uninline
        m_cUIManager.KillCapture();
        field_1B8 = FALSE;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 7255
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        if (pSprite != NULL) {
            CUIPanel* pPanel = m_lPopupStack.GetTail();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 7272
            UTIL_ASSERT(pPanel != NULL);

            // NOTE: Uninline.
            ShowPopupPanel(pPanel->m_nID, TRUE);

            // NOTE: Uninline.
            EnablePopupPanel(pPanel->m_nID, TRUE);

            UpdatePopupPanel(pPanel->m_nID, pSprite);
        }
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel(FALSE);
    }
}

// 0x5E2210
void CScreenCharacter::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x5E46C0
void CScreenCharacter::OnInformationButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 8345
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(57, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E47E0
void CScreenCharacter::OnBiographyButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 8403
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(12, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E4900
void CScreenCharacter::OnCustomizeBiographyButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 8460
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(51, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E4C40
void CScreenCharacter::OnScriptButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 8637
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(11, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E4D50
void CScreenCharacter::OnExportButtonClick()
{
    // TODO: Incomplete.
}

// 0x5E5330
void CScreenCharacter::OnLevelUpButtonClick()
{
    // TODO: Incomplete.
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

// 0x5E6950
void CScreenCharacter::CheckDropEquipment()
{
    CheckDropSlot(43);
    CheckDropSlot(44);
    CheckDropSlot(45);
    CheckDropSlot(46);
    CheckDropSlot(47);
    CheckDropSlot(48);
    CheckDropSlot(49);
    CheckDropSlot(50);
    CheckDropSlot(11);
    CheckDropSlot(12);
    CheckDropSlot(13);
    CheckDropSlot(5);
    CheckDropSlot(1);
    CheckDropSlot(6);
    CheckDropSlot(0);
    CheckDropSlot(2);
    CheckDropSlot(7);
    CheckDropSlot(3);
    CheckDropSlot(4);
    CheckDropSlot(8);
    CheckDropSlot(15);
    CheckDropSlot(16);
    CheckDropSlot(17);
}

// 0x5E6A30
void CScreenCharacter::CheckDropSlot(INT nSlot)
{
    // TODO: Incomplete.
}

// 0x5E7020
void CScreenCharacter::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9743
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        STRREF strError;
        if (pGame->CanRestParty(strError, 0, 0, 0)) {
            m_nErrorState = 1;
            m_dwErrorTextId = 15358;
            m_strErrorButtonText[0] = 17199;
            m_strErrorButtonText[1] = 11596;
            m_strErrorButtonText[2] = 13727;
            SummonPopup(50, pSprite, 1);
        } else {
            m_nErrorState = 0;
            m_dwErrorTextId = strError;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(9, pSprite, 1);
        }

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E71A0
void CScreenCharacter::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 9:
        m_nNumErrorButtons = 1;
        break;
    case 10:
        m_nNumErrorButtons = 2;
        break;
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 9829
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9842
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 9851
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 10508
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENCHARACTER_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x5E76D0
void CScreenCharacter::UpdateCustomizePanel(CGameSprite* pSprite)
{
    CUIControlButton* pButton;
    CUIPanel* pPanel = m_cUIManager.GetPanel(17);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9962
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(6));

    BOOL bEnabled = (pSprite->m_baseStats.m_flags & 0x800) != 0;

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9975
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(bEnabled);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9979
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(bEnabled);
}

// 0x5E9600
void CScreenCharacter::OnCustomizeButtonClick()
{
    // TODO: Incomplete.
}

// 0x5E9800
void CScreenCharacter::OnAppearanceButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11271
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(18, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E9910
void CScreenCharacter::OnSoundsButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11328
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        SummonPopup(20, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x5EAC00
CUIControlButtonCharacterCustomize::CUIControlButtonCharacterCustomize(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(10645, strRes); // "Customize"
    SetText(strRes.szText);
}

// 0x5EACF0
CUIControlButtonCharacterCustomize::~CUIControlButtonCharacterCustomize()
{
}

// 0x5EAD90
void CUIControlButtonCharacterCustomize::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12402
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnCustomizeButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EADD0
CUIControlButtonCharacterInformation::CUIControlButtonCharacterInformation(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11946, strRes); // "Information"
    SetText(strRes.szText);
}

// 0x5EAEC0
CUIControlButtonCharacterInformation::~CUIControlButtonCharacterInformation()
{
}

// 0x5EAF60
void CUIControlButtonCharacterInformation::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12458
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnInformationButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EAFA0
CUIControlButtonCharacterExport::CUIControlButtonCharacterExport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13956, strRes); // "Export"
    SetText(strRes.szText);
}

// 0x5EB090
CUIControlButtonCharacterExport::~CUIControlButtonCharacterExport()
{
}

// 0x5EB130
void CUIControlButtonCharacterExport::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12514
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnExportButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EB170
CUIControlButtonCharacterLevelUp::CUIControlButtonCharacterLevelUp(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(7175, strRes); // "Level Up"
    SetText(strRes.szText);
}

// 0x5EB260
CUIControlButtonCharacterLevelUp::~CUIControlButtonCharacterLevelUp()
{
}

// 0x5EB300
void CUIControlButtonCharacterLevelUp::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12570
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnLevelUpButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EB340
CUIControlButtonCharacterClassSelection::CUIControlButtonCharacterClassSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    CString sClass;
    STR_RES strRes;
    BYTE nClass;

    switch (m_nID) {
    case 2:
        nClass = CAIOBJECTTYPE_C_BARBARIAN;
        break;
    case 3:
        nClass = CAIOBJECTTYPE_C_BARD;
        break;
    case 4:
        nClass = CAIOBJECTTYPE_C_CLERIC;
        break;
    case 5:
        nClass = CAIOBJECTTYPE_C_DRUID;
        break;
    case 6:
        nClass = CAIOBJECTTYPE_C_FIGHTER;
        break;
    case 7:
        nClass = CAIOBJECTTYPE_C_MONK;
        break;
    case 8:
        nClass = CAIOBJECTTYPE_C_PALADIN;
        break;
    case 9:
        nClass = CAIOBJECTTYPE_C_RANGER;
        break;
    case 10:
        nClass = CAIOBJECTTYPE_C_ROGUE;
        break;
    case 11:
        nClass = CAIOBJECTTYPE_C_SORCERER;
        break;
    case 12:
        nClass = CAIOBJECTTYPE_C_WIZARD;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 12808
        UTIL_ASSERT(FALSE);
    }

    ruleTables.GetClassStringLower(nClass, 0x4000, 0, sClass, 1);
    SetText(sClass);

    m_nSelectedFrame = 0;
    pCharacter->m_nClass = 0;
}

// 0x5EB540
CUIControlButtonCharacterClassSelection::~CUIControlButtonCharacterClassSelection()
{
}

// 0x5EB5E0
void CUIControlButtonCharacterClassSelection::OnLButtonClick(CPoint pt)
{
    CSingleLock renderLock(&(m_pPanel->m_pManager->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12641
    UTIL_ASSERT(pCharacter != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12643
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        STRREF strDescription;

        switch (m_nID) {
        case 2:
            strDescription = 37;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_BARBARIAN;
            break;
        case 3:
            strDescription = 9562;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_BARD;
            break;
        case 4:
            strDescription = 9559;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_CLERIC;
            break;
        case 5:
            strDescription = 9560;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_DRUID;
            break;
        case 6:
            strDescription = 9556;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_FIGHTER;
            break;
        case 7:
            strDescription = 36;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_MONK;
            break;
        case 8:
            strDescription = 9558;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_PALADIN;
            break;
        case 9:
            strDescription = 9557;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_RANGER;
            break;
        case 10:
            strDescription = 9561;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_ROGUE;
            break;
        case 11:
            strDescription = 35;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_SORCERER;
            break;
        case 12:
            strDescription = 9563;
            pCharacter->m_nClass = CAIOBJECTTYPE_C_WIZARD;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 12724
            UTIL_ASSERT(FALSE);
        }

        CAIObjectType typeAI(pSprite->m_startTypeAI);
        typeAI.AddClass(pCharacter->m_nClass);
        pSprite->SetAIType(typeAI, TRUE, TRUE);

        pCharacter->UpdateHelp(m_pPanel->m_nID, 13, strDescription);
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x5EB8C0
CUIControlButtonInformationDone::CUIControlButtonInformationDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes); // "Done"
    SetText(strRes.szText);
}

// 0x5EB9B0
CUIControlButtonInformationDone::~CUIControlButtonInformationDone()
{
}

// 0x5EBA50
void CUIControlButtonInformationDone::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12874
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnDoneButtonClick();
}

#include "CScreenCharacter.h"

#include "CAIObjectType.h"
#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenCreateChar.h"
#include "CScreenWorld.h"
#include "CUIControlFactory.h"
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

// NOTE: Probably does not belong here.
//
// 0x8F3338
CString CScreenCharacter::SAVE_NAME("default");

// 0x5D50F0
void CScreenCharacter::ResetBiography(CGameSprite* pSprite)
{
    switch (pSprite->m_derivedStats.GetBestClass()) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        pSprite->m_baseStats.m_biography = 27862;
        break;
    case CAIOBJECTTYPE_C_BARD:
        pSprite->m_baseStats.m_biography = 19425;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        pSprite->m_baseStats.m_biography = 19422;
        break;
    case CAIOBJECTTYPE_C_DRUID:
        pSprite->m_baseStats.m_biography = 19421;
        break;
    case CAIOBJECTTYPE_C_FIGHTER:
        pSprite->m_baseStats.m_biography = 19423;
        break;
    case CAIOBJECTTYPE_C_MONK:
        pSprite->m_baseStats.m_biography = 27860;
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        pSprite->m_baseStats.m_biography = 19427;
        break;
    case CAIOBJECTTYPE_C_RANGER:
        pSprite->m_baseStats.m_biography = 19429;
        break;
    case CAIOBJECTTYPE_C_ROGUE:
        pSprite->m_baseStats.m_biography = 19428;
        break;
    case CAIOBJECTTYPE_C_SORCERER:
        pSprite->m_baseStats.m_biography = 27863;
        break;
    case CAIOBJECTTYPE_C_WIZARD:
        pSprite->m_baseStats.m_biography = 19430;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 199
        UTIL_ASSERT(FALSE);
    }
}

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

// 0x5D78E0
void CScreenCharacter::OnPortraitLClick(DWORD nPortrait)
{
    // NOTE: Unsigned compare.
    if (nPortrait < static_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetNumCharacters())) {
        m_nSelectedCharacter = nPortrait;

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            // NOTE: Uninline.
            LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterId(static_cast<SHORT>(nPortrait));

            for (SHORT index = 0; index < 6; index++) {
                if (g_pBaldurChitin->GetObjectGame()->m_characters[index] == nCharacterId) {
                    g_pBaldurChitin->GetBaldurMessage()->UpdateDemandCharacters(0, index, 0);
                }
            }
        }

        CheckMultiPlayerViewableModifyable();
        UpdateCursorShape(0);
        UpdateMainPanel(TRUE);
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x5D79B0
void CScreenCharacter::UpdateSavingThrows(CUIControlTextDisplay* pText, CDerivedStats& DStats)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    UpdateTextForceColor(pText,
        RGB(200, 200, 0),
        "%s",
        FetchString(17379)); // "Saving Throws"

    UpdateText(pText,
        "%s: %+d",
        FetchString(17380), // "Fortitude"
        DStats.m_nSaveVSFortitude);

    INT nTrapSenseBonus = ruleTables.GetTrapSenseBonus(DStats);
    if (nTrapSenseBonus != 0) {
        UpdateText(pText,
            "%s: %+d (%s: %d)",
            FetchString(17381), // "Reflex"
            DStats.m_nSaveVSReflex,
            FetchString(39802), // "Traps"
            nTrapSenseBonus);
    } else {
        UpdateText(pText,
            "%s: %+d",
            FetchString(17381), // "Reflex"
            DStats.m_nSaveVSReflex);
    }

    UpdateText(pText,
        "%s: %+d",
        FetchString(17382), // "Will"
        DStats.m_nSaveVSWill);
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

// NOTE: Inlined.
void CScreenCharacter::IncCurrentPortrait(CGameSprite* pSprite)
{
    INT nCount;
    switch (pSprite->m_startTypeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        nCount = CScreenCreateChar::MALE_PORTRAITS_COUNT;
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        nCount = CScreenCreateChar::FEMALE_PORTRAITS_COUNT;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 1808
        UTIL_ASSERT(FALSE);
    }

    m_nCurrentPortrait = (m_nCurrentPortrait + 1) % nCount;
}

// NOTE: Inlined.
void CScreenCharacter::DecCurrentPortrait(CGameSprite* pSprite)
{
    INT nCount;
    switch (pSprite->m_startTypeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        nCount = CScreenCreateChar::MALE_PORTRAITS_COUNT;
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        nCount = CScreenCreateChar::FEMALE_PORTRAITS_COUNT;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 1851
        UTIL_ASSERT(FALSE);
    }

    m_nCurrentPortrait = (m_nCurrentPortrait + nCount - 1) % nCount;
}

// 0x5D7C10
void CScreenCharacter::ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sPortrait;

    m_nCurrentPortrait = 0;
    sPortrait = GetCurrentPortrait(pSprite);

    m_cResPortraitSmallTemp = sPortrait + "S";
    m_cResPortraitLargeTemp = sPortrait + "L";
}

// 0x5D7D30
void CScreenCharacter::UpdateAppearancePanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(18);
    if (pPanel != NULL) {
        CUIControlButtonCharacterPortrait* pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 1923
        UTIL_ASSERT(pPortrait != NULL);

        CResRef portraitResRef(GetCurrentPortrait(pSprite) + "L");
        pPortrait->SetPortrait(portraitResRef);
        pPortrait->InvalidateRect();

        CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(3));
        pDone->SetEnabled(IsDoneButtonClickable(pSprite));
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

    m_nPortraitSmallIndex = -1;
    m_nPortraitLargeIndex = -1;
    UpdatePortraitList(pPanel, 3, m_nPortraitSmallIndex);
    UpdatePortraitList(pPanel, 2, m_nPortraitLargeIndex);

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

// 0x5D7F70
void CScreenCharacter::UpdateCustomPortraitsPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(19);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(4));

    if (pPanel != NULL) {
        CString sPortrait;
        CUIControlButtonCharacterPortrait* pPortrait;

        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 2015
        UTIL_ASSERT(pGame != NULL);

        pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 2019
        UTIL_ASSERT(pPortrait != NULL);

        sPortrait = "";
        if (m_nPortraitSmallIndex >= 0) {
            POSITION pos = m_pPortraits->FindIndex(m_nPortraitSmallIndex);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 2024
            UTIL_ASSERT(pos != NULL);

            sPortrait = m_pPortraits->GetAt(pos);
        }

        pPortrait->SetPortrait(sPortrait);

        UpdateLabel(pPanel, 0x10000006, "%s", (LPCSTR)sPortrait);

        pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 2032
        UTIL_ASSERT(pPortrait != NULL);

        sPortrait = "";
        if (m_nPortraitLargeIndex >= 0) {
            POSITION pos = m_pPortraits->FindIndex(m_nPortraitLargeIndex);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 2037
            UTIL_ASSERT(pos != NULL);

            sPortrait = m_pPortraits->GetAt(pos);
        }

        pPortrait->SetPortrait(sPortrait);

        UpdateLabel(pPanel, 0x10000005, "%s", (LPCSTR)sPortrait);

        CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(10));
        pDone->SetEnabled(IsDoneButtonClickable(pSprite));
    }
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

// FIXME: `sName` should be reference.
//
// 0x5D87F0
BOOLEAN CScreenCharacter::IsNameOnExportList(CString sName)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2472
    UTIL_ASSERT(m_pCharacters != NULL);

    CString sExistingName;

    POSITION pos = m_pCharacters->GetHeadPosition();
    while (pos != NULL) {
        // FIXME: Unnecessary copy.
        sExistingName = m_pCharacters->GetAt(pos);

        if (sExistingName == sName) {
            return TRUE;
        }

        m_pCharacters->GetNext(pos);
    }

    return FALSE;
}

// 0x5D88E0
void CScreenCharacter::ResetBiographyPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(12);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2658
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2661
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    CString sBiography;

    sBiography = FetchString(pSprite->GetBaseStats()->m_biography);

    pText->DisplayString(CString(""),
        sBiography,
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        TRUE);
}

// 0x5D8A10
void CScreenCharacter::ResetClassDescriptionPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(52);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2729
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2732
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    CString sDescription;

    BYTE nBestClass = pSprite->GetDerivedStats()->GetBestClass();
    STRREF strDescription = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetClassDescriptionStringRef(nBestClass, 0);
    sDescription = FetchString(strDescription);

    pText->DisplayString(CString(""),
        sDescription,
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        TRUE);
}

// 0x5DAA40
void CScreenCharacter::UpdateAbilitiesPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(7);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(28));

    HighlightLabel(pPanel,
        0x10000002,
        m_nExtraAbilityPoints > 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel,
        0x10000002,
        "%d",
        m_nExtraAbilityPoints);

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // STR
    UpdateLabel(pPanel,
        0x10000003,
        "%d",
        pSprite->m_baseStats.m_STRBase);
    UpdateLabel(pPanel,
        0x10000024,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_STRBase));
    HighlightLabel(pPanel,
        0x10000024,
        pSprite->m_baseStats.m_STRBase != 10 && pSprite->m_baseStats.m_STRBase != 11,
        pSprite->m_baseStats.m_STRBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    // DEX
    UpdateLabel(pPanel,
        0x10000004,
        "%d",
        pSprite->m_baseStats.m_DEXBase);
    UpdateLabel(pPanel,
        0x10000025,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_DEXBase));
    HighlightLabel(pPanel,
        0x10000025,
        pSprite->m_baseStats.m_DEXBase != 10 && pSprite->m_baseStats.m_DEXBase != 11,
        pSprite->m_baseStats.m_DEXBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    // CON
    UpdateLabel(pPanel,
        0x10000005,
        "%d",
        pSprite->m_baseStats.m_CONBase);
    UpdateLabel(pPanel,
        0x10000026,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CONBase));
    HighlightLabel(pPanel,
        0x10000026,
        pSprite->m_baseStats.m_CONBase != 10 && pSprite->m_baseStats.m_CONBase != 11,
        pSprite->m_baseStats.m_CONBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    // INT
    UpdateLabel(pPanel,
        0x10000006,
        "%d",
        pSprite->m_baseStats.m_INTBase);
    UpdateLabel(pPanel,
        0x10000027,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_INTBase));
    HighlightLabel(pPanel,
        0x10000027,
        pSprite->m_baseStats.m_INTBase != 10 && pSprite->m_baseStats.m_INTBase != 11,
        pSprite->m_baseStats.m_INTBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    // WIS
    UpdateLabel(pPanel,
        0x10000007,
        "%d",
        pSprite->m_baseStats.m_WISBase);
    UpdateLabel(pPanel,
        0x10000028,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_WISBase));
    HighlightLabel(pPanel,
        0x10000028,
        pSprite->m_baseStats.m_WISBase != 10 && pSprite->m_baseStats.m_WISBase != 11,
        pSprite->m_baseStats.m_WISBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    // CHR
    UpdateLabel(pPanel,
        0x10000008,
        "%d",
        pSprite->m_baseStats.m_CHRBase);
    UpdateLabel(pPanel,
        0x10000029,
        "%+d",
        ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CHRBase));
    HighlightLabel(pPanel,
        0x10000029,
        pSprite->m_baseStats.m_CHRBase != 10 && pSprite->m_baseStats.m_CHRBase != 11,
        pSprite->m_baseStats.m_CHRBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 3664
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable(pSprite));

    for (INT nIndex = 0; nIndex < 12; nIndex += 2) {
        CUIControlButton* pButton;

        BOOL bCanInc = m_nExtraAbilityPoints != 0;
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(16 + nIndex));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 3685
        UTIL_ASSERT(pButton != NULL);

        pButton->SetActive(bCanInc);
        pButton->SetEnabled(bCanInc);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(17 + nIndex));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 3685
        UTIL_ASSERT(pButton != NULL);

        BOOL bCanDec;
        switch (nIndex) {
        case 0:
            bCanDec = m_pTempBaseStats->m_STRBase < pSprite->m_baseStats.m_STRBase;
            break;
        case 2:
            bCanDec = m_pTempBaseStats->m_DEXBase < pSprite->m_baseStats.m_DEXBase;
            break;
        case 4:
            bCanDec = m_pTempBaseStats->m_CONBase < pSprite->m_baseStats.m_CONBase;
            break;
        case 6:
            bCanDec = m_pTempBaseStats->m_INTBase < pSprite->m_baseStats.m_INTBase;
            break;
        case 8:
            bCanDec = m_pTempBaseStats->m_WISBase < pSprite->m_baseStats.m_WISBase;
            break;
        case 10:
            bCanDec = m_pTempBaseStats->m_CHRBase < pSprite->m_baseStats.m_CHRBase;
            break;
        }

        pButton->SetActive(bCanDec);
        pButton->SetEnabled(bCanDec);
    }
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

// 0x5D8300
void CScreenCharacter::ResetCustomSoundsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sSound;
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2137
    UTIL_ASSERT(pGame != NULL);

    m_pSounds = pGame->GetSounds();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2146
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(45));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 2148
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;
    pText->field_A68 = 32767;

    INT nIndex = 0;
    POSITION pos = m_pSounds->GetHeadPosition();
    while (pos != NULL) {
        // FIXME: Unnecessary copy.
        sSound = m_pSounds->GetAt(pos);
        pText->DisplayString(CString(""),
            sSound,
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            nIndex,
            FALSE,
            TRUE);

        m_pSounds->GetNext(pos);
        nIndex++;
    }

    pos = pText->m_plstStrings->FindIndex(0);
    pText->SetTopString(pos);

    m_nCustomSoundSetIndex = -1;
    m_nCustomSoundIndex = 3;

    UpdateHelp(pPanel->m_nID, 8, 11315);
}

// 0x5DBA80
void CScreenCharacter::TimerSynchronousUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    pGame->SynchronousUpdate();

    field_17A4 = g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL;

    if (m_lPopupStack.GetCount() > 0 && m_cUIManager.field_2E == 1) {
        SHORT nPortrait;

        for (nPortrait = 0; nPortrait <= 5; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }

        for (nPortrait = 50; nPortrait <= 55; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }
    }

    field_17A4 = FALSE;

    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x5DB950
void CScreenCharacter::GetPartyInformation(DWORD& nPartyChapterKillsXPValue, DWORD& nPartyChapterKillsNumber, DWORD& nPartyGameKillsXPValue, DWORD& nPartyGameKillsNumber)
{
    nPartyChapterKillsXPValue = 0;
    nPartyChapterKillsNumber = 0;
    nPartyGameKillsXPValue = 0;
    nPartyGameKillsNumber = 0;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 4093
    UTIL_ASSERT(pGame != NULL);

    for (SHORT nIndex = 0; nIndex < pGame->GetNumCharacters(); nIndex) {
        LONG nCharacterId = pGame->GetCharacterId(nIndex);

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            nPartyChapterKillsXPValue += pSprite->m_cGameStats.m_nChapterKillsXPValue;
            nPartyChapterKillsNumber += pSprite->m_cGameStats.m_nChapterKillsNumber;

            nPartyGameKillsXPValue += pSprite->m_cGameStats.m_nGameKillsXPValue;
            nPartyGameKillsNumber += pSprite->m_cGameStats.m_nGameKillsNumber;

            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
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

// 0x5E1F50
BOOL CScreenCharacter::IsDoneButtonClickable(CGameSprite* pSprite)
{
    // TODO: Incomplete.

    return FALSE;
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

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
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
    g_pBaldurChitin->GetTlkTable().Fetch(m_dwErrorTextId, strRes);

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

// NOTE: Inlined.
INT CScreenCharacter::GetNumHatedRaces()
{
    return CSCREENCHARACTER_NUM_HATEDRACES;
}

// NOTE: Uninline.
void CScreenCharacter::SetTopHatedRace(INT nTopHatedRace)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10613
    UTIL_ASSERT(0 <= nTopHatedRace && nTopHatedRace <= GetNumHatedRaces());

    m_nTopHatedRace = nTopHatedRace;
}

// NOTE: Uninline.
BYTE CScreenCharacter::GetHatedRace(INT nIndex)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10639
    UTIL_ASSERT(0 <= nIndex && nIndex < CSCREENCHARACTER_NUM_HATEDRACES);

    return m_hatedRaces[nIndex];
}

// 0x5E94C0
void CScreenCharacter::CheckMultiPlayerViewableModifyable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11144
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        m_bMultiPlayerViewable = g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
            ? g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID
            : TRUE;
        m_bMultiPlayerModifyable = m_bMultiPlayerViewable;

        if (!pSprite->Orderable(TRUE)) {
            m_bMultiPlayerViewable = FALSE;
        }

        if (!m_bMultiPlayerViewable) {
            if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                m_bMultiPlayerViewable = g_pBaldurChitin->cNetwork.GetSessionHosting()
                    || pGame->m_singlePlayerPermissions.GetSinglePermission(CGamePermission::LEADER)
                    || pGame->m_singlePlayerPermissions.GetSinglePermission(CGamePermission::CHAR_RECORDS);
            }
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5E9600
void CScreenCharacter::OnCustomizeButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11209
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
        m_cResPortraitSmall = pSprite->GetBaseStats()->m_portraitSmall;
        m_cResPortraitLarge = pSprite->GetBaseStats()->m_portraitLarge;
        m_cResPortraitSmallTemp = m_cResPortraitSmall;
        m_cResPortraitLargeTemp = m_cResPortraitLarge;
        m_cResSoundSet = pSprite->m_secondarySounds;
        field_856 = pSprite->field_725A;

        if (pSprite->field_402 != NULL) {
            pSprite->field_402->m_cResRef.CopyToString(field_832);
            field_832.MakeUpper();
        } else {
            field_832 = "NONE";
        }

        SummonPopup(17, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
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

// 0x5E9A20
void CScreenCharacter::OnPortraitLargeItemSelect(INT nItem)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11436
    UTIL_ASSERT(pGame != NULL);

    // FIXME: What for?
    SHORT nPortrait = g_pBaldurChitin->m_pEngineCharacter->GetSelectedCharacter();

    // NOTE: Uninline.
    INT nGameSprite = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (nItem != m_nPortraitLargeIndex) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11456
            UTIL_ASSERT(m_pPortraits != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(19);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11460
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11462
            UTIL_ASSERT(pText != NULL);

            if (m_nPortraitLargeIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nPortraitLargeIndex),
                    pText->m_rgbTextColor);
            }

            m_nPortraitLargeIndex = nItem;

            if (m_nPortraitLargeIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nPortraitLargeIndex),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
            }

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5E9BD0
void CScreenCharacter::OnPortraitSmallItemSelect(INT nItem)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11512
    UTIL_ASSERT(pGame != NULL);

    // FIXME: What for?
    SHORT nPortrait = g_pBaldurChitin->m_pEngineCharacter->GetSelectedCharacter();

    // NOTE: Uninline.
    INT nGameSprite = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (nItem != m_nPortraitSmallIndex) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11532
            UTIL_ASSERT(m_pPortraits != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(19);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11536
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 11538
            UTIL_ASSERT(pText != NULL);

            if (m_nPortraitSmallIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nPortraitSmallIndex),
                    pText->m_rgbTextColor);
            }

            m_nPortraitSmallIndex = nItem;

            if (m_nPortraitSmallIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nPortraitSmallIndex),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
            }

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5E9D80
void CScreenCharacter::OnCustomPortraitsButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11592
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
        SummonPopup(19, pSprite, 1);

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E9E90
void CScreenCharacter::OnPlayButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    INT nGameSprite = pGame->GetCharacterId(m_nSelectedCharacter);

    // NOTE: Unused.
    STR_RES strRes;

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (m_pSounds->FindIndex(m_nCustomSoundSetIndex) != NULL) {
            // NOTE: Unused.
            CString v2;

            CString sSuffix;
            CString sSoundSetName;
            CString sDirName;
            CString sBaseName;

            int v1 = m_nCustomSoundIndex;

            while (1) {
                if (m_nCustomSoundSetIndex != -1) {
                    POSITION pos = m_pSounds->FindIndex(m_nCustomSoundSetIndex);
                    if (pos != NULL) {
                        sSoundSetName = m_pSounds->GetAt(pos);
                    }
                }

                memcpy(pSprite->field_725A,
                    sSoundSetName.GetBuffer(sSoundSetName.GetLength()),
                    min(sSoundSetName.GetLength(), 32));

                if (sSoundSetName.GetLength() < 32) {
                    pSprite->field_725A[sSoundSetName.GetLength()] = '\0';
                }

                sDirName = g_pBaldurChitin->GetObjectGame()->GetDirSounds() + sSoundSetName + '\\';

                g_pBaldurChitin->cDimm.AddToDirectoryList(sDirName, TRUE);

                CString sFileName;
                CString sPattern;

                sPattern = g_pBaldurChitin->GetObjectGame()->GetDirSounds() + "\\" + sSoundSetName + "\\*.wav";

                WIN32_FIND_DATAA findFileData;
                HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
                if (hFindFile != INVALID_HANDLE_VALUE) {
                    sFileName = findFileData.cFileName;

                    if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                        sFileName.MakeUpper();
                        sFileName = sFileName.SpanExcluding(".");
                        sFileName = sFileName.Left(sFileName.GetLength() - 2);
                        sBaseName = sFileName;
                    }

                    // FIXME: Leaking `hFindFile`.
                }

                if (m_nCustomSoundIndex < 10) {
                    sSuffix.Format("0%d", m_nCustomSoundIndex);
                } else {
                    sSuffix.Format("%d", m_nCustomSoundIndex);
                }

                sFileName = sBaseName + sSuffix;

                if (m_nCustomSoundIndex == 40) {
                    m_nCustomSoundIndex = 0;
                } else {
                    m_nCustomSoundIndex++;
                }

                if (m_nCustomSoundIndex == 30) {
                    m_nCustomSoundIndex = 34;
                }

                CSound cSound(CResRef(sFileName), 0, 0, 0, INT_MAX, FALSE);
                cSound.SetFireForget(TRUE);

                if (cSound.GetRes() != NULL) {
                    cSound.Play(FALSE);
                    break;
                }

                if (v1 == m_nCustomSoundIndex) {
                    break;
                }
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5EA480
void CScreenCharacter::OnSoundItemSelect(INT nItem)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // NOTE: Uninline.
    INT nGameSprite = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (nItem != m_nCustomSoundSetIndex) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 12046
            UTIL_ASSERT(m_pSounds != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(20);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 12050
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(5));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 12052
            UTIL_ASSERT(pText != NULL);

            if (m_nCustomSoundSetIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nCustomSoundSetIndex),
                    pText->m_rgbTextColor);
            }

            m_nCustomSoundSetIndex = nItem;

            if (m_nCustomSoundSetIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nCustomSoundSetIndex),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
            }

            m_nCustomSoundIndex = 3;

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5ED4A0
CUIControlButtonCharacterSpecializationSelection::CUIControlButtonCharacterSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x5ED500
CUIControlButtonCharacterSpecializationSelection::~CUIControlButtonCharacterSpecializationSelection()
{
}

// 0x5ED5A0
DWORD CUIControlButtonCharacterSpecializationSelection::GetSpecialization()
{
    BYTE nClass = g_pBaldurChitin->m_pEngineCharacter->m_nClass;

    switch (nClass) {
    case CAIOBJECTTYPE_C_WIZARD:
        switch (m_nID) {
        case 2:
            return SPECMASK_WIZARD_UNIVERSAL;
        case 3:
            return SPECMASK_WIZARD_ABJURER;
        case 4:
            return SPECMASK_WIZARD_CONJURER;
        case 5:
            return SPECMASK_WIZARD_DIVINER;
        case 6:
            return SPECMASK_WIZARD_ENCHANTER;
        case 7:
            return SPECMASK_WIZARD_ILLUSIONIST;
        case 8:
            return SPECMASK_WIZARD_EVOKER;
        case 9:
            return SPECMASK_WIZARD_NECROMANCER;
        case 10:
            return SPECMASK_WIZARD_TRANSMUTER;
        }
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        switch (m_nID) {
        case 2:
            return SPECMASK_PALADIN_ILMATER;
        case 3:
            return SPECMASK_PALADIN_HELM;
        case 4:
            return SPECMASK_PALADIN_MYSTRA;
        }
        break;
    case CAIOBJECTTYPE_C_MONK:
        switch (m_nID) {
        case 2:
            return SPECMASK_MONK_OLD_ORDER;
        case 3:
            return SPECMASK_MONK_BROKEN_ONES;
        case 4:
            return SPECMASK_MONK_DARK_MOON;
        }
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (m_nID) {
        case 2:
            return SPECMASK_CLERIC_ILMATER;
        case 3:
            return SPECMASK_CLERIC_LATHANDER;
        case 4:
            return SPECMASK_CLERIC_SELUNE;
        case 5:
            return SPECMASK_CLERIC_HELM;
        case 6:
            return SPECMASK_CLERIC_OGHMA;
        case 7:
            return SPECMASK_CLERIC_TEMPUS;
        case 8:
            return SPECMASK_CLERIC_BANE;
        case 9:
            return SPECMASK_CLERIC_MASK;
        case 10:
            return SPECMASK_CLERIC_TALOS;
        }
    }

    return 0;
}

// 0x5ED6F0
void CUIControlButtonCharacterSpecializationSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    INT nGameSprite = g_pBaldurChitin->GetObjectGame()->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        DWORD nSpecialization = GetSpecialization();

        // TODO: Looks odd.
        pCharacter->m_nSpecialization = nSpecialization | static_cast<WORD>(pCharacter->field_77C);

        STRREF strDescription;
        switch (nSpecialization) {
        case SPECMASK_CLERIC_ILMATER:
            strDescription = 38118;
            break;
        case SPECMASK_CLERIC_LATHANDER:
            strDescription = 38119;
            break;
        case SPECMASK_CLERIC_SELUNE:
            strDescription = 38120;
            break;
        case SPECMASK_CLERIC_HELM:
            strDescription = 38121;
            break;
        case SPECMASK_CLERIC_OGHMA:
            strDescription = 38122;
            break;
        case SPECMASK_CLERIC_TEMPUS:
            strDescription = 38123;
            break;
        case SPECMASK_CLERIC_BANE:
            strDescription = 38124;
            break;
        case SPECMASK_CLERIC_MASK:
            strDescription = 38125;
            break;
        case SPECMASK_CLERIC_TALOS:
            strDescription = 38126;
            break;
        case SPECMASK_MONK_OLD_ORDER:
            strDescription = 39410;
            break;
        case SPECMASK_MONK_BROKEN_ONES:
            strDescription = 39411;
            break;
        case SPECMASK_MONK_DARK_MOON:
            strDescription = 39412;
            break;
        case SPECMASK_PALADIN_ILMATER:
            strDescription = 39407;
            break;
        case SPECMASK_PALADIN_HELM:
            strDescription = 39408;
            break;
        case SPECMASK_PALADIN_MYSTRA:
            strDescription = 39409;
            break;
        case SPECMASK_WIZARD_ABJURER:
            strDescription = 9564;
            break;
        case SPECMASK_WIZARD_CONJURER:
            strDescription = 9565;
            break;
        case SPECMASK_WIZARD_DIVINER:
            strDescription = 9566;
            break;
        case SPECMASK_WIZARD_ENCHANTER:
            strDescription = 9567;
            break;
        case SPECMASK_WIZARD_ILLUSIONIST:
            strDescription = 9568;
            break;
        case SPECMASK_WIZARD_EVOKER:
            strDescription = 9569;
            break;
        case SPECMASK_WIZARD_NECROMANCER:
            strDescription = 9570;
            break;
        case SPECMASK_WIZARD_TRANSMUTER:
            strDescription = 9571;
            break;
        case SPECMASK_WIZARD_UNIVERSAL:
            strDescription = 9563;
        }

        pCharacter->UpdateHelp(m_pPanel->m_nID, 13, strDescription);
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5ED9D0
CUIControlButtonCharacterAbilitiesPlusMinus::CUIControlButtonCharacterAbilitiesPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x5EDA10
CUIControlButtonCharacterAbilitiesPlusMinus::~CUIControlButtonCharacterAbilitiesPlusMinus()
{
}

// 0x619220
BOOL CUIControlButtonCharacterAbilitiesPlusMinus::OnLButtonDown(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14242
    UTIL_ASSERT(pCharacter != NULL);

    CString sValue;

    STRREF strHelp;
    BYTE nMin;
    BYTE nMax;
    switch (m_nID) {
    case 16:
    case 17:
        strHelp = 9582;
        nMin = pCharacter->m_nMinSTR;
        nMax = pCharacter->m_nMaxSTR;
        break;
    case 18:
    case 19:
        strHelp = 9584;
        nMin = pCharacter->m_nMinDEX;
        nMax = pCharacter->m_nMaxDEX;
        break;
    case 20:
    case 21:
        strHelp = 9583;
        nMin = pCharacter->m_nMinCON;
        nMax = pCharacter->m_nMaxCON;
        break;
    case 22:
    case 23:
        strHelp = 9585;
        nMin = pCharacter->m_nMinINT;
        nMax = pCharacter->m_nMaxINT;
        break;
    case 24:
    case 25:
        strHelp = 9586;
        nMin = pCharacter->m_nMinWIS;
        nMax = pCharacter->m_nMaxWIS;
        break;
    case 26:
    case 27:
        strHelp = 9587;
        nMin = pCharacter->m_nMinCHR;
        nMax = pCharacter->m_nMaxCHR;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 14288
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    sValue.Format("%d", nMin);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

    pCharacter->UpdateHelp(m_pPanel->m_nID, 29, strHelp);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
}

// 0x5EDD50
void CUIControlButtonCharacterAbilitiesPlusMinus::AdjustValue()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    INT nGameSprite = pCharacter->field_1840;

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        BYTE nMin;
        BYTE nMax;
        BYTE* pBase;
        BYTE* pValue;
        BOOL bInc;
        switch (m_nID) {
        case 16:
        case 17:
            nMin = pCharacter->m_nMinSTR;
            nMax = pCharacter->m_nMaxSTR;
            pBase = &(pCharacter->m_pTempBaseStats->m_STRBase);
            pValue = &(pSprite->GetBaseStats()->m_STRBase);
            bInc = m_nID == 16;
            break;
        case 18:
        case 19:
            nMin = pCharacter->m_nMinDEX;
            nMax = pCharacter->m_nMaxDEX;
            pBase = &(pCharacter->m_pTempBaseStats->m_DEXBase);
            pValue = &(pSprite->GetBaseStats()->m_DEXBase);
            bInc = m_nID == 18;
            break;
        case 20:
        case 21:
            nMin = pCharacter->m_nMinCON;
            nMax = pCharacter->m_nMaxCON;
            pBase = &(pCharacter->m_pTempBaseStats->m_CONBase);
            pValue = &(pSprite->GetBaseStats()->m_CONBase);
            bInc = m_nID == 20;
            break;
        case 22:
        case 23:
            nMin = pCharacter->m_nMinINT;
            nMax = pCharacter->m_nMaxINT;
            pBase = &(pCharacter->m_pTempBaseStats->m_INTBase);
            pValue = &(pSprite->GetBaseStats()->m_INTBase);
            bInc = m_nID == 22;
            break;
        case 24:
        case 25:
            nMin = pCharacter->m_nMinWIS;
            nMax = pCharacter->m_nMaxWIS;
            pBase = &(pCharacter->m_pTempBaseStats->m_WISBase);
            pValue = &(pSprite->GetBaseStats()->m_WISBase);
            bInc = m_nID == 24;
            break;
        case 26:
        case 27:
            nMin = pCharacter->m_nMinCHR;
            nMax = pCharacter->m_nMaxCHR;
            pBase = &(pCharacter->m_pTempBaseStats->m_CHRBase);
            pValue = &(pSprite->GetBaseStats()->m_CHRBase);
            bInc = m_nID == 26;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 14431
            UTIL_ASSERT(FALSE);
        }

        if (bInc) {
            if (pCharacter->m_nExtraAbilityPoints > 0) {
                if (*pValue < nMax) {
                    (*pValue)++;
                    pCharacter->m_nExtraAbilityPoints--;
                    pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
                } else {
                    pCharacter->UpdateHelp(m_pPanel->m_nID, 29, 14838);
                }
            }
        } else {
            if (*pValue > *pBase) {
                if (*pBase > nMin) {
                    (*pBase)--;
                    pCharacter->m_nExtraAbilityPoints++;
                    pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
                } else {
                    pCharacter->UpdateHelp(m_pPanel->m_nID, 29, 14840);
                }
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5EE000
void CUIControlButtonCharacterAbilitiesHotArea::OnHotAreaClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14501
    UTIL_ASSERT(pCharacter != NULL);

    CString sValue;
    DWORD strDescription;
    BYTE nMin;
    BYTE nMax;
    switch (m_nID) {
    case 30:
        strDescription = 9582;
        nMin = pCharacter->m_nMinSTR;
        nMax = pCharacter->m_nMaxSTR;
        break;
    case 31:
        strDescription = 9584;
        nMin = pCharacter->m_nMinDEX;
        nMax = pCharacter->m_nMaxDEX;
        break;
    case 32:
        strDescription = 9583;
        nMin = pCharacter->m_nMinCON;
        nMax = pCharacter->m_nMaxCON;
        break;
    case 33:
        strDescription = 9585;
        nMin = pCharacter->m_nMinINT;
        nMax = pCharacter->m_nMaxINT;
        break;
    case 34:
        strDescription = 9586;
        nMin = pCharacter->m_nMinWIS;
        nMax = pCharacter->m_nMaxWIS;
        break;
    case 35:
        strDescription = 9587;
        nMin = pCharacter->m_nMinCHR;
        nMax = pCharacter->m_nMaxCHR;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 14541
        UTIL_ASSERT(FALSE);
    }

    sValue.Format("%d", nMin);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

    pCharacter->UpdateHelp(m_pPanel->m_nID, 29, strDescription);
}

// -----------------------------------------------------------------------------

// 0x5EE210
CUIControlScrollBarCharacterHatedRace::CUIControlScrollBarCharacterHatedRace(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarCharacterHatedRace::~CUIControlScrollBarCharacterHatedRace()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharacterHatedRace::UpdateScrollBar()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14602
    UTIL_ASSERT(pCharacter != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14604
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pCharacter->m_nTopHatedRace, CSCREENCREATECHAR_NUM_HATEDRACES, 11);
}

// 0x5EE230
void CUIControlScrollBarCharacterHatedRace::OnScrollUp()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14634
    UTIL_ASSERT(pCharacter != NULL);

    INT nTopHatedRace = max(pCharacter->m_nTopHatedRace - 1, 0);

    if (nTopHatedRace != pCharacter->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCharacter->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5EE310
void CUIControlScrollBarCharacterHatedRace::OnScrollDown()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14670
    UTIL_ASSERT(pCharacter != NULL);

    INT nTopHatedRace = min(pCharacter->m_nTopHatedRace + 1, 5);

    if (nTopHatedRace != pCharacter->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCharacter->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5EE3F0
void CUIControlScrollBarCharacterHatedRace::OnPageUp(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14706
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, 11);
    INT nTopHatedRace = max(pCharacter->m_nTopHatedRace - nStep, 0);

    if (nTopHatedRace != pCharacter->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCharacter->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5EE4F0
void CUIControlScrollBarCharacterHatedRace::OnPageDown(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14744
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, 11);
    INT nTopHatedRace = min(pCharacter->m_nTopHatedRace + nStep, 5);

    if (nTopHatedRace != pCharacter->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCharacter->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5EE5F0
void CUIControlScrollBarCharacterHatedRace::OnScroll()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14782
    UTIL_ASSERT(pCharacter != NULL);

    // NOTE: Uninline.
    pCharacter->SetTopHatedRace(5 * field_144 / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5EE6D0
void CUIControlScrollBarCharacterHatedRace::InvalidateItems()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14814
    UTIL_ASSERT(pCharacter != NULL);

    CSingleLock renderLock(&(pCharacter->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = g_pBaldurChitin->GetObjectGame()->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x5EE820
CUIControlButtonCharacterHatedRaceSelection::CUIControlButtonCharacterHatedRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nNotSelectedFrame = m_nNormalFrame;
    m_nSelectedFrame = 0;
}

// 0x5EE890
CUIControlButtonCharacterHatedRaceSelection::~CUIControlButtonCharacterHatedRaceSelection()
{
}

// 0x5EE930
void CUIControlButtonCharacterHatedRaceSelection::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 14903
    UTIL_ASSERT(pCharacter != NULL);

    INT nGameSprite = g_pBaldurChitin->GetObjectGame()->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        INT nIndex = pCharacter->m_nTopHatedRace + m_nID - 22;

        // NOTE: Uninline.
        pSprite->GetBaseStats()->m_favoredEnemies[pCharacter->field_17A0] = pCharacter->GetHatedRace(nIndex);

        STRREF strHelp;
        switch (pSprite->GetBaseStats()->m_favoredEnemies[pCharacter->field_17A0]) {
        case CAIOBJECTTYPE_R_OGRE:
            strHelp = 15998;
            break;
        case CAIOBJECTTYPE_R_WYVERN:
            strHelp = 37619;
            break;
        case CAIOBJECTTYPE_R_GIANT:
            strHelp = 3291;
            break;
        case CAIOBJECTTYPE_R_GOBLIN:
            strHelp = 3292;
            break;
        case CAIOBJECTTYPE_R_LIZARDMAN:
            strHelp = 3293;
            break;
        case CAIOBJECTTYPE_R_ORC:
            strHelp = 3294;
            break;
        case CAIOBJECTTYPE_R_SALAMANDER:
            strHelp = 3295;
            break;
        case CAIOBJECTTYPE_R_TROLL:
            strHelp = 3299;
            break;
        case CAIOBJECTTYPE_R_UMBERHULK:
            strHelp = 3300;
            break;
        case CAIOBJECTTYPE_R_UNDEAD:
            strHelp = 3297;
            break;
        case CAIOBJECTTYPE_R_YUANTI:
            strHelp = 3301;
            break;
        case CAIOBJECTTYPE_R_HARPY:
            strHelp = 37618;
            break;
        case CAIOBJECTTYPE_R_BUGBEAR:
            strHelp = 8032;
            break;
        case CAIOBJECTTYPE_R_HOOK_HORROR:
            strHelp = 37608;
            break;
        case CAIOBJECTTYPE_R_DRIDER:
            strHelp = 41079;
            break;
        case CAIOBJECTTYPE_R_SHAPESHIFTER:
            strHelp = 37609;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 15003
            UTIL_ASSERT(FALSE);
        }

        pCharacter->UpdateHelp(m_pPanel->m_nID, 8, strHelp);
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5EAC00
CUIControlButtonCharacterCustomize::CUIControlButtonCharacterCustomize(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(10645, strRes); // "Customize"
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
    g_pBaldurChitin->GetTlkTable().Fetch(11946, strRes); // "Information"
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
    g_pBaldurChitin->GetTlkTable().Fetch(13956, strRes); // "Export"
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
    g_pBaldurChitin->GetTlkTable().Fetch(7175, strRes); // "Level Up"
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
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes); // "Done"
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

// -----------------------------------------------------------------------------

// 0x5EBA90
CUIControlButtonInformationBiography::CUIControlButtonInformationBiography(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(18003, strRes); // "Biography"
    SetText(strRes.szText);
}

// 0x5EBB80
CUIControlButtonInformationBiography::~CUIControlButtonInformationBiography()
{
}

// 0x5EBC20
void CUIControlButtonInformationBiography::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12874
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnBiographyButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EEBD0
CUIControlButtonCharacterCustomizeMenu::CUIControlButtonCharacterCustomizeMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15039
    UTIL_ASSERT(pCharacter != NULL);

    STRREF dwText;
    switch (m_nID) {
    case 0:
        dwText = 11961; // "Appearance"
        break;
    case 1:
        dwText = 10647; // "Sounds"
        break;
    case 3:
        dwText = 17111; // "Script"
        break;
    case 4:
        dwText = 18003; // "Biography"
        break;
    default:
        dwText = -1;
        break;
    }
    SetText(CBaldurEngine::FetchString(dwText));
}

// 0x5EED00
CUIControlButtonCharacterCustomizeMenu::~CUIControlButtonCharacterCustomizeMenu()
{
}

// 0x5EEDA0
void CUIControlButtonCharacterCustomizeMenu::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15093
    UTIL_ASSERT(pCharacter != NULL);

    switch (m_nID) {
    case 0:
        pCharacter->OnAppearanceButtonClick();
        break;
    case 1:
        pCharacter->OnSoundsButtonClick();
        break;
    case 3:
        pCharacter->OnScriptButtonClick();
        break;
    case 9:
        pCharacter->OnCustomizeBiographyButtonClick();
        break;
    }
}

// -----------------------------------------------------------------------------

// 0x5EEE40
CUIControlTextDisplayCharacterPortraits::CUIControlTextDisplayCharacterPortraits(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayCharacterPortraits::~CUIControlTextDisplayCharacterPortraits()
{
}

// 0x5EEE70
void CUIControlTextDisplayCharacterPortraits::OnItemSelected(LONG lMarker)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15169
    UTIL_ASSERT(pCharacter != NULL);

    switch (m_nID) {
    case 2:
        pCharacter->OnPortraitLargeItemSelect(lMarker);
        break;
    case 3:
        pCharacter->OnPortraitSmallItemSelect(lMarker);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 15182
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x5EEEF0
void CUIControlButtonCharacterAppearanceLeft::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15211
    UTIL_ASSERT(pGame != NULL && pCharacter != NULL);

    INT nGameSprite = pGame->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CString sPortrait;
        CResRef portraitResRef;

        pCharacter->DecCurrentPortrait(pSprite);
        sPortrait = pCharacter->GetCurrentPortrait(pSprite);

        pCharacter->m_cResPortraitSmallTemp = sPortrait + "S";
        pCharacter->m_cResPortraitLargeTemp = sPortrait + "L";

        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x5EF130
void CUIControlButtonCharacterAppearanceRight::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15273
    UTIL_ASSERT(pGame != NULL && pCharacter != NULL);

    INT nGameSprite = pGame->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CString sPortrait;
        CResRef portraitResRef;

        pCharacter->IncCurrentPortrait(pSprite);
        sPortrait = pCharacter->GetCurrentPortrait(pSprite);

        pCharacter->m_cResPortraitSmallTemp = sPortrait + "S";
        pCharacter->m_cResPortraitLargeTemp = sPortrait + "L";

        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5EF370
CUIControlButtonCharacterAppearanceCustom::CUIControlButtonCharacterAppearanceCustom(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(17545, strRes); // "Custom"
    SetText(strRes.szText);
}

// 0x5EF460
CUIControlButtonCharacterAppearanceCustom::~CUIControlButtonCharacterAppearanceCustom()
{
}

// 0x5EF500
void CUIControlButtonCharacterAppearanceCustom::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15363
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnCustomPortraitsButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EF540
CUIControlButtonCharacterSoundPlay::CUIControlButtonCharacterSoundPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15391
    UTIL_ASSERT(pCharacter != NULL);

    SetText(CBaldurEngine::FetchString(17318));
}

// 0x5EF610
CUIControlButtonCharacterSoundPlay::~CUIControlButtonCharacterSoundPlay()
{
}

// 0x5EF6B0
void CUIControlButtonCharacterSoundPlay::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15418
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnPlayButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EF6F0
CUIControlTextDisplayCharacterSoundSounds::CUIControlTextDisplayCharacterSoundSounds(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayCharacterSoundSounds::~CUIControlTextDisplayCharacterSoundSounds()
{
}

// 0x5EF720
void CUIControlTextDisplayCharacterSoundSounds::OnItemSelected(LONG lMarker)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 15472
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnSoundItemSelect(lMarker);
}

#include "CScreenCreateChar.h"

#include "CBaldurChitin.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CUIControlFactory.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define SKILL_COUNT 16
#define SKILL_SLOTS 10

#define FEAT_COUNT 75
#define FEAT_SLOTS 10

// 0x8539E0
const char* CScreenCreateChar::MALE_PORTRAITS[] = {
    "2MELF1_",
    "2MAAS1_",
    "2MBAR1_",
    "2MDEF1_",
    "2MDEF2_",
    "2MGNM1_",
    "2MHAF1_",
    "2MHUM1_",
    "2MHUM2_",
    "2MHUM3_",
    "2MHUM4_",
    "2MHUM5_",
    "2MHUM6_",
    "2MHUM7_",
    "2MPAL1_",
    "2MORC1_",
    "2MDWF1_",
    "2MDWF2_",
    "DMC_",
    "DMF_",
    "DMF2_",
    "DMT_",
    "EMC_",
    "EMF_",
    "EMF2_",
    "EMT_",
    "EMW_",
    "GMT_",
    "GMW_",
    "HaMF_",
    "HaMT_",
    "HeMF_",
    "HeMT_",
    "HeMW_",
    "HMC_",
    "HMC2_",
    "HMC3_",
    "HMC4_",
    "HMF_",
    "HMF2_",
    "HMF3_",
    "HMF4_",
    "HMF5_",
    "HMF6_",
    "HMF7_",
    "HMW_",
    "HMW2_",
    "HMW3_",
    "HMW4_",
    "HMB_",
    "HMB2_",
};

// 0x853AB0
const char* CScreenCreateChar::FEMALE_PORTRAITS[] = {
    "2FBAR1_",
    "2FDEF1_",
    "2FELF1_",
    "2FELF2_",
    "2FELF3_",
    "2FGNM1_",
    "2FHUM1_",
    "2FHUM2_",
    "2FHUM3_",
    "2FHUM4_",
    "2FTIF1_",
    "2FORC1_",
    "DFF_",
    "EFC_",
    "EFF_",
    "EFW_",
    "EFW2_",
    "GFW_",
    "HaFF_",
    "HeFC_",
    "HaFT_",
    "HeFB_",
    "HeFF_",
    "HeFW_",
    "HFD_",
    "HFF_",
    "HFF2_",
    "HFT_",
    "HFT2_",
    "HFW_",
    "HFW2_",
    "HFW3_",
};

// 0x8F3B7C
const CString CScreenCreateChar::NUMBER("number");

// 0x8F3B94
const CString CScreenCreateChar::TOKEN_MINIMUM("MINIMUM");

// 0x8F3B98
const CString CScreenCreateChar::TOKEN_MAXIMUM("MAXIMUM");

// 0x605C40
CScreenCreateChar::CScreenCreateChar()
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenCreateChar::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x606C60
void CScreenCreateChar::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x49FC40
BOOL CScreenCreateChar::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x606C80
BOOL CScreenCreateChar::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x606C90
void CScreenCreateChar::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x49FC40
BOOL CScreenCreateChar::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x606CA0
void CScreenCreateChar::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x606CB0
BOOL CScreenCreateChar::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x699600
SHORT CScreenCreateChar::GetNumVirtualKeys()
{
    return CSCREENCREATECHAR_VIRTUAL_KEYS;
}

// 0x606CC0
CKeyInfo* CScreenCreateChar::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x606CD0
BYTE* CScreenCreateChar::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x606D00
CScreenCreateChar::~CScreenCreateChar()
{
    // TODO: Incomplete.
}

// 0x606F50
void CScreenCreateChar::EngineActivated()
{
    INT nGameSprite = GetSpriteId();

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        UpdateMainPanel(pSprite);
        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    UpdateCursorShape(0);
    m_cUIManager.InvalidateRect(NULL);
}

// 0x607070
void CScreenCreateChar::EngineDeactivated()
{
    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x5D72C0
void CScreenCreateChar::EngineDestroyed()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x6070B0
void CScreenCreateChar::EngineGameInit()
{
    field_14A4 = 0x4000;
    field_14A8 = 0;
}

// 0x6070D0
void CScreenCreateChar::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUICG"), g_pBaldurChitin->field_4A28);

    CPoint pt;
    if (g_pBaldurChitin->field_4A28) {
        pt.x = CVideo::SCREENWIDTH / 2 - CBaldurChitin::DEFAULT_SCREEN_WIDTH;
        pt.y = CVideo::SCREENHEIGHT / 2 - CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
    } else {
        pt.x = (CVideo::SCREENWIDTH - CBaldurChitin::DEFAULT_SCREEN_WIDTH) / 2;
        pt.y = (CVideo::SCREENHEIGHT - CBaldurChitin::DEFAULT_SCREEN_HEIGHT) / 2;
    }

    m_cUIManager.ShiftPanels(pt);

    for (int index = 0; index < 4; index++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->field_49B4[index]));
    }

    m_pCurrentScrollBar = NULL;

    m_cUIManager.GetPanel(1)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(53)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(16)->SetActive(FALSE);
    m_cUIManager.GetPanel(17)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(12)->SetActive(FALSE);
    m_cUIManager.GetPanel(11)->SetActive(FALSE);
    m_cUIManager.GetPanel(13)->SetActive(FALSE);
    m_cUIManager.GetPanel(14)->SetActive(FALSE);
    m_cUIManager.GetPanel(15)->SetActive(FALSE);
    m_cUIManager.GetPanel(18)->SetActive(FALSE);
    m_cUIManager.GetPanel(19)->SetActive(FALSE);
    m_cUIManager.GetPanel(20)->SetActive(FALSE);
    m_cUIManager.GetPanel(21)->SetActive(FALSE);
    m_cUIManager.GetPanel(51)->SetActive(FALSE);
    m_cUIManager.GetPanel(52)->SetActive(FALSE);
    m_cUIManager.GetPanel(54)->SetActive(FALSE);
    m_cUIManager.GetPanel(55)->SetActive(FALSE);
}

// 0x607380
void CScreenCreateChar::OnKeyDown(SHORT nKeysFlags)
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenCreateChar::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenCreateChar::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x6075C0
void CScreenCreateChar::OnLButtonDown(CPoint pt)
{
    m_cUIManager.OnLButtonDown(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
}

// 0x6075F0
void CScreenCreateChar::OnLButtonUp(CPoint pt)
{
    m_cUIManager.OnLButtonUp(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
}

// 0x49FC40
BOOL CScreenCreateChar::CheckMouseMove()
{
    return TRUE;
}

// 0x607620
void CScreenCreateChar::OnMouseMove(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenCreateChar::CheckMouseRButton()
{
    return TRUE;
}

// 0x6077E0
void CScreenCreateChar::OnRButtonDown(CPoint pt)
{
    m_cUIManager.OnRButtonDown(pt);
}

// 0x607800
void CScreenCreateChar::OnRButtonUp(CPoint pt)
{
    m_cUIManager.OnRButtonUp(pt);
}

// 0x607820
STRREF CScreenCreateChar::sub_607820(BYTE nRace)
{
    STRREF strRace;
    switch (nRace) {
    case 113:
        strRace = 15975;
        break;
    case 118:
        strRace = 37617;
        break;
    case 153:
        strRace = 3279;
        break;
    case 155:
        strRace = 3280;
        break;
    case 157:
        strRace = 3281;
        break;
    case 160:
        strRace = 3282;
        break;
    case 161:
        strRace = 3290;
        break;
    case 165:
        strRace = 3288;
        break;
    case 166:
        strRace = 3289;
        break;
    case 167:
        strRace = 3285;
        break;
    case 168:
        strRace = 30850;
        break;
    case 174:
        strRace = 37616;
        break;
    case 180:
        strRace = 28367;
        break;
    case 181:
        strRace = 37606;
        break;
    case 182:
        strRace = 37607;
        break;
    case 191:
        strRace = 37605;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 1183
        UTIL_ASSERT(FALSE);
    }
    return strRace;
}

// 0x607980
void CScreenCreateChar::TimerAsynchronousUpdate()
{
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        if (g_pChitin->cNetwork.MakePlayersVisible() == TRUE) {
            if (g_pChitin->cNetwork.GetSessionHosting()) {
                g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
            }
        }
    }

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x607A40
void CScreenCreateChar::TimerSynchronousUpdate()
{
    CUIPanel* pPanel = GetTopPopup();
    if (pPanel != NULL) {
        if (pPanel->m_nID == 13) {
            CUIControlBase* pControl = pPanel->GetControl(1);
            pControl->InvalidateRect();
        }
    }

    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x607A90
void CScreenCreateChar::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    CUIControlButton* pButton;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1289
    UTIL_ASSERT(pPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(15));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(13));
        pButton->SetEnabled(TRUE);
    } else {
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(15));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(13));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(16));
        pButton->SetEnabled(FALSE);
    }

    pPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }
}

// 0x607BB0
void CScreenCreateChar::UpdateMainPanel(CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x608AD0
void CScreenCreateChar::ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    switch (dwPanelId) {
    case 1:
        ResetGenderPanel(pPanel, pSprite);
        break;
    case 2:
        ResetClassPanel(pPanel, pSprite);
        break;
    case 3:
        ResetAlignmentPanel(pPanel, pSprite);
        break;
    case 4:
        AllocateAbilities(pSprite);
        UpdateHelp(pPanel->m_nID, 29, 17247);
        break;
    case 5:
        sub_609900(pPanel, pSprite);
        break;
    case 6:
        ResetSkillsPanel(pPanel, pSprite);
        break;
    case 7:
        sub_60A5C0(pPanel, pSprite);
        break;
    case 8:
        ResetRacePanel(pPanel, pSprite);
        break;
    case 11:
        ResetAppearancePanel(pPanel, pSprite);
        break;
    case 12:
        ResetClericWizardSpecializationPanel(pPanel, pSprite);
        break;
    case 13:
        sub_609B30(pPanel, pSprite);
        break;
    case 15:
        for (int index = 0; index < 8; index++) {
            pSprite->m_baseStats.m_favoredEnemies[index] = -1;
        }
        m_nTopHatedRace = 0;
        UpdateHelp(pPanel->m_nID, 8, 17256);
        break;
    case 16:
        sub_60A920(pPanel, pSprite);
        break;
    case 17:
        if (field_4D6) {
            sub_60B610(pPanel, pSprite);
        } else {
            sub_60AF60(pPanel, pSprite);
        }
        break;
    case 18:
        sub_609460(pPanel, pSprite);
        break;
    case 19:
        sub_609750(pPanel, pSprite);
        break;
    case 20:
        ResetImportPanel(pPanel, pSprite);
        break;
    case 21:
        ResetExportPanel(pPanel, pSprite);
        break;
    case 51:
        sub_609170(pPanel, pSprite);
        break;
    case 52:
        ResetMonkPaladinSpecializationPanel(pPanel, pSprite);
        break;
    case 53:
        ResetStartOverPanel(pPanel, pSprite);
        break;
    case 54:
        ResetSubRacePanel(pPanel, pSprite);
        break;
    case 55:
        ResetFeatsPanel(pPanel, pSprite);
        break;
    }
}

// 0x608DB0
void CScreenCreateChar::ResetExportPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1777
    UTIL_ASSERT(pGame != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1780
    UTIL_ASSERT(m_pCharacters == NULL);

    m_pCharacters = pGame->GetImportCharacters();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1782
    UTIL_ASSERT(m_pCharacters != NULL);

    m_nCharacterIndex = -1;
    UpdateCharacterList(pPanel, 2, m_nCharacterIndex);

    // TODO: Incomplete.

    UpdateHelp(pPanel->m_nID, 4, 10962);
}

// 0x608EA0
void CScreenCreateChar::ResetImportPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1821
    UTIL_ASSERT(pGame != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1824
    UTIL_ASSERT(m_pCharacters == NULL);

    m_pCharacters = pGame->GetImportCharacters();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1826
    UTIL_ASSERT(m_pCharacters != NULL);

    m_nCharacterIndex = -1;
    UpdateCharacterList(pPanel, 2, m_nCharacterIndex);

    UpdateHelp(pPanel->m_nID, 4, 10963);
}

// 0x608F50
void CScreenCreateChar::ResetMonkPaladinSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CUIControlButtonMonkPaladinSpecializationSelection* pButton = static_cast<CUIControlButtonMonkPaladinSpecializationSelection*>(pPanel->GetControl(1));

    CAIObjectType typeAI(pSprite->m_startTypeAI);
    UpdateHelp(pPanel->m_nID, 12, pButton->GetHelp(pSprite));

    for (INT nButton = 5; nButton <= 10; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton));
        pButton->SetEnabled(FALSE);
        pButton->SetActive(FALSE);
        pButton->SetInactiveRender(FALSE);
    }

    switch (typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_MONK:
        UpdateLabel(pPanel, 0x1000000A, "%s", FetchString(33));
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        UpdateLabel(pPanel, 0x1000000A, "%s", FetchString(1078));
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 1887
        UTIL_ASSERT(FALSE);
    }
}

// 0x6090C0
void CScreenCreateChar::ResetSubRacePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CUIControlButtonCharGenSubRaceSelection* pButton = static_cast<CUIControlButtonCharGenSubRaceSelection*>(pPanel->GetControl(1));
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_nSubRace = 0;
    pSprite->m_startTypeAI.Set(typeAI);
    UpdateHelp(pPanel->m_nID, 6, pButton->GetHelp(typeAI));
}

// 0x609170
void CScreenCreateChar::sub_609170(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x6092F0
void CScreenCreateChar::UpdateCharacterList(CUIPanel* pPanel, DWORD dwTextId, INT nSelected)
{
    CString sFileName;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2014
    UTIL_ASSERT(m_pCharacters != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2015
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2017
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

// 0x609460
void CScreenCreateChar::sub_609460(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x6095E0
void CScreenCreateChar::sub_6095E0()
{
    // TODO: Incomplete.
}

// 0x609750
void CScreenCreateChar::sub_609750(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x609900
void CScreenCreateChar::sub_609900(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x609A10
void CScreenCreateChar::ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x609B30
void CScreenCreateChar::sub_609B30(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60A4A0
void CScreenCreateChar::ResetClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);

    STRREF strDescription;
    switch (typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_WIZARD:
        strDescription = 10942;
        UpdateLabel(pPanel, 0x10000000, "%s", FetchString(1081));
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        strDescription = 9559;
        UpdateLabel(pPanel, 0x10000000, "%s", FetchString(1079));
        break;
    }

    UpdateHelp(pPanel->m_nID, 11, strDescription);
}

// 0x60A5C0
void CScreenCreateChar::sub_60A5C0(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60A920
void CScreenCreateChar::sub_60A920(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60AF60
void CScreenCreateChar::sub_60AF60(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60B610
void CScreenCreateChar::sub_60B610(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60BA30
void CScreenCreateChar::ResetClassPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60BB80
void CScreenCreateChar::sub_60BB80()
{
    // TODO: Incomplete.
}

// 0x60BBE0
void CScreenCreateChar::ResetGenderPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_nGender = 0;
    pSprite->m_startTypeAI.Set(typeAI);

    CUIControlButtonCharGenGenderSelection* pGender;

    pGender = static_cast<CUIControlButtonCharGenGenderSelection*>(pPanel->GetControl(2));
    pGender->SetText(FetchString(1050));

    pGender = static_cast<CUIControlButtonCharGenGenderSelection*>(pPanel->GetControl(3));
    pGender->SetText(FetchString(1051));

    UpdateHelp(pPanel->m_nID, 5, 17236);
}

// 0x60BCF0
void CScreenCreateChar::ResetRacePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_nRace = 0;
    typeAI.m_nSubRace = 0;
    pSprite->m_startTypeAI.Set(typeAI);

    UpdateHelp(pPanel->m_nID, 9, 17237);
}

// 0x60BD90
void CScreenCreateChar::ResetAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_nAlignment = 0;
    pSprite->m_startTypeAI.Set(typeAI);

    UpdateHelp(pPanel->m_nID, 11, 9602);
}

// 0x60BE30
BOOL CScreenCreateChar::ResetAbility(CGameSprite* pSprite, const CString& sMin, const CString& sMax, const CString& sMod, BYTE& nAbility, BYTE& nMin, BYTE& nMax, INT& nMod, BOOL bRandomize)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    INT nBestClass = pSprite->m_derivedStats.GetBestClass();

    const CString& sRace = pGame->m_ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    BYTE nMinRaceReq = static_cast<BYTE>(atol(pGame->m_ruleTables.m_tAbilityRaceReq.GetAt(sMin, sRace)));
    BYTE nMaxRaceReq = static_cast<BYTE>(atol(pGame->m_ruleTables.m_tAbilityRaceReq.GetAt(sMax, sRace)));
    BYTE nRaceAdj = static_cast<BYTE>(atol(pGame->m_ruleTables.m_tAbilityRaceAdj.GetAt(sMod, sRace)));

    const CString& sClass = pGame->m_ruleTables.GetClassString(nBestClass, pSprite->m_baseStats.m_specialization);
    BYTE nMinClassReq = static_cast<BYTE>(atol(pGame->m_ruleTables.m_tAbilityClassReq.GetAt(sMin, sClass)));

    if (bRandomize == TRUE) {
        INT v1 = 6;
        INT nValue = 0;
        INT nRolls = 3;

        while (nRolls > 0) {
            INT v2 = rand() % 6 + 1;
            nValue += v2;
            if (v2 < v1) {
                v1 = v2;
            }
            nRolls--;
        }
    } else {
        nAbility = static_cast<BYTE>(pGame->m_cOptions.field_CA);
    }

    BOOL bResult;
    if (nMinRaceReq > nAbility || nAbility > nMaxRaceReq) {
        bResult = FALSE;
    } else {
        bResult = nAbility + nRaceAdj >= nMinClassReq;
    }

    if (!bResult) {
        if (!bRandomize) {
            if (nAbility < nMinRaceReq) {
                nAbility = nMinRaceReq;
            }

            if (nAbility > nMaxRaceReq) {
                nAbility = nMaxRaceReq;
            }

            if (nAbility + nRaceAdj < nMinClassReq) {
                nAbility = nMinClassReq - nRaceAdj;
            }

            bResult = TRUE;
        }
    }

    nAbility += nRaceAdj;
    nMax = nMaxRaceReq + nRaceAdj;
    nMin = max(nMinRaceReq + nRaceAdj, nMinClassReq);
    nMin = max(nMin, 1);
    nMod = nRaceAdj;

    return bResult;
}

// 0x60C0A0
void CScreenCreateChar::ResetAbilities(CGameSprite* pSprite)
{
    m_nExtraAbilityPoints = 0;

    INT nTotal;
    do {
        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_STR,
                CRuleTables::MAX_STR,
                CRuleTables::MOD_STR,
                pSprite->m_baseStats.m_STRBase,
                m_nMinSTR,
                m_nMaxSTR,
                m_nModSTR,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal = pSprite->m_baseStats.m_STRBase;

        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_DEX,
                CRuleTables::MAX_DEX,
                CRuleTables::MOD_DEX,
                pSprite->m_baseStats.m_DEXBase,
                m_nMinDEX,
                m_nMaxDEX,
                m_nModDEX,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal += pSprite->m_baseStats.m_DEXBase;

        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_CON,
                CRuleTables::MAX_CON,
                CRuleTables::MOD_CON,
                pSprite->m_baseStats.m_CONBase,
                m_nMinCON,
                m_nMaxCON,
                m_nModCON,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal += pSprite->m_baseStats.m_CONBase;

        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_INT,
                CRuleTables::MAX_INT,
                CRuleTables::MOD_INT,
                pSprite->m_baseStats.m_INTBase,
                m_nMinINT,
                m_nMaxINT,
                m_nModINT,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal += pSprite->m_baseStats.m_INTBase;

        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_WIS,
                CRuleTables::MAX_WIS,
                CRuleTables::MOD_WIS,
                pSprite->m_baseStats.m_WISBase,
                m_nMinWIS,
                m_nMaxWIS,
                m_nModWIS,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal += pSprite->m_baseStats.m_WISBase;

        while (1) {
            BOOL bResult = ResetAbility(pSprite,
                CRuleTables::MIN_CHR,
                CRuleTables::MAX_CHR,
                CRuleTables::MOD_CHR,
                pSprite->m_baseStats.m_CHRBase,
                m_nMinCHR,
                m_nMaxCHR,
                m_nModCHR,
                TRUE);
            if (bResult) {
                break;
            }
        }
        nTotal += pSprite->m_baseStats.m_CHRBase;
    } while (nTotal < 75);
}

// 0x60C380
void CScreenCreateChar::AllocateAbilities(CGameSprite* pSprite)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    INT v1 = pGame->m_cOptions.field_CA;
    m_nExtraAbilityPoints = pGame->m_cOptions.field_C6 + 6 * v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_STR,
        CRuleTables::MAX_STR,
        CRuleTables::MOD_STR,
        pSprite->m_baseStats.m_STRBase,
        m_nMinSTR,
        m_nMaxSTR,
        m_nModSTR,
        FALSE);
    m_nExtraAbilityPoints -= v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_DEX,
        CRuleTables::MAX_DEX,
        CRuleTables::MOD_DEX,
        pSprite->m_baseStats.m_DEXBase,
        m_nMinDEX,
        m_nMaxDEX,
        m_nModDEX,
        FALSE);
    m_nExtraAbilityPoints -= v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_CON,
        CRuleTables::MAX_CON,
        CRuleTables::MOD_CON,
        pSprite->m_baseStats.m_CONBase,
        m_nMinCON,
        m_nMaxCON,
        m_nModCON,
        FALSE);
    m_nExtraAbilityPoints -= v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_INT,
        CRuleTables::MAX_INT,
        CRuleTables::MOD_INT,
        pSprite->m_baseStats.m_INTBase,
        m_nMinINT,
        m_nMaxINT,
        m_nModINT,
        FALSE);
    m_nExtraAbilityPoints -= v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_WIS,
        CRuleTables::MAX_WIS,
        CRuleTables::MOD_WIS,
        pSprite->m_baseStats.m_WISBase,
        m_nMinWIS,
        m_nMaxWIS,
        m_nModWIS,
        FALSE);
    m_nExtraAbilityPoints -= v1;

    ResetAbility(pSprite,
        CRuleTables::MIN_CHR,
        CRuleTables::MAX_CHR,
        CRuleTables::MOD_CHR,
        pSprite->m_baseStats.m_CHRBase,
        m_nMinCHR,
        m_nMaxCHR,
        m_nModCHR,
        FALSE);
    m_nExtraAbilityPoints -= v1;
}

// 0x60C550
void CScreenCreateChar::ResetStartOverPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CUIControlButton* pButton;

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pButton->SetText(FetchString(13912)); // "Yes"

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));
    pButton->SetText(FetchString(13913)); // "No"

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));
    pText->RemoveAll();

    if (field_149E == 4) {
        // "You have some unallocated points left.  Are you sure you wish to continue?"
        pText->DisplayString(CString(""),
            FetchString(1552),
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            -1,
            FALSE,
            TRUE);
    } else {
        // "Are you sure you would like to start over?"
        pText->DisplayString(CString(""),
            FetchString(40275),
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            -1,
            FALSE,
            TRUE);
    }
}

// 0x60C700
void CScreenCreateChar::ResetSkillsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60CA10
void CScreenCreateChar::ResetFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60CEB0
void CScreenCreateChar::UpdatePopupPanel(DWORD dwPanelId, CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);
    switch (dwPanelId) {
    case 1:
        UpdateGenderPanel(pPanel, pSprite);
        break;
    case 2:
        UpdateClassPanel(pPanel, pSprite);
        break;
    case 3:
        UpdateAlignmentPanel(pPanel, pSprite);
        break;
    case 4:
        UpdateAbilitiesPanel(pPanel, pSprite);
        break;
    case 5:
        if (1) {
            CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable());
        }
        break;
    case 6:
        UpdateSkillsPanel(pPanel, pSprite);
        break;
    case 7:
        sub_60EF70(pPanel, pSprite);
        break;
    case 8:
        if (1) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(10));

            for (INT nButton = 2; nButton <= 8; nButton++) {
                CUIControlButtonCharGenRaceSelection* pRace = static_cast<CUIControlButtonCharGenRaceSelection*>(pPanel->GetControl(nButton));

                // NOTE: Uninline.
                BYTE nRace = pRace->GetRace();

                pRace->SetSelected(pSprite->m_startTypeAI.m_nRace == nRace);
            }

            CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable());
        }
        break;
    case 11:
        UpdateAppearancePanel(pPanel, pSprite);
        break;
    case 12:
        UpdateClericWizardSpecializationPanel(pPanel, pSprite);
        break;
    case 15:
        sub_610190(pPanel, pSprite);
        break;
    case 16:
        sub_60F430(pPanel, pSprite);
        break;
    case 17:
        if (field_4D6) {
            sub_60FA40(pPanel, pSprite);
        } else {
            sub_60F810(pPanel, pSprite);
        }
        break;
    case 18:
        sub_60E080(pPanel, pSprite);
        break;
    case 19:
        if (1) {
            CUIControlButton* pButton;

            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(46));

            pButton = static_cast<CUIControlButton*>(pPanel->GetControl(47));
            pButton->SetEnabled(field_586 >= 0);

            pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable());
        }
        break;
    case 20:
        if (1) {
            if (field_1624 == NULL) {
                field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
            }

            m_pCurrentScrollBar = field_1624;

            CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable());
        }
        break;
    case 21:
        if (1) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));

            CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 3679
            UTIL_ASSERT(pDone != NULL);

            pDone->SetEnabled(IsDoneButtonClickable());
        }
        break;
    case 51:
        if (1) {
            CUIPanel* pPanel = m_cUIManager.GetPanel(51);
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
        }
        break;
    case 52:
        UpdateMonkPaladinSpecializationPanel(pPanel, pSprite);
        break;
    case 54:
        UpdateSubRacePanel(pPanel, pSprite);
        break;
    case 55:
        UpdateFeatsPanel(pPanel, pSprite);
        break;
    }
}

// 0x60D280
void CScreenCreateChar::UpdateMonkPaladinSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(13));

    CUIControlButton3State* pBtOption1 = static_cast<CUIControlButton3State*>(pPanel->GetControl(1));
    CUIControlButton3State* pBtOption2 = static_cast<CUIControlButton3State*>(pPanel->GetControl(2));
    CUIControlButton3State* pBtOption3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(3));
    CUIControlButton3State* pBtOption4 = static_cast<CUIControlButton3State*>(pPanel->GetControl(4));
    CUIControlButton3State* pBtOption5 = static_cast<CUIControlButton3State*>(pPanel->GetControl(5));
    CUIControlButton3State* pBtOption6 = static_cast<CUIControlButton3State*>(pPanel->GetControl(6));
    CUIControlButton3State* pBtOption7 = static_cast<CUIControlButton3State*>(pPanel->GetControl(7));
    CUIControlButton3State* pBtOption8 = static_cast<CUIControlButton3State*>(pPanel->GetControl(8));
    CUIControlButton3State* pBtOption9 = static_cast<CUIControlButton3State*>(pPanel->GetControl(9));
    CUIControlButton3State* pBtOption10 = static_cast<CUIControlButton3State*>(pPanel->GetControl(10));

    // FIXME: What for?
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    UTIL_ASSERT(pBtOption1 != NULL);
    UTIL_ASSERT(pBtOption2 != NULL);
    UTIL_ASSERT(pBtOption3 != NULL);
    UTIL_ASSERT(pBtOption4 != NULL);
    UTIL_ASSERT(pBtOption5 != NULL);
    UTIL_ASSERT(pBtOption6 != NULL);
    UTIL_ASSERT(pBtOption7 != NULL);
    UTIL_ASSERT(pBtOption8 != NULL);
    UTIL_ASSERT(pBtOption9 != NULL);
    UTIL_ASSERT(pBtOption10 != NULL);
    UTIL_ASSERT(pCreateChar != NULL);

    CString sClass;

    // FIXME: Unused.
    CString v1;
    CString v2;
    CString v3;

    sClass = g_pBaldurChitin->GetObjectGame()->m_ruleTables.GetClassString(pSprite->m_startTypeAI.m_nClass, 0);

    pBtOption1->SetInactiveRender(FALSE);
    pBtOption2->SetInactiveRender(FALSE);
    pBtOption3->SetInactiveRender(FALSE);
    pBtOption4->SetInactiveRender(FALSE);
    pBtOption5->SetInactiveRender(FALSE);
    pBtOption6->SetInactiveRender(FALSE);
    pBtOption7->SetInactiveRender(FALSE);
    pBtOption8->SetInactiveRender(FALSE);
    pBtOption9->SetInactiveRender(FALSE);
    pBtOption10->SetInactiveRender(FALSE);

    pBtOption1->SetActive(FALSE);
    pBtOption2->SetActive(FALSE);
    pBtOption3->SetActive(FALSE);
    pBtOption4->SetActive(FALSE);
    pBtOption5->SetActive(FALSE);
    pBtOption6->SetActive(FALSE);
    pBtOption7->SetActive(FALSE);
    pBtOption8->SetActive(FALSE);
    pBtOption9->SetActive(FALSE);
    pBtOption10->SetActive(FALSE);

    pBtOption1->SetEnabled(FALSE);
    pBtOption2->SetEnabled(FALSE);
    pBtOption3->SetEnabled(FALSE);
    pBtOption4->SetEnabled(FALSE);
    pBtOption5->SetEnabled(FALSE);
    pBtOption6->SetEnabled(FALSE);
    pBtOption7->SetEnabled(FALSE);
    pBtOption8->SetEnabled(FALSE);
    pBtOption9->SetEnabled(FALSE);
    pBtOption10->SetEnabled(FALSE);

    pBtOption1->SetInactiveRender(FALSE);
    pBtOption2->SetInactiveRender(FALSE);
    pBtOption3->SetInactiveRender(FALSE);
    pBtOption4->SetInactiveRender(FALSE);
    pBtOption5->SetInactiveRender(FALSE);
    pBtOption6->SetInactiveRender(FALSE);
    pBtOption7->SetInactiveRender(FALSE);
    pBtOption8->SetInactiveRender(FALSE);
    pBtOption9->SetInactiveRender(FALSE);
    pBtOption10->SetInactiveRender(FALSE);

    switch (pSprite->m_startTypeAI.m_nClass) {
    case CAIOBJECTTYPE_C_MONK:
        pBtOption1->SetText(FetchString(36877));
        pBtOption2->SetText(FetchString(36878));
        pBtOption3->SetText(FetchString(36879));
        pBtOption1->SetEnabled(TRUE);
        pBtOption2->SetEnabled(TRUE);
        pBtOption3->SetEnabled(TRUE);
        break;
    case CAIOBJECTTYPE_C_PALADIN:
        pBtOption1->SetText(FetchString(36875));
        pBtOption2->SetText(FetchString(36872));
        pBtOption3->SetText(FetchString(36873));
        pBtOption1->SetEnabled(TRUE);
        pBtOption2->SetEnabled(TRUE);
        pBtOption3->SetEnabled(TRUE);
        break;
    }

    pBtOption1->SetSelected(FALSE);
    pBtOption2->SetSelected(FALSE);
    pBtOption3->SetSelected(FALSE);
    pBtOption4->SetSelected(FALSE);
    pBtOption5->SetSelected(FALSE);
    pBtOption6->SetSelected(FALSE);
    pBtOption7->SetSelected(FALSE);
    pBtOption8->SetSelected(FALSE);
    pBtOption9->SetSelected(FALSE);
    pBtOption10->SetSelected(FALSE);

    switch (pSprite->m_baseStats.m_specialization) {
    case 0x1:
    case 0x8:
        pBtOption1->SetSelected(TRUE);
        break;
    case 0x2:
    case 0x10:
        pBtOption2->SetSelected(TRUE);
        break;
    case 0x4:
    case 0x20:
        pBtOption3->SetSelected(TRUE);
        break;
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x60D950
void CScreenCreateChar::UpdateSubRacePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(7));

    CUIControlButton3State* pBtOption1 = static_cast<CUIControlButton3State*>(pPanel->GetControl(1));
    CUIControlButton3State* pBtOption2 = static_cast<CUIControlButton3State*>(pPanel->GetControl(2));
    CUIControlButton3State* pBtOption3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(3));
    CUIControlButton3State* pBtOption4 = static_cast<CUIControlButton3State*>(pPanel->GetControl(4));

    // FIXME: What for?
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 3909
    UTIL_ASSERT(pBtOption1 != NULL);
    UTIL_ASSERT(pBtOption2 != NULL);
    UTIL_ASSERT(pBtOption3 != NULL);
    UTIL_ASSERT(pBtOption4 != NULL);
    UTIL_ASSERT(pCreateChar != NULL);

    CString sSubRaceFileName;
    CString sRace;
    CString sPureRace;
    CString sRaceMixed;
    CString v5;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    sRace = pGame->m_ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    sPureRace = pGame->m_ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, 0);

    sSubRaceFileName = pGame->m_ruleTables.m_tSrTable.GetAt(CString("SRFILE"), sPureRace);
    if (m_tSubRace.GetResRef() != sSubRaceFileName) {
        m_tSubRace.Load(CResRef(sSubRaceFileName));
    }

    pBtOption1->SetText(CString(""));
    pBtOption1->SetActive(FALSE);
    pBtOption1->SetEnabled(FALSE);
    pBtOption1->SetInactiveRender(FALSE);

    pBtOption2->SetText(CString(""));
    pBtOption2->SetActive(FALSE);
    pBtOption2->SetEnabled(FALSE);
    pBtOption2->SetInactiveRender(FALSE);

    pBtOption3->SetText(CString(""));
    pBtOption3->SetActive(FALSE);
    pBtOption3->SetEnabled(FALSE);
    pBtOption3->SetInactiveRender(FALSE);

    pBtOption4->SetText(CString(""));
    pBtOption4->SetActive(FALSE);
    pBtOption4->SetEnabled(FALSE);
    pBtOption4->SetInactiveRender(FALSE);

    for (INT nIndex = 0; nIndex < m_tSubRace.GetHeight(); nIndex++) {
        INT nSubRaceListIndex = atol(m_tSubRace.GetAt(CPoint(0, nIndex)));
        INT nSubRaceId = atol(pGame->m_ruleTables.m_tSrList.GetAt(CPoint(4, nSubRaceListIndex)));
        if (nSubRaceId == 0) {
            pGame->m_ruleTables.GetRaceStringMixed(pSprite->m_startTypeAI.m_nRace, sRaceMixed, 0);
        } else {
            STRREF strRace = atol(pGame->m_ruleTables.m_tSrList.GetAt(CPoint(2, nSubRaceListIndex)));
            sRaceMixed = FetchString(strRace);
        }

        switch (nIndex) {
        case 0:
            pBtOption1->SetText(sRaceMixed);
            pBtOption1->SetActive(TRUE);
            pBtOption1->SetEnabled(TRUE);
            pBtOption1->SetInactiveRender(TRUE);
            break;
        case 1:
            pBtOption2->SetText(sRaceMixed);
            pBtOption2->SetActive(TRUE);
            pBtOption2->SetEnabled(TRUE);
            pBtOption2->SetInactiveRender(TRUE);
            break;
        case 2:
            pBtOption3->SetText(sRaceMixed);
            pBtOption3->SetActive(TRUE);
            pBtOption3->SetEnabled(TRUE);
            pBtOption3->SetInactiveRender(TRUE);
            break;
        case 3:
            pBtOption4->SetText(sRaceMixed);
            pBtOption4->SetActive(TRUE);
            pBtOption4->SetEnabled(TRUE);
            pBtOption4->SetInactiveRender(TRUE);
            break;
        }
    }

    pBtOption1->SetSelected(FALSE);
    pBtOption2->SetSelected(FALSE);
    pBtOption3->SetSelected(FALSE);
    pBtOption4->SetSelected(FALSE);

    INT nSelectedSubRace = atol(m_tSubRace.GetAt(CPoint(0, pSprite->m_startTypeAI.m_nSubRace)));

    for (INT nIndex = 0; nIndex < m_tSubRace.GetHeight(); nIndex++) {
        INT nSubRace = atol(m_tSubRace.GetAt(CPoint(0, nIndex)));
        if (nSelectedSubRace == nSubRace) {
            switch (nIndex) {
            case 0:
                pBtOption1->SetSelected(TRUE);
                break;
            case 1:
                pBtOption2->SetSelected(TRUE);
                break;
            case 2:
                pBtOption3->SetSelected(TRUE);
                break;
            case 3:
                pBtOption4->SetSelected(TRUE);
                break;
            }
            break;
        }
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x60E080
void CScreenCreateChar::sub_60E080(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60E2D0
void CScreenCreateChar::UpdateAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60E3E0
void CScreenCreateChar::UpdateFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    if (field_1624 == NULL) {
        field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(104));
    }

    m_pCurrentScrollBar = field_1624;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    HighlightLabel(pPanel,
        0x1000000C,
        m_nExtraFeats != 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel,
        0x1000000C,
        "%d",
        m_nExtraFeats);

    pSprite->field_562C = 1;
    pSprite->sub_72DE60();

    m_nTopFeat = min(m_nTopFeat - (FEAT_COUNT - FEAT_SLOTS), FEAT_COUNT - FEAT_SLOTS);

    for (DWORD dwButtonId = 14; dwButtonId <= 32; dwButtonId += 2) {
        DWORD index = (dwButtonId - 14) / 2;
        DWORD id = pGame->m_ruleTables.GetFeatId(m_nTopFeat + index);
        STRREF strName = pGame->m_ruleTables.GetFeatName(id);
        UpdateLabel(pPanel,
            0x10000001 + index,
            "%s",
            FetchString(strName));
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());

    CUIControlScrollBarCharGenFeats* pScroll = static_cast<CUIControlScrollBarCharGenFeats*>(pPanel->GetControl(104));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4268
    UTIL_ASSERT(pScroll != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4268
    UTIL_ASSERT(pScroll != NULL);

    // NOTE: Uninline.
    pScroll->UpdateScrollBar();

    DWORD index = 0;
    for (DWORD dwButtonId = 15; dwButtonId < 35; dwButtonId += 2) {
        DWORD id = pGame->m_ruleTables.GetFeatId(m_nTopFeat + index);
        CUIControlButton* pButton;

        BOOL bPlusEnabled = pSprite->sub_763A40(id, 1) && m_nExtraFeats > 0;

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(dwButtonId - 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4286
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bPlusEnabled);
        pButton->SetActive(bPlusEnabled);

        HighlightLabel(pPanel,
            0x10000001 + index,
            !bPlusEnabled,
            COLOR_LABEL_DISABLE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(dwButtonId));

        BOOL bMinusEnabled = m_storedFeats[m_nTopFeat + index] < pSprite->GetFeatValue(m_nTopFeat + index);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4300
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bMinusEnabled);
        pButton->SetActive(bMinusEnabled);

        index++;
    }

    pPanel->InvalidateRect(NULL);
}

// 0x60E710
void CScreenCreateChar::UpdateGenderPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(4));

    for (INT nButton = 2; nButton <= 3; nButton++) {
        CUIControlButtonCharGenGenderSelection* pGender = static_cast<CUIControlButtonCharGenGenderSelection*>(pPanel->GetControl(nButton));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4379
        UTIL_ASSERT(pGender != NULL);

        // NOTE: Uninline.
        BYTE nGender = pGender->GetGender();

        pGender->SetSelected(pSprite->m_startTypeAI.m_nGender == nGender);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x60E7F0
void CScreenCreateChar::UpdateAbilitiesPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(28));

    HighlightLabel(pPanel,
        0x10000002,
        m_nExtraAbilityPoints > 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel,
        0x10000002,
        "%d",
        m_nExtraAbilityPoints);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // STR
    UpdateLabel(pPanel,
        0x10000003,
        "%d",
        pSprite->m_baseStats.m_STRBase);
    UpdateLabel(pPanel,
        0x10000024,
        "%+d",
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_STRBase));
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
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_DEXBase));
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
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CONBase));
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
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_INTBase));
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
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_WISBase));
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
        pGame->m_ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CHRBase));
    HighlightLabel(pPanel,
        0x10000029,
        pSprite->m_baseStats.m_CHRBase != 10 && pSprite->m_baseStats.m_CHRBase != 11,
        pSprite->m_baseStats.m_CHRBase < 10 ? RGB(255, 0, 0) : RGB(0, 255, 0));

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4454
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable());
}

// 0x60EB60
void CScreenCreateChar::UpdateSkillsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60EF70
void CScreenCreateChar::sub_60EF70(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60F430
void CScreenCreateChar::sub_60F430(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60F810
void CScreenCreateChar::sub_60F810(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60FA40
void CScreenCreateChar::sub_60FA40(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x60FC60
void CScreenCreateChar::UpdateClassPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(15));

    for (INT nButton = 2; nButton <= 12; nButton++) {
        CUIControlButtonCharGenClassSelection* pClass = static_cast<CUIControlButtonCharGenClassSelection*>(pPanel->GetControl(nButton));

        // NOTE: Uninline.
        BYTE nClass = pClass->GetClass();

        pClass->SetSelected(pSprite->m_startTypeAI.m_nClass == nClass);

        BOOL bEnabled;
        switch (pSprite->m_startTypeAI.m_nRace) {
        case CAIOBJECTTYPE_R_HUMAN:
        case CAIOBJECTTYPE_R_ELF:
        case CAIOBJECTTYPE_R_HALF_ELF:
        case CAIOBJECTTYPE_R_DWARF:
        case CAIOBJECTTYPE_R_HALFLING:
        case CAIOBJECTTYPE_R_GNOME:
        case CAIOBJECTTYPE_R_HALF_ORC:
            bEnabled = TRUE;
            break;
        default:
            bEnabled = FALSE;
            break;
        }

        pClass->SetEnabled(bEnabled);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x60FDB0
void CScreenCreateChar::UpdateAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(12));

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    for (INT nButton = 2; nButton <= 10; nButton++) {
        CUIControlButtonCharGenAlignmentSelection* pAlignment = static_cast<CUIControlButtonCharGenAlignmentSelection*>(pPanel->GetControl(nButton));

        // NOTE: Uninline.
        BYTE nAlignment = pAlignment->GetAlignment();

        pAlignment->SetSelected(pSprite->m_startTypeAI.m_nGender == nAlignment);

        BOOL bIsValid = pGame->m_ruleTables.IsValidAlignment(pSprite->m_startTypeAI.m_nClass,
            nAlignment,
            pSprite->m_baseStats.m_specialization);
        pAlignment->SetEnabled(bIsValid);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x60FEE0
void CScreenCreateChar::UpdateClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x610190
void CScreenCreateChar::sub_610190(CUIPanel* pPanel, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x6103A0
void CScreenCreateChar::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5394
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5396
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x6104B0
CString CScreenCreateChar::GetCurrentPortrait(CGameSprite* pSprite)
{
    switch (pSprite->m_startTypeAI.m_nGender) {
    case 1:
        return MALE_PORTRAITS[m_nCurrentPortrait];
    case 2:
        return FEMALE_PORTRAITS[m_nCurrentPortrait];
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 5534
        UTIL_ASSERT(FALSE);
    }
}

// 0x610540
void CScreenCreateChar::sub_610540()
{
    // TODO: Incomplete.
}

// 0x610850
void CScreenCreateChar::RecallMemoryAbilities(BYTE& nSTR, BYTE& nDEX, BYTE& nCON, BYTE& nINT, BYTE& nWIS, BYTE& nCHR, INT& nExtra)
{
    if (m_nMemorySTR != -1) {
        nSTR = m_nMemorySTR;
    }

    if (m_nMemoryDEX != -1) {
        nDEX = m_nMemoryDEX;
    }

    if (m_nMemoryCON != -1) {
        nCON = m_nMemoryCON;
    }

    if (m_nMemoryINT != -1) {
        nINT = m_nMemoryINT;
    }

    if (m_nMemoryWIS != -1) {
        nWIS = m_nMemoryWIS;
    }

    if (m_nMemoryExtra >= 0) {
        nExtra = m_nMemoryExtra;
    }
}

// NOTE: Inlined.
INT CScreenCreateChar::GetNumHatedRaces()
{
    return CSCREENCREATECHAR_NUM_HATEDRACES;
}

// NOTE: Uninline.
void CScreenCreateChar::SetTopHatedRace(INT nTopHatedRace)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5851
    UTIL_ASSERT(0 <= nTopHatedRace && nTopHatedRace <= GetNumHatedRaces());

    m_nTopHatedRace = nTopHatedRace;
}

// NOTE: Uninline.
BYTE CScreenCreateChar::GetHatedRace(INT nIndex)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5877
    UTIL_ASSERT(0 <= nIndex && nIndex < CSCREENCREATECHAR_NUM_HATEDRACES);

    return m_hatedRaces[nIndex];
}

// 0x6108D0
void CScreenCreateChar::sub_6108D0(INT a1)
{
    INT nGameSprite = GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (a1 != field_57E) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6064
            UTIL_ASSERT(m_pPortraits != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(18);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6068
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6070
            UTIL_ASSERT(pText != NULL);

            if (field_57E != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(field_57E),
                    pText->m_rgbTextColor);
            }

            field_57E = a1;

            if (field_57E != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(field_57E),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
            }

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x610A40
void CScreenCreateChar::sub_610A40(INT a1)
{
    INT nGameSprite = GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (a1 != field_57A) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6136
            UTIL_ASSERT(m_pPortraits != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(18);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6140
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(4));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 6142
            UTIL_ASSERT(pText != NULL);

            if (field_57A != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(field_57A),
                    pText->m_rgbTextColor);
            }

            field_57A = a1;

            if (field_57A != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(field_57A),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
            }

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x610BB0
void CScreenCreateChar::OnCharacterImportItemSelect(INT nItem)
{
    // TODO: Incomplete.
}

// 0x610DC0
void CScreenCreateChar::sub_610DC0()
{
    // TODO: Incomplete.
}

// 0x611900
void CScreenCreateChar::OnCharacterExportItemSelect(INT nItem)
{
    // TODO: Incomplete.
}

// 0x611AF0
void CScreenCreateChar::sub_611AF0()
{
    // TODO: Incomplete.
}

// 0x612800
void CScreenCreateChar::sub_612800()
{
    // TODO: Incomplete.
}

// 0x612930
void CScreenCreateChar::sub_612930()
{
    // TODO: Incomplete.
}

// 0x612DE0
void CScreenCreateChar::CompleteCharacterSkills()
{
    // TODO: Incomplete.
}

// 0x613310
void CScreenCreateChar::sub_613310()
{
    // TODO: Incomplete.
}

// 0x6139C0
void CScreenCreateChar::RemoveItems()
{
    // TODO: Incomplete.
}

// 0x613A30
void CScreenCreateChar::DeleteCharacter()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 7288
    UTIL_ASSERT(pGame != NULL);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(GetSpriteId(),
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pGame->GetObjectArray()->ReleaseShare(GetSpriteId(),
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        rc = pGame->GetObjectArray()->Delete(GetSpriteId(),
            CGameObjectArray::THREAD_ASYNCH,
            NULL,
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if (pSprite != NULL) {
                delete pSprite;
            }
            SetSpriteId(CGameObjectArray::INVALID_OBJECT_ID);
        } else {
            SetSpriteId(CGameObjectArray::INVALID_OBJECT_ID);
        }
    }
}

// 0x613B20
void CScreenCreateChar::ImportCharacter()
{
    // TODO: Incomplete.
}

// 0x613EF0
void CScreenCreateChar::sub_613EF0()
{
    // TODO: Incomplete.
}

// 0x614450
void CScreenCreateChar::OnSoundItemSelect(INT nItem)
{
    // TODO: Incomplete.
}

// 0x615B70
BOOL CScreenCreateChar::IsDoneButtonClickable()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x615F50
void CScreenCreateChar::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CScreenCreateChar::SetSpriteId(INT nSpriteId)
{
    m_nGameSprite = nSpriteId;
}

// 0x617190
INT CScreenCreateChar::GetSpriteId()
{
    return m_nGameSprite;
}

// 0x617190
void CScreenCreateChar::sub_617190()
{
    // TODO: Incomplete.
}

// 0x6171A0
void CScreenCreateChar::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x6175A0
void CScreenCreateChar::OnMainCancelButtonClick()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
CUIPanel* CScreenCreateChar::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x6179D0
void CScreenCreateChar::SummonPopup(DWORD dwPopupId, CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x617B70
void CScreenCreateChar::DismissPopup()
{
    // TODO: Incomplete.
}

// 0x617D60
void CScreenCreateChar::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }

    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.sub_7AC840();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.sub_7AC890();
}

// -----------------------------------------------------------------------------

// 0x6145C0
CUIControlButtonCharGenMenu::CUIControlButtonCharGenMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;

    STRREF strText;
    switch (m_nID) {
    case 0:
        strText = 12135;
        break;
    case 1:
        strText = 1048;
        break;
    case 2:
        strText = 12136;
        break;
    case 3:
        strText = 1049;
        break;
    case 4:
        strText = 17088;
        break;
    case 5:
        strText = 11983;
        break;
    case 6:
        strText = 11961;
        break;
    case 7:
        strText = 1047;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 8100
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(strText, strRes);
    SetText(strRes.szText);
}

// 0x614720
CUIControlButtonCharGenMenu::~CUIControlButtonCharGenMenu()
{
}

// 0x6147C0
void CUIControlButtonCharGenMenu::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        DWORD dwPopupId;
        switch (pCreateChar->field_4DE) {
        case 0:
            dwPopupId = 1;
            break;
        case 1:
            dwPopupId = 8;
            break;
        case 2:
            dwPopupId = 2;
            break;
        case 3:
            dwPopupId = 3;
            break;
        case 4:
            dwPopupId = 4;
            break;
        case 5:
            dwPopupId = 6;
            break;
        case 6:
            pCreateChar->sub_612800();
            dwPopupId = 13;
            break;
        case 7:
            dwPopupId = 5;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 8199
            UTIL_ASSERT(FALSE);
        }

        pCreateChar->SummonPopup(dwPopupId, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x6154F0
CUIControlButtonCharGenImport::CUIControlButtonCharGenImport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13955, strRes);
    SetText(strRes.szText);
}

// 0x6155E0
CUIControlButtonCharGenImport::~CUIControlButtonCharGenImport()
{
}

// 0x615680
void CUIControlButtonCharGenImport::OnLButtonClick(CPoint)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->SummonPopup(20, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x615780
CUIControlButtonCharGenBack::CUIControlButtonCharGenBack(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15416, strRes);
    SetText(strRes.szText);
}

// 0x615870
CUIControlButtonCharGenBack::~CUIControlButtonCharGenBack()
{
}

// 0x615910
void CUIControlButtonCharGenBack::OnLButtonClick(CPoint)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pCreateChar->field_4DE > pCreateChar->field_4DA) {
            pCreateChar->field_4DE--;
            if (pCreateChar->field_4DE < pCreateChar->field_4DA) {
                pCreateChar->field_4DE = pCreateChar->field_4DA;
            }
            pCreateChar->UpdateMainPanel(pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x6159C0
CUIControlButtonCharGenPopupDone::CUIControlButtonCharGenPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(36789, strRes);
    SetText(strRes.szText);
}

// 0x615AB0
CUIControlButtonCharGenPopupDone::~CUIControlButtonCharGenPopupDone()
{
}

// 615B50
void CUIControlButtonCharGenPopupDone::OnLButtonClick(CPoint)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    pCreateChar->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x619140
CUIControlButtonCharGenAbilitiesPlusMinus::CUIControlButtonCharGenAbilitiesPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x619180
CUIControlButtonCharGenAbilitiesPlusMinus::~CUIControlButtonCharGenAbilitiesPlusMinus()
{
}

// 0x619220
BOOL CUIControlButtonCharGenAbilitiesPlusMinus::OnLButtonDown(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 10595
    UTIL_ASSERT(pCreateChar != NULL);

    CString sValue;

    STRREF strHelp;
    BYTE nMin;
    BYTE nMax;
    switch (m_nID) {
    case 16:
    case 17:
        strHelp = 9582;
        nMin = pCreateChar->m_nMinSTR;
        nMax = pCreateChar->m_nMaxSTR;
        break;
    case 18:
    case 19:
        strHelp = 9584;
        nMin = pCreateChar->m_nMinDEX;
        nMax = pCreateChar->m_nMaxDEX;
        break;
    case 20:
    case 21:
        strHelp = 9583;
        nMin = pCreateChar->m_nMinCON;
        nMax = pCreateChar->m_nMaxCON;
        break;
    case 22:
    case 23:
        strHelp = 9585;
        nMin = pCreateChar->m_nMinINT;
        nMax = pCreateChar->m_nMaxINT;
        break;
    case 24:
    case 25:
        strHelp = 9586;
        nMin = pCreateChar->m_nMinWIS;
        nMax = pCreateChar->m_nMaxWIS;
        break;
    case 26:
    case 27:
        strHelp = 9587;
        nMin = pCreateChar->m_nMinCHR;
        nMax = pCreateChar->m_nMaxCHR;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 10641
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    sValue.Format("%d", nMin);
    g_pBaldurChitin->m_cTlkTable.SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->m_cTlkTable.SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

    pCreateChar->UpdateHelp(m_pPanel->m_nID, 29, strHelp);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
}

// 0x6194C0
void CUIControlButtonCharGenAbilitiesPlusMinus::AdjustValue()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

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
        BYTE* pValue;
        BOOL bInc;
        switch (m_nID) {
        case 16:
        case 17:
            nMin = pCreateChar->m_nMinSTR;
            nMax = pCreateChar->m_nMaxSTR;
            pValue = &(pSprite->m_baseStats.m_STRBase);
            bInc = m_nID == 16;
            break;
        case 18:
        case 19:
            nMin = pCreateChar->m_nMinDEX;
            nMax = pCreateChar->m_nMaxDEX;
            pValue = &(pSprite->m_baseStats.m_DEXBase);
            bInc = m_nID == 18;
            break;
        case 20:
        case 21:
            nMin = pCreateChar->m_nMinCON;
            nMax = pCreateChar->m_nMaxCON;
            pValue = &(pSprite->m_baseStats.m_CONBase);
            bInc = m_nID == 20;
            break;
        case 22:
        case 23:
            nMin = pCreateChar->m_nMinINT;
            nMax = pCreateChar->m_nMaxINT;
            pValue = &(pSprite->m_baseStats.m_INTBase);
            bInc = m_nID == 22;
            break;
        case 24:
        case 25:
            nMin = pCreateChar->m_nMinWIS;
            nMax = pCreateChar->m_nMaxWIS;
            pValue = &(pSprite->m_baseStats.m_WISBase);
            bInc = m_nID == 24;
            break;
        case 26:
        case 27:
            nMin = pCreateChar->m_nMinCHR;
            nMax = pCreateChar->m_nMaxCHR;
            pValue = &(pSprite->m_baseStats.m_CHRBase);
            bInc = m_nID == 26;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 10778
            UTIL_ASSERT(FALSE);
        }

        if (bInc) {
            if (pCreateChar->m_nExtraAbilityPoints > 0) {
                if (*pValue < nMax) {
                    (*pValue)++;
                    pCreateChar->m_nExtraAbilityPoints--;
                    pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
                } else {
                    pCreateChar->UpdateHelp(m_pPanel->m_nID, 29, 14838);
                }
            }
        } else {
            if (*pValue > nMin) {
                (*pValue)--;
                pCreateChar->m_nExtraAbilityPoints++;
                pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
            } else {
                pCreateChar->UpdateHelp(m_pPanel->m_nID, 29, 14840);
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x619710
CUIControlButtonCharGenAbilitiesStore::CUIControlButtonCharGenAbilitiesStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(17373, strRes);
    SetText(strRes.szText);
}

// 0x619800
CUIControlButtonCharGenAbilitiesStore::~CUIControlButtonCharGenAbilitiesStore()
{
}

// 0x6198A0
void CUIControlButtonCharGenAbilitiesStore::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CCreatureFileHeader* pBStats = &(pSprite->m_baseStats);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 10897
        UTIL_ASSERT(pBStats != NULL);

        pCreateChar->m_nMemorySTR = pBStats->m_STRBase;
        pCreateChar->m_nMemoryDEX = pBStats->m_DEXBase;
        pCreateChar->m_nMemoryCON = pBStats->m_CONBase;
        pCreateChar->m_nMemoryINT = pBStats->m_INTBase;
        pCreateChar->m_nMemoryWIS = pBStats->m_WISBase;
        pCreateChar->m_nMemoryCHR = pBStats->m_CHRBase;
        pCreateChar->m_nMemoryExtra = pCreateChar->m_nExtraAbilityPoints;

        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x6199D0
CUIControlButtonCharGenAbilitiesRecall::CUIControlButtonCharGenAbilitiesRecall(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(17374, strRes);
    SetText(strRes.szText);
}

// 0x619AC0
CUIControlButtonCharGenAbilitiesRecall::~CUIControlButtonCharGenAbilitiesRecall()
{
}

// 0x619B60
void CUIControlButtonCharGenAbilitiesRecall::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pCreateChar->m_nMemorySTR != -1
            || pCreateChar->m_nMemoryDEX != -1
            || pCreateChar->m_nMemoryCON != -1
            || pCreateChar->m_nMemoryINT != -1
            || pCreateChar->m_nMemoryWIS != -1
            || pCreateChar->m_nMemoryCHR != -1
            || pCreateChar->m_nMemoryExtra >= 0) {
            CCreatureFileHeader* pBStats = &(pSprite->m_baseStats);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 10980
            UTIL_ASSERT(pBStats != NULL);

            INT nExtra;
            pCreateChar->RecallMemoryAbilities(pBStats->m_STRBase,
                pBStats->m_DEXBase,
                pBStats->m_CONBase,
                pBStats->m_INTBase,
                pBStats->m_WISBase,
                pBStats->m_CHRBase,
                nExtra);
            pCreateChar->m_nExtraAbilityPoints = nExtra;

            pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x619CB0
CUIControlButtonCharGenAbilitiesReroll::CUIControlButtonCharGenAbilitiesReroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11982, strRes);
    SetText(strRes.szText);
}

// 0x619DA0
CUIControlButtonCharGenAbilitiesReroll::~CUIControlButtonCharGenAbilitiesReroll()
{
}

// 0x619E40
void CUIControlButtonCharGenAbilitiesReroll::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->ResetAbilities(pSprite);
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x619EE0
CUIControlButtonCharGenAbilitiesAllocate::CUIControlButtonCharGenAbilitiesAllocate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(1379, strRes);
    SetText(strRes.szText);
}

// 0x619FD0
CUIControlButtonCharGenAbilitiesAllocate::~CUIControlButtonCharGenAbilitiesAllocate()
{
}

// 0x61A090
void CUIControlButtonCharGenAbilitiesAllocate::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->AllocateAbilities(pSprite);
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x61A2E0
CUIControlScrollBarCharGenSkills::CUIControlScrollBarCharGenSkills(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarCharGenSkills::~CUIControlScrollBarCharGenSkills()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharGenSkills::UpdateScrollBar()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11289
    UTIL_ASSERT(pCreateChar != NULL);

    AdjustScrollBar(pCreateChar->m_nTopSkill, SKILL_COUNT, SKILL_SLOTS);
}

// 0x61A300
void CUIControlScrollBarCharGenSkills::OnScrollUp()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11314
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->m_nTopSkill = max(pCreateChar->m_nTopSkill - 1, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A3A0
void CUIControlScrollBarCharGenSkills::OnScrollDown()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11338
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->m_nTopSkill++;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A430
void CUIControlScrollBarCharGenSkills::OnPageUp(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11362
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, SKILL_SLOTS - 1);
    pCreateChar->m_nTopSkill = max(pCreateChar->m_nTopSkill - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A4E0
void CUIControlScrollBarCharGenSkills::OnPageDown(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11362
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, SKILL_SLOTS - 1);
    pCreateChar->m_nTopSkill += nStep;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A580
void CUIControlScrollBarCharGenSkills::OnScroll()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11418
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->m_nTopSkill = max(SKILL_COUNT * field_144, 0) / field_142;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A630
void CUIControlScrollBarCharGenSkills::InvalidateItems()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11445
    UTIL_ASSERT(pCreateChar != NULL);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x61A750
CUIControlButtonCharGenSkillsPlusMinus::CUIControlButtonCharGenSkillsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x61A790
CUIControlButtonCharGenSkillsPlusMinus::~CUIControlButtonCharGenSkillsPlusMinus()
{
}

// 0x61A830
BOOL CUIControlButtonCharGenSkillsPlusMinus::OnLButtonDown(CPoint pt)
{
    DWORD offset;
    switch (m_nID) {
    case 14:
    case 15:
        offset = 0;
        break;
    case 16:
    case 17:
        offset = 1;
        break;
    case 18:
    case 19:
        offset = 2;
        break;
    case 20:
    case 21:
        offset = 3;
        break;
    case 22:
    case 23:
        offset = 4;
        break;
    case 24:
    case 25:
        offset = 5;
        break;
    case 26:
    case 27:
        offset = 6;
        break;
    case 28:
    case 29:
        offset = 7;
        break;
    case 30:
    case 31:
        offset = 8;
        break;
    case 32:
    case 33:
        offset = 9;
        break;
    case 34:
    case 35:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 11586
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    DWORD id = pGame->m_ruleTables.GetSkillId(g_pBaldurChitin->m_pEngineCreateChar->m_nTopSkill + offset);
    STRREF strDescription = pGame->m_ruleTables.GetSkillDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return OnLButtonDown(pt);
}

// 0x61A980
void CUIControlButtonCharGenSkillsPlusMinus::AdjustValue()
{
    BOOL bInc;
    switch (m_nID) {
    case 14:
    case 16:
    case 18:
    case 20:
    case 22:
    case 24:
    case 26:
    case 28:
    case 30:
    case 32:
    case 34:
        bInc = TRUE;
        break;
    case 15:
    case 17:
    case 19:
    case 21:
    case 23:
    case 25:
    case 27:
    case 29:
    case 31:
    case 35:
        bInc = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 11668
        UTIL_ASSERT(FALSE);
    }

    DWORD offset;
    switch (m_nID) {
    case 14:
    case 15:
        offset = 0;
        break;
    case 16:
    case 17:
        offset = 1;
        break;
    case 18:
    case 19:
        offset = 2;
        break;
    case 20:
    case 21:
        offset = 3;
        break;
    case 22:
    case 23:
        offset = 4;
        break;
    case 24:
    case 25:
        offset = 5;
        break;
    case 26:
    case 27:
        offset = 6;
        break;
    case 28:
    case 29:
        offset = 7;
        break;
    case 30:
    case 31:
        offset = 8;
        break;
    case 32:
    case 33:
        offset = 9;
        break;
    case 34:
    case 35:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 11731
        UTIL_ASSERT(FALSE);
    }

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CAIObjectType typeAI(pSprite->m_startTypeAI);

        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        DWORD id = pGame->m_ruleTables.GetSkillId(pCreateChar->m_nTopSkill + offset);
        INT nValue = pSprite->GetSkillValue(id);

        // FIXME: Looks wrong (obtaining id from id).
        INT nCost = pSprite->GetSkillCost(pGame->m_ruleTables.GetSkillId(id),
            typeAI.m_nClass);

        if (bInc) {
            if (nCost != 0 && pCreateChar->m_nExtraSkillPoints >= nCost) {
                pSprite->SetSkillValue(id, nValue + 1);
                pCreateChar->m_nExtraSkillPoints -= nCost;
            }
        } else {
            if (nValue > 0 && pCreateChar->m_storedSkills[id] < pSprite->GetSkillValue(id)) {
                pSprite->SetSkillValue(id, nValue - 1);

                // FIXME: Looks wrong (obtaining id from id).
                pCreateChar->m_nExtraSkillPoints += pSprite->GetSkillCost(pGame->m_ruleTables.GetSkillId(id),
                    typeAI.m_nClass);
            }
        }

        pCreateChar->UpdatePopupPanel(pCreateChar->GetTopPopup()->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x61ACC0
CUIControlButtonCharGenAlignmentSelection::CUIControlButtonCharGenAlignmentSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;

    STRREF strText;
    switch (m_nID) {
    case 2:
        strText = 7186; // "Lawful Good"
        break;
    case 3:
        strText = 7183; // "Neutral Good"
        break;
    case 4:
        strText = 7189; // "Chaotic Good"
        break;
    case 5:
        strText = 7188; // "Lawful Neutral"
        break;
    case 6:
        strText = 7185; // "True Neutral"
        break;
    case 7:
        strText = 7191; // "Chaotic Neutral"
        break;
    case 8:
        strText = 7187; // "Lawful Evil"
        break;
    case 9:
        strText = 7184; // "Neutral Evil"
        break;
    case 10:
        strText = 7190; // "Chaotic Evil"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 11857
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(strText, strRes);
    SetText(strRes.szText);
    m_nSelectedFrame = 0;
}

// 0x61AE40
CUIControlButtonCharGenAlignmentSelection::~CUIControlButtonCharGenAlignmentSelection()
{
}

// 0x61AEE0
void CUIControlButtonCharGenAlignmentSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CAIObjectType typeAI(pSprite->m_startTypeAI);
        typeAI.m_nAlignment = GetAlignment();
        pSprite->m_startTypeAI.Set(typeAI);

        STRREF strDescription;
        switch (m_nID) {
        case 2:
            strDescription = 9603;
            break;
        case 3:
            strDescription = 9606;
            break;
        case 4:
            strDescription = 9609;
            break;
        case 5:
            strDescription = 9604;
            break;
        case 6:
            strDescription = 9608;
            break;
        case 7:
            strDescription = 9610;
            break;
        case 8:
            strDescription = 9605;
            break;
        case 9:
            strDescription = 9607;
            break;
        case 10:
            strDescription = 9611;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 11958
            UTIL_ASSERT(FALSE);
        }

        pCreateChar->UpdateHelp(m_pPanel->m_nID, 11, strDescription);
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// NOTE: Inlined.
BYTE CUIControlButtonCharGenAlignmentSelection::GetAlignment()
{
    switch (m_nID) {
    case 2:
        return CAIOBJECTTYPE_LAWFUL_GOOD;
    case 3:
        return CAIOBJECTTYPE_NEUTRAL_GOOD;
    case 4:
        return CAIOBJECTTYPE_CHAOTIC_GOOD;
    case 5:
        return CAIOBJECTTYPE_LAWFUL_NEUTRAL;
    case 6:
        return CAIOBJECTTYPE_NEUTRAL;
    case 7:
        return CAIOBJECTTYPE_CHAOTIC_NEUTRAL;
    case 8:
        return CAIOBJECTTYPE_LAWFUL_EVIL;
    case 9:
        return CAIOBJECTTYPE_NEUTRAL_EVIL;
    case 10:
        return CAIOBJECTTYPE_CHAOTIC_EVIL;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 12022
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x61B8D0
CUIControlButtonCharGenGenderSelection::CUIControlButtonCharGenGenderSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x61B930
CUIControlButtonCharGenGenderSelection::~CUIControlButtonCharGenGenderSelection()
{
}

// 0x61B9D0
void CUIControlButtonCharGenGenderSelection::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    CUIControlButton3State::OnLButtonClick(pt);
    switch (m_nID) {
    case 7:
        if (1) {
            CUIControlButton* pButton = static_cast<CUIControlButton*>(pCreateChar->GetManager()->GetPanel(1)->GetControl(2));
            pButton->OnLButtonClick(CPoint(0, 0));
        }
        break;
    case 8:
        if (1) {
            CUIControlButton* pButton = static_cast<CUIControlButton*>(pCreateChar->GetManager()->GetPanel(1)->GetControl(3));
            pButton->OnLButtonClick(CPoint(0, 0));
        }
        break;
    default:
        if (1) {
            INT nGameSprite = pCreateChar->GetSpriteId();

            CGameSprite* pSprite;
            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                CAIObjectType typeAI(pSprite->m_startTypeAI);
                typeAI.m_nGender = GetGender();
                pSprite->m_startTypeAI.Set(typeAI);

                STRREF strDescription;
                switch (m_nID) {
                case 2:
                    strDescription = 13083;
                    break;
                case 3:
                    strDescription = 13084;
                    break;
                case 7:
                case 8:
                    strDescription = -1;
                    break;
                default:
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
                    // __LINE__: 12370
                    UTIL_ASSERT(FALSE);
                }

                pCreateChar->UpdateHelp(m_pPanel->m_nID, 5, strDescription);
                pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }
}

// NOTE: Inlined.
BYTE CUIControlButtonCharGenGenderSelection::GetGender()
{
    switch (m_nID) {
    case 2:
    case 7:
        return CAIOBJECTTYPE_SEX_MALE;
    case 3:
    case 8:
        return CAIOBJECTTYPE_SEX_FEMALE;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 12415
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x61BC40
CUIControlButtonCharGenClassSelection::CUIControlButtonCharGenClassSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CString sClassName;
    // FIXME: Unused.
    STR_RES strRes;

    pGame->m_ruleTables.GetClassStringLower(GetClass(), 0x4000, 0, sClassName, 1);
    SetText(sClassName);
    m_nSelectedFrame = 0;
}

// 0x61BE30
CUIControlButtonCharGenClassSelection::~CUIControlButtonCharGenClassSelection()
{
}

// 0x61BED0
void CUIControlButtonCharGenClassSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pSprite->m_baseStats.m_specialization = 0;

        BYTE nClass = GetClass();
        CAIObjectType typeAI(pSprite->m_startTypeAI);
        typeAI.m_nAvClass = nClass;
        typeAI.m_nClass = nClass;
        typeAI.m_nClassMask = 0;
        typeAI.AddClass(nClass);
        pSprite->m_startTypeAI.Set(typeAI);

        STRREF strDescription;
        switch (m_nID) {
        case 2:
            strDescription = 37;
            break;
        case 3:
            strDescription = 9562;
            break;
        case 4:
            strDescription = 9559;
            break;
        case 5:
            strDescription = 9560;
            break;
        case 6:
            strDescription = 9556;
            break;
        case 7:
            strDescription = 36;
            break;
        case 8:
            strDescription = 9558;
            break;
        case 9:
            strDescription = 9557;
            break;
        case 10:
            strDescription = 9561;
            break;
        case 11:
            strDescription = 35;
            break;
        case 12:
            strDescription = 9563;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 12562
            UTIL_ASSERT(FALSE);
        }

        switch (m_nID) {
        case 2:
        case 3:
        case 5:
        case 6:
        case 9:
        case 10:
            pCreateChar->UpdateHelp(m_pPanel->m_nID, 16, strDescription);
            pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
            break;
        case 4:
        case 12:
            pCreateChar->SummonPopup(12, pSprite);
            break;
        case 7:
        case 8:
            pCreateChar->SummonPopup(52, pSprite);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 12596
            UTIL_ASSERT(FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// NOTE: Inlined.
BYTE CUIControlButtonCharGenClassSelection::GetClass()
{
    switch (m_nID) {
    case 2:
        return CAIOBJECTTYPE_C_BARBARIAN;
    case 3:
        return CAIOBJECTTYPE_C_BARD;
    case 4:
        return CAIOBJECTTYPE_C_CLERIC;
    case 5:
        return CAIOBJECTTYPE_C_DRUID;
    case 6:
        return CAIOBJECTTYPE_C_FIGHTER;
    case 7:
        return CAIOBJECTTYPE_C_MONK;
    case 8:
        return CAIOBJECTTYPE_C_PALADIN;
    case 9:
        return CAIOBJECTTYPE_C_RANGER;
    case 10:
        return CAIOBJECTTYPE_C_ROGUE;
    case 11:
        return CAIOBJECTTYPE_C_SORCERER;
    case 12:
        return CAIOBJECTTYPE_C_WIZARD;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 12662
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x61C1E0
CUIControlButtonCharGenRaceSelection::CUIControlButtonCharGenRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;

    STRREF strText;
    switch (m_nID) {
    case 2:
        strText = 7193; // "Human"
        break;
    case 3:
        strText = 7182; // "Dwarf"
        break;
    case 4:
        strText = 7194; // "Elf"
        break;
    case 5:
        strText = 7196; // "Gnome"
        break;
    case 6:
        strText = 7197; // "Half-Elf"
        break;
    case 7:
        strText = 22; // "Half-Orc"
        break;
    case 8:
        strText = 7195; // "Halfling"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 12727
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(strText, strRes);
    SetText(strRes.szText);
    m_nSelectedFrame = 0;
}

// 0x61C340
CUIControlButtonCharGenRaceSelection::~CUIControlButtonCharGenRaceSelection()
{
}

// 0x61C3E0
void CUIControlButtonCharGenRaceSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CAIObjectType typeAI(pSprite->m_startTypeAI);
        typeAI.m_nRace = GetRace();
        pSprite->m_startTypeAI.Set(typeAI);

        STRREF strDescription;
        switch (m_nID) {
        case 2:
            strDescription = 9550;
            break;
        case 3:
            strDescription = 9551;
            break;
        case 4:
            strDescription = 9552;
            break;
        case 5:
            strDescription = 9553;
            break;
        case 6:
            strDescription = 9555;
            break;
        case 7:
            strDescription = 25;
            break;
        case 8:
            strDescription = 9554;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 12820
            UTIL_ASSERT(FALSE);
        }

        switch (m_nID) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
            pCreateChar->SummonPopup(54, pSprite);
            break;
        case 6:
        case 7:
            pCreateChar->UpdateHelp(m_pPanel->m_nID, 9, strDescription);
            pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 12843
            UTIL_ASSERT(FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// NOTE: Inlined.
BYTE CUIControlButtonCharGenRaceSelection::GetRace()
{
    switch (m_nID) {
    case 2:
        return CAIOBJECTTYPE_R_HUMAN;
    case 3:
        return CAIOBJECTTYPE_R_DWARF;
    case 4:
        return CAIOBJECTTYPE_R_ELF;
    case 5:
        return CAIOBJECTTYPE_R_GNOME;
    case 6:
        return CAIOBJECTTYPE_R_HALF_ELF;
    case 7:
        return CAIOBJECTTYPE_R_HALF_ORC;
    case 8:
        return CAIOBJECTTYPE_R_HALFLING;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 12897
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x61C8F0
CUIControlEditCharGen::CUIControlEditCharGen(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, 0)
{
}

// 0x61C940
CUIControlEditCharGen::~CUIControlEditCharGen()
{
}

// 0x61CA10
void CUIControlEditCharGen::OnKeyDown(SHORT nKey)
{
    CUIControlEdit::OnKeyDown(nKey);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13111
    UTIL_ASSERT(pCreateChar != NULL);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (m_nID == 7) {
            pCreateChar->OnCharacterExportItemSelect(-1);
        }

        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x61CAE0
void CUIControlEditCharGen::OnEditReturn(CString sText)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (m_nID == 7) {
            pCreateChar->OnCharacterExportItemSelect(-1);
        }

        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x61CBC0
CUIControlButtonClericWizardSpecializationSelection::CUIControlButtonClericWizardSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x61CC20
CUIControlButtonClericWizardSpecializationSelection::~CUIControlButtonClericWizardSpecializationSelection()
{
}

// 0x61CCC0
DWORD CUIControlButtonClericWizardSpecializationSelection::GetSpecialization(BYTE nClass)
{
    switch (nClass) {
    case CAIOBJECTTYPE_C_WIZARD:
        switch (m_nID) {
        case 2:
            return 0x40;
        case 3:
            return 0x80;
        case 4:
            return 0x100;
        case 5:
            return 0x200;
        case 6:
            return 0x800;
        case 7:
            return 0x400;
        case 8:
            return 0x1000;
        case 9:
            return 0x2000;
        case 13:
            return 0x4000;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 13273
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (m_nID) {
        case 2:
            return 0x10000;
        case 3:
            return 0x20000;
        case 4:
            return 0x40000;
        case 5:
            return 0x80000;
        case 6:
            return 0x200000;
        case 7:
            return 0x100000;
        case 8:
            return 0x400000;
        case 9:
            return 0x800000;
        case 13:
            return 0x8000;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 13310
            UTIL_ASSERT(FALSE);
        }
        break;
    }

    return 0;
}

// 0x61CE20
void CUIControlButtonClericWizardSpecializationSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CAIObjectType typeAI(pSprite->m_startTypeAI);
        DWORD nSpecialization = GetSpecialization(typeAI.m_nClass);

        DWORD nSpecializationMask = 0;
        switch (typeAI.m_nClass) {
        case CAIOBJECTTYPE_C_WIZARD:
            nSpecializationMask = 0x7FC0;
            break;
        case CAIOBJECTTYPE_C_CLERIC:
            nSpecializationMask = 0xFF8000;
            break;
        }

        pSprite->m_baseStats.m_specialization &= ~nSpecializationMask;
        pSprite->m_baseStats.m_specialization |= nSpecialization;

        STRREF strDescription;
        switch (nSpecialization) {
        case 0x40:
            strDescription = 9564;
            break;
        case 0x80:
            strDescription = 9565;
            break;
        case 0x100:
            strDescription = 9566;
            break;
        case 0x200:
            strDescription = 9567;
            break;
        case 0x400:
            strDescription = 9568;
            break;
        case 0x800:
            strDescription = 9569;
            break;
        case 0x1000:
            strDescription = 9570;
            break;
        case 0x2000:
            strDescription = 9571;
            break;
        case 0x4000:
            strDescription = 9563;
            break;
        case 0x8000:
            strDescription = 38118;
            break;
        case 0x10000:
            strDescription = 38119;
            break;
        case 0x20000:
            strDescription = 38120;
            break;
        case 0x40000:
            strDescription = 38121;
            break;
        case 0x80000:
            strDescription = 38122;
            break;
        case 0x100000:
            strDescription = 38123;
            break;
        case 0x200000:
            strDescription = 38124;
            break;
        case 0x400000:
            strDescription = 38125;
            break;
        case 0x800000:
            strDescription = 38126;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 13447
            UTIL_ASSERT(FALSE);
        }

        pCreateChar->UpdateHelp(m_pPanel->m_nID, 11, strDescription);
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x61D820
CUIControlButtonCharGenAppearanceCustom::CUIControlButtonCharGenAppearanceCustom(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(17545, strRes);
    SetText(strRes.szText);
}

// 0x61D910
CUIControlButtonCharGenAppearanceCustom::~CUIControlButtonCharGenAppearanceCustom()
{
}

// 0x61D9B0
void CUIControlButtonCharGenAppearanceCustom::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13765
    UTIL_ASSERT(pCreateChar != NULL);

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->SummonPopup(18, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x61F220
void CUIControlButtonCharGenAbilitiesHotArea::OnHotAreaClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 14868
    UTIL_ASSERT(pCreateChar != NULL);

    CString sValue;
    DWORD strDescription;
    BYTE nMin;
    BYTE nMax;
    switch (m_nID) {
    case 30:
        strDescription = 3582;
        nMin = pCreateChar->m_nMinSTR;
        nMax = pCreateChar->m_nMaxSTR;
        break;
    case 31:
        strDescription = 9584;
        nMin = pCreateChar->m_nMinDEX;
        nMax = pCreateChar->m_nMaxDEX;
        break;
    case 32:
        strDescription = 9583;
        nMin = pCreateChar->m_nMinCON;
        nMax = pCreateChar->m_nMaxCON;
        break;
    case 33:
        strDescription = 9585;
        nMin = pCreateChar->m_nMinINT;
        nMax = pCreateChar->m_nMaxINT;
        break;
    case 34:
        strDescription = 9586;
        nMin = pCreateChar->m_nMinWIS;
        nMax = pCreateChar->m_nMaxWIS;
        break;
    case 35:
        strDescription = 9587;
        nMin = pCreateChar->m_nMinCHR;
        nMax = pCreateChar->m_nMaxCHR;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 18908
        UTIL_ASSERT(FALSE);
    }

    sValue.Format("%d", nMin);
    g_pBaldurChitin->m_cTlkTable.SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->m_cTlkTable.SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

    pCreateChar->UpdateHelp(m_pPanel->m_nID, 29, strDescription);
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61F430
void CUIControlButtonCharGenSkillsHotArea::OnHotAreaClick(CPoint pt)
{
    DWORD offset;
    switch (m_nID) {
    case 93:
        offset = 0;
        break;
    case 94:
        offset = 1;
        break;
    case 95:
        offset = 2;
        break;
    case 96:
        offset = 3;
        break;
    case 97:
        offset = 4;
        break;
    case 98:
        offset = 5;
        break;
    case 99:
        offset = 6;
        break;
    case 100:
        offset = 7;
        break;
    case 101:
        offset = 8;
        break;
    case 102:
        offset = 9;
        break;
    case 103:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14993
        UTIL_ASSERT(FALSE);
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    DWORD id = pGame->m_ruleTables.GetSkillId(offset + g_pBaldurChitin->m_pEngineCreateChar->m_nTopSkill);
    STRREF strDescription = pGame->m_ruleTables.GetSkillDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    // FIXME: Same call, what for?
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);
}

// -----------------------------------------------------------------------------

// 0x61F550
CUIControlButtonCharGenPopupCancel::CUIControlButtonCharGenPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15416, strRes); // "Back"
    SetText(strRes.szText);
}

// 0x61F640
CUIControlButtonCharGenPopupCancel::~CUIControlButtonCharGenPopupCancel()
{
}

// 0x61F6E0
void CUIControlButtonCharGenPopupCancel::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->m_pEngineCreateChar->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x61F700
CUIControlScrollBarCharGenHatedRace::CUIControlScrollBarCharGenHatedRace(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarCharGenHatedRace::~CUIControlScrollBarCharGenHatedRace()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharGenHatedRace::UpdateScrollBar()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15192
    UTIL_ASSERT(pCreateChar != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15194
    UTIL_ASSERT(pCreateChar != NULL);

    AdjustScrollBar(pCreateChar->m_nTopFeat, CSCREENCREATECHAR_NUM_HATEDRACES, 11);
}

// 0x61F720
void CUIControlScrollBarCharGenHatedRace::OnScrollUp()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15224
    UTIL_ASSERT(pCreateChar != NULL);

    INT nTopHatedRace = max(pCreateChar->m_nTopHatedRace - 1, 0);

    if (nTopHatedRace != pCreateChar->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCreateChar->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x61F800
void CUIControlScrollBarCharGenHatedRace::OnScrollDown()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15260
    UTIL_ASSERT(pCreateChar != NULL);

    INT nTopHatedRace = min(pCreateChar->m_nTopHatedRace + 1, 5);

    if (nTopHatedRace != pCreateChar->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCreateChar->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x61F8E0
void CUIControlScrollBarCharGenHatedRace::OnPageUp(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15296
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, 11);
    INT nTopHatedRace = max(pCreateChar->m_nTopHatedRace - nStep, 0);

    if (nTopHatedRace != pCreateChar->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCreateChar->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x61F9E0
void CUIControlScrollBarCharGenHatedRace::OnPageDown(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15334
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, 11);
    INT nTopHatedRace = min(pCreateChar->m_nTopHatedRace + nStep, 5);

    if (nTopHatedRace != pCreateChar->m_nTopHatedRace) {
        // NOTE: Uninline.
        pCreateChar->SetTopHatedRace(nTopHatedRace);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x61FAE0
void CUIControlScrollBarCharGenHatedRace::OnScroll()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15372
    UTIL_ASSERT(pCreateChar != NULL);

    // NOTE: Uninline.
    pCreateChar->SetTopHatedRace(5 * field_144 / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61FBC0
void CUIControlScrollBarCharGenHatedRace::InvalidateItems()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15404
    UTIL_ASSERT(pCreateChar != NULL);

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x61FCE0
CUIControlButtonCharGenHatedRaceSelection::CUIControlButtonCharGenHatedRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nNotSelectedFrame = m_nNormalFrame;
    m_nSelectedFrame = 0;
}

// 0x61FD50
CUIControlButtonCharGenHatedRaceSelection::~CUIControlButtonCharGenHatedRaceSelection()
{
}

// 0x61FDF0
void CUIControlButtonCharGenHatedRaceSelection::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15491
    UTIL_ASSERT(pCreateChar != NULL);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        INT nIndex = pCreateChar->m_nTopHatedRace + m_nID - 22;

        // NOTE: Uninline.
        BYTE nRace = pCreateChar->GetHatedRace(nIndex);
        pSprite->m_baseStats.m_favoredEnemies[0] = nRace;

        STRREF strHelp;
        switch (nRace) {
        case 113:
            strHelp = 15998;
            break;
        case 118:
            strHelp = 37619;
            break;
        case 153:
            strHelp = 3291;
            break;
        case 155:
            strHelp = 3293;
            break;
        case 160:
            strHelp = 3294;
            break;
        case 161:
            strHelp = 3295;
            break;
        case 165:
            strHelp = 3299;
            break;
        case 166:
            strHelp = 3300;
            break;
        case 167:
            strHelp = 3297;
            break;
        case 168:
            strHelp = 3301;
            break;
        case 174:
            strHelp = 37618;
            break;
        case 180:
            strHelp = 8032;
            break;
        case 181:
            strHelp = 37608;
            break;
        case 182:
            strHelp = 41079;
            break;
        case 191:
            strHelp = 37609;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 15590
            UTIL_ASSERT(FALSE);
        }

        pCreateChar->UpdateHelp(m_pPanel->m_nID, 12, strHelp);
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x620050
CUIControlButtonCharGenCancel::CUIControlButtonCharGenCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x620140
CUIControlButtonCharGenCancel::~CUIControlButtonCharGenCancel()
{
}

// 0x6201E0
void CUIControlButtonCharGenCancel::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15654
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->OnMainCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x621500
CUIControlTextDisplayCharGenImportCharacters::CUIControlTextDisplayCharGenImportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603670
CUIControlTextDisplayCharGenImportCharacters::~CUIControlTextDisplayCharGenImportCharacters()
{
}

// 0x621530
void CUIControlTextDisplayCharGenImportCharacters::OnItemSelected(LONG lMarker)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16272
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->OnCharacterImportItemSelect(lMarker);
}

// -----------------------------------------------------------------------------

// 0x621720
CUIControlTextDisplayCharGenSoundSounds::CUIControlTextDisplayCharGenSoundSounds(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603670
CUIControlTextDisplayCharGenSoundSounds::~CUIControlTextDisplayCharGenSoundSounds()
{
}

// 0x621750
void CUIControlTextDisplayCharGenSoundSounds::OnItemSelected(LONG lMarker)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16381
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->OnSoundItemSelect(lMarker);
}

// -----------------------------------------------------------------------------

// 0x621800
CUIControlButtonMonkPaladinSpecializationSelection::CUIControlButtonMonkPaladinSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x621860
CUIControlButtonMonkPaladinSpecializationSelection::~CUIControlButtonMonkPaladinSpecializationSelection()
{
}

// 0x621900
DWORD CUIControlButtonMonkPaladinSpecializationSelection::GetHelp(CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    CString sClass = g_pBaldurChitin->GetObjectGame()->m_ruleTables.GetClassString(typeAI.m_nClass,
        pSprite->m_baseStats.m_specialization);

    DWORD str = atol(g_pBaldurChitin->GetObjectGame()->m_ruleTables.m_tKitList.GetAt(CString("HELP"), sClass));
    if (str != 0) {
        return str;
    }

    switch (typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
        return 37;
    case CAIOBJECTTYPE_C_BARD:
        return 9562;
    case CAIOBJECTTYPE_C_CLERIC:
        return 9559;
    case CAIOBJECTTYPE_C_DRUID:
        return 9560;
    case CAIOBJECTTYPE_C_FIGHTER:
        return 9556;
    case CAIOBJECTTYPE_C_MONK:
        return 36;
    case CAIOBJECTTYPE_C_PALADIN:
        return 9558;
    case CAIOBJECTTYPE_C_RANGER:
        return 9557;
    case CAIOBJECTTYPE_C_ROGUE:
        return 9561;
    case CAIOBJECTTYPE_C_SORCERER:
        return 35;
    case CAIOBJECTTYPE_C_WIZARD:
        return 9563;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 16523
        UTIL_ASSERT(FALSE);
    }
}

// 0x621CE0
void CUIControlButtonMonkPaladinSpecializationSelection::OnLButtonClick(CPoint pt)
{
    CUIControlButton3State::OnLButtonClick(pt);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CAIObjectType typeAI(pSprite->m_startTypeAI);

        DWORD nSpecialization = 0;
        switch (typeAI.m_nClass) {
        case CAIOBJECTTYPE_C_MONK:
            nSpecialization = 8 << (m_nID - 1);
            break;
        case CAIOBJECTTYPE_C_PALADIN:
            nSpecialization = 1 << (m_nID - 1);
            break;
        }

        pSprite->m_baseStats.m_specialization = nSpecialization;

        pCreateChar->UpdateHelp(m_pPanel->m_nID, 12, GetHelp(pSprite));
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x621E40
CUIControlButtonCharGenSubRaceSelection::CUIControlButtonCharGenSubRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x621EA0
CUIControlButtonCharGenSubRaceSelection::~CUIControlButtonCharGenSubRaceSelection()
{
}

// 0x621F40
DWORD CUIControlButtonCharGenSubRaceSelection::GetHelp(const CAIObjectType& typeAI)
{
    INT nIndex = 0;
    switch (m_nID) {
    case 1:
        nIndex = 0;
        break;
    case 2:
        nIndex = 1;
        break;
    case 3:
        nIndex = 2;
        break;
    case 4:
        nIndex = 3;
        break;
    }

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nSubRaceListIndex = atol(pCreateChar->m_tSubRace.GetAt(CPoint(0, nIndex)));
    INT nSubRaceId = atol(g_pBaldurChitin->GetObjectGame()->m_ruleTables.m_tSrList.GetAt(CPoint(4, nSubRaceListIndex)));

    STRREF strHelp;
    if (pCreateChar->m_tSubRace.GetResRef() != "" && nSubRaceId != 0) {
        strHelp = atol(g_pBaldurChitin->GetObjectGame()->m_ruleTables.m_tSrList.GetAt(CPoint(2, nSubRaceListIndex)));
    } else {
        switch (typeAI.m_nRace) {
        case CAIOBJECTTYPE_R_HUMAN:
            strHelp = 9550;
            break;
        case CAIOBJECTTYPE_R_ELF:
            strHelp = 9552;
            break;
        case CAIOBJECTTYPE_R_HALF_ELF:
            strHelp = 9555;
            break;
        case CAIOBJECTTYPE_R_DWARF:
            strHelp = 9551;
            break;
        case CAIOBJECTTYPE_R_HALFLING:
            strHelp = 9554;
            break;
        case CAIOBJECTTYPE_R_GNOME:
            strHelp = 9553;
            break;
        case CAIOBJECTTYPE_R_HALF_ORC:
            strHelp = 25;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 16730
            UTIL_ASSERT(FALSE);
        }
    }

    return strHelp;
}

// 0x622130
void CUIControlButtonCharGenSubRaceSelection::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x622360
CUIControlButtonCharGenBiography::CUIControlButtonCharGenBiography(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16809
    UTIL_ASSERT(pCreateChar != NULL);

    SetText(CBaldurEngine::FetchString(18003));
}

// 0x622430
CUIControlButtonCharGenBiography::~CUIControlButtonCharGenBiography()
{
}

// 0x6224D0
void CUIControlButtonCharGenBiography::OnLButtonClick(CPoint pt)
{
    if (m_bEnabled) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
        CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 16837
        UTIL_ASSERT(pGame != NULL && pCreateChar != NULL);

        INT nGameSprite = pCreateChar->GetSpriteId();

        CGameSprite* pSprite;
        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pCreateChar->SummonPopup(51, pSprite);

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// -----------------------------------------------------------------------------

// 0x622580
CUIControlButtonCharacterBiographyClear::CUIControlButtonCharacterBiographyClear(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16880
    UTIL_ASSERT(pCreateChar != NULL);

    SetText(CBaldurEngine::FetchString(18622));
}

// 0x622650
CUIControlButtonCharacterBiographyClear::~CUIControlButtonCharacterBiographyClear()
{
}

// 0x6226F0
void CUIControlButtonCharacterBiographyClear::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x622730
CUIControlButtonCharacterBiographyRevert::CUIControlButtonCharacterBiographyRevert(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16928
    UTIL_ASSERT(pCreateChar != NULL);

    SetText(CBaldurEngine::FetchString(2240));
}

// 0x622800
CUIControlButtonCharacterBiographyRevert::~CUIControlButtonCharacterBiographyRevert()
{
}

// 0x6228A0
void CUIControlButtonCharacterBiographyRevert::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x622AC0
void CUIControlButtonCharGenFeatsHotArea::OnHotAreaClick(CPoint pt)
{
    DWORD offset;
    switch (m_nID) {
    case 93:
        offset = 0;
        break;
    case 94:
        offset = 1;
        break;
    case 95:
        offset = 2;
        break;
    case 96:
        offset = 3;
        break;
    case 97:
        offset = 4;
        break;
    case 98:
        offset = 5;
        break;
    case 99:
        offset = 6;
        break;
    case 100:
        offset = 7;
        break;
    case 101:
        offset = 8;
        break;
    case 102:
        offset = 9;
        break;
    case 103:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17069
        UTIL_ASSERT(FALSE);
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    DWORD id = pGame->m_ruleTables.GetFeatId(offset + g_pBaldurChitin->m_pEngineCreateChar->m_nTopFeat);
    STRREF strDescription = pGame->m_ruleTables.GetFeatDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);
}

// -----------------------------------------------------------------------------

// 0x622BC0
CUIControlScrollBarCharGenFeats::CUIControlScrollBarCharGenFeats(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarCharGenFeats::~CUIControlScrollBarCharGenFeats()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharGenFeats::UpdateScrollBar()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17119
    UTIL_ASSERT(pCreateChar != NULL);

    AdjustScrollBar(pCreateChar->m_nTopFeat, FEAT_COUNT, FEAT_SLOTS);
}

// 0x622BE0
void CUIControlScrollBarCharGenFeats::OnScrollUp()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17144
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->m_nTopFeat = max(pCreateChar->m_nTopFeat - 1, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622C80
void CUIControlScrollBarCharGenFeats::OnScrollDown()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17168
    UTIL_ASSERT(pCreateChar != NULL);

    if (pCreateChar->m_nTopFeat < FEAT_COUNT - FEAT_SLOTS) {
        pCreateChar->m_nTopFeat++;
    }

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622D30
void CUIControlScrollBarCharGenFeats::OnPageUp(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17197
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, FEAT_SLOTS - 1);
    pCreateChar->m_nTopFeat = max(pCreateChar->m_nTopFeat - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622DE0
void CUIControlScrollBarCharGenFeats::OnPageDown(int a1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17225
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(a1, FEAT_SLOTS - 1);
    pCreateChar->m_nTopFeat += nStep;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622E80
void CUIControlScrollBarCharGenFeats::OnScroll()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11418
    UTIL_ASSERT(pCreateChar != NULL);

    INT nTopFeat = max(FEAT_COUNT * field_144, 0) / field_142;
    pCreateChar->m_nTopFeat = max(min(nTopFeat - FEAT_SLOTS, FEAT_COUNT - FEAT_SLOTS), 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622F50
void CUIControlScrollBarCharGenFeats::InvalidateItems()
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11445
    UTIL_ASSERT(pCreateChar != NULL);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x623070
CUIControlButtonCharGenFeatsPlusMinus::CUIControlButtonCharGenFeatsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x6230B0
CUIControlButtonCharGenFeatsPlusMinus::~CUIControlButtonCharGenFeatsPlusMinus()
{
}

// 0x623150
BOOL CUIControlButtonCharGenFeatsPlusMinus::OnLButtonDown(CPoint pt)
{
    DWORD offset;
    switch (m_nID) {
    case 14:
    case 15:
        offset = 0;
        break;
    case 16:
    case 17:
        offset = 1;
        break;
    case 18:
    case 19:
        offset = 2;
        break;
    case 20:
    case 21:
        offset = 3;
        break;
    case 22:
    case 23:
        offset = 4;
        break;
    case 24:
    case 25:
        offset = 5;
        break;
    case 26:
    case 27:
        offset = 6;
        break;
    case 28:
    case 29:
        offset = 7;
        break;
    case 30:
    case 31:
        offset = 8;
        break;
    case 32:
    case 33:
        offset = 9;
        break;
    case 34:
    case 35:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 11586
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    DWORD id = pGame->m_ruleTables.GetFeatId(g_pBaldurChitin->m_pEngineCreateChar->m_nTopFeat + offset);
    STRREF strDescription = pGame->m_ruleTables.GetFeatDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return OnLButtonDown(pt);
}

// 0x6232A0
void CUIControlButtonCharGenFeatsPlusMinus::AdjustValue()
{
    BOOL bInc;
    switch (m_nID) {
    case 14:
    case 16:
    case 18:
    case 20:
    case 22:
    case 24:
    case 26:
    case 28:
    case 30:
    case 32:
    case 34:
        bInc = TRUE;
        break;
    case 15:
    case 17:
    case 19:
    case 21:
    case 23:
    case 25:
    case 27:
    case 29:
    case 31:
    case 35:
        bInc = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17507
        UTIL_ASSERT(FALSE);
    }

    DWORD offset;
    switch (m_nID) {
    case 14:
    case 15:
        offset = 0;
        break;
    case 16:
    case 17:
        offset = 1;
        break;
    case 18:
    case 19:
        offset = 2;
        break;
    case 20:
    case 21:
        offset = 3;
        break;
    case 22:
    case 23:
        offset = 4;
        break;
    case 24:
    case 25:
        offset = 5;
        break;
    case 26:
    case 27:
        offset = 6;
        break;
    case 28:
    case 29:
        offset = 7;
        break;
    case 30:
    case 31:
        offset = 8;
        break;
    case 32:
    case 33:
        offset = 9;
        break;
    case 34:
    case 35:
        offset = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17570
        UTIL_ASSERT(FALSE);
    }

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        DWORD id = g_pBaldurChitin->GetObjectGame()->m_ruleTables.GetFeatId(pCreateChar->m_nTopFeat + offset);
        INT nValue = pSprite->GetFeatValue(id);

        if (bInc) {
            if (pSprite->sub_763A40(id, 1) && pCreateChar->m_nExtraFeats > 0) {
                pSprite->SetFeatValue(id, nValue + 1);
                pCreateChar->m_nExtraFeats--;
            }
        } else {
            if (nValue > 0 && pCreateChar->m_storedFeats[id] < pSprite->GetFeatValue(id)) {
                pSprite->SetFeatValue(id, nValue - 1);
                pCreateChar->m_nExtraFeats++;

                CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
                for (INT nFeat = 0; nFeat < pGame->m_ruleTables.m_tFeats.GetHeight(); nFeat++) {
                    while (pSprite->GetFeatValue(nFeat) > 0) {
                        if (pSprite->sub_763200(nFeat, 1)) {
                            break;
                        }

                        pSprite->SetFeatValue(nFeat, pSprite->GetFeatValue(nFeat) - 1);
                        pCreateChar->m_nExtraFeats++;
                    }
                }
            }
        }

        pCreateChar->UpdatePopupPanel(pCreateChar->GetTopPopup()->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

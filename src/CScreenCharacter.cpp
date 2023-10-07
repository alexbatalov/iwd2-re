#include "CScreenCharacter.h"

#include "CAIObjectType.h"
#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenCreateChar.h"
#include "CScreenWorld.h"
#include "CSpell.h"
#include "CUIControlEditMultiLine.h"
#include "CUIControlFactory.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define FEAT_COUNT CGAMESPRITE_FEAT_NUMFEATS
#define FEAT_SLOTS 9

#define SKILL_COUNT CGAMESPRITE_SKILL_NUMSKILLS
#define SKILL_SLOTS 9

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
    m_bShiftKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    field_780 = 0;
    m_nExtraSkillPoints = 0;
    field_79C = 0;
    field_7A0 = 0;
    field_7A4 = 0;
    field_7A8 = 0;
    field_7AC = 0;
    field_7B0 = 0;
    m_nExtraMageSpells = 0;
    field_7BA = 0;
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    m_nCharacterIndex = 0;
    m_nTopHatedRace = 0;
    m_bMultiPlayerViewable = FALSE;
    m_bMultiPlayerModifyable = FALSE;
    m_nCurrentPortrait = 0;
    m_nPortraitSmallIndex = 0;
    m_nPortraitLargeIndex = 0;
    m_nCustomSoundSetIndex = 0;
    m_nCustomSoundIndex = 0;
    field_81A = 0;
    m_nSpecialization = 0;
    field_1772 = 0;
    field_1776 = 0;
    field_17A0 = 0;
    m_nClass = 0;
    field_17A4 = 0;
    m_nMinSTR = 0;
    m_nMinDEX = 0;
    m_nMinCON = 0;
    m_nMinINT = 0;
    m_nMinWIS = 0;
    m_nMinCHR = 0;
    m_nMaxSTR = 0;
    m_nMaxDEX = 0;
    m_nMaxCON = 0;
    m_nMaxINT = 0;
    m_nMaxWIS = 0;
    m_nMaxCHR = 0;
    m_nModSTR = 0;
    m_nModDEX = 0;
    m_nModCON = 0;
    m_nModINT = 0;
    m_nModWIS = 0;
    m_nModCHR = 0;
    field_17A8 = 0;
    field_17C0 = 0;
    field_1800 = 0;

    SetVideoMode(0);

    m_pVirtualKeys[0] = CKeyInfo(VK_ESCAPE, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo('1', 0, 0);
    m_pVirtualKeys[2] = CKeyInfo('2', 0, 0);
    m_pVirtualKeys[3] = CKeyInfo('3', 0, 0);
    m_pVirtualKeys[4] = CKeyInfo('4', 0, 0);
    m_pVirtualKeys[5] = CKeyInfo('5', 0, 0);
    m_pVirtualKeys[6] = CKeyInfo('6', 0, 0);
    m_pVirtualKeys[7] = CKeyInfo('7', 0, 0);
    m_pVirtualKeys[8] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[9] = CKeyInfo('9', 0, 0);
    m_pVirtualKeys[10] = CKeyInfo(VK_SPACE, -1, 0);
    m_pVirtualKeys[11] = CKeyInfo('A', 0, 0);
    m_pVirtualKeys[12] = CKeyInfo('B', 0, 0);
    m_pVirtualKeys[13] = CKeyInfo('C', 0, 0);
    m_pVirtualKeys[14] = CKeyInfo('D', 0, 0);
    m_pVirtualKeys[15] = CKeyInfo('E', 0, 0);
    m_pVirtualKeys[16] = CKeyInfo('F', 0, 0);
    m_pVirtualKeys[17] = CKeyInfo('G', 0, 0);
    m_pVirtualKeys[18] = CKeyInfo('H', 0, 0);
    m_pVirtualKeys[19] = CKeyInfo('I', 0, 0);
    m_pVirtualKeys[20] = CKeyInfo('J', 0, 0);
    m_pVirtualKeys[21] = CKeyInfo('K', 0, 0);
    m_pVirtualKeys[22] = CKeyInfo('L', 0, 0);
    m_pVirtualKeys[23] = CKeyInfo('M', 0, 0);
    m_pVirtualKeys[24] = CKeyInfo('N', 0, 0);
    m_pVirtualKeys[25] = CKeyInfo('O', 0, 0);
    m_pVirtualKeys[26] = CKeyInfo('P', 0, 0);
    m_pVirtualKeys[27] = CKeyInfo('Q', 0, 0);
    m_pVirtualKeys[28] = CKeyInfo('R', 0, 0);
    m_pVirtualKeys[29] = CKeyInfo('S', 0, 0);
    m_pVirtualKeys[30] = CKeyInfo('T', 0, 0);
    m_pVirtualKeys[31] = CKeyInfo('U', 0, 0);
    m_pVirtualKeys[32] = CKeyInfo('V', 0, 0);
    m_pVirtualKeys[33] = CKeyInfo('W', 0, 0);
    m_pVirtualKeys[34] = CKeyInfo('X', 0, 0);
    m_pVirtualKeys[35] = CKeyInfo('Y', 0, 0);
    m_pVirtualKeys[36] = CKeyInfo('Z', 0, 0);
    m_pVirtualKeys[37] = CKeyInfo('0', 0, 0);
    m_pVirtualKeys[38] = CKeyInfo(VK_BACK, 0, 0);
    m_pVirtualKeys[39] = CKeyInfo(VK_END, -1, 0);
    m_pVirtualKeys[40] = CKeyInfo(VK_HOME, -1, 0);
    m_pVirtualKeys[41] = CKeyInfo(VK_LEFT, static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND), static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND));
    m_pVirtualKeys[42] = CKeyInfo(VK_UP, 4, 0);
    m_pVirtualKeys[43] = CKeyInfo(VK_RIGHT, static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND), static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND));
    m_pVirtualKeys[44] = CKeyInfo(VK_DOWN, 0, 0);
    m_pVirtualKeys[45] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[46] = CKeyInfo(VK_INSERT, -1, 0);
    m_pVirtualKeys[47] = CKeyInfo(VK_DELETE, 0, 0);
    m_pVirtualKeys[48] = CKeyInfo(VK_NUMPAD0, -1, 0);
    m_pVirtualKeys[49] = CKeyInfo(VK_NUMPAD1, -1, 0);
    m_pVirtualKeys[50] = CKeyInfo(VK_NUMPAD2, -1, 0);
    m_pVirtualKeys[51] = CKeyInfo(VK_NUMPAD3, -1, 0);
    m_pVirtualKeys[52] = CKeyInfo(VK_NUMPAD4, static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND), static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND));
    m_pVirtualKeys[53] = CKeyInfo(VK_NUMPAD5, -1, 0);
    m_pVirtualKeys[54] = CKeyInfo(VK_NUMPAD6, static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND), static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND));
    m_pVirtualKeys[55] = CKeyInfo(VK_NUMPAD7, -1, 0);
    m_pVirtualKeys[56] = CKeyInfo(VK_NUMPAD8, -1, 0);
    m_pVirtualKeys[57] = CKeyInfo(VK_NUMPAD9, -1, 0);
    m_pVirtualKeys[58] = CKeyInfo(VK_MULTIPLY, -1, 0);
    m_pVirtualKeys[59] = CKeyInfo(VK_ADD, -1, 0);
    m_pVirtualKeys[60] = CKeyInfo(VK_SEPARATOR, -1, 0);
    m_pVirtualKeys[61] = CKeyInfo(VK_SUBTRACT, -1, 0);
    m_pVirtualKeys[62] = CKeyInfo(VK_DECIMAL, -1, 0);
    m_pVirtualKeys[63] = CKeyInfo(VK_DIVIDE, -1, 0);
    m_pVirtualKeys[64] = CKeyInfo(VK_F1, -1, 0);
    m_pVirtualKeys[65] = CKeyInfo(VK_F2, -1, 0);
    m_pVirtualKeys[66] = CKeyInfo(VK_F3, -1, 0);
    m_pVirtualKeys[67] = CKeyInfo(VK_F4, -1, 0);
    m_pVirtualKeys[68] = CKeyInfo(VK_F5, -1, 0);
    m_pVirtualKeys[69] = CKeyInfo(VK_F6, -1, 0);
    m_pVirtualKeys[70] = CKeyInfo(VK_F7, -1, 0);
    m_pVirtualKeys[71] = CKeyInfo(VK_F8, -1, 0);
    m_pVirtualKeys[72] = CKeyInfo(VK_F9, -1, 0);
    m_pVirtualKeys[73] = CKeyInfo(VK_F10, -1, 0);
    m_pVirtualKeys[74] = CKeyInfo(VK_F11, -1, 0);
    m_pVirtualKeys[75] = CKeyInfo(VK_F12, -1, 0);
    m_pVirtualKeys[76] = CKeyInfo(VK_NUMLOCK, -1, 0);
    m_pVirtualKeys[77] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[78] = CKeyInfo(VK_OEM_3, 0, 0);
    m_pVirtualKeys[79] = CKeyInfo(VK_OEM_MINUS, 0, 0);
    m_pVirtualKeys[80] = CKeyInfo(VK_OEM_PLUS, 0, 0);
    m_pVirtualKeys[81] = CKeyInfo(VK_OEM_4, 0, 0);
    m_pVirtualKeys[82] = CKeyInfo(VK_OEM_6, 0, 0);
    m_pVirtualKeys[83] = CKeyInfo(VK_OEM_5, 0, 0);
    m_pVirtualKeys[84] = CKeyInfo(VK_OEM_1, 0, 0);
    m_pVirtualKeys[85] = CKeyInfo(VK_OEM_7, 0, 0);
    m_pVirtualKeys[86] = CKeyInfo(VK_OEM_COMMA, 0, 0);
    m_pVirtualKeys[87] = CKeyInfo(VK_OEM_PERIOD, 0, 0);
    m_pVirtualKeys[88] = CKeyInfo(VK_OEM_2, 0, 0);
    m_pVirtualKeys[89] = CKeyInfo(VK_TAB, -1, 0);

    // FIXME: Buffer overrun.
    m_pVirtualKeys[90] = CKeyInfo(VK_PROCESSKEY, -1, 0);

    m_bCtrlKeyDown = FALSE;
    m_pScripts = NULL;
    m_nScriptIndex = -1;
    m_pCharacters = NULL;
    m_pPortraits = NULL;
    m_pSounds = NULL;
    m_pTempBaseStats = NULL;
    m_pTempDerivedStats = NULL;
    m_pBeforeLevelUpDerivedStats = NULL;

    for (UINT nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        if (m_spells.m_lists[nLevel].m_List.size() != 0) {
            m_spells.m_lists[nLevel].m_List.clear();
            m_spells.m_lists[nLevel].field_10 = 0;
            m_spells.m_lists[nLevel].field_14 = 0;
        }
    }
    m_spells.m_nHighestLevel = 0;

    field_2B6 = 0;
    field_866 = 0;
    field_1776 = 0;
    field_86A = 0;
    m_hatedRaces[0] = CAIObjectType::R_BUGBEAR;
    m_hatedRaces[1] = CAIObjectType::R_DRIDER;
    m_hatedRaces[2] = CAIObjectType::R_GIANT;
    m_hatedRaces[3] = CAIObjectType::R_GOBLIN;
    m_hatedRaces[4] = CAIObjectType::R_HARPY;
    m_hatedRaces[5] = CAIObjectType::R_HOOK_HORROR;
    m_hatedRaces[6] = CAIObjectType::R_LIZARDMAN;
    m_hatedRaces[7] = CAIObjectType::R_OGRE;
    m_hatedRaces[8] = CAIObjectType::R_ORC;
    m_hatedRaces[9] = CAIObjectType::R_SALAMANDER;
    m_hatedRaces[10] = CAIObjectType::R_SHAPESHIFTER;
    m_hatedRaces[11] = CAIObjectType::R_TROLL;
    m_hatedRaces[12] = CAIObjectType::R_UMBERHULK;
    m_hatedRaces[13] = CAIObjectType::R_UNDEAD;
    m_hatedRaces[14] = CAIObjectType::R_WYVERN;
    m_hatedRaces[15] = CAIObjectType::R_YUANTI;
    field_1B8 = 0;
    field_1844 = 0;
    field_1846 = 0;
    field_184A = 0;
    field_184E = 0;
    field_1852 = 0;
}

// 0x5D63B0
CScreenCharacter::~CScreenCharacter()
{
    if (m_pTempDerivedStats != NULL) {
        delete m_pTempDerivedStats;
        m_pTempDerivedStats = NULL;
    }

    if (m_pBeforeLevelUpDerivedStats != NULL) {
        delete m_pBeforeLevelUpDerivedStats;
        m_pBeforeLevelUpDerivedStats = NULL;

        for (UINT nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            if (m_spells.m_lists[nLevel].m_List.size() != 0) {
                m_spells.m_lists[nLevel].m_List.clear();
                m_spells.m_lists[nLevel].field_14 = 0;
                m_spells.m_lists[nLevel].field_18 = 0;
            }
        }
        m_spells.m_nHighestLevel = 0;
    }

    if (m_pTempBaseStats != NULL) {
        delete m_pTempBaseStats;
        m_pTempBaseStats = NULL;
    }
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

// 0x49FC40
BOOL CScreenCharacter::CheckMouseMove()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenCharacter::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenCharacter::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenCharacter::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenCharacter::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenCharacter::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenCharacter::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenCharacter::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
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

// 0x5D6C60
void CScreenCharacter::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIREC"), g_pBaldurChitin->field_4A28);

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

    m_nSelectedCharacter = 0;
    m_pCurrentScrollBar = NULL;
    m_pScripts = NULL;
    m_nScriptIndex = -1;
    m_pCharacters = NULL;
    m_pPortraits = NULL;
    m_pSounds = NULL;
    m_pTempBaseStats = NULL;
    m_pTempDerivedStats = NULL;
    m_pBeforeLevelUpDerivedStats = NULL;

    field_866 = 0;
    field_86A = 0;

    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(16)->SetActive(FALSE);
    m_cUIManager.GetPanel(9)->SetActive(FALSE);
    m_cUIManager.GetPanel(10)->SetActive(FALSE);
    m_cUIManager.GetPanel(11)->SetActive(FALSE);
    m_cUIManager.GetPanel(12)->SetActive(FALSE);
    m_cUIManager.GetPanel(13)->SetActive(FALSE);
    m_cUIManager.GetPanel(17)->SetActive(FALSE);
    m_cUIManager.GetPanel(18)->SetActive(FALSE);
    m_cUIManager.GetPanel(19)->SetActive(FALSE);
    m_cUIManager.GetPanel(20)->SetActive(FALSE);
    m_cUIManager.GetPanel(11)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);
    m_cUIManager.GetPanel(51)->SetActive(FALSE);
    m_cUIManager.GetPanel(52)->SetActive(FALSE);
    m_cUIManager.GetPanel(53)->SetActive(FALSE);
    m_cUIManager.GetPanel(54)->SetActive(FALSE);
    m_cUIManager.GetPanel(55)->SetActive(FALSE);
    m_cUIManager.GetPanel(56)->SetActive(FALSE);
    m_cUIManager.GetPanel(57)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 797
    UTIL_ASSERT(pPanel != NULL);

    CUIControlBase* pControl;

    pControl = pPanel->GetControl(0x10000028);
    UTIL_ASSERT(pControl != NULL) // 801
    pControl->SetToolTipStrRef(17183, -1, -1); // "Armor Class"

    pControl = pPanel->GetControl(0x10000029);
    UTIL_ASSERT(pControl != NULL) // 805
    pControl->SetToolTipStrRef(17184, -1, -1); // "Current Hit Points"

    pControl = pPanel->GetControl(0x1000002A);
    UTIL_ASSERT(pControl != NULL) // 809
    pControl->SetToolTipStrRef(17378, -1, -1); // "Maximum Hit Points"

    pControl = pPanel->GetControl(0x1000002F);
    UTIL_ASSERT(pControl != NULL) // 815
    pControl->SetToolTipStrRef(1145, -1, -1); // "Strength"

    pControl = pPanel->GetControl(0x10000009);
    UTIL_ASSERT(pControl != NULL) // 819
    pControl->SetToolTipStrRef(1151, -1, -1); // "Dexterity"

    pControl = pPanel->GetControl(0x1000000A);
    UTIL_ASSERT(pControl != NULL) // 823
    pControl->SetToolTipStrRef(1178, -1, -1); // "Constitution"

    pControl = pPanel->GetControl(0x1000000B);
    UTIL_ASSERT(pControl != NULL) // 827
    pControl->SetToolTipStrRef(1179, -1, -1); // "Intelligence"

    pControl = pPanel->GetControl(0x1000000C);
    UTIL_ASSERT(pControl != NULL) // 831
    pControl->SetToolTipStrRef(1180, -1, -1); // "Wisdom"

    pControl = pPanel->GetControl(0x1000000D);
    UTIL_ASSERT(pControl != NULL) // 835
    pControl->SetToolTipStrRef(1181, -1, -1); // "Charisma"

    pControl = pPanel->GetControl(60);
    UTIL_ASSERT(pControl != NULL) // 841
    pControl->SetToolTipStrRef(40316, -1, -1); // "General"

    pControl = pPanel->GetControl(61);
    UTIL_ASSERT(pControl != NULL) // 845
    pControl->SetToolTipStrRef(40317, -1, -1); // "Weapons and Armor"

    pControl = pPanel->GetControl(62);
    UTIL_ASSERT(pControl != NULL) // 849
    pControl->SetToolTipStrRef(40318, -1, -1); // "Skills and Feats"

    pControl = pPanel->GetControl(63);
    UTIL_ASSERT(pControl != NULL) // 853
    pControl->SetToolTipStrRef(33500, -1, -1); // "Miscellaneous"
}

// 0x5D72C0
void CScreenCharacter::EngineGameUninit()
{
    m_cUIManager.fUninit();
}

// 0x5D76E0
void CScreenCharacter::OnMouseMove(CPoint pt)
{
    CUIPanel* pPanel;

    if (m_cUIManager.GetPanel(11)->m_bActive) {
        pPanel = m_cUIManager.GetPanel(11);
        if (pPanel->GetControl(2)->IsOver(pt - pPanel->m_ptOrigin)) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
        } else {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(7));
        }
    } else if (m_cUIManager.GetPanel(16)->m_bActive) {
        pPanel = m_cUIManager.GetPanel(16);
        if (pPanel->GetControl(8)->IsOver(pt - pPanel->m_ptOrigin)) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(9));
        } else {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));
        }
    } else if (m_cUIManager.GetPanel(56)->m_bActive) {
        pPanel = m_cUIManager.GetPanel(56);
        if (pPanel->GetControl(92)->IsOver(pt - pPanel->m_ptOrigin)) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(91));
        } else {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(104));
        }
    } else if (m_cUIManager.GetPanel(57)->m_bActive) {
        pPanel = m_cUIManager.GetPanel(57);
        if (pPanel->GetControl(2)->IsOver(pt - pPanel->m_ptOrigin)) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(4));
        } else {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
        }
    }

    m_cUIManager.OnMouseMove(pt);
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

// 0x5D9610
BOOL CScreenCharacter::ResetAbility(CGameSprite* pSprite, const CString& sMin, const CString& sMax, const CString& sMod, BYTE& nAbility, BYTE& nMin, BYTE& nMax, INT& nMod)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    INT nBestClass = pSprite->m_derivedStats.GetBestClass();

    CString sRace = ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    BYTE nMinRaceReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceReq.GetAt(sMin, sRace)));
    BYTE nMaxRaceReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceReq.GetAt(sMax, sRace)));
    BYTE nRaceAdj = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceAdj.GetAt(sMod, sRace)));

    CString sClass = ruleTables.GetClassString(nBestClass, pSprite->m_baseStats.m_specialization);
    BYTE nMinClassReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityClassReq.GetAt(sMin, sClass)));

    nMax = 50;
    nMin = max(nMinRaceReq + nRaceAdj, nMinClassReq);
    nMin = max(nMin, 1);
    nMod = nRaceAdj;

    return TRUE;
}

// 0x5D97B0
void CScreenCharacter::ResetAbilitiesPanel(CGameSprite* pSprite, int a2)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(7);

    if (a2) {
        m_nExtraAbilityPoints = pSprite->GetDerivedStats()->m_nLevel / 4 - m_pTempDerivedStats->m_nLevel / 4;
        ResetAbility(pSprite,
            CRuleTables::MIN_STR,
            CRuleTables::MAX_STR,
            CRuleTables::MOD_STR,
            pSprite->GetBaseStats()->m_STRBase,
            m_nMinSTR,
            m_nMaxSTR,
            m_nModSTR);
        ResetAbility(pSprite,
            CRuleTables::MIN_DEX,
            CRuleTables::MAX_DEX,
            CRuleTables::MOD_DEX,
            pSprite->GetBaseStats()->m_DEXBase,
            m_nMinDEX,
            m_nMaxDEX,
            m_nModDEX);
        ResetAbility(pSprite,
            CRuleTables::MIN_CON,
            CRuleTables::MAX_CON,
            CRuleTables::MOD_CON,
            pSprite->GetBaseStats()->m_CONBase,
            m_nMinCON,
            m_nMaxCON,
            m_nModCON);
        ResetAbility(pSprite,
            CRuleTables::MIN_INT,
            CRuleTables::MAX_INT,
            CRuleTables::MOD_INT,
            pSprite->GetBaseStats()->m_INTBase,
            m_nMinINT,
            m_nMaxINT,
            m_nModINT);
        ResetAbility(pSprite,
            CRuleTables::MIN_WIS,
            CRuleTables::MAX_WIS,
            CRuleTables::MOD_WIS,
            pSprite->GetBaseStats()->m_WISBase,
            m_nMinWIS,
            m_nMaxWIS,
            m_nModWIS);
        ResetAbility(pSprite,
            CRuleTables::MIN_CHR,
            CRuleTables::MAX_CHR,
            CRuleTables::MOD_CHR,
            pSprite->GetBaseStats()->m_CHRBase,
            m_nMinCHR,
            m_nMaxCHR,
            m_nModCHR);
    }

    UpdateHelp(pPanel->m_nID, 29, 27337);
}

// 0x5DA490
void CScreenCharacter::UpdateHatedRacePanel(CGameSprite* pSprite)
{
    CCreatureFileHeader& BStats = *pSprite->GetBaseStats();

    CUIPanel* pPanel = m_cUIManager.GetPanel(16);

    if (pPanel != NULL) {
        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));

        for (INT nSlot = 0; nSlot < 11; nSlot++) {
            INT nIndex = m_nTopHatedRace + nSlot;

            // NOTE: Uninline.
            BYTE nRace = GetHatedRace(nIndex);

            CUIControlButtonCharacterHatedRaceSelection* pButton = static_cast<CUIControlButtonCharacterHatedRaceSelection*>(pPanel->GetControl(nSlot + 22));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 3391
            UTIL_ASSERT(pButton != NULL);

            STRREF strRace = GetRangerHatedRaceStrref(nRace);
            pButton->SetText(FetchString(strRace));

            pButton->SetSelected(m_hatedRaces[nIndex] == BStats.m_favoredEnemies[field_17A0]);
            pButton->SetEnabled(!g_pBaldurChitin->GetObjectGame()->GetRuleTables().IsHatedRace(nRace, BStats) || pButton->m_bSelected);
        }

        CUIControlScrollBarCharacterHatedRace* pScrollBar = static_cast<CUIControlScrollBarCharacterHatedRace*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 3403
        UTIL_ASSERT(pScrollBar != NULL);

        // NOTE: Uninline.
        pScrollBar->UpdateScrollBar();

        CUIControlButton* pDoneButton = static_cast<CUIControlButton*>(pPanel->GetControl(10));
        pDoneButton->SetEnabled(IsDoneButtonClickable(pSprite));

        CUIControlButton* pCancelButton = static_cast<CUIControlButton*>(pPanel->GetControl(11));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 3413
        UTIL_ASSERT(pCancelButton != NULL);

        pCancelButton->SetEnabled(TRUE);
    }
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

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(5));

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

// 0x66A540
void CScreenCharacter::TimerAsynchronousUpdate()
{
    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
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

// 0x5E0200
void CScreenCharacter::UpdateMiscInformation(CUIControlTextDisplay* pText, CGameSprite* pSprite)
{
    CResRef resRef;
    CString sFavouriteSpellName;
    CString sFavouriteWeaponName;

    DWORD nPartyChapterKillsXPValue;
    DWORD nPartyChapterKillsNumber;
    DWORD nPartyGameKillsXPValue;
    DWORD nPartyGameKillsNumber;
    GetPartyInformation(nPartyChapterKillsXPValue,
        nPartyChapterKillsNumber,
        nPartyGameKillsXPValue,
        nPartyGameKillsNumber);

    UpdateTextForceColor(pText,
        RGB(200, 200, 0),
        "%s",
        FetchString(40320)); // "Favorites"

    pSprite->m_cGameStats.GetFavouriteSpell(resRef);
    if (resRef != NULL) {
        CSpell cSpell;
        cSpell.SetResRef(resRef, TRUE, TRUE);

        cSpell.Demand();
        if (cSpell.GetRes() != NULL) {
            sFavouriteSpellName = FetchString(cSpell.GetGenericName());
        } else {
            sFavouriteSpellName = "Bad spell resref";
        }
    }

    UpdateText(pText,
        "%s: %s",
        FetchString(11949), // "Favorite Spell (if applicable)"
        sFavouriteSpellName);

    sFavouriteWeaponName = "";

    pSprite->m_cGameStats.GetFavouriteWeapon(resRef);
    if (resRef != "") {
        CItem cWeapon(resRef, 0, 0, 0, 0, 0);

        if (cWeapon.GetRes() != NULL) {
            STRREF strType;
            switch (cWeapon.GetItemType()) {
            case 5:
                strType = 10476; // "Bow and <WEAPONNAME>"
                break;
            case 14:
                strType = 10478; // "Sling and <WEAPONNAME>"
                break;
            case 31:
                strType = 10477; // "Crossbow and <WEAPONNAME>"
                break;
            default:
                strType = 10479; // "<WEAPONNAME>"
                break;
            }

            g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_WEAPONNAME,
                FetchString(cWeapon.GetGenericName()));

            sFavouriteWeaponName = FetchString(strType);
        }
    }

    UpdateText(pText,
        "%s: %s",
        FetchString(11950), // "Favorite Weapon"
        sFavouriteWeaponName);

    UpdateText(pText, "");

    UpdateTextForceColor(pText,
        RGB(200, 200, 0),
        "%s",
        FetchString(40322)); // "Combat Statistics"

    STRREF strName;
    pSprite->m_cGameStats.GetStrongestKill(strName);

    UpdateText(pText,
        "%s: %s",
        FetchString(11947), // "Most Powerful Vanquished"
        FetchString(strName));

    ULONG nCurrentTimeWithParty;
    pSprite->m_cGameStats.GetTimeWithParty(nCurrentTimeWithParty);

    CString sCurrentTimeWithParty;
    CTimerWorld::GetCurrentTimeString(nCurrentTimeWithParty, 16043, sCurrentTimeWithParty);

    UpdateText(pText,
        "%s: %s",
        FetchString(11948), // "Time Spent with Party"
        sCurrentTimeWithParty);

    UpdateText(pText,
        "%s: %d",
        FetchString(11953), // "Experience Value of Kills"
        pSprite->m_cGameStats.m_nGameKillsXPValue);

    UpdateText(pText,
        "%s: %d",
        FetchString(11954), // "Number of Kills"
        pSprite->m_cGameStats.m_nGameKillsNumber);

    UpdateText(pText,
        "%s: %d%%",
        FetchString(11951), // "Total Experience Value in Party"
        nPartyGameKillsXPValue > 0
            ? 100 * pSprite->m_cGameStats.m_nGameKillsXPValue / nPartyGameKillsXPValue
            : 0);

    UpdateText(pText,
        "%s: %d%%",
        FetchString(11952), // "Percentage of Total Kills in Party"
        nPartyGameKillsNumber > 0
            ? 100 * pSprite->m_cGameStats.m_nGameKillsNumber / nPartyGameKillsNumber
            : 0);
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

// 0x5E3B80
BOOL CScreenCharacter::OnCancelButtonClick()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5E4560
void CScreenCharacter::sub_5E4560()
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

// 0x5E4A20
void CScreenCharacter::sub_5E4A20()
{
    // TODO: Incomplete.
}

// 0x5E4B30
void CScreenCharacter::sub_5E4B30()
{
    // TODO: Incomplete.
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
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 8728
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(GetSelectedCharacter());

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (m_bMultiPlayerModifyable
            && (pSprite->GetBaseStats()->m_flags & 0x800) != 0
            && !pSprite->GetDerivedStats()->m_bPolymorphed) {
            SummonPopup(13, pSprite, 1);
        }

        pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E5330
void CScreenCharacter::OnLevelUpButtonClick()
{
    // TODO: Incomplete.
}

// 0x5E56F0
void CScreenCharacter::LevelUp(CGameSprite* pSprite)
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
void CScreenCharacter::UpdateScriptPanel(CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(11);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10006
    UTIL_ASSERT(pPanel != NULL);

    if (m_pCurrentScrollBar == NULL) {
        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(5));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10015
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x5E7790
void CScreenCharacter::RefreshScripts()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    const CRuleTables& rule = pGame->GetRuleTables();

    CString sScript;
    CString sTitle;
    CString sDescription;
    CStringList lStandardScripts;
    CStringList lCustomScripts;
    CString sOtherScript;
    POSITION pos1;
    POSITION pos2;

    m_nScriptIndex = -1;
    if (m_pScripts != NULL) {
        delete m_pScripts;
        m_pScripts = NULL;
    }

    m_pScripts = pGame->GetScripts();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10062
    UTIL_ASSERT(m_pScripts != NULL);

    BOOL bNoneFound = FALSE;
    pos1 = m_pScripts->GetHeadPosition();
    while (pos1 != NULL) {
        sScript = m_pScripts->GetAt(pos1);
        sScript.MakeUpper();
        rule.GetScriptDescription(sScript, sTitle, sDescription);

        if (sScript.CompareNoCase("none") != 0) {
            if (sDescription.Compare("") != 0) {
                pos2 = lStandardScripts.GetHeadPosition();
                while (pos2 != NULL) {
                    sOtherScript = lStandardScripts.GetAt(pos2);
                    if (sOtherScript.Compare(sScript) < 0) {
                        break;
                    }
                    lStandardScripts.GetNext(pos2);
                }

                if (pos2 != NULL) {
                    lStandardScripts.InsertBefore(pos2, sScript);
                } else {
                    lStandardScripts.AddTail(sScript);
                }
            } else {
                lCustomScripts.AddTail(sScript);
            }
        } else {
            bNoneFound = TRUE;
        }

        m_pScripts->GetNext(pos1);
    }

    m_pScripts->AddTail(&lStandardScripts);
    m_pScripts->AddTail(&lCustomScripts);

    if (bNoneFound) {
        m_pScripts->AddHead("None");
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(11);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10114
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10116
    UTIL_ASSERT(pText != NULL);

    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;
    pText->RemoveAll();
    pText->field_A68 = 0x7FFE;

    INT nIndex = 0;
    pos1 = m_pScripts->GetHeadPosition();
    while (pos1 != NULL) {
        sScript = m_pScripts->GetAt(pos1);
        rule.GetScriptDescription(sScript, sTitle, sDescription);
        if (sScript.CompareNoCase("none") != 0) {
            pText->DisplayString(CString(""),
                sTitle + ' ' + sDescription,
                pText->m_rgbLabelColor,
                pText->m_rgbTextColor,
                nIndex,
                FALSE,
                TRUE);
        } else {
            pText->DisplayString(CString(""),
                sScript,
                pText->m_rgbLabelColor,
                pText->m_rgbTextColor,
                nIndex,
                FALSE,
                TRUE);
        }

        pText->DisplayString(CString(""),
            CString(""),
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            -1,
            FALSE,
            TRUE);

        m_pScripts->GetNext(pos1);
        nIndex++;
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));
}

// 0x5E7C50
void CScreenCharacter::OnScriptItemSelect(INT nItem)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10164
    UTIL_ASSERT(pGame != NULL);

    CString sScript;
    CString sTitle;
    CString sDescription;

    if (nItem >= 0) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        // NOTE: Uninline.
        INT nGameSprite = pGame->GetCharacterId(m_nSelectedCharacter);

        CGameSprite* pSprite;
        BYTE rc;
        do {
            rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (nItem != m_nScriptIndex) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10198
                UTIL_ASSERT(m_pScripts != NULL);

                CUIPanel* pPanel = m_cUIManager.GetPanel(11);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10202
                UTIL_ASSERT(pPanel != NULL);

                CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10204
                UTIL_ASSERT(pText != NULL);

                if (m_nScriptIndex != -1) {
                    pText->SetItemTextColor(pText->GetItemBossPosition(m_nScriptIndex),
                        pText->m_rgbTextColor);
                }

                m_nScriptIndex = nItem;

                if (m_nScriptIndex != -1) {
                    pText->SetItemTextColor(pText->GetItemBossPosition(m_nScriptIndex),
                        CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
                }

                CUIControlTextDisplay* pDescriptionText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(4));
                pDescriptionText->RemoveAll();

                sScript = m_pScripts->GetAt(m_pScripts->FindIndex(m_nScriptIndex));
                pGame->GetRuleTables().GetScriptDescription(sScript, sTitle, sDescription);

                if (sScript.CompareNoCase("none") != 0) {
                    pDescriptionText->DisplayString(CString(""),
                        sTitle + ' ' + sDescription,
                        pDescriptionText->m_rgbLabelColor,
                        pDescriptionText->m_rgbTextColor,
                        -1,
                        FALSE,
                        TRUE);
                } else {
                    pDescriptionText->DisplayString(CString(""),
                        sTitle,
                        pDescriptionText->m_rgbLabelColor,
                        pDescriptionText->m_rgbTextColor,
                        -1,
                        FALSE,
                        TRUE);
                }

                pDescriptionText->SetTopString(pDescriptionText->m_plstStrings->FindIndex(0));

                UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
            }

            pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        renderLock.Unlock();
    }
}

// 0x5E7FF0
void CScreenCharacter::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10276
    UTIL_ASSERT(0 <= nButton && nButton < GetNumErrorButtons());

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 10278
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    INT nGameSprite = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        switch (m_nErrorState) {
        case 0:
            switch (nButton) {
            case 0:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10340
                UTIL_ASSERT(FALSE);
            }
            break;
        case 1:
            switch (nButton) {
            case 0:
                DismissPopup(pSprite);

                CInfGame::m_bHealPartyOnRest = FALSE;
                pGame->RestParty(1, 0);
                break;
            case 1:
                DismissPopup(pSprite);

                CInfGame::m_bHealPartyOnRest = TRUE;
                pGame->RestParty(1, 0);
                CInfGame::m_bHealPartyOnRest = FALSE;
                break;
            case 2:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10327
                UTIL_ASSERT(FALSE);
            }
            break;
        case 2:
            switch (nButton) {
            case 0:
                DismissPopup(pSprite);
                LevelUp(pSprite);
                break;
            case 1:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10371
                UTIL_ASSERT(FALSE);
            }
            break;
        case 3:
            switch (nButton) {
            case 0:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10353
                UTIL_ASSERT(FALSE);
            }
            break;
        case 6:
            switch (nButton) {
            case 0:
                if (1) {
                    DismissPopup(pSprite);

                    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                    // __LINE__: 10426
                    UTIL_ASSERT(nCharacterId != CGameObjectArray::INVALID_INDEX);

                    pGame->CharacterExport(nCharacterId, field_176E);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                    // __LINE__: 10430
                    UTIL_ASSERT(m_pCharacters != NULL);

                    delete m_pCharacters;
                    m_pCharacters = NULL;

                    DismissPopup(pSprite);
                }
                break;
            case 1:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10443
                UTIL_ASSERT(FALSE);
            }
            break;
        case 7:
            switch (nButton) {
            case 0:
                DismissPopup(pSprite);

                if (pSprite->HaveUnexportableItems()) {
                    m_nErrorState = 6;
                    m_dwErrorTextId = 26586;
                    m_strErrorButtonText[0] = 13912;
                    m_strErrorButtonText[1] = 13913;
                    SummonPopup(10, pSprite, 1);
                } else {
                    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                    // __LINE__: 10395
                    UTIL_ASSERT(nCharacterId != CGameObjectArray::INVALID_INDEX);

                    pGame->CharacterExport(nCharacterId, field_176E);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                    // __LINE__: 10399
                    UTIL_ASSERT(m_pCharacters != NULL);

                    delete m_pCharacters;
                    m_pCharacters = NULL;

                    DismissPopup(pSprite);
                }
                break;
            case 1:
                DismissPopup(pSprite);
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10413
                UTIL_ASSERT(FALSE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 10449
            UTIL_ASSERT(FALSE);
        }

        pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x5E8460
void CScreenCharacter::OnCharacterItemSelect(INT nItem)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // NOTE: Uninline.
    INT nGameSprite = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (nItem != m_nCharacterIndex) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 10552
            UTIL_ASSERT(m_pCharacters != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(13);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 10556
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
            // __LINE__: 10558
            UTIL_ASSERT(pText != NULL);

            if (m_nCharacterIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nCharacterIndex),
                    pText->m_rgbTextColor);
            }

            m_nCharacterIndex = nItem;

            if (m_nCharacterIndex != -1) {
                pText->SetItemTextColor(pText->GetItemBossPosition(m_nCharacterIndex),
                    CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);

                CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(6));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10577
                UTIL_ASSERT(pEdit != NULL);

                POSITION pos = m_pCharacters->FindIndex(m_nCharacterIndex);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
                // __LINE__: 10579
                UTIL_ASSERT(pos != NULL);

                pEdit->SetText(m_pCharacters->GetAt(pos));
            }

            UpdatePopupPanel(GetTopPopup()->m_nID, pSprite);
        }

        pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5E8690
void CScreenCharacter::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        if (!OnCancelButtonClick()) {
            break;
        }
    }

    while (m_lPopupStack.GetTailPosition() != NULL) {
        DismissPopup(NULL);
    }
}

// 0x5E86D0
void CScreenCharacter::UpdateCharacterStatus(LONG nCharacterId)
{
    CBaldurEngine::UpdateCharacterStatus(nCharacterId);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if (pGame != NULL && field_17A4 == 0) {
        if (pGame->GetCharacterId(GetSelectedCharacter()) == nCharacterId) {
            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                BOOL bIsDead = (pSprite->GetDerivedStats()->m_generalState & STATE_DEAD) != 0;

                pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);

                if (bIsDead) {
                    while (GetTopPopup() != NULL) {
                        OnCancelButtonClick();
                    }
                }
            }

            if (GetTopPopup() == NULL) {
                UpdateMainPanel(FALSE);
            }
        }
    }
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

// 0x5F89B0
void CScreenCharacter::sub_5F89B0(CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    for (INT nFeat = 0; nFeat < ruleTables.m_tFeats.GetHeight(); nFeat++) {
        if (m_storedFeats[nFeat] < pSprite->GetFeatValue(nFeat)) {
            while (pSprite->GetFeatValue(nFeat) > 0) {
                if (pSprite->sub_763200(nFeat, 1)) {
                    break;
                }

                pSprite->SetFeatValue(nFeat, pSprite->GetFeatValue(nFeat) - 1);
                m_nExtraFeats++;
            }
        }
    }
}

// 0x5F8C90
void CScreenCharacter::sub_5F8C90(int a1)
{
    // TODO: Incomplete.
}

// 0x5F91F0
void CScreenCharacter::sub_5F91F0(int a1)
{
    // TODO: Incomplete.
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

// 0x5EA7D0
CUIControlButtonCharacter5EA7D0::CUIControlButtonCharacter5EA7D0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x5EA820
CUIControlButtonCharacter5EA7D0::~CUIControlButtonCharacter5EA7D0()
{
}

// 0x5EA8C0
void CUIControlButtonCharacter5EA7D0::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12235
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->sub_5E4A20();
}

// -----------------------------------------------------------------------------

// 0x5EA900
CUIControlButtonCharacter5EA900::CUIControlButtonCharacter5EA900(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x5EA950
CUIControlButtonCharacter5EA900::~CUIControlButtonCharacter5EA900()
{
}

// 0x5EA9F0
void CUIControlButtonCharacter5EA900::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12289
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->sub_5E4B30();
}

// -----------------------------------------------------------------------------

// 0x5EAA30
CUIControlButtonCharacter5EAA30::CUIControlButtonCharacter5EAA30(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(16559, strRes);
    SetText(strRes.szText);
}

// 0x5EAB20
CUIControlButtonCharacter5EAA30::~CUIControlButtonCharacter5EAA30()
{
}

// 0x5EABC0
void CUIControlButtonCharacter5EAA30::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 12346
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->sub_5E4560();
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

// 0x5EBC60
CUIControlButtonCharacter5EBC60::CUIControlButtonCharacter5EBC60(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nSelectedFrame = 0;
    field_676 = "";
    field_66E = "";
}

// 0x5EBD30
CUIControlButtonCharacter5EBC60::~CUIControlButtonCharacter5EBC60()
{
}

// 0x5EBFA0
void CUIControlButtonCharacter5EBC60::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x5EC420
BOOL CUIControlButtonCharacter5EBC60::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x5EC5A0
CUIControlButtonCharacterPopupDone::CUIControlButtonCharacterPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, INT nType)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    if (nType == 0) {
        SetText(CBaldurEngine::FetchString(11973)); // "Done"
    } else {
        SetText(CBaldurEngine::FetchString(36789)); // "Next"
    }
}

// 0x5EC680
CUIControlButtonCharacterPopupDone::~CUIControlButtonCharacterPopupDone()
{
}

// 0x5EC720
void CUIControlButtonCharacterPopupDone::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13241
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EC760
CUIControlButtonCharacterPopupCancel::CUIControlButtonCharacterPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, INT nType)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    if (nType == 1) {
        SetText(CBaldurEngine::FetchString(12896)); // "Back"
    } else {
        SetText(CBaldurEngine::FetchString(13727)); // "Cancel"
    }
}

// 0x5EC840
CUIControlButtonCharacterPopupCancel::~CUIControlButtonCharacterPopupCancel()
{
}

// 0x5EC8E0
void CUIControlButtonCharacterPopupCancel::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13302
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x5EC920
CUIControlButtonCharacterBiographyRevert::CUIControlButtonCharacterBiographyRevert(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CBaldurEngine::FetchString(2240)); // "Revert"
}

// 0x5EC9F0
CUIControlButtonCharacterBiographyRevert::~CUIControlButtonCharacterBiographyRevert()
{
}

// 0x5ECA90
void CUIControlButtonCharacterBiographyRevert::OnLButtonClick(CPoint pt)
{
    if (m_bEnabled) {
        CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 13354
        UTIL_ASSERT(pCharacter != NULL);

        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 13358
        UTIL_ASSERT(pGame != NULL);

        // NOTE: Uninline.
        LONG nCharacterId = pGame->GetCharacterId(pCharacter->GetSelectedCharacter());

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            // NOTE: Unused.
            STR_RES strRes;

            CScreenCharacter::ResetBiography(pSprite);
            STRREF strBiography = pSprite->GetBaseStats()->m_biography;

            pCharacter->DismissPopup(pSprite);

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);

            CString sBiography = CBaldurEngine::FetchString(strBiography);
            BYTE nFixedPartyId = static_cast<BYTE>(g_pBaldurChitin->GetObjectGame()->GetFixedOrderCharacterPortraitNum(nCharacterId));
            g_pBaldurChitin->GetObjectGame()->ChangeBiography(nFixedPartyId, sBiography);
        }
    }
}

// -----------------------------------------------------------------------------

// 0x5ECC60
CUIControlButtonCharacterBiographyClear::CUIControlButtonCharacterBiographyClear(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CBaldurEngine::FetchString(18622)); // "Clear"
}

// 0x5ECD40
CUIControlButtonCharacterBiographyClear::~CUIControlButtonCharacterBiographyClear()
{
}

// 0x5ECDE0
void CUIControlButtonCharacterBiographyClear::OnLButtonClick(CPoint pt)
{
    if (m_bEnabled) {
        CUIControlEditMultiLine* pEdit = static_cast<CUIControlEditMultiLine*>(m_pPanel->GetControl(4));
        pEdit->Remove();

        g_pBaldurChitin->m_pEngineCharacter->field_1B8 = TRUE;
        g_pBaldurChitin->m_pEngineCharacter->GetManager()->SetCapture(pEdit, CUIManager::KEYBOARD);
    }
}

// -----------------------------------------------------------------------------

// 0x5ECE40
CUIControlTextDisplayCharacterScriptScripts::CUIControlTextDisplayCharacterScriptScripts(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayCharacterScriptScripts::~CUIControlTextDisplayCharacterScriptScripts()
{
}

// 0x5ED130
void CUIControlTextDisplayCharacterScriptScripts::OnItemSelected(LONG lMarker)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13512
    UTIL_ASSERT(pCharacter != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13514
    UTIL_ASSERT(pGame != NULL);

    INT nGameSprite = pGame->GetCharacterId(pCharacter->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCharacter->OnScriptItemSelect(lMarker);
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        pGame->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5ECFD0
CUIControlButtonCharacterError::CUIControlButtonCharacterError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x5ED020
CUIControlButtonCharacterError::~CUIControlButtonCharacterError()
{
}

// 0x5ED0C0
void CUIControlButtonCharacterError::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13597
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnErrorButtonClick(m_nID);
}

// -----------------------------------------------------------------------------

// 0x5ED100
CUIControlTextDisplayCharacterExportCharacters::CUIControlTextDisplayCharacterExportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayCharacterExportCharacters::~CUIControlTextDisplayCharacterExportCharacters()
{
}

// 0x5ED130
void CUIControlTextDisplayCharacterExportCharacters::OnItemSelected(LONG lMarker)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13651
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->OnCharacterItemSelect(lMarker);
}

// -----------------------------------------------------------------------------

// 0x5ED170
CUIControlEditCharacter::CUIControlEditCharacter(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, 0)
{
}

// 0x5ED1C0
CUIControlEditCharacter::~CUIControlEditCharacter()
{
}

// 0x5ED290
void CUIControlEditCharacter::OnKeyDown(SHORT nKey)
{
    CUIControlEdit::OnKeyDown(nKey);

    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 13706
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
        if (m_nID == 6) {
            pCharacter->OnCharacterItemSelect(-1);
        }

        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x5ED390
void CUIControlEditCharacter::OnEditReturn(CString sText)
{
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
        if (m_nID == 6) {
            pCharacter->OnCharacterItemSelect(-1);
        }

        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
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
    case 9:
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

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x5F6830
void CUIControlButtonCharacterFeatsHotArea::OnHotAreaClick(CPoint pt)
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17020
        UTIL_ASSERT(FALSE);
    }

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetFeatId(offset + g_pBaldurChitin->m_pEngineCharacter->m_nTopFeat);
    STRREF strDescription = ruleTables.GetFeatDescription(id);
    g_pBaldurChitin->m_pEngineCharacter->UpdateHelp(m_pPanel->m_nID, 92, strDescription);
}

// -----------------------------------------------------------------------------

// 0x5F6910
CUIControlScrollBarCharacterFeats::CUIControlScrollBarCharacterFeats(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarCharacterFeats::~CUIControlScrollBarCharacterFeats()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharacterFeats::UpdateScrollBar()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17070
    UTIL_ASSERT(pCharacter != NULL);

    AdjustScrollBar(pCharacter->m_nTopFeat, FEAT_COUNT, FEAT_SLOTS);
}

// 0x5F6930
void CUIControlScrollBarCharacterFeats::OnScrollUp()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17095
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->m_nTopFeat = max(pCharacter->m_nTopFeat - 1, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F69D0
void CUIControlScrollBarCharacterFeats::OnScrollDown()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17119
    UTIL_ASSERT(pCharacter != NULL);

    if (pCharacter->m_nTopFeat < FEAT_COUNT - FEAT_SLOTS) {
        pCharacter->m_nTopFeat++;
    }

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F6A80
void CUIControlScrollBarCharacterFeats::OnPageUp(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17148
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, FEAT_SLOTS - 1);
    pCharacter->m_nTopFeat = max(pCharacter->m_nTopFeat - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F6B30
void CUIControlScrollBarCharacterFeats::OnPageDown(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17176
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, FEAT_SLOTS - 1);
    pCharacter->m_nTopFeat += nStep;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F6BD0
void CUIControlScrollBarCharacterFeats::OnScroll()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17204
    UTIL_ASSERT(pCharacter != NULL);

    INT nTopFeat = max(FEAT_COUNT * field_144, 0) / field_142;
    pCharacter->m_nTopFeat = max(min(nTopFeat - FEAT_SLOTS, FEAT_COUNT - FEAT_SLOTS), 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F6CA0
void CUIControlScrollBarCharacterFeats::InvalidateItems()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 17235
    UTIL_ASSERT(pCharacter != NULL);

    CSingleLock renderLock(&(pCharacter->GetManager()->field_36), FALSE);
    renderLock.Lock();

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
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x5F6DC0
CUIControlButtonCharacterFeatsPlusMinus::CUIControlButtonCharacterFeatsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x5F6E00
CUIControlButtonCharacterFeatsPlusMinus::~CUIControlButtonCharacterFeatsPlusMinus()
{
}

// 0x5F6EA0
BOOL CUIControlButtonCharacterFeatsPlusMinus::OnLButtonDown(CPoint pt)
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17366
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetFeatId(g_pBaldurChitin->m_pEngineCharacter->m_nTopFeat + offset);
    STRREF strDescription = ruleTables.GetFeatDescription(id);
    g_pBaldurChitin->m_pEngineCharacter->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
}

// 0x5F6FD0
void CUIControlButtonCharacterFeatsPlusMinus::AdjustValue()
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
        bInc = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17444
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17497
        UTIL_ASSERT(FALSE);
    }

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
        DWORD id = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetFeatId(pCharacter->m_nTopFeat + offset);
        INT nValue = pSprite->GetFeatValue(id);

        if (bInc) {
            if (pSprite->sub_763A40(id, 1) && pCharacter->m_nExtraFeats > 0) {
                pSprite->SetFeatValue(id, nValue + 1);
                pCharacter->m_nExtraFeats--;
            }
        } else {
            if (nValue > 0 && pCharacter->m_storedFeats[id] < pSprite->GetFeatValue(id)) {
                pSprite->SetFeatValue(id, nValue - 1);
                pCharacter->m_nExtraFeats++;
                pCharacter->sub_5F89B0(pSprite);
            }
        }

        pCharacter->UpdatePopupPanel(pCharacter->GetTopPopup()->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x5F7250
CUIControlButtonCharacterFeatsCircle::CUIControlButtonCharacterFeatsCircle(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x5F72A0
CUIControlButtonCharacterFeatsCircle::~CUIControlButtonCharacterFeatsCircle()
{
}

// 0x5F7340
BOOL CUIControlButtonCharacterFeatsCircle::Render(BOOL bForce)
{
    CVidCell vcIcon;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    INT nFirstID;
    INT nIndex;
    switch (m_nID) {
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
        nFirstID = 36;
        nIndex = 0;
        break;
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
        nFirstID = 41;
        nIndex = 1;
        break;
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
        nFirstID = 46;
        nIndex = 2;
        break;
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
        nFirstID = 51;
        nIndex = 3;
        break;
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
        nFirstID = 56;
        nIndex = 4;
        break;
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
        nFirstID = 61;
        nIndex = 5;
        break;
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
        nFirstID = 66;
        nIndex = 6;
        break;
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
        nFirstID = 71;
        nIndex = 7;
        break;
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
        nFirstID = 76;
        nIndex = 8;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17714
        UTIL_ASSERT(FALSE);
    }

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nGameSprite,
            CGameObjectArray::THREAD_1,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        return FALSE;
    }

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    DWORD v1 = ruleTables.GetFeatId(nIndex + pCreateChar->m_nTopFeat);
    INT nFeatNumber = ruleTables.GetFeatId(v1);
    INT nValue = pSprite->GetFeatValue(nFeatNumber);
    INT nMaxValue = pSprite->GetMaxFeatValue(nFeatNumber);
    INT nKnobValue = nFirstID - m_nID + 4;

    if ((nValue > 0 || pSprite->sub_763A40(nFeatNumber, 1))
        && nKnobValue < nMaxValue) {
        CRect rControlRect(m_pPanel->m_ptOrigin + m_ptOrigin,
            m_size);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        // NOTE: Uninline.
        vcIcon.SetResRef(CResRef("GUIPFC"), m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

        if (nKnobValue >= nValue) {
            vcIcon.FrameSet(1);
        } else {
            vcIcon.FrameSet(0);
        }

        BOOL bResult = vcIcon.Render(0,
            rControlRect.left,
            rControlRect.top,
            rClip,
            NULL,
            0,
            0,
            -1);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 17756
        UTIL_ASSERT(bResult);
    }

    pCreateChar->UpdatePopupPanel(pCreateChar->GetTopPopup()->m_nID, pSprite);

    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nGameSprite,
        CGameObjectArray::THREAD_1,
        INFINITE);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x5F7F90
CUIControlScrollBarCharacterSkills::CUIControlScrollBarCharacterSkills(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarCharacterSkills::~CUIControlScrollBarCharacterSkills()
{
}

// NOTE: Inlined.
void CUIControlScrollBarCharacterSkills::UpdateScrollBar()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18162
    UTIL_ASSERT(pCharacter != NULL);

    AdjustScrollBar(pCharacter->m_nTopSkill, SKILL_COUNT, SKILL_SLOTS);
}

// 0x5F7FB0
void CUIControlScrollBarCharacterSkills::OnScrollUp()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18187
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->m_nTopSkill = max(pCharacter->m_nTopSkill - 1, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F8050
void CUIControlScrollBarCharacterSkills::OnScrollDown()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18211
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->m_nTopSkill++;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F80E0
void CUIControlScrollBarCharacterSkills::OnPageUp(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18235
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, SKILL_SLOTS - 1);
    pCharacter->m_nTopSkill = max(pCharacter->m_nTopSkill - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F8190
void CUIControlScrollBarCharacterSkills::OnPageDown(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 11362
    UTIL_ASSERT(pCharacter != NULL);

    INT nStep = min(nLines, SKILL_SLOTS - 1);
    pCharacter->m_nTopSkill += nStep;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F8230
void CUIControlScrollBarCharacterSkills::OnScroll()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18291
    UTIL_ASSERT(pCharacter != NULL);

    pCharacter->m_nTopSkill = max(SKILL_COUNT * field_144, 0) / field_142;

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F82E0
void CUIControlScrollBarCharacterSkills::InvalidateItems()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18318
    UTIL_ASSERT(pCharacter != NULL);

    CSingleLock renderLock(&(pCharacter->GetManager()->field_36), FALSE);
    renderLock.Lock();

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
        pCharacter->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x5F8400
CUIControlButtonCharacterSkillsPlusMinus::CUIControlButtonCharacterSkillsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x5F8440
CUIControlButtonCharacterSkillsPlusMinus::~CUIControlButtonCharacterSkillsPlusMinus()
{
}

// 0x5F84E0
BOOL CUIControlButtonCharacterSkillsPlusMinus::OnLButtonDown(CPoint pt)
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18449
        UTIL_ASSERT(FALSE);
    }

    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetSkillId(g_pBaldurChitin->m_pEngineCharacter->m_nTopSkill + offset);
    STRREF strDescription = ruleTables.GetSkillDescription(id);
    g_pBaldurChitin->m_pEngineCharacter->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
}

// 0x5F8610
void CUIControlButtonCharacterSkillsPlusMinus::AdjustValue()
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
        bInc = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18527
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18580
        UTIL_ASSERT(FALSE);
    }

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
        const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

        DWORD id = ruleTables.GetSkillId(pCharacter->m_nTopSkill + offset);
        INT nValue = pSprite->GetSkillValue(id);

        // FIXME: Looks wrong (obtaining id from id).
        INT nCost = pSprite->GetSkillCost(ruleTables.GetSkillId(id),
            pCharacter->m_nClass);

        if (bInc) {
            if (nCost != 0 && pCharacter->m_nExtraSkillPoints >= nCost) {
                pSprite->SetSkillValue(id, nValue + 1);
                pCharacter->m_nExtraSkillPoints -= nCost;
            }
        } else {
            if (nValue > 0 && pCharacter->m_storedSkills[id] < pSprite->GetSkillValue(id)) {
                pSprite->SetSkillValue(id, nValue - 1);

                // FIXME: Looks wrong (obtaining id from id).
                pCharacter->m_nExtraSkillPoints += pSprite->GetSkillCost(ruleTables.GetSkillId(id),
                    pCharacter->m_nClass);
            }
        }

        pCharacter->UpdatePopupPanel(pCharacter->GetTopPopup()->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x5F88D0
void CUIControlButtonCharacterSkillsHotArea::OnHotAreaClick(CPoint pt)
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18703
        UTIL_ASSERT(FALSE);
    }

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetSkillId(offset + g_pBaldurChitin->m_pEngineCharacter->m_nTopSkill);
    STRREF strDescription = ruleTables.GetSkillDescription(id);
    g_pBaldurChitin->m_pEngineCharacter->UpdateHelp(m_pPanel->m_nID, 92, strDescription);
}

// -----------------------------------------------------------------------------

// 0x5F8C10
void CUIControlCharacterHotArea778ED0::OnHotAreaClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18958
    UTIL_ASSERT(pCharacter != NULL);

    if (m_nID >= 27 && m_nID <= 37) {
        pCharacter->sub_5F8C90(m_nID - 37);
        pCharacter->UpdatePopupPanel(57, NULL);
    } else if (m_nID >= 71 && m_nID <= 81) {
        pCharacter->sub_5F91F0(pCharacter->field_1852 + m_nID - 71);
        pCharacter->UpdatePopupPanel(57, NULL);
    }
}

// -----------------------------------------------------------------------------

// 0x5F8A50
CUIControlButtonCharacterInformationFolder::CUIControlButtonCharacterInformationFolder(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
}

// 0x5F8AB0
CUIControlButtonCharacterInformationFolder::~CUIControlButtonCharacterInformationFolder()
{
}

// 0x5F8B50
void CUIControlButtonCharacterInformationFolder::OnLButtonClick(CPoint pt)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 18906
    UTIL_ASSERT(pCharacter != NULL);

    CUIPanel* pPanel;
    CUIControlTextDisplay* pText;

    switch (m_nID) {
    case 60:
    case 61:
    case 62:
    case 63:
        pCharacter->field_1844 = m_nID - 60;

        pPanel = pCharacter->GetManager()->GetPanel(2);
        pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(45));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18921
        UTIL_ASSERT(pText != NULL);

        pText->SetTopString(pText->m_plstStrings->FindIndex(0));
        pCharacter->UpdateMainPanel(FALSE);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 18906
        UTIL_ASSERT(pCharacter != NULL);
    }
}

// -----------------------------------------------------------------------------

// 0x5F9410
CUIControlScrollbarCharacter5F9410::CUIControlScrollbarCharacter5F9410(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollbarCharacter5F9410::~CUIControlScrollbarCharacter5F9410()
{
}

// NOTE: Inlined.
void CUIControlScrollbarCharacter5F9410::UpdateScrollBar()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19222
    UTIL_ASSERT(pCharacter);

    AdjustScrollBar(pCharacter->field_1852, pCharacter->field_184E, 11);
}

// 0x5F9430
void CUIControlScrollbarCharacter5F9410::OnScrollUp()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19250
    UTIL_ASSERT(pCharacter);

    pCharacter->field_1852 = max(pCharacter->field_1852 - 1, 0);

    pCharacter->UpdatePopupPanel(57, NULL);

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F94C0
void CUIControlScrollbarCharacter5F9410::OnScrollDown()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19277
    UTIL_ASSERT(pCharacter);

    if (pCharacter->field_1852 < pCharacter->field_184E - 11) {
        // NOTE: Original code is slightly different.
        pCharacter->field_1852 = min(pCharacter->field_1852 + 1, pCharacter->field_184E - 11);
    }

    pCharacter->UpdatePopupPanel(57, NULL);

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x5F9580
void CUIControlScrollbarCharacter5F9410::OnPageUp(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19310
    UTIL_ASSERT(pCharacter);

    if (pCharacter->field_184E > 11) {
        // NOTE: Original code is slightly different.
        INT nStep = min(nLines, 10);
        pCharacter->field_1852 = max(pCharacter->field_1852 - nLines, 0);

        pCharacter->UpdatePopupPanel(57, NULL);

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5F9640
void CUIControlScrollbarCharacter5F9410::OnPageDown(DWORD nLines)
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19353
    UTIL_ASSERT(pCharacter);

    if (pCharacter->field_184E > 11) {
        // NOTE: Original code is slightly different.
        INT nStep = min(nLines, 11);
        pCharacter->field_1852 = min(pCharacter->field_1852 + nStep, pCharacter->field_184E - 11);

        pCharacter->UpdatePopupPanel(57, NULL);

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x5F9720
void CUIControlScrollbarCharacter5F9410::OnScroll()
{
    CScreenCharacter* pCharacter = g_pBaldurChitin->m_pEngineCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 19396
    UTIL_ASSERT(pCharacter);

    int v1 = max(pCharacter->field_184E - 1, 0) * field_144 / field_142;
    pCharacter->field_1852 = min(max(v1, 0), pCharacter->field_184E - 11);

    if (pCharacter->field_184E > 11) {
        pCharacter->UpdatePopupPanel(57, NULL);
    }

    // NOTE: Uninline.
    UpdateScrollBar();
}

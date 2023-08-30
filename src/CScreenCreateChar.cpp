#include "CScreenCreateChar.h"

#include "CBaldurChitin.h"
#include "CCreatureFile.h"
#include "CGameAnimationType.h"
#include "CGameArea.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
#include "CIcon.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenConnection.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSinglePlayer.h"
#include "CSpell.h"
#include "CUIControlFactory.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidCell.h"

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
const CString CScreenCreateChar::TOKEN_NUMBER("number");

// 0x8F3B94
const CString CScreenCreateChar::TOKEN_MINIMUM("MINIMUM");

// 0x8F3B98
const CString CScreenCreateChar::TOKEN_MAXIMUM("MAXIMUM");

// 0x605C40
CScreenCreateChar::CScreenCreateChar()
{
    m_animation.m_animation = NULL;
    m_nFirstStep = 0;
    m_nCurrentStep = 0;
    m_nExtraFeats = 0;
    m_nExtraAbilityPoints = 0;
    m_nExtraSpells = 0;
    m_nExtraSkillPoints = 0;
    field_4F6 = 0;
    field_4FE = 0;
    field_502 = 0;
    field_506 = 0;
    field_50A = 0;

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

    m_nCurrentPortrait = 0;
    m_nTopHatedRace = 0;
    m_nRange = 0;
    m_nMemorySTR = 0;
    field_570 = 0;

    m_nMemoryDEX = 0;
    m_nMemoryCON = 0;
    m_nMemoryINT = 0;
    m_nMemoryWIS = 0;
    m_nMemoryCHR = 0;
    m_nMemoryExtra = 0;
    m_nPortraitSmallIndex = 0;
    m_nPortraitLargeIndex = 0;
    m_nCustomSoundSetIndex = 0;
    m_nCustomSoundIndex = 0;
    m_nCharacterIndex = 0;
    field_596 = 0;
    field_14A4 = 0;
    field_14A8 = 0;

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
    m_pVirtualKeys[42] = CKeyInfo(VK_UP, static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND), static_cast<BYTE>(CChitin::TIMER_UPDATES_PER_SECOND));
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

    m_bCtrlKeyDown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    m_bPickingDomainSpells = FALSE;
    m_nGameSprite = CGameObjectArray::INVALID_INDEX;
    m_nEngineState = 0;
    m_nCharacterSlot = -1;
    m_pPortraits = NULL;
    m_pCharacters = NULL;
    m_pSounds = NULL;
    m_nSpellLevel = 1;
    field_14A3 = 1;
    m_nErrorState = 0;
    m_nTopFeat = 0;
    field_14AE = 0;
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
    m_nTopSkill = 0;
    field_15E0 = 0;
    memset(m_storedFeats, 0, sizeof(m_storedFeats));
    memset(m_storedSkills, 0, sizeof(m_storedSkills));
    field_1628 = 0;
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
    if (m_animation.m_animation != NULL) {
        delete m_animation.m_animation;
        m_animation.m_animation = NULL;
    }
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
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_ESCAPE:
                if (GetTopPopup() != NULL) {
                    OnCancelButtonClick();
                }
                break;
            case VK_RETURN:
                if (GetTopPopup() != NULL && GetTopPopup()->m_nID != 51) {
                    if (g_pBaldurChitin->field_1A0) {
                        // FIXME: Unused.
                        g_pChitin->GetWnd();
                        if (g_pBaldurChitin->cImm.field_128) {
                            m_cUIManager.OnKeyDown(VK_RETURN);
                        } else {
                            OnDoneButtonClick();
                        }
                    } else {
                        OnDoneButtonClick();
                    }
                }
                break;
            default:
                if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                    switch (m_pVirtualKeysFlags[nKeyFlag]) {
                    case VK_TAB:
                        m_cUIManager.ForceToolTip();
                        break;
                    case VK_LEFT:
                    case VK_NUMPAD4:
                        if (GetTopPopup() != NULL && GetTopPopup()->m_nID == 11) {
                            CUIControlButton* pButton = static_cast<CUIControlButton*>(GetManager()->GetPanel(11)->GetControl(2));
                            pButton->OnLButtonClick(CPoint(0, 0));
                        }
                        break;
                    case VK_RIGHT:
                    case VK_NUMPAD6:
                        if (GetTopPopup() != NULL && GetTopPopup()->m_nID == 11) {
                            CUIControlButton* pButton = static_cast<CUIControlButton*>(GetManager()->GetPanel(11)->GetControl(3));
                            pButton->OnLButtonClick(CPoint(0, 0));
                        }
                        break;
                    case VK_SNAPSHOT:
                        g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                        break;
                    }
                }
            }
        }
    }
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
    if (m_cUIManager.GetPanel(15)->m_bActive) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(15);
        CUIControlBase* pControl = pPanel->GetControl(8);
        if (pControl != NULL && pControl->IsOver(pt - pPanel->m_ptOrigin)) {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(9));
            m_pCurrentScrollBar = field_1624;
        } else {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));
            m_pCurrentScrollBar = field_1624;
        }
    } else if (m_cUIManager.GetPanel(20)->m_bActive) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(20);
        CUIControlBase* pControl = pPanel->GetControl(4);
        if (pControl != NULL && pControl->IsOver(pt - pPanel->m_ptOrigin)) {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(5));
            m_pCurrentScrollBar = field_1624;
        } else {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
            m_pCurrentScrollBar = field_1624;
        }
    } else if (m_cUIManager.GetPanel(55)->m_bActive) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(55);
        CUIControlBase* pControl = pPanel->GetControl(92);
        if (pControl != NULL && pControl->IsOver(pt - pPanel->m_ptOrigin)) {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(91));
            m_pCurrentScrollBar = field_1624;
        } else {
            field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(104));
            m_pCurrentScrollBar = field_1624;
        }
    }

    m_cUIManager.OnMouseMove(pt);
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
STRREF CScreenCreateChar::GetRangerHatedRaceStrref(BYTE nRace)
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
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CResRef portraitResRef;
    CString sAlignment;
    CString sGender;
    CString v4;
    CString sRace;

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(10));

    for (INT nStep = 0; nStep < 8; nStep++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nStep));
        pButton->SetEnabled(nStep == m_nCurrentStep);
        pButton->InvalidateRect();
    }

    CUIControlButton* pAccept = static_cast<CUIControlButton*>(pPanel->GetControl(8));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1365
    UTIL_ASSERT(pAccept != NULL);

    pAccept->SetEnabled(m_nCurrentStep > 7);

    CUIControlButton* pCancel = static_cast<CUIControlButton*>(pPanel->GetControl(15));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1370
    UTIL_ASSERT(pCancel != NULL);

    if (m_nCurrentStep > 0) {
        pCancel->SetText(FetchString(36788));
    } else {
        pCancel->SetText(FetchString(13727));
    }

    CUIControlButtonCharGenBiography* pBiography = static_cast<CUIControlButtonCharGenBiography*>(pPanel->GetControl(16));
    pBiography->SetActive(TRUE);
    pBiography->SetInactiveRender(TRUE);
    pBiography->SetEnabled(m_nCurrentStep > 6);

    CUIControlButton* pBack = static_cast<CUIControlButton*>(pPanel->GetControl(11));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1387
    UTIL_ASSERT(pBack != NULL);

    if (m_nCurrentStep > 0 && m_nCurrentStep > m_nFirstStep) {
        pBack->SetEnabled(TRUE);
        pBack->SetActive(TRUE);
    } else {
        pBack->SetEnabled(FALSE);
        pBack->SetActive(FALSE);
    }

    CUIControlButtonCharGenPortrait* pPortrait = static_cast<CUIControlButtonCharGenPortrait*>(pPanel->GetControl(12));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1402
    UTIL_ASSERT(pPortrait != NULL);

    if (m_nCurrentStep > 0) {
        portraitResRef = pSprite->m_baseStats.m_portraitLarge;
    } else {
        portraitResRef = "";
    }

    pPortrait->SetPortrait(portraitResRef);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(9));

    pText->RemoveAll();

    if (m_nCurrentStep > 0) {
        if (m_nCurrentStep > 7) {
            UpdateText(pText,
                "%s: %s",
                FetchString(1047),
                (LPCSTR)pSprite->GetName());
        }

        if (m_nCurrentStep > 0) {
            ruleTables.GetGenderStringMixed(pSprite->m_startTypeAI.m_nGender, sGender);
            UpdateText(pText,
                "%s: %s",
                FetchString(12135),
                (LPCSTR)sGender);
        }

        if (m_nCurrentStep > 1) {
            ruleTables.GetRaceStringMixed(pSprite->m_startTypeAI.m_nRace, sRace, pSprite->m_startTypeAI.m_nSubRace);
            UpdateText(pText,
                "%s: %s",
                FetchString(1048),
                (LPCSTR)sRace);
        }

        if (m_nCurrentStep > 2) {
            DWORD nSpecialization = pSprite->GetSpecialization();

            CDerivedStats* pDStats = &(pSprite->m_derivedStats);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 10537
            UTIL_ASSERT(pDStats != NULL);

            CCreatureFileHeader* pBStats = &(pSprite->m_baseStats);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 10539
            UTIL_ASSERT(pBStats != NULL);

            UpdateClassEntry(pText,
                pSprite->m_startTypeAI,
                pDStats,
                nSpecialization,
                pSprite->m_startTypeAI.m_nClass,
                pBStats->m_flags);
        }

        if (m_nCurrentStep > 3) {
            ruleTables.GetAlignmentStringMixed(pSprite->m_startTypeAI.m_nAlignment, sAlignment);
            UpdateText(pText,
                "%s: %s",
                FetchString(1049),
                (LPCSTR)sAlignment);
        }

        if (m_nCurrentStep > 4) {
            UpdateText(pText, "");

            UpdateTextForceColor(pText,
                RGB(200, 200, 0),
                "%s",
                (LPCSTR)FetchString(17088));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1145),
                pSprite->m_baseStats.m_STRBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_STRBase));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1151),
                pSprite->m_baseStats.m_DEXBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_DEXBase));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1178),
                pSprite->m_baseStats.m_CONBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CONBase));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1179),
                pSprite->m_baseStats.m_INTBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_INTBase));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1180),
                pSprite->m_baseStats.m_WISBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_WISBase));

            UpdateText(pText,
                "%s: %d  (%+d)",
                (LPCSTR)FetchString(1181),
                pSprite->m_baseStats.m_CHRBase,
                ruleTables.GetAbilityScoreModifier(pSprite->m_baseStats.m_CHRBase));
        }

        if (m_nCurrentStep > 5) {
            UpdateText(pText, "");

            UpdateTextForceColor(pText,
                RGB(200, 200, 0),
                "%s",
                (LPCSTR)FetchString(11983));

            pSprite->DisplaySkills(pText);

            UpdateText(pText, "");

            UpdateTextForceColor(pText,
                RGB(200, 200, 0),
                "%s",
                (LPCSTR)FetchString(36361));

            pSprite->DisplayFeats(pText);

            // TODO: Incomplete (spells).
        }

        pText->SetTopString(pText->m_plstStrings->FindIndex(0));
    } else {
        pSprite->m_baseStats.m_biography = -1;
        pText->DisplayString(CString(""),
            FetchString(16575),
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            -1,
            FALSE,
            TRUE);
    }
}

// 0x608AD0
void CScreenCreateChar::ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);
    int index;

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
        ResetNamePanel(pPanel, pSprite);
        break;
    case 6:
        ResetSkillsPanel(pPanel, pSprite);
        break;
    case 7:
        ResetArcaneSpellsPanel(pPanel, pSprite);
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
        ResetColorsPanel(pPanel, pSprite);
        break;
    case 15:
        for (index = 0; index < 8; index++) {
            pSprite->m_baseStats.m_favoredEnemies[index] = -1;
        }
        m_nTopHatedRace = 0;
        UpdateHelp(pPanel->m_nID, 8, 17256);
        break;
    case 16:
        ResetMemorizeArcaneSpellsPanel(pPanel, pSprite);
        break;
    case 17:
        if (m_bPickingDomainSpells) {
            ResetMemorizeDomainSpellsPanel(pPanel, pSprite);
        } else {
            ResetMemorizeDivineSpellsPanel(pPanel, pSprite);
        }
        break;
    case 18:
        ResetCustomPortraitsPanel(pPanel, pSprite);
        break;
    case 19:
        ResetCustomSoundsPanel(pPanel, pSprite);
        break;
    case 20:
        ResetImportPanel(pPanel, pSprite);
        break;
    case 21:
        ResetExportPanel(pPanel, pSprite);
        break;
    case 51:
        ResetBiographyPanel(pPanel, pSprite);
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

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(7));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 1790
    UTIL_ASSERT(pEdit != NULL);

    pEdit->SetText(CString(""));

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
void CScreenCreateChar::ResetBiographyPanel(CUIPanel* pPanel, CGameSprite* pSprite)
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
void CScreenCreateChar::ResetCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2068
    UTIL_ASSERT(pGame != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2071
    UTIL_ASSERT(m_pPortraits == NULL);

    m_pPortraits = pGame->GetPortraits();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2073
    UTIL_ASSERT(m_pPortraits != NULL);

    m_nPortraitSmallIndex = -1;
    m_nPortraitLargeIndex = -1;

    UpdatePortraitList(pPanel, 4, m_nPortraitSmallIndex);
    UpdatePortraitList(pPanel, 2, m_nPortraitLargeIndex);

    CUIControlButtonCharGenPortrait* pPortrait;

    pPortrait = static_cast<CUIControlButtonCharGenPortrait*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2083
    UTIL_ASSERT(pPortrait != NULL);

    pPortrait->SetPortrait(CResRef(""));

    pPortrait = static_cast<CUIControlButtonCharGenPortrait*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2086
    UTIL_ASSERT(pPortrait != NULL);

    pPortrait->SetPortrait(CResRef(""));
}

// 0x6095E0
void CScreenCreateChar::UpdatePortraitList(CUIPanel* pPanel, DWORD dwTextId, INT nSelectedIndex)
{
    CString sPortrait;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2119
    UTIL_ASSERT(m_pPortraits != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2120
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2122
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;
    pText->field_A68 = 32767;

    INT nIndex = 0;
    POSITION pos = m_pPortraits->GetHeadPosition();
    while (pos != NULL) {
        COLORREF rgbTextColor = nIndex == nSelectedIndex
            ? CBaldurChitin::TEXTDISPLAY_COLOR_SELECT
            : pText->m_rgbTextColor;

        // FIXME: Unnecessary copy.
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

// 0x609750
void CScreenCreateChar::ResetCustomSoundsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sSound;
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2177
    UTIL_ASSERT(pGame != NULL);

    m_pSounds = pGame->GetSounds();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2186
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(45));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2188
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
    pText->SetItemTextColor(pos, CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);

    m_nCustomSoundSetIndex = 0;
    m_nCustomSoundIndex = 3;

    UpdateHelp(pPanel->m_nID, 50, 11315);
}

// 0x609900
void CScreenCreateChar::ResetNamePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sName(pSprite->GetName());

    // FIXME: Unused.
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_sName = CString("");

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 2241
    UTIL_ASSERT(pEdit != NULL);

    pEdit->SetText(sName);

    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
}

// 0x609A10
void CScreenCreateChar::ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CResRef portraitResRef;

    m_nCurrentPortrait = 0;

    CString sPortrait = GetCurrentPortrait(pSprite);

    portraitResRef = sPortrait + "S";
    portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitSmall);

    portraitResRef = sPortrait + "L";
    portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitLarge);
}

// 0x609B30
void CScreenCreateChar::ResetColorsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CString sRace = ruleTables.GetRaceString(typeAI.m_nRace, 0);

    CString sSubRaceFile = ruleTables.m_tSrTable.GetAt(CString("SRFILE"), sRace);

    if (m_tSubRace.GetResRef() != sSubRaceFile) {
        m_tSubRace.Load(CResRef(sSubRaceFile));
    }

    INT nSubRaceListIndex = atol(m_tSubRace.GetAt(CPoint(0, typeAI.m_nSubRace)));

    CString sColorFile;

    sColorFile = ruleTables.m_tSrList.GetAt(CPoint(5, nSubRaceListIndex));
    if (m_tHairColor.GetResRef() != sColorFile) {
        m_tHairColor.Load(CResRef(sColorFile));
    }

    sColorFile = ruleTables.m_tSrList.GetAt(CPoint(6, nSubRaceListIndex));
    if (m_tSkinColor.GetResRef() != sColorFile) {
        m_tSkinColor.Load(CResRef(sColorFile));
    }

    if (!field_1628) {
        CResRef portraitColorResRef("portcolr");
        C2DArray tPortraitColor;
        CString v1;
        CString sPortraitLarge;

        sPortraitLarge = pSprite->m_baseStats.m_portraitLarge;
        v1 = sPortraitLarge.Left(8);

        tPortraitColor.Load(portraitColorResRef);

        BOOL bDemanded = tPortraitColor.Demand();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 2351
        UTIL_ASSERT(bDemanded == TRUE);

        CPoint ptLocation;
        BOOLEAN bFound = tPortraitColor.Find(v1, ptLocation, TRUE);

        pSprite->m_baseStats.m_colors[0] = 30;

        if (bFound) {
            pSprite->GetAnimation()->SetColorRange(0, pSprite->m_baseStats.m_colors[0]);

            ptLocation.x = 3;
            pSprite->m_baseStats.m_colors[1] = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
            pSprite->GetAnimation()->SetColorRange(1, pSprite->m_baseStats.m_colors[1]);

            ptLocation.x = 2;
            pSprite->m_baseStats.m_colors[2] = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
            pSprite->GetAnimation()->SetColorRange(2, pSprite->m_baseStats.m_colors[2]);

            ptLocation.x = 0;
            pSprite->m_baseStats.m_colors[3] = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
            pSprite->GetAnimation()->SetColorRange(3, pSprite->m_baseStats.m_colors[3]);

            pSprite->m_baseStats.m_colors[4] = 23;
            pSprite->GetAnimation()->SetColorRange(4, pSprite->m_baseStats.m_colors[4]);

            pSprite->m_baseStats.m_colors[5] = 30;
            pSprite->GetAnimation()->SetColorRange(5, pSprite->m_baseStats.m_colors[5]);

            ptLocation.x = 1;
            pSprite->m_baseStats.m_colors[6] = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
            pSprite->GetAnimation()->SetColorRange(6, pSprite->m_baseStats.m_colors[6]);
        } else {
            pSprite->GetAnimation()->SetColorRange(0, pSprite->m_baseStats.m_colors[0]);

            pSprite->m_baseStats.m_colors[1] = 39;
            pSprite->GetAnimation()->SetColorRange(1, pSprite->m_baseStats.m_colors[1]);

            pSprite->m_baseStats.m_colors[2] = 41;
            pSprite->GetAnimation()->SetColorRange(2, pSprite->m_baseStats.m_colors[2]);

            pSprite->m_baseStats.m_colors[3] = 12;
            pSprite->GetAnimation()->SetColorRange(3, pSprite->m_baseStats.m_colors[3]);

            pSprite->m_baseStats.m_colors[4] = 23;
            pSprite->GetAnimation()->SetColorRange(4, pSprite->m_baseStats.m_colors[4]);

            pSprite->m_baseStats.m_colors[5] = 30;
            pSprite->GetAnimation()->SetColorRange(5, pSprite->m_baseStats.m_colors[5]);

            pSprite->m_baseStats.m_colors[6] = 0;
            pSprite->GetAnimation()->SetColorRange(6, pSprite->m_baseStats.m_colors[6]);
        }

        tPortraitColor.Release();

        UpdateCharacterAppearance();
    }
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
void CScreenCreateChar::ResetArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CAIObjectType typeAI(pSprite->m_startTypeAI);

    m_nSpellLevel = 1;

    if ((typeAI.m_nClassMask & CAIOBJECTTYPE_C_BARD) != 0) {
        INT nBardClass = pSprite->GetDerivedStats()->GetClassLevel(CAIObjectType::C_BARD);
        m_nExtraSpells = atol(ruleTables.m_tKnownSpellsBard.GetAt(CPoint(m_nSpellLevel - 1, nBardClass - 1)));
    } else if ((typeAI.m_nClassMask & CAIOBJECTTYPE_C_SORCERER) != 0) {
        INT nBardClass = pSprite->GetDerivedStats()->GetClassLevel(CAIObjectType::C_BARD);
        m_nExtraSpells = atol(ruleTables.m_tKnownSpellsSorcerer.GetAt(CPoint(m_nSpellLevel - 1, nBardClass - 1)));
    } else {
        INT nBonus = 0;
        ruleTables.GetMaxKnownSpells(typeAI.m_nClass,
            typeAI,
            *pSprite->GetDerivedStats(),
            pSprite->GetSpecialization(),
            1,
            nBonus);
        if ((pSprite->GetSpecialization() & SPECMASK_WIZARD_UNIVERSAL) != 0) {
            m_nExtraSpells = nBonus + 2;
        } else {
            m_nExtraSpells = nBonus + 3;
        }
    }

    CGameSpriteGroupedSpellList* pSpells = pSprite->GetSpells(typeAI.m_nClass);

    // NOTE: Uninline.
    pSpells->Clear();

    // NOTE: Uninline.
    pSprite->m_domainSpells.Clear();

    for (DWORD nButtonID = 2; nButtonID <= 25; nButtonID++) {
        CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 2528
        UTIL_ASSERT(pButton != NULL);

        pButton->SetSelected(FALSE);
    }

    CString sNumber;
    sNumber.Format("%d", m_nExtraSpells);

    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_NUMBER, sNumber);

    UpdateLabel(pPanel,
        0x10000000,
        "%s: %s %d",
        (LPCSTR)FetchString(31614), // "Arcane Spell Selection"
        (LPCSTR)FetchString(7192), // "Level"
        m_nSpellLevel);

    UpdateHelp(pPanel->m_nID, 27, 17250);
}

// 0x60A920
void CScreenCreateChar::ResetMemorizeArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // NOTE: Unused.
    CResRef v1;

    CDerivedStats& DStats = *pSprite->GetDerivedStats();
    CAIObjectType& typeAI = pSprite->m_startTypeAI;

    INT nMaxKnownSpellsBonus = 0;
    UINT nMaxKnownSpellsBase;
    UINT nMaxKnownSpells;

    UINT nClassIndex;
    UINT nLevel;

    for (nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            if (typeAI.m_nClass == CAIOBJECTTYPE_C_BARD
                || typeAI.m_nClass == CAIOBJECTTYPE_C_SORCERER) {
                nMaxKnownSpellsBase = ruleTables.GetMaxKnownSpells(typeAI.m_nClass,
                    typeAI,
                    DStats,
                    pSprite->GetSpecialization(),
                    nLevel + 1,
                    nMaxKnownSpellsBonus);
                nMaxKnownSpells = nMaxKnownSpellsBase + nMaxKnownSpellsBonus;
            } else {
                nMaxKnownSpells = 0;
            }

            // NOTE: Uninline.
            pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->field_14 = nMaxKnownSpells;

            // NOTE: Uninline.
            pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->field_18 = 0;
        }
    }

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    nMaxKnownSpellsBase = ruleTables.GetMaxKnownSpells(typeAI.m_nClass,
        typeAI,
        DStats,
        pSprite->GetSpecialization(),
        1,
        nMaxKnownSpellsBonus);
    nMaxKnownSpells = nMaxKnownSpellsBase + nMaxKnownSpellsBonus;

    if (nMaxKnownSpells >= pSprite->GetSpellsAtLevel(typeAI.m_nClass, 0)->m_List.size()) {
        nMaxKnownSpells = pSprite->GetSpellsAtLevel(typeAI.m_nClass, 0)->m_List.size();
    }

    m_nExtraSpells = nMaxKnownSpells;

    UpdateLabel(pPanel,
        0x10000000,
        "%s: %s %d",
        (LPCSTR)FetchString(17189), // "Memorize Arcane Spells"
        (LPCSTR)FetchString(7192), // "Level"
        m_nSpellLevel);

    for (nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            for (UINT nIndex = 0;; nIndex++) {
                // NOTE: Uninline.
                CGameSpriteSpellList* pSpells = pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel);

                if (nIndex >= pSpells->m_List.size()) {
                    break;
                }

                CGameSpriteSpellListEntry* pEntry = pSpells->Get(nIndex);
                pSprite->m_spells.m_spellsByClass[nClassIndex].sub_7260B0(pEntry->m_nID, nLevel, 0, 1);
            }
        }
    }

    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: .\Include\ObjCreature.h
        // __LINE__: 2625
        UTIL_ASSERT(pButton != NULL);

        pButton->SetSelected(FALSE);
    }

    CString sNumber;
    sNumber.Format("%d", m_nExtraSpells);
    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_NUMBER, sNumber);

    UpdateHelp(pPanel->m_nID, 27, 17253);
}

// 0x60AF60
void CScreenCreateChar::ResetMemorizeDivineSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CResRef resRef;

    UINT nClassIndex;
    UINT nLevel;

    for (nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            // NOTE: Uninline.
            pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->field_14 = 0;

            // NOTE: Uninline.
            pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->field_18 = 0;
        }
    }

    for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        pSprite->m_domainSpells.m_lists[nLevel].field_14 = 0;
        pSprite->m_domainSpells.m_lists[nLevel].field_18 = 0;
    }

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    UpdateLabel(pPanel,
        0x10000000,
        "%s: %s %d",
        (LPCSTR)FetchString(17224), // "Memorize Divine Spells"
        (LPCSTR)FetchString(7192), // "Level"
        m_nSpellLevel);

    for (nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
            // NOTE: Uninline.
            for (UINT nIndex = 0; nIndex < pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->m_List.size(); nIndex++) {
                UINT nID = pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel)->Get(nIndex)->m_nID;

                // __FILE__: .\Include\ObjCreature.h
                // __LINE__: 1741
                UTIL_ASSERT(nClassIndex <= CSPELLLIST_NUM_CLASSES);

                pSprite->m_spells.Get(nClassIndex)->sub_7260B0(nID, nLevel, 0, 1);

                // __FILE__: .\Include\ObjCreature.h
                // __LINE__: 1741
                UTIL_ASSERT(nClassIndex <= CSPELLLIST_NUM_CLASSES);

                // NOTE: Uninline.
                pSprite->m_spells.Get(nClassIndex)->Remove(nID, nLevel, 0, 1, 0);
            }
        }
    }

    pSprite->AddKnownDivineSpells(CAIOBJECTTYPE_C_CLERIC);
    pSprite->AddKnownDivineSpells(CAIOBJECTTYPE_C_DRUID);
    pSprite->AddKnownDivineSpells(CAIOBJECTTYPE_C_PALADIN);
    pSprite->AddKnownDivineSpells(CAIOBJECTTYPE_C_RANGER);

    INT nMaxKnownSpellsBonus;
    UINT nMaxKnownSpellsBase = ruleTables.GetMaxKnownSpells(pSprite->m_startTypeAI.m_nClass,
        pSprite->m_startTypeAI,
        *pSprite->GetDerivedStats(),
        pSprite->GetSpecialization(),
        1,
        nMaxKnownSpellsBonus);
    UINT nMaxKnownSpells = nMaxKnownSpellsBase + nMaxKnownSpellsBonus;

    if (nMaxKnownSpells >= pSprite->GetSpellsAtLevel(pSprite->m_startTypeAI.m_nClass, 0)->m_List.size()) {
        nMaxKnownSpells = pSprite->GetSpellsAtLevel(pSprite->m_startTypeAI.m_nClass, 0)->m_List.size();
    }

    m_nExtraSpells = nMaxKnownSpells;

    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 2724
        UTIL_ASSERT(pButton != NULL);

        pButton->SetSelected(FALSE);
    }

    CString sNumber;
    sNumber.Format("%d", m_nExtraSpells);
    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_NUMBER, sNumber);

    UpdateHelp(pPanel->m_nID, 27, 17254);
}

// 0x60B610
void CScreenCreateChar::ResetMemorizeDomainSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    UpdateLabel(pPanel,
        0x10000000,
        "%s: %s %d",
        (LPCSTR)FetchString(39848), // "Memorize Domain Spells"
        (LPCSTR)FetchString(7192), // "Level"
        m_nSpellLevel);

    for (UINT nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        // NOTE: Uninline.
        for (UINT nIndex = 0; nIndex < pSprite->m_domainSpells.GetSpellsAtLevel(nLevel)->m_List.size(); nIndex++) {
            UINT nID = pSprite->m_domainSpells.GetSpellsAtLevel(nLevel)->Get(nIndex)->m_nID;
            pSprite->m_domainSpells.sub_7260B0(nID, 0, 1, 0);
            pSprite->m_domainSpells.Remove(nID, 0, 0, 1, 0);
        }
    }

    // NOTE: Uninline.
    pSprite->m_domainSpells.Clear();

    DWORD dwClericSpecialization = pSprite->GetSpecialization() & SPECMASK_CLERIC;
    UINT nDomainIndex = g_pBaldurChitin->GetObjectGame()->GetSpellcasterDomainIndex(dwClericSpecialization);
    CGroupedSpellList* pSpells = &(g_pBaldurChitin->GetObjectGame()->m_spellsByDomain[nDomainIndex]);

    for (UINT nIndex = 0; nIndex < pSpells->m_lists[0].m_nCount; nIndex++) {
        // NOTE: Uninline.
        UINT nID = pSpells->m_lists[0].Get(nIndex);

        // NOTE: Uninline.
        const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID);

        pSprite->AddDomainSpell(0, resRef, 0, 0, 0);
    }

    m_nExtraSpells = 1;

    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 2795
        UTIL_ASSERT(pButton != NULL);

        pButton->SetSelected(FALSE);
    }

    CString sNumber;
    sNumber.Format("%d", m_nExtraSpells);
    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_NUMBER, sNumber);

    UpdateHelp(pPanel->m_nID, 27, 39852);
}

// 0x60BA30
void CScreenCreateChar::ResetClassPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CAIObjectType typeAI(pSprite->m_startTypeAI);
    typeAI.m_nClass = 0;
    pSprite->m_startTypeAI.Set(typeAI);

    pSprite->GetBaseStats()->m_specialization = 0;

    for (UINT nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
        // NOTE: Uninline.
        pSprite->m_spells.m_spellsByClass[nClassIndex].Clear();
    }

    // NOTE: Uninline.
    pSprite->m_domainSpells.Clear();

    // NOTE: Uninline.
    pSprite->m_innateSpells.Clear();

    UpdateHelp(pPanel->m_nID, 16, 17242);
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
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    INT nBestClass = pSprite->m_derivedStats.GetBestClass();

    const CString& sRace = ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    BYTE nMinRaceReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceReq.GetAt(sMin, sRace)));
    BYTE nMaxRaceReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceReq.GetAt(sMax, sRace)));
    BYTE nRaceAdj = static_cast<BYTE>(atol(ruleTables.m_tAbilityRaceAdj.GetAt(sMod, sRace)));

    const CString& sClass = ruleTables.GetClassString(nBestClass, pSprite->m_baseStats.m_specialization);
    BYTE nMinClassReq = static_cast<BYTE>(atol(ruleTables.m_tAbilityClassReq.GetAt(sMin, sClass)));

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
        nAbility = static_cast<BYTE>(g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nDefaultCharGenPoints);
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

    INT v1 = pGame->GetOptions()->m_nDefaultCharGenPoints;
    m_nExtraAbilityPoints = pGame->GetOptions()->m_nDefaultCharGenPointsPool + 6 * v1;

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

    if (m_nErrorState == 4) {
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
    INT iSkillNumber;
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CString sNumber;

    for (iSkillNumber = 0; iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS; iSkillNumber++) {
        pSprite->SetSkillValue(ruleTables.GetSkillId(iSkillNumber), 0);
    }

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    INT nExtraSkillPoints = pSprite->GetExtraSkillPoints(pSprite->m_startTypeAI.m_nClass);
    field_15E0 = nExtraSkillPoints;
    m_nExtraSkillPoints = nExtraSkillPoints;

    sNumber.Format("%d", nExtraSkillPoints);
    g_pBaldurChitin->m_cTlkTable.SetToken(TOKEN_NUMBER, sNumber);
    UpdateHelp(pPanel->m_nID, 92, 17248);

    for (iSkillNumber = 0; iSkillNumber < ruleTables.m_tSkills.GetHeight(); iSkillNumber++) {
        int value = atol(ruleTables.m_tSkills.GetAt(CPoint(pSprite->m_startTypeAI.m_nClass + 3, iSkillNumber)));
        pSprite->SetSkillValue(iSkillNumber, value);
    }

    m_nTopSkill = 0;
    while (m_nTopSkill < CGAMESPRITE_SKILL_NUMSKILLS) {
        m_storedSkills[m_nTopSkill] = pSprite->GetSkillValue(m_nTopSkill);
        m_nTopSkill++;
    }

    // Scroll to first available skill.
    m_nTopSkill = 0;
    while (m_nTopSkill < CGAMESPRITE_SKILL_NUMSKILLS) {
        if (pSprite->GetSkillCost(ruleTables.GetSkillId(m_nTopSkill), pSprite->m_startTypeAI.m_nClass) != 0) {
            break;
        }
        m_nTopSkill++;
    }

    for (UINT nSlot = 0; nSlot < SKILL_SLOTS; nSlot++) {
        CUIControlButton* pButton;
        INT nCost = pSprite->GetSkillCost(ruleTables.GetSkillId(nSlot), pSprite->m_startTypeAI.m_nClass);

        BOOL bEnabled = nCost != 0 && m_nExtraSkillPoints >= nCost;

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2 * nSlot + 14));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 3307
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bEnabled);
        pButton->SetActive(bEnabled);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2 * nSlot + 15));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 3314
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bEnabled);
        pButton->SetActive(bEnabled);
    }
}

// 0x60CA10
void CScreenCreateChar::ResetFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    INT nFeatNumber;

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CString sNumber;

    for (int index = 0; index < CGAMESPRITE_FEAT_NUMFEATS; index++) {
        pSprite->SetFeatValue(ruleTables.GetSkillId(index), 0);
    }

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    INT nExtraFeats = pSprite->GetExtraFeats(pSprite->m_startTypeAI.m_nClass);
    field_14AE = nExtraFeats;
    m_nExtraFeats = nExtraFeats;

    for (nFeatNumber = 0; nFeatNumber < ruleTables.m_tFeats.GetHeight(); nFeatNumber++) {
        int value = atol(ruleTables.m_tFeats.GetAt(CPoint(pSprite->m_startTypeAI.m_nClass + 2, nFeatNumber)));
        pSprite->SetFeatValue(nFeatNumber, value);
    }

    if (pSprite->m_startTypeAI.m_nClass == CAIOBJECTTYPE_C_CLERIC) {
        int offset;
        switch (pSprite->GetSpecialization()) {
        case SPECMASK_CLERIC_ILMATER:
            offset = 0;
            break;
        case SPECMASK_CLERIC_LATHANDER:
            offset = 1;
            break;
        case SPECMASK_CLERIC_SELUNE:
            offset = 2;
            break;
        case SPECMASK_CLERIC_HELM:
            offset = 3;
            break;
        case SPECMASK_CLERIC_OGHMA:
            offset = 4;
            break;
        case SPECMASK_CLERIC_TEMPUS:
            offset = 5;
            break;
        case SPECMASK_CLERIC_BANE:
            offset = 6;
            break;
        case SPECMASK_CLERIC_MASK:
            offset = 7;
            break;
        case SPECMASK_CLERIC_TALOS:
            offset = 8;
            break;
        }

        for (nFeatNumber = 0; nFeatNumber < ruleTables.m_tFeats.GetHeight(); nFeatNumber++) {
            int value = atol(ruleTables.m_tFeats.GetAt(CPoint(offset + 14, nFeatNumber)));
            if (value > 0 && value > pSprite->GetFeatValue(nFeatNumber)) {
                pSprite->SetFeatValue(nFeatNumber, value);
            }
        }
    }

    for (nFeatNumber = 0; nFeatNumber < ruleTables.m_tFeats.GetHeight(); nFeatNumber++) {
        int offset = GetRaceFeatColumn(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
        int value = atol(ruleTables.m_tFeats.GetAt(CPoint(offset + 23, nFeatNumber)));
        if (value > 0 && value > pSprite->GetFeatValue(nFeatNumber)) {
            pSprite->SetFeatValue(nFeatNumber, value);
        }
    }

    sNumber.Format("%d", m_nExtraFeats);

    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_NUMBER, sNumber);
    UpdateHelp(pPanel->m_nID, 92, 36476);

    for (m_nTopFeat = 0; m_nTopFeat < CGAMESPRITE_FEAT_NUMFEATS; m_nTopFeat++) {
        m_storedFeats[m_nTopFeat] = pSprite->GetFeatValue(m_nTopFeat);
    }

    for (m_nTopFeat = 0; m_nTopFeat < CGAMESPRITE_FEAT_NUMFEATS; m_nTopFeat++) {
        if (pSprite->sub_763A40(m_nTopFeat, 1)) {
            break;
        }
    }

    INT nSlot = 0;
    for (INT nButtonId = 15; nButtonId < 35; nButtonId += 2) {
        CUIControlButton* pButton;

        UINT nFeatNumber = ruleTables.GetFeatId(nSlot);

        BOOL bEnabled = pSprite->sub_763A40(nFeatNumber, 1);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButtonId - 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 3477
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bEnabled);
        pButton->SetActive(bEnabled);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButtonId));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 3484
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bEnabled);
        pButton->SetActive(bEnabled);

        nSlot++;
    }
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
            pButton->SetEnabled(IsDoneButtonClickable(pSprite));
        }
        break;
    case 6:
        UpdateSkillsPanel(pPanel, pSprite);
        break;
    case 7:
        UpdateArcaneSpellsPanel(pPanel, pSprite);
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
            pButton->SetEnabled(IsDoneButtonClickable(pSprite));
        }
        break;
    case 11:
        UpdateAppearancePanel(pPanel, pSprite);
        break;
    case 12:
        UpdateClericWizardSpecializationPanel(pPanel, pSprite);
        break;
    case 15:
        UpdateHatedRacePanel(pPanel, pSprite);
        break;
    case 16:
        UpdateMemorizeArcaneSpellsPanel(pPanel, pSprite);
        break;
    case 17:
        if (m_bPickingDomainSpells) {
            UpdateMemorizeDomainSpellsPanel(pPanel, pSprite);
        } else {
            UpdateMemorizeDivineSpellsPanel(pPanel, pSprite);
        }
        break;
    case 18:
        UpdateCustomPortraitsPanel(pPanel, pSprite);
        break;
    case 19:
        if (1) {
            CUIControlButton* pButton;

            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(46));

            pButton = static_cast<CUIControlButton*>(pPanel->GetControl(47));
            pButton->SetEnabled(m_nCustomSoundSetIndex >= 0);

            pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable(pSprite));
        }
        break;
    case 20:
        if (1) {
            if (field_1624 == NULL) {
                field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));
            }

            m_pCurrentScrollBar = field_1624;

            CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
            pButton->SetEnabled(IsDoneButtonClickable(pSprite));
        }
        break;
    case 21:
        if (1) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));

            CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 3679
            UTIL_ASSERT(pDone != NULL);

            pDone->SetEnabled(IsDoneButtonClickable(pSprite));
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

    sClass = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetClassString(pSprite->m_startTypeAI.m_nClass, 0);

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
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
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
    INT nIndex;

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    sRace = ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, pSprite->m_startTypeAI.m_nSubRace);
    sPureRace = ruleTables.GetRaceString(pSprite->m_startTypeAI.m_nRace, 0);

    sSubRaceFileName = ruleTables.m_tSrTable.GetAt(CString("SRFILE"), sPureRace);
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

    for (nIndex = 0; nIndex < m_tSubRace.GetHeight(); nIndex++) {
        INT nSubRaceListIndex = atol(m_tSubRace.GetAt(CPoint(0, nIndex)));
        INT nSubRaceId = atol(ruleTables.m_tSrList.GetAt(CPoint(4, nSubRaceListIndex)));
        if (nSubRaceId == 0) {
            ruleTables.GetRaceStringMixed(pSprite->m_startTypeAI.m_nRace, sRaceMixed, 0);
        } else {
            STRREF strRace = atol(ruleTables.m_tSrList.GetAt(CPoint(2, nSubRaceListIndex)));
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

    for (nIndex = 0; nIndex < m_tSubRace.GetHeight(); nIndex++) {
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
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60E080
void CScreenCreateChar::UpdateCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CString sPortrait;
    CUIControlButtonCharGenPortrait* pPortrait;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4067
    UTIL_ASSERT(pGame != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));

    pPortrait = static_cast<CUIControlButtonCharGenPortrait*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4072
    UTIL_ASSERT(pPortrait != NULL);

    sPortrait = "";
    if (m_nPortraitSmallIndex >= 0) {
        POSITION pos = m_pPortraits->FindIndex(m_nPortraitSmallIndex);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4077
        UTIL_ASSERT(pos != NULL);

        sPortrait = m_pPortraits->GetAt(pos);
    }

    // NOTE: Uninline.
    pPortrait->SetPortrait(CResRef(sPortrait));

    pPortrait = static_cast<CUIControlButtonCharGenPortrait*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4085
    UTIL_ASSERT(pPortrait != NULL);

    sPortrait = "";
    if (m_nPortraitLargeIndex >= 0) {
        POSITION pos = m_pPortraits->FindIndex(m_nPortraitLargeIndex);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4090
        UTIL_ASSERT(pos != NULL);

        sPortrait = m_pPortraits->GetAt(pos);
    }

    // NOTE: Uninline.
    pPortrait->SetPortrait(CResRef(sPortrait));

    UpdateLabel(pPanel, 0x10000007, "%s", sPortrait);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(6));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60E2D0
void CScreenCreateChar::UpdateAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    CUIControlButtonCharGenAppearancePortrait* pPortrait = static_cast<CUIControlButtonCharGenAppearancePortrait*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4188
    UTIL_ASSERT(pPortrait != NULL);

    CString sPortrait = GetCurrentPortrait(pSprite);

    // NOTE: Uninline.
    pPortrait->SetPortrait(CResRef(sPortrait + "L"));

    // FIXME: Redundant, previous `SetPortrait` has already invalidated button
    // if it was necessary.
    pPortrait->InvalidateRect();

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60E3E0
void CScreenCreateChar::UpdateFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    DWORD dwButtonId;

    if (field_1624 == NULL) {
        field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(104));
    }

    m_pCurrentScrollBar = field_1624;

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

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

    m_nTopFeat = min(m_nTopFeat, FEAT_COUNT - FEAT_SLOTS);

    for (dwButtonId = 14; dwButtonId <= 32; dwButtonId += 2) {
        DWORD index = (dwButtonId - 14) / 2;
        DWORD id = ruleTables.GetFeatId(m_nTopFeat + index);
        STRREF strName = ruleTables.GetFeatName(id);
        UpdateLabel(pPanel,
            0x10000001 + index,
            "%s",
            FetchString(strName));
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));

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
    for (dwButtonId = 15; dwButtonId < 35; dwButtonId += 2) {
        DWORD id = ruleTables.GetFeatId(m_nTopFeat + index);
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
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
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

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4454
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60EB60
void CScreenCreateChar::UpdateSkillsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    DWORD nButtonID;

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(104));

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    HighlightLabel(pPanel,
        0x1000000C,
        m_nExtraSkillPoints != 0,
        CBaldurEngine::COLOR_LABEL_HIGHLIGHT_BONUS);

    UpdateLabel(pPanel, 0x1000000C, "%d", m_nExtraSkillPoints);

    m_nTopSkill = min(m_nTopSkill, 6);

    for (nButtonID = 14; nButtonID < 33; nButtonID += 2) {
        DWORD nIndex = (nButtonID - 14) / 2;
        UINT nSkillID = ruleTables.GetSkillId(m_nTopSkill + nIndex);

        // FIXME: Why `GetSkillId` second time? It is not present in the code
        // path below.
        INT nCost = pSprite->GetSkillCost(ruleTables.GetSkillId(nSkillID), pSprite->m_startTypeAI.m_nClass);

        CString sName = FetchString(ruleTables.GetSkillName(nSkillID));
        if (nCost > 0) {
            UpdateLabel(pPanel,
                0x10000001 + nIndex,
                "%s (%d)",
                (LPCSTR)sName,
                nCost);
        } else {
            UpdateLabel(pPanel,
                0x10000001 + nIndex,
                "%s",
                (LPCSTR)sName);
        }
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));

    CUIControlScrollBarCharGenSkills* pScroll = static_cast<CUIControlScrollBarCharGenSkills*>(pPanel->GetControl(104));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 4587
    UTIL_ASSERT(pScroll != NULL);

    // NOTE: Uninline.
    pScroll->UpdateScrollBar();

    for (nButtonID = 15; nButtonID < 35; nButtonID += 2) {
        CUIControlButton* pButton;
        DWORD nIndex = (nButtonID - 15) / 2;
        UINT nSkillID = ruleTables.GetSkillId(m_nTopSkill + nIndex);
        INT nCost = pSprite->GetSkillCost(nSkillID, pSprite->m_startTypeAI.m_nClass);

        BOOL bCanIncrease = nCost != 0 && m_nExtraSkillPoints >= nCost;

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButtonID - 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4607
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bCanIncrease);
        pButton->SetActive(bCanIncrease);

        HighlightLabel(pPanel,
            0x10000001 + nIndex,
            !bCanIncrease,
            CBaldurEngine::COLOR_LABEL_DISABLE);

        BOOL bCanDecrease = m_storedSkills[m_nTopSkill + nIndex] < pSprite->GetSkillValue(m_nTopSkill + nIndex);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4620
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(bCanDecrease);
        pButton->SetActive(bCanDecrease);

        UpdateLabel(pPanel,
            0x10000069 + nIndex,
            "%d",
            pSprite->GetSkillValue(m_nTopSkill + nIndex));

        if (bCanDecrease) {
            HighlightLabel(pPanel,
                0x10000069 + nIndex,
                TRUE,
                RGB(0, 255, 255));
        } else if (bCanIncrease) {
            HighlightLabel(pPanel,
                0x10000069 + nIndex,
                TRUE,
                CBaldurEngine::COLOR_LABEL_NORMAL);
        } else {
            HighlightLabel(pPanel,
                0x10000069 + nIndex,
                TRUE,
                CBaldurEngine::COLOR_LABEL_DISABLE);
        }
    }

    pPanel->InvalidateRect(NULL);
}

// 0x60EF70
void CScreenCreateChar::UpdateArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));
    CResRef resRef;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    UINT nClassIndex = pGame->GetSpellcasterIndex(pSprite->m_startTypeAI.m_nClass);

    HighlightLabel(pPanel,
        0x1000001B,
        m_nExtraSpells != 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel,
        0x1000001B,
        "%d",
        m_nExtraSpells);

    UINT nSpells = pGame->m_spellsByClass[nClassIndex].m_lists[0].m_nCount;
    UINT nIndex = 0;

    for (DWORD nButtonID = 2; nButtonID <= 25; nButtonID++) {
        CUIControlButtonCharGenKnownArcaneSpellSelection* pButton = static_cast<CUIControlButtonCharGenKnownArcaneSpellSelection*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4695
        UTIL_ASSERT(pButton != NULL);

        // NOTE: Implementation is different. Original code has many inlined
        // stuff which is likely impossible to replicate one to one.
        while (nIndex < nSpells) {
            UINT nID = pGame->m_spellsByClass[nClassIndex].m_lists[0].Get(nIndex);
            resRef = pGame->m_spells.Get(nID);

            CSpell cSpell;
            cSpell.SetResRef(resRef, TRUE, TRUE);
            BOOL bUsable = cSpell.pRes != NULL && cSpell.CheckUsableBy(pSprite) == TRUE;
            cSpell.Release();

            if (bUsable) {
                break;
            }

            nIndex++;
        }

        if (nIndex < nSpells) {
            pButton->SetSpell(resRef);
            pButton->SetEnabled(TRUE);
        } else {
            pButton->SetSpell(CResRef(""));
            pButton->SetEnabled(FALSE);
        }

        nIndex++;
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    BOOL bIsDoneClickable = IsDoneButtonClickable(pSprite);
    pDone->SetEnabled(bIsDoneClickable);

    CUIControlButton* pAutoPick = static_cast<CUIControlButton*>(pPanel->GetControl(30));
    pAutoPick->SetEnabled(!bIsDoneClickable);
}

// 0x60F430
void CScreenCreateChar::UpdateMemorizeArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));

    CGameSpriteSpellList* pSpells = pSprite->GetSpellsAtLevel(pSprite->m_startTypeAI.m_nClass, 0);
    UINT nSpells = pSpells->m_List.size();
    CResRef resRef;

    UINT nIndex = 0;
    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButtonCharGenMemorizedArcaneSpellSelection* pButton = static_cast<CUIControlButtonCharGenMemorizedArcaneSpellSelection*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4781
        UTIL_ASSERT(pButton != NULL);

        // NOTE: Implementation is different. Original code has many inlined
        // stuff which is likely impossible to replicate one to one.
        while (nIndex < nSpells) {
            // TODO: Unclear.
            pSpells->CheckF8(nIndex);

            UINT nID = pSpells->m_List[nIndex].m_nID;
            resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID);

            CSpell cSpell;
            cSpell.SetResRef(resRef, TRUE, TRUE);
            cSpell.Demand();
            BOOL bUsable = cSpell.pRes != NULL && cSpell.CheckUsableBy(pSprite) == TRUE;
            cSpell.Release();

            if (bUsable) {
                break;
            }

            nIndex++;
        }

        if (nIndex < nSpells) {
            pButton->SetSpell(resRef);
            pButton->SetEnabled(TRUE);
        } else {
            pButton->SetSpell(CResRef(""));
            pButton->SetEnabled(FALSE);
        }

        nIndex++;
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));

    HighlightLabel(pPanel,
        0x1000001B,
        m_nExtraSpells != 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel, 0x1000001B, "%d", m_nExtraSpells);
}

// 0x60F810
void CScreenCreateChar::UpdateMemorizeDivineSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));

    CGameSpriteSpellList* pSpells = pSprite->GetSpellsAtLevel(pSprite->m_startTypeAI.m_nClass, 0);
    UINT nSpells = pSpells->m_List.size();

    UINT nIndex = 0;
    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButtonCharGenMemorizedDivineSpellSelection* pButton = static_cast<CUIControlButtonCharGenMemorizedDivineSpellSelection*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4863
        UTIL_ASSERT(pButton != NULL);

        if (nIndex < nSpells) {
            UINT nID = pSpells->Get(nIndex)->m_nID;
            pButton->SetSpell(g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID));
            pButton->SetEnabled(TRUE);
        } else {
            pButton->SetSpell(CResRef(""));
            pButton->SetEnabled(FALSE);
        }

        nIndex++;
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));

    HighlightLabel(pPanel,
        0x1000001B,
        m_nExtraSpells != 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel, 0x1000001B, "%d", m_nExtraSpells);
}

// 0x60FA40
void CScreenCreateChar::UpdateMemorizeDomainSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));

    CGameSpriteSpellList* pSpells = &(pSprite->m_domainSpells.m_lists[0]);
    UINT nSpells = pSpells->m_List.size();

    UINT nIndex = 0;
    for (DWORD nButtonID = 2; nButtonID <= 13; nButtonID++) {
        CUIControlButtonCharGenMemorizedDivineSpellSelection* pButton = static_cast<CUIControlButtonCharGenMemorizedDivineSpellSelection*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 4863
        UTIL_ASSERT(pButton != NULL);

        if (nIndex < nSpells) {
            UINT nID = pSpells->Get(nIndex)->m_nID;
            pButton->SetSpell(g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID));
            pButton->SetEnabled(TRUE);
        } else {
            pButton->SetSpell(CResRef(""));
            pButton->SetEnabled(FALSE);
        }

        nIndex++;
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));

    HighlightLabel(pPanel,
        0x1000001B,
        m_nExtraSpells != 0,
        COLOR_LABEL_HIGHLIGHT_BONUS);
    UpdateLabel(pPanel, 0x1000001B, "%d", m_nExtraSpells);
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
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60FDB0
void CScreenCreateChar::UpdateAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(12));

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    for (INT nButton = 2; nButton <= 10; nButton++) {
        CUIControlButtonCharGenAlignmentSelection* pAlignment = static_cast<CUIControlButtonCharGenAlignmentSelection*>(pPanel->GetControl(nButton));

        // NOTE: Uninline.
        BYTE nAlignment = pAlignment->GetAlignment();

        pAlignment->SetSelected(pSprite->m_startTypeAI.m_nAlignment == nAlignment);

        BOOL bIsValid = ruleTables.IsValidAlignment(pSprite->m_startTypeAI.m_nClass,
            nAlignment,
            pSprite->m_baseStats.m_specialization);
        pAlignment->SetEnabled(bIsValid);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x60FEE0
void CScreenCreateChar::UpdateClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(10));

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    if (pSprite->m_startTypeAI.IsClassValid(CAIObjectType::C_WIZARD)) {
        for (INT nButtonId = 2; nButtonId <= 13; nButtonId++) {
            // FIXME: Should be outside of the loop.
            CString sClassName;
            if (nButtonId <= 9 || nButtonId >= 13) {
                CUIControlButtonClericWizardSpecializationSelection* pButton = static_cast<CUIControlButtonClericWizardSpecializationSelection*>(pPanel->GetControl(nButtonId));
                DWORD nSpecialization = pSprite->m_baseStats.m_specialization;
                BOOLEAN bSelected = (pButton->GetSpecialization(CAIOBJECTTYPE_C_WIZARD) & nSpecialization) != 0;

                // FIXME: Meaningless at this point as was already used.
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
                // __LINE__: 5258
                UTIL_ASSERT(pButton != NULL);

                pButton->SetSelected(bSelected);
                pButton->SetEnabled(TRUE);
                ruleTables.GetClassStringLower(CAIOBJECTTYPE_C_WIZARD,
                    pButton->GetSpecialization(CAIOBJECTTYPE_C_WIZARD),
                    0,
                    sClassName,
                    1);
                pButton->SetText(sClassName);
            }
        }
    } else if (pSprite->m_startTypeAI.IsClassValid(CAIObjectType::C_CLERIC)) {
        for (INT nButtonId = 2; nButtonId <= 13; nButtonId++) {
            if (nButtonId <= 9 || nButtonId >= 13) {
                CUIControlButtonClericWizardSpecializationSelection* pButton = static_cast<CUIControlButtonClericWizardSpecializationSelection*>(pPanel->GetControl(nButtonId));
                DWORD nSpecialization = pSprite->m_baseStats.m_specialization;
                BOOLEAN bSelected = (pButton->GetSpecialization(CAIOBJECTTYPE_C_CLERIC) & nSpecialization) != 0;

                pButton->SetSelected(bSelected);
                pButton->SetEnabled(TRUE);

                STRREF strClass;
                switch (nButtonId) {
                case 13:
                    strClass = 38097; // "Painbearer of Ilmater"
                    break;
                case 2:
                    strClass = 38098; // "Morninglord of Lathander"
                    break;
                case 3:
                    strClass = 38099; // "Silverstar of Selune"
                    break;
                case 4:
                    strClass = 38100; // "Watcher of Helm"
                    break;
                case 5:
                    strClass = 38101; // "Lorekeeper of Oghma"
                    break;
                case 7:
                    strClass = 38102; // "Battleguard of Tempus"
                    break;
                case 6:
                    strClass = 38103; // "Dreadmaster of Bane"
                    break;
                case 8:
                    strClass = 38106; // "Demarch of Mask"
                    break;
                case 9:
                    strClass = 38107; // "Stormlord of Talos"
                    break;
                }

                pButton->SetText(FetchString(strClass));
            }
        }
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 5293
        UTIL_ASSERT(FALSE);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
}

// 0x610190
void CScreenCreateChar::UpdateHatedRacePanel(CUIPanel* pPanel, CGameSprite* pSprite)
{
    if (field_1624 == NULL) {
        field_1624 = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));
    }

    m_pCurrentScrollBar = field_1624;

    for (INT nIndex = 0; nIndex < 11; nIndex++) {
        // NOTE: Uninline.
        BYTE nRace = GetHatedRace(nIndex);

        CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(22 + nIndex));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 5346
        UTIL_ASSERT(pButton != NULL);

        pButton->SetText(FetchString(GetRangerHatedRaceStrref(nRace)));
        pButton->SetSelected(nRace == pSprite->m_baseStats.m_favoredEnemies[0]);
        pButton->SetEnabled(!g_pBaldurChitin->GetObjectGame()->GetRuleTables().IsHatedRace(nRace, pSprite->m_baseStats)
            || pButton->m_bSelected);
    }

    CUIControlScrollBarCharGenHatedRace* pScrollBar = static_cast<CUIControlScrollBarCharGenHatedRace*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5359
    UTIL_ASSERT(pScrollBar != NULL);

    // NOTE: Uninline.
    pScrollBar->UpdateScrollBar();

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(0));
    pDone->SetEnabled(IsDoneButtonClickable(pSprite));
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

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
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

// NOTE: Inlined.
void CScreenCreateChar::IncCurrentPortrait(CGameSprite* pSprite)
{
    INT nCount;
    switch (pSprite->m_startTypeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        nCount = sizeof(MALE_PORTRAITS) / sizeof(MALE_PORTRAITS[0]);
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        nCount = sizeof(FEMALE_PORTRAITS) / sizeof(FEMALE_PORTRAITS[0]);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 5575
        UTIL_ASSERT(FALSE);
    }

    m_nCurrentPortrait = (m_nCurrentPortrait + 1) % nCount;
}

void CScreenCreateChar::DecCurrentPortrait(CGameSprite* pSprite)
{
    INT nCount;
    switch (pSprite->m_startTypeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        nCount = sizeof(MALE_PORTRAITS) / sizeof(MALE_PORTRAITS[0]);
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        nCount = sizeof(FEMALE_PORTRAITS) / sizeof(FEMALE_PORTRAITS[0]);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 5618
        UTIL_ASSERT(FALSE);
    }

    m_nCurrentPortrait = (m_nCurrentPortrait + nCount - 1) % nCount;
}

// 0x610540
void CScreenCreateChar::StartCreateChar(INT nCharacterSlot, INT nEngineState)
{
    // 0x8B35E0
    static WORD facing[6][2] = {
        { 12, 0 },
        { 8, 0 },
        { 6, 0 },
        { 0, 0 },
        { 0, 0 },
        { 14, 0 },
    };

    field_14A4 = 0;
    field_14A8 = 0;
    m_nCharacterSlot = nCharacterSlot;
    m_nEngineState = nEngineState;
    m_nFirstStep = 0;
    m_nCurrentStep = 0;

    CCreatureFile cCreatureData;

    // NOTE: Uninline.
    cCreatureData.SetResRef(CResRef("CHARBASE"), TRUE, TRUE);

    CGameSprite* pSprite = new CGameSprite(reinterpret_cast<BYTE*>(cCreatureData.GetData()),
        cCreatureData.GetDataSize(),
        0,
        0,
        -1,
        0,
        0,
        INT_MAX,
        CPoint(-1, -1),
        facing[nCharacterSlot][0]);

    pSprite->SetResRef(cCreatureData.GetResRef());

    cCreatureData.Release();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5725
    UTIL_ASSERT(pSprite != NULL);

    m_nGameSprite = pSprite->m_id;

    pSprite->m_bGlobal = TRUE;
    pSprite->GetBaseStats()->m_flags = 0x800;
    pSprite->GetBaseStats()->m_xp = 0;
    pSprite->GetBaseStats()->field_3E = 10;
    pSprite->GetBaseStats()->m_numberOfAttacksBase = 1;
    pSprite->GetBaseStats()->m_skills[15] = 0;
    pSprite->GetBaseStats()->m_morale = 10;
    pSprite->GetBaseStats()->m_moraleBreak = 0;
    pSprite->GetBaseStats()->m_moraleRecoveryTime = 1;
    pSprite->m_dialog = "MULTIG";
    pSprite->GetBaseStats()->m_reputation = 100;

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    STRREF strTitle = 28210; // "Finish"
    if (nEngineState == 4) {
        strTitle = 13956; // "Export"
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5737
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(8));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5739
    UTIL_ASSERT(pPanel != NULL);

    pButton->SetText(FetchString(strTitle));
}

// NOTE: Inlined.
void CScreenCreateChar::CancelCreateChar()
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 5811
    UTIL_ASSERT(pSettings != NULL);

    DeleteCharacter();

    if (m_nEngineState != 4
        && pSettings->GetCharacterStatus(m_nCharacterSlot) != CMultiplayerSettings::CHARSTATUS_CHARACTER) {
        pSettings->SignalCharacterStatus(m_nCharacterSlot,
            CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_CANCEL,
            TRUE,
            TRUE);
    }

    m_nCharacterSlot = -1;
    m_nEngineState = 0;
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
void CScreenCreateChar::OnPortraitLargeItemSelect(INT nItem)
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
        if (nItem != m_nPortraitLargeIndex) {
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

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x610A40
void CScreenCreateChar::OnPortraitSmallItemSelect(INT nItem)
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
        if (nItem != m_nPortraitSmallIndex) {
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
void CScreenCreateChar::UpdateCharacterStats(CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CAIObjectType typeAI(pSprite->m_startTypeAI);

    // NOTE: Unused (besides assignment).
    CDerivedStats DStats;

    pSprite->GetDerivedStats()->m_barbarianLevel = 0;
    pSprite->GetDerivedStats()->m_bardLevel = 0;
    pSprite->GetDerivedStats()->m_clericLevel = 0;
    pSprite->GetDerivedStats()->m_druidLevel = 0;
    pSprite->GetDerivedStats()->m_fighterLevel = 0;
    pSprite->GetDerivedStats()->m_monkLevel = 0;
    pSprite->GetDerivedStats()->m_paladinLevel = 0;
    pSprite->GetDerivedStats()->m_rangerLevel = 0;
    pSprite->GetDerivedStats()->m_rogueLevel = 0;
    pSprite->GetDerivedStats()->m_sorcererLevel = 0;
    pSprite->GetDerivedStats()->m_wizardLevel = 0;
    pSprite->GetDerivedStats()->m_nLevel = 0;
    pSprite->GetDerivedStats()->m_classMask = 0;
    pSprite->GetDerivedStats()->m_nXP = 0;

    // TODO: Incomplete.
    // DStats = *pSprite->GetDerivedStats();

    ruleTables.GetNextLevel(typeAI.m_nClass, *pSprite->GetDerivedStats(), pSprite);

    pSprite->GetBaseStats()->m_barbarianLevel = pSprite->GetDerivedStats()->m_barbarianLevel;
    pSprite->GetBaseStats()->m_bardLevel = pSprite->GetDerivedStats()->m_bardLevel;
    pSprite->GetBaseStats()->m_clericLevel = pSprite->GetDerivedStats()->m_clericLevel;
    pSprite->GetBaseStats()->m_druidLevel = pSprite->GetDerivedStats()->m_druidLevel;
    pSprite->GetBaseStats()->m_fighterLevel = pSprite->GetDerivedStats()->m_fighterLevel;
    pSprite->GetBaseStats()->m_monkLevel = pSprite->GetDerivedStats()->m_monkLevel;
    pSprite->GetBaseStats()->m_paladinLevel = pSprite->GetDerivedStats()->m_paladinLevel;
    pSprite->GetBaseStats()->m_rangerLevel = pSprite->GetDerivedStats()->m_rangerLevel;
    pSprite->GetBaseStats()->m_rogueLevel = pSprite->GetDerivedStats()->m_rogueLevel;
    pSprite->GetBaseStats()->m_sorcererLevel = pSprite->GetDerivedStats()->m_sorcererLevel;
    pSprite->GetBaseStats()->m_wizardLevel = pSprite->GetDerivedStats()->m_wizardLevel;
    pSprite->GetBaseStats()->m_characterLevel = pSprite->GetDerivedStats()->m_nLevel;

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    int v1;
    int v2;
    int v3;
    ruleTables.sub_546B60(pSprite, v1, v2, v3, FALSE);

    pSprite->GetBaseStats()->m_attackBase = v1;
    pSprite->GetDerivedStats()->m_nLayOnHandsAmount = ruleTables.GetLayOnHandsAmount(typeAI, *pSprite->GetDerivedStats());
    pSprite->GetBaseStats()->m_colors[0] = 30;
    pSprite->GetBaseStats()->m_colors[1] = 39;
    pSprite->GetBaseStats()->m_colors[2] = 41;
    pSprite->GetBaseStats()->m_colors[3] = 12;
    pSprite->GetBaseStats()->m_colors[4] = 23;
    pSprite->GetBaseStats()->m_colors[5] = 30;
    pSprite->GetBaseStats()->m_colors[6] = 0;

    DWORD genderID;
    switch (typeAI.m_nGender) {
    case CAIOBJECTTYPE_SEX_MALE:
        genderID = 0x0;
        break;
    case CAIOBJECTTYPE_SEX_FEMALE:
        genderID = 0x10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 6653
        UTIL_ASSERT(FALSE);
    }

    DWORD raceID;
    switch (typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        raceID = 0x0;
        break;
    case CAIOBJECTTYPE_R_ELF:
    case CAIOBJECTTYPE_R_HALF_ELF:
        raceID = 0x1;
        break;
    case CAIOBJECTTYPE_R_DWARF:
        raceID = 0x2;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        raceID = 0x3;
        break;
    case CAIOBJECTTYPE_R_GNOME:
        raceID = 0x4;
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        raceID = 0x5;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 6686
        UTIL_ASSERT(FALSE);
    }

    DWORD classID;
    switch (typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
    case CAIOBJECTTYPE_C_FIGHTER:
    case CAIOBJECTTYPE_C_MONK:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        classID = 0x100;
        break;
    case CAIOBJECTTYPE_C_BARD:
    case CAIOBJECTTYPE_C_ROGUE:
        classID = 0x300;
        break;
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
        classID = 0x000;
        break;
    case CAIOBJECTTYPE_C_SORCERER:
    case CAIOBJECTTYPE_C_WIZARD:
        classID = 0x200;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 6721
        UTIL_ASSERT(FALSE);
    }

    USHORT animationID = static_cast<USHORT>(genderID | raceID | classID | 0x6000);

    // NOTE: Looks like inlined `CGameAnimation::SetAnimationType` but without
    // post-assignment assertion.
    if (pSprite->m_animation.m_animation != NULL) {
        delete pSprite->m_animation.m_animation;
    }
    pSprite->m_animation.m_animation = CGameAnimationType::SetAnimationType(animationID,
        pSprite->GetBaseStats()->m_colors,
        0);
    pSprite->GetBaseStats()->m_animationType = animationID;

    CString sRace = ruleTables.GetRaceString(typeAI.m_nRace, typeAI.m_nSubRace);
    pSprite->GetBaseStats()->m_resistFireBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::FIRE, sRace)));
    pSprite->GetBaseStats()->m_resistColdBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::COLD, sRace)));
    pSprite->GetBaseStats()->m_resistElectricityBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::ELEC, sRace)));
    pSprite->GetBaseStats()->m_resistAcidBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::ACID, sRace)));
    pSprite->GetBaseStats()->m_resistMagicBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::SPELL, sRace)));
    pSprite->GetBaseStats()->m_resistMagicFireBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::MAGIC_FIRE, sRace)));
    pSprite->GetBaseStats()->m_resistMagicColdBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::MAGIC_COLD, sRace)));
    pSprite->GetBaseStats()->m_resistSlashingBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::SLASHING, sRace)));
    pSprite->GetBaseStats()->m_resistCrushingBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::BLUDGEONING, sRace)));
    pSprite->GetBaseStats()->m_resistPiercingBase = static_cast<BYTE>(atol(ruleTables.m_tRaceRsMd.GetAt(CRuleTables::PIERCING, sRace)));

    CString sClass = ruleTables.GetClassString(typeAI.m_nClass, pSprite->GetSpecialization());
    pSprite->GetBaseStats()->m_resistFireBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::FIRE, sClass)));
    pSprite->GetBaseStats()->m_resistColdBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::COLD, sClass)));
    pSprite->GetBaseStats()->m_resistElectricityBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::ELEC, sClass)));
    pSprite->GetBaseStats()->m_resistAcidBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::ACID, sClass)));
    pSprite->GetBaseStats()->m_resistMagicBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::SPELL, sClass)));
    pSprite->GetBaseStats()->m_resistMagicFireBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::MAGIC_FIRE, sClass)));
    pSprite->GetBaseStats()->m_resistMagicColdBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::MAGIC_COLD, sClass)));
    pSprite->GetBaseStats()->m_resistSlashingBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::SLASHING, sClass)));
    pSprite->GetBaseStats()->m_resistCrushingBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::BLUDGEONING, sClass)));
    pSprite->GetBaseStats()->m_resistPiercingBase += static_cast<BYTE>(atol(ruleTables.m_tClassRsMd.GetAt(CRuleTables::PIERCING, sClass)));

    // TODO: Incomplete (base skills).

    UpdateCharacterAppearance();
}

// 0x612800
void CScreenCreateChar::UpdateCharacterAppearance()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(GetSpriteId(),
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        m_animation.SetAnimationType(pSprite->m_baseStats.m_animationType, pSprite->m_baseStats.m_colors, 0);

        pSprite->UnequipAll(TRUE);
        pSprite->EquipAll(TRUE);

        m_animation.SetSequence(pSprite->GetIdleSequence());

        pGame->GetObjectArray()->ReleaseShare(GetSpriteId(),
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x612930
void CScreenCreateChar::CompleteCharacterAbilities(CGameSprite* pSprite)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CAIObjectType typeAI(pSprite->m_startTypeAI);
    CDerivedStats DStats;

    DStats.m_barbarianLevel = 0;
    DStats.m_bardLevel = 0;
    DStats.m_clericLevel = 0;
    DStats.m_druidLevel = 0;
    DStats.m_fighterLevel = 0;
    DStats.m_monkLevel = 0;
    DStats.m_paladinLevel = 0;
    DStats.m_rangerLevel = 0;
    DStats.m_rogueLevel = 0;
    DStats.m_sorcererLevel = 0;
    DStats.m_wizardLevel = 0;

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();

    INT nHitPoints = ruleTables.GetStartingHitPoints(typeAI,
        *pSprite->GetDerivedStats(),
        pSprite->GetBaseStats()->m_CONBase);

    pSprite->GetBaseStats()->m_maxHitPointsBase = nHitPoints;
    pSprite->GetBaseStats()->m_hitPoints = nHitPoints;

    pSprite->field_7234 = 0;

    pSprite->GetBaseStats()->m_saveVSFortitudeBase = ruleTables.GetSavingThrow(typeAI,
        *pSprite->GetDerivedStats(),
        pSprite->GetBaseStats()->m_CONBase,
        CRuleTables::FORTITUDE);
    pSprite->GetBaseStats()->m_saveVSReflexBase = ruleTables.GetSavingThrow(typeAI,
        *pSprite->GetDerivedStats(),
        pSprite->GetBaseStats()->m_CONBase,
        CRuleTables::REFLEX);
    pSprite->GetBaseStats()->m_saveVSWillBase = ruleTables.GetSavingThrow(typeAI,
        *pSprite->GetDerivedStats(),
        pSprite->GetBaseStats()->m_CONBase,
        CRuleTables::WILL);

    pSprite->m_innateSpells.Clear();

    pSprite->sub_71E760(DStats, 1);

    pSprite->GetBaseStats()->m_xp = ruleTables.GetStartingExperiencePoints(pSprite);

    pSprite->field_562C = 1;
    pSprite->ProcessEffectList();
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
            SetSpriteId(CGameObjectArray::INVALID_INDEX);
        } else {
            SetSpriteId(CGameObjectArray::INVALID_INDEX);
        }
    }
}

// 0x613B20
void CScreenCreateChar::ImportCharacter()
{
    // TODO: Incomplete.
}

// 0x613EF0
void CScreenCreateChar::OnPlayButtonClick()
{
    INT nGameSprite = GetSpriteId();

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

// 0x614450
void CScreenCreateChar::OnSoundItemSelect(INT nItem)
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
        if (nItem != m_nCustomSoundSetIndex) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 7999
            UTIL_ASSERT(m_pSounds != NULL);

            CUIPanel* pPanel = m_cUIManager.GetPanel(19);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 8003
            UTIL_ASSERT(pPanel != NULL);

            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(45));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 8005
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

// 0x615B70
BOOL CScreenCreateChar::IsDoneButtonClickable(CGameSprite* pSprite)
{
    CString v1;
    CString v2;
    CUIControlEdit* pEdit;

    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 8840
    UTIL_ASSERT(pPanel != NULL);

    CAIObjectType typeAI(pSprite->m_startTypeAI);

    BOOL bClickable;

    switch (pPanel->m_nID) {
    case 1:
        bClickable = typeAI.m_nGender != 0;
        break;
    case 2:
        bClickable = typeAI.m_nClass != 0;
        break;
    case 3:
        bClickable = typeAI.m_nAlignment != 0;
        break;
    case 4:
    case 11:
    case 13:
    case 14:
    case 51:
    case 53:
    case 54:
        bClickable = TRUE;
        break;
    case 5:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(2));
        v1 = pEdit->GetText();
        v1.TrimLeft();
        v1.TrimRight();
        bClickable = v1 != "";
        break;
    case 6:
        bClickable = m_nExtraSkillPoints == 0;
        break;
    case 7:
        bClickable = m_nExtraSpells == 0;
        break;
    case 8:
        bClickable = typeAI.m_nRace != 0;
        break;
    case 12:
        if (typeAI.m_nClass == CAIOBJECTTYPE_C_WIZARD) {
            bClickable = (pSprite->GetSpecialization() & 0x7FC0) != 0;
        } else if (typeAI.m_nClass == CAIOBJECTTYPE_C_CLERIC) {
            bClickable = (pSprite->GetSpecialization() & 0xFF8000) != 0;
        } else {
            bClickable = FALSE;
        }
        break;
    case 15:
        bClickable = pSprite->m_baseStats.m_favoredEnemies[0] != CAIObjectType::R_NO_RACE;
        break;
    case 16:
        bClickable = m_nExtraSpells == 0;
        break;
    case 17:
        bClickable = m_nExtraSpells == 0;
        break;
    case 18:
        bClickable = m_nPortraitSmallIndex >= 0 && m_nPortraitLargeIndex >= 0;
        break;
    case 19:
        bClickable = m_nCustomSoundSetIndex >= 0;
        break;
    case 20:
        bClickable = m_nCharacterIndex >= 0;
        break;
    case 21:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(7));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 8960
        UTIL_ASSERT(pEdit != NULL);

        v2 = pEdit->GetText();
        v2.TrimLeft();
        v2.TrimRight();
        bClickable = v2 != "";
        break;
    case 52:
        bClickable = pSprite->m_baseStats.m_specialization != 0;
        break;
    case 55:
        bClickable = m_nExtraFeats == 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 8975
        UTIL_ASSERT(FALSE);
    }

    return bClickable;
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

// 0x6171A0
void CScreenCreateChar::OnCancelButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = m_nGameSprite;

    // FIXME: Unused.
    CString v1;

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        CUIPanel* pPanel = GetTopPopup();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 9624
        UTIL_ASSERT(pPanel != NULL);

        switch (pPanel->m_nID) {
        case 7:
        case 15:
            DismissPopup(pSprite);
            SummonPopup(55, pSprite);
            break;
        case 12:
        case 52:
            if (1) {
                CAIObjectType typeAI(pSprite->m_startTypeAI);
                typeAI.m_nClass = 0;
                pSprite->m_startTypeAI.Set(typeAI);
                pSprite->m_baseStats.m_specialization = 0;

                DismissPopup(pSprite);
            }
            break;
        case 16:
            DismissPopup(pSprite);
            SummonPopup(7, pSprite);
            break;
        case 17:
            if (m_bPickingDomainSpells) {
                m_bPickingDomainSpells = FALSE;
                DismissPopup(pSprite);
                SummonPopup(17, pSprite);
            } else {
                DismissPopup(pSprite);
                SummonPopup(55, pSprite);
            }
            break;
        case 18:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 9630
            UTIL_ASSERT(m_pPortraits != NULL);

            delete m_pPortraits;
            m_pPortraits = NULL;

            DismissPopup(pSprite);
            break;
        case 19:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 9656
            UTIL_ASSERT(m_pSounds != NULL);

            delete m_pSounds;
            m_pSounds = NULL;

            DismissPopup(pSprite);
            break;
        case 20:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 9638
            UTIL_ASSERT(m_pCharacters != NULL);

            delete m_pCharacters;
            m_pCharacters = NULL;

            DismissPopup(pSprite);
            break;
        case 21:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 9646
            UTIL_ASSERT(m_pCharacters != NULL);

            delete m_pCharacters;
            m_pCharacters = NULL;

            DismissPopup(pSprite);
            break;
        case 54:
            if (1) {
                CAIObjectType typeAI(pSprite->m_startTypeAI);
                typeAI.m_nSubRace = 0;
                pSprite->m_startTypeAI.Set(typeAI);

                DismissPopup(pSprite);
            }
            break;
        case 55:
            DismissPopup(pSprite);
            SummonPopup(6, pSprite);
            break;
        default:
            DismissPopup(pSprite);
            break;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x6175A0
void CScreenCreateChar::OnMainCancelButtonClick()
{
    // NOTE: Original code is different. Somehow it casts `CScreenSinglePlayer`
    // as `CScreenMultiPlayer` into one variable with only one assertion at
    // line 9758 (seen in multiplayer path below).
    if (g_pChitin->cNetwork.m_nServiceProvider == CNetwork::SERV_PROV_NULL) {
        CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

        UTIL_ASSERT(pSinglePlayer != NULL);
    } else {
        CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 9758
        UTIL_ASSERT(pMultiPlayer != NULL);
    }

    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 9762
    UTIL_ASSERT(pConnection != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 9764
    UTIL_ASSERT(pGame != NULL);

    g_pChitin->cVideo.ResetDoubleSizeData();

    if (m_nCurrentStep > 0) {
        // NOTE: Uninline.
        INT nGameSprite = GetSpriteId();

        CGameSprite* pSprite;
        BYTE rc;
        do {
            rc = pGame->GetObjectArray()->GetShare(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            m_nErrorState = 0;
            SummonPopup(53, pSprite);

            pGame->GetObjectArray()->ReleaseShare(nGameSprite,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    } else {
        switch (m_nEngineState) {
        case 1:
            // NOTE: Uninline.
            CancelCreateChar();

            pGame->DestroyGame(1, 0);

            SelectEngine(pConnection);
            break;
        case 2:
            // NOTE: Uninline.
            CancelCreateChar();

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                g_pChitin->cNetwork.CloseSession(TRUE);
            }

            pGame->DestroyGame(1, 0);

            pConnection->SetEliminateInitialize(TRUE);
            SelectEngine(pConnection);
            break;
        case 3:
            // NOTE: Uninline.
            CancelCreateChar();

            // NOTE: Original code is different. It uses one variable for
            // either `CScreenSinglePlayer` or `CScreenMultiPlayer` which was
            // set earlier. It calls `StartMultiPlayer` which seems to be binary
            // identical to `StartSinglePlayer`.
            if (g_pChitin->cNetwork.m_nServiceProvider == CNetwork::SERV_PROV_NULL) {
                g_pBaldurChitin->m_pEngineSinglePlayer->field_45C = 1;
                g_pBaldurChitin->m_pEngineSinglePlayer->StartSinglePlayer(1);
                g_pBaldurChitin->m_pEngineSinglePlayer->field_138E = 1;
                SelectEngine(g_pBaldurChitin->m_pEngineSinglePlayer);
            } else {
                g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 1;
                g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(1);
                g_pBaldurChitin->m_pEngineMultiPlayer->field_138E = 1;
                SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);
            }

            break;
        case 4:
            // NOTE: Uninline.
            CancelCreateChar();

            SelectEngine(pConnection);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 9845
            UTIL_ASSERT(FALSE);
        }
    }
}

// NOTE: Inlined.
CUIPanel* CScreenCreateChar::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenCreateChar::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1580
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Inlined.
void CScreenCreateChar::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 1624
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// 0x6179D0
void CScreenCreateChar::SummonPopup(DWORD dwPopupId, CGameSprite* pSprite)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pOldPanel = NULL;

    if (m_lPopupStack.GetCount() != 0) {
        pOldPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 9926
        UTIL_ASSERT(pOldPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pOldPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
    // __LINE__: 9932
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);

    ResetPopupPanel(pPanel->m_nID, pSprite);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    EnablePopupPanel(pPanel->m_nID, TRUE);

    UpdatePopupPanel(pPanel->m_nID, pSprite);

    if (pOldPanel != NULL && pPanel->m_pManager->field_2E == 1) {
        if (pOldPanel->sub_4D2D20()) {
            m_cUIManager.GetPanel(0)->InvalidateRect(NULL);
        }
    }
}

// 0x617B70
void CScreenCreateChar::DismissPopup(CGameSprite* pSprite)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 10015
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCharacter.cpp
        // __LINE__: 10032
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        UpdatePopupPanel(pPanel->m_nID, pSprite);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel(pSprite);
    }

    if (g_pBaldurChitin->field_1A0) {
        // FIXME: Unused.
        g_pChitin->GetWnd();
        if (g_pBaldurChitin->cImm.field_128) {
            g_pBaldurChitin->cImm.sub_7C2E10(g_pChitin->GetWnd()->GetSafeHwnd());
        }
    }
}

// 0x617D60
void CScreenCreateChar::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// 0x617D80
void CScreenCreateChar::sub_617D80()
{
    // TODO: Incomplete.
}

// 0x619030
void CScreenCreateChar::UpdateClassEntry(CUIControlTextDisplay* pText, const CAIObjectType& typeAI, CDerivedStats* DStats, DWORD nSpecialization, BYTE nClass, DWORD dwFlags)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    CString sClass;
    ruleTables.GetClassStringMixed(nClass,
        nSpecialization,
        dwFlags,
        sClass,
        typeAI.m_nGender != CAIOBJECTTYPE_SEX_FEMALE);

    UpdateText(pText, "%s", FetchString(12136) + ": " + sClass);
}

// 0x623BF0
int CScreenCreateChar::GetRaceFeatColumn(BYTE nRace, BYTE nSubRace)
{
    switch (nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            return 0;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
            return 1;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            return 2;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 17883
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            return 3;
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            return 4;
        case CAIOBJECTTYPE_SUBRACE_ELF_WILD:
            return 5;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 17901
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ELF:
        return 14;
    case CAIOBJECTTYPE_R_DWARF:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            return 6;
        case CAIOBJECTTYPE_SUBRACE_DWARF_GOLD:
            return 7;
        case CAIOBJECTTYPE_SUBRACE_DWARF_GRAY:
            return 8;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 17919
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            return 9;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART:
            return 10;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE:
            return 11;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 17937
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        switch (nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            return 12;
        case CAIOBJECTTYPE_SUBRACE_GNOME_DEEP:
            return 13;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 17951
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        return 15;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17961
        UTIL_ASSERT(FALSE);
    }
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

    g_pBaldurChitin->GetTlkTable().Fetch(strText, strRes);
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
        switch (pCreateChar->m_nCurrentStep) {
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
            pCreateChar->UpdateCharacterAppearance();
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

// 0x614950
CUIControlButtonCharGen614950::CUIControlButtonCharGen614950(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(28210, strRes);
    SetText(strRes.szText);
}

// 0x614A40
CUIControlButtonCharGen614950::~CUIControlButtonCharGen614950()
{
}

// 0x614EF0
void CUIControlButtonCharGen614950::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x6154F0
CUIControlButtonCharGenImport::CUIControlButtonCharGenImport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13955, strRes);
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
    g_pBaldurChitin->GetTlkTable().Fetch(15416, strRes);
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
        if (pCreateChar->m_nCurrentStep > pCreateChar->m_nFirstStep) {
            pCreateChar->m_nCurrentStep--;
            if (pCreateChar->m_nCurrentStep < pCreateChar->m_nFirstStep) {
                pCreateChar->m_nCurrentStep = pCreateChar->m_nFirstStep;
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
    g_pBaldurChitin->GetTlkTable().Fetch(36789, strRes);
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
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

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
    g_pBaldurChitin->GetTlkTable().Fetch(17373, strRes);
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
    g_pBaldurChitin->GetTlkTable().Fetch(17374, strRes);
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
    g_pBaldurChitin->GetTlkTable().Fetch(11982, strRes);
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
    g_pBaldurChitin->GetTlkTable().Fetch(1379, strRes);
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

// 0x61A130
CUIControlButtonCharGen61A130::CUIControlButtonCharGen61A130(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11221
    UTIL_ASSERT(pCreateChar != NULL);

    SetText(CBaldurEngine::FetchString(27338)); // "Auto Pick"
}

// 0x61A200
CUIControlButtonCharGen61A130::~CUIControlButtonCharGen61A130()
{
}

// 0x61A2A0
void CUIControlButtonCharGen61A130::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11245
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->sub_617D80();
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
void CUIControlScrollBarCharGenSkills::OnPageUp(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11362
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, SKILL_SLOTS - 1);
    pCreateChar->m_nTopSkill = max(pCreateChar->m_nTopSkill - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x61A4E0
void CUIControlScrollBarCharGenSkills::OnPageDown(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11362
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, SKILL_SLOTS - 1);
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

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetSkillId(g_pBaldurChitin->m_pEngineCreateChar->m_nTopSkill + offset);
    STRREF strDescription = ruleTables.GetSkillDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
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
    case 33:
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

        const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

        DWORD id = ruleTables.GetSkillId(pCreateChar->m_nTopSkill + offset);
        INT nValue = pSprite->GetSkillValue(id);

        // FIXME: Looks wrong (obtaining id from id).
        INT nCost = pSprite->GetSkillCost(ruleTables.GetSkillId(id),
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
                pCreateChar->m_nExtraSkillPoints += pSprite->GetSkillCost(ruleTables.GetSkillId(id),
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

    g_pBaldurChitin->GetTlkTable().Fetch(strText, strRes);
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

// 0x61B120
CUIControlButtonCharGenKnownArcaneSpellSelection::CUIControlButtonCharGenKnownArcaneSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
    m_iconResRef = "";
    m_spellResRef = "";
}

// 0x61B1F0
CUIControlButtonCharGenKnownArcaneSpellSelection::~CUIControlButtonCharGenKnownArcaneSpellSelection()
{
}

// FIXME: `cResRef` should be reference.
//
// 0x61B290
void CUIControlButtonCharGenKnownArcaneSpellSelection::SetSpell(CResRef cResRef)
{
    CString sIconResRef;

    if (m_spellResRef != cResRef) {
        m_spellResRef = cResRef;
        m_iconResRef = "";

        if (m_spellResRef != "") {
            CSpell cSpell;
            cSpell.SetResRef(m_spellResRef, TRUE, TRUE);
            cSpell.Demand();

            if (cSpell.pRes != NULL) {
                RESREF iconResRef;
                cSpell.GetIcon(iconResRef);
                m_iconResRef = iconResRef;

                m_iconResRef.CopyToString(sIconResRef);
                sIconResRef.SetAt(sIconResRef.GetLength() - 1, 'B');
                m_iconResRef = sIconResRef;

                SetToolTipStrRef(cSpell.GetGenericName(), -1, -1);
            }

            cSpell.Release();
        } else {
            SetToolTipStrRef(-1, -1, -1);
        }
    }
}

// 0x61B460
void CUIControlButtonCharGenKnownArcaneSpellSelection::OnLButtonClick(CPoint pt)
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
        CDerivedStats& DStats = *pSprite->GetDerivedStats();
        CAIObjectType& typeAI = pSprite->m_startTypeAI;

        CSpell cSpell;
        cSpell.SetResRef(m_spellResRef, TRUE, TRUE);
        cSpell.Demand();
        cSpell.GetDescription(); // // NOTE: Unused.
        cSpell.Release();

        UINT nMaxKnownSpells = 0;
        INT nMaxKnownSpellsBonus = 0;

        if (typeAI.m_nClass == CAIOBJECTTYPE_C_BARD
            || typeAI.m_nClass == CAIOBJECTTYPE_C_SORCERER) {
            nMaxKnownSpells = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetMaxKnownSpells(typeAI.m_nClass,
                typeAI,
                DStats,
                pSprite->GetSpecialization(),
                1,
                nMaxKnownSpellsBonus);
            nMaxKnownSpells += nMaxKnownSpellsBonus;
        }

        if (m_bSelected) {
            SetSelected(FALSE);
            pCreateChar->m_nExtraSpells++;
            pSprite->RemoveKnownSpell(typeAI.m_nClass, 0, m_spellResRef, 1, 0, 0);
        } else {
            if (pCreateChar->m_nExtraSpells > 0
                && cSpell.pRes != NULL
                && cSpell.CheckUsableBy(pSprite) == TRUE) {
                SetSelected(TRUE);
                pCreateChar->m_nExtraSpells--;
                pSprite->AddKnownSpell(typeAI.m_nClass, 0, m_spellResRef, nMaxKnownSpells, 0, 0);
            }
        }

        pCreateChar->UpdateHelp(m_pPanel->m_nID, 27, cSpell.GetDescription());
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x61B750
BOOL CUIControlButtonCharGenKnownArcaneSpellSelection::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton3State::Render(bForce)) {
        return FALSE;
    }

    if (m_spellResRef != "" && m_iconResRef != "") {
        CRect rControlFrame(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

        if (m_bPressed) {
            rControlFrame.OffsetRect(field_63E, field_642);
        }

        CPoint pos = rControlFrame.TopLeft();

        CRect rClip;
        rClip.IntersectRect(rControlFrame, m_rDirty);

        CIcon::RenderIcon(0,
            pos,
            m_size,
            rClip,
            m_iconResRef,
            m_pPanel->m_pManager->m_bDoubleSize,
            m_bEnabled ? 0x1 : 0,
            0,
            FALSE,
            0,
            FALSE,
            0);
    }

    return TRUE;
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
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CString sClassName;
    // FIXME: Unused.
    STR_RES strRes;

    ruleTables.GetClassStringLower(GetClass(), 0x4000, 0, sClassName, 1);
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
        case 11:
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

    g_pBaldurChitin->GetTlkTable().Fetch(strText, strRes);
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

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61C650
BOOL CUIControlButtonCharGenPortrait::Render(BOOL bForce)
{
    CResRef silhouetteResRef;

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

    if (m_portraitResRef == "" || m_portraitResRef == "NONE") {
        return FALSE;
    }

    CVidBitmap vbPortrait;
    vbPortrait.SetResRef(m_portraitResRef, TRUE, FALSE);
    vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

    if (m_pPanel->m_nID == 18 && m_nID == 1) {
        silhouetteResRef = CInfGame::SILHOUETTE_PORTRAIT_SM;
    } else {
        silhouetteResRef = CInfGame::SILHOUETTE_PORTRAIT_LG;
    }

    if (vbPortrait.pRes == NULL) {
        vbPortrait.SetResRef(silhouetteResRef, TRUE, TRUE);
        vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
    }

    // FIXME: Calls `GetBitCount` two times.
    if (vbPortrait.GetBitCount(FALSE) != 24 && vbPortrait.GetBitCount(FALSE) != 8) {
        vbPortrait.SetResRef(silhouetteResRef, TRUE, TRUE);
        vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
    }

    if (vbPortrait.pRes == NULL) {
        return FALSE;
    }

    CRect rControlFrame(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

    CRect rClip;
    rClip.IntersectRect(rControlFrame, m_rDirty);

    BOOL bResult = vbPortrait.RenderDirect(0, rControlFrame.left, rControlFrame.top, rClip, 0, FALSE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13053
    UTIL_ASSERT(bResult);

    return TRUE;
}

// NOTE: Inlined.
void CUIControlButtonCharGenPortrait::SetPortrait(const CResRef& resRef)
{
    if (m_portraitResRef != resRef) {
        m_portraitResRef = resRef;
        InvalidateRect();
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
            return SPECMASK_WIZARD_ABJURER;
        case 3:
            return SPECMASK_WIZARD_CONJURER;
        case 4:
            return SPECMASK_WIZARD_DIVINER;
        case 5:
            return SPECMASK_WIZARD_ENCHANTER;
        case 6:
            return SPECMASK_WIZARD_ILLUSIONIST;
        case 7:
            return SPECMASK_WIZARD_EVOKER;
        case 8:
            return SPECMASK_WIZARD_NECROMANCER;
        case 9:
            return SPECMASK_WIZARD_TRANSMUTER;
        case 13:
            return SPECMASK_WIZARD_UNIVERSAL;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 13273
            UTIL_ASSERT(FALSE);
        }
        break;
    case CAIOBJECTTYPE_C_CLERIC:
        switch (m_nID) {
        case 2:
            return SPECMASK_CLERIC_LATHANDER;
        case 3:
            return SPECMASK_CLERIC_SELUNE;
        case 4:
            return SPECMASK_CLERIC_HELM;
        case 5:
            return SPECMASK_CLERIC_OGHMA;
        case 6:
            return SPECMASK_CLERIC_BANE;
        case 7:
            return SPECMASK_CLERIC_TEMPUS;
        case 8:
            return SPECMASK_CLERIC_MASK;
        case 9:
            return SPECMASK_CLERIC_TALOS;
        case 13:
            return SPECMASK_CLERIC_ILMATER;
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
            break;
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

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61D0E0
void CUIControlButtonCharGenAppearancePortrait::SetPortrait(const CResRef& resRef)
{
    if (m_portraitResRef != resRef) {
        m_portraitResRef = resRef;
        InvalidateRect();
    }
}

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61D120
BOOL CUIControlButtonCharGenAppearancePortrait::Render(BOOL bForce)
{
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

    if (m_portraitResRef == "" || m_portraitResRef == "NONE") {
        return FALSE;
    }

    CVidBitmap vbPortrait;
    vbPortrait.SetResRef(m_portraitResRef, TRUE, FALSE);
    vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

    if (vbPortrait.pRes == NULL) {
        vbPortrait.SetResRef(CInfGame::SILHOUETTE_PORTRAIT_LG, TRUE, TRUE);
        vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
    }

    // FIXME: Calls `GetBitCount` two times.
    if (vbPortrait.GetBitCount(FALSE) != 24 && vbPortrait.GetBitCount(FALSE) != 8) {
        vbPortrait.SetResRef(CInfGame::SILHOUETTE_PORTRAIT_LG, TRUE, TRUE);
        vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
    }

    if (vbPortrait.pRes == NULL) {
        return FALSE;
    }

    CSize size;
    vbPortrait.GetImageDimensions(size, FALSE);

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;
    if (size.cx < m_size.cx && size.cy < m_size.cy) {
        pt.x += (m_size.cx - size.cx) / 2;
        pt.y += (m_size.cy - size.cy) / 2;
    }

    CRect rControlFrame(pt, size);

    CRect rClip;
    rClip.IntersectRect(rControlFrame, m_rDirty);

    BOOL bResult = vbPortrait.RenderDirect(0, pt.x, pt.y, rClip, 0, FALSE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13582
    UTIL_ASSERT(bResult);

    return TRUE;
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61D3E0
void CUIControlButtonCharGenAppearanceLeft::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13613
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
        CString sPortrait;
        CResRef portraitResRef;

        pCreateChar->DecCurrentPortrait(pSprite);
        sPortrait = pCreateChar->GetCurrentPortrait(pSprite);

        portraitResRef = sPortrait + "S";
        portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitSmall);

        portraitResRef = sPortrait + "L";
        portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitLarge);

        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61D600
void CUIControlButtonCharGenAppearanceRight::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 13675
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
        CString sPortrait;
        CResRef portraitResRef;

        pCreateChar->IncCurrentPortrait(pSprite);
        sPortrait = pCreateChar->GetCurrentPortrait(pSprite);

        portraitResRef = sPortrait + "S";
        portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitSmall);

        portraitResRef = sPortrait + "L";
        portraitResRef.GetResRef(pSprite->m_baseStats.m_portraitLarge);

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
    g_pBaldurChitin->GetTlkTable().Fetch(17545, strRes);
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

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x61DAC0
BOOL CUIControlButtonCharGenHairSkinAppearance::Render(BOOL bForce)
{
    // 0x8F3B9C
    static DWORD nCounter;

    CVidCell vcAppearance;

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

    CPoint ptPos(m_pPanel->m_ptOrigin.x + m_ptOrigin.x + m_size.cx / 2,
        m_pPanel->m_ptOrigin.y + m_ptOrigin.y + m_size.cy / 2);
    CSize size(128 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1),
        160 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1));

    CRect rPreview(ptPos, size);

    CRect rClip;
    rClip.IntersectRect(rPreview, m_rDirty);

    // FIXME: Creates area on every render.
    CGameArea* pArea = new CGameArea(0);
    CInfinity* pInfinity = pArea->GetInfinity();
    pInfinity->pVidMode = g_pBaldurChitin->GetCurrentVideoMode();
    pInfinity->rViewPort.SetRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);

    if ((nCounter & 1) != 0) {
        pCreateChar->m_animation.m_animation->IncrementFrame();
        pCreateChar->m_animation.m_animation->GetCurrentFrame();
        if (pCreateChar->m_animation.m_animation->IsEndOfSequence()) {
            pCreateChar->m_animation.SetSequence(pSprite->GetIdleSequence());
        }
    }
    nCounter++;

    CRect rFx;
    CPoint ptReference;
    pCreateChar->m_animation.CalculateFxRect(rFx, ptReference, 0);

    ptPos.x += pInfinity->nCurrentX;
    ptPos.y += pInfinity->nCurrentY + 20;

    CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
    renderLock.Lock(INFINITE);

    pCreateChar->m_animation.Render(pInfinity,
        pInfinity->pVidMode,
        0,
        rFx,
        ptPos,
        ptReference,
        0x20000,
        RGB(255, 255, 255),
        rClip,
        FALSE,
        FALSE,
        0,
        0);

    renderLock.Unlock();

    delete pArea;

    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nGameSprite,
        CGameObjectArray::THREAD_1,
        INFINITE);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x61E080
CUIControlButtonCharGenHairSkinColor::CUIControlButtonCharGenHairSkinColor(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_pDecal = new CVidCell(CResRef("COLGRAD"), m_pPanel->m_pManager->m_bDoubleSize);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 14066
    UTIL_ASSERT(m_pDecal != NULL);

    m_pDecal->SequenceSet(0);
    m_pPalette = NULL;

    switch (m_nID) {
    case 2:
    case 3:
    case 4:
    case 5:
        SetToolTipStrRef(-1, -1, -1);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14092
        UTIL_ASSERT(FALSE);
    }
}

// 0x61E1E0
CUIControlButtonCharGenHairSkinColor::~CUIControlButtonCharGenHairSkinColor()
{
    if (m_pDecal != NULL) {
        delete m_pDecal;
        m_pDecal = NULL;
    }

    if (m_pPalette != NULL) {
        delete m_pPalette;
        m_pPalette = NULL;
    }
}

// 0x61E2D0
void CUIControlButtonCharGenHairSkinColor::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // NOTE: Not used.
    pCreateChar->GetManager();

    switch (m_nID) {
    case 2:
        pCreateChar->m_nRange = CVIDPALETTE_RANGE_HAIR;
        break;
    case 3:
        pCreateChar->m_nRange = CVIDPALETTE_RANGE_SKIN;
        break;
    case 4:
        pCreateChar->m_nRange = CVIDPALETTE_RANGE_MAIN_CLOTH;
        break;
    case 5:
        pCreateChar->m_nRange = CVIDPALETTE_RANGE_MINOR_CLOTH;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14172
        UTIL_ASSERT(FALSE);
    }

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nGameSprite = pCreateChar->GetSpriteId();

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pCreateChar->SummonPopup(14, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();
}

// 0x61E430
BOOL CUIControlButtonCharGenHairSkinColor::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_pPalette == NULL) {
        m_pPalette = new CVidPalette(CVidPalette::TYPE_RANGE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14247
        UTIL_ASSERT(m_pPalette != NULL);
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    if (m_bPressed) {
        m_pDecal->FrameSet(1);
    } else {
        m_pDecal->FrameSet(0);
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // NOTE: Uninline.
    LONG nCharacterId = g_pBaldurChitin->m_pEngineCreateChar->GetSpriteId();

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        BYTE colorRange;
        switch (m_nID) {
        case 2:
            colorRange = pSprite->m_baseStats.m_colors[6];
            break;
        case 3:
            colorRange = pSprite->m_baseStats.m_colors[3];
            break;
        case 4:
            colorRange = pSprite->m_baseStats.m_colors[2];
            break;
        case 5:
            colorRange = pSprite->m_baseStats.m_colors[1];
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 14304
            UTIL_ASSERT(FALSE);
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            INFINITE);

        CRect rControlRect;
        rControlRect.left = pt.x;
        rControlRect.top = pt.y;
        rControlRect.right = rControlRect.left + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        rControlRect.bottom = rControlRect.top + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        m_pPalette->SetRange(0,
            colorRange,
            *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());

        m_pDecal->SetPalette(*m_pPalette);

        BOOL bResult = m_pDecal->Render(0, pt.x, pt.y, rClip, NULL, 0, 0, 0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14315
        UTIL_ASSERT(bResult);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x61E720
CUIControlButtonCharGenColorChoice::CUIControlButtonCharGenColorChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    if (m_nID == 35) {
        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(33479, strRes);
        SetText(strRes.szText);

        m_pDecal = NULL;
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14349
        UTIL_ASSERT(m_nID <= CRESUI_CONTROLBUTTONID_CHARGEN_COLOR_LASTCOLOR);

        m_pDecal = new CVidCell(CResRef("COLGRAD"), m_pPanel->m_pManager->m_bDoubleSize);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14355
        UTIL_ASSERT(m_pDecal != NULL);

        m_pDecal->SequenceSet(0);
    }

    m_pPalette = NULL;
}

// 0x61E8D0
CUIControlButtonCharGenColorChoice::~CUIControlButtonCharGenColorChoice()
{
    if (m_pDecal != NULL) {
        delete m_pDecal;
        m_pDecal = NULL;
    }

    if (m_pPalette != NULL) {
        delete m_pPalette;
        m_pPalette = NULL;
    }
}

// 0x61E9C0
void CUIControlButtonCharGenColorChoice::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;
    BOOL v2 = FALSE;

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
        BYTE colorRange = pCreateChar->m_nRange;
        BYTE rangeValue;
        if (GetColorRange(rangeValue)) {
            pSprite->m_baseStats.m_colors[colorRange] = rangeValue;
            pSprite->m_animation.SetColorRange(colorRange, rangeValue);
            pCreateChar->DismissPopup(pSprite);
            v2 = TRUE;
        } else if (m_nID == 35) {
            CResRef portraitColorResRef("portcolr");
            C2DArray tPortraitColor;
            CString v1;
            CString sPortraitLarge;

            sPortraitLarge = pSprite->m_baseStats.m_portraitLarge;
            v1 = sPortraitLarge.Left(8);

            tPortraitColor.Load(portraitColorResRef);
            v2 = TRUE;

            BOOL bDemanded = tPortraitColor.Demand();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
            // __LINE__: 14472
            UTIL_ASSERT(bDemanded == TRUE);

            CPoint ptLocation;
            BOOLEAN bFound = tPortraitColor.Find(v1, ptLocation, TRUE);

            if (bFound) {
                switch (colorRange) {
                case CVIDPALETTE_RANGE_MINOR_CLOTH:
                    ptLocation.x = 3;
                    rangeValue = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
                    break;
                case CVIDPALETTE_RANGE_MAIN_CLOTH:
                    ptLocation.x = 2;
                    rangeValue = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
                    break;
                case CVIDPALETTE_RANGE_SKIN:
                    ptLocation.x = 0;
                    rangeValue = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
                    break;
                case CVIDPALETTE_RANGE_HAIR:
                    ptLocation.x = 1;
                    rangeValue = static_cast<BYTE>(tPortraitColor.GetAtLong(ptLocation));
                    break;
                }
            } else {
                switch (colorRange) {
                case CVIDPALETTE_RANGE_MINOR_CLOTH:
                    rangeValue = CVIDPALETTE_CLOTH_DK_BROWN_1;
                    break;
                case CVIDPALETTE_RANGE_MAIN_CLOTH:
                    rangeValue = CVIDPALETTE_CLOTH_DK_BROWN_2;
                    break;
                case CVIDPALETTE_RANGE_SKIN:
                    rangeValue = CVIDPALETTE_SKIN_PINK;
                    break;
                case CVIDPALETTE_RANGE_HAIR:
                    rangeValue = CVIDPALETTE_HAIR_BLACK;
                    break;
                }
            }

            tPortraitColor.Release();

            pSprite->m_baseStats.m_colors[colorRange] = rangeValue;
            pSprite->m_animation.SetColorRange(colorRange, rangeValue);
            pCreateChar->DismissPopup(pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    renderLock.Unlock();

    if (v2 == TRUE) {
        pCreateChar->UpdateCharacterAppearance();
    }
}

// 0x61EE60
BOOL CUIControlButtonCharGenColorChoice::Render(BOOL bForce)
{
    if (m_nID == 35) {
        return CUIControlButton::Render(bForce);
    }

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_pPalette == NULL) {
        m_pPalette = new CVidPalette(CVidPalette::TYPE_RANGE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14590
        UTIL_ASSERT(m_pPalette != NULL);
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    if (m_bPressed) {
        m_pDecal->FrameSet(3);
    } else {
        m_pDecal->FrameSet(2);
    }

    BYTE colorRange;
    if (GetColorRange(colorRange)) {
        CRect rControlRect;
        rControlRect.left = pt.x;
        rControlRect.top = pt.y;
        rControlRect.right = rControlRect.left + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        rControlRect.bottom = rControlRect.top + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        m_pPalette->SetRange(0,
            colorRange,
            *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());

        m_pDecal->SetPalette(*m_pPalette);

        BOOL bResult = m_pDecal->Render(0, pt.x, pt.y, rClip, NULL, 0, 0, 0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14620
        UTIL_ASSERT(bResult);
    }

    return TRUE;
}

// 0x61F0C0
BOOL CUIControlButtonCharGenColorChoice::GetColorRange(BYTE& colorRange)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 14792
    UTIL_ASSERT(pCreateChar != NULL);

    // NOTE: Signed comparisons below.
    INT v1 = m_nID;
    switch (pCreateChar->m_nRange) {
    case CVIDPALETTE_RANGE_MINOR_CLOTH:
    case CVIDPALETTE_RANGE_MAIN_CLOTH:
        if (v1 < 31) {
            colorRange = v1 + 36;
            return TRUE;
        }

        if (v1 < 34) {
            colorRange = v1 - 10;
            return TRUE;
        }

        break;
    case CVIDPALETTE_RANGE_SKIN:
        if (v1 < pCreateChar->m_tSkinColor.GetHeight()) {
            colorRange = atoi(pCreateChar->m_tSkinColor.GetAt(CPoint(0, v1)));
            return TRUE;
        }

        break;
    case CVIDPALETTE_RANGE_HAIR:
        if (v1 < pCreateChar->m_tHairColor.GetHeight()) {
            colorRange = atoi(pCreateChar->m_tHairColor.GetAt(CPoint(0, v1)));
            return TRUE;
        }

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 14837
        UTIL_ASSERT(FALSE);
    }

    return FALSE;
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
        strDescription = 9582;
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
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MINIMUM, sValue);

    sValue.Format("%d", nMax);
    g_pBaldurChitin->GetTlkTable().SetToken(CScreenCreateChar::TOKEN_MAXIMUM, sValue);

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

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetSkillId(offset + g_pBaldurChitin->m_pEngineCreateChar->m_nTopSkill);
    STRREF strDescription = ruleTables.GetSkillDescription(id);
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
    g_pBaldurChitin->GetTlkTable().Fetch(15416, strRes); // "Back"
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

    AdjustScrollBar(pCreateChar->m_nTopHatedRace, CSCREENCREATECHAR_NUM_HATEDRACES, 11);
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
void CUIControlScrollBarCharGenHatedRace::OnPageUp(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15296
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, 11);
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
void CUIControlScrollBarCharGenHatedRace::OnPageDown(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 15334
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, 11);
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
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
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

// 0x620220
CUIControlButtonCharGenMemorizedArcaneSpellSelection::CUIControlButtonCharGenMemorizedArcaneSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
    m_iconResRef = "";
    m_spellResRef = "";
}

// 0x6202F0
CUIControlButtonCharGenMemorizedArcaneSpellSelection::~CUIControlButtonCharGenMemorizedArcaneSpellSelection()
{
}

// FIXME: `cResRef` should be reference.
//
// 0x620390
void CUIControlButtonCharGenMemorizedArcaneSpellSelection::SetSpell(CResRef cResRef)
{
    CString sIconResRef;

    if (m_spellResRef != cResRef) {
        m_spellResRef = cResRef;
        m_iconResRef = "";

        if (m_spellResRef != "") {
            CSpell cSpell;
            cSpell.SetResRef(m_spellResRef, TRUE, TRUE);
            cSpell.Demand();

            if (cSpell.pRes != NULL) {
                RESREF iconResRef;
                cSpell.GetIcon(iconResRef);
                m_iconResRef = iconResRef;

                m_iconResRef.CopyToString(sIconResRef);
                sIconResRef.SetAt(sIconResRef.GetLength() - 1, 'B');
                m_iconResRef = sIconResRef;

                SetToolTipStrRef(cSpell.GetGenericName(), -1, -1);
            }

            cSpell.Release();
        } else {
            SetToolTipStrRef(-1, -1, -1);
        }
    }
}

// 0x620560
void CUIControlButtonCharGenMemorizedArcaneSpellSelection::OnLButtonClick(CPoint pt)
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
        CDerivedStats& DStats = *pSprite->GetDerivedStats();
        CAIObjectType& typeAI = pSprite->m_startTypeAI;

        CSpell cSpell;
        cSpell.SetResRef(m_spellResRef, TRUE, TRUE);
        cSpell.Demand();

        STRREF strDescription = cSpell.GetDescription();

        cSpell.Release();

        CGameSpriteSpellList* pList = pSprite->GetSpellsAtLevel(typeAI.m_nClass, 0);
        UINT nButtonIndex = m_nID - 2;

        if (nButtonIndex < pList->m_List.size()) {
            UINT nID = pList->Get(nButtonIndex)->m_nID;

            // NOTE: Original code is an unreadable mess consisting mostly of
            // inlined functions.
            //
            // TODO: The code looks unsafe as checking for resref is the only
            // way to stop this loop.
            while (m_spellResRef != g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID)) {
                nButtonIndex++;
                nID = pList->Get(nButtonIndex)->m_nID;
            }

            if (m_bSelected) {
                pSprite->GetSpells(typeAI.m_nClass)->Remove(nID, 0, 0, 1, 0);
                pCreateChar->m_nExtraSpells++;
                SetSelected(FALSE);
            } else {
                if (pCreateChar->m_nExtraSpells > 0
                    && cSpell.pRes != NULL
                    && cSpell.CheckUsableBy(pSprite) == TRUE) {
                    pSprite->GetSpells(typeAI.m_nClass)->Add(nID, 0, 1, 0, 0);
                    pCreateChar->m_nExtraSpells--;
                    SetSelected(TRUE);
                }
            }

            pCreateChar->UpdateHelp(m_pPanel->m_nID, 27, strDescription);
            pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x620970
BOOL CUIControlButtonCharGenMemorizedArcaneSpellSelection::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton3State::Render(bForce)) {
        return FALSE;
    }

    if (m_spellResRef != "" && m_iconResRef != "") {
        CRect rControlFrame(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

        if (m_bPressed) {
            rControlFrame.OffsetRect(field_63E, field_642);
        }

        CPoint pos = rControlFrame.TopLeft();

        CRect rClip;
        rClip.IntersectRect(rControlFrame, m_rDirty);

        CIcon::RenderIcon(0,
            pos,
            m_size,
            rClip,
            m_iconResRef,
            m_pPanel->m_pManager->m_bDoubleSize,
            m_bEnabled ? 0x1 : 0,
            0,
            FALSE,
            0,
            FALSE,
            0);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x620AE0
CUIControlButtonCharGenMemorizedDivineSpellSelection::CUIControlButtonCharGenMemorizedDivineSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 1)
{
    m_nSelectedFrame = 0;
    m_iconResRef = "";
    m_spellResRef = "";
}

// 0x620BB0
CUIControlButtonCharGenMemorizedDivineSpellSelection::~CUIControlButtonCharGenMemorizedDivineSpellSelection()
{
}

// FIXME: `cResRef` should be reference.
//
// 0x620C50
void CUIControlButtonCharGenMemorizedDivineSpellSelection::SetSpell(CResRef cResRef)
{
    CString sIconResRef;

    if (m_spellResRef != cResRef) {
        m_spellResRef = cResRef;
        m_iconResRef = "";

        if (m_spellResRef != "") {
            CSpell cSpell;
            cSpell.SetResRef(m_spellResRef, TRUE, TRUE);
            cSpell.Demand();

            if (cSpell.pRes != NULL) {
                RESREF iconResRef;
                cSpell.GetIcon(iconResRef);
                m_iconResRef = iconResRef;

                m_iconResRef.CopyToString(sIconResRef);
                sIconResRef.SetAt(sIconResRef.GetLength() - 1, 'B');
                m_iconResRef = sIconResRef;

                SetToolTipStrRef(cSpell.GetGenericName(), -1, -1);
            }

            cSpell.Release();
        } else {
            SetToolTipStrRef(-1, -1, -1);
        }
    }
}

// 0x620E10
void CUIControlButtonCharGenMemorizedDivineSpellSelection::OnLButtonClick(CPoint pt)
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
        BOOLEAN bPickingDomainSpells = pCreateChar->m_bPickingDomainSpells;
        UINT nButtonIndex = m_nID - 2;
        STRREF strDescription;
        CResRef resRef;
        CAIObjectType& typeAI = pSprite->m_startTypeAI;

        // FIXME: This is a **copy**. Obviously this should be a pointer or
        // reference, since there is no need for a copy. I bet they simply
        // forgot to add a star.
        CGameSpriteSpellList spells = bPickingDomainSpells
            ? pSprite->m_domainSpells.m_lists[0]
            : *pSprite->GetSpellsAtLevel(pSprite->GetAIType().m_nClass, 0);

        if (nButtonIndex < spells.m_List.size()) {
            // NOTE: Uninline.
            UINT nID = spells.Get(nButtonIndex)->m_nID;

            // NOTE: Uninline.
            resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get(nID);

            if (resRef != "") {
                CSpell cSpell;
                cSpell.SetResRef(resRef, TRUE, TRUE);
                cSpell.Demand();
                strDescription = cSpell.GetDescription();
                cSpell.Release();
            }

            if (m_bSelected) {
                if (bPickingDomainSpells) {
                    pSprite->RemoveDomainSpell(0, resRef, 0, 1, 0);
                } else {
                    pSprite->GetSpells(typeAI.m_nClass)->Remove(nID, 0, 0, 1, 0);
                }
                pCreateChar->m_nExtraSpells++;
                SetSelected(FALSE);
            } else {
                if (pCreateChar->m_nExtraSpells > 0) {
                    if (bPickingDomainSpells) {
                        pSprite->AddDomainSpell(0, resRef, 1, 0, 0);
                    } else {
                        pSprite->GetSpells(typeAI.m_nClass)->Add(nID, 0, 1, 0, 0);
                    }
                    pCreateChar->m_nExtraSpells--;
                    SetSelected(TRUE);
                }
            }

            pCreateChar->UpdateHelp(m_pPanel->m_nID, 27, strDescription);
            pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x6212D0
BOOL CUIControlButtonCharGenMemorizedDivineSpellSelection::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton3State::Render(bForce)) {
        return FALSE;
    }

    if (m_spellResRef != "" && m_iconResRef != "") {
        CRect rControlFrame(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

        if (m_bPressed) {
            rControlFrame.OffsetRect(field_63E, field_642);
        }

        CPoint pos = rControlFrame.TopLeft();

        CRect rClip;
        rClip.IntersectRect(rControlFrame, m_rDirty);

        CIcon::RenderIcon(0,
            pos,
            m_size,
            rClip,
            m_iconResRef,
            m_pPanel->m_pManager->m_bDoubleSize,
            m_bEnabled ? 0x1 : 0,
            0,
            FALSE,
            0,
            FALSE,
            0);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x621440
CUIControlTextDisplayCharGenPortraits::CUIControlTextDisplayCharGenPortraits(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603670
CUIControlTextDisplayCharGenPortraits::~CUIControlTextDisplayCharGenPortraits()
{
}

// 0x621480
void CUIControlTextDisplayCharGenPortraits::OnItemSelected(LONG lMarker)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16204
    UTIL_ASSERT(pCreateChar != NULL);

    switch (m_nID) {
    case 2:
        pCreateChar->OnPortraitLargeItemSelect(lMarker);
        break;
    case 4:
        pCreateChar->OnPortraitSmallItemSelect(lMarker);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 16217
        UTIL_ASSERT(FALSE);
    }
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

// 0x621570
CUIControlButtonCharGenSoundPlay::CUIControlButtonCharGenSoundPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16300
    UTIL_ASSERT(pCreateChar != NULL);

    SetText(CBaldurEngine::FetchString(17318));
}

// 0x621640
CUIControlButtonCharGenSoundPlay::~CUIControlButtonCharGenSoundPlay()
{
}

// 0x6216E0
void CUIControlButtonCharGenSoundPlay::OnLButtonClick(CPoint pt)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16327
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->OnPlayButtonClick();
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

// 0x621790
CUIControlTextDisplayCharGenExportCharacters::CUIControlTextDisplayCharGenExportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603670
CUIControlTextDisplayCharGenExportCharacters::~CUIControlTextDisplayCharGenExportCharacters()
{
}

// 0x6217C0
void CUIControlTextDisplayCharGenExportCharacters::OnItemSelected(LONG lMarker)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 16435
    UTIL_ASSERT(pCreateChar != NULL);

    pCreateChar->OnCharacterExportItemSelect(lMarker);
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
    CString sClass = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetClassString(typeAI.m_nClass,
        pSprite->m_baseStats.m_specialization);

    DWORD str = atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tKitList.GetAt(CString("HELP"), sClass));
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
    INT nSubRaceId = atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tSrList.GetAt(CPoint(4, nSubRaceListIndex)));

    STRREF strHelp;
    if (pCreateChar->m_tSubRace.GetResRef() != "" && nSubRaceId != 0) {
        strHelp = atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tSrList.GetAt(CPoint(3, nSubRaceListIndex)));
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

        INT nRow = 0;
        switch (m_nID) {
        case 1:
            nRow = 0;
            break;
        case 2:
            nRow = 1;
            break;
        case 3:
            nRow = 2;
            break;
        case 4:
            nRow = 3;
            break;
        }

        INT nSubRaceListIndex = atol(pCreateChar->m_tSubRace.GetAt(CPoint(0, nRow)));
        typeAI.m_nSubRace = static_cast<BYTE>(atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tSrList.GetAt(CPoint(4, nSubRaceListIndex))));

        pSprite->m_startTypeAI.Set(typeAI);
        pCreateChar->UpdateHelp(m_pPanel->m_nID, 6, GetHelp(typeAI));
        pCreateChar->UpdatePopupPanel(m_pPanel->m_nID, pSprite);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nGameSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
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

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetFeatId(offset + g_pBaldurChitin->m_pEngineCreateChar->m_nTopFeat);
    STRREF strDescription = ruleTables.GetFeatDescription(id);
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
void CUIControlScrollBarCharGenFeats::OnPageUp(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17197
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, FEAT_SLOTS - 1);
    pCreateChar->m_nTopFeat = max(pCreateChar->m_nTopFeat - nStep, 0);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x622DE0
void CUIControlScrollBarCharGenFeats::OnPageDown(DWORD nLines)
{
    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 17225
    UTIL_ASSERT(pCreateChar != NULL);

    INT nStep = min(nLines, FEAT_SLOTS - 1);
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
    // __LINE__: 17253
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
    // __LINE__: 17284
    UTIL_ASSERT(pCreateChar != NULL);

    CSingleLock renderLock(&(pCreateChar->GetManager()->field_36), FALSE);
    renderLock.Lock();

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

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    DWORD id = ruleTables.GetFeatId(g_pBaldurChitin->m_pEngineCreateChar->m_nTopFeat + offset);
    STRREF strDescription = ruleTables.GetFeatDescription(id);
    g_pBaldurChitin->m_pEngineCreateChar->UpdateHelp(m_pPanel->m_nID, 92, strDescription);

    return CUIControlButtonPlusMinus::OnLButtonDown(pt);
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
        DWORD id = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetFeatId(pCreateChar->m_nTopFeat + offset);
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

                const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

                for (INT nFeat = 0; nFeat < ruleTables.m_tFeats.GetHeight(); nFeat++) {
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

// -----------------------------------------------------------------------------

// 0x6235C0
CUIControlButtonCharGenFeatsCircle::CUIControlButtonCharGenFeatsCircle(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x623610
CUIControlButtonCharGenFeatsCircle::~CUIControlButtonCharGenFeatsCircle()
{
}

// 0x6236B0
BOOL CUIControlButtonCharGenFeatsCircle::Render(BOOL bForce)
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
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
        nFirstID = 81;
        nIndex = 9;
        break;
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
        nFirstID = 86;
        nIndex = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17806
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

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
        // __LINE__: 17848
        UTIL_ASSERT(bResult);
    }

    pCreateChar->UpdatePopupPanel(pCreateChar->GetTopPopup()->m_nID, pSprite);

    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nGameSprite,
        CGameObjectArray::THREAD_1,
        INFINITE);

    return TRUE;
}

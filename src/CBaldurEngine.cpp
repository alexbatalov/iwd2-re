#include "CBaldurEngine.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenMap.h"
#include "CScreenMultiPlayer.h"
#include "CScreenOptions.h"
#include "CScreenSinglePlayer.h"
#include "CScreenSpellbook.h"
#include "CScreenWorld.h"
#include "CUIControlBase.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// NOTE: The following constants are ordered according to addresses of its
// dynamic initializers in range 0x426F30 - 0x4277B0.

// 0x8C8CD8
const CResRef CBaldurEngine::RESREF_SOUND_CLICKLEFT("GAM_09");

// 0x8CF6A8
const CResRef CBaldurEngine::RESREF_SOUND_CLICKRIGHT("GAM_10");

// 0x8CF670
const CResRef CBaldurEngine::RESREF_SOUND_WINDOWOPEN("GAM_03");

// 0x8CD330
const CResRef CBaldurEngine::RESREF_SOUND_WINDOWCLOSE("GAM_04");

// 0x8CB1F0
const CResRef CBaldurEngine::RESREF_SOUND_MAGEBOOK("GAM_05");

// 0x8CD320
const CResRef CBaldurEngine::RESREF_SOUND_PRIESTSCROLL("GAM_06");

// 0x8CAD70
const CResRef CBaldurEngine::RESREF_SOUND_POTION("GAM_07");

// 0x8CF470
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_TAKE_GENERIC("GAM_21A");

// 0x8CF468
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_DROP_GENERIC("GAM_21B");

// 0x8C8C78
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_TAKE_LEATHER("GAM_12A");

// 0x8CD400
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_DROP_LEATHER("GAM_12A1");

// 0x8C8CB0
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_TAKE_METAL("GAM_12B");

// 0x8CB228
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_DROP_METAL("GAM_12B1");

// 0x8CB1E8
const CResRef CBaldurEngine::RESREF_SOUND_SMMTL1("G_SmMtl1");

// 0x8CAD90
const CResRef CBaldurEngine::RESREF_SOUND_SMMTL2("G_SmMtl2");

// 0x8CF658
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_TAKE_WOOD("GAM_12D");

// 0x8CD2A0
const CResRef CBaldurEngine::RESREF_SOUND_EQUIP_DROP_WOOD("GAM_12D1");

// 0x8CAD88
const CResRef CBaldurEngine::RESREF_SOUND_BOOK1("G_Book1");

// 0x8CB1D8
const CResRef CBaldurEngine::RESREF_SOUND_BOOK2("G_Book2");

// 0x8CD280
const CResRef CBaldurEngine::RESREF_SOUND_NECK1("G_Neck1");

// 0x8CF650
const CResRef CBaldurEngine::RESREF_SOUND_NECK2("G_Neck2");

// 0x8CD3C0
const CResRef CBaldurEngine::RESREF_SOUND_LETHR1("G_Lethr1");

// 0x8CD380
const CResRef CBaldurEngine::RESREF_SOUND_LETHR2("G_Lethr2");

// 0x8CD270
const CResRef CBaldurEngine::RESREF_SOUND_CHAIN1("G_Chain1");

// 0x8CD2C0
const CResRef CBaldurEngine::RESREF_SOUND_CHAIN2("G_Chain2");

// 0x8CF638
const CResRef CBaldurEngine::RESREF_SOUND_PLATE1("G_Plate1");

// 0x8CD300
const CResRef CBaldurEngine::RESREF_SOUND_PLATE2("G_Plate2");

// 0x8CF6D0
const CResRef CBaldurEngine::RESREF_SOUND_BELT1("G_Belt1");

// 0x8CB250
const CResRef CBaldurEngine::RESREF_SOUND_BELT2("G_Belt2");

// 0x8CF6C8
const CResRef CBaldurEngine::RESREF_SOUND_GLOVE1("G_Glove1");

// 0x8CD460
const CResRef CBaldurEngine::RESREF_SOUND_GLOVE2("G_Glove2");

// 0x8CD3A8
const CResRef CBaldurEngine::RESREF_SOUND_BOOT1("G_Boot1");

// NOTE: Probably error, should it be `G_Boot2`?
//
// 0x8CD2E0
const CResRef CBaldurEngine::RESREF_SOUND_BOOT2("G_Boot1");

// 0x8CD388
const CResRef CBaldurEngine::RESREF_SOUND_ARRW1("G_Arrw1");

// 0x8CB1C8
const CResRef CBaldurEngine::RESREF_SOUND_ARRW2("G_Arrw2");

// 0x8CAD68
const CResRef CBaldurEngine::RESREF_SOUND_HELM1("G_Helm1");

// 0x8CD420
const CResRef CBaldurEngine::RESREF_SOUND_HELM2("G_Helm2");

// 0x8CD410
const CResRef CBaldurEngine::RESREF_SOUND_KEY1("G_Key1");

// 0x8CD3D8
const CResRef CBaldurEngine::RESREF_SOUND_KEY2("G_Key2");

// 0x8CAD58
const CResRef CBaldurEngine::RESREF_SOUND_POTN1("G_Potn1");

// 0x8CD3B8
const CResRef CBaldurEngine::RESREF_SOUND_POTN2("G_Potn2");

// 0x8CF610
const CResRef CBaldurEngine::RESREF_SOUND_SCROL1("G_Scrol1");

// 0x8CD3F0
const CResRef CBaldurEngine::RESREF_SOUND_SCROL2("G_Scrol2");

// 0x8CF630
const CResRef CBaldurEngine::RESREF_SOUND_BULLT1("G_Bullt1");

// 0x8CB1B8
const CResRef CBaldurEngine::RESREF_SOUND_BULLT2("G_Bullt2");

// 0x8CD348
const CResRef CBaldurEngine::RESREF_SOUND_BOW1("G_Bow1");

// 0x8CF6B8
const CResRef CBaldurEngine::RESREF_SOUND_BOW2("G_Bow2");

// 0x8CD318
const CResRef CBaldurEngine::RESREF_SOUND_DAGGR1("G_Daggr1");

// 0x8CD3B0
const CResRef CBaldurEngine::RESREF_SOUND_DAGGR2("G_Daggr2");

// 0x8CD278
const CResRef CBaldurEngine::RESREF_SOUND_MACE1("G_Mace1");

// 0x8CD3C8
const CResRef CBaldurEngine::RESREF_SOUND_MACE2("G_Mace2");

// 0x8CD2B0
const CResRef CBaldurEngine::RESREF_SOUND_SLING1("G_Sling1");

// 0x8CD378
const CResRef CBaldurEngine::RESREF_SOUND_SLING2("G_Sling2");

// 0x8CF678
const CResRef CBaldurEngine::RESREF_SOUND_HALB1("G_HalB1");

// 0x8CD310
const CResRef CBaldurEngine::RESREF_SOUND_HALB2("G_HalB2");

// 0x8CD2D0
const CResRef CBaldurEngine::RESREF_SOUND_HAMMR1("G_Hammr1");

// 0x8C8D08
const CResRef CBaldurEngine::RESREF_SOUND_HAMMR2("G_Hammr2");

// 0x8CD298
const CResRef CBaldurEngine::RESREF_SOUND_AXE1("G_Axe1");

// 0x8CD448
const CResRef CBaldurEngine::RESREF_SOUND_AXE2("G_Axe2");

// 0x8CF6C0
const CResRef CBaldurEngine::RESREF_SOUND_FLAIL1("G_Flail1");

// 0x8CB218
const CResRef CBaldurEngine::RESREF_SOUND_FLAIL2("G_Flail2");

// 0x8C8D18
const CResRef CBaldurEngine::RESREF_SOUND_CLOAK1("G_Cloak1");

// 0x8CF660
const CResRef CBaldurEngine::RESREF_SOUND_CLOAK2("G_Cloak2");

// 0x8CD360
const CResRef CBaldurEngine::RESREF_SOUND_GOLD1("G_Gold1");

// 0x8CD2E0
const CResRef CBaldurEngine::RESREF_SOUND_GOLD2("G_Gold2");

// 0x8C8D30
const CResRef CBaldurEngine::RESREF_SOUND_GEM1("G_Gem1");

// 0x8C8D20
const CResRef CBaldurEngine::RESREF_SOUND_GEM2("G_Gem2");

// 0x8CD258
const CResRef CBaldurEngine::RESREF_SOUND_SPEAR1("G_Spear1");

// 0x8CF6B0
const CResRef CBaldurEngine::RESREF_SOUND_SPEAR2("G_Spear2");

// 0x8CD328
const CResRef CBaldurEngine::RESREF_SOUND_STAFF1("G_Staff1");

// 0x8CB240
const CResRef CBaldurEngine::RESREF_SOUND_STAFF2("G_Staff2");

// 0x8CD428
const CResRef CBaldurEngine::RESREF_SOUND_WAND1("G_Wand1");

// 0x8CB208
const CResRef CBaldurEngine::RESREF_SOUND_WAND2("G_Wand2");

// 0x8C8CC0
const CResRef CBaldurEngine::RESREF_SOUND_CROSB1("G_CrosB1");

// 0x8C8D38
const CResRef CBaldurEngine::RESREF_SOUND_CROSB2("G_CrosB2");

// 0x8CF608
const CResRef CBaldurEngine::RESREF_SOUND_MSTAR1("G_MStar1");

// 0x8CB1E0
const CResRef CBaldurEngine::RESREF_SOUND_MSTAR2("G_MStar2");

// 0x8C8C90
const CResRef CBaldurEngine::RESREF_SOUND_SMSWD1("G_SmSwd1");

// 0x8C8CD0
const CResRef CBaldurEngine::RESREF_SOUND_SMSWD2("G_SmSwd2");

// 0x8CD2F0
const CResRef CBaldurEngine::RESREF_SOUND_LGSWD1("G_LgSwd1");

// 0x8CD3A0
const CResRef CBaldurEngine::RESREF_SOUND_LGSWD2("G_LgSwd2");

// 0x8CF618
const CResRef CBaldurEngine::RESREF_SOUND_RING1("G_Ring1");

// 0x8C8CF8
const CResRef CBaldurEngine::RESREF_SOUND_RING2("G_Ring2");

// 0x8CF620
const CResRef CBaldurEngine::RESREF_SOUND_BARM1("G_B_Arm1");

// 0x8CD288
const CResRef CBaldurEngine::RESREF_SOUND_BARM2("G_B_Arm2");

// 0x8CAD50
const CResRef CBaldurEngine::RESREF_SOUND_BSHD1("G_B_Shd1");

// 0x8CD350
const CResRef CBaldurEngine::RESREF_SOUND_BSHD2("G_B_Shd2");

// 0x8CF648
const CResRef CBaldurEngine::RESREF_SOUND_BWPN1("G_B_Wpn1");

// 0x8CD458
const CResRef CBaldurEngine::RESREF_SOUND_BWPN2("G_B_Wpn2");

// 0x8CAD78
const CResRef CBaldurEngine::RESREF_SOUND_BOLT1("G_Bolt1");

// 0x8C8D10
const CResRef CBaldurEngine::RESREF_SOUND_BOLT2("G_Bolt2");

// 0x8C8D28
const CResRef CBaldurEngine::RESREF_SOUND_BROKN1("G_Brokn1");

// 0x8CD3E0
const CResRef CBaldurEngine::RESREF_SOUND_BROKN2("G_Brokn2");

// 0x8CD368
const CResRef CBaldurEngine::RESREF_SOUND_BUCKR1("G_Buckr1");

// 0x8CB1F8
const CResRef CBaldurEngine::RESREF_SOUND_BUCKR2("G_Buckr2");

// 0x8C8CB8
const CResRef CBaldurEngine::RESREF_SOUND_CAND1("G_Cand1");

// 0x8CB1A0
const CResRef CBaldurEngine::RESREF_SOUND_CAND2("G_Cand2");

// 0x8CF688
const CResRef CBaldurEngine::RESREF_SOUND_CHILD1("G_Child1");

// 0x8C8CE0
const CResRef CBaldurEngine::RESREF_SOUND_CHILD2("G_Child2");

// 0x8CD3F8
const CResRef CBaldurEngine::RESREF_SOUND_CLUB1("G_Club1");

// 0x8CAD60
const CResRef CBaldurEngine::RESREF_SOUND_CLUB2("G_Club2");

// 0x8CD418
const CResRef CBaldurEngine::RESREF_SOUND_DART1("G_Dart1");

// 0x8CF6A0
const CResRef CBaldurEngine::RESREF_SOUND_DART2("G_Dart2");

// 0x8CD338
const CResRef CBaldurEngine::RESREF_SOUND_FEM1("G_Fem1");

// 0x8CAD48
const CResRef CBaldurEngine::RESREF_SOUND_FEM2("G_Fem2");

// 0x8CAD80
const CResRef CBaldurEngine::RESREF_SOUND_KEYS1("G_Keys1");

// 0x8CB1C0
const CResRef CBaldurEngine::RESREF_SOUND_KEYS2("G_Keys2");

// 0x8C8D00
const CResRef CBaldurEngine::RESREF_SOUND_LGSLD1("G_LgSld1");

// 0x8CD370
const CResRef CBaldurEngine::RESREF_SOUND_LGSLD2("G_LgSld2");

// 0x8CD2F8
const CResRef CBaldurEngine::RESREF_SOUND_MALE1("G_Male1");

// 0x8CD2C8
const CResRef CBaldurEngine::RESREF_SOUND_MALE2("G_Male2");

// 0x8CB230
const CResRef CBaldurEngine::RESREF_SOUND_MDSLD1("G_MdSld1");

// 0x8CD3D0
const CResRef CBaldurEngine::RESREF_SOUND_MDSLD2("G_MdSld2");

// 0x8C8C88
const CResRef CBaldurEngine::RESREF_SOUND_PAPR1("G_Papr1");

// 0x8CF690
const CResRef CBaldurEngine::RESREF_SOUND_PAPR2("G_Papr2");

// 0x8CD450
const CResRef CBaldurEngine::RESREF_SOUND_ROD1("G_Rod1");

// 0x8CD430
const CResRef CBaldurEngine::RESREF_SOUND_ROD2("G_Rod2");

// 0x8CF668
const CResRef CBaldurEngine::RESREF_SOUND_SKULL1("G_Skull1");

// 0x8CD2A8
const CResRef CBaldurEngine::RESREF_SOUND_SKULL2("G_Skull2");

// 0x8C8C98
const CResRef CBaldurEngine::RESREF_SOUND_SMSLD1("G_SmSld1");

// 0x8C8CE8
const CResRef CBaldurEngine::RESREF_SOUND_SMSLD2("G_SmSld2");

// 0x8CF640
const CResRef CBaldurEngine::RESREF_SOUND_SPIDR1("G_Spidr1");

// 0x8CD2E8
const CResRef CBaldurEngine::RESREF_SOUND_SPIDR2("G_Spidr2");

// 0x8C8CA8
const CResRef CBaldurEngine::RESREF_SOUND_TELE1("G_Tele1");

// 0x8CD408
const CResRef CBaldurEngine::RESREF_SOUND_TELE2("G_Tele2");

// 0x8CD290
const CResRef CBaldurEngine::RESREF_SOUND_WINE1("G_Wine1");

// 0x8CD2B8
const CResRef CBaldurEngine::RESREF_SOUND_WINE2("G_Wine2");

// 0x8CF680
const CResRef CBaldurEngine::RESREF_SOUND_8CF680("G_Lethr1");

// 0x8CB1D0
const CResRef CBaldurEngine::RESREF_SOUND_8CB1D0("G_Lethr2");

// 0x8CB1B0
const CResRef CBaldurEngine::RESREF_SOUND_8CB1B0("G_Cand1");

// 0x8CD390
const CResRef CBaldurEngine::RESREF_SOUND_8CD390("G_Cand2");

// 0x8CF628
const CResRef CBaldurEngine::RESREF_SOUND_8CF628("G_Sling1");

// 0x8CD260
const CResRef CBaldurEngine::RESREF_SOUND_8CD260("G_Sling2");

// 0x8CF698
const CResRef CBaldurEngine::RESREF_SOUND_8CF698("G_Glove1");

// 0x8CAD40
const CResRef CBaldurEngine::RESREF_SOUND_8CAD40("G_Glove2");

// 0x8CAD98
const CResRef CBaldurEngine::RESREF_SOUND_8CAD98("G_Glove1");

// 0x8C8C80
const CResRef CBaldurEngine::RESREF_SOUND_8C8C80("G_Glove2");

// 0x847F74
const COLORREF CBaldurEngine::COLOR_LABEL_NORMAL = RGB(255, 255, 255);

// 0x847F78
const COLORREF CBaldurEngine::COLOR_LABEL_HIGHLIGHT_PENALTY = RGB(255, 0, 0);

// 0x847F7C
const COLORREF CBaldurEngine::COLOR_LABEL_HIGHLIGHT_BONUS = RGB(255, 255, 0);

// 0x847F80
const COLORREF CBaldurEngine::COLOR_LABEL_DISABLE = RGB(160, 160, 160);

// 0x4277C0
CBaldurEngine::CBaldurEngine()
{
    m_nSelectedCharacter = 0;
    m_pCurrentScrollBar = NULL;
    field_102 = 0;
    field_FE = 0;
    m_nPickedCharacter = -1;
}

// #binary-identical
// 0x427830
BOOL CBaldurEngine::CheckMouseWheel()
{
    return m_pCurrentScrollBar != NULL || field_FE != 0;
}

// #binary-identical
// 0x427850
CUIManager* CBaldurEngine::GetManager()
{
    return &m_cUIManager;
}

// #binary-identical
// 0x427860
void CBaldurEngine::SetSelectedCharacter(int nNewSelectedCharacter)
{
    m_nSelectedCharacter = nNewSelectedCharacter;
}

// #binary-identical
// 0x427870
void CBaldurEngine::SetPickedCharacter(int nNewPickedCharacter)
{
    m_nPickedCharacter = nNewPickedCharacter;
}

// 0x427880
void CBaldurEngine::InvalidateCursorRect(const CRect& rect)
{
    CRect copy;
    copy.CopyRect(rect);
    m_cUIManager.InvalidateCursorRect(copy);
}

// #binary-identical
// 0x4278B0
void CBaldurEngine::ResetControls()
{
    m_cUIManager.InvalidateRect(NULL);
}

// #binary-identical
// 0x427930
int CBaldurEngine::GetSelectedCharacter()
{
    if (m_nSelectedCharacter >= g_pBaldurChitin->GetObjectGame()->GetNumCharacters()) {
        m_nSelectedCharacter = 0;
    }
    return m_nSelectedCharacter;
}

// #binary-identical
// 0x427960
int CBaldurEngine::GetPickedCharacter()
{
    if (m_nPickedCharacter >= g_pBaldurChitin->GetObjectGame()->GetNumCharacters()) {
        m_nPickedCharacter = -1;
    }
    return m_nPickedCharacter;
}

// 0x427990
void CBaldurEngine::SelectEngine(CWarp* pWarp)
{
    CBaldurEngine* pActiveEngine = g_pBaldurChitin->GetActiveEngine();

    pActiveEngine->GetManager()->ClearTooltip();

    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);

    CString sChatText("");
    BOOL bInputCapture = FALSE;
    if (pActiveEngine != NULL) {
        pActiveEngine->GetChatEditBoxStatus(sChatText, bInputCapture);
        pActiveEngine->CancelEngine();
    }

    CWarp::SelectEngine(pWarp);

    static_cast<CBaldurEngine*>(pWarp)->SetChatEditBoxStatus(sChatText, bInputCapture);
}

// 0x427A60
void CBaldurEngine::OnPortraitLClick(DWORD nPortrait)
{
    int nPrevSelectedCharacter = m_nSelectedCharacter;
    m_nSelectedCharacter = nPortrait;
    if (nPrevSelectedCharacter != -1) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(1);
        CUIControlBase* pControl = pPanel->GetControl(nPrevSelectedCharacter);
        if (pControl != NULL) {
            pControl->InvalidateRect();
        }
    }
}

// 0x427A90
void CBaldurEngine::UpdateCursorShape(BYTE nCursor)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    g_pBaldurChitin->GetObjectCursor()->SetCursor(pGame->m_tempCursor == 4 ? nCursor : pGame->m_tempCursor, FALSE);
}

// 0x4277C0
void CBaldurEngine::EnablePortrait(DWORD dwPanelId, DWORD dwControlId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);
    if (pPanel != NULL) {
        CUIControlBase* pControl = pPanel->GetControl(dwControlId);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
        // __LINE__: 3925
        UTIL_ASSERT(pControl != NULL);

        pControl->SetActive(bEnable);
        pControl->SetInactiveRender(bEnable);
    }
}

// 0x427B20
void CBaldurEngine::CheckEnablePortaits(DWORD dwPanelId)
{
    for (DWORD nPortrait = 0; nPortrait < 6; nPortrait++) {
        // NOTE: Unsigned compare.
        BOOL bEnable = nPortrait < static_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetNumCharacters());
        EnablePortrait(dwPanelId, nPortrait, bEnable);
    }
}

// 0x427B60
CString CBaldurEngine::FetchString(DWORD dwStrId)
{
    STR_RES strRes;
    if (!g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes)) {
        strRes.szText = "";
    }
    return strRes.szText;
}

// 0x427C20
void CBaldurEngine::UpdateText(CUIControlTextDisplay* pText, const char* format, ...)
{
    // 0x8CB258
    static char buffer[8192];

    // FIXME: Unused.
    STR_RES strRes;

    va_list args;
    va_start(args, format);

    _vsnprintf(buffer, sizeof(buffer), format, args);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4079
    UTIL_ASSERT(pText != NULL);

    pText->DisplayString(CString(""),
        CString(buffer),
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        TRUE);

    va_end(args);
}

// 0x427D60
void CBaldurEngine::UpdateTextNoTrim(CUIControlTextDisplay* pText, const char* format, ...)
{
    // 0x8CD468
    static char buffer[8192];

    // FIXME: Unused.
    STR_RES strRes;

    va_list args;
    va_start(args, format);

    _vsnprintf(buffer, sizeof(buffer), format, args);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4098
    UTIL_ASSERT(pText != NULL);

    pText->DisplayString(CString(""),
        CString(buffer),
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        FALSE);

    va_end(args);
}

// 0x427EA0
void CBaldurEngine::UpdateTextForceColor(CUIControlTextDisplay* pText, COLORREF rgbTextColor, const char* format, ...)
{
    // 0x8C8D40
    static char buffer[8192];

    // FIXME: Unused.
    STR_RES strRes;

    va_list args;
    va_start(args, format);

    _vsnprintf(buffer, sizeof(buffer), format, args);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4136
    UTIL_ASSERT(pText != NULL);

    pText->DisplayString(CString(""),
        CString(buffer),
        pText->m_rgbLabelColor,
        rgbTextColor,
        -1,
        FALSE,
        TRUE);

    va_end(args);
}

// 0x427FE0
void CBaldurEngine::UpdateLabel(CUIPanel* pPanel, DWORD nID, const char* format, ...)
{
    // NOTE: This buffer is not static (as in previous `UpdateText` functions).
    char buffer[4096];

    // FIXME: Unused.
    STR_RES strRes;

    va_list args;
    va_start(args, format);

    _vsnprintf(buffer, sizeof(buffer), format, args);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4181
    UTIL_ASSERT(pPanel != NULL);

    CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nID));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4183
    UTIL_ASSERT(pLabel != NULL);

    pLabel->SetText(CString(buffer));
}

// 0x428130
void CBaldurEngine::HighlightLabel(CUIPanel* pPanel, DWORD nID, BOOL bCustomColor, COLORREF rgbForegroundColor)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4214
    UTIL_ASSERT(pPanel != NULL);

    CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nID));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4216
    UTIL_ASSERT(pLabel != NULL);

    if (bCustomColor) {
        pLabel->SetForegroundColor(rgbForegroundColor);
    } else {
        pLabel->SetForegroundColor(RGB(255, 255, 255));
    }
}

// 0x4281B0
void CBaldurEngine::PlayGUISound(const CResRef& cResRef)
{
    CSound cSound(cResRef, 0, 0, 0, INT_MAX, FALSE);
    cSound.SetFireForget(TRUE);
    cSound.SetChannel(5, 0);
    cSound.Play(FALSE);
}

// 0x428240
void CBaldurEngine::UpdateCharacterStatus(LONG nCharacterId)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
    // __LINE__: 4273
    UTIL_ASSERT(pGame != NULL);

    SHORT nPortrait = pGame->GetCharacterPortraitNum(nCharacterId);
    if (nPortrait >= 0) {
        // NOTE: There is an unused condition at 0x428285.
        pGame->UpdatePortrait(nPortrait, 1);
    }
}

// #binary-identical
// 0x4282A0
void CBaldurEngine::GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture)
{
    sChatText = "";
    bInputCapture = FALSE;
}

// 0x4282C0
void CBaldurEngine::OnLeftPanelButtonClick(DWORD dwButtonId)
{
    switch (dwButtonId) {
    case 0:
        if (g_pBaldurChitin->m_pEngineWorld != g_pBaldurChitin->GetActiveEngine()) {
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
        }
        break;
    case 4:
        if (g_pBaldurChitin->m_pEngineSpellbook != g_pBaldurChitin->GetActiveEngine()) {
            g_pBaldurChitin->m_pEngineSpellbook->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineSpellbook);
        }
        break;
    case 5:
        if (g_pBaldurChitin->m_pEngineInventory != g_pBaldurChitin->GetActiveEngine()) {
            g_pBaldurChitin->m_pEngineInventory->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineInventory);
            g_pBaldurChitin->m_pEngineInventory->UnPauseGame();
        }
        break;
    case 6:
        if (g_pBaldurChitin->m_pEngineJournal != g_pBaldurChitin->GetActiveEngine()) {
            // FIXME: Calls `GetCurrentChapter` 4 times.
            g_pBaldurChitin->m_pEngineJournal->m_nChapter = max(min(g_pBaldurChitin->GetObjectGame()->GetCurrentChapter(), CGameJournal::NUM_CHAPTERS - 1), 0);
            g_pBaldurChitin->m_pEngineJournal->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineJournal);
        }
        break;
    case 7:
        if (g_pBaldurChitin->m_pEngineMap != g_pBaldurChitin->GetActiveEngine()) {
            g_pBaldurChitin->m_pEngineMap->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineMap);
        }
        break;
    case 8:
        if (g_pBaldurChitin->m_pEngineOptions != g_pBaldurChitin->GetActiveEngine()) {
            g_pBaldurChitin->m_pEngineOptions->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
            g_pBaldurChitin->m_pEngineOptions->m_bFromMainMenu = FALSE;
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineOptions);
        }
        break;
    case 13:
        if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
            if (g_pBaldurChitin->m_pEngineSinglePlayer != g_pBaldurChitin->GetActiveEngine()) {
                g_pBaldurChitin->m_pEngineSinglePlayer->field_45C = 2;
                g_pBaldurChitin->m_pEngineSinglePlayer->StartSinglePlayer(2);
                g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineSinglePlayer);
            }
        } else {
            if (g_pBaldurChitin->m_pEngineMultiPlayer != g_pBaldurChitin->GetActiveEngine()) {
                g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 2;
                g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(2);
                g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);
            }
        }
        break;
    }
}

// 0x4289C0
void CBaldurEngine::OnMouseWheel(BOOL bForward, LONG nTicks, DWORD nLines, WORD wFlags)
{
    if (nLines == 0) {
        return;
    }

    if (m_pCurrentScrollBar != NULL) {
        if (m_pCurrentScrollBar->m_pPanel->m_bActive
            && m_pCurrentScrollBar->m_bActive) {
            while (nTicks > 0) {
                if (bForward) {
                    m_pCurrentScrollBar->OnPageUp(nLines);
                } else {
                    m_pCurrentScrollBar->OnPageDown(nLines);
                }
                nTicks--;
            }
        }
    }

    // TODO: Incomplete.
}

// 0x799E60
void CBaldurEngine::OnPortraitLDblClick(DWORD nPortrait)
{
}

// 0x778900
void CBaldurEngine::UpdateContainerStatus(LONG nContainerId, SHORT nSlotNum)
{
}

// 0x799E60
void CBaldurEngine::UpdatePersonalItemStatus(LONG a2)
{
}

// 0x78E730
void CBaldurEngine::OnRestButtonClick()
{
}

// 0x799CA0
void CBaldurEngine::CheckEnableLeftPanel()
{
}

// 0x78E730
void CBaldurEngine::CancelEngine()
{
}

// 0x78E730
void CBaldurEngine::UpdatePartyGoldStatus()
{
}

// 0x71E750
void CBaldurEngine::SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture)
{
}

// 0x78E6E0
BOOL CBaldurEngine::StopMusic()
{
    return FALSE;
}

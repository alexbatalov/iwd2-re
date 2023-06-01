#ifndef CSCREENCREATECHAR_H_
#define CSCREENCREATECHAR_H_

#include "C2DArray.h"
#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlButtonPlusMinus.h"
#include "CUIControlEdit.h"
#include "CUIControlScrollBar.h"
#include "CUIControlTextDisplay.h"
#include "CVidFont.h"

#define CSCREENCREATECHAR_VIRTUAL_KEYS 90

// Seen in `CUIControlButtonCharGenHatedRaceSelection::OnLButtonClick` assertion.
#define CSCREENCREATECHAR_NUM_HATEDRACES 16

class CAIObjectType;
class CGameSprite;

class CScreenCreateChar : public CBaldurEngine {
public:
    static const char* MALE_PORTRAITS[];
    static const char* FEMALE_PORTRAITS[];
    static const CString NUMBER;
    static const CString TOKEN_MINIMUM;
    static const CString TOKEN_MAXIMUM;

    CScreenCreateChar();
    /* 0004 */ ~CScreenCreateChar() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00AC */ void OnKeyDown(SHORT nKeysFlags) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 0104 */ void CancelEngine() override;

    STRREF sub_607820(BYTE nRace);
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel(CGameSprite* pSprite);
    void ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite);
    void ResetExportPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetImportPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetMonkPaladinSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetSubRacePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_609170(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateCharacterList(CUIPanel* pPanel, DWORD dwTextId, INT nSelected);
    void ResetCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdatePortraitList(CUIPanel* pPanel, DWORD dwTextId, INT nSelectedIndex);
    void ResetCustomSoundsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetNamePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_609B30(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60A5C0(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60A920(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60AF60(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60B610(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetClassPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60BB80();
    void ResetGenderPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetRacePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    BOOL ResetAbility(CGameSprite* pSprite, const CString& sMin, const CString& sMax, const CString& sMod, BYTE& nAbility, BYTE& nMin, BYTE& nMax, INT& nMod, BOOL bRandomize);
    void ResetAbilities(CGameSprite* pSprite);
    void AllocateAbilities(CGameSprite* pSprite);
    void ResetStartOverPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetSkillsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdatePopupPanel(DWORD dwPanelId, CGameSprite* pSprite);
    void UpdateMonkPaladinSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateSubRacePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateFeatsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateGenderPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateAbilitiesPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateSkillsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60EF70(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60F430(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60F810(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_60FA40(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateClassPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_610190(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    CString GetCurrentPortrait(CGameSprite* pSprite);
    void sub_610540();
    void RecallMemoryAbilities(BYTE& nSTR, BYTE& nDEX, BYTE& nCON, BYTE& nINT, BYTE& nWIS, BYTE& nCHR, INT& nExtra);
    INT GetNumHatedRaces();
    void SetTopHatedRace(INT nTopHatedRace);
    BYTE GetHatedRace(INT nIndex);
    void sub_6108D0(INT a1);
    void sub_610A40(INT a1);
    void OnCharacterImportItemSelect(INT nItem);
    void sub_610DC0();
    void OnCharacterExportItemSelect(INT nItem);
    void sub_611AF0();
    void sub_612800();
    void sub_612930();
    void CompleteCharacterSkills();
    void sub_613310();
    void RemoveItems();
    void DeleteCharacter();
    void ImportCharacter();
    void sub_613EF0();
    void OnSoundItemSelect(INT nItem);
    BOOL IsDoneButtonClickable();
    void OnDoneButtonClick();
    void SetSpriteId(INT nSpriteId);
    INT GetSpriteId();
    void sub_617190();
    void OnCancelButtonClick();
    void OnMainCancelButtonClick();
    CUIPanel* GetTopPopup();
    void SummonPopup(DWORD dwPopupId, CGameSprite* pSprite);
    void DismissPopup();

    /* 0106 */ C2DArray field_106;
    /* 012A */ C2DArray m_tSubRace;
    /* 014E */ C2DArray field_14E;
    /* 0172 */ C2DArray field_172;
    /* 01A0 */ CKeyInfo m_pVirtualKeys[CSCREENCREATECHAR_VIRTUAL_KEYS];
    /* 0470 */ BYTE m_pVirtualKeysFlags[CSCREENCREATECHAR_VIRTUAL_KEYS];
    /* 04CA */ BOOL m_bCtrlKeyDown;
    /* 04CE */ BOOL m_bShiftKeyDown;
    /* 04D2 */ BOOL m_bCapsLockKeyOn;
    /* 04D6 */ int field_4D6;
    /* 04DA */ int field_4DA;
    /* 04DE */ int field_4DE;
    /* 04E2 */ INT m_nGameSprite;
    /* 04E6 */ INT m_nExtraFeats;
    /* 04EA */ INT m_nExtraAbilityPoints;
    /* 04F2 */ INT m_nExtraSkillPoints;
    /* 050E */ BYTE m_nMinSTR;
    /* 050F */ BYTE m_nMinDEX;
    /* 0510 */ BYTE m_nMinCON;
    /* 0511 */ BYTE m_nMinINT;
    /* 0512 */ BYTE m_nMinWIS;
    /* 0513 */ BYTE m_nMinCHR;
    /* 0514 */ BYTE m_nMaxSTR;
    /* 0515 */ BYTE m_nMaxDEX;
    /* 0516 */ BYTE m_nMaxCON;
    /* 0517 */ BYTE m_nMaxINT;
    /* 0518 */ BYTE m_nMaxWIS;
    /* 0519 */ BYTE m_nMaxCHR;
    /* 051A */ INT m_nModSTR;
    /* 051E */ INT m_nModDEX;
    /* 0522 */ INT m_nModCON;
    /* 0526 */ INT m_nModINT;
    /* 052A */ INT m_nModWIS;
    /* 052E */ INT m_nModCHR;
    /* 0532 */ INT m_nCurrentPortrait;
    /* 0536 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 055A */ BYTE m_hatedRaces[CSCREENCREATECHAR_NUM_HATEDRACES];
    /* 056A */ int m_nTopHatedRace;
    /* 056F */ BYTE m_nMemorySTR;
    /* 0571 */ BYTE m_nMemoryDEX;
    /* 0572 */ BYTE m_nMemoryCON;
    /* 0573 */ BYTE m_nMemoryINT;
    /* 0574 */ BYTE m_nMemoryWIS;
    /* 0575 */ BYTE m_nMemoryCHR;
    /* 0576 */ INT m_nMemoryExtra;
    /* 057A */ int field_57A;
    /* 057E */ int field_57E;
    /* 0582 */ CStringList* m_pPortraits;
    /* 0586 */ INT m_nCustomSoundIndex;
    /* 058A */ int field_58A;
    /* 058E */ INT m_nCharacterIndex;
    /* 0592 */ CStringList* m_pCharacters;
    /* 059A */ CStringList* m_pSounds;
    /* 059E */ CVidFont m_preLoadFontRealms;
    /* 0A9E */ CVidFont m_preLoadFontStnSml;
    /* 0F9E */ CVidFont m_preLoadFontTool;
    /* 149E */ INT field_149E;
    /* 14A4 */ int field_14A4;
    /* 14A8 */ int field_14A8;
    /* 14AC */ INT m_nTopFeat;
    /* 14B2 */ INT m_storedFeats[75];
    /* 15DE */ SHORT m_nTopSkill;
    /* 15E4 */ INT m_storedSkills[16];
    /* 1624 */ CUIControlScrollBar* field_1624;
};

class CUIControlButtonCharGenMenu : public CUIControlButton {
public:
    CUIControlButtonCharGenMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenMenu() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenImport : public CUIControlButton {
public:
    CUIControlButtonCharGenImport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenImport() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenBack : public CUIControlButton {
public:
    CUIControlButtonCharGenBack(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenBack() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenPopupDone : public CUIControlButton {
public:
    CUIControlButtonCharGenPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenPopupDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAbilitiesPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharGenAbilitiesPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesPlusMinus() override;
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

class CUIControlButtonCharGenAbilitiesStore : public CUIControlButton {
public:
    CUIControlButtonCharGenAbilitiesStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesStore() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAbilitiesRecall : public CUIControlButton {
public:
    CUIControlButtonCharGenAbilitiesRecall(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesRecall() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAbilitiesAllocate : public CUIControlButton {
public:
    CUIControlButtonCharGenAbilitiesAllocate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesAllocate() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAbilitiesReroll : public CUIControlButton {
public:
    CUIControlButtonCharGenAbilitiesReroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesReroll() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarCharGenSkills : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharGenSkills(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharGenSkills() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(int a1) override;
    void OnPageDown(int a1) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharGenSkillsPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharGenSkillsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenSkillsPlusMinus();
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

class CUIControlButtonCharGenAlignmentSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenAlignmentSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAlignmentSelection() override;
    void OnLButtonClick(CPoint pt) override;
    BYTE GetAlignment();
};

class CUIControlButtonCharGenGenderSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenGenderSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenGenderSelection() override;
    void OnLButtonClick(CPoint pt) override;
    BYTE GetGender();
};

class CUIControlButtonCharGenClassSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenClassSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenClassSelection() override;
    void OnLButtonClick(CPoint pt) override;
    BYTE GetClass();
};

class CUIControlButtonCharGenRaceSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenRaceSelection() override;
    void OnLButtonClick(CPoint pt) override;
    BYTE GetRace();
};

class CUIControlEditCharGen : public CUIControlEdit {
public:
    CUIControlEditCharGen(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditCharGen() override;
    void OnKeyDown(SHORT nKey) override;
    void OnEditReturn(CString sText) override;
};

class CUIControlButtonClericWizardSpecializationSelection : public CUIControlButton3State {
public:
    CUIControlButtonClericWizardSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonClericWizardSpecializationSelection() override;
    void OnLButtonClick(CPoint pt) override;
    DWORD GetSpecialization(BYTE nClass);
};

class CUIControlButtonCharGenAppearanceCustom : public CUIControlButton {
public:
    CUIControlButtonCharGenAppearanceCustom(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAppearanceCustom() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenPopupCancel : public CUIControlButton {
public:
    CUIControlButtonCharGenPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenPopupCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarCharGenHatedRace : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharGenHatedRace(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharGenHatedRace() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(int a1) override;
    void OnPageDown(int a1) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharGenHatedRaceSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenHatedRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenHatedRaceSelection() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenCancel : public CUIControlButton {
public:
    CUIControlButtonCharGenCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharGenImportCharacters : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenImportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenImportCharacters() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlTextDisplayCharGenSoundSounds : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenSoundSounds(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenSoundSounds() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonMonkPaladinSpecializationSelection : public CUIControlButton3State {
public:
    CUIControlButtonMonkPaladinSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMonkPaladinSpecializationSelection() override;
    void OnLButtonClick(CPoint pt) override;
    DWORD GetHelp(CGameSprite* pSprite);
};

class CUIControlButtonCharGenSubRaceSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenSubRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenSubRaceSelection() override;
    void OnLButtonClick(CPoint pt) override;
    DWORD GetHelp(const CAIObjectType& typeAI);
};

class CUIControlButtonCharGenBiography : public CUIControlButton {
public:
    CUIControlButtonCharGenBiography(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenBiography() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterBiographyClear : public CUIControlButton {
public:
    CUIControlButtonCharacterBiographyClear(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterBiographyClear() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterBiographyRevert : public CUIControlButton {
public:
    CUIControlButtonCharacterBiographyRevert(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterBiographyRevert() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarCharGenFeats : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharGenFeats(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharGenFeats() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(int a1) override;
    void OnPageDown(int a1) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharGenFeatsPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharGenFeatsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenFeatsPlusMinus() override;
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

#endif /* CSCREENCREATECHAR_H_ */

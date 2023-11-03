#ifndef CSCREENCREATECHAR_H_
#define CSCREENCREATECHAR_H_

#include "C2DArray.h"
#include "CBaldurEngine.h"
#include "CGameAnimation.h"
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

// Seen in `CUIControlButtonCharGenColorChoice` assertion.
#define CRESUI_CONTROLBUTTONID_CHARGEN_COLOR_LASTCOLOR 33

class CAIObjectType;
class CDerivedStats;
class CGameSprite;
class CVidCell;

class CScreenCreateChar : public CBaldurEngine {
public:
    static const char* MALE_PORTRAITS[];
    static const DWORD MALE_PORTRAITS_COUNT;
    static const char* FEMALE_PORTRAITS[];
    static const DWORD FEMALE_PORTRAITS_COUNT;
    static const CString TOKEN_NUMBER;
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

    STRREF GetRangerHatedRaceStrref(BYTE nRace);
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel(CGameSprite* pSprite);
    void ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite);
    void ResetExportPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetImportPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetMonkPaladinSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetSubRacePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetBiographyPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateCharacterList(CUIPanel* pPanel, DWORD dwTextId, INT nSelected);
    void ResetCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdatePortraitList(CUIPanel* pPanel, DWORD dwTextId, INT nSelectedIndex);
    void ResetCustomSoundsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetNamePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetColorsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetMemorizeArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetMemorizeDivineSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetMemorizeDomainSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetClassPanel(CUIPanel* pPanel, CGameSprite* pSprite);
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
    void UpdateArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateMemorizeArcaneSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateMemorizeDivineSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateMemorizeDomainSpellsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateClassPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateAlignmentPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateClericWizardSpecializationPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateHatedRacePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    CString GetCurrentPortrait(CGameSprite* pSprite);
    void IncCurrentPortrait(CGameSprite* pSprite);
    void DecCurrentPortrait(CGameSprite* pSprite);
    void StartCreateChar(INT nCharacterSlot, INT nEngineState);
    void StopCreateChar();
    void CancelCreateChar();
    void RecallMemoryAbilities(BYTE& nSTR, BYTE& nDEX, BYTE& nCON, BYTE& nINT, BYTE& nWIS, BYTE& nCHR, INT& nExtra);
    INT GetNumHatedRaces();
    void SetTopHatedRace(INT nTopHatedRace);
    BYTE GetHatedRace(INT nIndex);
    void OnPortraitLargeItemSelect(INT a1);
    void OnPortraitSmallItemSelect(INT a1);
    void OnCharacterImportItemSelect(INT nItem);
    void sub_610DC0();
    void OnCharacterExportItemSelect(INT nItem);
    void UpdateCharacterStats(CGameSprite* pSprite);
    void UpdateCharacterAppearance();
    void CompleteCharacterAbilities(CGameSprite* pSprite);
    void CompleteCharacterSkills(CGameSprite* pSprite);
    void CompleteCharacterWrapup(CGameSprite* pSprite);
    void RemoveItems(CGameSprite* pSprite);
    void DeleteCharacter();
    void ImportCharacter(const CString& sCharacter);
    void OnPlayButtonClick();
    void OnSoundItemSelect(INT nItem);
    BOOLEAN ExportCharacter(CGameSprite* pSprite);
    BOOL IsNameOnExportList(CString sName);
    BOOL IsDoneButtonClickable(CGameSprite* pSprite);
    void OnDoneButtonClick();
    void SetSpriteId(INT nSpriteId);
    INT GetSpriteId();
    void OnCancelButtonClick();
    void OnMainCancelButtonClick();
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void SummonPopup(DWORD dwPopupId, CGameSprite* pSprite);
    void DismissPopup(CGameSprite* pSprite);
    void sub_617D80();
    void UpdateClassEntry(CUIControlTextDisplay* pText, const CAIObjectType& typeAI, CDerivedStats* DStats, DWORD nSpecialization, BYTE nClass, DWORD dwFlags);
    int GetRaceFeatColumn(BYTE nRace, BYTE nSubRace);

    // NOTE: Seen in `OnDoneButtonClick` assertion.
    INT GetPortraitSmallIndex() { return m_nPortraitSmallIndex; }

    // NOTE: Seen in `OnDoneButtonClick` assertion.
    INT GetPortraitLargeIndex() { return m_nPortraitLargeIndex; }

    // NOTE: Seen in `OnDoneButtonClick` assertion.
    INT GetCustomSoundSetIndex() { return m_nCustomSoundSetIndex; }

    /* 0106 */ C2DArray field_106;
    /* 012A */ C2DArray m_tSubRace;
    /* 014E */ C2DArray m_tHairColor;
    /* 0172 */ C2DArray m_tSkinColor;
    /* 0196 */ CGameAnimation m_animation;
    /* 01A0 */ CKeyInfo m_pVirtualKeys[CSCREENCREATECHAR_VIRTUAL_KEYS];
    /* 0470 */ BYTE m_pVirtualKeysFlags[CSCREENCREATECHAR_VIRTUAL_KEYS];
    /* 04CA */ BOOL m_bCtrlKeyDown;
    /* 04CE */ BOOL m_bShiftKeyDown;
    /* 04D2 */ BOOL m_bCapsLockKeyOn;
    /* 04D6 */ BOOL m_bPickingDomainSpells;
    /* 04DA */ INT m_nFirstStep;
    /* 04DE */ INT m_nCurrentStep;
    /* 04E2 */ INT m_nGameSprite;
    /* 04E6 */ INT m_nExtraFeats;
    /* 04EA */ INT m_nExtraAbilityPoints;
    /* 04EE */ INT m_nExtraSpells;
    /* 04F2 */ INT m_nExtraSkillPoints;
    /* 04F6 */ int field_4F6;
    /* 04FE */ int field_4FE;
    /* 0502 */ int field_502;
    /* 0506 */ int field_506;
    /* 050A */ int field_50A;
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
    /* 0552 */ INT m_nEngineState;
    /* 0556 */ INT m_nCharacterSlot;
    /* 055A */ BYTE m_hatedRaces[CSCREENCREATECHAR_NUM_HATEDRACES];
    /* 056A */ INT m_nTopHatedRace;
    /* 056E */ BYTE m_nRange;
    /* 056F */ BYTE m_nMemorySTR;
    /* 0570 */ unsigned char field_570;
    /* 0571 */ BYTE m_nMemoryDEX;
    /* 0572 */ BYTE m_nMemoryCON;
    /* 0573 */ BYTE m_nMemoryINT;
    /* 0574 */ BYTE m_nMemoryWIS;
    /* 0575 */ BYTE m_nMemoryCHR;
    /* 0576 */ INT m_nMemoryExtra;
    /* 057A */ INT m_nPortraitSmallIndex;
    /* 057E */ INT m_nPortraitLargeIndex;
    /* 0582 */ CStringList* m_pPortraits;
    /* 0586 */ INT m_nCustomSoundSetIndex;
    /* 058A */ INT m_nCustomSoundIndex;
    /* 058E */ INT m_nCharacterIndex;
    /* 0592 */ CStringList* m_pCharacters;
    /* 0596 */ int field_596;
    /* 059A */ CStringList* m_pSounds;
    /* 059E */ CVidFont m_preLoadFontRealms;
    /* 0A9E */ CVidFont m_preLoadFontStnSml;
    /* 0F9E */ CVidFont m_preLoadFontTool;
    /* 149E */ INT m_nErrorState;
    /* 14A2 */ BYTE m_nSpellLevel;
    /* 14A3 */ unsigned char field_14A3;
    /* 14A4 */ int field_14A4;
    /* 14A8 */ int field_14A8;
    /* 14AC */ SHORT m_nTopFeat;
    /* 14AE */ int field_14AE;
    /* 14B2 */ INT m_storedFeats[75];
    /* 15DE */ SHORT m_nTopSkill;
    /* 15E0 */ int field_15E0;
    /* 15E4 */ INT m_storedSkills[16];
    /* 1624 */ CUIControlScrollBar* field_1624;
    /* 1628 */ int field_1628;
};

class CUIControlButtonCharGenMenu : public CUIControlButton {
public:
    CUIControlButtonCharGenMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenMenu() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAccept : public CUIControlButton {
public:
    CUIControlButtonCharGenAccept(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAccept() override;
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

class CUIControlButtonCharGen61A130 : public CUIControlButton {
public:
    CUIControlButtonCharGen61A130(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGen61A130() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarCharGenSkills : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharGenSkills(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharGenSkills() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
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

class CUIControlButtonCharGenKnownArcaneSpellSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenKnownArcaneSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenKnownArcaneSpellSelection() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    void SetSpell(CResRef cResRef);

    /* 066E */ CResRef m_iconResRef;
    /* 0676 */ CResRef m_spellResRef;
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

class CUIControlButtonCharGenHairSkinColor : public CUIControlButton {
public:
    CUIControlButtonCharGenHairSkinColor(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenHairSkinColor() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 0666 */ CVidCell* m_pDecal;
    /* 066A */ CVidPalette* m_pPalette;
};

class CUIControlButtonCharGenColorChoice : public CUIControlButton {
public:
    CUIControlButtonCharGenColorChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenColorChoice() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    BOOL GetColorRange(BYTE& colorRange);

    /* 0666 */ CVidCell* m_pDecal;
    /* 066A */ CVidPalette* m_pPalette;
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
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
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

class CUIControlButtonCharGenMemorizedArcaneSpellSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenMemorizedArcaneSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenMemorizedArcaneSpellSelection() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    void SetSpell(CResRef cResRef);

    /* 066E */ CResRef m_iconResRef;
    /* 0676 */ CResRef m_spellResRef;
};

class CUIControlButtonCharGenMemorizedDivineSpellSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharGenMemorizedDivineSpellSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenMemorizedDivineSpellSelection() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    void SetSpell(CResRef cResRef);

    /* 066E */ CResRef m_iconResRef;
    /* 0676 */ CResRef m_spellResRef;
};

class CUIControlTextDisplayCharGenPortraits : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenPortraits(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenPortraits() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlTextDisplayCharGenImportCharacters : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenImportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenImportCharacters() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonCharGenSoundPlay : public CUIControlButton {
public:
    CUIControlButtonCharGenSoundPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenSoundPlay() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharGenSoundSounds : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenSoundSounds(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenSoundSounds() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlTextDisplayCharGenExportCharacters : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharGenExportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharGenExportCharacters() override;
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

class CUIControlButtonCharGenBiographyClear : public CUIControlButton {
public:
    CUIControlButtonCharGenBiographyClear(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenBiographyClear() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenBiographyRevert : public CUIControlButton {
public:
    CUIControlButtonCharGenBiographyRevert(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenBiographyRevert() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarCharGenFeats : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharGenFeats(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharGenFeats() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
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

class CUIControlButtonCharGenFeatsCircle : public CUIControlButton {
public:
    CUIControlButtonCharGenFeatsCircle(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenFeatsCircle() override;
    BOOL Render(BOOL bForce) override;
};

#endif /* CSCREENCREATECHAR_H_ */

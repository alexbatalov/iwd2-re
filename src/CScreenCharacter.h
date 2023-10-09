#ifndef CSCREENCHARACTER_H_
#define CSCREENCHARACTER_H_

#include "CAIObjectType.h"
#include "CBaldurEngine.h"
#include "CGameSpriteSpells.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlButtonPlusMinus.h"
#include "CUIControlEdit.h"
#include "CUIControlScrollBar.h"
#include "CUIControlTextDisplay.h"
#include "CVidFont.h"

#define CSCREENCHARACTER_VIRTUAL_KEYS 90
#define CSCREENCHARACTER_ERROR_BUTTONS 3

#define CSCREENCHARACTER_NUM_HATEDRACES 16

class CCreatureFileHeader;
class CDerivedStats;
class CGameSprite;
class CUIPanel;

class CScreenCharacter : public CBaldurEngine {
public:
    static const CString TOKEN_SPELLLEVEL;
    static const CString TOKEN_WEAPONNAME;
    static const CString TOKEN_NUMBER;
    static const CString TOKEN_MINIMUM;
    static const CString TOKEN_MAXIMUM;

    static CString SAVE_NAME;

    CScreenCharacter();
    /* 0004 */ ~CScreenCharacter() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
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
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;
    /* 00F0 */ void OnRestButtonClick() override;
    /* 0104 */ void CancelEngine() override;
    /* 0108 */ void UpdateCharacterStatus(LONG nCharacterId) override;

    void UpdateSavingThrows(CUIControlTextDisplay* pText, CDerivedStats& DStats);
    CString GetCurrentPortrait(CGameSprite* pSprite);
    void IncCurrentPortrait(CGameSprite* pSprite);
    void DecCurrentPortrait(CGameSprite* pSprite);
    void ResetAppearancePanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateAppearancePanel(CGameSprite* pSprite);
    void ResetCustomPortraitsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateCustomPortraitsPanel(CGameSprite* pSprite);
    void UpdatePortraitList(CUIPanel* pPanel, DWORD dwControlId, INT nSelected);
    void ResetCustomSoundsPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void ResetClassPanel(CGameSprite* pSprite, int a2);
    void ResetExportPanel(CGameSprite* pSprite);
    void UpdateCharacterList(CUIPanel* pPanel, DWORD dwTextId, INT nSelected);
    BOOLEAN IsNameOnExportList(CString sName);
    void ResetBiographyPanel(CGameSprite* pSprite);
    void ResetClassDescriptionPanel(CGameSprite* pSprite);
    BOOL ResetAbility(CGameSprite* pSprite, const CString& sMin, const CString& sMax, const CString& sMod, BYTE& nAbility, BYTE& nMin, BYTE& nMax, INT& nMod);
    void ResetAbilitiesPanel(CGameSprite* pSprite, int a2);
    void ResetClassSelectionPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void UpdateHatedRacePanel(CGameSprite* pSprite);
    void UpdateSpecializationPanel(CGameSprite* pSprite);
    void UpdateAbilitiesPanel(CGameSprite* pSprite);
    void UpdateSpellsPanel(CGameSprite* pSprite);
    void GetPartyInformation(DWORD& nPartyChapterKillsXPValue, DWORD& nPartyChapterKillsNumber, DWORD& nPartyGameKillsXPValue, DWORD& nPartyGameKillsNumber);
    void EnableMainPanel(BOOL bEnable);
    STRREF GetRangerHatedRaceStrref(BYTE nRace);
    void UpdateMainPanel(BOOL bCharacterChanged);
    void UpdateGeneralInformation(CUIControlTextDisplay* pText, CGameSprite* pSprite);
    void UpdateEquipmentInformation(CUIControlTextDisplay* pText, CGameSprite* pSprite);
    void UpdateMiscInformation(CUIControlTextDisplay* pText, CGameSprite* pSprite);
    void ResetPopupPanel(DWORD dwPanelId, CGameSprite* pSprite, int a3);
    void UpdatePopupPanel(DWORD dwPanelId, CGameSprite* pSprite);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void SummonPopup(DWORD dwPopupId, CGameSprite* pSprite, int a3);
    void DismissPopup(CGameSprite* pSprite);
    BOOL IsDoneButtonClickable(CGameSprite* pSprite);
    void OnDoneButtonClick();
    BOOL OnCancelButtonClick();
    void sub_5E4560();
    void OnInformationButtonClick();
    void OnBiographyButtonClick();
    void OnCustomizeBiographyButtonClick();
    void sub_5E4A20();
    void sub_5E4B30();
    void OnScriptButtonClick();
    void OnExportButtonClick();
    void OnLevelUpButtonClick();
    void LevelUp(CGameSprite* pSprite);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    void CheckDropEquipment();
    void CheckDropSlot(INT nSlot);
    void ResetErrorPanel(CUIPanel* pPanel);
    void ResetScriptPanel(CUIPanel* pPanel);
    void UpdateCustomizePanel(CGameSprite* pSprite);
    void UpdateScriptPanel(CGameSprite* pSprite);
    void RefreshScripts();
    void OnScriptItemSelect(INT nItem);
    void OnErrorButtonClick(INT nButton);
    void OnCharacterItemSelect(INT nItem);
    INT GetNumHatedRaces();
    void SetTopHatedRace(INT nTopHatedRace);
    BYTE GetHatedRace(INT nIndex);
    void CheckMultiPlayerViewableModifyable();
    void OnCustomizeButtonClick();
    void OnAppearanceButtonClick();
    void OnSoundsButtonClick();
    void OnPortraitLargeItemSelect(INT nItem);
    void OnPortraitSmallItemSelect(INT nItem);
    void OnCustomPortraitsButtonClick();
    void OnPlayButtonClick();
    void OnSoundItemSelect(INT nItem);
    void ResetCustomizeBiographyPanel(CUIPanel* pPanel, CGameSprite* pSprite);
    void sub_5F89B0(CGameSprite* pSprite);
    void sub_5F8C90(int a1);
    void sub_5F91F0(int a1);

    static void ResetBiography(CGameSprite* pSprite);

    // NOTE: Seen in `OnErrorButtonClick` assertion.
    int GetNumErrorButtons() { return m_nNumErrorButtons; }

    /* 0106 */ BYTE m_nClass;
    /* 012C */ CAIObjectType m_typeAI;
    /* 01B0 */ BOOL m_bShiftKeyDown;
    /* 01B4 */ BOOL m_bCapsLockKeyOn;
    /* 01B8 */ BOOLEAN field_1B8;
    /* 01BA */ CGameSpriteGroupedSpellList m_spells;
    /* 02B6 */ int field_2B6;
    /* 02BA */ SHORT m_nTopSkill;
    /* 02C0 */ INT m_storedSkills[16];
    /* 0300 */ CKeyInfo m_pVirtualKeys[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 05D0 */ BYTE m_pVirtualKeysFlags[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 062A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0646 */ INT m_nExtraFeats;
    /* 064A */ SHORT m_nTopFeat;
    /* 0650 */ INT m_storedFeats[75];
    /* 077C */ WORD field_77C;
    /* 0780 */ int field_780;
    /* 0798 */ INT m_nExtraSkillPoints;
    /* 079C */ int field_79C;
    /* 07A0 */ int field_7A0;
    /* 07A4 */ int field_7A4;
    /* 07A8 */ int field_7A8;
    /* 07AC */ int field_7AC;
    /* 07B0 */ int field_7B0;
    /* 07B4 */ BOOLEAN m_bCtrlKeyDown;
    /* 07B6 */ INT m_nExtraMageSpells;
    /* 07BA */ int field_7BA;
    /* 07BE */ CStringList* m_pScripts;
    /* 07C2 */ INT m_nScriptIndex;
    /* 07C6 */ INT m_nErrorState;
    /* 07CA */ DWORD m_dwErrorTextId;
    /* 07CE */ INT m_nNumErrorButtons;
    /* 07D2 */ INT m_strErrorButtonText[CSCREENCHARACTER_ERROR_BUTTONS];
    /* 07DE */ INT m_nCharacterIndex;
    /* 07E2 */ CStringList* m_pCharacters;
    /* 07E6 */ BYTE m_hatedRaces[CSCREENCHARACTER_NUM_HATEDRACES];
    /* 07F6 */ INT m_nTopHatedRace;
    /* 07FA */ BOOL m_bMultiPlayerViewable;
    /* 07FE */ BOOL m_bMultiPlayerModifyable;
    /* 0802 */ int m_nCurrentPortrait;
    /* 0806 */ int m_nPortraitLargeIndex;
    /* 080A */ int m_nPortraitSmallIndex;
    /* 080E */ CStringList* m_pPortraits;
    /* 0812 */ INT m_nCustomSoundSetIndex;
    /* 0816 */ INT m_nCustomSoundIndex;
    /* 081A */ unsigned char field_81A;
    /* 081B */ CResRef m_cResPortraitSmall;
    /* 0823 */ CResRef m_cResPortraitLarge;
    /* 0832 */ CString field_832;
    /* 0836 */ CResRef m_cResPortraitSmallTemp;
    /* 083E */ CResRef m_cResPortraitLargeTemp;
    /* 0846 */ DWORD m_nSpecialization;
    /* 084A */ CStringList* m_pSounds;
    /* 084E */ CResRef m_cResSoundSet;
    /* 0856 */ CString field_856;
    /* 085A */ CCreatureFileHeader* m_pTempBaseStats;
    /* 085E */ CDerivedStats* m_pTempDerivedStats;
    /* 0862 */ CDerivedStats* m_pBeforeLevelUpDerivedStats;
    /* 0866 */ int field_866;
    /* 086A */ int field_86A;
    /* 086E */ CVidFont m_preLoadFontRealms;
    /* 0D6E */ CVidFont m_preLoadFontStnSml;
    /* 126E */ CVidFont m_preLoadFontTool;
    /* 176E */ CString field_176E;
    /* 1772 */ int field_1772;
    /* 1776 */ int field_1776;
    /* 1778 */ INT m_nExtraAbilityPoints;
    /* 177C */ BYTE m_nMinSTR;
    /* 177D */ BYTE m_nMinDEX;
    /* 177E */ BYTE m_nMinCON;
    /* 177F */ BYTE m_nMinINT;
    /* 1780 */ BYTE m_nMinWIS;
    /* 1781 */ BYTE m_nMinCHR;
    /* 1782 */ BYTE m_nMaxSTR;
    /* 1783 */ BYTE m_nMaxDEX;
    /* 1784 */ BYTE m_nMaxCON;
    /* 1785 */ BYTE m_nMaxINT;
    /* 1786 */ BYTE m_nMaxWIS;
    /* 1787 */ BYTE m_nMaxCHR;
    /* 1788 */ INT m_nModSTR;
    /* 178C */ INT m_nModDEX;
    /* 1790 */ INT m_nModCON;
    /* 1794 */ INT m_nModINT;
    /* 1798 */ INT m_nModWIS;
    /* 179C */ INT m_nModCHR;
    /* 17A0 */ int field_17A0;
    /* 17A4 */ int field_17A4;
    /* 17A8 */ int field_17A8;
    /* 17C0 */ int field_17C0;
    /* 1800 */ int field_1800;
    /* 1840 */ int field_1840;
    /* 1844 */ unsigned char field_1844;
    /* 1846 */ int field_1846;
    /* 184A */ int field_184A;
    /* 184E */ int field_184E;
    /* 1852 */ int field_1852;
};

class CUIControlButtonCharacterSpecializationSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharacterSpecializationSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterSpecializationSelection() override;
    void OnLButtonClick(CPoint pt) override;

    DWORD GetSpecialization();
};

class CUIControlButtonCharacterAbilitiesPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharacterAbilitiesPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterAbilitiesPlusMinus() override;
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

class CUIControlScrollBarCharacterHatedRace : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharacterHatedRace(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharacterHatedRace() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharacterHatedRaceSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharacterHatedRaceSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterHatedRaceSelection() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacter5EA7D0 : public CUIControlButton {
public:
    CUIControlButtonCharacter5EA7D0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacter5EA7D0() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacter5EA900 : public CUIControlButton {
public:
    CUIControlButtonCharacter5EA900(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacter5EA900() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacter5EAA30 : public CUIControlButton {
public:
    CUIControlButtonCharacter5EAA30(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacter5EAA30() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterCustomize : public CUIControlButton {
public:
    CUIControlButtonCharacterCustomize(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterCustomize() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterInformation : public CUIControlButton {
public:
    CUIControlButtonCharacterInformation(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterInformation() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterExport : public CUIControlButton {
public:
    CUIControlButtonCharacterExport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterExport() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterLevelUp : public CUIControlButton {
public:
    CUIControlButtonCharacterLevelUp(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterLevelUp() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterClassSelection : public CUIControlButton3State {
public:
    CUIControlButtonCharacterClassSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterClassSelection() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInformationDone : public CUIControlButton {
public:
    CUIControlButtonInformationDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInformationDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInformationBiography : public CUIControlButton {
public:
    CUIControlButtonInformationBiography(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInformationBiography() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacter5EBC60 : public CUIControlButton3State {
public:
    CUIControlButtonCharacter5EBC60(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacter5EBC60() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ CResRef field_66E;
    /* 0676 */ CResRef field_676;
};

class CUIControlButtonCharacterPopupDone : public CUIControlButton {
public:
    CUIControlButtonCharacterPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, INT nType);
    ~CUIControlButtonCharacterPopupDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterPopupCancel : public CUIControlButton {
public:
    CUIControlButtonCharacterPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, INT nType);
    ~CUIControlButtonCharacterPopupCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterBiographyRevert : public CUIControlButton {
public:
    CUIControlButtonCharacterBiographyRevert(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterBiographyRevert() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterBiographyClear : public CUIControlButton {
public:
    CUIControlButtonCharacterBiographyClear(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterBiographyClear() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharacterScriptScripts : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharacterScriptScripts(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharacterScriptScripts() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonCharacterError : public CUIControlButton {
public:
    CUIControlButtonCharacterError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharacterExportCharacters : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharacterExportCharacters(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharacterExportCharacters() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlEditCharacter : public CUIControlEdit {
public:
    CUIControlEditCharacter(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditCharacter() override;
    void OnKeyDown(SHORT nKey) override;
    void OnEditReturn(CString sText) override;
};

class CUIControlButtonCharacterCustomizeMenu : public CUIControlButton {
public:
    CUIControlButtonCharacterCustomizeMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterCustomizeMenu() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharacterPortraits : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharacterPortraits(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharacterPortraits() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonCharacterSoundPlay : public CUIControlButton {
public:
    CUIControlButtonCharacterSoundPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterSoundPlay() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterAppearanceCustom : public CUIControlButton {
public:
    CUIControlButtonCharacterAppearanceCustom(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterAppearanceCustom() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayCharacterSoundSounds : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayCharacterSoundSounds(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayCharacterSoundSounds() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlScrollBarCharacterFeats : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharacterFeats(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharacterFeats() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharacterFeatsPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharacterFeatsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterFeatsPlusMinus() override;
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

class CUIControlButtonCharacterFeatsCircle : public CUIControlButton {
public:
    CUIControlButtonCharacterFeatsCircle(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterFeatsCircle() override;
    BOOL Render(BOOL bForce) override;
};

class CUIControlScrollBarCharacterSkills : public CUIControlScrollBar {
public:
    CUIControlScrollBarCharacterSkills(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarCharacterSkills() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

class CUIControlButtonCharacterSkillsPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonCharacterSkillsPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterSkillsPlusMinus() override;
    BOOL OnLButtonDown(CPoint pt) override;
    void AdjustValue() override;
};

class CUIControlButtonCharacterInformationFolder : public CUIControlButton3State {
public:
    CUIControlButtonCharacterInformationFolder(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterInformationFolder() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollbarCharacter5F9410 : public CUIControlScrollBar {
public:
    CUIControlScrollbarCharacter5F9410(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollbarCharacter5F9410() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
};

#endif /* CSCREENCHARACTER_H_ */

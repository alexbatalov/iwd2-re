#ifndef CSCREENCHARACTER_H_
#define CSCREENCHARACTER_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlButtonPlusMinus.h"
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
    ~CScreenCharacter();
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;
    /* 00F0 */ void OnRestButtonClick() override;

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
    void UpdateAbilitiesPanel(CGameSprite* pSprite);
    void GetPartyInformation(DWORD& nPartyChapterKillsXPValue, DWORD& nPartyChapterKillsNumber, DWORD& nPartyGameKillsXPValue, DWORD& nPartyGameKillsNumber);
    void EnableMainPanel(BOOL bEnable);
    STRREF GetRangerHatedRaceStrref(BYTE nRace);
    void UpdateMainPanel(BOOL bCharacterChanged);
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
    void OnInformationButtonClick();
    void OnBiographyButtonClick();
    void OnCustomizeBiographyButtonClick();
    void OnScriptButtonClick();
    void OnExportButtonClick();
    void OnLevelUpButtonClick();
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    void CheckDropEquipment();
    void CheckDropSlot(INT nSlot);
    void ResetErrorPanel(CUIPanel* pPanel);
    void UpdateCustomizePanel(CGameSprite* pSprite);
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

    static void ResetBiography(CGameSprite* pSprite);

    /* 0106 */ BYTE m_nClass;
    /* 01B0 */ BOOL m_bShiftKeyDown;
    /* 01B4 */ BOOL m_bCapsLockKeyOn;
    /* 01B8 */ BOOLEAN field_1B8;
    /* 0300 */ CKeyInfo m_pVirtualKeys[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 05D0 */ BYTE m_pVirtualKeysFlags[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 062A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 077C */ WORD field_77C;
    /* 07B4 */ BOOLEAN m_bCtrlKeyDown;
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
    /* 086E */ CVidFont m_preLoadFontRealms;
    /* 0D6E */ CVidFont m_preLoadFontStnSml;
    /* 126E */ CVidFont m_preLoadFontTool;
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
    /* 1840 */ int field_1840;
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

#endif /* CSCREENCHARACTER_H_ */

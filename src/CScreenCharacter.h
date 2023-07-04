#ifndef CSCREENCHARACTER_H_
#define CSCREENCHARACTER_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CVidFont.h"

#define CSCREENCHARACTER_VIRTUAL_KEYS 90

class CGameSprite;
class CUIPanel;

class CScreenCharacter : public CBaldurEngine {
public:
    static const CString TOKEN_SPELLLEVEL;
    static const CString TOKEN_WEAPONNAME;
    static const CString TOKEN_NUMBER;
    static const CString TOKEN_MINIMUM;
    static const CString TOKEN_MAXIMUM;

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

    CString GetCurrentPortrait(CGameSprite* pSprite);
    void UpdatePortraitList(CUIPanel* pPanel, DWORD dwControlId, INT nSelected);
    void UpdateMainPanel(BOOL bCharacterChanged);
    CUIPanel* GetTopPopup();

    /* 01B0 */ BOOL m_bShiftKeyDown;
    /* 01B4 */ BOOL m_bCapsLockKeyOn;
    /* 01B8 */ BOOLEAN field_1B8;
    /* 0300 */ CKeyInfo m_pVirtualKeys[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 05D0 */ BYTE m_pVirtualKeysFlags[CSCREENCHARACTER_VIRTUAL_KEYS];
    /* 062A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 07B4 */ BOOLEAN m_bCtrlKeyDown;
    /* 0802 */ int m_nCurrentPortrait;
    /* 080E */ CStringList* m_pPortraits;
    /* 086E */ CVidFont m_preLoadFontRealms;
    /* 0D6E */ CVidFont m_preLoadFontStnSml;
    /* 126E */ CVidFont m_preLoadFontTool;
};

#endif /* CSCREENCHARACTER_H_ */

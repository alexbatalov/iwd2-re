#ifndef CSCREENKEYMAPS_H_
#define CSCREENKEYMAPS_H_

#include "mfc.h"

#include "CBaldurEngine.h"
#include "CKeyInfo.h"

#define CSCREENKEYMAPS_VIRTUAL_KEYS 92

class CScreenKeymaps : public CBaldurEngine {
public:
    struct Entry {
        unsigned char dummy[1];
    };

    CScreenKeymaps();
    /* 0004 */ ~CScreenKeymaps() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0038 */ BOOL GetCtrlKey() override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;

    void StartKeymaps();

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENKEYMAPS_VIRTUAL_KEYS];
    /* 03E6 */ BYTE m_pVirtualKeysFlags[CSCREENKEYMAPS_VIRTUAL_KEYS];
    /* 044E */ CTypedPtrList<CPtrList, Entry> field_44E;
    /* 076C */ int field_76C;
    /* 0774 */ unsigned char field_774;
    /* 0775 */ unsigned char field_775;
    /* 0776 */ unsigned char field_776;
    /* 047E */ BOOLEAN m_bSystemKeyCtrl;
    /* 0442 */ BOOL m_bSystemKeyShift;
    /* 0446 */ BOOL m_bSystemKeyCapsLock;
    /* 044A */ int field_44A;
    /* 046A */ int field_46A;
    /* 046E */ int field_46E;
    /* 0472 */ int field_472;
    /* 0476 */ int field_476;
    /* 047A */ int field_47A;
    /* 0480 */ int field_480;
    /* 0770 */ int field_770;
};

#endif /* CSCREENKEYMAPS_H_ */

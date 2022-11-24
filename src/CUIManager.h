#ifndef CUIMANAGER_H_
#define CUIMANAGER_H_

#include <afx.h>
#include <afxmt.h>
#include <afxtempl.h>

#include "CResRef.h"
#include "CUIPanel.h"

class CUIManager {
public:
    CUIManager();
    ~CUIManager();

    /* 000 */ int field_0;
    /* 004 */ int field_4;
    /* 008 */ CResRef field_8;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ int field_28;
    /* 002C */ unsigned char field_2C;
    /* 002E */ unsigned char field_2E;
    /* 002D */ unsigned char field_2D;
    /* 0032 */ int field_32;
    /* 0036 */ CCriticalSection field_36;
    /* 0056 */ CCriticalSection field_56;
    /* 0076 */ int field_76;
    /* 007A */ RECT field_7A;
    /* 008A */ RECT field_8A;
    /* 009A */ RECT field_9A;
    /* 00AA */ int field_AA;
    /* 00AE */ CTypedPtrList<CPtrList, CUIPanel*> m_lPanels; // #guess
};

#endif /* CUIMANAGER_H_ */

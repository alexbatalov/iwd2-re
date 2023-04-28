#ifndef CINFCURSOR_H_
#define CINFCURSOR_H_

#include "BalDataTypes.h"

class CUIControlBase;

class CInfCursor {
public:
    CInfCursor();
    ~CInfCursor();
    void Initialize();
    void SetCursor(INT nNewCursor, BOOLEAN bForce);
    void SetToolTip(STRREF nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, STRREF nSecondaryStrRef, STRREF nTertiaryStrRef);

    /* 0000 */ int field_0;
    /* 09EE */ int field_9EE;
    /* 09F2 */ int field_9F2;
    /* 09F6 */ int field_9F6;
    /* 09FA */ int field_9FA;
    /* 09FE */ int m_nState;
    /* 0A02 */ CUIControlBase* field_A02;
    /* 0A06 */ unsigned char field_A06;
};

#endif /* CINFCURSOR_H_ */

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

    /* 09FE */ int m_nState;
    /* 0A02 */ CUIControlBase* field_A02;
};

#endif /* CINFCURSOR_H_ */

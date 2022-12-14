#ifndef CINFCURSOR_H_
#define CINFCURSOR_H_

#include "BalDataTypes.h"

class CUIControlBase;

class CInfCursor {
public:
    CInfCursor();
    ~CInfCursor();
    void SetCursor(INT nNewCursor, BOOLEAN bForce);
    void SetToolTip(STRREF nStrRef, CUIControlBase* pControl, SHORT nHotKeyIndex1, SHORT nHotKeyIndex2, CString sKey, STRREF nSecondaryStrRef, STRREF nTertiaryStrRef);
};

#endif /* CINFCURSOR_H_ */

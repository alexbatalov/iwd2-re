#ifndef CRESREF_H_
#define CRESREF_H_

#include "ChDataTypes.h"

class CResRef {
public:
    CResRef();
    CResRef(const CString& sName);
    CResRef(const char* pName);
    CResRef(BYTE* resRef);
    void CopyToString(CString& str) const;
    const BYTE* GetResRef() const;
    CString GetResRefStr() const;
    BOOL IsValid() const;
    void CopyToString(char* pStr) const;
    BOOL operator!=(const CResRef& cResRef) const;
    BOOL operator!=(const CString& sName) const;
    BOOL operator!=(const char* pName) const;
    BOOL operator==(const CResRef& cResRef) const;
    BOOL operator==(const CString& sName) const;
    BOOL operator==(const char* pStr) const;
    BOOL operator!() const;
    CResRef operator=(const CResRef& cResRef);
    CResRef operator=(BYTE* resRef);
    CResRef operator=(const CString& sName);
    CResRef operator=(const char* pName);
    void MakeUpper();
    CResRef operator+=(const CString& sName);
    void GetResRef(BYTE* resRef) const;

    // #guess
    BYTE GetAt(int n) const { return m_resRef[n]; }

protected:
    RESREF m_resRef;
};

#endif /* CRESREF_H_ */

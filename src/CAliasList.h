#ifndef CALIASLIST_H_
#define CALIASLIST_H_

#include <afxwin.h>

class CAlias;

class CAliasList : public CObList {
public:
    BOOL AddAlias(CAlias* pAlias);
    BOOL ResolveFileName(const CString& a2, CString& a3);
};

#endif /* CALIASLIST_H_ */

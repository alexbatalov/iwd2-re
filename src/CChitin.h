#ifndef CCHITIN_H_
#define CCHITIN_H_

#include <afxwin.h>

class CChitin {
public:
    static void GetGameVersionInfo(HINSTANCE hInstance);
    static void FixReadonlyPermissions();
    static void DoFixReadonlyPermissions(CString path);

    static CString buildVersionString;
    static CString versionString;
    static CString name;
};

#endif /* CCHITIN_H_ */

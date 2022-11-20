#ifndef CCHITIN_H_
#define CCHITIN_H_

#include <afxwin.h>

class CChitin {
public:
    CChitin();
    virtual ~CChitin();
    static void GetGameVersionInfo(HINSTANCE hInstance);
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static void FixReadonlyPermissions();
    static void DoFixReadonlyPermissions(CString path);

    int field_1932;

    static CString buildVersionString;
    static CString versionString;
    static CString name;
};

#endif /* CCHITIN_H_ */

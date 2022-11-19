#include <afxwin.h>

#include <iostream>

#include "CChitin.h"

// 0x421820
static BOOL IsSupportedOS(DWORD& majorVersion, DWORD& minorVersion)
{
    OSVERSIONINFOEX info = { 0 };
    BOOL supported = TRUE;
    int servicePack;

    info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (!GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&info))) {
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

        if (!GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&info))) {
            return FALSE;
        }
    }

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        supported = FALSE;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        if (info.dwMajorVersion < 4) {
            supported = FALSE;
        }
        break;
    case VER_PLATFORM_WIN32_NT:
        servicePack = 0;
        sscanf(info.szCSDVersion, "Service Pack %d", &servicePack);
        if (info.dwMajorVersion <= 3 || (info.dwMajorVersion == 4 && info.dwMinorVersion != 0 && servicePack < 5)) {
            supported = FALSE;
        }
    }

    majorVersion = info.dwMajorVersion;
    minorVersion = info.dwMinorVersion;
    return supported;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::cout << std::endl;
    std::cout << "BEGIN LOGGING SESSION";
    std::cout << std::endl;

    CChitin::GetGameVersionInfo(hInstance);

    AfxSetResourceHandle(hInstance);

    CChitin::FixReadonlyPermissions();

    DWORD majorVersion;
    DWORD minorVersion;
    if (IsSupportedOS(majorVersion, minorVersion)) {
        // TODO: Incomplete.
    } else {
        const char* text = "Icewind Dale II requires one of these Microsoft Operating Systems to run:\r\n"
            "\r\n"
            "  \x95 Windows XP\r\n"
            "  \x95 Windows 2000\r\n"
            "  \x95 Windows NT 4 with Service Pack 5 or above\r\n"
            "  \x95 Windows ME\r\n"
            "  \x95 Windows 98\r\n"
            "  \x95 Windows 95\r\n"
            "\r\n"
            "Press Enter to Exit";
        const char* caption = "Operating System Not Supported";
        MessageBox(NULL, text, caption, MB_ICONERROR);
    }

    return 0;
}

#include <afxwin.h>

#include <iostream>

#include "CBaldurChitin.h"

// 0x421820
static BOOL IsSupportedOS(DWORD& majorVersion, DWORD& minorVersion)
{
    OSVERSIONINFOEXA info = { 0 };
    BOOL supported = TRUE;
    int servicePack;

    info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

#pragma warning(suppress : 4996)
    if (!GetVersionExA(reinterpret_cast<LPOSVERSIONINFOA>(&info))) {
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

#pragma warning(suppress : 4996)
        if (!GetVersionExA(reinterpret_cast<LPOSVERSIONINFOA>(&info))) {
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
    if (!IsSupportedOS(majorVersion, minorVersion)) {
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
        MessageBoxA(NULL, text, caption, MB_ICONERROR);
        return 0;
    }

    char v1[] = "Global\\Icewind2";
    char v2[] = "Icewind2";
    char* mutexName = v2;
    if (majorVersion >= 5) {
        mutexName = v1;
    }

    HANDLE mutexHandle = CreateMutexA(NULL, FALSE, mutexName);

    // NOTE: Wrong check, should check for `INVALID_HANDLE_VALUE`.
    if (mutexHandle == NULL) {
        return 0;
    }

    if (WaitForSingleObject(mutexHandle, 0) == WAIT_TIMEOUT) {
        CloseHandle(mutexHandle);
        return 0;
    }

    CBaldurChitin baldurChitin;
    if (baldurChitin.field_1932 != 0) {
        CloseHandle(mutexHandle);
        return 0;
    }

    char currentDirectory[261];
    GetCurrentDirectoryA(sizeof(currentDirectory), currentDirectory);

    char currentDirectoryCopy[261];
    lstrcpyA(currentDirectoryCopy, currentDirectory);
    lstrcatA(currentDirectoryCopy, "\\register");
    SetCurrentDirectoryA(currentDirectoryCopy);

    STARTUPINFO startupInfo = { 0 };
    PROCESS_INFORMATION processInfo;
    if (CreateProcessA(NULL, "reg32.exe FALSE", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInfo)) {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
    }

    SetCurrentDirectoryA(currentDirectory);
    SetCurrentDirectoryA("C:\\Program Files (x86)\\GOG.com\\Icewind Dale II");

    baldurChitin.Init(hInstance);
    int rc = baldurChitin.WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    CloseHandle(mutexHandle);
    return rc;
}

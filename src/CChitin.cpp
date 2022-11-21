#include "CChitin.h"

#include <direct.h>
#include <winver.h>

// 0x8FB938
CString CChitin::buildVersionString;

// 0x8FB940
CString CChitin::versionString;

// 0x8FB944
CString CChitin::name;

// 0x8FB974
int CChitin::dword_8FB974;

// 0x8FB978
int CChitin::dword_8FB978;

// 0x8FB97C
int CChitin::dword_8FB97C;

// TODO: Check generated assembly once memory layout is complete.
//
// 0x78E2A0
CChitin::CChitin()
{
    field_184 = 0;
    field_188 = 0;
    field_18C = 0;
    field_190 = 0;
    field_194 = 0;
    field_198 = 0;
    m_nThreads = 0;
    field_1A28 = 0;
    m_dwThreadIds[m_nThreads] = GetCurrentThreadId();

    HANDLE currentProcess = GetCurrentProcess();
    HANDLE currentThread = GetCurrentThread();
    if (DuplicateHandle(currentProcess, currentThread, currentProcess, &(m_hThreadHandles[m_nThreads]), 0, TRUE, DUPLICATE_SAME_ACCESS)) {
        m_nThreads++;
    }

    InitializeCriticalSection(&field_2FC);
    InitializeCriticalSection(&field_32C);
    InitializeCriticalSection(&field_314);
    InitializeCriticalSection(&field_344);
    InitializeCriticalSection(&field_C4);
    InitializeCriticalSection(&field_35C);
    InitializeCriticalSection(&field_394);
    InitializeCriticalSection(&field_3AC);
    InitializeCriticalSection(&field_1C32);

    InitializeVariables();
    InitVariables3D();

    OSVERSIONINFO versionInfo;
    memset(&versionInfo, 0, sizeof(OSVERSIONINFO));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&versionInfo);

    dwPlatformId = versionInfo.dwPlatformId;

    if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        cDimm.field_D6 = cDimm.dwTotalPhysicalMemory - 0x1000000;
    } else {
        cDimm.field_D6 = cDimm.dwTotalPhysicalMemory - 0x800000;
    }

    field_FE = 0;
    field_1C4C = 0;
    field_1A2A = 0;
    field_1A2E = 0;

    for (int i = 0; i < 16; i++) {
        field_1A32[i] = 1000;
    }

    memset(field_1A72, 0, sizeof(field_1A72));
    memset(field_1AB2, 0, sizeof(field_1AB2));
    memset(field_1AF2, 0, sizeof(field_1AF2));
    memset(field_1B32, 0, sizeof(field_1B32));

    field_110 = 0;
    field_114 = 0;

    field_118 = "";
    field_120 = "";
    field_11C = "";
    field_124 = 0;
    field_128 = 0;
    field_12C = "";
    field_131 = 0;
    field_132 = "";
    field_130 = 0;
    field_136 = 6;
    dword_8FB974 = 0;
    dword_8FB978 = 0;
    dword_8FB97C = 0;
    field_180 = 0;
    field_19C = 0;
    field_1C4A = 1;
    field_2EC = 0;
}

// TODO: Check generated assembly once memory layout is complete.
//
// 0x78E930
CChitin::~CChitin()
{
    if (cVideo.m_bIs3dAccelerated) {
        Shutdown3D();
    }

    field_14C.RemoveAll();

    cDimm.DestroyKeyTable();
    cDimm.DumpAll();

    DeleteCriticalSection(&field_2FC);
    DeleteCriticalSection(&field_32C);
    DeleteCriticalSection(&field_314);
    DeleteCriticalSection(&field_C4);
    DeleteCriticalSection(&field_35C);

    if (m_eventTimer != NULL) {
        CloseHandle(m_eventTimer);
    }

    if (field_B4 != NULL) {
        CloseHandle(field_B4);
    }

    DeleteCriticalSection(&field_394);
    DeleteCriticalSection(&field_3AC);
    DeleteCriticalSection(&field_1C32);
}

// BINARY IDENTICAL
// 0x78FDF0
void CChitin::GetGameVersionInfo(HINSTANCE hInstance)
{
    char filename[256] = "Oct 16 2002";
    GetModuleFileName(hInstance, filename, 256);

    DWORD handle;
    DWORD size = GetFileVersionInfoSize(filename, &handle);
    if (size != 0) {
        BYTE* fileVersionInfo = new BYTE[size];
        GetFileVersionInfo(filename, handle, size, fileVersionInfo);

        LPVOID buffer;
        UINT len;
        if (VerQueryValue(fileVersionInfo, "\\StringFileInfo\\040904B0\\PrivateBuild", &buffer, &len)) {
            char buildDate[] = "Oct 16 2002";
            char buildTime[] = "15:36:32";
            char months[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
            buildDate[3] = '\0';

            int month = (strstr(months, buildDate) - months) / 3 + 1;
            buildVersionString.Format("%-2.2i%-2.2i%2.2s",
                month,
                atoi(&(buildDate[4])),
                buildTime);
        } else {
            buildVersionString = "";
        }

        if (VerQueryValue(fileVersionInfo, "\\StringFileInfo\\040904B0\\ProductVersion", &buffer, &len)) {
            versionString = CString(reinterpret_cast<char*>(buffer));
        } else {
            versionString = "";
        }

        if (VerQueryValue(fileVersionInfo, "\\StringFileInfo\\040904B0\\ProductName", &buffer, &len)) {
            name = CString(reinterpret_cast<char*>(buffer));
        } else {
            name = "";
        }

        if (fileVersionInfo != NULL) {
            delete[] fileVersionInfo;
        }
    }
}

// 0x7926B0
int CChitin::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // TODO: Incomplete.

    return 0;
}

// Removes `readonly` file attribute on all files in special directories.
//
// BINARY IDENTICAL
// 0x792940
void CChitin::FixReadonlyPermissions()
{
    CString cache;
    CString mpsave;
    CString mptemp;
    CString save;
    CString temp;
    CString tempsave;

    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cache = cwd;
        cache += "\\cache";

        mpsave = cwd;
        mpsave += "\\mpsave";

        mptemp = cwd;
        mptemp += "\\mptemp";

        save = cwd;
        save += "\\save";

        temp = cwd;
        temp += "\\temp";

        tempsave = cwd;
        tempsave += "\\tempsave";

        DoFixReadonlyPermissions(cache);
        DoFixReadonlyPermissions(mpsave);
        DoFixReadonlyPermissions(mptemp);
        DoFixReadonlyPermissions(save);
        DoFixReadonlyPermissions(temp);
        DoFixReadonlyPermissions(tempsave);
    }
}

// NOTE: Passing object produces unncessary copies at call sites.
//
// BINARY IDENTICAL
// 0x792B50
void CChitin::DoFixReadonlyPermissions(CString path)
{
    CFileFind fileFind;

    BOOLEAN exists = fileFind.FindFile(path);
    if (exists) {
        DWORD attrs = GetFileAttributes(path);
        attrs &= ~FILE_ATTRIBUTE_READONLY;
        SetFileAttributes(path, attrs);
    }

    path += "\\*.*";

    BOOLEAN working = fileFind.FindFile(path);
    while (working) {
        working = fileFind.FindNextFile();
        if (!fileFind.IsDots()) {
            if (fileFind.IsDirectory()) {
                DoFixReadonlyPermissions(fileFind.GetFilePath());
            }

            DWORD attrs = GetFileAttributes(fileFind.GetFilePath());
            attrs &= ~FILE_ATTRIBUTE_READONLY;
            SetFileAttributes(fileFind.GetFilePath(), attrs);
        }
    }
}

// 0x7902C0
void CChitin::InitializeVariables()
{
    // TODO: Incomplete.
}

// 0x7C8980
void CChitin::InitVariables3D()
{
    // TODO: Incomplete.
}

// #guess
// 0x7C8B10
void CChitin::Shutdown3D()
{
    // TODO: Incomplete.
}

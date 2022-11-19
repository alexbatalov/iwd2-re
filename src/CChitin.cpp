#include "CChitin.h"

#include <winver.h>

// 0x8FB938
CString CChitin::buildVersionString;

// 0x8FB940
CString CChitin::versionString;

// 0x8FB944
CString CChitin::name;

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

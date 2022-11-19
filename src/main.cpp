#include <afxwin.h>

#include <iostream>

#include "CChitin.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::cout << std::endl;
    std::cout << "BEGIN LOGGING SESSION";
    std::cout << std::endl;

    CChitin::GetGameVersionInfo(hInstance);

    AfxSetResourceHandle(hInstance);

    // TODO: Incomplete.

    return 0;
}

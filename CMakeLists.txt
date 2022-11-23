cmake_minimum_required(VERSION 3.13)

set(EXECUTABLE_NAME iwd2-re)

project(${EXECUTABLE_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_MFC_FLAG 2)

add_executable(${EXECUTABLE_NAME} WIN32)

target_sources(${EXECUTABLE_NAME} PUBLIC
    "src/CAliasList.cpp"
    "src/CAliasList.h"
    "src/CBaldurChitin.cpp"
    "src/CBaldurChitin.h"
    "src/CBaldurMessage.cpp"
    "src/CBaldurMessage.h"
    "src/CCacheStatus.cpp"
    "src/CCacheStatus.h"
    "src/CChitin.cpp"
    "src/CChitin.h"
    "src/CDimm.cpp"
    "src/CDimm.h"
    "src/CDimmKeyTable.cpp"
    "src/CDimmKeyTable.h"
    "src/CGameSpy.cpp"
    "src/CGameSpy.h"
    "src/CImm.cpp"
    "src/CImm.h"
    "src/CMessageHandler.cpp"
    "src/CMessageHandler.h"
    "src/CNetwork.cpp"
    "src/CNetwork.h"
    "src/CNetworkWindow.cpp"
    "src/CNetworkWindow.h"
    "src/CProgressBar.cpp"
    "src/CProgressBar.h"
    "src/CRes.cpp"
    "src/CRes.h"
    "src/CResCache.cpp"
    "src/CResCache.h"
    "src/CResMosaic.cpp"
    "src/CResMosaic.h"
    "src/CResRef.cpp"
    "src/CResRef.h"
    "src/CSound.cpp"
    "src/CSound.h"
    "src/CSoundMixer.cpp"
    "src/CSoundMixer.h"
    "src/CSoundProperties.cpp"
    "src/CSoundProperties.h"
    "src/CSwitchCDStatus.cpp"
    "src/CSwitchCDStatus.h"
    "src/CTlkFileOverride.cpp"
    "src/CTlkFileOverride.h"
    "src/CTlkTable.cpp"
    "src/CTlkTable.h"
    "src/CUnknown1.cpp"
    "src/CUnknown1.h"
    "src/CUnknown2.cpp"
    "src/CUnknown2.h"
    "src/CVidBitmap.cpp"
    "src/CVidBitmap.h"
    "src/CVidBlitter.cpp"
    "src/CVidBlitter.h"
    "src/CVidCell.cpp"
    "src/CVidCell.h"
    "src/CVideo.cpp"
    "src/CVideo.h"
    "src/CVidFont.cpp"
    "src/CVidFont.h"
    "src/CVidImage.cpp"
    "src/CVidImage.h"
    "src/CVidInf.cpp"
    "src/CVidInf.h"
    "src/CVidMode.cpp"
    "src/CVidMode.h"
    "src/CVidMosaic.cpp"
    "src/CVidMosaic.h"
    "src/CVidPalette.cpp"
    "src/CVidPalette.h"
    "src/CWarp.cpp"
    "src/CWarp.h"
    "src/main.cpp"
)

target_compile_definitions(${EXECUTABLE_NAME} PUBLIC
    _AFXDLL
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_WARNINGS
    _SBCS
)

target_link_libraries(${EXECUTABLE_NAME}
    version
)

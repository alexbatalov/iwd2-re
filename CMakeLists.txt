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
    "src/CChitin.cpp"
    "src/CChitin.h"
    "src/CDimm.cpp"
    "src/CDimm.h"
    "src/CGameSpy.cpp"
    "src/CGameSpy.h"
    "src/CImm.cpp"
    "src/CImm.h"
    "src/CNetwork.cpp"
    "src/CNetwork.h"
    "src/CProgressBar.cpp"
    "src/CProgressBar.h"
    "src/CSound.cpp"
    "src/CSound.h"
    "src/CSoundMixer.cpp"
    "src/CSoundMixer.h"
    "src/CSoundProperties.cpp"
    "src/CSoundProperties.h"
    "src/CUnknown1.cpp"
    "src/CUnknown1.h"
    "src/CUnknown2.cpp"
    "src/CUnknown2.h"
    "src/CVideo.cpp"
    "src/CVideo.h"
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

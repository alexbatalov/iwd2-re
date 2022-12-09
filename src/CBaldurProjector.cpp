#include "CBaldurProjector.h"

#include "CBaldurChitin.h"
#include "CUtil.h"

// 0x43E640
CBaldurProjector::CBaldurProjector()
{
    field_106 = 0;

    m_pVirtualKeysFlags[0] = 0;
    m_pVirtualKeysFlags[1] = 0;

    SetVideoMode(0);

    m_bDeactivateEngine = FALSE;

    m_pVirtualKeys[0] = CKeyInfo(VK_SPACE, 0, 0);
    m_pVirtualKeys[1] = CKeyInfo(VK_ESCAPE, 0, 0);

    field_10A = 0;
    field_144 = 1;
    field_145 = 0;
    field_146 = 0;
    field_147 = 0;

    field_14A.SetResRef(CResRef("NORMAL"), g_pChitin->field_2EC, 1);
    field_14A.SetColor(0xFFFFFF, 0, 0);
    field_14A.RegisterFont();
    field_64E = "";

    m_hBink = NULL;
    field_652 = "";
    field_65A = 4;

    m_pfnBinkOpen = NULL;
    m_pfnBinkDDSurfaceType = NULL;
    m_pfnBinkDoFrame = NULL;
    field_66A = 0;
    m_pfnBinkNextFrame = NULL;
    m_pfnBinkClose = NULL;
    m_pfnBinkGetSummary = NULL;
    m_pfnBinkCopyToBuffer = NULL;
    m_pfnBinkOpenDirectSound = NULL;
    m_pfnBinkSetSoundSystem = NULL;
    m_pfnBinkSetSoundOnOff = NULL;
    m_pfnBinkWait = NULL;
    m_pfnBinkGetError = NULL;
    m_pfnBinkSetVolume = NULL;
    m_hBinkDLL = NULL;
    field_69A = 0;
    field_69E = 1;

    m_hBinkDLL = LoadLibraryA("binkw32");
    if (m_hBinkDLL != NULL) {
        m_pfnBinkOpen = reinterpret_cast<BinkOpen*>(GetProcAddress(m_hBinkDLL, "_BinkOpen@8"));
        m_pfnBinkDDSurfaceType = reinterpret_cast<BinkDDSurfaceType*>(GetProcAddress(m_hBinkDLL, "_BinkDDSurfaceType@4"));
        m_pfnBinkDoFrame = reinterpret_cast<BinkDoFrame*>(GetProcAddress(m_hBinkDLL, "_BinkDoFrame@4"));
        m_pfnBinkCopyToBuffer = reinterpret_cast<BinkCopyToBuffer*>(GetProcAddress(m_hBinkDLL, "_BinkCopyToBuffer@28"));
        m_pfnBinkNextFrame = reinterpret_cast<BinkNextFrame*>(GetProcAddress(m_hBinkDLL, "_BinkNextFrame@4"));
        m_pfnBinkClose = reinterpret_cast<BinkClose*>(GetProcAddress(m_hBinkDLL, "_BinkClose@4"));
        m_pfnBinkGetSummary = reinterpret_cast<BinkGetSummary*>(GetProcAddress(m_hBinkDLL, "_BinkGetSummary@8"));
        m_pfnBinkSetSoundOnOff = reinterpret_cast<BinkSetSoundOnOff*>(GetProcAddress(m_hBinkDLL, "_BinkSetSoundOnOff@8"));
        m_pfnBinkWait = reinterpret_cast<BinkWait*>(GetProcAddress(m_hBinkDLL, "_BinkWait@4"));
        m_pfnBinkGetError = reinterpret_cast<BinkGetError*>(GetProcAddress(m_hBinkDLL, "_BinkGetError@0"));
        m_pfnBinkSetVolume = reinterpret_cast<BinkSetVolume*>(GetProcAddress(m_hBinkDLL, "_BinkSetVolume@12"));
        m_pfnBinkOpenDirectSound = reinterpret_cast<BinkOpenDirectSound*>(GetProcAddress(m_hBinkDLL, "_BinkOpenDirectSound@4"));
        m_pfnBinkSetSoundSystem = reinterpret_cast<BinkSetSoundSystem*>(GetProcAddress(m_hBinkDLL, "_BinkSetSoundSystem@8"));

        if (m_pfnBinkOpen == NULL
            || m_pfnBinkDDSurfaceType == NULL
            || m_pfnBinkDoFrame == NULL
            || m_pfnBinkNextFrame == NULL
            || m_pfnBinkClose == NULL
            || m_pfnBinkGetSummary == NULL
            || m_pfnBinkCopyToBuffer == NULL
            || m_pfnBinkSetSoundOnOff == NULL
            || m_pfnBinkWait == NULL
            || m_pfnBinkGetError == NULL
            || m_pfnBinkOpenDirectSound == NULL
            || m_pfnBinkSetSoundSystem == NULL
            || m_pfnBinkSetVolume == NULL) {
            FreeLibrary(m_hBinkDLL);
            m_hBinkDLL = NULL;
        }
    }
}

// 0x43E9E0
void CBaldurProjector::OnLButtonDown(CPoint pt)
{
    m_bDeactivateEngine = TRUE;
}

// 0x43E9F0
SHORT CBaldurProjector::GetNumVirtualKeys()
{
    return CBALDURPROJECTOR_VIRTUAL_KEYS;
}

// 0x43EA00
CKeyInfo* CBaldurProjector::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x43EA10
BYTE* CBaldurProjector::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x43EA20
void CBaldurProjector::OnKeyDown(SHORT a2)
{
    m_bDeactivateEngine = TRUE;
}

// 0x43EA30
void CBaldurProjector::EngineGameInit()
{
    field_144 = 0;
}

// 0x43EA40
void CBaldurProjector::EngineGameUninit()
{
    field_144 = 1;
}

// 0x43EA70
CBaldurProjector::~CBaldurProjector()
{
    while (!m_lMovies.IsEmpty()) {
        CResRef* pResRef = m_lMovies.RemoveHead();
        delete pResRef;
    }

    EnterCriticalSection(&(g_pChitin->field_3AC));

    if (m_hBink != NULL) {
        m_pfnBinkClose(m_hBink);
        field_14A.Unload();
    }

    // TODO: Incomplete. Destroying some global object and surface, probably
    // related to subtitles.

    field_64E = "";

    if (m_hBinkDLL != NULL) {
        FreeLibrary(m_hBinkDLL);
        m_hBinkDLL = NULL;
    }

    LeaveCriticalSection(&(g_pChitin->field_3AC));
}

// 0x43F000
void CBaldurProjector::PlayMovie(const CResRef& cResRef)
{
    if (cResRef != "") {
        while (!m_lMovies.IsEmpty()) {
            CResRef* pResRef = m_lMovies.RemoveHead();
            delete pResRef;
        }

        PlayMovieInternal(cResRef, TRUE);
    }
}

// #guess
// 0x43F060
BOOL CBaldurProjector::ResolveMovieFileName(const CResRef& cResRef, CString& sMovieFileName)
{
    BOOL resolved = FALSE;
    CString sBaseName = cResRef.GetResRefStr();
    CString sFileName("");

    sMovieFileName = "";

    if (cResRef != "") {
        do {
            WIN32_FIND_DATAA ffd;
            HANDLE hFindFile;

            sFileName = "hd0:\\override\\";
            sFileName += sBaseName;
            sFileName += ".mve";

            if (g_pChitin->lAliases.ResolveFileName(sFileName, sMovieFileName) == TRUE) {
                hFindFile = FindFirstFileA(sMovieFileName, &ffd);
                if (hFindFile != INVALID_HANDLE_VALUE) {
                    resolved = TRUE;
                    FindClose(hFindFile);
                    break;
                }
            }

            sFileName = "hd0:\\data\\";
            sFileName += sBaseName;
            sFileName += ".mve";

            if (g_pChitin->lAliases.ResolveFileName(sFileName, sMovieFileName) == TRUE) {
                hFindFile = FindFirstFileA(sMovieFileName, &ffd);
                if (hFindFile != INVALID_HANDLE_VALUE) {
                    resolved = TRUE;
                    FindClose(hFindFile);
                    break;
                }
            }

            sFileName = "cd2:\\data\\";
            sFileName += sBaseName;
            sFileName += ".mve";

            if (g_pChitin->lAliases.ResolveFileName(sFileName, sMovieFileName) == TRUE) {
                hFindFile = FindFirstFileA(sMovieFileName, &ffd);
                if (hFindFile != INVALID_HANDLE_VALUE) {
                    resolved = TRUE;
                    FindClose(hFindFile);
                    break;
                }
            }
        } while (0);
    }

    return resolved;
}

// 0x43F230
void CBaldurProjector::PlayMovieInternal(const CResRef& cResRef, BOOL bAsynchThread)
{
    EnterCriticalSection(&(g_pChitin->field_3AC));

    if (cResRef != "") {
        if (m_hBink != NULL) {
            m_pfnBinkClose(m_hBink);
            m_hBink = NULL;
            field_64E = "";
        }

        field_144 = 1;
        field_145 = 0;

        CString sMovieFileName("");
        BOOL resolved = ResolveMovieFileName(cResRef, sMovieFileName);

        field_652 = cResRef;

        if (resolved) {
            field_64E = sMovieFileName;

            if (cResRef == "BISLOGO") {
                g_pBaldurChitin->AddPlayedMovie(cResRef);
                g_pBaldurChitin->AddPlayedMovie(CResRef("WOTC"));
            } else if (cResRef == "INTRO" || cResRef == "MIDDLE" || cResRef == "END") {
                field_144 = 0;

                CString sMovie;
                cResRef.CopyToString(sMovie);

                if (GetPrivateProfileIntA("Movies", sMovie, FALSE, g_pBaldurChitin->GetConfigFileName())) {
                    field_145 = 1;
                }

                g_pBaldurChitin->AddPlayedMovie(cResRef);
            } else if (cResRef == "CREDITS" || cResRef == "ECREDIT") {
                field_145 = 1;
            }

            if (g_pChitin->pActiveEngine == this) {
                EngineDeactivated();
                EngineActivated();
            } else {
                SelectEngine(this);
            }
        } else {
            field_145 = 1;
        }
    }

    LeaveCriticalSection(&g_pChitin->field_3AC);
}

// 0x43F460
void CBaldurProjector::PlayMovieNext(const CResRef& cResRef)
{
    CResRef* temp = new CResRef();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurProjector.cpp
    // __LINE__: 786
    UTIL_ASSERT(temp != NULL);

    *temp = cResRef;

    m_lMovies.AddTail(temp);
}

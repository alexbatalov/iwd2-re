#include "CBaldurProjector.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x8CFF2C
BOOLEAN CBaldurProjector::byte_8CFF2C;

// NOTE: Not sure if it's actually part of class. There is a strange mix of
// `this` vs. instance obtained from global `g_pBaldurChitin`.
//
// 0x43E300
void CBaldurProjector::sub_43E300(HBINK bnk)
{
    LPDIRECTDRAWSURFACE pSurface = g_pChitin->pActiveEngine->pVidMode->pSurfaces[CVIDINF_SURFACE_BACK];

    DDSURFACEDESC surfaceDesc;
    surfaceDesc.dwSize = sizeof(surfaceDesc);

    int nType = m_pfnBinkDDSurfaceType(pSurface);

    int nDestX = (CVideo::SCREENWIDTH - bnk->width) / 2;
    int nDestY = (CVideo::SCREENHEIGHT - bnk->height) / 2;

    if (nDestX >= 0 && nDestY >= 0) {
        if (field_65A > 0) {
            field_65A--;
            g_pChitin->pActiveEngine->pVidMode->EraseScreen(CVIDINF_SURFACE_BACK, RGB(0, 0, 0));
        }

        // TODO: Incomplete (subtitles).

        m_pfnBinkDoFrame(bnk);

        do {
            if (pSurface->Lock(NULL, &surfaceDesc, DDLOCK_WAIT, NULL) == DDERR_SURFACELOST) {
                if (pSurface->Restore() == DD_OK) {
                    continue;
                } else {
                    break;
                }
            }

            m_pfnBinkCopyToBuffer(bnk,
                surfaceDesc.lpSurface,
                surfaceDesc.lPitch,
                bnk->height,
                nDestX,
                nDestY,
                nType | 0xF0000000);

            pSurface->Unlock(surfaceDesc.lpSurface);

            g_pChitin->pActiveEngine->pVidMode->Flip(FALSE);
        } while (0);

        if (bnk->frame_num != bnk->frames) {
            m_pfnBinkNextFrame(bnk);
        }
    }
}

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
    m_bSelectEngine = FALSE;
    field_147 = 0;

    field_14A.SetResRef(CResRef("NORMAL"), g_pChitin->field_2EC, 1);
    field_14A.SetColor(0xFFFFFF, 0, 0);
    field_14A.RegisterFont();
    m_sCurrentMovieFileName = "";

    m_hBink = NULL;
    m_currentMovieResRef = "";
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
    m_bThreadPriorityChanged = FALSE;
    m_nPrevThreadPriority = 1;

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

// 0x49FC40
BOOL CBaldurProjector::CheckMouseLButton()
{
    return TRUE;
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
        m_hBink = NULL;
        field_14A.Unload();
    }

    // TODO: Incomplete. Destroying some global object and surface, probably
    // related to subtitles.

    m_sCurrentMovieFileName = "";

    if (m_hBinkDLL != NULL) {
        FreeLibrary(m_hBinkDLL);
        m_hBinkDLL = NULL;
    }

    LeaveCriticalSection(&(g_pChitin->field_3AC));
}

// 0x43EC20
void CBaldurProjector::EngineActivated()
{
    if (m_hBinkDLL == NULL) {
        SelectEngine(pLastEngine);
        return;
    }

    EnterCriticalSection(&(g_pChitin->field_3AC));

    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }

        if (m_hBink != NULL) {
            m_pfnBinkClose(m_hBink);
            m_hBink = NULL;
        }
    }

    // TODO: Incomplete.

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        SelectEngine(pLastEngine);
        LeaveCriticalSection(&(g_pChitin->field_3AC));
        return;
    }

    g_pBaldurChitin->cSoundMixer.StartSong(-1, 5);

    if (m_hBink == NULL) {
        m_pfnBinkSetSoundSystem(m_pfnBinkOpenDirectSound, reinterpret_cast<unsigned int>(pSoundMixer->m_pDirectSound));
        m_hBink = m_pfnBinkOpen(m_sCurrentMovieFileName, 0x4000);

        if (m_hBink == NULL) {
            char* error = m_pfnBinkGetError();
            SelectEngine(pLastEngine);
            LeaveCriticalSection(&(g_pChitin->field_3AC));
            return;
        }

        m_pfnBinkSetSoundOnOff(m_hBink, 1);
        m_pfnBinkSetVolume(m_hBink, 0, 32767 * g_pBaldurChitin->GetObjectGame()->m_cOptions.m_nVolumeMovie / 100);

        m_nPrevThreadPriority = GetThreadPriority(GetCurrentThread());
        m_bThreadPriorityChanged = SetThreadPriority(GetCurrentThread(), 15);

        if (g_pBaldurChitin->GetObjectGame()->m_cOptions.m_bDisplayMovieSubtitles) {
            // TODO: Incomplete.
        }
    }

    pDimm->Suspend();
    pVidMode->m_bPointerEnabled = FALSE;
    field_65A = 4;
    g_pChitin->pActiveEngine->pVidMode->EraseScreen(CVIDINF_SURFACE_BACK, RGB(0, 0, 0));

    LeaveCriticalSection(&(g_pChitin->field_3AC));
}

// 0x43EED0
void CBaldurProjector::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    if (m_bThreadPriorityChanged == TRUE) {
        SetThreadPriority(GetCurrentThread(), m_nPrevThreadPriority);
    }

    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
        EnterCriticalSection(&(g_pChitin->field_3AC));

        if (m_hBink != NULL) {
            while (m_pfnBinkWait(m_hBink)) {
            }

            m_pfnBinkClose(m_hBink);
            m_hBink = NULL;
        }

        // TODO: Incomplete.

        pDimm->Resume();
        pVidMode->m_bPointerEnabled = TRUE;

        LeaveCriticalSection(&(g_pChitin->field_3AC));
    }
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
            m_sCurrentMovieFileName = "";
        }

        field_144 = 1;
        field_145 = 0;

        CString sMovieFileName("");
        BOOL resolved = ResolveMovieFileName(cResRef, sMovieFileName);

        m_currentMovieResRef = cResRef;

        if (resolved) {
            m_sCurrentMovieFileName = sMovieFileName;

            if (cResRef == "BISLOGO") {
                g_pBaldurChitin->AddPlayedMovie(cResRef);
                g_pBaldurChitin->AddPlayedMovie(CResRef("WOTC"));
            } else if (cResRef == "INTRO" || cResRef == "MIDDLE" || cResRef == "END") {
                field_144 = 0;

                CString sMovie;
                cResRef.CopyToString(sMovie);

                if (GetPrivateProfileIntA("Movies", sMovie, FALSE, g_pBaldurChitin->GetIniFileName())) {
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

// 0x43F4C0
void CBaldurProjector::TimerAsynchronousUpdate()
{
    EnterCriticalSection(&(g_pChitin->field_3AC));

    if (m_bSelectEngine) {
        m_bSelectEngine = FALSE;

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()) {
            // TODO: Incomplete.
        }

        if (g_pChitin->cNetwork.GetSessionHosting() == 1
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            // TODO: Incomplete.
        }

        SelectEngine(pLastEngine);
    }

    if (g_pChitin->pActiveEngine == this && !m_bSelectEngine) {
        BOOLEAN v1 = byte_8CFF2C && m_bDeactivateEngine;
        BOOLEAN v2 = (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                         || g_pChitin->cNetwork.GetServiceProvider() == -1)
            && (field_144 || field_145) && m_bDeactivateEngine;

        if (m_hBink != NULL) {
            if (v1 || v2 || m_hBink->frame_num == m_hBink->frames) {
                byte_8CFF2C = FALSE;

                if (m_hBink != NULL) {
                    m_pfnBinkClose(m_hBink);
                    m_hBink = NULL;
                }

                if (field_145) {
                    field_145 = 0;
                }

                m_bDeactivateEngine = FALSE;

                if (!m_lMovies.IsEmpty()) {
                    do {
                        CResRef* pMovieResRef = m_lMovies.RemoveHead();
                        if (pMovieResRef != NULL) {
                            PlayMovieInternal(*pMovieResRef, FALSE);
                            delete pMovieResRef;
                        }
                    } while (m_hBink == NULL && !m_lMovies.IsEmpty());
                }

                if (m_hBink == NULL) {
                    m_bSelectEngine = TRUE;
                }
            } else {
                if (m_pfnBinkWait(m_hBink) == 0) {
                    sub_43E300(m_hBink);
                }
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_3AC));
}

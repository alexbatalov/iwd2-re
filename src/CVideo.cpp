#include "CVideo.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CWarp.h"

// 0x85DE2C
const USHORT CVideo::word_85DE2C = 16;

// 0x85DE2E
const USHORT CVideo::word_85DE2E = 32;

// #guess
// 0x8BA318
DWORD CVideo::FPS = 60;

// 0x8BA31C
USHORT CVideo::SCREENWIDTH = 800;

// 0x8BA31E
USHORT CVideo::SCREENHEIGHT = 600;

// #guess
// 0x794F10
static HRESULT WINAPI EnumDisplayModesCallback(LPDDSURFACEDESC lpDDSD, LPVOID lpContext)
{
    CVideo* video = reinterpret_cast<CVideo*>(lpContext);

    if (lpDDSD->dwWidth == CVideo::SCREENWIDTH && lpDDSD->dwHeight == CVideo::SCREENHEIGHT) {
        switch (lpDDSD->ddpfPixelFormat.dwRGBBitCount) {
        case 16:
            video->m_bSupports16bpp = TRUE;
            if (lpDDSD->dwMipMapCount <= CVideo::FPS) {
                if (lpDDSD->dwMipMapCount > video->m_dwMipMapCount16) {
                    video->m_dwMipMapCount16 = lpDDSD->dwMipMapCount;
                }
            }
            break;
        case 24:
            video->m_bSupports24bpp = TRUE;
            if (lpDDSD->dwMipMapCount <= CVideo::FPS) {
                if (lpDDSD->dwMipMapCount > video->m_dwMipMapCount24) {
                    video->m_dwMipMapCount24 = lpDDSD->dwMipMapCount;
                }
            }
            break;
        case 32:
            video->m_bSupports32bpp = TRUE;
            if (lpDDSD->dwMipMapCount <= CVideo::FPS) {
                if (lpDDSD->dwMipMapCount > video->m_dwMipMapCount32) {
                    video->m_dwMipMapCount32 = lpDDSD->dwMipMapCount;
                }
            }
            break;
        }
    }

    return DDENUMRET_OK;
}

// 0x794FC0
CVideo::CVideo()
{
    field_163 = 0;
    m_pDirectDraw = NULL;
    m_pDirectDraw2 = NULL;
    m_pDirectDrawClipper = NULL;
    m_nBpp = 16;
    m_nNextBpp = 16;
    m_bSupports16bpp = FALSE;
    m_bSupports24bpp = FALSE;
    m_bSupports32bpp = FALSE;
    field_162 = 0;
    m_dwMipMapCount16 = 0;
    m_dwMipMapCount24 = 0;
    m_dwMipMapCount32 = 0;
    m_pVidModes[0] = NULL;
    m_pVidModes[1] = NULL;
    m_pVidModes[2] = NULL;
    m_pVidModes[3] = NULL;
    m_pCurrentVidMode = NULL;
    field_12A = 0;
    field_12E = 0;
    m_bIs3dAccelerated = FALSE;
    field_136 = 6408;
    field_13A = 0;
    field_13E = 0;
    field_114 = "";
    field_11C = -1;
    field_11E = 0;
    m_doubleSizeData = NULL;
    m_doubleSizeDataSize = 0;
}

// 0x7950A0
CVideo::~CVideo()
{
    for (int k = 0; k < 4; k++) {
        if (m_pVidModes[k] != NULL) {
            delete m_pVidModes[k];
            m_pVidModes[k] = NULL;
        }
    }

    if (m_doubleSizeData != NULL) {
        operator delete(m_doubleSizeData);
        m_doubleSizeData = NULL;
    }
}

// 0x7950F0
void CVideo::SetDoubleSizeData(size_t size)
{
    if (m_doubleSizeData == NULL || size > m_doubleSizeDataSize) {
        if (m_doubleSizeData != NULL) {
            operator delete(m_doubleSizeData);
        }

        m_doubleSizeDataSize = size;
        m_doubleSizeData = operator new(size);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 230
        UTIL_ASSERT(m_doubleSizeData != NULL);
    }
}

// 0x795150
void CVideo::ResetDoubleSizeData()
{
    if (m_doubleSizeData != NULL) {
        operator delete(m_doubleSizeData);
    }

    field_114 = "";
    field_11C = -1;
    field_11E = 0;
    m_doubleSizeData = NULL;
    m_doubleSizeDataSize = 0;
}

// 0x7951B0
CVidMode* CVideo::GetVidMode(int a1)
{
    if (m_pVidModes[a1] == NULL) {
        if (a1 == 0) {
            m_pVidModes[a1] = new CVidInf();
        }
    }
    return m_pVidModes[a1];
}

// 0x795230
void CVideo::CleanUp()
{
    if (m_bIs3dAccelerated) {
        CleanUp3d();
    } else {
        if (m_pCurrentVidMode != NULL) {
            m_pCurrentVidMode->DeactivateVideoMode(0);
            m_pCurrentVidMode = NULL;
        }

        if (m_pDirectDrawClipper != NULL) {
            m_pDirectDrawClipper->Release();
            m_pDirectDrawClipper = NULL;
        }

        if (m_pDirectDraw2 != NULL) {
            if (g_pChitin->m_bFullscreen) {
                m_pDirectDraw2->RestoreDisplayMode();
            }
            m_pDirectDraw2->Release();
            m_pDirectDraw2 = NULL;
        }

        if (m_pDirectDraw != NULL) {
            m_pDirectDraw->Release();
            m_pDirectDraw = NULL;
        }
    }
}

// 0x7952C0
BOOL CVideo::Initialize(HWND hWnd, BOOLEAN bFullscreen)
{
    HRESULT result;

    result = DirectDrawCreate(NULL, &m_pDirectDraw, NULL);
    if (result != DD_OK) {
        return FALSE;
    }

    m_hWnd = hWnd;

    if (bFullscreen) {
        result = m_pDirectDraw->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
        if (result != DD_OK) {
            switch (result) {
            case DDERR_INVALIDOBJECT:
            case DDERR_INVALIDPARAMS:
            case DDERR_EXCLUSIVEMODEALREADYSET:
            case DDERR_OUTOFMEMORY:
            case DDERR_HWNDALREADYSET:
            case DDERR_HWNDSUBCLASSED:
                if (1) {
                    CString msg;
                    msg.LoadStringA(g_pChitin->GetIDSExclusiveMode());
                    MessageBoxA(NULL, msg, CChitin::m_sGameName, 0);
                }
                return FALSE;
            default:
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                // __LINE__: 431
                UTIL_ASSERT(FALSE);
            }
        }

        result = m_pDirectDraw->QueryInterface(IID_IDirectDraw2, reinterpret_cast<LPVOID*>(&m_pDirectDraw2));
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 444
        UTIL_ASSERT(result == DD_OK);

        field_162 = 1;
        field_163 = 1;

        DDSURFACEDESC ddsd = { 0 };
        ddsd.dwSize = sizeof(ddsd);
        ddsd.dwWidth = SCREENWIDTH;
        ddsd.dwHeight = SCREENHEIGHT;
        m_pDirectDraw2->EnumDisplayModes(0, &ddsd, this, EnumDisplayModesCallback);

        if (max(m_dwMipMapCount32, max(m_dwMipMapCount24, m_dwMipMapCount16)) < 60) {
            CVideo::FPS = 60;
        } else {
            CVideo::FPS = max(m_dwMipMapCount32, max(m_dwMipMapCount24, m_dwMipMapCount16));
        }
    } else {
        result = m_pDirectDraw->SetCooperativeLevel(NULL, DDSCL_NORMAL);
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 460
        UTIL_ASSERT(result == DD_OK);

        result = m_pDirectDraw->QueryInterface(IID_IDirectDraw2, reinterpret_cast<LPVOID*>(&m_pDirectDraw2));
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 462
        UTIL_ASSERT(result == DD_OK);

        field_162 = 0;

        DDSURFACEDESC ddsd = { 0 };
        ddsd.dwSize = sizeof(ddsd);
        ddsd.dwWidth = SCREENWIDTH;
        ddsd.dwHeight = SCREENHEIGHT;
        m_pDirectDraw2->EnumDisplayModes(0, &ddsd, this, EnumDisplayModesCallback);

        if (m_pDirectDraw2->CreateClipper(0, &m_pDirectDrawClipper, NULL) != DD_OK) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
            // __LINE__: 482
            UTIL_ASSERT(FALSE);
        }

        if (m_pDirectDrawClipper->SetHWnd(0, hWnd) != DD_OK) {
            m_pDirectDrawClipper->Release();
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
            // __LINE__: 491
            UTIL_ASSERT(FALSE);
        }
    }

    if (m_pCurrentVidMode != NULL) {
        m_pCurrentVidMode->ActivateVideoMode(NULL, hWnd, bFullscreen);

        cVidBlitter.Init();
        cVidBlitter.field_E6 = 0;
    }

    return TRUE;
}

// 0x795630
void CVideo::SetExclusiveMode(unsigned char a2)
{
    if (a2 == 0) {
        if (field_162 == 1 && field_163 == 1) {
            if (m_pDirectDraw2 != NULL) {
                HRESULT result = m_pDirectDraw2->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                // __LINE__: 536
                UTIL_ASSERT(result == DD_OK);

                field_162 = 0;
            }
        }
    } else if (a2 == 1) {
        if (field_162 == 0 && field_163 == 1) {
            if (m_hWnd != NULL) {
                HRESULT result = m_pDirectDraw2->SetCooperativeLevel(m_hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                // __LINE__: 544
                UTIL_ASSERT(result == DD_OK);
            }
            field_162 = 1;
        }
    }
}

// 0x795700
void CVideo::ChangeBppValue()
{
    if (!m_bIs3dAccelerated) {
        if (g_pChitin->m_bFullscreen) {
            g_pChitin->field_F8 = 1;
            if (g_pChitin->pActiveEngine != NULL) {
                g_pChitin->pActiveEngine->EngineDeactivated();
            }
            g_pChitin->field_E0 = 1;

            CVidMode* pVidMode = m_pCurrentVidMode;

            CleanUp();

            switch (m_nNextBpp) {
            case 16:
            case 24:
            case 32:
                m_nBpp = m_nNextBpp;
                break;
            default:
                m_nBpp = 16;
                m_nNextBpp = 16;
                break;
            }

            if (g_pChitin != NULL) {
                g_pChitin->SaveBitsPerPixel(m_nBpp);
            }

            m_pCurrentVidMode = pVidMode;

            if (Initialize(g_pChitin->GetWnd()->GetSafeHwnd(), g_pChitin->m_bFullscreen)) {
                g_pChitin->Resume();
                g_pChitin->field_F8 = 0;

                if (g_pChitin->pActiveEngine != NULL) {
                    g_pChitin->pActiveEngine->EngineActivated();
                }
            } else {
                g_pChitin->ShutDown(-1, NULL, NULL);
            }
        } else {
            g_pChitin->SaveBitsPerPixel(m_nNextBpp);
            m_nNextBpp = m_nBpp;
        }
    }
}

// 0x795820
BOOL CVideo::SetNextBpp(USHORT nNewBpp)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 693
    UTIL_ASSERT(nNewBpp == 16 || nNewBpp == 24 || nNewBpp == 32);

    if (nNewBpp != m_nBpp) {
        switch (nNewBpp) {
        case 16:
            if (m_bSupports16bpp) {
                m_nNextBpp = nNewBpp;
            }
            return TRUE;
        case 24:
            if (m_bSupports24bpp) {
                m_nNextBpp = nNewBpp;
            }
            return TRUE;
        case 32:
            if (m_bSupports32bpp) {
                m_nNextBpp = nNewBpp;
            }
            return TRUE;
        default:
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
            // __LINE__: 700
            UTIL_ASSERT(FALSE);
        }
    }

    return TRUE;
}

// 0x7958B0
void CVideo::SetBitsPerPixels(USHORT nNewBpp, BOOLEAN a3)
{
    switch (nNewBpp) {
    case 16:
    case 24:
    case 32:
        m_nBpp = nNewBpp;
        m_nNextBpp = nNewBpp;
        break;
    default:
        m_nBpp = 16;
        m_nNextBpp = 16;
        break;
    }

    if (a3) {
        if (g_pChitin != NULL) {
            g_pChitin->SaveBitsPerPixel(m_nBpp);
        }
    }
}

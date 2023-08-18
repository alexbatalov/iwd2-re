#include "CVidCell.h"

#include "CUtil.h"
#include "CVidMode.h"
#include "CVidPoly.h"

// 0x9064F4
BOOL CVidCell::TRANSLUCENT_BLTS_ON;

// 0x8BAC8C
BOOL CVidCell::TRANSLUCENT_SHADOWS_ON = TRUE;

// #binary-identical
// 0x7ACD70
CVidCell::CVidCell()
{
    m_nCurrentFrame = 0;
    m_nCurrentSequence = 0;
    m_bPaletteChanged = FALSE;
    m_pFrame = NULL;
    m_bDoubleSize = FALSE;
    field_C8 = 1;
    m_bShadowOn = TRUE;
}

// 0x7ACE50
CVidCell::CVidCell(CResRef cNewResRef, BOOL bDoubleSize)
{
    // NOTE: Uninline.
    SetResRef(cNewResRef, bDoubleSize, TRUE);

    field_C8 = 1;
    m_nCurrentFrame = 0;
    m_nCurrentSequence = 0;
    m_bPaletteChanged = FALSE;
    m_pFrame = NULL;
    m_bShadowOn = TRUE;
}

// 0x7AD0F0
CVidCell::~CVidCell()
{
    for (int index = 0; index < CVidPalette::NUM_RANGES; index++) {
        if (m_paletteAffects.pRangeTints[index] != NULL) {
            delete m_paletteAffects.pRangeTints[index];
        }

        if (m_paletteAffects.pRangeAdds[index] != NULL) {
            delete m_paletteAffects.pRangeAdds[index];
        }

        if (m_paletteAffects.pRangeLights[index] != NULL) {
            delete m_paletteAffects.pRangeLights[index];
        }
    }
}

// #binary-identical
// 0x7AD280
void CVidCell::AddRangeAffect(USHORT nAffectType, USHORT nRangeId, COLORREF rgbAffectColor, BYTE pulsePeriod)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 523
    UTIL_ASSERT(nRangeId < CVidPalette::NUM_RANGES);

    switch (nAffectType) {
    case 0:
        if (m_paletteAffects.pRangeTints[nRangeId] == NULL) {
            m_paletteAffects.pRangeTints[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeTints[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeTintPeriods[nRangeId] = pulsePeriod;
        break;
    case 1:
    case 3:
        if (m_paletteAffects.pRangeAdds[nRangeId] == NULL) {
            m_paletteAffects.pRangeAdds[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeAdds[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeAddPeriods[nRangeId] = pulsePeriod;
        break;
    case 2:
        if (m_paletteAffects.pRangeLights[nRangeId] == NULL) {
            m_paletteAffects.pRangeLights[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeLights[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeLightPeriods[nRangeId] = pulsePeriod;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 523
        UTIL_ASSERT(FALSE);
    }
}

// #binary-identical
// 0x7AD3A0
void CVidCell::DeleteResPaletteAffect()
{
    if (m_paletteAffects.pRangeTints[0] != NULL) {
        delete m_paletteAffects.pRangeTints[0];
        m_paletteAffects.pRangeTints[0] = NULL;
        m_paletteAffects.aRangeTintPeriods[0] = 0;
    }

    if (m_paletteAffects.pRangeAdds[0] != NULL) {
        delete m_paletteAffects.pRangeAdds[0];
        m_paletteAffects.pRangeAdds[0] = NULL;
        m_paletteAffects.aRangeAddPeriods[0] = 0;
    }

    if (m_paletteAffects.pRangeLights[0] != NULL) {
        delete m_paletteAffects.pRangeLights[0];
        m_paletteAffects.pRangeLights[0] = NULL;
        m_paletteAffects.aRangeLightPeriods[0] = 0;
    }
}

// #binary-identical
// 0x7AD400
void CVidCell::DeleteRangeAffects(USHORT nRangeId)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 635
    UTIL_ASSERT(nRangeId < CVidPalette::NUM_RANGES);

    if (m_paletteAffects.pRangeTints[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeTints[nRangeId];
        m_paletteAffects.pRangeTints[nRangeId] = NULL;
    }

    if (m_paletteAffects.pRangeAdds[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeAdds[nRangeId];
        m_paletteAffects.pRangeAdds[nRangeId] = NULL;
    }

    if (m_paletteAffects.pRangeLights[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeLights[nRangeId];
        m_paletteAffects.pRangeLights[nRangeId] = NULL;
    }
}

// 0x7AD490
BOOL CVidCell::Demand(BOOLEAN& bDemanded)
{
    if (!bDemanded) {
        if (m_header.GetResRef() != "") {
            if (m_header.pRes->m_pBamHeaderCopy != NULL) {
                bDemanded = TRUE;
            }

            if (!bDemanded) {
                if (m_header.pRes->Demand() == NULL) {
                    return FALSE;
                }
            }
        } else {
            if (pRes == NULL) {
                return FALSE;
            }

            if (pRes->m_pBamHeaderCopy != NULL) {
                bDemanded = TRUE;
            }

            if (!bDemanded) {
                if (pRes->Demand() == NULL) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

// 0x7AD520
BOOL CVidCell::GetCurrentCenterPoint(CPoint& ptReference, BOOLEAN bDemanded)
{
    if (pRes == NULL) {
        ptReference.x = 0;
        ptReference.y = 0;
        return FALSE;
    }

    if (!Demand(bDemanded)) {
        ptReference.x = 0;
        ptReference.y = 0;
        return FALSE;
    }

    SHORT nSequence;
    // NOTE: Uninline.
    if (m_nCurrentSequence < GetResBamHeader()->nSequences) {
        nSequence = m_nCurrentSequence;
    } else {
        nSequence = 0;
    }

    SHORT nFrame;
    // NOTE: Uninline.
    if (m_nCurrentFrame < GetResSequences()[nSequence].nFrames) {
        nFrame = m_nCurrentFrame;
    } else {
        if (field_C8) {
            // NOTE: Uninline.
            if (GetResSequences()[nSequence].nFrames > 0) {
                // NOTE: Uninline.
                nFrame = m_nCurrentFrame % GetResSequences()[nSequence].nFrames;
            } else {
                nFrame = 0;
            }
        } else {
            // NOTE: Uninline.
            nFrame = GetResSequences()[nSequence].nFrames - 1;
        }
    }

    if (nFrame < 0) {
        if (field_C8) {
            // FIXME: Repeating calls.
            // NOTE: Lots of inlining.
            if (GetResSequences()[nSequence].nFrames > 0) {
                nFrame = GetResSequences()[nSequence].nFrames + nFrame % GetResSequences()[nSequence].nFrames;
                if (nFrame == GetResSequences()[nSequence].nFrames) {
                    nFrame = 0;
                }
            } else {
                nFrame = 0;
            }
        } else {
            nFrame = 0;
        }
    }

    BOOL bSuccess;

    // NOTE: Uninline.
    FRAMEENTRY* pFrame = GetResFrame(nSequence, nFrame);
    if (pFrame != NULL) {
        ptReference.x = pFrame->nCenterX;
        ptReference.y = pFrame->nCenterY;
        bSuccess = TRUE;
    } else {
        bSuccess = FALSE;
    }

    // NOTE: Uninline.
    Release(bDemanded);

    return bSuccess;
}

// 0x7AD800
BOOL CVidCell::GetCurrentFrameSize(CSize& frameSize, BOOLEAN bDemanded)
{
    if (pRes == NULL) {
        frameSize.cx = 0;
        frameSize.cy = 0;
        return FALSE;
    }

    if (!Demand(bDemanded)) {
        frameSize.cx = 0;
        frameSize.cy = 0;
        return FALSE;
    }

    SHORT nSequence;
    // NOTE: Uninline.
    if (m_nCurrentSequence < GetResBamHeader()->nSequences) {
        nSequence = m_nCurrentSequence;
    } else {
        nSequence = 0;
    }

    SHORT nFrame;
    // NOTE: Uninline.
    if (m_nCurrentFrame < GetResSequences()[nSequence].nFrames) {
        nFrame = m_nCurrentFrame;
    } else {
        if (field_C8) {
            // NOTE: Uninline.
            if (GetResSequences()[nSequence].nFrames > 0) {
                // NOTE: Uninline.
                nFrame = m_nCurrentFrame % GetResSequences()[nSequence].nFrames;
            } else {
                nFrame = 0;
            }
        } else {
            // NOTE: Uninline.
            nFrame = GetResSequences()[nSequence].nFrames - 1;
        }
    }

    if (nFrame < 0) {
        if (field_C8) {
            // FIXME: Repeating calls.
            // NOTE: Lots of inlining.
            if (GetResSequences()[nSequence].nFrames > 0) {
                nFrame = GetResSequences()[nSequence].nFrames + nFrame % GetResSequences()[nSequence].nFrames;
                if (nFrame == GetResSequences()[nSequence].nFrames) {
                    nFrame = 0;
                }
            } else {
                nFrame = 0;
            }
        } else {
            nFrame = 0;
        }
    }

    BOOL bSuccess;

    // NOTE: Uninline.
    FRAMEENTRY* pFrame = GetResFrame(nSequence, nFrame);
    if (pFrame != NULL) {
        frameSize.cx = pFrame->nWidth;
        frameSize.cy = pFrame->nHeight;
        bSuccess = TRUE;
    } else {
        bSuccess = FALSE;
    }

    // NOTE: Uninline.
    Release(bDemanded);

    return bSuccess;
}

// 0x7ADAE0
BYTE CVidCell::GetSequenceLength(WORD nSequence, BOOLEAN bDemanded)
{
    if (!Demand(bDemanded)) {
        return 0;
    }

    BYTE nFrames;
    // NOTE: Uninline.
    if (nSequence < GetResBamHeader()->nSequences) {
        // NOTE: Uninline.
        nFrames = static_cast<BYTE>(GetResSequences()[nSequence].nFrames);
    } else {
        nFrames = 0;
    }

    // NOTE: Uninline.
    Release(bDemanded);

    return nFrames;
}

// 0x7ADBC0
BOOL CVidCell::GetFrameCenterPoint(SHORT nSequence, SHORT nFrame, CSize& ptCtr, BOOLEAN bDemanded)
{
    if (nSequence == -1) {
        nSequence = m_nCurrentSequence;
    }

    if (nFrame == -1) {
        nFrame = m_nCurrentFrame;
        nSequence = m_nCurrentSequence;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1176
    UTIL_ASSERT(pRes != NULL);

    if (!Demand(bDemanded)) {
        return FALSE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1189
    UTIL_ASSERT(nSequence < GetResBamHeader()->nSequences);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1189
    UTIL_ASSERT(nFrame < GetResSequences()[nSequence].nFrames);

    BOOL bSuccess;

    FRAMEENTRY* pFrame = GetResFrame(nSequence, nFrame);
    if (pFrame != NULL) {
        ptCtr.cx = pFrame->nCenterX;
        ptCtr.cy = pFrame->nCenterY;
        bSuccess = TRUE;
    } else {
        bSuccess = FALSE;
    }

    Release(bDemanded);

    return bSuccess;
}

// 0x7ADD80
BOOL CVidCell::GetFrameSize(SHORT nSequence, SHORT nFrame, CSize& frameSize, BOOLEAN bDemanded)
{
    if (nSequence == -1) {
        nSequence = m_nCurrentSequence;
    }

    if (nFrame == -1) {
        nFrame = m_nCurrentFrame;
        nSequence = m_nCurrentSequence;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1258
    UTIL_ASSERT(pRes != NULL);

    if (!Demand(bDemanded)) {
        return FALSE;
    }

    // NOTE: Uninline.
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1271
    UTIL_ASSERT(nSequence < GetResBamHeader()->nSequences);

    // NOTE: Uninline.
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1272
    UTIL_ASSERT(nFrame < GetResSequences()[nSequence].nFrames);

    BOOL bSuccess;

    // NOTE: Uninline.
    FRAMEENTRY* pFrame = GetResFrame(nSequence, nFrame);
    if (pFrame != NULL) {
        frameSize.cx = pFrame->nWidth;
        frameSize.cy = pFrame->nHeight;
        bSuccess = TRUE;
    } else {
        bSuccess = FALSE;
    }

    // NOTE: Uninline.
    Release(bDemanded);

    return bSuccess;
}

// 0x7ADF40
SHORT CVidCell::GetNumberSequences(BOOLEAN bDemanded)
{
    if (pRes == NULL) {
        return 0;
    }

    if (!Demand(bDemanded)) {
        return 0;
    }

    SHORT nSequences = GetResBamHeader()->nSequences;

    Release(bDemanded);

    return nSequences;
}

// #binary-identical
// 0x7ADFE0
BOOL CVidCell::FrameAdvance()
{
    m_nCurrentFrame++;
    return TRUE;
}

// #binary-identical
// 0x7ADFF0
BOOL CVidCell::FrameSet(SHORT nFrame)
{
    m_nCurrentFrame = nFrame;
    return TRUE;
}

// 0x7AE010
BOOL CVidCell::IsEndOfSequence(BOOLEAN bDemanded)
{
    BOOL bResult = FALSE;

    if (pRes == NULL) {
        return TRUE;
    }

    if (!Demand(bDemanded)) {
        return FALSE;
    }

    // NOTE: Uninline.
    if (m_nCurrentSequence < GetResBamHeader()->nSequences) {
        bResult = TRUE;
        // FIXME: Repeating calls.
        // NOTE: Uninline.
        if (m_nCurrentFrame < GetResSequences()[m_nCurrentSequence].nFrames - 1) {
            // NOTE: Uninline.
            if (GetResSequences()[m_nCurrentSequence].nFrames != 0) {
                bResult = FALSE;
            }
        }
    }

    // NOTE: Uninline.
    Release(bDemanded);

    return bResult;
}

// 0x7AE140
void CVidCell::RestoreBackground(INT nFrom, INT nTo, const CRect& rClip)
{
    RECT srcRect;
    srcRect.left = 0;
    srcRect.top = 0;
    srcRect.right = rClip.Width();
    srcRect.bottom = rClip.Height();

    do {
        HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(g_pChitin->GetCurrentVideoMode()->pSurfaces[nTo],
            rClip.left,
            rClip.top,
            g_pChitin->GetCurrentVideoMode()->pSurfaces[nFrom],
            &srcRect,
            DDBLTFAST_WAIT);
        g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
        if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
            break;
        }
    } while (!g_pChitin->field_1932);
}

// 0x7AE210
void CVidCell::RealizePalette(DWORD dwFlags)
{
    if (!m_bPaletteChanged) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 1537
        UTIL_ASSERT(pRes != NULL);

        m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    }

    m_cPalette.Realize(CVidImage::rgbTempPal, g_pChitin->cVideo.m_nBpp, dwFlags, &m_paletteAffects, 255);
}

// #binary-identical
// 0x7AE290
BOOL CVidCell::SequenceSet(SHORT nSequence)
{
    m_nCurrentSequence = nSequence;
    return TRUE;
}

// 0x7AE2B0
void CVidCell::SetPalette(RGBQUAD* pPalette, int nEntries, USHORT nType)
{
    if (pPalette != NULL) {
        m_cPalette.SetPalette(pPalette, nEntries, nType);
        m_bPaletteChanged = TRUE;
    } else {
        m_cPalette.SetPalette(NULL, 0, CVidPalette::TYPE_RESOURCE);
        m_bPaletteChanged = FALSE;
    }
}

// 0x7AE300
void CVidCell::SetPalette(const CVidPalette& cPalette)
{
    m_cPalette.SetPalette(cPalette);
    m_bPaletteChanged = TRUE;
}

// #binary-identical
// 0x7AE320
void CVidCell::AddResPaletteAffect(USHORT nAffectType, COLORREF rgbAffectColor, BYTE pulsePeriod)
{
    switch (nAffectType) {
    case 0:
        if (m_paletteAffects.pRangeTints[0] == NULL) {
            m_paletteAffects.pRangeTints[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeTints[0] = rgbAffectColor;
        m_paletteAffects.aRangeTintPeriods[0] = pulsePeriod;
        break;
    case 1:
    case 3:
        if (m_paletteAffects.pRangeAdds[0] == NULL) {
            m_paletteAffects.pRangeAdds[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeAdds[0] = rgbAffectColor;
        m_paletteAffects.aRangeAddPeriods[0] = pulsePeriod;
        break;
    case 2:
        if (m_paletteAffects.pRangeLights[0] == NULL) {
            m_paletteAffects.pRangeLights[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeLights[0] = rgbAffectColor;
        m_paletteAffects.aRangeLightPeriods[0] = pulsePeriod;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 1704
        UTIL_ASSERT(FALSE);
    }
}

// 0x7AE3F0
void CVidCell::StoreBackground(INT nFrom, INT nTo, INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered)
{
    if (GetFrame(FALSE)) {
        rStorage.left = x - m_pFrame->nCenterX;
        rStorage.top = y - m_pFrame->nCenterY;

        rStorage.left = x - m_pFrame->nCenterX;
        rStorage.top = y - m_pFrame->nCenterY;

        if (bNumbered) {
            rStorage.right = max(rStorage.left + m_pFrame->nWidth, rStorage.left + m_pFrame->nCenterX + 16);
            rStorage.bottom = max(rStorage.top + m_pFrame->nHeight, rStorage.top + m_pFrame->nCenterY + 16);
        } else {
            rStorage.right = rStorage.left + m_pFrame->nWidth;
            rStorage.bottom = rStorage.top + m_pFrame->nHeight;
        }

        // NOTE: Looks like intersection.
        if (rStorage.left < rClip.left) {
            rStorage.left = rClip.left;
        }

        if (rStorage.top < rClip.top) {
            rStorage.top = rClip.top;
        }

        if (rStorage.right >= rClip.right) {
            rStorage.right = rClip.right;
        }

        if (rStorage.bottom >= rClip.bottom) {
            rStorage.bottom = rClip.bottom;
        }

        if (rStorage.left < rStorage.right && rStorage.top < rStorage.bottom) {
            do {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(g_pChitin->GetCurrentVideoMode()->pSurfaces[nTo],
                    0,
                    0,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[nFrom],
                    &rStorage,
                    DDBLTFAST_WAIT);
                g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            } while (!g_pChitin->field_1932);
        }
    }
}

// 0x7AE590
void CVidCell::SuppressTint(SHORT nRange)
{
    m_paletteAffects.suppressTints |= 1 << nRange;
}

// 0x7AE5B0
void CVidCell::UnsuppressTint(SHORT nRange)
{
    m_paletteAffects.suppressTints &= ~(1 << nRange);
}

// 0x7AE5D0
BOOL CVidCell::Render(WORD* pSurface, LONG lPitch, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransVal)
{
    BOOL bSuccess;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 1902
    UTIL_ASSERT(!((dwFlags & CVIDIMG_TRANSLUCENT) && (dwFlags & CVIDCELL_BRIGHTEST)));

    if (m_pFrame == NULL) {
        if (!GetFrame(FALSE)) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
            // __LINE__: 1913
            UTIL_ASSERT_MSG(FALSE, GetResRef().GetResRefStr() + ".BAM is corrupted (GetFrame() failed)");
        }
    }

    if ((dwFlags & 0x200) != 0 && TRANSLUCENT_BLTS_ON) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 1902
        UTIL_ASSERT(nTransVal >= 0);

        switch (g_pChitin->cVideo.m_nBpp) {
        case 16:
            bSuccess = sub_7B49D0(pSurface
                    + lPitch / 2 * (nRefPointY - m_pFrame->nCenterY)
                    + (nRefPointX - m_pFrame->nCenterX),
                lPitch,
                dwFlags);
            break;
        case 24:
            bSuccess = sub_7D0C60(reinterpret_cast<BYTE*>(pSurface)
                    + lPitch * (nRefPointY - m_pFrame->nCenterY)
                    + 3 * (nRefPointX - m_pFrame->nCenterX),
                lPitch,
                dwFlags);
            break;
        case 32:
            bSuccess = sub_7D1190(reinterpret_cast<DWORD*>(pSurface)
                    + lPitch / 4 * (nRefPointY - m_pFrame->nCenterY)
                    + (nRefPointX - m_pFrame->nCenterX),
                lPitch,
                dwFlags);
            break;
        default:
            bSuccess = FALSE;
            break;
        }
    } else {
        if ((dwFlags & CVIDIMG_TRANSLUCENT) != 0) {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
            // __LINE__: 1954
            UTIL_ASSERT(nTransVal >= 0);

            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AFED0(pSurface
                        + lPitch / 2 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags,
                    nTransVal);
                break;
            case 24:
                bSuccess = sub_7CF8D0(reinterpret_cast<BYTE*>(pSurface)
                        + lPitch * (nRefPointY - m_pFrame->nCenterY)
                        + 3 * (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags,
                    nTransVal);
                break;
            case 32:
                bSuccess = sub_7D0950(reinterpret_cast<DWORD*>(pSurface)
                        + lPitch / 4 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags,
                    nTransVal);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        } else if ((dwFlags & 0x8) != 0) {
            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AFB50(pSurface
                        + lPitch / 2 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 24:
                bSuccess = sub_7CF650(reinterpret_cast<BYTE*>(pSurface)
                        + lPitch * (nRefPointY - m_pFrame->nCenterY)
                        + 3 * (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 32:
                bSuccess = sub_7D0730(reinterpret_cast<DWORD*>(pSurface)
                        + lPitch / 4 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        } else if ((dwFlags & 0x4) != 0 && CVidCell::TRANSLUCENT_SHADOWS_ON) {
            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AF8A0(pSurface
                        + lPitch / 2 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 24:
                bSuccess = sub_7CF3F0(reinterpret_cast<BYTE*>(pSurface)
                        + lPitch * (nRefPointY - m_pFrame->nCenterY)
                        + 3 * (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 32:
                bSuccess = sub_7D0470(reinterpret_cast<DWORD*>(pSurface)
                        + lPitch / 4 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        } else {
            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AF1C0(pSurface
                        + lPitch / 2 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 24:
                bSuccess = sub_7CECD0(reinterpret_cast<BYTE*>(pSurface)
                        + lPitch * (nRefPointY - m_pFrame->nCenterY)
                        + 3 * (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags);
                break;
            case 32:
                bSuccess = Blt8To32(reinterpret_cast<DWORD*>(pSurface)
                        + lPitch / 4 * (nRefPointY - m_pFrame->nCenterY)
                        + (nRefPointX - m_pFrame->nCenterX),
                    lPitch,
                    dwFlags,
                    255);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        }
    }

    pRes->Release();
    m_pFrame = NULL;

    return bSuccess;
}

// 0x7AEAD0
BOOL CVidCell::Render(INT nSurface, int x, int y, const CRect& rClip, CVidPoly* pClipPoly, int nPolys, DWORD dwFlags, int nTransVal)
{
    BOOL bSuccess;

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return Render3d(x, y, rClip, pClipPoly, nPolys, dwFlags | 0x1, nTransVal, 0);
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 2065
    UTIL_ASSERT(nSurface < g_pChitin->GetCurrentVideoMode()->GetNumSurfaces() && g_pChitin->GetCurrentVideoMode()->pSurfaces[nSurface] != NULL);

    if (m_nFxSurface == -1) {
        if (!g_pChitin->GetCurrentVideoMode()->GetFXSurface(m_nFxSurface, dwFlags)) {
            return FALSE;
        }
    }

    DDCOLORKEY ddck;
    g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface]->GetColorKey(DDCKEY_SRCBLT, &ddck);

    if (m_pFrame == NULL) {
        if (!GetFrame(FALSE)) {
            return FALSE;
        }
    }

    int left = x - m_pFrame->nCenterX;
    int top = y - m_pFrame->nCenterY;
    CRect rSrc(0, 0, m_pFrame->nWidth, m_pFrame->nHeight);
    CRect rDest(left, top, left + m_pFrame->nWidth, top + m_pFrame->nHeight);

    DDSURFACEDESC ddsd;

    if ((dwFlags & CVIDIMG_TRANSLUCENT) || ((dwFlags & 0x4) != 0 && CVidCell::TRANSLUCENT_SHADOWS_ON)) {
        BltBackGroundToFx(g_pChitin->GetCurrentVideoMode()->pSurfaces[nSurface],
            rDest,
            rClip,
            dwFlags);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 2112
        UTIL_ASSERT(m_nFxSurface != -1);

        ddsd.dwSize = sizeof(ddsd);
        if (!g_pChitin->GetCurrentVideoMode()->LockSurface(m_nFxSurface, &ddsd, rSrc)) {
            pRes->Release();
            return FALSE;
        }

        if ((dwFlags & 0x4) != 0) {
            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AF8A0(reinterpret_cast<WORD*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags);
                break;
            case 24:
                bSuccess = sub_7CF3F0(reinterpret_cast<BYTE*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags);
                break;
            case 32:
                bSuccess = sub_7D0470(reinterpret_cast<DWORD*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        } else {
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
            // __LINE__: 2145
            UTIL_ASSERT(nTransVal >= 0);

            switch (g_pChitin->cVideo.m_nBpp) {
            case 16:
                bSuccess = sub_7AFED0(reinterpret_cast<WORD*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags,
                    nTransVal);
                break;
            case 24:
                bSuccess = sub_7CF8D0(reinterpret_cast<BYTE*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags,
                    nTransVal);
                break;
            case 32:
                bSuccess = sub_7D0950(reinterpret_cast<DWORD*>(ddsd.lpSurface),
                    ddsd.lPitch,
                    dwFlags,
                    nTransVal);
                break;
            default:
                bSuccess = FALSE;
                break;
            }
        }
    } else {
        DDBLTFX fx;
        fx.dwSize = sizeof(fx);
        fx.dwFillColor = ddck.dwColorSpaceLowValue;

        g_pChitin->cVideo.cVidBlitter.Blt(g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
            rSrc,
            NULL,
            NULL,
            DDBLT_COLORFILL | DDBLT_WAIT,
            &fx);

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 2180
        UTIL_ASSERT(m_nFxSurface != -1);

        ddsd.dwSize = sizeof(ddsd);
        if (!g_pChitin->GetCurrentVideoMode()->LockSurface(m_nFxSurface, &ddsd, rSrc)) {
            pRes->Release();
            return FALSE;
        }

        switch (g_pChitin->cVideo.m_nBpp) {
        case 16:
            bSuccess = sub_7AF1C0(reinterpret_cast<WORD*>(ddsd.lpSurface),
                ddsd.lPitch,
                dwFlags);
            break;
        case 24:
            bSuccess = sub_7CECD0(reinterpret_cast<BYTE*>(ddsd.lpSurface),
                ddsd.lPitch,
                dwFlags);
            break;
        case 32:
            bSuccess = Blt8To32(reinterpret_cast<DWORD*>(ddsd.lpSurface),
                ddsd.lPitch,
                dwFlags,
                255);
            break;
        default:
            bSuccess = FALSE;
            break;
        }
    }

    if (pClipPoly != NULL) {
        for (int nIndex = 0; nIndex < nPolys; nIndex++) {
            pClipPoly[nIndex].FillPoly(reinterpret_cast<WORD*>(ddsd.lpSurface),
                ddsd.lPitch,
                rSrc,
                ddck.dwColorSpaceLowValue,
                0,
                CPoint(left, top));
        }
    }

    g_pChitin->GetCurrentVideoMode()->UnLockSurface(m_nFxSurface, ddsd.lpSurface);

    if (bSuccess) {
        BltFromFX(g_pChitin->GetCurrentVideoMode()->pSurfaces[nSurface],
            left,
            top,
            rClip,
            dwFlags);
    }

    pRes->Release();
    m_pFrame = NULL;

    return bSuccess;
}

// 0x7AF060
BOOL CVidCell::Render(WORD* pSurface, LONG lPitch, INT nRefPtX, INT nRefPtY, const CRect& rClip, BOOLEAN bDemanded, DWORD dwFlags, const CPoint& ptSource)
{
    if (m_pFrame == NULL) {
        if (!GetFrame(bDemanded)) {
            return FALSE;
        }
    }

    if (pRes == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 2289
        UTIL_ASSERT_MSG(FALSE, "CVidCell::Render m_pFrame = GARBAGE");
    }

    CPoint pt(nRefPtX - m_pFrame->nCenterX, nRefPtY - m_pFrame->nCenterY);

    BOOL bResult;
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        bResult = Blt8To16(pSurface,
            lPitch,
            pt,
            rClip,
            dwFlags,
            ptSource);
        break;
    case 24:
        bResult = Blt8To24(reinterpret_cast<BYTE*>(pSurface),
            lPitch,
            pt,
            rClip,
            dwFlags,
            ptSource);
        break;
    case 32:
        bResult = Blt8To32(reinterpret_cast<DWORD*>(pSurface),
            lPitch,
            pt,
            rClip,
            dwFlags,
            ptSource,
            0);
        break;
    default:
        bResult = FALSE;
        break;
    }

    m_pFrame = NULL;

    if (!bDemanded) {
        pRes->Release();
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 2323
    UTIL_ASSERT(bResult);

    return bResult;
}

// 0x7AF1C0
BOOL CVidCell::sub_7AF1C0(WORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7AF3C0
BOOL CVidCell::Blt8To16(WORD* pSurface, LONG lPitch, const CPoint& pt, const CRect& rClip, DWORD dwFlags, const CPoint& ptSource)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7AF8A0
BOOL CVidCell::sub_7AF8A0(WORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7AFB50
BOOL CVidCell::sub_7AFB50(WORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7AFED0
BOOL CVidCell::sub_7AFED0(WORD* pSurface, LONG lPitch, DWORD dwFlags, INT nTransVal)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7B0490
void CVidCell::BltBackGroundToFx(LPDIRECTDRAWSURFACE pSurface, CRect& rSrc, const CRect& rClip, DWORD dwFlags)
{
    HRESULT hr;

    int destX = 0;
    int destY = 0;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 4908
    UTIL_ASSERT(m_nFxSurface != -1);

    CRect rSrcSurface(rSrc);

    if (rSrcSurface.left < rClip.left) {
        rSrcSurface.left = rClip.left;
        destX = rClip.left - rSrc.left;
    }

    if (rSrcSurface.top < rClip.top) {
        rSrcSurface.top = rClip.top;
        destY = rClip.top - rSrc.top;
    }

    if (rSrcSurface.right >= rClip.right) {
        rSrcSurface.right = rClip.right;
    }

    if (rSrcSurface.bottom >= rClip.bottom) {
        rSrcSurface.bottom = rClip.bottom;
    }

    if ((dwFlags & 0x10) != 0 || (dwFlags & 0x20) != 0) {
        DDBLTFX fx;
        fx.dwSize = sizeof(fx);
        fx.dwDDFX = 0;
        if ((dwFlags & 0x10) != 0) {
            fx.dwDDFX |= DDBLTFX_MIRRORLEFTRIGHT;
        }
        if ((dwFlags & 0x20) != 0) {
            fx.dwDDFX |= DDBLTFX_MIRRORUPDOWN;
        }

        do {
            RECT rDest;
            rDest.left = destX;
            rDest.top = destY;
            rDest.right = destX + rSrc.Width();
            rDest.bottom = destY + rSrc.Height();

            hr = g_pChitin->cVideo.cVidBlitter.Blt(g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                &rDest,
                pSurface,
                &rSrc,
                DDBLT_WAIT | DDBLT_DDFX,
                &fx);
        } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
    } else {
        do {
            hr = g_pChitin->cVideo.cVidBlitter.BltFast(g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                destX,
                destY,
                pSurface,
                rSrcSurface,
                DDBLTFAST_WAIT);
            if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                break;
            }
        } while (!g_pChitin->field_1932);
    }
}

// 0x7B06E0
BOOL CVidCell::BltFromFX(LPDIRECTDRAWSURFACE pSurface, int x, int y, const CRect& rClip, DWORD dwFlags)
{
    HRESULT hr;

    int destX = x;
    int destY = y;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5003
    UTIL_ASSERT(m_nFxSurface != -1);

    CRect rSrcSurface;
    rSrcSurface.left = 0;
    rSrcSurface.top = 0;
    rSrcSurface.right = m_pFrame->nWidth;
    rSrcSurface.bottom = m_pFrame->nHeight;

    if (x < rClip.left) {
        destX = rClip.left;
        rSrcSurface.left = rClip.left - x;
    }

    if (y < rClip.top) {
        destY = rClip.top;
        rSrcSurface.top = rClip.top - y;
    }

    if (x + m_pFrame->nWidth - 1 >= rClip.right) {
        rSrcSurface.right -= x + m_pFrame->nWidth - rClip.right;
    }

    if (y + m_pFrame->nHeight - 1 >= rClip.bottom) {
        rSrcSurface.bottom -= y + m_pFrame->nHeight - rClip.bottom;
    }

    if (rSrcSurface.bottom > rSrcSurface.top && rSrcSurface.right > rSrcSurface.left) {
        if ((dwFlags & 0x10) != 0 || (dwFlags & 0x20) != 0) {
            DDBLTFX fx;
            fx.dwSize = sizeof(fx);
            fx.dwDDFX = 0;
            if ((dwFlags & 0x10) != 0) {
                fx.dwDDFX |= DDBLTFX_MIRRORLEFTRIGHT;
            }
            if ((dwFlags & 0x20) != 0) {
                fx.dwDDFX |= DDBLTFX_MIRRORUPDOWN;
            }

            do {
                RECT rDest;
                rDest.left = destX;
                rDest.top = destY;
                rDest.right = rSrcSurface.right - rSrcSurface.left;
                rDest.bottom = rSrcSurface.bottom - rSrcSurface.top;

                hr = g_pChitin->cVideo.cVidBlitter.Blt(pSurface,
                    &rDest,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                    &rSrcSurface,
                    DDBLT_WAIT | DDBLT_DDFX,
                    &fx);
                g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
            } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
        } else {
            do {
                hr = g_pChitin->cVideo.cVidBlitter.BltFast(pSurface,
                    destX,
                    destY,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                    &rSrcSurface,
                    DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
                g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            } while (!g_pChitin->field_1932);
        }
    }

    return TRUE;
}

// 0x7B0980
BOOL CVidCell::GetFrame(BOOLEAN bDemanded)
{
    if (!bDemanded) {
        if (pRes->Demand() == NULL) {
            return FALSE;
        }
    }

    BAMHEADER* pHeader;
    if (pRes->m_bCacheHeader) {
        pHeader = pRes->m_pBamHeaderCopy;
    } else {
        pHeader = pRes->m_pBamHeader;
    }

    if (!(m_nCurrentSequence < pHeader->nSequences)) {
        m_nCurrentSequence = 0;
    }

    if (!(m_nCurrentFrame < pRes->m_pSequences[m_nCurrentSequence].nFrames)) {
        if (field_C8) {
            if (pRes->m_pSequences[m_nCurrentSequence].nFrames > 0) {
                m_nCurrentFrame = m_nCurrentFrame % pRes->m_pSequences[m_nCurrentSequence].nFrames;
            } else {
                m_nCurrentFrame = 0;
            }
        } else {
            m_nCurrentFrame = pRes->m_pSequences[m_nCurrentSequence].nFrames - 1;
        }
    }

    if (m_nCurrentFrame < 0) {
        if (field_C8) {
            if (pRes->m_pSequences[m_nCurrentSequence].nFrames > 0) {
                m_nCurrentFrame = pRes->m_pSequences[m_nCurrentSequence].nFrames + m_nCurrentFrame % pRes->m_pSequences[m_nCurrentSequence].nFrames;
                if (m_nCurrentFrame == pRes->m_pSequences[m_nCurrentSequence].nFrames) {
                    m_nCurrentFrame = 0;
                }
            } else {
                m_nCurrentFrame = 0;
            }
        } else {
            m_nCurrentFrame = 0;
        }
    }

    m_pFrame = pRes->GetFrame(m_nCurrentSequence, m_nCurrentFrame, m_bDoubleSize);

    return m_pFrame != NULL;
}

// 0x7C4120
void CVidCell::StoreBackground(INT x, INT y, const CRect& rClip, CRect& rStorage, BOOLEAN bNumbered)
{
    if (GetFrame(FALSE)) {
        rStorage.left = x - m_pFrame->nCenterX;
        rStorage.top = y - m_pFrame->nCenterY;

        if (bNumbered) {
            rStorage.right = max(rStorage.left + m_pFrame->nWidth, rStorage.left + m_pFrame->nCenterX + 16);
            rStorage.bottom = max(rStorage.top + m_pFrame->nHeight, rStorage.top + m_pFrame->nCenterY + 16);
        } else {
            rStorage.right = rStorage.left + m_pFrame->nWidth;
            rStorage.bottom = rStorage.top + m_pFrame->nHeight;
        }

        // NOTE: Looks like intersection.
        if (rStorage.left < rClip.left) {
            rStorage.left = rClip.left;
        }

        if (rStorage.top < rClip.top) {
            rStorage.top = rClip.top;
        }

        if (rStorage.right >= rClip.right) {
            rStorage.right = rClip.right;
        }

        if (rStorage.bottom >= rClip.bottom) {
            rStorage.bottom = rClip.bottom;
        }
    } else {
        rStorage.SetRect(0, 0, 0, 0);
    }
}

// 0x7CECD0
BOOL CVidCell::sub_7CECD0(BYTE* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7CEEB0
BOOL CVidCell::Blt8To24(BYTE* pSurface, LONG lPitch, const CPoint& pt, const CRect& rClip, DWORD dwFlags, const CPoint& ptSource)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7CF3F0
BOOL CVidCell::sub_7CF3F0(BYTE* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7CF650
BOOL CVidCell::sub_7CF650(BYTE* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7CF8D0
BOOL CVidCell::sub_7CF8D0(BYTE* pSurface, LONG lPitch, DWORD dwFlags, INT nTransVal)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7CFBC0
BOOL CVidCell::Blt8To32(DWORD* pSurface, LONG lPitch, DWORD dwFlags, INT nTransVal)
{
    int nWidth = m_pFrame->nWidth;
    int nHeight = m_pFrame->nHeight;

    if (nWidth == 0 || nHeight == 0) {
        return TRUE;
    }

    if (!m_bPaletteChanged) {
        m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    }

    m_cPalette.Realize(CVidImage::rgbTempPal, 32, dwFlags, &m_paletteAffects, nTransVal);

    if (!m_bShadowOn) {
        CVidImage::rgbTempPal[CVidPalette::SHADOW_ENTRY] = g_pChitin->GetCurrentVideoMode()->field_24;
    }

    if (g_pChitin->field_174) {
        if (m_nCurrentFrame == 0) {
            for (int index = CVidPalette::SHADOW_ENTRY + 1; index < 256; index++) {
                CVidImage::rgbTempPal[index] = g_pChitin->GetCurrentVideoMode()->ConvertToSurfaceRGB(255);
            }
        }
    }

    BYTE* pFrameData = pRes->GetFrameData(m_pFrame, m_bDoubleSize);
    BAMHEADER* pBamHeader = pRes->m_bCacheHeader
        ? pRes->m_pBamHeaderCopy
        : pRes->m_pBamHeader;
    BYTE nTransparentColor = pBamHeader->nTransparentColor;

    // NOTE: Original code is slightly different, but does the same thing.
    if (pRes->GetCompressed(m_pFrame, m_bDoubleSize)) {
        int nRunLength = 0;
        int pos = 0;
        for (int y = 0; y < nHeight; y++) {
            int nRemainingWidth = nWidth;
            while (nRemainingWidth != 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nRemainingWidth == nRunLength) {
                        pos += 2;

                        pSurface += nRemainingWidth;
                        nRunLength = 0;
                        nRemainingWidth = 0;
                    } else if (nRemainingWidth > nRunLength) {
                        pos += 2;

                        pSurface += nRunLength;
                        nRemainingWidth -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pSurface += nRemainingWidth;
                        nRunLength -= nRemainingWidth;
                        nRemainingWidth = 0;
                    }
                } else {
                    pos++;

                    *pSurface++ = CVidImage::rgbTempPal[nColor];
                    nRemainingWidth--;
                }
            }
            pSurface += lPitch / 4 - nWidth;
        }
    } else {
        for (int y = 0; y < nHeight; y++) {
            for (int x = 0; x < nWidth; x++) {
                BYTE nColor = *pFrameData;
                if (nColor != nTransparentColor) {
                    *pSurface = CVidImage::rgbTempPal[nColor];
                }
                pFrameData++;
                pSurface++;
            }
            pSurface += lPitch / 4 - nWidth;
        }
    }

    return TRUE;
}

// 0x7CFDF0
BOOL CVidCell::Blt8To32(DWORD* pSurface, LONG lPitch, const CPoint& pt, const CRect& rClip, DWORD dwFlags, const CPoint& ptSource, INT nTransVal)
{
    int nBltWidth = m_pFrame->nWidth - ptSource.x;
    int nBltHeight = m_pFrame->nHeight - ptSource.y;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5029
    UTIL_ASSERT(ptSource.x >= 0 && ptSource.y >= 0);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5030
    UTIL_ASSERT(rClip.top >= 0 && rClip.top <= rClip.bottom && rClip.left >= 0 && rClip.left <= rClip.right);

    if (pt.y > rClip.bottom
        || pt.x > rClip.right
        || pt.x + nBltWidth < rClip.left
        || pt.y + nBltHeight < rClip.top) {
        return TRUE;
    }

    BYTE* pFrameData = pRes->GetFrameData(m_pFrame, m_bDoubleSize);
    BAMHEADER* pBamHeader = pRes->m_bCacheHeader
        ? pRes->m_pBamHeaderCopy
        : pRes->m_pBamHeader;
    BYTE nTransparentColor = pBamHeader->nTransparentColor;

    DWORD* pDest = pSurface + lPitch / 4 * pt.y + pt.x;

    // NOTE: Original code is different, but does the same thing.
    if (pRes->GetCompressed(m_pFrame, m_bDoubleSize)) {
        int nWidth = m_pFrame->nWidth;
        int nHeight = m_pFrame->nHeight;
        int nRunLength = 0;
        int pos = 0;

        // Skip src top.
        int nSkipSrcH = ptSource.y;
        while (nSkipSrcH > 0) {
            int nRemainingWidth = nWidth;
            while (nRemainingWidth != 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nRemainingWidth == nRunLength) {
                        pos += 2;

                        nRunLength = 0;
                        nRemainingWidth = 0;
                    } else if (nRemainingWidth > nRunLength) {
                        pos += 2;

                        nRemainingWidth -= nRunLength;
                        nRunLength = 0;
                    } else {
                        nRunLength -= nRemainingWidth;
                        nRemainingWidth = 0;
                    }
                } else {
                    pos++;
                    nRemainingWidth--;
                }
            }
            nSkipSrcH--;
        }

        // Skip dest top.
        int nSkipDestH = max(rClip.top - pt.y, 0);
        while (nSkipDestH > 0) {
            int nRemainingWidth = nWidth;
            while (nRemainingWidth != 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nRemainingWidth == nRunLength) {
                        pos += 2;

                        pDest += nRemainingWidth;
                        nRunLength = 0;
                        nRemainingWidth = 0;
                    } else if (nRemainingWidth > nRunLength) {
                        pos += 2;

                        pDest += nRunLength;
                        nRemainingWidth -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pDest += nRemainingWidth;
                        nRunLength -= nRemainingWidth;
                        nRemainingWidth = 0;
                    }
                } else {
                    pos++;

                    pDest++;
                    nRemainingWidth--;
                }
            }
            pDest += lPitch / 4 - nWidth;
            nSkipDestH--;
        }

        int nBltH = min(nHeight - ptSource.y, rClip.bottom - pt.y);
        while (nBltH > 0) {
            int nRemainingWidth = nWidth;

            // Skip src left.
            int nSkipSrcW = min(ptSource.x, nRemainingWidth);
            nRemainingWidth -= nSkipSrcW;
            while (nSkipSrcW > 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nSkipSrcW == nRunLength) {
                        pos += 2;

                        nRunLength = 0;
                        nSkipSrcW = 0;
                    } else if (nSkipSrcW > nRunLength) {
                        pos += 2;

                        nSkipSrcW -= nRunLength;
                        nRunLength = 0;
                    } else {
                        nRunLength -= nSkipSrcW;
                        nSkipSrcW = 0;
                    }
                } else {
                    pos++;
                    nSkipSrcW--;
                }
            }

            // Skip dest left.
            int nSkipDestW = min(max(rClip.left - pt.x, 0), nRemainingWidth);
            nRemainingWidth -= nSkipDestW;
            while (nSkipDestW > 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nSkipDestW == nRunLength) {
                        pos += 2;

                        pDest += nSkipDestW;
                        nRunLength = 0;
                        nSkipDestW = 0;
                    } else if (nSkipDestW > nRunLength) {
                        pos += 2;

                        pDest += nRunLength;
                        nSkipDestW -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pDest += nSkipDestW;
                        nRunLength -= nSkipDestW;
                        nSkipDestW = 0;
                    }
                } else {
                    pos++;
                    pDest++;
                    nSkipDestW--;
                }
            }

            // Blt.
            int nBltW = min(max(rClip.right - rClip.left, 0), nRemainingWidth);
            nRemainingWidth -= nBltW;
            while (nBltW > 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nBltW == nRunLength) {
                        pos += 2;

                        pDest += nBltW;
                        nRunLength = 0;
                        nBltW = 0;
                    } else if (nBltW > nRunLength) {
                        pos += 2;

                        pDest += nRunLength;
                        nBltW -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pDest += nBltW;
                        nRunLength -= nBltW;
                        nBltW = 0;
                    }
                } else {
                    pos++;

                    *pDest++ = CVidImage::rgbTempPal[nColor];
                    nBltW--;
                }
            }

            // Skip remainder.
            while (nRemainingWidth > 0) {
                BYTE nColor = pFrameData[pos];
                if (nColor == nTransparentColor) {
                    if (nRunLength == 0) {
                        nRunLength = pFrameData[pos + 1] + 1;
                    }

                    if (nRemainingWidth == nRunLength) {
                        pos += 2;

                        pDest += nRemainingWidth;
                        nRunLength = 0;
                        nRemainingWidth = 0;
                    } else if (nRemainingWidth > nRunLength) {
                        pos += 2;

                        pDest += nRunLength;
                        nRemainingWidth -= nRunLength;
                        nRunLength = 0;
                    } else {
                        pDest += nRemainingWidth;
                        nRunLength -= nRemainingWidth;
                        nRemainingWidth = 0;
                    }
                } else {
                    pos++;

                    pDest++;
                    nRemainingWidth--;
                }
            }
            pDest += lPitch / 4 - nWidth;
            nBltH--;
        }
    } else {
        // TODO: Incomplete.
    }

    return TRUE;
}

// 0x7D0470
BOOL CVidCell::sub_7D0470(DWORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7D0730
BOOL CVidCell::sub_7D0730(DWORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7D0950
BOOL CVidCell::sub_7D0950(DWORD* pSurface, LONG lPitch, DWORD dwFlags, INT nTransVal)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7B49D0
BOOL CVidCell::sub_7B49D0(WORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7D0C60
BOOL CVidCell::sub_7D0C60(BYTE* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7D1190
BOOL CVidCell::sub_7D1190(DWORD* pSurface, LONG lPitch, DWORD dwFlags)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x7C4240
void CVidCell::RenderTexture(INT x, INT y, const CRect& rFxRect, CSize dataPitch, const CRect& rClip, DWORD dwFlags)
{
    // TODO: Incomplete.
}

// 0x7C4960
BOOL CVidCell::Render3d(INT x, INT y, DWORD dwFlags, INT nTransVal)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7C4A90
BOOL CVidCell::Render3d(INT x, INT y, const CRect& rClip, CVidPoly* pClipPoly, int nPolys, DWORD dwFlags, INT nTransVal, BOOL bDemanded)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7C4E20
BOOL CVidCell::Render3d(INT x, INT y, const CRect& rClip, BOOLEAN bDemanded, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7C5210
BOOL CVidCell::FXRender3d(INT nRefPtX, INT nRefPtY, const CRect& rFXRect, DWORD dwFlags, INT nTransVal, BOOL bAlphaValues)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7C5330
BOOL CVidCell::FXRender3d(INT nRefPtX, INT nRefPtY, const CRect& rFXRect, const CRect& rClip, BOOLEAN a5, DWORD dwFlags, BOOL bAlphaValues)
{
    // TODO: Incomplete.

    return FALSE;
}

// NOTE: Inlined in many places. Seen in `CVidCell::GetFrameCenterPoint`
// assertion.
BAMHEADER* CVidCell::GetResBamHeader()
{
    if (m_header.GetResRef() != "") {
        return m_header.pRes->m_pBamHeaderCopy;
    } else {
        if (pRes->m_bCacheHeader) {
            return pRes->m_pBamHeaderCopy;
        } else {
            return pRes->m_pBamHeader;
        }
    }
}

// NOTE: Inlined in many places.
FRAMEENTRY* CVidCell::GetResFrame(WORD nSequence, WORD nFrame)
{
    if (m_header.GetResRef() != "") {
        return m_header.pRes->GetFrame(nSequence, nFrame, m_bDoubleSize);
    } else {
        return pRes->GetFrame(nSequence, nFrame, m_bDoubleSize);
    }
}

// NOTE: Inlined in many places. Seen in `CVidCell::GetFrameCenterPoint`
// assertion.
SEQUENCEENTRY* CVidCell::GetResSequences()
{
    if (m_header.GetResRef() != "") {
        return m_header.pRes->m_pSequences;
    } else {
        return pRes->m_pSequences;
    }
}

// NOTE: Inlined in many places.
void CVidCell::Release(BOOLEAN& bDemanded)
{
    if (!bDemanded) {
        if (m_header.GetResRef() != "") {
            m_header.Release();
        } else {
            pRes->Release();
        }
    }
}

// NOTE: Inlined.
void CVidCell::UnsuppressTintAllRanges()
{
    m_paletteAffects.suppressTints = 0;
}

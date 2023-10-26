#include "CGameAnimationTypeAmbient.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CInfinity.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6A6F10
CGameAnimationTypeAmbient::CGameAnimationTypeAmbient(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_falseColor = TRUE;
    m_pathSmooth = FALSE;
    m_bInvulnerable = FALSE;
    m_listType = CGAMEOBJECT_LIST_FRONT;
    m_nSndFreq = -1;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_resRef = "ABAT";
        m_falseColor = FALSE;
        m_pathSmooth = TRUE;
        m_pSndDeath = "";
        break;
    case 0x100:
        m_colorChunks = -1;
        m_moveScale = 4;
        m_moveScaleCurrent = 4;
        m_resRef = "ACAT";
        m_rEllipse.left = -12;
        m_rEllipse.top = -9;
        m_rEllipse.right = 12;
        m_rEllipse.bottom = 9;
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x200:
        m_colorChunks = -1;
        m_moveScale = 10;
        m_moveScaleCurrent = 10;
        m_resRef = "ACHK";
        m_rEllipse.left = -12;
        m_rEllipse.top = -9;
        m_rEllipse.right = 12;
        m_rEllipse.bottom = 9;
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x300:
        m_colorChunks = -1;
        m_moveScale = 4;
        m_moveScaleCurrent = 4;
        m_resRef = "ARAT";
        m_rEllipse.left = -12;
        m_rEllipse.top = -9;
        m_rEllipse.right = 12;
        m_rEllipse.bottom = 9;
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x400:
        m_colorChunks = -1;
        m_moveScale = 4;
        m_moveScaleCurrent = 4;
        m_resRef = "ASQU";
        m_rEllipse.left = -12;
        m_rEllipse.top = -9;
        m_rEllipse.right = 12;
        m_rEllipse.bottom = 9;
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x500:
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_resRef = "ABAT";
        m_falseColor = FALSE;
        m_pathSmooth = TRUE;
        m_listType = CGAMEOBJECT_LIST_FLIGHT;
        m_pSndDeath = "";
        break;
    case 0x600:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;

        if ((animationID & 0xF0) != 0) {
            m_resRef = "NPROH";
        } else {
            m_resRef = "NBEGH";
        }
        break;
    case 0x700:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 4;
        m_bInvulnerable = TRUE;

        if ((animationID & 0xF0) != 0) {
            m_resRef = "NGRLH";
        } else {
            m_resRef = "NBOYH";
        }

        m_pSndDeath = "FAL_01B";
        break;
    case 0x800:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 5;

        if ((animationID & 0xF0) != 0) {
            m_resRef = "NFAWH";
        } else {
            m_resRef = "NFAMH";
        }
        break;
    case 0x900:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;

        if ((animationID & 0xF0) != 0) {
            m_resRef = "NSIWH";
        } else {
            m_resRef = "NSIMH";
        }
        break;
    case 0xA00:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;

        if ((animationID & 0xF0) != 0) {
            m_resRef = "NNOWH";
        } else {
            m_resRef = "NNOMH";
        }
        break;
    case 0xB00:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;
        m_resRef = "NSLVH";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3343
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;

    if (!MIRROR_BAM) {
        // NOTE: Uninline.
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE, TRUE);
    }

    m_currentVidCellExtend = &m_g1VidCellExtend;
    m_currentVidCell = m_currentVidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetPalette(m_charPalette);
        }
    }

    m_currentBamSequence = 1;

    if (MIRROR_BAM) {
        if (m_falseColor) {
            m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
        } else {
            m_g1VidCellBase.m_bShadowOn = FALSE;
        }
    } else {
        if (m_animationID == 0xC500) {
            if (m_falseColor) {
                m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
            } else {
                m_g1VidCellBase.m_bShadowOn = FALSE;
                m_g1VidCellExtend.m_bShadowOn = FALSE;
            }
        }
    }

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6A7890
CGameAnimationTypeAmbient::~CGameAnimationTypeAmbient()
{
}

// 0x6A76A0
BOOLEAN CGameAnimationTypeAmbient::DetectedByInfravision()
{
    return m_listType != CGAMEOBJECT_LIST_FLIGHT;
}

// 0x6A76B0
BYTE CGameAnimationTypeAmbient::GetListType()
{
    return m_listType;
}

// 0x6A76C0
BOOL CGameAnimationTypeAmbient::GetPathSmooth()
{
    return m_pathSmooth;
}

// 0x6A76D0
BOOL CGameAnimationTypeAmbient::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 941
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6A7710
BOOL CGameAnimationTypeAmbient::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 942
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6A7750
BOOL CGameAnimationTypeAmbient::IsFalseColor()
{
    return m_falseColor;
}

// 0x6A7760
BOOL CGameAnimationTypeAmbient::IsInvulnerable()
{
    return m_bInvulnerable;
}

// 0x6A7770
BOOL CGameAnimationTypeAmbient::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6A77A0
void CGameAnimationTypeAmbient::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 946
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6A77E0
void CGameAnimationTypeAmbient::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 947
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6A7820
SHORT CGameAnimationTypeAmbient::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 956
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6A7930
void CGameAnimationTypeAmbient::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3417
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6A79A0
void CGameAnimationTypeAmbient::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6A7A10
void CGameAnimationTypeAmbient::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3478
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
    } else {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
    }
}

// 0x6A7AF0
CVidPalette* CGameAnimationTypeAmbient::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3515
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            return &m_charPalette;
        }

        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3530
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6A7BB0
void CGameAnimationTypeAmbient::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3560
        UTIL_ASSERT(m_currentVidCell != NULL);

        resRef = m_resRef;
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3592
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A7C90
const char* CGameAnimationTypeAmbient::GetSndWalk(SHORT a1)
{
    switch (m_animationID) {
    case 0x400:
    case 0x600:
    case 0x700:
    case 0x800:
    case 0x900:
    case 0xA00:
    case 0xB00:
        break;
    default:
        return NULL;
    }

    const char* v1;
    switch (a1) {
    case 1:
        v1 = "FS_Dirt ";
        break;
    case 2:
        v1 = "FS_WdSn ";
        break;
    case 3:
    case 9:
        v1 = "FS_WOOD ";
        break;
    case 4:
        v1 = "FS_Tomb ";
        break;
    case 7:
        v1 = "FS_Ston ";
        break;
    case 11:
        v1 = "FS_Snow ";
        break;
    case 15:
        v1 = "FS_Gras ";
        break;
    default:
        return NULL;
    }

    char* szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3699
    UTIL_ASSERT(szTemp != NULL);

    memcpy(szTemp, v1, 9);

    szTemp[7] = rand() % 6 + '1';
    szTemp[8] = '\0';

    if (strcmp(szTemp, m_walkRef) == 0) {
        if (szTemp[7] == '6') {
            szTemp[7] = '1';
        } else {
            szTemp[7]++;
        }
    }

    memcpy(m_walkRef, szTemp, 9);

    // FIXME: Leaks `szTemp`.
    return szTemp;
}

// 0x6A7E20
void CGameAnimationTypeAmbient::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3862
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_g1VidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_g1VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3899
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A7FA0
void CGameAnimationTypeAmbient::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3924
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellExtend.UnsuppressTintAllRanges();
        }
    }
}

// 0x6A8070
void CGameAnimationTypeAmbient::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3973
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellBase.SuppressTint(0);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g1VidCellExtend.SuppressTint(0);
                }
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.SetTintColor(tintColor);
                }
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 4020
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A8220
void CGameAnimationTypeAmbient::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 4045
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g1VidCellBase.SuppressTint(0);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellExtend.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(tintColor);
            }
        }
    }
}

// 0x6A8320
void CGameAnimationTypeAmbient::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 4102
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 4112
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6A8410
void CGameAnimationTypeAmbient::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 4138
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6A8470
void CGameAnimationTypeAmbient::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 4169
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 4170
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (MIRROR_BAM) {
        if (m_currentBamDirection > m_extendDirectionTest) {
            dwRenderFlags |= CInfinity::MIRROR_FX;
        }

        if (transparency) {
            dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
            dwRenderFlags |= 0x2;
        } else {
            dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
            dwRenderFlags |= 0x1;
        }
    } else {
        if (m_animationID != 0xC500) {
            dwRenderFlags |= 0x4;

            dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;

            if (transparency) {
                dwRenderFlags |= 0x2;
            }
        } else {
            if (transparency) {
                dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
                dwRenderFlags |= 0x2;
            } else {
                dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
                dwRenderFlags |= 0x1;
            }
        }
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        if (m_animationID == 0xC500) {
            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);
        } else {
            COLORREF oldTintColor = m_currentVidCell->GetTintColor();
            BYTE b = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
                ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
                : 0;
            BYTE g = GetGValue(oldTintColor) + GetGValue(rgbTintColor) - 255 >= 0
                ? GetGValue(oldTintColor) + GetGValue(rgbTintColor) + 1
                : 0;
            BYTE r = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
                ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
                : 0;
            m_currentVidCell->SetTintColor(RGB(r, g, b));

            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);

            m_currentVidCell->SetTintColor(oldTintColor);
        }

        if (m_animationID != 0xC500) {
            pInfinity->FXRenderClippingPolys(ptPos.x,
                ptPos.y - posZ,
                posZ,
                ptReference,
                CRect(rGCBounds.left, rGCBounds.top - posZ, rGCBounds.right, rGCBounds.bottom - posZ),
                bDithered,
                dwRenderFlags);
        }

        if (bFadeOut) {
            pInfinity->FXUnlock(dwRenderFlags, &rFXRect, ptPos + ptReference);
        } else {
            pInfinity->FXUnlock(dwRenderFlags, &rFXRect, CPoint(0, 0));
        }

        pInfinity->FXBltFrom(nSurface,
            rFXRect,
            ptPos.x,
            ptPos.y,
            ptReference.x,
            ptReference.y,
            dwRenderFlags);
    }
}

// 0x6A8780
SHORT CGameAnimationTypeAmbient::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    if (m_listType == CGAMEOBJECT_LIST_FLIGHT && nSequence != 10) {
        nSequence = 7;
    }

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 4;
        break;
    case 2:
    case 3:
    case 7:
        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 6:
        if (m_currentBamSequence != 2 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 8:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        nSequence = 7;

        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 9:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 5;
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 10;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 4312
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);

    if (bRandomFrame) {
        BYTE nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            m_currentVidCell->FrameSet(rand() % nSequenceLength);
        } else {
            m_currentVidCell->FrameSet(0);
        }
    } else {
        m_currentVidCell->FrameSet(0);
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

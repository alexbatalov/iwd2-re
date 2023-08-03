#include "CGameAnimationTypeMonsterIcewind.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6E0410
CGameAnimationTypeMonsterIcewind::CGameAnimationTypeMonsterIcewind(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    // TODO: Incomplete.
}

// 0x6E5040
CGameAnimationTypeMonsterIcewind::~CGameAnimationTypeMonsterIcewind()
{
}

// 0x6E4E90
BOOLEAN CGameAnimationTypeMonsterIcewind::DetectedByInfravision()
{
    return m_bDetectedByInfravision;
}

// 0x6E4EA0
BOOL CGameAnimationTypeMonsterIcewind::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2202
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6E4EE0
BOOL CGameAnimationTypeMonsterIcewind::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2203
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6E4F20
BOOL CGameAnimationTypeMonsterIcewind::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6E4F50
void CGameAnimationTypeMonsterIcewind::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2206
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6E4F90
void CGameAnimationTypeMonsterIcewind::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2207
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6E4FD0
SHORT CGameAnimationTypeMonsterIcewind::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2216
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6E5290
void CGameAnimationTypeMonsterIcewind::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 25865
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6E5300
void CGameAnimationTypeMonsterIcewind::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if ((!m_bExtendDir || MIRROR_BAM)
        && m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6E5380
void CGameAnimationTypeMonsterIcewind::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 25926
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (m_bExtendDir && !MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if ((!m_bExtendDir || MIRROR_BAM) && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
    } else {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
    }
}

// 0x6E5470
CVidPalette* CGameAnimationTypeMonsterIcewind::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 25963
        UTIL_ASSERT(m_currentVidCell != NULL);

        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 25978
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6E5B50
void CGameAnimationTypeMonsterIcewind::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 26345
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_a1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_shVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_awVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_slVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_deVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_daVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_paVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_reVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_coVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_twVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_waVidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_a1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_shVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_awVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_slVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_deVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_daVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_paVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_reVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_coVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_twVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_waVidCellBase.UnsuppressTint(colorRange & 0xF);

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a3VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_shVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_awVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_slVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_deVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_daVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_paVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_reVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_coVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_caVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_twVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_waVidCellExtend.DeleteRangeAffects(colorRange & 0xF);

                m_a1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a2VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a3VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_shVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_awVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_slVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_deVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_daVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_paVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_reVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_coVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_caVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_twVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_waVidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_shVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_awVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_slVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_deVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_daVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_paVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_reVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_coVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_twVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_waVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_shVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_awVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_slVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_deVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_daVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_paVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_reVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_coVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_twVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_waVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();
            m_shVidCellBase.DeleteResPaletteAffect();
            m_awVidCellBase.DeleteResPaletteAffect();
            m_slVidCellBase.DeleteResPaletteAffect();
            m_deVidCellBase.DeleteResPaletteAffect();
            m_daVidCellBase.DeleteResPaletteAffect();
            m_paVidCellBase.DeleteResPaletteAffect();
            m_reVidCellBase.DeleteResPaletteAffect();
            m_coVidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_twVidCellBase.DeleteResPaletteAffect();
            m_waVidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();
            m_shVidCellBase.UnsuppressTintAllRanges();
            m_awVidCellBase.UnsuppressTintAllRanges();
            m_slVidCellBase.UnsuppressTintAllRanges();
            m_deVidCellBase.UnsuppressTintAllRanges();
            m_daVidCellBase.UnsuppressTintAllRanges();
            m_paVidCellBase.UnsuppressTintAllRanges();
            m_reVidCellBase.UnsuppressTintAllRanges();
            m_coVidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_twVidCellBase.UnsuppressTintAllRanges();
            m_waVidCellBase.UnsuppressTintAllRanges();

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.DeleteResPaletteAffect();
                m_a2VidCellExtend.DeleteResPaletteAffect();
                m_a3VidCellExtend.DeleteResPaletteAffect();
                m_shVidCellExtend.DeleteResPaletteAffect();
                m_awVidCellExtend.DeleteResPaletteAffect();
                m_slVidCellExtend.DeleteResPaletteAffect();
                m_deVidCellExtend.DeleteResPaletteAffect();
                m_daVidCellExtend.DeleteResPaletteAffect();
                m_paVidCellExtend.DeleteResPaletteAffect();
                m_reVidCellExtend.DeleteResPaletteAffect();
                m_coVidCellExtend.DeleteResPaletteAffect();
                m_caVidCellExtend.DeleteResPaletteAffect();
                m_twVidCellExtend.DeleteResPaletteAffect();
                m_waVidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_a1VidCellExtend.UnsuppressTintAllRanges();
                m_a2VidCellExtend.UnsuppressTintAllRanges();
                m_a3VidCellExtend.UnsuppressTintAllRanges();
                m_shVidCellExtend.UnsuppressTintAllRanges();
                m_awVidCellExtend.UnsuppressTintAllRanges();
                m_slVidCellExtend.UnsuppressTintAllRanges();
                m_deVidCellExtend.UnsuppressTintAllRanges();
                m_daVidCellExtend.UnsuppressTintAllRanges();
                m_paVidCellExtend.UnsuppressTintAllRanges();
                m_reVidCellExtend.UnsuppressTintAllRanges();
                m_coVidCellExtend.UnsuppressTintAllRanges();
                m_caVidCellExtend.UnsuppressTintAllRanges();
                m_twVidCellExtend.UnsuppressTintAllRanges();
                m_waVidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 26515
        UTIL_ASSERT(FALSE);
    }
}

// 0x6E6490
void CGameAnimationTypeMonsterIcewind::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 26540
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_shVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_awVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_slVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_deVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_daVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_paVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_reVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_coVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_twVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_waVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (m_bExtendDir && !MIRROR_BAM) {
            m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_shVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_awVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_slVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_deVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_daVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_paVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_reVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_coVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_twVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_waVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_a1VidCellBase.DeleteResPaletteAffect();
        m_a2VidCellBase.DeleteResPaletteAffect();
        m_a3VidCellBase.DeleteResPaletteAffect();
        m_shVidCellBase.DeleteResPaletteAffect();
        m_awVidCellBase.DeleteResPaletteAffect();
        m_slVidCellBase.DeleteResPaletteAffect();
        m_deVidCellBase.DeleteResPaletteAffect();
        m_daVidCellBase.DeleteResPaletteAffect();
        m_paVidCellBase.DeleteResPaletteAffect();
        m_reVidCellBase.DeleteResPaletteAffect();
        m_coVidCellBase.DeleteResPaletteAffect();
        m_caVidCellBase.DeleteResPaletteAffect();
        m_twVidCellBase.DeleteResPaletteAffect();
        m_waVidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_a1VidCellBase.UnsuppressTintAllRanges();
        m_a2VidCellBase.UnsuppressTintAllRanges();
        m_a3VidCellBase.UnsuppressTintAllRanges();
        m_shVidCellBase.UnsuppressTintAllRanges();
        m_awVidCellBase.UnsuppressTintAllRanges();
        m_slVidCellBase.UnsuppressTintAllRanges();
        m_deVidCellBase.UnsuppressTintAllRanges();
        m_daVidCellBase.UnsuppressTintAllRanges();
        m_paVidCellBase.UnsuppressTintAllRanges();
        m_reVidCellBase.UnsuppressTintAllRanges();
        m_coVidCellBase.UnsuppressTintAllRanges();
        m_caVidCellBase.UnsuppressTintAllRanges();
        m_twVidCellBase.UnsuppressTintAllRanges();
        m_waVidCellBase.UnsuppressTintAllRanges();

        if (m_bExtendDir && !MIRROR_BAM) {
            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();
            m_shVidCellBase.DeleteResPaletteAffect();
            m_awVidCellBase.DeleteResPaletteAffect();
            m_slVidCellBase.DeleteResPaletteAffect();
            m_deVidCellBase.DeleteResPaletteAffect();
            m_daVidCellBase.DeleteResPaletteAffect();
            m_paVidCellBase.DeleteResPaletteAffect();
            m_reVidCellBase.DeleteResPaletteAffect();
            m_coVidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_twVidCellBase.DeleteResPaletteAffect();
            m_waVidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();
            m_shVidCellBase.UnsuppressTintAllRanges();
            m_awVidCellBase.UnsuppressTintAllRanges();
            m_slVidCellBase.UnsuppressTintAllRanges();
            m_deVidCellBase.UnsuppressTintAllRanges();
            m_daVidCellBase.UnsuppressTintAllRanges();
            m_paVidCellBase.UnsuppressTintAllRanges();
            m_reVidCellBase.UnsuppressTintAllRanges();
            m_coVidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_twVidCellBase.UnsuppressTintAllRanges();
            m_waVidCellBase.UnsuppressTintAllRanges();
        }
    }
}

// 0x6E78F0
void CGameAnimationTypeMonsterIcewind::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 27004
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_palette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 27014
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6E79E0
void CGameAnimationTypeMonsterIcewind::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27040
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

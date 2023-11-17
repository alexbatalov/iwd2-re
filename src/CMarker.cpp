#include "CMarker.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x85C17A
const BYTE CMarker::RECTICLE = 0;

// 0x85C17B
const BYTE CMarker::ELLIPSE = 1;

// 0x85C17C
const COLORREF CMarker::PC_COLOR = RGB(0, 128, 0);

// 0x85C180
const COLORREF CMarker::PC_NONECONTROLED_COLOR = RGB(115, 100, 198);

// 0x85C184
const COLORREF CMarker::PC_NONECONTROLED_SELECTED_COLOR = RGB(190, 183, 255);

// 0x85C188
const COLORREF CMarker::ENEMY_COLOR = RGB(255, 0, 32);

// 0x85C18C
const COLORREF CMarker::NEUTRAL_COLOR = RGB(64, 255, 255);

// 0x85C190
const COLORREF CMarker::PC_SELECTED_COLOR = RGB(0, 250, 0);

// 0x85C194
const COLORREF CMarker::TALKING_COLOR = RGB(255, 255, 255);

// 0x85C198
const COLORREF CMarker::PC_MORALE_FAILURE_COLOR = RGB(255, 255, 0);

// 0x85C19C
const SHORT CMarker::PICKED_FLASH_PERIOD = 20;

// 0x85C19E
const BYTE CMarker::RECTICLE_DEST_SIZE = 12;

// 0x85C19F
const BYTE CMarker::RECTICLE_MAX_STRETCH = 4;

// 0x85C1A0
const BYTE CMarker::RECTICLE_XCTROFFSET = 2;

// 0x85C1A1
const BYTE CMarker::RECTICLE_XGAP = 4;

// 0x7668D0
CMarker::CMarker()
{
    m_rgbColor = 0;
    m_nRecticleCounter = 0;
    m_nRecticleForceRender = 0;
    m_nRecticleForceRenderTarget = 0;
    m_type = ELLIPSE;

    memset(&m_recticleDesc, 0, sizeof(m_recticleDesc));

    m_bTalking = FALSE;
}

// 0x766900
void CMarker::AsynchronousUpdate(CGameSprite* pSprite)
{
    BYTE enemyAlly = pSprite->m_liveTypeAI.m_nEnemyAlly;

    if (m_nRecticleForceRender > 0) {
        m_nRecticleForceRender--;
    }

    if (m_nRecticleForceRenderTarget > 0) {
        m_nRecticleForceRenderTarget--;
    }

    BOOLEAN dialogTalker = FALSE;
    if (g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_mode == 386
        || g_pBaldurChitin->GetObjectGame()->GetGameSave()->m_mode == 1282) {
        CRect rViewPort(pSprite->GetArea()->GetInfinity()->rViewPort);

        INT x;
        INT y;
        pSprite->GetArea()->GetInfinity()->GetViewPosition(x, y);

        if (abs(pSprite->GetPos().x - (x + rViewPort.Width() / 2)) < 16
            && abs(pSprite->GetPos().y - (y + rViewPort.Height() / 2)) < 12) {
            dialogTalker = TRUE;
        }
    }

    m_bTalking = FALSE;
    if (pSprite->m_talkingCounter <= 0 && !dialogTalker) {
        if (enemyAlly > CAIObjectType::EA_GOODCUTOFF) {
            if (enemyAlly == CAIObjectType::EA_ARENAPC) {
                if (!pSprite->m_moraleFailure
                    && (pSprite->GetDerivedStats()->m_generalState & STATE_PANIC) == 0
                    && !pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_179]
                    && ((pSprite->GetDerivedStats()->m_generalState & STATE_BERSERK) == 0
                        || !pSprite->m_berserkActive)) {
                    if (pSprite->m_bSelected) {
                        m_rgbColor = PC_SELECTED_COLOR;
                    } else {
                        if ((g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                                || g_pChitin->cNetwork.m_idLocalPlayer != pSprite->m_remotePlayerID)
                            && pSprite->m_nUnselectableCounter == 0) {
                            m_rgbColor = PC_COLOR;

                            m_rgbColor = RGB(GetRValue(m_rgbColor),
                                GetGValue(m_rgbColor) - 7 * g_pChitin->GetCurrentVideoMode()->m_nGammaCorrection,
                                0);
                        } else {
                            m_rgbColor = PC_NONECONTROLED_COLOR;
                        }
                    }
                } else {
                    m_rgbColor = PC_MORALE_FAILURE_COLOR;
                }
            } else if (enemyAlly < CAIObjectType::EA_EVILCUTOFF) {
                if (!pSprite->m_moraleFailure
                    && (pSprite->GetDerivedStats()->m_generalState & STATE_PANIC) == 0
                    && !pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_179]
                    && ((pSprite->GetDerivedStats()->m_generalState & STATE_BERSERK) == 0
                        || !pSprite->m_berserkActive)) {
                    m_rgbColor = NEUTRAL_COLOR;
                } else {
                    m_rgbColor = PC_MORALE_FAILURE_COLOR;
                }
            } else {
                if (!pSprite->m_moraleFailure
                    && (pSprite->GetDerivedStats()->m_generalState & STATE_PANIC) == 0
                    && !pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_179]
                    && ((pSprite->GetDerivedStats()->m_generalState & STATE_BERSERK) == 0
                        || !pSprite->m_berserkActive)
                    && (pSprite->GetBaseStats()->m_flags & 0x8000) == 0) {
                    m_rgbColor = ENEMY_COLOR;
                } else {
                    m_rgbColor = PC_MORALE_FAILURE_COLOR;
                }
            }
        } else {
            if (!pSprite->m_moraleFailure
                && (pSprite->GetDerivedStats()->m_generalState & STATE_PANIC) == 0
                && !pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_179]
                && ((pSprite->GetDerivedStats()->m_generalState & STATE_BERSERK) == 0
                    || !pSprite->m_berserkActive)
                && !pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_ANIMAL_RAGE]) {
                if (pSprite->m_bSelected) {
                    m_rgbColor = PC_SELECTED_COLOR;
                } else {
                    if ((g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                            || g_pChitin->cNetwork.m_idLocalPlayer != pSprite->m_remotePlayerID)
                        && pSprite->m_nUnselectableCounter == 0) {
                        m_rgbColor = PC_COLOR;

                        m_rgbColor = RGB(GetRValue(m_rgbColor),
                            GetGValue(m_rgbColor) - 7 * g_pChitin->GetCurrentVideoMode()->m_nGammaCorrection,
                            0);
                    } else {
                        m_rgbColor = PC_NONECONTROLED_COLOR;
                    }
                }
            }
        }
    } else {
        m_rgbColor = TALKING_COLOR;
        m_bTalking = TRUE;

        if (pSprite->Orderable(FALSE)) {
            SHORT nPortrait = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(pSprite->GetId());
            g_pBaldurChitin->GetObjectGame()->UpdatePortrait(nPortrait, 1);
            pSprite->m_talkingRenderCount = 2;
        }
    }

    if (pSprite->m_talkingCounter <= 0) {
        if (pSprite->m_talkingRenderCount > 0) {
            pSprite->m_talkingRenderCount--;
            SHORT nPortrait = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(pSprite->GetId());
            g_pBaldurChitin->GetObjectGame()->UpdatePortrait(nPortrait, 1);
        }
    }

    if (pSprite->GetId() == pSprite->GetArea()->m_iPicked
        || pSprite->GetId() == pSprite->GetArea()->m_iPickedTarget) {
        ULONG nAsyncCounter = g_pBaldurChitin->nAUCounter % 20;
        BYTE red;
        BYTE green;
        BYTE blue;

        if (nAsyncCounter < 5) {
            red = static_cast<BYTE>(nAsyncCounter * GetRValue(m_rgbColor) / 5);
            green = static_cast<BYTE>(nAsyncCounter * GetGValue(m_rgbColor) / 5);
            blue = static_cast<BYTE>(nAsyncCounter * GetBValue(m_rgbColor) / 5);
        } else if (nAsyncCounter < 10) {
            nAsyncCounter -= 5;
            red = static_cast<BYTE>(GetRValue(m_rgbColor) + nAsyncCounter * (255 - GetRValue(m_rgbColor)) / 5);
            green = static_cast<BYTE>(GetGValue(m_rgbColor) + nAsyncCounter * (255 - GetGValue(m_rgbColor)) / 5);
            blue = static_cast<BYTE>(GetBValue(m_rgbColor) + nAsyncCounter * (255 - GetBValue(m_rgbColor)) / 5);
        } else if (nAsyncCounter < 15) {
            nAsyncCounter -= 10;
            red = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetRValue(m_rgbColor)) / 5);
            green = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetGValue(m_rgbColor)) / 5);
            blue = static_cast<BYTE>(255 - nAsyncCounter * (255 - GetBValue(m_rgbColor)) / 5);
        } else {
            nAsyncCounter -= 15;
            red = static_cast<BYTE>(GetRValue(m_rgbColor) - nAsyncCounter * GetRValue(m_rgbColor) / 5);
            green = static_cast<BYTE>(GetGValue(m_rgbColor) - nAsyncCounter * GetGValue(m_rgbColor) / 5);
            blue = static_cast<BYTE>(GetBValue(m_rgbColor) - nAsyncCounter * GetBValue(m_rgbColor) / 5);
        }

        m_rgbColor = RGB(red, green, blue);
    }
}

// 0x766E40
void CMarker::Render(CVidMode* pVidMode, INT nSurface, CGameSprite* pSprite)
{
    BOOLEAN bPickedTarget = pSprite->GetId() == pSprite->GetArea()->m_iPickedTarget;
    const CRect& rEllipse = pSprite->GetAnimation()->GetEllipseRect();

    if (rEllipse.right != 0 && rEllipse.bottom != 0) {
        if (bPickedTarget) {
            m_nRecticleCounter++;
            m_type = RECTICLE;
        }

        Render(pVidMode,
            nSurface,
            pSprite->GetArea()->GetInfinity(),
            pSprite->GetPos(),
            rEllipse.right,
            rEllipse.bottom);

        if (bPickedTarget) {
            if (m_nRecticleCounter > 0) {
                m_nRecticleCounter--;
                if (m_nRecticleCounter == 0) {
                    m_type = ELLIPSE;
                }
            }
        }
    }
}

// 0x766EF0
void CMarker::Render(CVidMode* pVidMode, INT nSurface, CInfinity* pInfinity, const CPoint& dest, LONG nXSize, LONG nYSize)
{
    COLORREF rgbColor = m_rgbColor;
    CSize size;
    CPoint ptObjCenter;
    LONG nXOffset;

    rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyFadeAmount(rgbColor);
    rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(rgbColor);

    ptObjCenter.x = dest.x + pInfinity->rViewPort.left - pInfinity->nCurrentX;
    ptObjCenter.y = dest.y + pInfinity->rViewPort.top - pInfinity->nCurrentY;

    size.cx = nXSize;
    size.cy = nYSize;

    switch (m_type) {
    case RECTICLE:
        nXOffset = (g_pBaldurChitin->nAUCounter / 2) % 8;
        if (nXOffset > 4) {
            nXOffset = 8 - nXOffset;
        }
        m_recticleDesc.piePieceXOffset = static_cast<SHORT>(nXOffset);
        m_recticleDesc.piePieceYOffset = 3 * m_recticleDesc.piePieceXOffset / 4;
        m_recticleDesc.yAxis = static_cast<SHORT>(nYSize);
        m_recticleDesc.piePiecePtXOffset = static_cast<SHORT>(nXSize - 2);
        m_recticleDesc.ptCenter = ptObjCenter;
        m_recticleDesc.xAxis = static_cast<SHORT>(nXSize);
        m_recticleDesc.piePiecePtYOffset = static_cast<SHORT>(3 * (nXSize - 2) / 4);
        m_recticleDesc.xGap = 4;
        m_recticleDesc.yGap = 2;
        pVidMode->DrawRecticle(m_recticleDesc, pInfinity->rViewPort, rgbColor);
        break;
    case ELLIPSE:
        if (m_bTalking) {
            nXOffset = (g_pBaldurChitin->nAUCounter / 2) % 8;
            if (nXOffset > 4) {
                nXOffset = 8 - nXOffset;
            }
            size.cx += nXOffset;
            size.cy += 3 * nXOffset / 4;
        }
        pVidMode->DrawEllipse(ptObjCenter, size, pInfinity->rViewPort, rgbColor);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjItem.cpp
        // __LINE__: 638
        UTIL_ASSERT(FALSE);
    }
}

// 0x7670D0
BYTE CMarker::SetType(BYTE nType)
{
    switch (nType) {
    case RECTICLE:
        m_type = RECTICLE;
        m_nRecticleCounter++;
        break;
    case ELLIPSE:
        if (m_nRecticleCounter > 0) {
            m_nRecticleCounter--;
            if (m_nRecticleCounter == 0) {
                m_type = ELLIPSE;
            }
        }
        break;
    }

    return m_type;
}

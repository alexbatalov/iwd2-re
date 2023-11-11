#include "CCacheStatus.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x8A7BA8
int CCacheStatus::PARCHMENT_TEXT_START_X = 400;

// 0x8A7BAC
int CCacheStatus::PARCHMENT_TEXT_START_Y = 36;

// 0x8A7BB0
int CCacheStatus::dword_8A7BB0 = 320;

// 0x8A7BB4
int CCacheStatus::dword_8A7BB4 = 335;

// 0x8A7BB8
int CCacheStatus::TRAVEL_AREA_START_X = 18;

// 0x8A7BBC
int CCacheStatus::TRAVEL_AREA_START_Y = 50;

// 0x8A7BC0
int CCacheStatus::UPDATE_TEXT_X = 400;

// 0x8A7BC4
int CCacheStatus::UPDATE_TEXT_Y = 481;

// 0x8A7BC8
int CCacheStatus::PROGRESSBAR_BACKGROUND_START_X = 51;

// 0x8A7BCC
int CCacheStatus::PROGRESSBAR_BACKGROUND_START_Y = 525;

// 0x8A7BD0
int CCacheStatus::PROGRESSBAR_BACKGROUND_SIZE_X = 595;

// 0x8A7BD4
int CCacheStatus::PROGRESSBAR_FOREGROUND_X_OFFSET = 45;

// 0x8A7BD8
int CCacheStatus::PROGRESSBAR_FOREGROUND_SIZE_Y = 26;

// 0x8A7BDC
int CCacheStatus::PROGRESSBAR_FOREGROUND_CAP_OFFSET = 7;

// 0x8A7BE0
int CCacheStatus::MINIBAR_FOREGROUND_CAP_OFFSET = 4;

// 0x8A7BE4
int CCacheStatus::dword_8A7BE4 = 230;

// 0x8A7BE8
int CCacheStatus::dword_8A7BE8 = 5;

// 0x8A7BEC
int CCacheStatus::MINIBAR_X_FIRST = 40;

// 0x8A7BF0
int CCacheStatus::MINIBAR_X_INC = 155;

// 0x8A7BF4
int CCacheStatus::MINIBAR_Y_FIRST = 180;

// 0x8A7BF8
int CCacheStatus::MINIBAR_Y_INC = 80;

// 0x8A7BFC
int CCacheStatus::MINIBAR_NAME_START_X = 20;

// 0x8A7C00
int CCacheStatus::MINIBAR_NAME_SIZE_X = 98;

// 0x8A7C04
int CCacheStatus::MINIBAR_NAME_START_Y = 35;

// 0x8A7C08
int CCacheStatus::MINIBAR_BACKGROUND_START_Y = 8;

// 0x8A7C0C
int CCacheStatus::MINIBAR_FOREGROUND_START_X = 14;

// 0x8A7C10
int CCacheStatus::MINIBAR_FOREGROUND_START_Y = 48;

// 0x8A7C14
int CCacheStatus::dword_8A7C14 = 87;

// 0x8A7C18
int CCacheStatus::MINIBAR_FOREGROUND_FORCE_DISPLAY_SIZE_X = 20;

// 0x8A7C1C
int CCacheStatus::dword_8A7C1C = 24;

// 0x8A7C20
int CCacheStatus::MINIBAR_SKULL_START_X = 116;

// 0x8A7C24
int CCacheStatus::MINIBAR_SKULL_START_Y = 39;

// 0x8A7C28
int CCacheStatus::dword_8A7C28 = 415;

// 0x8A7C2C
int CCacheStatus::PROGRESSBAR_TIMEOUT_CENTER_X = 100;

// 0x8A7C30
int CCacheStatus::PROGRESSBAR_TIMEOUT_START1_Y = 130;

// 0x8A7C34
int CCacheStatus::PROGRESSBAR_TIMEOUT_START2_Y = 142;

// 0x8A7C38
int CCacheStatus::PROGRESSBAR_TIMEOUT_START3_Y = 159;

// 0x8A7C3C
int CCacheStatus::PROGRESSBAR_MAXHINTWIDTH = 466;

// 0x8D0770
int CCacheStatus::dword_8D0770 = TRAVEL_AREA_START_X + 84;

// 0x8D0B7C
int CCacheStatus::dword_8D0B7C = TRAVEL_AREA_START_Y + 47;

// 0x8D0B80
int CCacheStatus::PROGRESSBAR_FOREGROUND_START_X = PROGRESSBAR_BACKGROUND_START_X + 22;

// 0x8D0B8C
int CCacheStatus::PROGRESSBAR_FOREGROUND_START_Y = PROGRESSBAR_BACKGROUND_START_Y + 18;

// 0x8D0B90
int CCacheStatus::PROGRESSBAR_SKULL_START_X = PROGRESSBAR_BACKGROUND_START_X + 623;

// 0x8D0BA0
int CCacheStatus::PROGRESSBAR_SKULL_START_Y = PROGRESSBAR_BACKGROUND_START_Y + 2;

// 0x8D0BA4
int CCacheStatus::MINIBAR_BACKGROUND_START_X;

// 0x8D0BA8;
BOOL CCacheStatus::dword_8D0BA8;

// 0x4400D0
CCacheStatus::CCacheStatus()
{
    m_nScreensDrawn = 0;
    m_bDemandedResources = FALSE;
    m_bTravelScreen = 0;
    m_nProgressBarCaption = 0;
    m_nParchmentCaption = 0;
    m_dwLastUpdateTickCount = 0;
    m_bActivateEngine = FALSE;
    m_bWaiting = FALSE;
}

// 0x440270
CCacheStatus::~CCacheStatus()
{
}

// 0x440400
void CCacheStatus::Init()
{
    if (g_pBaldurChitin->field_4A28) {
        PARCHMENT_TEXT_START_X *= 2;
        PARCHMENT_TEXT_START_Y *= 2;
        dword_8A7BB0 *= 2;
        dword_8A7BB4 *= 2;
        TRAVEL_AREA_START_X *= 2;
        TRAVEL_AREA_START_Y *= 2;
        dword_8D0B7C *= 2;
        dword_8D0770 *= 2;
        UPDATE_TEXT_Y *= 2;
        UPDATE_TEXT_X *= 2;
        PROGRESSBAR_BACKGROUND_START_X *= 2;
        PROGRESSBAR_BACKGROUND_START_Y *= 2;
        PROGRESSBAR_FOREGROUND_START_X *= 2;
        PROGRESSBAR_BACKGROUND_SIZE_X *= 2;
        PROGRESSBAR_FOREGROUND_X_OFFSET *= 2;
        PROGRESSBAR_FOREGROUND_START_Y *= 2;
        PROGRESSBAR_FOREGROUND_SIZE_Y *= 2;
        PROGRESSBAR_FOREGROUND_CAP_OFFSET *= 2;
        MINIBAR_FOREGROUND_CAP_OFFSET *= 2;
        PROGRESSBAR_SKULL_START_X *= 2;
        PROGRESSBAR_SKULL_START_Y *= 2;
        dword_8A7BE4 *= 2;
        dword_8A7BE8 *= 2;
        MINIBAR_X_FIRST *= 2;
        MINIBAR_X_INC *= 2;
        MINIBAR_Y_FIRST *= 2;
        MINIBAR_Y_INC *= 2;
        MINIBAR_NAME_START_X *= 2;
        MINIBAR_NAME_SIZE_X *= 2;
        MINIBAR_NAME_START_Y *= 2;
        MINIBAR_BACKGROUND_START_X *= 2; // NOTE: This value is not initialized.
        MINIBAR_BACKGROUND_START_Y *= 2;
        MINIBAR_FOREGROUND_START_X *= 2;
        MINIBAR_FOREGROUND_START_Y *= 2;
        dword_8A7C14 *= 2;
        MINIBAR_FOREGROUND_FORCE_DISPLAY_SIZE_X *= 2;
        dword_8A7C1C *= 2;
        MINIBAR_SKULL_START_X *= 2;
        MINIBAR_SKULL_START_Y *= 2;
        dword_8A7C28 *= 2;
        PROGRESSBAR_TIMEOUT_CENTER_X *= 2;
        PROGRESSBAR_TIMEOUT_START1_Y *= 2;
        PROGRESSBAR_TIMEOUT_START2_Y *= 2;
        PROGRESSBAR_TIMEOUT_START3_Y *= 2;
        PROGRESSBAR_MAXHINTWIDTH *= 2;
    }
}

// 0x4406A0
void CCacheStatus::InvalidateScreen()
{
    m_nScreensDrawn = 0;
}

// 0x4406B0
void CCacheStatus::Update(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
    STR_RES strRes;
    CString sOutputString;
    CRect clipRect;
    CRect mosaicRect;
    CSize mosSize;
    INT x;
    INT y;
    WORD nScreenWidth;
    WORD nScreenHeight;

    CSingleLock renderLock(&m_critSect, FALSE);
    renderLock.Lock(INFINITE);

    if (!g_pChitin->cProgressBar.m_bProgressBarActivated && nTotalBytes != 0) {
        renderLock.Unlock();
        return;
    }

    CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());
    if (pVidInf == NULL) {
        renderLock.Unlock();
        return;
    }

    if ((!bEnabled || nBytesCopied != 0 || nTotalBytes != 0) && !m_bDemandedResources) {
        renderLock.Unlock();
        return;
    }

    if (bWaiting != m_bWaiting) {
        m_bWaiting = bWaiting;
        m_nScreensDrawn = 0;
    }

    if (nBytesCopied == 0 && nTotalBytes == 0) {
        while (g_pBaldurChitin->field_F8 == TRUE) {
            SleepEx(50, FALSE);
        }

        if (bEnabled == TRUE) {
            for (int side = 0; side < 4; side++) {
                m_mosBorders[side].SetResRef(g_pBaldurChitin->m_aBorderPanels[side].refMosaic, FALSE, TRUE);
                m_mosBorders[side].m_bDoubleSize = g_pBaldurChitin->field_4A28;
            }

            if (bTravel) {
                m_mosBackground.SetResRef(CResRef("GTRSCRN"), FALSE, TRUE);
                m_mosBackground.m_bDoubleSize = g_pBaldurChitin->field_4A28;

                CPoint ptLocation;
                if (g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tAreaLoad.Find(g_pBaldurChitin->GetObjectGame()->field_1B86, ptLocation, TRUE)) {
                    CString sBackground = g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tAreaLoad.GetAt(ptLocation);
                    if (sBackground != "*") {
                        m_mosTravelArea.SetResRef(CResRef(sBackground), FALSE, TRUE);
                        m_mosTravelArea.m_bDoubleSize = g_pBaldurChitin->field_4A28;
                    }
                }
            } else {
                m_mosBackground.SetResRef(CResRef("GPROGBAR"), FALSE, TRUE);
                m_mosBackground.m_bDoubleSize = g_pBaldurChitin->field_4A28;
            }

            m_mosProgressBarSkull.SetResRef(CResRef("GTRBPSK"), FALSE, TRUE);
            m_mosProgressBarSkull.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosProgressBarSkullHighlighted.SetResRef(CResRef("GTRBPSK2"), FALSE, TRUE);
            m_mosProgressBarSkullHighlighted.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosProgressBarBackground.SetResRef(CResRef("GTRBPBG"), FALSE, TRUE);
            m_mosProgressBarBackground.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosProgressBarForeground.SetResRef(CResRef("GTRBPBAR"), FALSE, TRUE);
            m_mosProgressBarForeground.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosProgressBarCap.SetResRef(CResRef("GTRBPCAP"), FALSE, TRUE);
            m_mosProgressBarCap.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_vidFont.SetResRef(CResRef("NORMAL"), g_pBaldurChitin->field_4A28, FALSE);
            m_vidFont.RegisterFont();
            m_vidFont.SetColor(RGB(255, 255, 255), RGB(0, 0, 0), FALSE);

            m_initialsFont.SetResRef(CResRef("INITIALS"), g_pBaldurChitin->field_4A28, FALSE);
            m_initialsFont.RegisterFont();

            m_parchmentFont.SetResRef(CResRef("INFOFONT"), g_pBaldurChitin->field_4A28, FALSE);
            m_parchmentFont.RegisterFont();
            m_parchmentFont.SetColor(RGB(255, 255, 255), RGB(10, 10, 10), FALSE);

            m_skullAnimating.SetResRef(CResRef("SKULANIM"), g_pBaldurChitin->field_4A28, FALSE, TRUE);

            m_mosMinibarSkull.SetResRef(CResRef("GTRSPSK"), FALSE, TRUE);
            m_mosMinibarSkull.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosMinibarSkullHighlighted.SetResRef(CResRef("GTRSPSK2"), FALSE, TRUE);
            m_mosMinibarSkullHighlighted.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosMinibarBackground.SetResRef(CResRef("GTRSPBG"), FALSE, TRUE);
            m_mosMinibarBackground.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosMinibarForeground.SetResRef(CResRef("GTRSPBAR"), FALSE, TRUE);
            m_mosMinibarForeground.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            m_mosMinibarForegroundCap.SetResRef(CResRef("GTRSPCAP"), FALSE, TRUE);
            m_mosMinibarForegroundCap.m_bDoubleSize = g_pBaldurChitin->field_4A28;

            for (int side = 0; side < 4; side++) {
                if (m_mosBorders[side].GetRes() != NULL) {
                    m_mosBorders[side].GetRes()->Demand();
                }
            }

            m_mosBackground.GetRes()->Demand();
            m_mosProgressBarSkull.GetRes()->Demand();
            m_mosProgressBarSkullHighlighted.GetRes()->Demand();
            m_mosProgressBarBackground.GetRes()->Demand();
            m_mosProgressBarForeground.GetRes()->Demand();
            m_mosProgressBarCap.GetRes()->Demand();
            m_vidFont.GetRes()->Demand();
            m_initialsFont.GetRes()->Demand();
            m_parchmentFont.GetRes()->Demand();

            if (m_mosTravelArea.GetResRef().GetResRefStr() != "") {
                m_mosTravelArea.GetRes()->Demand();
            }

            m_skullAnimating.GetRes()->Demand();
            m_mosMinibarSkull.GetRes()->Demand();
            m_mosMinibarSkullHighlighted.GetRes()->Demand();
            m_mosMinibarBackground.GetRes()->Demand();
            m_mosMinibarForeground.GetRes()->Demand();
            m_mosMinibarForegroundCap.GetRes()->Demand();

            g_pBaldurChitin->GetObjectCursor()->SetCursor(100, FALSE);
            g_pBaldurChitin->GetObjectCursor()->m_bVisible = FALSE;
            g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidInf);

            if (g_pBaldurChitin->GetObjectGame()->GetVisibleArea() != NULL) {
                g_pBaldurChitin->cSoundMixer.m_nActiveArea = -1;
                g_pBaldurChitin->cSoundMixer.UpdateSoundList();
                g_pBaldurChitin->m_pEngineWorld->m_weather.OnAreaChange(TRUE);
            }

            m_bDemandedResources = TRUE;
            m_nScreensDrawn = 0;
            m_bTravelScreen = bTravel;
            m_nProgressBarCaption = nProgressBarCaption;
            m_nParchmentCaption = nParchmentCaption;
            m_dwLastUpdateTickCount = GetTickCount();

            m_nCurrentHint = GetPrivateProfileIntA("Game Options",
                "Current Loading Hint",
                0,
                g_pBaldurChitin->GetIniFileName());
            if (m_nCurrentHint > g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetNumLoadingHints()) {
                m_nCurrentHint = 0;
            }

            sOutputString.Format("%d", m_nCurrentHint);
            WritePrivateProfileStringA("Game Options",
                "Current Loading Hint",
                sOutputString,
                g_pBaldurChitin->GetIniFileName());
        } else {
            for (int side = 0; side < 4; side++) {
                if (m_mosBorders[side].GetRes() != NULL) {
                    m_mosBorders[side].GetRes()->Release();
                }
            }

            m_mosBackground.GetRes()->Release();

            if (m_mosTravelArea.GetResRef().GetResRefStr() != "") {
                m_mosTravelArea.GetRes()->Release();
            }

            m_mosProgressBarSkull.GetRes()->Release();
            m_mosProgressBarSkullHighlighted.GetRes()->Release();
            m_mosProgressBarBackground.GetRes()->Release();
            m_mosProgressBarForeground.GetRes()->Release();
            m_mosProgressBarCap.GetRes()->Release();
            m_skullAnimating.GetRes()->Release();
            m_vidFont.GetRes()->Release();
            m_vidFont.Unload();
            m_initialsFont.GetRes()->Release();
            m_initialsFont.Unload();
            m_parchmentFont.GetRes()->Release();
            m_parchmentFont.Unload();
            m_mosMinibarSkull.GetRes()->Release();
            m_mosMinibarSkullHighlighted.GetRes()->Release();
            m_mosMinibarBackground.GetRes()->Release();
            m_mosMinibarForeground.GetRes()->Release();
            m_mosMinibarForegroundCap.GetRes()->Release();

            m_bDemandedResources = FALSE;

            STRREF strHint = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetLoadingHint(m_nCurrentHint);
            g_pBaldurChitin->GetTlkTable().Fetch(strHint, strRes);
            sOutputString.Format(strRes.szText);

            int pos = 0;
            while ((pos = CUtil::Find(sOutputString, '\n', pos)) != -1) {
                // FIXME: Why not `SetAt`?
                sOutputString = sOutputString.Left(pos) + ' ' + sOutputString.Mid(pos + 1);
            }

            g_pBaldurChitin->m_pEngineWorld->DisplayText(CString(""),
                sOutputString,
                RGB(0, 0, 0),
                RGB(245, 245, 150),
                -1,
                FALSE);
            g_pBaldurChitin->m_pEngineWorld->DisplayText(CString(""), CString(""), -1, FALSE);

            if (m_bActivateEngine) {
                m_bActivateEngine = FALSE;

                CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
                if (pEngine != NULL) {
                    pEngine->EngineActivated();
                }

                g_pChitin->Resume();
            }

            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, TRUE);
            g_pBaldurChitin->GetObjectCursor()->m_bVisible = TRUE;
            g_pBaldurChitin->GetObjectCursor()->CursorUpdate(g_pBaldurChitin->GetActiveEngine()->pVidMode);

            g_pBaldurChitin->GetActiveEngine()->GetManager()->InvalidateRect(NULL);

            m_nScreensDrawn = 0;
            m_bTravelScreen = FALSE;
            m_nProgressBarCaption = 0;
            m_nParchmentCaption = 0;

            while (g_pBaldurChitin->m_bReInitializing) {
                SleepEx(25, FALSE);
            }

            if (g_pBaldurChitin->GetObjectGame()->GetVisibleArea() != NULL) {
                g_pBaldurChitin->cSoundMixer.m_nActiveArea = reinterpret_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetVisibleArea());
                g_pBaldurChitin->cSoundMixer.UpdateSoundList();
                g_pBaldurChitin->m_pEngineWorld->m_weather.OnAreaChange(FALSE);
                if (g_pBaldurChitin->cSoundMixer.sub_7ACA10()) {
                    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
                    pArea->m_startedMusicCounter = 10;
                    pArea->m_startedMusic = FALSE;
                }
            }
        }
    } else {
        if (bDisplayMinibars == TRUE) {
            m_nScreensDrawn = 0;
        }

        if (GetTickCount() - m_dwLastUpdateTickCount >= 3000) {
            m_dwLastUpdateTickCount = GetTickCount();
            m_nScreensDrawn = 0;
        }

        if (g_pBaldurChitin->field_4A28) {
            x = CVideo::SCREENWIDTH / 2 - CBaldurChitin::DEFAULT_SCREEN_WIDTH;
            y = CVideo::SCREENHEIGHT / 2 - CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
            nScreenWidth = CBaldurChitin::DEFAULT_SCREEN_WIDTH * 2;
            nScreenHeight = CBaldurChitin::DEFAULT_SCREEN_HEIGHT * 2;
        } else {
            x = (CVideo::SCREENWIDTH - CBaldurChitin::DEFAULT_SCREEN_WIDTH) / 2;
            y = (CVideo::SCREENHEIGHT - CBaldurChitin::DEFAULT_SCREEN_HEIGHT) / 2;
            nScreenWidth = CBaldurChitin::DEFAULT_SCREEN_WIDTH;
            nScreenHeight = CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
        }

        if (m_bDemandedResources == TRUE && m_nScreensDrawn < 2 && !g_pBaldurChitin->m_bReInitializing) {
            clipRect.left = 0;
            clipRect.top = 0;
            clipRect.right = CVideo::SCREENWIDTH;
            clipRect.bottom = CVideo::SCREENHEIGHT;

            for (int side = 0; side < 4; side++) {
                // NOTE: Inlining.
                UI_PANELHEADER* panelInfo = side < 4
                    ? &(g_pBaldurChitin->m_aBorderPanels[side])
                    : NULL;

                if (g_pBaldurChitin->field_4A28) {
                    mosaicRect.left = 0;
                    mosaicRect.top = 0;
                    mosaicRect.right = 2 * panelInfo->nWidth;
                    mosaicRect.bottom = 2 * panelInfo->nHeight;
                    if (panelInfo->nWidth > 0 && panelInfo->nHeight > 0) {
                        m_mosBorders[side].Render(CVIDINF_SURFACE_BACK,
                            2 * panelInfo->x,
                            2 * panelInfo->y,
                            mosaicRect,
                            clipRect,
                            0x1,
                            TRUE);
                    }
                } else {
                    mosaicRect.left = 0;
                    mosaicRect.top = 0;
                    mosaicRect.right = panelInfo->nWidth;
                    mosaicRect.bottom = panelInfo->nHeight;
                    if (panelInfo->nWidth > 0 && panelInfo->nHeight > 0) {
                        m_mosBorders[side].Render(CVIDINF_SURFACE_BACK,
                            panelInfo->x,
                            panelInfo->y,
                            mosaicRect,
                            clipRect,
                            0x1,
                            TRUE);
                    }
                }
            }

            mosaicRect.left = 0;
            mosaicRect.top = 0;
            mosaicRect.right = nScreenWidth;
            mosaicRect.bottom = nScreenHeight;

            clipRect.left = x;
            clipRect.top = y;
            clipRect.right = x + nScreenWidth;
            clipRect.bottom = y + nScreenHeight;

            m_mosBackground.Render(CVIDINF_SURFACE_BACK,
                x,
                y,
                mosaicRect,
                clipRect,
                0x1,
                TRUE);

            if (m_nProgressBarCaption != 0 && !m_bTravelScreen) {
                if (pVidInf->BKLock(clipRect)) {
                    g_pBaldurChitin->GetTlkTable().Fetch(m_nProgressBarCaption, strRes);
                    sOutputString.Format(strRes.szText);
                    pVidInf->BKTextOut(&m_vidFont,
                        sOutputString,
                        PARCHMENT_TEXT_START_X - m_vidFont.GetStringLength(sOutputString, TRUE) / 2,
                        PARCHMENT_TEXT_START_Y,
                        mosaicRect,
                        0,
                        TRUE);
                    pVidInf->BKUnlock();
                }
            }

            if (m_bTravelScreen == TRUE) {
                if (m_mosTravelArea.cResRef.GetResRefStr() != "") {
                    m_mosTravelArea.GetSize(mosSize, TRUE);

                    mosaicRect.left = 0;
                    mosaicRect.top = 0;
                    mosaicRect.right = mosSize.cx;
                    mosaicRect.bottom = mosSize.cy;

                    m_mosTravelArea.Render(CVIDINF_SURFACE_BACK,
                        x + TRAVEL_AREA_START_X,
                        y + TRAVEL_AREA_START_Y,
                        mosaicRect,
                        clipRect,
                        0x1,
                        TRUE);
                }

                if (m_nParchmentCaption != 0) {
                    if (pVidInf->BKLock(clipRect)) {
                        CString sTemp;
                        g_pBaldurChitin->GetTlkTable().Fetch(m_nParchmentCaption, strRes);
                        sTemp = strRes.szText;
                        pVidInf->BKTextOut(&m_vidFont,
                            sTemp,
                            PARCHMENT_TEXT_START_X - m_vidFont.GetStringLength(sTemp, TRUE) / 2,
                            PARCHMENT_TEXT_START_Y,
                            mosaicRect,
                            0,
                            TRUE);
                        pVidInf->BKUnlock();
                    }
                }
            }

            m_nScreensDrawn++;
        }

        if (m_bDemandedResources == TRUE && m_nScreensDrawn != 0 && !g_pBaldurChitin->m_bReInitializing) {
            LONG v1;
            if (nTotalBytes != 0) {
                v1 = PROGRESSBAR_FOREGROUND_START_X
                    + PROGRESSBAR_FOREGROUND_X_OFFSET
                    + static_cast<LONG>(static_cast<float>(nBytesCopied) / static_cast<float>(nTotalBytes) * static_cast<float>(PROGRESSBAR_BACKGROUND_SIZE_X - PROGRESSBAR_FOREGROUND_X_OFFSET));
            } else {
                v1 = PROGRESSBAR_FOREGROUND_START_X + PROGRESSBAR_FOREGROUND_X_OFFSET;
            }

            if (!g_pBaldurChitin->field_F8) {
                if (bDisplayMinibars == TRUE) {
                    if (bTimeoutCounter == TRUE) {
                        clipRect.left = x;
                        clipRect.top = y;
                        clipRect.right = x + nScreenWidth;
                        clipRect.bottom = y + nScreenHeight;

                        if (pVidInf->BKLock(clipRect)) {
                            CString sTemp;

                            clipRect.left = 0;
                            clipRect.top = 0;
                            clipRect.right = CVideo::SCREENWIDTH;
                            clipRect.bottom = CVideo::SCREENHEIGHT;

                            g_pBaldurChitin->GetTlkTable().Fetch(13980, strRes);
                            sTemp = strRes.szText;
                            pVidInf->BKTextOut(&m_vidFont,
                                sTemp,
                                PROGRESSBAR_TIMEOUT_CENTER_X - m_vidFont.GetStringLength(sTemp, TRUE) / 2,
                                PROGRESSBAR_TIMEOUT_START1_Y,
                                clipRect,
                                0,
                                TRUE);

                            g_pBaldurChitin->GetTlkTable().Fetch(11794, strRes);
                            sTemp = strRes.szText;
                            pVidInf->BKTextOut(&m_vidFont,
                                sTemp,
                                PROGRESSBAR_TIMEOUT_CENTER_X - m_vidFont.GetStringLength(sTemp, TRUE) / 2,
                                PROGRESSBAR_TIMEOUT_START2_Y,
                                clipRect,
                                0,
                                TRUE);

                            sTemp.Format("%d", nSecondsToTimeout);
                            sTemp = strRes.szText;
                            pVidInf->BKTextOut(&m_vidFont,
                                sTemp,
                                PROGRESSBAR_TIMEOUT_CENTER_X - m_vidFont.GetStringLength(sTemp, TRUE) / 2,
                                PROGRESSBAR_TIMEOUT_START3_Y,
                                clipRect,
                                0,
                                TRUE);

                            pVidInf->BKUnlock();
                        }
                    }

                    for (SHORT nColumn = 0; nColumn < 2; nColumn++) {
                        for (SHORT nRow = 0; nRow < 3; nRow++) {
                            SHORT nPlayerIndex = nColumn * 2 + nRow;
                            CString sPlayerName;
                            BOOLEAN bWaitingArea;
                            LONG nWaitReason;
                            DWORD nCopied;
                            DWORD nToCopy;
                            DWORD nStartX;
                            DWORD nStartY;

                            if (g_pChitin->cNetwork.GetPlayerID(nPlayerIndex) != 0) {
                                g_pChitin->cNetwork.GetPlayerName(nPlayerIndex, sPlayerName);
                                if (g_pChitin->cNetwork.m_nLocalPlayer == nPlayerIndex) {
                                    bWaitingArea = bWaiting;
                                    nCopied = nBytesCopied;
                                    nToCopy = nTotalBytes;
                                } else {
                                    bWaitingArea = g_pChitin->cProgressBar.GetRemoteWaiting(nPlayerIndex);
                                    nWaitReason = g_pChitin->cProgressBar.GetRemoteWaitingReason(nPlayerIndex);
                                    nCopied = g_pChitin->cProgressBar.GetRemoteActionProgres(nPlayerIndex);
                                    nToCopy = g_pChitin->cProgressBar.GetRemoteActionTarget(nPlayerIndex);
                                }

                                nStartX = MINIBAR_X_FIRST + nColumn * (dword_8A7C28 + MINIBAR_X_INC);
                                nStartY = MINIBAR_Y_FIRST + nRow * MINIBAR_Y_INC;

                                clipRect.left = x + nStartX;
                                clipRect.top = y + nStartY;
                                clipRect.right = clipRect.left + MINIBAR_X_INC;
                                clipRect.bottom = clipRect.top + MINIBAR_Y_INC;

                                m_mosMinibarBackground.GetSize(mosSize, TRUE);

                                mosaicRect.left = 0;
                                mosaicRect.top = 0;
                                mosaicRect.right = mosSize.cx;
                                mosaicRect.bottom = mosSize.cy;

                                m_mosMinibarBackground.Render(CVIDINF_SURFACE_BACK,
                                    x + nStartX + MINIBAR_BACKGROUND_START_X,
                                    y + nStartY + MINIBAR_BACKGROUND_START_Y,
                                    mosaicRect,
                                    clipRect,
                                    0x1,
                                    TRUE);

                                m_mosMinibarSkullHighlighted.GetSize(mosSize, TRUE);

                                mosaicRect.left = 0;
                                mosaicRect.top = 0;
                                mosaicRect.right = mosSize.cx;
                                mosaicRect.bottom = mosSize.cy;

                                if (static_cast<float>(nCopied) / static_cast<float>(nToCopy) >= 0.99
                                    || (bWaitingArea == TRUE && rand() % 16 > 8)) {
                                    m_mosMinibarSkullHighlighted.Render(CVIDINF_SURFACE_BACK,
                                        x + nStartX + MINIBAR_SKULL_START_X,
                                        y + nStartY + MINIBAR_SKULL_START_Y,
                                        mosaicRect,
                                        clipRect,
                                        0x1,
                                        TRUE);
                                } else {
                                    m_mosMinibarSkull.Render(CVIDINF_SURFACE_BACK,
                                        x + nStartX + MINIBAR_SKULL_START_X,
                                        y + nStartY + MINIBAR_SKULL_START_Y,
                                        mosaicRect,
                                        clipRect,
                                        0x1,
                                        TRUE);
                                }

                                INT nLength = MINIBAR_FOREGROUND_START_X + nStartX + MINIBAR_FOREGROUND_FORCE_DISPLAY_SIZE_X;
                                if (nToCopy != 0) {
                                    nLength += static_cast<INT>(static_cast<float>(nCopied) / static_cast<float>(nToCopy) * static_cast<float>(dword_8A7C14 - MINIBAR_FOREGROUND_FORCE_DISPLAY_SIZE_X));
                                }

                                m_mosMinibarForeground.GetSize(mosSize, TRUE);

                                mosaicRect.top = 0;
                                mosaicRect.left = 0;
                                mosaicRect.right = mosSize.cx;
                                mosaicRect.bottom = mosSize.cy;

                                clipRect.left = x + nStartX + MINIBAR_FOREGROUND_START_X;
                                clipRect.top = 0;
                                clipRect.right = x + nLength;
                                clipRect.bottom = CVideo::SCREENHEIGHT;

                                m_mosMinibarForeground.Render(CVIDINF_SURFACE_BACK,
                                    clipRect.left,
                                    y + nStartY + MINIBAR_FOREGROUND_START_Y,
                                    mosaicRect,
                                    clipRect,
                                    0x1,
                                    TRUE);

                                m_mosMinibarForegroundCap.GetSize(mosSize, TRUE);

                                mosaicRect.top = 0;
                                mosaicRect.left = 0;
                                mosaicRect.right = mosSize.cx;
                                mosaicRect.bottom = mosSize.cy;

                                clipRect.left = x + nStartX;
                                clipRect.top = y + nStartY;
                                clipRect.right = clipRect.left + MINIBAR_X_INC;
                                clipRect.bottom = clipRect.top + MINIBAR_Y_INC;

                                m_mosMinibarForegroundCap.Render(CVIDINF_SURFACE_BACK,
                                    x + nLength,
                                    y + nStartY + MINIBAR_FOREGROUND_START_Y + MINIBAR_FOREGROUND_CAP_OFFSET,
                                    mosaicRect,
                                    clipRect,
                                    0x1,
                                    TRUE);

                                clipRect.left = 0;
                                clipRect.top = 0;
                                clipRect.right = CVideo::SCREENWIDTH;
                                clipRect.bottom = CVideo::SCREENHEIGHT;

                                if (pVidInf->BKLock(clipRect)) {
                                    clipRect.left = x + nStartX + MINIBAR_NAME_START_X;
                                    clipRect.right = clipRect.left + MINIBAR_NAME_SIZE_X;

                                    pVidInf->BKTextOut(&m_vidFont,
                                        sPlayerName,
                                        clipRect.left,
                                        y + nStartY + MINIBAR_NAME_START_Y,
                                        clipRect,
                                        0,
                                        TRUE);
                                    pVidInf->BKUnlock();
                                }
                            }
                        }
                    }
                } else {
                    m_mosProgressBarBackground.GetSize(mosSize, TRUE);

                    mosaicRect.left = 0;
                    mosaicRect.top = 0;
                    mosaicRect.right = mosSize.cx;
                    mosaicRect.bottom = mosSize.cy;

                    // FIXME: Original code does not have initialization for
                    // `clipRect`. In some circumstances it leads to highlighted
                    // image well, not being highlighted.

                    m_mosProgressBarBackground.Render(CVIDINF_SURFACE_BACK,
                        x + PROGRESSBAR_BACKGROUND_START_X,
                        y + PROGRESSBAR_BACKGROUND_START_Y,
                        mosaicRect,
                        clipRect,
                        0x1,
                        TRUE);

                    if (!bWaiting) {
                        m_mosProgressBarSkullHighlighted.GetSize(mosSize, TRUE);

                        mosaicRect.left = 0;
                        mosaicRect.top = 0;
                        mosaicRect.right = mosSize.cx;
                        mosaicRect.bottom = mosSize.cy;

                        if (static_cast<float>(nBytesCopied) / static_cast<float>(nTotalBytes) >= 0.99f) {
                            m_mosProgressBarSkullHighlighted.Render(CVIDINF_SURFACE_BACK,
                                x + PROGRESSBAR_SKULL_START_X,
                                y + PROGRESSBAR_SKULL_START_Y,
                                mosaicRect,
                                clipRect,
                                0x1,
                                TRUE);
                        } else {
                            m_mosProgressBarSkull.Render(CVIDINF_SURFACE_BACK,
                                x + PROGRESSBAR_SKULL_START_X,
                                y + PROGRESSBAR_SKULL_START_Y,
                                mosaicRect,
                                clipRect,
                                0x1,
                                TRUE);
                        }
                    }

                    mosaicRect.left = 0;
                    mosaicRect.top = 0;
                    mosaicRect.right = v1 - PROGRESSBAR_FOREGROUND_START_X;
                    mosaicRect.bottom = PROGRESSBAR_FOREGROUND_SIZE_Y;

                    clipRect.left = x + PROGRESSBAR_FOREGROUND_START_X;
                    clipRect.top = 0;
                    clipRect.right = x + v1;
                    clipRect.bottom = CVideo::SCREENHEIGHT;

                    m_mosProgressBarForeground.Render(CVIDINF_SURFACE_BACK,
                        x + PROGRESSBAR_FOREGROUND_START_X,
                        y + PROGRESSBAR_FOREGROUND_START_Y,
                        mosaicRect,
                        clipRect,
                        0x1,
                        TRUE);

                    clipRect.left = 0;
                    clipRect.top = 0;
                    clipRect.right = CVideo::SCREENWIDTH;
                    clipRect.bottom = CVideo::SCREENHEIGHT;

                    m_mosProgressBarCap.GetSize(mosSize, TRUE);
                    m_mosProgressBarCap.Render(CVIDINF_SURFACE_BACK,
                        x + v1,
                        y + PROGRESSBAR_FOREGROUND_START_Y + PROGRESSBAR_FOREGROUND_CAP_OFFSET,
                        mosaicRect,
                        clipRect,
                        0x1,
                        TRUE);

                    clipRect.left = x;
                    clipRect.top = y;
                    clipRect.right = x + nScreenWidth;
                    clipRect.bottom = y + nScreenHeight;

                    if (pVidInf->BKLock(clipRect)) {
                        if (bWaiting == TRUE) {
                            CString sTemp;

                            g_pBaldurChitin->GetTlkTable().Fetch(nWaitingReason, strRes);
                            sTemp = strRes.szText;
                            pVidInf->BKTextOut(&m_vidFont,
                                sTemp,
                                UPDATE_TEXT_X - m_vidFont.GetStringLength(sTemp, TRUE) / 2,
                                UPDATE_TEXT_Y,
                                clipRect,
                                0,
                                TRUE);

                            if (m_skullAnimating.IsEndOfSequence(TRUE)) {
                                m_skullAnimating.FrameSet(0);
                            } else {
                                m_skullAnimating.FrameAdvance();
                            }

                            m_skullAnimating.RealizePalette(0x1);

                            pVidInf->BKRender(&m_skullAnimating,
                                PROGRESSBAR_SKULL_START_X,
                                PROGRESSBAR_SKULL_START_Y,
                                clipRect,
                                0x1,
                                TRUE);
                        } else {
                            STRREF strHint = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetLoadingHint(m_nCurrentHint);
                            CString sStrings[4];

                            g_pBaldurChitin->GetTlkTable().Fetch(strHint, strRes);

                            sOutputString.Format(strRes.szText);

                            int pos = 0;
                            while ((pos = CUtil::Find(sOutputString, '\n', pos)) != -1) {
                                // FIXME: Why not `SetAt`?
                                sOutputString = sOutputString.Left(pos) + ' ' + sOutputString.Mid(pos + 1);
                            }

                            INT nLines = CUtil::SplitString(&m_vidFont,
                                sOutputString,
                                PROGRESSBAR_MAXHINTWIDTH,
                                4,
                                sStrings,
                                FALSE,
                                TRUE,
                                FALSE,
                                -1);
                            if (nLines > 1) {
                                nLines = CUtil::SplitString(&m_vidFont,
                                    sOutputString,
                                    PROGRESSBAR_MAXHINTWIDTH,
                                    4,
                                    sStrings,
                                    FALSE,
                                    TRUE,
                                    FALSE,
                                    static_cast<WORD>((m_vidFont.GetStringLength(sOutputString, TRUE) + nLines - 1) / nLines));
                            }

                            INT nFontHeight;
                            switch (nLines) {
                            case 2:
                                nFontHeight = m_vidFont.GetFontHeight(TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[0],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[0], TRUE) / 2,
                                    UPDATE_TEXT_Y - nFontHeight,
                                    clipRect,
                                    0,
                                    TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[1],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[1], TRUE) / 2,
                                    UPDATE_TEXT_Y + nFontHeight,
                                    clipRect,
                                    0,
                                    TRUE);
                                break;
                            case 3:
                                nFontHeight = m_vidFont.GetFontHeight(TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[0],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[0], TRUE) / 2,
                                    UPDATE_TEXT_Y - nFontHeight,
                                    clipRect,
                                    0,
                                    TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[1],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[1], TRUE) / 2,
                                    UPDATE_TEXT_Y,
                                    clipRect,
                                    0,
                                    TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[2],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[2], TRUE) / 2,
                                    UPDATE_TEXT_Y + nFontHeight,
                                    clipRect,
                                    0,
                                    TRUE);
                                break;
                            case 4:
                                nFontHeight = m_vidFont.GetFontHeight(TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[0],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[0], TRUE) / 2,
                                    UPDATE_TEXT_Y - 3 * nFontHeight / 2,
                                    clipRect,
                                    0,
                                    TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[1],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[1], TRUE) / 2,
                                    UPDATE_TEXT_Y - nFontHeight / 2,
                                    clipRect,
                                    0,
                                    TRUE);
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[2],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[2], TRUE) / 2,
                                    UPDATE_TEXT_Y + nFontHeight,
                                    clipRect,
                                    0,
                                    TRUE);
                                // FIXME: Where is line 4?
                                break;
                            default:
                                pVidInf->BKTextOut(&m_vidFont,
                                    sStrings[0],
                                    UPDATE_TEXT_X - m_vidFont.GetStringLength(sStrings[0], TRUE) / 2,
                                    UPDATE_TEXT_Y,
                                    clipRect,
                                    0,
                                    TRUE);
                                break;
                            }
                        }

                        pVidInf->BKUnlock();
                    }
                }

                pVidInf->Flip(FALSE);
            } else {
                m_nScreensDrawn = 0;
            }
        }
    }

    renderLock.Unlock();
    dword_8D0BA8 = TRUE;
}

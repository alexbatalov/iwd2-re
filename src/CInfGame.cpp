#include "CInfGame.h"

#include <process.h>

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CBaldurProjector.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSave.h"
#include "CScreenSinglePlayer.h"
#include "CScreenWorldMap.h"
#include "CSearchBitmap.h"
#include "CUIControlBase.h"
#include "CUIManager.h"
#include "CUIPanel.h"

// 0x8E707C
const CString CInfGame::FOGOWAR_RESREF("FOGOWAR");

// 0x8E74AC
const CString CInfGame::SAVE_OBJECT_LIST_NAME("SVTRIOBJ");

// 0x8E74F4
const CString CInfGame::CHAPTER_GLOBAL("CHAPTER");

// 0x8E74E8
const CString CInfGame::TOKEN_CURRENT_CHAPTER("CurrentChapter");

// 0x8E7510
const CString CInfGame::TOKEN_CHARACTER("CHARNAME");

// 0x8E7498
const CString CInfGame::TOKEN_GABBER("GABBER");

// 0x8E7064
const CString CInfGame::TOKEN_SIRMAAM("PROTAGONIST_SIRMAAM");

// 0x8E7084
const CString CInfGame::TOKEN_GIRLBOY("PROTAGONIST_GIRLBOY");

// 0x8E74FC
const CString CInfGame::TOKEN_BROTHERSISTER("PROTAGONIST_BROTHERSISTER");

// 0x8E7060
const CString CInfGame::TOKEN_LADYLORD("PROTAGONIST_LADYLORD");

// 0x8E7520
const CString CInfGame::TOKEN_MALEFEMALE("PROTAGONIST_MALEFEMALE");

// 0x8E7518
const CString CInfGame::TOKEN_HESHE("PROTAGONIST_HESHE");

// 0x8E7504
const CString CInfGame::TOKEN_HISHER("PROTAGONIST_HISHER");

// 0x8E74DC
const CString CInfGame::TOKEN_RACE("PROTAGONIST_RACE");

// 0x8E74D0
const CString CInfGame::TOKEN_HIMHER("PROTAGONIST_HIMHER");

// 0x8E7074
const CString CInfGame::TOKEN_MANWOMAN("PROTAGONIST_MANWOMAN");

// 0x8E74C4
const CString CInfGame::TOKEN_GABBER_SIRMAAM("SIRMAAM");

// 0x8E7070
const CString CInfGame::TOKEN_GABBER_GIRLBOY("GIRLBOY");

// 0x8E74E4
const CString CInfGame::TOKEN_GABBER_BROTHERSISTER("BROTHERSISTER");

// 0x8E7088
const CString CInfGame::TOKEN_GABBER_LADYLORD("LADYLORD");

// 0x8E7080
const CString CInfGame::TOKEN_GABBER_MALEFEMALE("MALEFEMALE");

// 0x8E751C
const CString CInfGame::TOKEN_GABBER_HESHE("HESHE");

// 0x8E74EC
const CString CInfGame::TOKEN_GABBER_HISHER("HISHER");

// 0x8E708C
const CString CInfGame::TOKEN_GABBER_RACE("RACE");

// 0x8E74C8
const CString CInfGame::TOKEN_GABBER_HIMHER("HIMHER");

// 0x8E74F0
const CString CInfGame::TOKEN_GABBER_MANWOMAN("MANWOMAN");

// 0x8E7494
const CString CInfGame::TOKEN_PLAYER1("PLAYER1");

// 0x8E74BC
const CString CInfGame::TOKEN_PLAYER2("PLAYER2");

// 0x8E7490
const CString CInfGame::TOKEN_PLAYER3("PLAYER3");

// 0x8E74A4
const CString CInfGame::TOKEN_PLAYER4("PLAYER4");

// 0x8E74C0
const CString CInfGame::TOKEN_PLAYER5("PLAYER5");

// 0x8E749C
const CString CInfGame::TOKEN_PLAYER6("PLAYER6");

// 0x8E74D8
const CString CInfGame::TOKEN_SURFACE_UNDERDARK("SURFACE_UNDERDARK");

// 0x8E74D4
const CString CInfGame::AUTO_SAVE_NAME("000000000-Auto-Save");

// 0x8E7508
const CString CInfGame::QUICK_SAVE_NAME("000000002-Quick-Save");

// 0x8E750C
const CString CInfGame::QUICK_SAVE_BACKUP_NAME("000000001-Quick-Save-Backup");

// 0x8E706C
const CString CInfGame::SILHOUETTE_PORTRAIT_SM("noportsm");

// 0x8E705C
const CString CInfGame::SILHOUETTE_PORTRAIT_LG("noportlg");

// 0x59CC30
CInfGame::CInfGame()
{
    // TODO: Incomplete.
}

// 0x59ECB0
CInfGame::~CInfGame()
{
    // TODO: Incomplete.
}

// 0x59F500
void CInfGame::StartSearchThread()
{
    if (_beginthread(SearchThreadMain, 0, NULL) == -1) {
        CloseHandle(m_hSearchThread);
        m_hSearchThread = NULL;
    }
}

// 0x5AA350
void CInfGame::SaveOptions()
{
    // TODO: Incomplete.
}

// 0x5AF360
void CInfGame::UpdatePortrait(SHORT nPortrait, DWORD dwPanelId)
{
    if (nPortrait != -1) {
        CBaldurEngine* pEngine = static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine);
        if (pEngine != g_pBaldurChitin->m_pEngineProjector
            && pEngine != g_pBaldurChitin->m_pEngineMultiPlayer
            && pEngine != g_pBaldurChitin->m_pEngineSinglePlayer
            && pEngine != g_pBaldurChitin->m_pEngineWorldMap
            && pEngine != g_pBaldurChitin->m_pEngineSave) {
            CUIManager* pManager = pEngine->GetManager();
            CUIPanel* pPanel = pManager->GetPanel(dwPanelId);
            if (pPanel != NULL) {
                CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                if (pControl != NULL) {
                    pControl->InvalidateRect();
                }
            } else {
                // NOTE: Obtaining active engine second time, probably some
                // inlining. Looks similar to `CBaldurEngine::OnPortraitLClick`.
                CUIManager* pManager = static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->GetManager();
                CUIPanel* pPanel = pManager->GetPanel(1);
                if (pPanel != NULL) {
                    CUIControlBase* pControl = pPanel->GetControl(nPortrait);
                    if (pControl != NULL) {
                        pControl->InvalidateRect();
                    }
                }
            }
        }
    }
}

// 0x5AF4E0
SHORT CInfGame::GetCharacterPortaitNum(LONG nCharacterId)
{
    if (nCharacterId != -1) {
        for (SHORT nPortrait = 0; nPortrait < 6; nPortrait++) {
            if (m_nCharacterPortaits[nPortrait] == nCharacterId) {
                return nPortrait;
            }
        }
    }

    return -1;
}

// 0x5BB800
BOOL CInfGame::Is3DSound(int nSoundChannel)
{
    return m_ruleTables.Is3DSound(nSoundChannel);
}

// 0x5BB810
float CInfGame::GetSoundReverbMix(int nSoundChannel, int nReverb)
{
    return m_ruleTables.GetSoundReverbMix(nSoundChannel, nReverb);
}

// 0x5BE900
void CInfGame::SynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x5C0EA0
void CInfGame::ApplyVolumeSliders(BOOLEAN a2)
{
    g_pBaldurChitin->cSoundMixer.SetMusicVolume(m_cOptions.m_nVolumeMusic);

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(0, m_cOptions.m_nVolumeVoices);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(1, m_cOptions.m_nVolumeAmbients);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(3, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(4, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(5, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeVoices);

    for (int k = 7; k < 13; k++) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(k, m_cOptions.m_nVolumeVoices);
    }

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(13, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(14, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(15, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(20, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(18, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(19, m_cOptions.m_nVolumeSFX);

    if (a2 == TRUE) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, m_cOptions.m_nVolumeAmbients);
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, m_cOptions.m_nVolumeAmbients);
    }

    g_pBaldurChitin->cSoundMixer.UpdateSoundList();
}

// 0x5C1E30
BOOL CInfGame::CanRestParty(STRREF& strError, unsigned char a2, unsigned char a3, unsigned char a4)
{
    // TODO: Incomplete.

    return FALSE;
}

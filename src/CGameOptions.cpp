#include "CGameOptions.h"

// 0x5C9B60
CGameOptions::CGameOptions()
{
    field_B4 = 0;
    field_BC = 0;
    m_bGore = TRUE;
    field_4 = 0;
    m_nMouseScrollSpeed = 28;
    m_bSubtitles = FALSE;
    m_nGuiFeedbackLevel = 3;
    m_nLocatorFeedbackLevel = 3;
    m_nVolumeMusic = 50;
    m_nVolumeSFX = 50;
    m_nVolumeVoices = 50;
    m_nVolumeAmbients = 50;
    m_nVolumeMovie = 50;
    m_bFootStepsSounds = TRUE;
    field_30 = 1;
    m_bTranslucentShadows = TRUE;
    field_38 = 0;
    field_3C = 0;
    m_nTooltips = 30;
    field_44 = 3000;
    m_nCommandSoundsFrequency = 2;
    m_nSelectionSoundsFrequency = 3;
    m_bAlwaysDither = TRUE;
    m_nDifficultyLevel = 3;
    m_nKeyboardScrollSpeed = 36;
    m_nEffectTextLevel = 62;
    field_5C = 1;
    m_bAttackSounds = TRUE;
    m_nAutoPauseState = 0;
    m_bAutoPauseCenter = TRUE;
    m_nDifficultyMultiplier = 0;
    m_nMPDifficultyMultiplier = 0;
    m_bDarkvision = FALSE;
    field_7C = 1;
    m_bWeatherEnabled = TRUE;
    field_84 = 0;
    m_bEnvironmentalAudio = TRUE;
    field_8C = 0;
    m_bDisplayMovieSubtitles = FALSE;
    field_94 = 1;
    m_bStaticAnimations = TRUE;
    m_bTranslucentBlts = TRUE;
    m_bMaxHP = FALSE;
    m_bAutoPauseOnTrap = FALSE;
    field_A8 = 0;
    field_AC = 0;
    field_B0 = 1;
    field_B8 = 0;
    field_C0 = 100;
    field_C2 = 0;
    field_C6 = 16;
    field_CA = 10;
    m_nShadedSelectionBox = 0;
    field_D2 = 1;
    field_D6 = 0;
    field_DA = 0;
}

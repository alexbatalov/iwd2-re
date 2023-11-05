#include "CGameOptions.h"

#include "CScreenWorld.h"

// 0x5C9B60
CGameOptions::CGameOptions()
{
    m_bHotkeysOnToolTips = FALSE;
    m_bDuplicateFloatingText = FALSE;
    m_nGore = 1;
    m_nGoreOption = 0;
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
    m_nBoredTime = CScreenWorld::BORED_TIME;
    m_nCommandSoundsFrequency = 2;
    m_nSelectionSoundsFrequency = 3;
    m_bAlwaysDither = TRUE;
    m_nDifficultyLevel = 3;
    m_nKeyboardScrollSpeed = 36;
    m_nEffectTextLevel = 62;
    m_nTutorialState = 1;
    m_bAttackSounds = TRUE;
    m_nAutoPauseState = 0;
    m_bAutoPauseCenter = TRUE;
    m_nDifficultyMultiplier = 0;
    m_nMPDifficultyMultiplier = 0;
    m_bDarkvision = FALSE;
    m_bQuickItemMapping = TRUE;
    m_bWeatherEnabled = TRUE;
    m_bCheatsEnabled = FALSE;
    m_bEnvironmentalAudio = TRUE;
    m_bTerrainHugging = FALSE;
    m_bDisplayMovieSubtitles = FALSE;
    field_94 = 1;
    m_bStaticAnimations = TRUE;
    m_bTranslucentBlts = TRUE;
    m_bMaxHP = FALSE;
    m_bAutoPauseOnTrap = FALSE;
    m_bShowQuestXP = FALSE;
    field_AC = 0;
    m_bCriticalHitScreenShake = TRUE;
    m_bSuppressExtraDifficultyDamage = FALSE;
    m_nTilesPrecachePercent = 100;
    m_nNightmareMode = 0;
    m_nDefaultCharGenPointsPool = 16;
    m_nDefaultCharGenPoints = 10;
    m_nShadedSelectionBox = 0;
    m_bAllScreenShake = TRUE;
    m_nOldPortraitHealth = 0;
    m_nHitPointBarSequence = 0;
}

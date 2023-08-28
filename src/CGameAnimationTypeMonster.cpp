#include "CGameAnimationTypeMonster.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6A89A0
CGameAnimationTypeMonster::CGameAnimationTypeMonster(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    m_bHideWeapons = FALSE;
    m_splitBamChar = '\0';
    m_animationID = animationID;
    m_falseColor = TRUE;
    field_7D0 = FALSE;
    m_translucent = FALSE;
    m_renderWeapons = TRUE;
    m_bDetectedByInfravision = TRUE;
    m_nSndFreq = -1;
    m_bPathSmooth = FALSE;
    m_currentShootSequence = 3;
    m_currentShootSplit = '3';
    m_bSplitBams = FALSE;
    m_bCanLieDown = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        switch (animationID & 0xF) {
        case 0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MOGH";
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 1:
            m_moveScale = 6;
            m_moveScaleCurrent = 6;
            m_resRef = "MOGN";
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 4421
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x100:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_resRef = "MBAS";
        m_falseColor = FALSE;
        m_nSndFreq = 70;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";

        if ((animationID & 0xF) == 1) {
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MBAS_GR"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
        }
        break;
    case 0x200:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 10;
        m_moveScaleCurrent = 10;
        m_resRef = "MBER";
        m_falseColor = FALSE;
        m_nSndFreq = 60;
        m_personalSpace = 3;
        m_pSndDeath = "FAL_03B";

        switch (animationID & 0xF) {
        case 0:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MBER_BL"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MBER_CA"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MBER_PO"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x300:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_bPathSmooth = TRUE;
        m_falseColor = FALSE;
        m_colorBlood = 50;

        switch (animationID & 0xF0) {
        case 0x00:
            m_bSplitBams = TRUE;
            switch (animationID & 0xF) {
            case 0:
                m_resRef = "MEAE";
                m_moveScale = 10;
                m_moveScaleCurrent = 10;
                m_nSndFreq = 8;
                m_personalSpace = 5;
                m_pSndDeath = "FAL_03B";
                break;
            case 2:
                m_resRef = "MEAE";
                m_moveScale = 10;
                m_moveScaleCurrent = 10;
                m_nSndFreq = 6;
                m_personalSpace = 3;
                m_pSndDeath = "FAL_03B";
                field_7D0 = TRUE;
                field_7D4.SetResRef(CResRef("MEAE_SH"), TRUE, TRUE);
                field_7D4.m_bDoubleSize = FALSE;
                m_rEllipse.left = -36;
                m_rEllipse.top = -24;
                m_rEllipse.right = 36;
                m_rEllipse.bottom = 24;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 4512
                UTIL_ASSERT(FALSE);
            }
            break;
        case 0x10:
            m_bSplitBams = TRUE;
            switch (animationID & 0xF) {
            case 0:
                m_resRef = "MFIE";
                m_moveScale = 10;
                m_moveScaleCurrent = 10;
                m_nSndFreq = 8;
                m_personalSpace = 3;
                m_pSndDeath = "FAL_03B";
                break;
            case 1:
                m_resRef = "MFIS";
                m_moveScale = 7;
                m_moveScaleCurrent = 7;
                m_nSndFreq = 8;
                m_personalSpace = 3;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 4539
                UTIL_ASSERT(FALSE);
            }
            break;
        case 0x20:
            m_bSplitBams = TRUE;
            m_translucent = TRUE;
            switch (animationID & 0xF) {
            case 0:
                m_resRef = "MAIR";
                m_moveScale = 10;
                m_moveScaleCurrent = 10;
                m_nSndFreq = 8;
                m_personalSpace = 3;
                m_pSndDeath = "FAL_03B";
                break;
            case 1:
                m_rEllipse.left = -16;
                m_rEllipse.top = -12;
                m_rEllipse.right = 16;
                m_rEllipse.bottom = 12;
                m_resRef = "MAIS";
                m_moveScale = 7;
                m_moveScaleCurrent = 7;
                m_nSndFreq = 8;
                m_personalSpace = 3;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 4567
                UTIL_ASSERT(FALSE);
            }
            break;
        }
    case 0x400:
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_resRef = "MDOG";
        m_falseColor = FALSE;
        m_nSndFreq = 150;
        m_pSndDeath = "FAL_01B";

        switch (animationID & 0xF) {
        case 0:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MDOG_WI"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 1:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MDOG_WA"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MDOG_MO"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x500:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;
        m_resRef = "MDOP";
        m_falseColor = FALSE;
        m_colorBlood = 60;
        if ((animationID & 0xF) == 1) {
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MDOP_GR"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
        }
        break;
    case 0x600:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 8;
        m_resRef = "METT";
        m_falseColor = FALSE;
        m_colorBlood = 50;
        break;
    case 0x700:
        m_falseColor = FALSE;
        m_colorBlood = 66;
        m_bDetectedByInfravision = FALSE;

        switch (animationID & 0xF) {
        case 0:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            break;
        case 1:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MGHL_RE"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 2:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MGHL_GA"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x800:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 8;
        m_resRef = "MGIB";
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x900:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 2;
        m_moveScaleCurrent = 2;
        m_resRef = "MSLI";
        m_falseColor = FALSE;
        m_translucent = TRUE;
        m_bDetectedByInfravision = FALSE;
        m_nSndFreq = 24;
        m_personalSpace = 3;
        m_pSndDeath = "";

        switch (animationID & 0xF) {
        case 0:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSLI_GR"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            m_colorBlood = 7;
            break;
        case 1:
            m_moveScale = 10;
            m_moveScaleCurrent = 10;
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSLI_OL"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            m_colorBlood = 36;
            break;
        case 2:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSLI_MU"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            m_colorBlood = 51;
            break;
        case 3:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSLI_OC"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            m_colorBlood = 37;
            break;
        case 4:
            m_colorBlood = 27;
            break;
        }
        break;
    case 0xA00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 9;
        m_moveScaleCurrent = 9;
        m_resRef = "MSPI";
        m_falseColor = FALSE;
        m_nSndFreq = 20;
        m_personalSpace = 5;
        m_colorBlood = 51;
        m_colorChunks = -1;

        switch (animationID & 0xF) {
        case 0:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSPI_GI"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 1:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSPI_HU"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSPI_PH"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSPI_SW"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 4:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MSPI_WR"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0xB00:
        m_colorChunks = -1;
        m_moveScale = 15;
        m_moveScaleCurrent = 15;
        m_resRef = "MWLF";
        m_falseColor = FALSE;
        m_nSndFreq = 150;
        m_pSndDeath = "FAL_01B";

        switch (animationID & 0xF) {
        case 1:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MWLF_WO"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MWLF_DI"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MWLF_WI"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 4:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MWLF_VA"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        case 5:
            field_7D0 = TRUE;
            field_7D4.SetResRef(CResRef("MWLF_DR"), TRUE, TRUE);
            field_7D4.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0xC00:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 4;
        m_pSndDeath = "FAL_01B";

        switch (m_animationID & 0xF) {
        case 0:
            m_resRef = "MXVT";
            break;
        case 1:
            m_resRef = "MTAS";
            break;
        }
        break;
    case 0xD00:
        m_moveScale = 3;
        m_moveScaleCurrent = 3;
        m_resRef = "MZOM";
        m_falseColor = TRUE;
        m_colorBlood = 37;
        m_bDetectedByInfravision = FALSE;
        m_nSndFreq = 8;
        m_combatRounds[0].SetResRef(CResRef("rbzomb1"), TRUE, TRUE);
        m_combatRounds[1].SetResRef(CResRef("rbzomb2"), TRUE, TRUE);
        break;
    case 0xE00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 10;
        m_moveScaleCurrent = 10;

        switch (m_animationID & 0xF) {
        case 0:
            m_resRef = "MWER";
            break;
        case 1:
            m_resRef = "MGWE";
            break;
        }

        m_nSndFreq = 5;
        m_falseColor = FALSE;
        break;
    case 0xF00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_bPathSmooth = TRUE;
        m_falseColor = FALSE;

        switch (animationID & 0xF) {
        case 0:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 10;
            m_moveScaleCurrent = 10;
            m_resRef = "MTRO";
            m_falseColor = FALSE;
            m_nSndFreq = 8;
            m_colorBlood = 50;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 1:
            m_bSplitBams = TRUE;
            m_moveScale = 8;
            m_moveScaleCurrent = 8;
            m_resRef = "MMIN";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_falseColor = FALSE;
            m_nSndFreq = 6;
            m_colorBlood = 61;
            m_pSndDeath = "FAL_01B";
            break;
        case 2:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 8;
            m_moveScaleCurrent = 8;
            m_resRef = "MBEH";
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_falseColor = FALSE;
            m_colorBlood = 61;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 3:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 11;
            m_moveScaleCurrent = 11;
            m_falseColor = FALSE;
            m_resRef = "MIMP";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorBlood = 61;
            m_pSndDeath = "FAL_01B";
            break;
        case 4:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 13;
            m_moveScaleCurrent = 13;
            m_falseColor = FALSE;
            m_nSndFreq = 6;
            m_resRef = "MIGO";
            m_rEllipse.left = -36;
            m_rEllipse.top = -26;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_colorBlood = 26;
            m_personalSpace = 7;
            m_pSndDeath = "FAL_03B";
            m_bDetectedByInfravision = 0;
            break;
        case 5:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 11;
            m_moveScaleCurrent = 11;
            m_falseColor = FALSE;
            m_resRef = "MDJI";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 6:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 11;
            m_moveScaleCurrent = 11;
            m_falseColor = FALSE;
            m_nSndFreq = 9;
            m_resRef = "MDJL";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 7:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 13;
            m_moveScaleCurrent = 13;
            m_falseColor = FALSE;
            m_nSndFreq = 6;
            m_resRef = "MGLC";
            m_colorBlood = 93;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            m_bDetectedByInfravision = 0;
            break;
        case 8:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_falseColor = FALSE;
            m_nSndFreq = 2;
            m_resRef = "MOTY";
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        case 10:
            m_bSplitBams = TRUE;
            m_moveScale = 15;
            m_moveScaleCurrent = 15;
            m_resRef = "MGCP";
            m_rEllipse.left = -28;
            m_rEllipse.top = -20;
            m_rEllipse.right = 28;
            m_rEllipse.bottom = 20;
            m_falseColor = FALSE;
            m_nSndFreq = 150;
            break;
        case 11:
            m_bSplitBams = TRUE;
            m_moveScale = 15;
            m_moveScaleCurrent = 15;
            m_resRef = "MGCL";
            m_rEllipse.left = -28;
            m_rEllipse.top = -20;
            m_rEllipse.right = 28;
            m_rEllipse.bottom = 20;
            m_falseColor = FALSE;
            m_nSndFreq = 150;
            break;
        case 16:
            m_bSplitBams = TRUE;
            m_moveScale = 10;
            m_moveScaleCurrent = 10;
            m_resRef = "MRAK";
            m_falseColor = FALSE;
            m_nSndFreq = 8;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 19:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 13;
            m_moveScaleCurrent = 13;
            m_resRef = "MSNK";
            m_falseColor = FALSE;
            m_nSndFreq = 4;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        case 24:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 8;
            m_moveScaleCurrent = 8;
            m_resRef = "ADER";
            m_falseColor = FALSE;
            m_personalSpace = 3;
            break;
        case 36:
            m_bSplitBams = TRUE;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "NPIR";
            m_falseColor = FALSE;
            m_nSndFreq = 4;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 39:
            m_bSplitBams = TRUE;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MDRO";
            m_falseColor = FALSE;
            m_nSndFreq = 4;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 41:
            m_bSplitBams = TRUE;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MFDR";
            m_falseColor = FALSE;
            m_nSndFreq = 4;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            break;
        case 42:
            m_bSplitBams = TRUE;
            m_moveScale = 5;
            m_moveScaleCurrent = 5;
            m_resRef = "NSAI";
            m_falseColor = FALSE;
            m_nSndFreq = 6;
            m_personalSpace = 3;
            break;
        case 46:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MRAV";
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_falseColor = FALSE;
            m_rEllipse.bottom = 24;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 47:
            m_bSplitBams = TRUE;
            m_colorChunks = -1;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MSPS";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_falseColor = FALSE;
            m_rEllipse.bottom = 12;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_01B";
            break;
        case 50:
            m_bSplitBams = TRUE;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MSLY";
            m_falseColor = FALSE;
            m_personalSpace = 3;
            break;
        case 56:
            m_colorChunks = -1;
            m_moveScale = 12;
            m_moveScaleCurrent = 12;
            m_resRef = "MEYE";
            m_falseColor = FALSE;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_01B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 5129
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5134
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
        m_g2VidCellBase.SetPalette(m_charPalette);

        m_g1VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_g2VidCellWeaponBase.SetPalette(m_weaponPalette);
    }

    m_currentVidCellWeaponBase = NULL;
    m_currentVidCellWeapon = NULL;
    m_currentBamSequence = 1;
    m_extendDirectionTest = CGameSprite::DIR_N;
    ChangeDirection(facing);
}

// 0x6AB170
CGameAnimationTypeMonster::~CGameAnimationTypeMonster()
{
}

// 0x6AAF90
BOOLEAN CGameAnimationTypeMonster::CanLieDown()
{
    return m_bCanLieDown;
}

// 0x6AAFA0
BOOLEAN CGameAnimationTypeMonster::DetectedByInfravision()
{
    return m_bDetectedByInfravision;
}

// 0x6AAFB0
BOOL CGameAnimationTypeMonster::GetPathSmooth()
{
    return m_bPathSmooth;
}

// 0x6AAFC0
BOOL CGameAnimationTypeMonster::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1035
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6AB000
BOOL CGameAnimationTypeMonster::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1036
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6AB040
BOOL CGameAnimationTypeMonster::IsFalseColor()
{
    return m_falseColor;
}

// 0x6AB050
BOOL CGameAnimationTypeMonster::IsMirroring()
{
    return m_currentBamDirection > m_extendDirectionTest;
}

// 0x6AB070
void CGameAnimationTypeMonster::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1039
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->FrameAdvance();
    }
}

// 0x6AB0B0
void CGameAnimationTypeMonster::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1040
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }
}

// 0x6AB100
SHORT CGameAnimationTypeMonster::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1050
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6AB250
void CGameAnimationTypeMonster::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 5178
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptChar;
    m_currentVidCell->GetCurrentCenterPoint(ptChar, FALSE);
    ptReference = ptChar;

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    if (m_renderWeapons && m_currentVidCellWeapon != NULL) {
        CPoint ptWeapon;
        m_currentVidCellWeapon->GetCurrentCenterPoint(ptWeapon, FALSE);

        ptReference.x = max(ptWeapon.x, ptReference.x);
        ptReference.y = max(ptWeapon.y, ptReference.y);

        frameSize.cx += ptReference.x - ptChar.x;
        frameSize.cy += ptReference.y - ptChar.y;
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);

        m_currentVidCellWeapon->GetCurrentFrameSize(frameSize, FALSE);

        rFx.right = max(frameSize.cx + ptReference.x - ptWeapon.x, rFx.right);
        rFx.bottom = max(frameSize.cy + ptReference.y - ptWeapon.y, rFx.bottom);
    } else {
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
    }
}

// 0x6AB390
void CGameAnimationTypeMonster::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if (m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6AB3F0
void CGameAnimationTypeMonster::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 5287
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;
    m_currentVidCell = m_currentVidCellBase;

    if (m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
    } else {
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
    }

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon = m_currentVidCellWeaponBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamDirection - m_currentBamDirection + 16);
        } else {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamDirection + m_currentBamDirection);
        }
    }
}

// 0x6AB4D0
CVidPalette* CGameAnimationTypeMonster::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5330
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            return &m_charPalette;
        }

        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_falseColor) {
            return &m_weaponPalette;
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5348
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6AB5B0
void CGameAnimationTypeMonster::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5378
        UTIL_ASSERT(m_currentVidCell != NULL);

        switch (m_animationID & 0xF00) {
        case 0x200:
            switch (m_animationID & 0xF) {
            case 0:
                resRef = m_resRef + "0";
                break;
            case 1:
                resRef = m_resRef + "1";
                break;
            }
            break;
        case 0x900:
            if ((m_animationID & 0xF) == 2) {
                resRef = m_resRef + "2";
            }
            break;
        case 0xA00:
            if ((m_animationID & 0xF) == 3) {
                resRef = m_resRef + "3";
            }
            break;
        case 0xB00:
            if ((m_animationID & 0xF) == 0) {
                resRef = m_resRef + "0";
            }
            break;
        case 0xF00:
            resRef = "MMI2";
            break;
        default:
            resRef = m_resRef;
            break;
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        resRef = "";
        break;
    }
}

// 0x6ABB10
void CGameAnimationTypeMonster::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 5768
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g2VidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_g2VidCellBase.UnsuppressTint(colorRange & 0xF);
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            m_g1VidCellBase.DeleteResPaletteAffect();
            m_g2VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
            m_g2VidCellBase.UnsuppressTintAllRanges();
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            m_g1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
            m_g2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
            m_g2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5805
        UTIL_ASSERT(FALSE);
    }
}

// 0x6ABC90
void CGameAnimationTypeMonster::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 5830
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
            ClearColorEffects(colorRange | 0x10);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_g2VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_g2VidCellBase.UnsuppressTintAllRanges();

        if (m_currentVidCellWeapon != NULL) {
            m_g1VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            m_g1VidCellWeaponBase.DeleteResPaletteAffect();
            m_g2VidCellWeaponBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellWeaponBase.UnsuppressTintAllRanges();
            m_g2VidCellWeaponBase.UnsuppressTintAllRanges();
        }
    }
}

// 0x6ABDD0
void CGameAnimationTypeMonster::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5883
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_g2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
                m_g2VidCellBase.SuppressTint(colorRange & 0xF);
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellBase.SuppressTint(0);
                m_g2VidCellBase.SuppressTint(0);
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
                m_g2VidCellBase.SetTintColor(tintColor);
            }
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            if (m_falseColor) {
                m_g1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                    m_g2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                }
            } else {
                if (effectType != 0) {
                    m_g1VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellWeaponBase.SuppressTint(0);
                    m_g2VidCellWeaponBase.SuppressTint(0);
                } else {
                    m_g1VidCellWeaponBase.SetTintColor(tintColor);
                    m_g2VidCellWeaponBase.SetTintColor(tintColor);
                }
            }
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 5948
        UTIL_ASSERT(FALSE);
    }
}

// 0x6AC000
void CGameAnimationTypeMonster::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 5973
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
            SetColorEffect(effectType, colorRange | 0x10, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_g1VidCellBase.SuppressTint(0);
            m_g2VidCellBase.SuppressTint(0);

            if (m_currentVidCellWeapon != NULL) {
                m_g1VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellWeaponBase.SuppressTint(0);
                m_g2VidCellWeaponBase.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
            m_g2VidCellBase.SetTintColor(tintColor);

            if (m_currentVidCellWeapon != NULL) {
                m_g1VidCellWeaponBase.SetTintColor(tintColor);
                m_g2VidCellWeaponBase.SetTintColor(tintColor);
            }
        }
    }
}

// 0x6AC160
void CGameAnimationTypeMonster::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 6037
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
            if (m_currentVidCellWeapon != NULL) {
                m_weaponPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            }
            break;
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 6051
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6AC290
void CGameAnimationTypeMonster::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 6077
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
            SetColorRange(colorRange | 0x10, rangeValue);
        }
    }
}

// 0x6AC730
SHORT CGameAnimationTypeMonster::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    m_renderWeapons = TRUE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_renderWeapons = FALSE;
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 4;

        if (m_bSplitBams) {
            m_splitBamChar = '4';

            // NOTE: Uninline.
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    case 2:
        m_renderWeapons = FALSE;
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentBamSequence = 6;

        if (m_bSplitBams) {
            m_splitBamChar = '6';

            // NOTE: Uninline.
            m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    case 3:
        m_renderWeapons = FALSE;
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentBamSequence = 5;

        if (m_bSplitBams) {
            m_splitBamChar = '6';

            // NOTE: Uninline.
            m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeapon = &m_g1VidCellWeaponBase;
        }

        m_currentBamSequence = 3;

        if (m_bSplitBams) {
            m_splitBamChar = '3';

            // NOTE: Uninline.
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    case 6:
        if (m_currentBamSequence != 2 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeapon = &m_g1VidCellWeaponBase;
        }

        m_currentBamSequence = 2;

        if (m_bSplitBams) {
            m_splitBamChar = '2';

            // NOTE: Uninline.
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    case 14:
    case 15:
        nSequence = 7;
    case 7:
        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeapon = &m_g1VidCellWeaponBase;
        }

        m_currentBamSequence = 1;

        if (m_bSplitBams) {
            m_splitBamChar = '\0';

            // NOTE: Uninline.
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1" + m_splitBamChar), FALSE, TRUE, TRUE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 6437
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);

    SHORT nFrame = 0;
    if (bRandomFrame) {
        SHORT nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            nFrame = rand() % nSequenceLength;
        }
    }
    m_currentVidCell->FrameSet(nFrame);

    if (m_renderWeapons) {
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeapon->FrameSet(nFrame);
        }
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

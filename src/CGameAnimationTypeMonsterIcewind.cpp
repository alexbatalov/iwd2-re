#include "CGameAnimationTypeMonsterIcewind.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6E0410
CGameAnimationTypeMonsterIcewind::CGameAnimationTypeMonsterIcewind(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_palette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_falseColor = FALSE;
    m_currentVidCellWeaponExtend = NULL;
    m_currentVidCellWeaponBase = NULL;
    m_bDetectedByInfravision = TRUE;
    m_nSndFreq = -1;
    field_1CDA = 10;
    field_1CDE = -1;
    m_bExtendDir = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_colorBlood = 51;
        m_nSndFreq = 5;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MBET";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_resRef = "MBBM";
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_resRef = "MBBR";
            m_pSndDeath = "FAL_03B";
            break;
        case 0x30:
            m_resRef = "MBFI";
            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_rEllipse.left = -64;
            m_rEllipse.top = -48;
            m_rEllipse.right = 64;
            m_rEllipse.bottom = 48;
            m_resRef = "MBRH";
            m_colorChunks = -1;
            m_personalSpace = 7;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_rEllipse.left = -64;
            m_rEllipse.top = -48;
            m_rEllipse.right = 64;
            m_rEllipse.bottom = 48;
            m_resRef = "MREM";
            m_colorChunks = -1;
            m_nSndFreq = 14;
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_rEllipse.left = -24;
            m_rEllipse.top = -16;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 16;
            m_resRef = "MHOH";
            m_colorChunks = -1;
            m_nSndFreq = 14;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24494
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x100:
        switch (animationID & 0xF0) {
        case 0x00:
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MCYC";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_nSndFreq = 15;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "METN";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_nSndFreq = 10;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x30:
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MGFR";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_nSndFreq = 15;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MGVE";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_nSndFreq = 10;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MGFO";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_nSndFreq = 10;
            field_1CDA = 26;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24567
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x200:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_colorChunks = -1;
        m_nSndFreq = 10;

        switch (animationID & 0xF0) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x90:
            m_resRef = "MEL";

            if ((animationID & 0xF0) == 0x90) {
                m_resRef = "MEW2";
                m_rEllipse.left = -24;
                m_rEllipse.top = -18;
                m_rEllipse.right = 24;
                m_rEllipse.bottom = 18;
            } else {
                m_resRef += "AEFW"[((animationID >> 4) & 0xF) - 1];
                m_rEllipse.left = -36;
                m_rEllipse.top = -24;
                m_rEllipse.right = 36;
                m_rEllipse.bottom = 24;
            }

            m_colorBlood = 34;
            m_colorChunks = -1;
            m_personalSpace = 3;

            if ((animationID & 0xF0) != 0x20) {
                m_bDetectedByInfravision = FALSE;
            }

            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MHAR";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_resRef = "MWWE";
            m_colorBlood = 31;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MFEY";
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x70:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MDTR";
            m_colorBlood = 48;
            m_colorChunks = -1;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MFE2";
            m_colorBlood = 48;
            m_colorChunks = -1;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24658
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x300:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_bDetectedByInfravision = FALSE;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MGH2";
            m_colorBlood = 63;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_resRef = "MGH3";
            m_colorBlood = 63;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_resRef = "MWIG";
            m_colorBlood = 65;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x30:
            m_moveScale = 3;
            m_moveScaleCurrent = 3;
            m_resRef = "MZO2";
            m_nSndFreq = 12;
            m_colorBlood = 63;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_moveScale = 3;
            m_moveScaleCurrent = 3;
            m_resRef = "MZO3";
            m_nSndFreq = 12;
            m_colorBlood = 63;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_resRef = "MWI2";
            m_colorBlood = 65;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_resRef = "MWI3";
            m_colorBlood = 65;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MMUM";
            m_colorBlood = 63;
            m_nSndFreq = 12;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x90:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MHIS";
            m_colorBlood = 47;
            m_nSndFreq = 12;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xA0:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MDRD";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_colorBlood = 47;
            m_nSndFreq = 14;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xB0:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MWAV";
            m_colorBlood = 63;
            m_nSndFreq = 12;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24787
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x400:
        switch (animationID & 0xF0) {
        case 0x00:
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x90:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MGO";

            switch (animationID & 0xF0) {
            case 0x00:
                m_resRef += '1';
                break;
            case 0x10:
                m_resRef += '2';
                break;
            case 0x20:
                m_resRef += '3';
                break;
            case 0x30:
                m_resRef += '4';
                break;
            case 0x90:
                m_resRef += '5';
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 24814
                UTIL_ASSERT(FALSE);
            }

            m_colorBlood = 66;
            m_nSndFreq = 8;
            field_1CDA = 11;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MSVI";
            m_nSndFreq = 7;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MSV2";
            m_nSndFreq = 7;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_moveScale = 11;
            m_moveScaleCurrent = 11;
            m_resRef = "MGWO";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_colorBlood = 47;
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x70:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MGOC";
            m_colorBlood = 66;
            m_nSndFreq = 8;
            field_1CDA = 11;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_moveScale = 11;
            m_moveScaleCurrent = 11;
            m_resRef = "MGW2";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_colorBlood = 47;
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24884
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x500:
        m_rEllipse.left = -36;
        m_rEllipse.top = -24;
        m_rEllipse.right = 36;
        m_rEllipse.bottom = 24;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_colorChunks = -1;
        m_bDetectedByInfravision = 0;
        m_nSndFreq = 10;

        switch (animationID & 0xF0) {
        case 0x10:
            m_resRef = "MGIR";
            m_colorBlood = 24;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_resRef = "MGIC";
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_colorBlood = 31;
            m_personalSpace = 3;
            m_nSndFreq = 10;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24920
            UTIL_ASSERT(FALSE);
            break;
        }
        break;
    case 0x600:
        switch (animationID & 0xF0) {
        case 0x20:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MSKB";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_colorBlood = 63;
            m_colorChunks = -1;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 12;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 24943
            UTIL_ASSERT(FALSE);
            break;
        }
        break;
    case 0x700:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MMIN";
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_resRef = "MTRO";
            m_nSndFreq = 9;
            m_colorBlood = 66;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_resRef = "MTIC";
            m_nSndFreq = 10;
            m_colorBlood = 56;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x30:
            m_resRef = "MTSN";
            m_nSndFreq = 10;
            m_colorBlood = 56;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            m_resRef = "MUMB";
            m_nSndFreq = 9;
            m_colorBlood = 65;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_resRef = "MYET";
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x70:
            m_resRef = "MBA4";
            m_nSndFreq = 8;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_resRef = "MBA5";
            m_nSndFreq = 8;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x90:
            m_resRef = "MBA6";
            m_nSndFreq = 8;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xA0:
            m_resRef = "MBAI";
            m_nSndFreq = 8;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xB0:
            m_moveScale = 9;
            m_moveScaleCurrent = 9;
            m_resRef = "MBOA";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 8;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xC0:
            m_resRef = "MABW";
            m_nSndFreq = 10;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xD0:
            m_resRef = "MMAL";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_nSndFreq = 10;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xE0:
            m_resRef = "MSCR";
            m_nSndFreq = 9;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xF0:
            m_resRef = "MUM2";
            m_nSndFreq = 8;
            m_colorBlood = 65;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 25079
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x800:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 5;

        switch (animationID & 0xF0) {
        case 0x00:
        case 0xF0:
            m_resRef = "MOR";
            if ((animationID & 0xF0) == 0) {
                m_resRef += '6';
            } else {
                m_resRef += '7';
            }
            m_colorBlood = 47;
            field_1CDA = 21;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
            m_resRef = "MOR" + (((animationID >> 4) & 0xF) + '0');
            m_colorBlood = 47;
            field_1CDA = 21;
            m_nSndFreq = 9;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x60:
            m_resRef = "MNO1";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 9;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x70:
            m_resRef = "MNO2";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 9;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_resRef = "MNO3";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 10;
            m_colorBlood = 47;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x90:
            m_resRef = "MLI3";
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_nSndFreq = 9;
            m_colorBlood = 37;
            m_colorChunks = -1;
            m_personalSpace = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xA0:
            m_resRef = "MYU3";
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xB0:
            m_resRef = "MYUH";
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xC0:
            m_resRef = "MBUG";
            m_rEllipse.left = -28;
            m_rEllipse.top = -20;
            m_rEllipse.right = 28;
            m_rEllipse.bottom = 20;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xD0:
            m_resRef = "MNOS";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 9;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xE0:
            m_resRef = "MBU2";
            m_rEllipse.left = -28;
            m_rEllipse.top = -20;
            m_rEllipse.right = 28;
            m_rEllipse.bottom = 20;
            m_colorBlood = 47;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 25193
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x900:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 5;
        m_colorChunks = -1;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MSH1";
            m_colorBlood = 66;
            m_bDetectedByInfravision = FALSE;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_resRef = "MSH2";
            m_colorBlood = 66;
            m_bDetectedByInfravision = FALSE;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_resRef = "MGHO";
            m_colorBlood = 63;
            m_bDetectedByInfravision = FALSE;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 25231
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0xA00:
        switch (animationID & 0xF0) {
        case 0x10:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MCRD";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 5;
            m_colorBlood = 37;
            m_colorChunks = -1;
            m_personalSpace = 3;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 25253
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0xB00:
        switch (animationID & 0xF0) {
        case 0x00:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MANI";
            m_colorBlood = 27;
            m_colorChunks = -1;
            m_bDetectedByInfravision = 0;
            m_nSndFreq = 10;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x10:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MAN2";
            m_colorBlood = 27;
            m_colorChunks = -1;
            m_bDetectedByInfravision = 0;
            m_nSndFreq = 10;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x20:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MAN3";
            m_colorBlood = 27;
            m_colorChunks = -1;
            m_bDetectedByInfravision = 0;
            m_nSndFreq = 10;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x30:
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_nSndFreq = 9;
            m_colorChunks = -1;
            m_resRef = "MBE1";
            m_pSndDeath = "FAL_03B";
            break;
        case 0x40:
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_nSndFreq = 8;
            m_colorChunks = -1;
            m_resRef = "MBE2";
            m_pSndDeath = "FAL_03B";
            break;
        case 0x50:
            switch (animationID & 0xF) {
            case 0x1:
                m_moveScale = 5;
                m_moveScaleCurrent = 5;
                m_resRef = "MSEE";
                m_nSndFreq = 9;
                m_rEllipse.left = -16;
                m_rEllipse.top = -12;
                m_rEllipse.right = 16;
                m_rEllipse.bottom = 12;
                m_pSndDeath = "FAL_03B";
                break;
            case 0x2:
                m_moveScale = 7;
                m_moveScaleCurrent = 7;
                m_resRef = "MFIR";
                m_nSndFreq = 5;
                m_rEllipse.left = -24;
                m_rEllipse.top = -18;
                m_rEllipse.right = 24;
                m_rEllipse.bottom = 18;
                m_pSndDeath = "FAL_03B";
                break;
            }
            break;
        case 0x60:
            m_moveScale = 5;
            m_moveScaleCurrent = 5;
            m_resRef = "MLIC";
            m_colorBlood = 63;
            m_colorChunks = -1;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 9;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x70:
            m_moveScale = 5;
            m_moveScaleCurrent = 5;
            m_resRef = "MLER";
            m_colorBlood = 66;
            m_colorChunks = -1;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 9;
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x80:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MMAN";
            m_nSndFreq = 5;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_pSndDeath = "FAL_03B";
            break;
        case 0x90:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MMYC";
            m_bDetectedByInfravision = FALSE;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 5;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xA0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MMY2";
            m_colorBlood = 58;
            m_colorChunks = -1;
            m_bDetectedByInfravision = FALSE;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xB0:
            m_moveScale = 0;
            m_moveScaleCurrent = 0;
            m_resRef = "MSHR";
            m_colorBlood = 46;
            m_colorChunks = -1;
            m_bDetectedByInfravision = FALSE;
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xC0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MTAN";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 5;
            m_colorChunks = -1;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xD0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MSAL";
            m_colorBlood = 47;
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xE0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MSA2";
            m_colorBlood = 56;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 0xF0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MARU";
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 25467
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0xC00:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_personalSpace = 5;

        switch (animationID & 0xF0) {
        case 0x00:
            m_rEllipse.left = -36;
            m_rEllipse.top = -24;
            m_rEllipse.right = 36;
            m_rEllipse.bottom = 24;
            m_moveScale = 9;
            m_moveScaleCurrent = 8;
            m_nSndFreq = 9;
            m_personalSpace = 5;
            m_resRef = "MWDR";
            break;
        case 0x10:
            m_resRef = "MCHY";
            m_nSndFreq = 9;
            break;
        case 0x20:
            m_resRef = "MSHE";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_nSndFreq = 9;
            m_personalSpace = 3;
            break;
        case 0x30:
            m_resRef = "MCHI";
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_nSndFreq = 9;
            m_personalSpace = 5;
            break;
        case 0x40:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MDH1";
            m_nSndFreq = 9;
            m_personalSpace = 3;
            break;
        case 0x50:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MDH2";
            m_nSndFreq = 9;
            m_personalSpace = 3;
            break;
        }
        break;
    case 0xD00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 9;
        m_colorChunks = -1;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MCOR";
            break;
        case 0x10:
            m_resRef = "MGLA";
            break;
        case 0x20:
            m_resRef = "MLEM";
            break;
        }
        m_nSndFreq = 8;
        break;
    case 0xE00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 9;
        m_colorChunks = -1;
        m_personalSpace = 3;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MWEB";
            break;
        case 0x10:
            m_resRef = "MWRA";
            break;
        }
        break;
    case 0xF00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 9;
        m_colorChunks = -1;
        m_personalSpace = 3;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MISA";
            break;
        case 0x10:
            m_resRef = "MMAD";
            break;
        case 0x20:
            m_moveScale = 13;
            m_moveScaleCurrent = 13;
            m_resRef = "MWOR";
            break;
        case 0x50:
        case 0x60:
        case 0x70:
            m_moveScale = 0;
            m_moveScaleCurrent = 0;
            m_resRef = "MKG";
            m_resRef += "123"[((animationID >> 4) & 0xF) - 0x5];
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_bDetectedByInfravision = FALSE;
            m_colorBlood = 91;
            m_colorChunks = 0;
            m_personalSpace = 3;
            break;
        case 0x90:
            m_moveScale = 10;
            m_moveScaleCurrent = 10;
            m_resRef = "MWIL";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorBlood = 63;
            m_personalSpace = 3;
            break;
        case 0xA0:
            m_resRef = "MGEN";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorChunks = 0;
            m_colorBlood = -1;
            m_personalSpace = 3;
            break;
        case 0xB0:
            m_resRef = "MGEN";
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_colorChunks = 0;
            m_colorBlood = -1;
            m_personalSpace = 3;
            break;
        case 0xC0:
            m_resRef = "MGEN";
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_colorChunks = 0;
            m_colorBlood = -1;
            m_personalSpace = 5;
            break;
        case 0xE0:
            m_resRef = "MGEN";
            m_rEllipse.left = -12;
            m_rEllipse.top = -9;
            m_rEllipse.right = 12;
            m_rEllipse.bottom = 9;
            m_colorChunks = 0;
            m_colorBlood = -1;
            m_personalSpace = 3;
            break;
        case 0xF0:
            m_resRef = "MGEN";
            m_rEllipse.left = -48;
            m_rEllipse.top = -36;
            m_rEllipse.right = 48;
            m_rEllipse.bottom = 36;
            m_colorChunks = 0;
            m_colorBlood = -1;
            m_personalSpace = 7;
            break;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 25741
        UTIL_ASSERT(FALSE);
    }

    m_a1VidCellBase.SetResRef(CResRef(m_resRef + "A1"), FALSE, TRUE, TRUE);
    m_a2VidCellBase.SetResRef(CResRef(m_resRef + "A2"), FALSE, TRUE, TRUE);
    m_a3VidCellBase.SetResRef(CResRef(m_resRef + "A3"), FALSE, TRUE, TRUE);
    m_a4VidCellBase.SetResRef(CResRef(m_resRef + "A4"), FALSE, TRUE, TRUE);
    m_guVidCellBase.SetResRef(CResRef(m_resRef + "Gu"), FALSE, TRUE, TRUE);
    m_slVidCellBase.SetResRef(CResRef(m_resRef + "Sl"), FALSE, TRUE, TRUE);
    m_deVidCellBase.SetResRef(CResRef(m_resRef + "De"), FALSE, TRUE, TRUE);
    m_ghVidCellBase.SetResRef(CResRef(m_resRef + "Gh"), FALSE, TRUE, TRUE);
    m_sdVidCellBase.SetResRef(CResRef(m_resRef + "Sd"), FALSE, TRUE, TRUE);
    m_scVidCellBase.SetResRef(CResRef(m_resRef + "Sc"), FALSE, TRUE, TRUE);
    m_spVidCellBase.SetResRef(CResRef(m_resRef + "Sp"), FALSE, TRUE, TRUE);
    m_caVidCellBase.SetResRef(CResRef(m_resRef + "Ca"), FALSE, TRUE, TRUE);
    m_twVidCellBase.SetResRef(CResRef(m_resRef + "Tw"), FALSE, TRUE, TRUE);
    m_wkVidCellBase.SetResRef(CResRef(m_resRef + "Wk"), FALSE, TRUE, TRUE);

    m_currentVidCellBase = &m_wkVidCellBase;

    if (m_bExtendDir && !MIRROR_BAM) {
        m_a1VidCellExtend.SetResRef(CResRef(m_resRef + "A1E"), FALSE, TRUE, TRUE);
        m_a2VidCellExtend.SetResRef(CResRef(m_resRef + "A2E"), FALSE, TRUE, TRUE);
        m_a3VidCellExtend.SetResRef(CResRef(m_resRef + "A3E"), FALSE, TRUE, TRUE);
        m_a4VidCellExtend.SetResRef(CResRef(m_resRef + "A4E"), FALSE, TRUE, TRUE);
        m_guVidCellExtend.SetResRef(CResRef(m_resRef + "GuE"), FALSE, TRUE, TRUE);
        m_slVidCellExtend.SetResRef(CResRef(m_resRef + "SlE"), FALSE, TRUE, TRUE);
        m_deVidCellExtend.SetResRef(CResRef(m_resRef + "DeE"), FALSE, TRUE, TRUE);
        m_ghVidCellExtend.SetResRef(CResRef(m_resRef + "GhE"), FALSE, TRUE, TRUE);
        m_sdVidCellExtend.SetResRef(CResRef(m_resRef + "SdE"), FALSE, TRUE, TRUE);
        m_scVidCellExtend.SetResRef(CResRef(m_resRef + "ScE"), FALSE, TRUE, TRUE);
        m_spVidCellExtend.SetResRef(CResRef(m_resRef + "SpE"), FALSE, TRUE, TRUE);
        m_caVidCellExtend.SetResRef(CResRef(m_resRef + "CaE"), FALSE, TRUE, TRUE);
        m_twVidCellExtend.SetResRef(CResRef(m_resRef + "TwE"), FALSE, TRUE, TRUE);
        m_wkVidCellExtend.SetResRef(CResRef(m_resRef + "WkE"), FALSE, TRUE, TRUE);
    }

    m_currentVidCellExtend = &m_wkVidCellExtend;
    m_currentVidCell = m_currentVidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_palette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_a1VidCellBase.SetPalette(m_palette);
        m_a2VidCellBase.SetPalette(m_palette);
        m_a3VidCellBase.SetPalette(m_palette);
        m_a4VidCellBase.SetPalette(m_palette);
        m_guVidCellBase.SetPalette(m_palette);
        m_slVidCellBase.SetPalette(m_palette);
        m_deVidCellBase.SetPalette(m_palette);
        m_ghVidCellBase.SetPalette(m_palette);
        m_sdVidCellBase.SetPalette(m_palette);
        m_scVidCellBase.SetPalette(m_palette);
        m_spVidCellBase.SetPalette(m_palette);
        m_caVidCellBase.SetPalette(m_palette);
        m_twVidCellBase.SetPalette(m_palette);
        m_wkVidCellBase.SetPalette(m_palette);

        if (m_bExtendDir && !MIRROR_BAM) {
            m_a1VidCellExtend.SetPalette(m_palette);
            m_a2VidCellExtend.SetPalette(m_palette);
            m_a3VidCellExtend.SetPalette(m_palette);
            m_a4VidCellExtend.SetPalette(m_palette);
            m_guVidCellExtend.SetPalette(m_palette);
            m_slVidCellExtend.SetPalette(m_palette);
            m_deVidCellExtend.SetPalette(m_palette);
            m_ghVidCellExtend.SetPalette(m_palette);
            m_sdVidCellExtend.SetPalette(m_palette);
            m_scVidCellExtend.SetPalette(m_palette);
            m_spVidCellExtend.SetPalette(m_palette);
            m_caVidCellExtend.SetPalette(m_palette);
            m_twVidCellExtend.SetPalette(m_palette);
            m_wkVidCellExtend.SetPalette(m_palette);
        }
    }

    m_currentBamSequence = 0;
    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
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

// 0x6E5850
const char* CGameAnimationTypeMonsterIcewind::GetSndWalk(SHORT a1)
{
    char* szTemp;

    if (m_animationID == ANIM_DRAGON_WHITE) {
        szTemp = new char[8];

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 26114
        UTIL_ASSERT(szTemp != NULL);

        strcpy(szTemp, "DRAGON12");
        return szTemp;
    }

    switch (m_animationID & 0xFFF0) {
    case 0xE000:
    case 0xE010:
    case 0xE020:
    case 0xE030:
    case 0xE040:
    case 0xE050:
    case 0xE250:
    case 0xE260:
    case 0xE280:
    case 0xE3B0:
    case 0xE8A0:
    case 0xE900:
    case 0xE910:
    case 0xE920:
    case 0xEA20:
    case 0xEB90:
    case 0xEBA0:
    case 0xEBB0:
    case 0xEBC0:
    case 0xEBD0:
    case 0xEBE0:
    case 0xED20:
    case 0xEF90:
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

    szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 26216
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
            m_a4VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_deVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_ghVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_slVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_guVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_spVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_scVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_sdVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_twVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_wkVidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_a1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a4VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_deVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_ghVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_slVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_guVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_spVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_scVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_sdVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_twVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_wkVidCellBase.UnsuppressTint(colorRange & 0xF);

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a3VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a4VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_deVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_ghVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_slVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_guVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_spVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_caVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_scVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_sdVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_twVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_wkVidCellExtend.DeleteRangeAffects(colorRange & 0xF);

                m_a1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a2VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a3VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a4VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_deVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_ghVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_slVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_guVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_spVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_caVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_scVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_sdVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_twVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_wkVidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a4VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_deVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_ghVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_slVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_guVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_spVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_scVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_sdVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_twVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_wkVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a4VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_deVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_ghVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_slVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_guVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_spVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_scVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_sdVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_twVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_wkVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();
            m_a4VidCellBase.DeleteResPaletteAffect();
            m_deVidCellBase.DeleteResPaletteAffect();
            m_ghVidCellBase.DeleteResPaletteAffect();
            m_slVidCellBase.DeleteResPaletteAffect();
            m_guVidCellBase.DeleteResPaletteAffect();
            m_spVidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_scVidCellBase.DeleteResPaletteAffect();
            m_sdVidCellBase.DeleteResPaletteAffect();
            m_twVidCellBase.DeleteResPaletteAffect();
            m_wkVidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();
            m_a4VidCellBase.UnsuppressTintAllRanges();
            m_deVidCellBase.UnsuppressTintAllRanges();
            m_ghVidCellBase.UnsuppressTintAllRanges();
            m_slVidCellBase.UnsuppressTintAllRanges();
            m_guVidCellBase.UnsuppressTintAllRanges();
            m_spVidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_scVidCellBase.UnsuppressTintAllRanges();
            m_sdVidCellBase.UnsuppressTintAllRanges();
            m_twVidCellBase.UnsuppressTintAllRanges();
            m_wkVidCellBase.UnsuppressTintAllRanges();

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.DeleteResPaletteAffect();
                m_a2VidCellExtend.DeleteResPaletteAffect();
                m_a3VidCellExtend.DeleteResPaletteAffect();
                m_a4VidCellExtend.DeleteResPaletteAffect();
                m_deVidCellExtend.DeleteResPaletteAffect();
                m_ghVidCellExtend.DeleteResPaletteAffect();
                m_slVidCellExtend.DeleteResPaletteAffect();
                m_guVidCellExtend.DeleteResPaletteAffect();
                m_spVidCellExtend.DeleteResPaletteAffect();
                m_caVidCellExtend.DeleteResPaletteAffect();
                m_scVidCellExtend.DeleteResPaletteAffect();
                m_sdVidCellExtend.DeleteResPaletteAffect();
                m_twVidCellExtend.DeleteResPaletteAffect();
                m_wkVidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_a1VidCellExtend.UnsuppressTintAllRanges();
                m_a2VidCellExtend.UnsuppressTintAllRanges();
                m_a3VidCellExtend.UnsuppressTintAllRanges();
                m_a4VidCellExtend.UnsuppressTintAllRanges();
                m_deVidCellExtend.UnsuppressTintAllRanges();
                m_ghVidCellExtend.UnsuppressTintAllRanges();
                m_slVidCellExtend.UnsuppressTintAllRanges();
                m_guVidCellExtend.UnsuppressTintAllRanges();
                m_spVidCellExtend.UnsuppressTintAllRanges();
                m_caVidCellExtend.UnsuppressTintAllRanges();
                m_scVidCellExtend.UnsuppressTintAllRanges();
                m_sdVidCellExtend.UnsuppressTintAllRanges();
                m_twVidCellExtend.UnsuppressTintAllRanges();
                m_wkVidCellExtend.UnsuppressTintAllRanges();
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
        m_a4VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_deVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_ghVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_slVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_guVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_spVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_scVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_sdVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_twVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_wkVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (m_bExtendDir && !MIRROR_BAM) {
            m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a4VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_deVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_ghVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_slVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_guVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_spVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_scVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_sdVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_twVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_wkVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_a1VidCellBase.DeleteResPaletteAffect();
        m_a2VidCellBase.DeleteResPaletteAffect();
        m_a3VidCellBase.DeleteResPaletteAffect();
        m_a4VidCellBase.DeleteResPaletteAffect();
        m_deVidCellBase.DeleteResPaletteAffect();
        m_ghVidCellBase.DeleteResPaletteAffect();
        m_slVidCellBase.DeleteResPaletteAffect();
        m_guVidCellBase.DeleteResPaletteAffect();
        m_spVidCellBase.DeleteResPaletteAffect();
        m_caVidCellBase.DeleteResPaletteAffect();
        m_scVidCellBase.DeleteResPaletteAffect();
        m_sdVidCellBase.DeleteResPaletteAffect();
        m_twVidCellBase.DeleteResPaletteAffect();
        m_wkVidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_a1VidCellBase.UnsuppressTintAllRanges();
        m_a2VidCellBase.UnsuppressTintAllRanges();
        m_a3VidCellBase.UnsuppressTintAllRanges();
        m_a4VidCellBase.UnsuppressTintAllRanges();
        m_deVidCellBase.UnsuppressTintAllRanges();
        m_ghVidCellBase.UnsuppressTintAllRanges();
        m_slVidCellBase.UnsuppressTintAllRanges();
        m_guVidCellBase.UnsuppressTintAllRanges();
        m_spVidCellBase.UnsuppressTintAllRanges();
        m_caVidCellBase.UnsuppressTintAllRanges();
        m_scVidCellBase.UnsuppressTintAllRanges();
        m_sdVidCellBase.UnsuppressTintAllRanges();
        m_twVidCellBase.UnsuppressTintAllRanges();
        m_wkVidCellBase.UnsuppressTintAllRanges();

        if (m_bExtendDir && !MIRROR_BAM) {
            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();
            m_a4VidCellBase.DeleteResPaletteAffect();
            m_deVidCellBase.DeleteResPaletteAffect();
            m_ghVidCellBase.DeleteResPaletteAffect();
            m_slVidCellBase.DeleteResPaletteAffect();
            m_guVidCellBase.DeleteResPaletteAffect();
            m_spVidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_scVidCellBase.DeleteResPaletteAffect();
            m_sdVidCellBase.DeleteResPaletteAffect();
            m_twVidCellBase.DeleteResPaletteAffect();
            m_wkVidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();
            m_a4VidCellBase.UnsuppressTintAllRanges();
            m_deVidCellBase.UnsuppressTintAllRanges();
            m_ghVidCellBase.UnsuppressTintAllRanges();
            m_slVidCellBase.UnsuppressTintAllRanges();
            m_guVidCellBase.UnsuppressTintAllRanges();
            m_spVidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_scVidCellBase.UnsuppressTintAllRanges();
            m_sdVidCellBase.UnsuppressTintAllRanges();
            m_twVidCellBase.UnsuppressTintAllRanges();
            m_wkVidCellBase.UnsuppressTintAllRanges();
        }
    }
}

// 0x6E6A60
void CGameAnimationTypeMonsterIcewind::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 26667
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_a1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a4VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_deVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_ghVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_slVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_guVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_spVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_scVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_sdVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_twVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_wkVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_a1VidCellBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellBase.SuppressTint(colorRange & 0xF);
                m_a4VidCellBase.SuppressTint(colorRange & 0xF);
                m_deVidCellBase.SuppressTint(colorRange & 0xF);
                m_ghVidCellBase.SuppressTint(colorRange & 0xF);
                m_slVidCellBase.SuppressTint(colorRange & 0xF);
                m_guVidCellBase.SuppressTint(colorRange & 0xF);
                m_spVidCellBase.SuppressTint(colorRange & 0xF);
                m_caVidCellBase.SuppressTint(colorRange & 0xF);
                m_scVidCellBase.SuppressTint(colorRange & 0xF);
                m_sdVidCellBase.SuppressTint(colorRange & 0xF);
                m_twVidCellBase.SuppressTint(colorRange & 0xF);
                m_wkVidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a3VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a4VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_deVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_ghVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_slVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_guVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_spVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_caVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_scVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_sdVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_twVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_wkVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_a1VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a2VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a3VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a4VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_deVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_ghVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_slVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_guVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_spVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_caVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_scVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_sdVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_twVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_wkVidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a4VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_deVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_ghVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_slVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_guVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_spVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_scVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_sdVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_twVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_wkVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_a1VidCellBase.SuppressTint(0);
                m_a2VidCellBase.SuppressTint(0);
                m_a3VidCellBase.SuppressTint(0);
                m_a4VidCellBase.SuppressTint(0);
                m_deVidCellBase.SuppressTint(0);
                m_ghVidCellBase.SuppressTint(0);
                m_slVidCellBase.SuppressTint(0);
                m_guVidCellBase.SuppressTint(0);
                m_spVidCellBase.SuppressTint(0);
                m_caVidCellBase.SuppressTint(0);
                m_scVidCellBase.SuppressTint(0);
                m_sdVidCellBase.SuppressTint(0);
                m_twVidCellBase.SuppressTint(0);
                m_wkVidCellBase.SuppressTint(0);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_a1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a4VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_deVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_ghVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_slVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_guVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_spVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_caVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_scVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_sdVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_twVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_wkVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_a1VidCellExtend.SuppressTint(0);
                    m_a2VidCellExtend.SuppressTint(0);
                    m_a3VidCellExtend.SuppressTint(0);
                    m_a4VidCellExtend.SuppressTint(0);
                    m_deVidCellExtend.SuppressTint(0);
                    m_ghVidCellExtend.SuppressTint(0);
                    m_slVidCellExtend.SuppressTint(0);
                    m_guVidCellExtend.SuppressTint(0);
                    m_spVidCellExtend.SuppressTint(0);
                    m_caVidCellExtend.SuppressTint(0);
                    m_scVidCellExtend.SuppressTint(0);
                    m_sdVidCellExtend.SuppressTint(0);
                    m_twVidCellExtend.SuppressTint(0);
                    m_wkVidCellExtend.SuppressTint(0);
                }
            } else {
                m_a1VidCellBase.SetTintColor(tintColor);
                m_a2VidCellBase.SetTintColor(tintColor);
                m_a3VidCellBase.SetTintColor(tintColor);
                m_a4VidCellBase.SetTintColor(tintColor);
                m_deVidCellBase.SetTintColor(tintColor);
                m_ghVidCellBase.SetTintColor(tintColor);
                m_slVidCellBase.SetTintColor(tintColor);
                m_guVidCellBase.SetTintColor(tintColor);
                m_spVidCellBase.SetTintColor(tintColor);
                m_caVidCellBase.SetTintColor(tintColor);
                m_scVidCellBase.SetTintColor(tintColor);
                m_sdVidCellBase.SetTintColor(tintColor);
                m_twVidCellBase.SetTintColor(tintColor);
                m_wkVidCellBase.SetTintColor(tintColor);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_a1VidCellExtend.SetTintColor(tintColor);
                    m_a2VidCellExtend.SetTintColor(tintColor);
                    m_a3VidCellExtend.SetTintColor(tintColor);
                    m_a4VidCellExtend.SetTintColor(tintColor);
                    m_deVidCellExtend.SetTintColor(tintColor);
                    m_ghVidCellExtend.SetTintColor(tintColor);
                    m_slVidCellExtend.SetTintColor(tintColor);
                    m_guVidCellExtend.SetTintColor(tintColor);
                    m_spVidCellExtend.SetTintColor(tintColor);
                    m_caVidCellExtend.SetTintColor(tintColor);
                    m_scVidCellExtend.SetTintColor(tintColor);
                    m_sdVidCellExtend.SetTintColor(tintColor);
                    m_twVidCellExtend.SetTintColor(tintColor);
                    m_wkVidCellExtend.SetTintColor(tintColor);
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
        // __LINE__: 26844
        UTIL_ASSERT(FALSE);
    }
}

// 0x6E73B0
void CGameAnimationTypeMonsterIcewind::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 26869
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a4VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_deVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_ghVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_slVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_guVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_spVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_scVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_sdVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_twVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_wkVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_a1VidCellBase.SuppressTint(0);
            m_a2VidCellBase.SuppressTint(0);
            m_a3VidCellBase.SuppressTint(0);
            m_a4VidCellBase.SuppressTint(0);
            m_deVidCellBase.SuppressTint(0);
            m_ghVidCellBase.SuppressTint(0);
            m_slVidCellBase.SuppressTint(0);
            m_guVidCellBase.SuppressTint(0);
            m_spVidCellBase.SuppressTint(0);
            m_caVidCellBase.SuppressTint(0);
            m_scVidCellBase.SuppressTint(0);
            m_sdVidCellBase.SuppressTint(0);
            m_twVidCellBase.SuppressTint(0);
            m_wkVidCellBase.SuppressTint(0);

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a4VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_deVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_ghVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_slVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_guVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_spVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_caVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_scVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_sdVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_twVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_wkVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_a1VidCellExtend.SuppressTint(0);
                m_a2VidCellExtend.SuppressTint(0);
                m_a3VidCellExtend.SuppressTint(0);
                m_a4VidCellExtend.SuppressTint(0);
                m_deVidCellExtend.SuppressTint(0);
                m_ghVidCellExtend.SuppressTint(0);
                m_slVidCellExtend.SuppressTint(0);
                m_guVidCellExtend.SuppressTint(0);
                m_spVidCellExtend.SuppressTint(0);
                m_caVidCellExtend.SuppressTint(0);
                m_scVidCellExtend.SuppressTint(0);
                m_sdVidCellExtend.SuppressTint(0);
                m_twVidCellExtend.SuppressTint(0);
                m_wkVidCellExtend.SuppressTint(0);
            }
        } else {
            m_a1VidCellBase.SetTintColor(tintColor);
            m_a2VidCellBase.SetTintColor(tintColor);
            m_a3VidCellBase.SetTintColor(tintColor);
            m_a4VidCellBase.SetTintColor(tintColor);
            m_deVidCellBase.SetTintColor(tintColor);
            m_ghVidCellBase.SetTintColor(tintColor);
            m_slVidCellBase.SetTintColor(tintColor);
            m_guVidCellBase.SetTintColor(tintColor);
            m_spVidCellBase.SetTintColor(tintColor);
            m_caVidCellBase.SetTintColor(tintColor);
            m_scVidCellBase.SetTintColor(tintColor);
            m_sdVidCellBase.SetTintColor(tintColor);
            m_twVidCellBase.SetTintColor(tintColor);
            m_wkVidCellBase.SetTintColor(tintColor);

            if (m_bExtendDir && !MIRROR_BAM) {
                m_a1VidCellExtend.SetTintColor(tintColor);
                m_a2VidCellExtend.SetTintColor(tintColor);
                m_a3VidCellExtend.SetTintColor(tintColor);
                m_a4VidCellExtend.SetTintColor(tintColor);
                m_deVidCellExtend.SetTintColor(tintColor);
                m_ghVidCellExtend.SetTintColor(tintColor);
                m_slVidCellExtend.SetTintColor(tintColor);
                m_guVidCellExtend.SetTintColor(tintColor);
                m_spVidCellExtend.SetTintColor(tintColor);
                m_caVidCellExtend.SetTintColor(tintColor);
                m_scVidCellExtend.SetTintColor(tintColor);
                m_sdVidCellExtend.SetTintColor(tintColor);
                m_twVidCellExtend.SetTintColor(tintColor);
                m_wkVidCellExtend.SetTintColor(tintColor);
            }
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

// 0x6E7A40
void CGameAnimationTypeMonsterIcewind::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27071
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27072
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if ((!m_bExtendDir || MIRROR_BAM) && m_currentBamDirection > m_extendDirectionTest) {
        dwRenderFlags |= CInfinity::MIRROR_FX;
    }

    if (m_bExtendDir && !MIRROR_BAM) {
        dwRenderFlags |= 0x4;
    }

    if ((m_bExtendDir && !MIRROR_BAM)
        || m_currentVidCellWeaponExtend != NULL
        || transparency != 0) {
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;

        if (transparency != 0) {
            dwRenderFlags |= 0x2;
        }
    } else {
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
        dwRenderFlags |= 0x1;
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
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

        if (m_currentVidCellWeaponExtend != NULL) {
            m_bitmap.GetRes()->Demand();
            m_currentVidCell->SetPalette(m_bitmap.GetRes()->GetColorTable(),
                m_bitmap.GetRes()->GetColorCount(),
                CVidPalette::TYPE_RESOURCE);
        }

        if (m_currentVidCellWeaponBase == NULL) {
            if (transparency != 0) {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags | 0x2,
                    transparency);
            } else {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags,
                    0);
            }
        } else {
            if (transparency != 0) {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags | 0x2,
                    (transparency * 128) / 255 + 128);
            } else {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags | 0x2,
                    128);
            }
        }

        if (m_currentVidCellWeaponExtend != NULL) {
            m_bitmap.Release();
        }

        m_currentVidCell->SetTintColor(oldTintColor);

        pInfinity->FXRenderClippingPolys(ptPos.x,
            ptPos.y - posZ,
            posZ,
            ptReference,
            CRect(rGCBounds.left, rGCBounds.top - posZ, rGCBounds.right, rGCBounds.bottom - posZ),
            bDithered,
            dwRenderFlags);

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

// 0x6E7DF0
SHORT CGameAnimationTypeMonsterIcewind::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
        m_currentVidCellBase = &m_guVidCellBase;
        m_currentVidCellExtend = &m_guVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 2:
        if ((m_animationID & 0x1) != 0) {
            m_currentVidCellBase = &m_caVidCellBase;
            m_currentVidCellExtend = &m_caVidCellExtend;
            m_currentBamSequence = 0;
        }
        break;
    case 3:
        if ((m_animationID & 0x1) != 0) {
            m_currentVidCellBase = &m_spVidCellBase;
            m_currentVidCellExtend = &m_spVidCellExtend;
            m_currentBamSequence = 0;
        }
        break;
    case 4:
        m_currentVidCellBase = &m_ghVidCellBase;
        m_currentVidCellExtend = &m_ghVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 5:
        m_currentVidCellBase = &m_deVidCellBase;
        m_currentVidCellExtend = &m_deVidCellExtend;
        m_currentBamSequence = 0;
    case 6:
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_sdVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_sdVidCellBase;
        m_currentVidCellExtend = &m_sdVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 7:
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_scVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_scVidCellBase;
        m_currentVidCellExtend = &m_scVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 8:
        if ((m_animationID & 2) != 0) {
            m_currentVidCellBase = &m_a4VidCellBase;
            m_currentVidCellExtend = &m_a4VidCellExtend;
            m_currentBamSequence = 0;
            nSequence = 8;
        }
        break;
    case 9:
        m_currentVidCellBase = &m_twVidCellBase;
        m_currentVidCellExtend = &m_twVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 10:
        m_currentVidCellBase = &m_wkVidCellBase;
        m_currentVidCellExtend = &m_wkVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 11:
        m_currentVidCellBase = &m_a1VidCellBase;
        m_currentVidCellExtend = &m_a1VidCellExtend;
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 12:
        if ((m_animationID & 4) != 0) {
            m_currentVidCellBase = &m_a3VidCellBase;
            m_currentVidCellExtend = &m_a3VidCellExtend;
        } else {
            m_currentVidCellBase = &m_a1VidCellBase;
            m_currentVidCellExtend = &m_a1VidCellExtend;
        }
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 13:
        if ((m_animationID & 8) != 0) {
            m_currentVidCellBase = &m_a2VidCellBase;
            m_currentVidCellExtend = &m_a2VidCellExtend;
        } else {
            m_currentVidCellBase = &m_a1VidCellBase;
            m_currentVidCellExtend = &m_a1VidCellExtend;
        }
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 14:
    case 15:
        nSequence = 7;
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_scVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_scVidCellBase;
        m_currentVidCellExtend = &m_scVidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 17:
        m_currentVidCellBase = &m_a1VidCellBase;
        m_currentVidCellExtend = &m_a1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 27299
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);

    SHORT nFrame = 0;
    if (bRandomFrame) {
        BYTE nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            nFrame = rand() % nSequenceLength;
        }
    }
    m_currentVidCell->FrameSet(nFrame);

    return nSequence;
}

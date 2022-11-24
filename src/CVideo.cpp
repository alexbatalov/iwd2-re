#include "CVideo.h"

#include "CVidInf.h"

// 0x794FC0
CVideo::CVideo()
{
    field_163 = 0;
    field_142 = 0;
    field_146 = 0;
    field_14A = 0;
    field_0 = 16;
    field_2 = 16;
    field_4 = 0;
    field_5 = 0;
    field_6 = 0;
    field_162 = 0;
    field_108 = 0;
    field_10C = 0;
    field_110 = 0;
    m_pVidModes[0] = NULL;
    m_pVidModes[1] = NULL;
    m_pVidModes[2] = NULL;
    m_pVidModes[3] = NULL;
    field_15E = 0;
    field_12A = 0;
    field_12E = 0;
    m_bIs3dAccelerated = FALSE;
    field_136 = 6408;
    field_13A = 0;
    field_13E = 0;
    field_114 = "";
    field_11C = -1;
    field_11E = 0;
    field_122 = 0;
    field_126 = 0;
}

// 0x7950A0
CVideo::~CVideo()
{
    for (int k = 0; k < 4; k++) {
        if (m_pVidModes[k] != NULL) {
            delete m_pVidModes[k];
            m_pVidModes[k] = NULL;
        }
    }

    // TODO: Incomplete.
}

// 0x7951B0
CVidMode* CVideo::GetVidMode(int a1)
{
    if (m_pVidModes[a1] == NULL) {
        if (a1 == 0) {
            m_pVidModes[a1] = new CVidInf();
        }
    }
    return m_pVidModes[a1];
}

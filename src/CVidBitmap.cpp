#include "CVidBitmap.h"

#include "CUtil.h"

// 0x7B2A40
CVidBitmap::CVidBitmap()
{
    m_nBitCount = 8;
    m_bDoubleSize = FALSE;
}

// 0x7B2DB0
CVidBitmap::~CVidBitmap()
{
}

// 0x7B2F60
BOOL CVidBitmap::GetPixelColor(RGBQUAD& color, INT nX, INT nY, BOOL bLoaded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 7337
    UTIL_ASSERT(pRes != NULL);

    if (pRes == NULL) {
        return FALSE;
    }

    if (bLoaded) {
        pRes->GetPixelColor(nX, nY, color, m_bDoubleSize);
        return TRUE;
    }

    if (pRes->Demand()) {
        pRes->GetPixelColor(nX, nY, color, m_bDoubleSize);
        pRes->Release();
        return TRUE;
    }

    return FALSE;
}

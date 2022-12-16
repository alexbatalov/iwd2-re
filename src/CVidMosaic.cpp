#include "CVidMosaic.h"

#include "CUtil.h"

// 0x7B0AA0
CVidMosaic::CVidMosaic()
{
    pRes = NULL;
    m_bDoubleSize = FALSE;
}

// 0x7B0B20
CVidMosaic::~CVidMosaic()
{
    // TODO: Incomplete.
}

// 0x7B0BF0
void CVidMosaic::GetSize(CSize& frameSize, BOOL a3)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5312
    UTIL_ASSERT(pRes != NULL);

    if (!a3) {
        pRes->Demand();
    }

    frameSize.cx = pRes->GetMosaicWidth(m_bDoubleSize);
    frameSize.cy = pRes->GetMosaicHeight(m_bDoubleSize);

    if (!a3) {
        pRes->Release();
    }
}

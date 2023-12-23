#include "CResBitmap.h"

#include "CUtil.h"

// 0x77EB90
CResBitmap::CResBitmap()
{
    nColors = 0;
    nXWords = 0;
    bParsed = FALSE;
    pBitmapData = NULL;
    pBitmapFileHeader = NULL;
    pBitmapInfoHeader = NULL;
    pColorTable = NULL;
}

// 0x77EBE0
CResBitmap::~CResBitmap()
{
}

// 0x77EC60
void* CResBitmap::Demand()
{
    void* pData = CRes::Demand();
    if (!bParsed || GetDemands() <= 1) {
        Parse(pData);

        if (!bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x77ECA0
int CResBitmap::GetBitDepth()
{
    if (bParsed) {
        return pBitmapInfoHeader->biBitCount;
    }

    return -1;
}

// 0x77ECC0
int CResBitmap::GetColorCount()
{
    if (bParsed) {
        return nColors != 0 ? nColors : 256;
    }

    return -1;
}

// 0x77ECE0
RGBQUAD* CResBitmap::GetColorTable()
{
    if (bParsed) {
        return pColorTable;
    }

    return NULL;
}

// 0x77ECF0
BYTE* CResBitmap::GetImageData(BOOL bDoubleSize)
{
    if (!bParsed) {
        return NULL;
    }

    if (!bDoubleSize || pBitmapInfoHeader->biBitCount == 4) {
        return pBitmapData;
    }

    if (m_pDimmKeyTableEntry != NULL) {
        if (m_pDimmKeyTableEntry->resRef == g_pChitin->cVideo.field_114
            && m_pDimmKeyTableEntry->nResType == g_pChitin->cVideo.field_11C) {
            return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
        }
        g_pChitin->cVideo.field_114 = m_pDimmKeyTableEntry->resRef;
        g_pChitin->cVideo.field_11C = m_pDimmKeyTableEntry->nResType;
    } else {
        g_pChitin->cVideo.field_114 = CResRef("");
        g_pChitin->cVideo.field_11C = -1;
    }

    g_pChitin->cVideo.field_11E = 0;
    g_pChitin->cVideo.SetDoubleSizeData(2 * pBitmapInfoHeader->biHeight * ((2 * pBitmapInfoHeader->biWidth * pBitmapInfoHeader->biBitCount / 8 + 3) & ~3));

    BYTE* pSrc = pBitmapData;
    BYTE* pDest = reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);

    INT nHeight = pBitmapInfoHeader->biHeight;
    INT nWidth = pBitmapInfoHeader->biWidth;
    INT nOffset = (2 * pBitmapInfoHeader->biWidth * pBitmapInfoHeader->biBitCount / 8 + 3) & ~3;
    INT nDestJump = nOffset - 2 * pBitmapInfoHeader->biWidth * pBitmapInfoHeader->biBitCount / 8;
    INT nSrcJump = ((pBitmapInfoHeader->biWidth * pBitmapInfoHeader->biBitCount / 8 + 3) & ~3) - pBitmapInfoHeader->biWidth * pBitmapInfoHeader->biBitCount / 8;

    BYTE color;
    BYTE r;
    BYTE g;
    BYTE b;
    int x;
    int y;

    switch (pBitmapInfoHeader->biBitCount) {
    case 8:
        for (y = 0; y < nHeight; y++) {
            for (x = 0; x < nWidth; x++) {
                color = *pSrc++;
                pDest[0] = color;
                pDest[nOffset] = color;
                pDest[1] = color;
                pDest[nOffset + 1] = color;
                pDest += 2;
            }
            pSrc += nSrcJump;
            pDest += nOffset + nDestJump;
        }
        break;
    case 24:
        for (y = 0; y < nHeight; y++) {
            for (x = 0; x < nWidth; x++) {
                r = *pSrc++;
                g = *pSrc++;
                b = *pSrc++;

                pDest[0] = r;
                pDest[nOffset] = r;
                pDest++;

                pDest[0] = g;
                pDest[nOffset] = g;
                pDest++;

                pDest[0] = b;
                pDest[nOffset] = b;
                pDest++;

                pDest[0] = r;
                pDest[nOffset] = r;
                pDest++;

                pDest[0] = g;
                pDest[nOffset] = g;
                pDest++;

                pDest[0] = b;
                pDest[nOffset] = b;
                pDest++;
            }
            pSrc += nSrcJump;
            pDest += nOffset + nDestJump;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 1564
        UTIL_ASSERT(FALSE);
    }

    return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
}

// 0x77EF70
void CResBitmap::GetImageDimensions(CSize& size, BOOL bDoubleSize)
{
    if (bParsed) {
        size.cx = pBitmapInfoHeader->biWidth;
        size.cy = pBitmapInfoHeader->biHeight;

        if (bDoubleSize) {
            size.cx *= 2;
            size.cy *= 2;
        }
    } else {
        size.cx = 0;
        size.cy = 0;
    }
}

// 0x77EFD0
BOOL CResBitmap::GetPixelColor(int x, int y, RGBQUAD& color, BOOL bDoubleSize)
{
    if (!bParsed) {
        return FALSE;
    }

    switch (pBitmapInfoHeader->biBitCount) {
    case 4:
    case 8:
        color = pColorTable[GetPixelValue(x, y, bDoubleSize)];
        return TRUE;
    case 24:
        if (bDoubleSize) {
            x *= 2;
            y *= 2;
        }

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDataTypes.cpp
        // __LINE__: 1686
        UTIL_ASSERT(!(x >= pBitmapInfoHeader->biWidth || x < 0 || y > pBitmapInfoHeader->biHeight || y < 0));

        color = *reinterpret_cast<RGBQUAD*>(pBitmapData + 3 * x + 4 * nXWords * (pBitmapInfoHeader->biHeight - y - 1));
    }

    return FALSE;
}

// 0x77F0B0
BYTE CResBitmap::GetPixelValue(int x, int y, BOOL bDoubleSize)
{
    if (bDoubleSize && pBitmapInfoHeader->biBitCount != 4) {
        x *= 2;
        y *= 2;
    }

    if (x >= 0 && x < pBitmapInfoHeader->biWidth
        && y >= 0 && y < pBitmapInfoHeader->biHeight) {
        switch (pBitmapInfoHeader->biBitCount) {
        case 4:
            if (bParsed) {
                if ((x & 1) == 0) {
                    return pBitmapData[4 * nXWords * (pBitmapInfoHeader->biHeight - y - 1) + x / 2] >> 4;
                } else {
                    return pBitmapData[4 * nXWords * (pBitmapInfoHeader->biHeight - y - 1) + x / 2] & 0xF;
                }
            }
            break;
        case 8:
            if (bParsed) {
                return pBitmapData[4 * nXWords * (pBitmapInfoHeader->biHeight - y - 1) + x];
            }
            break;
        }
    }

    return 0;
}

int CResBitmap::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        bParsed = FALSE;
        pBitmapFileHeader = NULL;
        pBitmapInfoHeader = NULL;
    }
    return rc;
}

// 0x77F1C0
BOOL CResBitmap::Parse(void* pData)
{
    bParsed = FALSE;
    pBitmapFileHeader = NULL;
    pBitmapInfoHeader = NULL;

    if (pData == NULL) {
        return FALSE;
    }

    pBitmapFileHeader = reinterpret_cast<LPBITMAPFILEHEADER>(pData);
    if (pBitmapFileHeader->bfType != 'MB') {
        pBitmapFileHeader = NULL;
        return FALSE;
    }

    pBitmapInfoHeader = reinterpret_cast<LPBITMAPINFOHEADER>(pBitmapFileHeader + 1);
    if (pBitmapInfoHeader->biCompression != 0) {
        return FALSE;
    }

    switch (pBitmapInfoHeader->biBitCount) {
    case 4:
        nColors = pBitmapInfoHeader->biClrUsed;
        pColorTable = reinterpret_cast<RGBQUAD*>(pBitmapInfoHeader + 1);
        pBitmapData = reinterpret_cast<BYTE*>(pData) + pBitmapFileHeader->bfOffBits;
        nXWords = pBitmapInfoHeader->biWidth / 8;
        if (pBitmapInfoHeader->biWidth % 8 != 0) {
            nXWords++;
        }
        break;
    case 8:
        nColors = pBitmapInfoHeader->biClrUsed;
        pColorTable = reinterpret_cast<RGBQUAD*>(pBitmapInfoHeader + 1);
        pBitmapData = reinterpret_cast<BYTE*>(pData) + pBitmapFileHeader->bfOffBits;
        nXWords = pBitmapInfoHeader->biWidth / 4;
        if (pBitmapInfoHeader->biWidth % 4 != 0) {
            nXWords++;
        }
        break;
    case 24:
        nColors = -1;
        pColorTable = NULL;
        pBitmapData = reinterpret_cast<BYTE*>(pData) + pBitmapFileHeader->bfOffBits;
        nXWords = 3 * pBitmapInfoHeader->biWidth / 4;
        if (3 * pBitmapInfoHeader->biWidth % 4 != 0) {
            nXWords++;
        }
        break;
    default:
        pBitmapFileHeader = NULL;
        pBitmapInfoHeader = NULL;
        return FALSE;
    }

    bParsed = TRUE;
    return bParsed;
}

// 0x77F310
BOOL CResBitmap::DemandLoadedBitmap()
{
    return Parse(m_pData);
}

// 0x77F320
void CResBitmap::ReleaseLoadedBitmap()
{
    bParsed = 0;
    pBitmapFileHeader = NULL;
    pBitmapInfoHeader = NULL;
}

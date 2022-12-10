#include "CUtil.h"

#include <zlib.h>

#include "CChitin.h"

// #guess
// 0x8FB8E8
CCriticalSection CUtil::ZLIB_CRITICAL_SECTION;

// 0x780AD0
int CUtil::Compress(BYTE* pDest, DWORD* nDestSize, const BYTE* pSrc, DWORD nSrcSize, int nLevel)
{
    CSingleLock compressionLock(&ZLIB_CRITICAL_SECTION, FALSE);
    compressionLock.Lock(INFINITE);

    int err = compress2(pDest, nDestSize, pSrc, nSrcSize, nLevel);

    compressionLock.Unlock();

    return err;
}

// 0x780B60
int CUtil::Uncompress(BYTE* dest, DWORD* destLen, const BYTE* source, DWORD sourceLen)
{
    CSingleLock decompressionLock(&ZLIB_CRITICAL_SECTION, FALSE);
    decompressionLock.Lock(INFINITE);

    int err = uncompress(dest, destLen, source, sourceLen);

    decompressionLock.Unlock();

    return err;
}

// 0x780C00
void CUtil::UtilAssert(int nLineNumber, const char* szFileName, const char* pExp, const char* pText)
{
    const char* fileName = strrchr(szFileName, '\\') + 1;
    if (pText == NULL) {
        pText = "no msg.";
    }

    char buffer[1024];
    sprintf(buffer, "ASSERTION FAILED!\nFile: %s\nLine: %d\n\nExp: %s\n\nMsg: %s\nRun Debugger?", fileName, nLineNumber, pExp, pText);

    g_pChitin->SuspendThreads();
    g_pChitin->ShutDown(nLineNumber, fileName, pText);

    abort();
}

// 0x780C80
LONG CUtil::UtilRandInt(LONG nRange, LONG nWeight)
{
    LONG nValue = nWeight + ((nRange * rand()) >> 15);

    if (nValue >= nRange) {
        nValue = nRange - 1;
    }

    if (nValue < 0) {
        nValue = 0;
    }

    return nValue;
}

// 0x780CB0
int CUtil::GetCurrentBitsPerPixels()
{
    HDC dc = GetDC(NULL);
    int bpp = GetDeviceCaps(dc, PLANES) * GetDeviceCaps(dc, BITSPIXEL);
    ReleaseDC(NULL, dc);
    return bpp;
}

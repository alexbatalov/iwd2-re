#ifndef CUTIL_H_
#define CUTIL_H_

#include "mfc.h"

class CUtil {
public:
    static int Compress(BYTE* pDest, DWORD* nDestSize, const BYTE* pSrc, DWORD nSrcSize, int nLevel);
    static int Uncompress(BYTE* dest, DWORD* destLen, const BYTE* source, DWORD sourceLen);
    static void UtilAssert(int nLineNumber, const char* szFileName, const char* pExp, const char* pText);
    static LONG UtilRandInt(LONG nRange, LONG nWeight);
    static int GetCurrentBitsPerPixels();

    static CCriticalSection ZLIB_CRITICAL_SECTION;
};

#define UTIL_ASSERT(cond)                                   \
    if (!(cond)) {                                          \
        CUtil::UtilAssert(__LINE__, __FILE__, #cond, NULL); \
    }

#define UTIL_ASSERT_MSG(cond, text)                         \
    if (!(cond)) {                                          \
        CUtil::UtilAssert(__LINE__, __FILE__, #cond, text); \
    }

#endif /* CUTIL_H_ */

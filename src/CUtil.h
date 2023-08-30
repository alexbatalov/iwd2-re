#ifndef CUTIL_H_
#define CUTIL_H_

#include "mfc.h"

class CVidFont;

class CUtil {
public:
    static int Compress(BYTE* pDest, DWORD* nDestSize, const BYTE* pSrc, DWORD nSrcSize, int nLevel);
    static int Uncompress(BYTE* dest, DWORD* destLen, const BYTE* source, DWORD sourceLen);
    __declspec(noreturn) static void UtilAssert(int nLineNumber, const char* szFileName, const char* pExp, const char* pText);
    static LONG UtilRandInt(LONG nRange, LONG nWeight);
    static int GetCurrentBitsPerPixels();
    static BYTE SplitString(CVidFont* pTextFont, const CString& sSource, WORD nLineLength, BYTE nMaxStrings, CString* pStringsOut, BOOL bDivideWords, BOOL bDemanded, BOOL bCheckRemainderForNewLine, WORD nSuggestedSplitLength);
    static int Find(const CString& sString, char ch, int start);
    static int FindOneOf(const CString& sString, const CString& sSeparators, int start);
    static void TrimLeft(CString& sString);
    static void TrimRight(CString& sString);

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

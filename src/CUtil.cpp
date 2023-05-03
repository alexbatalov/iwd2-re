#include "CUtil.h"

#include <zlib.h>

#include "CChitin.h"
#include "CVidFont.h"

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

// 0x780CF0
BYTE CUtil::SplitString(CVidFont* pTextFont, const CString& sSource, WORD nLineLength, BYTE nMaxStrings, CString* pStringsOut, BOOL bDivideWords, BOOL bDemanded, BOOL bCheckRemainderForNewLine, WORD nSuggestedSplitLength)
{
    if (sSource.Compare("") == 0) {
        return 0;
    }

    if (pStringsOut == NULL || nMaxStrings == 0 || nLineLength == 0) {
        return 0;
    }

    if (!bDemanded) {
        if (pTextFont->pRes->Demand() == NULL) {
            return 0;
        }
    }

    pStringsOut[0] = sSource;
    for (BYTE nNext = 1; nNext < nMaxStrings; nNext++) {
        pStringsOut[nNext] = "";
    }

    BYTE nCurrentLine = 0;
    while (nCurrentLine < nMaxStrings) {
        if (pStringsOut[nCurrentLine].IsEmpty()) {
            break;
        }

        int nSpace = -1;

        // TODO: Incomplete (unclear DBCS code).
        for (int nIndex = 0; nIndex < pStringsOut[nCurrentLine].GetLength(); nIndex++) {
            char ch = pStringsOut[nCurrentLine][nIndex];
            if (ch == '\n' || ch == '\r') {
                if (nCurrentLine + 1 < nMaxStrings) {
                    pStringsOut[nCurrentLine + 1] = pStringsOut[nCurrentLine].Mid(nIndex + 1);
                }

                if (nCurrentLine + 1 != nMaxStrings || bCheckRemainderForNewLine) {
                    pStringsOut[nCurrentLine] = pStringsOut[nCurrentLine].Left(nIndex);
                }

                break;
            }

            if (ch == ' ') {
                nSpace = nIndex;
            }

            LONG nSubStringWidth = pTextFont->GetStringLength(pStringsOut[nCurrentLine].Left(nIndex + 1), TRUE);

            // NOTE: Signed compare.
            if (nSubStringWidth > static_cast<WORD>(nLineLength)
                || (nSubStringWidth >= nSuggestedSplitLength
                    && nSpace == nIndex)) {
                if (nCurrentLine + 1 < nMaxStrings) {
                    if (bDivideWords || nSpace == -1) {
                        pStringsOut[nCurrentLine + 1] = pStringsOut[nCurrentLine].Mid(nIndex);
                        pStringsOut[nCurrentLine] = pStringsOut[nCurrentLine].Left(nIndex);
                    } else {
                        pStringsOut[nCurrentLine + 1] = pStringsOut[nCurrentLine].Mid(nSpace + 1);
                        pStringsOut[nCurrentLine] = pStringsOut[nCurrentLine].Left(nSpace);
                    }
                }

                break;
            }
        }

        nCurrentLine++;
    }

    if (!bDemanded) {
        pTextFont->pRes->Release();
    }

    return nCurrentLine;
}

// 0x781470
void CUtil::TrimLeft(CString& sString)
{
    int nIndex = 0;
    while (nIndex < sString.GetLength()) {
        if (g_pChitin->field_1A0 && IsDBCSLeadByte(sString[nIndex])) {
            break;
        }

        if (sString[nIndex] != ' '
            && sString[nIndex] != '\t'
            && sString[nIndex] != '\n') {
            break;
        }

        nIndex++;
    }

    sString = sString.Mid(nIndex);
}

#ifndef CUTIL_H_
#define CUTIL_H_

#include <afx.h>
#include <afxwin.h>

class CUtil {
public:
    static void UtilAssert(int nLineNumber, const char* szFileName, const char* pExp, const char* pText);
    static int GetCurrentBitsPerPixels();
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

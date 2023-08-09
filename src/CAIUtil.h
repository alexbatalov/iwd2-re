#ifndef CAIUTIL_H_
#define CAIUTIL_H_

#include "mfc.h"

class CAIUtil {
public:
    static CString ReadTo(CString& line, CString pattern, BOOL consume);
    static CString ReadBetween(CString& line, CString pattern);
    static CString ReadToChar(CString& line, char c);
    static CString ReadAfterChar(CString& line, char c);
};

#endif /* CAIUTIL_H_ */

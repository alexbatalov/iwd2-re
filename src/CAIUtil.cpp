#include "CAIUtil.h"

// 0x4215F0
CString CAIUtil::ReadToChar(CString& line, char c)
{
    for (int index = 0; index < line.GetLength(); index++) {
        if (line[index] == c) {
            return line.Left(index);
        }
    }

    return line;
}

// 0x4216D0
CString CAIUtil::ReadAfterChar(CString& line, char c)
{
    CString temp("");

    int index = line.Find(c);
    if (index >= 0) {
        temp = line.Right(line.GetLength() - index - 1);
    }

    return temp;
}

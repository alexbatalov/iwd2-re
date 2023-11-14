#include "CAIUtil.h"

// 0x4210E0
CString CAIUtil::RemoveAllWS(CString str)
{
    CString sTemp;
    char prev = ' ';

    int index = 0;
    while (index < str.GetLength()) {
        if (IsCharAlphaNumericA(str[index])) {
            sTemp += str[index];
        }

        switch (str[index]) {
        case '!':
        case '"':
        case '#':
        case '(':
        case ')':
        case '*':
        case ',':
        case '-':
        case '.':
        case '[':
        case ']':
        case '_':
            sTemp += str[index];
            break;
        case '/':
            if (prev == '/') {
                return sTemp.Left(sTemp.GetLength() - 1);
            }
            break;
        }

        prev = str[index];
        index++;
    }

    return sTemp;
}

// 0x421260
CString CAIUtil::ReadTo(CString& line, CString pattern, BOOL consume)
{
    CString sTemp;

    if (line.GetLength() < pattern.GetLength()) {
        return line;
    }

    int index = line.Find(pattern);
    if (index < 0) {
        return line;
    }

    sTemp = line.Left(index);

    if (consume) {
        line = line.Right(line.GetLength() - pattern.GetLength() - index);
    }

    return sTemp;
}

// 0x421390
CString CAIUtil::ReadBetween(CString& line, CString sep)
{
    CString sTemp;
    CString sRemainder;
    CString sBetween;

    if (line.GetLength() < sep.GetLength()) {
        return CString("");
    }

    int start = line.Find(sep);
    if (start < 0) {
        return CString("");
    }

    if (line.GetLength() <= sep.GetLength() + start) {
        sTemp = "";
    } else {
        sTemp = line.Right(line.GetLength() - sep.GetLength() - start);
    }

    int end = sTemp.Find(sep);
    if (end < 0) {
        return sTemp;
    }

    sBetween = sTemp.Left(end);

    if (sTemp.GetLength() <= sep.GetLength() + end) {
        sRemainder = "";
    } else {
        sRemainder = sTemp.Right(sTemp.GetLength() - sep.GetLength() - end);
    }

    line = sRemainder;

    return sBetween;
}

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

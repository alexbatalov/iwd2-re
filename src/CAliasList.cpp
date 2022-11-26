#include "CAliasList.h"

#include <direct.h>

#include "CAlias.h"

// #binary-identical
// 0x781A90
BOOL CAliasList::AddAlias(CAlias* pAlias)
{
    if (pAlias == NULL) {
        return FALSE;
    }

    if (pAlias->field_4) {
        AddTail(pAlias);
    }

    return pAlias->field_4;
}

// #not-binary-identical
// 0x781AC0
BOOL CAliasList::ResolveFileName(const CString& a2, CString& a3)
{
    CString temp;
    CFileFind fileFind;
    char workingDirectory[260];

    POSITION aliasPos = GetHeadPosition();
    while (aliasPos != NULL) {
        CAlias* pAlias = static_cast<CAlias*>(GetNext(aliasPos));
        if (pAlias != NULL) {
            if (a2.FindOneOf(pAlias->field_8) != -1) {
                POSITION pos = pAlias->field_C.GetHeadPosition();
                if (pos != NULL) {
                    while (pos != NULL) {
                        temp = pAlias->field_C.GetNext(pos);
                        if (temp.GetAt(0) == '.' && temp.GetAt(1) != '.') {
                            if (getcwd(workingDirectory, sizeof(workingDirectory)) != NULL) {
                                temp = workingDirectory;

                                int length = strlen(workingDirectory);
                                if (workingDirectory[length - 1] == '/' || workingDirectory[length - 1] == '\\') {
                                    temp += a2.Right(a2.GetLength() - 2);
                                } else {
                                    temp += a2.Right(a2.GetLength() - 1);
                                }
                            }
                        }

                        a3 = a2.Right(a2.GetLength() - pAlias->field_8.GetLength());
                        a3 = temp + a3;

                        if (fileFind.FindFile(a3)) {
                            break;
                        }

                        if (fileFind.FindFile(a3 + "*.*")) {
                            break;
                        }
                    }

                    return TRUE;
                }
            }
        }
    }

    if (a2.GetAt(0) == '.' && a2.GetAt(1) != '.') {
        if (getcwd(workingDirectory, sizeof(workingDirectory)) != NULL) {
            a3 = workingDirectory;

            int length = strlen(workingDirectory);
            if (workingDirectory[length - 1] == '/' || workingDirectory[length - 1] == '\\') {
                a3 += a2.Right(a2.GetLength() - 2);
            } else {
                a3 += a2.Right(a2.GetLength() - 1);
            }

            return TRUE;
        }
    }

    return FALSE;
}

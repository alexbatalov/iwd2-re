#include "CImm.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidMosaic.h"
#include "CWarp.h"

// 0xA09FC0
const CSize CImm::PADDING(3, 3);

// WM_IME_STARTCOMPOSITION
// NOTE: Inlined in `WndProc`.
void CImm::OnStartComposition()
{
    m_dwState |= 0x1;
}

// WM_IME_ENDCOMPOSITION
// NOTE: Inlined in `WndProc`.
void CImm::OnEndComposition()
{
    m_dwState &= ~0x1;
}

// WM_IME_COMPOSITION
// 0x7C2640
void CImm::OnComposition(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if ((lParam & GCS_RESULTSTR) != 0) {
        if ((lParam & GCS_RESULTCLAUSE) != 0) {
            sub_7C27D0(hWnd, TRUE);
        } else {
            sub_7C27D0(hWnd, FALSE);
        }
    } else if ((lParam & GCS_COMPSTR) != 0) {
        sub_7C2680(hWnd, lParam);
    }
}

// 0x7C2680
void CImm::sub_7C2680(HWND hWnd, LPARAM lParam)
{
    CSingleLock lock(&m_cCriticalSection);
    lock.Lock();

    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        LONG nCompStrLength = ImmGetCompositionStringA(hImc, GCS_COMPSTR, NULL, 0);
        if (nCompStrLength != 0) {
            CHAR* lpCompStr = new CHAR[nCompStrLength + 1];

            // __FILE__: C:\Projects\Icewind2\src\chitin\chimeui.cpp
            // __LINE__: 109
            UTIL_ASSERT(lpCompStr != NULL);

            ImmGetCompositionStringA(hImc, GCS_COMPSTR, lpCompStr, nCompStrLength);
            lpCompStr[nCompStrLength] = '\0';

            field_134 = lpCompStr;

            delete lpCompStr;

            if ((lParam & GCS_COMPATTR) != 0) {
                LONG nCompStrAttrLength = ImmGetCompositionStringA(hImc, GCS_COMPATTR, NULL, 0);
                if (nCompStrAttrLength != 0) {
                    CHAR* lpCompStrAttr = new CHAR[nCompStrAttrLength + 1];

                    // __FILE__: C:\Projects\Icewind2\src\chitin\chimeui.cpp
                    // __LINE__: 124
                    UTIL_ASSERT(lpCompStrAttr != NULL);

                    ImmGetCompositionStringA(hImc, GCS_COMPATTR, lpCompStrAttr, nCompStrAttrLength);
                    lpCompStrAttr[nCompStrAttrLength] = '\0';

                    delete lpCompStrAttr;
                }
            }
        }

        ImmReleaseContext(hWnd, hImc);
        lock.Unlock();
    }
}

// 0x7C27D0
void CImm::sub_7C27D0(HWND hWnd, BOOL a3)
{
    CSingleLock lock(&m_cCriticalSection);
    lock.Lock();

    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        LONG nResultStrLength = ImmGetCompositionStringA(hImc, GCS_RESULTSTR, NULL, 0);
        if (nResultStrLength != 0) {
            CHAR* lpResultStr = new CHAR[nResultStrLength + 1];

            // __FILE__: C:\Projects\Icewind2\src\chitin\chimeui.cpp
            // __LINE__: 176
            UTIL_ASSERT(lpResultStr != NULL);

            ImmGetCompositionStringA(hImc, GCS_COMPSTR, lpResultStr, nResultStrLength);
            lpResultStr[nResultStrLength] = '\0';

            field_130 = lpResultStr;

            delete lpResultStr;

            if (a3) {
                LONG nResultClsLength = ImmGetCompositionStringA(hImc, GCS_RESULTCLAUSE, NULL, 0);
                if (nResultClsLength != 0) {
                    CHAR* lpResultCls = new CHAR[nResultClsLength + 1];

                    // __FILE__: C:\Projects\Icewind2\src\chitin\chimeui.cpp
                    // __LINE__: 188
                    UTIL_ASSERT(lpResultCls != NULL);

                    ImmGetCompositionStringA(hImc, GCS_RESULTCLAUSE, lpResultCls, nResultClsLength);
                    lpResultCls[nResultClsLength] = '\0';

                    field_130 += CString(lpResultCls);

                    delete lpResultCls;

                    field_134 = "";
                    m_sCandidateList = "";

                    g_pChitin->pActiveEngine->OnKeyDown(1);
                }
            }
        }

        ImmReleaseContext(hWnd, hImc);
        lock.Unlock();
    }
}

// WM_IME_NOTIFY
// 0x7C29C0
BOOL CImm::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam) {
    case IMN_CHANGECANDIDATE:
    case IMN_OPENCANDIDATE:
        HandleCandidateList(hWnd, lParam);
        return TRUE;
    case IMN_CLOSECANDIDATE:
        m_sCandidateList = "";
        m_dwState &= ~0x2;
        return TRUE;
    case IMN_SETOPENSTATUS:
        if (1) {
            HIMC hImc = ImmGetContext(hWnd);
            if (hImc != NULL) {
                if (!ImmGetOpenStatus(hImc)) {
                    m_sCandidateList = "";
                    m_dwState = 0;
                }
                ImmReleaseContext(hWnd, hImc);
            }
        }
        return TRUE;
    default:
        return FALSE;
    }
}

// 0x7C2A80
void CImm::HandleCandidateList(HWND hWnd, LPARAM lParam)
{
    CSingleLock lock(&m_cCriticalSection);
    lock.Lock();

    m_dwState &= ~0x2;
    m_sCandidateList = "";

    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        for (DWORD index = 0; index < 32; index++) {
            if ((lParam & (1 << index)) != 0) {
                DWORD nLength = ImmGetCandidateListA(hImc, index, NULL, 0);
                if (nLength != 0) {
                    CHAR* lpStr = new CHAR[nLength];

                    // __FILE__: C:\Projects\Icewind2\src\chitin\chimeui.cpp
                    // __LINE__: 306
                    UTIL_ASSERT(lpStr != NULL);

                    ImmGetCandidateListA(hImc, index, (LPCANDIDATELIST)lpStr, lParam);
                    m_sCandidateList = ParseCandidateList((LPCANDIDATELIST)lpStr);

                    delete lpStr;

                    m_dwState |= 0x2;
                }
                break;
            }
        }

        ImmReleaseContext(hWnd, hImc);
        lock.Unlock();
    }
}

// 0x7C2BD0
CString CImm::ParseCandidateList(LPCANDIDATELIST lpCandidateList)
{
    CString sString("");
    // TODO: Odd size.
    char buffer[52];

    DWORD dwPageSize = lpCandidateList->dwPageSize;
    if (dwPageSize == 0) {
        dwPageSize = 5;
    }

    DWORD dwEnd = lpCandidateList->dwPageStart + dwPageSize;
    if (dwEnd >= lpCandidateList->dwCount) {
        dwEnd = lpCandidateList->dwCount;
    }

    int nNum = 1;
    for (DWORD nIndex = lpCandidateList->dwPageStart; nIndex < dwEnd; nIndex++) {
        LPCSTR lpCandidate = (LPCSTR)lpCandidateList + lpCandidateList->dwOffset[nIndex];
        buffer[lstrlenA(lpCandidate)] = '\0';
        sprintf(buffer, "%d:%s  ", nNum, lpCandidate);
        sString += buffer;
        nNum++;
    }

    return sString;
}

// 0x7C2CC0
void CImm::sub_7C2CC0(HWND hWnd)
{
    field_12C = FALSE;

    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        DWORD fdwConversion;
        DWORD fdwSentense;
        ImmGetConversionStatus(hImc, &fdwConversion, &fdwSentense);
        fdwConversion |= IME_CMODE_NATIVE;

        switch (PRIMARYLANGID(GetSystemDefaultLangID())) {
        case LANG_CHINESE:
            if (m_hKeyboardLayout != NULL) {
                ActivateKeyboardLayout((HKL)HKL_NEXT, 0);
            } else {
                m_hKeyboardLayout = ActivateKeyboardLayout((HKL)HKL_NEXT, 0);
            }

            if (m_hKeyboardLayout == GetKeyboardLayout(0)) {
                ActivateKeyboardLayout((HKL)HKL_NEXT, 0);
            }
            break;
        case LANG_JAPANESE:
            if (m_hKeyboardLayout != NULL) {
                ActivateKeyboardLayout((HKL)HKL_NEXT, KLF_REORDER);
            } else {
                m_hKeyboardLayout = ActivateKeyboardLayout((HKL)HKL_NEXT, KLF_REORDER);
            }

            ImmSetOpenStatus(hImc, TRUE);

            if (field_12C) {
                field_12C = FALSE;
                fdwConversion &= ~IME_CMODE_KATAKANA;
                fdwConversion |= IME_CMODE_FULLSHAPE;
            } else {
                fdwConversion |= IME_CMODE_KATAKANA;
                fdwConversion |= IME_CMODE_FULLSHAPE;
                field_12C = TRUE;
            }
        }

        ImmSetConversionStatus(hImc, fdwConversion, fdwSentense);

        field_128 = 1;

        ImmReleaseContext(hWnd, hImc);

        m_sCandidateList = "";
        field_134 = "";
        field_130 = "";
    }
}

// 0x7C2E10
void CImm::sub_7C2E10(HWND hWnd)
{
    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        DWORD fdwConversion;
        DWORD fdwSentense;
        ImmGetConversionStatus(hImc, &fdwConversion, &fdwSentense);

        fdwConversion &= ~IME_CMODE_NATIVE;
        ImmSetConversionStatus(hImc, fdwConversion, fdwSentense);

        switch (PRIMARYLANGID(GetSystemDefaultLangID())) {
        case LANG_CHINESE:
            if (m_hKeyboardLayout != NULL) {
                ActivateKeyboardLayout(m_hKeyboardLayout, KLF_REORDER);
            }
            break;
        case LANG_JAPANESE:
            ImmSetOpenStatus(hImc, FALSE);

            if (m_hKeyboardLayout != NULL) {
                ActivateKeyboardLayout(m_hKeyboardLayout, KLF_REORDER);
            }
            break;
        }

        ImmReleaseContext(hWnd, hImc);

        m_sCandidateList = "";
        field_134 = "";
        field_130 = "";
    }
}

// 0x7C2ED0
CString CImm::sub_7C2ED0(HWND hWnd)
{
    CString sString("");

    HIMC hImc = ImmGetContext(hWnd);
    if (hImc != NULL) {
        switch (PRIMARYLANGID(GetSystemDefaultLangID())) {
        case LANG_CHINESE:
            if (1) {
                CHAR szDescription[5] = { 0 };
                ImmGetDescriptionA(GetKeyboardLayout(0), szDescription, sizeof(szDescription));
                szDescription[4] = '\0';

                if (szDescription[0] != '\0') {
                    sString = szDescription;
                } else {
                    sString = "En";
                }

                ImmReleaseContext(hWnd, hImc);
            }
            break;
        case LANG_JAPANESE:
            if (1) {
                DWORD fdwConversion;
                DWORD fdwSentense;
                ImmGetConversionStatus(hImc, &fdwConversion, &fdwSentense);

                if ((fdwConversion & IME_CMODE_NATIVE) != 0 && (fdwConversion & IME_CMODE_KATAKANA) != 0) {
                    sString = "\x91\x53\x8A\x70\x83\x4A\x83\x5E\x83\x4A\x83\x69";
                } else {
                    sString = "\x91\x53\x8A\x70\x82\xD0\x82\xE7\x82\xAA\x82\xC8";
                }
            }
            break;
        }

        // FIXME: Leaking `hImc`.
    }

    return sString;
}

// 0x7C3140
void CImm::sub_7C3140(const CRect& a1, const CRect& a2, int a3, BOOL bDemanded)
{
    // TODO: Incomplete.
}

// 0x7C34A0
CString CImm::sub_7C34A0()
{
    return m_sCandidateList;
}

// 0x7C34D0
CString CImm::sub_7C34D0()
{
    return field_134;
}

// NOTE: Probably inlined in `CChitin::DestroyServices`.
void CImm::CleanUp()
{
    if (field_13C != NULL) {
        delete field_13C;
    }

    field_13C = NULL;
}

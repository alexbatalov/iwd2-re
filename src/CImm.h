#ifndef CIMM_H_
#define CIMM_H_

#include "mfc.h"

class CVidMosaic;

// #guess
class CImm {
public:
    // NOTE: Constructor is inlined in `CChitin` constructor. This is the only
    // way to explain how assignments appear before other static object
    // constructor calls.
    CImm()
    {
        m_dwState = 0;
        field_12C = FALSE;
        field_128 = 0;
        m_hKeyboardLayout = NULL;
        field_13C = 0;
    }

    // NOTE: Destructor is inlined in `CChitin` destructor.
    ~CImm() { }

    void OnStartComposition();
    void OnEndComposition();
    void OnComposition(HWND hWnd, WPARAM wParam, LPARAM lParam);
    void sub_7C2680(HWND hWnd, LPARAM lParam);
    void sub_7C27D0(HWND hWnd, BOOL a3);
    BOOL OnNotify(HWND hWnd, WPARAM wPara, LPARAM lParam);
    void HandleCandidateList(HWND hWnd, LPARAM lParam);
    CString ParseCandidateList(LPCANDIDATELIST lpCandidateList);
    void sub_7C2CC0(HWND hWnd);
    void sub_7C2E10(HWND hWnd);
    CString sub_7C2ED0(HWND hWnd);
    void sub_7C3140(const CRect& a1, const CRect& a2, int a3, BOOL bDemanded);
    CString sub_7C34A0();
    CString sub_7C34D0();
    void CleanUp();

    static const CSize PADDING;

    /* 0000 */ DWORD m_dwState;
    /* 0104 */ HKL m_hKeyboardLayout;
    /* 0108 */ CCriticalSection m_cCriticalSection;
    /* 0128 */ int field_128;
    /* 012C */ BOOL field_12C;
    /* 0130 */ CString field_130;
    /* 0134 */ CString field_134;
    /* 0138 */ CString m_sCandidateList;
    /* 013C */ CVidMosaic* field_13C;
};

#endif /* CIMM_H_ */

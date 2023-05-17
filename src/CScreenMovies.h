#ifndef CSCREENMOVIES_H_
#define CSCREENMOVIES_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlTextDisplay.h"
#include "CVidFont.h"

#define CSCREENMOVIES_VIRTUAL_KEYS 46

class CScreenMovies : public CBaldurEngine {
public:
    CScreenMovies();
    /* 0004 */ ~CScreenMovies() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00AC */ void OnKeyDown(SHORT nKeysFlags) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;

    void OnMovieItemSelect(INT nMovieIndex);
    void OnPlayButtonClick();
    void OnCreditsButtonClick();
    void OnDoneButtonClick();
    void StartMovies(INT nEngineState);
    void StopMovies();

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENMOVIES_VIRTUAL_KEYS];
    /* 0276 */ BYTE m_pVirtualKeysFlags[CSCREENMOVIES_VIRTUAL_KEYS];
    /* 02A4 */ INT m_nEngineState;
    /* 02A8 */ CStringList* m_pMovies;
    /* 02AC */ INT m_nMovieIndex;
    /* 02B0 */ CVidFont m_preLoadFontRealms;
    /* 07B0 */ unsigned char field_7B0;
};

class CUIControlTextDisplayMovies : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayMovies(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayMovies() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonMoviesPlay : public CUIControlButton {
public:
    CUIControlButtonMoviesPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMoviesPlay() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMoviesCredits : public CUIControlButton {
public:
    CUIControlButtonMoviesCredits(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMoviesCredits() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMoviesDone : public CUIControlButton {
public:
    CUIControlButtonMoviesDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMoviesDone() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENMOVIES_H_ */

#ifndef CSCREENMAP_H_
#define CSCREENMAP_H_

#include "CBaldurEngine.h"
#include "CUIControlButton.h"

class CScreenMap : public CBaldurEngine {
public:
    CScreenMap();
    ~CScreenMap();

    void OnErrorButtonClick(INT nButton);
    void OnCancelButtonClick();
    void OnDoneButtonClick();
};

class CUIControlButtonMapWorld : public CUIControlButton {
public:
    CUIControlButtonMapWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapWorld() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapError : public CUIControlButton {
public:
    CUIControlButtonMapError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNoteDone : public CUIControlButton {
public:
    CUIControlButtonMapNoteDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNoteCancel : public CUIControlButton {
public:
    CUIControlButtonMapNoteCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENMAP_H_ */

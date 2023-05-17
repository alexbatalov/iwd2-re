#ifndef CSCREENSTORE_H_
#define CSCREENSTORE_H_

#include "CBaldurEngine.h"
#include "CUIControlButton.h"

class CScreenStore : public CBaldurEngine {
public:
    CScreenStore();
    ~CScreenStore();
};

class CUIControlPortraitStore : public CUIControlButton {
public:
    CUIControlPortraitStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitStore() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSTORE_H_ */

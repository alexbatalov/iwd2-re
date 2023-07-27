#ifndef CSCREENMAP_H_
#define CSCREENMAP_H_

#include "CBaldurEngine.h"
#include "CUIControlButton.h"

class CScreenMap : public CBaldurEngine {
public:
    CScreenMap();
    ~CScreenMap();

    void OnErrorButtonClick(INT nButton);
};

class CUIControlButtonMapError : public CUIControlButton {
public:
    CUIControlButtonMapError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapError() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENMAP_H_ */

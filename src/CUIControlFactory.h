#ifndef CUICONTROLFACTORY_H_
#define CUICONTROLFACTORY_H_

#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlTextDisplay.h"

class CBaldurEngine;

class CUIControlButtonHotArea : public CUIControlButton {
public:
    CUIControlButtonHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonHotArea() override;
    BOOL Render(BOOL bForce) override;
    BOOL OnLButtonDown(CPoint pt) override;
    virtual void OnHotAreaClick(CPoint pt);
};

class CUIControlButtonOptionsHotArea : public CUIControlButtonHotArea {
public:
    CUIControlButtonOptionsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsHotArea() override;
    void OnHotAreaClick(CPoint pt) override;
};

class CUIControlPortraitBase : public CUIControlButton {
public:
    CUIControlPortraitBase(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons);
    ~CUIControlPortraitBase();
};

class CUIControlTextDisplayJournal : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayJournal(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayJournal() override;
    void OnButtonLClick(CPoint pt) override;
};

class CUIControlPortraitGeneral : public CUIControlPortraitBase {
public:
    CUIControlPortraitGeneral(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitGeneral() override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;
};

class CUIControlButtonAI : public CUIControlButton {
public:
    CUIControlButtonAI(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonAI() override;
};

class CUIControlButtonRest : public CUIControlButton {
public:
    CUIControlButtonRest(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonRest() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonGeneralBase : public CUIControlButton3State {
public:
    CUIControlButtonGeneralBase(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralBase() override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ CBaldurEngine* field_66E;
};

class CUIControlButtonGeneralWorld : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralWorld() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonGeneralInventory : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralInventory(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralInventory() override;
};

class CUIControlButtonGeneralMap : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralMap() override;
};

class CUIControlButtonGeneralJournal : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralJournal(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralJournal() override;
};

class CUIControlButtonGeneralCharacter : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralCharacter() override;
};

class CUIControlButtonGeneralSpellbook : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralSpellbook(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralSpellbook() override;
};

class CUIControlButtonGeneralOptions : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralOptions() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonGeneralOptionsFromMainMenu : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralOptionsFromMainMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralOptionsFromMainMenu() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonGeneralMultiPlayer : public CUIControlButtonGeneralBase {
public:
    CUIControlButtonGeneralMultiPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonGeneralMultiPlayer() override;
};

class CUIControlButton77DCC0 : public CUIControlButton {
public:
    CUIControlButton77DCC0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButton77DCC0() override;

    /* 0666 */ short field_666;
    /* 0668 */ short field_668;
};

#endif /* CUICONTROLFACTORY_H_ */

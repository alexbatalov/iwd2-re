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

class CUIControlButtonCharGenPortrait : public CUIControlButton {
public:
    CUIControlButtonCharGenPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenPortrait() override;
    BOOL Render(BOOL bForce) override;
    void SetPortrait(const CResRef& resRef);

    /* 0666 */ CResRef m_portraitResRef;
};

class CUIControlButtonCharGenAbilitiesHotArea : public CUIControlButtonHotArea {
public:
    CUIControlButtonCharGenAbilitiesHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAbilitiesHotArea() override;
    void OnHotAreaClick(CPoint pt) override;
};

class CUIControlButtonCharGenSkillsHotArea : public CUIControlButtonHotArea {
public:
    CUIControlButtonCharGenSkillsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenSkillsHotArea() override;
    void OnHotAreaClick(CPoint pt) override;
};

class CUIControlButtonCharGenAppearancePortrait : public CUIControlButton {
public:
    CUIControlButtonCharGenAppearancePortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAppearancePortrait() override;
    BOOL Render(BOOL bForce) override;
    void SetPortrait(const CResRef& resRef);

    /* 0666 */ CResRef m_portraitResRef;
};

class CUIControlButtonCharGenAppearanceLeft : public CUIControlButton {
public:
    CUIControlButtonCharGenAppearanceLeft(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAppearanceLeft() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenAppearanceRight : public CUIControlButton {
public:
    CUIControlButtonCharGenAppearanceRight(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenAppearanceRight() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonCharGenHairSkinAppearance : public CUIControlButton {
public:
    CUIControlButtonCharGenHairSkinAppearance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenHairSkinAppearance() override;
    BOOL Render(BOOL bForce) override;
};

class CUIControlButtonCharGenFeatsHotArea : public CUIControlButtonHotArea {
public:
    CUIControlButtonCharGenFeatsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharGenFeatsHotArea() override;
    void OnHotAreaClick(CPoint pt) override;
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

class CUIControlButtonMultiPlayerHotArea : public CUIControlButtonHotArea {
public:
    CUIControlButtonMultiPlayerHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerHotArea() override;
    void OnHotAreaClick(CPoint pt) override;
};

class CUIControlPortraitGeneral : public CUIControlPortraitBase {
public:
    CUIControlPortraitGeneral(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitGeneral() override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;
};

class CUIControlButtonCharacterPortrait : public CUIControlButton {
public:
    CUIControlButtonCharacterPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonCharacterPortrait() override;
    void SetPortrait(const CResRef& resRef);

    /* 0666 */ CResRef m_portraitResRef;
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

class CUIControlEncumbrance : public CUIControlButton {
public:
    CUIControlEncumbrance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlEncumbrance() override;
    BOOL Render(BOOL bForce) override;

    void SetEncumbrance(int a1, int a2);
    void SetVolume(int a1, int a2);

    /* 0666 */ CVidFont field_666;
    /* 0B66 */ int field_B66;
    /* 0B6A */ int field_B6A;
    /* 0B6E */ int field_B6E;
    /* 0B72 */ int field_B72;
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

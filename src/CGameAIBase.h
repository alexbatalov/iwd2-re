#ifndef CGAMEAIBASE_H_
#define CGAMEAIBASE_H_

#include "CAIAction.h"
#include "CAIObjectType.h"
#include "CGameObject.h"

class CAIResponse;
class CAIScript;
class CAITrigger;
class CGameDoor;
class CGameEffect;
class CGameSpawning;
class CGameSprite;
class CGameStatic;
class CGameTiledObject;
class CGameTimer;
class CGameTrigger;
class CItem;
class CResRef;
class CSpell;
class CVariable;

class CGameAIBase : public CGameObject {
public:
    static const SHORT ACTION_DONE;
    static const SHORT ACTION_INTERRUPTABLE;
    static const SHORT ACTION_NORMAL;
    static const SHORT ACTION_ERROR;
    static const SHORT ACTION_NO_ACTION;
    static const SHORT ACTION_STOPPED;

    static const BYTE EFFECT_LIST_TIMED;
    static const BYTE EFFECT_LIST_EQUIPED;

    static const CString DEAD_GLOBAL_PREFIX;
    static CAIAction m_aiAction;

    CGameAIBase();
    /* 0000 */ ~CGameAIBase() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 006C */ virtual void ClearActions(BOOL a1);
    /* 0074 */ virtual void AddAction(const CAIAction& action);
    /* 0078 */ virtual void AddEffect(CGameEffect* pEffect, BYTE list, BOOL noSave, BOOL immediateApply);
    /* 007C */ virtual void ClearAI(BOOLEAN a1);
    /* 0080 */ virtual void DoAction();
    /* 0084 */ virtual SHORT ExecuteAction();
    /* 0088 */ virtual void InsertAction(const CAIAction& action);
    /* 008C */ virtual void ProcessAI();
    /* 0090 */ virtual void SetCurrAction(const CAIAction& action);
    /* 0094 */ virtual void SetScript(SHORT level, CAIScript* script);
    /* 0098 */ virtual SHORT GetVisualRange();
    /* 009C */ virtual const BYTE* GetVisibleTerrainTable();
    /* 00A0 */ virtual const BYTE* GetTerrainTable();
    /* 00A8 */ virtual SHORT GetHelpRange();
    /* 00AC */ virtual void ApplyTriggers();
    /* 00B0 */ virtual void AutoPause(DWORD type);
    /* 00B4 */ virtual BOOL GetCanSeeInvisible();

    void CheckTimers(LONG cycles);
    void ClearTriggers();
    BOOL CheckAppropriateTarget(CSpell* pSpell, CGameAIBase* pTarget);
    BOOL PartyHasItem(const CResRef& resRef);
    void ApplyEffectToParty(CGameEffect* pEffect);
    SHORT MoveView(CPoint dest, int speed);
    SHORT MoveViewPoint();
    SHORT MoveViewObject(CGameObject* target);
    SHORT MoveCursor(CPoint dest, SHORT speed);
    SHORT ClickLButton(CPoint pt);
    SHORT ClickLButtonPoint();
    SHORT ClickLButtonObject(CGameObject* target);
    SHORT DoubleClickLButton(CPoint pt);
    SHORT DoubleClickLButtonPoint();
    SHORT DoubleClickLButtonObject(CGameObject* target);
    SHORT ClickRButton(CPoint pt);
    SHORT ClickRButtonPoint();
    SHORT ClickRButtonObject(CGameObject* target);
    SHORT DoubleClickRButton(CPoint pt);
    SHORT DoubleClickRButtonPoint();
    SHORT DoubleClickRButtonObject(CGameObject* target);
    SHORT MoveCursorPoint();
    SHORT ChangeAIScript();
    SHORT StartTimer();
    SHORT SendTrigger(CGameAIBase* sprite);
    SHORT Wait();
    SHORT SmallWait();
    SHORT Shout();
    void PutItemGround(CItem* pItem);
    SHORT ClearActions(CGameObject* target);
    SHORT TakePartyGold();
    SHORT GivePartyGold();
    SHORT GiveOrder(CGameAIBase* sprite);
    SHORT DisplayString(CGameAIBase* sprite);
    SHORT StartMovie();
    SHORT RevealAreaOnMap();
    SHORT ChangeTileState(CGameTiledObject* target);
    SHORT TriggerActivation(CGameTrigger* target);
    SHORT StartMusic();
    SHORT SetMusic();
    SHORT FinalSave();
    SHORT Unlock(CGameAIBase* pObject);
    SHORT MoveGlobal(CGameSprite* pSprite);
    SHORT Lock(CGameAIBase* pObject);
    SHORT DestroyItem();
    SHORT DetectSecretDoor(CGameDoor* target);
    SHORT FadeToColor();
    SHORT FadeFromColor();
    SHORT sub_467970();
    SHORT SpawnPtActivate(CGameSpawning* target);
    SHORT SpawnPtDeactivate(CGameSpawning* target);
    SHORT SpawnPtSpawn(CGameSpawning* target);
    SHORT StaticStart(CGameStatic* target, BOOL bStart);

    SCRIPTNAME& GetScriptName();
    void SetTrigger(const CAITrigger& trigger);

    void SetDefaultScript(CAIScript* script);
    void ResetCurrResponse();
    CAIAction& GetNextAction(CAIAction& action);
    void InsertResponse(CAIResponse& response, BOOL checkCurrentResponse, BOOL clearActions);

    void sub_481890(CRect* r, CArray<CRect*>& ary);
    void FireSpell(const CResRef& resRef, CGameObject* target);
    static CVariable* GetGlobalVariable(const CString& sScope, const CString& sName, int a3);
    void sub_4530F0(const CAIObjectType& type);
    void sub_453110(const CAIObjectType& type);
    void SetLastActionReturn(SHORT returnValue);
    int sub_45B6D0();
    void sub_45B6E0(const CAIObjectType& type);

    /* 006E */ CAIObjectType m_lAttacker;
    /* 00AA */ LONG m_lAttackStyle;
    /* 00AE */ CAIObjectType m_lOrderedBy;
    /* 00EA */ CAIObjectType field_EA;
    /* 0126 */ CAIObjectType field_126;
    /* 0162 */ CAIObjectType field_162;
    /* 019E */ CAIObjectType m_lHitter;
    /* 01DA */ CAIObjectType m_lHelp;
    /* 0216 */ CAIObjectType m_lTrigger;
    /* 0252 */ CAIObjectType m_lSeen;
    /* 028E */ CAIObjectType m_lTalkedTo;
    /* 02CA */ CAIObjectType m_lHeard;
    /* 0306 */ CAIObjectType field_306;
    /* 0342 */ CAIObjectType field_342;
    /* 037E */ CAIObjectType field_37E;
    /* 03BA */ CAIObjectType field_3BA;
    /* 03F6 */ CAIScript* m_overrideScript;
    /* 03FA */ CAIScript* m_special1Script;
    /* 03FE */ CAIScript* m_teamScript;
    /* 0402 */ CAIScript* m_special2Script;
    /* 0406 */ CAIScript* m_combatScript;
    /* 040A */ CAIScript* m_special3Script;
    /* 040E */ CAIScript* m_movementScript;
    /* 0412 */ CTypedPtrList<CPtrList, CAIAction*> m_queuedActions;
    /* 042E */ CTypedPtrList<CPtrList, CAITrigger*> m_pendingTriggers;
    /* 044A */ int field_44A;
    /* 044E */ CTypedPtrList<CPtrList, CGameTimer*> m_timers;
    /* 046A */ SHORT m_curResponseNum;
    /* 046C */ SHORT m_curResponseSetNum;
    /* 046E */ SHORT m_curScriptNum;
    /* 0470 */ BOOL m_interrupt;
    /* 0474 */ SHORT m_actionCount;
    /* 0476 */ CAIAction m_curAction;
    /* 054C */ int field_54C;
    /* 0550 */ short field_550;
    /* 0552 */ short field_552;
    /* 0554 */ SCRIPTNAME m_scriptName;
    /* 0574 */ BOOL m_inCutScene;
    /* 0578 */ BOOL m_firstCall;
    /* 057C */ BOOL m_forceActionPick;
    /* 0580 */ int field_580;
    /* 0584 */ LONG m_randValue;
    /* 0588 */ int field_588;
    /* 058C */ int field_58C;
    /* 0590 */ BYTE m_reactionRoll;
    /* 0592 */ SHORT m_nLastActionReturn;
    /* 0594 */ unsigned char field_594;
    /* 0595 */ unsigned char field_595;
    /* 0596 */ unsigned char field_596;
};

class CGameAIArea : public CGameAIBase {
public:
    CGameAIArea();
    /* 0000 */ ~CGameAIArea() override;
    /* 0028 */ BOOLEAN CanSaveGame(STRREF& strError) override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
};

class CGameAIGame : public CGameAIBase {
public:
    CGameAIGame();
    /* 0000 */ ~CGameAIGame() override;
    /* 0028 */ BOOLEAN CanSaveGame(STRREF& strError) override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
};

#endif /* CGAMEAIBASE_H_ */

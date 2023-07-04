#ifndef CGAMEAIBASE_H_
#define CGAMEAIBASE_H_

#include "CAIAction.h"
#include "CAIObjectType.h"
#include "CGameObject.h"

class CAIScript;
class CAITrigger;

class CGameAIBase : public CGameObject {
public:
    static const SHORT ACTION_DONE;
    static const SHORT ACTION_INTERRUPTABLE;
    static const SHORT ACTION_NORMAL;
    static const SHORT ACTION_ERROR;
    static const SHORT ACTION_NO_ACTION;
    static const SHORT ACTION_STOPPED;

    CGameAIBase();
    /* 0000 */ ~CGameAIBase() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0088 */ virtual void InsertAction(const CAIAction& action);
    /* 0090 */ virtual void SetCurrAction(const CAIAction& action);
    /* 0094 */ virtual void SetScript(SHORT level, CAIScript* script);
    /* 009C */ virtual const BYTE* GetVisibleTerrainTable();
    /* 00A0 */ virtual const BYTE* GetTerrainTable();
    /* 00AC */ virtual void ApplyTriggers();

    void CheckTimers(LONG cycles);
    void ClearTriggers();
    SHORT StartMusic();

    /* 006E */ CAIObjectType field_6E;
    /* 00AE */ CAIObjectType field_AE;
    /* 00EA */ CAIObjectType field_EA;
    /* 0126 */ CAIObjectType field_126;
    /* 0162 */ CAIObjectType field_162;
    /* 019E */ CAIObjectType field_19E;
    /* 01DA */ CAIObjectType field_1DA;
    /* 0216 */ CAIObjectType field_216;
    /* 0252 */ CAIObjectType field_252;
    /* 028E */ CAIObjectType field_28E;
    /* 02CA */ CAIObjectType field_2CA;
    /* 0306 */ CAIObjectType field_306;
    /* 0342 */ CAIObjectType field_342;
    /* 037E */ CAIObjectType field_37E;
    /* 03BA */ CAIObjectType field_3BA;
    /* 03F6 */ CAIScript* field_3F6;
    /* 03FA */ CAIScript* field_3FA;
    /* 03FE */ CAIScript* field_3FE;
    /* 0402 */ CAIScript* field_402;
    /* 0406 */ CAIScript* field_406;
    /* 040A */ CAIScript* field_40A;
    /* 040E */ CAIScript* field_40E;
    /* 0412 */ CTypedPtrList<CPtrList, CAIAction*> m_queuedActions;
    /* 042E */ CTypedPtrList<CPtrList, CAITrigger*> m_pendingTriggers;
    /* 044E */ CPtrList field_44E;
    /* 0470 */ BOOL m_interrupt;
    /* 0474 */ SHORT m_actionCount;
    /* 0476 */ CAIAction m_curAction;
};

#endif /* CGAMEAIBASE_H_ */

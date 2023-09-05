#include "CAICondition.h"

#include "CAITrigger.h"
#include "CAIUtil.h"
#include "CGameAIBase.h"

// NOTE: Inlined.
CAICondition::CAICondition()
{
}

// 0x403F10
CAICondition::~CAICondition()
{
    POSITION pos = m_triggerList.GetHeadPosition();
    while (pos != NULL) {
        CAITrigger* trigger = m_triggerList.GetNext(pos);
        if (trigger != NULL) {
            delete trigger;
        }
    }

    m_triggerList.RemoveAll();
}

// 0x403FB0
void CAICondition::Set(const CAICondition& condition)
{
    POSITION pos = condition.m_triggerList.GetHeadPosition();
    while (pos != NULL) {
        CAITrigger* trigger = condition.m_triggerList.GetNext(pos);
        m_triggerList.AddTail(new CAITrigger(*trigger));
    }
}

// 0x404090
void CAICondition::Add(const CAITrigger& trigger)
{
    m_triggerList.AddTail(new CAITrigger(trigger));
}

// 0x404150
BOOLEAN CAICondition::Hold(CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller)
{
    LONG nOrCounter = 0;
    BOOLEAN bFound = FALSE;

    POSITION pos = m_triggerList.GetHeadPosition();
    if (pos == NULL) {
        return TRUE;
    }

    while (pos != NULL) {
        if (nOrCounter <= 0) {
            bFound = FALSE;
        }

        CAITrigger* node = m_triggerList.GetNext(pos);
        if (node->m_triggerID == CAITRIGGER_OR) {
            nOrCounter = node->m_specificID;
        } else {
            nOrCounter--;
        }

        bFound |= TriggerHolds(node, triggerList, caller);
        if (bFound) {
            while (nOrCounter > 0 && pos != NULL) {
                m_triggerList.GetNext(pos);
                nOrCounter--;
            }
        } else {
            if (nOrCounter <= 0) {
                break;
            }
        }
    }

    return bFound;
}

// 0x4041D0
BOOL CAICondition::TriggerHolds(CAITrigger* pTrigger, CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller)
{
    SHORT triggerID = pTrigger->m_triggerID;

    if ((CAITrigger::STATUSTRIGGER & triggerID) != 0) {
        BOOL triggerHolds = caller->EvaluateStatusTrigger(*pTrigger);
        if ((pTrigger->m_flags & 0x1) != 0) {
            triggerHolds = !triggerHolds;
        }
        return triggerHolds;
    }

    POSITION pos = triggerList.GetHeadPosition();
    while (pos != NULL) {
        pTrigger->m_triggerCause.Decode(caller);

        CAITrigger* node = triggerList.GetNext(pos);
        BOOL triggerHolds = node->OfType(*pTrigger);
        if ((pTrigger->m_flags & 0x1) != 0) {
            triggerHolds = !triggerHolds;
        }

        if (triggerHolds) {
            if (triggerID == CAITRIGGER_ATTACKEDBY
                || triggerID == CAITRIGGER_HELP
                || triggerID == CAITRIGGER_HELPEX) {
                caller->field_342.Set(node->m_triggerCause);
            }

            return TRUE;
        }
    }

    return FALSE;
}

// 0x404290
void CAICondition::Read(CString sData)
{
    CString sTriggerData;

    sTriggerData = CAIUtil::ReadBetween(sData, CString("TR\n"));

    while (sTriggerData.GetLength() > 0) {
        CAITrigger* pTrigger = new CAITrigger(CAITrigger::NO_TRIGGER, 0);
        pTrigger->Read(sData);
        m_triggerList.AddTail(pTrigger);

        sTriggerData = CAIUtil::ReadBetween(sData, CString("TR\n"));
    }
}

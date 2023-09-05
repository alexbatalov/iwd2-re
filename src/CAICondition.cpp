#include "CAICondition.h"

#include "CAIUtil.h"

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
BOOL CAICondition::Hold(CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller)
{
    // TODO: Incomplete.

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

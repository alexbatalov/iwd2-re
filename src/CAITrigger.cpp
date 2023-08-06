#include "CAITrigger.h"

// 0x847D98
const SHORT CAITrigger::NO_TRIGGER = 0;

// 0x847E04
const SHORT CAITrigger::ONCREATION = 54;

// NOTE: Inlined.
CAITrigger::CAITrigger(const CAITrigger& trigger)
{
    m_triggerID = trigger.m_triggerID;
    m_specificID = trigger.m_specificID;
    m_triggerCause.Set(trigger.m_triggerCause);
    m_flags = trigger.m_flags;
    m_specific2 = trigger.m_specific2;
    m_specific3 = trigger.m_specific3;
    m_string1 = trigger.m_string1;
    m_string2 = trigger.m_string2;
}

// 0x420D10
CAITrigger::CAITrigger(SHORT triggerID, const CAIObjectType& cause, LONG specificID)
{
    m_flags = 0;
    m_specific2 = 0;
    m_specific3 = 0;
    m_string1 = "";
    m_string2 = "";
    m_triggerID = triggerID;
    m_triggerCause.Set(cause);
    m_specificID = specificID;
}

// 0x420DC0
CAITrigger::CAITrigger(SHORT triggerID, LONG specificID)
{
    m_flags = 0;
    m_specific2 = 0;
    m_specific3 = 0;
    m_string1 = "";
    m_string2 = "";
    m_triggerID = triggerID;
    m_specificID = specificID;
}

// 0x4043E0
CAITrigger::~CAITrigger()
{
}

// 0x420E60
BOOL CAITrigger::OfType(const CAITrigger& trigger) const
{
    return m_triggerID == trigger.m_triggerID
        && (m_specificID == trigger.m_specificID || trigger.m_specificID == 0)
        && m_triggerCause.OfType(trigger.m_triggerCause, FALSE, FALSE);
}

// 0x420EA0
void CAITrigger::Read(const CString& sData)
{
    // TODO: Incomplete.
}

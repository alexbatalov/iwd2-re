#include "CAITrigger.h"

#include "CAIUtil.h"

// 0x847D98
const SHORT CAITrigger::NO_TRIGGER = 0;

// 0x847DA4
const SHORT CAITrigger::RECEIVEDORDER = 6;

// 0x847DDC
const SHORT CAITrigger::TIMEREXPIRED = CAITRIGGER_TIMEREXPIRED;

// 0x847DDC
const SHORT CAITrigger::TRIGGER = CAITRIGGER_TRIGGER;

// 0x847DF6
const SHORT CAITrigger::HEARD = CAITRIGGER_HEARD;

// 0x847E04
const SHORT CAITrigger::ONCREATION = 54;

// 0x847E3C
const SHORT CAITrigger::OPENED = CAITRIGGER_OPENED;

// 0x847E46
const SHORT CAITrigger::UNLOCKED = 87;

// 0x847F48
const SHORT CAITrigger::STATUSTRIGGER = 0x4000;

// 0x4816B0
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
    CString sMutableData(sData);

    CString v1 = CAIUtil::ReadTo(sMutableData, CString("OB\n"), FALSE);

    sscanf(v1,
        "%d %ld %ld %ld %ld ",
        &m_triggerID,
        &m_specificID,
        &m_flags,
        &m_specific2,
        &m_specific3);

    m_string1 = CAIUtil::ReadBetween(sMutableData, CString('"'));
    m_string2 = CAIUtil::ReadBetween(sMutableData, CString('"'));

    CString v2 = CAIUtil::ReadBetween(sMutableData, CString("OB\n"));
    m_triggerCause.Read(v2);
}

// 0x466480
CAITrigger& CAITrigger::operator=(const CAITrigger& other)
{
    m_triggerID = other.m_triggerID;
    m_specificID = other.m_specificID;
    m_triggerCause.Set(other.m_triggerCause);
    m_flags = other.m_flags;
    m_specific2 = other.m_specific2;
    m_specific3 = other.m_specific3;
    m_string1 = other.m_string1;
    m_string2 = other.m_string2;
    return *this;
}

// 0x41E1E0
const CAIObjectType& CAITrigger::GetCause() const
{
    return m_triggerCause;
}

// 0x41E1F0
LONG CAITrigger::GetSpecifics() const
{
    return m_specificID;
}

// 0x45B490
void CAITrigger::Decode(CGameAIBase* caller)
{
    m_triggerCause.Decode(caller);
}

// 0x45B4A0
void CAITrigger::SetSpecifics(LONG specific)
{
    m_specificID = specific;
}

// 0x45B4B0
LONG CAITrigger::GetInt1() const
{
    return m_specific2;
}

// 0x45B4C0
void CAITrigger::SetInt1(LONG value)
{
    m_specific2 = value;
}

// 0x45B4D0
LONG CAITrigger::GetInt2() const
{
    return m_specific3;
}

// NOTE: Inlined.
void CAITrigger::SetInt2(LONG value)
{
    m_specific3 = value;
}

// 0x45B4E0
const CString& CAITrigger::GetString1() const
{
    return m_string1;
}

// 0x45B4F0
const CString& CAITrigger::GetString2() const
{
    return m_string2;
}

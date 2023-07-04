#include "CAIAction.h"

#include "CGameAIBase.h"

// 0x847784
const SHORT CAIAction::NO_ACTION = 0;

// 0x8477C0
const SHORT CAIAction::SPELL = 31;

// 0x847832
const SHORT CAIAction::SPELLPOINT = 95;

// 0x847856
const SHORT CAIAction::FORCESPELL = 113;

// 0x847858
const SHORT CAIAction::FORCESPELLPOINT = 114;

// 0x8478B4
const SHORT CAIAction::APPLYSPELL = 160;

// 0x8478DE
const SHORT CAIAction::REALLYFORCESPELL = 181;

// 0x8478F2
const SHORT CAIAction::SPELLNODEC = 191;

// 0x8478F4
const SHORT CAIAction::SPELLPOINTNODEC = 192;

// 0x8C6118
const CAIAction CAIAction::NULL_ACTION;

// 0x403A40
CAIAction::CAIAction()
{
    m_actionID = NO_ACTION;
    m_specificID = 0;
    m_specificID2 = 0;
    m_specificID3 = 0;
    m_string1 = "";
    m_string2 = "";
    m_internalFlags = 0;
}

// NOTE: Inlined.
CAIAction::CAIAction(const CAIAction& action)
{
    m_actionID = action.m_actionID;
    m_actorID.Set(action.m_actorID);
    m_acteeID.Set(action.m_acteeID);
    m_acteeID2.Set(action.m_acteeID2);
    m_specificID = action.m_specificID;
    m_specificID2 = action.m_specificID2;
    m_specificID3 = action.m_specificID2;
    m_string1 = action.m_string1;
    m_string2 = action.m_string2;
    m_dest = action.m_dest;
    m_internalFlags = action.m_internalFlags;
}

// 0x403B40
CAIAction::~CAIAction()
{
}

// 0x403BC0
BOOL CAIAction::OfType(SHORT type) const
{
    return m_actionID == type;
}

// 0x403BD0
void CAIAction::Read(CString sData)
{
    // TODO: Incomplete.
}

// 0x403E60
void CAIAction::Decode(CGameAIBase* caller)
{
    m_actorID.Decode(caller);
    m_acteeID.Decode(caller);
    m_acteeID2.Decode(caller);
}

// 0x452B80
SHORT CAIAction::GetActionID() const
{
    return m_actionID;
}

// 0x452B90
CString CAIAction::GetString2() const
{
    return m_string2;
}

// 0x452BC0
DWORD CAIAction::GetFlags() const
{
    return m_internalFlags;
}

// 0x41E170
const CAIObjectType& CAIAction::GetActee2() const
{
    return m_acteeID2;
}

// 0x41E180
LONG CAIAction::GetSpecifics() const
{
    return m_specificID;
}

// 0x41E190
LONG CAIAction::GetSpecifics2() const
{
    return m_specificID2;
}

// 0x41E1A0
LONG CAIAction::GetSpecifics3() const
{
    return m_specificID3;
}

// 0x41E1B0
CString CAIAction::GetString1() const
{
    return m_string1;
}

#include "CAIAction.h"

#include "CGameAIBase.h"

// 0x847784
const SHORT CAIAction::NO_ACTION = 0;

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

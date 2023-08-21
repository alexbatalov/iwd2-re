#include "CAIScript.h"

#include "CAIConditionResponse.h"

// NOTE: Inlined in `CAIScriptFile::CAIScriptFile`.
CAIScript::CAIScript()
{
    field_8 = 0;
}

// 0x45FE00
CAIScript::CAIScript(CResRef cNewResRef)
{
    m_cResRef = cNewResRef;
    Read(cNewResRef, FALSE);
}

// 0x40EFC0
CAIScript::~CAIScript()
{
    POSITION pos = m_caList.GetHeadPosition();
    while (pos != NULL) {
        CAIConditionResponse* pConditionResponse = m_caList.GetNext(pos);
        if (pConditionResponse != NULL) {
            delete pConditionResponse;
        }
    }

    m_caList.RemoveAll();
}

// 0x40F050
void CAIScript::Add(const CAICondition& condition, const CAIResponseSet& responseSet)
{
    m_caList.AddTail(new CAIConditionResponse(condition, responseSet));
}

// 0x40F160
void CAIScript::Read(CResRef cNewResRef, BOOL a2)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
BOOL CAIScript::IsEmpty()
{
    return m_caList.IsEmpty();
}

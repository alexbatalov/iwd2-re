#include "CAIScript.h"

#include "CAIConditionResponse.h"

// NOTE: Inlined in `CAIScriptFile::CAIScriptFile`.
CAIScript::CAIScript()
{
    field_8 = 0;
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

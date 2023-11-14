#include "CAIResponse.h"

#include "CAIUtil.h"

// 0x40DAB0
CAIResponse::CAIResponse()
{
    m_weight = -1;
    m_responseNum = -1;
    m_responseSetNum = -1;
    m_scriptNum = -1;
}

// 0x40DAE0
CAIResponse::~CAIResponse()
{
    POSITION pos = m_actionList.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* action = m_actionList.GetNext(pos);
        if (action != NULL) {
            delete action;
        }
    }

    m_actionList.RemoveAll();
}

// 0x40DBA0
void CAIResponse::Set(const CAIResponse& response)
{
    POSITION pos = m_actionList.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* action = m_actionList.GetNext(pos);
        if (action != NULL) {
            delete action;
        }
    }

    m_actionList.RemoveAll();

    m_weight = response.m_weight;

    pos = response.m_actionList.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* action = response.m_actionList.GetNext(pos);
        m_actionList.AddTail(new CAIAction(*action));
    }
}

// 0x40DD90
void CAIResponse::Add(const CAIAction& action)
{
    m_actionList.AddTail(new CAIAction(action));
}

// 0x40DED0
void CAIResponse::Add(const CAIResponse& response)
{
    POSITION pos = response.m_actionList.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* action = response.m_actionList.GetNext(pos);
        m_actionList.AddTail(new CAIAction(*action));
    }

    if (m_weight == -1) {
        m_weight = response.m_weight;
    }

    if (m_responseNum == -1) {
        m_responseNum = response.m_responseNum;
    }

    if (m_responseSetNum == -1) {
        m_responseSetNum = response.m_responseSetNum;
    }

    if (m_scriptNum == -1) {
        m_scriptNum = response.m_scriptNum;
    }
}

// 0x40E080
BOOL CAIResponse::InList(SHORT actionID)
{
    POSITION pos = m_actionList.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* action = m_actionList.GetNext(pos);
        if (action->OfType(actionID)) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x40E0C0
BOOL CAIResponse::InListEnd(SHORT actionID)
{
    POSITION pos = m_actionList.GetTailPosition();
    while (pos != NULL) {
        CAIAction* action = m_actionList.GetPrev(pos);
        if (action->OfType(actionID)) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x40E100
void CAIResponse::Read(CString sData)
{
    CAIAction temp;
    CString v1;
    CString v2;

    v1 = CAIUtil::ReadTo(sData, CString("AC\n"), FALSE);

    v2 = CAIUtil::ReadBetween(sData, CString("AC\n"));
    while (v2.GetLength() > 0) {
        temp.Read(v2);

        CAIAction* action = new CAIAction(temp);
        m_actionList.AddTail(action);

        temp = CAIAction::NULL_ACTION;

        v2 = CAIUtil::ReadBetween(sData, CString("AC\n"));
    }
}

// 0x40FA30
CAIResponseSet::CAIResponseSet()
{
}

// 0x40E4B0
CAIResponseSet::~CAIResponseSet()
{
    POSITION pos = m_responseList.GetHeadPosition();
    while (pos != NULL) {
        CAIResponse* response = m_responseList.GetNext(pos);
        if (response != NULL) {
            delete response;
        }
    }

    m_responseList.RemoveAll();
}

// 0x40E5D0
void CAIResponseSet::Add(const CAIResponse& response)
{
    // NOTE: Code below uses `Set` implying there is no copy constructor.
    CAIResponse* copy = new CAIResponse();
    copy->Set(response);
    m_weightTotal += copy->m_weight;
    m_responseList.AddTail(copy);
}

// 0x40E670
CAIResponse* CAIResponseSet::Choose()
{
    LONG trigger = m_weightTotal != 0 ? rand() % m_weightTotal : 0;
    LONG accum = 0;
    SHORT responseNum = 0;

    POSITION pos = m_responseList.GetHeadPosition();
    while (pos != NULL) {
        CAIResponse* response = m_responseList.GetNext(pos);
        accum += response->m_weight;
        responseNum++;

        if (trigger <= accum) {
            response->m_responseNum = responseNum;
            return response;
        }
    }

    return NULL;
}

// 0x40E6C0
void CAIResponseSet::Set(const CAIResponseSet& responseSet)
{
    m_weightTotal = responseSet.m_weightTotal;

    POSITION pos = responseSet.m_responseList.GetHeadPosition();
    while (pos != NULL) {
        CAIResponse* response = responseSet.m_responseList.GetNext(pos);
        CAIResponse* copy = new CAIResponse();
        copy->Set(*response);
        m_responseList.AddTail(copy);
    }
}

// 0x40E770
void CAIResponseSet::Read(CString sData)
{
    CString v1;
    CString v2;

    v2 = CAIUtil::ReadBetween(sData, CString("RE\n"));
    while (v2.GetLength() > 0) {
        CAIResponse* response = new CAIResponse();
        response->Read(v2);

        Add(*response);

        delete response;

        v2 = CAIUtil::ReadBetween(sData, CString("RE\n"));
    }
}

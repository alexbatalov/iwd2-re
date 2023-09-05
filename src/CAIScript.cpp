#include "CAIScript.h"

#include "CAIAction.h"
#include "CAIConditionResponse.h"
#include "CAITrigger.h"
#include "CAIUtil.h"
#include "CBaldurChitin.h"
#include "CGameAIBase.h"
#include "CInfGame.h"

// NOTE: Inlined.
CAIPlayerScript::CAIPlayerScript()
{
}

// NOTE: Inlined.
CAIPlayerScript::~CAIPlayerScript()
{
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CAINonPlayerScript::CAINonPlayerScript()
{
}

// NOTE: Inlined.
CAINonPlayerScript::~CAINonPlayerScript()
{
}

// -----------------------------------------------------------------------------

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

// 0x40EBA0
CAIResponse* CAIScript::Find(CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller)
{
    SHORT responseSetNum = 0;
    CAIResponse* response = new CAIResponse();

    POSITION pos = m_caList.GetHeadPosition();
    while (pos != NULL) {
        responseSetNum++;
        CAIConditionResponse* pConditionResponse = m_caList.GetNext(pos);
        if (pConditionResponse->m_condition.Hold(triggerList, caller)) {
            // NOTE: Unused.
            CAIResponseSet resSet;

            CAIResponse* chooseResponse = pConditionResponse->m_responseSet.Choose();
            response->Add(*chooseResponse);
            response->m_responseNum = chooseResponse->m_responseNum;
            response->m_responseSetNum = responseSetNum;

            if (!response->InListEnd(CAIAction::CONTINUE)) {
                return response;
            }

            // NOTE: Probably inlining.
            if (response != NULL) {
                POSITION pos = response->m_actionList.GetHeadPosition();
                while (pos != NULL) {
                    CAIAction oldAction;
                    oldAction = caller->m_curAction;

                    POSITION currPos = pos;
                    CAIAction* action = response->m_actionList.GetNext(pos);

                    if (g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_lSCRINST.Find(action->m_actionID) != NULL) {
                        caller->SetCurrAction(*action);
                        caller->ExecuteAction();

                        response->m_actionList.RemoveAt(currPos);
                        delete action;
                    }

                    caller->SetCurrAction(oldAction);
                }
            }
        }
    }

    return response;
}

// 0x40F050
void CAIScript::Add(const CAICondition& condition, const CAIResponseSet& responseSet)
{
    m_caList.AddTail(new CAIConditionResponse(condition, responseSet));
}

// FIXME: `cNewResRef` should be reference.
//
// 0x40F160
void CAIScript::Read(CResRef cNewResRef, BOOL playerScript)
{
    // 0x8C8004
    static DWORD counter;

    POSITION pos = m_caList.GetHeadPosition();
    while (pos != NULL) {
        CAIConditionResponse* node = m_caList.GetNext(pos);
        if (node != NULL) {
            delete node;
        }
    }
    m_caList.RemoveAll();

    // NOTE: Unused.
    CFile file;

    m_cResRef = cNewResRef;

    CString sText;

    if (playerScript) {
        // NOTE: Lots of inlined stuff from this point.
        CAIPlayerScript cPScript;
        cPScript.SetResRef(cNewResRef, TRUE, TRUE);

        if (cPScript.GetRes() == NULL) {
            return;
        }

        cPScript.GetRes()->Demand();
        sText = cPScript.GetRes()->GetText();
        cPScript.GetRes()->Release();
    } else {
        // NOTE: Lots of inlined stuff from this point.
        CAINonPlayerScript cNPScript;
        cNPScript.SetResRef(cNewResRef, TRUE, TRUE);

        if (cNPScript.GetRes() != NULL) {
            cNPScript.GetRes()->Demand();
            sText = cNPScript.GetRes()->GetText();
            cNPScript.GetRes()->Release();
        } else {
            CAIPlayerScript cPScript;
            cPScript.SetResRef(cNewResRef, TRUE, TRUE);

            if (cPScript.GetRes() == NULL) {
                return;
            }

            cPScript.GetRes()->Demand();
            sText = cPScript.GetRes()->GetText();
            cPScript.GetRes()->Release();
        }
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    BOOL bInLoad = pGame->m_bInLoadGame == TRUE || pGame->m_bInLoadArea == TRUE;

    CString v1 = CAIUtil::ReadBetween(sText, CString("SC\n"));
    CString v2 = CAIUtil::ReadBetween(v1, CString("CR\n"));

    while (v2.GetLength() > 0) {
        if (bInLoad == TRUE) {
            if ((counter & 31) == 31) {
                SleepEx(25, FALSE);
            }
            counter++;
        }

        CAIConditionResponse* pConditionResponse = new CAIConditionResponse();
        pConditionResponse->Read(v2);

        // NOTE: Uninline.
        Add(pConditionResponse->m_condition, pConditionResponse->m_responseSet);

        delete pConditionResponse;

        v2 = CAIUtil::ReadBetween(v1, CString("CR\n"));
    }
}

// NOTE: Inlined.
BOOL CAIScript::IsEmpty()
{
    return m_caList.IsEmpty();
}

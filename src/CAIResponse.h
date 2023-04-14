#ifndef CAIRESPONSE_H_
#define CAIRESPONSE_H_

#include "mfc.h"

#include "CAIAction.h"

class CAIResponse {
public:
    CAIResponse();
    ~CAIResponse();
    void Set(const CAIResponse& response);
    void Add(const CAIAction& action);
    void Add(const CAIResponse& response);
    BOOL InList(SHORT actionID);
    BOOL InListEnd(SHORT actionID);
    void Read(CString sData);

    SHORT m_weight;
    SHORT m_responseNum;
    SHORT m_responseSetNum;
    SHORT m_scriptNum;
    CTypedPtrList<CPtrList, CAIAction*> m_actionList;
};

class CAIResponseSet {
public:
    CAIResponseSet();
    ~CAIResponseSet();
    void Add(const CAIResponse& response);
    CAIResponse* Choose();
    void Set(const CAIResponseSet& responseSet);
    void Read(CString sData);

    CTypedPtrList<CPtrList, CAIResponse*> m_responseList;
    LONG m_weightTotal;
};

#endif /* CAIRESPONSE_H_ */

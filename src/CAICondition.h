#ifndef CAICONDITION_H_
#define CAICONDITION_H_

#include "mfc.h"

class CAITrigger;
class CGameAIBase;

class CAICondition {
public:
    CAICondition();
    ~CAICondition();
    void Set(const CAICondition& condition);
    void Add(const CAITrigger& trigger);
    BOOLEAN Hold(CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller);
    BOOL TriggerHolds(CAITrigger* pTrigger, CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller);
    void Read(CString sData);

    CTypedPtrList<CPtrList, CAITrigger*> m_triggerList;
};

#endif /* CAICONDITION_H_ */

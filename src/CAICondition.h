#ifndef CAICONDITION_H_
#define CAICONDITION_H_

#include "mfc.h"

#include "CAITrigger.h"

class CAICondition {
public:
    CAICondition();
    ~CAICondition();
    void Set(const CAICondition& condition);
    void Add(const CAITrigger& trigger);
    void Read(CString sData);

    CTypedPtrList<CPtrList, CAITrigger*> m_triggerList;
};

#endif /* CAICONDITION_H_ */

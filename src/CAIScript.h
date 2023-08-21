#ifndef CAISCRIPT_H_
#define CAISCRIPT_H_

#include "mfc.h"

#include "CResRef.h"

class CAICondition;
class CAIConditionResponse;
class CAIResponseSet;

class CAIScript {
public:
    CAIScript();
    CAIScript(CResRef cNewResRef);
    ~CAIScript();

    void Add(const CAICondition& condition, const CAIResponseSet& responseSet);
    void Read(CResRef cNewResRef, BOOL a2);

    BOOL IsEmpty();

    /* 0000 */ CResRef m_cResRef;
    /* 0008 */ int field_8;
    /* 000C */ CTypedPtrList<CPtrList, CAIConditionResponse*> m_caList;
};

#endif /* CAISCRIPT_H_ */

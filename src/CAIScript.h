#ifndef CAISCRIPT_H_
#define CAISCRIPT_H_

#include "mfc.h"

#include "CResRef.h"
#include "CResText.h"

class CAICondition;
class CAIConditionResponse;
class CAIResponse;
class CAIResponseSet;
class CAITrigger;
class CGameAIBase;

class CAIPlayerScript : public CResHelper<CResText, 1017> {
public:
    CAIPlayerScript();
    ~CAIPlayerScript();
};

class CAINonPlayerScript : public CResHelper<CResText, 1007> {
public:
    CAINonPlayerScript();
    ~CAINonPlayerScript();
};

class CAIScript {
public:
    CAIScript();
    CAIScript(CResRef cNewResRef);
    ~CAIScript();

    CAIResponse* Find(CTypedPtrList<CPtrList, CAITrigger*>& triggerList, CGameAIBase* caller);
    void Add(const CAICondition& condition, const CAIResponseSet& responseSet);
    void Read(CResRef cNewResRef, BOOL playerScript);

    BOOL IsEmpty();

    /* 0000 */ CResRef m_cResRef;
    /* 0008 */ int field_8;
    /* 000C */ CTypedPtrList<CPtrList, CAIConditionResponse*> m_caList;
};

#endif /* CAISCRIPT_H_ */

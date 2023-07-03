#ifndef CAITRIGGER_H_
#define CAITRIGGER_H_

#include "CAIObjectType.h"

class CAITrigger {
public:
    static const SHORT NO_TRIGGER;

    CAITrigger(const CAITrigger& trigger);
    CAITrigger(SHORT triggerID, const CAIObjectType& cause, LONG specificID);
    CAITrigger(SHORT triggerID, LONG specificID);
    ~CAITrigger();
    BOOL OfType(const CAITrigger& trigger) const;
    void Read(const CString& sData);

    SHORT m_triggerID;
    LONG m_specificID;
    CAIObjectType m_triggerCause;
    LONG m_flags;
    LONG m_specific2;
    LONG m_specific3;
    CString m_string1;
    CString m_string2;
};

#endif /* CAITRIGGER_H_ */

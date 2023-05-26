#ifndef CAIACTION_H_
#define CAIACTION_H_

#include "mfc.h"

#include "CAIObjectType.h"

class CGameAIBase;

class CAIAction {
public:
    static const SHORT NO_ACTION;

    static const CAIAction NULL_ACTION;

    CAIAction();
    CAIAction(const CAIAction& action);
    ~CAIAction();
    BOOL OfType(SHORT type) const;
    void Read(CString sData);
    void Decode(CGameAIBase* caller);

    SHORT GetActionID() const;
    CString GetString2() const;
    DWORD GetFlags() const;

    SHORT m_actionID;
    CAIObjectType m_actorID;
    CAIObjectType m_acteeID;
    CAIObjectType m_acteeID2;
    LONG m_specificID;
    LONG m_specificID2;
    LONG m_specificID3;
    CString m_string1;
    CString m_string2;
    CPoint m_dest;
    DWORD m_internalFlags;
};

#endif /* CAIACTION_H_ */

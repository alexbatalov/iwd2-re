#ifndef CAIACTION_H_
#define CAIACTION_H_

#include "mfc.h"

#include "CAIObjectType.h"

#define CAIACTION_MOVEVIEWPOINTUNTILDONE 264

class CGameAIBase;

class CAIAction {
public:
    static const SHORT NO_ACTION;
    static const SHORT ATTACK;
    static const SHORT SPELL;
    static const SHORT CONTINUE;
    static const SHORT LEADER;
    static const SHORT GROUPATTACK;
    static const SHORT SPELLPOINT;
    static const SHORT FORCESPELL;
    static const SHORT FORCESPELLPOINT;
    static const SHORT APPLYSPELL;
    static const SHORT REALLYFORCESPELL;
    static const SHORT SPELLNODEC;
    static const SHORT SPELLPOINTNODEC;
    static const SHORT GIVEPARTYGOLD;

    static const CAIAction NULL_ACTION;

    CAIAction();
    CAIAction(SHORT actionID, const CAIObjectType& actee, LONG specificID, LONG specificID2, LONG specificID3);
    CAIAction(SHORT actionID, const CPoint& dest, LONG specificID, LONG specificID2);
    CAIAction(const CAIAction& action);
    ~CAIAction();
    BOOL OfType(SHORT type) const;
    void Read(CString sData);
    void Decode(CGameAIBase* caller);
    CAIAction& operator=(const CAIAction& other);

    const CPoint& GetDest() const;
    SHORT GetActionID() const;
    CString GetString2() const;
    DWORD GetFlags() const;
    const CAIObjectType& GetActee2() const;
    LONG GetSpecifics() const;
    LONG GetSpecifics2() const;
    LONG GetSpecifics3() const;
    CString GetString1() const;

    void SetString2(CString sText);
    void SetString1(CString sText);

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

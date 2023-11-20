#ifndef CVARIABLEHASH_H_
#define CVARIABLEHASH_H_

#include "FileFormat.h"

class CGameSprite;

class CVariable : public CAreaVariable {
public:
    CVariable();
    CVariable(const CVariable& other);
    CVariable& operator=(const CVariable& other);

    CString GetName();
    void SetName(CString sName);
    int GetIntValue();
};

class CVariableHashBase {
public:
    static int PRIME[];

    /* 0000 */ virtual BOOL AddKey(CVariable& var) = 0;
    /* 0004 */ virtual CVariable* FindKey(CString sVarName) = 0;
    /* 0008 */ virtual CVariable* FindKey(CString sVarName, LONG nValue) = 0;
    /* 000C */ virtual void Marshal(CVariable** pList, WORD* pCount) = 0;
    /* 0010 */ virtual void MarshalToCharacter(CGameSprite* pSprite) = 0;
    /* 0014 */ virtual void ClearAll() = 0;
    /* 0018 */ virtual void Resize(LONG nSize) = 0;
    /* 001C */ virtual BOOL RemoveKey(CString sVarName, BOOL a2, LONG nValue) = 0;

    int Hash(CString sName);

    /* 0004 */ LONG m_nTableEntries;
};

class CVariableHash : public CVariableHashBase {
public:
    CVariableHash(LONG nSize = 512);
    ~CVariableHash();

    /* 0000 */ BOOL AddKey(CVariable& var) override;
    /* 0004 */ CVariable* FindKey(CString sVarName) override;
    /* 0008 */ CVariable* FindKey(CString sVarName, LONG nValue) override;
    /* 000C */ void Marshal(CVariable** pList, WORD* pCount) override;
    /* 0010 */ void MarshalToCharacter(CGameSprite* pSprite) override;
    /* 0014 */ void ClearAll() override;
    /* 0018 */ void Resize(LONG nSize) override;
    /* 001C */ BOOL RemoveKey(CString sVarName, BOOL a2, LONG nValue) override;

    /* 0008 */ CVariable* m_hashEntries;
};

class CNamedCreatureVariableHashEntry {
public:
    CNamedCreatureVariableHashEntry();
    CNamedCreatureVariableHashEntry(const CVariable& var);

    void sub_550B30();
    CNamedCreatureVariableHashEntry* sub_550CF0();

    /* 0000 */ CVariable m_variable;
    /* 0054 */ CNamedCreatureVariableHashEntry* m_pNext;
};

class CNamedCreatureVariableHash : public CVariableHashBase {
public:
    CNamedCreatureVariableHash(LONG nSize = 512);
    ~CNamedCreatureVariableHash();

    /* 0000 */ BOOL AddKey(CVariable& var) override;
    /* 0004 */ CVariable* FindKey(CString sVarName) override;
    /* 0008 */ CVariable* FindKey(CString sVarName, LONG nValue) override;
    /* 000C */ void Marshal(CVariable** pList, WORD* pCount) override;
    /* 0010 */ void MarshalToCharacter(CGameSprite* pSprite) override;
    /* 0014 */ void ClearAll() override;
    /* 0018 */ void Resize(LONG nSize) override;
    /* 001C */ BOOL RemoveKey(CString sVarName, BOOL a2, LONG nValue) override;

    /* 0008 */ CNamedCreatureVariableHashEntry** m_hashEntries;
};

#endif /* CVARIABLEHASH_H_ */

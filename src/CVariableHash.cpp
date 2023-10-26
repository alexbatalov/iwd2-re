#include "CVariableHash.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"

// 0x84EC4C
int CVariableHashBase::PRIME[] = {
    0x02,
    0x03,
    0x05,
    0x07,
    0x0B,
    0x0D,
    0x11,
    0x13,
    0x17,
    0x1D,
    0x1F,
    0x25,
    0x29,
    0x2B,
    0x2F,
    0x35,
    0x3B,
    0x3D,
    0x43,
    0x47,
    0x49,
    0x4F,
    0x53,
    0x59,
    0x5B,
    0x5D,
    0x61,
    0x65,
    0x67,
    0x6B,
    0x71,
    0x7F,
    0x83,
    0x89,
};

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CVariable::CVariable()
{
}

// 0x5505A0
CVariable::CVariable(const CVariable& other)
{
    strncpy(m_name, other.m_name, 32);
    m_type = other.m_type;
    m_resRefType = other.m_resRefType;
    m_dwValue = other.m_dwValue;
    m_intValue = other.m_intValue;
    m_floatValue = other.m_floatValue;
    strncpy(m_stringValue, other.m_stringValue, 32);
}

// 0x4EDA30
CString CVariable::GetName()
{
    return CString(m_name);
}

// FIXME: Use reference.
//
// 0x452C60
void CVariable::SetName(CString sName)
{
    strncpy(m_name, sName, 32);
}

// NOTE: Inlined.
CVariable& CVariable::operator=(const CVariable& other)
{
    if (this != &other) {
        strncpy(m_name, other.m_name, 32);
        m_type = other.m_type;
        m_resRefType = other.m_resRefType;
        m_dwValue = other.m_dwValue;
        m_intValue = other.m_intValue;
        m_floatValue = other.m_floatValue;
        strncpy(m_stringValue, other.m_stringValue, 32);
    }
    return *this;
}

// -----------------------------------------------------------------------------

// FIXME: Use reference.
//
// 0x54FAD0
int CVariableHashBase::Hash(CString sName)
{
    int length = sName.GetLength();
    int v1 = 0;
    int v2 = 0;
    int v3 = 1;

    for (int index = 0; index < length && index < 32; index++) {
        int v4 = PRIME[index] * ((v2 + length) & 0x2F);
        v1 += v4;
        v3 *= v4 & (m_nTableEntries - 1);
    }

    return (m_nTableEntries - 1) & (v1 + v3);
}

// -----------------------------------------------------------------------------

// 0x54FB40
CVariableHash::CVariableHash(LONG nSize)
{
    m_hashEntries = new CVariable[nSize];
    m_nTableEntries = nSize;
}

// 0x54FC10
CVariableHash::~CVariableHash()
{
    delete m_hashEntries;
}

// 0x54FC30
BOOL CVariableHash::AddKey(CVariable& var)
{
    if (var.GetName().GetLength() == 0) {
        return FALSE;
    }

    CString sName = var.GetName();
    CString sTemp;

    for (int index = 0; index < sName.GetLength(); index++) {
        if (sName[index] != ' ') {
            sTemp += sName[index];
        }
    }

    sName = sTemp;
    sName = sName.SpanExcluding(" ");
    sName.MakeUpper();
    var.SetName(sName);

    int end = Hash(sName);
    int curr = end;

    BOOL v1 = g_pBaldurChitin->GetObjectGame()->field_1B84;
    BOOL bDone = FALSE;
    BOOL bResult = FALSE;
    while (!bDone) {
        if (v1 && curr == 255) {
            SleepEx(10, FALSE);
        }

        if (m_hashEntries[curr].m_name[0] == '\0'
            || memcmp(m_hashEntries[curr].m_name, var.m_name, 32) == 0) {
            bResult = TRUE;

            m_hashEntries[curr] = var;

            break;
        }

        curr++;
        if (curr >= m_nTableEntries) {
            curr = 0;
        }

        if (curr == end) {
            bDone = TRUE;
            Resize(2 * m_nTableEntries);
            AddKey(var);
        }
    }

    return bResult;
}

// FIXME: Use reference.
//
// 0x54FE90
CVariable* CVariableHash::FindKey(CString sVarName)
{
    CString sCopy(sVarName);
    CString sTemp;

    for (int index = 0; index < sCopy.GetLength(); index++) {
        if (sCopy[index] != ' ') {
            sTemp += sCopy[index];
        }
    }

    sCopy = sTemp;
    sCopy = sCopy.SpanExcluding(" ");
    sCopy.MakeUpper();

    int end = Hash(sCopy);
    int curr = end;

    BOOL bDone = FALSE;
    CVariable* var = NULL;
    while (!bDone) {
        // FIXME: Unnecessary copying.
        if (m_hashEntries[curr].GetName() == sCopy) {
            var = &(m_hashEntries[curr]);
            break;
        }

        // FIXME: Unnecessary copying.
        if (m_hashEntries[curr].GetName() == "") {
            break;
        }

        curr++;
        if (curr >= m_nTableEntries) {
            curr = 0;
        }

        if (curr == end) {
            bDone = TRUE;
        }
    }

    return var;
}

// FIXME: Use reference.
//
// 0x550070
CVariable* CVariableHash::FindKey(CString sVarName, LONG nValue)
{
    CString sCopy(sVarName);
    CString sTemp;

    for (int index = 0; index < sCopy.GetLength(); index++) {
        if (sCopy[index] != ' ') {
            sTemp += sCopy[index];
        }
    }

    sCopy = sTemp;
    sCopy = sCopy.SpanExcluding(" ");
    sCopy.MakeUpper();

    int end = Hash(sCopy);
    int curr = end;

    BOOL bDone = FALSE;
    CVariable* var = NULL;
    while (!bDone) {
        // FIXME: Unnecessary copying.
        if (m_hashEntries[curr].GetName() == sCopy
            && m_hashEntries[curr].m_intValue == nValue) {
            var = &(m_hashEntries[curr]);
            break;
        }

        // FIXME: Unnecessary copying.
        if (m_hashEntries[curr].GetName() == "") {
            break;
        }

        curr++;
        if (curr >= m_nTableEntries) {
            curr = 0;
        }

        if (curr == end) {
            bDone = TRUE;
        }
    }

    return var;
}

// 0x550280
void CVariableHash::ClearAll()
{
    for (int index = 0; index < m_nTableEntries; index++) {
        // FIXME: Unnecessary copying.
        if (m_hashEntries[index].GetName() != "") {
            CVariable dummy;
            m_hashEntries[index] = dummy;
        }
    }
}

// 0x5503A0
void CVariableHash::Marshal(CVariable** pList, WORD* pCount)
{
    CTypedPtrList<CPtrList, CVariable*> l;

    for (int index = 0; index < m_nTableEntries; index++) {
        // FIXME: Unnecessary copying.
        if (m_hashEntries[index].GetName() != "") {
            l.AddTail(new CVariable(m_hashEntries[index]));
        }
    }

    *pCount = static_cast<WORD>(l.GetCount());

    if (*pCount != 0) {
        *pList = new CVariable[*pCount];

        int index = 0;
        while (l.GetCount() != 0) {
            CVariable* pTemp = l.RemoveHead();
            (*pList)[index] = *pTemp;
            delete pTemp;
        }
    }
}

// 0x550600
void CVariableHash::MarshalToCharacter(CGameSprite* pSprite)
{
    // TODO: Incomplete.
}

// 0x550920
void CVariableHash::Resize(LONG nSize)
{
    CVariable* oldHashEntries = m_hashEntries;
    LONG oldTableEntries = m_nTableEntries;

    m_hashEntries = new CVariable[nSize];
    m_nTableEntries = nSize;

    for (int index = 0; index < oldTableEntries; index++) {
        if (oldHashEntries[index].GetName() != "") {
            AddKey(oldHashEntries[index]);
        }
    }

    delete oldHashEntries;
}

// 0x550270
int CVariableHash::RemoveKey(CString sVarName, BOOL a2, LONG nValue)
{
    return 0;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CNamedCreatureVariableHashEntry::CNamedCreatureVariableHashEntry()
{
    m_pNext = NULL;
}

// NOTE: Inlined.
CNamedCreatureVariableHashEntry::CNamedCreatureVariableHashEntry(const CVariable& var)
    : m_variable(var)
{
    m_pNext = NULL;
}

// 0x550B30
void CNamedCreatureVariableHashEntry::sub_550B30()
{
    if (m_pNext != NULL) {
        m_pNext->sub_550B30();

        delete m_pNext;
        m_pNext = NULL;
    }
}

// 0x550CF0
CNamedCreatureVariableHashEntry* CNamedCreatureVariableHashEntry::sub_550CF0()
{
    CNamedCreatureVariableHashEntry* var = this;

    while (var->m_pNext != NULL) {
        var = var->m_pNext;
    }

    return var;
}

// -----------------------------------------------------------------------------

// 0x550A20
CNamedCreatureVariableHash::CNamedCreatureVariableHash(LONG nSize)
{
    m_nTableEntries = nSize;
    m_hashEntries = new CNamedCreatureVariableHashEntry*[nSize];

    for (int index = 0; index < nSize; index++) {
        m_hashEntries[index] = NULL;
    }
}

// 0x550A90
CNamedCreatureVariableHash::~CNamedCreatureVariableHash()
{
    // NOTE: Uninline.
    ClearAll();

    delete m_hashEntries;
    m_hashEntries = NULL;
}

// 0x550B60
void CNamedCreatureVariableHash::ClearAll()
{
    if (m_hashEntries != NULL) {
        for (int index = 0; index < m_nTableEntries; index++) {
            if (m_hashEntries[index] != NULL) {
                // NOTE: Uninline.
                m_hashEntries[index]->sub_550B30();

                delete m_hashEntries[index];
                m_hashEntries[index] = NULL;
            }
        }
    }
}

// 0x550BC0
void CNamedCreatureVariableHash::Resize(LONG nSize)
{
    int index;

    if (nSize < m_nTableEntries && m_hashEntries) {
        for (index = nSize; index < m_nTableEntries; index++) {
            if (m_hashEntries[index] != NULL) {
                // NOTE: Uninline.
                m_hashEntries[index]->sub_550B30();

                delete m_hashEntries[index];
                m_hashEntries[index] = NULL;
            }
        }
    }

    CNamedCreatureVariableHashEntry** oldHashEntries = m_hashEntries;
    LONG oldTableEntries = m_nTableEntries;

    m_hashEntries = new CNamedCreatureVariableHashEntry*[nSize];

    for (index = 0; index < nSize; index++) {
        m_hashEntries[index] = NULL;
    }

    for (index = 0; index < oldTableEntries; index++) {
        if (oldHashEntries[index] != NULL) {
            CNamedCreatureVariableHashEntry* pCurr = oldHashEntries[index];
            while (pCurr != NULL) {
                CNamedCreatureVariableHashEntry* pNext = pCurr->m_pNext;
                pCurr->m_pNext = NULL;

                int hash = Hash(pCurr->m_variable.GetName());
                if (m_hashEntries[hash] != NULL) {
                    m_hashEntries[hash]->sub_550CF0()->m_pNext = pCurr;
                } else {
                    m_hashEntries[hash] = pCurr;
                }

                pCurr = pNext;
            }
        }
    }

    delete oldHashEntries;
}

// 0x550D10
BOOL CNamedCreatureVariableHash::AddKey(CVariable& var)
{
    CString sName = var.GetName();
    CString sTemp;

    for (int index = 0; index < sName.GetLength() && index < 32; index++) {
        if (sName[index] != ' ') {
            sTemp += static_cast<char>(toupper(sName[index]));
        }
    }

    if (sTemp == "") {
        return FALSE;
    }

    int hash = Hash(sName);

    if (m_hashEntries[hash] != NULL) {
        CNamedCreatureVariableHashEntry* pCurr = m_hashEntries[hash];
        while (pCurr != NULL) {
            // FIXME: Unnecessary copying.
            if (pCurr->m_variable.GetName() == sTemp) {
                pCurr->m_variable = var;
                return TRUE;
            }
            pCurr = pCurr->m_pNext;
        }
    }

    CNamedCreatureVariableHashEntry* pVar = new CNamedCreatureVariableHashEntry(var);
    if (m_hashEntries[hash] != NULL) {
        m_hashEntries[hash]->sub_550CF0()->m_pNext = pVar;
    } else {
        m_hashEntries[hash] = pVar;
    }

    // FIXME: Probably wrong.
    return FALSE;
}

// FIXME: Use reference.
//
// 0x550F70
CVariable* CNamedCreatureVariableHash::FindKey(CString sVarName)
{
    CString sTemp;

    for (int index = 0; index < sVarName.GetLength(); index++) {
        if (sVarName[index] != ' ') {
            sTemp += static_cast<char>(toupper(sVarName[index]));
        }
    }

    if (sTemp != "") {
        int hash = Hash(sTemp);

        CNamedCreatureVariableHashEntry* pEntry = m_hashEntries[hash];
        while (pEntry != NULL) {
            if (pEntry->m_variable.GetName() == sTemp) {
                return &(pEntry->m_variable);
            }
            pEntry = pEntry->m_pNext;
        }
    }

    return NULL;
}

// 0x551090
CVariable* CNamedCreatureVariableHash::FindKey(CString sVarName, LONG nValue)
{
    CString sTemp;

    for (int index = 0; index < sVarName.GetLength(); index++) {
        if (sVarName[index] != ' ') {
            sTemp += static_cast<char>(toupper(sVarName[index]));
        }
    }

    if (sTemp != "") {
        int hash = Hash(sTemp);

        CNamedCreatureVariableHashEntry* pEntry = m_hashEntries[hash];
        while (pEntry != NULL) {
            if (pEntry->m_variable.GetName() == sTemp
                && pEntry->m_variable.m_intValue == nValue) {
                return &(pEntry->m_variable);
            }
            pEntry = pEntry->m_pNext;
        }
    }

    return NULL;
}

// 0x5511C0
BOOL CNamedCreatureVariableHash::RemoveKey(CString sVarName, BOOL a2, LONG nValue)
{
    CString sTemp;

    for (int index = 0; index < sVarName.GetLength(); index++) {
        if (sVarName[index] != ' ') {
            sTemp += static_cast<char>(toupper(sVarName[index]));
        }
    }

    if (sTemp != "") {
        int hash = Hash(sTemp);

        CNamedCreatureVariableHashEntry* pEntry = m_hashEntries[hash];
        CNamedCreatureVariableHashEntry* pPrev = pEntry;
        while (pEntry != NULL) {
            if (pEntry->m_variable.GetName() == sTemp
                && (!a2 || pEntry->m_variable.m_intValue == nValue)) {
                if (pPrev == pEntry) {
                    delete pEntry;
                    m_hashEntries[hash] = NULL;
                } else {
                    pPrev->m_pNext = pEntry->m_pNext;
                    delete pEntry;
                }

                return TRUE;
            }
            pPrev = pEntry;
            pEntry = pEntry->m_pNext;
        }
    }

    return FALSE;
}

// 0x551350
void CNamedCreatureVariableHash::Marshal(CVariable** pList, WORD* pCount)
{
    *pList = NULL;
    *pCount = 0;
}

// 0x4A51D0
void CNamedCreatureVariableHash::MarshalToCharacter(CGameSprite* pSprite)
{
}

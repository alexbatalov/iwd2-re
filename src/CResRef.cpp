#include "CResRef.h"

// 0x78A960
CResRef::CResRef()
{
    memset(m_resRef, 0, RESREF_SIZE);
}

// 0x78A970
CResRef::CResRef(const CString& sName)
{
    *this = sName;
}

// 0x78A990
CResRef::CResRef(const char* pName)
{
    memset(m_resRef, 0, RESREF_SIZE);

    for (unsigned int i = 0; i < RESREF_SIZE; i++) {
        if (pName[i] == '\0') {
            break;
        }

        m_resRef[i] = pName[i];
        if (m_resRef[i] > '`' && m_resRef[i] < '{') {
            m_resRef[i] -= 'a' - 'A';
        }
    }
}

// 0x78A9D0
CResRef::CResRef(BYTE* resRef)
{
    *this = resRef;
}

// 0x78A9F0
void CResRef::CopyToString(CString& str) const
{
    char temp[RESREF_SIZE + 1];
    memcpy(temp, m_resRef, RESREF_SIZE);
    temp[RESREF_SIZE] = '\0';
    str = temp;
}

// 0x78AA20
const BYTE* CResRef::GetResRef() const
{
    return m_resRef;
}

// 0x78AA30
CString CResRef::GetResRefStr() const
{
    CString sResRef;
    sResRef.Format("%.*s", RESREF_SIZE, m_resRef);
    return sResRef;
}

// 0x78AAC0
BOOL CResRef::IsValid() const
{
    return m_resRef[0] != '\0';
}

// 0x78AAD0
void CResRef::CopyToString(char* pStr) const
{
    memcpy(pStr, m_resRef, RESREF_SIZE);
    pStr[RESREF_SIZE] = '\0';
}

// 0x78AAF0
BOOL CResRef::operator!=(const CResRef& cResRef) const
{
    return memcmp(m_resRef, cResRef.GetResRef(), RESREF_SIZE) != 0;
}

// 0x78AB20
BOOL CResRef::operator!=(const CString& sName) const
{
    return *this != static_cast<LPCTSTR>(sName);
}

// 0x78AB40
BOOL CResRef::operator!=(const char* pName) const
{
    for (unsigned int i = 0; i < RESREF_SIZE; i++) {
        // NOTE: Signed math.
        int c1 = pName[i] >= 'a' && pName[i] <= 'z' ? pName[i] - ('a' - 'A') : pName[i];

        // NOTE: Unsigned math.
        int c2 = m_resRef[i] >= 'a' && m_resRef[i] <= 'z' ? m_resRef[i] - ('a' - 'A') : m_resRef[i];

        if (c1 != c2) {
            return TRUE;
        }

        if (c1 == '\0') {
            return FALSE;
        }
    }

    return FALSE;
}

// NOTE: Inlined.
BOOL CResRef::operator==(const CResRef& cResRef) const
{
    return memcmp(m_resRef, cResRef.GetResRef(), RESREF_SIZE) == 0;
}

// 0x78ABA0
BOOL CResRef::operator==(const CString& sName) const
{
    return *this == static_cast<LPCTSTR>(sName);
}

// 0x78ABB0
BOOL CResRef::operator==(const char* pName) const
{
    for (unsigned int i = 0; i < RESREF_SIZE; i++) {
        // NOTE: Signed math.
        int c1 = pName[i] >= 'a' && pName[i] <= 'z' ? pName[i] - ('a' - 'A') : pName[i];

        // NOTE: Unsigned math.
        int c2 = m_resRef[i] >= 'a' && m_resRef[i] <= 'z' ? m_resRef[i] - ('a' - 'A') : m_resRef[i];

        if (c1 != c2) {
            return FALSE;
        }

        if (c1 == '\0') {
            return TRUE;
        }
    }

    return TRUE;
}

// 0x78AC20
BOOL CResRef::operator!() const
{
    return m_resRef[0] == '\0';
}

// 0x78AC30
CResRef CResRef::operator=(const CResRef& cResRef)
{
    memcpy(m_resRef, cResRef.GetResRef(), RESREF_SIZE);
    return *this;
}

// 0x78AC50
CResRef CResRef::operator=(BYTE* resRef)
{
    memcpy(m_resRef, resRef, RESREF_SIZE);
    MakeUpper();
    return *this;
}

// 0x78ACC0
CResRef CResRef::operator=(const CString& sName)
{
    LPCTSTR v1 = static_cast<LPCTSTR>(sName);
    unsigned int nLength = sName.GetLength();

    memset(m_resRef, 0, RESREF_SIZE);

    if (nLength > 0) {
        memcpy(m_resRef, v1, min(RESREF_SIZE, nLength));

        for (unsigned int i = 0; i < min(RESREF_SIZE, nLength); i++) {
            if (m_resRef[i] > '`' && m_resRef[i] < '{') {
                m_resRef[i] -= 'a' - 'A';
            }
        }
    }

    return *this;
}

// 0x78AD40
CResRef CResRef::operator=(const char* pName)
{
    memset(m_resRef, 0, RESREF_SIZE);

    for (unsigned int i = 0; i < RESREF_SIZE; i++) {
        unsigned char c = static_cast<unsigned char>(pName[i]);
        if (c == '\0') {
            break;
        }

        m_resRef[i] = c;
        if (c > '`' && c < '{') {
            m_resRef[i] = c - ('a' - 'A');
        }
    }

    return *this;
}

// 0x78AD90
void CResRef::MakeUpper()
{
    for (unsigned int i = 0; i < RESREF_SIZE; i++) {
        if (m_resRef[i] == '\0') {
            memset(m_resRef + i + 1, 0, RESREF_SIZE - 1 - i);
            return;
        }

        if (m_resRef[i] > '`' && m_resRef[i] < '{') {
            m_resRef[i] -= 'a' - 'A';
        }
    }
}

// 0x78ADD0
CResRef CResRef::operator+=(const CString& sName)
{
    CString sResRef;

    CopyToString(sResRef);
    sResRef += sName;
    sResRef.MakeUpper();

    if (sResRef.GetLength() > 0) {
        memcpy(m_resRef, sResRef.GetBuffer(RESREF_SIZE), min(sResRef.GetLength(), RESREF_SIZE));
    }

    return *this;
}

// 0x78AEB0
void CResRef::GetResRef(BYTE* resRef) const
{
    memcpy(resRef, m_resRef, RESREF_SIZE);
}

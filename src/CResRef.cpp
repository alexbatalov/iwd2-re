#include "CResRef.h"

// 0x78A960
CResRef::CResRef()
{
    memset(m_resRef, 0, sizeof(m_resRef));
}

// NOTE: Bad design, returning object produces unnecessary temporary instance
// at call sites. Should return reference to this instance, not a new object.
//
// #binary-identical
// 0x78AD40
CResRef CResRef::operator=(const char* pName)
{
    memset(m_resRef, 0, sizeof(m_resRef));

    for (unsigned int i = 0; i < sizeof(m_resRef); i++) {
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

// #binary-identical
// 0x78AB40
BOOL CResRef::operator!=(const char* pName)
{
    for (unsigned int i = 0; i < sizeof(m_resRef); i++) {
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

#include "CChatBuffer.h"

// #binary-identical
// 0x442B90
CChatBuffer::CChatBuffer()
{
    m_nMessageCount = 0;
}

// 0x442BB0
CChatBuffer::~CChatBuffer()
{
    POSITION pos = m_lMessages.GetHeadPosition();
    while (pos != NULL) {
        CString* string = m_lMessages.GetAt(pos);
        if (string != NULL) {
            delete string;
        }

        m_lMessages.GetNext(pos);
    }

    m_lMessages.RemoveAll();
}

// 0x442CA0
void CChatBuffer::ClearMessages()
{
    while (m_lMessages.GetCount() > 0) {
        CString* pString = m_lMessages.GetHead();
        if (pString != NULL) {
            delete pString;
        }

        m_lMessages.RemoveHead();
    }

    m_nMessageCount = 0;
}

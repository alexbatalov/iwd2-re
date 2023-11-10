#include "CChatBuffer.h"

#include "CUIControlTextDisplay.h"
#include "CUtil.h"

// 0x8483C0
const INT CChatBuffer::MAX_MESSAGES = 30;

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

// 0x442C30
void CChatBuffer::AddMessage(const CString& sMessage)
{
    m_lMessages.AddTail(new CString(sMessage));
    if (m_lMessages.GetCount() > MAX_MESSAGES) {
        CString* pString = m_lMessages.GetHead();
        delete pString;
        m_lMessages.RemoveHead();
    }
    m_nMessageCount++;
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

// 0x442CF0
int CChatBuffer::UpdateTextDisplay(CUIControlTextDisplay* pText, INT nCount)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CChatBuffer.cpp
    // __LINE__: 186
    UTIL_ASSERT(pText != NULL);

    int v1 = m_nMessageCount - nCount;
    if (m_lMessages.GetCount() < v1) {
        v1 = m_lMessages.GetCount();
    }

    if (v1 > 0) {
        POSITION pos = m_lMessages.FindIndex(m_lMessages.GetCount() - v1);
        while (pos != NULL) {
            CString* pString = m_lMessages.GetNext(pos);

            pText->DisplayString(*pString, RGB(110, 160, 220), -1, FALSE);
        }
    }

    return m_nMessageCount;
}

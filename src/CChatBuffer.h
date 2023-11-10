#ifndef CCHATBUFFER_H_
#define CCHATBUFFER_H_

#include "mfc.h"

class CUIControlTextDisplay;

class CChatBuffer {
public:
    static const INT MAX_MESSAGES;

    CChatBuffer();
    ~CChatBuffer();
    void AddMessage(const CString& sMessage);
    void ClearMessages();
    int UpdateTextDisplay(CUIControlTextDisplay* pText, INT nCount);

    CTypedPtrList<CPtrList, CString*> m_lMessages;
    int m_nMessageCount;
};

#endif /* CCHATBUFFER_H_ */

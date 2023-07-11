#ifndef CCHATBUFFER_H_
#define CCHATBUFFER_H_

#include "mfc.h"

class CUIControlTextDisplay;

class CChatBuffer {
public:
    CChatBuffer();
    ~CChatBuffer();
    void AddMessage(const CString& sMessage);
    void ClearMessages();
    int UpdateTextDisplay(CUIControlTextDisplay* pText, int a2);

    CTypedPtrList<CPtrList, CString*> m_lMessages;
    int m_nMessageCount;
};

#endif /* CCHATBUFFER_H_ */

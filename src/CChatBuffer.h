#ifndef CCHATBUFFER_H_
#define CCHATBUFFER_H_

#include <afx.h>
#include <afxtempl.h>

class CChatBuffer {
public:
    CChatBuffer();
    ~CChatBuffer();
    void AddMessage(const CString& sMessage);
    void ClearMessages();

    CTypedPtrList<CPtrList, CString*> m_lMessages;
    int m_nMessageCount;
};

#endif /* CCHATBUFFER_H_ */

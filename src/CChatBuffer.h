#ifndef CCHATBUFFER_H_
#define CCHATBUFFER_H_

#include <afx.h>
#include <afxtempl.h>

class CChatBuffer {
public:
    CChatBuffer();
    ~CChatBuffer();

    CTypedPtrList<CPtrList, CString*> field_0;
    int field_1C;
};

#endif /* CCHATBUFFER_H_ */

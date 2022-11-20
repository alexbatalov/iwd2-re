#ifndef CBALDURCHITIN_H_
#define CBALDURCHITIN_H_

#include <afxwin.h>

#include "CChitin.h"

class CBaldurChitin : public CChitin {
public:
    CBaldurChitin();
    ~CBaldurChitin();
    void Init(HINSTANCE hInstance);
};

extern CChitin* g_pChitin;
extern CBaldurChitin* g_pBaldurChitin;

#endif /* CBALDURCHITIN_H_ */

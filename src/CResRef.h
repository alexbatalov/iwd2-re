#ifndef CRESREF_H_
#define CRESREF_H_

#include <windows.h>

typedef BYTE RESREF[8];

class CResRef {
public:
    CResRef();

    CResRef operator=(const char* pName);

protected:
    RESREF m_resRef;
};

#endif /* CRESREF_H_ */

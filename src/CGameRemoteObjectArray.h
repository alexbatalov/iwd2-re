#ifndef CGAMEREMOTEOBJECTARRAY_H_
#define CGAMEREMOTEOBJECTARRAY_H_

#include "mfc.h"

class CGameRemoteObjectArray {
public:
    BOOL Find(DWORD remotePlayerID, LONG remoteObjectID, LONG& localObjectID);
};

#endif /* CGAMEREMOTEOBJECTARRAY_H_ */
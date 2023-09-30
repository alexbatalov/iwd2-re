#ifndef CGAMEREMOTEOBJECTARRAY_H_
#define CGAMEREMOTEOBJECTARRAY_H_

#include "mfc.h"

class CGameRemoteObjectArray {
public:
    BOOL CleanControlChanges();
    BOOL Find(DWORD remotePlayerID, LONG remoteObjectID, LONG& localObjectID);
    BOOL ChangeControlOnLoadGame();
};

#endif /* CGAMEREMOTEOBJECTARRAY_H_ */

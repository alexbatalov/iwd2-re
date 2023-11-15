#ifndef CGAMEBUTTONLIST_H_
#define CGAMEBUTTONLIST_H_

#include "mfc.h"

class CButtonData;

class CGameButtonList : public CTypedPtrList<CPtrList, CButtonData*> {
public:
};

#endif /* CGAMEBUTTONLIST_H_ */

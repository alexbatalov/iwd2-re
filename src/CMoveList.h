#ifndef CMOVELIST_H_
#define CMOVELIST_H_

#include "mfc.h"

#include "CResRef.h"

class CGameArea;

class CMoveListEntry {
public:
    CMoveListEntry();

    /* 0000 */ LONG m_nSpriteId;
    /* 0004 */ CResRef m_areaResRef;
    /* 000C */ CPoint m_ptDestination;
    /* 0014 */ BYTE m_nFacing;
    /* 0016 */ LONG m_nDelay;
};

class CMoveList : public CTypedPtrList<CPtrList, CMoveListEntry*> {
public:
    CMoveList();
    ~CMoveList() override;
    void ClearAll();
    void CheckLoad(CGameArea* pArea);
};

#endif /* CMOVELIST_H_ */

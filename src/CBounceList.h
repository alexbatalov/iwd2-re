#ifndef CBOUNCELIST_H_
#define CBOUNCELIST_H_

#include "mfc.h"

class CGameSprite;
class CProjectile;

class CBounceEntry {
public:
    LONG m_levelDecrement;
    DWORD m_effectId;
    CProjectile* m_pProjectile;
    BOOL m_decrementOnly;
};

class CBounceList : public CTypedPtrList<CPtrList, CBounceEntry*> {
public:
    void Process(CGameSprite* pSprite);
};

#endif /* CBOUNCELIST_H_ */

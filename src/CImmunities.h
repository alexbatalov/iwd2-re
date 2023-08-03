#ifndef CIMMUNITIES_H_
#define CIMMUNITIES_H_

#include "mfc.h"

class CWeaponIdentification {
public:
    WORD m_itemType;
    DWORD m_itemFlags;
    DWORD m_itemFlagMask;
    DWORD m_attributes;
};

#endif /* CIMMUNITIES_H_ */

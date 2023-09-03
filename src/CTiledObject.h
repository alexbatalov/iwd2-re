#ifndef CTILEDOBJECT_H_
#define CTILEDOBJECT_H_

#include "mfc.h"

#include "CResRef.h"

class CResWED;

class CTiledObject {
public:
    static const WORD STATE_PRIMARY_TILE;
    static const WORD STATE_SECONDARY_TILE;

    CTiledObject();

    /* 0000 */ LONG m_nWedIndex;
    /* 0004 */ CResWED* m_pResWed;
    /* 0008 */ WORD m_wAIState;
    /* 000A */ WORD m_wRenderState;
    /* 000C */ POSITION m_posAreaList;
    /* 0010 */ CResRef m_resId;
};

#endif /* CTILEDOBJECT_H_ */

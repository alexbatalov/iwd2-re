#ifndef CAISCRIPTFILE_H_
#define CAISCRIPTFILE_H_

#include "mfc.h"

#include "CAIIdList.h"

class CAIScriptFile {
public:
    static const CString IF;
    static const CString THEN;
    static const CString END;
    static const CString RESPONSE;
    static const CString COMMENT;

    BOOL LoadAllLists(CString a1);

    /* 002E */ CAIIdList m_triggers;
    /* 006E */ CAIIdList m_actions;
    /* 00AE */ CAIIdList m_objects;
};

#endif /* CAISCRIPTFILE_H_ */

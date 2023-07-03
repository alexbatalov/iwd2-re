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

    SHORT DecodeTriggerID(CString sName);
    SHORT DecodeActionID(CString sName);
    BYTE DecodeSpecialCase(CString sName);
    void ParseError(CString sError);
    CString ReadToChar(CString sLine, char c);
    CString ReadAfterChar(CString sLine, char c);
    BOOL LoadAllLists(CString a1);

    /* 0002 */ LONG m_lineNumber;
    /* 0016 */ CString m_errors;
    /* 002E */ CAIIdList m_triggers;
    /* 006E */ CAIIdList m_actions;
    /* 00AE */ CAIIdList m_objects;
};

#endif /* CAISCRIPTFILE_H_ */

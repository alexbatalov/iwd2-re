#ifndef CAISCRIPTFILE_H_
#define CAISCRIPTFILE_H_

#include "mfc.h"

#include "CAIIdList.h"
#include "CAIObjectType.h"

class CAICondition;
class CAIResponse;
class CAIResponseSet;
class CAIScript;

class CAIScriptFile {
public:
    static const CString IF;
    static const CString THEN;
    static const CString END;
    static const CString RESPONSE;
    static const CString COMMENT;

    CAIScriptFile();
    ~CAIScriptFile();

    SHORT DecodeTriggerID(CString sName);
    SHORT DecodeActionID(CString sName);
    BYTE DecodeSpecialCase(CString sName);
    LONG ParseInt(CString sID, CString sListName);
    void ParseError(CString sError);
    CAIObjectType ParseObjectAtomic(CString sLine);
    CString ReadToChar(CString sLine, char c);
    CString ReadAfterChar(CString sLine, char c);
    BOOL LoadAllLists(CString a1);

    void Clear();

    /* 0000 */ SHORT m_parseMode;
    /* 0002 */ LONG m_lineNumber;
    /* 0006 */ CAIScript* m_curScript;
    /* 000A */ CAIResponseSet* m_curResponseSet;
    /* 000E */ CAICondition* m_curCondition;
    /* 0012 */ CAIResponse* m_curResponse;
    /* 0016 */ CString m_errors;
    /* 001A */ CFile m_file;
    /* 002A */ CString m_decompiledText;
    /* 002E */ CAIIdList m_triggers;
    /* 006E */ CAIIdList m_actions;
    /* 00AE */ CAIIdList m_objects;
};

#endif /* CAISCRIPTFILE_H_ */

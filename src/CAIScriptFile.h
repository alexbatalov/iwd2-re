#ifndef CAISCRIPTFILE_H_
#define CAISCRIPTFILE_H_

#include "mfc.h"

#include "CAIAction.h"
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
    void ParseConditionalString(CString sData);
    void ParseResponseString(CString sData);
    SHORT ParseOneLine(CString sLine);
    SHORT ParseTrigger(CString sData);
    CString GetIdLine(CAIIdList& ids, CString& name);
    SHORT DecodeTriggerType(CString IDLine, LONG& paramCount);
    CString GetConstFile(CString sLine);
    CAIAction ParseAction(CString sData);
    SHORT DecodeTriggerID(CString sName);
    SHORT DecodeActionID(CString sName);
    BYTE DecodeSpecialCase(CString sName);
    CPoint ParsePoint(CString sLine);
    LONG ParseInt(CString sID, CString sListName);
    void ParseError(CString sError);
    CAIObjectType ParseObjectType(CString& sLine);
    CAIObjectType ParseObjectFunction(CString sLine);
    CAIObjectType ParseObjectAtomic(CString sLine);
    CString ReadToChar(CString sLine, char c);
    CString ReadAfterChar(CString sLine, char c);
    BOOL LoadAllLists(CString a1);
    SHORT DecodeActionType(CString IDLine, LONG& paramCount);
    CString GetParameterType(CString param);
    CString GetParameter(SHORT parNum, CString IDLine);

    void Clear();

    void NewResponseSet();
    void NewResponse(SHORT weight);
    void NewConditional();
    void SaveEntry();

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

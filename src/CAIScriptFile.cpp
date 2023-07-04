#include "CAIScriptFile.h"

#include "CAICondition.h"
#include "CAIResponse.h"
#include "CAIScript.h"

// 0x8C8438
const CString CAIScriptFile::IF("IF");

// 0x8C8424
const CString CAIScriptFile::THEN("THEN");

// 0x8C8410
const CString CAIScriptFile::END("END");

// 0x8C8430
const CString CAIScriptFile::RESPONSE("RESPONSE");

// 0x8C8420
const CString CAIScriptFile::COMMENT("//");

// 0x40FDC0
CAIScriptFile::CAIScriptFile()
{
    m_parseMode = 0;
    m_lineNumber = 0;
    m_curScript = new CAIScript();
    m_curResponseSet = NULL;
    m_curCondition = NULL;
    m_curResponse = NULL;
    LoadAllLists(".\\");
}

// 0x40FEB0
CAIScriptFile::~CAIScriptFile()
{
    if (m_curScript != NULL) {
        delete m_curScript;
    }

    if (m_curResponseSet != NULL) {
        delete m_curResponseSet;
    }

    if (m_curCondition != NULL) {
        delete m_curCondition;
    }

    if (m_curResponse != NULL) {
        delete m_curResponse;
    }
}

// FIXME: Use reference.
//
// 0x41CDB0
SHORT CAIScriptFile::DecodeTriggerID(CString sName)
{
    CAIId* pId = m_triggers.Find(sName, FALSE);
    if (pId != NULL) {
        return static_cast<SHORT>(pId->m_id);
    }

    ParseError("Trigger:" + sName + " Not found.  Check for proper brackets.");

    return -1;
}

// FIXME: Use reference.
//
// 0x41CEB0
SHORT CAIScriptFile::DecodeActionID(CString sName)
{
    CAIId* pId = m_actions.Find(sName, FALSE);
    if (pId != NULL) {
        return static_cast<SHORT>(pId->m_id);
    }

    ParseError("Action:" + sName + " Not found.  Check for proper brackets.");

    return -1;
}

// FIXME: Use reference.
//
// 0x41CF90
BYTE CAIScriptFile::DecodeSpecialCase(CString sName)
{
    CAIId* pId = m_objects.Find(sName, FALSE);
    if (pId != NULL) {
        return static_cast<BYTE>(pId->m_id);
    }

    ParseError("Special Case:" + sName + " Not found.  Check for proper brackets.");

    return -1;
}

// 0x41D310
void CAIScriptFile::ParseError(CString sError)
{
    sError += " Line Number:";

    char buffer[256];
    sprintf(buffer, "%d\n", m_lineNumber);

    sError += buffer;
    m_errors += sError;
}

// FIXME: `CAIUtil::ReadToChar` is better (does not use `operator+` every
// character).
//
// 0x41DF20
CString CAIScriptFile::ReadToChar(CString sLine, char c)
{
    CString sString("");

    for (int index = 0; index < sLine.GetLength(); index++) {
        if (sLine[index] == c) {
            break;
        }

        sString += sLine[index];
    }

    return sString;
}

// FIXME: Duplicate of `CAIUtil::ReadAfterChar`.
// FIXME: Use reference.
//
// 0x41DFE0
CString CAIScriptFile::ReadAfterChar(CString sLine, char c)
{
    CString sString("");

    int index = sLine.Find(c);
    if (index >= 0) {
        sString = sLine.Right(sLine.GetLength() - index - 1);
    }

    return sString;
}

// 0x41E0B0
BOOL CAIScriptFile::LoadAllLists(CString a1)
{
    m_triggers.LoadList(CResRef("TRIGGER"), FALSE);
    m_actions.LoadList(CResRef("ACTION"), FALSE);
    m_objects.LoadList(CResRef("OBJECT"), FALSE);

    return TRUE;
}

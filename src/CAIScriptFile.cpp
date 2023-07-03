#include "CAIScriptFile.h"

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

// 0x41E0B0
BOOL CAIScriptFile::LoadAllLists(CString a1)
{
    m_triggers.LoadList(CResRef("TRIGGER"), FALSE);
    m_actions.LoadList(CResRef("ACTION"), FALSE);
    m_objects.LoadList(CResRef("OBJECT"), FALSE);

    return TRUE;
}

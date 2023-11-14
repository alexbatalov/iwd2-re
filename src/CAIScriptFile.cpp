#include "CAIScriptFile.h"

#include "CAICondition.h"
#include "CAIIdList.h"
#include "CAIResponse.h"
#include "CAIScript.h"
#include "CAITrigger.h"
#include "CAIUtil.h"

#define SIG_V 5

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

// 0x40FCD0
void CAIScriptFile::Clear()
{
    m_errors = "";
    m_parseMode = 0;
    m_lineNumber = 0;

    if (m_curScript != NULL) {
        delete m_curScript;
        m_curScript = NULL;
    }

    m_curScript = new CAIScript();

    if (m_curResponseSet != NULL) {
        delete m_curResponseSet;
    }
    m_curResponseSet = NULL;

    if (m_curCondition != NULL) {
        delete m_curCondition;
    }
    m_curCondition = NULL;

    if (m_curResponse != NULL) {
        delete m_curResponse;
    }
    m_curResponse = NULL;
}

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

// 0x40FFA0
void CAIScriptFile::ParseConditionalString(CString sData)
{
    CString sLine;

    Clear();

    m_curCondition = new CAICondition();
    m_parseMode = 1;
    m_lineNumber = 0;

    while (sData.GetLength() > 0) {
        sLine = "";
        if (sData.Find('\n') >= 0) {
            sLine = CAIUtil::ReadTo(sData, CString("\n"), TRUE);
        } else {
            sLine = sData;
            sData = "";
        }
        m_lineNumber++;
        ParseOneLine(sLine);
    }
}

// 0x410120
void CAIScriptFile::ParseResponseString(CString sData)
{
    CString sLine;

    Clear();

    m_parseMode = 2;
    m_lineNumber = 0;

    // NOTE: Uninline.
    NewResponse(100);

    while (sData.GetLength() > 0) {
        sLine = "";
        if (sData.Find('\n') >= 0) {
            sLine = CAIUtil::ReadTo(sData, CString("\n"), TRUE);
        } else {
            sLine = sData;
            sData = "";
        }
        m_lineNumber++;
        ParseOneLine(sLine);
    }
}

// 0x4102B0
SHORT CAIScriptFile::ParseOneLine(CString sLine)
{
    sLine = CAIUtil::RemoveAllWS(sLine);

    CString sTemp;
    CString sResponse;
    SHORT weight;
    CAIAction action;

    sTemp = ReadToChar(sLine, '#');
    if (sLine == IF) {
        if (m_parseMode == 0) {
            // NOTE: Uninline.
            NewConditional();

            m_parseMode = 1;
        } else {
            ParseError(CString("Can not nest IF statements. Check for missing END."));
        }
    } else if (sLine == THEN) {
        if (m_parseMode == 1) {
            // NOTE: Uninline.
            NewResponseSet();

            m_parseMode = 2;
        } else {
            ParseError(CString("Misplaced THEN."));
            m_parseMode = -1;
        }
    } else if (sTemp == RESPONSE) {
        if (m_parseMode == 2) {
            sResponse = ReadAfterChar(sLine, '#');
            weight = static_cast<SHORT>(ParseInt(CString(sResponse), CString("")));

            // NOTE: Uninline.
            NewResponse(weight);
        } else {
            ParseError("Misplaced RESPONSE.");
        }
    } else if (sLine == END) {
        if (m_parseMode == 2) {
            // NOTE: Uninline.
            SaveEntry();

            m_parseMode = 0;
        } else {
            ParseError("Misplaced END.");
        }
    } else if (sLine == COMMENT) {
        if (sLine.GetLength() != 0) {
            switch (m_parseMode) {
            case 0:
                ParseError("Statement out side of IF END.");
                break;
            case 1:
                ParseTrigger(sLine);
                break;
            case 2:
                action = ParseAction(sLine);
                m_curResponse->Add(action);
                break;
            default:
                ParseError("Unknown Mode");
                m_parseMode = -1;
                break;
            }
        }
    }

    return m_parseMode;
}

// NOTE: See notes on `ParseAction`.
//
// 0x410B40
SHORT CAIScriptFile::ParseTrigger(CString sData)
{
    LONG specifics = 0;
    LONG specifics2 = 0;
    LONG specifics3 = 0;
    LONG flags = 0;
    LONG paramCount;
    SHORT triggerType;
    CString element;
    CString restOfLine;
    CString name;
    CString area;
    CAITrigger trigger(CAITrigger::NO_TRIGGER, 0);
    CAIObjectType cause;
    CString string1;
    CString string2;
    CString triggerIdLine;
    CString constFile;

    if (sData.GetLength() > 0 && sData[0] == '!') {
        flags |= 0x1;
        sData = sData.Right(sData.GetLength() - 1);
    }

    element = ReadToChar(sData, '(');
    restOfLine = ReadAfterChar(sData, '(');

    if (element.IsEmpty()) {
        ParseError("Invlaid trigger: No Opening bracket '('");
        return -1;
    }

    trigger.m_triggerID = DecodeTriggerID(element);
    triggerIdLine = GetIdLine(m_triggers, element);

    if (trigger.m_triggerID < 0) {
        return -1;
    }

    element = ReadAfterChar(element, '(');
    if (element.IsEmpty()) {
        ParseError("Invalid trigger: Nothing after opening bracket '('");
        return -1;
    }

    triggerType = DecodeTriggerType(triggerIdLine, paramCount);
    if (paramCount != -1) {
        LONG commaCount = 0;
        for (int index = 0; index < triggerIdLine.GetLength(); index++) {
            if (triggerIdLine[index] == ',') {
                commaCount++;
            }
        }

        if ((commaCount > paramCount - 1 && paramCount > 0)
            || (paramCount == 0 && commaCount != 0)) {
            ParseError(CString("Warning: Too many parameters:" + triggerIdLine));
        } else if (commaCount < paramCount - 1 && paramCount > 0) {
            ParseError(CString("Warning: Too few parameters:" + triggerIdLine));
        }
    }

    switch (triggerType) {
    case 4:
        triggerIdLine = triggerIdLine.Left(triggerIdLine.GetLength() - 1);
        if (triggerIdLine.IsEmpty()) {
            ParseError(CString("Missing First Parameter"));
            return -1;
        }

        cause = ParseObjectType(element);
        break;
    case 5:
        break;
    case 6:
        element = restOfLine.Left(restOfLine.GetLength() - 1);
        if (element.IsEmpty()) {
            ParseError(CString("Missing First Parameter"));
            return -1;
        }

        constFile = GetConstFile(GetParameter(1, triggerIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 9:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Missing First Parameter"));
            return -1;
        }

        cause = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = restOfLine.Left(restOfLine.GetLength() - 1);

        if (element.IsEmpty()) {
            ParseError(CString("Missing Second Parameter"));
            return -1;
        }

        constFile = GetConstFile(GetParameter(2, triggerIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 11:
        restOfLine = restOfLine.Right(restOfLine.GetLength() - 1);
        element = ReadToChar(restOfLine, '"');
        string1 = element;
        break;
    case 12:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = restOfLine.Left(restOfLine.GetLength() - 1);

        constFile = GetConstFile(GetParameter(2, triggerIdLine));
        specifics = ParseInt(restOfLine, constFile);
        string1 = name;
        break;
    case 13:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');

        restOfLine = restOfLine.Left(restOfLine.GetLength() - 1);

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics = ParseInt(restOfLine, constFile);

        string1 = area + name;
        break;
    case 14:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Missing First Parameter"));
            return -1;
        }

        constFile = GetConstFile(GetParameter(1, triggerIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = restOfLine.Left(restOfLine.GetLength() - 1);

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError(CString("Missing First Parameter"));
            return -1;
        }

        constFile = GetConstFile(GetParameter(2, triggerIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 15:
        restOfLine = restOfLine.Right(restOfLine.GetLength() - 1);

        element = ReadToChar(restOfLine, '"');
        string1 = element;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = restOfLine.Left(restOfLine.GetLength() - 1);

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError("Missing First Parameter");
            return -1;
        }

        cause = ParseObjectType(element);
        break;
    case 18:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');

        string1 = name;
        string2 = area;
        break;
    case 19:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Missing First Parameter");
            return -1;
        }

        cause = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(2, triggerIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Third".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 22:
        restOfLine = restOfLine.Right(restOfLine.GetLength() - 1);

        element = ReadToChar(restOfLine, '"');
        string1 = element;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError("Missing First Parameter");
            return -1;
        }

        cause = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = restOfLine.Left(restOfLine.GetLength() - 1);

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Third".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 24:
        element = ReadToChar(restOfLine, ',');
        restOfLine = ReadAfterChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError("Must specify first name");
        }

        element = element.Right(element.GetLength() - 1);
        element = ReadToChar(element, '"');
        string1 = element;

        element = ReadToChar(restOfLine, ',');
        restOfLine = ReadAfterChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError("Missing First Parameter");
            return -1;
        }

        cause = ParseObjectType(element);

        element = ReadToChar(restOfLine, ',');
        restOfLine = ReadAfterChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Third".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics = ParseInt(element, constFile);

        element = ReadToChar(restOfLine, ',');
        restOfLine = ReadAfterChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Fourth".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(4, triggerIdLine));
        specifics2 = ParseInt(element, constFile);

        element = ReadToChar(restOfLine, ')');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Fifth".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(5, triggerIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 29:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Missing First Parameter");
            return -1;
        }

        cause = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Second".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(2, triggerIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');

        element = restOfLine.Left(restOfLine.GetLength() - 1);
        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Third".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics2 = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');

        element = restOfLine.Left(restOfLine.GetLength() - 1);
        if (element.IsEmpty()) {
            // FIXME: Typo - should be "Fourth".
            ParseError("Missing First Parameter");
            return -1;
        }

        constFile = GetConstFile(GetParameter(4, triggerIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 30:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second string"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string1 = area + name;

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify third string"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify fourth string"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string2 = area + name;

        restOfLine = restOfLine.Left(restOfLine.GetLength() - 1);

        constFile = GetConstFile(GetParameter(5, triggerIdLine));
        specifics = ParseInt(restOfLine, constFile);
        break;
    case 33:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second string"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string1 = area + name;

        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, triggerIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = restOfLine.Left(restOfLine.GetLength() - 1);
        restOfLine = ReadAfterChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, triggerIdLine));
        specifics2 = ParseInt(restOfLine, constFile);
        break;
    default:
        ParseError(CString("Parser Error: Unknown statement"));
        break;
    }

    trigger.m_triggerCause = cause;
    trigger.m_specificID = specifics;
    trigger.m_specific2 = specifics2;
    trigger.m_specific3 = specifics3;
    trigger.m_string1 = string1;
    trigger.m_string2 = string2;
    trigger.m_flags = flags;
    m_curCondition->Add(trigger);

    return 1;
}

// 0x414F40
CString CAIScriptFile::GetIdLine(CAIIdList& ids, CString& name)
{
    CAIId* node = ids.Find(name, FALSE);
    if (node != NULL) {
        return node->m_line;
    } else {
        return CString("");
    }
}

// 0x414FA0
SHORT CAIScriptFile::DecodeTriggerType(CString IDLine, LONG& paramCount)
{
    return DecodeActionType(IDLine, paramCount);
}

// 0x415010
CString CAIScriptFile::GetConstFile(CString sLine)
{
    return ReadAfterChar(sLine, '*');
}

// NOTE: This function is HUGE. There are hundreds of `CString` ctor/dtor calls
// because helper functions accept object instances rather than references
// leading to excessive number of temporaries.
//
// 0x415080
CAIAction CAIScriptFile::ParseAction(CString sData)
{
    CString element;
    CString restOfLine;
    CString constFile;
    CString actionIdLine;
    CString name;
    CString area;

    CAIAction action;
    LONG specifics = 0;
    LONG specifics2 = 0;
    LONG specifics3 = 0;
    SHORT actionType;
    LONG paramCount;
    CAIObjectType actee1;
    CAIObjectType actee2;
    CAIObjectType actor;
    CPoint point(0, 0);
    CString string1;
    CString string2;
    CAIAction nullAction;

    element = ReadToChar(sData, '(');
    restOfLine = ReadAfterChar(sData, '(');

    if (element.IsEmpty()) {
        ParseError(CString("Invalid action: No Opening bracket '('"));
        return nullAction;
    }

    action.m_actionID = DecodeActionID(element);
    actionIdLine = GetIdLine(m_actions, element);

    if (action.m_actionID < 0) {
        return nullAction;
    }

    // FIXME: Already done above.
    restOfLine = ReadAfterChar(sData, '(');

    if (restOfLine.IsEmpty()) {
        ParseError(CString("Invalid action: Nothing after opening bracket '('"));
        return nullAction;
    }

    restOfLine = restOfLine.Left(restOfLine.GetLength() - 1);

    actionType = DecodeActionType(actionIdLine, paramCount);
    if (paramCount != -1) {
        LONG commaCount = 0;
        for (int index = 0; index < sData.GetLength(); index++) {
            if (sData[index] == ',') {
                commaCount++;
            }
        }

        if ((commaCount > paramCount - 1 && paramCount > 0)
            || (paramCount != 0 && commaCount == 0)) {
            ParseError(CString("Warning: Too many parameters:") + sData);
        } else if (commaCount < paramCount - 1 && paramCount > 0) {
            ParseError(CString("Warning: Too few parameters:") + sData);
        }
    }

    switch (actionType) {
    case 1:
        point = ParsePoint(restOfLine);
        break;
    case 2:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);

        restOfLine = ReadAfterChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(restOfLine, constFile);
        break;
    case 3:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        actee2 = ParseObjectType(element);
        break;
    case 4:
        actee1 = ParseObjectType(restOfLine);
        break;
    case 5:
        break;
    case 6:
        constFile = GetConstFile(GetParameter(1, actionIdLine));
        specifics = ParseInt(restOfLine, constFile);
        break;
    case 7:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);
        break;
    case 8:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        actee2 = ParseObjectType(element);
        break;
    case 9:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 10:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        actor = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError("Too few Parameters");
            return nullAction;
        }

        action = ParseAction(element);
        action.m_actorID = actor;

        return action;
    case 11:
        restOfLine = restOfLine.Right(restOfLine.GetLength() - 1);
        element = ReadToChar(restOfLine, '"');
        string1 = element;
        break;
    case 12:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(restOfLine, constFile);
        break;
    case 13:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(restOfLine, constFile);
        string1 = area + name;
        break;
    case 14:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(1, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(name, '"');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 15:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        element = ReadAfterChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);
        break;
    case 16:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        element = ReadAfterChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);
        break;
    case 17:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);

        element = ReadAfterChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 18:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify second name"));
        }

        restOfLine = ReadAfterChar(restOfLine, ',');

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');

        string1 = name;
        string2 = area;
        break;
    case 19:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);

        element = ReadAfterChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 20:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 21:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 22:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseAction(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 23:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseAction(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 24:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 25:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 27:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify file name"));
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        element = ReadAfterChar(restOfLine, ',');

        point = ParsePoint(element);
        break;
    case 28:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(1, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        element = ReadAfterChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 29:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(2, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 30:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify second string"));
        }

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string1 = area + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify third string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify fourth string"));
            return nullAction;
        }

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string2 = area + name;

        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify integer!"));
        }

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 33:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify second string"));
        }

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string1 = area + name;

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 34:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify second string"));
        }

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string1 = area + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify third string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify fourth string"));
        }

        area = element.Right(element.GetLength() - 1);
        area = ReadToChar(area, '"');
        area += ':';
        string2 = area + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        element = ReadAfterChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(6, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 35:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee2 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 36:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee2 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 37:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;
        break;
    case 38:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "second".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;
        break;
    case 39:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "second".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "third".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = string2 + ':' + name;
        break;
    case 40:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "second".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "third".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = string2 + ':' + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 41:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "second".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "third".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = string2 + ':' + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(6, actionIdLine));
        specifics2 = ParseInt(element, constFile);
        break;
    case 42:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string1 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "second".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            // FIXME: Typo - should be "third".
            ParseError(CString("Must specify first string"));
            return nullAction;
        }

        name = element.Right(element.GetLength() - 1);
        name = ReadToChar(name, '"');
        string2 = string2 + ':' + name;

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(5, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(6, actionIdLine));
        specifics2 = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        // FIXME: Should be 7?
        constFile = GetConstFile(GetParameter(6, actionIdLine));
        specifics3 = ParseInt(element, constFile);
        break;
    case 43:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    case 44:
        element = ReadToChar(restOfLine, ',');
        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        actee1 = ParseObjectType(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        point = ParsePoint(element);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        if (element.IsEmpty()) {
            ParseError(CString("Too few Parameters"));
            return nullAction;
        }

        constFile = GetConstFile(GetParameter(3, actionIdLine));
        specifics = ParseInt(element, constFile);

        restOfLine = ReadAfterChar(restOfLine, ',');
        element = ReadToChar(restOfLine, ',');

        constFile = GetConstFile(GetParameter(4, actionIdLine));
        specifics = ParseInt(element, constFile);
        break;
    default:
        ParseError(CString("Unknown Action:") + element);
        break;
    }

    action.m_actorID = actor;
    action.m_acteeID = actee1;
    action.m_acteeID2 = actee2;
    action.m_specificID = specifics;
    action.m_specificID2 = specifics2;
    action.m_specificID3 = specifics3;
    action.m_dest = point;
    action.SetString1(string1);
    action.SetString2(string2);

    return action;
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

// 0x41D070
CPoint CAIScriptFile::ParsePoint(CString sLine)
{
    SHORT x;
    SHORT y;
    CString element;
    CString restOfString;

    restOfString = sLine.Right(sLine.GetLength() - 1);
    if (restOfString.GetLength() != 0) {
        element = ReadToChar(restOfString, '.');
        if (element.GetLength() != 0) {
            x = static_cast<SHORT>(strtol(element, NULL, 10));
            restOfString = ReadAfterChar(restOfString, '.');
            if (restOfString.GetLength() != 0) {
                element = restOfString.Left(restOfString.GetLength() - 1);
                if (element.GetString() != 0) {
                    y = static_cast<SHORT>(strtol(element, NULL, 10));

                    return CPoint(x, y);
                }
            }
        }
    }

    ParseError("Illegal Point.  Proper format: [X.Y]");

    return CPoint(0, 0);
}

// 0x41D250
LONG CAIScriptFile::ParseInt(CString sID, CString sListName)
{
    CResRef resRef(sListName);
    CAIIdList ids(resRef);
    CAIId* id = ids.Find(sID, FALSE);
    if (id != NULL) {
        return id->m_id;
    }

    return strtol(sID, 0, 10);
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

// 0x41D3C0
CAIObjectType CAIScriptFile::ParseObjectType(CString& sLine)
{
    CString element;
    CString location;
    CString restOfString;

    BOOLEAN bDone = FALSE;

    BYTE tArr[10];
    tArr[0] = 0;
    tArr[1] = 0;
    tArr[2] = 0;
    tArr[3] = 0;
    tArr[4] = 0;
    tArr[5] = 0;
    tArr[6] = 0;
    tArr[7] = 0;
    tArr[8] = 0;
    tArr[9] = 0;

    CString constArr[10];
    constArr[0] = "EA";
    constArr[1] = "GENERAL";
    constArr[2] = "RACE";
    constArr[3] = "SUBRACE";
    constArr[4] = "CLASS";
    constArr[5] = "SPECIFIC";
    constArr[6] = "GENDER";
    constArr[7] = "ALIGN";
    constArr[8] = "AVCLASS";
    constArr[9] = "CLASSMSK";

    SHORT count = 0;

    CAIObjectType object;

    if (sLine == "") {
        sLine = "MYSELF";
    }

    if (sLine[0] == '"') {
        element = sLine.Right(sLine.GetLength() - 1).SpanExcluding("\"");
        object.m_sName = element;

        int openPos = sLine.ReverseFind('[');
        int closePos = sLine.ReverseFind(']');
        int quotePos = sLine.ReverseFind('"');
        if (quotePos >= 0 && openPos > quotePos && closePos > openPos) {
            location = ReadAfterChar(restOfString, '[');
        }
    } else if (sLine[0] == '[') {
        restOfString = sLine.Right(sLine.GetLength() - 1);

        location = ReadAfterChar(restOfString, '[');

        restOfString = ReadToChar(restOfString, ']');

        while (count < 10 && !bDone) {
            element = ReadToChar(restOfString, '.');
            if (element[element.GetLength() - 1] == ']') {
                element = element.Left(element.GetLength() - 1);
                bDone = TRUE;
            }

            tArr[count] = static_cast<BYTE>(ParseInt(element, constArr[count]));
            restOfString = ReadAfterChar(restOfString, '.');

            if (restOfString.IsEmpty()) {
                bDone = TRUE;
            }

            count++;
        }

        if (count >= 10 && !bDone) {
            ParseError(CString("Too many parameters provided for this object."));
        }

        object = CAIObjectType(tArr[0],
            tArr[1],
            tArr[2],
            tArr[3],
            tArr[4],
            tArr[5],
            tArr[6],
            tArr[7],
            -1,
            tArr[8],
            tArr[9]);
    } else if (sLine[sLine.GetLength() - 1] == ')') {
        object = ParseObjectFunction(sLine);
    } else {
        location = ReadAfterChar(sLine, '[');
        sLine = ReadToChar(sLine, '[');
        object = ParseObjectAtomic(sLine);
    }

    if (!location.IsEmpty()) {
        int v1;
        int v2;
        int v3;
        int v4;
        int values = sscanf(location,
            "%d.%d.%d.%d",
            &v1,
            &v2,
            &v3,
            &v4);
        switch (values) {
        case 2:
            object.SetCenter(CPoint(v1, v2));
            break;
        case 3:
            object.SetCenter(CPoint(v1, v2));
            object.SetRadius(v3);
            break;
        case 4:
            object.SetRect(CRect(v1, v2, v3, v4));
            break;
        default:
            object.m_nLocationType = 0;
            break;
        }
    } else {
        object.m_nLocationType = 0;
    }

    return object;
}

// 0x41DBD0
CAIObjectType CAIScriptFile::ParseObjectFunction(CString sLine)
{
    SHORT count = 0;
    BYTE* tArr;
    BYTE specialCase;
    CString element;
    CString restOfString;
    CAIObjectType object;

    element = ReadToChar(sLine, '(');
    restOfString = ReadAfterChar(sLine, '(');
    restOfString = restOfString.Left(restOfString.GetLength() - 1);
    object = ParseObjectType(restOfString);
    specialCase = DecodeSpecialCase(element);

    tArr = object.m_SpecialCase;
    while (count < 5) {
        if (tArr[count] == 0) {
            break;
        }
        count++;
    }

    if (count < 5) {
        tArr[count] = specialCase;
        object.SetSpecialCase(tArr);
    } else {
        ParseError(CString("Too many nested functions."));
    }

    return object;
}

// 0x41DE10
CAIObjectType CAIScriptFile::ParseObjectAtomic(CString sLine)
{
    CAIObjectType type;

    // NOTE: Original code is different.
    type.m_SpecialCase[0] = DecodeSpecialCase(sLine);

    return type;
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

// FIXME: There are hundreds of unnecessary `CString` ctor/dtor calls.
//
// 0x41E200
SHORT CAIScriptFile::DecodeActionType(CString IDLine, LONG& paramCount)
{
    CString param;
    CString paramType;

    param = GetParameter(1, IDLine);
    param.TrimLeft();
    param.TrimRight();

    paramCount = 0;

    if (param == "") {
        return 5;
    }

    paramType = GetParameterType(param);
    if (paramType == "") {
        return -1;
    }

    if (paramType == CString('P')) {
        param = GetParameter(2, IDLine);
        if (param == "") {
            paramCount = 1;
            return 1;
        }

        paramType = GetParameterType(param);
        if (paramType == CString('I')) {
            paramCount = 2;
            return 2;
        }

        return -1;
    } else if (paramType == CString('O')) {
        param = GetParameter(2, IDLine);
        if (param == "") {
            paramCount = 1;
            return 4;
        }

        paramType = GetParameterType(param);
        if (paramType == CString('O')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 8;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 35;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    param = GetParameter(5, IDLine);
                    if (param == "") {
                        paramCount = 4;
                        return 36;
                    }
                }
            }
        }

        if (paramType == CString('P')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 7;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 43;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    param = GetParameter(5, IDLine);
                    if (param == "") {
                        paramCount = 4;
                        return 44;
                    }
                }
            }
        }

        if (paramType == CString('A')) {
            paramCount = -1;
            return 10;
        }

        if (paramType == CString('I')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 9;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('O')) {
                paramCount = 3;
                return 3;
            }

            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 19;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    paramCount = 4;
                    return 29;
                }
            }
        } else if (paramType == CString('S')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 37;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('S')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 38;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('S')) {
                    param = GetParameter(5, IDLine);
                    if (param == "") {
                        paramCount = 4;
                        return 39;
                    }

                    paramType = GetParameterType(param);
                    if (paramType == CString('I')) {
                        param = GetParameter(6, IDLine);
                        if (param == "") {
                            paramCount = 5;
                            return 40;
                        }

                        paramType = GetParameterType(param);
                        if (paramType == CString('I')) {
                            param = GetParameter(7, IDLine);
                            if (param == "") {
                                paramCount = 6;
                                return 41;
                            }

                            paramType = GetParameterType(param);
                            if (paramType == CString('I')) {
                                param = GetParameter(8, IDLine);
                                if (param == "") {
                                    paramCount = 7;
                                    return 42;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if (paramType == CString('I')) {
        param = GetParameter(2, IDLine);
        if (param == "") {
            paramCount = 1;
            return 6;
        }

        param = GetParameter(3, IDLine);
        if (param != "") {
            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                paramCount = 3;
                return 28;
            }
        } else {
            param = GetParameter(2, IDLine);
            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                paramCount = 2;
                return 14;
            }
        }
    } else if (paramType == CString('S')) {
        param = GetParameter(2, IDLine);
        if (param == "") {
            paramCount = 1;
            return 11;
        }

        paramType = GetParameterType(param);
        if (paramType == CString('I')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 12;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 20;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    paramCount = 4;
                    return 21;
                }
            }
        } else if (paramType == CString('P')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 16;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                paramCount = 3;
                return 17;
            }
        } else if (paramType == CString('S')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 18;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 13;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    paramCount = 4;
                    return 33;
                }
            }

            if (paramType == CString('S')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 32;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('S')) {
                    param = GetParameter(5, IDLine);
                    if (param == "") {
                        paramCount = 4;
                        return 31;
                    }

                    paramType = GetParameterType(param);
                    if (paramType == CString('I')) {
                        param = GetParameter(6, IDLine);
                        if (param == "") {
                            paramCount = 5;
                            return 30;
                        }

                        paramType = GetParameterType(param);
                        if (paramType == CString('I')) {
                            paramCount = 6;
                            return 34;
                        }
                    }
                }
            } else if (paramType == CString('P')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 26;
                }

                paramType = GetParameterType(param);
                if (paramType == 'I') {
                    paramCount = 4;
                    return 25;
                }
            }
        } else if (paramType == CString('O')) {
            param = GetParameter(3, IDLine);
            if (param == "") {
                paramCount = 2;
                return 15;
            }

            paramType = GetParameterType(param);
            if (paramType == CString('I')) {
                param = GetParameter(4, IDLine);
                if (param == "") {
                    paramCount = 3;
                    return 22;
                }

                paramType = GetParameterType(param);
                if (paramType == CString('I')) {
                    param = GetParameter(5, IDLine);
                    if (param == "") {
                        paramCount = 4;
                        return 23;
                    }

                    paramType = GetParameterType(param);
                    if (paramType == CString('I')) {
                        paramCount = 5;
                        return 24;
                    }
                }
            } else if (paramType == CString('P')) {
                paramCount = 3;
                return 27;
            }
        }
    }

    return -1;
}

// 0x420A60
CString CAIScriptFile::GetParameterType(CString param)
{
    return ReadToChar(param, ':');
}

// 0x420AD0
CString CAIScriptFile::GetParameter(SHORT parNum, CString IDLine)
{
    SHORT curParNum;
    CString parameters;
    CString curPar;

    parameters = ReadAfterChar(IDLine, '(');
    parameters.TrimLeft();
    parameters.TrimRight();

    if (parameters != "") {
        parameters = parameters.Left(parameters.GetLength() - 1);
        curParNum = 0;
        while (curParNum < parNum) {
            curPar = ReadToChar(parameters, ',');
            parameters = ReadAfterChar(parameters, ',');
            curParNum++;
        }

        curPar.TrimLeft();
        curPar.TrimRight();
        return curPar;
    } else {
        return CString("");
    }
}

// NOTE: Inlined.
void CAIScriptFile::NewResponseSet()
{
    if (m_curResponseSet != NULL) {
        delete m_curResponseSet;
    }

    m_curResponseSet = new CAIResponseSet();
}

// NOTE: Inlined.
void CAIScriptFile::NewResponse(SHORT weight)
{
    if (m_curResponse != NULL) {
        if (m_curResponseSet != NULL) {
            m_curResponseSet->Add(*m_curResponse);
        }

        if (m_curResponse != NULL) {
            delete m_curResponse;
        }
    }

    m_curResponse = new CAIResponse();
    m_curResponse->m_weight = weight;
}

// NOTE: Inlined.
void CAIScriptFile::NewConditional()
{
    if (m_curCondition != NULL) {
        delete m_curCondition;
    }

    m_curCondition = new CAICondition();
}

// NOTE: Inlined.
void CAIScriptFile::SaveEntry()
{
    if (m_curResponseSet != NULL && m_curCondition != NULL) {
        if (m_curResponse != NULL) {
            m_curResponseSet->Add(*m_curResponse);

            if (m_curResponse != NULL) {
                delete m_curResponse;
            }

            m_curResponse = NULL;
        }

        m_curScript->Add(*m_curCondition, *m_curResponseSet);
    }
}

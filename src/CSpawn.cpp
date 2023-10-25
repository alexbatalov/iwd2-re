#include "CSpawn.h"

#include "CGameAIBase.h"
#include "CGameArea.h"
#include "CMemINI.h"
#include "CUtil.h"

template <class Thing>
static void _SpawnReleasePointer(Thing*& rPointer);

// 0x8FA838
static const CString ScopeStr("::");

// 0x8FA800
static const CString INIDefault("BlackIsle");

// 0x8FA7F0
const CString CSpawnFile::EventListKey("events");

// 0x8FA81C
const CString CSpawnFile::MainSectionKey("spawn_main");

// 0x8FA7FC
const CString CSpawnFile::ExitEventKey("exit");

// 0x8FA334
const CString CSpawnFile::EnterEventKey("enter");

// 0x8FA844
const CString CSpawnList::IntervalKey("interval");

// 0x8FA344
const CString CSpawnList::AliasListKey("critters");

// 0x8FA85C
const CString CSpawnList::ControlKey("control_var");

// 0x8FA7DC
const CString CSpawnList::SpawnTimesKey("spawn_time_of_day");

// 0x8FA7AC
const CString CSpawn::SpecVarKey("spec_var");

// 0x8FA7B0
const CString CSpawn::SpecKey("spec");

// 0x8FA7B4
const CString CSpawn::SpecRegionKey("spec_area");

// 0x8FA860
const CString CSpawn::SpecQtyKey("spec_qty");

// 0x8FA354
const CString CSpawn::SpecVarIncKey("spec_var_inc");

// 0x8FA820
const CString CSpawn::SpecVarValueKey("spec_var_value");

// 0x8FA34C
const CString CSpawn::SpecVarOperationKey("spec_var_operation");

// 0x8FA848
const CString CSpawn::GreaterThanKey("greater_than");

// 0x8FA7E8
const CString CSpawn::LessThanKey("less_than");

// 0x8FA840
const CString CSpawn::EqualToKey("equal_to");

// 0x8FA804
const CString CSpawn::NotEqualToKey("not_equal_to");

// 0x8FA768
const CString CSpawn::AreaDiff1Key("area_diff_1");

// 0x8FA868
const CString CSpawn::AreaDiff2Key("area_diff_2");

// 0x8FA794
const CString CSpawn::AreaDiff3Key("area_diff_3");

// 0x8FA828
const CString CSpawn::CreFileKey("cre_file");

// 0x8FA764
const CString CSpawn::CreateQtyKey("create_qty");

// 0x8FA7C4
const CString CSpawn::ScriptNameKey("script_name");

// 0x8FA7D4
const CString CSpawn::EAKey("ai_ea");

// 0x8FA7D8
const CString CSpawn::GeneralKey("ai_general");

// 0x8FA7EC
const CString CSpawn::RaceKey("ai_race");

// 0x8FA818
const CString CSpawn::ClassKey("ai_class");

// 0x8FA858
const CString CSpawn::GenderKey("ai_gender");

// 0x8FA350
const CString CSpawn::SpecificsKey("ai_specifics");

// 0x8FA7C8
const CString CSpawn::AlignmentKey("ai_alignment");

// 0x8FA76C
const CString CSpawn::FactionKey("ai_faction");

// 0x8FA7B8
const CString CSpawn::TeamKey("ai_team");

// 0x8FA814
const CString CSpawn::OverrideScriptKey("script_override");

// 0x8FA7C0
const CString CSpawn::ScriptSpecial1Key("script_special_1");

// 0x8FA830
const CString CSpawn::ScriptTeamKey("script_team");

// 0x8FA784
const CString CSpawn::ScriptSpecial2Key("script_special_2");

// 0x8FA7E4
const CString CSpawn::ScriptCombatKey("script_combat");

// 0x8FA808
const CString CSpawn::ScriptSpecial3Key("script_special_3");

// 0x8FA7CC
const CString CSpawn::ScriptMovementKey("script_movement");

// 0x8FA7E0
const CString CSpawn::DialogFileKey("dialog");

// 0x8FA84C
const CString CSpawn::DeathGoodKey("good_mod");

// 0x8FA798
const CString CSpawn::DeathLawKey("law_mod");

// 0x8FA778
const CString CSpawn::DeathLadyKey("lady_mod");

// 0x8FA80C
const CString CSpawn::DeathMurderKey("murder_mod");

// 0x8FA7F4
const CString CSpawn::ObitScripnameKey("death_scriptname");

// 0x8FA850
const CString CSpawn::ObitFactionKey("death_faction");

// 0x8FA834
const CString CSpawn::ObitTeamKey("death_team");

// 0x8FA340
const CString CSpawn::SpawnPointsKey("spawn_point");

// 0x8FA758
const CString CSpawn::PointSelectKey("point_select");

// 0x8FA854
const CString CSpawn::PointVarKey("point_select_var");

// 0x8FA330
const CString CSpawn::FacingKey("facing");

// 0x8FA348
const CString CSpawn::CanSeeKey("ignore_can_see");

// 0x8FA7A8
const CString CSpawn::CrowdCheckKey("check_crowd");

// 0x8FA864
const CString CSpawn::SafeSpotKey("find_safest_point");

// 0x8FA7A0
const CString CSpawn::SavePointVarKey("Save_selected_point");

// 0x8FA770
const CString CSpawn::SaveFacingVarKey("save_selected_facing");

// 0x8FA7D0
const CString CSpawn::SpawnFromPointVarKey("spawn_point_global");

// 0x8FA760
const CString CSpawn::FacePointVarKey("spawn_facing_global");

// 0x8FA7BC
const CString CSpawn::IncrementPointIndexKey("inc_spawn_point_index");

// 0x8FA810
const CString CSpawn::HoldSelectedPointKey("hold_selected_point_key");

// 0x8FA780
const CString CSpawn::ViewPortKey("check_by_view_port");

// 0x8FA83C
const CString CSpawn::DontSpawnKey("do_not_spawn");

// 0x8FA75C
const CString CSpawn::CreatureTimesKey("time_of_day");

// 0x7683E0
CSpawnFile::CSpawnFile(CMemINI* pMemINI)
{
    RemoveAll();

    mpExitList = NULL;
    mpEnterList = NULL;

    UTIL_ASSERT_MSG(pMemINI != NULL, "Empty INI");

    CMemINISection* pSection = pMemINI->GetSection(MainSectionKey);
    if (pSection != NULL && pSection->GetCount() > 0) {
        CString sEventList;

        // NOTE: Uninline.
        if (GetINIKey(pSection, EventListKey, sEventList)) {
            CStringArray Sections;
            ParseData(sEventList, Sections);

            for (int index = Sections.GetCount(); index > 0; index--) {
                if (pMemINI->GetSection(Sections[index - 1])) {
                    CSpawnList* pList = new CSpawnList(pMemINI, Sections[index - 1]);
                    if (pList->GetCount() > 0) {
                        AddTail(pList);
                    } else {
                        delete pList;
                    }
                }
            }
        }

        mpExitList = NULL;
        mpEnterList = NULL;

        CString sExitEvent;
        CString sEnterEvent;

        // NOTE: Uninline.
        if (GetINIKey(pSection, ExitEventKey, sExitEvent)) {
            sExitEvent.TrimLeft();
            sExitEvent.TrimRight();

            CMemINISection* pSpawnSection = pMemINI->GetSection(sExitEvent);
            if (pSpawnSection != NULL && pSpawnSection->GetCount() > 0) {
                mpExitList = new CSpawnList(pMemINI, sExitEvent);
            }
        }

        // NOTE: Uninline.
        if (GetINIKey(pSection, EnterEventKey, sEnterEvent)) {
            sEnterEvent.TrimRight();
            sEnterEvent.TrimLeft();

            CMemINISection* pSpawnSection = pMemINI->GetSection(sEnterEvent);
            if (pSpawnSection != NULL && pSpawnSection->GetCount() > 0) {
                mpEnterList = new CSpawnList(pMemINI, sEnterEvent);
            }
        }
    }

    m_bInSpawn = FALSE;
}

// 0x7686A0
CSpawnFile::~CSpawnFile()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CSpawnList* pList = reinterpret_cast<CSpawnList*>(GetNext(pos));
        delete pList;
    }
    RemoveAll();

    if (mpExitList != NULL) {
        delete mpExitList;
    }

    if (mpEnterList != NULL) {
        delete mpEnterList;
    }
}

// 0x768730
int CSpawnFile::Execute(CGameArea* pArea)
{
    int rc = 0;

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
        || g_pChitin->cNetwork.GetSessionHosting()) {
        m_bInSpawn = TRUE;

        POSITION pos = GetHeadPosition();
        while (pos != NULL) {
            CSpawnList* pList = reinterpret_cast<CSpawnList*>(GetNext(pos));
            if (pList != NULL) {
                rc += pList->Execute(pArea, FALSE);
            }
        }

        m_bInSpawn = FALSE;
    }

    return rc;
}

// 0x7687A0
int CSpawnFile::ExitSpawn(CGameArea* pArea)
{
    int rc = 0;

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
        || g_pChitin->cNetwork.GetSessionHosting()) {
        m_bInSpawn = TRUE;
        if (mpExitList != NULL) {
            rc = mpExitList->Execute(pArea, TRUE);
        }
        m_bInSpawn = FALSE;
    }

    return rc;
}

// 0x7687F0
int CSpawnFile::EnterSpawn(CGameArea* pArea)
{
    int rc = 0;

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
        || g_pChitin->cNetwork.GetSessionHosting()) {
        m_bInSpawn = TRUE;
        if (mpEnterList != NULL) {
            rc = mpEnterList->Execute(pArea, TRUE);
        }
        m_bInSpawn = FALSE;
    }

    return rc;
}

// 0x768840
int CSpawnFile::ParseData(const CString& sData, CStringArray& Sections)
{
    CString sMutableData(sData);
    sMutableData.TrimLeft();
    sMutableData.TrimRight();

    int count = 0;
    while (sMutableData.GetLength() > 0) {
        int pos = sMutableData.FindOneOf(",.");
        if (pos >= 0) {
            CString sSection = sMutableData.Left(pos);
            sMutableData = sMutableData.Mid(pos + 1);

            if (sSection.GetLength() > 0) {
                count++;
                Sections.Add(sSection);
            }
        } else {
            Sections.Add(sMutableData);
            sMutableData.Empty();
        }
    }
    return count;
}

// NOTE: Inlined.
BOOL CSpawnFile::GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue)
{
    if (pSection != NULL) {
        CMemINIValue* pValue = pSection->Get(sKey);
        if (pValue != NULL) {
            sValue = pValue->GetValue();
            return TRUE;
        }
    }
    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x768970
CSpawnList::CSpawnList(CMemINI* pMemINI, const CString& sSection)
{
    mInterval = INT_MAX;
    field_20 = 0;
    field_24 = 0;
    field_28 = 0;
    CheckSpawnTimes = 0;
    SpawnTimeOfDay = 0;
    pControlVar = NULL;

    RemoveAll();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
    // __LINE__: 419
    UTIL_ASSERT_MSG(pMemINI != NULL, "Empty INI");

    CMemINISection* pSection = pMemINI->GetSection(sSection);
    if (pSection && pSection->GetCount() > 0) {
        mSectionAlias = pSection->GetSectionName();

        CStringArray Sections;
        CString sValue;

        // NOTE: Uninline.
        if (GetINIKey(pSection, AliasListKey, sValue)) {
            int Qty = ParseData(sValue, Sections);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
            // __LINE__: 430
            UTIL_ASSERT_MSG(Qty == (Sections.GetUpperBound() + 1), "error parsing section list");

            for (int index = 0; index < Qty; index++) {
                CMemINISection* pSpawnSection = pMemINI->GetSection(Sections[index]);
                if (pSpawnSection != NULL && pSpawnSection->GetCount() > 0) {
                    CSpawn* pSpawn = new CSpawn(pSpawnSection);
                    if (pSpawn->DataIsValid) {
                        AddTail(pSpawn);
                    } else {
                        delete pSpawn;
                    }
                }
            }
        }

        // NOTE: Uninline.
        if (GetINIKey(pSection, IntervalKey, sValue)) {
            mInterval = atoi(sValue);
        }

        if (mInterval < 15) {
            mInterval = 15;
        }

        pControlVar = NULL;

        // NOTE: Uninline.
        if (GetINIKey(pSection, ControlKey, sValue)) {
            int pos = sValue.FindOneOf(ScopeStr);
            if (pos > 0 && pos + ScopeStr.GetLength() < sValue.GetLength() - 1) {
                pControlVar = new CSpawnVar(sValue.Left(pos),
                    sValue.Mid(pos + ScopeStr.GetLength()));
            }
        }

        // NOTE: Uninline.
        if (GetINIKey(pSection, ControlKey, sValue)) {
            sValue.TrimRight();
            sValue.TrimLeft();
            sValue.MakeLower();
        }
    }
}

// 0x768E90
CSpawnList::~CSpawnList()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CSpawn* pSpawn = GetNext(pos);
        delete pSpawn;
    }
    RemoveAll();

    if (pControlVar != NULL) {
        delete pControlVar;
    }

    pControlVar = NULL;
    field_20 = 0;
    field_24 = 0;
    field_28 = 0;
}

// 0x768D50
int CSpawnList::ParseData(const CString& sData, CStringArray& Sections)
{
    CString sMutableData(sData);
    sMutableData.TrimLeft();
    sMutableData.TrimRight();

    int count = 0;
    while (sMutableData.GetLength() > 0) {
        int pos = sMutableData.FindOneOf(",.");
        if (pos >= 0) {
            CString sSection = sMutableData.Left(pos);
            sMutableData = sMutableData.Mid(pos + 1);

            sSection.TrimRight();
            sMutableData.TrimLeft();

            if (sSection.GetLength() > 0) {
                count++;
                Sections.Add(sSection);
            }
        } else {
            Sections.Add(sMutableData);
            sMutableData.Empty();
        }
    }

    return count;
}

// 0x768FA0
int CSpawnList::Execute(CGameArea* pArea, BOOL bForce)
{
    // TODO: Incomplete.

    return 0;
}

// NOTE: Inlined.
BOOL CSpawnList::GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue)
{
    if (pSection != NULL) {
        CMemINIValue* pValue = pSection->Get(sKey);
        if (pValue != NULL) {
            sValue = pValue->GetValue();
            return TRUE;
        }
    }
    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x769460
CSpawn::CSpawn(CMemINISection* pSection)
{
    mSearchQty = 0;
    mCreateQty = 0;
    mEA = 0;
    mGeneral = 0;
    mRace = 0;
    mClass = 0;
    mGender = 0;
    mSpecifics = 0;
    mFaction = 0;
    mTeam = 0;
    mAlignment = 0;
    mDeathGoodModifier = 0;
    mDeathLawModifier = 0;
    mDeathLadyModifier = 0;
    mDeathMurderModifier = 0;
    Facing = 0;
    field_136 = 0;
    field_13A = 0;
    field_13E = 0;
    field_13F = 0;
    field_140 = 0;
    field_141 = 0;
    mInterval = -1;
    SpawnFlags = 0;
    DataIsValid = FALSE;
    pSpawnFacingStorageLabel = 0;
    pSpawnFacingStorageScope = 0;
    pExplicitSpawnFacingLabel = 0;
    pExplicitSpawnFacingScope = 0;
    mpSearchQtyVar = 0;
    mpSearchKeyVar = 0;
    mpSpawnPointStorage = NULL;
    mpExplicitSpawnPoint = NULL;
    pPointIndexLabel = 0;
    pPointIndexScope = 0;
    mpTeamScript = 0;
    mpSpecial1Script = 0;
    mpMovementScript = 0;
    mpSpecial3Script = 0;
    mpCombatScript = 0;
    mpSpecial2Script = 0;
    mpOverrideScript = 0;
    mpScriptName = 0;
    mpCreateQtyLabel = 0;
    mpCreateQtyScope = 0;
    mSequentialStartValue = 0;
    mTimeOfDay = 0;
    Read(pSection);
}

// 0x769750
CSpawn::~CSpawn()
{
    Zark();
}

// 0x769840
void CSpawn::Zark()
{
    DataIsValid = FALSE;
    mAlignment = 0;
    mTeam = 0;
    mFaction = 0;
    mSpecifics = 0;
    mGender = 0;
    mClass = 0;
    mRace = 0;
    mGeneral = 0;
    mEA = 0;
    mDeathMurderModifier = 0;
    mDeathLadyModifier = 0;
    mDeathLawModifier = 0;
    mDeathGoodModifier = 0;

    // NOTE: Uninline.
    mSpawnPointArray.Zark();

    mDialogFiles.RemoveAll();
    mCREFiles.RemoveAll();

    // NOTE: The following calls are inlined.
    _SpawnReleasePointer(mpSearchKeyVar);
    _SpawnReleasePointer(mpSearchQtyVar);
    _SpawnReleasePointer(mpCreateQtyScope);
    _SpawnReleasePointer(mpCreateQtyLabel);
    _SpawnReleasePointer(mpScriptName);
    _SpawnReleasePointer(mpOverrideScript);
    _SpawnReleasePointer(mpSpecial2Script);
    _SpawnReleasePointer(mpCombatScript);
    _SpawnReleasePointer(mpSpecial3Script);
    _SpawnReleasePointer(mpMovementScript);
    _SpawnReleasePointer(mpSpecial1Script);
    _SpawnReleasePointer(mpTeamScript);
    _SpawnReleasePointer(pPointIndexScope);
    _SpawnReleasePointer(pPointIndexLabel);
    _SpawnReleasePointer(mpExplicitSpawnPoint);

    // NOTE: The following calls are not inlined.
    _SpawnReleasePointer(pExplicitSpawnFacingScope);
    _SpawnReleasePointer(pExplicitSpawnFacingLabel);
    _SpawnReleasePointer(mpSpawnPointStorage);
    _SpawnReleasePointer(pSpawnFacingStorageScope);
    _SpawnReleasePointer(pSpawnFacingStorageLabel);
}

// 0x769AA0
int CSpawn::ReadValues(const CString& sData, CStringArray& Values)
{
    CString sMutableData(sData);

    Values.RemoveAll();
    sMutableData.TrimLeft();
    sMutableData.TrimRight();

    while (sMutableData.GetLength() > 0) {
        int pos = sMutableData.FindOneOf(",.");
        if (pos >= 0) {
            CString sValue = sMutableData.Left(pos);
            sMutableData = sMutableData.Mid(pos + 1);

            sValue.TrimRight();
            sMutableData.TrimLeft();

            if (sValue.GetLength() > 0) {
                Values.Add(sValue);
            }
        } else {
            Values.Add(sMutableData);
            sMutableData.Empty();
        }
    }

    return Values.GetCount();
}

// 0x769BF0
void CSpawn::Read(CMemINISection* pSection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
    // __LINE__: 900
    UTIL_ASSERT_MSG(pSection != NULL, "Reading spawn data from empty INI file");

    SectionAlias = pSection->GetSectionName();

    Zark();

    CString sValue;
    CMemINIValue* pValue;

    // NOTE: Uninline.
    if (GetINIKey(pSection, SpecKey, sValue)) {
        // TODO: Incomplete.
    } else {
        field_13E = FALSE;
    }

    pValue = pSection->Get(SpecVarKey);
    if (pValue != NULL) {
        mpSearchKeyVar = new CSpawnVar(pValue);
        SpawnFlags |= SPAWN_KEY_CONTROLLED;

        // NOTE: Uninline.
        if (GetINIKey(pSection, SpecVarIncKey, sValue)) {
            field_136 = atoi(sValue);
        } else {
            field_136 = 0;
        }

        // NOTE: Uninline.
        if (GetINIKey(pSection, SpecVarOperationKey, sValue)) {
            if (_strnicmp(GreaterThanKey, sValue, GreaterThanKey.GetLength()) == 0) {
                field_132 = 0;
            } else if (_strnicmp(LessThanKey, sValue, LessThanKey.GetLength()) == 0) {
                field_132 = 1;
            } else if (_strnicmp(EqualToKey, sValue, EqualToKey.GetLength()) == 0) {
                field_132 = 2;
            } else {
                field_132 = 3;
            }
        } else {
            field_132 = 3;
        }
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SpecVarIncKey, sValue)) {
        field_13A = atoi(sValue);
    } else {
        field_13A = 0;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, AreaDiff1Key, sValue)) {
        field_13F = atoi(sValue) > 0;
    } else {
        field_13F = TRUE;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, AreaDiff2Key, sValue)) {
        field_140 = atoi(sValue) > 0;
    } else {
        field_140 = TRUE;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, AreaDiff3Key, sValue)) {
        field_141 = atoi(sValue) > 0;
    } else {
        field_141 = TRUE;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SpecQtyKey, sValue)) {
        if (sValue.FindOneOf(ScopeStr) > 0) {
            mpSearchQtyVar = new CSpawnVar(pSection->Get(SpecQtyKey));
            SpawnFlags |= SPAWN_SEARCH_QTY_GLOBAL;
        } else {
            mSearchQty = atoi(sValue);
        }
    } else {
        mSearchQty = 1;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SpecRegionKey, sValue)) {
        CStringArray Regions;

        mSearchRegion[0] = 0;
        mSearchRegion[1] = 0;
        mSearchRegion[2] = 0;
        mSearchRegion[3] = 0;

        int count = ReadValues(sValue, Regions);

        for (int index = 0; index < Regions.GetCount() && index < 4; index++) {
            mSearchRegion[index] = atoi(Regions[index]);
        }

        switch (count) {
        case 4:
            SpawnFlags |= SPAWN_SEARCH_REGION;
            break;
        case 3:
            SpawnFlags |= SPAWN_SEARCH_RADIUS;
            break;
        case 2:
            mSearchRegion[3] = 1;
            SpawnFlags |= SPAWN_SEARCH_RADIUS;
            break;
        }
    }

    // NOTE: Uninline.
    if (!GetINIKey(pSection, CreFileKey, sValue)) {
        Zark();
        return;
    }

    if (ReadValues(sValue, mCREFiles) < 1) {
        Zark();
        return;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, CreateQtyKey, sValue)) {
        int pos = sValue.FindOneOf(ScopeStr);
        if (pos > 0) {
            mpCreateQtyScope = new CString(sValue.Left(pos));
            mpCreateQtyLabel = new CString(sValue.Mid(pos + ScopeStr.GetLength()));
            SpawnFlags |= SPAWN_QTY_GLOBAL;
        } else {
            mCreateQty = atoi(sValue);
        }
    } else {
        SpawnFlags |= SPAWN_CREATE_SEARCH_QTY;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptNameKey, sValue)) {
        mpScriptName = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, EAKey, sValue)) {
        mEA = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, GeneralKey, sValue)) {
        mGeneral = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, RaceKey, sValue)) {
        mRace = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ClassKey, sValue)) {
        mClass = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, GenderKey, sValue)) {
        mGender = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SpecificsKey, sValue)) {
        mSpecifics = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, AlignmentKey, sValue)) {
        mAlignment = static_cast<BYTE>(atoi(sValue));
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, OverrideScriptKey, sValue)) {
        mpOverrideScript = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptSpecial2Key, sValue)) {
        mpSpecial2Script = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptCombatKey, sValue)) {
        mpCombatScript = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptSpecial3Key, sValue)) {
        mpSpecial3Script = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptMovementKey, sValue)) {
        mpMovementScript = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptSpecial1Key, sValue)) {
        mpSpecial1Script = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ScriptTeamKey, sValue)) {
        mpTeamScript = new CString(sValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DialogFileKey, sValue)) {
        ReadValues(sValue, mDialogFiles);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DeathGoodKey, sValue)) {
        mDeathGoodModifier = atoi(sValue);
        SpawnFlags |= SPAWN_MODIFIES_GOOD;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DeathGoodKey, sValue)) {
        mDeathLawModifier = atoi(sValue);
        SpawnFlags |= SPAWN_MODIFIES_LAW;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DeathLadyKey, sValue)) {
        mDeathLadyModifier = atoi(sValue);
        SpawnFlags |= SPAWN_MODIFIES_LADY;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DeathMurderKey, sValue)) {
        mDeathMurderModifier = atoi(sValue);
        SpawnFlags |= SPAWN_MODIFIES_MURDER;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ObitScripnameKey, sValue)) {
        SpawnFlags |= SPAWN_DEATH_SCRIPTNAME;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ObitFactionKey, sValue)) {
        SpawnFlags |= SPAWN_DEATH_FACTION;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, ObitTeamKey, sValue)) {
        SpawnFlags |= SPAWN_DEATH_TEAM;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, CreatureTimesKey, sValue)) {
        sValue.TrimRight();
        sValue.TrimLeft();
        sValue.MakeLower();

        int timeOfDay = 0;
        int bit = 0;
        for (int pos = min(sValue.GetLength() - 1, 31); pos >= 0; pos--) {
            if (sValue[pos] != '0' && sValue[pos] != 'o') {
                timeOfDay |= 1 << bit;
            }
        }

        mTimeOfDay = timeOfDay;
        SpawnFlags |= SPAWN_TIME_OF_DAY_CHECK;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, FacingKey, sValue)) {
        Facing = atoi(sValue);
        SpawnFlags |= SPAWN_SET_FACING;
    } else {
        Facing = 0;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, PointSelectKey, sValue)) {
        sValue.MakeLower();

        switch (sValue[0]) {
        case 's':
            mPointSelectMode = POINT_SELECT_SEQUENTIAL;
            break;
        case 'i':
            mPointSelectMode = POINT_SELECT_INDEXED_SEQUENTIAL;
            break;
        case 'e':
            mPointSelectMode = POINT_SELECT_EXPLICIT;
            break;
        case 'r':
        default:
            mPointSelectMode = POINT_SELECT_RANDOM_SEQUENTIAL;
            break;
        }
    } else {
        mPointSelectMode = POINT_SELECT_RANDOM_SEQUENTIAL;
    }

    if (mPointSelectMode == POINT_SELECT_EXPLICIT) {
        if (!GetINIKey(pSection, SpawnFromPointVarKey, sValue)) {
            Zark();
            return;
        }

        mpExplicitSpawnPoint = new CSpawnPointVar(pSection->Get(SpawnFromPointVarKey));
        if (mpExplicitSpawnPoint == NULL) {
            Zark();
            return;
        }
    } else {
        if (!GetINIKey(pSection, SpawnPointsKey, sValue)) {
            Zark();
            return;
        }

        if (mSpawnPointArray.Parse(sValue) < 1) {
            Zark();
            return;
        }
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, FacePointVarKey, sValue)) {
        int pos = sValue.FindOneOf(ScopeStr);
        if (pos > 0) {
            pExplicitSpawnFacingScope = new CString(sValue.Left(pos));
            pExplicitSpawnFacingLabel = new CString(sValue.Mid(pos + ScopeStr.GetLength()));
        }
    }

    pValue = pSection->Get(SavePointVarKey);
    if (pValue != NULL) {
        mpSpawnPointStorage = new CSpawnPointVar(pValue);
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SaveFacingVarKey, sValue)) {
        int pos = sValue.FindOneOf(ScopeStr);
        if (pos > 0) {
            pSpawnFacingStorageScope = new CString(sValue.Left(pos));
            pSpawnFacingStorageLabel = new CString(sValue.Mid(pos + ScopeStr.GetLength()));
        }
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, IncrementPointIndexKey, sValue)) {
        SpawnFlags |= SPAWN_INC_POINT_INDEX;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, HoldSelectedPointKey, sValue)) {
        SpawnFlags |= SPAWN_HOLD_SELECTED_POINT;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, PointVarKey, sValue)) {
        int pos = sValue.FindOneOf(ScopeStr);
        pPointIndexScope = new CString(sValue.Left(pos));
        pPointIndexLabel = new CString(sValue.Mid(pos + ScopeStr.GetLength()));
    } else {
        if (mPointSelectMode == POINT_SELECT_INDEXED_SEQUENTIAL) {
            Zark();
            return;
        }
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, CanSeeKey, sValue)) {
        SpawnFlags |= SPAWN_IGNORE_CAN_SEE;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, CanSeeKey, sValue)) {
        SpawnFlags |= SPAWN_CHECK_VIEW_PORT;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, CrowdCheckKey, sValue)) {
        SpawnFlags |= SPAWN_CROWD_CHECK;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, SafeSpotKey, sValue)) {
        SpawnFlags |= SPAWN_FINDSAFESTPOINT;
    }

    // NOTE: Uninline.
    if (GetINIKey(pSection, DontSpawnKey, sValue)) {
        SpawnFlags |= SPAWN_DO_NOTHING;
    }

    DataIsValid = TRUE;
}

// 0x76AD20
int CSpawn::GetSpawnPointIndex()
{
    int value;

    switch (mPointSelectMode) {
    case POINT_SELECT_RANDOM_SEQUENTIAL:
        if (mSpawnPointArray.GetCount() != 0) {
            value = rand() % mSpawnPointArray.GetCount();
        } else {
            value = 0;
        }
        break;
    case POINT_SELECT_INDEXED_SEQUENTIAL:
        if (1) {
            CVariable* pVar = CGameAIBase::GetGlobalVariable(*pPointIndexScope, *pPointIndexLabel, 0);
            int index = pVar->m_intValue;
            if ((SpawnFlags & SPAWN_INC_POINT_INDEX) != 0) {
                pVar->m_intValue = index + 1;
            }
            value = index % mSpawnPointArray.GetCount();
        }
        break;
    default:
        value = mSequentialStartValue++;
        if (mSequentialStartValue > mSpawnPointArray.GetCount() - 1) {
            mSequentialStartValue = 0;
        }
        break;
    }

    return value;
}

// 0x76ADB0
BOOL CSpawn::SelectSpawnPoint(CGameArea* pArea, const CRect& rect, int a3)
{
    if (mPointSelectMode == POINT_SELECT_EXPLICIT) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
        // __LINE__: 1467
        UTIL_ASSERT_MSG(mpExplicitSpawnPoint != NULL, "Cant't reference spawn point var");

        CPoint pt;
        mpExplicitSpawnPoint->GetValue(pArea, pt);
        mSpelectedPoint.SetLocation(pt);

        if (pExplicitSpawnFacingScope != NULL
            && pExplicitSpawnFacingLabel != NULL) {
            CVariable* pFacingVar = CGameAIBase::GetGlobalVariable(*pExplicitSpawnFacingScope,
                *pExplicitSpawnFacingLabel,
                0);
            mSpelectedPoint.SetFacing(pFacingVar->m_intValue & 15);
        } else {
            mSpelectedPoint.SetFacing(0);
        }
        return TRUE;
    }

    int PointCount = mSpawnPointArray.GetCount();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
    // __LINE__: 1484
    UTIL_ASSERT_MSG(PointCount > 0, "No points to spawn to");

    int PointIndex = GetSpawnPointIndex();

    if ((SpawnFlags & SPAWN_FINDSAFESTPOINT) != 0) {
        for (int index = 0; index < PointCount; index++) {
            CSpawnPoint* pPoint = mSpawnPointArray[PointIndex];
            if (pPoint->IsSafeLocation(pArea)) {
                mSpelectedPoint.SetLocation(pPoint->GetLocation());
                mSpelectedPoint.SetFacing(pPoint->GetFacing());
                return TRUE;
            }

            if (++PointIndex >= PointCount) {
                PointIndex = 0;
            }
        }
    }

    for (int index = 0; index < PointCount; index++) {
        CSpawnPoint* pPoint = mSpawnPointArray[PointIndex];
        if (pPoint->IsSafeLocation(pArea)) {
            mSpelectedPoint.SetLocation(pPoint->GetLocation());
            mSpelectedPoint.SetFacing(pPoint->GetFacing());
            return TRUE;
        }

        if (!pPoint->IsVisible(pArea)
            || !pPoint->IsInViewport(pArea)
            || (SpawnFlags & SPAWN_IGNORE_CAN_SEE) != 0) {
            mSpelectedPoint.SetLocation(pPoint->GetLocation());
            mSpelectedPoint.SetFacing(pPoint->GetFacing());
            return TRUE;
        }

        if (++PointIndex >= PointCount) {
            // NOTE: Skipping point at index 0 (fallback value, see below).
            PointIndex = 1;
        }
    }

    if ((SpawnFlags & SPAWN_IGNORE_CAN_SEE) != 0) {
        CSpawnPoint* pPoint = mSpawnPointArray[0];
        mSpelectedPoint.SetLocation(pPoint->GetLocation());
        mSpelectedPoint.SetFacing(pPoint->GetFacing());
    }

    return FALSE;
}

// 0x76B160
int CSpawn::ExecuteSpawn(CGameArea* pArea)
{
    // TODO: Incomplete.

    return 0;
}

// NOTE: Inlined.
BOOL CSpawn::GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue)
{
    if (pSection != NULL) {
        CMemINIValue* pValue = pSection->Get(sKey);
        if (pValue != NULL) {
            sValue = pValue->GetValue();
            return TRUE;
        }
    }
    return FALSE;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CSpawnPoint::CSpawnPoint()
{
    mLocation.x = 0;
    mLocation.y = 0;
    mFacing = 0;
}

// NOTE: Inlined.
CSpawnPoint::CSpawnPoint(const CPoint& pt, int facing)
{
    mLocation = pt;
    mFacing = facing;
}

// 0x769650
CSpawnPoint::~CSpawnPoint()
{
}

// 0x76BCD0
BOOL CSpawnPoint::IsVisible(CGameArea* pArea)
{
    // NOTE: Uninline.
    LONG nIndex = pArea->m_visibility.PointToTile(mLocation);

    return pArea->m_visibility.IsTileVisible(nIndex);
}

// 0x76BD20
BOOL CSpawnPoint::IsInViewport(CGameArea* pArea)
{
    CRect r;
    r.left = pArea->GetInfinity()->nCurrentX;
    r.top = pArea->GetInfinity()->nCurrentY;
    r.right = r.left + pArea->GetInfinity()->rViewPort.Width();
    r.bottom = r.top + pArea->GetInfinity()->rViewPort.Height();

    return r.PtInRect(mLocation);
}

// NOTE: Inlined.
BOOL CSpawnPoint::IsSafeLocation(CGameArea* pArea)
{
    return !IsVisible(pArea) && !IsInViewport(pArea);
}

// -----------------------------------------------------------------------------

// 0x7696A0
CSpawnPointArray::~CSpawnPointArray()
{
    Zark();
}

// 0x76BD90
int CSpawnPointArray::Parse(const CString& sData)
{
    // NOTE: Uninline.
    Zark();

    CString sMutableString(sData);
    int count = 0;
    CPoint pt;
    int facing;

    sMutableString.TrimLeft();
    sMutableString.TrimRight();

    while (sMutableString.GetLength() > 0) {
        int openPos = sMutableString.Find('[');
        int closePos = sMutableString.Find(']');
        if (openPos >= 0 && closePos >= 0) {
            CString sPoint = sMutableString.Mid(openPos + 1, closePos - openPos - 1);

            int semicolonPos = sPoint.ReverseFind(':');
            if (semicolonPos >= 0) {
                if (semicolonPos != sPoint.GetLength() - 1) {
                    facing = atoi(sPoint.Mid(semicolonPos + 1));
                } else {
                    facing = 0;
                }
                sPoint = sPoint.Left(semicolonPos);
            } else {
                facing = mDefaultFacing;
            }

            int separatorPos = sPoint.FindOneOf(",.");
            if (separatorPos > 0 && separatorPos < sPoint.GetLength() - 1) {
                pt.x = atoi(sPoint.Left(separatorPos));
                pt.y = atoi(sPoint.Mid(separatorPos + 1));
                Add(new CSpawnPoint(pt, facing));
            }

            sMutableString = sMutableString.Mid(closePos + 1);
        } else {
            sMutableString.Empty();
        }
    }

    return count;
}

// NOTE: Inlined.
void CSpawnPointArray::Zark()
{
    for (int index = 0; index < GetCount(); index++) {
        CSpawnPoint* pPoint = GetAt(index);
        if (pPoint != NULL) {
            delete pPoint;
        }
    }
    RemoveAll();

    // FIXME: One time is enough.
    RemoveAll();
}

// -----------------------------------------------------------------------------

// 0x76C010
CSpawnVar::CSpawnVar(CMemINIValue* pValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
    // __LINE__: 1954
    UTIL_ASSERT_MSG(pValue != NULL, "CSpawnVar - Bad value pointer");

    // FIXME: Odd naming.
    CString Buffer = pValue->GetValue();
    int ScopeSeq = Buffer.FindOneOf(ScopeStr);

    if (ScopeSeq > 0) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Spawn.cpp
        // __LINE__: 1961
        UTIL_ASSERT_MSG((ScopeSeq + ScopeStr.GetLength()) < (Buffer.GetLength() - 1), "Bad var specified in spawn data");

        mScope = Buffer.Left(ScopeSeq);
        mLabel = Buffer.Mid(ScopeSeq + ScopeStr.GetLength());
    } else {
        mScope = "GLOBAL";
        mLabel = Buffer;
    }

    // NOTE: Unused.
    CGameAIBase::GetGlobalVariable(mScope, mLabel, 0);
}

// NOTE: Inlined.
CSpawnVar::CSpawnVar(const CString& sScope, const CString& sLabel)
{
    mScope = sScope;
    mLabel = sLabel;
}

// 0x768F50
CSpawnVar::~CSpawnVar()
{
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CSpawnPointVar::CSpawnPointVar(CMemINIValue* pValue)
    : CSpawnVar(pValue)
{
}

// 0x76C220
CSpawnPointVar::~CSpawnPointVar()
{
}

// NOTE: Inlined.
int CSpawnPointVar::GetValue(CGameArea* pArea, CPoint& pt) const
{
    CVariable* pVar = CGameAIBase::GetGlobalVariable(mScope, mLabel, 0);
    if (pVar != NULL) {
        int value = pVar->m_intValue;
        pt.x = (value >> 16) & 0xFFFF;
        pt.y = value & 0xFFFF;
        return value;
    } else {
        pt.x = 0;
        pt.y = 0;
        return 0;
    }
}

// -----------------------------------------------------------------------------

// 0x76C180 (CString)
// 0x76C1B0 (CSpawnPointVar)
template <class Thing>
void _SpawnReleasePointer(Thing*& rPointer)
{
    if (rPointer != NULL) {
        delete rPointer;
        rPointer = NULL;
    }
}

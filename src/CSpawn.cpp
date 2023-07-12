#include "CSpawn.h"

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

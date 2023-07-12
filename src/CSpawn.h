#ifndef CSPAWN_H_
#define CSPAWN_H_

#include "mfc.h"

class CSpawnFile {
public:
    static const CString EventListKey;
    static const CString MainSectionKey;
    static const CString ExitEventKey;
    static const CString EnterEventKey;
};

class CSpawnList {
public:
    static const CString IntervalKey;
    static const CString AliasListKey;
    static const CString ControlKey;
    static const CString SpawnTimesKey;
};

class CSpawn {
public:
    static const CString SpecVarKey;
    static const CString SpecKey;
    static const CString SpecRegionKey;
    static const CString SpecQtyKey;
    static const CString SpecVarIncKey;
    static const CString SpecVarValueKey;
    static const CString SpecVarOperationKey;
    static const CString GreaterThanKey;
    static const CString LessThanKey;
    static const CString EqualToKey;
    static const CString NotEqualToKey;
    static const CString AreaDiff1Key;
    static const CString AreaDiff2Key;
    static const CString AreaDiff3Key;
    static const CString CreFileKey;
    static const CString CreateQtyKey;
    static const CString ScriptNameKey;
    static const CString EAKey;
    static const CString GeneralKey;
    static const CString RaceKey;
    static const CString ClassKey;
    static const CString GenderKey;
    static const CString SpecificsKey;
    static const CString AlignmentKey;
    static const CString FactionKey;
    static const CString TeamKey;
    static const CString OverrideScriptKey;
    static const CString ScriptSpecial1Key;
    static const CString ScriptTeamKey;
    static const CString ScriptSpecial2Key;
    static const CString ScriptCombatKey;
    static const CString ScriptSpecial3Key;
    static const CString ScriptMovementKey;
    static const CString DialogFileKey;
    static const CString DeathGoodKey;
    static const CString DeathLawKey;
    static const CString DeathLadyKey;
    static const CString DeathMurderKey;
    static const CString ObitScripnameKey;
    static const CString ObitFactionKey;
    static const CString ObitTeamKey;
    static const CString SpawnPointsKey;
    static const CString PointSelectKey;
    static const CString PointVarKey;
    static const CString FacingKey;
    static const CString CanSeeKey;
    static const CString CrowdCheckKey;
    static const CString SafeSpotKey;
    static const CString SavePointVarKey;
    static const CString SaveFacingVarKey;
    static const CString SpawnFromPointVarKey;
    static const CString FacePointVarKey;
    static const CString IncrementPointIndexKey;
    static const CString HoldSelectedPointKey;
    static const CString ViewPortKey;
    static const CString DontSpawnKey;
    static const CString CreatureTimesKey;
};

#endif /* CSPAWN_H_ */

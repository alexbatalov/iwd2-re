#ifndef CSPAWN_H_
#define CSPAWN_H_

#include "mfc.h"

// NOTE: This unit has odd naming convention, inconsistent with other codebase.

class CGameArea;
class CMemINI;
class CMemINISection;
class CMemINIValue;

enum {
    SPAWN_KEY_CONTROLLED = 0x1,
    SPAWN_SEARCH_QTY_GLOBAL = 0x2,
    SPAWN_SEARCH_REGION = 0x4,
    SPAWN_SEARCH_RADIUS = 0x8,
    SPAWN_QTY_GLOBAL = 0x10,
    SPAWN_SET_SCRIPTNAME = 0x20,
    SPAWN_CREATE_SEARCH_QTY = 0x40,
    SPAWN_MODIFIES_GOOD = 0x400,
    SPAWN_MODIFIES_LAW = 0x800,
    SPAWN_MODIFIES_LADY = 0x1000,
    SPAWN_MODIFIES_MURDER = 0x2000,
    SPAWN_DEATH_SCRIPTNAME = 0x4000,
    SPAWN_DEATH_FACTION = 0x8000,
    SPAWN_DEATH_TEAM = 0x10000,
    SPAWN_SET_FACING = 0x20000,
    SPAWN_IGNORE_CAN_SEE = 0x40000,
    SPAWN_CHECK_VIEW_PORT = 0x80000,
    SPAWN_CROWD_CHECK = 0x100000,
    SPAWN_FINDSAFESTPOINT = 0x200000,
    SPAWN_INC_POINT_INDEX = 0x400000,
    SPAWN_HOLD_SELECTED_POINT = 0x800000,
    SPAWN_DO_NOTHING = 0x1000000,
    SPAWN_TIME_OF_DAY_CHECK = 0x2000000,
};

enum {
    SPAWN_DEFAULT_RADIUS = 1,
    SPAWN_POINT_REGION_ELEMENTS = 2,
    SPAWN_RADIUS_REGION_ELEMENT = 3,
    SPAWN_RECTANGULAR_REGION_ELEMENTS = 4,
};

enum {
    POINT_SELECT_RANDOM_SEQUENTIAL = 0,
    POINT_SELECT_SEQUENTIAL = 1,
    POINT_SELECT_INDEXED_SEQUENTIAL = 2,
    POINT_SELECT_EXPLICIT = 3,
};

class CSpawnVar {
public:
    CSpawnVar(CMemINIValue* pValue);
    CSpawnVar(const CString& sScope, const CString& sLabel);
    ~CSpawnVar();

    /* 0000 */ CString mScope;
    /* 0004 */ CString mLabel;
};

class CSpawnPointVar : public CSpawnVar {
public:
    CSpawnPointVar(CMemINIValue* pValue);
    ~CSpawnPointVar();
    int GetValue(CGameArea* pArea, CPoint& pt) const;
};

class CSpawnPoint {
public:
    CSpawnPoint();
    CSpawnPoint(const CPoint& pt, int facing);
    virtual ~CSpawnPoint();
    void SetLocation(const CPoint& pt) { mLocation = pt; }
    void SetFacing(int facing) { mFacing = facing; }
    const CPoint& GetLocation() const { return mLocation; }
    int GetFacing() const { return mFacing; }
    BOOL IsVisible(CGameArea* pArea);
    BOOL IsInViewport(CGameArea* pArea);
    BOOL IsSafeLocation(CGameArea* pArea);

protected:
    /* 0004 */ CPoint mLocation;
    /* 000C */ int mFacing;
};

class CSpawnPointArray : public CTypedPtrArray<CPtrArray, CSpawnPoint*> {
public:
    ~CSpawnPointArray() override;
    void Zark();
    int Parse(const CString& sData);
    int GetDefaultFacing() const { return mDefaultFacing; }
    void SetDefaultFacing(int facing) { mDefaultFacing = facing; }

protected:
    /* 0014 */ int mDefaultFacing;
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

    CSpawn(CMemINISection* pSection);
    virtual ~CSpawn();
    int ExecuteSpawn(CGameArea* pArea);
    BOOL GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue);
    BOOL GetINIKey(CMemINISection* pSection, const CString& sKey, int& nValue);
    int ReadValues(const CString& sValue, CStringArray& Values);
    void Read(CMemINISection* pSection);
    void InitPointers();
    void Zark();
    int GetSpawnPointIndex();
    BOOL SelectSpawnPoint(CGameArea* pArea, const CRect& rect, int a3);

    /* 0004 */ int mInterval;
    /* 0008 */ CString SectionAlias;
    /* 000C */ int SpawnFlags;
    /* 0010 */ BOOL DataIsValid;
    /* 0050 */ int mSearchQty;
    /* 0054 */ int mSearchRegion[4];
    /* 0064 */ CSpawnVar* mpSearchKeyVar;
    /* 0068 */ CSpawnVar* mpSearchQtyVar;
    /* 006C */ CStringArray mCREFiles;
    /* 0080 */ int mCreateQty;
    /* 0084 */ CString* mpCreateQtyScope;
    /* 0088 */ CString* mpCreateQtyLabel;
    /* 008C */ CString* mpScriptName;
    /* 0090 */ BYTE mEA;
    /* 0091 */ BYTE mGeneral;
    /* 0092 */ BYTE mRace;
    /* 0093 */ BYTE mClass;
    /* 0094 */ BYTE mGender;
    /* 0095 */ BYTE mSpecifics;
    /* 0096 */ BYTE mFaction;
    /* 0097 */ BYTE mTeam;
    /* 0098 */ BYTE mAlignment;
    /* 009A */ CString* mpOverrideScript;
    /* 009E */ CString* mpSpecial1Script;
    /* 00A2 */ CString* mpTeamScript;
    /* 00A6 */ CString* mpSpecial2Script;
    /* 00AA */ CString* mpCombatScript;
    /* 00AE */ CString* mpSpecial3Script;
    /* 00B2 */ CString* mpMovementScript;
    /* 00B6 */ CStringArray mDialogFiles;
    /* 00CA */ int mDeathGoodModifier;
    /* 00CE */ int mDeathLawModifier;
    /* 00D2 */ int mDeathLadyModifier;
    /* 00D6 */ int mDeathMurderModifier;
    /* 00DA */ int Facing;
    /* 00DE */ CSpawnPointArray mSpawnPointArray;
    /* 00F6 */ CSpawnPoint mSpelectedPoint;
    /* 0106 */ int mPointSelectMode;
    /* 010A */ CString* pPointIndexScope;
    /* 010E */ CString* pPointIndexLabel;
    /* 0112 */ CSpawnPointVar* mpExplicitSpawnPoint;
    /* 0116 */ CString* pExplicitSpawnFacingScope;
    /* 011A */ CString* pExplicitSpawnFacingLabel;
    /* 011E */ CSpawnPointVar* mpSpawnPointStorage;
    /* 0122 */ CString* pSpawnFacingStorageScope;
    /* 0126 */ CString* pSpawnFacingStorageLabel;
    /* 012A */ int mSequentialStartValue;
    /* 012E */ DWORD mTimeOfDay;
    /* 0132 */ int field_132;
    /* 0136 */ int field_136;
    /* 013A */ int field_13A;
    /* 013E */ BOOLEAN field_13E;
    /* 013F */ BOOLEAN field_13F;
    /* 0140 */ BOOLEAN field_140;
    /* 0141 */ BOOLEAN field_141;
};

class CSpawnList : public CTypedPtrList<CPtrList, CSpawn*> {
public:
    static const CString IntervalKey;
    static const CString AliasListKey;
    static const CString ControlKey;
    static const CString SpawnTimesKey;

    CSpawnList(CMemINI* pMemINI, const CString& sSection);
    ~CSpawnList() override;
    int ParseData(const CString& sData, CStringArray& Sections);
    int Execute(CGameArea* pArea, BOOL bForce);

    BOOL GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue);

    /* 001C */ CString mSectionAlias;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ int field_28;
    /* 002C */ BOOL CheckSpawnTimes;
    /* 0030 */ DWORD SpawnTimeOfDay;
    /* 0034 */ unsigned int mInterval;
    /* 0038 */ CSpawnVar* pControlVar;
};

class CSpawnFile : public CTypedPtrList<CPtrList, void*> {
public:
    static const CString EventListKey;
    static const CString MainSectionKey;
    static const CString ExitEventKey;
    static const CString EnterEventKey;

    CSpawnFile(CMemINI* pMemINI);
    ~CSpawnFile() override;
    int Execute(CGameArea* pArea);
    int ExitSpawn(CGameArea* pArea);
    int EnterSpawn(CGameArea* pArea);
    int ParseData(const CString& sData, CStringArray& Sections);

    BOOL GetINIKey(CMemINISection* pSection, const CString& sKey, CString& sValue);

    /* 001C */ CSpawnList* mpExitList;
    /* 0020 */ CSpawnList* mpEnterList;
    /* 0024 */ BOOL m_bInSpawn;
};

#endif /* CSPAWN_H_ */

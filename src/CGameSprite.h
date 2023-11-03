#ifndef CGAMESPRITE_H_
#define CGAMESPRITE_H_

#include "CAIObjectType.h"
#include "CButtonData.h"
#include "CDerivedStats.h"
#include "CGameAIBase.h"
#include "CGameAnimation.h"
#include "CGameEffectList.h"
#include "CGameSpriteEquipment.h"
#include "CGameSpriteSpells.h"
#include "CGameStatsSprite.h"
#include "CMarker.h"
#include "CResRef.h"
#include "CSound.h"
#include "CStrRes.h"
#include "CVidCell.h"
#include "FileFormat.h"

// SEQUENCE.IDS

#define CGAMESPRITE_SEQ_ATTACK 0
#define CGAMESPRITE_SEQ_AWAKE 1
#define CGAMESPRITE_SEQ_CAST 2
#define CGAMESPRITE_SEQ_CONJURE 3
#define CGAMESPRITE_SEQ_DAMAGE 4
#define CGAMESPRITE_SEQ_DIE 5
#define CGAMESPRITE_SEQ_HEAD_TURN 6
#define CGAMESPRITE_SEQ_READY 7
#define CGAMESPRITE_SEQ_SHOOT 8
#define CGAMESPRITE_SEQ_TWITCH 9
#define CGAMESPRITE_SEQ_WALK 10
#define CGAMESPRITE_SEQ_ATTACK_SLASH 11
#define CGAMESPRITE_SEQ_ATTACK_BACKSLASH 12
#define CGAMESPRITE_SEQ_ATTACK_JAB 13
#define CGAMESPRITE_SEQ_EMERGE 14
#define CGAMESPRITE_SEQ_HIDE 15
#define CGAMESPRITE_SEQ_SLEEP 17

#define CGAMESPRITE_FEAT_AEGIS_OF_RIME 0
#define CGAMESPRITE_FEAT_AMBIDEXTERITY 1
#define CGAMESPRITE_FEAT_AQUA_MORTIS 2
#define CGAMESPRITE_FEAT_ARMOR_PROF 3
#define CGAMESPRITE_FEAT_ARMORED_ARCANA 4
#define CGAMESPRITE_FEAT_ARTERIAL_STRIKE 5
#define CGAMESPRITE_FEAT_BLIND_FIGHT 6
#define CGAMESPRITE_FEAT_BULLHEADED 7
#define CGAMESPRITE_FEAT_CLEAVE 8
#define CGAMESPRITE_FEAT_COMBAT_CASTING 9
#define CGAMESPRITE_FEAT_COURTEOUS_MAGOCRACY 10
#define CGAMESPRITE_FEAT_CRIPPLING_STRIKE 11
#define CGAMESPRITE_FEAT_DASH 12
#define CGAMESPRITE_FEAT_DEFLECT_ARROWS 13
#define CGAMESPRITE_FEAT_DIRTY_FIGHTING 14
#define CGAMESPRITE_FEAT_DISCIPLINE 15
#define CGAMESPRITE_FEAT_DODGE 16
#define CGAMESPRITE_FEAT_ENVENOM_WEAPON 17
#define CGAMESPRITE_FEAT_EXOTIC_BASTARD 18
#define CGAMESPRITE_FEAT_EXPERTISE 19
#define CGAMESPRITE_FEAT_EXTRA_RAGE 20
#define CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING 21
#define CGAMESPRITE_FEAT_EXTRA_SMITING 22
#define CGAMESPRITE_FEAT_EXTRA_TURNING 23
#define CGAMESPRITE_FEAT_FIENDSLAYER 24
#define CGAMESPRITE_FEAT_FORESTER 25
#define CGAMESPRITE_FEAT_GREAT_FORTITUDE 26
#define CGAMESPRITE_FEAT_HAMSTRING 27
#define CGAMESPRITE_FEAT_HERETICS_BANE 28
#define CGAMESPRITE_FEAT_HEROIC_INSPIRATION 29
#define CGAMESPRITE_FEAT_IMPROVED_CRITICAL 30
#define CGAMESPRITE_FEAT_IMPROVED_EVASION 31
#define CGAMESPRITE_FEAT_IMPROVED_INITIATIVE 32
#define CGAMESPRITE_FEAT_IMPROVED_TURNING 33
#define CGAMESPRITE_FEAT_IRON_WILL 34
#define CGAMESPRITE_FEAT_LIGHTNING_REFLEXES 35
#define CGAMESPRITE_FEAT_LINGERING_SONG 36
#define CGAMESPRITE_FEAT_LUCK_OF_HEROES 37
#define CGAMESPRITE_FEAT_MARTIAL_AXE 38
#define CGAMESPRITE_FEAT_MARTIAL_BOW 39
#define CGAMESPRITE_FEAT_MARTIAL_FLAIL 40
#define CGAMESPRITE_FEAT_MARTIAL_GREATSWORD 41
#define CGAMESPRITE_FEAT_MARTIAL_HAMMER 42
#define CGAMESPRITE_FEAT_MARTIAL_LARGESWORD 43
#define CGAMESPRITE_FEAT_MARTIAL_POLEARM 44
#define CGAMESPRITE_FEAT_MAXIMIZED_ATTACKS 45
#define CGAMESPRITE_FEAT_MERCANTILE_BACKGROUND 46
#define CGAMESPRITE_FEAT_POWER_ATTACK 47
#define CGAMESPRITE_FEAT_PRECISE_SHOT 48
#define CGAMESPRITE_FEAT_RAPID_SHOT 49
#define CGAMESPRITE_FEAT_RESIST_POISON 50
#define CGAMESPRITE_FEAT_SCION_OF_STORMS 51
#define CGAMESPRITE_FEAT_SHIELD_PROF 52
#define CGAMESPRITE_FEAT_SIMPLE_CROSSBOW 53
#define CGAMESPRITE_FEAT_SIMPLE_MACE 54
#define CGAMESPRITE_FEAT_SIMPLE_MISSILE 55
#define CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF 56
#define CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE 57
#define CGAMESPRITE_FEAT_SLIPPERY_MIND 58
#define CGAMESPRITE_FEAT_SNAKE_BLOOD 59
#define CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT 60
#define CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION 61
#define CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY 62
#define CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE 63
#define CGAMESPRITE_FEAT_SPELL_PENETRATION 64
#define CGAMESPRITE_FEAT_SPIRIT_OF_FLAME 65
#define CGAMESPRITE_FEAT_STRONG_BACK 66
#define CGAMESPRITE_FEAT_STUNNING_FIST 67
#define CGAMESPRITE_FEAT_SUBVOCAL_CASTING 68
#define CGAMESPRITE_FEAT_TOUGHNESS 69
#define CGAMESPRITE_FEAT_TWO_WEAPON_FIGHTING 70
#define CGAMESPRITE_FEAT_WEAPON_FINESSE 71
#define CGAMESPRITE_FEAT_WILDSHAPE_BOAR 72
#define CGAMESPRITE_FEAT_WILDSHAPE_PANTHER 73
#define CGAMESPRITE_FEAT_WILDSHAPE_SHAMBLER 74
#define CGAMESPRITE_FEAT_NUMFEATS 75

#define CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE 2
#define CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE 3
#define CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE 2
#define CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE 2
#define CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE 2
#define CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE 2
#define CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE 2
#define CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL 5

#define CGAMESPRITE_SKILL_ALCHEMY 0
#define CGAMESPRITE_SKILL_ANIMAL_EMPATHY 1
#define CGAMESPRITE_SKILL_BLUFF 2
#define CGAMESPRITE_SKILL_CONCENTRATION 3
#define CGAMESPRITE_SKILL_DIPLOMACY 4
#define CGAMESPRITE_SKILL_DISABLE_DEVICE 5
#define CGAMESPRITE_SKILL_HIDE 6
#define CGAMESPRITE_SKILL_INTIMIDATE 7
#define CGAMESPRITE_SKILL_KNOWLEDGE_ARCANA 8
#define CGAMESPRITE_SKILL_MOVE_SILENTLY 9
#define CGAMESPRITE_SKILL_OPEN_LOCK 10
#define CGAMESPRITE_SKILL_PICK_POCKET 11
#define CGAMESPRITE_SKILL_SEARCH 12
#define CGAMESPRITE_SKILL_SPELLCRAFT 13
#define CGAMESPRITE_SKILL_USE_MAGIC_DEVICE 14
#define CGAMESPRITE_SKILL_WILDERNESS_LORE 15
#define CGAMESPRITE_SKILL_NUMSKILLS 16

class CSearchRequest;
class CUIControlBase;
class CUIControlTextDisplay;
class CVariableHash;

class CGameSprite : public CGameAIBase {
public:
    static const BYTE DIR_S;
    static const BYTE DIR_SW;
    static const BYTE DIR_W;
    static const BYTE DIR_NW;
    static const BYTE DIR_N;
    static const BYTE DIR_NE;
    static const BYTE DIR_E;
    static const BYTE DIR_SE;
    static const BYTE DIR_SSW;
    static const BYTE DIR_SWW;
    static const BYTE DIR_NWW;
    static const BYTE DIR_NNW;
    static const BYTE DIR_NNE;
    static const BYTE DIR_NEE;
    static const BYTE DIR_SEE;
    static const BYTE DIR_SSE;
    static const BYTE NUM_DIR;

    static const BYTE SOUND_SELECT_ACTION;
    static const BYTE SOUND_REACT_TO_DEATH;
    static const SHORT EXACT_SCALE;

    static const SHORT USER_OVERRIDE_COUNT;

    static const BYTE SEQ_ATTACK;
    static const BYTE SEQ_AWAKE;
    static const BYTE SEQ_CAST;
    static const BYTE SEQ_CONJURE;
    static const BYTE SEQ_DAMAGE;
    static const BYTE SEQ_DIE;
    static const BYTE SEQ_EMERGE;
    static const BYTE SEQ_HEAD_TURN;
    static const BYTE SEQ_HIDE;
    static const BYTE SEQ_READY;
    static const BYTE SEQ_SHOOT;
    static const BYTE SEQ_SLEEP;
    static const BYTE SEQ_TWITCH;
    static const BYTE SEQ_WALK;

    static const LONG STANDARD_VERBAL_CONSTANT_LENGTH;

    static const CPoint PORTRAIT_ICON_SIZE;
    static const CResRef SPIN110;
    static const CResRef SPIN111;
    static const CResRef SPIN107;
    static const CResRef SPIN141;
    static const CResRef SPIN142;
    static const CResRef SPIN143;
    static const CResRef SPIN244;
    static const CResRef SPIN245;
    static const CResRef SPIN246;
    static const CResRef SPIN108;
    static const CResRef SPIN109;
    static const CResRef SPIN120;
    static const CResRef SPIN121;
    static const CResRef SPIN125;
    static const CResRef SPIN139;
    static const CResRef SPIN152;
    static const CResRef SPIN275;
    static const CResRef SPIN276;
    static const CResRef SPIN277;
    static const CResRef SPIN278;
    static const CResRef SPIN279;
    static const CResRef SPIN970;
    static const CResRef SPIN197;
    static const CResRef SPPR327;
    static const CResRef SPPR328;
    static const CResRef SPPR429;
    static const CResRef SPIN198;
    static const CResRef SPIN199;
    static const CResRef SPIN200;
    static const CResRef SPIN243;
    static const CResRef SPIN201;
    static const CResRef SPIN202;
    static const CResRef SPIN203;
    static const CResRef SPIN247;
    static const CResRef SPIN204;
    static const CResRef SPIN205;
    static const CResRef SPIN206;
    static const CResRef SPIN207;
    static const CResRef SPIN208;
    static const CResRef SPIN209;
    static const CResRef SPIN210;
    static const CResRef SPIN231;
    static const CResRef SPIN191;
    static const CResRef SPIN211;
    static const CResRef SPIN212;
    static const CResRef SPIN213;
    static const CResRef SPIN214;
    static const CResRef SPIN215;
    static const CResRef SPIN216;
    static const CResRef SPIN217;
    static const CResRef SPIN218;
    static const CResRef SPIN229;
    static const CResRef SPIN232;
    static const CResRef SPIN233;
    static const CResRef SPIN234;
    static const CResRef SPIN235;
    static const CResRef SPIN236;
    static const CResRef SPIN260;
    static const CString FA;
    static const CString GA;
    static const CString RA;
    static const CString AP;
    static const CResRef SPWI110;
    static const CResRef SPIN122;
    static const CResRef SPIN285;

    static BOOLEAN SHOW_CHARACTER_HP;
    static BOOLEAN GRAVITY_IS_DOWN;

    CGameSprite(BYTE* pCreature, LONG creatureSize, int a3, WORD type, DWORD expirationTime, WORD huntingRange, WORD followRange, DWORD timeOfDayVisible, CPoint startPos, WORD facing);
    /* 0014 */ LONG GetTargetId() override;
    /* 0038 */ BOOL DoesIntersect(CRect r);
    /* 003C */ BOOL OnSearchMap() override;
    /* 0044 */ void OnFormationButton(const CPoint& pt) override;
    /* 007C */ void ClearAI(BOOLEAN bSetSequence) override;
    /* 009C */ const BYTE* GetVisibleTerrainTable() override;
    /* 00A0 */ const BYTE* GetTerrainTable() override;
    /* 00B4 */ BOOL GetCanSeeInvisible() override;
    /* 00BC */ virtual void SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart);
    /* 00C0 */ virtual void ResetAITypeLive();
    /* 00C4 */ virtual void ResetAIType();

    void DropPath();
    void DropSearchRequest();
    void OnLightningStrike();
    void MakeGlobal();
    SHORT GetNumSounds(SHORT nOffset, SHORT nMaxNum);
    void PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption);
    void VerbalConstant(LONG verbalConstant);
    LONG GetLength(LONG verbalConstant);
    BOOL IsSpellSchool(BYTE spellSchool);
    void SetFootstepChannel();
    BYTE GetSound(BYTE soundID);
    void RenderMarkers(CVidMode* pVidMode, int a2);
    void RenderPortrait(const CPoint& cpRenderPosition, const CSize& szControl, BOOL bPressed, BOOL reorderHighlight, BOOL selectFromMarker, const CRect& rClip, BOOL bDoubleSize);
    void RenderToMapScreen(const CRect& rClipBase, const CPoint& ptCharPos);
    void Select();
    void Unselect();
    void SetCharacterToolTip(CUIControlBase* pControl);
    void SetDirection(const CPoint& posDest);
    void SetDirection(SHORT direction);
    void SetIdleSequence();
    SHORT GetIdleSequence();
    void SetSequence(SHORT nSequence);
    void RenderDamageArrow(CGameArea* pArea, CVidMode* pVidMode, INT nSurface);
    void Unmarshal(BYTE* pCreature, LONG creatureSize, WORD facing, int a4);
    void UnmarshalScripts();
    void FetchCommonStrings();
    void LoadAreaInformation(CAreaFileCreature* pCreature);
    BYTE GetChannel();
    CItem* GetLauncher(const ITEM_ABILITY* ability, SHORT& launcherSlot);
    void UnequipAll(BOOL a1);
    void EquipAll(BOOL a1);
    void Equip(SHORT slotNum);
    void Unequip(SHORT slotNum);
    SHORT GetTurnUndeadLevel();
    SHORT GetBackstabDamageMultiplier();
    SHORT GetLayOnHandsAmount();
    INT GetNumQuickWeaponSlots();
    SHORT FindItemPersonal(const CString& sName, int number, BOOL restrictToEquiped);
    DWORD GetCarriedWeight();
    void AddKnownDivineSpells(const BYTE& nClass);
    void GetNumInventoryPersonalSlots(INT& nUsedSlots, INT& nTotalSlots);
    void SetModalState(BYTE modalState, BOOL bUpdateToolbar);
    void CheckSequence(BYTE& sequence);
    BOOL HaveUnexportableItems();
    void SetMonkAbilities();
    LONG GetLevel();
    void sub_723BF0(BOOLEAN a1, BOOLEAN a2);
    INT GetAC();
    INT sub_723F60();
    void sub_72DE60();
    void sub_71E760(CDerivedStats& DStats, int a2);
    int sub_71F6E0();
    const CString& GetName();
    STRREF GetNameRef();
    BOOL Orderable(BOOL bIgnoreControl);
    DWORD GetSpecialization();
    BOOL ProcessEffectList();
    void ClearStoredPaths();
    void ClearDialogActions();
    BOOL HandleEffects();
    SHORT GetCriticalHitBonus();
    SHORT LeaveParty();
    void SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4);
    SHORT FindTraps();
    SHORT Turn();
    BOOL HasClassMask(DWORD dwMask);
    INT GetClassLevel(INT iClassType);
    void SetClassLevel(INT iClassType, INT nLevel);
    BOOL HasClassLevel(INT iClassType);
    void SetFeatValue(UINT nFeatNumber, INT iFeatValue);
    INT GetFeatValue(UINT nFeatNumber);
    INT GetMaxFeatValue(UINT nFeatNumber);
    BOOL sub_763150(UINT nFeatNumber);
    BOOL sub_763200(UINT nFeatNumber, INT a2);
    BOOL sub_763A40(UINT nFeatNumber, INT a2);
    int GetExtraFeats(BYTE nClass);
    int GetExtraSkillPoints(BYTE nClass);
    void SetSkillValue(UINT iSkillNumber, INT iSkillValue);
    INT GetSkillValue(UINT iSkillNumber);
    INT GetSkillCost(UINT iSkillNumber, BYTE nClass);
    INT GetEffectiveCharacterLevel();
    INT GetRacialFavoredClass(DWORD& nSpecialization);
    INT GetMulticlassingPenalty();
    void DisplayFeats(CUIControlTextDisplay* pText);
    void DisplaySkills(CUIControlTextDisplay* pText);
    void MoveOntoArea(CGameArea* pArea, const CPoint& dest, SHORT facingDirection);

    void SetResRef(const CResRef& resRef);
    CCreatureFileHeader* GetBaseStats();
    CDerivedStats* GetDerivedStats();
    CGameEffectList* GetEquipedEffectList();
    CGameEffectList* GetTimedEffectList();
    void AddPortraitIcon(int icon);
    void RemovePortraitIcon(int icon);
    CGameSpriteSpellList* GetInnateSpells();
    CGameSpriteSpellList* GetSongs();
    CGameSpriteSpellList* GetShapeshifts();

    CGameAnimation* GetAnimation();
    CGameSpriteEquipment* GetEquipment();
    SHORT GetHappiness();

    INT GetNextHatedRacesSlot();
    BOOL sub_724690(SHORT a1);

    // NOTE: See `CGameSpriteSpells` for explanation of the overall ugliness of
    // the following functions.

    CGameSpriteGroupedSpellList* GetSpells(const BYTE& nClass);
    CGameSpriteSpellList* GetSpellsAtLevel(const BYTE& nClass, const UINT& nLevel);
    UINT GetNumSpells();
    BOOLEAN sub_724900();
    BOOLEAN sub_724920();
    BOOLEAN AddKnownSpell(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5, const unsigned int& a6);
    BOOLEAN AddDomainSpell(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN AddInnateSpell(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN AddSong(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN AddShapeshift(const CResRef& resRef, const unsigned int& a2);
    BOOLEAN sub_724C40(const unsigned int& a1);
    BOOLEAN RemoveKnownSpell(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5, const unsigned int& a6);
    BOOLEAN RemoveDomainSpell(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN RemoveInnateSpell(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN RemoveSong(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN RemoveShapeshift(const CResRef& resRef);
    BOOLEAN sub_724FD0(const BYTE& nClass, const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN sub_725110(const UINT& nSpellLevel, const CResRef& resRef, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN sub_725210(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3);
    BOOLEAN sub_725270(const CResRef& resRef, const unsigned int& a2, const unsigned int& a3);
    BOOLEAN sub_725330(const CResRef& resRef, const DWORD& dwClassMask, UINT nLevel, BOOLEAN a4);
    BOOLEAN sub_7256B0(const CResRef& resRef, const UINT& nLevel, BOOLEAN a3);
    BOOLEAN sub_725840(const CResRef& resRef, BOOLEAN a2);

    INT sub_726270(UINT nFeatNumber);

    /* 0598 */ CResRef m_resRef;
    /* 05A0 */ CString m_sName;
    /* 05A4 */ CCreatureFileHeader m_baseStats;
    /* 0920 */ CDerivedStats m_derivedStats;
    /* 1778 */ CDerivedStats m_tempStats;
    /* 25D0 */ CDerivedStats m_bonusStats;
    /* 342C */ CButtonData field_342C[8];
    /* 360C */ CButtonData field_360C[9];
    /* 3828 */ CButtonData field_3828[3];
    /* 38DC */ CButtonData field_38DC[9];
    /* 3AF8 */ CButtonData field_3AF8[9];
    /* 3D38 */ BYTE m_nLastSpellbookClassIndex;
    /* 3D39 */ BYTE m_nLastSpellbookSpellLevel;
    /* 3DFA */ CAIObjectType m_liveTypeAI;
    /* 3E36 */ CAIObjectType m_startTypeAI;
    /* 3E72 */ WORD m_type;
    /* 3E74 */ DWORD m_expirationTime;
    /* 3E78 */ WORD m_huntingRange;
    /* 3E7A */ WORD m_followRange;
    /* 3E7C */ CPoint m_posStart;
    /* 3E84 */ DWORD m_timeOfDayVisible;
    /* 4284 */ CGameSpriteSpells m_spells;
    /* 4984 */ CGameSpriteGroupedSpellList m_domainSpells;
    /* 4A84 */ CGameSpriteSpellList m_innateSpells;
    /* 4AA0 */ CGameSpriteSpellList m_songs;
    /* 4ABC */ CGameSpriteSpellList m_shapeshifts;
    /* 4AD8 */ CGameSpriteEquipment m_equipment;
    /* 4BAC */ int field_4BAC;
    /* 4BB0 */ int field_4BB0;
    /* 4BB4 */ unsigned char field_4BB4;
    /* 4BB6 */ CGameStatsSprite m_cGameStats;
    /* 4C4A */ CResRef m_currentArea;
    /* 4C52 */ BOOLEAN m_bGlobal;
    /* 4C53 */ unsigned char field_4C53;
    /* 4C54 */ int field_4C54;
    /* 4C58 */ int field_4C58;
    /* 4C5C */ int field_4C5C;
    /* 4C60 */ int field_4C60;
    /* 4C64 */ int field_4C64;
    /* 4C68 */ unsigned char field_4C68;
    /* 4C6A */ CSound m_sndWalk[2];
    /* 4D32 */ int field_4D32;
    /* 4D36 */ CSound m_sndArmor[2];
    /* 4DFE */ unsigned char field_4DFE;
    /* 4E00 */ CSound m_sndReady;
    /* 4E64 */ CSound m_sndDeath;
    /* 4FF4 */ int m_nNumberOfTimesTalkedTo;
    /* 4FF8 */ int field_4FF8;
    /* 5004 */ unsigned char field_5004[96];
    /* 5064 */ short m_nHappiness;
    /* 5066 */ CAIObjectType m_interactingWith;
    /* 50A2 */ LONG m_triggerId;
    /* 50A6 */ BOOL m_active;
    /* 50AA */ BOOL m_activeAI;
    /* 50AE */ BOOL m_activeImprisonment;
    /* 50B2 */ BOOL m_bSelected;
    /* 50B6 */ int field_50B6;
    /* 50BA */ unsigned char field_50BA;
    /* 50BB */ BYTE m_terrainTable[16];
    /* 50CB */ BYTE m_visibleTerrainTable[16];
    /* 50DB */ BYTE m_flightTerrainTable[16];
    /* 50EC */ CGameAnimation m_animation;
    /* 50F6 */ short* m_pSpriteEffectArray;
    /* 50FA */ CPoint* m_pSpriteEffectArrayPosition;
    /* 50FE */ unsigned char field_50FE;
    /* 5100 */ BYTE m_spriteEffectDuration;
    /* 5101 */ unsigned char field_5101;
    /* 5102 */ unsigned char field_5102;
    /* 5103 */ unsigned char field_5103;
    /* 5202 */ int field_5202;
    /* 5304 */ int field_5304;
    /* 5320 */ unsigned char field_5320;
    /* 5321 */ BOOLEAN m_bEscapingArea;
    /* 5322 */ int field_5322;
    /* 5326 */ int field_5326;
    /* 532A */ unsigned char field_532A;
    /* 532C */ int field_532C;
    /* 5330 */ int field_5330;
    /* 5334 */ int field_5334;
    /* 5338 */ float field_5338;
    /* 533C */ short field_533C;
    /* 533E */ unsigned char field_533E;
    /* 533F */ BOOLEAN m_bVisibilityUpdated;
    /* 5340 */ int field_5340;
    /* 5344 */ int field_5344;
    /* 5348 */ SHORT m_nSequence;
    /* 534A */ int field_534A;
    /* 534E */ int field_534E;
    /* 5352 */ int field_5352;
    /* 5356 */ int field_5356;
    /* 535A */ CPoint m_posDest;
    /* 5362 */ int field_5362;
    /* 5366 */ int field_5366;
    /* 536A */ int field_536A;
    /* 536E */ int field_536E;
    /* 5372 */ CPoint m_posLastVisMapEntry;
    /* 537A */ SHORT m_skipDeltaDirection;
    /* 537C */ SHORT m_deltaDirection;
    /* 537E */ SHORT m_nNewDirection;
    /* 5380 */ SHORT m_nDirection;
    /* 5382 */ LONG* m_pPath;
    /* 5386 */ short m_nPath;
    /* 5388 */ CTypedPtrList<CPtrList, int*> m_pPathTemp;
    /* 53A4 */ CTypedPtrList<CPtrList, int*> m_nPathTemp;
    /* 53C0 */ short m_currPath;
    /* 53C2 */ BOOL m_walkBackwards;
    /* 53C6 */ int field_53C6;
    /* 53CA */ COLORREF m_lastRGBColor;
    /* 53CE */ int field_53CE;
    /* 53D2 */ int field_53D2;
    /* 53D6 */ CSearchRequest* m_currentSearchRequest;
    /* 53DA */ short field_53DA;
    /* 53DC */ short field_53DC;
    /* 53DE */ int field_53DE;
    /* 53E2 */ int field_53E2;
    /* 53E6 */ int field_53E6;
    /* 54A4 */ int field_54A4;
    /* 54A8 */ int field_54A8;
    /* 54AC */ int field_54AC;
    /* 54B0 */ int field_54B0;
    /* 54B4 */ int field_54B4;
    /* 54B8 */ int field_54B8;
    /* 54BC */ int field_54BC;
    /* 54C0 */ int field_54C0;
    /* 54C4 */ LONG field_54C4;
    /* 54C8 */ int m_followStart;
    /* 54E8 */ short field_54E8;
    /* 54EA */ int field_54EA;
    /* 54EE */ int field_54EE;
    /* 54F2 */ short field_54F2;
    /* 54F4 */ short field_54F4;
    /* 54F6 */ short field_54F6;
    /* 54F8 */ short field_54F8;
    /* 54FA */ CGameEffectList m_equipedEffectList;
    /* 5526 */ CGameEffectList m_timedEffectList;
    /* 556E */ int field_556E;
    /* 5572 */ int field_5572;
    /* 5576 */ SHORT m_userCommandPause;
    /* 5578 */ SHORT m_nCommandPause;
    /* 557A */ int field_557A;
    /* 557E */ int field_557E;
    /* 5582 */ int field_5582;
    /* 5586 */ POSITION m_groupPosition;
    /* 558A */ BOOL m_groupMove;
    /* 558E */ int field_558E;
    /* 5592 */ int field_5592;
    /* 5596 */ int field_5596;
    /* 559A */ int field_559A;
    /* 559E */ short field_559E;
    /* 55A0 */ short field_55A0;
    /* 55A2 */ int field_55A2[20];
    /* 55F2 */ int field_55F2;
    /* 55F6 */ int field_55F6;
    /* 55FA */ int field_55FA;
    /* 55FE */ int field_55FE;
    /* 5602 */ unsigned char field_5602;
    /* 5604 */ short field_5604;
    /* 5606 */ short field_5606;
    /* 5608 */ int field_5608;
    /* 560C */ short field_560C;
    /* 560E */ short field_560E;
    /* 5610 */ short field_5610;
    /* 5612 */ short field_5612;
    /* 5614 */ short field_5614;
    /* 5616 */ short field_5616;
    /* 5618 */ int field_5618;
    /* 561C */ short field_561C;
    /* 561E */ short field_561E;
    /* 5620 */ short field_5620;
    /* 5622 */ short field_5622;
    /* 5624 */ int field_5624;
    /* 5628 */ BOOL m_inFormation;
    /* 562C */ int field_562C;
    /* 5630 */ unsigned char field_5630;
    /* 5632 */ int field_5632;
    /* 5636 */ unsigned char field_5636;
    /* 5638 */ int field_5638;
    /* 563C */ int field_563C;
    /* 5640 */ int field_5640;
    /* 5644 */ BOOL m_removeFromArea;
    /* 5648 */ CMarker m_marker;
    /* 566C */ CMarker m_destMarker;
    /* 5690 */ LONG m_targetId;
    /* 5694 */ CPoint m_targetPoint;
    /* 569C */ short m_targetAreaSize;
    /* 56E4 */ CResRef field_56E4;
    /* 56EC */ unsigned char field_56EC;
    /* 56DC */ CResRef m_dialog;
    /* 56EE */ STR_RES m_speech[64];
    /* 70F2 */ int field_70F2;
    /* 70F6 */ BYTE field_70F6;
    /* 70F7 */ BYTE field_70F7;
    /* 70F8 */ BYTE field_70F8;
    /* 70F9 */ BYTE field_70F9;
    /* 70FA */ BYTE field_70FA;
    /* 710A */ SHORT field_710A;
    /* 710C */ SHORT field_710C;
    /* 710E */ SHORT field_710E;
    /* 7110 */ int field_7110;
    /* 7114 */ int field_7114;
    /* 7118 */ int field_7118;
    /* 711C */ short field_711C;
    /* 711E */ int field_711E;
    /* 7122 */ LONG m_dialogWait;
    /* 7126 */ LONG m_dialogWaitTarget;
    /* 712A */ int m_talkingCounter;
    /* 712E */ unsigned char field_712E;
    /* 7130 */ CTypedPtrList<CPtrList, int*> m_portraitIcons; // NOTE: Stores actual ints disguised as pointers.
    /* 714C */ CVidCell m_portraitIconVidCell;
    /* 7226 */ BOOL m_firstActionSound;
    /* 722A */ ULONG field_722A;
    /* 722E */ LONG field_722E;
    /* 7234 */ int field_7234;
    /* 7238 */ int field_7238;
    /* 723C */ int field_723C;
    /* 7240 */ int field_7240;
    /* 7244 */ ULONG m_lastRegenerationTime;
    /* 724C */ unsigned char field_724C;
    /* 724D */ BOOLEAN m_bHappinessChanged;
    /* 7252 */ CResRef m_secondarySounds;
    /* 725A */ unsigned char field_725A[32];
    /* 727E */ int field_727E;
    /* 7292 */ int field_7292;
    /* 7296 */ SHORT m_currentActionId;
    /* 72A2 */ short field_72A2;
    /* 72A4 */ BOOL field_72A4;
    /* 72A4 */ BOOL m_bAllowEffectListCall;
    /* 72A8 */ unsigned char field_72A8;
    /* 72AA */ int field_72AA;
    /* 72AE */ int field_72AE;
    /* 72B2 */ CVariableHash* field_72B2;
    /* 72B6 */ int field_72B6;
    /* 72D6 */ int field_72D6;
    /* 72DE */ int field_72DE;
    /* 72E6 */ int field_72E6;
    /* 7430 */ unsigned char field_7430;
    /* 752E */ BOOL m_bSendSpriteUpdate;
    /* 7532 */ int field_7532;
    /* 7536 */ int field_7536;
    /* 7540 */ int field_7540;
    /* 7544 */ int field_7544;
    /* 7548 */ CVidCell field_7548[32];
    /* 9088 */ CSound field_9088[32];
    /* 9D08 */ int field_9D08;
    /* 9D0C */ int field_9D0C;
    /* 9D10 */ int field_9D10;
    /* 9D14 */ unsigned char field_9D14;
    /* 9D15 */ unsigned char field_9D15;
};

#endif /* CGAMESPRITE_H_ */

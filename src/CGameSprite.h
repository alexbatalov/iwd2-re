#ifndef CGAMESPRITE_H_
#define CGAMESPRITE_H_

#include "CAIObjectType.h"
#include "CBounceList.h"
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
#include "CVidBitmap.h"
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

#define MAX_SELECTABLE_FEAT_USE_LEVELS 5

#define STATICBUFFERSIZE_CGAMESPRITE 128

class CBlood;
class CGameButtonList;
class CMemINIValue;
class CPersistantEffect;
class CProjectile;
class CSearchBitmap;
class CSearchRequest;
class CSpell;
class CUIControlBase;
class CUIControlTextDisplay;
class CVariableHash;
class CVisibilityMap;
class IcewindCVisualEffect;

typedef struct {
    CString field_0;
    INT field_4;
} CGameSpriteSoundEntry;

class CGameSpriteLastUpdate {
public:
    void Initialize(BOOL bFullUpdateRequired);
};

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

    static const BYTE SOUND_DYING;
    static const BYTE SOUND_SELECT;
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
    static const BYTE SEQ_ATTACK_SLASH;
    static const BYTE SEQ_ATTACK_BACKSLASH;
    static const BYTE SEQ_ATTACK_JAB;

    static const ITEM_ABILITY DEFAULT_ATTACK;

    static const LONG STANDARD_VERBAL_CONSTANT_LENGTH;

    static const SHORT FLY_RIGHT;
    static const SHORT FLY_LEFT;
    static const SHORT FLY_RADIUS_RANDOM;
    static const SHORT FLY_RADIUS_BASE;
    static const SHORT FLY_0;
    static const SHORT FLY_90;
    static const SHORT FLY_180;
    static const SHORT FLY_270;
    static const SHORT FLY_360;

    static const WORD FEEDBACK_BACKSTAB;
    static const WORD FEEDBACK_CRITICALHIT;
    static const WORD FEEDBACK_CRITICALMISS;
    static const WORD FEEDBACK_TOHIT;
    static const WORD FEEDBACK_SPELL;
    static const WORD FEEDBACK_ATTACKS;
    static const WORD FEEDBACK_MODAL;
    static const WORD FEEDBACK_LOCKPICKSUCCEEDED;
    static const WORD FEEDBACK_LOCKPICKFAILED;
    static const WORD FEEDBACK_TRAPDISARMED;
    static const WORD FEEDBACK_TRAPDETECTED;
    static const WORD FEEDBACK_ITEMCURSED;
    static const WORD FEEDBACK_HIDEFAILED;
    static const WORD FEEDBACK_TOOHEAVY_SLOWED;
    static const WORD FEEDBACK_TOOHEAVY_STOPPED;
    static const WORD FEEDBACK_16;
    static const WORD FEEDBACK_HIDESUCCEEDED;
    static const WORD FEEDBACK_MORALEFAILURE_PANIC;
    static const WORD FEEDBACK_MORALEFAILURE_RUN;
    static const WORD FEEDBACK_MORALEFAILURE_BERSERK;
    static const WORD FEEDBACK_LEVELUP;
    static const WORD FEEDBACK_SPELLFAILED_INDOORS;
    static const WORD FEEDBACK_LEAVING_SHADOWS;
    static const WORD FEEDBACK_BASHDOORSUCCEEDED;
    static const WORD FEEDBACK_BASHDOORFAILED;
    static const WORD FEEDBACK_BASHCHESTSUCCEEDED;
    static const WORD FEEDBACK_BASHCHESTFAILED;
    static const WORD FEEDBACK_BACKSTAB_UNUSABLE_WEAPON;
    static const WORD FEEDBACK_29;
    static const WORD FEEDBACK_PICKPOCKETFAILED_ARMOR;
    static const WORD FEEDBACK_PICKPOCKETFAILED_HOSTILE;
    static const WORD FEEDBACK_PICKPOCKETFAILED_SKILL;
    static const WORD FEEDBACK_PICKPOCKETFAILED_NOITEMS;
    static const WORD FEEDBACK_PICKPOCKETFAILED_INVENTORYFULL;
    static const WORD FEEDBACK_PICKPOCKETSUCCEEDED;
    static const WORD FEEDBACK_GAINEDSPECIALABILITY;
    static const WORD FEEDBACK_IMMUNE_TO_WEAPON;
    static const WORD FEEDBACK_CHARACTER_CONTROL_SEIZURE;
    static const WORD FEEDBACK_TRAPDISARMEDFAILED;
    static const WORD FEEDBACK_CRITICALHITAVOIDED;
    static const WORD FEEDBACK_AURA_CLEANSED;
    static const WORD FEEDBACK_42;
    static const WORD FEEDBACK_43;
    static const WORD FEEDBACK_44;
    static const WORD FEEDBACK_45;
    static const WORD FEEDBACK_46;
    static const WORD FEEDBACK_47;
    static const WORD FEEDBACK_ITEM_DROPPED_FULL;
    static const WORD FEEDBACK_LOCK_UNPICKABLE;
    static const WORD FEEDBACK_TOOMANYSUMMONED;
    static const WORD FEEDBACK_SILENCED;
    static const WORD FEEDBACK_CRIPPLINGSTRIKESUCCEEDED;
    static const WORD FEEDBACK_SNEAK_UNUSABLE_WEAPON;
    static const WORD FEEDBACK_EFFECTSEVADED;
    static const WORD FEEDBACK_SPELLFAILED_DISRUPTED;
    static const WORD FEEDBACK_GAINEDBARDSONG;
    static const WORD FEEDBACK_STATICCHARGEEND;
    static const WORD FEEDBACK_IMMUNE_TO_RESOURCE;
    static const WORD FEEDBACK_LEAVEFAILED_INVENTORY;
    static const WORD FEEDBACK_BACKSTAB_AVOIDED;
    static const WORD FEEDBACK_SPELLFAILED_CASTFAILURE;
    static const WORD FEEDBACK_62;
    static const WORD FEEDBACK_63;
    static const WORD FEEDBACK_CRIPPLINGSTRIKEFAILED;
    static const WORD FEEDBACK_USEMAGICDEVICEFAILED;
    static const WORD FEEDBACK_USEMAGICDEVICESUCCEEDED;
    static const WORD FEEDBACK_SEARCHSTART;
    static const WORD FEEDBACK_SEARCHEND;
    static const WORD FEEDBACK_69;
    static const WORD FEEDBACK_TURNUNDEADEND;
    static const WORD FEEDBACK_71;
    static const WORD FEEDBACK_BATTLESONGSTART;
    static const WORD FEEDBACK_BATTLESONGEND;
    static const WORD FEEDBACK_74;
    static const WORD FEEDBACK_ARTERIALSTRIKESUCCEEDED;
    static const WORD FEEDBACK_HAMSTRINGSUCCEEDED;
    static const WORD FEEDBACK_77;
    static const WORD FEEDBACK_78;
    static const WORD FEEDBACK_79;
    static const WORD FEEDBACK_HEROICINSPIRATION;
    static const WORD FEEDBACK_TARGETCONCEALED;
    static const WORD FEEDBACK_UNCANNYDODGESUCCEEDED;
    static const WORD FEEDBACK_ROLL;
    static const WORD FEEDBACK_SPELLFAILURE_CONCENTRATION;
    static const WORD FEEDBACK_SPONTANEOUSCASTING;
    static const WORD FEEDBACK_TOGGLEFEAT;
    static const WORD FEEDBACK_CLEAVE;
    static const WORD FEEDBACK_LINGERINGSONG;
    static const WORD FEEDBACK_89;
    static const WORD FEEDBACK_CALLLIGHTNINGEND;
    static const WORD FEEDBACK_MAGICALWEAPONINUSE;
    static const WORD FEEDBACK_LEAVEFAILED_LEVELUP;
    static const WORD FEEDBACK_LEAVEFAILED_STORE;

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

    static const CString TOKEN_SPECIALABILITY;

    static BYTE STATICBUFFER[STATICBUFFERSIZE_CGAMESPRITE];
    static BOOLEAN SHOW_CHARACTER_HP;
    static BOOLEAN GRAVITY_IS_DOWN;
    static INT m_bRollFeedbackEnabled;

    CGameSprite(BYTE* pCreature, LONG creatureSize, int a3, WORD type, DWORD expirationTime, WORD huntingRange, WORD followRange, DWORD timeOfDayVisible, CPoint startPos, WORD facing);
    /* 0000 */ ~CGameSprite() override;
    /* 0008 */ void AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType) override;
    /* 000C */ void AIUpdate() override;
    /* 0014 */ LONG GetTargetId() override;
    /* 0018 */ void GetNextWaypoint(CPoint* pt) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;
    /* 0038 */ BOOL DoesIntersect(CRect r);
    /* 003C */ BOOL OnSearchMap() override;
    /* 0044 */ void OnFormationButton(const CPoint& pt) override;
    /* 004C */ void Render(CGameArea* pArea, CVidMode* pVidMode, INT nSurface) override;
    /* 0058 */ void SetCursor(LONG nToolTip) override;
    /* 007C */ void ClearAI(BOOLEAN bSetSequence) override;
    /* 0094 */ void SetScript(SHORT level, CAIScript* script) override;
    /* 009C */ const BYTE* GetVisibleTerrainTable() override;
    /* 00A0 */ const BYTE* GetTerrainTable() override;
    /* 00B0 */ void AutoPause(DWORD type) override;
    /* 00B4 */ BOOL GetCanSeeInvisible() override;
    /* 00B8 */ virtual void SetTarget(const CPoint& target, BOOL collisionPath);
    /* 00BC */ virtual void SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart);
    /* 00C0 */ virtual void ResetAITypeLive();
    /* 00C4 */ virtual void ResetAIType();

    void AddBlood(SHORT nHeight, SHORT nDirection, SHORT nType);
    void AIUpdateWalk();
    void SetPath(LONG* pPath, SHORT nPath);
    BOOL sub_6FB440();
    void AIUpdateFly();
    void ChangeDirection();
    void CheckIfVisible();
    void DropPath();
    void DropSearchRequest();
    BOOL MoveToBack();
    BOOL MoveToFront();
    void OnLightningStrike();
    void MakeGlobal();
    SHORT GetNumSounds(SHORT nOffset, SHORT nMaxNum);
    void PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption);
    void VerbalConstant(LONG verbalConstant);
    LONG GetLength(LONG verbalConstant);
    BOOL IsSpellSchool(BYTE spellSchool);
    void SetFootstepChannel();
    BYTE GetSound(BYTE soundID);
    void RenderMarkers(CVidMode* pVidMode, INT nSurface);
    void RenderPortrait(const CPoint& cpRenderPosition, const CSize& szControl, BOOL bPressed, BOOL reorderHighlight, BOOL selectFromMarker, const CRect& rClip, BOOL bDoubleSize);
    void RenderToMapScreen(const CRect& rClipBase, const CPoint& ptCharPos);
    COLORREF GetMapScreenColor();
    void Select();
    void Unselect();
    void SetCharacterToolTip(CUIControlBase* pControl);
    void SetDirection(const CPoint& posDest);
    void SetDirection(SHORT direction);
    void SetFacing(SHORT direction);
    void InitBlur();
    void SetIdleSequence();
    SHORT GetIdleSequence();
    void SetSequence(SHORT nSequence);
    void SetTarget(CSearchRequest* pSearchRequest, BOOL collisionPath, BYTE frontList);
    void SetTargetFly(BYTE circleType, BYTE facing, LONG radius);
    void StartSpriteEffect(BYTE spriteEffect, BYTE intensityLevel, BYTE effectDuration, BOOLEAN a4);
    void RenderSpriteCover(CVidMode* pVidMode, INT nSurface, CVidCell* pVidCell, const IcewindCVisualEffect& vfx);
    void RenderDamageArrow(CGameArea* pArea, CVidMode* pVidMode, INT nSurface);
    void RenderSpriteEffect(CVidMode* pVidMode, INT nSurface);
    void UpdateSpriteEffect();
    void ClearMarshal(BOOL unequip);
    void Marshal(CAreaFileCreature** pCreature);
    void Marshal(BYTE** pCreature, LONG* creatureSize, WORD* facing, BOOLEAN a4, BOOLEAN a5);
    void Marshal(CSavedGamePartyCreature& partyCreature, BOOLEAN bNetworkMessage);
    void MarshalMessage(BYTE** pData, DWORD* dwSize);
    void Unmarshal(CSavedGamePartyCreature* pCreature, BOOLEAN bPartyMember, BOOLEAN bProgressBarInPlace);
    void Unmarshal(BYTE* pCreature, LONG creatureSize, WORD facing, int a4);
    void UnmarshalScripts();
    void FetchCommonStrings();
    void LoadAreaInformation(CAreaFileCreature* pCreature);
    BYTE GetChannel();
    void RenderMirrorImage(INT placement, CRect& rFX, CRect& rGCBounds, CRect& rViewRect, CPoint& ptReference, CSearchBitmap* pSearch, CVisibilityMap* pVisibility, CVidMode* pVidMode, INT nSurface, COLORREF& rgbTint, BOOLEAN& bDithered, BOOLEAN& bFadeOut, DWORD& dwRenderFlags);
    void GetSelectedWeaponButton(CButtonData& cButtonData);
    void GetWeaponButton(BYTE nButtonNum, CButtonData& cButtonData);
    void SetSelectedWeaponButton(SHORT buttonNum);
    void InitQuickSpellData(CResRef resRef, BYTE type, CButtonData& cButtonData, BYTE nClass, BYTE a5, BYTE a6);
    void InitQuickItemData(SHORT itemNum, SHORT abilityNum, int a3, CButtonData& cButtonData);
    CGameButtonList* GetSongsButtonList();
    BOOLEAN CanCast(BYTE nClass, DWORD nSpecialization, CSpell* pSpell);
    CGameButtonList* GetInternalButtonList();
    CGameButtonList* GetItemUsages(SHORT slotNum, WORD buttonType, SHORT abilityNum);
    CItem* GetLauncher(const ITEM_ABILITY* ability, SHORT& launcherSlot);
    SHORT GetLauncherSlot(SHORT slotNum, SHORT abilityNum);
    BOOL CheckLauncherType(const ITEM_ABILITY* ability, CItem* pLauncher);
    BOOL ReadyCursor();
    void ReadySpell(SHORT buttonNum, INT nType, BOOLEAN firstCall);
    void ReadyItem(SHORT buttonNum, BOOLEAN firstCall);
    void ReadyOffInternalList(CButtonData buttonData, BOOLEAN firstCall);
    void sub_71A0E0(CButtonData buttonData, BOOLEAN firstCall);
    void sub_71A550(CButtonData buttonData, BOOLEAN firstCall);
    void CheckToolTipItem(BYTE buttonNum);
    CItem* GetQuickItem(BYTE buttonNum);
    void UnequipAll(BOOL a1);
    void EquipAll(BOOL a1);
    void Equip(SHORT slotNum);
    void Unequip(SHORT slotNum);
    SHORT GetTurnUndeadLevel();
    SHORT GetBackstabDamageMultiplier();
    SHORT GetLayOnHandsAmount();
    void AddSpecialAbility(const CResRef& cResInnateSpell, BOOL feedBack);
    void RemoveSpecialAbility(const CResRef& cResInnateSpell);
    void CheckLoadState();
    INT GetNumQuickWeaponSlots();
    SHORT FindItemPersonal(const CString& sName, int number, BOOL restrictToEquiped);
    SHORT CountItemPersonal(const CString& sName);
    DWORD GetCarriedWeight();
    void GetQuickWeapon(BYTE buttonNum, CButtonData& buttonData);
    void InitializeWalkingSound();
    void PlayDialogSound(CGameSprite* pNPC);
    void AddKnownDivineSpells(const BYTE& nClass);
    void DisplayTextRef(STRREF nameRef, STRREF textRef, COLORREF nameColor, COLORREF textColor);
    void GetNumInventoryPersonalSlots(INT& nUsedSlots, INT& nTotalSlots);
    void SetModalState(BYTE modalState, BOOL bUpdateToolbar);
    BOOL sub_7202E0();
    void CheckSequence(BYTE& sequence);
    void sub_7204C0();
    void sub_720B50(CMemINIValue* a1, CMemINIValue* a2);
    SHORT FindItemBags(const CString& sName, LONG number, BOOL checkForIdentified);
    SHORT TakeItemBags(const CString& sName, LONG number, SHORT slotNum);
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
    void PlaySound(const CResRef& res);
    BOOL Orderable(BOOL bIgnoreControl);
    BOOL Animate();
    DWORD GetSpecialization();
    void ResolvePausedAction(const CAIAction* curAction, POSITION pos);
    void ResolveTargetPoint(const CAIAction* curAction, POSITION pos);
    BOOL ProcessEffectList();
    void ClearStoredPaths();
    void ClearDialogActions();
    BOOL HandleEffects();
    void FeedBack(WORD nFeedBackId, LONG a2, LONG a3, LONG a4, LONG a5, LONG a6, LONG a7);
    BOOLEAN sub_737910(BOOL a1);
    SHORT GetCriticalHitBonus();
    SHORT sub_73C6A0(CGameSprite* target, CItem* curWeapon, const ITEM_ABILITY* curAttack);
    SHORT sub_73C7E0();
    SHORT sub_73C8C0(CGameSprite* target);
    SHORT sub_73CA20(CItem* curWeapon, const ITEM_ABILITY* curAttack);
    SHORT sub_73CAD0();
    SHORT sub_73CAE0(CItem* curWeapon, const ITEM_ABILITY* curAttack);
    SHORT sub_73CB10(CItem* curWeapon, const ITEM_ABILITY* curAttack);
    SHORT sub_73CC40(CItem* curWeapon, const ITEM_ABILITY* curAttack);
    SHORT sub_73D420();
    SHORT sub_73D440(CItem* curWeapon);
    SHORT MoveToPoint();
    SHORT OneSwing();
    SHORT Recoil();
    SHORT PlayDead();
    SHORT JumpToPoint(CPoint dest, BOOL spriteUpdate);
    SHORT Face();
    SHORT FaceObject(CGameAIBase* pObject);
    SHORT LeaveParty();
    void MoveGlobal(const CString& sArea, const CPoint& ptStart);
    SHORT GroupAttack(CGameSprite* pTarget);
    SHORT Enemy();
    SHORT SetDialog();
    void SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4);
    void sub_756930(CItem* pItem, CItem* pLauncher);
    SHORT EquipItem();
    SHORT FindTraps();
    SHORT Panic();
    SHORT Turn();
    SHORT EquipMostDamagingMelee();
    const CAIObjectType& GetLiveAIType();
    SHORT GetCasterLevel(CSpell* pSpell, BYTE nClass, DWORD nSpecialization);
    SHORT sub_75F240();
    SHORT sub_75F3D0(int a1);
    SHORT SetAtOffset(DWORD stat, DWORD value, BOOL modify);
    SHORT ForceHide(CGameSprite* pSprite);
    SHORT sub_7615F0(int a1);
    void sub_761650();
    SHORT DropItem(CItem* pItem);
    void sub_761990();
    SHORT PlayBardSong();
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
    void SetColorRange(BYTE rangeValue);
    void DisplayFeats(CUIControlTextDisplay* pText);
    void DisplaySkills(CUIControlTextDisplay* pText);
    SHORT JumpToArea(CString areaName, const CPoint& dest, SHORT facingDirection, SHORT delay);
    void MoveOntoArea(CGameArea* pArea, const CPoint& dest, SHORT facingDirection);

    void SetResRef(const CResRef& resRef);
    void sub_453160(int a1);
    int sub_453170();
    SHORT GetSequence();
    CCreatureFileHeader* GetBaseStats();
    CDerivedStats* GetDerivedStats();
    void sub_4531B0();
    CGameEffectList* GetEquipedEffectList();
    CGameEffectList* GetTimedEffectList();
    void SetStealthGreyOut(LONG greyOut);
    void AddPortraitIcon(int icon);
    void RemovePortraitIcon(int icon);
    CGameSpriteSpellList* GetInnateSpells();
    CGameSpriteSpellList* GetSongs();
    CGameSpriteSpellList* GetShapeshifts();
    DWORD sub_5940D0();
    INT sub_5940E0(BYTE buttonNum);
    void sub_594120(BYTE buttonNum, int a2);
    BYTE GetModalState();

    int sub_45B710();
    SHORT GetDirection(const CPoint& target);
    SHORT GetDirection();
    static SHORT GetDirection(const CPoint& ptStart, const CPoint& ptTarget);
    CGameAnimation* GetAnimation();
    CGameSpriteEquipment* GetEquipment();
    SHORT GetHappiness();
    BOOL GetActive();
    CVariableHash* GetLocalVariables();

    INT sub_724010(INT a1);
    INT sub_7240A0();
    INT sub_724170();
    INT sub_724270();
    INT sub_724360();
    BOOL CheckAranceFailure(INT nRoll);
    INT sub_724430();
    BOOL CheckDivineFailure(INT nRoll);
    BOOLEAN sub_7245D0();
    INT GetNextHatedRacesSlot();
    void ResetQuickSlots();
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
    void sub_726330(UINT nFeatNumber, INT nValue);
    void sub_726570();
    INT sub_726800();
    void sub_726810(BYTE nWeaponSet);
    BYTE GetLastSong();

    void GetQuickSpell(BYTE buttonNum, CButtonData& buttonData);
    void GetQuickItem(BYTE buttonNum, CButtonData& buttonData);
    void GetQuickAbility(BYTE buttonNum, CButtonData& buttonData);
    void GetQuickSong(BYTE buttonNum, CButtonData& buttonData);
    void SetQuickWeapon(BYTE buttonNum, CButtonData buttonData);
    void SetQuickWeapon(BYTE buttonNum, BYTE index);
    void SetQuickItem(BYTE buttonNum, CButtonData buttonData);
    void SetQuickSpell(BYTE buttonNum, CButtonData buttonData);
    void SetQuickAbility(BYTE buttonNum, CButtonData buttonData);
    void SetQuickSong(BYTE buttonNum, CButtonData buttonData);
    CDerivedStats* GetActiveStats();

    /* 0598 */ CResRef m_resRef;
    /* 05A0 */ CString m_sName;
    /* 05A4 */ CCreatureFileHeader m_baseStats;
    /* 0920 */ CDerivedStats m_derivedStats;
    /* 1778 */ CDerivedStats m_tempStats;
    /* 25D0 */ CDerivedStats m_bonusStats;
    /* 342C */ CButtonData m_quickWeapons[8];
    /* 360C */ CButtonData m_quickSpells[9];
    /* 3828 */ CButtonData m_quickItems[3];
    /* 38DC */ CButtonData m_quickInnates[9];
    /* 3AF8 */ CButtonData m_quickSongs[9];
    /* 3D14 */ int field_3D14[9];
    /* 3D38 */ BYTE m_nLastSpellbookClassIndex;
    /* 3D39 */ BYTE m_nLastSpellbookSpellLevel;
    /* 3D3A */ unsigned char field_3D3A[8];
    /* 3D42 */ BYTE m_nLastSong;
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
    /* 4BAC */ BYTE* m_pDialogData;
    /* 4BB0 */ DWORD m_nDialogData;
    /* 4BB4 */ BYTE m_lastCharacterCount;
    /* 4BB6 */ CGameStatsSprite m_cGameStats;
    /* 4C4A */ CResRef m_currentArea;
    /* 4C52 */ BOOLEAN m_bGlobal;
    /* 4C53 */ BYTE m_nModalState;
    /* 4C54 */ int field_4C54[5];
    /* 4C68 */ BYTE m_nWeaponSet;
    /* 4C6A */ CSound m_sndWalk[2];
    /* 4D32 */ int m_nSndWalk;
    /* 4D36 */ CSound m_sndArmor[2];
    /* 4DFE */ unsigned char m_currSndWalk;
    /* 4DFF */ BYTE m_currSndArmor;
    /* 4E00 */ CSound m_sndReady;
    /* 4E64 */ CSound m_sndDeath;
    /* 4F90 */ CSound m_sndSpriteEffect;
    /* 4FF4 */ int m_nNumberOfTimesTalkedTo;
    /* 4FF8 */ BOOL m_bSeenPartyBefore;
    /* 5004 */ LONG m_nNumberOfTimesInteractedWith[24];
    /* 5064 */ SHORT m_nHappiness;
    /* 5066 */ CAIObjectType m_interactingWith;
    /* 50A2 */ LONG m_triggerId;
    /* 50A6 */ BOOL m_active;
    /* 50AA */ BOOL m_activeAI;
    /* 50AE */ BOOL m_activeImprisonment;
    /* 50B2 */ BOOL m_bSelected;
    /* 50B6 */ BOOL m_bPortraitUpdate;
    /* 50BA */ BOOLEAN m_bInfravisionOn;
    /* 50BB */ BYTE m_terrainTable[16];
    /* 50CB */ BYTE m_visibleTerrainTable[16];
    /* 50DB */ BYTE m_flightTerrainTable[16];
    /* 50EC */ CGameAnimation m_animation;
    /* 50F6 */ USHORT* m_pSpriteEffectArray;
    /* 50FA */ POINT* m_pSpriteEffectArrayPosition;
    /* 50FE */ BYTE m_nTwitches;
    /* 50FF */ BYTE m_spriteEffectSequenceNumber;
    /* 5100 */ BYTE m_spriteEffectDuration;
    /* 5101 */ BYTE m_spriteEffectSequenceLength;
    /* 5102 */ BYTE m_spriteEffectBaseIntensity;
    /* 5103 */ BYTE m_spriteEffectRandomIntensity;
    /* 5104 */ CVidCell m_spriteEffectVidCell;
    /* 51DE */ CVidPalette m_spriteEffectPalette;
    /* 5202 */ DWORD m_spriteEffectFlags;
    /* 5206 */ CVidCell m_spriteSplashVidCell;
    /* 52E0 */ CVidPalette m_spriteSplashPalette;
    /* 5304 */ int field_5304;
    /* 5308 */ CRect m_rSpriteEffectFX;
    /* 5318 */ CPoint m_ptSpriteEffectReference;
    /* 5320 */ BYTE m_effectExtendDirection;
    /* 5321 */ BOOLEAN m_bEscapingArea;
    /* 5322 */ BOOL m_animationRunning;
    /* 5326 */ LONG m_posZDelta;
    /* 532A */ BYTE m_doBounce;
    /* 532C */ double m_fCircleChange;
    /* 5334 */ double m_fCurrCircleChange;
    /* 533C */ SHORT m_radius;
    /* 533E */ BYTE m_circleFacing;
    /* 533F */ BOOLEAN m_bVisibilityUpdated;
    /* 5340 */ double m_fDirectionOffset;
    /* 5348 */ SHORT m_nSequence;
    /* 534A */ CPoint m_posExact;
    /* 5352 */ int field_5352;
    /* 5356 */ int field_5356;
    /* 535A */ CPoint m_posDest;
    /* 5362 */ CPoint m_posOld;
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
    /* 53C6 */ BOOL m_turningAbout;
    /* 53CA */ COLORREF m_lastRGBColor;
    /* 53CE */ BOOL m_pathSearchInvalidDest;
    /* 53D2 */ int field_53D2;
    /* 53D6 */ CSearchRequest* m_currentSearchRequest;
    /* 53DA */ SHORT m_nBloodFlashAmount;
    /* 53DC */ SHORT m_nDamageLocatorTime;
    /* 53DE */ COLORREF m_nDamageLocatorColor;
    /* 53E2 */ BOOL m_bBloodFlashOn;
    /* 53E6 */ int field_53E6;
    /* 53EA */ CVidBitmap m_vbPortraitSmall;
    /* 54A4 */ BOOL m_bVisibleMonster;
    /* 54A8 */ int field_54A8;
    /* 54AC */ BOOL m_bBumped;
    /* 54B0 */ CPoint m_ptBumpedFrom;
    /* 54B8 */ int field_54B8;
    /* 54BC */ int field_54BC;
    /* 54C0 */ int field_54C0;
    /* 54C4 */ LONG field_54C4;
    /* 54C8 */ int m_followStart;
    /* 54CC */ CTypedPtrList<CPtrList, CBlood*> m_lstBlood;
    /* 54E8 */ short field_54E8;
    /* 54EA */ int field_54EA;
    /* 54EE */ int field_54EE;
    /* 54F2 */ short field_54F2;
    /* 54F4 */ short field_54F4;
    /* 54F6 */ SHORT m_moveToFrontQueue;
    /* 54F8 */ SHORT m_moveToBackQueue;
    /* 54FA */ CGameEffectList m_equipedEffectList;
    /* 5526 */ CGameEffectList m_timedEffectList;
    /* 5552 */ CTypedPtrList<CPtrList, CPersistantEffect*> m_persistantEffects;
    /* 556E */ CPoint m_curDest;
    /* 5576 */ SHORT m_userCommandPause;
    /* 5578 */ SHORT m_nCommandPause;
    /* 557A */ int field_557A;
    /* 557E */ int field_557E;
    /* 5582 */ int field_5582;
    /* 5586 */ POSITION m_groupPosition;
    /* 558A */ BOOL m_groupMove;
    /* 558E */ int field_558E;
    /* 5592 */ CProjectile* m_curProjectile;
    /* 5596 */ CSpell* m_curSpell;
    /* 559A */ CItem* m_curItem;
    /* 559E */ short field_559E;
    /* 55A0 */ short field_55A0;
    /* 55A2 */ int field_55A2[20];
    /* 55F2 */ int field_55F2;
    /* 55F6 */ int field_55F6;
    /* 55FA */ int field_55FA;
    /* 55FE */ int field_55FE;
    /* 5602 */ unsigned char field_5602;
    /* 5604 */ SHORT m_speedFactor;
    /* 5606 */ short field_5606;
    /* 5608 */ BOOL m_endOfDamageSeq;
    /* 560C */ short field_560C;
    /* 560E */ short field_560E;
    /* 5610 */ short field_5610;
    /* 5612 */ short field_5612;
    /* 5614 */ short field_5614;
    /* 5616 */ short field_5616;
    /* 5618 */ int field_5618;
    /* 561C */ short field_561C;
    /* 561E */ short field_561E;
    /* 5620 */ SHORT m_recoilFrame;
    /* 5622 */ SHORT m_attackFrame;
    /* 5624 */ int field_5624;
    /* 5628 */ BOOL m_inFormation;
    /* 562C */ int field_562C;
    /* 5630 */ unsigned char field_5630;
    /* 5632 */ int field_5632;
    /* 5636 */ unsigned char field_5636;
    /* 5638 */ BOOL m_hasColorEffects;
    /* 563C */ BOOL m_hasColorRangeEffects;
    /* 5640 */ int field_5640;
    /* 5644 */ BOOL m_removeFromArea;
    /* 5648 */ CMarker m_marker;
    /* 566C */ CMarker m_destMarker;
    /* 5690 */ LONG m_targetId;
    /* 5694 */ CPoint m_targetPoint;
    /* 569C */ short m_targetAreaSize;
    /* 569E */ BYTE m_nTempSelectedWeapon;
    /* 56DF */ BYTE m_nTempSelectedWeaponAbility;
    /* 56A0 */ CButtonData m_currentUseButton;
    /* 56E4 */ CResRef field_56E4;
    /* 56EC */ unsigned char field_56EC;
    /* 56DC */ CResRef m_dialog;
    /* 56EE */ STR_RES m_speech[64];
    /* 70EE */ int field_70EE;
    /* 70F2 */ int field_70F2;
    /* 70F6 */ BYTE field_70F6;
    /* 70F7 */ BYTE field_70F7;
    /* 70F8 */ BYTE field_70F8;
    /* 70F9 */ BYTE field_70F9;
    /* 70FA */ BYTE field_70FA;
    /* 70FB */ BOOLEAN field_70FB;
    /* 70FC */ BOOLEAN field_70FC;
    /* 70FD */ BOOLEAN field_70FD;
    /* 70FE */ BOOLEAN field_70FE;
    /* 70FF */ BOOLEAN field_70FF;
    /* 7100 */ BOOLEAN field_7100;
    /* 7101 */ BOOLEAN field_7101;
    /* 7106 */ int field_7106;
    /* 710A */ SHORT field_710A;
    /* 710C */ SHORT field_710C;
    /* 710E */ SHORT field_710E;
    /* 7110 */ int field_7110;
    /* 7114 */ BOOL m_moraleFailure;
    /* 7118 */ int field_7118;
    /* 711C */ short field_711C;
    /* 711E */ int field_711E;
    /* 7122 */ LONG m_dialogWait;
    /* 7126 */ LONG m_dialogWaitTarget;
    /* 712A */ int m_talkingCounter;
    /* 712E */ BYTE m_talkingRenderCount;
    /* 712F */ BOOLEAN m_inControlLastTime;
    /* 7130 */ CTypedPtrList<CPtrList, int*> m_portraitIcons; // NOTE: Stores actual ints disguised as pointers.
    /* 714C */ CVidCell m_portraitIconVidCell;
    /* 7226 */ BOOL m_firstActionSound;
    /* 722A */ ULONG field_722A;
    /* 722E */ BOOL m_berserkActive;
    /* 7232 */ SHORT m_attackSoundDeadzone;
    /* 7234 */ LONG m_nHPCONBonusTotalOld;
    /* 7238 */ BOOL m_bHPCONBonusTotalUpdate;
    /* 723C */ DWORD m_modalCounter;
    /* 7240 */ BOOL m_bHiding;
    /* 7244 */ ULONG m_lastRegenerationTime;
    /* 7248 */ int field_7248;
    /* 724C */ unsigned char field_724C;
    /* 724D */ BOOLEAN m_bHappinessChanged;
    /* 724E */ LONG m_nUnselectableCounter;
    /* 7252 */ CResRef m_secondarySounds;
    /* 725A */ unsigned char field_725A[32];
    /* 727A */ LONG m_nStealthGreyOut;
    /* 727E */ int field_727E;
    /* 7282 */ unsigned char field_7282;
    /* 7283 */ unsigned char field_7283;
    /* 7284 */ unsigned char field_7284;
    /* 728E */ int field_728E;
    /* 7292 */ BOOL m_bForceVisualEffects;
    /* 7296 */ SHORT m_currentActionId;
    /* 7298 */ BOOL m_bPlayedEncumberedStopped;
    /* 729C */ BOOL m_bPlayedEncumberedSlowed;
    /* 72A0 */ short field_72A0;
    /* 72A2 */ short field_72A2;
    /* 72A4 */ BOOL m_bAllowEffectListCall;
    /* 72A8 */ unsigned char field_72A8;
    /* 72AA */ int field_72AA;
    /* 72AE */ int field_72AE;
    /* 72B2 */ CVariableHash* m_pLocalVariables;
    /* 72B6 */ BOOL m_bInUnmarshal;
    /* 72BA */ CBounceList m_lBounceList;
    /* 72D6 */ int field_72D6;
    /* 72DA */ LONG m_nBounceCounter;
    /* 72DE */ int field_72DE;
    /* 72E2 */ LONG field_72E2;
    /* 72E6 */ CGameButtonList* m_internalButtonList;
    /* 72F0 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_72F0;
    /* 730C */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_730C;
    /* 7328 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_7328;
    /* 7344 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_7344;
    /* 7360 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_7360;
    /* 737C */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_737C;
    /* 7398 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_7398;
    /* 73B4 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_73B4;
    /* 73D0 */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_73D0;
    /* 73EC */ CList<CGameSpriteSoundEntry, CGameSpriteSoundEntry> field_73EC;
    /* 7408 */ CString field_7408;
    /* 740C */ int field_740C;
    /* 7410 */ CString field_7410;
    /* 7414 */ int field_7414;
    /* 7418 */ CString field_7418;
    /* 741C */ int field_741C;
    /* 7420 */ CString field_7420;
    /* 7424 */ int field_7424;
    /* 7428 */ CString field_7428;
    /* 742C */ int field_742C;
    /* 7430 */ unsigned char field_7430;
    /* 7432 */ CGameSpriteLastUpdate m_cLastSpriteUpdate;
    /* 752E */ BOOL m_bSendSpriteUpdate;
    /* 7532 */ int field_7532;
    /* 7536 */ int field_7536;
    /* 753A */ int field_753A;
    /* 753C */ int field_753C;
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

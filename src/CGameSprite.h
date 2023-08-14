#ifndef CGAMESPRITE_H_
#define CGAMESPRITE_H_

#include "CAIObjectType.h"
#include "CDerivedStats.h"
#include "CGameAIBase.h"
#include "CGameAnimation.h"
#include "CGameSpriteEquipment.h"
#include "CResRef.h"
#include "CSound.h"
#include "FileFormat.h"

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

#define CGAMESPRITE_SKILL_NUMSKILLS 16

class CUIControlTextDisplay;

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

    /* 0014 */ LONG GetTargetId() override;
    /* 0038 */ BOOL DoesIntersect(CRect r);
    /* 003C */ BOOL OnSearchMap() override;
    /* 0044 */ void OnFormationButton(const CPoint& pt) override;
    /* 009C */ const BYTE* GetVisibleTerrainTable() override;
    /* 00A0 */ const BYTE* GetTerrainTable() override;
    /* 00BC */ virtual void SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart);
    /* 00C0 */ virtual void ResetAITypeLive();
    /* 00C4 */ virtual void ResetAIType();

    void DropPath();
    void OnLightningStrike();
    void MakeGlobal();
    void PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption);
    void SetFootstepChannel();
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
    DWORD GetCarriedWeight();
    void GetNumInventoryPersonalSlots(INT& nUsedSlots, INT& nTotalSlots);
    void sub_72DE60();
    int sub_71F6E0();
    const CString& GetName();
    STRREF GetNameRef();
    BOOL Orderable(BOOL bIgnoreControl);
    DWORD GetSpecialization();
    BOOL ProcessEffectList();
    void SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4);
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

    void SetResRef(const CResRef& resRef);

    CGameAnimation* GetAnimation();

    /* 0598 */ CResRef m_resRef;
    /* 05A0 */ CString m_sName;
    /* 05A4 */ CCreatureFileHeader m_baseStats;
    /* 0920 */ CDerivedStats m_derivedStats;
    /* 1778 */ CDerivedStats m_tempStats;
    /* 3D38 */ BYTE m_nLastSpellbookClassIndex;
    /* 3D39 */ BYTE m_nLastSpellbookSpellLevel;
    /* 3DFA */ CAIObjectType m_liveTypeAI;
    /* 3E36 */ CAIObjectType m_startTypeAI;
    /* 4AD8 */ CGameSpriteEquipment m_equipment;
    /* 4C52 */ BOOLEAN m_bGlobal;
    /* 4C53 */ unsigned char field_4C53;
    /* 4C68 */ unsigned char field_4C68;
    /* 4C6A */ CSound m_sndWalk[2];
    /* 4D36 */ CSound m_sndArmor[2];
    /* 4E00 */ CSound m_sndReady;
    /* 4E64 */ CSound m_sndDeath;
    /* 50BB */ BYTE m_terrainTable[16];
    /* 50CB */ BYTE m_visibleTerrainTable[16];
    /* 50EC */ CGameAnimation m_animation;
    /* 5382 */ LONG* m_pPath;
    /* 5586 */ POSITION m_groupPosition;
    /* 558A */ BOOL m_groupMove;
    /* 562C */ int field_562C;
    /* 5690 */ LONG m_targetId;
    /* 5694 */ CPoint m_targetPoint;
    /* 70F2 */ int field_70F2;
    /* 72A4 */ BOOL field_72A4;
    /* 9D15 */ unsigned char field_9D15;
};

#endif /* CGAMESPRITE_H_ */

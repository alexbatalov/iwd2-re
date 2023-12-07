#ifndef CGAMEEFFECT_H_
#define CGAMEEFFECT_H_

#include "mfc.h"

#include "CResRef.h"
#include "CSound.h"
#include "FileFormat.h"

class CGameSprite;

#define CGAMEEFFECT_AC 0
#define CGAMEEFFECT_ATTACKNO 1
#define CGAMEEFFECT_AWAKEN 2
#define CGAMEEFFECT_BERSERK 3
#define CGAMEEFFECT_CALM 4
#define CGAMEEFFECT_CHARM 5
#define CGAMEEFFECT_CHR 6
#define CGAMEEFFECT_COLORCHANGE 7
#define CGAMEEFFECT_COLORGLOWSOLID 8
#define CGAMEEFFECT_COLORGLOWPULSE 9
#define CGAMEEFFECT_CON 10
#define CGAMEEFFECT_CUREPOISON 11
#define CGAMEEFFECT_DAMAGE 12
#define CGAMEEFFECT_DEATH 13
#define CGAMEEFFECT_DEFROST 14
#define CGAMEEFFECT_DEX 15
#define CGAMEEFFECT_HASTE 16
#define CGAMEEFFECT_HEAL 17
#define CGAMEEFFECT_HITPOINTS 18
#define CGAMEEFFECT_INT 19
#define CGAMEEFFECT_INVISIBLE 20
#define CGAMEEFFECT_LORE 21
#define CGAMEEFFECT_LUCK 22
#define CGAMEEFFECT_MORALE 23
#define CGAMEEFFECT_PANIC 24
#define CGAMEEFFECT_POISON 25
#define CGAMEEFFECT_REMOVECURSE 26
#define CGAMEEFFECT_RESISTACID 27
#define CGAMEEFFECT_RESISTCOLD 28
#define CGAMEEFFECT_RESISTELECTRICITY 29
#define CGAMEEFFECT_RESISTFIRE 30
#define CGAMEEFFECT_RESISTMAGIC 31
#define CGAMEEFFECT_RESURRECT 32
#define CGAMEEFFECT_SAVEVSFORTITUDE 33
#define CGAMEEFFECT_SAVEVSRELFEX 34
#define CGAMEEFFECT_SAVEVSWILL 35
#define CGAMEEFFECT_SILENCE 38
#define CGAMEEFFECT_SLEEP 39
#define CGAMEEFFECT_SLOW 40
#define CGAMEEFFECT_SPARKLE 41
#define CGAMEEFFECT_SPELLMEMORIZATIONMAGE 42
#define CGAMEEFFECT_STONETOFLESH 43
#define CGAMEEFFECT_STR 44
#define CGAMEEFFECT_STUN 45
#define CGAMEEFFECT_UNSTUN 46
#define CGAMEEFFECT_VISIBLE 47
#define CGAMEEFFECT_VOCALIZE 48
#define CGAMEEFFECT_WIS 49
#define CGAMEEFFECT_SINGLECOLORPULSEALL 50
#define CGAMEEFFECT_COLORTINTSOLID 51
#define CGAMEEFFECT_COLORLIGHTSOLID 52
#define CGAMEEFFECT_ANIMATIONCHANGE 53
#define CGAMEEFFECT_BASEATTACKBONUS 54
#define CGAMEEFFECT_SLAY 55
#define CGAMEEFFECT_ALIGNMENTREVERSAL 56
#define CGAMEEFFECT_ALIGNMENTCHANGE 57
#define CGAMEEFFECT_DISPELEFFECTS 58
#define CGAMEEFFECT_SKILLSTEALTH 59
#define CGAMEEFFECT_CASTINGFAILURE 60
#define CGAMEEFFECT_SKILLALCHEMY 61
#define CGAMEEFFECT_SPELLMEMOIZATIONCLERIC 62
#define CGAMEEFFECT_INFRAVISION 63
#define CGAMEEFFECT_INFRAVISIONOFF 64
#define CGAMEEFFECT_BLUR 65
#define CGAMEEFFECT_TRANSLUCENT 66
#define CGAMEEFFECT_SUMMON 67
#define CGAMEEFFECT_SKILLUNSUMMON 68
#define CGAMEEFFECT_NONDETECTION 69
#define CGAMEEFFECT_ENDNONDETECTION 70
#define CGAMEEFFECT_SEXCHANGE 71
#define CGAMEEFFECT_AICHANGE 72
#define CGAMEEFFECT_DAMAGEMOD 73
#define CGAMEEFFECT_BLINDNESS 74
#define CGAMEEFFECT_CUREBLINDNESS 75
#define CGAMEEFFECT_FEEBLEMINDEDNESS 76
#define CGAMEEFFECT_CUREFEEBLEMINDEDNESS 77
#define CGAMEEFFECT_DISEASE 78
#define CGAMEEFFECT_CUREDISEASE 79
#define CGAMEEFFECT_DEAFNESS 80
#define CGAMEEFFECT_CUREDEAFNESS 81
#define CGAMEEFFECT_SETAISCRIPT 82
#define CGAMEEFFECT_IMMUNITYTOPROJECTILE 83
#define CGAMEEFFECT_RESISTSLASHING 86
#define CGAMEEFFECT_RESISTCRUSHING 87
#define CGAMEEFFECT_RESISTPIERCING 88
#define CGAMEEFFECT_RESISTMISSILE 89
#define CGAMEEFFECT_SKILLLOCKPICKING 90
#define CGAMEEFFECT_SKILLTRAPS 91
#define CGAMEEFFECT_SKILLPICKPOCKET 92
#define CGAMEEFFECT_FATIGUE 93
#define CGAMEEFFECT_INTOXICATION 94
#define CGAMEEFFECT_SKILLTRACKING 95
#define CGAMEEFFECT_LEVEL 96
#define CGAMEEFFECT_STREXTRA 97
#define CGAMEEFFECT_REGENERATION 98
#define CGAMEEFFECT_DURATIONCASTING 99
#define CGAMEEFFECT_PROTECTIONFROMCREATURE 100
#define CGAMEEFFECT_IMMUNITYTOEFFECT 101
#define CGAMEEFFECT_IMMUNITYTOSPELLLEVEL 102
#define CGAMEEFFECT_NAME 103
#define CGAMEEFFECT_XP 104
#define CGAMEEFFECT_GOLD 105
#define CGAMEEFFECT_MORALBREAK 106
#define CGAMEEFFECT_PORTRAIT 107
#define CGAMEEFFECT_REPUTATION 108
#define CGAMEEFFECT_HOLDCREATURE 109
#define CGAMEEFFECT_RETREATFROM 110
#define CGAMEEFFECT_CREATEWEAPON 111
#define CGAMEEFFECT_DESTROYWEAPON 112
#define CGAMEEFFECT_EQUIPWEAPON 113
#define CGAMEEFFECT_DITHER 114
#define CGAMEEFFECT_DISPELINVISIBLE 116
#define CGAMEEFFECT_SHOWAREA 117
#define CGAMEEFFECT_SHOWCREATURES 118
#define CGAMEEFFECT_MIRRORIMAGE 119
#define CGAMEEFFECT_IMMUNETOWEAPON 120
#define CGAMEEFFECT_VISUALANIMATIONEFFECT 121
#define CGAMEEFFECT_CREATEITEM 122
#define CGAMEEFFECT_DESTROYITEM 123
#define CGAMEEFFECT_TELEPORT 124
#define CGAMEEFFECT_KNOCK 125
#define CGAMEEFFECT_MOVEMENTRATE_126 126
#define CGAMEEFFECT_CONFUSION 128
#define CGAMEEFFECT_NON_CUMULATIVEAID 129
#define CGAMEEFFECT_NON_CUMULATIVEBLESS 130
#define CGAMEEFFECT_NON_CUMULATIVECHANT 131
#define CGAMEEFFECT_NON_CUMULATIVEDRAWUPONHOLYMIGHT 132
#define CGAMEEFFECT_NON_CUMULATIVELUCK 133
#define CGAMEEFFECT_PETRIFICATION 134
#define CGAMEEFFECT_POLYMORPH 135
#define CGAMEEFFECT_FORCEVISIBLE 136
#define CGAMEEFFECT_SETSEQUENCE 138
#define CGAMEEFFECT_DISPLAYSTRING 139
#define CGAMEEFFECT_CASTINGGLOW 140
#define CGAMEEFFECT_VISUALSPELLHIT 141
#define CGAMEEFFECT_PORTRAITICON 142
#define CGAMEEFFECT_REPLACEITEM 143
#define CGAMEEFFECT_DISABLEBUTTON 144
#define CGAMEEFFECT_DISABLESPELLTYPE 145
#define CGAMEEFFECT_CASTSPELL 146
#define CGAMEEFFECT_LEARNSPELL 147
#define CGAMEEFFECT_CASTSPELLPOINT 148
#define CGAMEEFFECT_IDENTIFY 149
#define CGAMEEFFECT_DETECTTRAPS 150
#define CGAMEEFFECT_REPLACESELF 151
#define CGAMEEFFECT_PLAYMOVIE 152
#define CGAMEEFFECT_SANCTUARY 153
#define CGAMEEFFECT_ENTANGLE 154
#define CGAMEEFFECT_WEBHOLD 157
#define CGAMEEFFECT_GREASEPOOL 158
#define CGAMEEFFECT_MIRRORIMAGERUN 159
#define CGAMEEFFECT_DISPELSANCTUARY 160
#define CGAMEEFFECT_REMOVEPANIC 161
#define CGAMEEFFECT_REMOVEHOLD 162
#define CGAMEEFFECT_RESTOREMOVEMENTRATE 163
#define CGAMEEFFECT_REMOVEINTOXICATION 164
#define CGAMEEFFECT_PAUSECASTER 165
#define CGAMEEFFECT_RESISTANCETOMAGIC 166
#define CGAMEEFFECT_MISSILETHAC0BONUS 167
#define CGAMEEFFECT_DESTROYSELF 168
#define CGAMEEFFECT_IMMUNITYTOPORTRAITICON 169
#define CGAMEEFFECT_DAMAGEVISUALEFFECT 170
#define CGAMEEFFECT_ADDINNATEABILITY 171
#define CGAMEEFFECT_REMOVEINNATEABILITY 172
#define CGAMEEFFECT_RESISTANCETOPOISON 173
#define CGAMEEFFECT_PLAYSOUND 174
#define CGAMEEFFECT_HOLDCREATURESPELL_175 175
#define CGAMEEFFECT_MOVEMENTRATE_176 176
#define CGAMEEFFECT_APPLYEFFECT 177
#define CGAMEEFFECT_SELECTIVETOHITBONUS 178
#define CGAMEEFFECT_SELECTDAMAGEBONUS 179
#define CGAMEEFFECT_RESTRICTEQUIPITEM 180
#define CGAMEEFFECT_RESTRICTEQUIPITEMTYPE 181
#define CGAMEEFFECT_APPLYEFFECTEQUIPITEM 182
#define CGAMEEFFECT_APPLYEFFECTEQUIPITEMTYPE 183
#define CGAMEEFFECT_SETDONOJUMP 184
#define CGAMEEFFECT_HOLDCREATURESPELL_185 185
#define CGAMEEFFECT_JUMPTOAREA 186
#define CGAMEEFFECT_SETLOCALVARIABLE 187
#define CGAMEEFFECT_AURACLEANSING 188
#define CGAMEEFFECT_MENTALSPEED 189
#define CGAMEEFFECT_PHYSICALSPEED 190
#define CGAMEEFFECT_CASTINGLEVELBONUS 191
#define CGAMEEFFECT_FINDFAMILIAR 192
#define CGAMEEFFECT_SEEINVISIBLE 193
#define CGAMEEFFECT_IGNOREDIALOGPAUSE 194
#define CGAMEEFFECT_HITPOINTSONDEATH 195
#define CGAMEEFFECT_FAMILIARBLOCK 196
#define CGAMEEFFECT_BOUNCEPROJECTILE 197
#define CGAMEEFFECT_BOUNCEEFFECT 198
#define CGAMEEFFECT_BOUNCELEVEL 199
#define CGAMEEFFECT_BOUNCELEVELDECREMENT 200
#define CGAMEEFFECT_IMMUNITYLEVELDECREMENT 201
#define CGAMEEFFECT_BOUNCESCHOOL 202
#define CGAMEEFFECT_BOUNCESECONDARYTYPE 203
#define CGAMEEFFECT_IMMUNITYSCHOOL 204
#define CGAMEEFFECT_IMMUNITYSECONDARYTYPE 205
#define CGAMEEFFECT_IMMUNITYSPELL 206
#define CGAMEEFFECT_BOUNCESPELL 207
#define CGAMEEFFECT_MINHITPOINTS 208
#define CGAMEEFFECT_POWERWORDKILL 209
#define CGAMEEFFECT_POWERWORDSTUN 210
#define CGAMEEFFECT_IMPRISONMENT 211
#define CGAMEEFFECT_FREEDOM 212
#define CGAMEEFFECT_MAZE 213
#define CGAMEEFFECT_SECONDARYCASTLIST 214
#define CGAMEEFFECT_VISUALEFFECT 215
#define CGAMEEFFECT_LEVELDRAIN 216
#define CGAMEEFFECT_POWERWORDSLEEP 217
#define CGAMEEFFECT_STONESKINS 218
#define CGAMEEFFECT_PROTECTIONCIRCLE 219
#define CGAMEEFFECT_DISPELSCHOOL 220
#define CGAMEEFFECT_DISPELSECONDARYTYPE 221
#define CGAMEEFFECT_RANDOMTELEPORT 222
#define CGAMEEFFECT_IMMUNITYSCHOOLDECREMENT 223
#define CGAMEEFFECT_LEVELRESTORATION 224
#define CGAMEEFFECT_REVEALMAGIC 225
#define CGAMEEFFECT_SECONDARYTYPEDECREMENT 226
#define CGAMEEFFECT_BOUNCESCHOOLDECREMENT 227
#define CGAMEEFFECT_BOUNCESECONDARYTYPEDECREMENT 228
#define CGAMEEFFECT_DISPELSCHOOLONE 229
#define CGAMEEFFECT_DISPELSECONDARYTYPEONE 230
#define CGAMEEFFECT_TIMESTOP 231
#define CGAMEEFFECT_MAGICAL_REST 292

class CGameEffectBase {
public:
    CGameEffectBase();

    /* 0000 */ CResRef m_version;
    /* 0008 */ DWORD m_effectID;
    /* 000C */ DWORD m_targetType;
    /* 0010 */ DWORD m_spellLevel;
    /* 0014 */ LONG m_effectAmount;
    /* 0018 */ DWORD m_dwFlags;
    /* 001C */ DWORD m_durationType;
    /* 0020 */ DWORD m_duration;
    /* 0024 */ WORD m_probabilityUpper;
    /* 0026 */ WORD m_probabilityLower;
    /* 0028 */ CResRef m_res;
    /* 0030 */ DWORD m_numDice;
    /* 0034 */ DWORD m_diceSize;
    /* 0038 */ DWORD m_savingThrow;
    /* 003C */ LONG m_saveMod;
    /* 0040 */ DWORD m_special;
    /* 0044 */ DWORD m_school;
    /* 0048 */ int field_48;
    /* 004C */ DWORD m_minLevel;
    /* 0050 */ DWORD m_maxLevel;
    /* 0054 */ DWORD m_flags;
    /* 0058 */ LONG m_effectAmount2;
    /* 005C */ LONG m_effectAmount3;
    /* 0060 */ LONG m_effectAmount4;
    /* 0064 */ LONG m_effectAmount5;
    /* 0068 */ CResRef m_res2;
    /* 0070 */ CResRef m_res3;
    /* 0078 */ CPoint m_source;
    /* 0080 */ CPoint m_target;
    /* 0088 */ DWORD m_sourceType;
    /* 008C */ CResRef m_sourceRes;
    /* 0094 */ DWORD m_sourceFlags;
    /* 0098 */ DWORD m_projectileType;
    /* 009C */ LONG m_slotNum;
    /* 00A0 */ SCRIPTNAME m_scriptName;
    /* 00C0 */ DWORD m_casterLevel;
    /* 00C4 */ DWORD m_firstCall;
    /* 00C8 */ DWORD m_secondaryType;
    /* 00CC */ DWORD m_pad[15];
};

class CGameEffect : public CGameEffectBase {
public:
    static const CString EFFECT_NAME[];

    static CGameEffect* DecodeEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, const CPoint& target);

    CGameEffect();
    CGameEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target, BOOL usesDice);
    /* 0000 */ ~CGameEffect();
    /* 0004 */ virtual CGameEffect* Copy();
    /* 0008 */ virtual BOOL ApplyEffect(CGameSprite* pSprite);
    /* 000C */ virtual BOOL ResolveEffect(CGameSprite* pSprite);
    /* 0014 */ virtual void OnLoad(CGameSprite* pSprite);
    /* 001C */ virtual BOOL UsesDice();
    /* 0020 */ virtual void DisplayString(CGameSprite* pSprite);

    BOOL Compare(const CGameEffect& other);
    void PlaySound(const CResRef& soundResRef, CGameSprite* pSprite);
    BOOL CheckExpiration();
    ITEM_EFFECT* GetItemEffect();
    void DisplayStringRef(CGameSprite* pSprite, STRREF str);
    void AddColorEffect(CGameSprite* pSprite, BYTE r, BYTE g, BYTE b, BYTE periodLength);
    void AddColorEffect(CGameSprite* pSprite, BYTE r, BYTE g, BYTE b);
    void CopyFromBase(CGameEffectBase* pBase);
    void SetEffectID(WORD effectID);
    void SetDWFlags(DWORD dwFlags);
    void sub_493400(BOOL a1);
    void sub_594020(BOOL bEnabled);
    void SetSource(const CPoint& pt);
    void SetSourceId(LONG sourceID);

    void sub_4C3F30(CGameSprite* pSprite, INT nValue);
    void AdjustResistMagic(CGameSprite* pSprite, SHORT nValue);
    void AdjustTHAC0(CGameSprite* pSprite, SHORT nValue);
    void AdjustSTR(CGameSprite* pSprite, INT nValue);
    void AdjustDEX(CGameSprite* pSprite, INT nValue);
    void AdjustINT(CGameSprite* pSprite, INT nValue);
    void AdjustWIS(CGameSprite* pSprite, INT nValue);
    void AdjustCON(CGameSprite* pSprite, INT nValue);
    void Immobilize(CGameSprite* pSprite);
    void AddSlowEffect(CGameSprite* pSprite);
    void AddPanicEffect(CGameSprite* pSprite);
    void RemoveAllOfType(CGameSprite* pSprite, WORD effectID, LONG effectAmount);
    void AddPortraitIcon(CGameSprite* pSprite, int icon);
    void SetSpellState(CGameSprite* pSprite, DWORD dwSpellState);
    static void ClearItemEffect(ITEM_EFFECT* itemEffect, WORD newEffectId);

    /* 010C */ LONG m_sourceID;
    /* 0110 */ BOOL m_done;
    /* 0114 */ BOOL m_forceRepass;
    /* 0118 */ int field_118;
    /* 011C */ BOOL m_compareIdOnly;
    /* 0120 */ BOOL m_compareIdAndFlagsOnly;
    /* 0124 */ CSound m_sound;
    /* 0188 */ int field_188;
};

class CGameEffectAC : public CGameEffect {
public:
    CGameEffectAC(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectAttackNo : public CGameEffect {
public:
    CGameEffectAttackNo(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAwaken : public CGameEffect {
public:
    CGameEffectAwaken(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBerserk : public CGameEffect {
public:
    CGameEffectBerserk(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBarbarianRage : public CGameEffect {
public:
    CGameEffectBarbarianRage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCalm : public CGameEffect {
public:
    CGameEffectCalm(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCharm : public CGameEffect {
public:
    CGameEffectCharm(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSlipperyMind : public CGameEffect {
public:
    CGameEffectSlipperyMind(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectCHR : public CGameEffect {
public:
    CGameEffectCHR(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectColorChange : public CGameEffect {
public:
    CGameEffectColorChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectColorGlowSolid : public CGameEffect {
public:
    CGameEffectColorGlowSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectColorGlowPulse : public CGameEffect {
public:
    CGameEffectColorGlowPulse(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCON : public CGameEffect {
public:
    CGameEffectCON(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCurePoison : public CGameEffect {
public:
    CGameEffectCurePoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDamage : public CGameEffect {
public:
    CGameEffectDamage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;

    void sub_4A7750(CGameSprite* pSprite);
};

class CGameEffectDeath : public CGameEffect {
public:
    CGameEffectDeath();
    CGameEffectDeath(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffectDeath(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target, int a5);
    CGameEffect* Copy() override;

    /* 018C */ int field_18C;
};

class CGameEffectDefrost : public CGameEffect {
public:
    CGameEffectDefrost(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDEX : public CGameEffect {
public:
    CGameEffectDEX(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHaste : public CGameEffect {
public:
    CGameEffectHaste(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHeal : public CGameEffect {
public:
    CGameEffectHeal();
    CGameEffectHeal(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectHitPoints : public CGameEffect {
public:
    CGameEffectHitPoints(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectINT : public CGameEffect {
public:
    CGameEffectINT(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectInvisible : public CGameEffect {
public:
    CGameEffectInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectLore : public CGameEffect {
public:
    CGameEffectLore(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectLuck : public CGameEffect {
public:
    CGameEffectLuck(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMorale : public CGameEffect {
public:
    CGameEffectMorale(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPanic : public CGameEffect {
public:
    CGameEffectPanic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPoison : public CGameEffect {
public:
    CGameEffectPoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectRemoveCurse : public CGameEffect {
public:
    CGameEffectRemoveCurse(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectResistAcid : public CGameEffect {
public:
    CGameEffectResistAcid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistCold : public CGameEffect {
public:
    CGameEffectResistCold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistElectricity : public CGameEffect {
public:
    CGameEffectResistElectricity(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistFire : public CGameEffect {
public:
    CGameEffectResistFire(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistMagic : public CGameEffect {
public:
    CGameEffectResistMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResurrect : public CGameEffect {
public:
    CGameEffectResurrect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSaveVsFortitude : public CGameEffect {
public:
    CGameEffectSaveVsFortitude(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSaveVsRelfex : public CGameEffect {
public:
    CGameEffectSaveVsRelfex(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSaveVsWill : public CGameEffect {
public:
    CGameEffectSaveVsWill(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSilence : public CGameEffect {
public:
    CGameEffectSilence(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSleep : public CGameEffect {
public:
    CGameEffectSleep(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSlow : public CGameEffect {
public:
    CGameEffectSlow(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSparkle : public CGameEffect {
public:
    CGameEffectSparkle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSpellMemorizationMage : public CGameEffect {
public:
    CGameEffectSpellMemorizationMage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectStoneToFlesh : public CGameEffect {
public:
    CGameEffectStoneToFlesh();
    CGameEffectStoneToFlesh(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSTR : public CGameEffect {
public:
    CGameEffectSTR(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectStun : public CGameEffect {
public:
    CGameEffectStun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectUnstun : public CGameEffect {
public:
    CGameEffectUnstun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectVisible : public CGameEffect {
public:
    CGameEffectVisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectVocalize : public CGameEffect {
public:
    CGameEffectVocalize(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectWIS : public CGameEffect {
public:
    CGameEffectWIS(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSingleColorPulseAll : public CGameEffect {
public:
    CGameEffectSingleColorPulseAll(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectColorTintSolid : public CGameEffect {
public:
    CGameEffectColorTintSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectColorLightSolid : public CGameEffect {
public:
    CGameEffectColorLightSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectAnimationChange : public CGameEffect {
public:
    CGameEffectAnimationChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBaseAttackBonus : public CGameEffect {
public:
    CGameEffectBaseAttackBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSlay : public CGameEffect {
public:
    CGameEffectSlay(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAlignmentReversal : public CGameEffect {
public:
    CGameEffectAlignmentReversal(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAlignmentChange : public CGameEffect {
public:
    CGameEffectAlignmentChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDispelEffects : public CGameEffect {
public:
    CGameEffectDispelEffects(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSkillStealth : public CGameEffect {
public:
    CGameEffectSkillStealth(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHideInShadows : public CGameEffect {
public:
    CGameEffectHideInShadows(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCastingFailure : public CGameEffect {
public:
    CGameEffectCastingFailure(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillAlchemy : public CGameEffect {
public:
    CGameEffectSkillAlchemy(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSpellMemoizationCleric : public CGameEffect {
public:
    CGameEffectSpellMemoizationCleric(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectInfravision : public CGameEffect {
public:
    CGameEffectInfravision(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectInfravisionOff : public CGameEffect {
public:
    CGameEffectInfravisionOff(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBlur : public CGameEffect {
public:
    CGameEffectBlur(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectTranslucent : public CGameEffect {
public:
    CGameEffectTranslucent(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSummon : public CGameEffect {
public:
    CGameEffectSummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;

    /* 018C */ int field_18C;
    /* 0190 */ int field_190;
};

class CGameEffectSkillUnsummon : public CGameEffect {
public:
    CGameEffectSkillUnsummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectNonDetection : public CGameEffect {
public:
    CGameEffectNonDetection(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectEndNonDetection : public CGameEffect {
public:
    CGameEffectEndNonDetection(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSexChange : public CGameEffect {
public:
    CGameEffectSexChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAIChange : public CGameEffect {
public:
    CGameEffectAIChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDamageMod : public CGameEffect {
public:
    CGameEffectDamageMod(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBlindness : public CGameEffect {
public:
    CGameEffectBlindness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDayBlindness : public CGameEffect {
public:
    CGameEffectDayBlindness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCureBlindness : public CGameEffect {
public:
    CGameEffectCureBlindness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectFeebleMindedness : public CGameEffect {
public:
    CGameEffectFeebleMindedness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCureFeebleMindedness : public CGameEffect {
public:
    CGameEffectCureFeebleMindedness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDisease : public CGameEffect {
public:
    CGameEffectDisease(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectCureDisease : public CGameEffect {
public:
    CGameEffectCureDisease(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDeafness : public CGameEffect {
public:
    CGameEffectDeafness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCureDeafness : public CGameEffect {
public:
    CGameEffectCureDeafness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSetAIScript : public CGameEffect {
public:
    CGameEffectSetAIScript(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectImmunityToProjectile : public CGameEffect {
public:
    CGameEffectImmunityToProjectile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistSlashing : public CGameEffect {
public:
    CGameEffectResistSlashing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistCrushing : public CGameEffect {
public:
    CGameEffectResistCrushing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistPiercing : public CGameEffect {
public:
    CGameEffectResistPiercing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistMissile : public CGameEffect {
public:
    CGameEffectResistMissile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillLockPicking : public CGameEffect {
public:
    CGameEffectSkillLockPicking(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillTraps : public CGameEffect {
public:
    CGameEffectSkillTraps(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillPickPocket : public CGameEffect {
public:
    CGameEffectSkillPickPocket(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillUseMagicDevice : public CGameEffect {
public:
    CGameEffectSkillUseMagicDevice(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectFatigue : public CGameEffect {
public:
    CGameEffectFatigue(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectIntoxication : public CGameEffect {
public:
    CGameEffectIntoxication(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSkillTracking : public CGameEffect {
public:
    CGameEffectSkillTracking(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectLevel : public CGameEffect {
public:
    CGameEffectLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSTRExtra : public CGameEffect {
public:
    CGameEffectSTRExtra(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRegeneration : public CGameEffect {
public:
    CGameEffectRegeneration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDurationCasting : public CGameEffect {
public:
    CGameEffectDurationCasting(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectProtectionFromCreature : public CGameEffect {
public:
    CGameEffectProtectionFromCreature(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImmunityToEffect : public CGameEffect {
public:
    CGameEffectImmunityToEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImmunityToSpellLevel : public CGameEffect {
public:
    CGameEffectImmunityToSpellLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectName : public CGameEffect {
public:
    CGameEffectName(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectXP : public CGameEffect {
public:
    CGameEffectXP(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectGold : public CGameEffect {
public:
    CGameEffectGold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectMoralBreak : public CGameEffect {
public:
    CGameEffectMoralBreak(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPortrait : public CGameEffect {
public:
    CGameEffectPortrait(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectReputation : public CGameEffect {
public:
    CGameEffectReputation(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHoldCreature : public CGameEffect {
public:
    CGameEffectHoldCreature(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRetreatFrom : public CGameEffect {
public:
    CGameEffectRetreatFrom(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCreateWeapon : public CGameEffect {
public:
    CGameEffectCreateWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDestroyWeapon : public CGameEffect {
public:
    CGameEffectDestroyWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectEquipWeapon : public CGameEffect {
public:
    CGameEffectEquipWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDither : public CGameEffect {
public:
    CGameEffectDither(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDispelInvisible : public CGameEffect {
public:
    CGameEffectDispelInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectShowArea : public CGameEffect {
public:
    CGameEffectShowArea(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectShowCreatures : public CGameEffect {
public:
    CGameEffectShowCreatures(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMirrorImage : public CGameEffect {
public:
    CGameEffectMirrorImage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectImmuneToWeapon : public CGameEffect {
public:
    CGameEffectImmuneToWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectVisualAnimationEffect : public CGameEffect {
public:
    CGameEffectVisualAnimationEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectCreateItem : public CGameEffect {
public:
    CGameEffectCreateItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDestroyItem : public CGameEffect {
public:
    CGameEffectDestroyItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectTeleport : public CGameEffect {
public:
    CGameEffectTeleport(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectKnock : public CGameEffect {
public:
    CGameEffectKnock(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMovementRate : public CGameEffect {
public:
    CGameEffectMovementRate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMovementRateWithPortrait : public CGameEffect {
public:
    CGameEffectMovementRateWithPortrait(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectConfusion : public CGameEffect {
public:
    CGameEffectConfusion(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectNon_CumulativeAid : public CGameEffect {
public:
    CGameEffectNon_CumulativeAid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectNon_CumulativeBless : public CGameEffect {
public:
    CGameEffectNon_CumulativeBless(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectNon_CumulativeChant : public CGameEffect {
public:
    CGameEffectNon_CumulativeChant(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectNon_CumulativeDrawUponHolyMight : public CGameEffect {
public:
    CGameEffectNon_CumulativeDrawUponHolyMight(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectNon_CumulativeLuck : public CGameEffect {
public:
    CGameEffectNon_CumulativeLuck(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPetrification : public CGameEffect {
public:
    CGameEffectPetrification();
    CGameEffectPetrification(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectPolymorph : public CGameEffect {
public:
    CGameEffectPolymorph(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectForceVisible : public CGameEffect {
public:
    CGameEffectForceVisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSetSequence : public CGameEffect {
public:
    CGameEffectSetSequence(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDisplayString : public CGameEffect {
public:
    CGameEffectDisplayString(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectVisualSpellHit : public CGameEffect {
public:
    CGameEffectVisualSpellHit(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectPortraitIcon : public CGameEffect {
public:
    CGameEffectPortraitIcon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectReplaceItem : public CGameEffect {
public:
    CGameEffectReplaceItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDisableButton : public CGameEffect {
public:
    CGameEffectDisableButton(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDisableSpellType : public CGameEffect {
public:
    CGameEffectDisableSpellType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCastSpell : public CGameEffect {
public:
    CGameEffectCastSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectLearnSpell : public CGameEffect {
public:
    CGameEffectLearnSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectCastSpellPoint : public CGameEffect {
public:
    CGameEffectCastSpellPoint(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectIdentify : public CGameEffect {
public:
    CGameEffectIdentify(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDetectTraps : public CGameEffect {
public:
    CGameEffectDetectTraps(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectReplaceSelf : public CGameEffect {
public:
    CGameEffectReplaceSelf(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectPlayMovie : public CGameEffect {
public:
    CGameEffectPlayMovie(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSanctuary : public CGameEffect {
public:
    CGameEffectSanctuary(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectEntangle : public CGameEffect {
public:
    CGameEffectEntangle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectWebHold : public CGameEffect {
public:
    CGameEffectWebHold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectGreasePool : public CGameEffect {
public:
    CGameEffectGreasePool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectMirrorImageRun : public CGameEffect {
public:
    CGameEffectMirrorImageRun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDispelSanctuary : public CGameEffect {
public:
    CGameEffectDispelSanctuary(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRemovePanic : public CGameEffect {
public:
    CGameEffectRemovePanic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRemoveHold : public CGameEffect {
public:
    CGameEffectRemoveHold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRestoreMovementRate : public CGameEffect {
public:
    CGameEffectRestoreMovementRate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRemoveIntoxication : public CGameEffect {
public:
    CGameEffectRemoveIntoxication(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPauseCaster : public CGameEffect {
public:
    CGameEffectPauseCaster(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistanceToMagic : public CGameEffect {
public:
    CGameEffectResistanceToMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMissileTHAC0Bonus : public CGameEffect {
public:
    CGameEffectMissileTHAC0Bonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDestroySelf : public CGameEffect {
public:
    CGameEffectDestroySelf(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImmunityToPortraitIcon : public CGameEffect {
public:
    CGameEffectImmunityToPortraitIcon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDamageVisualEffect : public CGameEffect {
public:
    CGameEffectDamageVisualEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAddInnateAbility : public CGameEffect {
public:
    CGameEffectAddInnateAbility(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectRemoveInnateAbility : public CGameEffect {
public:
    CGameEffectRemoveInnateAbility(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectResistanceToPoison : public CGameEffect {
public:
    CGameEffectResistanceToPoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPlaySound : public CGameEffect {
public:
    CGameEffectPlaySound(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHoldCreatureSpell : public CGameEffect {
public:
    CGameEffectHoldCreatureSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectApplyEffect : public CGameEffect {
public:
    CGameEffectApplyEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSelectiveToHitBonus : public CGameEffect {
public:
    CGameEffectSelectiveToHitBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSelectiveDamageBonus : public CGameEffect {
public:
    CGameEffectSelectiveDamageBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRestrictEquipItem : public CGameEffect {
public:
    CGameEffectRestrictEquipItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectRestrictEquipItemType : public CGameEffect {
public:
    CGameEffectRestrictEquipItemType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectApplyEffectEquipItem : public CGameEffect {
public:
    CGameEffectApplyEffectEquipItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectApplyEffectEquipItemType : public CGameEffect {
public:
    CGameEffectApplyEffectEquipItemType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSetDoNoJump : public CGameEffect {
public:
    CGameEffectSetDoNoJump(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectJumpToArea : public CGameEffect {
public:
    CGameEffectJumpToArea(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSetLocalVariable : public CGameEffect {
public:
    CGameEffectSetLocalVariable(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectAuraCleansing : public CGameEffect {
public:
    CGameEffectAuraCleansing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectMentalSpeed : public CGameEffect {
public:
    CGameEffectMentalSpeed(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPhysicalSpeed : public CGameEffect {
public:
    CGameEffectPhysicalSpeed(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectCastingLevelBonus : public CGameEffect {
public:
    CGameEffectCastingLevelBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectFeatCleave : public CGameEffect {
public:
    CGameEffectFeatCleave(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectFindFamiliar : public CGameEffect {
public:
    CGameEffectFindFamiliar(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectSeeInvisible : public CGameEffect {
public:
    CGameEffectSeeInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectIgnoreDialogPause : public CGameEffect {
public:
    CGameEffectIgnoreDialogPause(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectHitPointsOnDeath : public CGameEffect {
public:
    CGameEffectHitPointsOnDeath(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectFamiliarBlock : public CGameEffect {
public:
    CGameEffectFamiliarBlock(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBounceProjectile : public CGameEffect {
public:
    CGameEffectBounceProjectile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBounceEffect : public CGameEffect {
public:
    CGameEffectBounceEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBounceLevel : public CGameEffect {
public:
    CGameEffectBounceLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBounceLevelDecrement : public CGameEffect {
public:
    CGameEffectBounceLevelDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectImmunityLevelDecrement : public CGameEffect {
public:
    CGameEffectImmunityLevelDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBounceSchool : public CGameEffect {
public:
    CGameEffectBounceSchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBounceSecondaryType : public CGameEffect {
public:
    CGameEffectBounceSecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectImmunitySchool : public CGameEffect {
public:
    CGameEffectImmunitySchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImmunitySecondaryType : public CGameEffect {
public:
    CGameEffectImmunitySecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImmunitySpell : public CGameEffect {
public:
    CGameEffectImmunitySpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectBounceSpell : public CGameEffect {
public:
    CGameEffectBounceSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectMinHitPoints : public CGameEffect {
public:
    CGameEffectMinHitPoints(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPowerWordKill : public CGameEffect {
public:
    CGameEffectPowerWordKill(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPowerWordStun : public CGameEffect {
public:
    CGameEffectPowerWordStun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectImprisonment : public CGameEffect {
public:
    CGameEffectImprisonment(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectFreedom : public CGameEffect {
public:
    CGameEffectFreedom(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectMaze : public CGameEffect {
public:
    CGameEffectMaze(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSecondaryCastList : public CGameEffect {
public:
    CGameEffectSecondaryCastList(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectVisualEffect : public CGameEffect {
public:
    CGameEffectVisualEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectLevelDrain : public CGameEffect {
public:
    CGameEffectLevelDrain(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectPowerWordSleep : public CGameEffect {
public:
    CGameEffectPowerWordSleep(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectStoneSkins : public CGameEffect {
public:
    CGameEffectStoneSkins(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectProtectionCircle : public CGameEffect {
public:
    CGameEffectProtectionCircle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDispelSchool : public CGameEffect {
public:
    CGameEffectDispelSchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectDispelSecondaryType : public CGameEffect {
public:
    CGameEffectDispelSecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectRandomTeleport : public CGameEffect {
public:
    CGameEffectRandomTeleport(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectImmunitySchoolDecrement : public CGameEffect {
public:
    CGameEffectImmunitySchoolDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectLevelRestoration : public CGameEffect {
public:
    CGameEffectLevelRestoration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
};

class CGameEffectRevealMagic : public CGameEffect {
public:
    CGameEffectRevealMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectSecondaryTypeDecrement : public CGameEffect {
public:
    CGameEffectSecondaryTypeDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBounceSchoolDecrement : public CGameEffect {
public:
    CGameEffectBounceSchoolDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectBounceSecondaryTypeDecrement : public CGameEffect {
public:
    CGameEffectBounceSecondaryTypeDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDispelSchoolOne : public CGameEffect {
public:
    CGameEffectDispelSchoolOne(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDispelSecondaryTypeOne : public CGameEffect {
public:
    CGameEffectDispelSecondaryTypeOne(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectTimeStop : public CGameEffect {
public:
    CGameEffectTimeStop(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectDisguise : public CGameEffect {
public:
    CGameEffectDisguise(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;

    /* 018C */ int field_18C;
};

class CGameEffectHeroicInspiration : public CGameEffect {
public:
    CGameEffectHeroicInspiration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

class CGameEffectPreventAISlowdown : public CGameEffect {
public:
    CGameEffectPreventAISlowdown(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target);
    CGameEffect* Copy() override;
    BOOL ApplyEffect(CGameSprite* pSprite) override;
};

#endif /* CGAMEEFFECT_H_ */

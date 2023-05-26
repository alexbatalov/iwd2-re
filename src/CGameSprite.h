#ifndef CGAMESPRITE_H_
#define CGAMESPRITE_H_

#include "CAIObjectType.h"
#include "CDerivedStats.h"
#include "CGameAIBase.h"
#include "CResRef.h"
#include "CSound.h"

class CGameSprite : public CGameAIBase {
public:
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

    /* 0014 */ LONG GetTargetId() override;
    /* 003C */ BOOL OnSearchMap() override;
    /* 0044 */ void OnFormationButton(const CPoint& pt) override;
    /* 00BC */ virtual void SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart);
    /* 00C0 */ virtual void ResetAITypeLive();
    /* 00C4 */ virtual void ResetAIType();

    void PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption);
    void SetFootstepChannel();
    BYTE GetChannel();
    SHORT GetTurnUndeadLevel();
    SHORT GetLayOnHandsAmount();

    /* 0920 */ CDerivedStats m_derivedStats;
    /* 3DFA */ CAIObjectType m_liveTypeAI;
    /* 3E36 */ CAIObjectType m_startTypeAI;
    /* 4C6A */ CSound m_sndWalk[2];
    /* 4D36 */ CSound m_sndArmor[2];
    /* 4E00 */ CSound m_sndReady;
    /* 4E64 */ CSound m_sndDeath;
    /* 5690 */ LONG m_targetId;
};

#endif /* CGAMESPRITE_H_ */

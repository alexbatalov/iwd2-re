#ifndef CBALDURENGINE_H_
#define CBALDURENGINE_H_

#include "CUIManager.h"
#include "CWarp.h"

class CBaldurEngine : public CWarp {
public:
    static const CResRef RESREF_SOUND_CLICKLEFT;
    static const CResRef RESREF_SOUND_CLICKRIGHT;
    static const CResRef RESREF_SOUND_WINDOWOPEN;
    static const CResRef RESREF_SOUND_WINDOWCLOSE;
    static const CResRef RESREF_SOUND_MAGEBOOK;
    static const CResRef RESREF_SOUND_PRIESTSCROLL;
    static const CResRef RESREF_SOUND_POTION;
    static const CResRef RESREF_SOUND_EQUIP_TAKE_GENERIC;
    static const CResRef RESREF_SOUND_EQUIP_DROP_GENERIC;
    static const CResRef RESREF_SOUND_EQUIP_TAKE_LEATHER;
    static const CResRef RESREF_SOUND_EQUIP_DROP_LEATHER;
    static const CResRef RESREF_SOUND_EQUIP_TAKE_METAL;
    static const CResRef RESREF_SOUND_EQUIP_DROP_METAL;
    static const CResRef RESREF_SOUND_SMMTL1;
    static const CResRef RESREF_SOUND_SMMTL2;
    static const CResRef RESREF_SOUND_EQUIP_TAKE_WOOD;
    static const CResRef RESREF_SOUND_EQUIP_DROP_WOOD;
    static const CResRef RESREF_SOUND_BOOK1;
    static const CResRef RESREF_SOUND_BOOK2;
    static const CResRef RESREF_SOUND_NECK1;
    static const CResRef RESREF_SOUND_NECK2;
    static const CResRef RESREF_SOUND_LETHR1;
    static const CResRef RESREF_SOUND_LETHR2;
    static const CResRef RESREF_SOUND_CHAIN1;
    static const CResRef RESREF_SOUND_CHAIN2;
    static const CResRef RESREF_SOUND_PLATE1;
    static const CResRef RESREF_SOUND_PLATE2;
    static const CResRef RESREF_SOUND_BELT1;
    static const CResRef RESREF_SOUND_BELT2;
    static const CResRef RESREF_SOUND_GLOVE1;
    static const CResRef RESREF_SOUND_GLOVE2;
    static const CResRef RESREF_SOUND_BOOT1;
    static const CResRef RESREF_SOUND_BOOT2;
    static const CResRef RESREF_SOUND_ARRW1;
    static const CResRef RESREF_SOUND_ARRW2;
    static const CResRef RESREF_SOUND_HELM1;
    static const CResRef RESREF_SOUND_HELM2;
    static const CResRef RESREF_SOUND_KEY1;
    static const CResRef RESREF_SOUND_KEY2;
    static const CResRef RESREF_SOUND_POTN1;
    static const CResRef RESREF_SOUND_POTN2;
    static const CResRef RESREF_SOUND_SCROL1;
    static const CResRef RESREF_SOUND_SCROL2;
    static const CResRef RESREF_SOUND_BULLT1;
    static const CResRef RESREF_SOUND_BULLT2;
    static const CResRef RESREF_SOUND_BOW1;
    static const CResRef RESREF_SOUND_BOW2;
    static const CResRef RESREF_SOUND_DAGGR1;
    static const CResRef RESREF_SOUND_DAGGR2;
    static const CResRef RESREF_SOUND_MACE1;
    static const CResRef RESREF_SOUND_MACE2;
    static const CResRef RESREF_SOUND_SLING1;
    static const CResRef RESREF_SOUND_SLING2;
    static const CResRef RESREF_SOUND_HALB1;
    static const CResRef RESREF_SOUND_HALB2;
    static const CResRef RESREF_SOUND_HAMMR1;
    static const CResRef RESREF_SOUND_HAMMR2;
    static const CResRef RESREF_SOUND_AXE1;
    static const CResRef RESREF_SOUND_AXE2;
    static const CResRef RESREF_SOUND_FLAIL1;
    static const CResRef RESREF_SOUND_FLAIL2;
    static const CResRef RESREF_SOUND_CLOAK1;
    static const CResRef RESREF_SOUND_CLOAK2;
    static const CResRef RESREF_SOUND_GOLD1;
    static const CResRef RESREF_SOUND_GOLD2;
    static const CResRef RESREF_SOUND_GEM1;
    static const CResRef RESREF_SOUND_GEM2;
    static const CResRef RESREF_SOUND_SPEAR1;
    static const CResRef RESREF_SOUND_SPEAR2;
    static const CResRef RESREF_SOUND_STAFF1;
    static const CResRef RESREF_SOUND_STAFF2;
    static const CResRef RESREF_SOUND_WAND1;
    static const CResRef RESREF_SOUND_WAND2;
    static const CResRef RESREF_SOUND_CROSB1;
    static const CResRef RESREF_SOUND_CROSB2;
    static const CResRef RESREF_SOUND_MSTAR1;
    static const CResRef RESREF_SOUND_MSTAR2;
    static const CResRef RESREF_SOUND_SMSWD1;
    static const CResRef RESREF_SOUND_SMSWD2;
    static const CResRef RESREF_SOUND_LGSWD1;
    static const CResRef RESREF_SOUND_LGSWD2;
    static const CResRef RESREF_SOUND_RING1;
    static const CResRef RESREF_SOUND_RING2;
    static const CResRef RESREF_SOUND_BARM1;
    static const CResRef RESREF_SOUND_BARM2;
    static const CResRef RESREF_SOUND_BSHD1;
    static const CResRef RESREF_SOUND_BSHD2;
    static const CResRef RESREF_SOUND_BWPN1;
    static const CResRef RESREF_SOUND_BWPN2;
    static const CResRef RESREF_SOUND_BOLT1;
    static const CResRef RESREF_SOUND_BOLT2;
    static const CResRef RESREF_SOUND_BROKN1;
    static const CResRef RESREF_SOUND_BROKN2;
    static const CResRef RESREF_SOUND_BUCKR1;
    static const CResRef RESREF_SOUND_BUCKR2;
    static const CResRef RESREF_SOUND_CAND1;
    static const CResRef RESREF_SOUND_CAND2;
    static const CResRef RESREF_SOUND_CHILD1;
    static const CResRef RESREF_SOUND_CHILD2;
    static const CResRef RESREF_SOUND_CLUB1;
    static const CResRef RESREF_SOUND_CLUB2;
    static const CResRef RESREF_SOUND_DART1;
    static const CResRef RESREF_SOUND_DART2;
    static const CResRef RESREF_SOUND_FEM1;
    static const CResRef RESREF_SOUND_FEM2;
    static const CResRef RESREF_SOUND_KEYS1;
    static const CResRef RESREF_SOUND_KEYS2;
    static const CResRef RESREF_SOUND_LGSLD1;
    static const CResRef RESREF_SOUND_LGSLD2;
    static const CResRef RESREF_SOUND_MALE1;
    static const CResRef RESREF_SOUND_MALE2;
    static const CResRef RESREF_SOUND_MDSLD1;
    static const CResRef RESREF_SOUND_MDSLD2;
    static const CResRef RESREF_SOUND_PAPR1;
    static const CResRef RESREF_SOUND_PAPR2;
    static const CResRef RESREF_SOUND_ROD1;
    static const CResRef RESREF_SOUND_ROD2;
    static const CResRef RESREF_SOUND_SKULL1;
    static const CResRef RESREF_SOUND_SKULL2;
    static const CResRef RESREF_SOUND_SMSLD1;
    static const CResRef RESREF_SOUND_SMSLD2;
    static const CResRef RESREF_SOUND_SPIDR1;
    static const CResRef RESREF_SOUND_SPIDR2;
    static const CResRef RESREF_SOUND_TELE1;
    static const CResRef RESREF_SOUND_TELE2;
    static const CResRef RESREF_SOUND_WINE1;
    static const CResRef RESREF_SOUND_WINE2;
    static const CResRef RESREF_SOUND_8CF680;
    static const CResRef RESREF_SOUND_8CB1D0;
    static const CResRef RESREF_SOUND_8CB1B0;
    static const CResRef RESREF_SOUND_8CD390;
    static const CResRef RESREF_SOUND_8CF628;
    static const CResRef RESREF_SOUND_8CD260;
    static const CResRef RESREF_SOUND_8CF698;
    static const CResRef RESREF_SOUND_8CAD40;
    static const CResRef RESREF_SOUND_8CAD98;
    static const CResRef RESREF_SOUND_8C8C80;

    CBaldurEngine();
    ~CBaldurEngine();
    void InvalidateCursorRect(const CRect& rect) override;
    void ResetControls() override;

    /* 00CC */ virtual CUIManager* GetUIManager();
    /* 00D0 */ virtual int GetSelectedCharacter();
    /* 00D4 */ virtual int GetPickedCharacter();
    /* 00D8 */ virtual void SetSelectedCharacter(int nNewSelectedCharacter);
    /* 00DC */ virtual void SetPickedCharacter(int nNewPickedCharacter);

    /* 0028 */ int m_nSelectedCharacter;
    /* 002C */ int m_nPickedCharacter;
    /* 0030 */ CUIManager m_cUIManager;
    /* 00FA */ int field_FA;
    /* 00FE */ int field_FE;
    /* 0102 */ int field_102;
};

#endif /* CBALDURENGINE_H_ */

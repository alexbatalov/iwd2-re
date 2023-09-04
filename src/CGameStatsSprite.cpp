#include "CGameStatsSprite.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"

// 0x4CAE30
CGameStatsRes::CGameStatsRes()
{
    m_cResRef = "";
    m_nTimesUsed = 0;
}

// 0x78E730
CGameStatsRes::~CGameStatsRes()
{
}

// -----------------------------------------------------------------------------

// 0x4CAEC0
CGameStatsSprite::CGameStatsSprite()
{
    int index;

    m_strStrongestKillName = -1;
    m_nStrongestKillXPValue = 0;
    m_nJoinPartyTime = 0;
    m_nPreviousTimeWithParty = 0;
    m_bWithParty = FALSE;
    m_nChapterKillsXPValue = 0;
    m_nChapterKillsNumber = 0;
    m_nGameKillsXPValue = 0;
    m_nGameKillsNumber = 0;

    for (index = 0; index < CGAMESTATSSPRITE_SPELL_STATS; index++) {
        m_pSpellStats[index].m_cResRef = "";
        m_pSpellStats[index].m_nTimesUsed = 0;
    }

    for (index = 0; index < CGAMESTATSSPRITE_WEAPON_STATS; index++) {
        m_pWeaponStats[index].m_cResRef = "";
        m_pWeaponStats[index].m_nTimesUsed = 0;
    }
}

// 0x6F2D00
CGameStatsSprite::~CGameStatsSprite()
{
}

// 0x4CAFA0
void CGameStatsSprite::RecordKill(CGameSprite* pSprite)
{
    m_nChapterKillsNumber++;
    m_nGameKillsNumber++;

    m_nChapterKillsXPValue += pSprite->GetDerivedStats()->m_nXPValue;
    m_nGameKillsXPValue += pSprite->GetDerivedStats()->m_nXPValue;

    if (pSprite->GetDerivedStats()->m_nXPValue > m_nStrongestKillXPValue) {
        m_strStrongestKillName = pSprite->GetBaseStats()->m_name;
        m_nStrongestKillXPValue = pSprite->GetDerivedStats()->m_nXPValue;
    }
}

// 0x4CAFF0
void CGameStatsSprite::GetStrongestKill(STRREF& strName)
{
    strName = m_strStrongestKillName;
}

// 0x4CB000
void CGameStatsSprite::RecordJoinParty()
{
    if (!m_bWithParty) {
        m_nJoinPartyTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
        m_bWithParty = TRUE;
    }
}

// 0x4CB030
void CGameStatsSprite::RecordLeaveParty()
{
    if (m_bWithParty) {
        m_nPreviousTimeWithParty = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime - m_nJoinPartyTime;
        m_bWithParty = FALSE;
    }
}

// 0x4CB060
void CGameStatsSprite::GetTimeWithParty(ULONG& nCurrentTimeWithParty)
{
    nCurrentTimeWithParty = m_nPreviousTimeWithParty;
    if (m_bWithParty) {
        nCurrentTimeWithParty += g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime - m_nJoinPartyTime;
    }
}

// 0x4CB090
void CGameStatsSprite::RecordSpellUse(const CResRef& cResSpell)
{
    SHORT minValue = SHORT_MAX;
    int minIndex;

    int index;
    for (index = 0; index < CGAMESTATSSPRITE_SPELL_STATS; index++) {
        if (m_pSpellStats[index].m_cResRef == cResSpell) {
            m_pSpellStats[index].m_nTimesUsed++;
            break;
        }

        if (m_pSpellStats[index].m_nTimesUsed < minValue) {
            minValue = m_pSpellStats[index].m_nTimesUsed;
            minIndex = index;
        }
    }

    if (index == CGAMESTATSSPRITE_SPELL_STATS) {
        m_pSpellStats[minIndex].m_cResRef = cResSpell;
        m_pSpellStats[minIndex].m_nTimesUsed = 1;
    }
}

// 0x4CB140
void CGameStatsSprite::RecordWeaponUse(const CResRef& cResWeapon)
{
    SHORT minValue = SHORT_MAX;
    int minIndex;

    int index;
    for (index = 0; index < CGAMESTATSSPRITE_WEAPON_STATS; index++) {
        if (m_pWeaponStats[index].m_cResRef == cResWeapon) {
            m_pWeaponStats[index].m_nTimesUsed++;
            break;
        }

        if (m_pWeaponStats[index].m_nTimesUsed < minValue) {
            minValue = m_pWeaponStats[index].m_nTimesUsed;
            minIndex = index;
        }
    }

    if (index == CGAMESTATSSPRITE_WEAPON_STATS) {
        m_pWeaponStats[minIndex].m_cResRef = cResWeapon;
        m_pWeaponStats[minIndex].m_nTimesUsed = 1;
    }
}

// 0x4CB1F0
void CGameStatsSprite::GetFavouriteSpell(CResRef& cResSpell)
{
    cResSpell = "";

    SHORT maxValue = 0;

    for (int index = 0; index < CGAMESTATSSPRITE_SPELL_STATS; index++) {
        if (m_pSpellStats[index].m_nTimesUsed > maxValue) {
            cResSpell = m_pSpellStats[index].m_cResRef;
            maxValue = m_pSpellStats[index].m_nTimesUsed;
        }
    }
}

// 0x4CB250
void CGameStatsSprite::GetFavouriteWeapon(CResRef& cResWeapon)
{
    cResWeapon = "";

    SHORT maxValue = 0;

    for (int index = 0; index < CGAMESTATSSPRITE_WEAPON_STATS; index++) {
        if (m_pWeaponStats[index].m_nTimesUsed > maxValue) {
            cResWeapon = m_pWeaponStats[index].m_cResRef;
            maxValue = m_pWeaponStats[index].m_nTimesUsed;
        }
    }
}

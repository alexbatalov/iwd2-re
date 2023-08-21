#include "CGameSprite.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenInventory.h"
#include "CUtil.h"
#include "CVariableHash.h"

// 0x85BB38
const BYTE CGameSprite::DIR_S = 0;

// 0x85BB39
const BYTE CGameSprite::DIR_SW = 2;

// 0x85BB3A
const BYTE CGameSprite::DIR_W = 4;

// 0x85BB3B
const BYTE CGameSprite::DIR_NW = 6;

// 0x85BB3C
const BYTE CGameSprite::DIR_N = 8;

// 0x85BB3D
const BYTE CGameSprite::DIR_NE = 10;

// 0x85BB3E
const BYTE CGameSprite::DIR_E = 12;

// 0x85BB3F
const BYTE CGameSprite::DIR_SE = 14;

// 0x85BB40
const BYTE CGameSprite::DIR_SSW = 1;

// 0x85BB41
const BYTE CGameSprite::DIR_SWW = 3;

// 0x85BB42
const BYTE CGameSprite::DIR_NWW = 5;

// 0x85BB43
const BYTE CGameSprite::DIR_NNW = 7;

// 0x85BB44
const BYTE CGameSprite::DIR_NNE = 9;

// 0x85BB45
const BYTE CGameSprite::DIR_NEE = 11;

// 0x85BB46
const BYTE CGameSprite::DIR_SEE = 13;

// 0x85BB47
const BYTE CGameSprite::DIR_SSE = 15;

// 0x85BB48
const BYTE CGameSprite::NUM_DIR = 16;

// 0x8F94B8
const CPoint CGameSprite::PORTRAIT_ICON_SIZE(10, 10);

// 0x8F93F8
const CResRef CGameSprite::SPIN110("SPIN110");

// 0x8F92A0
const CResRef CGameSprite::SPIN111("SPIN111");

// 0x8F9328
const CResRef CGameSprite::SPIN107("SPIN107");

// 0x8F93E8
const CResRef CGameSprite::SPIN141("SPIN141");

// 0x8F92D0
const CResRef CGameSprite::SPIN142("SPIN142");

// 0x8F9468
const CResRef CGameSprite::SPIN143("SPIN143");

// 0x8F92C8
const CResRef CGameSprite::SPIN244("SPIN244");

// 0x8F94A0
const CResRef CGameSprite::SPIN245("SPIN245");

// 0x8F9488
const CResRef CGameSprite::SPIN246("SPIN246");

// 0x8F8E60
const CResRef CGameSprite::SPIN108("SPIN108");

// 0x8F92E0
const CResRef CGameSprite::SPIN109("SPIN109");

// 0x8F92B8
const CResRef CGameSprite::SPIN120("SPIN120");

// 0x8F9298
const CResRef CGameSprite::SPIN121("SPIN121");

// 0x8F9320
const CResRef CGameSprite::SPIN125("SPIN125");

// 0x8F9330
const CResRef CGameSprite::SPIN139("SPIN139");

// 0x8F9478
const CResRef CGameSprite::SPIN152("SPIN152");

// 0x8F9338
const CResRef CGameSprite::SPIN275("SPIN275");

// 0x8F8E70
const CResRef CGameSprite::SPIN276("SPIN276");

// 0x8F92F8
const CResRef CGameSprite::SPIN277("SPIN277");

// 0x8F92E8
const CResRef CGameSprite::SPIN278("SPIN278");

// 0x8F93D0
const CResRef CGameSprite::SPIN279("SPIN279");

// 0x8F8E18
const CResRef CGameSprite::SPIN970("SPIN970");

// 0x8F94B0
const CResRef CGameSprite::SPIN197("SPIN197");

// 0x8F8E90
const CResRef CGameSprite::SPPR327("SPPR327");

// 0x8F94D0
const CResRef CGameSprite::SPPR328("SPPR328");

// 0x8F92A8
const CResRef CGameSprite::SPPR429("SPPR429");

// 0x8F9460
const CResRef CGameSprite::SPIN198("SPIN198");

// 0x8F9448
const CResRef CGameSprite::SPIN199("SPIN199");

// 0x8F9300
const CResRef CGameSprite::SPIN200("SPIN200");

// 0x8F8E30
const CResRef CGameSprite::SPIN243("SPIN243");

// 0x8F9438
const CResRef CGameSprite::SPIN201("SPIN201");

// 0x8F9308
const CResRef CGameSprite::SPIN202("SPIN202");

// 0x8F8E28
const CResRef CGameSprite::SPIN203("SPIN203");

// 0x8F9418
const CResRef CGameSprite::SPIN247("SPIN247");

// 0x8F9348
const CResRef CGameSprite::SPIN204("SPIN204");

// 0x8F9490
const CResRef CGameSprite::SPIN205("SPIN205");

// 0x8F92B0
const CResRef CGameSprite::SPIN206("SPIN206");

// 0x8F9458
const CResRef CGameSprite::SPIN207("SPIN207");

// 0x8F9470
const CResRef CGameSprite::SPIN208("SPIN208");

// 0x8F9498
const CResRef CGameSprite::SPIN209("SPIN209");

// 0x8F8E88
const CResRef CGameSprite::SPIN210("SPIN210");

// 0x8F94C0
const CResRef CGameSprite::SPIN231("SPIN231");

// 0x8F94A8
const CResRef CGameSprite::SPIN191("SPIN191");

// 0x8F8E48
const CResRef CGameSprite::SPIN211("SPIN211");

// 0x8F8E78
const CResRef CGameSprite::SPIN212("SPIN212");

// 0x8F8E40
const CResRef CGameSprite::SPIN213("SPIN213");

// 0x8F9428
const CResRef CGameSprite::SPIN214("SPIN214");

// 0x8F8E58
const CResRef CGameSprite::SPIN215("SPIN215");

// 0x8F94E8
const CResRef CGameSprite::SPIN216("SPIN216");

// 0x8F92C0
const CResRef CGameSprite::SPIN217("SPIN217");

// 0x8F9400
const CResRef CGameSprite::SPIN218("SPIN218");

// 0x8F9310
const CResRef CGameSprite::SPIN229("SPIN229");

// 0x8F94D8
const CResRef CGameSprite::SPIN232("SPIN232");

// 0x8F93E0
const CResRef CGameSprite::SPIN233("SPIN233");

// 0x8F8E68
const CResRef CGameSprite::SPIN234("SPIN234");

// 0x8F93D8
const CResRef CGameSprite::SPIN235("SPIN235");

// 0x8F9410
const CResRef CGameSprite::SPIN236("SPIN236");

// 0x8F8E20
const CResRef CGameSprite::SPIN260("SPIN260");

// 0x8F9340
const CString CGameSprite::FA("FA_");

// 0x8F9430
const CString CGameSprite::GA("GA_");

// 0x8F94E0
const CString CGameSprite::RA("RA_");

// 0x8F94C8
const CString CGameSprite::AP("AP_");

// 0x8F9480
const CResRef CGameSprite::SPWI110("SPWI110");

// 0x8F9408
const CResRef CGameSprite::SPIN122("SPIN122");

// 0x8F93F0
const CResRef CGameSprite::SPIN285("SPIN285");

// 0x8F950C
BOOLEAN CGameSprite::SHOW_CHARACTER_HP;

// 0x8F950D
BOOLEAN CGameSprite::GRAVITY_IS_DOWN;

// 0x6EF990
CGameSprite::CGameSprite(BYTE* pCreature, LONG creatureSize, int a3, WORD type, DWORD expirationTime, WORD huntingRange, WORD followRange, DWORD timeOfDayVisible, CPoint startPos, WORD facing)
{
    int index;

    field_7540 = 0;
    field_7544 = 0;
    field_5101 = 0;
    field_5102 = 0;
    field_5103 = 0;
    m_bEscapingArea = 0;
    field_4D32 = 0;
    field_4DFE = 0;
    field_5320 = 0;
    field_5322 = 0;
    field_5326 = 0;
    field_533E = 0;
    field_533C = 0;
    field_5340 = 0;
    field_5344 = 0;
    m_skipDeltaDirection = 0;
    m_deltaDirection = 0;
    m_walkBackwards = 0;
    field_53C6 = 0;
    field_54EE = 0;
    field_54F4 = 0;
    field_556E = 0;
    field_5572 = 0;
    field_5372 = 0;
    field_5376 = 0;
    m_nCommandPause = 0;
    field_557A = 0;
    field_557E = 0;
    field_558E = 0;
    field_559E = 0;
    field_55A0 = 0;
    field_5604 = 0;
    field_5606 = 0;
    field_560E = 0;
    field_5610 = 0;
    field_5618 = 0;
    field_561C = 0;
    field_5624 = 0;
    field_5630 = 0;
    field_5632 = 0;
    field_5636 = 0;
    field_7118 = 0;
    field_711C = 0;
    field_7226 = 0;
    field_7292 = 0;
    m_currentActionId = 0;
    field_72A8 = 0;
    field_72B6 = 0;
    field_72D6 = 0;
    field_72DE = 0;
    field_7532 = 0;
    field_7536 = 0;
    field_9D08 = 0;
    field_9D0C = 0;
    field_9D10 = 0;
    m_objectType = TYPE_SPRITE;
    m_resRef = "";
    field_532C = 0;
    field_5330 = 0;
    field_5334 = 0;
    field_5338 = 1.875;
    m_bGlobal = FALSE;
    field_534A = 0;
    field_534E = 0;
    field_5352 = 0;
    field_5356 = 0;
    m_posDest.x = 0;
    m_posDest.y = 0;
    field_5362 = 0;
    field_5366 = 0;
    field_536A = 0;
    field_536E = 0;
    m_nSequence = -1;
    m_nNewDirection = facing & 0xF;
    m_nDirection = facing & 0xF;
    m_pPath = 0;
    m_nPath = 0;
    m_currPath = 0;
    field_53CE = 0;
    field_54F2 = 17;
    field_53D2 = 0;
    m_currentSearchRequest = 0;
    field_4BB4 = 0;
    field_56EC = 0;
    field_5644 = 0;
    m_talkingCounter = 0;
    field_54F6 = 0;
    field_54F8 = 0;
    m_curResponseNum = -1;
    m_curResponseSetNum = -1;
    m_curScriptNum = -1;
    m_curAction = CAIAction::NULL_ACTION;
    m_interrupt = FALSE;
    field_5608 = 0;
    field_5628 = 0;
    m_lastRGBColor = 0x8000;
    m_bVisibilityUpdated = TRUE;
    m_targetId = (int)CGameObjectArray::INVALID_INDEX;
    m_targetPoint.x = -1;
    m_targetPoint.y = -1;
    m_targetAreaSize = 0;
    m_destMarker.SetType(CMarker::RECTICLE);
    field_722E = CGameObjectArray::INVALID_INDEX;
    m_typeAI.Set(CAIObjectType::ANYONE);
    m_liveTypeAI.Set(CAIObjectType::ANYONE);
    m_startTypeAI.Set(CAIObjectType::ANYONE);
    field_3F6 = 0;
    field_3FA = 0;
    field_3FE = 0;
    field_402 = 0;
    field_406 = 0;
    field_40A = 0;
    m_defaultScript = NULL;
    field_54BC = 0;
    field_54C0 = 0;
    field_54C4 = (int)CGameObjectArray::INVALID_INDEX;
    m_followStart = 0;
    field_5576 = 0;
    field_5620 = 0;
    field_561E = 0;
    field_44A = 0;
    field_54C = 0;
    field_560C = 0;
    field_5616 = 0;
    field_5612 = 0;
    field_5614 = 0;
    field_54E8 = -1;
    field_54EA = 0;
    field_5622 = -2;
    field_72A2 = 0;
    m_bAllowEffectListCall = TRUE;
    field_72AA = 0;
    field_7292 = 0;
    field_5582 = 0;
    field_9D14 = 0;
    field_9D15 = 0;
    field_5638 = 0;
    field_563C = 0;
    field_5640 = 0;
    m_groupPosition = 0;
    m_groupMove = 0;
    field_562C = 0;
    field_5592 = 0;
    field_5596 = 0;
    field_559A = 0;
    m_nNumberOfTimesTalkedTo = 0;
    field_4FF8 = 0;
    field_710A = 0;
    field_710C = 0;
    field_710E = 0;
    field_7110 = 0x7FFF;
    field_7114 = 0;
    m_nHappiness = 0;
    m_bHappinessChanged = FALSE;
    field_72AE = 1;
    m_lastRegenerationTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;

    CButtonData buttonData;

    for (index = 0; index < 8; index++) {
        field_342C[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        field_360C[index] = buttonData;
    }

    for (index = 0; index < 3; index++) {
        field_3828[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        field_38DC[index] = buttonData;
    }

    for (index = 0; index < 9; index++) {
        field_3AF8[index] = buttonData;
    }

    field_70F6 = rand() % 20 + 1;
    field_70F7 = rand() % 20 + 1;
    field_70F8 = rand() % 20 + 1;
    field_70F9 = rand() % 20 + 1;
    field_70FA = rand() % 100;
    field_55F2 = 0;
    field_55F6 = 0;
    field_55FA = 0;
    field_55FE = 0;
    field_5602 = 0;

    for (index = 0; index < 20; index++) {
        field_55A2[index] = -65538;
    }

    memset(field_5004, 0, sizeof(field_5004));

    field_54B8 = 0;
    field_54A8 = 0;
    field_54AC = 0;
    field_54B0 = -1;
    field_54B4 = -1;
    field_54A4 = 0;
    m_bSelected = FALSE;
    field_50BA = 0;
    field_50B6 = 0;
    field_53DA = 0;
    field_53DC = 0;
    field_53DE = 0x1E1EFF;
    field_53E2 = 0;
    field_53E6 = 0;
    field_50FE = 0;

    // NOTE: See `CGameArea` note on default terrain tables.
    memcpy(m_terrainTable, DEFAULT_TERRAIN_TABLE, 16);
    memcpy(m_visibleTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);
    memcpy(m_flightTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);

    if (g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id, this, INFINITE) == CGameObjectArray::SUCCESS) {
        m_pSpriteEffectArray = NULL;
        m_pSpriteEffectArrayPosition = NULL;
        m_spriteEffectDuration = 0;
        field_5202 = 0;
        field_5304 = 0;
        field_532A = 3;
        field_4C53 = 0;
        field_4C54 = 0;
        field_4C58 = 0;
        field_4C5C = 0;
        field_4C60 = 0;
        field_4C64 = 0;
        field_4C68 = 0;

        field_7548[0].SetResRef(CResRef("SanctuC"), FALSE, TRUE);
        field_7548[1].SetResRef(CResRef("EntangC"), FALSE, TRUE);
        field_7548[6].SetResRef(CResRef("MGoInvC"), FALSE, TRUE);
        field_7548[3].SetResRef(CResRef("ShieldC"), FALSE, TRUE);
        field_7548[4].SetResRef(CResRef("GreaseC"), FALSE, TRUE);
        field_7548[5].SetResRef(CResRef("WebC"), FALSE, TRUE);
        field_7548[7].SetResRef(CResRef("GoInvuC"), FALSE, TRUE);
        field_7548[8].SetResRef(CResRef("SoFlamC"), FALSE, TRUE);
        field_7548[9].SetResRef(CResRef("AMShelC"), FALSE, TRUE);
        field_7548[10].SetResRef(CResRef("ORSpheC"), FALSE, TRUE);
        field_7548[11].SetResRef(CResRef("PFNMisC"), FALSE, TRUE);
        field_7548[12].SetResRef(CResRef("CoFearC"), FALSE, TRUE);
        field_7548[13].SetResRef(CResRef("EShielC"), FALSE, TRUE);
        field_7548[14].SetResRef(CResRef("FiAuraC"), FALSE, TRUE);
        field_7548[15].SetResRef(CResRef("FrAuraC"), FALSE, TRUE);
        field_7548[16].SetResRef(CResRef("IPlaguC"), FALSE, TRUE);
        field_7548[17].SetResRef(CResRef("SShellC"), FALSE, TRUE);
        field_7548[18].SetResRef(CResRef("SoLatC1"), FALSE, TRUE);
        field_7548[19].SetResRef(CResRef("SoLatC2"), FALSE, TRUE);
        field_7548[20].SetResRef(CResRef("GSoLaC1"), FALSE, TRUE);
        field_7548[21].SetResRef(CResRef("GSoLaC2"), FALSE, TRUE);
        field_7548[22].SetResRef(CResRef("SEyesC1"), FALSE, TRUE);
        field_7548[23].SetResRef(CResRef("SEyesC2"), FALSE, TRUE);
        field_7548[26].SetResRef(CResRef("FShiRC1"), FALSE, TRUE);
        field_7548[28].SetResRef(CResRef("FShiRC1"), FALSE, TRUE);
        field_7548[27].SetResRef(CResRef("FShiBC1"), FALSE, TRUE);
        field_7548[29].SetResRef(CResRef("FShiBC1"), FALSE, TRUE);
        field_7548[31].SetResRef(CResRef("DArmorC"), FALSE, TRUE);
        field_7548[30].SetResRef(CResRef("TShellC"), FALSE, TRUE);
        field_7548[2].SetResRef(CResRef("Wisp"), FALSE, TRUE);

        field_9088[7].SetResRef(CResRef("AFT_M05"), TRUE, TRUE);
        field_9088[8].SetResRef(CResRef("MISC_01C"), TRUE, TRUE);
        field_9088[9].SetResRef(CResRef("AFT_M04"), TRUE, TRUE);
        field_9088[10].SetResRef(CResRef("AFT_M03"), TRUE, TRUE);
        field_9088[11].SetResRef(CResRef("AFT_M01"), TRUE, TRUE);
        field_9088[12].SetResRef(CResRef("AFT_P02"), TRUE, TRUE);
        field_9088[13].SetResRef(CResRef("AFT_P03"), TRUE, TRUE);
        field_9088[17].SetResRef(CResRef("AFT_P25"), TRUE, TRUE);
        field_9088[18].SetResRef(CResRef("AFT_P20"), TRUE, TRUE);
        field_9088[20].SetResRef(CResRef("AFT_P26"), TRUE, TRUE);
        field_9088[0].SetResRef(CResRef("AFT_P01"), TRUE, TRUE);
        field_9088[6].SetResRef(CResRef("AFT_M02"), TRUE, TRUE);
        field_9088[3].SetResRef(CResRef("EFF_M11C"), TRUE, TRUE);

        m_type = type;
        m_expirationTime = expirationTime;
        m_huntingRange = huntingRange;
        m_followRange = followRange;
        m_posStart = startPos;
        m_timeOfDayVisible = timeOfDayVisible;

        field_50AA = 1;
        field_50AE = 1;

        memset(&m_baseStats, 0, sizeof(m_baseStats));

        field_4BAC = 0;
        field_4BB0 = 0;
        m_dialogWait = 0;
        m_dialogWaitTarget = CGameObjectArray::INVALID_INDEX;
        field_724C = 1;
        field_56E4 = "";
        field_712E = 0;
        field_711E = 1;

        if (m_portraitIconVidCell.pRes != NULL) {
            m_portraitIconVidCell.pRes->Request();
        }

        field_722A = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
        m_interactingWith.Set(CAIObjectType::NOONE);
        field_7234 = 0;
        field_7238 = 1;
        field_723C = 0;
        field_7240 = 0;
        m_secondarySounds = "";

        memset(field_725A, 0, sizeof(field_725A));

        field_727E = 0;
        field_72B2 = new CVariableHash(16);
        field_72E6 = 0;

        SleepEx(10, FALSE);
        Unmarshal(pCreature, creatureSize, facing, a3);
        SleepEx(10, FALSE);
        UnmarshalScripts();
        SleepEx(10, FALSE);

        // NOTE: Inlining as `STR_RES` object is immediately destroyed.
        if (1) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_name, strRes);
            m_sName = strRes.szText;
        }

        for (index = 0; index < 3; index++) {
            g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[33 + index],
                m_speech[33 + index]);
        }

        for (index = 0; index < 7; index++) {
            g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_speech[15 + index],
                m_speech[15 + index]);
        }

        for (index = 0; index < 2; index++) {
            m_sndWalk[index].m_nVolumeVariance = 50;
        }

        // TODO: Incomplete(0x6F2552).
    } else {
        // FIXME: Does not look cool.
        delete this;
    }
}

// 0x6F2990
BOOL CGameSprite::DoesIntersect(CRect r)
{
    r.InflateRect(0, 0, 1, 1);

    CRect rEllipse = m_animation.GetEllipseRect();
    rEllipse.OffsetRect(m_pos);

    CRect rIntersection;
    rIntersection.IntersectRect(r, rEllipse);

    return !rIntersection.IsRectNull();
}

// 0x6F2B50
const BYTE* CGameSprite::GetVisibleTerrainTable()
{
    return m_visibleTerrainTable;
}

// 0x
BOOL CGameSprite::OnSearchMap()
{
    return ((m_listType == LIST_FRONT || (m_derivedStats.m_generalState & 0x1) != 0))
        && m_pArea != NULL
        && m_pos.x >= 0
        && m_pos.y >= 0;
}

// 0x6F2B90
void CGameSprite::SetAIType(const CAIObjectType& typeAI, BOOL updateLive, BOOL updateStart)
{
    m_typeAI.Set(typeAI);

    if (updateLive) {
        m_liveTypeAI.Set(typeAI);
    }

    if (updateStart) {
        m_startTypeAI.Set(typeAI);
    }
}

// 0x6F2BD0
void CGameSprite::ResetAITypeLive()
{
    m_typeAI.m_nGeneral = m_liveTypeAI.m_nGeneral;
    m_startTypeAI.m_nGeneral = m_liveTypeAI.m_nGeneral;
}

// 0x6F2BF0
void CGameSprite::ResetAIType()
{
    m_typeAI.Set(m_startTypeAI);

    BYTE prev = m_liveTypeAI.m_nGeneral;
    m_liveTypeAI.Set(m_startTypeAI);
    m_liveTypeAI.m_nGeneral = prev;
}

// 0x6F2C50
LONG CGameSprite::GetTargetId()
{
    return m_targetId;
}

// 0x6F2C60
const BYTE* CGameSprite::GetTerrainTable()
{
    return m_terrainTable;
}

// 0x6FF2F0
void CGameSprite::DropPath()
{
    if (m_pPath != NULL) {
        delete m_pPath;
        m_pPath = NULL;
    }
}

// 0x700BB0
void CGameSprite::OnFormationButton(const CPoint& pt)
{
    if (m_canBeSeen > 0) {
        PlaySound(9, 1, 0, 1);
    } else {
        CGameObject::OnFormationButton(pt);
    }
}

// 0x700BE0
void CGameSprite::OnLightningStrike()
{
    // TODO: Incomplete.
}

// 0x700F20
void CGameSprite::MakeGlobal()
{
    if (!m_bGlobal) {
        m_bGlobal = TRUE;

        g_pBaldurChitin->GetObjectGame()->m_lstGlobalCreatures.AddTail(reinterpret_cast<int*>(m_id));

        CVariable v;
        v.SetName(CString(GetScriptName()));
        v.m_intValue = m_id;
        g_pBaldurChitin->GetObjectGame()->GetNamedCreatures()->AddKey(v);
    }
}

// 0x700FE0
SHORT CGameSprite::GetNumSounds(SHORT nOffset, SHORT nMaxNum)
{
    SHORT nSounds = 0;

    if (m_secondarySounds == "") {
        for (INT nIndex = 0; nIndex < nMaxNum; nIndex++) {
            if (m_baseStats.m_speech[nOffset + nIndex] == -1) {
                break;
            }

            nSounds++;
        }
    } else {
        nSounds = nMaxNum;
    }

    return nSounds;
}

// 0x7011E0
void CGameSprite::PlaySound(BYTE soundID, BOOL showText, BOOL showCircle, BOOL overrideOption)
{
    // TODO: Incomplete.
}

// 0x703170
BOOL CGameSprite::IsSpellSchool(BYTE spellSchool)
{
    return ((GetSpecialization() & SPECMASK_WIZARD_ABJURER) != 0 && spellSchool == 1)
        || ((GetSpecialization() & SPECMASK_WIZARD_CONJURER) != 0 && spellSchool == 2)
        || ((GetSpecialization() & SPECMASK_WIZARD_DIVINER) != 0 && spellSchool == 3)
        || ((GetSpecialization() & SPECMASK_WIZARD_ENCHANTER) != 0 && spellSchool == 4)
        || ((GetSpecialization() & SPECMASK_WIZARD_ILLUSIONIST) != 0 && spellSchool == 5)
        || ((GetSpecialization() & SPECMASK_WIZARD_EVOKER) != 0 && spellSchool == 6)
        || ((GetSpecialization() & SPECMASK_WIZARD_NECROMANCER) != 0 && spellSchool == 7)
        || ((GetSpecialization() & SPECMASK_WIZARD_TRANSMUTER) != 0 && spellSchool == 8)
        || ((GetSpecialization() & SPECMASK_WIZARD_UNIVERSAL) != 0 && spellSchool == 9);
}

// 0x703270
void CGameSprite::SetFootstepChannel()
{
    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id) == -1) {
        for (int index = 0; index < 2; index++) {
            m_sndWalk[index].SetChannel(19, reinterpret_cast<DWORD>(m_pArea));
            m_sndArmor[index].SetChannel(20, reinterpret_cast<DWORD>(m_pArea));
        }
        m_sndReady.SetChannel(19, reinterpret_cast<DWORD>(m_pArea));
        m_sndDeath.SetChannel(15, reinterpret_cast<DWORD>(m_pArea));
    } else {
        for (int index = 0; index < 2; index++) {
            m_sndWalk[index].SetChannel(18, reinterpret_cast<DWORD>(m_pArea));
            m_sndArmor[index].SetChannel(20, reinterpret_cast<DWORD>(m_pArea));
        }
        m_sndReady.SetChannel(18, reinterpret_cast<DWORD>(m_pArea));
        m_sndDeath.SetChannel(15, reinterpret_cast<DWORD>(m_pArea));
    }
}

// 0x703330
BYTE CGameSprite::GetSound(BYTE soundID)
{
    // NOTE: Unused.
    STR_RES strRes;

    SHORT nNumSounds;
    BYTE nSound;

    switch (soundID) {
    case 2:
        nNumSounds = GetNumSounds(7, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 7;
        } else {
            nSound = 7;
        }
        break;
    case 3:
        nNumSounds = GetNumSounds(9, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 9;
        } else {
            nSound = 9;
        }
        break;
    case 4:
        nNumSounds = GetNumSounds(11, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 11;
        } else {
            nSound = 11;
        }
        break;
    case 5:
        nNumSounds = GetNumSounds(2, 5);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 2;
        } else {
            nSound = 2;
        }
        break;
    case 6:
        nNumSounds = GetNumSounds(33, 3);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 33;
        } else {
            nSound = 33;
        }
        break;
    case 7:
        nNumSounds = GetNumSounds(36, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 36;
        } else {
            nSound = 36;
        }
        break;
    case 8:
        nNumSounds = GetNumSounds(13, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 13;
        } else {
            nSound = 13;
        }
        break;
    case 9:
        if (field_710C > 8) {
            nSound = field_710E + 29;
            field_710E++;
            if (field_710E >= GetNumSounds(29, 4)) {
                field_710E = 0;
            }
            field_710A = 0;
            field_710C = 0;
        } else {
            nNumSounds = GetNumSounds(15, 7);
            if (nNumSounds > 0) {
                nSound = field_710A % nNumSounds;
            } else {
                nSound = 0;
            }
            field_710A++;
            field_710C++;
        }
        break;
    case 10:
        nNumSounds = GetNumSounds(15, 7);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 15;
        } else {
            nSound = 15;
        }
        break;
    case 11:
        nNumSounds = GetNumSounds(22, 7);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 22;
        } else {
            nSound = 22;
        }
        break;
    case 12:
        nNumSounds = GetNumSounds(29, 4);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 29;
        } else {
            nSound = 29;
        }
        break;
    case 13:
        nNumSounds = GetNumSounds(38, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 38;
        } else {
            nSound = 38;
        }
        break;
    case 14:
        nNumSounds = GetNumSounds(40, 4);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 40;
        } else {
            nSound = 40;
        }
        break;
    case 15:
        // FIXME: Not sure if it can overrun `m_speech` and treat `m_biography`
        // as sound?
        nNumSounds = GetNumSounds(44, 20);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 44;
        } else {
            nSound = 44;
        }
        break;
    case 16:
        nNumSounds = GetNumSounds(40, 2);
        if (nNumSounds != 0) {
            nSound = rand() % nNumSounds + 40;
        } else {
            nSound = 40;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 7658
        UTIL_ASSERT(FALSE);
    }

    return nSound;
}

// 0x7071F0
SHORT CGameSprite::GetIdleSequence()
{
    if (m_pArea != NULL
        && m_pArea->m_bAreaLoaded
        && g_pBaldurChitin->GetObjectGame()->sub_5AC0A0(m_pArea)) {
        return 7; // SEQ_READY
    } else {
        return 6; // SEQ_HEAD_TURN
    }
}

// 0x70CF90
void CGameSprite::Unmarshal(BYTE* pCreature, LONG creatureSize, WORD facing, int a4)
{
    // TODO: Incomplete.

    memcpy(&m_baseStats, pCreature + 8, sizeof(m_baseStats));

    m_animation.SetAnimationType(m_baseStats.m_animationType, m_baseStats.m_colors, facing);
}

// 0x70E750
void CGameSprite::UnmarshalScripts()
{
    // TODO: Incomplete.
}

// 0x70F270
BYTE CGameSprite::GetChannel()
{
    SHORT nPortraitNum = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(m_id);
    if (nPortraitNum != -1) {
        return nPortraitNum + 7;
    }
    return 13;
}

// 0x718650
CItem* CGameSprite::GetLauncher(const ITEM_ABILITY* ability, SHORT& launcherSlot)
{
    int index;
    launcherSlot = 0;

    if (ability == NULL || ability->type != 2) {
        return NULL;
    }

    switch (ability->launcherType) {
    case 1:
        launcherSlot = 2 * field_4C68 + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 15) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 15) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    case 2:
        launcherSlot = 2 * field_4C68 + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 27) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 27) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    case 3:
        launcherSlot = 2 * field_4C68 + 43;

        if (m_equipment.m_items[launcherSlot] != NULL
            && m_equipment.m_items[launcherSlot]->GetItemType() == 18) {
            return m_equipment.m_items[launcherSlot];
        }

        for (index = 0; index < 8; index++) {
            if (m_equipment.m_items[43 + index] != NULL
                && m_equipment.m_items[43 + index]->GetItemType() == 18) {
                return m_equipment.m_items[43 + index];
            }
        }

        break;
    }

    return NULL;
}

// 0x71B460
void CGameSprite::UnequipAll(BOOL animationOnly)
{
    if (m_equipment.m_items[6] != NULL) {
        m_equipment.m_items[6]->Unequip(this, 6, TRUE, animationOnly);
    }

    if (m_equipment.m_items[1] != NULL) {
        m_equipment.m_items[1]->Unequip(this, 1, TRUE, animationOnly);
    }

    if (m_equipment.m_items[5] != NULL) {
        m_equipment.m_items[5]->Unequip(this, 5, TRUE, animationOnly);
    }

    if (m_equipment.m_items[7] != NULL) {
        m_equipment.m_items[7]->Unequip(this, 7, TRUE, animationOnly);
    }

    if (m_equipment.m_items[8] != NULL) {
        m_equipment.m_items[8]->Unequip(this, 8, TRUE, animationOnly);
    }

    if (m_equipment.m_items[0] != NULL) {
        m_equipment.m_items[0]->Unequip(this, 0, TRUE, animationOnly);
    }

    if (m_equipment.m_items[2] != NULL) {
        m_equipment.m_items[2]->Unequip(this, 2, TRUE, animationOnly);
    }

    if (m_equipment.m_items[3] != NULL) {
        m_equipment.m_items[3]->Unequip(this, 3, TRUE, animationOnly);
    }

    if (m_equipment.m_items[4] != NULL) {
        m_equipment.m_items[4]->Unequip(this, 4, TRUE, animationOnly);
    }

    BYTE nIndex = 2 * (field_4C68 + 22);
    if (m_equipment.m_items[nIndex] != NULL) {
        m_equipment.m_items[nIndex]->Unequip(this, nIndex, TRUE, animationOnly);
    }

    if (m_equipment.m_items[m_equipment.m_selectedWeapon] != NULL) {
        m_equipment.m_items[m_equipment.m_selectedWeapon]->Unequip(this, nIndex, TRUE, animationOnly);

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Demand();
        ITEM_ABILITY* pAbility = m_equipment.m_items[m_equipment.m_selectedWeapon]->GetAbility(m_equipment.m_selectedWeaponAbility);

        SHORT lSlot;
        CItem* pLauncher = GetLauncher(pAbility, lSlot);
        if (pLauncher != NULL) {
            pLauncher->Unequip(this, lSlot, TRUE, animationOnly);
        }

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Release();
    }
}

// 0x71B5E0
void CGameSprite::EquipAll(BOOL animationOnly)
{
    if (m_equipment.m_items[6] != NULL) {
        m_equipment.m_items[6]->Unequip(this, 6, TRUE, animationOnly);
    }

    if (m_equipment.m_items[1] != NULL) {
        m_equipment.m_items[1]->Unequip(this, 1, TRUE, animationOnly);
    }

    if (m_equipment.m_items[5] != NULL) {
        m_equipment.m_items[5]->Unequip(this, 5, TRUE, animationOnly);
    }

    if (m_equipment.m_items[7] != NULL) {
        m_equipment.m_items[7]->Unequip(this, 7, TRUE, animationOnly);
    }

    if (m_equipment.m_items[8] != NULL) {
        m_equipment.m_items[8]->Unequip(this, 8, TRUE, animationOnly);
    }

    if (m_equipment.m_items[0] != NULL) {
        m_equipment.m_items[0]->Unequip(this, 0, TRUE, animationOnly);
    }

    if (m_equipment.m_items[2] != NULL) {
        m_equipment.m_items[2]->Unequip(this, 2, TRUE, animationOnly);
    }

    if (m_equipment.m_items[3] != NULL) {
        m_equipment.m_items[3]->Unequip(this, 3, TRUE, animationOnly);
    }

    if (m_equipment.m_items[4] != NULL) {
        m_equipment.m_items[4]->Unequip(this, 4, TRUE, animationOnly);
    }

    BOOL v1 = FALSE;
    BYTE v2 = 2 * field_4C68 + 43;
    if (m_equipment.m_selectedWeapon == v2) {
        v1 = TRUE;
    }

    if (m_equipment.m_items[m_equipment.m_selectedWeapon] != NULL) {
        m_equipment.m_items[m_equipment.m_selectedWeapon]->Equip(this, m_equipment.m_selectedWeapon, animationOnly);

        m_equipment.m_items[m_equipment.m_selectedWeapon]->Demand();

        ITEM_ABILITY* pAbility = m_equipment.m_items[m_equipment.m_selectedWeapon]->GetAbility(m_equipment.m_selectedWeaponAbility);

        SHORT lSlot;
        CItem* pLauncher = GetLauncher(pAbility, lSlot);
        if (pLauncher != NULL) {
            pLauncher->Equip(this, lSlot, animationOnly);

            if (lSlot == v2) {
                v1 = TRUE;
            }
        }
    }

    BYTE v3 = 2 * (field_4C68 + 22);
    if (m_equipment.m_items[v3] != NULL && v1 == TRUE) {
        m_equipment.m_items[v3]->Equip(this, v3, animationOnly);
    }
}

// 0x71B770
void CGameSprite::Equip(SHORT slotNum)
{
    if (slotNum <= 51) {
        if (m_equipment.m_items[slotNum] != NULL) {
            if (slotNum >= 0 && slotNum <= 8) {
                m_equipment.m_items[slotNum]->Equip(this, slotNum, FALSE);
            }
        }
    }
}

// 0x71B7A0
void CGameSprite::Unequip(SHORT slotNum)
{
    if (slotNum <= 51) {
        if (m_equipment.m_items[slotNum] != NULL) {
            switch (slotNum) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 43:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
                if (slotNum == m_equipment.m_selectedWeapon) {
                    m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);

                    m_equipment.m_items[slotNum]->Demand();

                    ITEM_ABILITY* pAbility = m_equipment.m_items[slotNum]->GetAbility(m_equipment.m_selectedWeaponAbility);

                    SHORT lSlot;
                    CItem* pLauncher = GetLauncher(pAbility, lSlot);
                    if (pLauncher != NULL) {
                        pLauncher->Unequip(this, slotNum, TRUE, FALSE);
                    }

                    m_equipment.m_items[slotNum]->Release();

                    SelectWeaponAbility(10, 0, 0, 1);
                } else {
                    m_equipment.m_items[slotNum]->Unequip(this, slotNum, TRUE, FALSE);
                }
                break;
            }
        }
    }
}

// 0x71B8D0
SHORT CGameSprite::GetTurnUndeadLevel()
{
    DWORD nLevel = m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC);

    // FIXME: Calculates paladin class twice.
    if (m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) > 2) {
        nLevel += m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) - 2;
    }

    return static_cast<SHORT>(nLevel);
}

// 0x71B910
SHORT CGameSprite::GetBackstabDamageMultiplier()
{
    if (!m_typeAI.IsClassValid(CAIObjectType::C_ROGUE)) {
        return 0;
    }

    CDerivedStats* DStats = &m_derivedStats;
    if (!field_72A4) {
        DStats = &m_tempStats;
    }

    INT nLevel = DStats->GetBardMonkRogueLevel();
    return atol(g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tBackstabMultiplier.GetAt(CPoint(nLevel, 0)));
}

// 0x71B9A0
SHORT CGameSprite::GetLayOnHandsAmount()
{
    return g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetLayOnHandsAmount(m_typeAI, m_derivedStats);
}

// 0x71C0A0
INT CGameSprite::GetNumQuickWeaponSlots()
{
    return g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetNumQuickWeaponSlots(m_typeAI.m_nClass);
}

// 0x71D480
DWORD CGameSprite::GetCarriedWeight()
{
    DWORD weight = 0;

    for (int index = 0; index < 51; index++) {
        if (m_equipment.m_items[index] != NULL) {
            weight += m_equipment.m_items[index]->GetWeight();
        }
    }

    return weight;
}

// 0x71FBA0
void CGameSprite::GetNumInventoryPersonalSlots(INT& nUsedSlots, INT& nTotalSlots)
{
    nTotalSlots = CScreenInventory::PERSONAL_INVENTORY_SIZE;
    nUsedSlots = 0;

    for (int index = 0; index < nTotalSlots; index++) {
        if (m_equipment.m_items[index + 18] != NULL) {
            nUsedSlots++;
        }
    }
}

// 0x72DE60
void CGameSprite::sub_72DE60()
{
    // TODO: Incomplete.
}

// 0x71F6E0
int CGameSprite::sub_71F6E0()
{
    int v1;

    switch (m_typeAI.m_nClass) {
    case CAIOBJECTTYPE_C_BARBARIAN:
    case CAIOBJECTTYPE_C_CLERIC:
    case CAIOBJECTTYPE_C_DRUID:
    case CAIOBJECTTYPE_C_FIGHTER:
    case CAIOBJECTTYPE_C_PALADIN:
    case CAIOBJECTTYPE_C_RANGER:
        v1 = 10;
        break;
    case CAIOBJECTTYPE_C_BARD:
    case CAIOBJECTTYPE_C_MONK:
    case CAIOBJECTTYPE_C_ROGUE:
        v1 = 15;
        break;
    default:
        v1 = 5;
        break;
    }

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_ELF:
        v1 += 20;
        break;
    case CAIOBJECTTYPE_R_DWARF:
        v1 += 10;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        v1 += 5;
        break;
    }

    if (field_4C53 == 2) {
        v1 = 100;
    }

    return v1;
}

// 0x71F760
const CString& CGameSprite::GetName()
{
    if (m_baseStats.m_name != -1) {
        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(m_baseStats.m_name, strRes);
        m_sName = strRes.szText;
    }

    return m_sName;
}

// 0x71F820
STRREF CGameSprite::GetNameRef()
{
    STRREF strName = m_baseStats.m_name;

    if (strName == -1) {
        SHORT nSlot = g_pBaldurChitin->GetObjectGame()->GetCharacterSlotFromId(m_id);
        if (nSlot < 0) {
            nSlot = 0;
        }

        strName = -2 - nSlot;
    }

    return strName;
}

// 0x728460
BOOL CGameSprite::Orderable(BOOL bIgnoreControl)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x728570
DWORD CGameSprite::GetSpecialization()
{
    return m_baseStats.m_specialization;
}

// 0x72DE60
BOOL CGameSprite::ProcessEffectList()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x74F830
void CGameSprite::SelectWeaponAbility(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4)
{
    // TODO: Incomplete.
}

// 0x762740
BOOL CGameSprite::HasClassMask(DWORD dwMask)
{
    return (dwMask & GetAIType().m_nClassMask) != 0;
}

// 0x762760
INT CGameSprite::GetClassLevel(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28701
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28702
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_baseStats.m_classLevels[iClassType - 1];
}

// 0x7627C0
void CGameSprite::SetClassLevel(INT iClassType, INT nLevel)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28719
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28719
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    m_baseStats.m_characterLevel += static_cast<BYTE>(nLevel) - m_baseStats.m_classLevels[iClassType];
    m_baseStats.m_classLevels[iClassType - 1] = static_cast<BYTE>(nLevel);
}

// 0x762830
BOOL CGameSprite::HasClassLevel(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28739
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28740
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_baseStats.m_classLevels[iClassType - 1] != 0;
}

// 0x762890
void CGameSprite::SetFeatValue(UINT nFeatNumber, INT iFeatValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28756
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if (iFeatValue > 0) {
        m_baseStats.m_feats[nFeatNumber >> 5] |= 1 << (nFeatNumber & 0x1F);
    } else {
        m_baseStats.m_feats[nFeatNumber >> 5] &= ~(1 << (nFeatNumber & 0x1F));
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28774
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE);

        m_baseStats.m_featArmorProficiency = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28781
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE);

        m_baseStats.m_featArmoredArcana = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_CLEAVE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28781
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE);

        m_baseStats.m_featCleave = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28795
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featBastardSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28802
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE);

        m_baseStats.m_featExtraRage = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28809
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE);

        m_baseStats.m_featExtraShapeshifting = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28816
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE);

        m_baseStats.m_featExtraSmiting = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28823
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE);

        m_baseStats.m_featExtraTurning = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28830
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featAxe = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28837
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featBow = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28844
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featFlail = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28851
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featGreatSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28858
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featHammer = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28865
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featLargeSword = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28872
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featPolearm = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28879
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featCrossbow = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28886
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featMace = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28893
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featMissile = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28890
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featQuarterStaff = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28897
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE);

        m_baseStats.m_featSmallBlade = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28914
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE);

        m_baseStats.m_featFocusEnchantment = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28921
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE);

        m_baseStats.m_featFocusEvocation = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28928
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE);

        m_baseStats.m_featFocusNecromancy = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28935
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE);

        m_baseStats.m_featFocusTransmutation = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28942
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE);

        m_baseStats.m_featSpellPenetration = iFeatValue;
        break;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
        // __LINE__: 28949
        UTIL_ASSERT(iFeatValue <= CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL);

        m_baseStats.m_featToughness = iFeatValue;
        break;
    }
}

// 0x762E20
INT CGameSprite::GetFeatValue(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 28968
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) == 0) {
        return 0;
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return m_baseStats.m_featArmorProficiency;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_baseStats.m_featArmoredArcana;
    case CGAMESPRITE_FEAT_CLEAVE:
        return m_baseStats.m_featCleave;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return m_baseStats.m_featBastardSword;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_featExtraRage;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_featExtraShapeshifting;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_featExtraSmiting;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_featExtraTurning;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return m_baseStats.m_featAxe;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return m_baseStats.m_featBow;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return m_baseStats.m_featFlail;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return m_baseStats.m_featGreatSword;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return m_baseStats.m_featHammer;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return m_baseStats.m_featLargeSword;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return m_baseStats.m_featPolearm;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return m_baseStats.m_featCrossbow;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return m_baseStats.m_featMace;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return m_baseStats.m_featMissile;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return m_baseStats.m_featQuarterStaff;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return m_baseStats.m_featSmallBlade;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return m_baseStats.m_featFocusEnchantment;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return m_baseStats.m_featFocusEvocation;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return m_baseStats.m_featFocusNecromancy;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return m_baseStats.m_featFocusTransmutation;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return m_baseStats.m_featSpellPenetration;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return m_baseStats.m_featToughness;
    }
    return 1;
}

// 0x7630A0
INT CGameSprite::GetMaxFeatValue(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29126
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE;
    case CGAMESPRITE_FEAT_CLEAVE:
        return CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE;
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE;
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL;
    }

    return 1;
}

// 0x763150
BOOL CGameSprite::sub_763150(UINT nFeatNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29278
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) == 0) {
        return 0;
    }

    if (nFeatNumber == CGAMESPRITE_FEAT_CLEAVE) {
        if (m_derivedStats.m_nSTR >= 13) {
            if (sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK)) {
                INT nValue = GetFeatValue(CGAMESPRITE_FEAT_CLEAVE);
                if (nValue == 1 || nValue == 2) {
                    if (m_baseStats.m_attackBase >= 4) {
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }

    return sub_763200(nFeatNumber, 0);
}

// 0x763200
BOOL CGameSprite::sub_763200(UINT nFeatNumber, INT a2)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29333
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    SHORT nSTR = m_derivedStats.m_nSTR;
    SHORT nDEX = m_derivedStats.m_nDEX;
    SHORT nINT = m_derivedStats.m_nINT;
    SHORT nWIS = m_derivedStats.m_nWIS;

    if (a2 == 1) {
        nSTR = m_baseStats.m_STRBase;
        nDEX = m_baseStats.m_DEXBase;
        nINT = m_baseStats.m_INTBase;
        nWIS = m_baseStats.m_WISBase;
    }

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_AEGIS_OF_RIME:
    case CGAMESPRITE_FEAT_AQUA_MORTIS:
    case CGAMESPRITE_FEAT_SCION_OF_STORMS:
    case CGAMESPRITE_FEAT_SPIRIT_OF_FLAME:
        return (m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_BARD) >= 11
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_CLERIC) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_DRUID) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_WIZARD) >= 7
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_PALADIN) >= 15
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER) >= 15
                   || m_derivedStats.GetClassLevel(CAIOBJECTTYPE_C_RANGER) >= 8)
            && m_derivedStats.field_144[13] >= 10;
    case CGAMESPRITE_FEAT_AMBIDEXTERITY:
        return nDEX >= 15;
    case CGAMESPRITE_FEAT_ARMOR_PROF:
    case CGAMESPRITE_FEAT_BLIND_FIGHT:
    case CGAMESPRITE_FEAT_COURTEOUS_MAGOCRACY:
    case CGAMESPRITE_FEAT_DASH:
    case CGAMESPRITE_FEAT_DISCIPLINE:
    case CGAMESPRITE_FEAT_FORESTER:
    case CGAMESPRITE_FEAT_GREAT_FORTITUDE:
    case CGAMESPRITE_FEAT_IMPROVED_INITIATIVE:
    case CGAMESPRITE_FEAT_IRON_WILL:
    case CGAMESPRITE_FEAT_LIGHTNING_REFLEXES:
    case CGAMESPRITE_FEAT_PRECISE_SHOT:
    case CGAMESPRITE_FEAT_SHIELD_PROF:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
    case CGAMESPRITE_FEAT_STRONG_BACK:
    case CGAMESPRITE_FEAT_TOUGHNESS:
    case CGAMESPRITE_FEAT_TWO_WEAPON_FIGHTING:
        return TRUE;
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD);
    case CGAMESPRITE_FEAT_ARTERIAL_STRIKE:
        return m_baseStats.m_rogueLevel > 0 && m_baseStats.m_attackBase >= 4;
    case CGAMESPRITE_FEAT_BULLHEADED:
        return m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
            || m_typeAI.m_nRace == CAIOBJECTTYPE_R_DWARF;
    case CGAMESPRITE_FEAT_CLEAVE:
        if (!(nSTR >= 13 && sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK))) {
            return FALSE;
        }

        if (GetFeatValue(CGAMESPRITE_FEAT_CLEAVE) >= 1) {
            return m_baseStats.m_attackBase >= 4;
        }

        return TRUE;
    case CGAMESPRITE_FEAT_COMBAT_CASTING:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD)
            || m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_CRIPPLING_STRIKE:
        return m_baseStats.m_rogueLevel >= 10;
    case CGAMESPRITE_FEAT_DEFLECT_ARROWS:
    case CGAMESPRITE_FEAT_DODGE:
    case CGAMESPRITE_FEAT_RAPID_SHOT:
        return nDEX >= 13;
    case CGAMESPRITE_FEAT_DIRTY_FIGHTING:
        return nDEX >= 13 && m_baseStats.m_attackBase >= 2;
    case CGAMESPRITE_FEAT_ENVENOM_WEAPON:
        return m_baseStats.m_rogueLevel > 0
            && m_baseStats.m_skills[0] >= 8;
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return GetFeatValue(CGAMESPRITE_FEAT_EXOTIC_BASTARD) != 2
            || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_EXPERTISE:
        return nINT >= 13;
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_barbarianLevel > 0;
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_druidLevel >= 3;
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_paladinLevel >= 2;
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_paladinLevel >= 3
            || m_baseStats.m_clericLevel > 0;
    case CGAMESPRITE_FEAT_FIENDSLAYER:
        return (GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_LARGESWORD) >= 2
                   || GetFeatValue(CGAMESPRITE_FEAT_MARTIAL_GREATSWORD) >= 2)
            && m_baseStats.m_paladinLevel >= 3;
    case CGAMESPRITE_FEAT_HAMSTRING:
        return m_baseStats.m_rogueLevel >= 3;
    case CGAMESPRITE_FEAT_HERETICS_BANE:
        return m_baseStats.m_attackBase >= 4
            && m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_HEROIC_INSPIRATION:
        return m_baseStats.m_barbarianLevel > 0
            || m_baseStats.m_barbarianLevel > 0
            || m_baseStats.m_paladinLevel > 0;
    case CGAMESPRITE_FEAT_IMPROVED_CRITICAL:
        return m_baseStats.m_attackBase >= 8;
    case CGAMESPRITE_FEAT_IMPROVED_EVASION:
        return m_baseStats.m_rogueLevel >= 10
            || m_baseStats.m_monkLevel >= 9;
    case CGAMESPRITE_FEAT_IMPROVED_TURNING:
        return m_baseStats.m_clericLevel > 0
            || m_baseStats.m_paladinLevel >= 3;
    case CGAMESPRITE_FEAT_LINGERING_SONG:
        return m_baseStats.m_bardLevel > 0;
    case CGAMESPRITE_FEAT_LUCK_OF_HEROES:
        return m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN;
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return GetFeatValue(nFeatNumber) != 3 || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_MAXIMIZED_ATTACKS:
        if (1) {
            INT nWeaponSpecializations = 0;
            for (INT nFeatNumber = CGAMESPRITE_FEAT_MARTIAL_AXE; nFeatNumber <= CGAMESPRITE_FEAT_MARTIAL_POLEARM; nFeatNumber++) {
                if (GetFeatValue(nFeatNumber) == 3) {
                    nWeaponSpecializations++;
                }
            }

            if (GetFeatValue(CGAMESPRITE_FEAT_EXOTIC_BASTARD) == 3) {
                nWeaponSpecializations++;
            }

            if (nWeaponSpecializations < 2) {
                for (INT nFeatNumber = CGAMESPRITE_FEAT_SIMPLE_CROSSBOW; nFeatNumber <= CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE; nFeatNumber++) {
                    if (GetFeatValue(nFeatNumber) == 3) {
                        nWeaponSpecializations++;
                    }
                }
            }

            return nWeaponSpecializations >= 2 && m_baseStats.m_skills[3] >= 4;
        }
    case CGAMESPRITE_FEAT_MERCANTILE_BACKGROUND:
        // TODO: Incomplete.
        return FALSE;
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return GetFeatValue(nFeatNumber) != 3 || m_baseStats.m_fighterLevel >= 4;
    case CGAMESPRITE_FEAT_SNAKE_BLOOD:
        // TODO: Incomplete.
        return FALSE;
    case CGAMESPRITE_FEAT_STUNNING_FIST:
        return (nDEX >= 13 && nWIS >= 13 && m_baseStats.m_attackBase >= 8)
            || m_baseStats.m_monkLevel > 0;
    case CGAMESPRITE_FEAT_SUBVOCAL_CASTING:
        return m_derivedStats.HasClassMask(CLASSMASK_WIZARD | CLASSMASK_SORCERER | CLASSMASK_BARD)
            || m_derivedStats.HasClassMask(CLASSMASK_RANGER | CLASSMASK_PALADIN | CLASSMASK_DRUID | CLASSMASK_CLERIC);
    case CGAMESPRITE_FEAT_WEAPON_FINESSE:
        return GetFeatValue(CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE)
            && m_baseStats.m_attackBase >= 1;
    case CGAMESPRITE_FEAT_WILDSHAPE_BOAR:
    case CGAMESPRITE_FEAT_WILDSHAPE_PANTHER:
        return m_baseStats.m_druidLevel >= 5;
    case CGAMESPRITE_FEAT_WILDSHAPE_SHAMBLER:
        return m_baseStats.m_druidLevel >= 8;
    }

    return FALSE;
}

// 0x763A40
BOOL CGameSprite::sub_763A40(UINT nFeatNumber, INT a2)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 29873
    UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

    switch (nFeatNumber) {
    case CGAMESPRITE_FEAT_ARMOR_PROF:
        return m_baseStats.m_featArmorProficiency < CGAMESPRITE_FEAT_MAX_ARMOR_PROFICIENCY_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_ARMORED_ARCANA:
        return m_baseStats.m_featArmoredArcana < CGAMESPRITE_FEAT_MAX_ARMORED_ARCANA_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_CLEAVE:
        return m_baseStats.m_featCleave < CGAMESPRITE_FEAT_MAX_CLEAVE_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
        return m_baseStats.m_featBastardSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_RAGE:
        return m_baseStats.m_featExtraRage < CGAMESPRITE_FEAT_MAX_EXTRA_RAGE_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
        return m_baseStats.m_featExtraShapeshifting < CGAMESPRITE_FEAT_MAX_EXTRA_SHAPESHIFTING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_SMITING:
        return m_baseStats.m_featExtraSmiting < CGAMESPRITE_FEAT_MAX_EXTRA_SMITING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_EXTRA_TURNING:
        return m_baseStats.m_featExtraTurning < CGAMESPRITE_FEAT_MAX_EXTRA_TURNING_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_AXE:
        return (m_baseStats.m_featAxe != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featAxe < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_BOW:
        return (m_baseStats.m_featBow != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featBow < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
        return (m_baseStats.m_featFlail != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featFlail < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
        return (m_baseStats.m_featGreatSword != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featGreatSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
        return (m_baseStats.m_featHammer != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featHammer < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
        return (m_baseStats.m_featLargeSword != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featLargeSword < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
        return (m_baseStats.m_featPolearm != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featPolearm < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
        return (m_baseStats.m_featCrossbow != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featCrossbow < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_MACE:
        return (m_baseStats.m_featMace != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featMace < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
        return (m_baseStats.m_featMissile != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featMissile < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
        return (m_baseStats.m_featQuarterStaff != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featQuarterStaff < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
        return (m_baseStats.m_featSmallBlade != CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE - 1
                   || m_baseStats.m_attackBase >= 4)
            && m_baseStats.m_featSmallBlade < CGAMESPRITE_FEAT_MAX_WEAPON_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
        return m_baseStats.m_featFocusEnchantment < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_ENCHANTMENT_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
        return m_baseStats.m_featFocusEvocation < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_EVOCATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
        return m_baseStats.m_featFocusNecromancy < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_NECROMANCY_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
        return m_baseStats.m_featFocusTransmutation < CGAMESPRITE_FEAT_MAX_SPELL_FOCUS_TRANSMUTATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_SPELL_PENETRATION:
        return m_baseStats.m_featSpellPenetration < CGAMESPRITE_FEAT_MAX_SPELL_PENETRATION_UPGRADE
            && sub_763200(nFeatNumber, 1);
    case CGAMESPRITE_FEAT_TOUGHNESS:
        return m_baseStats.m_featToughness < CGAMESPRITE_FEAT_TOUGHNESS_MAX_LEVEL
            && sub_763200(nFeatNumber, 1);
    }

    if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) != 0) {
        return FALSE;
    }

    if (a2) {
        return sub_763200(nFeatNumber, 1);
    }

    return TRUE;
}

// 0x763CB0
int CGameSprite::GetExtraFeats(BYTE nClass)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int classLevel = m_derivedStats.GetClassLevel(nClass);

    int feats = atol(ruleTables.m_tFeatLevel.GetAt(CPoint(0, m_derivedStats.m_nLevel - 1)));
    feats += atol(ruleTables.m_tFeatClass.GetAt(CPoint(nClass - 1, classLevel - 1)));

    if (m_derivedStats.m_nLevel == 1) {
        if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
            && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE) {
            feats++;
        } else if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HALFLING
            && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART) {
            feats++;
        }
    }

    return feats;
}

// 0x763DA0
int CGameSprite::GetExtraSkillPoints(BYTE nClass)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int sp = atol(ruleTables.m_tSkillPoints.GetAt(CPoint(nClass - 1, 0)));

    sp += ruleTables.GetAbilityScoreModifier(m_baseStats.m_INTBase);

    if (sp < 1) {
        sp = 1;
    }

    if (m_derivedStats.m_nLevel == 1) {
        sp *= 4;
    }

    if (m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN
        && m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_PURERACE) {
        if (m_derivedStats.m_nLevel == 1) {
            sp++;
        }
        sp++;
    }

    return sp;
}

// 0x764270
void CGameSprite::SetSkillValue(UINT iSkillNumber, INT iSkillValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30424
    UTIL_ASSERT(iSkillValue >= 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30425
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    m_baseStats.m_skills[iSkillNumber] = static_cast<BYTE>(iSkillValue);
}

// 0x7642D0
INT CGameSprite::GetSkillValue(UINT iSkillNumber)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30444
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    return m_baseStats.m_skills[iSkillNumber];
}

// 0x764310
INT CGameSprite::GetSkillCost(UINT iSkillNumber, BYTE nClass)
{
    INT iClassType;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30463
    UTIL_ASSERT(iSkillNumber < CGAMESPRITE_SKILL_NUMSKILLS);

    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    int v1 = 0;
    int v2 = 0;
    int v3 = 0;

    // A way to bypass condition below without `goto`. Need a better
    // understanding of the calculations to get rid of it.
    // TODO: Review calculations.
    bool check = true;

    for (iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        if (m_derivedStats.HasClass(iClassType)) {
            INT nCost = atol(ruleTables.m_tSkillCosts.GetAt(CPoint(iClassType - 1, iSkillNumber)));
            if (nCost == 1) {
                v3 = 1;
                if (iClassType == nClass) {
                    v2 = 1;
                    check = false;
                    break;
                }

                if (v1 > 0) {
                    check = false;
                    break;
                }
            } else if (nCost == 2) {
                if (v3 == 0) {
                    v3 = 2;
                }

                if (iClassType == nClass) {
                    v2 = 2;
                    v1 = 2;
                }
            } else if (nCost > 2) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
                // __LINE__: 30508
                UTIL_ASSERT_MSG(FALSE, "Invalid Skill Cost (not 0, 1 or 2) in SKILCOST.2DA");
            }
        }
    }

    if (check) {
        if (v1 <= 0) {
            return v1;
        }
    }

    INT nLevels = 0;
    for (iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        INT nLevel = m_derivedStats.GetClassLevel(iClassType);
        if (nLevel > 0) {
            INT nCost = atol(ruleTables.m_tSkillCosts.GetAt(CPoint(iClassType - 1, iSkillNumber)));
            if (nCost > 0) {
                nLevels += nLevel;
            }
        }
    }

    if (m_baseStats.m_skills[iSkillNumber] < (nLevels + 3) / v3) {
        return v2;
    }

    return 0;
}

// 0x764520
INT CGameSprite::GetEffectiveCharacterLevel()
{
    INT nLevel = m_derivedStats.m_nLevel;

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            nLevel += 1;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            nLevel += 2;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_DWARF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_DWARF_GRAY:
            nLevel += 2;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_GNOME_DEEP:
            nLevel += 3;
            break;
        }
        break;
    }

    return nLevel;
}

// 0x764590
INT CGameSprite::GetRacialFavoredClass(DWORD& nSpecialization)
{
    INT iClass;

    nSpecialization = 0;

    switch (m_typeAI.m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            iClass = m_derivedStats.GetBestClass();
            if (m_derivedStats.m_nLevel == 0) {
                iClass = CAIOBJECTTYPE_C_FIGHTER;
            }
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR:
            iClass = CAIOBJECTTYPE_C_PALADIN;
            break;
        case CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING:
            iClass = CAIOBJECTTYPE_C_ROGUE;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_ELF:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
            iClass = CAIOBJECTTYPE_C_WIZARD;
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_DROW:
            switch (m_typeAI.m_nGender) {
            case CAIOBJECTTYPE_SEX_MALE:
                iClass = CAIOBJECTTYPE_C_WIZARD;
                break;
            case CAIOBJECTTYPE_SEX_FEMALE:
                iClass = CAIOBJECTTYPE_C_CLERIC;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
                // __LINE__: 30684
                UTIL_ASSERT_MSG(FALSE, "Character has no gender");
            }
            break;
        case CAIOBJECTTYPE_SUBRACE_ELF_WILD:
            iClass = CAIOBJECTTYPE_C_SORCERER;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_HALF_ELF:
        iClass = m_derivedStats.GetBestClass();
        if (m_derivedStats.m_nLevel == 0) {
            iClass = CAIOBJECTTYPE_C_FIGHTER;
        }
        break;
    case CAIOBJECTTYPE_R_DWARF:
        iClass = CAIOBJECTTYPE_C_FIGHTER;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        switch (m_typeAI.m_nSubRace) {
        case CAIOBJECTTYPE_SUBRACE_PURERACE:
        case CAIOBJECTTYPE_SUBRACE_HALFLING_STRONGHEART:
            iClass = CAIOBJECTTYPE_C_ROGUE;
            break;
        case CAIOBJECTTYPE_SUBRACE_HALFLING_GHOSTWISE:
            // TODO: This does not look right.
            iClass = CAIOBJECTTYPE_C_BARBARIAN;
            break;
        }
        break;
    case CAIOBJECTTYPE_R_GNOME:
        iClass = CAIOBJECTTYPE_C_WIZARD;
        nSpecialization = 0x400; // WIZARD_ILLUSIONIST
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        iClass = CAIOBJECTTYPE_C_BARBARIAN;
        break;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 30733
    UTIL_ASSERT_MSG(iClass != 0, "GetRacialFavoredClass() returned 0!");

    return iClass;
}

// 0x7646E0
INT CGameSprite::GetMulticlassingPenalty()
{
    if (m_derivedStats.m_nLevel == 0) {
        return 0;
    }

    DWORD nSpecialization = 0;
    INT iExcludedRacialClass = 0;
    INT iRacialFavoredClass = GetRacialFavoredClass(nSpecialization);
    INT iBestClass = m_derivedStats.GetBestClass();

    if (iRacialFavoredClass == iBestClass
        && (nSpecialization == 0
            || (m_baseStats.m_specialization & nSpecialization) != 0)) {
        if (m_derivedStats.GetClassLevel(iBestClass) == m_derivedStats.m_nLevel) {
            // Means there is no multiclassing.
            return 0;
        }

        iExcludedRacialClass = iRacialFavoredClass;
        iBestClass = 0;
        for (INT iClass = 1; iClass <= CAIOBJECT_CLASS_MAX; iClass++) {
            if (iClass != iRacialFavoredClass) {
                if (m_derivedStats.GetClassLevel(iClass) != 0) {
                    if (iBestClass == 0
                        || m_derivedStats.GetClassLevel(iClass) > m_derivedStats.GetClassLevel(iBestClass)) {
                        iBestClass = iClass;
                    }
                }
            }
        }
    }

    INT nBestClassLevel = m_derivedStats.GetClassLevel(iBestClass);
    if (nBestClassLevel <= 2) {
        return 0;
    }

    INT nPenalty = 0;
    for (INT iClass = 1; iClass <= CAIOBJECT_CLASS_MAX; iClass++) {
        if (iClass != iExcludedRacialClass && iClass != iBestClass) {
            INT nClassLevel = m_derivedStats.GetClassLevel(iClass);
            if (nClassLevel != 0) {
                if (nBestClassLevel - nClassLevel > 1
                    && iClass != iRacialFavoredClass) {
                    nPenalty += 20;
                }
            }
        }
    }

    // 100% penalty, really?
    if (nPenalty > 100) {
        nPenalty = 100;
    }

    return nPenalty;
}

// 0x765C50
void CGameSprite::DisplayFeats(CUIControlTextDisplay* pText)
{
    CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31489
    UTIL_ASSERT(pText != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31490
    UTIL_ASSERT(pEngine != NULL);

    for (int index = 0; index < CGAMESPRITE_FEAT_NUMFEATS; index++) {
        UINT nFeatNumber = ruleTables.GetFeatId(index);
        INT nFeatRank = GetFeatValue(nFeatNumber);
        if (nFeatRank > 0) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
            // __LINE__: 29233
            UTIL_ASSERT(nFeatNumber < CGAMESPRITE_FEAT_NUMFEATS);

            if ((m_baseStats.m_feats[nFeatNumber >> 5] & (1 << (nFeatNumber & 0x1F))) != 0) {
                switch (nFeatNumber) {
                case CGAMESPRITE_FEAT_ARMOR_PROF:
                case CGAMESPRITE_FEAT_ARMORED_ARCANA:
                case CGAMESPRITE_FEAT_CLEAVE:
                case CGAMESPRITE_FEAT_EXOTIC_BASTARD:
                case CGAMESPRITE_FEAT_EXTRA_RAGE:
                case CGAMESPRITE_FEAT_EXTRA_SHAPESHIFTING:
                case CGAMESPRITE_FEAT_EXTRA_SMITING:
                case CGAMESPRITE_FEAT_EXTRA_TURNING:
                case CGAMESPRITE_FEAT_MARTIAL_AXE:
                case CGAMESPRITE_FEAT_MARTIAL_BOW:
                case CGAMESPRITE_FEAT_MARTIAL_FLAIL:
                case CGAMESPRITE_FEAT_MARTIAL_GREATSWORD:
                case CGAMESPRITE_FEAT_MARTIAL_HAMMER:
                case CGAMESPRITE_FEAT_MARTIAL_LARGESWORD:
                case CGAMESPRITE_FEAT_MARTIAL_POLEARM:
                case CGAMESPRITE_FEAT_SIMPLE_CROSSBOW:
                case CGAMESPRITE_FEAT_SIMPLE_MACE:
                case CGAMESPRITE_FEAT_SIMPLE_MISSILE:
                case CGAMESPRITE_FEAT_SIMPLE_QUARTERSTAFF:
                case CGAMESPRITE_FEAT_SIMPLE_SMALLBLADE:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_ENCHANTMENT:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_EVOCATION:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_NECROMANCY:
                case CGAMESPRITE_FEAT_SPELL_FOCUS_TRANSMUTE:
                case CGAMESPRITE_FEAT_SPELL_PENETRATION:
                case CGAMESPRITE_FEAT_TOUGHNESS:
                    CBaldurEngine::UpdateText(pText,
                        "%s: %d",
                        (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)),
                        nFeatRank);
                    break;
                default:
                    CBaldurEngine::UpdateText(pText,
                        "%s",
                        (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)));
                    break;
                }
            } else {
                CBaldurEngine::UpdateText(pText,
                    "%s",
                    (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetFeatName(nFeatNumber)));
            }
        }
    }
}

// 0x765E40
void CGameSprite::DisplaySkills(CUIControlTextDisplay* pText)
{
    CBaldurEngine* pEngine = g_pBaldurChitin->GetActiveEngine();
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31521
    UTIL_ASSERT(pText != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreatureAI.cpp
    // __LINE__: 31522
    UTIL_ASSERT(pEngine != NULL);

    for (int index = 0; index < CGAMESPRITE_SKILL_NUMSKILLS; index++) {
        INT nSkillId = ruleTables.GetSkillId(index);
        if (m_baseStats.m_skills[nSkillId] == m_derivedStats.field_144[nSkillId]) {
            if (m_derivedStats.field_144[nSkillId] != 0) {
                CBaldurEngine::UpdateText(pText,
                    "%s: %d",
                    (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetSkillName(nSkillId)),
                    m_derivedStats.field_144[nSkillId]);
            }
        } else {
            CBaldurEngine::UpdateText(pText,
                "%s: %d (%d)",
                (LPCSTR)CBaldurEngine::FetchString(ruleTables.GetSkillName(nSkillId)),
                m_derivedStats.field_144[nSkillId],
                m_baseStats.m_skills[nSkillId]);
        }
    }
}

// 0x42FDC0
void CGameSprite::SetResRef(const CResRef& resRef)
{
    m_resRef = resRef;
}

// 0x453190
CCreatureFileHeader* CGameSprite::GetBaseStats()
{
    return &m_baseStats;
}

// 0x4531A0
CDerivedStats* CGameSprite::GetDerivedStats()
{
    return &m_derivedStats;
}

// NOTE: Inlined.
CGameAnimation* CGameSprite::GetAnimation()
{
    return &m_animation;
}

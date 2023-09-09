#include "CStore.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CUtil.h"

// 0x54B0E0
CStore::CStore()
{
    m_nBuyTypes = 0;
    m_nDrinks = 0;
    m_nSpells = 0;
    m_pBuyTypes = NULL;
    m_pDrinks = NULL;
    m_pSpells = NULL;
    memset(m_pVersion, 0, sizeof(m_pVersion));
    m_bLocalCopy = FALSE;
}

// 0x54B150
CStore::CStore(const CResRef& resRef)
{
    m_pBuyTypes = NULL;
    m_pDrinks = NULL;
    m_pSpells = NULL;
    memset(m_pVersion, 0, sizeof(m_pVersion));
    m_bLocalCopy = FALSE;
    SetResRef(resRef);
}

// 0x54B1E0
CStore::~CStore()
{
    while (!m_lInventory.IsEmpty()) {
        CStoreFileItem* pStoreItem = m_lInventory.RemoveHead();
        delete pStoreItem;
    }
    m_lInventory.RemoveAll();

    if (m_pBuyTypes != NULL) {
        delete m_pBuyTypes;
    }

    if (m_pDrinks != NULL) {
        delete m_pDrinks;
    }

    if (m_pSpells != NULL) {
        delete m_pSpells;
    }
}

// 0x54B2A0
void CStore::SetResRef(const CResRef& resRef)
{
    CStoreFile storeData;

    while (!m_lInventory.IsEmpty()) {
        CStoreFileItem* pStoreItem = m_lInventory.RemoveHead();
        delete pStoreItem;
    }
    m_lInventory.RemoveAll();

    if (m_pBuyTypes != NULL) {
        delete m_pBuyTypes;
    }

    if (m_pDrinks != NULL) {
        delete m_pDrinks;
    }

    if (m_pSpells != NULL) {
        delete m_pSpells;
    }

    storeData.SetResRef(resRef, TRUE, TRUE);

    BYTE* pData = reinterpret_cast<BYTE*>(storeData.GetData());

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
    // __LINE__: 200
    UTIL_ASSERT(pData != NULL);

    DWORD nData = storeData.GetDataSize();
    DWORD cnt = 0;

    memcpy(m_pVersion, pData, 8);
    cnt += 8;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
    // __LINE__: 224
    UTIL_ASSERT(cnt <= nData);

    if (memcmp(m_pVersion, "STORV9.0", 8) == 0) {
        if ((storeData.pRes->GetID() & 0xFFF00000) < 0xFC000000) {
            m_bLocalCopy = FALSE;
        } else {
            CString sStoreDir;
            CString sTempDir;

            g_pChitin->cDimm.GetElementInDirectoryList(~storeData.pRes->GetID() >> 20, sStoreDir);
            g_pChitin->lAliases.ResolveFileName(g_pBaldurChitin->GetObjectGame()->m_sTempDir, sTempDir);
            m_bLocalCopy = sStoreDir == sTempDir;
        }

        memcpy(&m_header, pData + 8, sizeof(m_header));
        cnt += sizeof(m_header);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
        // __LINE__: 247
        UTIL_ASSERT(cnt <= nData);

        // NOTE: Original code is slightly different.
        for (DWORD nIndex = 0; nIndex < m_header.m_nInventoryCount; nIndex++) {
            CStoreFileItem* pItem = new CStoreFileItem;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 256
            UTIL_ASSERT(pItem);

            memcpy(pItem, pData + m_header.m_nInventoryOffset + sizeof(CStoreFileItem) * nIndex, sizeof(CStoreFileItem));
            m_lInventory.AddTail(pItem);

            cnt += sizeof(CStoreFileItem);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 260
            UTIL_ASSERT(cnt <= nData);
        }
        m_header.m_nInventoryCount = 0;

        m_nBuyTypes = m_header.m_nBuyTypesCount;
        if (m_nBuyTypes != 0) {
            m_pBuyTypes = new DWORD[m_nBuyTypes];

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 268
            UTIL_ASSERT(m_pBuyTypes != NULL);

            memcpy(m_pBuyTypes, pData + m_header.m_nbuyTypesOffset, sizeof(DWORD) * m_nBuyTypes);

            cnt += sizeof(DWORD) * m_nBuyTypes;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 271
            UTIL_ASSERT(cnt <= nData);
        }

        m_nDrinks = m_header.m_drinkCount;
        if (m_nDrinks != 0) {
            m_pDrinks = new CStoreFileDrinks();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 278
            UTIL_ASSERT(m_pDrinks != NULL);

            memcpy(m_pDrinks, pData + m_header.m_drinkOffset, sizeof(CStoreFileDrinks) * m_nDrinks);

            cnt += sizeof(CStoreFileDrinks) * m_nDrinks;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 281
            UTIL_ASSERT(cnt <= nData);
        }

        m_nSpells = m_header.m_spellCount;
        if (m_nSpells != 0) {
            m_pSpells = new CStoreFileSpell;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 288
            UTIL_ASSERT(m_pSpells != NULL);

            memcpy(m_pSpells, pData + m_header.m_spellOffset, sizeof(CStoreFileSpell) * m_nSpells);

            cnt += sizeof(CStoreFileSpell) * m_nSpells;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
            // __LINE__: 291
            UTIL_ASSERT(cnt <= nData);
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CStore.cpp
        // __LINE__: 294
        UTIL_ASSERT(cnt == nData);

        storeData.Release();
    }
}

// 0x54B9A0
void CStore::Marshal(const CString& sDirName)
{
    // TODO: Incomplete.
}

// 0x54BDC0
DWORD CStore::GetItemSellValue(CItem& cItem, unsigned char a2)
{
    DWORD dwBaseValue = cItem.GetBaseValue();

    if ((cItem.m_flags & 0x1) == 0) {
        return 1;
    }

    if (dwBaseValue <= 0) {
        return 0;
    }

    DWORD dwMarkDown;

    DWORD dwItemType = cItem.GetItemType();
    if (dwItemType == 34 || dwItemType == 10 || dwItemType == 1 || dwItemType == 70) {
        dwMarkDown = m_header.m_nSellMarkDown;
    } else {
        DWORD v1 = 0;
        BOOL v2 = FALSE;
        POSITION pos = m_lInventory.GetHeadPosition();
        while (pos != NULL) {
            CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
            if (cItem.GetResRef() == CResRef(pStoreItem->m_itemId)) {
                if ((pStoreItem->m_nStoreFlags & 0x1) != 0) {
                    dwMarkDown = 20;
                    v2 = TRUE;
                    break;
                }

                if (cItem.GetMaxStackable() > 1) {
                    v1 += pStoreItem->m_nInStock * pStoreItem->m_usageCount[0];
                } else {
                    v1 += pStoreItem->m_nInStock;
                }
            }

            m_lInventory.GetNext(pos);
        }

        if (!v2) {
            dwMarkDown = m_header.m_nSellMarkDown - v1 * m_header.m_nAdditionalMarkDown;
            if (dwMarkDown < 20) {
                dwMarkDown = 20;
            }
        }
    }

    if (cItem.GetMaxStackable() > 1) {
        dwBaseValue *= cItem.GetUsageCount(0);
    } else {
        INT nTotalCharges = 0;
        INT nChargesLeft = 0;
        for (INT nAbility = 0; nAbility < 3; nAbility++) {
            INT nMaxUsageCount = cItem.GetMaxUsageCount(nAbility);
            if (nMaxUsageCount > 0) {
                nTotalCharges += nMaxUsageCount;
                nChargesLeft += cItem.GetUsageCount(nAbility);
            }
        }

        if (nTotalCharges > 0) {
            dwBaseValue *= nChargesLeft;
            dwBaseValue /= nTotalCharges;
        }
    }

    DWORD dwValue = dwBaseValue * (a2 + dwMarkDown) / 100;
    if (dwValue <= 0) {
        dwValue = 1;
    }

    return dwValue;
}

// 0x54BF40
DWORD CStore::GetItemBuyValue(CItem& cItem, BYTE nCHR, SHORT nReputation, unsigned char a4)
{
    DWORD dwMarkUp = m_header.m_nBuyMarkUp;

    // NOTE: Unused.
    cItem.GetItemType();

    DWORD dwBaseValue = cItem.GetBaseValue();

    if (cItem.GetMaxStackable() > 1) {
        dwBaseValue *= cItem.GetUsageCount(0);
    } else {
        INT nTotalCharges = 0;
        INT nChargesLeft = 0;
        for (INT nAbility = 0; nAbility < 3; nAbility++) {
            INT nMaxUsageCount = cItem.GetMaxUsageCount(nAbility);
            if (nMaxUsageCount > 0) {
                nTotalCharges += nMaxUsageCount;
                nChargesLeft += cItem.GetUsageCount(nAbility);
            }
        }

        if (nTotalCharges > 0) {
            dwBaseValue *= nChargesLeft;
            dwBaseValue /= nTotalCharges;
        }
    }

    g_pBaldurChitin->GetObjectGame()->GetRuleTables().AdjustStoreMarkup(nCHR, nReputation, dwMarkUp);

    if (dwMarkUp > a4) {
        dwMarkUp -= a4;
    } else {
        dwMarkUp = 0;
    }

    DWORD dwValue = dwMarkUp * dwBaseValue / 100;
    if (dwValue <= 0) {
        dwValue = 1;
    }

    return dwValue;
}

// 0x54C020
INT CStore::GetNumItems()
{
    INT nItems = 0;

    POSITION pos = m_lInventory.GetHeadPosition();
    while (pos != NULL) {
        CStoreFileItem* pStoreItem = m_lInventory.GetNext(pos);
        if ((pStoreItem->m_nStoreFlags & 0x1) != 0) {
            return INT_MAX;
        }

        nItems += pStoreItem->m_nInStock;
    }

    return nItems;
}

// 0x54C050
DWORD CStore::GetItemNumInStock(INT nIndex)
{
    POSITION pos = m_lInventory.FindIndex(nIndex);
    if (pos == NULL) {
        return 0;
    }

    CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
    if ((pStoreItem->m_nStoreFlags & 0x1) != 0) {
        // FIXME: Why?
        return 65535;
    }

    return pStoreItem->m_nInStock;
}

// 0x54C080
BOOL CStore::GetItem(INT nIndex, CItem& cItem)
{
    POSITION pos = m_lInventory.FindIndex(nIndex);
    if (pos == NULL) {
        return FALSE;
    }

    CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
    cItem.SetResRef(CResRef(pStoreItem->m_itemId), TRUE);
    cItem.m_wear = pStoreItem->m_wear;
    cItem.m_flags = pStoreItem->m_dynamicFlags;

    if (cItem.GetLoreValue() == 0 || (pStoreItem->m_nStoreFlags & 0x1) != 0) {
        cItem.m_flags |= 0x1;
    }

    // NOTE: Similar condition?
    if ((pStoreItem->m_nStoreFlags & 0x1) != 0 || cItem.GetLoreValue() > 0) {
        cItem.m_flags |= 0x8;
    }

    for (INT nAbility = 0; nAbility < 3; nAbility++) {
        cItem.SetUsageCount(nAbility, pStoreItem->m_usageCount[nAbility]);
    }

    return TRUE;
}

// 0x54C130
CResRef CStore::GetItemId(INT nIndex)
{
    POSITION pos = m_lInventory.FindIndex(nIndex);
    if (pos == NULL) {
        return CResRef("");
    }

    CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
    return CResRef(pStoreItem->m_itemId);
}

// 0x54C170
INT CStore::GetItemIndex(const CResRef& itemId)
{
    INT nIndex = 0;
    POSITION pos = m_lInventory.GetHeadPosition();
    while (pos != NULL) {
        CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
        if (itemId == CResRef(pStoreItem->m_itemId)) {
            return nIndex;
        }

        m_lInventory.GetNext(pos);
        nIndex++;
    }

    return INT_MAX;
}

// 0x54C1D0
void sub_54C1D0()
{
    // TODO: Incomplete.
}

// 0x54C230
void sub_54C230()
{
    // TODO: Incomplete.
}

// 0x54C460
void sub_54C460()
{
    // TODO: Incomplete.
}

// 0x54C5B0
void sub_54C5B0()
{
    // TODO: Incomplete.
}

// 0x54C5F0
void sub_54C5F0()
{
    // TODO: Incomplete.
}

// 0x54C770
void sub_54C770()
{
    // TODO: Incomplete.
}

// 0x54CA80
void sub_54CA80()
{
    // TODO: Incomplete.
}

// 0x54CAF0
void sub_54CAF0()
{
    // TODO: Incomplete.
}

// 0x54C5B0
INT CStore::AddItemExt(CItem& cItem, DWORD storeFlags)
{
    // TODO: Incomplete.

    return -1;
}

// 0x54CB60
void CStore::CompressItems()
{
    POSITION pos = m_lInventory.GetHeadPosition();
    while (pos != NULL) {
        CStoreFileItem* pStoreItem = m_lInventory.GetAt(pos);
        if (pStoreItem->m_nInStock == 0 && (pStoreItem->m_nStoreFlags & 0x1) == 0) {
            POSITION posToRemove = pos;
            m_lInventory.GetNext(pos);
            m_lInventory.RemoveAt(posToRemove);
            delete pStoreItem;
        } else {
            m_lInventory.GetNext(pos);
        }
    }
}

// 0x54CBB0
BOOL CStore::GetSpell(INT nIndex, CResRef& spellResRef, DWORD& dwCost)
{
    // NOTE: Signed compare.
    if (nIndex < 0 || nIndex >= static_cast<INT>(m_nSpells)) {
        return FALSE;
    }

    spellResRef = m_pSpells[nIndex].m_spell;
    dwCost = m_pSpells[nIndex].m_cost;
    return TRUE;
}

// 0x54CC10
BOOL CStore::GetDrink(INT nIndex, STRREF& strName, DWORD& dwCost, DWORD& dwRumorChance)
{
    // NOTE: Signed compare.
    if (nIndex < 0 || nIndex >= static_cast<INT>(m_nDrinks)) {
        return FALSE;
    }

    strName = m_pDrinks[nIndex].m_strName;
    dwCost = m_pDrinks[nIndex].m_nCost;
    dwRumorChance = m_pDrinks[nIndex].m_nRumorChance;
    return TRUE;
}

// 0x54CCB0
void sub_54CCB0()
{
    // TODO: Incomplete.
}

// 0x54CF80
void sub_54CF80()
{
    // TODO: Incomplete.
}

// 0x54CFE0
void sub_54CFE0()
{
    // TODO: Incomplete.
}

// 0x54D130
void sub_54D130()
{
    // TODO: Incomplete.
}

// 0x54CCB0
void CStore::InvalidateStore(const CResRef& resRef)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x54CC70
void* CStoreFile::GetData()
{
    if (pRes != NULL) {
        return pRes->Demand();
    } else {
        return NULL;
    }
}

// 0x54CC80
DWORD CStoreFile::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

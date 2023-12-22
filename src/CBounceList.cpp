#include "CBounceList.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CProjectile.h"

// 0x43FE00
void CBounceList::Process(CGameSprite* pSprite)
{
    while (!IsEmpty()) {
        CBounceEntry* node = RemoveHead();

        CGameSprite* pTarget;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(node->m_pProjectile->m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pTarget),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (node->m_levelDecrement > 0) {
                pSprite->GetEquipedEffectList()->ModifyAllOfType(static_cast<WORD>(node->m_effectId),
                    -node->m_levelDecrement,
                    TRUE);
                pSprite->GetTimedEffectList()->ModifyAllOfType(static_cast<WORD>(node->m_effectId),
                    -node->m_levelDecrement,
                    TRUE);
                pSprite->field_562C = 1;
            }

            if (!node->m_decrementOnly) {
                CMessage* message = new CMessageFireProjectile(node->m_pProjectile->m_projectileType,
                    pTarget->GetId(),
                    pSprite->GetPos(),
                    node->m_pProjectile->DetermineHeight(pSprite),
                    pSprite->GetId(),
                    pSprite->GetId(),
                    0);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);

                node->m_pProjectile->Fire(pSprite->GetArea(),
                    pSprite->GetId(),
                    pTarget->GetId(),
                    pTarget->GetPos(),
                    node->m_pProjectile->DetermineHeight(pSprite),
                    0);

                node->m_pProjectile = NULL;
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(node->m_pProjectile->m_targetId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        delete node;
    }
    RemoveAll();
}

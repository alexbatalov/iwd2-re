#include "CProjectile.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"

// 0x6A3130
BOOLEAN CProjectile::IsProjectile()
{
    return TRUE;
}

// 0x5551B0
void CProjectile::RemoveSelf()
{
    RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        delete this;
    }
}

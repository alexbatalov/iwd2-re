#include "CGameSound.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x4C9010
CGameSound::~CGameSound()
{
    if (m_bLoopPlaying) {
        m_looping.Stop();
    }
}

// 0x4C95B0
void CGameSound::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSound.cpp
        // __LINE__: 346
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x4C9610
void CGameSound::SetActive(BOOL bActive)
{
    if (bActive) {
        if ((m_soundObject.m_dwFlags & 0x1) == 0) {
            m_soundObject.m_dwFlags |= 0x1;
        }
    } else {
        if ((m_soundObject.m_dwFlags & 0x1) != 0) {
            if (m_bLoopPlaying) {
                m_looping.Stop();
                m_bLoopPlaying = FALSE;
            }

            m_soundObject.m_dwFlags &= ~0x1;
        }
    }
}

// 0x4C9670
BOOL CGameSound::IsActive()
{
    return (m_soundObject.m_dwFlags & 0x1) != 0;
}

// 0x4C9680
void CGameSound::Marshal(CAreaFileSoundObject** pSoundObject)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSound.cpp
    // __LINE__: 432
    UTIL_ASSERT(pSoundObject != NULL);

    *pSoundObject = new CAreaFileSoundObject;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSound.cpp
    // __LINE__: 435
    UTIL_ASSERT(*pSoundObject != NULL);

    memcpy(*pSoundObject, &m_soundObject, sizeof(CAreaFileSoundObject));
}

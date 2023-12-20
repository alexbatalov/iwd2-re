#include "Icewind586B70.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "IcewindMisc.h"

// 0x8E6400
Icewind586B70* Icewind586B70::mInstance;

// 0x586B70
Icewind586B70::Icewind586B70()
    : mEntries(6)
{
}

// 0x586BD0
Icewind586B70* Icewind586B70::Instance()
{
    if (mInstance == NULL) {
        mInstance = new Icewind586B70();
    }
    return mInstance;
}

// 0x586C80
void Icewind586B70::Destroy()
{
    if (mInstance != NULL) {
        delete mInstance;
    }
}

// 0x586CA0
bool Icewind586B70::sub_586CA0(CGameSprite* sprite)
{
    if (!IcewindMisc::IsPC(sprite)) {
        return true;
    }

    // NOTE: Uninline.
    return GetCount() + 1 <= 6;
}

// 0x586CF0
bool Icewind586B70::sub_586CF0(CGameSprite* sprite1, CGameSprite* sprite2)
{
    if (!IcewindMisc::IsPC(sprite1)) {
        return true;
    }

    // NOTE: Uninline.
    if (GetCount() + 1 > 6) {
        return false;
    }

    for (int index = 0; index < 6; index++) {
        if (mEntries[index].field_0 != 0
            && mEntries[index].field_4 != 0
            && sprite2->GetId() == mEntries[index].field_0) {
            return false;
        }
    }

    return true;
}

// 0x586D60
void Icewind586B70::sub_586D60(CGameSprite* sprite1, CGameSprite* sprite2)
{
    if (!IcewindMisc::IsPC(sprite1)) {
        return;
    }

    for (int index = 0; index < 6; index++) {
        if (mEntries[index].field_0 == 0 || mEntries[index].field_4 == 0) {
            // NOTE: Odd check, looks like inlining.
            if (index != -1) {
                mEntries[index].field_0 = sprite2->GetId();
                mEntries[index].field_4 = sprite1->GetId();
                mEntries[index].field_8 = false;
            }
        }
    }
}

// 0x586F20
void Icewind586B70::sub_586F20(CGameSprite* sprite1, CGameSprite* sprite2)
{
    if (!IcewindMisc::IsPC(sprite1)) {
        return;
    }

    for (int index = 0; index < 6; index++) {
        if (mEntries[index].field_0 == 0 || mEntries[index].field_4 == 0) {
            // NOTE: Odd check, looks like inlining.
            if (index != -1) {
                mEntries[index].field_0 = sprite2->GetId();
                mEntries[index].field_4 = sprite1->GetId();
                mEntries[index].field_8 = true;
            }
        }
    }
}

// 0x586F80
void Icewind586B70::Remove(CGameSprite* sprite)
{
    for (std::vector<Entry>::iterator it = mEntries.begin(); it < mEntries.end(); it++) {
        if (sprite->GetId() == it->field_0) {
            it->field_0 = 0;
            it->field_4 = 0;
            it->field_8 = false;
        }
    }
}

// 0x586FC0
void Icewind586B70::sub_586FC0(CGameSprite* sprite)
{
    if (sprite->GetBaseStats()->field_2E9) {
        mEntries[sprite->GetBaseStats()->field_2E9].field_0 = sprite->GetId();
        mEntries[sprite->GetBaseStats()->field_2E9].field_8 = sprite->GetBaseStats()->field_2F7 != 0;
        sprite->GetBaseStats()->field_2E9 = 0;
        sprite->GetBaseStats()->field_2F7 = 0;

        CAIObjectType typeAI(sprite->GetAIType());
        CAIObjectType liveTypeAI(sprite->GetLiveAIType());
        CAIObjectType startTypeAI(sprite->GetLiveAIType());

        g_pBaldurChitin->GetObjectGame()->AddCharacterToAllies(sprite->GetId());

        if (!mEntries[sprite->GetBaseStats()->field_2E9].field_8) {
            startTypeAI.SetEnemyAlly(CAIObjectType::EA_ALL);
            sprite->m_startTypeAI.Set(startTypeAI);
        }

        typeAI.SetEnemyAlly(CAIObjectType::EA_ALLY);
        sprite->SetAIType(typeAI, FALSE, FALSE);

        liveTypeAI.SetEnemyAlly(CAIObjectType::EA_ALLY);
        sprite->m_liveTypeAI.Set(liveTypeAI);
    }

    for (int index = 0; index < 6; index++) {
        if (sprite->GetBaseStats()->field_2EA[index]) {
            mEntries[index].field_4 = sprite->GetId();
            sprite->GetBaseStats()->field_2EA[index] = FALSE;
        }
    }
}

// 0x587190
void Icewind586B70::sub_587190()
{
    CGameSprite* sprite;
    BYTE rc;

    for (int index = 0; index < 6; index++) {
        if (mEntries[index].field_0 != 0) {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(mEntries[index].field_0,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&sprite),
                INFINITE);
            if (rc != CGameObjectArray::SUCCESS) {
                return;
            }

            sprite->GetBaseStats()->field_2E9 = index + 1;
            sprite->GetBaseStats()->field_2F7 = mEntries[index].field_8;

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(mEntries[index].field_0,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        if (mEntries[index].field_4 != 0) {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(mEntries[index].field_4,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&sprite),
                INFINITE);
            if (rc != CGameObjectArray::SUCCESS) {
                return;
            }

            sprite->GetBaseStats()->field_2EA[index] = 1;

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(mEntries[index].field_4,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x5872A0
void Icewind586B70::Clear()
{
    for (int index = 0; index < 6; index++) {
        mEntries[index].field_0 = 0;
        mEntries[index].field_4 = 0;
        mEntries[index].field_8 = false;
    }
}

// NOTE: Inlined.
Icewind586B70::Entry::Entry()
{
    field_0 = 0;
    field_4 = 0;
    field_8 = false;
}

// 0x587500
void Icewind586B70::Entry::Clear()
{
    field_0 = 0;
    field_4 = 0;
    field_8 = false;
}

// 0x587610
int Icewind586B70::GetCount()
{
    int count = 0;
    for (int index = 0; index < 6; index++) {
        if (mEntries[index].field_0 != 0 && mEntries[index].field_4 != 0) {
            count++;
        }
    }
    return count;
}

// 0x587630
Icewind586B70::Entry::Entry(int a1, int a2)
{
    field_0 = a1;
    field_4 = a2;
    field_8 = false;
}

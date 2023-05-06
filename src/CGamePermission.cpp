#include "CGamePermission.h"

#include "CUtil.h"

// 0x84C534
const BYTE CGamePermission::TOTAL_PERMISSIONS = CGAMEPERMISSION_TOTAL_PERMISSIONS;

// 084C535
const BYTE CGamePermission::AREA_TRANSITION = 1;

// 0x84C536
const BYTE CGamePermission::CHAR_RECORDS = 3;

// 0x84C537
const BYTE CGamePermission::DIALOG = 2;

// 0x84C538
const BYTE CGamePermission::GROUP_POOL = 5;

// 0x84C539
const BYTE CGamePermission::LEADER = 6;

// 0x84C53A
const BYTE CGamePermission::MODIFY_CHARS = 7;

// 0x84C53B
const BYTE CGamePermission::PAUSING = 4;

// 0x84C53C
const BYTE CGamePermission::PURCHASING = 0;

// 0x4C8A40
CGamePermission::CGamePermission()
{
    m_bPermissions[AREA_TRANSITION] = TRUE;
    m_bPermissions[CHAR_RECORDS] = TRUE;
    m_bPermissions[DIALOG] = TRUE;
    m_bPermissions[GROUP_POOL] = TRUE;
    m_bPermissions[LEADER] = TRUE;
    m_bPermissions[MODIFY_CHARS] = TRUE;
    m_bPermissions[PAUSING] = TRUE;
    m_bPermissions[PURCHASING] = TRUE;
}

// 0x4C8A60
BOOLEAN CGamePermission::GetSinglePermission(INT nPermission)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGamePermission.cpp
    // __LINE__: 128
    UTIL_ASSERT_MSG(nPermission >= 0 && nPermission < TOTAL_PERMISSIONS,
        "CGamePermission::GetPermission:  Bad Permission requested.");

    return m_bPermissions[nPermission];
}

// 0x4C8AA0
void CGamePermission::SetSinglePermission(INT nPermission, BOOLEAN bValue)
{
    m_bPermissions[nPermission] = bValue;
}

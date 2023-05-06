#include "CGamePermission.h"

#include "CUtil.h"

// 0x4C8A40
CGamePermission::CGamePermission()
{
    m_bPermissions[1] = TRUE;
    m_bPermissions[3] = TRUE;
    m_bPermissions[2] = TRUE;
    m_bPermissions[5] = TRUE;
    m_bPermissions[6] = TRUE;
    m_bPermissions[7] = TRUE;
    m_bPermissions[4] = TRUE;
    m_bPermissions[0] = TRUE;
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

#ifndef CGAMEPERMISSION_H_
#define CGAMEPERMISSION_H_

#include "mfc.h"

// Seen in `CGamePermission::GetSinglePermission`.
#define TOTAL_PERMISSIONS 8

class CGamePermission {
public:
    CGamePermission();
    BOOLEAN GetSinglePermission(INT nPermission);
    void SetSinglePermission(INT nPermission, BOOLEAN bValue);

    BOOLEAN m_bPermissions[TOTAL_PERMISSIONS];
};

#endif /* CGAMEPERMISSION_H_ */

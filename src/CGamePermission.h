#ifndef CGAMEPERMISSION_H_
#define CGAMEPERMISSION_H_

#include "mfc.h"

#define CGAMEPERMISSION_TOTAL_PERMISSIONS 8

class CGamePermission {
public:
    CGamePermission();
    BOOLEAN GetSinglePermission(INT nPermission);
    void SetSinglePermission(INT nPermission, BOOLEAN bValue);

    static const BYTE TOTAL_PERMISSIONS;
    static const BYTE AREA_TRANSITION;
    static const BYTE CHAR_RECORDS;
    static const BYTE DIALOG;
    static const BYTE GROUP_POOL;
    static const BYTE LEADER;
    static const BYTE MODIFY_CHARS;
    static const BYTE PAUSING;
    static const BYTE PURCHASING;

    BOOLEAN m_bPermissions[CGAMEPERMISSION_TOTAL_PERMISSIONS];
};

#endif /* CGAMEPERMISSION_H_ */

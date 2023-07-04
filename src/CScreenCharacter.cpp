#include "CScreenCharacter.h"

// 0x8F3324
const CString CScreenCharacter::TOKEN_SPELLLEVEL("SPELLLEVEL");

// 0x8F3320
const CString CScreenCharacter::TOKEN_WEAPONNAME("WEAPONNAME");

// 0x8F333C
const CString CScreenCharacter::TOKEN_NUMBER("number");

// 0x8F332C
const CString CScreenCharacter::TOKEN_MINIMUM("MINIMUM");

// 0x8F3334
const CString CScreenCharacter::TOKEN_MAXIMUM("MAXIMUM");

// 0x5D5220
CScreenCharacter::CScreenCharacter()
{
    // TODO: Incomplete.
}

// 0x5D63B0
CScreenCharacter::~CScreenCharacter()
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenCharacter::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x5D62F0
void CScreenCharacter::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x5D6300
BOOL CScreenCharacter::GetShiftKey()
{
    return field_1B8 && m_bShiftKeyDown;
}

// 0x5D6320
void CScreenCharacter::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x5D6330
BOOL CScreenCharacter::CheckSystemKeyShift()
{
    return field_1B8;
}

// 0x5D6340
void CScreenCharacter::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x5D6350
BOOL CScreenCharacter::GetCapsLockKey()
{
    return field_1B8 && m_bCapsLockKeyOn;
}

// 0x5D6330
BOOL CScreenCharacter::CheckSystemKeyCapsLock()
{
    return field_1B8;
}

// 0x699600
SHORT CScreenCharacter::GetNumVirtualKeys()
{
    return CSCREENCHARACTER_VIRTUAL_KEYS;
}

// 0x5D6370
CKeyInfo* CScreenCharacter::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x5D6380
BYTE* CScreenCharacter::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

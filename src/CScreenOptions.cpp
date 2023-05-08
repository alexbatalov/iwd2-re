#include "CScreenOptions.h"

#include "CGameOptions.h"
#include "CUIPanel.h"

// 0x6530E0
CScreenOptions::CScreenOptions()
{
    m_dwErrorTextId = 0;
    m_dwErrorState = 0;
    m_nNumErrorButtons = 0;
    field_484 = 0;
    field_488 = 0;
    field_48A = 0;
    field_48B = 0;
    field_48C = 0;
    field_48D = 0;
    field_E90 = 0;
    field_E91 = 0;
    m_bFullScreenOptions = FALSE;

    SetVideoMode(0);
    m_pVirtualKeys[0] = CKeyInfo(VK_ESCAPE, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo('1', 0, 0);
    m_pVirtualKeys[2] = CKeyInfo('2', 0, 0);
    m_pVirtualKeys[3] = CKeyInfo('3', 0, 0);
    m_pVirtualKeys[4] = CKeyInfo('4', 0, 0);
    m_pVirtualKeys[5] = CKeyInfo('5', 0, 0);
    m_pVirtualKeys[6] = CKeyInfo('6', 0, 0);
    m_pVirtualKeys[7] = CKeyInfo('7', 0, 0);
    m_pVirtualKeys[8] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[9] = CKeyInfo('9', 0, 0);
    m_pVirtualKeys[10] = CKeyInfo(VK_SPACE, -1, 0);
    m_pVirtualKeys[11] = CKeyInfo('A', 0, 0);
    m_pVirtualKeys[12] = CKeyInfo('B', 0, 0);
    m_pVirtualKeys[13] = CKeyInfo('C', 0, 0);
    m_pVirtualKeys[14] = CKeyInfo('D', 0, 0);
    m_pVirtualKeys[15] = CKeyInfo('E', 0, 0);
    m_pVirtualKeys[16] = CKeyInfo('F', 0, 0);
    m_pVirtualKeys[17] = CKeyInfo('G', 0, 0);
    m_pVirtualKeys[18] = CKeyInfo('H', 0, 0);
    m_pVirtualKeys[19] = CKeyInfo('I', 0, 0);
    m_pVirtualKeys[20] = CKeyInfo('J', 0, 0);
    m_pVirtualKeys[21] = CKeyInfo('K', 0, 0);
    m_pVirtualKeys[22] = CKeyInfo('L', 0, 0);
    m_pVirtualKeys[23] = CKeyInfo('M', 0, 0);
    m_pVirtualKeys[24] = CKeyInfo('N', 0, 0);
    m_pVirtualKeys[25] = CKeyInfo('O', 0, 0);
    m_pVirtualKeys[26] = CKeyInfo('P', 0, 0);
    m_pVirtualKeys[27] = CKeyInfo('Q', 0, 0);
    m_pVirtualKeys[28] = CKeyInfo('R', 0, 0);
    m_pVirtualKeys[29] = CKeyInfo('S', 0, 0);
    m_pVirtualKeys[30] = CKeyInfo('T', 0, 0);
    m_pVirtualKeys[31] = CKeyInfo('U', 0, 0);
    m_pVirtualKeys[32] = CKeyInfo('V', 0, 0);
    m_pVirtualKeys[33] = CKeyInfo('W', 0, 0);
    m_pVirtualKeys[34] = CKeyInfo('X', 0, 0);
    m_pVirtualKeys[35] = CKeyInfo('Y', 0, 0);
    m_pVirtualKeys[36] = CKeyInfo('Z', 0, 0);
    m_pVirtualKeys[37] = CKeyInfo('0', 0, 0);
    m_pVirtualKeys[38] = CKeyInfo(VK_BACK, 0, 0);
    m_pVirtualKeys[39] = CKeyInfo('#', -1, 0);
    m_pVirtualKeys[40] = CKeyInfo('$', -1, 0);
    m_pVirtualKeys[41] = CKeyInfo('%', 0, 0);
    m_pVirtualKeys[42] = CKeyInfo('&', 0, 0);
    m_pVirtualKeys[43] = CKeyInfo('\\', 0, 0);
    m_pVirtualKeys[44] = CKeyInfo('(', 0, 0);
    m_pVirtualKeys[45] = CKeyInfo(',', -1, 0);
    m_pVirtualKeys[46] = CKeyInfo('-', -1, 0);
    m_pVirtualKeys[47] = CKeyInfo('.', 0, 0);
    m_pVirtualKeys[48] = CKeyInfo('`', -1, 0);
    m_pVirtualKeys[49] = CKeyInfo('a', -1, 0);
    m_pVirtualKeys[50] = CKeyInfo('b', -1, 0);
    m_pVirtualKeys[51] = CKeyInfo('c', -1, 0);
    m_pVirtualKeys[52] = CKeyInfo('d', -1, 0);
    m_pVirtualKeys[53] = CKeyInfo('e', -1, 0);
    m_pVirtualKeys[54] = CKeyInfo('f', -1, 0);
    m_pVirtualKeys[55] = CKeyInfo('g', -1, 0);
    m_pVirtualKeys[56] = CKeyInfo('h', -1, 0);
    m_pVirtualKeys[57] = CKeyInfo('i', -1, 0);
    m_pVirtualKeys[58] = CKeyInfo('j', -1, 0);
    m_pVirtualKeys[59] = CKeyInfo('k', -1, 0);
    m_pVirtualKeys[60] = CKeyInfo('l', -1, 0);
    m_pVirtualKeys[61] = CKeyInfo('m', -1, 0);
    m_pVirtualKeys[62] = CKeyInfo('n', -1, 0);
    m_pVirtualKeys[63] = CKeyInfo('o', -1, 0);
    m_pVirtualKeys[64] = CKeyInfo('p', -1, 0);
    m_pVirtualKeys[65] = CKeyInfo('q', -1, 0);
    m_pVirtualKeys[66] = CKeyInfo('r', -1, 0);
    m_pVirtualKeys[67] = CKeyInfo('s', -1, 0);
    m_pVirtualKeys[68] = CKeyInfo('t', -1, 0);
    m_pVirtualKeys[69] = CKeyInfo('u', -1, 0);
    m_pVirtualKeys[70] = CKeyInfo('v', -1, 0);
    m_pVirtualKeys[71] = CKeyInfo('w', -1, 0);
    m_pVirtualKeys[72] = CKeyInfo('x', -1, 0);
    m_pVirtualKeys[73] = CKeyInfo('y', -1, 0);
    m_pVirtualKeys[74] = CKeyInfo('z', -1, 0);
    m_pVirtualKeys[75] = CKeyInfo('{', -1, 0);
    m_pVirtualKeys[76] = CKeyInfo(VK_NUMLOCK, -1, 0);
    m_pVirtualKeys[77] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[78] = CKeyInfo(0xC0, 0, 0);
    m_pVirtualKeys[79] = CKeyInfo(0xBD, 0, 0);
    m_pVirtualKeys[80] = CKeyInfo(0xBB, 0, 0);
    m_pVirtualKeys[81] = CKeyInfo(0xDB, 0, 0);
    m_pVirtualKeys[82] = CKeyInfo(0xDD, 0, 0);
    m_pVirtualKeys[83] = CKeyInfo(0xDC, 0, 0);
    m_pVirtualKeys[84] = CKeyInfo(0xBA, 0, 0);
    m_pVirtualKeys[85] = CKeyInfo(0xDE, 0, 0);
    m_pVirtualKeys[86] = CKeyInfo(0xBC, 0, 0);
    m_pVirtualKeys[87] = CKeyInfo(0xBE, 0, 0);
    m_pVirtualKeys[88] = CKeyInfo(0xBF, 0, 0);
    m_pVirtualKeys[89] = CKeyInfo(VK_TAB, -1, 0);

    m_bCtrlKeyDown = FALSE;
    m_bExitProgram = FALSE;
}

// 0x49FC40
BOOL CScreenOptions::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseMove()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseLButton()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseRButton()
{
    return TRUE;
}

// 0x653D40
void CScreenOptions::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x653D80
CScreenOptions::~CScreenOptions()
{
}

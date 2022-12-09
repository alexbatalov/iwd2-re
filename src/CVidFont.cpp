#include "CVidFont.h"

// 0x792CA0
CVidFont::CVidFont()
{
    field_4E2 = 0;
    field_4F4 = 0;
    field_4F8 = 0;
    field_4FC = 0;
    field_4DE = 0;
    m_hFont = NULL;
    field_4E6 = -1;
    field_4E8 = -1;
    field_4EA = -1;
    field_4EC = 0xFFFFFF;
    field_4F0 = 0xFFFFFF;
}

// 0x792D10
CVidFont::~CVidFont()
{
    if (m_hFont != NULL) {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
}

// 0x7930F0
void CVidFont::SetColor(COLORREF color, int a3, int a4)
{
    // TODO: Incomplete.
}

// 0x7A1210
void CVidFont::TextOut3d(const CString& sText, int a3, int a4, const CRect& rect, int a6, int a7)
{
    // TODO: Incomplete.
}

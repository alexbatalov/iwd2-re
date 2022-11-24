#include "CChatBuffer.h"

// #binary-identical
// 0x442B90
CChatBuffer::CChatBuffer()
{
    field_1C = 0;
}

// 0x442BB0
CChatBuffer::~CChatBuffer()
{
    POSITION pos = field_0.GetHeadPosition();
    while (pos != NULL) {
        CString* string = field_0.GetAt(pos);
        if (string != NULL) {
            delete string;
        }

        field_0.GetNext(pos);
    }

    field_0.RemoveAll();
}

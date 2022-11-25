#ifndef CTLKTABLE_H_
#define CTLKTABLE_H_

#include <afx.h>
#include <afxmt.h>
#include <afxtempl.h>

#include "CTlkFileOverride.h"

extern unsigned char byte_8FB954;

class CTlkFile : public CFile {
public:
};

class CTlkTable {
public:
    static BOOLEAN STRREF_ON;

    CTlkTable();
    ~CTlkTable();

    CTypedPtrMap<CMapWordToPtr, USHORT, CTlkFile*> field_0;
    CMapStringToString field_1C;
    CCriticalSection field_38;
    unsigned char field_58;
    CTlkFileOverride m_override;
    unsigned char field_A4;
};

#endif /* CTLKTABLE_H_ */

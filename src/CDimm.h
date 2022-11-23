#ifndef CDIMM_H_
#define CDIMM_H_

#include <afx.h>
#include <afxtempl.h>

#include "CDimmKeyTable.h"
#include "CResCache.h"

class CRes;

// #memory-identical
class CDimm {
public:
    CDimm();
    ~CDimm();

    int CancelRequest(CRes* pRes);
    void DestroyKeyTable();
    void Dump(CRes* pRes, int a2, int a3);
    void DumpAll();
    void ReleaseResObject(CRes* pRes);

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ short field_8;
    /* 000A */ CObList field_A;
    /* 0026 */ CObList field_26;
    /* 0042 */ CObList field_42;
    /* 005E */ CObList field_5E;
    /* 007A */ CObList field_7A;
    /* 0096 */ CObList field_96;
    /* 00B2 */ CObList field_B2;
    /* 00CE */ int field_CE;
    /* 00D2 */ int field_D2;
    /* 00D6 */ int field_D6;
    /* 00DA */ int field_DA;
    /* 00DE */ int dwTotalPhysicalMemory; // #guess
    /* 00E2 */ int field_E2;
    /* 00E6 */ int field_E6;
    /* 00EA */ short field_EA;
    /* 00EC */ int field_EC;
    /* 00F0 */ CResCache cResCache; // #guess
    /* 024C */ CDimmKeyTable cKeyTable; // #guess
    /* 0270 */ int field_270;
    /* 0274 */ int field_274;
    /* 0278 */ CList<CString, CString> field_278;
    /* 0294 */ unsigned char field_294;
    /* 0295 */ unsigned char field_295;
    /* 0296 */ unsigned char field_296;
    /* 0297 */ unsigned char field_297;
    /* 0298 */ CString field_298;
    /* 029C */ int field_29C;
    /* 02A0 */ int field_2A0;
    /* 02A4 */ unsigned char field_2A4;
    /* 02A5 */ unsigned char field_2A5;
    /* 02A6 */ unsigned char field_2A6;
};

#endif /* CDIMM_H_ */

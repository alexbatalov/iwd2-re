#ifndef CRES_H_
#define CRES_H_

#include "mfc.h"

#include "CChitin.h"
#include "CResRef.h"
#include "ChDataTypes.h"

struct CDimmKeyTableEntry;

class CRes : public CObject {
public:
    enum Flags {
        RES_FLAG_0x04 = 0x04,
        RES_FLAG_0x08 = 0x08,
        RES_FLAG_0x10 = 0x10,
        RES_FLAG_0x100 = 0x100,
    };

    CRes();
    ~CRes();

    /* 000C */ virtual BOOL func_C();
    /* 0010 */ virtual void func_10();
    /* 0014 */ virtual int func_14();
    /* 0018 */ virtual int func_18();

    int CancelRequest();
    int Dump(int a2);
    int GetDemands();
    RESID GetID();
    /* 001C */ virtual CResRef GetResRef();
    /* 0020 */ virtual USHORT GetResType();
    int Release();
    int Request();
    void SetID(RESID nNewID);
    void SetPriority(int nNewPriority);
    BOOL Write(const CString& sFilePath, LPVOID lpBuf, DWORD dwSize);

    /* 0004 */ DWORD dwFlags; // #guess
    /* 0008 */ int field_8;
    /* 000C */ CObList* m_pCurrentList; // #guess
    /* 0010 */ CDimmKeyTableEntry* m_pDimmKeyTableEntry; // #guess
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ CCriticalSection field_20;
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ POSITION m_pCurrentListPos; // #guess
    /* 004C */ RESID m_nID;
};

template <class T, int nType>
class CResHelper {
public:
    /* 0000 */ int field_0;
    /* 0004 */ T* pRes;
    /* 0008 */ CResRef cResRef;

    CResHelper()
    {
        pRes = NULL;
        cResRef = "";
        field_0 = 0;
    }

    ~CResHelper()
    {
        if (pRes != NULL && cResRef != "") {
            if (field_0) {
                (static_cast<CRes*>(pRes))->CancelRequest();
                field_0 = 0;
            }
            g_pChitin->cDimm.ReleaseResObject(pRes);
        }
        pRes = NULL;
    }
};

#endif /* CRES_H_ */

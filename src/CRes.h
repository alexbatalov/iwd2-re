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
    /* 0000 */ /* GetRuntimeClass */
    /* 0004 */ ~CRes() override;
    /* 0008 */ /* Serialize */
    /* 000C */ virtual BOOL OnResourceFreed();
    /* 0010 */ virtual void OnResourceServiced();
    /* 0014 */ virtual int GetFixedResourceSize();
    /* 0018 */ virtual int GetFixedResourceDataOffset();
    /* 001C */ virtual CResRef GetResRef();
    /* 0020 */ virtual USHORT GetType();

    int CancelRequest();
    int Dump(int a2);
    int GetDemands();
    RESID GetID();
    int Release();
    int Request();
    void SetID(RESID nNewID);
    void SetPriority(unsigned int nNewPriority);
    BOOL Write(const CString& sFilePath, LPVOID lpBuf, DWORD dwSize);

    /* 0004 */ DWORD dwFlags; // #guess
    /* 0008 */ void* m_pData;
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

    void SetResRef(const CResRef& cNewResRef, BOOL bSetAutoRequest, BOOL bWarningIfMissing)
    {
        if (cResRef != cNewResRef && cResRef != "") {
            if (field_0) {
                (static_cast<CRes*>(pRes))->CancelRequest();
            }
        }

        if (cNewResRef != "") {
            T* pNewRes = static_cast<T*>(g_pChitin->cDimm.GetResObject(cNewResRef, nType, TRUE));
            if (pNewRes != NULL) {
                pRes = pNewRes;
                cResRef = cNewResRef;
            } else {
                pRes = NULL;
                cResRef = "";
            }
        } else {
            pRes = NULL;
            cResRef = "";
        }
    }
};

#endif /* CRES_H_ */

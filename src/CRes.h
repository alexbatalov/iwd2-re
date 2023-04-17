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
        RES_FLAG_0x20 = 0x20,
        RES_FLAG_0x40 = 0x40,
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
    void* Demand();
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
    /* 001C */ DWORD m_nResSizeActual;
    /* 0020 */ CCriticalSection field_20;
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ POSITION m_pCurrentListPos; // #guess
    /* 004C */ RESID m_nID;
};

template <class T, int nType>
class CResHelper {
public:
    /* 0000 */ BOOL bLoading;
    /* 0004 */ T* pRes;
    /* 0008 */ CResRef cResRef;

    CResHelper()
    {
        pRes = NULL;
        cResRef = "";
        bLoading = FALSE;
    }

    ~CResHelper()
    {
        if (pRes != NULL && cResRef != "") {
            if (bLoading) {
                (static_cast<CRes*>(pRes))->CancelRequest();
                bLoading = FALSE;
            }
            g_pChitin->cDimm.ReleaseResObject(pRes);
        }
        pRes = NULL;
    }

    void SetResRef(const CResRef& cNewResRef, BOOL bSetAutoRequest, BOOL bWarningIfMissing)
    {
        if (cResRef != cNewResRef) {
            if (pRes != NULL && cResRef != "" && bLoading) {
                (static_cast<CRes*>(pRes))->CancelRequest();
            }

            if (cNewResRef != "") {
                T* pNewRes = static_cast<T*>(g_pChitin->cDimm.GetResObject(cNewResRef, nType, bWarningIfMissing));
                if (pNewRes != NULL) {
                    pRes = pNewRes;
                    if (bSetAutoRequest) {
                        bLoading = TRUE;
                        static_cast<CRes*>(pNewRes)->Request();
                    }
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
    }

    const CResRef& GetResRef() const
    {
        return cResRef;
    }

    int Request()
    {
        if (pRes != NULL) {
            return static_cast<CRes*>(pRes)->Request();
        } else {
            return 0;
        }
    }

    int Release()
    {
        if (pRes != NULL) {
            return static_cast<CRes*>(pRes)->Release();
        } else {
            return 0;
        }
    }
};

#endif /* CRES_H_ */

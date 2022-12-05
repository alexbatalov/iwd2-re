#ifndef CDIMM_H_
#define CDIMM_H_

#include <afx.h>
#include <afxtempl.h>

#include "CDimmKeyTable.h"
#include "CResCache.h"

#define DIMM_NOT_IN_DIRECTORY_LIST 80

class CRes;
class CResFile;

// #memory-identical
class CDimm {
public:
    // #guess
    enum Priority {
        PRIORITY_LOW,
        PRIORITY_MEDIUM,
        PRIORITY_HIGH,
        PRIORITY_ANY,
    };

    CDimm();
    ~CDimm();

    BOOL AddToDirectoryList(const CString& sDirName, BOOL a3);
    BOOL AddTemporaryKey(const CString& a2, CResRef cResRef, USHORT nResType);
    BOOL RemoveTemporaryKey(const CString& sDirName, CResRef cResRef, USHORT nType);
    int CancelRequest(CRes* pRes);
    BOOL CDScan(USHORT a2);
    BOOL CreateKeyTable();
    void DestroyKeyTable();
    int Dump(CRes* pRes, int a2, int a3);
    int DumpAll();
    int FindDirectoryInDirectoryList(const CString& sDirName);
    BOOL FindFileInDirectoryList(const CString& sDirName, CString& sFileName);
    BOOL GetElementInDirectoryList(int a2, CString& a3);
    int GetMemoryAmount();
    CResFile* GetResFilePtr(UINT a2);
    BOOL GetResFileName(UINT nIndex, CString& sResFileName, USHORT& nResType, BOOLEAN a5);
    CRes* GetResObject(const CResRef& cResRef, USHORT nResType, BOOLEAN a3);
    BOOL MemoryAlmostFull();
    void ReduceFreedList(UINT a2);
    int Release(CRes* pRes);
    void ReleaseResObject(CRes* pRes);
    BOOL RemoveFromDirectoryList(const CString& sDirName, BOOL a3);
    int Request(CRes* pRes);
    BOOL RequestsPending(int nPriority);
    INT RequestsPendingCount();
    INT RequestsPendingCount(int nPriority);
    BOOL Resume();
    BOOL ResumeServicing();
    void SetNewPriority(CRes* pRes, int nNewPriority);
    BOOL Suspend();
    void Update();
    BOOL WriteResourceWithData(const CString& sFileName, CRes* pRes, LPVOID lpBuf, DWORD dwSize);
    BOOL WriteSetUp(const CString& a2, CString& a3);

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ short field_8;
    /* 000A */ CObList m_lServicedLow; // #guess
    /* 0026 */ CObList m_lServicedMedium; // #guess
    /* 0042 */ CObList m_lServicedHigh; // #guess
    /* 005E */ CObList m_lRequestedLow; // #guess
    /* 007A */ CObList m_lRequestedMedium; // #guess
    /* 0096 */ CObList m_lRequestedHigh; // #guess
    /* 00B2 */ CObList m_lFreed; // #guess
    /* 00CE */ int field_CE;
    /* 00D2 */ int field_D2;
    /* 00D6 */ unsigned int field_D6;
    /* 00DA */ unsigned int field_DA;
    /* 00DE */ DWORD dwTotalPhysicalMemory; // #guess
    /* 00E2 */ unsigned int m_nResFiles;
    /* 00E6 */ int field_E6;
    /* 00EA */ short field_EA;
    /* 00EC */ CResFile** m_ppResFiles;
    /* 00F0 */ CResCache cResCache; // #guess
    /* 024C */ CDimmKeyTable m_cKeyTable; // #guess
    /* 0270 */ int field_270;
    /* 0274 */ int field_274;
    /* 0278 */ CList<CString, CString> m_lDirectories; // #guess
    /* 0294 */ unsigned char field_294;
    /* 0295 */ unsigned char field_295;
    /* 0296 */ unsigned char field_296;
    /* 0297 */ unsigned char field_297;
    /* 0298 */ CString field_298;
    /* 029C */ int field_29C;
    /* 02A0 */ int field_2A0;
    /* 02A4 */ unsigned char field_2A4;
    /* 02A5 */ BOOLEAN m_bTemporaryKeyAdd;
    /* 02A6 */ BOOLEAN m_bTemporaryDirAdd; // #guess
};

#endif /* CDIMM_H_ */

#ifndef CAIIDLIST_H_
#define CAIIDLIST_H_

#include "mfc.h"

#include "CRes.h"
#include "CResText.h"

class CAIId {
public:
    LONG m_id;
    CString m_line;
};

class CAIIdList : public CResHelper<CResText, 1008> {
public:
    CAIIdList();
    CAIIdList(CResRef id);
    ~CAIIdList();
    void LoadList(BOOL faster);
    CAIId* Find(CString name, BOOL caseSensitive) const;
    void LoadList(CResRef id, BOOL faster);
    CAIId* Find(LONG id) const;

    CString m_fileName;
    CTypedPtrList<CPtrList, CAIId*> m_idList;
    BOOL m_faster;
    CAIId** m_pIdArray;
    LONG m_nArray;
};

#endif /* CAIIDLIST_H_ */

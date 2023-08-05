#ifndef C2DARRAY_H_
#define C2DARRAY_H_

#include "CRes.h"
#include "CResText.h"

class C2DArray : public CResHelper<CResText, 1012> {
public:
    C2DArray();
    ~C2DArray();
    BOOL Demand();
    BOOL Release();
    void Load(const CResRef& cResRef);
    const CString& GetAt(const CString& nX, const CString& nY) const;
    LONG GetAtLong(const CPoint& coordinates) const;
    SHORT GetHeight() const { return m_nSizeY; }
    SHORT GetWidth() const { return m_nSizeX; }
    // 0x403530
    CString GetDefault() const { return m_default; }
    CString* GetRowNames() const { return m_pNamesX; }
    CString* GetColumnNames() const { return m_pNamesY; }
    BOOLEAN Find(CString& sSearchString, CString& sXLabel, CString& sYLabel, BOOLEAN bSearchLabels) const;
    BOOLEAN Find(CString& sSearchString, CPoint& ptLocation, BOOLEAN bSearchLabels) const;
    BOOLEAN Find(CString& sSearchString, CPoint& ptLocation) const;

    const CString& GetAt(const CPoint& coordinates) const;

protected:
    CString* m_pNamesX;
    CString* m_pNamesY;
    CString* m_pArray;
    CString m_default;
    SHORT m_nSizeX;
    SHORT m_nSizeY;
};

#endif /* C2DARRAY_H_ */

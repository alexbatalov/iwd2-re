#ifndef CMEMINI_H_
#define CMEMINI_H_

#include "mfc.h"

#include "CResINI.h"

class CMemINIValue {
public:
    CMemINIValue(const CString& name, const CString& value);
    virtual ~CMemINIValue();
    const CString& GetName() const { return mName; }
    const CString& GetValue() const { return mValue; }
    void SetName(const CString& name) { mName = name; }
    void SetValue(const CString& value) { mValue = value; }
    CMemINIValue& operator=(const CMemINIValue& other);
    int operator==(const CMemINIValue& other);
    int operator!=(const CMemINIValue& other);

protected:
    CString mName;
    CString mValue;
};

class CMemINISection : public CTypedPtrList<CPtrList, CMemINIValue*> {
public:
    CMemINISection(const CString& sectionName);
    ~CMemINISection() override;
    void ClearSection();
    void Set(const CString& name, const CString& value);
    void Set(const CMemINIValue& value);
    CMemINIValue* Get(const CString& name);
    void SetSectionName(const CString& sectionName) { mSectionName = sectionName; }
    const CString& GetSectionName() const { return mSectionName; }

protected:
    CString mSectionName;
};

// NOTE: Have to follow original code with `void*` pointer is arg type because
// `CTypedPtrList` cannot handle nested `CPtrList` (compiler chokes when it
// tries to instantiate `Add` overloads which accept new element and an
// array of said elements).
class CMemINI : public CTypedPtrList<CPtrList, void*> {
public:
    CMemINI();
    ~CMemINI() override;
    void ClearINI();
    CMemINIValue* Get(const CString& sectionName, const CString& name);
    CMemINIValue* GetFast(const CString& sectionName, const CString& name);
    CMemINISection* GetSection(const CString& sectionName);
    void SetFileName(const CString& fileName) { mFileName = fileName; }
    const CString& GetFileName() const { return mFileName; }
    int Load(const CString& source);

protected:
    CString mFileName;
    CMemINISection* mpLastSection;
};

class CMemINIRes : public CResHelper<CResINI, 2050> {
public:
    CMemINIRes();
    BOOL IsEOF() const { return mEOF; }
    void Rewind();
    CString GetLine();
    BYTE* GetData();
    DWORD GetDataSize();

protected:
    /* 0010 */ BYTE* mpData;
    /* 0014 */ int mDataLength;
    /* 0018 */ CResRef ResRef;
    /* 0020 */ int mFilePosition;
    /* 0024 */ BOOL mEOF;
};

#endif /* CMEMINI_H_ */

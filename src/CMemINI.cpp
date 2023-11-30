#include "CMemINI.h"

// 0x6A0CE0
CMemINIValue::CMemINIValue(const CString& name, const CString& value)
    : mName(name)
    , mValue(value)
{
}

// 0x6A0D40
CMemINIValue::~CMemINIValue()
{
}

// NOTE: Inlined.
CMemINIValue& CMemINIValue::operator=(const CMemINIValue& other)
{
    mName = other.GetName();
    mValue = other.GetValue();
    return *this;
}

// NOTE: Inlined.
int CMemINIValue::operator==(const CMemINIValue& other)
{
    return mName == other.GetName()
        && mValue == other.GetValue();
}

// NOTE: Inlined.
int CMemINIValue::operator!=(const CMemINIValue& other)
{
    return mName != other.GetName()
        || mValue != other.GetValue();
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CMemINISection::CMemINISection(const CString& sectionName)
    : mSectionName(sectionName)
{
    RemoveAll();
}

// 0x6A0DC0
CMemINISection::~CMemINISection()
{
    // NOTE: Uninline.
}

// NOTE: Inlined.
void CMemINISection::ClearSection()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMemINIValue* value = GetNext(pos);
        if (value != NULL) {
            delete value;
        }
    }
    RemoveAll();
}

// NOTE: Inlined.
void CMemINISection::Set(const CString& name, const CString& value)
{
    CMemINIValue* v = Get(name);
    if (v != NULL) {
        v->SetValue(value);
    } else {
        AddTail(new CMemINIValue(name, value));
    }
}

// NOTE: Inlined.
void CMemINISection::Set(const CMemINIValue& value)
{
    Set(value.GetName(), value.GetValue());
}

// 0x6A1400
CMemINIValue* CMemINISection::Get(const CString& name)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMemINIValue* v = GetNext(pos);
        if (v != NULL) {
            if (v->GetName().CompareNoCase(name) == 0) {
                return v;
            }
        }
    }
    return NULL;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CMemINI::CMemINI()
{
    mpLastSection = NULL;
}

// 0x46A010
CMemINI::~CMemINI()
{
    ClearINI();
}

// 0x6A0C80
void CMemINI::ClearINI()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMemINISection* section = reinterpret_cast<CMemINISection*>(GetNext(pos));
        if (section != NULL) {
            delete section;
        }
    }
    RemoveAll();

    mpLastSection = NULL;
}

// NOTE: Inlined.
CMemINIValue* CMemINI::Get(const CString& sectionName, const CString& name)
{
    CMemINISection* section = GetSection(sectionName);
    if (section != NULL) {
        return section->Get(name);
    }

    return NULL;
}

// 0x6A0E90
CMemINIValue* CMemINI::GetFast(const CString& sectionName, const CString& name)
{
    if (mpLastSection != NULL && mpLastSection->GetSectionName().CompareNoCase(sectionName) == 0) {
        // NOTE: Uninline.
        return mpLastSection->Get(name);
    }

    // NOTE: Uninline.
    return Get(sectionName, name);
}

// 0x6A0E40
CMemINISection* CMemINI::GetSection(const CString& sectionName)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMemINISection* section = reinterpret_cast<CMemINISection*>(GetNext(pos));
        if (section != NULL) {
            if (section->GetSectionName().CompareNoCase(sectionName) == 0) {
                return section;
            }
        }
    }
    return NULL;
}

// 0x6A0F70
int CMemINI::Load(const CString& source)
{
    int values = 0;

    // NOTE: Uninline.
    ClearINI();

    CMemINIRes res;
    res.SetResRef(CResRef(source), TRUE, source.Left(2) != "AR");

    if (res.GetRes() == NULL) {
        return 0;
    }

    // NOTE: Uninline.
    res.Rewind();

    CMemINISection* section;
    while (!res.IsEOF()) {
        CString str = res.GetLine();
        str.TrimLeft();
        str.TrimRight();
        if (str.GetLength() > 2) {
            if (str[0] == '[') {
                int closeIndex = str.Find(']');
                if (closeIndex > 0) {
                    CString sectionName = str.Mid(1, closeIndex - 1);
                    sectionName.TrimLeft();
                    sectionName.TrimRight();

                    section = GetSection(sectionName);
                    if (section == NULL) {
                        section = new CMemINISection(sectionName);
                        AddTail(section);
                    }
                }
            } else if (str[0] != ';' && str[0] != '/') {
                int equIndex = str.Find('=');
                if (equIndex > 0 && equIndex < str.GetLength() - 1) {
                    CString name = str.Left(equIndex);
                    CString value = str.Mid(equIndex + 1);

                    name.TrimRight();
                    value.TrimLeft();

                    if (section != NULL) {
                        // NOTE: Uninline.
                        section->Set(name, value);
                        values++;
                    }
                }
            }
        }
    }

    if (GetCount() > 0) {
        mpLastSection = reinterpret_cast<CMemINISection*>(GetHead());
    }

    return values;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CMemINIRes::CMemINIRes()
{
    mpData = NULL;
    mDataLength = 0;
    mFilePosition = 0;
    mEOF = FALSE;
}

// NOTE: Inlined.
void CMemINIRes::Rewind()
{
    mDataLength = GetDataSize();
    mpData = GetData();
}

// 0x6A1440
CString CMemINIRes::GetLine()
{
    if (mEOF) {
        return CString("");
    }

    int start = mFilePosition;
    int end = start;
    while (end < mDataLength) {
        if (mpData[end] == '\r' || mpData[end] == '\n') {
            break;
        }
        end++;
    }

    CString str(reinterpret_cast<char*>(mpData + start), end - start);

    while (end < mDataLength) {
        if (mpData[end] != '\r' && mpData[end] != '\n') {
            break;
        }
        end++;
    }

    if (end >= mDataLength) {
        mEOF = TRUE;
    }

    return str;
}

// NOTE: Inlined.
BYTE* CMemINIRes::GetData()
{
    if (pRes != NULL) {
        return reinterpret_cast<BYTE*>(pRes->Demand());
    } else {
        return NULL;
    }
}

// NOTE: Inlined.
DWORD CMemINIRes::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

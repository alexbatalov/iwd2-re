#include "C2DArray.h"

#include "CAIUtil.h"

#define TAB '\t'
#define NEWLINE '\n'
#define SPACE ' '

// NOTE: Inlined.
C2DArray::C2DArray()
{
    m_nSizeX = 0;
    m_nSizeY = 0;
    m_pNamesX = NULL;
    m_pNamesY = NULL;
    m_pArray = NULL;
}

// NOTE: Inlined.
C2DArray::~C2DArray()
{
    if (m_pNamesX != NULL) {
        delete[] m_pNamesX;
    }

    if (m_pNamesY != NULL) {
        delete[] m_pNamesY;
    }

    if (m_pArray != NULL) {
        delete[] m_pArray;
    }
}

// 0x402B10
BOOL C2DArray::Demand()
{
    if (cResRef == "") {
        return FALSE;
    }

    if (pRes == NULL) {
        return FALSE;
    }

    pRes->Demand();

    return pRes != NULL;
}

// 0x402B50
BOOL C2DArray::Release()
{
    if (pRes != NULL) {
        // NOTE: Calls unknown method of `CResText` at 0x402B5A, which in turn
        // calls `Release` and always returns 1.
        pRes->Release();
        return 1;
    } else {
        return 0;
    }
}

// 0x402B70
void C2DArray::Load(const CResRef& cResRef)
{
    SetResRef(cResRef, TRUE, TRUE);
    Request();
    if (pRes != NULL) {
        pRes->Demand();
        CString sText = pRes->GetText();
        pRes->Release();

        sText.Replace(TAB, SPACE);

        CString v1;
        CString v2;
        CString v3;
        CString v4;
        CString v5;
        SHORT sizeX;
        SHORT sizeY;
        SHORT posX;
        SHORT posY;

        v1 = CAIUtil::ReadAfterChar(sText, NEWLINE);
        v5 = CAIUtil::ReadToChar(v1, NEWLINE);
        v1 = CAIUtil::ReadAfterChar(v1, NEWLINE);
        v5.TrimLeft();
        v5.TrimRight();
        m_default = v5;

        v3 = CAIUtil::ReadToChar(v1, NEWLINE);
        v1 = CAIUtil::ReadAfterChar(v1, NEWLINE);
        v3.TrimLeft();
        v3.TrimRight();

        sizeX = 0;
        v4 = v3;
        while (v4.GetLength() > 0) {
            sizeX++;
            v4 = CAIUtil::ReadAfterChar(v4, SPACE);
            v4.TrimLeft();
            v4.TrimRight();
        }

        m_nSizeX = sizeX;

        if (m_pNamesX != NULL) {
            delete m_pNamesX;
        }

        m_pNamesX = new CString[m_nSizeX];

        posX = 0;
        v4 = v3;
        while (v4.GetLength() > 0) {
            v5 = CAIUtil::ReadToChar(v4, SPACE);
            m_pNamesX[posX] = v5;
            m_pNamesX[posX].MakeUpper();
            v4 = CAIUtil::ReadAfterChar(v4, SPACE);
            v4.TrimLeft();
            v4.TrimRight();
            posX++;
        }

        sizeY = 0;
        v2 = v1;
        while (v2.GetLength() > 0) {
            sizeY++;
            v2 = CAIUtil::ReadAfterChar(v2, NEWLINE);
        }

        m_nSizeY = sizeY;

        if (m_pNamesY != NULL) {
            delete m_pNamesY;
        }

        m_pNamesY = new CString[m_nSizeY];

        if (m_pArray != NULL) {
            delete m_pArray;
        }

        m_pArray = new CString[m_nSizeX * m_nSizeY];

        posY = 0;
        v2 = v1;
        while (v2.GetLength() > 0) {
            v3 = CAIUtil::ReadToChar(v2, NEWLINE);
            v2 = CAIUtil::ReadAfterChar(v2, NEWLINE);
            v5 = CAIUtil::ReadToChar(v3, SPACE);
            m_pNamesY[posY] = v5;
            m_pNamesY[posY].MakeUpper();
            v4 = CAIUtil::ReadAfterChar(v3, SPACE);
            v4.TrimLeft();
            v4.TrimRight();

            posX = 0;
            while (v4.GetLength() > 0 && posX < m_nSizeX) {
                v5 = CAIUtil::ReadToChar(v4, SPACE);
                v4 = CAIUtil::ReadAfterChar(v4, SPACE);
                v4.TrimLeft();
                v4.TrimRight();
                m_pArray[posY * m_nSizeX + posX] = v5;
                posX++;
            }
            posY++;
        }
    }
}

// 0x403340
const CString& C2DArray::GetAt(const CString& nX, const CString& nY) const
{
    CString nameX = nX;
    nameX.MakeUpper();

    CString nameY = nY;
    nameY.MakeUpper();

    for (SHORT x = 0; x < m_nSizeX; x++) {
        if (m_pNamesX[x].Compare(nameX) == 0) {
            for (SHORT y = 0; y < m_nSizeY; y++) {
                if (m_pNamesY[y].Compare(nameY) == 0) {
                    return m_pArray[x + y * m_nSizeX];
                }
            }
        }
    }

    return m_default;
}

// 0x403440
LONG C2DArray::GetAtLong(const CPoint& coordinates) const
{
    LONG value;

    if (coordinates.x >= 0 && coordinates.x < m_nSizeX && coordinates.y >= 0 && coordinates.y < m_nSizeY) {
        value = atol(m_pArray[coordinates.x + m_nSizeX * coordinates.y].GetBuffer(128));
        m_pArray[coordinates.x + m_nSizeX * coordinates.y].ReleaseBuffer();
    } else {
        // FIXME: Unnecessary copy.
        CString string = GetDefault();
        value = atol(string.GetBuffer(128));
        string.ReleaseBuffer();
    }

    return value;
}

// 0x403550
BOOLEAN C2DArray::Find(CString& sSearchString, CString& sXLabel, CString& sYLabel, BOOLEAN bSearchLabels) const
{
    CString sString = sSearchString;
    sString.MakeUpper();

    for (SHORT x = 0; x < m_nSizeX; x++) {
        if (bSearchLabels == TRUE) {
            if (m_pNamesX[x].Compare(sString) == 0) {
                sXLabel = m_pNamesX[x];
                sXLabel.MakeUpper();
                sYLabel = "";
                return TRUE;
            }
        }

        for (SHORT y = 0; y < m_nSizeY; y++) {
            if (bSearchLabels == TRUE) {
                if (x == 0) {
                    if (m_pNamesY[y].Compare(sString) == 0) {
                        sXLabel = "";
                        sYLabel = m_pNamesY[y];
                        sYLabel.MakeUpper();
                        return TRUE;
                    }
                }
            }

            if (m_pArray[x + y * m_nSizeX].Compare(sString) == 0) {
                sXLabel = m_pNamesX[x];
                sXLabel.MakeUpper();
                sYLabel = m_pNamesY[y];
                sYLabel.MakeUpper();
                return TRUE;
            }
        }
    }

    return FALSE;
}

// 0x4037A0
BOOLEAN C2DArray::Find(CString& sSearchString, CPoint& ptLocation, BOOLEAN bSearchLabels) const
{
    CString sString = sSearchString;
    sString.MakeUpper();

    for (SHORT x = 0; x < m_nSizeX; x++) {
        if (bSearchLabels == TRUE) {
            if (m_pNamesX[x].Compare(sString) == 0) {
                ptLocation.x = x;
                ptLocation.y = -1;
                return TRUE;
            }
        }

        for (SHORT y = 0; y < m_nSizeY; y++) {
            if (bSearchLabels == TRUE) {
                if (x == 0) {
                    if (m_pNamesY[y].Compare(sString) == 0) {
                        ptLocation.x = -1;
                        ptLocation.y = y;
                        return TRUE;
                    }
                }
            }

            if (m_pArray[x + y * m_nSizeX].Compare(sString) == 0) {
                ptLocation.x = x;
                ptLocation.y = y;
                return TRUE;
            }
        }
    }

    return FALSE;
}

// #guess
// 0x4038E0
BOOLEAN C2DArray::Find(CString& sSearchString, CPoint& ptLocation) const
{
    CString sString = sSearchString;
    sString.MakeUpper();

    for (SHORT y = 0; y < m_nSizeY; y++) {
        if (m_pNamesY->Compare(sString) == 0) {
            ptLocation.x = -1;
            ptLocation.y = y;
            return TRUE;
        }
    }

    return FALSE;
}

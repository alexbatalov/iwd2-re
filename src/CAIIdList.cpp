#include "CAIIdList.h"

#include "CAIUtil.h"

// 0x40A1D0
CAIIdList::CAIIdList()
{
    m_pIdArray = NULL;
    m_nArray = 0;
    m_faster = FALSE;
}

// 0x40A280
CAIIdList::CAIIdList(CResRef id)
{
    // NOTE: Uninline.
    SetResRef(id, TRUE, TRUE);
    LoadList(FALSE);
}

// 0x40A3E0
CAIIdList::~CAIIdList()
{
    POSITION pos = m_idList.GetHeadPosition();
    while (pos != NULL) {
        CAIId* node = m_idList.GetNext(pos);
        if (node != NULL) {
            delete node;
        }
    }
    m_idList.RemoveAll();

    if (m_faster) {
        delete m_pIdArray;
    }
}

// 0x40A4D0
void CAIIdList::LoadList(BOOL faster)
{
    LONG maxId = 0;
    char idLine[256] = { 0 };
    BOOL negatives = FALSE;
    CString temp;

    Request();

    if (pRes != NULL) {
        pRes->Demand();
        CString text = pRes->GetText();
        pRes->Release();

        CString line;
        CString remainingText = CAIUtil::ReadAfterChar(text, '\n');
        while (remainingText.GetLength() > 0) {
            line = CAIUtil::ReadToChar(remainingText, '\n');
            remainingText = CAIUtil::ReadAfterChar(remainingText, '\n');

            LONG id;
            sscanf(line, "%i %s", &id, idLine);

            CAIId* node = new CAIId;
            node->m_id = id;

            if (id > maxId) {
                maxId = id;
            }

            if (id < 0) {
                negatives = TRUE;
            }

            temp = idLine;
            temp.TrimLeft();
            temp.TrimRight();
            node->m_line = temp;
            m_idList.AddTail(node);
        }

        m_pIdArray = NULL;
        m_faster = faster && !negatives;

        if (m_faster) {
            m_nArray = maxId + 1;
            m_pIdArray = new CAIId*[m_nArray];

            for (LONG index = 0; index < m_nArray; index++) {
                m_pIdArray[index] = NULL;
            }

            POSITION pos = m_idList.GetHeadPosition();
            while (pos != NULL) {
                CAIId* node = m_idList.GetNext(pos);
                m_pIdArray[node->m_id] = node;
            }
        }
    }
}

// 0x40A790
CAIId* CAIIdList::Find(CString name, BOOL caseSensitive) const
{
    CString funcName;

    name.TrimLeft();
    name.TrimRight();

    POSITION pos = m_idList.GetHeadPosition();
    while (pos != NULL) {
        CAIId* node = m_idList.GetNext(pos);

        funcName = CAIUtil::ReadToChar(node->m_line, '(');
        funcName.TrimLeft();
        funcName.TrimRight();

        if (!caseSensitive) {
            if (name.Compare(funcName) == 0) {
                return node;
            }
        } else {
            // FIXME: Can be uppercased once outside of the loop.
            name.MakeUpper();
            funcName.MakeUpper();

            if (name.Compare(funcName) == 0) {
                return node;
            }
        }
    }

    return NULL;
}

// 0x40A8F0
void CAIIdList::LoadList(CResRef id, BOOL faster)
{
    SetResRef(id, TRUE, TRUE);
    LoadList(faster);
}

// 0x40AA00
CAIId* CAIIdList::Find(LONG id) const
{
    if (m_faster) {
        if (id > 0 && id < m_nArray) {
            return m_pIdArray[id];
        }
    } else {
        POSITION pos = m_idList.GetHeadPosition();
        while (pos != NULL) {
            CAIId* node = m_idList.GetNext(pos);
            if (node->m_id == id) {
                return node;
            }
        }
    }

    return NULL;
}

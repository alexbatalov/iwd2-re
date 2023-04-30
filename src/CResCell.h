#ifndef CRESCELL_H_
#define CRESCELL_H_

#include "mfc.h"

#include "CRes.h"
#include "ChDataTypes.h"

class CResCell : public CRes {
public:
    CResCell();
    /* 0004 */ ~CResCell() override;
    void* Demand();
    FRAMEENTRY* GetFrame(WORD nSequence, WORD nFrame, BOOL bDoubleSize);
    BOOL GetCompressed(FRAMEENTRY* pFrame, BOOL bDoubleSize);
    BYTE* GetFrameData(FRAMEENTRY* pFrame, BOOL bDoubleSize);
    int Release();
    void ResRefChange();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed; // #guess
    /* 0054 */ BAMHEADER* m_pBamHeader;
    /* 0058 */ BAMHEADER* m_pBamHeaderCopy;
    /* 005C */ FRAMEENTRY* m_pFrames;
    /* 0060 */ SEQUENCEENTRY* m_pSequences;
    /* 0064 */ WORD* m_pFrameList;
    /* 0068 */ WORD m_nFrameListSize;
    /* 006A */ RGBQUAD* m_pPalette;
    /* 006E */ FRAMEENTRY m_doubleSizeFrameEntry; // #guess
    /* 007A */ BOOL m_bParsing; // #guess
    /* 007E */ int field_7E;
};

#endif /* CRESCELL_H_ */

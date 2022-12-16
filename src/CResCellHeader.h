#ifndef CRESCELLHEADER_H_
#define CRESCELLHEADER_H_

#include "mfc.h"

#include "CRes.h"
#include "ChDataTypes.h"

class CResCellHeader : public CRes {
public:
    CResCellHeader();
    /* 0004 */ ~CResCellHeader() override;
    void* Demand();
    FRAMEENTRY* GetFrame(WORD nSequence, WORD nFrame, BOOL bDoubleSize);
    int Release();
    void ResRefChange();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
    /* 0054 */ BAMHEADER* m_pBamHeader; // #guess
    /* 0058 */ BAMHEADER* m_pBamHeaderCopy;
    /* 005C */ FRAMEENTRY* m_pFrames;
    /* 0060 */ SEQUENCEENTRY* m_pSequences;
    /* 0064 */ WORD* m_pFrameList;
    /* 0068 */ WORD m_nFrameListSize; // #guess
    /* 006A */ FRAMEENTRY m_doubleSizeFrameEntry; // #guess
    /* 0076 */ BOOL m_bParsing;
};

#endif /* CRESCELLHEADER_H_ */

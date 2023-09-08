#ifndef CRESWAVE_H_
#define CRESWAVE_H_

#include "CRes.h"

#include <mmsystem.h>

class CResWave : public CRes {
public:
    CResWave();
    ~CResWave();
    void* Demand();
    LPWAVEFORMATEX GetWaveFormatPtr();
    DWORD GetWaveSize();
    int Release();
    BOOL Parse(void* pData);
    BOOL ParseNormalWave(void* pData);
    BOOL ParseCompressedWave(void* pData);
    int CopyWaveData(BYTE* pWaveData);

    /* 0050 */ BOOL m_bCompressed;
    /* 0054 */ BOOL m_bParsed;
    /* 0058 */ DWORD m_nWaveNormalSize;
    /* 005C */ DWORD m_nWaveCompressedSize;
    /* 0060 */ BYTE* m_pWaveData;
    /* 0064 */ LPWAVEFORMATEX m_pWaveFormatEx;
};

#endif /* CRESWAVE_H_ */

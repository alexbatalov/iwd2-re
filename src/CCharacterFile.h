#ifndef CCHARACTERFILE_H_
#define CCHARACTERFILE_H_

#include "CResBIO.h"
#include "CResCHR.h"

// NOTE: Class names are guesses, modelled on `CCreatureFile`.

// Exported character (`.CHR`).
class CCharacterFile : public CResHelper<CResCHR, 1018> {
public:
    BYTE* GetData();
    DWORD GetDataSize();
    void ReleaseData();
};

// Character biography (`.RES`).
class CBiographyFile : public CResHelper<CResBIO, 1022> {
public:
    char* GetData();
};

#endif /* CCHARACTERFILE_H_ */

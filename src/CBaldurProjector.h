#ifndef CBALDURPROJECTOR_H_
#define CBALDURPROJECTOR_H_

#include "mfc.h"

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CResRef.h"
#include "CVidFont.h"

#define CBALDURPROJECTOR_VIRTUAL_KEYS 2

typedef void* HBINK;
typedef HBINK(BinkOpen)(const char* name, unsigned int flags);
typedef int(BinkDDSurfaceType)(void* lpDDS);
typedef int(BinkDoFrame)(HBINK bnk);
typedef void(BinkNextFrame)(HBINK bnk);
typedef void(BinkClose)(HBINK bnk);
typedef void(BinkGetSummary)(HBINK bnk, void* summary);
typedef int(BinkCopyToBuffer)(HBINK bnk, void* dest, int pitch, unsigned int height, unsigned int x, unsigned int y, unsigned int flags);
typedef void*(BinkOpenDirectSound)(unsigned int param);
typedef int(BinkSetSoundSystem)(void* open, unsigned int param);
typedef int(BinkSetSoundOnOff)(HBINK bnk, int onoff);
typedef int(BinkWait)(HBINK bnk);
typedef char*(BinkGetError)();
typedef void(BinkSetVolume)(HBINK bnk, int volume);

class CBaldurProjector : public CBaldurEngine {
public:
    CBaldurProjector();
    ~CBaldurProjector();

    /* 0024 */ void EngineGameInit();
    /* 0028 */ void EngineGameUninit();
    /* 0070 */ void OnLButtonDown(CPoint pt);
    /* 00A0 */ SHORT GetNumVirtualKeys();
    /* 00A4 */ CKeyInfo* GetVirtualKeys();
    /* 00A8 */ BYTE* GetVirtualKeysFlags();
    /* 00AC */ void OnKeyDown(SHORT a2);

    void PlayMovie(const CResRef& cResRef);
    BOOL ResolveMovieFileName(const CResRef& cResRef, CString& sMovieFileName);
    void PlayMovieInternal(const CResRef& cResRef, BOOL bAsynchThread);
    void PlayMovieNext(const CResRef& cResRef);

    /* 0106 */ int field_106;
    /* 010A */ int field_10A;
    /* 0112 */ BOOL m_bDeactivateEngine; // #guess
    /* 0116 */ CKeyInfo m_pVirtualKeys[CBALDURPROJECTOR_VIRTUAL_KEYS];
    /* 0126 */ BYTE m_pVirtualKeysFlags[CBALDURPROJECTOR_VIRTUAL_KEYS];
    /* 0128 */ CTypedPtrList<CPtrList, CResRef*> m_lMovies; // #guess
    /* 0144 */ unsigned char field_144;
    /* 0145 */ unsigned char field_145;
    /* 0146 */ unsigned char field_146;
    /* 0147 */ unsigned char field_147;
    /* 014A */ CVidFont field_14A;
    /* 064A */ HBINK m_hBink; // #guess
    /* 064E */ CString field_64E;
    /* 0652 */ CResRef field_652;
    /* 065A */ int field_65A;
    /* 065E */ BinkOpen* m_pfnBinkOpen; // #guess
    /* 0662 */ BinkDDSurfaceType* m_pfnBinkDDSurfaceType; // #guess
    /* 0666 */ BinkDoFrame* m_pfnBinkDoFrame; // #guess
    /* 066A */ int field_66A;
    /* 066E */ BinkNextFrame* m_pfnBinkNextFrame; // #guess
    /* 0672 */ BinkClose* m_pfnBinkClose; // #guess
    /* 0676 */ BinkGetSummary* m_pfnBinkGetSummary; // #guess
    /* 067A */ BinkCopyToBuffer* m_pfnBinkCopyToBuffer; // #guess
    /* 067E */ BinkOpenDirectSound* m_pfnBinkOpenDirectSound; // #guess
    /* 0682 */ BinkSetSoundSystem* m_pfnBinkSetSoundSystem; // #guess
    /* 0686 */ BinkSetSoundOnOff* m_pfnBinkSetSoundOnOff; // #guess
    /* 068A */ BinkWait* m_pfnBinkWait; // #guess
    /* 068E */ BinkGetError* m_pfnBinkGetError; // #guess
    /* 0692 */ BinkSetVolume* m_pfnBinkSetVolume; // #guess
    /* 0696 */ HMODULE m_hBinkDLL; // #guess
    /* 069A */ int field_69A;
    /* 069E */ int field_69E;
};

#endif /* CBALDURPROJECTOR_H_ */

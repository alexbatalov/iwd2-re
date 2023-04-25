#ifndef CBALDURPROJECTOR_H_
#define CBALDURPROJECTOR_H_

#include "mfc.h"

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CResRef.h"
#include "CVidFont.h"

#define CBALDURPROJECTOR_VIRTUAL_KEYS 2

// NOTE: Incomplete, but the rest is not used in the code.
typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int frames;
    unsigned int frame_num;
} BINK;

typedef BINK* HBINK;
typedef HBINK(__stdcall BinkOpen)(const char* name, unsigned int flags);
typedef int(__stdcall BinkDDSurfaceType)(void* lpDDS);
typedef int(__stdcall BinkDoFrame)(HBINK bnk);
typedef void(__stdcall BinkNextFrame)(HBINK bnk);
typedef void(__stdcall BinkClose)(HBINK bnk);
typedef void(__stdcall BinkGetSummary)(HBINK bnk, void* summary);
typedef int(__stdcall BinkCopyToBuffer)(HBINK bnk, void* dest, int pitch, unsigned int height, unsigned int x, unsigned int y, unsigned int flags);
typedef void*(__stdcall BinkOpenDirectSound)(unsigned int param);
typedef int(__stdcall BinkSetSoundSystem)(void* open, unsigned int param);
typedef int(__stdcall BinkSetSoundOnOff)(HBINK bnk, int onoff);
typedef int(__stdcall BinkWait)(HBINK bnk);
typedef char*(__stdcall BinkGetError)();
typedef void(__stdcall BinkSetVolume)(HBINK bnk, unsigned int trackid, int volume);

class CBaldurProjector : public CBaldurEngine {
public:
    CBaldurProjector();
    ~CBaldurProjector();

    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00AC */ void OnKeyDown(SHORT a2) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;

    void PlayMovie(const CResRef& cResRef);
    BOOL ResolveMovieFileName(const CResRef& cResRef, CString& sMovieFileName);
    void PlayMovieInternal(const CResRef& cResRef, BOOL bAsynchThread);
    void PlayMovieNext(const CResRef& cResRef);
    void sub_43E300(HBINK bnk);

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
    /* 064E */ CString m_sCurrentMovieFileName;
    /* 0652 */ CResRef m_currentMovieResRef;
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
    /* 069A */ BOOL m_bThreadPriorityChanged;
    /* 069E */ int m_nPrevThreadPriority;
};

#endif /* CBALDURPROJECTOR_H_ */

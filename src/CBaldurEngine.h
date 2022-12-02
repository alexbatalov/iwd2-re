#ifndef CBALDURENGINE_H_
#define CBALDURENGINE_H_

#include "CUIManager.h"
#include "CWarp.h"

class CBaldurEngine : public CWarp {
public:
    CBaldurEngine();
    ~CBaldurEngine();
    void InvalidateCursorRect(const CRect& rect);
    void ResetControls();

    /* 00CC */ virtual CUIManager* GetUIManager();
    /* 00D0 */ virtual int GetSelectedCharacter();
    /* 00D4 */ virtual int GetPickedCharacter();
    /* 00D8 */ virtual void SetSelectedCharacter(int nNewSelectedCharacter);
    /* 00DC */ virtual void SetPickedCharacter(int nNewPickedCharacter);

    /* 0028 */ int m_nSelectedCharacter;
    /* 002C */ int m_nPickedCharacter;
    /* 0030 */ CUIManager m_cUIManager;
    /* 00FA */ int field_FA;
    /* 00FE */ int field_FE;
    /* 0102 */ int field_102;
};

#endif /* CBALDURENGINE_H_ */

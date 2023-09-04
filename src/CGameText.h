#ifndef CGAMETEXT_H_
#define CGAMETEXT_H_

#include "CGameObject.h"
#include "CVidCell.h"
#include "CVidFont.h"

class CGameArea;

class CGameText : public CGameObject {
public:
    static const CSize PADDING;

    CGameText(CGameArea* pArea, const CPoint& pt, BYTE nDuration, BYTE nBeginFade, const CString& sText);
    /* 0000 */ ~CGameText() override;
    /* 000C */ virtual void AIUpdate();
    /* 0048 */ virtual void RemoveFromArea();
    /* 0050 */ virtual BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter);

    void SetText(const CPoint& pt, BYTE nDuration, BYTE nBeginFade, const CString& sText);

    /* 006E */ CVidCell m_vidCell;
    /* 0148 */ CVidFont m_textFont;
    /* 0648 */ INT m_nDuration;
    /* 064C */ INT m_nBeginFade;
    /* 0650 */ BYTE m_nMaxLines;
    /* 0652 */ CString* m_szLine;
    /* 0656 */ int m_nLines;
};

#endif /* CGAMETEXT_H_ */

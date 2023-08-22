#include "CIcon.h"

#include "CResRef.h"
#include "CUIControlButton.h"
#include "CUtil.h"
#include "CVidCell.h"

// 0x8D7E68
const CPoint CIcon::LAST_DIGIT_OFFSET(25, 25);

// 0x8D7E60
const CPoint CIcon::FIRST_DIGIT_OFFSET(2, 2);

// 0x8D7E38
const CSize CIcon::ICON_SIZE_SM(32, 32);

// 0x8D7E58
const CSize CIcon::ICON_SIZE_LG(64, 64);

// 0x4E66E0
void CIcon::RenderIcon(int a1, const CPoint& pos, const CSize& size, const CRect& rBoundingBox, const CResRef& cResIcon, BOOL bDoubleSize, DWORD dwFlags, WORD wCount, BOOL bForceCount, WORD wSecondCount, BOOL bForceSecondCount, COLORREF rgbTint)
{
    CVidCell vcIcon;
    CVidCell vcNumber;
    CString sNumber;
    DWORD dwRenderFlags = 0;
    BOOL bResult;

    if (cResIcon != "") {
        // NOTE: Uninline.
        vcIcon.SetResRef(cResIcon, bDoubleSize, TRUE);

        if (vcIcon.pRes != NULL) {
            vcIcon.SequenceSet(1);
            vcIcon.FrameSet(0);

            LONG x = pos.x;
            LONG y = pos.y;
            LONG width = size.cx;
            LONG height = size.cy;
            int scale = (bDoubleSize ? 2 : 1);

            if (width > ICON_SIZE_SM.cx * scale) {
                x += (width - ICON_SIZE_SM.cx * scale) / 2;
            }

            if (height > ICON_SIZE_SM.cy * scale) {
                y += (height - ICON_SIZE_SM.cy * scale) / 2;
            }

            if ((dwFlags & 0x1) != 0) {
                dwRenderFlags = 0x20000;
                vcIcon.SetTintColor(CUIControlButton::TINT_DISABLED);
            } else if ((dwFlags & 0x2) != 0) {
                dwRenderFlags = 0xA0000;
                vcIcon.SetTintColor(CUIControlButton::TINT_INVALID);
            } else {
                if (rgbTint != 0) {
                    dwRenderFlags = 0x20000;
                    vcIcon.SetTintColor(rgbTint);
                }
            }

            CRect rClip(rBoundingBox);

            bResult = vcIcon.Render(0, x, y, rClip, NULL, 0, dwFlags, -1);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CIcon.cpp
            // __LINE__: 174
            UTIL_ASSERT(bResult);

            if (wCount > 0) {
                // NOTE: Uninline.
                vcNumber.SetResRef(CResRef("NUMBER"), bDoubleSize, TRUE);

                vcNumber.SequenceSet(0);

                x += LAST_DIGIT_OFFSET.x * scale;

                WORD wRemaining = wCount;
                do {
                    SHORT nFrame = wRemaining % 10;
                    wRemaining /= 10;

                    if (nFrame > 0 || wRemaining > 0) {
                        vcNumber.FrameSet(nFrame);

                        bResult = vcNumber.Render(0, x, y + LAST_DIGIT_OFFSET.y * scale, rClip, NULL, 0, 0, -1);

                        // __FILE__: C:\Projects\Icewind2\src\Baldur\CIcon.cpp
                        // __LINE__: 193
                        UTIL_ASSERT(bResult);
                    }

                    x -= 5 * scale;
                } while (wRemaining > 0);
            } else if (bForceCount) {
                // NOTE: Uninline.
                vcNumber.SetResRef(CResRef("NUMBER"), bDoubleSize, TRUE);

                vcNumber.SequenceSet(0);
                vcNumber.FrameSet(0);

                x += LAST_DIGIT_OFFSET.x * scale;
                y += LAST_DIGIT_OFFSET.y * scale;

                bResult = vcNumber.Render(0, x, y, rClip, NULL, 0, 0, -1);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CIcon.cpp
                // __LINE__: 205
                UTIL_ASSERT(bResult);
            }

            if (wSecondCount > 0 || bForceSecondCount) {
                // NOTE: Uninline.
                vcNumber.SetResRef(CResRef("NUMBER"), bDoubleSize, TRUE);

                vcNumber.SequenceSet(0);

                sNumber.Format("%d", wSecondCount);

                x += FIRST_DIGIT_OFFSET.x * scale;

                for (int pos = 0; pos < sNumber.GetLength(); pos++) {
                    vcNumber.FrameSet(sNumber[pos] - '0');

                    // NOTE: `y` is not scaled.
                    bResult = vcNumber.Render(0, x, y + FIRST_DIGIT_OFFSET.y, rClip, NULL, 0, 0, -1);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CIcon.cpp
                    // __LINE__: 217
                    UTIL_ASSERT(bResult);

                    x += 5 * scale;
                }
            }
        }
    }
}

#ifndef CCHITIN3D_H_
#define CCHITIN3D_H_

#include "CVideo3d.h"

class CChitin3d {
public:
    static PFNSWAPBUFFERSPROC SwapBuffers;
    static PFNWGLMAKECURRENTPROC wglMakeCurrent;
    static PFNWGLCREATECONTEXTPROC wglCreateContext;
    static PFNWGLGETCURRENTDCPROC wglGetCurrentDC;
    static PFNWGLDELETECONTEXTPROC wglDeleteContext;
    static PFNSETPIXELFORMATPROC SetPixelFormat;
    static PFNCHOOSEPIXELFORMATPROC ChoosePixelFormat;
};

#endif /* CCHITIN3D_H_ */

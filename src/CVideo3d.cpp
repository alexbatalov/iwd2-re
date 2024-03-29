#include "CVideo3d.h"

#include "CChitin.h"
#include "CChitin3d.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVideo.h"
#include "CWarp.h"

// 0x848398
const float CVideo3d::SUB_PIXEL_SHIFT = 0.2f;

// 0x907514
PFNGLACCUMPROC CVideo3d::glAccum;

// 0x907518
PFNGLALPHAFUNCPROC CVideo3d::glAlphaFunc;

// 0x90751C
PFNGLARETEXTURESRESIDENTPROC CVideo3d::glAreTexturesResident;

// 0x907520
PFNGLARRAYELEMENTPROC CVideo3d::glArrayElement;

// 0x907524
PFNGLBEGINPROC CVideo3d::glBegin;

// 0x907528
PFNGLBINDTEXTUREPROC CVideo3d::glBindTexture;

// 0x90752C
PFNGLBITMAPPROC CVideo3d::glBitmap;

// 0x907530
PFNGLBLENDFUNCPROC CVideo3d::glBlendFunc;

// 0x907534
PFNGLCALLLISTPROC CVideo3d::glCallList;

// 0x907538
PFNGLCALLLISTSPROC CVideo3d::glCallLists;

// 0x90753C
PFNGLCLEARPROC CVideo3d::glClear;

// 0x907540
PFNGLCLEARACCUMPROC CVideo3d::glClearAccum;

// 0x907544
PFNGLCLEARCOLORPROC CVideo3d::glClearColor;

// 0x907548
PFNGLCLEARDEPTHPROC CVideo3d::glClearDepth;

// 0x90754C
PFNGLCLEARINDEXPROC CVideo3d::glClearIndex;

// 0x907550
PFNGLCLEARSTENCILPROC CVideo3d::glClearStencil;

// 0x907554
PFNGLCLIPPLANEPROC CVideo3d::glClipPlane;

// 0x907558
PFNGLCOLOR3BPROC CVideo3d::glColor3b;

// 0x90755C
PFNGLCOLOR3BVPROC CVideo3d::glColor3bv;

// 0x907560
PFNGLCOLOR3DPROC CVideo3d::glColor3d;

// 0x907564
PFNGLCOLOR3DVPROC CVideo3d::glColor3dv;

// 0x907568
PFNGLCOLOR3FPROC CVideo3d::glColor3f;

// 0x90756C
PFNGLCOLOR3FVPROC CVideo3d::glColor3fv;

// 0x907570
PFNGLCOLOR3IPROC CVideo3d::glColor3i;

// 0x907574
PFNGLCOLOR3IVPROC CVideo3d::glColor3iv;

// 0x907578
PFNGLCOLOR3SPROC CVideo3d::glColor3s;

// 0x90757C
PFNGLCOLOR3SVPROC CVideo3d::glColor3sv;

// 0x907580
PFNGLCOLOR3UBPROC CVideo3d::glColor3ub;

// 0x907584
PFNGLCOLOR3UBVPROC CVideo3d::glColor3ubv;

// 0x907588
PFNGLCOLOR3UIPROC CVideo3d::glColor3ui;

// 0x90758C
PFNGLCOLOR3UIVPROC CVideo3d::glColor3uiv;

// 0x907590
PFNGLCOLOR3USPROC CVideo3d::glColor3us;

// 0x907594
PFNGLCOLOR3USVPROC CVideo3d::glColor3usv;

// 0x907598
PFNGLCOLOR4BPROC CVideo3d::glColor4b;

// 0x90759C
PFNGLCOLOR4BVPROC CVideo3d::glColor4bv;

// 0x9075A0
PFNGLCOLOR4DPROC CVideo3d::glColor4d;

// 0x9075A4
PFNGLCOLOR4DVPROC CVideo3d::glColor4dv;

// 0x9075A8
PFNGLCOLOR4FPROC CVideo3d::glColor4f;

// 0x9075AC
PFNGLCOLOR4FVPROC CVideo3d::glColor4fv;

// 0x9075B0
PFNGLCOLOR4IPROC CVideo3d::glColor4i;

// 0x9075B4
PFNGLCOLOR4IVPROC CVideo3d::glColor4iv;

// 0x9075B8
PFNGLCOLOR4SPROC CVideo3d::glColor4s;

// 0x9075BC
PFNGLCOLOR4SVPROC CVideo3d::glColor4sv;

// 0x9075C0
PFNGLCOLOR4UBPROC CVideo3d::glColor4ub;

// 0x9075C4
PFNGLCOLOR4UBVPROC CVideo3d::glColor4ubv;

// 0x9075C8
PFNGLCOLOR4UIPROC CVideo3d::glColor4ui;

// 0x9075CC
PFNGLCOLOR4UIVPROC CVideo3d::glColor4uiv;

// 0x9075D0
PFNGLCOLOR4USPROC CVideo3d::glColor4us;

// 0x9075D4
PFNGLCOLOR4USVPROC CVideo3d::glColor4usv;

// 0x9075D8
PFNGLCOLORMASKPROC CVideo3d::glColorMask;

// 0x9075DC
PFNGLCOLORMATERIALPROC CVideo3d::glColorMaterial;

// 0x9075E0
PFNGLCOLORPOINTERPROC CVideo3d::glColorPointer;

// 0x9075E4
PFNGLCOPYPIXELSPROC CVideo3d::glCopyPixels;

// 0x9075E8
PFNGLCOPYTEXIMAGE1DPROC CVideo3d::glCopyTexImage1D;

// 0x9075EC
PFNGLCOPYTEXIMAGE2DPROC CVideo3d::glCopyTexImage2D;

// 0x9075F0
PFNGLCOPYTEXSUBIMAGE1DPROC CVideo3d::glCopyTexSubImage1D;

// 0x9075F4
PFNGLCOPYTEXSUBIMAGE2DPROC CVideo3d::glCopyTexSubImage2D;

// 0x9075F8
PFNGLCULLFACEPROC CVideo3d::glCullFace;

// 0x9075FC
PFNGLDELETELISTSPROC CVideo3d::glDeleteLists;

// 0x907600
PFNGLDELETETEXTURESPROC CVideo3d::glDeleteTextures;

// 0x907604
PFNGLDEPTHFUNCPROC CVideo3d::glDepthFunc;

// 0x907608
PFNGLDEPTHMASKPROC CVideo3d::glDepthMask;

// 0x90760C
PFNGLDEPTHRANGEPROC CVideo3d::glDepthRange;

// 0x907610
PFNGLDISABLEPROC CVideo3d::glDisable;

// 0x907614
PFNGLDISABLECLIENTSTATEPROC CVideo3d::glDisableClientState;

// 0x907618
PFNGLDRAWARRAYSPROC CVideo3d::glDrawArrays;

// 0x90761C
PFNGLDRAWBUFFERPROC CVideo3d::glDrawBuffer;

// 0x907620
PFNGLDRAWELEMENTSPROC CVideo3d::glDrawElements;

// 0x907624
PFNGLDRAWPIXELSPROC CVideo3d::glDrawPixels;

// 0x907628
PFNGLEDGEFLAGPROC CVideo3d::glEdgeFlag;

// 0x90762C
PFNGLEDGEFLAGPOINTERPROC CVideo3d::glEdgeFlagPointer;

// 0x907630
PFNGLEDGEFLAGVPROC CVideo3d::glEdgeFlagv;

// 0x907634
PFNGLENABLEPROC CVideo3d::glEnable;

// 0x907638
PFNGLENABLECLIENTSTATEPROC CVideo3d::glEnableClientState;

// 0x90763C
PFNGLENDPROC CVideo3d::glEnd;

// 0x907640
PFNGLENDLISTPROC CVideo3d::glEndList;

// 0x907644
PFNGLEVALCOORD1DPROC CVideo3d::glEvalCoord1d;

// 0x907648
PFNGLEVALCOORD1DVPROC CVideo3d::glEvalCoord1dv;

// 0x90764C
PFNGLEVALCOORD1FPROC CVideo3d::glEvalCoord1f;

// 0x907650
PFNGLEVALCOORD1FVPROC CVideo3d::glEvalCoord1fv;

// 0x907654
PFNGLEVALCOORD2DPROC CVideo3d::glEvalCoord2d;

// 0x907658
PFNGLEVALCOORD2DVPROC CVideo3d::glEvalCoord2dv;

// 0x90765C
PFNGLEVALCOORD2FPROC CVideo3d::glEvalCoord2f;

// 0x907660
PFNGLEVALCOORD2FVPROC CVideo3d::glEvalCoord2fv;

// 0x907664
PFNGLEVALMESH1PROC CVideo3d::glEvalMesh1;

// 0x907668
PFNGLEVALMESH2PROC CVideo3d::glEvalMesh2;

// 0x90766C
PFNGLEVALPOINT1PROC CVideo3d::glEvalPoint1;

// 0x907670
PFNGLEVALPOINT2PROC CVideo3d::glEvalPoint2;

// 0x907674
PFNGLFEEDBACKBUFFERPROC CVideo3d::glFeedbackBuffer;

// 0x907678
PFNGLFINISHPROC CVideo3d::glFinish;

// 0x90767C
PFNGLFLUSHPROC CVideo3d::glFlush;

// 0x907680
PFNGLFOGFPROC CVideo3d::glFogf;

// 0x907684
PFNGLFOGFVPROC CVideo3d::glFogfv;

// 0x907688
PFNGLFOGIPROC CVideo3d::glFogi;

// 0x90768C
PFNGLFOGIVPROC CVideo3d::glFogiv;

// 0x907690
PFNGLFRONTFACEPROC CVideo3d::glFrontFace;

// 0x907694
PFNGLFRUSTUMPROC CVideo3d::glFrustum;

// 0x907698
PFNGLGENLISTSPROC CVideo3d::glGenLists;

// 0x90769C
PFNGLGENTEXTURESPROC CVideo3d::glGenTextures;

// 0x9076A0
PFNGLGETBOOLEANVPROC CVideo3d::glGetBooleanv;

// 0x9076A4
PFNGLGETCLIPPLANEPROC CVideo3d::glGetClipPlane;

// 0x9076A8
PFNGLGETDOUBLEVPROC CVideo3d::glGetDoublev;

// 0x9076AC
PFNGLGETERRORPROC CVideo3d::glGetError;

// 0x9076B0
PFNGLGETFLOATVPROC CVideo3d::glGetFloatv;

// 0x9076B4
PFNGLGETINTEGERVPROC CVideo3d::glGetIntegerv;

// 0x9076B8
PFNGLGETLIGHTFVPROC CVideo3d::glGetLightfv;

// 0x9076BC
PFNGLGETLIGHTIVPROC CVideo3d::glGetLightiv;

// 0x9076C0
PFNGLGETMAPDVPROC CVideo3d::glGetMapdv;

// 0x9076C4
PFNGLGETMAPFVPROC CVideo3d::glGetMapfv;

// 0x9076C8
PFNGLGETMAPIVPROC CVideo3d::glGetMapiv;

// 0x9076CC
PFNGLGETMATERIALFVPROC CVideo3d::glGetMaterialfv;

// 0x9076D0
PFNGLGETMATERIALIVPROC CVideo3d::glGetMaterialiv;

// 0x9076D4
PFNGLGETPIXELMAPFVPROC CVideo3d::glGetPixelMapfv;

// 0x9076D8
PFNGLGETPIXELMAPUIVPROC CVideo3d::glGetPixelMapuiv;

// 0x9076DC
PFNGLGETPIXELMAPUSVPROC CVideo3d::glGetPixelMapusv;

// 0x9076E0
PFNGLGETPOINTERVPROC CVideo3d::glGetPointerv;

// 0x9076E4
PFNGLGETPOLYGONSTIPPLEPROC CVideo3d::glGetPolygonStipple;

// 0x9076E8
PFNGLGETSTRINGPROC CVideo3d::glGetString;

// 0x9076EC
PFNGLGETTEXENVFVPROC CVideo3d::glGetTexEnvfv;

// 0x9076F0
PFNGLGETTEXENVIVPROC CVideo3d::glGetTexEnviv;

// 0x9076F4
PFNGLGETTEXGENDVPROC CVideo3d::glGetTexGendv;

// 0x9076F8
PFNGLGETTEXGENFVPROC CVideo3d::glGetTexGenfv;

// 0x9076FC
PFNGLGETTEXGENIVPROC CVideo3d::glGetTexGeniv;

// 0x907700
PFNGLGETTEXIMAGEPROC CVideo3d::glGetTexImage;

// 0x907704
PFNGLGETTEXLEVELPARAMETERFVPROC CVideo3d::glGetTexLevelParameterfv;

// 0x907708
PFNGLGETTEXLEVELPARAMETERIVPROC CVideo3d::glGetTexLevelParameteriv;

// 0x90770C
PFNGLGETTEXPARAMETERFVPROC CVideo3d::glGetTexParameterfv;

// 0x907710
PFNGLGETTEXPARAMETERIVPROC CVideo3d::glGetTexParameteriv;

// 0x907714
PFNGLHINTPROC CVideo3d::glHint;

// 0x907718
PFNGLINDEXMASKPROC CVideo3d::glIndexMask;

// 0x90771C
PFNGLINDEXPOINTERPROC CVideo3d::glIndexPointer;

// 0x907720
PFNGLINDEXDPROC CVideo3d::glIndexd;

// 0x907724
PFNGLINDEXDVPROC CVideo3d::glIndexdv;

// 0x907728
PFNGLINDEXFPROC CVideo3d::glIndexf;

// 0x90772C
PFNGLINDEXFVPROC CVideo3d::glIndexfv;

// 0x907730
PFNGLINDEXIPROC CVideo3d::glIndexi;

// 0x907734
PFNGLINDEXIVPROC CVideo3d::glIndexiv;

// 0x907738
PFNGLINDEXSPROC CVideo3d::glIndexs;

// 0x90773C
PFNGLINDEXSVPROC CVideo3d::glIndexsv;

// 0x907740
PFNGLINDEXUBPROC CVideo3d::glIndexub;

// 0x907744
PFNGLINDEXUBVPROC CVideo3d::glIndexubv;

// 0x907748
PFNGLINITNAMESPROC CVideo3d::glInitNames;

// 0x90774C
PFNGLINTERLEAVEDARRAYSPROC CVideo3d::glInterleavedArrays;

// 0x907750
PFNGLISENABLEDPROC CVideo3d::glIsEnabled;

// 0x907754
PFNGLISLISTPROC CVideo3d::glIsList;

// 0x907758
PFNGLISTEXTUREPROC CVideo3d::glIsTexture;

// 0x90775C
PFNGLLIGHTMODELFPROC CVideo3d::glLightModelf;

// 0x907760
PFNGLLIGHTMODELFVPROC CVideo3d::glLightModelfv;

// 0x907764
PFNGLLIGHTMODELIPROC CVideo3d::glLightModeli;

// 0x907768
PFNGLLIGHTMODELIVPROC CVideo3d::glLightModeliv;

// 0x90776C
PFNGLLIGHTFPROC CVideo3d::glLightf;

// 0x907770
PFNGLLIGHTFVPROC CVideo3d::glLightfv;

// 0x907774
PFNGLLIGHTIPROC CVideo3d::glLighti;

// 0x907778
PFNGLLIGHTIVPROC CVideo3d::glLightiv;

// 0x90777C
PFNGLLINESTIPPLEPROC CVideo3d::glLineStipple;

// 0x907780
PFNGLLINEWIDTHPROC CVideo3d::glLineWidth;

// 0x907784
PFNGLLISTBASEPROC CVideo3d::glListBase;

// 0x907788
PFNGLLOADIDENTITYPROC CVideo3d::glLoadIdentity;

// 0x90778C
PFNGLLOADMATRIXDPROC CVideo3d::glLoadMatrixd;

// 0x907790
PFNGLLOADMATRIXFPROC CVideo3d::glLoadMatrixf;

// 0x907794
PFNGLLOADNAMEPROC CVideo3d::glLoadName;

// 0x907798
PFNGLLOGICOPPROC CVideo3d::glLogicOp;

// 0x90779C
PFNGLMAP1DPROC CVideo3d::glMap1d;

// 0x9077A0
PFNGLMAP1FPROC CVideo3d::glMap1f;

// 0x9077A4
PFNGLMAP2DPROC CVideo3d::glMap2d;

// 0x9077A8
PFNGLMAP2FPROC CVideo3d::glMap2f;

// 0x9077AC
PFNGLMAPGRID1DPROC CVideo3d::glMapGrid1d;

// 0x9077B0
PFNGLMAPGRID1FPROC CVideo3d::glMapGrid1f;

// 0x9077B4
PFNGLMAPGRID2DPROC CVideo3d::glMapGrid2d;

// 0x9077B8
PFNGLMAPGRID2FPROC CVideo3d::glMapGrid2f;

// 0x9077BC
PFNGLMATERIALFPROC CVideo3d::glMaterialf;

// 0x9077C0
PFNGLMATERIALFVPROC CVideo3d::glMaterialfv;

// 0x9077C4
PFNGLMATERIALIPROC CVideo3d::glMateriali;

// 0x9077C8
PFNGLMATERIALIVPROC CVideo3d::glMaterialiv;

// 0x9077CC
PFNGLMATRIXMODEPROC CVideo3d::glMatrixMode;

// 0x9077D0
PFNGLMULTMATRIXDPROC CVideo3d::glMultMatrixd;

// 0x9077D4
PFNGLMULTMATRIXFPROC CVideo3d::glMultMatrixf;

// 0x9077D8
PFNGLNEWLISTPROC CVideo3d::glNewList;

// 0x9077DC
PFNGLNORMAL3BPROC CVideo3d::glNormal3b;

// 0x9077E0
PFNGLNORMAL3BVPROC CVideo3d::glNormal3bv;

// 0x9077E4
PFNGLNORMAL3DPROC CVideo3d::glNormal3d;

// 0x9077E8
PFNGLNORMAL3DVPROC CVideo3d::glNormal3dv;

// 0x9077EC
PFNGLNORMAL3FPROC CVideo3d::glNormal3f;

// 0x9077F0
PFNGLNORMAL3FVPROC CVideo3d::glNormal3fv;

// 0x9077F4
PFNGLNORMAL3IPROC CVideo3d::glNormal3i;

// 0x9077F8
PFNGLNORMAL3IVPROC CVideo3d::glNormal3iv;

// 0x9077FC
PFNGLNORMAL3SPROC CVideo3d::glNormal3s;

// 0x907800
PFNGLNORMAL3SVPROC CVideo3d::glNormal3sv;

// 0x907804
PFNGLNORMALPOINTERPROC CVideo3d::glNormalPointer;

// 0x907808
PFNGLORTHOPROC CVideo3d::glOrtho;

// 0x90780C
PFNGLPASSTHROUGHPROC CVideo3d::glPassThrough;

// 0x907810
PFNGLPIXELMAPFVPROC CVideo3d::glPixelMapfv;

// 0x907814
PFNGLPIXELMAPUIVPROC CVideo3d::glPixelMapuiv;

// 0x907818
PFNGLPIXELMAPUSVPROC CVideo3d::glPixelMapusv;

// 0x90781C
PFNGLPIXELSTOREFPROC CVideo3d::glPixelStoref;

// 0x907820
PFNGLPIXELSTOREIPROC CVideo3d::glPixelStorei;

// 0x907824
PFNGLPIXELTRANSFERFPROC CVideo3d::glPixelTransferf;

// 0x907828
PFNGLPIXELTRANSFERIPROC CVideo3d::glPixelTransferi;

// 0x90782C
PFNGLPIXELZOOMPROC CVideo3d::glPixelZoom;

// 0x907830
PFNGLPOINTSIZEPROC CVideo3d::glPointSize;

// 0x907834
PFNGLPOLYGONMODEPROC CVideo3d::glPolygonMode;

// 0x907838
PFNGLPOLYGONOFFSETPROC CVideo3d::glPolygonOffset;

// 0x90783C
PFNGLPOLYGONSTIPPLEPROC CVideo3d::glPolygonStipple;

// 0x907840
PFNGLPOPATTRIBPROC CVideo3d::glPopAttrib;

// 0x907844
PFNGLPOPCLIENTATTRIBPROC CVideo3d::glPopClientAttrib;

// 0x907848
PFNGLPOPMATRIXPROC CVideo3d::glPopMatrix;

// 0x90784C
PFNGLPOPNAMEPROC CVideo3d::glPopName;

// 0x907850
PFNGLPRIORITIZETEXTURESPROC CVideo3d::glPrioritizeTextures;

// 0x907854
PFNGLPUSHATTRIBPROC CVideo3d::glPushAttrib;

// 0x907858
PFNGLPUSHCLIENTATTRIBPROC CVideo3d::glPushClientAttrib;

// 0x90785C
PFNGLPUSHMATRIXPROC CVideo3d::glPushMatrix;

// 0x907860
PFNGLPUSHNAMEPROC CVideo3d::glPushName;

// 0x907864
PFNGLRASTERPOS2DPROC CVideo3d::glRasterPos2d;

// 0x907868
PFNGLRASTERPOS2DVPROC CVideo3d::glRasterPos2dv;

// 0x90786C
PFNGLRASTERPOS2FPROC CVideo3d::glRasterPos2f;

// 0x907870
PFNGLRASTERPOS2FVPROC CVideo3d::glRasterPos2fv;

// 0x907874
PFNGLRASTERPOS2IPROC CVideo3d::glRasterPos2i;

// 0x907878
PFNGLRASTERPOS2IVPROC CVideo3d::glRasterPos2iv;

// 0x90787C
PFNGLRASTERPOS2SPROC CVideo3d::glRasterPos2s;

// 0x907880
PFNGLRASTERPOS2SVPROC CVideo3d::glRasterPos2sv;

// 0x907884
PFNGLRASTERPOS3DPROC CVideo3d::glRasterPos3d;

// 0x907888
PFNGLRASTERPOS3DVPROC CVideo3d::glRasterPos3dv;

// 0x90788C
PFNGLRASTERPOS3FPROC CVideo3d::glRasterPos3f;

// 0x907890
PFNGLRASTERPOS3FVPROC CVideo3d::glRasterPos3fv;

// 0x907894
PFNGLRASTERPOS3IPROC CVideo3d::glRasterPos3i;

// 0x907898
PFNGLRASTERPOS3IVPROC CVideo3d::glRasterPos3iv;

// 0x90789C
PFNGLRASTERPOS3SPROC CVideo3d::glRasterPos3s;

// 0x9078A0
PFNGLRASTERPOS3SVPROC CVideo3d::glRasterPos3sv;

// 0x9078A4
PFNGLRASTERPOS4DPROC CVideo3d::glRasterPos4d;

// 0x9078A8
PFNGLRASTERPOS4DVPROC CVideo3d::glRasterPos4dv;

// 0x9078AC
PFNGLRASTERPOS4FPROC CVideo3d::glRasterPos4f;

// 0x9078B0
PFNGLRASTERPOS4FVPROC CVideo3d::glRasterPos4fv;

// 0x9078B4
PFNGLRASTERPOS4IPROC CVideo3d::glRasterPos4i;

// 0x9078B8
PFNGLRASTERPOS4IVPROC CVideo3d::glRasterPos4iv;

// 0x9078BC
PFNGLRASTERPOS4SPROC CVideo3d::glRasterPos4s;

// 0x9078C0
PFNGLRASTERPOS4SVPROC CVideo3d::glRasterPos4sv;

// 0x9078C4
PFNGLREADBUFFERPROC CVideo3d::glReadBuffer;

// 0x9078C8
PFNGLREADPIXELSPROC CVideo3d::glReadPixels;

// 0x9078CC
PFNGLRECTDPROC CVideo3d::glRectd;

// 0x9078D0
PFNGLRECTDVPROC CVideo3d::glRectdv;

// 0x9078D4
PFNGLRECTFPROC CVideo3d::glRectf;

// 0x9078D8
PFNGLRECTFVPROC CVideo3d::glRectfv;

// 0x9078DC
PFNGLRECTIPROC CVideo3d::glRecti;

// 0x9078E0
PFNGLRECTIVPROC CVideo3d::glRectiv;

// 0x9078E4
PFNGLRECTSPROC CVideo3d::glRects;

// 0x9078E8
PFNGLRECTSVPROC CVideo3d::glRectsv;

// 0x9078EC
PFNGLRENDERMODEPROC CVideo3d::glRenderMode;

// 0x9078F0
PFNGLROTATEDPROC CVideo3d::glRotated;

// 0x9078F4
PFNGLROTATEFPROC CVideo3d::glRotatef;

// 0x9078F8
PFNGLSCALEDPROC CVideo3d::glScaled;

// 0x9078FC
PFNGLSCALEFPROC CVideo3d::glScalef;

// 0x907900
PFNGLSCISSORPROC CVideo3d::glScissor;

// 0x907904
PFNGLSELECTBUFFERPROC CVideo3d::glSelectBuffer;

// 0x907908
PFNGLSHADEMODELPROC CVideo3d::glShadeModel;

// 0x90790C
PFNGLSTENCILFUNCPROC CVideo3d::glStencilFunc;

// 0x907910
PFNGLSTENCILMASKPROC CVideo3d::glStencilMask;

// 0x907914
PFNGLSTENCILOPPROC CVideo3d::glStencilOp;

// 0x907918
PFNGLTEXCOORD1DPROC CVideo3d::glTexCoord1d;

// 0x90791C
PFNGLTEXCOORD1DVPROC CVideo3d::glTexCoord1dv;

// 0x907920
PFNGLTEXCOORD1FPROC CVideo3d::glTexCoord1f;

// 0x907924
PFNGLTEXCOORD1FVPROC CVideo3d::glTexCoord1fv;

// 0x907928
PFNGLTEXCOORD1IPROC CVideo3d::glTexCoord1i;

// 0x90792C
PFNGLTEXCOORD1IVPROC CVideo3d::glTexCoord1iv;

// 0x907930
PFNGLTEXCOORD1SPROC CVideo3d::glTexCoord1s;

// 0x907934
PFNGLTEXCOORD1SVPROC CVideo3d::glTexCoord1sv;

// 0x907938
PFNGLTEXCOORD2DPROC CVideo3d::glTexCoord2d;

// 0x90793C
PFNGLTEXCOORD2DVPROC CVideo3d::glTexCoord2dv;

// 0x907940
PFNGLTEXCOORD2FPROC CVideo3d::glTexCoord2f;

// 0x907944
PFNGLTEXCOORD2FVPROC CVideo3d::glTexCoord2fv;

// 0x907948
PFNGLTEXCOORD2IPROC CVideo3d::glTexCoord2i;

// 0x90794C
PFNGLTEXCOORD2IVPROC CVideo3d::glTexCoord2iv;

// 0x907950
PFNGLTEXCOORD2SPROC CVideo3d::glTexCoord2s;

// 0x907954
PFNGLTEXCOORD2SVPROC CVideo3d::glTexCoord2sv;

// 0x907958
PFNGLTEXCOORD3DPROC CVideo3d::glTexCoord3d;

// 0x90795C
PFNGLTEXCOORD3DVPROC CVideo3d::glTexCoord3dv;

// 0x907960
PFNGLTEXCOORD3FPROC CVideo3d::glTexCoord3f;

// 0x907964
PFNGLTEXCOORD3FVPROC CVideo3d::glTexCoord3fv;

// 0x907968
PFNGLTEXCOORD3IPROC CVideo3d::glTexCoord3i;

// 0x90796C
PFNGLTEXCOORD3IVPROC CVideo3d::glTexCoord3iv;

// 0x907970
PFNGLTEXCOORD3SPROC CVideo3d::glTexCoord3s;

// 0x907974
PFNGLTEXCOORD3SVPROC CVideo3d::glTexCoord3sv;

// 0x907978
PFNGLTEXCOORD4DPROC CVideo3d::glTexCoord4d;

// 0x90797C
PFNGLTEXCOORD4DVPROC CVideo3d::glTexCoord4dv;

// 0x907980
PFNGLTEXCOORD4FPROC CVideo3d::glTexCoord4f;

// 0x907984
PFNGLTEXCOORD4FVPROC CVideo3d::glTexCoord4fv;

// 0x907988
PFNGLTEXCOORD4IPROC CVideo3d::glTexCoord4i;

// 0x90798C
PFNGLTEXCOORD4IVPROC CVideo3d::glTexCoord4iv;

// 0x907990
PFNGLTEXCOORD4SPROC CVideo3d::glTexCoord4s;

// 0x907994
PFNGLTEXCOORD4SVPROC CVideo3d::glTexCoord4sv;

// 0x907998
PFNGLTEXCOORDPOINTERPROC CVideo3d::glTexCoordPointer;

// 0x90799C
PFNGLTEXENVFPROC CVideo3d::glTexEnvf;

// 0x9079A0
PFNGLTEXENVFVPROC CVideo3d::glTexEnvfv;

// 0x9079A4
PFNGLTEXENVIPROC CVideo3d::glTexEnvi;

// 0x9079A8
PFNGLTEXENVIVPROC CVideo3d::glTexEnviv;

// 0x9079AC
PFNGLTEXGENDPROC CVideo3d::glTexGend;

// 0x9079B0
PFNGLTEXGENDVPROC CVideo3d::glTexGendv;

// 0x9079B4
PFNGLTEXGENFPROC CVideo3d::glTexGenf;

// 0x9079B8
PFNGLTEXGENFVPROC CVideo3d::glTexGenfv;

// 0x9079BC
PFNGLTEXGENIPROC CVideo3d::glTexGeni;

// 0x9079C0
PFNGLTEXGENIVPROC CVideo3d::glTexGeniv;

// 0x9079C4
PFNGLTEXIMAGE1DPROC CVideo3d::glTexImage1D;

// 0x9079C8
PFNGLTEXIMAGE2DPROC CVideo3d::glTexImage2D;

// 0x9079CC
PFNGLTEXPARAMETERFPROC CVideo3d::glTexParameterf;

// 0x9079D0
PFNGLTEXPARAMETERFVPROC CVideo3d::glTexParameterfv;

// 0x9079D4
PFNGLTEXPARAMETERIPROC CVideo3d::glTexParameteri;

// 0x9079D8
PFNGLTEXPARAMETERIVPROC CVideo3d::glTexParameteriv;

// 0x9079DC
PFNGLTEXSUBIMAGE1DPROC CVideo3d::glTexSubImage1D;

// 0x9079E0
PFNGLTEXSUBIMAGE2DPROC CVideo3d::glTexSubImage2D;

// 0x9079E4
PFNGLTRANSLATEDPROC CVideo3d::glTranslated;

// 0x9079E8
PFNGLTRANSLATEFPROC CVideo3d::glTranslatef;

// 0x9079EC
PFNGLVERTEX2DPROC CVideo3d::glVertex2d;

// 0x9079F0
PFNGLVERTEX2DVPROC CVideo3d::glVertex2dv;

// 0x9079F4
PFNGLVERTEX2FPROC CVideo3d::glVertex2f;

// 0x9079F8
PFNGLVERTEX2FVPROC CVideo3d::glVertex2fv;

// 0x9079FC
PFNGLVERTEX2IPROC CVideo3d::glVertex2i;

// 0x907A00
PFNGLVERTEX2IVPROC CVideo3d::glVertex2iv;

// 0x907A04
PFNGLVERTEX2SPROC CVideo3d::glVertex2s;

// 0x907A08
PFNGLVERTEX2SVPROC CVideo3d::glVertex2sv;

// 0x907A0C
PFNGLVERTEX3DPROC CVideo3d::glVertex3d;

// 0x907A10
PFNGLVERTEX3DVPROC CVideo3d::glVertex3dv;

// 0x907A14
PFNGLVERTEX3FPROC CVideo3d::glVertex3f;

// 0x907A18
PFNGLVERTEX3FVPROC CVideo3d::glVertex3fv;

// 0x907A1C
PFNGLVERTEX3IPROC CVideo3d::glVertex3i;

// 0x907A20
PFNGLVERTEX3IVPROC CVideo3d::glVertex3iv;

// 0x907A24
PFNGLVERTEX3SPROC CVideo3d::glVertex3s;

// 0x907A28
PFNGLVERTEX3SVPROC CVideo3d::glVertex3sv;

// 0x907A2C
PFNGLVERTEX4DPROC CVideo3d::glVertex4d;

// 0x907A30
PFNGLVERTEX4DVPROC CVideo3d::glVertex4dv;

// 0x907A34
PFNGLVERTEX4FPROC CVideo3d::glVertex4f;

// 0x907A38
PFNGLVERTEX4FVPROC CVideo3d::glVertex4fv;

// 0x907A3C
PFNGLVERTEX4IPROC CVideo3d::glVertex4i;

// 0x907A40
PFNGLVERTEX4IVPROC CVideo3d::glVertex4iv;

// 0x907A44
PFNGLVERTEX4SPROC CVideo3d::glVertex4s;

// 0x907A48
PFNGLVERTEX4SVPROC CVideo3d::glVertex4sv;

// 0x907A4C
PFNGLVERTEXPOINTERPROC CVideo3d::glVertexPointer;

// 0x907A50
PFNGLVIEWPORTPROC CVideo3d::glViewport;

// 0x907A54
PFNGLUBEGINCURVEPROC CVideo3d::gluBeginCurve;

// 0x907A58
PFNGLUBEGINPOLYGONPROC CVideo3d::gluBeginPolygon;

// 0x907A5C
PFNGLUBEGINSURFACEPROC CVideo3d::gluBeginSurface;

// 0x907A60
PFNGLUBEGINTRIMPROC CVideo3d::gluBeginTrim;

// 0x907A64
PFNGLUBUILD1DMIPMAPSPROC CVideo3d::gluBuild1DMipmaps;

// 0x907A68
PFNGLUBUILD2DMIPMAPSPROC CVideo3d::gluBuild2DMipmaps;

// 0x907A6C
PFNGLUCYLINDERPROC CVideo3d::gluCylinder;

// 0x907A70
PFNGLUDELETENURBSRENDERERPROC CVideo3d::gluDeleteNurbsRenderer;

// 0x907A74
PFNGLUDELETEQUADRICPROC CVideo3d::gluDeleteQuadric;

// 0x907A78
PFNGLUDELETETESSPROC CVideo3d::gluDeleteTess;

// 0x907A7C
PFNGLUDISKPROC CVideo3d::gluDisk;

// 0x907A80
PFNGLUENDCURVEPROC CVideo3d::gluEndCurve;

// 0x907A84
PFNGLUENDPOLYGONPROC CVideo3d::gluEndPolygon;

// 0x907A88
PFNGLUENDSURFACEPROC CVideo3d::gluEndSurface;

// 0x907A8C
PFNGLUENDTRIMPROC CVideo3d::gluEndTrim;

// 0x907A90
PFNGLUERRORSTRINGPROC CVideo3d::gluErrorString;

// 0x907A94
PFNGLUGETNURBSPROPERTYPROC CVideo3d::gluGetNurbsProperty;

// 0x907A98
PFNGLUGETSTRINGPROC CVideo3d::gluGetString;

// 0x907A9C
PFNGLUGETTESSPROPERTYPROC CVideo3d::gluGetTessProperty;

// 0x907AA0
PFNGLULOADSAMPLINGMATRICESPROC CVideo3d::gluLoadSamplingMatrices;

// 0x907AA4
PFNGLULOOKATPROC CVideo3d::gluLookAt;

// 0x907AA8
PFNGLUNEWNURBSRENDERERPROC CVideo3d::gluNewNurbsRenderer;

// 0x907AAC
PFNGLUNEWQUADRICPROC CVideo3d::gluNewQuadric;

// 0x907AB0
PFNGLUNEWTESSPROC CVideo3d::gluNewTess;

// 0x907AB4
PFNGLUNEXTCONTOURPROC CVideo3d::gluNextContour;

// 0x907AB8
PFNGLUNURBSCALLBACKPROC CVideo3d::gluNurbsCallback;

// 0x907ABC
PFNGLUNURBSCURVEPROC CVideo3d::gluNurbsCurve;

// 0x907AC0
PFNGLUNURBSPROPERTYPROC CVideo3d::gluNurbsProperty;

// 0x907AC4
PFNGLUNURBSSURFACEPROC CVideo3d::gluNurbsSurface;

// 0x907AC8
PFNGLUORTHO2DPROC CVideo3d::gluOrtho2D;

// 0x907ACC
PFNGLUPARTIALDISKPROC CVideo3d::gluPartialDisk;

// 0x907AD0
PFNGLUPERSPECTIVEPROC CVideo3d::gluPerspective;

// 0x907AD4
PFNGLUPICKMATRIXPROC CVideo3d::gluPickMatrix;

// 0x907AD8
PFNGLUPROJECTPROC CVideo3d::gluProject;

// 0x907ADC
PFNGLUPWLCURVEPROC CVideo3d::gluPwlCurve;

// 0x907AE0
PFNGLUQUADRICCALLBACKPROC CVideo3d::gluQuadricCallback;

// 0x907AE4
PFNGLUQUADRICDRAWSTYLEPROC CVideo3d::gluQuadricDrawStyle;

// 0x907AE8
PFNGLUQUADRICNORMALSPROC CVideo3d::gluQuadricNormals;

// 0x907AEC
PFNGLUQUADRICORIENTATIONPROC CVideo3d::gluQuadricOrientation;

// 0x907AF0
PFNGLUQUADRICTEXTUREPROC CVideo3d::gluQuadricTexture;

// 0x907AF4
PFNGLUSCALEIMAGEPROC CVideo3d::gluScaleImage;

// 0x907AF8
PFNGLUSPHEREPROC CVideo3d::gluSphere;

// 0x907AFC
PFNGLUTESSBEGINCONTOURPROC CVideo3d::gluTessBeginContour;

// 0x907B00
PFNGLUTESSBEGINPOLYGONPROC CVideo3d::gluTessBeginPolygon;

// 0x907B04
PFNGLUTESSCALLBACKPROC CVideo3d::gluTessCallback;

// 0x907B08
PFNGLUTESSENDCONTOURPROC CVideo3d::gluTessEndContour;

// 0x907B0C
PFNGLUTESSENDPOLYGONPROC CVideo3d::gluTessEndPolygon;

// 0x907B10
PFNGLUTESSNORMALPROC CVideo3d::gluTessNormal;

// 0x907B14
PFNGLUTESSPROPERTYPROC CVideo3d::gluTessProperty;

// 0x907B18
PFNGLUTESSVERTEXPROC CVideo3d::gluTessVertex;

// 0x907B1C
PFNGLUUNPROJECTPROC CVideo3d::gluUnProject;

// 0x907B20
DWORD CVideo3d::texImageData[CVIDINF_FX_WIDTH * CVIDINF_FX_HEIGHT];

// -----------------------------------------------------------------------------

// 0x7BBA50
void CVideo::CleanUp3d()
{
    g_pChitin->UnloadFonts();

    if (m_pCurrentVidMode != NULL) {
        m_pCurrentVidMode->DeactivateVideoMode(NULL);
        m_pCurrentVidMode = NULL;
    }

    if (m_hGLRC != NULL) {
        CChitin3d::wglMakeCurrent(m_hDC, NULL);
        CChitin3d::wglDeleteContext(m_hGLRC);
        m_hGLRC = NULL;
    }

    if (m_hDC != NULL) {
        ReleaseDC(g_pChitin->GetWnd()->GetSafeHwnd(), m_hDC);
        m_hDC = NULL;
    }

    if (m_bFullscreen) {
        ChangeDisplaySettingsA(NULL, 0);
    }
}

// 0x7BBAF0
BOOL CVideo::Initialize3d(HWND hWnd, BOOLEAN bFullscreen, int a4)
{
    m_bFullscreen = bFullscreen;
    if (bFullscreen) {
        if (!CVidInf::SetDisplayMode()) {
            return FALSE;
        }

        if (a4) {
            OpenIcon(hWnd);
        }

        RECT r;
        SetRect(&r, 0, 0, SCREENWIDTH, SCREENHEIGHT);
        AdjustWindowRectEx(&r,
            GetWindowLongA(hWnd, GWL_STYLE),
            GetMenu(hWnd) != NULL,
            GetWindowLongA(hWnd, GWL_EXSTYLE));
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, r.right - r.left, r.bottom - r.top, 0);
    } else {
        CVidMode::SetWindowedMode(hWnd);
    }

    m_hDC = GetDC(hWnd);
    if (!SetPixelFormat(m_hDC)) {
        return FALSE;
    }

    m_hGLRC = CChitin3d::wglCreateContext(m_hDC);
    CChitin3d::wglMakeCurrent(m_hDC, m_hGLRC);

    InitializeRenderEnv();

    if (m_pCurrentVidMode != NULL) {
        m_pCurrentVidMode->ActivateVideoMode3d(NULL, hWnd, m_bFullscreen);
    }

    return TRUE;
}

// 0x7BBC20
void CVideo::InitializeRenderEnv()
{
    CVideo3d::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glClearDepth(1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_LIGHTING);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_CULL_FACE);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glFrontFace(GL_CCW);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glCullFace(GL_BACK);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glShadeModel(GL_SMOOTH);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glViewport(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glMatrixMode(GL_PROJECTION);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPushMatrix();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glLoadIdentity();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glOrtho(0.0,
        static_cast<GLdouble>(CVideo::SCREENWIDTH),
        static_cast<GLdouble>(CVideo::SCREENHEIGHT),
        0.0,
        1.0,
        -1.0);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glClear(GL_LIGHT0);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    field_136 = GL_RGBA;
}

// 0x7BBF50
BOOL CVideo::SetPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = g_pChitin->GetSavedBitsPerPixel();
    pfd.cRedBits = 0;
    pfd.cRedShift = 0;
    pfd.cGreenBits = 0;
    pfd.cGreenShift = 0;
    pfd.cBlueBits = 0;
    pfd.cBlueShift = 0;
    pfd.cAlphaBits = 0;
    pfd.cAlphaShift = 0;
    pfd.cAccumBits = 0;
    pfd.cAccumRedBits = 0;
    pfd.cAccumGreenBits = 0;
    pfd.cAccumBlueBits = 0;
    pfd.cAccumAlphaBits = 0;
    pfd.cDepthBits = 0;
    pfd.cStencilBits = 0;
    pfd.cAuxBuffers = 0;
    pfd.iLayerType = 0;
    pfd.bReserved = 0;
    pfd.dwLayerMask = 0;
    pfd.dwVisibleMask = 0;
    pfd.dwDamageMask = 0;
    pfd.cColorBits = !g_pChitin->field_2F4 ? 32 : 16;

    int iPixelFormat = CChitin3d::ChoosePixelFormat(hDC, &pfd);
    if (iPixelFormat == 0) {
        CString sMessage;
        sMessage.LoadStringA(g_pChitin->GetIDSChoosePixelFormat());
        MessageBoxA(NULL, sMessage, CChitin::m_sGameName, 0);
        return FALSE;
    }

    if (!CChitin3d::SetPixelFormat(hDC, iPixelFormat, &pfd)) {
        CString sMessage;
        sMessage.LoadStringA(g_pChitin->GetIDSSetPixelFormat());
        MessageBoxA(NULL, sMessage, CChitin::m_sGameName, 0);
        return FALSE;
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x78E6E0
BOOL CVidMode::CreateSurfaces3d()
{
    return FALSE;
}

// 0x78E6E0
BOOL CVidMode::DestroySurfaces3d(CVidMode* pNextVidMode)
{
    return FALSE;
}

// 0x7BC100
BOOL CVidMode::ActivateVideoMode3d(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen)
{
    return TRUE;
}

// 0x7BC110
void CVidMode::Set3dClipRect(const CRect& rClip)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CVideo3d::glScissor(rClip.left,
            CVideo::SCREENHEIGHT - rClip.bottom,
            rClip.Width(),
            rClip.Height());
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }
}

// 0x7BC180
void CVidMode::EnableScissoring()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CVideo3d::glEnable(GL_SCISSOR_TEST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }
}

// 0x7BC1C0
void CVidMode::DisableScissoring()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CVideo3d::glDisable(GL_SCISSOR_TEST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }
}

// 0x7BC200
GLuint CVidMode::GetTextureId()
{
    GLuint textures[1];

    DeleteDisposableTextures();
    CVideo3d::glGenTextures(1, textures);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    return textures[1];
}

// 0x7BC250
BOOL CVidMode::DrawLine3d(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const CRect& rSurface, COLORREF rgbColor)
{
    if (!ClipLine(nXFrom, nYFrom, nXTo, nYTo, rSurface)) {
        return FALSE;
    }

    float v1 = 0.0f;
    float v2 = 0.0f;

    if (nXTo == nXFrom) {
        if (nYTo != nYFrom) {
            v2 = 1.0f;
        }
    } else {
        if (nYTo == nYFrom) {
            v1 = 1.0f;
        }
    }

    CVideo3d::glColor4f(static_cast<float>(GetRValue(rgbColor)) / 255.0f,
        static_cast<float>(GetGValue(rgbColor)) / 255.0f,
        static_cast<float>(GetBValue(rgbColor)) / 255.0f,
        1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glLineWidth(1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_LINES);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    if (nXFrom > nXTo || nYFrom > nYTo) {
        CVideo3d::glVertex3f(static_cast<float>(nXTo) + CVideo3d::SUB_PIXEL_SHIFT,
            static_cast<float>(nYTo) + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
        CVideo3d::glVertex3f(static_cast<float>(nXFrom) + v1 + CVideo3d::SUB_PIXEL_SHIFT,
            static_cast<float>(nYFrom) + v2 + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
    } else {
        CVideo3d::glVertex3f(static_cast<float>(nXFrom) + CVideo3d::SUB_PIXEL_SHIFT,
            static_cast<float>(nYFrom) + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
        CVideo3d::glVertex3f(static_cast<float>(nXTo) + v1 + CVideo3d::SUB_PIXEL_SHIFT,
            static_cast<float>(nYTo) + v2 + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
    }

    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    return TRUE;
}

// 0x7BC500
BOOL CVidMode::DrawRect3d(const CRect& r, const CRect& rClip, COLORREF rgbColor)
{
    DrawLine3d(r.left, r.top, r.right, r.top, rClip, rgbColor);
    DrawLine3d(r.right, r.top, r.right, r.bottom, rClip, rgbColor);
    DrawLine3d(r.right, r.bottom, r.left, r.bottom, rClip, rgbColor);
    DrawLine3d(r.left, r.bottom, r.left, r.top, rClip, rgbColor);
    return TRUE;
}

// 0x7BC580
BOOL CVidMode::DrawEllipse3d(const CPoint& ptCenter, const CSize& axis, const CRect& rClip, COLORREF rgbColor)
{
    BYTE* pPixelList = new BYTE[max(axis.cx, axis.cy)];
    LONG nArcLength = GetEllipseArcPixelList(axis.cx, axis.cy, pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 675
    UTIL_ASSERT(nArcLength <= max(axis.cx, axis.cy));

    DrawEllipseHOctant3d(ptCenter.x,
        ptCenter.y - axis.cy,
        nArcLength,
        -1,
        1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawEllipseHOctant3d(ptCenter.x + 1,
        ptCenter.y + pPixelList[0] - axis.cy,
        nArcLength - 1,
        1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawEllipseHOctant3d(ptCenter.x,
        ptCenter.y + axis.cy,
        nArcLength,
        -1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawEllipseHOctant3d(ptCenter.x + 1,
        ptCenter.y - pPixelList[0] + axis.cy,
        nArcLength - 1,
        1,
        -1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    nArcLength = GetEllipseArcPixelList(axis.cy, axis.cx, pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 698
    UTIL_ASSERT(nArcLength < max(axis.cx, axis.cy));

    DrawEllipseVOctant3d(ptCenter.x - axis.cx,
        ptCenter.y,
        nArcLength,
        1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawEllipseVOctant3d(ptCenter.x + pPixelList[0] - axis.cx,
        ptCenter.y + 1,
        nArcLength - 1,
        1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawEllipseVOctant3d(ptCenter.x + axis.cx,
        ptCenter.y,
        nArcLength,
        -1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawEllipseVOctant3d(ptCenter.x - pPixelList[0] + axis.cx,
        ptCenter.y + 1,
        nArcLength - 1,
        -1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    delete pPixelList;

    return TRUE;
}

// 0x7BC7A0
BOOL CVidMode::DrawRecticle3d(const CVIDMODE_RECTICLE_DESCRIPTION& recticleDesc, const CRect& rClip, COLORREF rgbColor)
{
    BYTE* pPixelList = new BYTE[max(recticleDesc.xAxis, recticleDesc.yAxis)];
    CRect rLineClip(rClip.left, rClip.top, rClip.right - 1, rClip.bottom - 1);

    INT v1 = recticleDesc.xAxis + recticleDesc.piePieceXOffset;
    INT v2 = recticleDesc.yAxis + recticleDesc.piePieceYOffset;
    INT v3;

    LONG nArcLength = GetEllipseArcPixelList(recticleDesc.xAxis,
        recticleDesc.yAxis,
        pPixelList);

    nArcLength -= 1;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 757
    UTIL_ASSERT(nArcLength < max(recticleDesc.xAxis, recticleDesc.yAxis));

    v3 = DrawEllipseHOctant3d(recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - v2,
        nArcLength - recticleDesc.xGap,
        -1,
        1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawLine3d(recticleDesc.ptCenter.x + recticleDesc.xGap - nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + recticleDesc.piePiecePtYOffset - v2,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseHOctant3d(recticleDesc.ptCenter.x + 1,
        recticleDesc.ptCenter.y + pPixelList[0] - v2,
        nArcLength - recticleDesc.xGap - 1,
        1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawLine3d(recticleDesc.ptCenter.x - recticleDesc.xGap + nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + recticleDesc.piePiecePtYOffset - v2,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseHOctant3d(recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + v2,
        nArcLength - recticleDesc.xGap,
        -1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawLine3d(recticleDesc.ptCenter.x + recticleDesc.xGap - nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - recticleDesc.piePiecePtYOffset + v2,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseHOctant3d(recticleDesc.ptCenter.x + 1,
        recticleDesc.ptCenter.y - pPixelList[0] + v2,
        nArcLength - recticleDesc.xGap - 1,
        1,
        -1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawLine3d(recticleDesc.ptCenter.x - recticleDesc.xGap + nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - recticleDesc.piePiecePtYOffset + v2,
        rLineClip,
        rgbColor);

    nArcLength = GetEllipseArcPixelList(recticleDesc.yAxis,
        recticleDesc.xAxis,
        pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 789
    UTIL_ASSERT(nArcLength < max(recticleDesc.xAxis, recticleDesc.yAxis));

    v3 = DrawEllipseVOctant3d(recticleDesc.ptCenter.x - v1,
        recticleDesc.ptCenter.y,
        nArcLength - recticleDesc.yGap,
        1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawLine3d(v3,
        recticleDesc.ptCenter.y + recticleDesc.yGap - nArcLength,
        recticleDesc.ptCenter.x + recticleDesc.piePiecePtXOffset - v1,
        recticleDesc.ptCenter.y,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseVOctant3d(recticleDesc.ptCenter.x + pPixelList[0] - v1,
        recticleDesc.ptCenter.y + 1,
        nArcLength - recticleDesc.yGap - 1,
        1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawLine3d(v3,
        recticleDesc.ptCenter.y - recticleDesc.yGap + nArcLength,
        recticleDesc.ptCenter.x + recticleDesc.piePiecePtXOffset - v1,
        recticleDesc.ptCenter.y,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseVOctant3d(recticleDesc.ptCenter.x + v1,
        recticleDesc.ptCenter.y,
        nArcLength - recticleDesc.yGap,
        -1,
        -1,
        pPixelList,
        &rClip,
        rgbColor);

    DrawLine3d(v3,
        recticleDesc.ptCenter.y + recticleDesc.yGap - nArcLength,
        recticleDesc.ptCenter.x - recticleDesc.piePiecePtXOffset + v1,
        recticleDesc.ptCenter.y,
        rLineClip,
        rgbColor);

    v3 = DrawEllipseVOctant3d(recticleDesc.ptCenter.x - pPixelList[0] + v1,
        recticleDesc.ptCenter.y + 1,
        nArcLength - recticleDesc.yGap - 1,
        -1,
        1,
        pPixelList + 1,
        &rClip,
        rgbColor);

    DrawLine3d(v3,
        recticleDesc.ptCenter.y - recticleDesc.yGap + nArcLength,
        recticleDesc.ptCenter.x - recticleDesc.piePiecePtXOffset + v1,
        recticleDesc.ptCenter.y,
        rLineClip,
        rgbColor);

    delete pPixelList;

    return TRUE;
}

// 0x7BCBB0
LONG CVidMode::DrawEllipseHOctant3d(LONG x, LONG y, INT nArcLength, int a4, int a5, BYTE* pPixelList, const CRect* rClip, COLORREF rgbColor)
{
    CPoint pt(x, y);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glColor4f(static_cast<float>(GetRValue(rgbColor)) / 255.0f,
        static_cast<float>(GetGValue(rgbColor)) / 255.0f,
        static_cast<float>(GetBValue(rgbColor)) / 255.0f,
        1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPointSize(1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_POINTS);
    if (rClip != NULL) {
        while (nArcLength != 0) {
            if (rClip->PtInRect(pt)) {
                // NOTE: Original code adds `CVideo3d::SUB_PIXEL_SHIFT`, however
                // it's value (0.2) is too small and due to rounding all points
                // in the arc appears between pixels (rendering no arc at all).
                CVideo3d::glVertex3f(static_cast<float>(pt.x) + 0.5f,
                    static_cast<float>(pt.y) + 0.5f,
                    0.0f);
            }
            if (*pPixelList++ != 0) {
                pt.y += a5;
            }
            pt.x += a4;
            nArcLength--;
        }
    } else {
        while (nArcLength != 0) {
            // NOTE: See rounding issue above.
            CVideo3d::glVertex3f(static_cast<float>(pt.x) + 0.5f,
                static_cast<float>(pt.y) + 0.5f,
                0.0f);
            if (*pPixelList++ != 0) {
                pt.y += a5;
            }
            pt.x += a4;
            nArcLength--;
        }
    }
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    return pt.y;
}

// 0x7BCE20
LONG CVidMode::DrawEllipseVOctant3d(LONG x, LONG y, INT nArcLength, int a4, int a5, BYTE* pPixelList, const CRect* rClip, COLORREF rgbColor)
{
    CPoint pt(x, y);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glColor4f(static_cast<float>(GetRValue(rgbColor)) / 255.0f,
        static_cast<float>(GetGValue(rgbColor)) / 255.0f,
        static_cast<float>(GetBValue(rgbColor)) / 255.0f,
        1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPointSize(1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_POINTS);
    if (rClip != NULL) {
        while (nArcLength != 0) {
            if (rClip->PtInRect(pt)) {
                // NOTE: See rounding issue above.
                CVideo3d::glVertex3f(static_cast<float>(pt.x) + 0.5f,
                    static_cast<float>(pt.y) + 0.5f,
                    0.0f);
            }
            if (*pPixelList++ != 0) {
                pt.x += a4;
            }
            pt.y += a5;
            nArcLength--;
        }
    } else {
        while (nArcLength != 0) {
            // NOTE: See rounding issue above.
            CVideo3d::glVertex3f(static_cast<float>(pt.x) + 0.5f,
                static_cast<float>(pt.y) + 0.5f,
                0.0f);
            if (*pPixelList++ != 0) {
                pt.x += a4;
            }
            pt.y += a5;
            nArcLength--;
        }
    }
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    return pt.x;
}

// 0x7BD090
BOOL CVidMode::OutlinePoly3d(const CPoint* pPoly, SHORT nVertices, const CRect& rSurface, COLORREF rgbColor, const CPoint& ptOffset)
{
    for (SHORT nIndex = 0; nIndex < nVertices - 1; nIndex++) {
        DrawLine3d(pPoly[nIndex].x - ptOffset.x,
            pPoly[nIndex].y - ptOffset.y,
            pPoly[nIndex + 1].x - ptOffset.x,
            pPoly[nIndex + 1].y - ptOffset.y,
            rSurface,
            rgbColor);
    }

    DrawLine3d(pPoly[nVertices - 1].x - ptOffset.x,
        pPoly[nVertices - 1].y - ptOffset.y,
        pPoly[0].x - ptOffset.x,
        pPoly[0].y - ptOffset.y,
        rSurface,
        rgbColor);

    return TRUE;
}

// 0x7BD140
void CVidMode::FillRect3d(const VERTEX_DESC* pVertices)
{
    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_QUADS);

    for (INT nIndex = 0; nIndex < 4; nIndex++) {
        CVideo3d::glColor4f(pVertices[nIndex].color.fRed,
            pVertices[nIndex].color.fGreen,
            pVertices[nIndex].color.fBlue,
            pVertices[nIndex].color.fAlpha);
        CVideo3d::glVertex3f(pVertices[nIndex].fX + CVideo3d::SUB_PIXEL_SHIFT,
            pVertices[nIndex].fY + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
    }

    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7BD270
void CVidMode::RenderTint3d(COLORREF rgbTint, const CRect& rClip)
{
    BYTE r = GetRValue(rgbTint);
    BYTE g = GetGValue(rgbTint);
    BYTE b = GetBValue(rgbTint);

    BYTE nBrightnessCorrection = g_pChitin->GetCurrentVideoMode()->m_nBrightnessCorrection;
    if (nBrightnessCorrection != 0) {
        r = ~((~nBrightnessCorrection * ~r) >> 8);
        g = ~((~nBrightnessCorrection * ~g) >> 8);
        b = ~((~nBrightnessCorrection * ~b) >> 8);
    }

    BYTE nGammaCorrection = g_pChitin->GetCurrentVideoMode()->m_nGammaCorrection;
    if (nGammaCorrection != 0) {
        DWORD nLight = (1 << CVidPalette::LIGHT_SCALE) + nGammaCorrection;
        r = static_cast<BYTE>(min((nLight * r) / 8, 255));
        g = static_cast<BYTE>(min((nLight * g) / 8, 255));
        b = static_cast<BYTE>(min((nLight * b) / 8, 255));
    }

    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_QUADS);
    CVideo3d::glColor4f(static_cast<float>(r) / 512.0f,
        static_cast<float>(g) / 512.0f,
        static_cast<float>(b) / 512.0f,
        1.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.left) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.top) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.left) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.bottom) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.right) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.bottom) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.right) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.top) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7BD5A0
void CVidMode::RenderFlash3d(COLORREF rgbTint, const CRect& rClip)
{
    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_QUADS);
    CVideo3d::glColor4f(static_cast<float>(GetRValue(rgbTint)) / 256.0f,
        static_cast<float>(GetGValue(rgbTint)) / 256.0f,
        static_cast<float>(GetBValue(rgbTint)) / 256.0f,
        1.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.left) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.top) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.left) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.bottom) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.right) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.bottom) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glVertex3f(static_cast<float>(rClip.right) + CVideo3d::SUB_PIXEL_SHIFT,
        static_cast<float>(rClip.top) + CVideo3d::SUB_PIXEL_SHIFT,
        0.0f);
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7BD740
void CVidMode::RenderFan(const VERTEX_DESC* pVertices, INT nVertices)
{
    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_TRIANGLE_FAN);

    for (INT nIndex = 0; nIndex < nVertices; nIndex++) {
        CVideo3d::glColor4f(pVertices[nIndex].color.fRed,
            pVertices[nIndex].color.fGreen,
            pVertices[nIndex].color.fBlue,
            pVertices[nIndex].color.fAlpha);
        CVideo3d::glVertex3f(pVertices[nIndex].fX + CVideo3d::SUB_PIXEL_SHIFT,
            pVertices[nIndex].fY + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
    }

    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7BD880
void CVidMode::RenderQuad(const VERTEX_DESC* pVertices, INT nVertices)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 1438
    UTIL_ASSERT(nVertices == 4);

    CVideo3d::glDisable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBegin(GL_QUADS);

    for (INT nIndex = 0; nIndex < nVertices; nIndex++) {
        CVideo3d::glColor4f(pVertices[nIndex].color.fRed,
            pVertices[nIndex].color.fGreen,
            pVertices[nIndex].color.fBlue,
            pVertices[nIndex].color.fAlpha);
        CVideo3d::glVertex3f(pVertices[nIndex].fX + CVideo3d::SUB_PIXEL_SHIFT,
            pVertices[nIndex].fY + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
    }

    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x5CEDE0
void CVidMode::RenderBlackFade3d()
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        COLORREF rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(RGB(0, 0, 0));
        GLfloat alpha = 1.0f - static_cast<GLfloat>(g_pChitin->GetCurrentVideoMode()->m_nFade) / static_cast<GLfloat>(CVidMode::NUM_FADE_FRAMES);

        CVideo3d::glDisable(GL_TEXTURE_2D);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glEnable(GL_BLEND);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glBegin(GL_QUADS);

        CVideo3d::glColor4f(static_cast<GLfloat>(GetRValue(rgbColor)) / 255.0f,
            static_cast<GLfloat>(GetGValue(rgbColor)) / 255.0f,
            static_cast<GLfloat>(GetBValue(rgbColor)) / 255.0f,
            alpha);

        CVideo3d::glVertex3f(0.0f,
            0.0f,
            0.0f);
        CVideo3d::glVertex3f(0.0f,
            static_cast<GLfloat>(CVideo::SCREENHEIGHT) + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
        CVideo3d::glVertex3f(static_cast<GLfloat>(CVideo::SCREENWIDTH) + CVideo3d::SUB_PIXEL_SHIFT,
            static_cast<GLfloat>(CVideo::SCREENHEIGHT) + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f);
        CVideo3d::glVertex3f(static_cast<GLfloat>(CVideo::SCREENWIDTH) + CVideo3d::SUB_PIXEL_SHIFT,
            0.0f,
            0.0f);

        CVideo3d::glEnd();
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glDisable(GL_BLEND);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }
}

// -----------------------------------------------------------------------------

// 0x7BDC60
BOOL CVidInf::ActivateVideoMode3d(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen)
{
    if (pPrevVidMode != NULL && pPrevVidMode->GetType() == 0) {
        return TRUE;
    }

    g_pChitin->cVideo.SetBitsPerPixels(32, FALSE);
    memset(CVidImage::rgbTempPal, 255, sizeof(CVidImage::rgbTempPal));

    if (!CreateSurfaces3d()) {
        return FALSE;
    }

    g_pChitin->cVideo.m_pCurrentVidMode = this;
    g_pChitin->PreLoadFonts();

    return TRUE;
}

// 0x7BDCE0
BOOL CVidInf::SetDisplayMode()
{
    INT i = 0; // NOTE: Signed compare in assertion below.
    INT iBestMode = 0;
    DWORD nBestFrequency = 0;
    DEVMODEA dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;

    // FIXME: Unused.
    g_pChitin->GetSavedBitsPerPixel();

    DWORD nBpp = !g_pChitin->field_2F4 ? 32 : 16;

    while (EnumDisplaySettingsA(NULL, i, &dm)) {
        if (dm.dmBitsPerPel == nBpp
            && dm.dmPelsWidth == CVideo::SCREENWIDTH
            && dm.dmPelsHeight == CVideo::SCREENHEIGHT
            && dm.dmDisplayFrequency <= CVideo::FPS
            && dm.dmDisplayFrequency >= nBestFrequency) {
            nBestFrequency = dm.dmDisplayFrequency;
            iBestMode = i;
        }
        i++;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo3d.cpp
    // __LINE__: 1832
    UTIL_ASSERT_MSG(i > 0, "No video modes supported?");

    EnumDisplaySettingsA(NULL, iBestMode, &dm);
    if (ChangeDisplaySettingsA(&dm, CDS_RESET | CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL) {
        CVideo::FPS = dm.dmDisplayFrequency;
        return TRUE;
    }

    EnumDisplaySettingsA(NULL, iBestMode, &dm);
    dm.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH | DM_BITSPERPEL;
    if (ChangeDisplaySettingsA(&dm, CDS_RESET | CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL) {
        return TRUE;
    }

    if (CVideo::SCREENWIDTH != GetSystemMetrics(SM_CXFULLSCREEN)
        || CVideo::SCREENHEIGHT != GetSystemMetrics(SM_CYFULLSCREEN)) {
        EnumDisplaySettingsA(NULL, iBestMode, &dm);
        dm.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
        if (ChangeDisplaySettingsA(&dm, CDS_RESET | CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
            CString sMessage;
            sMessage.LoadStringA(g_pChitin->GetIDSSetGameResolution());
            MessageBoxA(NULL, sMessage, CChitin::m_sGameName, 0);
            return FALSE;
        }
    }

    if (CUtil::GetCurrentBitsPerPixels() != nBpp) {
        EnumDisplaySettingsA(NULL, iBestMode, &dm);
        dm.dmFields = DM_BITSPERPEL;
        if (ChangeDisplaySettingsA(&dm, CDS_RESET | CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
            CString sMessage;
            sMessage.LoadStringA(g_pChitin->GetIDSSetGameBitDepth());
            MessageBoxA(NULL, sMessage, CChitin::m_sGameName, 0);
            return FALSE;
        }
    }

    return TRUE;
}

// 0x7BDF90
BOOL CVidInf::CreateSurfaces3d()
{
    g_pChitin->SetRenderCount(2);
    m_dwRBitShift = 0;
    m_dwGBitShift = 8;
    m_dwBBitShift = 16;

    // NOTE: Probably useless in 3D, but where is `m_dwGBitCount` and
    // `m_dwBBitCount`?
    m_dwRBitCount = 8;

    field_C2 = 0;
    field_C6 = 0;
    field_CA = 0;

    m_dwRBitMask = 0xFF;
    m_dwGBitMask = 0xFF00;
    m_dwBBitMask = 0xFF0000;

    field_24 = 0;

    g_pChitin->m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    g_pChitin->m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    m_nVRamSurfaces = 780;

    g_pChitin->cVideo.field_13E = 0;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, 0);

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexEnvf(GL_TEXTURE_ENV,
        GL_TEXTURE_ENV_MODE,
        static_cast<GLfloat>(GL_DECAL));
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    g_pChitin->cVideo.field_13E = 2;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, 2);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        static_cast<GLfloat>(GL_NEAREST));
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        static_cast<GLfloat>(GL_NEAREST));
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGBA,
        CVidInf::FX_WIDTH,
        CVidInf::FX_HEIGHT,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        CVideo3d::texImageData);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    field_178.SetResRef(CResRef("NORMAL"), g_pChitin->field_2EC, TRUE);
    field_178.SetColor(RGB(255, 255, 255), RGB(0, 0, 0), FALSE);
    field_178.RegisterFont();

    return TRUE;
}

// 0x7BE210
BOOL CVidInf::DestroySurfaces3d(CVidMode* pNextVidMode)
{
    if (pNextVidMode != NULL && pNextVidMode->GetType() == 0) {
        return TRUE;
    }

    field_178.Unload();

    GLuint texture1 = 2;
    CVideo3d::glDeleteTextures(1, &texture1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    GLuint texture2 = 5;
    CVideo3d::glDeleteTextures(1, &texture2);

    GLuint texture3 = 6;
    CVideo3d::glDeleteTextures(1, &texture3);

    for (int index = 0; index < m_nVRamSurfaces; index++) {
        GLuint texture = static_cast<GLuint>(index);
        CVideo3d::glDeleteTextures(1, &texture);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }

    DeleteDisposableTextures();

    return TRUE;
}

// 0x7BE300
BOOL CVidInf::RenderPointer3d(UINT nSurface)
{
    CSingleLock positionLock(&(g_pChitin->m_csPointerPosition));
    CSingleLock renderLock(&m_csRenderPointer);

    if (g_pChitin->m_bPointerUpdated) {
        return FALSE;
    }

    renderLock.Lock(INFINITE);
    CVidCell* pPointerVidCell = m_pPointerVidCell;
    renderLock.Unlock();

    if (!m_bPointerInside || pPointerVidCell == NULL || !m_bPointerEnabled) {
        return FALSE;
    }

    g_pChitin->m_bPointerUpdated = TRUE;

    positionLock.Lock(INFINITE);
    CPoint pt = g_pChitin->m_ptPointer;
    positionLock.Unlock();

    CRect rClip(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);

    renderLock.Lock(INFINITE);
    pPointerVidCell->StoreBackground(pt.x,
        pt.y,
        rClip,
        m_rPointerStorage,
        m_nPointerNumber > 0);
    RenderPointerImage(pPointerVidCell,
        nSurface,
        m_nPointerNumber,
        pt.x,
        pt.y,
        m_rPointerStorage);
    renderLock.Unlock();

    g_pChitin->pActiveEngine->InvalidateCursorRect(m_rPointerStorage);

    return TRUE;
}

// 0x7BE4E0
BOOL CVidInf::WindowedFlip3d(BOOL bRenderCursor)
{
    if (bRenderCursor) {
        m_rPointerStorage.left = 0;
        m_rPointerStorage.top = 0;
        m_rPointerStorage.right = 0;
        m_rPointerStorage.bottom = 0;
        g_pChitin->m_bPointerUpdated = FALSE;
        RenderPointer3d(CVIDINF_SURFACE_BACK);
    }

    CChitin3d::SwapBuffers(g_pChitin->cVideo.m_hDC);
    return TRUE;
}

// #binary-identical
// 0x7BE530
void CVidInf::DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
    field_178.SetColor(color, 0, 0);

    CRect screenRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    field_178.TextOut3d(sText, x, y + 16, screenRect, 0, 0);
}

// -----------------------------------------------------------------------------

// 0x7BEA80
BOOL CVidMode::CheckResults3d(int rc)
{
    GLenum prevErr = GL_NO_ERROR;
    INT cnt = 0;
    CString sFunction;
    BOOL bResult = TRUE;

    if (rc != 0) {
        for (int k = 0; k < 255; k++) {
            GLenum err = CVideo3d::glGetError();
            if (err == GL_NO_ERROR) {
                break;
            }

            if (err != prevErr) {
                CString sMessage;
                sMessage.Format("%s: %d occurences\n", sFunction, cnt);
                cnt = 0;

                switch (err) {
                case GL_STACK_OVERFLOW:
                    sFunction = CString("GL_STACK_OVERFLOW");
                    bResult = FALSE;
                    break;
                case GL_STACK_UNDERFLOW:
                    sFunction = CString("GL_STACK_UNDERFLOW");
                    bResult = FALSE;
                    break;
                case GL_OUT_OF_MEMORY:
                    sFunction = CString("GL_OUT_OF_MEMORY");
                    bResult = FALSE;
                    break;
                case GL_INVALID_OPERATION:
                    sFunction = CString("GL_INVALID_OPERATION");
                    bResult = FALSE;
                    break;
                case GL_INVALID_ENUM:
                    sFunction = CString("GL_INVALID_ENUM");
                    bResult = FALSE;
                    break;
                case GL_INVALID_VALUE:
                    sFunction = CString("GL_INVALID_VALUE");
                    bResult = FALSE;
                    break;
                default:
                    sFunction = CString("Unknown Error (default case)");
                    bResult = FALSE;
                    break;
                }
            } else {
                cnt++;
            }
        }

        if (cnt != 0) {
            CString sMessage;
            sMessage.Format("%s: %d occurences\n", sFunction, cnt);
            cnt = 0;
        }
    }

    return bResult;
}

// 0x7BED50
void CVidMode::AddDisposableTexture(INT nTextureId)
{
    CSingleLock lock(&m_disposableTexturesCritSect, FALSE);
    lock.Lock(INFINITE);

    POSITION pos = m_lDisposableTextureIds.GetHeadPosition();
    while (pos != NULL) {
        INT nCurrTextureId = reinterpret_cast<INT>(m_lDisposableTextureIds.GetNext(pos));
        if (nCurrTextureId == nTextureId) {
            break;
        }
    }

    if (pos == NULL) {
        m_lDisposableTextureIds.AddTail(reinterpret_cast<INT*>(nTextureId));
    }

    lock.Unlock();
}

// 0x7BEDE0
void CVidMode::DeleteDisposableTextures()
{
    CSingleLock lock(&m_disposableTexturesCritSect, FALSE);
    lock.Lock(INFINITE);

    while (!m_lDisposableTextureIds.IsEmpty()) {
        GLuint texture = static_cast<GLuint>(reinterpret_cast<INT>(m_lDisposableTextureIds.RemoveHead()));
        CVideo3d::glDeleteTextures(1, &texture);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }

    lock.Unlock();
}

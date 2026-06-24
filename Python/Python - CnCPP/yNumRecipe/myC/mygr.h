/******************************************************************************/
/*                           file name : myGR.h                               */
/*                         description : Gr Interface to MSWindow & XnMotif   */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43320222                             */
/* 4332 0222-0431,0720-____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0121,0211,0308,0315,0409,0512,0522,0612,1005,____,____,____,____,____ */
/* 4334 0104-0110,0215,0328,____,____,____,____,____,____,____,____,____,____ */
/* 4335 0913-0914,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0215,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef grMFC_header_INSTALLED
#define grMFC_header_INSTALLED 1
/******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

#ifndef gecore_header_INSTALLED
typedef struct {
   int x,y;
   unsigned int width,height,borderWidth;
} GERECT;
#endif

void myGROpen();
void myGRClose();
void myGRGEClose(char *pGEClose);

const char *myGRVersionPointer( void );
const char *myGRLogPointer( void );
const char *myGRErrorLogPointer( void );
const char *myGRTemporaryFilesPointer( void );

void myGRSetEchoFunction( int(*pointer)(const char*) );

void myGRExecute(
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     const char *pFile,
     BLOBLIST **ppBlobList
     );
void myGRExecuteSilently(
     const char *pFile,const char *pScript,
     BLOBLIST **ppBlobList
     );
void myGRRefresh(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int bGEClose,char **ppGEClose
     );
void myGRRefreshPlotViewport (
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int nPlotIndex, /* 1..* */
     int bGEClose,char **ppGEClose
     );
void myGRRefreshPlotByOne(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *GC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int nPlotIndex, /* 1..* */
     int bGEClose,char **ppGEClose
     );
void myGRPrint(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     const char *pFileName,int bLandscape
     );
void myGRFreeBlob(
     BLOBLIST *pBlobList
     );
void myGRBlob2File(
     const BLOBLIST *pBlobList,const char *pFileName,const char *pWindow
     );
void myGRBlobChangeFont(
     const BLOBLIST *pBlobList,const char *pFontName
     );

void myDLLPrintToFile(const DLL *list,const char *pFileName);

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* myGR.h */

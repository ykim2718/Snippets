/******************************************************************************/
/*                           file name : tools.c                              */
/*                         description : standard tools                       */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43240118                             */
/* 4324 0118-1021,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 1002,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0329,0804,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0322,0418,0822,0827,____,____,____,____,____,____,____,____,____,____ */
/* 4330 0831,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4331 0714,0920,0929,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0225-0226,0708,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0222,0309,0403-0409,0508-0511,0825-0829,____,____,____,____,____,____ */
/* 4334 0219,0515,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0218-0222,0308,0311,0529,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/
#ifndef standard_tools_header_INSTALLED
#define standard_tools_header_INSTALLED 1
#if defined(__cplusplus)
extern "C" {
#endif
/******************************************************************************/
#include "myCore.h"
#include "nrecipe.h"

#define EVERLOOPBEG do{
#define EVERLOOPEND }while(1)

double dvalue            _((int order));
double atofEx            _((char *value,int isLessThanZero));
int    order             _((double d));
double round             _((double d));
double orderCeil         _((double d,int order));
double orderFloor        _((double d,int order));
double stepRound         _((double value,double step));

/*----------------------------------------------------------------------------*/

int    GetMtrxFrFile _(( /* based 1 */
       const char *qName,MATRIX *pMtx,int *pnRow,int *pnCol ));
int    GetMtrxFrFileWithBlockIndex _(( /* based 1 */
       const char *qName,MATRIX *pMtx,int *nRow,int *nCol,
       int nBlockIndex,int *vBlockIndex ));
int    GetMtrxFrFileEx _(( /* based 1 */
       const char *qName,MATRIX *pMatrix,int *pnRow,int *pnCol,
       char ***pppHeader,int *pnHeaderCount ));
int    GetMtrxFrFileEx2 _((const char*,int,int,int,int,MATRIX*));
int    GetMtrxRowColFrFile _((const char *qName,int *pnRow,int *pnCol));
int    GetMtrxPropertyFrFile _((
       const char* qName,int bVertical,int bLogarithm,
       int* nRow,int* nCol,VECTOR* pVMin,VECTOR* pVMax ));

/*----------------------------------------------------------------------------*/

int    IsInIntVector _((int iValue,int *pVec,int nl,int nh));

/*----------------------------------------------------------------------------*/
/* file & directory functions */

int    myFopen            _(( ));
int    myFclose           _(( ));
int    myFread            _(( ));
int    myFwrite           _(( ));
long   myFtellsize        _(( ));
int    myOpen             _(( ));
int    myClose            _(( ));
int    myRead             _(( ));
int    myWrite            _(( ));
long   myTellsize         _(( ));
int    myFileToStream     _((const char* fileName,char** stream));
int    myFileToStreamEx   _((const char* fileName,int nReadOut,char** stream));
int    myStreamToFile     _((const char* fileName,const char* stream));
long   myStrLseek         _(( ));

char  *myGetCurrentDirName _((void));
int    myGetDirectoryFileNames _((char *directory,char ***names));

int    myDoesFileExist    _((const char *qFile));

char  *get_relative_path    _((const char *qRefPath,const char *qPath));
char  *yGetShortPath       _((const char *qPath,int nLength));
char  *yGetFolderFromFullPath _((const char *qFullPath,int nFullPath));

/*----------------------------------------------------------------------------*/

int    mySigHandle       _(( ));
void   myExit            _(( ));

/*----------------------------------------------------------------------------*/

/* getopt.h - get command line options
 * Parse the command line options, System V style.
 */
int    getopt _((int,char *[],char *));

/*----------------------------------------------------------------------------*/

int GetDLLOfFile();
int GetDLLOfFile_();

/*----------------------------------------------------------------------------*/

int   endTest            _(( ));

/*----------------------------------------------------------------------------*/

char *CurrentKoreanDate();
char *CurrentDateAndTime();

/******************************************************************************/
#if defined(__cplusplus)
}
#endif
#endif /* tools.h */

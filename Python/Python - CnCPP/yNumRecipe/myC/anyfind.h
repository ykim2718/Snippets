/******************************************************************************/
/*                           file name : anyfind.h                            */
/*                         description : anyfind                              */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43310711                             */
/* 4331 0711-0713,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0403-0505,1101-1126-____,____,____,____,____,____,____,____,____,____ */
/* 4333 0104-0516,0614-0701,0810,0825,____,____,____,____,____,____,____,____ */
/* 4334 0210-0217,0410-0413,0430,____,____,____,____,____,____,____,____,____ */
/* 4336 0208-0209,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef anyfind_header_INSTALLED
#define anyfind_header_INSTALLED 1
/******************************************************************************/

#include "myCore.h"
#include "anyfind_def.h"

/******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

int AFOpen _((
    AFLIST **ppList,
    int nSearchType,int nDataUnitType,int nNumericPostProcessType,
    int bCaseSensitive,int bComposite
    ));
int AFClose _((
    AFLIST *pList
    ));
int AFAddNode _((
    AFLIST *pList,int nSearchType,const char *qPattern,int nDividerType
    ));
int AFAddNodeOneToOne _((
    AFLIST *pList,
    char *pSearchString,char *pAlias,char *pFormat,char *pEquation,
    int nDividerType,int nFirst,int nLast,
    double lc,double uc
    ));
int AFAddNodeOneToMany _((
    AFLIST *pList,
    char *sBeginning,char *sEnding,char *sBlockSelections,
    int bBlockSelectionAll,int n1stColumn,
    char *sOtherColumns,char *sFormat,char *sEquation,
    double dCutLow,double dCutHigh
    ));
int AFExtractEx _((
    AFLIST *pList,const char *qFileNames,
    char ****ppppString2d,int *pNrl,int *pNrh,int *pNcl,int *pNch,
    int ((*pSynchronizer)(char*))
    ));
int AFExtract _((
    AFLIST *pList,const char *qFileName,
    char ****ppppString2d,int *pNrl,int *pNrh,int *pNcl,int *pNch
    ));
int AFExchangeRowColPerBlock _((
   char ****ppppString2d,
   int *pNrl,int *pNrh,int *pNcl,int *pNch,
   int nColBlockUnit,int nRCExchangeType
   ));
int AFGetColumnCountPerBlock _((
    AFLIST *pList
    ));
int AFPutItToStream _((
    AFLIST *pList,char ***pppString2d,
    int nrl,int nrh,int ncl,int nch,char **ppStream,
    int bLeftHeaderAttachment,
    int nExHeader,char **sExHeader
    ));
int AFGetPatternAliasArrayB1 _((
    AFLIST *pList,int bNumericHeader,
    char ***rArray,int *nCount
    ));
int AFPrintList _((
    AFLIST *pList
    ));
int AFGetErrorMessagePointer _((char **pMessage)); /* Do not free pMessage */

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* anyfind.h */

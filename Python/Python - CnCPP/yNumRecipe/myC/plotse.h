/******************************************************************************/
/*                           file name : plotse.h                             */
/*                         description : plot script editor                   */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43300423                             */
/* 4330 0814-0824,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0331,0507,0629,0830-0924-1029,1107-1123,____,____,____,____,____,____ */
/* 4334 0209-0226,0320,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef plotse_header_INSTALLED
#define plotse_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"
#include "any.h"

typedef struct _SEDEFNODE {
   struct _SEDEFNODE *next;
   char *src,*dst;
} SEDEFNODE;

typedef struct {
   SEDEFNODE *head,*tail;
   int nTotal;
} SEDEFLIST;

typedef struct {
   char *pCommand;
   int nSignificant;
   IPTRFN pFunc;
} SECMDELEM;

typedef struct {
   SECMDELEM *pArray;
   int nTotal;
} SECMDTABLE;

#if defined(__cplusplus)
extern "C" {
#endif

int SEOpen _(( const char *pStream,DLL **ppList ));
int SEOpenThruFile _(( const char *qFileName,DLL **ppList ));
int SEClose _(( DLL *pList ));
int SEReorderLevel2nd _(( DLL *pList ));
int SEDeleteLevel4thAmbiguity _(( DLL *pList )); /* Repetition & Antonym */
int SEGetSimpleScript _(( const char *pScript,char **ppScript ));
int SEMixUpScripts _(( const char *pScripts,char **ppScript,int bRelayout ));
char *SEGetDelegateName();
char *SEGetPlotName _(( const char *qScript,int nPlotIndex ));
int SEGetPlotCount _(( const char *qScript ));
int SEGetIndexedRectOnRect _((
   double dWidth,double dHeight,double dWidthMargin,double dHeightMargin,
   int nIndexB1,int nTotal,
   double *pLeft,double *pRight,double *pTop,double *pBottom
   ));
int SEGetIndexedViewportForGrWizard _((
   int nIndexB1,int nTotal,
   double *pLeft,double *pRight,double *pTop,double *pBottom
   ));
int SEDeleteIndexedPlotBlock _(( const char *qScript,int nPlotIndex ));

int SEMacroOpen();
int SEMacroClose();
int SEMacroDefine _(( const char *qSrc,const char *qDst ));
int SEMacroRun _(( char **ppStringWID ));

int SECmdOpen _((int nTotal));
int SECmdClose();
int SECmdSetProcedure();
int SECmdRun _((DLL *pList,char *pClientData,IPTRFN pError));

DLN *SEGetLastNodeUnderCurrentLevel _((
   DLL *pList,
   DLN *pNodeCurrent,
   int bIncludingCurrentLevel
   ));

int SEGetReservedWordLevel _((
   const char *str
   ));

char *SEGetNextOptionAddress _((
   const char *
   ));

#if defined(_MSC_)
int SEGetOptionPosition _((
   const char *,
   const char *,int,
   ...
   ));
#elif defined(_UNIXC_) || defined(_HP715C_)
int SEGetOptionPosition _((
   ));
#endif

int SEGetSafeOptionPosition _((
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));

int SEGet1stOptionPosition _((
   const char *pScript,
   const char *pOption,
   int nStart
   ));

int SEGetOptionLength _(( /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ));

int SEGetOptionNameLength _(( /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ));

int SEGetOptionValueLength _(( /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ));

int SEGetOptionBlockLength _((
   const char *pScript,
   int nStart
   ));

int SEGetOptionFrequencyInaRange _((
   const char *pScript,
   int nStart,
   const char *pOption
   ));
int SEBeautifyScript _((
   char *pScript,
   int nScriptLength, /* must have enough extra space. */
   int nLineLength
   ));
const char *SEGetOptionValueAddress _((
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));
char *SEGetOptionValueString _((
   const char *pDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));
double SEGetOptionValueFloating _((
   double nDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));
int SEGetOptionValueInteger _((
   int nDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));
int SESetOptionParameter _((
   const char *pScript,int nScript,
   const char *pOption,int nOption,
   ...
   ));
int SEDelOptionParameter _((
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ));

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* plotse.h */


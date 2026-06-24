/******************************************************************************/
/*                           file name : anyfind_def.h                        */
/*                         description : anyfind structure definition         */
/*                            compiler : MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43360209                             */
/* 4331 0711-0713,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0403-0505,1101-1126-____,____,____,____,____,____,____,____,____,____ */
/* 4333 0104-0516,0614-0701,0810,0825,____,____,____,____,____,____,____,____ */
/* 4334 0210-0217,0410-0413,0430,____,____,____,____,____,____,____,____,____ */
/* 4336 0208-0209,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef anyfind_def_header_INSTALLED
#define anyfind_def_header_INSTALLED 1
/******************************************************************************/

typedef struct _AFNODE { /* 20030209 */
   struct _AFNODE *next,*prev;
} AFNODE;

typedef struct _AFNODEONETOONE { /* AF_ABSOLUTE,AF_SEQUENTIAL,AF_WILD */
   struct _AFNODEONETOONE *next,*prev;
   char *pAlias,*pPattern,*pFormat,*pEquation;
   enum { AF_WHITESPACE=0,AF_CHAR,AF_ADDRESS,AF_EQUATION } nDividerType;
   int nFirst,nLast; /* nFirst<0 is just a finding to move address */
   double dLc,dUc;
} AFNODEONETOONE;

typedef struct _AFNODEONETOMANY { /* AF_BLOCK */
   struct _AFNOTEONETOMANY *next,*prev;
   char *pBeginning,*pEnding,*pBlockSelections;
   int bBlockSelectionAll;
   int n1stColumn;
   char *pOtherColumns,*pFormat,*pEquation;
   double dCutLow,dCutHigh;
   struct {
      char *pWorkFolder; /* temporary directory */
      char *pExtractor,*pJoiner; /* execution file */
   } script;
} AFNODEONETOMANY;

typedef struct _AFLIST {
   AFNODE *head,*tail;
   int nTotal;
   enum { AF_ABSOLUTE=0,AF_SEQUENTIAL=1,AF_WILD=2,AF_BLOCK=3 } nSearchType;
                                               /* AF_BLOCK -> 20030208 */
   enum { AF_FILE=0,AF_FILES=1 } nDataUnitType;
   enum { AF_NONE=0,AF_AVERAGE=1,AF_MEDIAN=2,AF_MIN=3,AF_MAX=4,
          AF_RANGE=5,AF_STDDEV=6,AF_SUM=7,AF_COUNT=8 } nNumPostProcessType;
   int bCaseSensitive;
   int bComposite; /* 2001.0410 : for composite map */
} AFLIST;

static char *qNumericPostProcessStrings[]={
   "None","Average","Median","Min","Max","Range","Stddev","Sum","Count"
};

// 2001.0430
#define AF_ROWCOL_EXCHANGE_NONE       0 // Do nothing
#define AF_ROWCOL_EXCHANGE_BYPATTERN  1 // To make Pattern Columnar Matrix Type
#define AF_ROWCOL_EXCHANGE_BYPATTERN2 2 // To make Pattern2 Columnar Matrix Type
#define AF_ROWCOL_EXCHANGE_BYSPLIT    3 // To make Split Columnar Matrix Type

#define AF_COMMAND_LINE_END    "\r\n"
#define AF_NULL_STRING         "#"
#define AF_SPLIT_INDICATOR     '<'
#define AF_SPLIT_DIVIDER       '\n'

#define AF_INDEXOF_PATTERN  0
#define AF_INDEXOF_ALIAS    1
#define AF_INDEXOF_FIRSTNO  2
#define AF_INDEXOF_LASTNO   3
#define AF_INDEXOF_FORMAT   4
#define AF_INDEXOF_EQUATION 5
#define AF_INDEXOF_LOWERCUT 6
#define AF_INDEXOF_UPPERCUT 7
#define AF_INDEXOF_TOTAL    8

#define AF_OPT_BEGINNING         "sBeginning="
#define AF_OPT_ENDING            "sEnding="
#define AF_OPT_BLOCKSELECTIONS   "sBlockSelections="
#define AF_OPT_BLOCKSELECTIONALL "bBlockSelectionAll="
#define AF_OPT_FIRSTCOLUMN       "n1stColumn="
#define AF_OPT_OTHERCOLUMNS      "sOtherColumns="
#define AF_OPT_FORMAT            "sFormat="
#define AF_OPT_EQUATION          "sEquation="
#define AF_OPT_CUTLOW            "nCutLow="
#define AF_OPT_CUTHIGH           "nCutHigh="

/******************************************************************************/
#endif /* anyfind_def.h */

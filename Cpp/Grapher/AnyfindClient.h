/*
 * AnyfindClient.h
 * shik96@samsung.co.kr, 2K.0810,2001.0411
 */

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
   int nPattern,nSplit;
   char **vb1PatternAlias,**vb1SplitAlias; /* vector whose base is 1 */
   int nRow,nCol,nColCountPerBlock;
   char *dpMessage; /* dynamic pointer */
} GargamelInfo;

extern int GargamelOpen(
   char **pAnyfind, char **spMessage /* static */
   );
extern int GargamelClose(
   char *pAnyfind, GargamelInfo *pInfo
   );
extern int GargamelDoit (
   /* vftbl pointer */
   const char *pAnyfind,
   /* in */
   const char *sFilePattern,const char *sFileSplit,const char *sFileToWrite,
   int nSearchType,int nColMatrixType,int nPostProcessType,
   int bNumericAlias,int bComposite,
   /* out */
   GargamelInfo **pInfo
   );

extern int GargamelGetPostProcessType(
   char ***pppTable,
   int *nTable
   );

#if defined(__cplusplus)
}
#endif
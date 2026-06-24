/******************************************************************************

       File: yNrecipe.h
Description: Numberical Recipes in C
    Creator: Kim, Yongshik (copyRight)
       Date: 43240112-43240112
   Revision: Kim, Yongshik
     Update: 4329 0827,
	         4332 0303,
	         4334 0419,0604,
	         4336 0212-0225,0318,0502-0504,0525,0611,0806,0820,0901-0909,
	              0929-1003,1122,1207-1222,1231,
	         4337 0101-0110,0315,0613
Last Update: 2016.3.24-0403

*******************************************************************************/

#ifndef yNrecipe_header_INSTALLED
#define yNrecipe_header_INSTALLED 1
#if defined(__cplusplus)
extern "C" {
#endif
/******************************************************************************/

#include "yCore.h"
#include "yNumber.h"

#ifndef MIN
#define MIN(x,y) ((x)<(y) ? (x):(y))
#endif

#ifndef MAX
#define MAX(x,y) ((x)>(y) ? (x):(y))
#endif

#ifndef ABS
#define ABS(x)   ((x)<0 ? (-(x)):(x))
#endif

#ifndef SQUARE
#define SQUARE(x)   ((x)*(x))
#endif

#ifndef DEQUAL
#define DEQUAL(d1,d2,tol) (ABS((d1)-(d2))<tol)
#endif

// Macro to restrict a given value to an upper or lower boundary value
#ifndef BOUND
#define BOUND(x,min,max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#endif

// Macro to swap two values
#ifndef SWAP
#define SWAP(x,y) ((x)^=(y)^=(x)^=(y))
#endif
#ifndef SWAP2 // 2016.3.25
#define SWAP2(a, b, T) do { T t; t = a; a = b; b = t; } while(0)
#endif

#ifndef noof
#define noof(obj)         (sizeof(obj)/sizeof((obj)[0]))
#endif

/*----------------------------------------------------------------------------*/

#define MTX_VERTICAL   0
#define MTX_HORIZONTAL 1

typedef double *VECTOR; /* 20030218 */
typedef double **MATRIX; /* 20030218 */
typedef struct { double *v; int l,h; } Vector; /* 20030806 */
typedef struct { double *x,*y; int l,h; } Vector2d; /* 2016.4.3 */
typedef struct { double *x,*y,*z; int l,h; } Vector3d; /* 2016.4.3 */
typedef struct { double **m; int rl,rh,cl,ch; } Matrix; /* 20030806 */
typedef struct { double x,y; } Point2d; /* 2016.3.31 */
typedef struct { double x,y,z; } Point3d; /* 2016.3.31 */
typedef struct { double mean,stdev; } UVNParameter; /* 201/6.3.31 */
typedef struct { double m_x,s_x,m_y,s_y,r; } BVNParameter; /* 2016.3.31 */
typedef struct { double _11,_12,_21,_22; } Matrix2d; /* 2016.3.31 - 4.3 */
typedef struct { double _11,_12,_13,_21,_22,_23,_31,_32,_33; } Matrix3d; /* 2016.3.31 - 4.3 */


Vector *VCreateEx _(( int nL, int nH ));
int    VDestoryEx _(( Vector *V ));
Matrix *MCreateEx _(( int nRL,int nRH,int nCL,int nCH ));
int    MDestroyEx _(( Matrix *M ));

VECTOR VCreate _(( int nL,int nH ));
int    VDestroy _(( VECTOR vAny,int nL,int nH ));
int    VCopy _(( VECTOR vSource,VECTOR vDestination,int nL,int nH ));
VECTOR VDuplicate _(( VECTOR vAny,int nL,int nH ));
VECTOR VDuplicateSafely _(( VECTOR vAny,int nL,int nH,int *nNewH ));
int    VChangeBase _(( VECTOR *pVec,int nBaseOld,int nBaseNew ));
int    VChangeBase2 _(( VECTOR *pV1,VECTOR *pV2,int nBaseOld,int nBaseNew ));
int    VGetMinOrMaxValue _(( VECTOR vAny,int nL,int nH,int bMax,double *pdReturn ));
int    VGetMinMaxValue _(( VECTOR vAny,int nL,int nH,double *pdMin,double *pdMax));
double VGetOneSideStdev _(( VECTOR vAny,int nL,int nH,double dRef,int bPositiveSide));
int    VCheckIntegrity _(( VECTOR vAny,int nL,int nH ));
int    VCheckMonotonity _(( VECTOR vAny,int nL,int nH ));
int    VCheckGreaterThanZero _(( VECTOR vAny,int nL,int nH ));
int    VIsInIntVector _((int iValue, int *pVec, int nl, int nh));
int    VMakeYVectorMonotonicByXVector _(( VECTOR vX,VECTOR vY,int nL,int nH ));
int    VGetValueIndexOfMonotonicVector _(( VECTOR V,int nL,int nH,double dValue,int *pResult ));
int    VGetValueIndexOfMonotonicVectorEx _(( VECTOR V,int nL,int nH,double dValue,int *pResult,double dTolerance ));
int    VGetFirstIndexOfNumberBlock _(( VECTOR V,int nL,int nH,int *pnFirst ));
int    VGetLastIndexOfNumberBlock _(( VECTOR V,int nL,int nH,int *pnLast ));
int    VGetIndexedBoudaryWithSpan _(( int nL,int nH, int nSpan, int nIndex, int *pnLB, int *pnHB ));
int    VGetMaxValueIndexOfMonotonicVector _(( VECTOR vV,int nV,int *pResult));
int    VGetMaxSlopeOfMonotonicVectorByHalfRangeMethod _(( VECTOR vX,VECTOR vY,int nXY,double *pResult));
int    VGetSlopeVector _(( VECTOR vX,VECTOR vY,int nL,int nH,int bFit,VECTOR *pvSlope ));
int    VGetSlopeVectorOverSpan _(( VECTOR vX,VECTOR vY,int nL,int nH,int nSpan,VECTOR *pvSlope ));
int    VGetMonotonicRangeOfVector _(( VECTOR vV,int nL,int nH,int *pnL,int *npH));
int    VGetInterpolatedYValueWithXYVectors _((
          double dXValue,VECTOR vX,VECTOR vY,int nL,int nH,int nSpan,double *pdReturn ));
int    VGetCumAreaVector _((
          VECTOR vX,VECTOR vY,int nL,int nH,int bAbsolute,VECTOR *pvArea ));
int    VGetEqualSpanVector _((
          double dStart,double dStop,int nTotal,int bLog,VECTOR *pvSpan,int *nL,int *nH ));
int    VChangeXStepsInARange _((
       VECTOR vX,VECTOR vY,int nL,int nH,
       VECTOR *pvXNew,VECTOR *pvYNew,int *pnLNew,int *pnHNew,
       double dXStart,double dXStop,double dXStep ));
int    VWriteToFile _((
       const char *qFile,const char *qFormat,VECTOR vAny,int nL,int nH ));

MATRIX MCreate _(( int nRl,int nRh,int nCl,int nCh ));
int    MDestroy _(( MATRIX M,int nRl,int nRh,int nCl,int nCh ));
int    MCopy _(( MATRIX mSource,MATRIX mDestination,
              int nRl,int nRh,int nCl,int nCh ));
int    MGetMinMaxVector _((   ));
int    MGetMinMaxValue _((const MATRIX Mtx,int bVertical,int nIndex,
                          int nL,int nH,int bLogarithm,
                          double *pMin,double *pMax));
int    MGetVector _((const MATRIX Mtx,int bVertical,int nIndex,int nL,int nH,
                  VECTOR *pVec));
int    MGetSafeVector _((const MATRIX Mtx,int bVertical,int nIndex,int nL,int nH,
                  VECTOR *pVec,int *pnL,int *pnH ));
int    MGetSafeVectorPair _((
       const MATRIX Mtx,int bVertical,int nL,int nH,
       int nXIndex,int nYIndex,VECTOR *pXVec,VECTOR *pYVec,int *pnL,int *pnH ));
int    MGetSafeVectorTriple _((
       const MATRIX Mtx,int bVertical,int nL,int nH,
       int nXIndex,int nYIndex,int nZIndex,
       VECTOR *pXVec,VECTOR *pYVec,VECTOR *pZVec,int *pnL,int *pnH ));
int    MAddVector _((
       MATRIX *pmAny,int nRL,int nRH,int nCL,int nCH,VECTOR vAny,int bRightHandSide,
       int *nCLNew,int *nCHNew ));

double MGetColMinimum _((MATRIX mAny,int nRL,int nRH,int nCL,int nCH,int nCol));
double MGetColMaximum _((MATRIX mAny,int nRL,int nRH,int nCL,int nCH,int nCol));
double MGetColMinAndIndex _((MATRIX mAny,int nRL,int nRH,int nColumn,int *pnIndex ));
double MGetColMaxAndIndex _((MATRIX mAny,int nRL,int nRH,int nColumn,int *pnIndex ));

MATRIX MRotate _((   ));
int    MInflate _((MATRIX *pMatrix,int nRL,int nRH,int nCL,int nCH,
                   int nrhNew,int nchNew));
int    MReverseColumn _(( MATRIX mAny,int nRL,int nRH,int nColumn ));

int    MWriteToFile  _((
       const char *qFile,const char *qFormat,
       const MATRIX mAny,int nRL,int nRH,int nCL,int nCH ));
void   MWriteToStdout _((MATRIX mAny,int nRL,int nRH,int nCL,int nCH ));
int    MCreateFromStream _(( char *mem,double ***mtrx,int *rowNo,int *colNo ));

double GetR2WithChi2 _(( VECTOR vData,int nLow,int nHigh,double dChi2 ));
double GetPearsonR2 _(( VECTOR vX,VECTOR vY,int nLow,int nHigh ));
double xfit _((
       VECTOR x,VECTOR y,int ndata,double *yi,double *slope ));
double xxfit _((
       VECTOR x,VECTOR y,int ndata,double *yi,double *slope,int nMinFit,double dMinR2 ));
double xsvdfit _(( VECTOR x,VECTOR y,int ndata,VECTOR vOut,int nOut,
       void (*_svdfit)() ));
double xmrqmin _((
       VECTOR vX,VECTOR vY,int nData,VECTOR vGuess,int nGuess,void (*_mrqmin)() ));
double xxmrqmin _((
       VECTOR x,VECTOR y,int nData,VECTOR vGuess,int nGuess,void (*_mrqmin)(),
       int nMinFit,double dMinR2,
       VECTOR *pvAnswer,int *pnRLAnswer,int *pnRHAnswer ));

/*----------------------------------------------------------------------------*/

double dvalue      _((int order));
double atofEx      _((char *value, int isLessThanZero));
int    order       _((double d));
#if _MSVSC_ == 6
double round       _((double d));
#endif
double orderCeil   _((double d, int order));
double orderFloor  _((double d, int order));
double stepRound   _((double value, double step));

double fnorm       _((double x, double mean, double stddev));
double cnorm       _((double x, double mean, double stddev));
double icnorm      _((double x));
double twoptint    _((double xa[], double ya[], int n, double x));

#if _MSVSC_ == 6
double asinh       _((double));
double acosh       _((double));
double atanh       _((double));
#endif

/*----------------------------------------------------------------------------*/

int   test_Endianness _(());

/******************************************************************************/
#if defined(__cplusplus)
}
#endif
#endif /* yNrecipe.h */

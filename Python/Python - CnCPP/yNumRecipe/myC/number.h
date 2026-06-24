/******************************************************************************/
/*                           file name : number.h                             */
/*                         description : tools for number                     */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43251120                             */
/* 4332 0222-0331,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0428,0611,0822,1208,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0210,0524,1102,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef number_header_INSTALLED
#define number_header_INSTALLED 1
/******************************************************************************/
#include <ctype.h>
#include "myCore.h"

#if !defined(MIN)
#define MIN(x,y) ((x)<(y) ? (x):(y))
#endif
#if !defined(MAX)
#define MAX(x,y) ((x)>(y) ? (x):(y))
#endif
#if !defined(ABS)
#define ABS(x)   ((x)<0 ? (-(x)):(x))
#endif
#if !defined(SQUARE)
#define SQUARE(x)   ((x)*(x))
#endif
#if !defined(DEQUAL)
#define DEQUAL(d1,d2,tol) (ABS((d1)-(d2))<tol)
#endif

/* Macro to restrict a given value to an upper or lower boundary value */
#if !defined(BOUND)
#define BOUND(x,min,max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#endif

/* Macro to swap two values */
#if !defined(SWAP)
#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))
#endif

#define PI 3.141592653589793238462643383279 /* A History of Pi,Petr Beckmann,1971 */
#define RADIAN(degree) ((degree)*PI/180)
#define DEGREE(radian) ((radian)*180/PI)

#define NUMNULLCHR  '#'
#define issign(c)   ((c)=='+'||(c)=='-')
#define isdot(c)    ((c)=='.')
#define isnumchr(c) (isdigit(c)||issign(c)||isdot(c))
#define isnanchr(c) ((c)==NUMNULLCHR)
#define isnumber(s) (isnumchr(*(s))||isnanchr(*(s)))
#define isnumstr(s) (isdigit((s)[0])? 1:\
                     isnanchr((s)[0])? 1:\
                     issign((s)[0])? \
                        isdigit((s)[1])? 1:\
                        isdot((s)[1])? isdigit((s)[2])? 1:0:0:\
                     isdot((s)[0])? isdigit((s)[1])? 1:0:0)
 
#define BITS(n,m) (~(~0 << (m) << 1)&(~0 << (n)))
#define BIT(n) (BITS(n,n))
#define BITS_(n,mask) ((n)&~(mask))

#define ISWAP(a,b) {(a)^=(b);(b)^=(a);(a)^=(b);}

/*----------------------------------------------------------------------------*/

#if defined (_MSC_)
#include <limits.h>
#endif
#define MkMinInteger(i) ((sizeof(i)==1) ? (i)=CHAR_MIN:                           \
                         (sizeof(i)==2) ? (i)=SHRT_MIN:                           \
                         (sizeof(i)==4) ? (i)=LONG_MIN:0)
#define MkMaxInteger(i) ((sizeof(i)==1) ? (i)=CHAR_MAX:                           \
                         (sizeof(i)==2) ? (i)=SHRT_MAX:                           \
                         (sizeof(i)==4) ? (i)=LONG_MAX:0)
#define IsMinInteger(i) ((sizeof(i)==1) ? ((i)==CHAR_MIN) ? 1:0:                  \
                         (sizeof(i)==2) ? ((i)==SHRT_MIN) ? 1:0:                  \
                         (sizeof(i)==4) ? ((i)==LONG_MIN) ? 1:0:0)
#define IsMaxInteger(i) ((sizeof(i)==1) ? ((i)==CHAR_MAX) ? 1:0:                  \
                         (sizeof(i)==2) ? ((i)==SHRT_MAX) ? 1:0:                  \
                         (sizeof(i)==4) ? ((i)==LONG_MAX) ? 1:0:0)
#define IsMinOrMaxInt(i) (IsMinInteger(i)||IsMaxInteger(i))
/*
#define Mk2ndMaxInteger(i) (MkMaxInteger(i),(i)-=1)
#define Is2ndMaxInteger(i) (IsMaxInteger(i+1))
*/

/*----------------------------------------------------------------------------*/

#if defined (_MSC_)

#include <float.h>

#define NUMBER_MIN_POSITIVE_DOUBLE (DBL_MIN)
#define NUMBER_MIN_NEGATIVE_DOUBLE (DBL_MIN*-1)
#define NUMBER_MAX_POSITIVE_DOUBLE (DBL_MAX)
#define NUMBER_MAX_NEGATIVE_DOUBLE (DBL_MAX*-1)

#define MkNaNDouble(d) ((d)=(sizeof(d)==sizeof(double)) ?                      \
        NUMBER_MAX_POSITIVE_DOUBLE:FLT_MAX)
#define IsNaNDouble(d) ((sizeof(d)==sizeof(double)) ?                          \
        (d)==NUMBER_MAX_POSITIVE_DOUBLE||(d)==NUMBER_MAX_NEGATIVE_DOUBLE:      \
        (d)==FLT_MAX)
/*#define mkDoubleNaN(d) ((d)=DBL_MAX)
#define isDoubleNaN(d) ((d)==DBL_MAX)*/
#define MkPositiveMinDouble(d) ((d)=DBL_MIN)
#define MkNegativeMinDouble(d) ((d)=DBL_MAX*-1)
#define MkPositiveMaxDouble(d) ((d)=DBL_MAX)
#define MkNegativeMaxDouble(d) ((d)=DBL_MAX*-1)

#define MkNaNFloat(f)  (mkDoubleNaN(f))
#define IsNaNFloat(f)  (isDoubleNaN(f))

#elif defined(_UNIXC_) || defined(_HP715C_)

#define MkNaNDouble(d) (((unsigned long *)&(d))[0]=0x7fffffffL)
#define IsNaNDouble(d) (((unsigned long *)&(d))[0]==0x7fffffffL)
#define MkNaNFloat(f)  (mkNaNDouble(f))
#define IsNaNFloat(f)  (isNaNDouble(f))

#else
#error Compiler type (_MSC_,_UNIXC_,...) should be defined.
#endif

/******************************************************************************/
#endif /* number.h */

/******************************************************************************

       File: yNumber.h
Description: Basic definitions for Numbers
    Creator: Kim, Yongshik (copyRight)
       Date: 43251120
   Revision: Kim, Yongshik
     Update: 4332 0222-0331,
	         4333 0428,0611,0822,1208,
	         4336 0210,0524,1102
Last Update: 2016 0324-0402

*******************************************************************************/

#ifndef yNumber_header_INSTALLED
#define yNumber_header_INSTALLED 1
/******************************************************************************/
#include <math.h>
#include <ctype.h>

typedef char               int8s;
typedef unsigned char      int8u;
typedef short              int16s;
typedef unsigned short     int16u;
typedef int                int32s;
typedef unsigned int       int32u;
typedef long long          int64s;
typedef unsigned long long int64u;

#define PI 3.141592653589793238462643383279 // A History of Pi,Petr Beckmann,1971
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

#include <math.h>
#include <float.h>
/*
#if defined (_MSVSC_)
#include <limits.h>
#endif
*/
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

#define NaNDouble   HUGE_VAL // 2016.3.26
#define NaNFloat    NAN      // 2016.3.26

#define NUMBER_MIN_POSITIVE_DOUBLE (DBL_MIN)
#define NUMBER_MIN_NEGATIVE_DOUBLE (DBL_MIN*-1)
#define NUMBER_MAX_POSITIVE_DOUBLE (DBL_MAX)
#define NUMBER_MAX_NEGATIVE_DOUBLE (DBL_MAX*-1)


#define MkNaNDouble(d) ((d)=NaNDouble)
#define IsNaNDouble(d) ((d)==NaNDouble)
#define MkNaNFloat(f)  (MkNaNDouble(f))
#define IsNaNFloat(f)  (IsNaNDouble(f))

#define MkPositiveMinDouble(d) ((d)=DBL_MIN)
#define MkNegativeMinDouble(d) ((d)=DBL_MAX*-1)
#define MkPositiveMaxDouble(d) ((d)=DBL_MAX)
#define MkNegativeMaxDouble(d) ((d)=DBL_MAX*-1)

/******************************************************************************/
#endif /* yNumber.h */

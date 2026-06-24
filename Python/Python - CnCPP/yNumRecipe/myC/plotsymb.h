/******************************************************************************/
/*                           file name : plotsymb.h                           */
/*                         description : stroke-symbol file used in PLOT      */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43260426                             */
/* 4329 0511-0515,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0317,0409,0517-0523,0606,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef plot_symb_header_INSTALLED
#define plot_symb_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"

typedef union {
   struct {
#if defined(_UNIXC_) || defined(_HP715C_)
          unsigned char row : 4;
          unsigned char col : 4;
#elif defined(_MSC_)
          unsigned char row : 4;
          unsigned char col : 4;
#else
#error Compiler type (_UNIXC_/_HP715C_/_MSC_/..) must be defined.
#endif
          } part;
   struct {
          unsigned char obj : 8;
          } whole;
} PLTSTROKESYMB;

#define STROKESYMB_TOTAL           71
#define STROKESYMB_INDEX_OF_ALPHA  28
#define STROKESYMB_INDEX_OF_SQUARE 6
#define STROKESYMB_DATA_UNIT       32

/******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

int GetStrokeSymbolPoints _(( /* 1000 scale */
   int code,
   int *xPoints,int *yPoints, /* [0..(total-1)] */
   int total
   ));

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* plotsymb.h */

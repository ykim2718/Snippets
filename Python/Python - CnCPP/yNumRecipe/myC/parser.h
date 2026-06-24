/******************************************************************************/
/*                           file name : parser.h                             */
/*                         description : math parser library header           */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43240124                             */
/* 4324 0124-0403,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0418,0509,0816,____,____,____,____,____,____,____,____,____,____,____ */
/* 4334 0213,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#ifndef parser_header_INSTALLED
#define parser_header_INSTALLED 1
/******************************************************************************/

#include <setjmp.h>
extern jmp_buf jb_parser;
void mathparserEx _(( const char *qExpression,double *dResult )); /* 2001.0213*/
void mathparser _(( const char *expr, double *result ));
double mathparserSlotValue _((char slot));

/******************************************************************************/
#endif /* parser.h */

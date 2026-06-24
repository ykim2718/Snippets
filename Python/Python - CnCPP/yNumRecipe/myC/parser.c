/******************************************************************************/
/*                           file name : parser.h                             */
/*                         description : math parser library header           */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43240124                             */
/*                                                                            */
/*                         RECURSIVE DESCENDENT PARSER                        */
/*                                                                            */
/* 4324 0124-0403,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 0823,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0124,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0418,0509,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4334 0213,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#include "myCore.h"
#include "parser.h"
#include "nrecipe.h"
#include "str.h"

/******************************************************************************/

#define TOKENSIZE  0xff
#define TOKENTYPE  unsigned char

#define DELIMITER  0x01
#define VARIABLE   0x02
#define NUMBER     0x03
#define STRING     0x04
#define QUOTE      0x05
#define COMMA      0x06

#define tolower_(c) (('A'<=(c)&&(c)<='Z') ? (c)-'A'+'a':(c))
#define iscmnd(tt) ((0x50<=(tt)&&(tt)<=0x9f) ? 1:0)
#define isfunc(tt) ((0xa0<=(tt)&&(tt)<=0xff) ? 1:0)
#define idfunc(tt) ((0xa0<=(tt)&&(tt)<=0xcf) ? 1:\
                    (0xd0<=(tt)&&(tt)<=0xef) ? 2:\
                    (0xf0<=(tt)&&(tt)<=0xff) ? 3:0)

/* command */
#define GOTO       0x50

/* function_1*/
#define _ABS_       0xa0
#define _SQRT_      0xa1
#define _EXP_       0xa2
#define _LOG_       0xa3
#define _LOG2_      0xa4
#define _LOG10_     0xa5
#define _POW10_     0xa6
#define _SIN_       0xa7
#define _COS_       0xa8
#define _TAN_       0xa9
#define _ASIN_      0xb0
#define _ACOS_      0xb1
#define _ATAN_      0xb2
#define _SINH_      0xb3
#define _COSH_      0xb4
#define _TANH_      0xb5 
#define _ASINH_     0xb6
#define _ACOSH_     0xb7
#define _ATANH_     0xb8

/* function_2*/
#define _POW_       0xd0
#define _ATAN2_     0xd1
#define _HYPOT_     0xd2

/* function_3*/
#define _LIFE_      0xf0

/******************************************************************************/

jmp_buf jb_parser;
static const char *prog;
static char token[TOKENSIZE];
static TOKENTYPE tok_type;
static 
double vars[26] = { /* 26 user variables A-Z */
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0  
};
static
struct functions {
   char func[10];
   int tok;
} ftable[] = {
/* function_1 */
   "abs",  _ABS_,  "sqrt", _SQRT_,  "exp",  _EXP_,   "log",  _LOG_,
   "pow",  _LOG_,  "log2", _LOG2_,  "log10",_LOG10_, "pow10",_POW10_,
   "sin",  _SIN_,  "cos",  _COS_,   "tan",  _TAN_,   "asin", _ASIN_,
   "acos", _ACOS_, "atan", _ATAN_,  "sinh", _SINH_,  "cosh", _COSH_,
   "tanh", _TANH_, "asinh",_ASINH_, "acosh",_ACOSH_, "atanh",_ATANH_,
/* function_2 */
   "pow",  _POW_,  "atan2",_ATAN2_, "hypot",_HYPOT_,  
/* function_3 */
   "life", _LIFE_,
    0,0
};

       void mathparser();
       double mathparserSlotValue _((char slot));
static void level_1();
static void level_2();
static void level_3();
static void level_4();
static void level_5();
static void level_6();
static void level_7();
static void primitive();
static void arith();
static void func_1();
static void func_2();
static void func_3();
static void unary();
static void putback();
static double find_var();
static void get_token();
static int isdelim();
static int isspace_();
static int func_look_up();
static void serror();
static void aerror();

/******************************************************************************/

void mathparserEx( qExpression,dResult ) /* 2001.0213 */
   const char *qExpression;
   double *dResult;
{
   const char cDelimiter=';';
   int nCount,nIndex;
   char *pAddr;

   nCount=chrcount(qExpression,cDelimiter);
   for (pAddr=(char*)qExpression,nIndex=1;nIndex<=nCount;nIndex++) {
      pAddr=strchr(pAddr,cDelimiter);
      *pAddr=0;
      pAddr++;
   }
   for (pAddr=(char*)qExpression,nIndex=0;nIndex<=nCount;nIndex++) {
      mathparser(pAddr,dResult);
      if (nIndex==nCount) break;
      pAddr+=strlen(pAddr)+1;
      pAddr[-1]=cDelimiter;
   }
}

void mathparser( expr,result )
   const char *expr;
   double *result;
{
   prog = expr;

   get_token();
   if (!*token) {
      serror( 2 );
      return;
   }
   level_1( result );
}

double mathparserSlotValue( slot )
   char slot;
{
   return vars[toupper(slot)-'A'];
}

static /* Process an assignment statement. */
void level_1( result )
   double *result;
{
   int slot,ttok_type;
   char temp_token[TOKENSIZE];

   if (tok_type == VARIABLE ) {
      strcpy( temp_token,token );
      ttok_type = tok_type;
      slot = toupper(*token) - 'A';
      get_token();
      if (*token!='=') {
         putback();
         strcpy( token,temp_token );
         tok_type = ttok_type;
      } else {
         get_token();
         level_2( result );
         vars[slot] = *result;
         return;
      }
   }
   level_2( result );
}

static /* Add or subtract two terms. */
void level_2( result )
   double *result;
{
   register char op;
   double hold;
 
   level_3( result );
   while ((op=*token)=='+'||op=='-') {
      get_token();
      level_3( &hold );
      arith( op,result,&hold );
   }
}

static /* Multiply or divide two factors. */
void level_3( result )
   double *result;
{
   register char op;
   double hold;

   level_4( result );
   while ((op=*token)=='*'||op=='/'||op=='%') {
      get_token();
      level_4( &hold );
      arith( op,result,&hold );
   }
}

static /* Process an integer exponent. */
void level_4( result )
   double *result;
{
   double hold;

   level_5( result );
   if (*token=='^') {
      get_token();
      level_4( &hold );
      arith( '^',result,&hold );
   }
}

static /* Process a unary + or -. */
void level_5( result )
   double *result;
{
   register char op;

   op = 0;
   if ((tok_type==DELIMITER)&&*token=='+'||*token=='-') {
      op = *token;
      get_token();
   }
   level_6( result );
   if (op) unary( op,result );
}

static /* Process a parenthesized expression. */
void level_6( result )
   double *result;
{
   if ((tok_type==DELIMITER)&&(*token=='(')) {
      get_token();
      level_1( result );
      if (*token!=')') serror( 1 );
      get_token();
   } else if (isfunc(tok_type))
      level_7( result );
   else 
      primitive( result );
}

static /* Process a function with a parenthesized expression. */
void level_7( result )
   double *result;
{
   int ttok_type;
   double a1,a2,a3; a1=a2=a3=0.0;

   ttok_type = tok_type;
   get_token();
   if (*token!='(') serror(2);
   level_6( result );
   switch (idfunc(ttok_type)) {
      case 1 : func_1( ttok_type,result );break;
      case 2 : func_2( ttok_type,result,a1,a2 );break;
      case 3 : func_3( ttok_type,result,a1,a2,a3 );break;
   }
}

static /* Find value of number or variable. */
void primitive( result )
   double *result;
{
   switch(tok_type) {
      case VARIABLE:
           *result = find_var(token);
           get_token();
           return;
      case NUMBER:
           *result = atof(token);
           get_token();
           return;
      default:
           serror(0);
   }
}

static /* Perform the specified arithmetic. */
void arith( o,r,h )
   char o;
   double *r,*h;
{
   register int t,ex;

   switch(o) {
      case '-': *r = *r - *h;
                break;
      case '+': *r = *r + *h;
                break;
      case '*': *r =*r * *h;
                break;
      case '/': if (*h==0) aerror(0);
                *r = (*r) / (*h);
                break;
      case '%': t=(int)((*r)/(*h));
                *r = *r - (t * (*h));
                break;
      case '^': ex=(int)(*r);
                if (*h==0) *r = 1;
                else *r = pow(*r,*h);
                break;
   }
}

static /* Perform a function with one argument. */
void func_1( tok_type,result )
   TOKENTYPE tok_type;
   double *result;
{
   switch ( tok_type ) {
      case _ABS_    : *result = fabs(*result); break;
      case _SQRT_   : *result = sqrt(*result); break;
      case _EXP_    : *result = exp(*result);  break;
      case _LOG_    : if (*result<=0) aerror(1);
                      *result = log(*result);  break;
      case _LOG2_   : if (*result<=0) aerror(1);
                      *result = log(*result)/log(2.0); break;
      case _LOG10_  : if (*result<=0) aerror(1);
                      *result = log10(*result);break;
      case _POW10_  : *result = pow10(*result);break;
      case _SIN_    : *result = sin(*result);  break;
      case _COS_    : *result = cos(*result);  break;
      case _TAN_    : *result = tan(*result);  break;
      case _ASIN_   : *result = asin(*result); break;
      case _ACOS_   : *result = acos(*result); break;
      case _ATAN_   : *result = atan(*result); break;
      case _SINH_   : *result = sinh(*result); break;
      case _COSH_   : *result = cosh(*result); break;
      case _TANH_   : *result = tanh(*result); break;
      case _ASINH_  : *result = asinh(*result);break;
      case _ACOSH_  : *result = acosh(*result);break;
      case _ATANH_  : *result = atanh(*result);break;
   }
}

static /* Perform a function with two argument. */
void func_2( tok_type,result,a1,a2 )
   TOKENTYPE tok_type;
   double *result,a1,a2;
{
   switch ( tok_type ) {
      case _POW_    : *result = pow(a1,a2);    break;
      case _ATAN2_  : *result = atan2(a1,a2);  break;
      case _HYPOT_  : *result = hypot(a1,a2);  break;
   }
}

static /* Perform a function with three argument. */
void func_3( tok_type,result,a1,a2,a3 )
   TOKENTYPE tok_type;
   double *result,a1,a2,a3;
{
   switch ( tok_type ) {
      case _LIFE_  : break;
      default      :      ;
   }
}

static /* Evaluate a unary operator. */
void unary( o,r )
   char o;
   double *r;
{
   if (o=='-') *r = -(*r);
}

static /* Return a token to its resting place. */
void putback()
{
   char *t;

   t = token;
   for (;*t;t++) prog--;
}

static /* Find the value of a variable. */
double find_var( s )
   char *s;
{
   if (!isalpha(*s)) {
      serror( 1 );
      return 0;
    }
    return vars[toupper(*token)-'A'];
}

static /* Get a token. */
void get_token()
{
   register char *temp;

   tok_type = 0;
   temp = token;

   while (isspace_(*prog)) ++prog;

   if (strchr("+-*/%^=()",*prog)) {
      tok_type = DELIMITER;
      *temp++ = *prog++;
   } else if (isalpha(*prog)) {
      while (!isdelim(*prog)) *temp++ = *prog++;
      tok_type = STRING;
   } else if (isdigit(*prog)) {
      while (!isdelim(*prog)) *temp++ = *prog++;
      if ((prog[0]=='+'||prog[0]=='-')
      && (prog[-1]=='e'||prog[-1]=='E')) {
         *temp++ = *prog++;
         while (!isdelim(*prog)) *temp++ = *prog++;
      }
      tok_type = NUMBER;
   }

   *temp = '\0';

   if (tok_type==STRING) {
      tok_type = func_look_up( token );
      if (!tok_type) tok_type=VARIABLE;
   }
}

static /* Return true if c is a delimiter. */
int isdelim( c )
   char c;
{
   if (strchr(" +-/*%^=()",c) 
   || c==9
   || c=='\r'
   || c==0 )
      return 1;
   return 0;
}

static /* Return true if c is a space or tab. */
int isspace_( c )
   char c;
{
   if (c==' '||c=='\t') return 1;
   return 0;
}
  
static 
int func_look_up( s )
   char *s;
{
   register int i;
   char *p;

   p = s;
   while (*p) {  *p=tolower_(*p);p++; }
   for (i=0;*ftable[i].func;i++) 
      if (!strcmp(ftable[i].func,s)) return ftable[i].tok;
   return 0;
}

static 
void serror( error )
   int error;
{
   static char *se[]={
      "syntax error",
      "unbalanced parentheses",
      "no expression present"
   };
 
   printf("%s in parser()\n",se[error]);
   longjmp( jb_parser,1 );
}

static 
void aerror( error )
   int error;
{
   static char *ae[]={
      "unable to devide by zero",
      "bad number at log-func",
   };
 
   printf("%s in parser(),2",ae[error]);
   longjmp( jb_parser,1 );
}

/******************************************************************************/
/* end of parser.c */

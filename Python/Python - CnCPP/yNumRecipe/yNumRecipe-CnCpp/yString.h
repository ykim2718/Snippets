/******************************************************************************

       File: yString.h
Description: String and stream library
    Creator: Kim, Yongshik (copyRight)
       Date: 43250215
   Revision: Kim, Yongshik
     Update: 4327 1004,
	         4328 0515,0611,0804,1105,1115,
			 4329 0320,
			 4330 0604,0830,
			 4331 0711-0715,0929,
			 4333 0127,0403,0504-0527,0609,0612,0621,0629,0703,0809,0816,1107,
			 4334 0209,0219-0221,
			 4336 0209-0218,0417,0512,0529,
			 4337 0613,1221,1226
Last Update: 2016 0324-0402

*******************************************************************************/

#ifndef yString_header_INSTALLED
#define yString_header_INSTALLED 1
#if defined(__cplusplus)
extern "C" {
#endif
/******************************************************************************/

#include "yCore.h"
#include "yNumber.h"

#define CNULL             (char*)0
#define strequ(s1,s2)     (!strcmp((const char*)(s1),(const char*)(s2)))
#define strnequ(s1,s2,n)  (!strncmp((s1),(s2),(n)))
#define strdplEx(s)       ((s)?(*(s))?strdpl(s):NULL:NULL)
#define freeEx(s)         ((s)?(free(s),(s)=NULL):NULL)
#define salloc(type,no)   (type*)malloc((unsigned int)((no)*sizeof(type)))

#ifndef noof
#define noof(obj)         (sizeof(obj)/sizeof((obj)[0]))
#endif

#define whitechars         " \t\n\f\r"
/* ISO-LATIN-1,
'\t' \u0009 HORIZONTAL TABULATION
'\n' \u000A NEW LINE
'\f' \u000C FORM FEED
'\r' \u000D CARRIAGE RETURN
'  ' \u0020 SPACE
*/

/******************************************************************************/

char *skipwhite          _((char**));
char *rskipwhite         _((char**));
char *skipblack          _((char**));
char *rskipblack         _((char**));
char *skipstring         _((char**,char*));
char *skipdigit          _((char**));
char *skipalpha          _((char**));
int  chrchrs             _((char,char*));

char *indexalnum         _((char*));
char *indexdigit         _((char*));

char *strtrimleft        _((char*));
char *strtrimright       _((char*));
char *strtrim            _((char*)); /* trimming the white at the both ends. */
char *strcompact         _((char*)); /* reduce adjacent spaces to a space
                                        and trim the both end spaces. */
char *strmid             _((const char*,int nFrom,int nTo));
char *strmidp            _((const char*,const char* qFrom,const char* qTo)); /* 20030209 */
char *strmiddle          _((const char*,int nIndex,int nCount)); /* 2001.0221 */
char *strleft            _((const char*,const char*));
char *strright           _((const char*,const char*));
int   strtokcount        _((const char*,const char*));
char *strtokbyindex      _((const char*,const char*,int nIndex)); /* nIndex=0,... */
char *strcommon          _((const char*,const char*,int nStart));
char *strreverse         _((const char *)); /* 20010210:GY */
char *strinsert          _((char **ppStr,int nIndex,const char *qStr)); /* 2001.0221 */
char *strdelete          _((const char*,int nIndex,int nCount)); /* 2001.0219 */
char *strreplace         _((char **ppStr,const char *qSrc,const char *qDst));

char *strdel             _((const char*,const char*,size_t));
char *strins             _((const char*,const char*,const char*));
char *strrep             _((char *str,char *src,char *dst));

char *strchrs            _((const char*,const char* chars));
/* char *strstr             _(( )); */
char *strstrnocase       _((const char *s1,const char *s2));
char *strrstr            _((const char *s1,const char *s2));
#if defined(_MSVSC_)
char *strvfromto           (char *first, ...);
#elif defined(_UNIXC_) || defined(_HP715C_)
char *strvfromto            ();
#endif
char *strcpy2buf         _((char *buf,const char *src, int16u bufSize));
char *strdpl             _((const char*));
char *strdplwf           _(( )); /* strdpl with some filling */
#if defined(_MSVSC_)
char *strvcat              (const char *first, ...);
#elif defined(_UNIXC_) || defined(_HP715C_)
char *strvcat              ();
#endif

char *strtolower         _((char*));
char *strtoupper         _((char*));
char *strescape          _(( ));

int  strseq              _((char *str,char **strings,int no));

int  strweq              _((const char *str,const char *filter));
int  strnweq             _((char *string,char *filter,int length));

char  *itostr            _((int,const char*)); /* 20030529: const char* -> char* */
char  *itostr2           _((int,const char*)); /* 20041221: eg) 11 -> "11st" */
char  *dtostr            _((double,const char*)); /* 20030530.scientific form: eg) 0.1 -> "100m" */
char  *dtostre           _((double,int)); /* 20041226.engineering form: eg) 0.1 -> 1e-1 */

const char  *dtos        _((double,const char*));
double stod              _((const char*)); /* 20030417 */
const char  *c2ha        _((char)); /* ? 20030529 */
int    ha2i              _((  )); /* ? 20030529 */

char **alloStrings       _((int));
int  freeStrings         _((char**, int));
char **alloString1d      _((int nrl,int nrh));
char ***alloString2d     _((int nrl,int nrh,int ncl,int nch));
int  freeString1d        _((char **s1d,int nrl,int nrh));
int  freeString2d        _((char ***s2d,int nrl,int nrh,int ncl,int nch));

char *string1dtostream   _((char **array,int nl,int nh,char *space));
char *string2dtostream   _((char ***matrix,int nrl,int nrh,int ncl,int nch,
                            char *space,char *newLine));

int chrcount             _((const char *stream,char chr));
int strcount             _((const char *stream,const char* string));

#define id_strwid(strwid) (*(int*)((strwid)+strlen(strwid)+1))
char *strdplwid          _((const char *string,int nID));
char *strtrimwid         _((char *string));

int  getintgerarray      _((const char *qString,int *nArray,int**vArray));

/******************************************************************************/
#if defined(__cplusplus)
}
#endif
#endif /* yString.h */

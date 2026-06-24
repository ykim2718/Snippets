/******************************************************************************

     File: yString.c
  Creator: Kim, Yongshik
Date: 43250215
Revised by: Kim, Yongshik
Update: 4326 0915
        4327 1004
        4328 0515,0611,0706,0804,0826,1115
        4329 0320,0518
        4330 0604,0606,0830,0920
        4331 0711-0713,0916,0929
        4332 0401-1126
        4333 0127,0403,0512-0527,0607,0612,0616,0621,0626,0629,0704,0705,0809,
		     0811,0816,1107
        4334 0209,0215,0218-0219,0302
        4336 0209-0220,0417,0522,0803,0811,0813
        4337 0613,1221
Last Update: 20160325-0402

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "yCore.h"
#include "yAlloc.h"
#include "yNumber.h"
#include "yNrecipe.h"
#include "yAny.h"
#include "yString.h"


/******************************************************************************/

static char qBuffer[1024];

/******************************************************************************/
/**********************************k*i*m***************************************/
/****************************y*o*n*g*-*s*h*i*k*********************************/
/******************************************************************************/
/******************************************************************************/

#if defined(_UNIXC_)
static
void *memmove( s1,s2,n ) /* copy char s2[n] to s1[n] safely */
                         /* P.J.Plauger,"The Standard C Libray",page 400 */
   char *s1,s2[];
   size_t n;
{
   char *sc1;
   char *sc2;

   sc1=s1;
   sc2=s2;
   if (sc2<sc1 && sc1<sc2+n)
      for (sc1+=n,sc2+=n;0<n;--n)
         *--sc1=*--sc2;          /* copy backwards */
   else
      for (;0<n;--n)
         *sc1++=*sc2++;          /* copy forewards */
   return (s1);
}
#endif

char *skipwhite( p )
   char **p;
{
#if defined(_UNIXC_)
   while (**p
   &&     isspace(**p))
      (*p)++;
#elif defined(_MSVSC_)
   while (**p
   &&     iswspace(**p))
      (*p)++;
#else
#error (Y) Compiler type should be defined.
#endif
   return (char *)*p;
}

char *rskipwhite( p )
   char **p;
{
#if defined(_UNIXC_)
   while (**p && isspace(**p))
      (*p)--;
#elif defined(_MSVSC_)
   while (**p && iswspace(**p))
      (*p)--;
#else
#error (Y) Compiler type should be defined.
#endif
   return (char *)*p;
}

char *skipblack( p )
   char **p;
{
#if defined(_UNIXC_)
   while (**p && !isspace(**p))
      (*p)++;
#elif defined(_MSVSC_)
   while (**p && !iswspace(**p))
      (*p)++;
#else
#error (Y) Compiler type should be defined.
#endif
   return (char *)*p;
}

char *rskipblack( p )
   char **p;
{
#if defined(_UNIXC_)
   while (**p && !isspace(**p))
      (*p)--;
#elif defined(_MSVSC_)
   while (**p && !iswspace(**p))
      (*p)--;
#else
#error (Y) Compiler type should be defined.
#endif
   return (char *)*p;
}

char *skipstring( str,skip )
   char **str,*skip;
{
	register size_t i, l, found;  // Y, 2016.3.28, register int i,l,found;

   l=strlen(skip);
   found=0;
   while (*str) {
      for (i=0;i<l;i++)
        if (skip[i]==**str) {
           found=1;
           break;
        }
      if (found) {
         found=0;
         (*str)++;
      } else
         break;
   }
   return (char *)*str;
}

char *skipdigit( p )
   char **p;
{
   while (**p
   &&     isdigit(**p))
      (*p)++;
   return (char *)*p;
}

char *skipalpha( p )
   char **p;
{
   while (**p
   &&     isalpha(**p))
      (*p)++;
   return (char *)*p;
}

int chrchrs( chr,chars )
   char chr,*chars;
{
   while(*chars) {
      if (chr==*chars)
         return TRUE;
      chars++;
   }
   return FALSE;
}

char *indexalnum( str )
   char *str;
{
   register size_t i,l; // 2016.3.28, size_t <-- int
   l=strlen(str);
   for (i=0;i<l;i++,str++)
      if (isalnum(*str)) return str;
   return NULL;
}

char *indexdigit( str )
   char *str;
{
   register size_t i,l; // 2016.3.28, size_t <-- int
   l=strlen(str);
   for (i=0;i<l;i++,str++)
      if (isdigit(*str)) return str;
   return NULL;
}

char *strtrimleft( str )
   char *str;
{
   char *p1;
   p1=str;
   skipwhite(&p1);
   if (str!=p1)
      memmove(str,p1,strlen(p1)+1);
   return str;
}

char *strtrimright( str )
   char *str;
{
   char *p2;
   p2=str+strlen(str)-1;
   rskipwhite(&p2);
   *(++p2)=(char)0;
   return str;
}

char *strtrim( str ) /* Trims the white at the both ends.
                        No change in the address of str. */
   char *str;
{
   strtrimleft(str);
   return strtrimright(str);
   /*
   char *p1,*p2;

   p1=str;
   p2=str+strlen(str)-1;
   skipwhite(&p1);
   rskipwhite(&p2);
   *(++p2)=(char)0;
   if (str!=p1)
      memmove(str,p1,strlen(p1)+1);
   return str;
   */
}

char *strcompact( str )
   char *str;
{
   char *p,*q;

   q=p=str;

   if (*p==' ') {
      while (*q==' ') q++;
      memcpy(p,q,strlen(q)+1);
   }

   while (*p) {
      if (*p==' ') {
         q=++p;
         while (*q==' ') q++;
         if (p!=q) {
            memcpy(p,q,strlen(q)+1);
         }
      }
      p++;
   }
   p=str+strlen(str)-1;
   if (*p==' ') *p='\0';

   return str;
}

char *strmid( qStr,nFrom,nTo )
   const char *qStr;
   int nFrom,nTo;
{
   if (nFrom>nTo) SWAP(nFrom,nTo);
   return strmiddle(qStr,nFrom,nTo-nFrom+1);
}

char *strmidp( qStr,qFrom,qTo ) /* 20030209 */
   const char *qStr,*qFrom,*qTo;
{
   char *pFrom,*pTo;
   if (qTo) {
      pFrom=(char*)(qFrom<qTo ? qFrom:qTo);
      pTo=(char*)(qFrom>qTo ? qFrom:qTo);
   } else {
      pFrom=(char*)qFrom;
      pTo=(char*)qStr+strlen(qStr)-1;
   }

   return strmiddle(qStr,(int)(pFrom-qStr),(int)(pTo-pFrom)+1);
}

char *strmiddle( qStr,nIndex,nCount )
   const char *qStr;
   int nIndex,nCount;
{
   char *pNew;
   pNew=salloc(char,nCount+1);
   strncpy(pNew,qStr+nIndex,nCount);
   pNew[nCount]=0;
   return pNew;
}

char *strleft( str,divider )
   const char *str,*divider;
{
   char *p1,*p2;
   p1=p2=strstr(str,divider);
   if (!p1) return (char*)0;
   *p1=(char)0;
   p2=strdpl(str);
   *p1=*divider;
   return p2;
}

char *strright( str,divider )
   const char *str,*divider;
{
   char *p;
   p=strstr(str,divider);
   return (p) ? strdpl(p):(char*)0;
}

int strtokcount( qStr,qDelimiter ) /* 20030518-19 */
   const char *qStr,*qDelimiter;
{
   char *pStr=(char*)qStr;
   int nCount=0;
   while (pStr&&*pStr) {
      while (*pStr&&strchr(qDelimiter,(int)*pStr)) pStr++;
      if (*pStr&&!strchr(qDelimiter,(int)*pStr)) nCount++;
      while (*pStr&&!strchr(qDelimiter,(int)*pStr)) pStr++;
   }
   return nCount;
}

char *strtokbyindex( str,delimiter,nIndex ) /* nIndex=0,... */
   const char *str,*delimiter;
   int nIndex;
{
   char *pFrom=(char*)str,*pTo;
   int nTo;
   while (strchr(delimiter,(int)*pFrom)) pFrom++;
   while (nIndex--) {
      pFrom=strchrs(pFrom,(char*)delimiter);
      if (!pFrom) return (char*)0;
      while (strchr(delimiter,(int)*pFrom)) pFrom++;
   }
   pTo=strchrs(pFrom,(char*)delimiter);
   nTo=pTo ? (int)(pTo-pFrom-1):(int)strlen(pFrom);
   return strmid(pFrom,0,nTo);
}

char *strcommon( first,second,nStart )
   const char *first,*second;
   int nStart;
{
   int nTo=nStart;
   if (nStart<0) return 0;
   while (first[nTo]==second[nTo]) nTo++;
   return strmid(first,nStart,nTo-1);
}

char *strreverse( pString )
   const char *pString;
{
#if defined(_UNIXC_)
#error strreverse() is not ready in UNIXC.
   int nLength,nOffset;
   char cTemp;
   if (!pString) return pString;
   nLength=strlen(pString);
   nOffset=nLength%2+1;
   nLength>>=2;
   while (nLength--) {
      cTemp=pString[nLength];
      pString[nLength]=pString[nLength+nOffset];
      nOffset++;
   }
   return pString;
#elif defined(_MSVSC_)
   return _strrev((char*)pString); /* 20030308 */
   /* return (char*)_wcsrev((wchar_t*)pString); */
#else
#error (Y) Compiler type should be defined.
#endif
}

char *strinsert( ppStr,nIndex,qStr )
   char **ppStr;
   int nIndex;
   const char *qStr;
{
   int nLength,nLengthNew;
   nLength=(int)strlen(qStr);
   nLengthNew=(int)strlen(*ppStr)+nLength+1;
   *ppStr=myReAlloc(*ppStr,nLengthNew);
   memmove(*ppStr+nIndex+nLength,*ppStr+nIndex,
      nLengthNew-nLength-nIndex);
   strncpy(*ppStr+nIndex,qStr,nLength);
   return *ppStr;
}

char *strdelete( qString,nIndex,nCount )
   const char *qString;
   int nIndex,nCount;
{
   strcpy(
      (void*)((char*)qString+nIndex),
      (void*)((char*)qString+nIndex+nCount)
   );
   return (char*)qString;
}

char *strreplace( ppStr,qSrc,qDst )
   char **ppStr;
   const char *qSrc,*qDst;
{
   unsigned int nLength,nSrcLength,nDstLength,nCount;
   char *pAddr,*pReturn;

   nLength=(int)strlen(*ppStr);
   nSrcLength=(int)strlen(qSrc);
   nDstLength=(int)strlen(qDst);

   pAddr=*ppStr;
   nCount=0;
   while (pAddr=strstr(pAddr,qSrc)) {
      pAddr++;
      nCount++;
   }
   if (!nCount) return NULL;

   nCount=nLength+nCount*(nDstLength-nSrcLength);
   nCount=nCount>0 ? nCount+nLength:nLength; /* Y.Kim,20030212 */
   pAddr=pReturn=(char*)malloc(nCount+1);
   strcpy(pReturn,*ppStr);
   while (pAddr=strstr(pAddr,qSrc)) {
      strdel(pReturn,pAddr,strlen(qSrc));
      strins(pReturn,pAddr,qDst);
      pAddr+=nDstLength;
   }

   free(*ppStr);
   return *ppStr=pReturn;
}

char *strdel( str,pos,num )
   const char *str,*pos;
   size_t num;
{
   size_t len=strlen(str);

   if ((pos>=&str[len])
   ||  (num==0))
      return (char*)str;
   num=MIN(num,strlen(pos));
   if (num) {
      memcpy((char*)pos,&pos[num],strlen(&pos[num])+1);
   }
   return (char*)str;
}

char *strins( str,pos,ins )
   const char *str,*pos,*ins;
{
   size_t len=strlen(ins);
   char *tmp=(char*)&pos[len];

   memmove(tmp,pos,strlen(pos)+1);
   memmove((char*)pos,ins,len);
   return (char*)str;
}

char *strrep( str,src,dst )
   char *str,*src,*dst;
{
   char *strwork=str;
   size_t len=strlen(dst);

   while ((strwork=strstr(strwork,src))) {
      strdel(str,strwork,strlen(src));
      strins(str,strwork,dst);
      strwork+=len;
   }
   return str;
}

char *strchrs( str,chrs )
   const char *str,*chrs;
{
   char *ptr=(char*)str;
   size_t i,l; // y, 2016.3.28, size_t <-- int

   if (!ptr) return 0;
   if (!(l=strlen(chrs))) return 0;
   while (*ptr) {
      for (i=0;i<l;i++)
         if (*ptr==chrs[i])
            return ptr;
      ptr++;
   }
   return 0;
}

/*
char *strstr( s1,s2 )
    char *s1,*s2;
{
   register int i;

   while (*s1!='\0') {
      i=0;
      while (*s1++==s2[i++]) {
         if (i==strlen(s2)) return (s1-i);
      }
   }
   return NULL;
}
*/

char *strstrnocase( s1,s2 )
   const char *s1,*s2;
{
   char *s1New,*s2New,*ptr;

   if (!s1||!s2) return 0;
   s1New=strdpl(s1);
   s2New=strdpl(s2);
   strtolower(s1New);
   strtolower(s2New);
   ptr=strstr(s1New,s2New);
   free(s1New);
   free(s2New);
   return (char*)(ptr ? s1+(long)(ptr-s1New):0);
}

char *strrstr( s1,s2 ) /* not used yet , 990409,shik */
   const char *s1,*s2;
{
   char *p;
   int l2,i;

   if (!s1||!strlen(s1)) return 0;
   if (!s2||!strlen(s2)) return 0;
   l2=(int)strlen(s2)-1;
   for (p=(char*)s1+strlen(s1)-1;p>=s1;p--) {
      if (s2[l2]==*p) {
         i=l2;
         while (p>=s1 && i>=0 && s2[i--]==*p) p--;
         if (i<0) return ++p;
      }
   }
   return 0;
}

#if defined(_MSVSC_)
char *strvfromto( char *first, ... ) // char*,int,int,...,-1
{
   va_list ap;
   int from,to;
   size_t length;// y, 2016.3.28, size_t <-- int

   va_start(ap,first);
   length=strlen(first);
   while ((from=va_arg(ap,int))>0) {
      to=va_arg(ap,int);
      memmove(first+to,first+from,length-from+1);
   }
   va_end(ap);
   return (char*)first;
}
#elif defined(_UNIXC_) || defined(_HP715C_)
char *strvfromto( va_alist ) /* char*,int,int,...,NULL */
   va_dcl
{
   retunr (char*)0;
}
#else
#error (Y) Compiler type (_MSVSC_,_UNIXC_,...) should be defined.
#endif

char *strcpy2buf( buf,src,bufSize )
   char *buf;
   const char *src;
   int16u bufSize;
{
   int16u length=(int16u)strlen(src);// y, 2016.3.28, size_t <-- int

   if (length<bufSize)
      strcpy(buf,src);
   else {
      bufSize--;
      strncpy(buf,src,bufSize);
      buf[bufSize]=0;
   }
   return buf;
}

char *strdpl( str )
   const char *str;
{
   char *buf;

   if (!str||!*str) return (char*)0; /* 20030215 */
   buf=(char*)malloc(strlen(str)+1);
   if (!buf) return (char*)0;
   return strcpy(buf,str);
}

char *strdplwf( str,length,fillingChar,rightAlignment ) /* with filling character */
   char *str;
   int length;
   char fillingChar;
   int rightAlignment; /* -1=Left,0=Center,1=Right */
{
   char *ptr;
   register int i,j;

   ptr=salloc(char,length+1);
   memset(ptr,fillingChar,length);
   j=MIN(length,(int)strlen(str));
   switch (rightAlignment) {
   case  0 : /* later ... */
   case -1 : strncpy(ptr,str,j);
      break;
   case  1 : i=length-(int)strlen(str);
      if (i>0) strncpy(ptr+i,str,j);
      else if (i<0) strncpy(ptr,str-i,j);
      else strncpy(ptr,str,j);
      break;
   }
   return ptr;
}

#if defined(_MSVSC_)
char *strvcat( const char *first, ... ) // char*,char*,...,NULL
{
   va_list ap;
   int total=0,length=0,i;
   const char *table[256];
   char *pNew,*ptr;

   va_start(ap,first);
   if (!first) return (char*)0;
   length+=(int)strlen(first);
   table[total++]=first;
   i=noof(table);
   while (ptr=va_arg(ap,char*)) {
      length+=(int)strlen(ptr);
      table[total++]=ptr;
      if (total>=i) return (char*)0;
   }
   va_end(ap);
   pNew=ptr=salloc(char,length+1);
   for (i=0;i<total;i++) {
      strcpy(ptr,table[i]);
      ptr+=strlen(table[i]);
   }
   return pNew;
}
#elif defined(_UNIXC_) || defined(_HP715C_)
char *strvcat( va_alist ) /* char*,char*,NULL */
   va_dcl
{
   return (char*)0;
}
#else
#error Compiler type (_MSVSC_,_UNIXC_,...) should be defined.
#endif

char *strtolower( str )
   char *str;
{
   register char *p;
   p=str;
   while (*p) {
      *p=tolower(*p);
      p++;
   }
   return str;
}

char *strtoupper( str )
   char *str;
{
   register char *p;
   p=str;
   while (*p) {
      *p=toupper(*p);
      p++;
   }
   return str;
}

char *strescape( str )
   char *str;
{
   char *p;

   p=str;
   while (*p) {
      if (*p=='\\') {
         p++;
         switch (*p) {
         case 0    : return str;
         case 'b'  : *(p-1)='\b';break; /* backspace */
         case 'f'  : *(p-1)='\f';break; /* form-feed */
         case 'n'  : *(p-1)='\n';break; /* new-line */
         case 'r'  : *(p-1)='\r';break; /* carriage return */
         case 't'  : *(p-1)='\t';break; /* tab */
         case 'v'  : *(p-1)='\v';break; /* vertical tab */
         case '\'' : *(p-1)='\'';break; /* single quote character */
         case '\\' : *(p-1)='\\';break; /* backslash */
         }
         memmove(p,p+1,strlen(p));
         p--;
      }
      p++;
   }
   return str;
}

int strseq( str,strings,no )
   char *str,**strings;
   int no;
{
   register int i;

   for (i=0;i<no;i++)
     if (strequ(str,strings[i])) return 1;
   return 0;
}

/*
 * from "c shell" source code
 */
int strweq( qString, qFilter )
   const char *qString,*qFilter;
{
#define TRIM 0177
   register char *s=(char*)qString, *p=(char*)qFilter;
   register int scc;
   int ok, lc;
   int c, cc;

   for (;;) {
      scc = *s++ & TRIM;
      switch (c = *p++) {
         case '[': ok = 0;
                   lc = 077777;
                   while (cc = *p++) {
                      if (cc == ']') {
                         if (ok)
                            break;
                         return (0);
                      }
                      if (cc == '-') {
                         if (lc <= scc && scc <= *p++)
                            ok++;
                      } else
                         if (scc == (lc = cc))
                            ok++;
                   }
                   if (cc == 0)
                      return (0); /* missing ] */
                   continue;
         case '*': if (!*p)
                      return (1);
                   for (s--; *s; s++)
                      if (strweq(s, p))
                         return (1);
                   return (0);
         case 0:   return (scc == 0);
         default:  if ((c & TRIM) != scc)
                      return (0);
                   continue;
         case '?': if (scc == 0)
                      return (0);
                   continue;
      }
   }
#undef  TRIM
}

int strnweq( string,filter,length ) /* 990505 */
   char *string,*filter;
   int length;
{
   int chr,result;

   chr=string[length];
   string[length]=0;
   result=strweq(string,filter);
   string[length]=(char)chr;
   return result;
}

char *itostr( i,qFormat )
   int i;
   const char *qFormat;
{
   sprintf(qBuffer,qFormat,i);
   return strdpl(qBuffer);
}

char *itostr2( i,qFormat )
   int i;
   const char *qFormat;
{
   sprintf(qBuffer,qFormat,i);
   switch (i%3) {
   case 1 : strcat(qBuffer,"st");break;
   case 2 : strcat(qBuffer,"nd");break;
   case 3 : strcat(qBuffer,"rd");break;
   default : strcat(qBuffer,"th");
   }
   return strdpl(qBuffer);
}

char *dtostr( dNumber,qFormat ) /* 20030530.scientific form: eg) 0.1 -> "100m" */
   double dNumber;
   const char *qFormat;
{
   extern int order();
   char *pFormat,*pAddr,cUnitPrefix,qFmt[16];
   int i;

   pFormat=(char*)qFormat;
   for (pAddr=strchr(pFormat,'%')+1;
        *pAddr&&isnumchr(*pAddr);
        pAddr++);
   if (tolower(*pAddr)!='z') {
R:    sprintf(qBuffer,pFormat,dNumber);
   } else {
      i=order(dNumber);
      if (i>27||-24>i) { pFormat="%g";goto R; } /* 20030813 */
      else if (i>=24)  { cUnitPrefix='Y'; dNumber/=1e+24; } /* yotta */
      else if (i>=21)  { cUnitPrefix='Z'; dNumber/=1e+21; } /* zetta */
      else if (i>=18)  { cUnitPrefix='E'; dNumber/=1e+18; } /* exa */
      else if (i>=15)  { cUnitPrefix='P'; dNumber/=1e+15; } /* peta */
      else if (i>=12)  { cUnitPrefix='T'; dNumber/=1e+12; } /* tera */
      else if (i>=9)   { cUnitPrefix='G'; dNumber/=1e+09; } /* giga */
      else if (i>=6)   { cUnitPrefix='M'; dNumber/=1e+06; } /* mega */
      else if (i>=3)   { cUnitPrefix='K'; dNumber/=1e+03; } /* kilo */
      else if (i>=0)   { cUnitPrefix=0; }
      else if (i>=-3)  { cUnitPrefix='m'; dNumber/=1e-03; } /* milli */
      else if (i>=-6)  { cUnitPrefix='u'; dNumber/=1e-06; } /* micro */
      else if (i>=-9)  { cUnitPrefix='n'; dNumber/=1e-09; } /* nano */
      else if (i>=-12) { cUnitPrefix='p'; dNumber/=1e-12; } /* pico */
      else if (i>=-15) { cUnitPrefix='f'; dNumber/=1e-15; } /* femto */
      else if (i>=-18) { cUnitPrefix='a'; dNumber/=1e-18; } /* atto */
      else if (i>=-21) { cUnitPrefix='z'; dNumber/=1e-21; } /* zepto */
      else if (i>=-24) { cUnitPrefix='y'; dNumber/=1e-24; } /* yocto */
      else             { goto R; }
      memcpy(qFmt,pFormat,MIN(16,strlen(pFormat)+1));
      qFmt[pAddr-pFormat]=(pAddr-pFormat)>1 ? 'f':'g'; /* 20030803 */
      sprintf(qBuffer,qFmt,dNumber);
      i=(int)strlen(qBuffer);
      qBuffer[i++]=cUnitPrefix;
      qBuffer[i]=0;
   }
   if (pAddr=strchrs(qBuffer,"eE")) {
      pAddr++;
      if (*pAddr=='+') strdelete(pAddr,0,1); /* 20030811, while (issign(*pAddr)) pAddr++; */
      while (*pAddr=='0'&&strlen(pAddr)>1) strdelete(pAddr,0,1);
   }
   return strdpl(qBuffer);
}

char *dtostre( double dNumber, int nPrecision ) /* 20041226.engineering form: eg) 0.1 -> 1e-1 */
{
   char qFormat[16],qep0[]="e+0",qem0[]="e-0";
   sprintf(qFormat,"%%.%de",nPrecision);
   sprintf(qBuffer,qFormat,dNumber);
   strtolower(qBuffer);
   while (strstr(qBuffer,qep0)) strrep(qBuffer,qem0,"e");
   while (strstr(qBuffer,qem0)) strrep(qBuffer,qem0,"e-");
   return strdpl(qBuffer);
}

const char *dtos( dNumber,qFormat )
   double dNumber;
   const char *qFormat;
{
   char *pNumber=dtostr(dNumber,qFormat);
   strncpy(qBuffer,pNumber,1024);
   freeEx(pNumber);
   return qBuffer;
}

/* Dieter K. Schroder,"Semicondcutor Material and Device Characterization" */
static
struct {
   const char cPrefix;
   const double dValue;
} PREFIXES[] = {
   {'Y',1e+24},{'Z',1e+21},{'E',1e+18},{'P',1e+15},{'T',1e+12},{'G',1e+09},
   {'M',1e+06},{'K',1e+03},{'m',1e-03},{'u',1e-06},{'n',1e-09},{'p',1e-12},
   {'f',1e-15},{'a',1e-18},{'z',1e-21},{'y',1e-24}
};

double stod( qValue ) /* 20030417 */
   const char *qValue;
{
   double dValue;
   char *pAddr;
   int j;

   dValue=atof(qValue);
   pAddr=(char*)qValue;
   while (*pAddr&&isnumchr(*pAddr)) pAddr++;
   if (*pAddr) {
      for (j=0;j<sizeof(PREFIXES)/sizeof(PREFIXES[0]);j++) {
         if (*pAddr==PREFIXES[j].cPrefix) {
            dValue*=PREFIXES[j].dValue;
            break;
         }
      }
   }
   return dValue;
}

const char *c2ha( c )
   char c;
/*
 * "%02.2x"
 */
{
   register char b;

   b=(c&0x0f);
   qBuffer[1]=(b>9) ? b+'W':b+'0';
   c>>=4;
   b=(c&0x0f);
   qBuffer[0]=(b>9) ? b+'W':b+'0';
   qBuffer[2]='\0';
   return( qBuffer );
}

int ha2i( s )
   char *s;
{
   return (int)strtol(s,NULL,16);
/*
   ?
   int res=0,c;

   while (c=toupper(*s++)) {
      if (isdigit(c))
         res=(res<<4)|(c-'0');
      else if (c>='A'&&c<='F')
         res=(res<<4)|(c-'A'+10);
      else
         break;
   }
   return res;
*/
}

char **alloStrings( total )
   int total;
{
   return (char**)malloc(sizeof(char*)*total);
}

int freeStrings( strings,total )
   char **strings;
   int total;
{
   register int i;

   for (i=0;i<total;i++)
      if (strings[i])
         free(strings[i]);
   free(strings);
   return (1);
}

char **alloString1d( nrl,nrh )
   int nrl,nrh;
{
   char **s1d;
   int j;

   s1d=salloc(char *,j=(nrh-nrl+1));
   memset(s1d,0,j*sizeof(char*));
   if (!s1d)
      return (char**)0;
   s1d-=nrl;
   return s1d;
}

char ***alloString2d( nrl,nrh,ncl,nch )
   int nrl,nrh,ncl,nch;
{
   char ***s2d;
   int i,j;

   s2d=salloc(char **,j=(nrh-nrl+1));
   memset(s2d,0,j*sizeof(char*));
   if (!s2d)
      return (char ***)0;
   s2d-=nrl;
   for (i=nrl;i<=nrh;i++) {
      s2d[i]=salloc(char *,j=(nch-ncl+1));
      memset(s2d[i],0,j*sizeof(char*));
      if (!s2d[i])
         return (char ***)0;
      s2d[i]-=ncl;
   }
   return s2d;
}

int freeString1d( s1d,nrl,nrh )
   char **s1d;
   int nrl,nrh;
{
   register int i;

   if (!s1d) return FALSE;
   for (i=nrh;i>=nrl;i--) if (s1d[i]) freeEx(s1d[i]);
   free((char*)(s1d+nrl));
   return TRUE;
}

int freeString2d( s2d,nrl,nrh,ncl,nch )
   char ***s2d;
   int nrl,nrh,ncl,nch;
{
   register int i,j;

   if (!s2d) return FALSE;
   for (i=nrh;i>=nrl;i--) {
      if (!s2d[i]) continue;
      for (j=nch;j>=ncl;j--) if(s2d[i][j]) freeEx(s2d[i][j]);
      free((char*)(s2d[i]+ncl));
   }
   free((char*)(s2d+nrl));
   return TRUE;
}

char *string1dtostream( array,nl,nh,space ) // not used yet ..
   char **array;
   int nl,nh;
	char *space;
{
   int i,j,spaceLength,totalLength;
	char *pointer,*ptr;

   j=0; //???

	spaceLength=(int)strlen(space);
	totalLength=0;
	for (i=nl;i<=nh;i++)
		totalLength+=(int)strlen(array[i])+spaceLength;
	totalLength-=j;
   ptr=pointer=(char*)malloc(sizeof(char)*(totalLength+1));
	if (!pointer) {
		return (char*)0;
	}
	memset(pointer,' ',totalLength+1);
   for (i=nl;i<=nh;i++) {
		j=(int)strlen(array[i]);
		strncpy(ptr,array[i],j);
		ptr+=j;
		strncpy(ptr,space,spaceLength);
		if (i==nh) break;
		ptr+=spaceLength;
	}
	ptr[0]=0;
	if (ptr!=(pointer+totalLength+1)) {
		free(pointer);
		return (char*)0;
	}
	return pointer;
}

char *string2dtostream( matrix,nrl,nrh,ncl,nch,space,newLine )
   char ***matrix;
   int nrl,nrh,ncl,nch;
	char *space,*newLine;
{
	int i,j,spaceLength,newLineLength,totalLength;
	unsigned int *eachLength;
	char *pointer,*ptr;

	spaceLength=(int)strlen(space);
	newLineLength=(int)strlen(newLine);
	eachLength=(unsigned int*)malloc((i=sizeof(unsigned int)*(nch-ncl+1)));
	memset(eachLength,0,i);
	eachLength-=ncl;
	for (i=nrl;i<=nrh;i++) {
		for (j=ncl;j<=nch;j++) {
         eachLength[j]=MAX(eachLength[j],(int)strlen(matrix[i][j]));
		}
	}
	totalLength=0;
	for (j=ncl;j<=nch;j++)
		totalLength+=eachLength[j]+spaceLength;
	totalLength=(totalLength-spaceLength+newLineLength)*(nrh-nrl+1)-newLineLength;
	ptr=pointer=(char*)malloc(sizeof(char)*(totalLength+1));
	if (!pointer) {
		free(eachLength+ncl);
		return (char*)0;
	}
   memset(pointer,' ',totalLength+1);
   for (i=nrl;i<=nrh;i++) {
		for (j=ncl;j<=nch;j++) {
         strncpy(ptr,matrix[i][j],strlen(matrix[i][j]));
			ptr+=eachLength[j];
			if (j==nch) break;
			strncpy(ptr,space,spaceLength);
			ptr+=spaceLength;
		}
		if (i==nrh) break;
		strncpy(ptr,newLine,newLineLength);
		ptr+=newLineLength;
	}
	free(eachLength+ncl);
	ptr[0]=0;
	if (ptr!=(pointer+totalLength)) {
		free(pointer);
		return (char*)0;
	}
	return pointer;
}

int chrcount( const char *stream,char chr )
{
   int i=0;
   while (*stream) {
      if (*stream==chr) i++;
      stream++;
   }
   return i;
}

int strcount( const char *stream,const char* string )
{
   int nCount=0;
   char *pAddress;

   pAddress=strstr(stream,string);
   if (!pAddress) return 0;
   pAddress++;
   nCount++;
   while (*pAddress && (pAddress=strstr(pAddress,string))) {
      pAddress++;
      nCount++;
   }
   return nCount;
}

char *strdplwid( string,nID )
   const char *string;
   int nID;
{
   size_t j,k; // y, 2016.3.28, size_t <-- int
   char *ptr;

   j=strlen(string)+1;
   k=j+sizeof(int)+2; /* 2 -> double zero */
   ptr=salloc(char,k);
   strcpy(ptr,string);
   ptr[k-2]=0;
   ptr[k-1]=0;
   *(int*)(ptr+j)=(int)nID;
   return ptr; /* token + 0 + (int)nID + 00 */
}

char *strtrimwid( string )
   char *string;
{
   int ID=id_strwid(string),j;

   string=strtrim(string);
   j=(int)strlen(string)+1;
   *(int*)(string+j)=(int)ID;
   *(string+j+sizeof(int))=0;
   *(string+j+sizeof(int)+1)=0;
   return string;
}

int getintgerarray( qString,nArray,vArray )
   const char *qString;
   int *nArray,**vArray;
/*
 * in  : "1,3,4-9,10,11,12-13"
 * out : vArray[0-based]={1,3,4,5,6,7,8,9,10,11,12,13}
 */
{
   int iParity2=BIT(sizeof(int)*8-2);
   int nCol,*vCol,nIndex,nEnd,nCurrent;
   char *pAddr;

   *vArray=0;
   *vArray=0;

   nCol=chrcount(qString,',')+chrcount(qString,':')+1;
   vCol=salloc(int,nCol+1);
   for (nIndex=0,pAddr=(char*)qString;*pAddr;pAddr++) {
      switch (*pAddr) {
      case '0' : case '1' : case '2' : case '3' : case '4' :
      case '5' : case '6' : case '7' : case '8' : case '9' :
         vCol[nIndex++]=(int)atof(pAddr);
         skipdigit(&pAddr);
         pAddr--;
         break;
      case '-' :
         pAddr++;
         if (!*pAddr) goto R;
         nEnd=(int)atof(pAddr);
         nCurrent=ABS(vCol[nIndex-1]);
         if (nEnd<nCurrent) {
            free(vCol);
            *nArray=0;
            *vArray=0;
            return FALSE;
         } else if (nEnd>nCurrent) {
            nCol+=nEnd-nCurrent;
            vCol=realloc(vCol,nCol*sizeof(int));
            for (nCurrent++;nCurrent<=nEnd;nCurrent++) {
               vCol[nIndex++]=nCurrent;
            }
         } // else {}
         skipdigit(&pAddr);
         pAddr--;
         break;
      }
   }

R: *vArray=vCol;
   return (*nArray=nCol);
}

/******************************************************************************/
/* str.c */

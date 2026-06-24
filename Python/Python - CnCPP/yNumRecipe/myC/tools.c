/******************************************************************************/
/*                           file name : tools.c                              */
/*                         description : standard tools                       */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43230724                             */
/* 4323 0724-1231,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4324 0101-0421,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 1002,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0804,1031,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0320,0321,0418,0827,0913,____,____,____,____,____,____,____,____,____ */
/* 4330 0423,0831,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4331 0930,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0505,0708,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0222,0403-0529,0608,0622,0811-0828,1124,____,____,____,____,____,____ */
/* 4334 0219,0515,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0211-0216,0308,0529,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>

#include "myCore.h"
#include "nrecipe.h"
#include "number.h"
#include "any.h"
#include "str.h"
#include "tools.h"
#include "nr.h"

/******************************************************************************/

static char qBuf1024[1024+1];

/******************************************************************************/
/***********************************k*i*m**************************************/
/*****************************y*o*n*g*-*s*h*i*k********************************/
/******************************************************************************/

double dvalue( o )
   int o;
{
/*
   double d;
   float  f;

   d=pow10((double)o);
 * trick : 43250624 GY * 
   f=(float)d;   
   d=(double)f;
   return d;
*/
   char str[16];
   double d;

   sprintf(str,"1.00000e%d",o);
   d=atof(str);
   return d;
}

double atofEx( value,isLessThanZero )
   char *value;
   int isLessThanZero;
{
   char *p=value,c;
   double d;

   while (isnumchr(*p)) p++;
   c=*p;
   d=atof(value);
   if (isLessThanZero) {
      switch (tolower(c)) {
      case 'a' : d*=1e-18;break;
      case 'f' : d*=1e-15;break;
      case 'p' : d*=1e-12;break;
      case 'n' : d*=1e-09;break;
      case 'u' : d*=1e-06;break;
      case 'm' : d*=1e-03;break;
      }
   } else {
      switch (toupper(c)) {
      case 'K' : d*=1e+03;break;
      case 'M' : d*=1e+06;break;
      case 'G' : d*=1e+09;break;
      case 'T' : d*=1e+12;break;
      case 'P' : d*=1e+15;break;
      case 'E' : d*=1e+18;break;
      }
   }
   return d;
}

int order( d )
   double d;
{
   char str[16],*e;
   register int i;

   sprintf(str,"%1e",d);
   strtok(str,"e");
   e=strtok(NULL,"e");
   i=atoi(e);
   return(i);
}

double round( d )
   double d;
{
   if ((d-floor(d))>=0.5) return(ceil(d));
   else return(floor(d));
}

double orderCeil( d,o )
   double d;
   int o;
{
   register double dd,tmpo;

   tmpo=dvalue(o);
   d/=tmpo;
   dd=ceil(d);
   /* if (d==dd) dd+=1; 2K.0608 */
   return(dd*tmpo);
}

double orderFloor( d,o )
   double d;
   int o;
{
   register double dd,tmpo;

   tmpo=dvalue(o);
   d/=tmpo;
   dd=floor(d);
   /* if (d==dd) dd-=1; 2K.0608 */
   return(dd*tmpo);
}   

double stepRound( value,step )
   double value;
   double step;
{
   double r;

   r=value-round(value/step)*step;
   return value-r;
/*
   return step*floor((double)(value/step+0.5));
*/

/*
#define ABS(x) ((x)<0 ? (-(x)):(x))
   r=fmod(value,step);
   if (ABS(r)<=step/2)
      return value-r;
   else
      return step+value-r;
*/
}

int GetMtrxFrFile( qName,pMtx,pnRow,pnCol ) /* 2K.0527 */
   const char *qName;
   MATRIX *pMtx;
   int *pnRow,*pnCol;
/*
 * out : matrix[1..nRow][1..nCol]
 */
{
   /* 20030312 */
   return GetMtrxFrFileWithBlockIndex(qName,pMtx,pnRow,pnCol,0,0);
/*
#  define DLL_MAX_NO 2e4
   char *pStream,*pFrom,*pTo,*ptr,*qSkip=" ,'\"\\\t\f\n";
   int bResult;
   DLL **ppTable,*pList;
   DLN *node;
   int i,j,r=0,c=0;

   if (!(ppTable=salloc(DLL*,DLL_MAX_NO))) {
      errWarning("Error @GetMtrxFrFile(), DLL table allocation failure.");
      return FALSE;
   }

   bResult=myFileToStream(qName,&pStream);
   if (!bResult) {
      char *pTmp,qFolder[_MAX_PATH];
      _getcwd(qFolder,_MAX_PATH); * 20030216 *
      pTmp=strvcat(
         "Error @GetMtrxFrFile(),\n"
         "Stream allocation failure for : \n",qName,
         "\nCurrent directory is : \n",qFolder,
         0);
      errWarning(pTmp);
      free(pTmp);
      return FALSE;
   }

   pFrom=pStream;
   pTo=strchr(pFrom,'\n');
   while (pTo && *pTo) {
      ptr=strmid((const char*)pFrom,0,pTo-pFrom);
      pFrom=pTo+1;
      strtrim(ptr);
      if (!isnumstr(ptr)) goto Next;
      DLLOpen(&pList);
      DLLAddTokensWMA(pList,ptr,qSkip);
      ppTable[r]=pList;
      r++;
      c=MAX(c,pList->total);
      if (r>=DLL_MAX_NO) {
         free(ptr);
         errWarning(
            "Warning @GetMtrxFrFile(), Matrix-Row(Line) > DLL_MAX_NO(2e4).");
         return FALSE;
      }
Next: free(ptr);
      pTo=strchr(pFrom,'\n');
      if (!pTo) {
         pTo=*pFrom ? pFrom+strlen(pFrom)-1:0;
      }
   }

   free(pStream);

   *pMtx=dmatrix(1,r,1,c);
   *pnRow=r;
   *pnCol=c;
   for (i=1;i<=r;i++) {
      for (j=1;j<=c;j++) {
         node=ppTable[i-1]->head;
         while (node) {
            if (isnumchr(*node->tok))
               (*pMtx)[i][j]=atof(node->tok); 
            else 
               MkNaNDouble((*pMtx)[i][j]);
            node=node->next;
            j++;
         }
         for (;j<=c;j++)
               MkNaNDouble((*pMtx)[i][j]);
         DLLCloseWMA(ppTable[i-1]);
      }
   }

   * 20030307 *
   for (j=c;j>=1;j--) {
      for (i=1;i<=r && IsNaNDouble((*pMtx)[i][j]);i++);
      if (i>r) *pnCol--;
   }

   free(ppTable);
   return *pnRow**pnCol;
#  undef DLL_MAX_NO
*/
}

int GetMtrxFrFileWithBlockIndex( /* 20030311 */
    const char *qName,
    MATRIX *pMtx,int *pnRow,int *pnCol,
    int nBlockIndex,int *vBlockIndex /* 0-based index */
)
{
#  define DLL_MAX_NO 2e4
   char *pStream,*pFrom,*pTo,*pAddr,*qSkip=" ,'\"\\\t\f\n";
   int bResult,nBlockCount,bBlockFound;
   DLL **ppTable,*pList;
   DLN *pNode;
   int iR,iC,nRow=0,nCol=0;

   if (!(ppTable=salloc(DLL*,DLL_MAX_NO))) {
      errWarning("Error @GetMtrxFrFile(), DLL table allocation failure.");
      return FALSE;
   }

   bResult=myFileToStream(qName,&pStream);
   if (!bResult) {
      char *pTmp,qFolder[_MAX_PATH];
      _getcwd(qFolder,_MAX_PATH); /* 20030216 */
      pTmp=strvcat(
         "Error from GetMtrxFrFileWithBlockIndex(),\n"
         "Stream allocation failure for : \n",qName,
         "\nCurrent directory is : ",qFolder," ",
         0);
      errWarning(pTmp);
      free(pTmp);
      return FALSE;
   }

   nBlockCount=0;
   bBlockFound=-1; /* unchecked state */
   pFrom=pStream;
   pTo=strchr(pFrom,'\n');
   while (pTo && *pTo) {
      pAddr=strmid((const char*)pFrom,0,pTo-pFrom);
      pFrom=pTo+1;
      strtrim(pAddr);
      if (isnumstr(pAddr)) {
         if (bBlockFound==-1) {
            if (nBlockIndex && vBlockIndex) {
               nBlockCount++;
               bBlockFound=
                  IsInIntVector(nBlockCount,vBlockIndex,0,nBlockIndex-1);
            } else
               bBlockFound=TRUE;
         }
         if (bBlockFound==TRUE) {
            DLLOpen(&pList);
            DLLAddTokensWMA(pList,pAddr,qSkip);
            ppTable[nRow]=pList;
            nRow++;
            nCol=MAX(nCol,pList->total);
            if (nRow>=DLL_MAX_NO) {
               free(pAddr);
               errWarning(
                  "Warning from GetMtrxFrFileWithBlockIndex(), \n"
                  "Matrix-Row(Line) > DLL_MAX_NO(2e4).");
               return FALSE;
            }
         }
      } else {
         free(pAddr);   
         bBlockFound=-1; /* being left unchecked */
      }
      pTo=strchr(pFrom,'\n');
      if (!pTo) pTo=*pFrom ? pFrom+strlen(pFrom)-1:0;
   }

   free(pStream);

   *pMtx=dmatrix(1,nRow,1,nCol);
   *pnRow=nRow;
   *pnCol=nCol;
   for (iR=1;iR<=nRow;iR++) {
      for (iC=1;iC<=nCol;iC++) {
         pNode=ppTable[iR-1]->head;
         while (pNode) {
            if (isnumchr(*pNode->tok))
               (*pMtx)[iR][iC]=atof(pNode->tok); 
            else 
               MkNaNDouble((*pMtx)[iR][iC]);
            pNode=pNode->next;
            iC++;
         }
         for (;iC<=nCol;iC++)
               MkNaNDouble((*pMtx)[iR][iC]);
         DLLCloseWMA(ppTable[iR-1]);
      }
   }

   /* 20030307 */
   for (iC=nCol;iC>=1;iC--) {
      for (iR=1;iR<=nRow && IsNaNDouble((*pMtx)[iR][iC]);iR++);
      if (iR>nRow) (*pnCol)--; /* 20030529 */
   }

   free(ppTable);
   return *pnRow**pnCol;
#  undef DLL_MAX_NO
}

int GetMtrxFrFileEx( qName,pMatrix,pnRow,pnCol,pppHeader,pnHeaderCount )
   /* in */
   const char *qName;
   /* out */
   MATRIX *pMatrix;
   int *pnRow,*pnCol;
   char ***pppHeader;
   int *pnHeaderCount;
{
#  define DLL_MAX_NO 10000
   char *pStream,*pFrom,*pTo,*pAddr,*qSkip=" \\\t\f\n",*p0,*p1;
   int bResult;
   DLL **ppTable,*pList;
   DLN *pNode;
   int i,j,r,c;

   *pMatrix=0;
   *pnRow=*pnCol=0;
   *pppHeader=0;
   *pnHeaderCount=0;

   ppTable=salloc(DLL*,DLL_MAX_NO);
   if (!ppTable) {
      errWarning("Error @GetMtrxFrFileEx(), <table> alloc. failure !");
      return FALSE;
   }

   bResult=myFileToStream(qName,&pStream);
   if (!bResult) {
      errWarning("Error @GetMtrxFrFileEx(), <stream> alloc. failure !");
      free(ppTable);
      return FALSE;
   }

   r=c=0;
   pFrom=pStream;
   pTo=strchr(pFrom,'\n');
   while (pTo && *pTo) {
      pAddr=strmid((const char*)pFrom,0,pTo-pFrom);
      pFrom=pTo+1;
      //strtrim(pAddr);
      p0=strtokbyindex(pAddr,qSkip,0);
      p1=strtokbyindex(pAddr,qSkip,1);
      if (!p0 || !*p0 || !p1 || !*p1) goto Next;
      if (isnumstr(p0)||!isnumstr(p1)) goto Next;
      DLLOpen(&pList);
      DLLAddTokensWMA(pList,pAddr,qSkip);
      ppTable[r]=pList;
      r++;
      c=MAX(c,pList->total);
      if (r>=DLL_MAX_NO) {
         free(pAddr);
         errWarning("matrix-row > DLL_MAX_NO in GetMtrxFrFileEx()");
         return FALSE;
      }
Next: free(pAddr);
      pTo=strchr(pFrom,'\n');
      if (!pTo) {
         pTo=*pFrom ? pFrom+strlen(pFrom)-1:0;
      }
   }

   free(pStream);

   if (!r) return FALSE; /* Y.Kim,20030211 */
   
   c--; /* for the 1st column of Header */
   *pMatrix=dmatrix(1,r,1,c);
   *pnRow=r;
   *pnCol=c;
   *pppHeader=salloc(char*,r);
   *pnHeaderCount=r;

   for (i=1;i<=r;i++)
      for (j=1;j<=c;j++) {
         pNode=ppTable[i-1]->head;
         (*pppHeader)[i-1]=strdpl(pNode->tok);
         pNode=pNode->next;
         while (pNode) {
            if (isnumchr(*pNode->tok))
               (*pMatrix)[i][j]=atof(pNode->tok); 
            else 
               MkNaNDouble((*pMatrix)[i][j]);
            pNode=pNode->next;
            j++;
         }
         for (;j<=c;j++)
               MkNaNDouble((*pMatrix)[i][j]);
         DLLCloseWMA(ppTable[i-1]);
      }

   free(ppTable);
   return *pnRow**pnCol;
#  undef DLL_MAX_NO
}

int GetMtrxFrFileEx2( qName,nrl,nrh,ncl,nch,pMtx )
   const char *qName;
   int nrl,nrh,ncl,nch;
   MATRIX *pMtx;
{
   FILE *in;
   char *sBuffer,*qSkip=" ,'\"\\\t\f\n";
   int nBuffer,nri,nci,i,j,done;
   DLL *dll;
   DLN *dln;

   in=fopen(qName,"r");
   if (!in) {
      sprintf(qBuf1024,"\" %s \" file opening in GetMtrxFrFileEx2()",qName);
      errExit(qBuf1024);
   }
   sBuffer=0;
   i=1;
   do {
      nBuffer=1024*i++;
      freeEx(sBuffer);
      sBuffer=salloc(char,nBuffer);
      fgets(sBuffer,nBuffer,in);
   } while (!strchr(sBuffer,'\n'));
   fseek(in,0,SEEK_SET);

   *pMtx=dmatrix(nrl,nrh,ncl,nch);

   nri=nrl-1;
   nci=ncl-1;
   done=FALSE;
   EVERLOOPBEG;
      if (!fgets(sBuffer,nBuffer,in)) break;
      DLLOpen(&dll);
      if (!DLLAddTokens(dll,sBuffer,qSkip))
         continue;
      if (!isnumstr(dll->head->tok)) {
         DLLClose(dll);
         continue;
      }
      done=TRUE;
      if (nrh<++nri) break;
      dln=dll->head;
      do {
         if (nch<++nci) break;

         if (isnumchr(*(dln->tok)))
            (*pMtx)[nri][nci]=atof(dln->tok);
         else 
            MkNaNDouble(((*pMtx)[nri][nci]));
      } while(dln=dln->next);
         if (nci<nch)
            for (i=nci+1;i<=nch;i++)
               MkNaNDouble(((*pMtx)[nri][i]));
         nci=ncl-1;
      DLLClose(dll);
   EVERLOOPEND;
      if (nri<nrh)
         for (i=nri+1;i<=nrh;i++)
            for (j=ncl;j<=nch;j++)
               MkNaNDouble(((*pMtx)[i][j]));

   free(sBuffer);
   fclose(in);

   if (!done) {
      sprintf(qBuf1024,"\" %s \" file structure in GetMtrxFrFileEx2()",qName);
      errExit(qBuf1024);
   }
   return (1);
}

/* 20030222 */
int GetMtrxRowColFrFile(
   const char *qName,int *pnRow,int *pnCol
   )
{
   DLL *pList;
   char *pStream,*pFrom,*pTo,*pAddr,*qSkip=" ,'\"\\\t\f\n";
   int bResult;

   *pnRow=*pnCol=0;
   bResult=myFileToStream(qName,&pStream);
   if (!bResult) return FALSE;
   pFrom=pStream;
   pTo=strchr(pFrom,'\n');
   while (pTo && *pTo) {
      pAddr=strmid((const char*)pFrom,0,pTo-pFrom);
      pFrom=pTo+1;
      strtrim(pAddr);
      if (isnumstr(pAddr)) {
         (*pnRow)++;
         DLLOpen(&pList);
         DLLAddTokensWMA(pList,pAddr,qSkip);
         *pnCol=MAX(*pnCol,pList->total);
         DLLCloseWMA(pList);
      }
      free(pAddr);
      pTo=strchr(pFrom,'\n');
      if (!pTo) {
         pTo=*pFrom ? pFrom+strlen(pFrom)-1:0;
      }
   }
   free(pStream);
   return *pnRow**pnCol;
}

int GetMtrxPropertyFrFile( qName,bVertical,bLogarithm,pnRow,pnCol,pVMin,pVMax )
   const char* qName;
   int bVertical,bLogarithm,*pnRow,*pnCol;
   VECTOR *pVMin,*pVMax;
{
   MATRIX Mtx;
   int nIndex;
   double dMin,dMax;

   *pnRow=*pnCol=0;
   GetMtrxFrFile(qName,&Mtx,pnRow,pnCol);
   if (bVertical) {
      *pVMin=dvector(1,*pnCol);
      *pVMax=dvector(1,*pnCol);
      for (nIndex=1;nIndex<=*pnCol;nIndex++) {
         MGetMinMaxValue(Mtx,bVertical,nIndex,1,*pnRow,bLogarithm,&dMin,&dMax);
         (*pVMin)[nIndex]=dMin;
         (*pVMax)[nIndex]=dMax;
      }
   } else {
      exit(1);
   }
   free_dmatrix(Mtx,1,*pnRow,1,*pnCol);
   return *pnRow**pnCol;
}

int IsInIntVector( int iValue,int *pVec,int nl,int nh )
{
   int j;
   for (j=nl;j<=nh;j++) {
      if (iValue==pVec[j]) return TRUE;
   }
   return FALSE;
}

int myFopen() /* create if not exist */
{
	return (1);
}

int myFclose()
{
 	return (1);
}

int myFread()
{
	return (1);
}

int myFwrite()
{
	return (1);
}

long myFtellsize( file )
   FILE *file;
{
   long back,beg,end;

   back=ftell(file);
   fseek(file,0L,0);
   beg=ftell(file);
   fseek(file,0L,2);
   end=ftell(file);
   fseek(file,back,0);
   return(end-beg+1);
}

int myOpen( name,nHandle ) /* create if not exist */
   char *name;
   int *nHandle;
{
   *nHandle=open(name,F_OPENMODE);
   if (*nHandle==INVALID) {
      *nHandle=creat(name,F_CREATEMODE);
      if (*nHandle==INVALID) return FALSE;
      close(*nHandle);
      *nHandle=open(name,F_OPENMODE);
   }
   return TRUE;
}

int myClose( nHandle )
   int nHandle;
{
   return close(nHandle);
}

int myRead( nHandle,pos,ptr,size )
   int nHandle;
   long pos;
   char *ptr;
   int size;
{
   lseek(nHandle,pos,0);
   return read(nHandle,ptr,size);
}

int myWrite( nHandle,pos,ptr,size )
   int nHandle;
   long pos;
   char *ptr;
   int size;
{
   lseek(nHandle,pos,0);
   write(nHandle,ptr,size);
   return (1);
}

long myTellsize( nHandle )
   int nHandle;
{
   long back,beg,end;

   back=tell(nHandle);
   lseek(nHandle,0L,0);
   beg=tell(nHandle);
   lseek(nHandle,0L,2);
   end=tell(nHandle);
   lseek(nHandle,back,0);
   return(end-beg+1);
}

int myFileToStream( sFileName,ppStream )
   const char *sFileName;
   char **ppStream;
{
   int f,fsize,i;
   char *ptr;

   *ppStream=0;
   if ((f=open(sFileName,O_RDONLY))==-1)
      return FALSE;
   fsize=myTellsize(f);
   if (!(ptr=(char*)malloc(sizeof(char)*fsize)))
      return FALSE;
   i=read(f,ptr,fsize-1);
   ptr[i+0]=(char)0;
   *ppStream=ptr;
   close(f);
   while (i--) {
      if (!*ptr) *ptr=' ';
      ptr++;
   }
   return TRUE;
}

int myFileToStreamEx( sFileName,nReadOut,ppStream )
   const char *sFileName;
   int nReadOut;
   char **ppStream;
{
   int f,fsize,i;
   char *ptr;

   if ((f=open(sFileName,O_RDONLY))==-1)
      return FALSE;
   fsize=(nReadOut>0) ? nReadOut:myTellsize(f);
   if (!(ptr=(char*)malloc(sizeof(char)*fsize)))
      return FALSE;
   i=read(f,ptr,fsize-1);
   ptr[i+0]=(char)0;
   *ppStream=ptr;
   close(f);
   while (i--) {
      if (!*ptr) *ptr=' ';
      ptr++;
   }
   return TRUE;
}

int myStreamToFile( qFileName,qStream )
   const char *qFileName,*qStream;
{
   int nHandle;
   if (!myOpen(qFileName,&nHandle))
      return FALSE;
   myWrite(nHandle,0,qStream,strlen(qStream));
   myClose(nHandle);
   return TRUE;
}

long myStrLseek( fid,str )
   int fid;
   char *str;
{
   long back,pos;
   int i;
   char l=strlen(str),*ptr;

   back=tell(fid);
   while ((i=read(fid,qBuf1024,1024))>l) {
      if (ptr=strstr(qBuf1024,str)) break;
      lseek(fid,-l,1);
   }
   pos=tell(fid);
   pos=(pos-1024L>0) ? pos-1024L : pos-(long)i;
   pos=(ptr) ? pos+(long)(ptr-(char*)&(qBuf1024[0])) : INVALID;

   lseek(fid,back,0);
   return pos;
}

char *myGetCurrentDirName()
{
#if defined(_MSC_)
   char buffer[_MAX_PATH];

   if( _getcwd(buffer,_MAX_PATH)==NULL) perror( "_getcwd error" );
   return strdpl(buffer);
#else
   return NULL;
#endif
}

int myGetDirectoryFileNames( directory,names )
   char *directory; /* if null, get the files at the current directory */
   char ***names;
{
#if defined(_MSC_)
   char buffer[_MAX_PATH],*ptr;
   long nHandle;
   struct _finddata_t findData;
   register int i,total;

   if (directory)
      strcpy(buffer,directory);
   else {
      ptr=myGetCurrentDirName();
      strcpy(buffer,ptr);
      free(ptr);
   }
   i=strlen(buffer);
   if ((i+3)<=_MAX_PATH) {
      buffer[i++]='\\';
      buffer[i++]='*';
      buffer[i]=(char)0;
   }
   total=0;
   nHandle=_findfirst(buffer,&findData);
   while (!_findnext(nHandle,&findData))
      if (findData.attrib==_A_ARCH) total++;
   _findclose(nHandle);
   i=1;
   *names=alloString1d(i,total);
   nHandle=_findfirst(buffer,&findData);
   while (!_findnext(nHandle,&findData))
      if (findData.attrib==_A_ARCH) (*names)[i++]=strdpl(findData.name);
   _findclose(nHandle);   
   return total;
#else
   *names=NULL;
   return 0;
#endif
}

int myDoesFileExist( qFile )
   const char *qFile;
{
   FILE *pFile;
   
   pFile=fopen(qFile,"r");
   if (!pFile) return FALSE;
   fclose(pFile);
   return TRUE;
}

char *get_relative_path( qRefPath,qPath )
   const char *qRefPath,*qPath; /* must be full path and folder only */
{
   int nIndex,nRefPath,nPath,nCount;
   char *pRefPath,*pPath,*pNew;
   const char *qFolder="\\";
   const char *qDoubleDot="..";

   if (!qRefPath || !*qRefPath) return (char*)0;
   if (!qPath || !*qPath) return (char*)0;
   if (qRefPath[0]==*qFolder) return  (char*)0;
   if (qPath[0]==*qFolder) return  (char*)0;

   pRefPath=strdpl(qRefPath);
   pPath=strdpl(qPath);
   strtolower(pRefPath); /* 20030308 */
   strtolower(pPath); /* 20030308 */
   strtrim(pRefPath);
   strtrim(pPath);
   nRefPath=strlen(pRefPath);
   nPath=strlen(pPath);
   if (pRefPath[nRefPath-1]==qFolder[0]) pRefPath[--nRefPath]=0;

   nCount=MIN(nRefPath,nPath);
   for (nIndex=0;nIndex<nCount;nIndex++) {
      if (pRefPath[nIndex]!=pPath[nIndex]) break;
   }
   if (!nIndex) return (char*)0;

   strcpy(pRefPath,pRefPath+nIndex);
   if (nIndex==nRefPath) { /* Reference path is shallower than or
                            * equal to the path. */
      freeEx(pRefPath);
      strcpy(pPath,pPath+nIndex);
      if (pPath[0]==qFolder[0]) strcpy(pPath,pPath+1);
      return pPath;
   }
   nCount=strcount(pRefPath,qFolder)+1;
   freeEx(pRefPath);
   if (strlen(pPath)>=(unsigned)nIndex) strcpy(pPath,pPath+nIndex);

   pRefPath=salloc(char,nCount*(strlen(qFolder)+strlen(qDoubleDot))+1);
   nIndex=0;
   while (nCount-->0) {
      strcpy(pRefPath+nIndex,qDoubleDot);
      nIndex+=strlen(qDoubleDot);
      strcpy(pRefPath+nIndex,qFolder);
      nIndex+=strlen(qFolder);
   }

   pNew=strvcat(pRefPath,pPath,0);
   freeEx(pRefPath);
   freeEx(pPath);
   return pNew;
}

char *yGetShortPath( qPath,nLength )
   const char *qPath;
   int nLength;
{
   char *pPath,*sDivider="\\:";
   char *p0,*p1,*p2;
   int l,m,dummy=3;

   pPath=strdpl(qPath); /* 20030529 */
   l=strlen(pPath);
   if (l<nLength) return (char*)pPath;
   m=0;
   p0=p1=strchrs(pPath,sDivider);
   while ((l-m)>nLength) {
      p1++;
      p2=strchrs(p1,sDivider);
      //if (!p2) return (char*)0;
      if (!p2) { /* 20030911AM03:07 -_- */
         p2=p1-1;
         break;
      }
      m=p2-p0-dummy;
      p1=p2;
   }
   memcpy(p0+dummy+1,p2,strlen(p2)+1);
   for (m=1;m<=dummy;m++)
      p0[m]='.';
   return (char*)pPath;
}

char *yGetFolderFromFullPath( /* 20030308 */
   const char *qPath,int nLength
)
{
   char *pPath,*sDivider="\\:",*pAddr;

   pPath=strdpl(qPath); /* 20030529 */
   if (nLength<=0) return pPath;
   strreverse(pPath);
   pAddr=strchrs(pPath,sDivider);
   if (pAddr) strcpy((char*)pPath,pAddr);
   strreverse(pPath);
   return pPath;
}

int mySigHandle()
{
/*
   void (*istat)(),(*fstat),(*tstat)();

   istat = signal(SIGINT,SIG_IGN);
   fstat = signal(SIGFPE,SIG_IGN);
   tstat = signal(SIGTERM,SIG_IGN);

   setjmp( signalbuf );

   if (istat!=SIG_IGN) signal(SIGINT,sysExit);
   if (fstat!=SIG_IGN) signal(SIGFPE,sysExit);
   if (tstat!=SIG_IGN) signal(SIGTERM,sysExit);
*/
   return (1);
}

void myExit()
{
   fprintf(stderr,"\n");
   fprintf(stderr,"tools.c:(c)Y.S.Kim,%s\n",__VERSION__);
   fprintf(stderr,"\n");
   exit(1); /* in sysExit() */
}

/******************************************************************************/

/* getopt.c - get command line options
 *
 * Parse the command line options, System V style.
 *
 * Standard option syntax is:
 *
 *         option = -[optLetter,...][argLetter argument]
 *
 * where
 *    - there is no space between the '-' and optLetters or argLetters.
 *    - optLetters and argLetters are alphabetic, not punctuation characters.
 *    - optLetters, if present, must be matched in options.
 *    - argLetters, if present, are found in options followed by ':'.
 *    - argument is any white-space delimited string.  Note that it can
 *      include the '-'.
 *    - upper and lower case letters are distinct.
 *
 * There may be multiple option clusters on a command line, each
 * beginning with a '-', but all must appear before any non-option
 * arguments (arguments not introduced by a '-'). optLetters and
 * argLetters may be repeated, it is up to the caller to decide
 * if that is an error.
 *
 * The character '-' appearing alone as the last argument is an error.
 * The lead-in sequence '--' causes itself and all the rest of the
 * line to be ignored (allowing non-options which begin with '-'.
 *
 * The string *options allows valid optLetters and argLetters to be
 * recognized.               argLetters are followed with ':'.  getopt() returns the
 * value of the option character found, or EOF if no more options are in
 * the command line.    If option is an argLetter then the global optarg is
 * set to point to the argument string (having skipped any white-space).
 *
 * The global optind is initially 1 and is always left as the index
 * of the next argument of argv[] which getopt has not taken.      Note
 * that if '--' is used then optind is stepped to the next argument
 * before getopt() returns EOF.
 *
 * If an error occurs, that is '-' precedes an unknown letter, then
 * getopt() will return a '?' character and normally prints an error
 * message via perror().        If the global variable opterr is set to
 * false (zero) before calling getopt() then the error message is
 * not printed.
 *
 * For example, if
 *
 *         *options == "A:F:PuU:wXZ:"
 *
 * then 'P', 'u', 'w', and 'X' are option letters and 'F', 'U', 'Z'
 * are followed by arguments.     A valid command line may be:
 *
 *     command  -uPFPi -X -A L otherparameters
 *
 * where:
 *      - 'u' and 'P' will be returned as isolated option letters.
 *    - 'F' will return with "Pi" as its argument string.
 *    - 'X' is an isolated option.
 *    - 'A' will return with "L" as its argument.
 *    - "otherparameters" is not an option, and terminates getOpt.  The
 *      caller may collect remaining arguments using argv pointers.
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>

int   optind  = 1;    /* index of which argument is next */
char *optarg;         /* pointer to argument of current option */
int   opterr  = 1;    /* allow error message  */

static char *letP = NULL;    /* remember next option char's location */

int getopt( int argc, char *argv[], char *options )
{
   unsigned char ch;
   char *optP;
   
   if (argc > optind) {
      if (letP == NULL) {
         if ((letP = argv[optind]) == NULL ||
            *(letP++) != '-')  goto gopEOF;
         if (*letP == '-') {
            optind++;  goto gopEOF;
         }
      }
      if (0 == (ch = *(letP++))) {
         optind++;  goto gopEOF;
      }
      if (':' == ch  ||  (optP = strchr(options, ch)) == NULL)
         goto gopError;
      if (':' == *(++optP)) {
         optind++;
         if (0 == *letP) {
            if (argc <= optind)  goto  gopError;
            letP = argv[optind++];
         }
         optarg = letP;
         letP = NULL;
      } else {
         if (0 == *letP) {
            optind++;
            letP = NULL;
         }
         optarg = NULL;
      }
      return ch;
   }
gopEOF:
   optarg = letP = NULL;
   return EOF;

gopError:
   optarg = NULL;
   errno  = EINVAL;
   if (opterr)
      perror ("getopt()");
   return ('?');
}

/******************************************************************************/

#if defined(_UNIXC_)
#include <dirent.h>

int GetDLLOfFile( directory,list )
   char *directory;
   DLL  **list;
{
   char *path,*filter,*ptr;
   DIR *dir;
   struct dirent *ent;
   DLN *node;

   path=qBuf1024;
   strcpy(path,directory);

   if (strpbrk(path,"*?")) {
      filter=strrchr(path,'/');
      if (filter)
         *(filter++)='\0';
      else
         filter=path;
      filter=strdpl(filter);
   } else {
      filter=strdpl("*");
   }

   if (dir=opendir(path)) {
      openAnyDLObject(list,sizeof(DLL));
      (*list)->total=0;
      ptr=path+strlen(path);
      for (ent=readdir(dir);
           ent;
           ent=readdir(dir)) {
         if (strweq(ent->d_name,filter)) {
            node=salloc(DLN,1);
            sprintf(ptr,"/%s",ent->d_name);
            node->tok=strdpl(path);
            AddAnyDLObject(*list,node);
            ((*list)->total)++;
         }
      }
      closedir(dir);
      free(filter);
      return TRUE;
   } else {
      *list=NULL;
      free(filter);
      return FALSE;
   }
}

int GetDLLOfFile_()
{
}

#endif

/******************************************************************************/

int endTest()
{
   short s;

   s=0x1234;
   if (((char*)&s)[0]==0x12
   &&  ((char*)&s)[1]==0x34) {
      printf("Big-Endian ...\n");
   } else if (((char*)&s)[1]==0x12
          &&  ((char*)&s)[0]==0x34) {
      printf("Little-Endian ...\n");
   }
   return (1);
}

/******************************************************************************/

char *CurrentKoreanDate( type )
   int type; /* 0 : Korean Classic Date, 1 : Jejus Date */
{
   struct tm *tm_now;
   time_t secs_now;

   type=type ? type:type+2333+1900;
   time(&secs_now);
   tm_now=localtime(&secs_now);
   sprintf(qBuf1024,"%04d%02d%02d",
           tm_now->tm_year+type,(tm_now->tm_mon)+1,tm_now->tm_mday);
   return qBuf1024;
}

char *CurrentDateAndTime()
{
   struct tm *tm_now;
   time_t secs_now;

   time(&secs_now);
   tm_now=localtime(&secs_now);
   sprintf(qBuf1024,"%02d.%02d.%02d.%02d:%02d",
           tm_now->tm_year+1900,(tm_now->tm_mon)+1,tm_now->tm_mday,
           tm_now->tm_hour,tm_now->tm_min);
   return qBuf1024;
}

/******************************************************************************/
/* tools.c */

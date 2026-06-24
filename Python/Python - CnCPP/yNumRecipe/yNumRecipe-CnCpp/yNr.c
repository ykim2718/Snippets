/******************************************************************************

       File: yNr.c
Description: Numerical Recipes in C
    Creator: ...
       Date: 43261120
   Revision: Kim, Yongshik (copyRight)
     Update: 43320225,0720
             43330530,0622
Last Update: 20160325

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

/******************************************************************************/

#include "yCore.h"
#include "ynumber.h"
#include "ynrecipe.h"
#include "ynr.h"

#define float double /* 990720(c)shik */

#ifdef MIN
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif

#undef EXTRACOMPILATION

/******************************************************************************/
/******************************************************************************/

/*

               NUMERICAL RECIPES C DISKETTE V1.0
               --------- ------- - -------- ----
            The entire contents of this diskette are
       Copyright (C) 1985, 1987 by Numerical Recipes Software
               P.O. Box 243, Cambridge, MA  02238
         Unauthorized reproduction is strictly prohibited.

Please read this document completely before attempting to use the NUMERICAL
RECIPES C DISKETTE.  Your use of any computer procedures on this diskette
constitutes acceptance of the terms of the DISCLAIMER OF WARRANTY, which is
given in full at the end of this document.

WHAT IS THIS DISKETTE?

     This diskette contains machine-readable source code for the C functions
in the book "Numerical Recipes in C: The Art of Scientific Computing" published
by Cambridge University Press (1988).  If you do not have the book, this
diskette will not be very useful to you, since the code on this diskette does
not include the book's explanations or line-by-line program comments.  Details
on how to order the book are given at the end of this document.

WHAT PROGRAMS ARE ON THIS DISKETTE?

     All 205 functions listed in "Numerical Recipes: The Art of Scientific
Computing" are included as C source code on this diskette.  Also on this
diskette are the following supplementary files:

     -- NRUTIL.C  short utilities for error reporting, and vector
        and matrix memory allocation.  These are used by other programs
        on this diskette.

     -- NRUTIL.H  the header declarations file corresponding to NRUTIL.C

     -- COMPLEX.C  utilities for complex arithmetic that are used by a
        few programs on this diskette.

     -- COMPLEX.H  the header declarations file corresponding to COMPLEX.C

     -- MALLOC.H  a header file that declares malloc() and free(), included
        for compatibility with some C compilers.  You can probably delete
        this file, or replace it by one containing only a blank line.

     -- NR.H  a header declarations file for all the Numerical Recipes
        functions on this diskette.  Three formats are present: traditional,
        LINT arguments, and ANSI.

     -- README.DOC this file

HOW DO YOU ACCESS THE PROGRAMS?

     This diskette has one "hidden" subdirectory:  The subdirectory \RECIPES
contains the 205 Numerical Recipes functions, all with names of the format
*.C. For example, if this diskette is in drive A: and you are in some other
working directory, you can copy the function BCUCOF to your working directory
by the command COPY A:\RECIPES\BCUCOF.C <enter> where <enter> denotes the enter
or return key.  If you want to copy all the Recipe files, e.g. to a hard disk,
you can do this by the command COPY A:\RECIPES\*.* <enter> This will take some
time, since the number of files is large.  Also note that some hard disks have
a minimum file block size as large as 4096 bytes.  Since most of the files are
much shorter than that, the programs on this diskette may occupy substantially
more space on a hard disk.  We recommend that you create a backup copy of this
diskette using the DISKCOPY command, then copy individual programs to your
working directory only as you need them.

WHAT DO YOU DO IF YOU NEED HELP?

     If you believe that this diskette is defective in manufacture, return it
to the place of purchase for replacement, or contact Cambridge University Press
at 32 East 57th Street, New York, NY 10022, USA.

     For technical questions or assistance, write to Numerical Recipes
Software, P.O. Box 243, Cambridge, MA  02238, USA.  Please note, however, that
the programs on this diskette are sold "as is" (see DISCLAIMER OF WARRANTY
below).  The authors of NUMERICAL RECIPES are interested in receiving reports
of bugs, but they cannot guarantee to correct them on any fixed schedule.  User
satisfaction is important to authors and publisher, however, so you should not
hesitate to make your comments or problems known.

HOW TO ORDER ADDITIONAL PRODUCTS:

     The Numerical Recipes series is available in three languages, FORTRAN,
C, and Pascal, and for a variety of machines, including IBM PC compatibles,
IBM PS/2 compatibles, Apple Macintosh, DEC VAX/VMS, DEC VAX/ULTRIX, Sun
Workstation (UNIX), and others.  For each language and machine, the series
includes the Main Book ("Numerical Recipes: The Art of Scientific Computing"),
an Example Book, and machine-readable versions of the software.

Some of the above products can be ordered from Cambridge University Press,
while others must be ordered from Numerical Recipes Software.

Order the following items from Cambridge University Press, 510 North Avenue,
New Rochelle, New York 10801, Tel. (800) 431-1580 (outside of Canada and New
York), (914) 235-0300 (in Canada and New York); or contact your local
bookstore:

     Numerical Recipes (Main Book) FORTRAN/PASCAL edition
     Numerical Recipes (Main Book) C edition
     Numerical Recipes Example Book in FORTRAN
     Numerical Recipes Example Book in Pascal
     Numerical Recipes Example Book in C
     IBM PC 5.25" diskette for Main Book (specify FORTRAN, Pascal, or C)
     IBM PC 5.25" diskette for Example Book (specify FORTRAN, Pascal, or C)
     Apple Macintosh Disk for Main Book (specify FORTRAN, Pascal, or C)
     Apple Macintosh Disk for Example Book (specify FORTRAN, Pascal, or C)

Order the following items from Numerical Recipes Software, P.O. Box 243,
Cambridge, MA  02238:

     PS/2 or laptop 3.5" diskette (one diskette for both Main Book
          and Example Book  -- specify FORTRAN, Pascal, or C)
     VAX/VMS Numerical Recipes license and magtape distribution
          (Main Book and Examples -- specify FORTRAN, Pascal, or C)
     UNIX or ULTRIX Numerical Recipes license and magtape distribution
          (Main Book and Examples -- specify FORTRAN, Pascal, or C)
     IBM Mainframe Numerical Recipes license and magtape distribution
          (Main Book and Examples -- specify FORTRAN, Pascal, or C)

                       DISCLAIMER OF WARRANTY
                       ---------- -- --------
     THE PROGRAMS AND FUNCTIONS ON THIS DISKETTE ARE PROVIDED "AS IS" WITHOUT
WARRANTY OF ANY KIND.  WE MAKE NO WARRANTIES, EXPRESS OR IMPLIED, THAT THE
PROGRAMS AND FUNCTIONS ARE FREE OF ERROR, OR ARE CONSISTENT WITH ANY PARTICULAR
STANDARD OF MERCHANTABILITY, OR THAT THEY WILL MEET YOUR REQUIREMENTS FOR ANY
PARTICULAR APPLICATION.  THEY SHOULD NOT BE RELIED ON FOR SOLVING A PROBLEM
WHOSE INCORRECT SOLUTION COULD RESULT IN INJURY TO A PERSON OR LOSS OF
PROPERTY.  IF YOU DO USE THE PROGRAMS OR FUNCTIONS IN SUCH A MANNER, IT IS AT
YOUR OWN RISK.  THE AUTHORS AND PUBLISHER DISCLAIM ALL LIABILITY FOR DIRECT,
INCIDENTAL, OR CONSEQUENTIAL DAMAGES RESULTING FROM YOUR USE OF THE PROGRAMS OR
FUNCTIONS ON THIS DISKETTE.  ANY LIABILITY OF SELLER OR MANUFACTURER WILL BE
LIMITED EXCLUSIVELY TO PRODUCT REPLACEMENT OF DISKETTES WITH MANUFACTURING
DEFECTS.
*/

/******************************************************************************/

#ifndef SQR_installed
#define SQR_installed
static double sqrarg;
#define SQR(a) (sqrarg=(a),sqrarg*sqrarg)
#endif

/*---1.0 ---------------------------------------------------------------------*/
/*---2.0 ---------------------------------------------------------------------*/

void invmatrix( a,n ) /* shik,940729 */
   double **a;
   int n;
{
   float **y,d,*col;
   int i,j,*indx;

   y=(float**)matrix(1,n,1,n);
   col=(float*)vector(1,n);
   indx=ivector(1,n);
   ludcmp((float**)a,n,indx,&d);
   for (j=1;j<=n;j++) {
      for (i=1;i<=n;i++) col[i]=(float)0.0;
      col[j]=(float)1.0;
      lubksb((float**)a,n,indx,col);
      for (i=1;i<=n;i++) y[i][j]=col[i];
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         a[i][j]=y[i][j];
   free_matrix(y,1,n,1,n);
   free_vector(col,1,n);
   free_ivector(indx,1,n);
}

/*---3.0 ---------------------------------------------------------------------*/
/*---4.0 ---------------------------------------------------------------------*/
/*---5.0 ---------------------------------------------------------------------*/
/*---6.0 ---------------------------------------------------------------------*/
/*---7.0 ---------------------------------------------------------------------*/
/*---8.0 ---------------------------------------------------------------------*/
/*---9.0 ---------------------------------------------------------------------*/
/*---10.0---------------------------------------------------------------------*/

#define NMAX 5000
#define ALPHA 1.0
#define BETA 0.5
#define GAMMA 2.0

#define GET_PSUM for (j=1;j<=ndim;j++) { for (i=1,sum=(float)0.0;i<=mpts;i++)\
                  sum += p[i][j]; psum[j]=sum;}

void amoeba(p,y,ndim,ftol,funk,nfunk)
float **p,y[],ftol,(*funk)();
int ndim,*nfunk;
{
   int i,j,ilo,ihi,inhi,mpts=ndim+1;
   float ytry,ysave,sum,rtol,amotry(),*psum,*vector();
   void nrerror(),free_vector();

   psum=vector(1,ndim);
   *nfunk=0;
   GET_PSUM
   for (;;) {
      ilo=1;
      ihi = y[1]>y[2] ? (inhi=2,1) : (inhi=1,2);
      for (i=1;i<=mpts;i++) {
         if (y[i] < y[ilo]) ilo=i;
         if (y[i] > y[ihi]) {
            inhi=ihi;
            ihi=i;
         } else if (y[i] > y[inhi])
            if (i != ihi) inhi=i;
      }
      rtol=(float)(2.0*fabs(y[ihi]-y[ilo])/(fabs(y[ihi])+fabs(y[ilo])));
      if (rtol < ftol) break;
      if (*nfunk >= NMAX) nrerror("Too many iterations in AMOEBA");
      ytry=amotry(p,y,psum,ndim,funk,ihi,nfunk,-ALPHA);
      if (ytry <= y[ilo])
         ytry=amotry(p,y,psum,ndim,funk,ihi,nfunk,GAMMA);
      else if (ytry >= y[inhi]) {
         ysave=y[ihi];
         ytry=amotry(p,y,psum,ndim,funk,ihi,nfunk,BETA);
         if (ytry >= ysave) {
            for (i=1;i<=mpts;i++) {
               if (i != ilo) {
                  for (j=1;j<=ndim;j++) {
                     psum[j]=(float)0.5*(p[i][j]+p[ilo][j]);
                     p[i][j]=psum[j];
                  }
                  y[i]=(*funk)(psum);
               }
            }
            *nfunk += ndim;
            GET_PSUM
         }
      }
   }
   free_vector(psum,1,ndim);
}

float amotry(p,y,psum,ndim,funk,ihi,nfunk,fac)
float **p,*y,*psum,(*funk)(),fac;
int ndim,ihi,*nfunk;
{
   int j;
   float fac1,fac2,ytry,*ptry,*vector();
   void nrerror(),free_vector();

   ptry=vector(1,ndim);
   fac1=(float)((1.0-fac)/ndim);
   fac2=(float)(fac1-fac);
   for (j=1;j<=ndim;j++) ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
   ytry=(*funk)(ptry);
   ++(*nfunk);
   if (ytry < y[ihi]) {
      y[ihi]=ytry;
      for (j=1;j<=ndim;j++) {
         psum[j] += ptry[j]-p[ihi][j];
         p[ihi][j]=ptry[j];
      }
   }
   free_vector(ptry,1,ndim);
   return ytry;
}

#undef ALPHA
#undef BETA
#undef GAMMA
#undef NMAX
/*----------------------------------------------------------------------------*/

#define TFACTR 0.9
#define ALEN(a,b,c,d) sqrt(((b)-(a))*((b)-(a))+((d)-(c))*((d)-(c)))

void anneal(x,y,iorder,ncity)
float x[],y[];
int iorder[],ncity;
{
   int ans,nover,nlimit,i1,i2,idum;
   unsigned long int iseed;
   int i,j,k,nsucc,nn,idec;
   static int n[7];
   float path,de,t;
   float ran3();
   int irbit1(),metrop();
   void reverse(),trnspt();
   float revcst(),trncst();

   nover=100*ncity;
   nlimit=10*ncity;
   path=(float)0.0;
   t=(float)0.5;
   for (i=1;i<ncity;i++) {
      i1=iorder[i];
      i2=iorder[i+1];
      path += ALEN(x[i1],x[i2],y[i1],y[i2]);
   }
   i1=iorder[ncity];
   i2=iorder[1];
   path += ALEN(x[i1],x[i2],y[i1],y[i2]);
   idum = -1;
   iseed=111;
   for (j=1;j<=100;j++) {
      nsucc=0;
      for (k=1;k<=nover;k++) {
         do {
            n[1]=1+(int) (ncity*ran3(&idum));
            n[2]=1+(int) ((ncity-1)*ran3(&idum));
            if (n[2] >= n[1]) ++n[2];
            nn=1+((n[1]-n[2]+ncity-1) % ncity);
         } while (nn<3);
         idec=irbit1(&iseed);
         if (idec == 0) {
            n[3]=n[2]+(int) (abs(nn-2)*ran3(&idum))+1;
            n[3]=1+((n[3]-1) % ncity);
            de=trncst(x,y,iorder,ncity,n);
            ans=metrop(de,t);
            if (ans) {
               ++nsucc;
               path += de;
               trnspt(iorder,ncity,n);
            }
         } else {
            de=revcst(x,y,iorder,ncity,n);
            ans=metrop(de,t);
            if (ans) {
               ++nsucc;
               path += de;
               reverse(iorder,ncity,n);
            }
         }
         if (nsucc >= nlimit) break;
      }
      printf("\n %s %10.6f %s %12.6f \n","T =",t,
         "    Path Length =",path);
      printf("Successful Moves: %6d\n",nsucc);
      t *= TFACTR;
      if (nsucc == 0) return;
   }
}

float revcst(x,y,iorder,ncity,n)
float x[],y[];
int iorder[],ncity,n[];
{
   float xx[5],yy[5],de;
   int j,ii;

   n[3]=1 + ((n[1]+ncity-2) % ncity);
   n[4]=1 + (n[2] % ncity);
   for (j=1;j<=4;j++) {
      ii=iorder[n[j]];
      xx[j]=x[ii];
      yy[j]=y[ii];
   }
   de = -ALEN(xx[1],xx[3],yy[1],yy[3]);
   de -= ALEN(xx[2],xx[4],yy[2],yy[4]);
   de += ALEN(xx[1],xx[4],yy[1],yy[4]);
   de += ALEN(xx[2],xx[3],yy[2],yy[3]);
   return de;
}

void reverse(iorder,ncity,n)
int iorder[],ncity,n[];
{
   int nn,j,k,l,itmp;

   nn=(1+((n[2]-n[1]+ncity) % ncity))/2;
   for (j=1;j<=nn;j++) {
      k=1 + ((n[1]+j-2) % ncity);
      l=1 + ((n[2]-j+ncity) % ncity);
      itmp=iorder[k];
      iorder[k]=iorder[l];
      iorder[l]=itmp;
   }
}

float trncst(x,y,iorder,ncity,n)
float x[],y[];
int iorder[],ncity,n[];
{
   float xx[7],yy[7],de;
   int j,ii;

   n[4]=1 + (n[3] % ncity);
   n[5]=1 + ((n[1]+ncity-2) % ncity);
   n[6]=1 + (n[2] % ncity);
   for (j=1;j<=6;j++) {
      ii=iorder[n[j]];
      xx[j]=x[ii];
      yy[j]=y[ii];
   }
   de = -ALEN(xx[2],xx[6],yy[2],yy[6]);
   de -= ALEN(xx[1],xx[5],yy[1],yy[5]);
   de -= ALEN(xx[3],xx[4],yy[3],yy[4]);
   de += ALEN(xx[1],xx[3],yy[1],yy[3]);
   de += ALEN(xx[2],xx[4],yy[2],yy[4]);
   de += ALEN(xx[5],xx[6],yy[5],yy[6]);
   return de;
}

void trnspt(iorder,ncity,n)
int iorder[],ncity,n[];
{
   int m1,m2,m3,nn,j,jj,*jorder,*ivector();
   void free_ivector();

   jorder=ivector(1,ncity);
   m1=1 + ((n[2]-n[1]+ncity) % ncity);
   m2=1 + ((n[5]-n[4]+ncity) % ncity);
   m3=1 + ((n[3]-n[6]+ncity) % ncity);
   nn=1;
   for (j=1;j<=m1;j++) {
      jj=1 + ((j+n[1]-2) % ncity);
      jorder[nn++]=iorder[jj];
   }
   if (m2>0) {
      for (j=1;j<=m2;j++) {
         jj=1+((j+n[4]-2) % ncity);
         jorder[nn++]=iorder[jj];
      }
   }
   if (m3>0) {
      for (j=1;j<=m3;j++) {
         jj=1 + ((j+n[6]-2) % ncity);
         jorder[nn++]=iorder[jj];
      }
   }
   for (j=1;j<=ncity;j++)
      iorder[j]=jorder[j];
   free_ivector(jorder,1,ncity);
}

int metrop(de,t)
float de,t;
{
   static int gljdum=1;
   float ran3();

   return de < 0.0 || ran3(&gljdum) < exp(-de/t);
}

#undef TFACTR
#undef ALEN
/*----------------------------------------------------------------------------*/

void bcucof(y,y1,y2,y12,d1,d2,c)
float y[],y1[],y2[],y12[],d1,d2,**c;
{
   static int wt[16][16]={
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
      {-3,0,0,3,0,0,0,0,-2,0,0,-1,0,0,0,0},
      {2,0,0,-2,0,0,0,0,1,0,0,1,0,0,0,0},
      {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
      {0,0,0,0,-3,0,0,3,0,0,0,0,-2,0,0,-1},
      {0,0,0,0,2,0,0,-2,0,0,0,0,1,0,0,1},
      {-3,3,0,0,-2,-1,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,-3,3,0,0,-2,-1,0,0},
      {9,-9,9,-9,6,3,-3,-6,6,-6,-3,3,4,2,1,2},
      {-6,6,-6,6,-4,-2,2,4,-3,3,3,-3,-2,-1,-1,-2},
      {2,-2,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,2,-2,0,0,1,1,0,0},
      {-6,6,-6,6,-3,-3,3,3,-4,4,2,-2,-2,-2,-1,-1},
      {4,-4,4,-4,2,2,-2,-2,2,-2,-2,2,1,1,1,1}};
   int l,k,j,i;
   float xx,d1d2,cl[16],x[16];

   d1d2=d1*d2;
   for (i=1;i<=4;i++) {
      x[i-1]=y[i];
      x[i+3]=y1[i]*d1;
      x[i+7]=y2[i]*d2;
      x[i+11]=y12[i]*d1d2;
   }
   for (i=0;i<=15;i++) {
      xx=(float)0.0;
      for (k=0;k<=15;k++) xx += wt[i][k]*x[k];
      cl[i]=xx;
   }
   l=0;
   for (i=1;i<=4;i++)
      for (j=1;j<=4;j++) c[i][j]=cl[l++];
}
void bcuint(y,y1,y2,y12,x1l,x1u,x2l,x2u,x1,x2,ansy,ansy1,ansy2)
float y[],y1[],y2[],y12[],x1l,x1u,x2l,x2u,x1,x2,*ansy,*ansy1,*ansy2;
{
   int i;
   float t,u,d1,d2,**c,**matrix();
   void bcucof(),nrerror(),free_matrix();

   c=matrix(1,4,1,4);
   d1=x1u-x1l;
   d2=x2u-x2l;
   bcucof(y,y1,y2,y12,d1,d2,c);
   if (x1u == x1l || x2u == x2l) nrerror("Bad input in routine BCUINT");
   t=(x1-x1l)/d1;
   u=(x2-x2l)/d2;
   *ansy=(*ansy2)=(*ansy1)=(float)0.0;
   for (i=4;i>=1;i--) {
      *ansy=t*(*ansy)+((c[i][4]*u+c[i][3])*u+c[i][2])*u+c[i][1];
      *ansy2=t*(*ansy2)+(3.0*c[i][4]*u+2.0*c[i][3])*u+c[i][2];
      *ansy1=u*(*ansy1)+(3.0*c[4][i]*t+2.0*c[3][i])*t+c[2][i];
   }
   *ansy1 /= d1;
   *ansy2 /= d2;
   free_matrix(c,1,4,1,4);
}
/*----------------------------------------------------------------------------*/

#define ACC 40.0
#define BIGNO 1.0e10
#define BIGNI 1.0e-10

float bessi(n,x)
int n;
float x;
{
   int j;
   float bi,bim,bip,tox,ans;
   float bessi0();
   void nrerror();

   if (n < 2) nrerror("Index n less than 2 in BESSI");
   if (x == 0.0)
      return (float)0.0;
   else {
      tox=2.0/fabs(x);
      bip=ans=(float)0.0;
      bi=(float)1.0;
      for (j=2*(n+(int) sqrt(ACC*n));j>0;j--) {
         bim=bip+j*tox*bi;
         bip=bi;
         bi=bim;
         if (fabs(bi) > BIGNO) {
            ans *= BIGNI;
            bi *= BIGNI;
            bip *= BIGNI;
         }
         if (j == n) ans=bip;
      }
      ans *= bessi0(x)/bi;
      return  x < 0.0 && n%2 == 1 ? -ans : ans;
   }
}

#undef ACC
#undef BIGNO
#undef BIGNI
/*----------------------------------------------------------------------------*/

float bessi0(x)
float x;
{
   float ax,ans;
   double y;

   if ((ax=fabs(x)) < 3.75) {
      y=x/3.75;
      y*=y;
      ans=1.0+y*(3.5156229+y*(3.0899424+y*(1.2067492
         +y*(0.2659732+y*(0.360768e-1+y*0.45813e-2)))));
   } else {
      y=3.75/ax;
      ans=(exp(ax)/sqrt(ax))*(0.39894228+y*(0.1328592e-1
         +y*(0.225319e-2+y*(-0.157565e-2+y*(0.916281e-2
         +y*(-0.2057706e-1+y*(0.2635537e-1+y*(-0.1647633e-1
         +y*0.392377e-2))))))));
   }
   return ans;
}
/*----------------------------------------------------------------------------*/

float bessi1(x)
float x;
{
   float ax,ans;
   double y;

   if ((ax=fabs(x)) < 3.75) {
      y=x/3.75;
      y*=y;
      ans=ax*(0.5+y*(0.87890594+y*(0.51498869+y*(0.15084934
         +y*(0.2658733e-1+y*(0.301532e-2+y*0.32411e-3))))));
   } else {
      y=3.75/ax;
      ans=0.2282967e-1+y*(-0.2895312e-1+y*(0.1787654e-1
         -y*0.420059e-2));
      ans=0.39894228+y*(-0.3988024e-1+y*(-0.362018e-2
         +y*(0.163801e-2+y*(-0.1031555e-1+y*ans))));
      ans *= (exp(ax)/sqrt(ax));
   }
   return x < 0.0 ? -ans : ans;
}
/*----------------------------------------------------------------------------*/

#define ACC 40.0
#define BIGNO 1.0e10
#define BIGNI 1.0e-10

float bessj(n,x)
int n;
float x;
{
   int j,jsum,m;
   float ax,bj,bjm,bjp,sum,tox,ans;
   float bessj0(),bessj1();
   void nrerror();

   if (n < 2) nrerror("Index n less than 2 in BESSJ");
   ax=fabs(x);
   if (ax == 0.0)
      return 0.0;
   else if (ax > (float) n) {
      tox=2.0/ax;
      bjm=bessj0(ax);
      bj=bessj1(ax);
      for (j=1;j<n;j++) {
         bjp=j*tox*bj-bjm;
         bjm=bj;
         bj=bjp;
      }
      ans=bj;
   } else {
      tox=2.0/ax;
      m=2*((n+(int) sqrt(ACC*n))/2);
      jsum=0;
      bjp=ans=sum=0.0;
      bj=1.0;
      for (j=m;j>0;j--) {
         bjm=j*tox*bj-bjp;
         bjp=bj;
         bj=bjm;
         if (fabs(bj) > BIGNO) {
            bj *= BIGNI;
            bjp *= BIGNI;
            ans *= BIGNI;
            sum *= BIGNI;
         }
         if (jsum) sum += bj;
         jsum=!jsum;
         if (j == n) ans=bjp;
      }
      sum=2.0*sum-bj;
      ans /= sum;
   }
   return  x < 0.0 && n%2 == 1 ? -ans : ans;
}

#undef ACC
#undef BIGNO
#undef BIGNI
/*----------------------------------------------------------------------------*/

float bessj0(x)
float x;
{
   float ax,z;
   double xx,y,ans,ans1,ans2;

   if ((ax=fabs(x)) < 8.0) {
      y=x*x;
      ans1=57568490574.0+y*(-13362590354.0+y*(651619640.7
         +y*(-11214424.18+y*(77392.33017+y*(-184.9052456)))));
      ans2=57568490411.0+y*(1029532985.0+y*(9494680.718
         +y*(59272.64853+y*(267.8532712+y*1.0))));
      ans=ans1/ans2;
   } else {
      z=8.0/ax;
      y=z*z;
      xx=ax-0.785398164;
      ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4
         +y*(-0.2073370639e-5+y*0.2093887211e-6)));
      ans2 = -0.1562499995e-1+y*(0.1430488765e-3
         +y*(-0.6911147651e-5+y*(0.7621095161e-6
         -y*0.934935152e-7)));
      ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
   }
   return ans;
}
/*----------------------------------------------------------------------------*/

float bessj1(x)
float x;
{
   float ax,z;
   double xx,y,ans,ans1,ans2;

   if ((ax=fabs(x)) < 8.0) {
      y=x*x;
      ans1=x*(72362614232.0+y*(-7895059235.0+y*(242396853.1
         +y*(-2972611.439+y*(15704.48260+y*(-30.16036606))))));
      ans2=144725228442.0+y*(2300535178.0+y*(18583304.74
         +y*(99447.43394+y*(376.9991397+y*1.0))));
      ans=ans1/ans2;
   } else {
      z=8.0/ax;
      y=z*z;
      xx=ax-2.356194491;
      ans1=1.0+y*(0.183105e-2+y*(-0.3516396496e-4
         +y*(0.2457520174e-5+y*(-0.240337019e-6))));
      ans2=0.04687499995+y*(-0.2002690873e-3
         +y*(0.8449199096e-5+y*(-0.88228987e-6
         +y*0.105787412e-6)));
      ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
      if (x < 0.0) ans = -ans;
   }
   return ans;
}
float bessk(n,x)
int n;
float x;
{
   int j;
   float bk,bkm,bkp,tox;
   float bessk0(),bessk1();
   void nrerror();

   if (n < 2) nrerror("Index n less than 2 in BESSK");
   tox=2.0/x;
   bkm=bessk0(x);
   bk=bessk1(x);
   for (j=1;j<n;j++) {
      bkp=bkm+j*tox*bk;
      bkm=bk;
      bk=bkp;
   }
   return bk;
}
/*----------------------------------------------------------------------------*/

float bessk0(x)
float x;
{
   double y,ans;
   float bessi0();

   if (x <= 2.0) {
      y=x*x/4.0;
      ans=(-log(x/2.0)*bessi0(x))+(-0.57721566+y*(0.42278420
         +y*(0.23069756+y*(0.3488590e-1+y*(0.262698e-2
         +y*(0.10750e-3+y*0.74e-5))))));
   } else {
      y=2.0/x;
      ans=(exp(-x)/sqrt(x))*(1.25331414+y*(-0.7832358e-1
         +y*(0.2189568e-1+y*(-0.1062446e-1+y*(0.587872e-2
         +y*(-0.251540e-2+y*0.53208e-3))))));
   }
   return ans;
}
/*----------------------------------------------------------------------------*/

float bessk1(x)
float x;
{
   double y,ans;
   float bessi1();

   if (x <= 2.0) {
      y=x*x/4.0;
      ans=(log(x/2.0)*bessi1(x))+(1.0/x)*(1.0+y*(0.15443144
         +y*(-0.67278579+y*(-0.18156897+y*(-0.1919402e-1
         +y*(-0.110404e-2+y*(-0.4686e-4)))))));
   } else {
      y=2.0/x;
      ans=(exp(-x)/sqrt(x))*(1.25331414+y*(0.23498619
         +y*(-0.3655620e-1+y*(0.1504268e-1+y*(-0.780353e-2
         +y*(0.325614e-2+y*(-0.68245e-3)))))));
   }
   return ans;
}
float bessy(n,x)
int n;
float x;
{
   int j;
   float by,bym,byp,tox;
   float bessy0(),bessy1();
   void nrerror();

   if (n < 2) nrerror("Index n less than 2 in BESSY");
   tox=2.0/x;
   by=bessy1(x);
   bym=bessy0(x);
   for (j=1;j<n;j++) {
      byp=j*tox*by-bym;
      bym=by;
      by=byp;
   }
   return by;
}
/*----------------------------------------------------------------------------*/

float bessy0(x)
float x;
{
   float z;
   double xx,y,ans,ans1,ans2;
   float bessj0();

   if (x < 8.0) {
      y=x*x;
      ans1 = -2957821389.0+y*(7062834065.0+y*(-512359803.6
         +y*(10879881.29+y*(-86327.92757+y*228.4622733))));
      ans2=40076544269.0+y*(745249964.8+y*(7189466.438
         +y*(47447.26470+y*(226.1030244+y*1.0))));
      ans=(ans1/ans2)+0.636619772*bessj0(x)*log(x);
   } else {
      z=8.0/x;
      y=z*z;
      xx=x-0.785398164;
      ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4
         +y*(-0.2073370639e-5+y*0.2093887211e-6)));
      ans2 = -0.1562499995e-1+y*(0.1430488765e-3
         +y*(-0.6911147651e-5+y*(0.7621095161e-6
         +y*(-0.934945152e-7))));
      ans=sqrt(0.636619772/x)*(sin(xx)*ans1+z*cos(xx)*ans2);
   }
   return ans;
}
/*----------------------------------------------------------------------------*/

float bessy1(x)
float x;
{
   float z;
   double xx,y,ans,ans1,ans2;
   float bessj1();

   if (x < 8.0) {
      y=x*x;
      ans1=x*(-0.4900604943e13+y*(0.1275274390e13
         +y*(-0.5153438139e11+y*(0.7349264551e9
         +y*(-0.4237922726e7+y*0.8511937935e4)))));
      ans2=0.2499580570e14+y*(0.4244419664e12
         +y*(0.3733650367e10+y*(0.2245904002e8
         +y*(0.1020426050e6+y*(0.3549632885e3+y)))));
      ans=(ans1/ans2)+0.636619772*(bessj1(x)*log(x)-1.0/x);
   } else {
      z=8.0/x;
      y=z*z;
      xx=x-2.356194491;
      ans1=1.0+y*(0.183105e-2+y*(-0.3516396496e-4
         +y*(0.2457520174e-5+y*(-0.240337019e-6))));
      ans2=0.04687499995+y*(-0.2002690873e-3
         +y*(0.8449199096e-5+y*(-0.88228987e-6
         +y*0.105787412e-6)));
      ans=sqrt(0.636619772/x)*(sin(xx)*ans1+z*cos(xx)*ans2);
   }
   return ans;
}
/*----------------------------------------------------------------------------*/

float beta(z,w)
float z,w;
{
   float gammln();

   return exp(gammln(z)+gammln(w)-gammln(z+w));
}
/*----------------------------------------------------------------------------*/

#define ITMAX 100
#define EPS 3.0e-7

float betacf(a,b,x)
float a,b,x;
{
   float qap,qam,qab,em,tem,d;
   float bz,bm=1.0,bp,bpp;
   float az=1.0,am=1.0,ap,app,aold;
   int m;
   void nrerror();

   qab=a+b;
   qap=a+1.0;
   qam=a-1.0;
   bz=1.0-qab*x/qap;
   for (m=1;m<=ITMAX;m++) {
      em=(float) m;
      tem=em+em;
      d=em*(b-em)*x/((qam+tem)*(a+tem));
      ap=az+d*am;
      bp=bz+d*bm;
      d = -(a+em)*(qab+em)*x/((qap+tem)*(a+tem));
      app=ap+d*az;
      bpp=bp+d*bz;
      aold=az;
      am=ap/bpp;
      bm=bp/bpp;
      az=app/bpp;
      bz=1.0;
      if (fabs(az-aold) < (EPS*fabs(az))) return az;
   }
   nrerror("a or b too big, or ITMAX too small in BETACF");
   return NaNFloat; // 2016.3.26
}

#undef ITMAX
#undef EPS
/*----------------------------------------------------------------------------*/

float betai(a,b,x)
float a,b,x;
{
   float bt;
   float gammln(),betacf();
   void nrerror();

   if (x < 0.0 || x > 1.0) nrerror("Bad x in routine BETAI");
   if (x == 0.0 || x == 1.0) bt=0.0;
   else
      bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
   if (x < (a+1.0)/(a+b+2.0))
      return bt*betacf(a,b,x)/a;
   else
      return 1.0-bt*betacf(b,a,1.0-x)/b;
}
/*----------------------------------------------------------------------------*/

float bico(n,k)
int n,k;
{
   float factln();

   return floor(0.5+exp(factln(n)-factln(k)-factln(n-k)));
}
/*----------------------------------------------------------------------------*/

#ifndef PI
#define PI 3.141592654
#endif

float bnldev(pp,n,idum)
float pp;
int n,*idum;
{
   int j;
   static int nold=(-1);
   float am,em,g,angle,p,bnl,sq,t,y;
   static float pold=(-1.0),pc,plog,pclog,en,oldg;
   float ran1(),gammln();

   p=(pp <= 0.5 ? pp : 1.0-pp);
   am=n*p;
   if (n < 25) {
      bnl=0.0;
      for (j=1;j<=n;j++)
         if (ran1(idum) < p) bnl += 1.0;
   } else if (am < 1.0) {
      g=exp(-am);
      t=1.0;
      for (j=0;j<=n;j++) {
         t *= ran1(idum);
         if (t < g) break;
      }
      bnl=(j <= n ? j : n);
   } else {
      if (n != nold) {
         en=n;
         oldg=gammln(en+1.0);
         nold=n;
      } if (p != pold) {
         pc=1.0-p;
         plog=log(p);
         pclog=log(pc);
         pold=p;
      }
      sq=sqrt(2.0*am*pc);
      do {
         do {
            angle=PI*ran1(idum);
            y=tan(angle);
            em=sq*y+am;
         } while (em < 0.0 || em >= (en+1.0));
         em=floor(em);
         t=1.2*sq*(1.0+y*y)*exp(oldg-gammln(em+1.0)
            -gammln(en-em+1.0)+em*plog+(en-em)*pclog);
      } while (ran1(idum) > t);
      bnl=em;
   }
   if (p != pp) bnl=n-bnl;
   return bnl;
}

#undef PI
/*----------------------------------------------------------------------------*/

#define ITMAX 100
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : -fabs(a))
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

float brent(ax,bx,cx,f,tol,xmin)
float ax,bx,cx,tol,*xmin;
float (*f)();   /* ANSI: float (*f)(float); */
{
   int iter;
   float a,b,d,etemp,fu,fv,fw,fx,p,q,r,tol1,tol2,u,v,w,x,xm;
   float e=0.0;
   void nrerror();

   a=((ax < cx) ? ax : cx);
   b=((ax > cx) ? ax : cx);
   x=w=v=bx;
   fw=fv=fx=(*f)(x);
   for (iter=1;iter<=ITMAX;iter++) {
      xm=0.5*(a+b);
      tol2=2.0*(tol1=tol*fabs(x)+ZEPS);
      if (fabs(x-xm) <= (tol2-0.5*(b-a))) {
         *xmin=x;
         return fx;
      }
      if (fabs(e) > tol1) {
         r=(x-w)*(fx-fv);
         q=(x-v)*(fx-fw);
         p=(x-v)*q-(x-w)*r;
         q=2.0*(q-r);
         if (q > 0.0) p = -p;
         q=fabs(q);
         etemp=e;
         e=d;
         if (fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a-x) || p >=
q*(b-x))
            d=CGOLD*(e=(x >= xm ? a-x : b-x));
         else {
            d=p/q;
            u=x+d;
            if (u-a < tol2 || b-u < tol2)
               d=SIGN(tol1,xm-x);
         }
      } else {
         d=CGOLD*(e=(x >= xm ? a-x : b-x));
      }
      u=(fabs(d) >= tol1 ? x+d : x+SIGN(tol1,d));
      fu=(*f)(u);
      if (fu <= fx) {
         if (u >= x) a=x; else b=x;
         SHFT(v,w,x,u)
         SHFT(fv,fw,fx,fu)
      } else {
         if (u < x) a=u; else b=u;
         if (fu <= fw || w == x) {
            v=w;
            w=u;
            fv=fw;
            fw=fu;
         } else if (fu <= fv || v == x || v == w) {
            v=u;
            fv=fu;
         }
      }
   }
   nrerror("Too many iterations in BRENT");
   *xmin=x;
   return fx;
}

#undef ITMAX
#undef CGOLD
#undef ZEPS
#undef SIGN
/*----------------------------------------------------------------------------*/

#define IGREG 2299161

void caldat(julian,mm,id,iyyy)
long julian;
int *mm,*id,*iyyy;
{
   long ja,jalpha,jb,jc,jd,je;

   if (julian >= IGREG) {
      jalpha=(long)(((float) (julian-1867216)-0.25)/36524.25); /* shik */
      ja=julian+1+jalpha-(long) (0.25*jalpha);
   } else
      ja=julian;
   jb=ja+1524;
   jc=(long)( 6680.0+((float) (jb-2439870)-122.1)/365.25 ); /* shik */
   jd=(long)( 365*jc+(0.25*jc) ); /* shik */
   je=(long)( (jb-jd)/30.6001 ); /* shik */
   *id=jb-jd-(int) (30.6001*je);
   *mm=je-1;
   if (*mm > 12) *mm -= 12;
   *iyyy=jc-4715;
   if (*mm > 2) --(*iyyy);
   if (*iyyy <= 0) --(*iyyy);
}

#undef IGREG
/*----------------------------------------------------------------------------*/

#define CA 0.0003
#define PIO2 1.57079632679490

float cel(qqc,pp,aa,bb)
float qqc,pp,aa,bb;
{
   float a,b,e,f,g,em,p,q,qc;
   void nrerror();

   if (qqc == 0.0) nrerror("Bad qqc in routine CEL");
   qc=fabs(qqc);
   a=aa;
   b=bb;
   p=pp;
   e=qc;
   em=1.0;
   if (p > 0.0) {
      p=sqrt(p);
      b /= p;
   } else {
      f=qc*qc;
      q=1.0-f;
      g=1.0-p;
      f -= p;
      q *= (b-a*p);
      p=sqrt(f/g);
      a=(a-b)/g;
      b = -q/(g*g*p)+a*p;
   }
   for (;;) {
      f=a;
      a += (b/p);
      g=e/p;
      b += (f*g);
      b += b;
      p=g+p;
      g=em;
      em += qc;
      if (fabs(g-qc) <= g*CA) break;
      qc=sqrt(e);
      qc += qc;
      e=qc*em;
   }
   return PIO2*(b+a*em)/(em*(em+p));
}

#undef CA
#undef PIO2
void chder(a,b,c,cder,n)
float a,b,c[],cder[];
int n;
{
   int j;
   float con;

   cder[n-1]=0.0;
   cder[n-2]=2*(n-1)*c[n-1];
   for (j=n-3;j>=0;j--)
      cder[j]=cder[j+2]+2*(j+1)*c[j+1];
   con=2.0/(b-a);
   for (j=0;j<n;j++)
      cder[j] *= con;
}
float chebev(a,b,c,m,x)
float a,b,c[],x;
int m;
{
   float d=0.0,dd=0.0,sv,y,y2;
   int j;
   void nrerror();

   if ((x-a)*(x-b) > 0.0) nrerror("x not in range in routine CHEBEV");
   y2=2.0*(y=(2.0*x-a-b)/(b-a));
   for (j=m-1;j>=1;j--) {
      sv=d;
      d=y2*d-dd+c[j];
      dd=sv;
   }
   return y*d-dd+0.5*c[0];
}
/*----------------------------------------------------------------------------*/

#define PI 3.141592653589793

void chebft(a,b,c,n,func)
float a,b,c[];
float (*func)();   /* ANSI: float (*func)(float); */
int n;
{
   int k,j;
   float fac,bpa,bma,*f,*vector();
   void free_vector();

   f=vector(0,n-1);
   bma=0.5*(b-a);
   bpa=0.5*(b+a);
   for (k=0;k<n;k++) {
      float y=cos(PI*(k+0.5)/n);
      f[k]=(*func)(y*bma+bpa);
   }
   fac=2.0/n;
   for (j=0;j<n;j++) {
      double sum=0.0;
      for (k=0;k<n;k++)
         sum += f[k]*cos(PI*j*(k+0.5)/n);
      c[j]=fac*sum;
   }
   free_vector(f,0,n-1);
}

#undef PI
void chebpc(c,d,n)
float c[],d[];
int n;
{
   int k,j;
   float sv,*dd,*vector();
   void free_vector();

   dd=vector(0,n-1);
   for (j=0;j<n;j++) d[j]=dd[j]=0.0;
   d[0]=c[n-1];
   for (j=n-2;j>=1;j--) {
      for (k=n-j;k>=1;k--) {
         sv=d[k];
         d[k]=2.0*d[k-1]-dd[k];
         dd[k]=sv;
      }
      sv=d[0];
      d[0] = -dd[0]+c[j];
      dd[0]=sv;
   }
   for (j=n-1;j>=1;j--)
      d[j]=d[j-1]-dd[j];
   d[0] = -dd[0]+0.5*c[0];
   free_vector(dd,0,n-1);
}
void chint(a,b,c,cint,n)
float a,b,c[],cint[];
int n;
{
   int j;
   float sum=0.0,fac=1.0,con;

   con=0.25*(b-a);
   for (j=1;j<=n-2;j++) {
      cint[j]=con*(c[j-1]-c[j+1])/j;
      sum += fac*cint[j];
      fac = -fac;
   }
   cint[n-1]=con*c[n-2]/(n-1);
   sum += fac*cint[n-1];
   cint[0]=2.0*sum;
}


/*----------------------------------------------------------------------------*/


#define ITMAX 100
#define ZEPS 1.0e-10
#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : -fabs(a))
#define MOV3(a,b,c, d,e,f) (a)=(d);(b)=(e);(c)=(f);

float dbrent(ax,bx,cx,f,df,tol,xmin)
float ax,bx,cx,tol,*xmin;
float (*f)(),(*df)(); /* ANSI: float (*f)(float),(*df)(float); */
{
   int iter,ok1,ok2;
   float a,b,d,d1,d2,du,dv,dw,dx,e=0.0;
   float fu,fv,fw,fx,olde,tol1,tol2,u,u1,u2,v,w,x,xm;
   void nrerror();

   a=(ax < cx ? ax : cx);
   b=(ax > cx ? ax : cx);
   x=w=v=bx;
   fw=fv=fx=(*f)(x);
   dw=dv=dx=(*df)(x);
   for (iter=1;iter<=ITMAX;iter++) {
      xm=0.5*(a+b);
      tol1=tol*fabs(x)+ZEPS;
      tol2=2.0*tol1;
      if (fabs(x-xm) <= (tol2-0.5*(b-a))) {
         *xmin=x;
         return fx;
      }
      if (fabs(e) > tol1) {
         d1=2.0*(b-a);
         d2=d1;
         if (dw != dx)  d1=(w-x)*dx/(dx-dw);
         if (dv != dx)  d2=(v-x)*dx/(dx-dv);
         u1=x+d1;
         u2=x+d2;
         ok1 = (a-u1)*(u1-b) > 0.0 && dx*d1 <= 0.0;
         ok2 = (a-u2)*(u2-b) > 0.0 && dx*d2 <= 0.0;
         olde=e;
         e=d;
         if (ok1 || ok2) {
            if (ok1 && ok2)
               d=(fabs(d1) < fabs(d2) ? d1 : d2);
            else if (ok1)
               d=d1;
            else
               d=d2;
            if (fabs(d) <= fabs(0.5*olde)) {
               u=x+d;
               if (u-a < tol2 || b-u < tol2)
                  d=SIGN(tol1,xm-x);
            } else {
               d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
            }
         } else {
            d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
         }
      } else {
         d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
      }
      if (fabs(d) >= tol1) {
         u=x+d;
         fu=(*f)(u);
      } else {
         u=x+SIGN(tol1,d);
         fu=(*f)(u);
         if (fu > fx) {
            *xmin=x;
            return fx;
         }
      }
      du=(*df)(u);
      if (fu <= fx) {
         if (u >= x) a=x; else b=x;
         MOV3(v,fv,dv, w,fw,dw)
         MOV3(w,fw,dw, x,fx,dx)
         MOV3(x,fx,dx, u,fu,du)
      } else {
         if (u < x) a=u; else b=u;
         if (fu <= fw || w == x) {
            MOV3(v,fv,dv, w,fw,dw)
            MOV3(w,fw,dw, u,fu,du)
         } else if (fu < fv || v == x || v == w) {
            MOV3(v,fv,dv, u,fu,du)
         }
      }
   }
   nrerror("Too many iterations in routine DBRENT");
   return NaNFloat; // 2016.3.26
}

#undef ITMAX
#undef ZEPS
#undef SIGN
#undef MOV3
void ddpoly(c,nc,x,pd,nd)
int nc,nd;
float c[],x,pd[];
{
   int nnd,j,i;
   float cnst=1.0;

   pd[0]=c[nc];
   for (j=1;j<=nd;j++) pd[j]=0.0;
   for (i=nc-1;i>=0;i--) {
      nnd=(nd < (nc-i) ? nd : nc-i);
      for (j=nnd;j>=1;j--)
         pd[j]=pd[j]*x+pd[j-1];
      pd[0]=pd[0]*x+c[i];
   }
   for (i=2;i<=nd;i++) {
      cnst *= i;
      pd[i] *= cnst;
   }
}
/*----------------------------------------------------------------------------*/

/* typedef struct IMMENSE {unsigned long l,r;} immense; !shik */
/* typedef struct GREAT {unsigned short l,c,r;} great; !shik */

unsigned long bit[33];   /* defining declaration */

void des(inp,key,newkey,isw,out)
immense inp,key,*out;
int *newkey,isw;
{
   static char ip[65]=
      {0,58,50,42,34,26,18,10,2,60,52,44,36,
      28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,
      32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,
      27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,
      31,23,15,7};
   static char ipm[65]=
      {0,40,8,48,16,56,24,64,32,39,7,47,15,
      55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,
      53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,
      51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,
      49,17,57,25};
   static great kns[17];
   static int initflag=1;
   int ii,i,j,k;
   unsigned long ic,shifter,getbit();
   immense itmp;
   void cyfun(),ks();

   if (initflag) {
      initflag=0;
      bit[1]=shifter=1L;
      for(j=2;j<=32;j++) bit[j] = (shifter <<= 1);
   }
   if (*newkey) {
      *newkey=0;
      for(i=1;i<=16;i++) ks(key,i,&kns[i]);
   }
   itmp.r=itmp.l=0L;
   for(j=32,k=64;j>=1;j--,k--) {
      itmp.r = (itmp.r <<= 1) | getbit(inp,ip[j],32);
      itmp.l = (itmp.l <<= 1) | getbit(inp,ip[k],32);
   }
   for(i=1;i<=16;i++) {
      ii = (isw == 1 ? 17-i : i);
      cyfun(itmp.l,kns[ii],&ic);
      ic ^= itmp.r;
      itmp.r=itmp.l;
      itmp.l=ic;
   }
   ic=itmp.r;
   itmp.r=itmp.l;
   itmp.l=ic;
   (*out).r=(*out).l=0L;
   for(j=32,k=64;j>=1;j--,k--) {
      (*out).r = ((*out).r <<= 1) | getbit(itmp,ipm[j],32);
      (*out).l = ((*out).l <<= 1) | getbit(itmp,ipm[k],32);
   }
}
extern unsigned long bit[];   /* defined in DES */

/* typedef struct IMMENSE {unsigned long l,r;} immense; !shik */
/* typedef struct GREAT {unsigned short l,c,r;} great; !shik */

unsigned long getbit(source,bitno,nbits)
immense source;
int bitno,nbits;
{
   if (bitno <= nbits)
      return bit[bitno] & source.r ? 1L : 0L;
   else
      return bit[bitno-nbits] & source.l ? 1L : 0L;
}

void ks(key,n,kn)
immense key;
great *kn;
int n;
{
   static immense icd;
   static char ipc1[57]={0,57,49,41,33,25,17,9,1,58,50,
      42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,
      52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,
      30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
   static char ipc2[49]={0,14,17,11,24,1,5,3,28,15,6,21,
      10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,
      37,47,55,30,40,51,45,33,48,44,49,39,56,34,
      53,46,42,50,36,29,32};
   int it,i,j,k,l;

   if (n == 1) {
      icd.r=icd.l=0L;
      for(j=28,k=56;j>=1;j--,k--) {
         icd.r = (icd.r <<= 1) | getbit(key,ipc1[j],32);
         icd.l = (icd.l <<= 1) | getbit(key,ipc1[k],32);
      }
   }
   if (n == 1 || n == 2 || n == 9 || n == 16) it=1;
   else it=2;
   for(i=1;i<=it;i++) {
      icd.r = (icd.r | ((icd.r & 1L) << 28)) >> 1;
      icd.l = (icd.l | ((icd.l & 1L) << 28)) >> 1;
   }
   (*kn).r=(*kn).c=(*kn).l=0;
   for(j=16,k=32,l=48;j>=1;j--,k--,l--) {
      (*kn).r=((*kn).r <<= 1) | (unsigned short)
         getbit(icd,ipc2[j],28);
      (*kn).c=((*kn).c <<= 1) | (unsigned short)
         getbit(icd,ipc2[k],28);
      (*kn).l=((*kn).l <<= 1) | (unsigned short)
         getbit(icd,ipc2[l],28);
   }
}

void cyfun(ir,k,iout)
unsigned long ir,*iout;
great k;
{
   static char iet[49]={0,32,1,2,3,4,5,4,5,6,7,8,9,8,9,
      10,11,12,13,12,13,14,15,16,17,16,17,18,19,
      20,21,20,21,22,23,24,25,24,25,26,27,28,29,
      28,29,30,31,32,1};
   static char ipp[33]={0,16,7,20,21,29,12,28,17,1,15,
      23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,
      30,6,22,11,4,25};
   static char is[16][4][9]={
      0,14,15,10,7,2,12,4,13,0,0,3,13,13,14,10,13,1,
      0,4,0,13,10,4,9,1,7,0,15,13,1,3,11,4,6,2,
      0,4,1,0,13,12,1,11,2,0,15,13,7,8,11,15,0,15,
      0,1,14,6,6,2,14,4,11,0,12,8,10,15,8,3,11,1,
      0,13,8,9,14,4,10,2,8,0,7,4,0,11,2,4,11,13,
      0,14,7,4,9,1,15,11,4,0,8,10,13,0,12,2,13,14,
      0,1,14,14,3,1,15,14,4,0,4,7,9,5,12,2,7,8,
      0,8,11,9,0,11,5,13,1,0,2,1,0,6,7,12,8,7,
      0,2,6,6,0,7,9,15,6,0,14,15,3,6,4,7,4,10,
      0,13,10,8,12,10,2,12,9,0,4,3,6,10,1,9,1,4,
      0,15,11,3,6,10,2,0,15,0,2,2,4,15,7,12,9,3,
      0,6,4,15,11,13,8,3,12,0,9,15,9,1,14,5,4,10,
      0,11,3,15,9,11,6,8,11,0,13,8,6,0,13,9,1,7,
      0,2,13,3,7,7,12,7,14,0,1,4,8,13,2,15,10,8,
      0,8,4,5,10,6,8,13,1,0,1,14,10,3,1,5,10,4,
      0,11,1,0,13,8,3,14,2,0,7,2,7,8,13,10,7,13,
      0,3,9,1,1,8,0,3,10,0,10,12,2,4,5,6,14,12,
      0,15,5,11,15,15,7,10,0,0,5,11,4,9,6,11,9,15,
      0,10,7,13,2,5,13,12,9,0,6,0,8,7,0,1,3,5,
      0,12,8,1,1,9,0,15,6,0,11,6,15,4,15,14,5,12,
      0,6,2,12,8,3,3,9,3,0,12,1,5,2,15,13,5,6,
      0,9,12,2,3,12,4,6,10,0,3,7,14,5,0,1,0,9,
      0,12,13,7,5,15,4,7,14,0,11,10,14,12,10,14,12,11,
      0,7,6,12,14,5,10,8,13,0,14,12,3,11,9,7,15,0,
      0,5,12,11,11,13,14,5,5,0,9,6,12,1,3,0,2,0,
      0,3,9,5,5,6,1,0,15,0,10,0,11,12,10,6,14,3,
      0,9,0,4,12,0,7,10,0,0,5,9,11,10,9,11,15,14,
      0,10,3,10,2,3,13,5,3,0,0,5,5,7,4,0,2,5,
      0,0,5,2,4,14,5,6,12,0,3,11,15,14,8,3,8,9,
      0,5,2,14,8,0,11,9,5,0,6,14,2,2,5,8,3,6,
      0,7,10,8,15,9,11,1,7,0,8,5,1,9,6,8,6,2,
      0,0,15,7,4,14,6,2,8,0,13,9,12,14,3,13,12,11};
   static char ibin[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
   great ie;
   unsigned long itmp,ietmp1,ietmp2;
   char iec[9];
   int jj,irow,icol,iss,j,l,m;

   ie.r=ie.c=ie.l=0;
   for(j=16,l=32,m=48;j>=1;j--,l--,m--) {
      ie.r = (ie.r <<= 1) | (bit[iet[j]] & ir ? 1 : 0);
      ie.c = (ie.c <<= 1) | (bit[iet[l]] & ir ? 1 : 0);
      ie.l = (ie.l <<= 1) | (bit[iet[m]] & ir ? 1 : 0);
   }
   ie.r ^= k.r;
   ie.c ^= k.c;
   ie.l ^= k.l;
   ietmp1=((unsigned long) ie.c << 16)+(unsigned long) ie.r;
   ietmp2=((unsigned long) ie.l << 8)+((unsigned long) ie.c >> 8);
   for(j=1,m=5;j<=4;j++,m++) {
      iec[j]=(char)( ietmp1 & 0x3fL ); /* shik */
      iec[m]=(char)( ietmp2 & 0x3fL ); /* shik */
      ietmp1 >>= 6;
      ietmp2 >>= 6;
   }
   itmp=0L;
   for(jj=8;jj>=1;jj--) {
      j=iec[jj];
      irow=((j & 0x1) << 1)+((j & 0x20) >> 5);
      icol=((j & 0x2) << 2)+(j & 0x4)
         +((j & 0x8) >> 2)+((j & 0x10) >> 4);
      iss=is[icol][irow][jj];
      itmp = (itmp <<= 4) | ibin[iss];
   }
   *iout=0L;
   for(j=32;j>=1;j--)
      *iout = (*iout <<= 1) | (bit[ipp[j]] & itmp ? 1 : 0);
}
extern int ncom;   /* defined in DLINMIN */
extern float *pcom,*xicom,(*nrfunc)();
extern void (*nrdfun)();

float df1dim(x)
float x;
{
   int j;
   float df1=0.0;
   float *xt,*df,*vector();
   void free_vector();

   xt=vector(1,ncom);
   df=vector(1,ncom);
   for (j=1;j<=ncom;j++) xt[j]=pcom[j]+x*xicom[j];
   (*nrdfun)(xt,df);
   for (j=1;j<=ncom;j++) df1 += df[j]*xicom[j];
   free_vector(df,1,ncom);
   free_vector(xt,1,ncom);
   return df1;
}
/*----------------------------------------------------------------------------*/

#define ITMAX 200
#define EPS 1.0e-10

void dfpmin(p,n,ftol,iter,fret,func,dfunc)
float p[],ftol,*fret,(*func)();
void (*dfunc)();
int n,*iter;
{
   int j,i,its;
   float fp,fae,fad,fac;
   float *xi,*g,*dg,*hdg,*vector();
   float **hessin,**matrix();
   void linmin(),nrerror(),free_matrix(),free_vector();

   hessin=matrix(1,n,1,n);
   xi=vector(1,n);
   g=vector(1,n);
   dg=vector(1,n);
   hdg=vector(1,n);
   fp=(*func)(p);
   (*dfunc)(p,g);
   for (i=1;i<=n;i++) {
      for (j=1;j<=n;j++) hessin[i][j]=0.0;
      hessin[i][i]=1.0;
      xi[i] = -g[i];
   }
   for (its=1;its<=ITMAX;its++) {
      *iter=its;
      linmin(p,xi,n,fret,func);
      if (2.0*fabs(*fret-fp) <= ftol*(fabs(*fret)+fabs(fp)+EPS)) {
         free_vector(hdg,1,n);
         free_vector(dg,1,n);
         free_vector(g,1,n);
         free_vector(xi,1,n);
         free_matrix(hessin,1,n,1,n);
         return;
      }
      fp=(*fret);
      for (i=1;i<=n;i++) dg[i]=g[i];
      *fret=(*func)(p);
      (*dfunc)(p,g);
      for (i=1;i<=n;i++) dg[i]=g[i]-dg[i];
      for (i=1;i<=n;i++) {
         hdg[i]=0.0;
         for (j=1;j<=n;j++) hdg[i] += hessin[i][j]*dg[j];
      }
      fac=fae=0.0;
      for (i=1;i<=n;i++) {
         fac += dg[i]*xi[i];
         fae += dg[i]*hdg[i];
      }
      fac=1.0/fac;
      fad=1.0/fae;
      for (i=1;i<=n;i++) dg[i]=fac*xi[i]-fad*hdg[i];
      for (i=1;i<=n;i++)
         for (j=1;j<=n;j++)
            hessin[i][j] += fac*xi[i]*xi[j]
               -fad*hdg[i]*hdg[j]+fae*dg[i]*dg[j];
      for (i=1;i<=n;i++) {
         xi[i]=0.0;
         for (j=1;j<=n;j++) xi[i] -= hessin[i][j]*g[j];
      }
   }
   nrerror("Too many iterations in DFPMIN");
}

#undef ITMAX
#undef EPS
#define TOL 2.0e-4

int ncom=0;   /* defining declarations */
float *pcom=0,*xicom=0,(*nrfunc)();
void (*nrdfun)();

void dlinmin(p,xi,n,fret,func,dfunc)
float p[],xi[],*fret,(*func)();
void (*dfunc)();
int n;
{
   int j;
   float xx,xmin,fx,fb,fa,bx,ax;
   float dbrent(),f1dim(),df1dim(),*vector();
   void mnbrak(),free_vector();

   ncom=n;
   pcom=vector(1,n);
   xicom=vector(1,n);
   nrfunc=func;
   nrdfun=dfunc;
   for (j=1;j<=n;j++) {
      pcom[j]=p[j];
      xicom[j]=xi[j];
   }
   ax=0.0;
   xx=1.0;
   bx=2.0;
   mnbrak(&ax,&xx,&bx,&fa,&fx,&fb,f1dim);
   *fret=dbrent(ax,xx,bx,f1dim,df1dim,TOL,&xmin);
   for (j=1;j<=n;j++) {
      xi[j] *= xmin;
      p[j] += xi[j];
   }
   free_vector(xicom,1,n);
   free_vector(pcom,1,n);
}

#undef TOL
void eclass(nf,n,lista,listb,m)
int nf[],lista[],listb[],n,m;
{
   int l,k,j;

   for (k=1;k<=n;k++) nf[k]=k;
   for (l=1;l<=m;l++) {
      j=lista[l];
      while (nf[j] != j) j=nf[j];
      k=listb[l];
      while (nf[k] != k) k=nf[k];
      if (j != k) nf[j]=k;
   }
   for (j=1;j<=n;j++)
      while (nf[j] != nf[nf[j]]) nf[j]=nf[nf[j]];
}
void eclazz(nf,n,equiv)
int n,nf[];
int (*equiv)();
{
   int kk,jj;

   nf[1]=1;
   for (jj=2;jj<=n;jj++) {
      nf[jj]=jj;
      for (kk=1;kk<=(jj-1);kk++) {
          nf[kk]=nf[nf[kk]];
          if ((*equiv)(jj,kk)) nf[nf[nf[kk]]]=jj;
      }
   }
   for (jj=1;jj<=n;jj++) nf[jj]=nf[nf[jj]];
}
/*----------------------------------------------------------------------------*/

#define PI 3.14159265
#define CA 0.0003
#define CB 1.0e-9

float el2(x,qqc,aa,bb)
float x,qqc,aa,bb;
{
   float a,b,c,d,e,f,g,em,eye,p,qc,y,z;
   int l;
   void nrerror();

   if (x == 0.0) return 0.0;
   else if (qqc) {
      qc=qqc;
      a=aa;
      b=bb;
      d=1.0+(c=x*x);
      p=sqrt((1.0+c*qc*qc)/d);
      d=x/d;
      c=d/(p+p);
      z=(eye=a)-b;
      a=0.5*(b+a);
      y=fabs(1.0/x);
      f=0.0;
      l=0;
      em=1.0;
      qc=fabs(qc);
      for (;;) {
         b += (eye*qc);
         g=(e=em*qc)/p;
         d += (f*g);
         f=c;
         eye=a;
         p += g;
         c=0.5*(d/p+c);
         g=em;
         em += qc;
         a=0.5*(b/em+a);
         y -= (e/y);
         if (y == 0.0) y=sqrt(e)*CB;
            if (fabs(g-qc) <= CA*g) break;
            qc=sqrt(e)*2.0;
            l *= 2;
            if (y<0.0) l++;
         }
      if (y<0.0) l++;
      e=(atan(em/y)+PI*l)*a/em;
      if (x < 0.0) e = -e;
      return e+c*z;
   } else nrerror("Bad qqc in routine EL2");
   return NaNFloat; // 2016.3.26
}

#undef PI
#undef CA
#undef CB
/*----------------------------------------------------------------------------*/
#if _MSVSC_ == 6

float erf(x)
float x;
{
   float gammp();

   return x < 0.0 ? -gammp(0.5,x*x) : gammp(0.5,x*x);
}
float erfc(x)
float x;
{
   float gammp(),gammq();

   return x < 0.0 ? 1.0+gammp(0.5,x*x) : gammq(0.5,x*x);
}
#endif
/*----------------------------------------------------------------------------*/

float erfcc(x)
float x;
{
   float t,z,ans;

   z=fabs(x);
   t=1.0/(1.0+0.5*z);
   ans=t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
      t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
      t*(-0.82215223+t*0.17087277)))))))));
   return  x >= 0.0 ? ans : 2.0-ans;
}
/*----------------------------------------------------------------------------*/

void eulsum(sum,term,jterm,wksp)
float *sum,term,wksp[];
int jterm;
{
   int j;
   static int nterm;
   float tmp,dum;

   if (jterm == 1) {
      nterm=1;
      *sum=0.5*(wksp[1]=term);
   } else {
      tmp=wksp[1];
      wksp[1]=term;
      for (j=1;j<=nterm-1;j++) {
         dum=wksp[j+1];
         wksp[j+1]=0.5*(wksp[j]+tmp);
         tmp=dum;
      }
      wksp[nterm+1]=0.5*(wksp[nterm]+tmp);
      if (fabs(wksp[nterm+1]) <= fabs(wksp[nterm]))
         *sum += (0.5*wksp[++nterm]);
      else
         *sum += wksp[nterm+1];
   }
}
/*----------------------------------------------------------------------------*/


float expdev(idum)
int *idum;
{
   float ran1();

   return -log(ran1(idum));
}
float factln(n)
int n;
{
   static float a[101];
   float gammln();
   void nrerror();

   if (n < 0) nrerror("Negative factorial in routine FACTLN");
   if (n <= 1) return 0.0;
   if (n <= 100) return a[n] ? a[n] : (a[n]=gammln(n+1.0));
   else return gammln(n+1.0);
}
/*----------------------------------------------------------------------------*/

float factrl(n)
int n;
{
   static int ntop=4;
   static float a[33]={1.0,1.0,2.0,6.0,24.0};
   int j;
   float gammln();
   void nrerror();

   if (n < 0) nrerror("Negative factorial in routine FACTRL");
   if (n > 32) return exp(gammln(n+1.0));
   while (ntop<n) {
      j=ntop++;
      a[ntop]=a[j]*ntop;
   }
   return a[n];
}
/*----------------------------------------------------------------------------*/

#define RAD (3.14159265/180.0)

void flmoon(n,nph,jd,frac)
int n,nph;
long *jd;
float *frac;
{
   int i;
   float am,as,c,t,t2,xtra;
   void nrerror();

   c=n+nph/4.0;
   t=c/1236.85;
   t2=t*t;
   as=359.2242+29.105356*c;
   am=306.0253+385.816918*c+0.010730*t2;
   *jd=2415020+28L*n+7L*nph;
   xtra=0.75933+1.53058868*c+((1.178e-4)-(1.55e-7)*t)*t2;
   if (nph == 0 || nph == 2)
      xtra += (0.1734-3.93e-4*t)*sin(RAD*as)-0.4068*sin(RAD*am);
   else if (nph == 1 || nph == 3)
      xtra += (0.1721-4.0e-4*t)*sin(RAD*as)-0.6280*sin(RAD*am);
   else nrerror("nph is unknown in FLMOON");
   i=(xtra >= 0.0 ? (int) floor(xtra) : (int) ceil(xtra-1.0));
   *jd += i;
   *frac=xtra-i;
}
/*----------------------------------------------------------------------------*/



#define ITMAX 200
#define EPS 1.0e-10
#define FREEALL free_vector(xi,1,n);free_vector(h,1,n);free_vector(g,1,n);

void frprmn(p,n,ftol,iter,fret,func,dfunc)
float p[],ftol,*fret,(*func)();
void (*dfunc)();
int n,*iter;
{
   int j,its;
   float gg,gam,fp,dgg;
   float *g,*h,*xi,*vector();
   void linmin(),nrerror(),free_vector();

   g=vector(1,n);
   h=vector(1,n);
   xi=vector(1,n);
   fp=(*func)(p);
   (*dfunc)(p,xi);
   for (j=1;j<=n;j++) {
      g[j] = -xi[j];
      xi[j]=h[j]=g[j];
   }
   for (its=1;its<=ITMAX;its++) {
      *iter=its;
      linmin(p,xi,n,fret,func);
      if (2.0*fabs(*fret-fp) <= ftol*(fabs(*fret)+fabs(fp)+EPS)) {
         FREEALL
         return;
      }
      fp=(*func)(p);
      (*dfunc)(p,xi);
      dgg=gg=0.0;
      for (j=1;j<=n;j++) {
         gg += g[j]*g[j];
/*        dgg += xi[j]*xi[j];   */
         dgg += (xi[j]+g[j])*xi[j];
      }
      if (gg == 0.0) {
         FREEALL
         return;
      }
      gam=dgg/gg;
      for (j=1;j<=n;j++) {
         g[j] = -xi[j];
         xi[j]=h[j]=g[j]+gam*h[j];
      }
   }
   nrerror("Too many iterations in FRPRMN");
}

#undef ITMAX
#undef EPS
#undef FREEALL
/*----------------------------------------------------------------------------*/

float gamdev(ia,idum)
int ia,*idum;
{
   int j;
   float am,e,s,v1,v2,x,y;
   float ran1();
   void nrerror();

   if (ia < 1) nrerror("Error in routine GAMDEV");
   if (ia < 6) {
      x=1.0;
      for (j=1;j<=ia;j++) x *= ran1(idum);
      x = -log(x);
   } else {
      do {
         do {
            do {
               v1=2.0*ran1(idum)-1.0;
               v2=2.0*ran1(idum)-1.0;
            } while (v1*v1+v2*v2 > 1.0);
            y=v2/v1;
            am=ia-1;
            s=sqrt(2.0*am+1.0);
            x=s*y+am;
         } while (x <= 0.0);
         e=(1.0+y*y)*exp(am*log(x/am)-s*y);
      } while (ran1(idum) > e);
   }
   return x;
}
/*----------------------------------------------------------------------------*/

float gammln(xx)
float xx;
{
   double x,tmp,ser;
   static double cof[6]={76.18009173,-86.50532033,24.01409822,
      -1.231739516,0.120858003e-2,-0.536382e-5};
   int j;

   x=xx-1.0;
   tmp=x+5.5;
   tmp -= (x+0.5)*log(tmp);
   ser=1.0;
   for (j=0;j<=5;j++) {
      x += 1.0;
      ser += cof[j]/x;
   }
   return -tmp+log(2.50662827465*ser);
}
float gammp(a,x)
float a,x;
{
   float gamser,gammcf,gln;
   void gser(),gcf(),nrerror();

   if (x < 0.0 || a <= 0.0) nrerror("Invalid arguments in routine GAMMP");
   if (x < (a+1.0)) {
      gser(&gamser,a,x,&gln);
      return gamser;
   } else {
      gcf(&gammcf,a,x,&gln);
      return 1.0-gammcf;
   }
}
float gammq(a,x)
float a,x;
{
   float gamser,gammcf,gln;
   void gcf(),gser(),nrerror();

   if (x < 0.0 || a <= 0.0) nrerror("Invalid arguments in routine GAMMQ");
   if (x < (a+1.0)) {
      gser(&gamser,a,x,&gln);
      return 1.0-gamser;
   } else {
      gcf(&gammcf,a,x,&gln);
      return gammcf;
   }
}
/*----------------------------------------------------------------------------*/

float gasdev(idum)
int *idum;
{
   static int iset=0;
   static float gset;
   float fac,r,v1,v2;
   float ran1();

   if  (iset == 0) {
      do {
         v1=2.0*ran1(idum)-1.0;
         v2=2.0*ran1(idum)-1.0;
         r=v1*v1+v2*v2;
      } while (r >= 1.0);
      fac=sqrt(-2.0*log(r)/r);
      gset=v1*fac;
      iset=1;
      return v2*fac;
   } else {
      iset=0;
      return gset;
   }
}
/*----------------------------------------------------------------------------*/

#define EPS 3.0e-11

void gauleg(x1,x2,x,w,n)
double x1,x2,x[],w[];
int n;
{
   int m,j,i;
   double z1,z,xm,xl,pp,p3,p2,p1;

   m=(n+1)/2;
   xm=0.5*(x2+x1);
   xl=0.5*(x2-x1);
   for (i=1;i<=m;i++)  {
      z=cos(3.141592654*(i-0.25)/(n+0.5));
      do {
         p1=1.0;
         p2=0.0;
         for (j=1;j<=n;j++) {
            p3=p2;
            p2=p1;
            p1=((2.0*j-1.0)*z*p2-(j-1.0)*p3)/j;
         }
         pp=n*(z*p1-p2)/(z*z-1.0);
         z1=z;
         z=z1-p1/pp;
      } while (fabs(z-z1) > EPS);
      x[i]=xm-xl*z;
      x[n+1-i]=xm+xl*z;
      w[i]=2.0*xl/((1.0-z*z)*pp*pp);
      w[n+1-i]=w[i];
   }
}

#undef EPS
/*----------------------------------------------------------------------------*/

#undef SWAP
#define SWAP(a,b) {float temp=(a);(a)=(b);(b)=temp;}

void gaussj(a,n,b,m)
float **a,**b;
int n,m;
{
   int *indxc,*indxr,*ipiv;
   int i,icol,irow,j,k,l,ll,*ivector();
   float big,dum,pivinv;
   void nrerror(),free_ivector();

   indxc=ivector(1,n);
   indxr=ivector(1,n);
   ipiv=ivector(1,n);
   for (j=1;j<=n;j++) ipiv[j]=0;
   for (i=1;i<=n;i++) {
      big=0.0;
      for (j=1;j<=n;j++)
         if (ipiv[j] != 1)
            for (k=1;k<=n;k++) {
               if (ipiv[k] == 0) {
                  if (fabs(a[j][k]) >= big) {
                     big=fabs(a[j][k]);
                     irow=j;
                     icol=k;
                  }
               } else if (ipiv[k] > 1) nrerror("GAUSSJ: Singular Matrix-1");
            }
      ++(ipiv[icol]);
      if (irow != icol) {
         for (l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l])
         for (l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l])
      }
      indxr[i]=irow;
      indxc[i]=icol;
      if (a[icol][icol] == 0.0) nrerror("GAUSSJ: Singular Matrix-2");
      pivinv=1.0/a[icol][icol];
      a[icol][icol]=1.0;
      for (l=1;l<=n;l++) a[icol][l] *= pivinv;
      for (l=1;l<=m;l++) b[icol][l] *= pivinv;
      for (ll=1;ll<=n;ll++)
         if (ll != icol) {
            dum=a[ll][icol];
            a[ll][icol]=0.0;
            for (l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
            for (l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
         }
   }
   for (l=n;l>=1;l--) {
      if (indxr[l] != indxc[l])
         for (k=1;k<=n;k++)
            SWAP(a[k][indxr[l]],a[k][indxc[l]]);
   }
   free_ivector(ipiv,1,n);
   free_ivector(indxr,1,n);
   free_ivector(indxc,1,n);
}

#undef SWAP
/*----------------------------------------------------------------------------*/

#define ITMAX 100
#define EPS 3.0e-7

void gcf(gammcf,a,x,gln)
float a,x,*gammcf,*gln;
{
   int n;
   float gold=0.0,g,fac=1.0,b1=1.0;
   float b0=0.0,anf,ana,an,a1,a0=1.0;
   float gammln();
   void nrerror();

   *gln=gammln(a);
   a1=x;
   for (n=1;n<=ITMAX;n++) {
      an=(float) n;
      ana=an-a;
      a0=(a1+a0*ana)*fac;
      b0=(b1+b0*ana)*fac;
      anf=an*fac;
      a1=x*a0+anf*a1;
      b1=x*b0+anf*b1;
      if (a1) {
         fac=1.0/a1;
         g=b1*fac;
         if (fabs((g-gold)/g) < EPS) {
            *gammcf=exp(-x+a*log(x)-(*gln))*g;
            return;
         }
         gold=g;
      }
   }
   nrerror("a too large, ITMAX too small in routine GCF");
}

#undef ITMAX
#undef EPS
/*----------------------------------------------------------------------------*/

#define R 0.61803399
#define C (1.0-R)
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

float golden(ax,bx,cx,f,tol,xmin)
float ax,bx,cx,tol,*xmin;
float (*f)();   /* ANSI: float (*f)(float); */
{
   float f0,f1,f2,f3,x0,x1,x2,x3;

   x0=ax;
   x3=cx;
   if (fabs(cx-bx) > fabs(bx-ax)) {
      x1=bx;
      x2=bx+C*(cx-bx);
   } else {
      x2=bx;
      x1=bx-C*(bx-ax);
   }
   f1=(*f)(x1);
   f2=(*f)(x2);
   while (fabs(x3-x0) > tol*(fabs(x1)+fabs(x2))) {
      if (f2 < f1) {
         SHFT(x0,x1,x2,R*x1+C*x3)
         SHFT(f0,f1,f2,(*f)(x2))
      } else {
         SHFT(x3,x2,x1,R*x2+C*x0)
         SHFT(f3,f2,f1,(*f)(x1))
      }
   }
   if (f1 < f2) {
      *xmin=x1;
      return f1;
   } else {
      *xmin=x2;
      return f2;
   }
}

#undef C
#undef R
/*----------------------------------------------------------------------------*/

#define ITMAX 100
#define EPS 3.0e-7

void gser(gamser,a,x,gln)
float a,x,*gamser,*gln;
{
   int n;
   float sum,del,ap;
   float gammln();
   void nrerror();

   *gln=gammln(a);
   if (x <= 0.0) {
      if (x < 0.0) nrerror("x less than 0 in routine GSER");
      *gamser=0.0;
      return;
   } else {
      ap=a;
      del=sum=1.0/a;
      for (n=1;n<=ITMAX;n++) {
         ap += 1.0;
         del *= x/ap;
         sum += del;
         if (fabs(del) < fabs(sum)*EPS) {
            *gamser=sum*exp(-x+a*log(x)-(*gln));
            return;
         }
      }
      nrerror("a too large, ITMAX too small in routine GSER");
      return;
   }
}

#undef ITMAX
#undef EPS
/*----------------------------------------------------------------------------*/

void hunt(xx,n,x,jlo)
int n,*jlo;
float xx[],x;
{
   int jm,jhi,inc,ascnd;

   ascnd=(xx[n] > xx[1]);
   if (*jlo <= 0 || *jlo > n) {
      *jlo=0;
      jhi=n+1;
   } else {
      inc=1;
      if (x >= xx[*jlo] == ascnd) {
         if (*jlo == n) return;
         jhi=(*jlo)+1;
         while (x >= xx[jhi] == ascnd) {
            *jlo=jhi;
            inc += inc;
            jhi=(*jlo)+inc;
            if (jhi > n) {
               jhi=n+1;
               break;
            }
         }
      } else {
         if (*jlo == 1) {
            *jlo=0;
            return;
         }
         jhi=(*jlo);
         *jlo -= 1;
         while (x < xx[*jlo] == ascnd) {
            jhi=(*jlo);
            inc += inc;
            *jlo=jhi-inc;
            if (*jlo < 1) {
               *jlo=0;
               break;
            }
         }
      }
   }
   while (jhi-(*jlo) != 1) {
      jm=(jhi+(*jlo)) >> 1;
      if (x > xx[jm] == ascnd)
         *jlo=jm;
      else
         jhi=jm;
   }
}
#undef SIGN
void indexx(n,arrin,indx)
int n,indx[];
float arrin[];
{
   int l,j,ir,indxt,i;
   float q;

   for (j=1;j<=n;j++) indx[j]=j;
   l=(n >> 1) + 1;
   ir=n;
   for (;;) {
      if (l > 1)
         q=arrin[(indxt=indx[--l])];
      else {
         q=arrin[(indxt=indx[ir])];
         indx[ir]=indx[1];
         if (--ir == 1) {
            indx[1]=indxt;
            return;
         }
      }
      i=l;
      j=l << 1;
      while (j <= ir) {
         if (j < ir && arrin[indx[j]] < arrin[indx[j+1]]) j++;
         if (q < arrin[indx[j]]) {
            indx[i]=indx[j];
            j += (i=j);
         }
         else j=ir+1;
      }
      indx[i]=indxt;
   }
}
#define IB1 1
#define IB2 2
#define IB5 16
#define IB18 131072

int irbit1(iseed)
unsigned long *iseed;
{
   unsigned long newbit;

   newbit = (*iseed & IB18) >> 17
      ^ (*iseed & IB5) >> 4
      ^ (*iseed & IB2) >> 1
      ^ (*iseed & IB1);
   *iseed=(*iseed << 1) | newbit;
   return (int) newbit;
}

#undef IB1
#undef IB2
#undef IB5
#undef IB18
#define IB1 1
#define IB2 2
#define IB5 16
#define IB18 131072
#define MASK IB1+IB2+IB5

int irbit2(iseed)
unsigned long *iseed;
{
   if (*iseed & IB18) {
      *iseed=((*iseed ^ MASK) << 1) | IB1;
      return 1;
   } else {
      *iseed <<= 1;
      return 0;
   }
}

#undef MASK
#undef IB18
#undef IB5
#undef IB2
#undef IB1
/*----------------------------------------------------------------------------*/


#define IGREG (15+31L*(10+12L*1582))

long julday(mm,id,iyyy)
int mm,id,iyyy;
{
   long jul;
   int ja,jy,jm;
   void nrerror();

   if (iyyy == 0) nrerror("JULDAY: there is no year zero.");
   if (iyyy < 0) ++iyyy;
   if (mm > 2) {
      jy=iyyy;
      jm=mm+1;
   } else {
      jy=iyyy-1;
      jm=mm+13;
   }
   jul = (long) (floor(365.25*jy)+floor(30.6001*jm)+id+1720995);
   if (id+31L*(mm+12L*iyyy) >= IGREG) {
      ja=(int)(0.01*jy); /* shik */
      jul += 2-ja+(int) (0.25*ja);
   }
   return jul;
}

#undef IGREG
/*----------------------------------------------------------------------------*/
/* #include "complex.h" !shik */

#define EPSS 6.e-8
#define MAXIT 100

void laguer(a,m,x,eps,polish)
fcomplex a[],*x;
int m,polish;
float eps;
{
   int j,iter;
   float err,dxold,cdx,abx;
   fcomplex sq,h,gp,gm,g2,g,b,d,dx,f,x1;
   void nrerror();

   dxold=Cabs(*x);
   for (iter=1;iter<=MAXIT;iter++) {
      b=a[m];
      err=Cabs(b);
      d=f=Complex(0.0,0.0);
      abx=Cabs(*x);
      for (j=m-1;j>=0;j--) {
         f=Cadd(Cmul(*x,f),d);
         d=Cadd(Cmul(*x,d),b);
         b=Cadd(Cmul(*x,b),a[j]);
         err=Cabs(b)+abx*err;
      }
      err *= EPSS;
      if (Cabs(b) <= err) return;
      g=Cdiv(d,b);
      g2=Cmul(g,g);
      h=Csub(g2,RCmul(2.0,Cdiv(f,b)));
      sq=Csqrt(RCmul((float) (m-1),Csub(RCmul((float) m,h),g2)));
      gp=Cadd(g,sq);
      gm=Csub(g,sq);
      if (Cabs(gp) < Cabs(gm))gp=gm;
      dx=Cdiv(Complex((float) m,0.0),gp);
      x1=Csub(*x,dx);
      if (x->r == x1.r && x->i == x1.i) return;
      *x=x1;
      cdx=Cabs(dx);
      if (iter > 6 && cdx >= dxold) return;
      dxold=cdx;
      if (!polish)
         if (cdx <= eps*Cabs(*x)) return;
   }
   nrerror("Too many iterations in routine LAGUER");
}

#undef EPSS
#undef MAXIT

/*---10.5---------------------------------------------------------------------*/
#define ITMAX 200

void powell(p,xi,n,ftol,iter,fret,func)
float p[],**xi,ftol,*fret,(*func)();
int n,*iter;
{
   int i,ibig,j;
   float t,fptt,fp,del;
   float *pt,*ptt,*xit,*vector();
   void linmin(),nrerror(),free_vector();

   pt=vector(1,n);
   ptt=vector(1,n);
   xit=vector(1,n);
   *fret=(*func)(p);
   for (j=1;j<=n;j++) pt[j]=p[j];
   for (*iter=1;;(*iter)++) {
      fp=(*fret);
      ibig=0;
      del=0.0;
      for (i=1;i<=n;i++) {
         for (j=1;j<=n;j++) xit[j]=xi[j][i];
         fptt=(*fret);
         linmin(p,xit,n,fret,func);
         if (fabs(fptt-(*fret)) > del) {
            del=fabs(fptt-(*fret));
            ibig=i;
         }
      }
      if (2.0*fabs(fp-(*fret)) <= ftol*(fabs(fp)+fabs(*fret))) {
         free_vector(xit,1,n);
         free_vector(ptt,1,n);
         free_vector(pt,1,n);
         return;
      }
      if (*iter == ITMAX) nrerror("Too many iterations in routine POWELL");
      for (j=1;j<=n;j++) {
         ptt[j]=2.0*p[j]-pt[j];
         xit[j]=p[j]-pt[j];
         pt[j]=p[j];
      }
      fptt=(*func)(ptt);
      if (fptt < fp) {
         t=2.0*(fp-2.0*(*fret)+fptt)*SQR(fp-(*fret)-del)-del*SQR(fp-fptt);
         if (t < 0.0) {
            linmin(p,xit,n,fret,func);
            for (j=1;j<=n;j++) xi[j][ibig]=xit[j];
         }
      }
   }
}
#undef ITMAX

#define TOL 2.0e-4

extern int ncom; /* defined in DLINMIN !shik */
extern float *pcom,*xicom,(*nrfunc)(); /* !shik */
extern void (*nrdfun)(); /* !shik */

void linmin(p,xi,n,fret,func)
float p[],xi[],*fret,(*func)();
int n;
{
   int j;
   float xx,xmin,fx,fb,fa,bx,ax;
   float brent(),f1dim(),*vector();
   void mnbrak(),free_vector();

   ncom=n;
   pcom=vector(1,n);
   xicom=vector(1,n);
   nrfunc=func;
   for (j=1;j<=n;j++) {
      pcom[j]=p[j];
      xicom[j]=xi[j];
   }
   ax=0.0;
   xx=1.0;
   bx=2.0;
   mnbrak(&ax,&xx,&bx,&fa,&fx,&fb,f1dim);
   *fret=brent(ax,xx,bx,f1dim,TOL,&xmin);
   for (j=1;j<=n;j++) {
      xi[j] *= xmin;
      p[j] += xi[j];
   }
   free_vector(xicom,1,n);
   free_vector(pcom,1,n);
}

#undef TOL

float f1dim(x)
float x;
{
   int j;
   float f,*xt,*vector();
   void free_vector();

   xt=vector(1,ncom);
   for (j=1;j<=ncom;j++) xt[j]=pcom[j]+x*xicom[j];
   f=(*nrfunc)(xt);
   free_vector(xt,1,ncom);
   return f;
}

/*----------------------------------------------------------------------------*/

void locate(xx,n,x,j)
float xx[],x;
int n,*j;
{
   int ascnd,ju,jm,jl;

   jl=0;
   ju=n+1;
   ascnd=xx[n] > xx[1];
   while (ju-jl > 1) {
      jm=(ju+jl) >> 1;
      if (x > xx[jm] == ascnd)
         jl=jm;
      else
         ju=jm;
   }
   *j=jl;
}
void lubksb(a,n,indx,b)
float **a,b[];
int n,*indx;
{
   int i,ii=0,ip,j;
   float sum;

   for (i=1;i<=n;i++) {
      ip=indx[i];
      sum=b[ip];
      b[ip]=b[i];
      if (ii)
         for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
      else if (sum) ii=i;
      b[i]=sum;
   }
   for (i=n;i>=1;i--) {
      sum=b[i];
      for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
      b[i]=sum/a[i][i];
   }
}
/*----------------------------------------------------------------------------*/

#define TINY 1.0e-20;

void ludcmp(a,n,indx,d)
int n,*indx;
float **a,*d;
{
   int i,imax,j,k;
   float big,dum,sum,temp;
   float *vv,*vector();
   void nrerror(),free_vector();

   vv=vector(1,n);
   *d=1.0;
   for (i=1;i<=n;i++) {
      big=(float)0.0;
      for (j=1;j<=n;j++)
         if ((temp=fabs(a[i][j])) > big) big=temp;
      if (big == 0.0) nrerror("Singular matrix in routine LUDCMP");
      vv[i]=1.0/big;
   }
   for (j=1;j<=n;j++) {
      for (i=1;i<j;i++) {
         sum=a[i][j];
         for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
         a[i][j]=sum;
      }
      big=(float)0.0;
      for (i=j;i<=n;i++) {
         sum=a[i][j];
         for (k=1;k<j;k++)
            sum -= a[i][k]*a[k][j];
         a[i][j]=sum;
         if ( (dum=vv[i]*fabs(sum)) >= big) {
            big=dum;
            imax=i;
         }
      }
      if (j != imax) {
         for (k=1;k<=n;k++) {
            dum=a[imax][k];
            a[imax][k]=a[j][k];
            a[j][k]=dum;
         }
         *d = -(*d);
         vv[imax]=vv[j];
      }
      indx[j]=imax;
      if (a[j][j] == 0.0) a[j][j]=TINY;
      if (j != n) {
         dum=1.0/(a[j][j]);
         for (i=j+1;i<=n;i++) a[i][j] *= dum;
      }
   }
   free_vector(vv,1,n);
}

#undef TINY
/*----------------------------------------------------------------------------*/



#define FUNC(x) ((*funk)(-log(x))/(x))

float midexp(funk,aa,bb,n)
float aa,bb;
float (*funk)();   /* ANSI: float (*funk)(float); */
int n;
{
   float x,tnm,sum,del,ddel,b,a;
   static float s;
   static int it;
   int j;

   b=(float)exp(-aa);
   a=(float)0.0;
   if (n == 1) {
      it=1;
      return (s=(b-a)*FUNC(0.5*(a+b)));
   } else {
      tnm=it;
      del=(b-a)/(3.0*tnm);
      ddel=del+del;
      x=a+0.5*del;
      sum=0.0;
      for (j=1;j<=it;j++) {
         sum += FUNC(x);
         x += ddel;
         sum += FUNC(x);
         x += del;
      }
      it *= 3;
      return (s=(s+(b-a)*sum/tnm)/3.0);
   }
}

#undef FUNC
#define FUNC(x) ((*funk)(1.0/(x))/((x)*(x)))

float midinf(funk,aa,bb,n)
float aa,bb;
int n;
float (*funk)();   /* ANSI: float (*funk)(float); */
{
   float x,tnm,sum,del,ddel,b,a;
   static float s;
   static int it;
   int j;

   b=1.0/aa;
   a=1.0/bb;
   if (n == 1) {
      it=1;
      return (s=(b-a)*FUNC(0.5*(a+b)));
   } else {
      tnm=it;
      del=(b-a)/(3.0*tnm);
      ddel=del+del;
      x=a+0.5*del;
      sum=0.0;
      for (j=1;j<=it;j++) {
         sum += FUNC(x);
         x += ddel;
         sum += FUNC(x);
         x += del;
      }
      it *= 3;
      return (s=(s+(b-a)*sum/tnm)/3.0);
   }
}

#undef FUNC
#define FUNC(x) ((*func)(x))

float midpnt(func,a,b,n)
float a,b;
int n;
float (*func)();   /* ANSI: float (*func)(float); */
{
   float x,tnm,sum,del,ddel;
   static float s;
   static int it;
   int j;

   if (n == 1) {
      it=1;
      return (s=(b-a)*FUNC(0.5*(a+b)));
   } else {
      tnm=it;
      del=(b-a)/(3.0*tnm);
      ddel=del+del;
      x=a+0.5*del;
      sum=0.0;
      for (j=1;j<=it;j++) {
         sum += FUNC(x);
         x += ddel;
         sum += FUNC(x);
         x += del;
      }
      it *= 3;
      s=(s+(b-a)*sum/tnm)/3.0;
      return s;
   }
}

#undef FUNC
/*----------------------------------------------------------------------------*/

#define FUNC(x) (2.0*(x)*(*funk)(aa+(x)*(x)))

float midsql(funk,aa,bb,n)
float aa,bb;
int n;
float (*funk)();   /* ANSI: float (*funk)(float); */
{
   float x,tnm,sum,del,ddel,b,a;
   static float s;
   static int it;
   int j;

   b=sqrt(bb-aa);
   a=0.0;
   if (n == 1) {
      it=1;
      return (s=(b-a)*FUNC(0.5*(a+b)));
   } else {
      tnm=it;
      del=(b-a)/(3.0*tnm);
      ddel=del+del;
      x=a+0.5*del;
      sum=0.0;
      for (j=1;j<=it;j++) {
         sum += FUNC(x);
         x += ddel;
         sum += FUNC(x);
         x += del;
      }
      it *= 3;
      return (s=(s+(b-a)*sum/tnm)/3.0);
   }
}

#undef FUNC
/*----------------------------------------------------------------------------*/

#define FUNC(x) (2.0*(x)*(*funk)(bb-(x)*(x)))

float midsqu(funk,aa,bb,n)
float aa,bb;
float (*funk)();   /* ANSI: float (*funk)(float); */
int n;
{
   float x,tnm,sum,del,ddel,b,a;
   static float s;
   static int it;
   int j;

   b=sqrt(bb-aa);
   a=0.0;
   if (n == 1) {
      it=1;
      return (s=(b-a)*FUNC(0.5*(a+b)));
   } else {
      tnm=it;
      del=(b-a)/(3.0*tnm);
      ddel=del+del;
      x=a+0.5*del;
      sum=0.0;
      for (j=1;j<=it;j++) {
         sum += FUNC(x);
         x += ddel;
         sum += FUNC(x);
         x += del;
      }
      it *= 3;
      return (s=(s+(b-a)*sum/tnm)/3.0);
   }
}

#undef FUNC
/*----------------------------------------------------------------------------*/

#define GOLD 1.618034
#define GLIMIT 100.0
#define TINY 1.0e-20
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : -fabs(a))
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

void mnbrak(ax,bx,cx,fa,fb,fc,func)
float *ax,*bx,*cx,*fa,*fb,*fc;
float (*func)();   /* ANSI: float (*func)(float); */
{
   float ulim,u,r,q,fu,dum;

   *fa=(*func)(*ax);
   *fb=(*func)(*bx);
   if (*fb > *fa) {
      SHFT(dum,*ax,*bx,dum)
      SHFT(dum,*fb,*fa,dum)
   }
   *cx=(*bx)+GOLD*(*bx-*ax);
   *fc=(*func)(*cx);
   while (*fb > *fc) {
      r=(*bx-*ax)*(*fb-*fc);
      q=(*bx-*cx)*(*fb-*fa);
      u=(*bx)-((*bx-*cx)*q-(*bx-*ax)*r)/
         (2.0*SIGN(MAX(fabs(q-r),TINY),q-r));
      ulim=(*bx)+GLIMIT*(*cx-*bx);
      if ((*bx-u)*(u-*cx) > 0.0) {
         fu=(*func)(u);
         if (fu < *fc) {
            *ax=(*bx);
            *bx=u;
            *fa=(*fb);
            *fb=fu;
            return;
         } else if (fu > *fb) {
            *cx=u;
            *fc=fu;
            return;
         }
         u=(*cx)+GOLD*(*cx-*bx);
         fu=(*func)(u);
      } else if ((*cx-u)*(u-ulim) > 0.0) {
         fu=(*func)(u);
         if (fu < *fc) {
            SHFT(*bx,*cx,u,*cx+GOLD*(*cx-*bx))
            SHFT(*fb,*fc,fu,(*func)(u))
         }
      } else if ((u-ulim)*(ulim-*cx) >= 0.0) {
         u=ulim;
         fu=(*func)(u);
      } else {
         u=(*cx)+GOLD*(*cx-*bx);
         fu=(*func)(u);
      }
      SHFT(*ax,*bx,*cx,u)
      SHFT(*fa,*fb,*fc,fu)
   }
}

#undef GOLD
#undef GLIMIT
#undef TINY
#undef MAX
#undef SIGN
#undef SHFT
/*----------------------------------------------------------------------------*/
#ifdef EXTRACOMPILATION

#define FREERETURN {free_matrix(alpha,1,n,1,n);free_vector(bet,1,n);\
   free_ivector(indx,1,n);return;}

void mnewt(ntrial,x,n,tolx,tolf)
int ntrial,n;
float x[],tolx,tolf;
{
   int k,i,*indx,*ivector();
   float errx,errf,d,*bet,**alpha,*vector(),**matrix();
   void usrfun(),ludcmp(),lubksb(),free_ivector(),free_vector(),
      free_matrix();

   indx=ivector(1,n);
   bet=vector(1,n);
   alpha=matrix(1,n,1,n);
   for (k=1;k<=ntrial;k++) {
      usrfun(x,alpha,bet);
      errf=0.0;
      for (i=1;i<=n;i++) errf += fabs(bet[i]);
      if (errf <= tolf) FREERETURN
      ludcmp(alpha,n,indx,&d);
      lubksb(alpha,n,indx,bet);
      errx=0.0;
      for (i=1;i<=n;i++) {
         errx += fabs(bet[i]);
         x[i] += bet[i];
      }
      if (errx <= tolx) FREERETURN
   }
   FREERETURN
}

#undef FREERETURN
#endif
/*----------------------------------------------------------------------------*/
void mprove(a,alud,n,indx,b,x)
float **a,**alud,b[],x[];
int n,indx[];
{
   int j,i;
   double sdp;
   float *r,*vector();
   void lubksb(),free_vector();

   r=vector(1,n);
   for (i=1;i<=n;i++) {
      sdp = -b[i];
      for (j=1;j<=n;j++) sdp += a[i][j]*x[j];
      r[i]=sdp;
   }
   lubksb(alud,n,indx,r);
   for (i=1;i<=n;i++) x[i] -= r[i];
   free_vector(r,1,n);
}
void pcshft(a,b,d,n)
float a,b,d[];
int n;
{
   int k,j;
   float fac,cnst;

   cnst=2.0/(b-a);
   fac=cnst;
   for (j=1;j<n;j++) {
      d[j] *= fac;
      fac *= cnst;
   }
   cnst=0.5*(a+b);
   for (j=0;j<=n-2;j++)
      for (k=n-2;k>=j;k--)
         d[k] -= cnst*d[k+1];
}
/*----------------------------------------------------------------------------*/

void piksr2(n,arr,brr)
int n;
float arr[],brr[];
{
   int i,j;
   float a,b;

   for (j=2;j<=n;j++) {
      a=arr[j];
      b=brr[j];
      i=j-1;
      while (i > 0 && arr[i] > a) {
         arr[i+1]=arr[i];
         brr[i+1]=brr[i];
         i--;
      }
      arr[i+1]=a;
      brr[i+1]=b;
   }
}
void piksrt(n,arr)
int n;
float arr[];
{
   int i,j;
   float a;

   for (j=2;j<=n;j++) {
      a=arr[j];
      i=j-1;
      while (i > 0 && arr[i] > a) {
         arr[i+1]=arr[i];
         i--;
      }
      arr[i+1]=a;
   }
}
/*----------------------------------------------------------------------------*/

float plgndr(l,m,x)
int l,m;
float x;
{
   float fact,pll,pmm,pmmp1,somx2;
   int i,ll;
   void nrerror();

   if (m < 0 || m > l || fabs(x) > 1.0)
      nrerror("Bad arguments in routine PLGNDR");
   pmm=1.0;
   if (m > 0) {
      somx2=sqrt((1.0-x)*(1.0+x));
      fact=1.0;
      for (i=1;i<=m;i++) {
         pmm *= -fact*somx2;
         fact += 2.0;
      }
   }
   if (l == m)
      return pmm;
   else {
      pmmp1=x*(2*m+1)*pmm;
      if (l == (m+1))
         return pmmp1;
      else {
         for (ll=(m+2);ll<=l;ll++) {
            pll=(x*(2*ll-1)*pmmp1-(ll+m-1)*pmm)/(ll-m);
            pmm=pmmp1;
            pmmp1=pll;
         }
         return pll;
      }
   }
}
/*----------------------------------------------------------------------------*/

#define PI 3.141592654

float poidev(xm,idum)
float xm;
int *idum;
{
   static float sq,alxm,g,oldm=(-1.0);
   float em,t,y;
   float ran1(),gammln();

   if (xm < 12.0) {
      if (xm != oldm) {
         oldm=xm;
         g=exp(-xm);
      }
      em = -1;
      t=1.0;
      do {
         em += 1.0;
         t *= ran1(idum);
      } while (t > g);
   } else {
      if (xm != oldm) {
         oldm=xm;
         sq=sqrt(2.0*xm);
         alxm=log(xm);
         g=xm*alxm-gammln(xm+1.0);
      }
      do {
         do {
            y=tan(PI*ran1(idum));
            em=sq*y+xm;
         } while (em < 0.0);
         em=floor(em);
         t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
      } while (ran1(idum) > t);
   }
   return em;
}

#undef PI
void polcoe(x,y,n,cof)
float x[],y[],cof[];
int n;
{
   int k,j,i;
   float phi,ff,b,*s,*vector();
   void free_vector();

   s=vector(0,n);
   for (i=0;i<=n;i++) s[i]=cof[i]=0.0;
   s[n] = -x[0];
   for (i=1;i<=n;i++) {
      for (j=n-i;j<=n-1;j++)
         s[j] -= x[i]*s[j+1];
      s[n] -= x[i];
   }
   for (j=0;j<=n;j++) {
      phi=n+1;
      for (k=n;k>=1;k--)
         phi=k*s[k]+x[j]*phi;
      ff=y[j]/phi;
      b=1.0;
      for (k=n;k>=0;k--) {
         cof[k] += b*ff;
         b=s[k]+x[j]*b;
      }
   }
   free_vector(s,0,n);
}
/*----------------------------------------------------------------------------*/

void polcof(xa,ya,n,cof)
float xa[],ya[],cof[];
int n;
{
   int k,j,i;
   float xmin,dy,*x,*y,*vector();
   void polint(),free_vector();

   x=vector(0,n);
   y=vector(0,n);
   for (j=0;j<=n;j++) {
      x[j]=xa[j];
      y[j]=ya[j];
   }
   for (j=0;j<=n;j++) {
      polint(x-1,y-1,n+1-j,0.0,&cof[j],&dy);
      xmin=1.0e38;
      k = -1;
      for (i=0;i<=n-j;i++) {
         if (fabs(x[i]) < xmin) {
            xmin=fabs(x[i]);
            k=i;
         }
         if (x[i])  y[i]=(y[i]-cof[j])/x[i];
      }
      for (i=k+1;i<=n-j;i++) {
         y[i-1]=y[i];
         x[i-1]=x[i];
      }
   }
   free_vector(y,0,n);
   free_vector(x,0,n);
}
void poldiv(u,n,v,nv,q,r)
float u[],v[],q[],r[];
int n,nv;
{
   int k,j;

   for (j=0;j<=n;j++) {
      r[j]=u[j];
      q[j]=0.0;
   }
   for (k=n-nv;k>=0;k--) {
      q[k]=r[nv+k]/v[nv];
      for (j=nv+k-1;j>=k;j--)
         r[j] -= q[k]*v[j-k];
   }
   r[nv]=0.0;
}
void polin2(x1a,x2a,ya,m,n,x1,x2,y,dy)
float x1a[],x2a[],**ya,x1,x2,*y,*dy;
int m,n;
{
   int j;
   float *ymtmp,*vector();
   void polint(),free_vector();

   ymtmp=vector(1,m);
   for (j=1;j<=m;j++) {
      polint(x2a,ya[j],n,x2,&ymtmp[j],dy);
   }
   polint(x1a,ymtmp,m,x1,y,dy);
   free_vector(ymtmp,1,m);
}
/*----------------------------------------------------------------------------*/

void polint(xa,ya,n,x,y,dy)
float xa[],ya[],x,*y,*dy;
int n;
{
   int i,m,ns=1;
   float den,dif,dift,ho,hp,w;
   float *c,*d,*vector();
   void nrerror(),free_vector();

   dif=fabs(x-xa[1]);
   c=vector(1,n);
   d=vector(1,n);
   for (i=1;i<=n;i++) {
      if ( (dift=fabs(x-xa[i])) < dif) {
         ns=i;
         dif=dift;
      }
      c[i]=ya[i];
      d[i]=ya[i];
   }
   *y=ya[ns--];
   for (m=1;m<n;m++) {
      for (i=1;i<=n-m;i++) {
         ho=xa[i]-x;
         hp=xa[i+m]-x;
         w=c[i+1]-d[i];
         if ( (den=ho-hp) == 0.0) nrerror("Error in routine POLINT");
         den=w/den;
         d[i]=hp*den;
         c[i]=ho*den;
      }
      *y += (*dy=(2*ns < (n-m) ? c[ns+1] : d[ns--]));
   }
   free_vector(d,1,n);
   free_vector(c,1,n);
}
/*----------------------------------------------------------------------------*/
#define M 7
#define NSTACK 50
#define FM 7875
#define FA 211
#define FC 1663

void qcksrt(n,arr)
int n;
float arr[]; /* [1..n] */
{
   int l=1,jstack=0,j,ir,iq,i;
   int istack[NSTACK+1];
   long int fx=0L;
   float a;
   void nrerror();

   ir=n;
   for (;;) {
      if (ir-l < M) {
         for (j=l+1;j<=ir;j++) {
            a=arr[j];
            /* for (i=j-1;arr[i]>a && i>0;i--)   2K.0530 */
            for (i=j-1;i>0 && arr[i]>a;i--)
               arr[i+1]=arr[i];
            arr[i+1]=a;
         }
         if (jstack == 0) return;
         ir=istack[jstack--];
         l=istack[jstack--];
      } else {
         i=l;
         j=ir;
         fx=(fx*FA+FC) % FM;
         iq=l+((ir-l+1)*fx)/FM;
         a=arr[iq];
         arr[iq]=arr[l];
         for (;;) {
            while (j > 0 && a < arr[j]) j--;
            if (j <= i) {
               arr[i]=a;
               break;
            }
            arr[i++]=arr[j];
            while (a > arr[i] && i <= n) i++;
            if (j <= i) {
               arr[(i=j)]=a;
               break;
            }
            arr[j--]=arr[i];
         }
         if (ir-i >= i-l) {
            istack[++jstack]=i+1;
            istack[++jstack]=ir;
            ir=i-1;
         } else {
            istack[++jstack]=l;
            istack[++jstack]=i-1;
            l=i+1;
         }
         if (jstack > NSTACK) nrerror("NSTACK too small in QCKSRT");
      }
   }
}

#undef M
#undef NSTACK
#undef FM
#undef FA
#undef FC
float qgaus(func,a,b)
float a,b;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int j;
   float xr,xm,dx,s;
   static float x[]={0.0,0.1488743389,0.4333953941,
      0.6794095682,0.8650633666,0.97390652};
   static float w[]={0.0,0.2955242247,0.2692667193,
      0.2190863625,0.1494513491,0.06667134};

   xm=0.5*(b+a);
   xr=0.5*(b-a);
   s=0;
   for (j=1;j<=5;j++) {
      dx=xr*x[j];
      s += w[j]*((*func)(xm+dx)+(*func)(xm-dx));
   }
   return s *= xr;
}
/*----------------------------------------------------------------------------*/

#define EPS 1.0e-6
#define JMAX 20
#define JMAXP JMAX+1
#define K 5

float qromb(func,a,b)
float a,b;
float (*func)();
{
   float ss,dss,trapzd();
   float s[JMAXP+1],h[JMAXP+1];
   int j;
   void polint(),nrerror();

   h[1]=1.0;
   for (j=1;j<=JMAX;j++) {
      s[j]=trapzd(func,a,b,j);
      if (j >= K) {
         polint(&h[j-K],&s[j-K],K,0.0,&ss,&dss);
         if (fabs(dss) < EPS*fabs(ss)) return ss;
      }
      s[j+1]=s[j];
      h[j+1]=0.25*h[j];
   }
   nrerror("Too many steps in routine QROMB");
   return NaNFloat; // 2016.3.26
}

#undef EPS
#undef JMAX
#undef JMAXP
#undef K
/*----------------------------------------------------------------------------*/

#define EPS 1.0e-6
#define JMAX 14
#define JMAXP JMAX+1
#define K 5

float qromo(func,a,b,choose)
float a,b;
float (*func)();
float (*choose)();   /* ANSI: float choose(float(*)(float),float,float,int); */
{
   int j;
   float ss,dss,h[JMAXP+1],s[JMAXP+1];
   void polint(),nrerror();

   h[1]=1.0;
   for (j=1;j<=JMAX;j++) {
      s[j]=(*choose)(func,a,b,j);
      if (j >= K) {
         polint(&h[j-K],&s[j-K],K,0.0,&ss,&dss);
         if (fabs(dss) < EPS*fabs(ss)) return ss;
      }
      s[j+1]=s[j];
      h[j+1]=h[j]/9.0;
   }
   nrerror("Too many steps in routing QROMO");
   return NaNFloat; // 2016.3.26
}

#undef EPS
#undef JMAX
#undef JMAXP
#undef K
/*----------------------------------------------------------------------------*/

#define ITMAX 20
#define TINY 1.0e-6

void qroot(p,n,b,c,eps)
float p[],*b,*c,eps;
int n;
{
   int iter,i;
   float sc,sb,s,rc,rb,r,dv,delc,delb;
   float *q,*qq,*rem,*vector();
   float d[3];
   void poldiv(),nrerror(),free_vector();

   q=vector(0,n);
   qq=vector(0,n);
   rem=vector(0,n);
   d[2]=1.0;
   for (iter=1;iter<=ITMAX;iter++) {
      d[1]=(*b);
      d[0]=(*c);
      poldiv(p,n,d,2,q,rem);
      s=rem[0];
      r=rem[1];
      poldiv(q,(n-1),d,2,qq,rem);
      sc = -rem[0];
      rc = -rem[1];
      for (i=n-1;i>=0;i--) q[i+1]=q[i];
      q[0]=0.0;
      poldiv(q,n,d,2,qq,rem);
      sb = -rem[0];
      rb = -rem[1];
      dv=1.0/(sb*rc-sc*rb);
      *b += (delb=(r*sc-s*rc)*dv);
      *c += (delc=(-r*sb+s*rb)*dv);
      if ((fabs(delb) <= eps*fabs(*b) || fabs(*b) < TINY)
      &&  (fabs(delc) <= eps*fabs(*c) || fabs(*c) < TINY)) {
         free_vector(rem,0,n);
         free_vector(qq,0,n);
         free_vector(q,0,n);
         return;
      }
   }
   nrerror("Too many iterations in routine QROOT");
}

#undef ITMAX
#undef TINY
/*----------------------------------------------------------------------------*/

#define EPS 1.0e-6
#define JMAX 20

float qsimp(func,a,b)
float a,b;
float (*func)();
{
   int j;
   float s,st,ost,os,trapzd();
   void nrerror();

   ost = os =  -1.0e30;
   for (j=1;j<=JMAX;j++) {
      st=trapzd(func,a,b,j);
      s=(4.0*st-ost)/3.0;
      if (fabs(s-os) < EPS*fabs(os)) return s;
      os=s;
      ost=st;
   }
   nrerror("Too many steps in routine QSIMP");
   return NaNFloat; // 2016.3.26
}

#undef EPS
#undef JMAX
/*----------------------------------------------------------------------------*/

#define EPS 1.0e-5
#define JMAX 20

float qtrap(func,a,b)
float a,b;
float (*func)();
{
   int j;
   float s,olds,trapzd();
   void nrerror();

   olds = -1.0e30;
   for (j=1;j<=JMAX;j++) {
      s=trapzd(func,a,b,j);
      if (fabs(s-olds) < EPS*fabs(olds)) return s;
      olds=s;
   }
   nrerror("Too many steps in routine QTRAP");
   return NaNFloat; // 2016.3.26
}

#undef EPS
#undef JMAX

/*---4.6----------------------------------------------------------------------*/

#ifdef EXTRACOMPILATION

static float xsav,ysav;
static float (*nrfunc)(); /* ANSI: static float (*nrfunc)(float,float,float);
*/

float quad3d(func,x1,x2)
float x1,x2,(*func)();
{
   float qgaus(),f1();

   nrfunc=func;
   return qgaus(f1,x1,x2);
}

float f1(x)
float x;
{
   float qgaus(),f2();
   float yy1(),yy2();   /* ANSI: float yy1(float),yy2(float); */

   xsav=x;
   return qgaus(f2,yy1(x),yy2(x));
}

float f2(y)
float y;
{
   float qgaus(),f3();
   float z1(),z2(); /* ANSI: float z1(float,float),z2(float,float); */

   ysav=y;
   return qgaus(f3,z1(xsav,y),z2(xsav,y));
}

float f3(z)
float z;
{
   return (*nrfunc)(xsav,ysav,z);
}
#endif

/*----------------------------------------------------------------------------*/


float ran0(idum)
int *idum;
{
   static float y,maxran,v[98];
   float dum;
   static int iff=0;
   int j;
   unsigned i,k;
   void nrerror();

   if (*idum < 0 || iff == 0) {
      iff=1;
      i=2;
      do {
         k=i;
         i<<=1;
      } while (i);
      maxran=k;
      srand(*idum);
      *idum=1;
      for (j=1;j<=97;j++) dum=rand();
      for (j=1;j<=97;j++) v[j]=rand();
      y=rand();
   }
   j=(int)(1+97.0*y/maxran); /* shik */
   if (j > 97 || j < 1) nrerror("RAN0: This cannot happen.");
   y=v[j];
   v[j]=rand();
   return y/maxran;
}
#define M1 259200
#define IA1 7141
#define IC1 54773
#define RM1 (1.0/M1)
#define M2 134456
#define IA2 8121
#define IC2 28411
#define RM2 (1.0/M2)
#define M3 243000
#define IA3 4561
#define IC3 51349

float ran1(idum)
int *idum;
{
   static long ix1,ix2,ix3;
   static float r[98];
   float temp;
   static int iff=0;
   int j;
   void nrerror();

   if (*idum < 0 || iff == 0) {
      iff=1;
      ix1=(IC1-(*idum)) % M1;
      ix1=(IA1*ix1+IC1) % M1;
      ix2=ix1 % M2;
      ix1=(IA1*ix1+IC1) % M1;
      ix3=ix1 % M3;
      for (j=1;j<=97;j++) {
         ix1=(IA1*ix1+IC1) % M1;
         ix2=(IA2*ix2+IC2) % M2;
         r[j]=(ix1+ix2*RM2)*RM1;
      }
      *idum=1;
   }
   ix1=(IA1*ix1+IC1) % M1;
   ix2=(IA2*ix2+IC2) % M2;
   ix3=(IA3*ix3+IC3) % M3;
   j=1 + ((97*ix3)/M3);
   if (j > 97 || j < 1) nrerror("RAN1: This cannot happen.");
   temp=r[j];
   r[j]=(ix1+ix2*RM2)*RM1;
   return temp;
}

#undef M1
#undef IA1
#undef IC1
#undef RM1
#undef M2
#undef IA2
#undef IC2
#undef RM2
#undef M3
#undef IA3
#undef IC3
/*----------------------------------------------------------------------------*/

#define M 714025
#define IA 1366
#define IC 150889

float ran2(idum)
long *idum;
{
   static long iy,ir[98];
   static int iff=0;
   int j;
   void nrerror();

   if (*idum < 0 || iff == 0) {
      iff=1;
      if ((*idum=(IC-(*idum)) % M) < 0) *idum = -(*idum);
      for (j=1;j<=97;j++) {
         *idum=(IA*(*idum)+IC) % M;
         ir[j]=(*idum);
      }
      *idum=(IA*(*idum)+IC) % M;
      iy=(*idum);
   }
   j=(int)(1 + 97.0*iy/M); /* shik */
   if (j > 97 || j < 1) nrerror("RAN2: This cannot happen.");
   iy=ir[j];
   *idum=(IA*(*idum)+IC) % M;
   ir[j]=(*idum);
   return (float) iy/M;
}

#undef M
#undef IA
#undef IC
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

float ran3(idum)
int *idum;
{
   static int inext,inextp;
   static long ma[56];
   static int iff=0;
   long mj,mk;
   int i,ii,k;

   if (*idum < 0 || iff == 0) {
      iff=1;
      mj=MSEED-(*idum < 0 ? -*idum : *idum);
      mj %= MBIG;
      ma[55]=mj;
      mk=1;
      for (i=1;i<=54;i++) {
         ii=(21*i) % 55;
         ma[ii]=mk;
         mk=mj-mk;
         if (mk < MZ) mk += MBIG;
         mj=ma[ii];
      }
      for (k=1;k<=4;k++)
         for (i=1;i<=55;i++) {
            ma[i] -= ma[1+(i+30) % 55];
            if (ma[i] < MZ) ma[i] += MBIG;
         }
      inext=0;
      inextp=31;
      *idum=1;
   }
   if (++inext == 56) inext=1;
   if (++inextp == 56) inextp=1;
   mj=ma[inext]-ma[inextp];
   if (mj < MZ) mj += MBIG;
   ma[inext]=mj;
   return mj*FAC;
}

#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
#define IM 11979
#define IA 430
#define IC 2531
#define NACC 24
#define IB1 1L
#define IB3 4L
#define IB4 8L
#define IB32 0x80000000L
#define MASK IB1+IB3+IB4

/* typedef struct IMMENSE {unsigned long l,r;} immense; !shik */

float ran4(idum)
int *idum;
{
   static int newkey,iff=0;
   static immense inp,key,jot;
   static double pow[66];
   unsigned long isav,isav2;
   int j;
   double r4;
   void des();

   if (*idum < 0 || iff == 0) {
      iff=1;
      *idum %= IM;
      if (*idum < 0) *idum += IM;
      pow[1]=0.5;
      key.r=key.l=inp.r=inp.l=0L;
      for (j=1;j<=64;j++) {
         *idum = ((long) (*idum)*IA+IC) % IM;
         isav=2*(unsigned long)(*idum)/IM;
         if (isav) isav=IB32;
         isav2=(4*(unsigned long)(*idum)/IM) % 2;
         if (isav2) isav2=IB32;
         if (j <= 32) {
            key.r=(key.r >>= 1) | isav;
            inp.r=(inp.r >>= 1) | isav2;
         } else {
            key.l=(key.l >>= 1) | isav;
            inp.l=(inp.l >>= 1) | isav2;
         }
         pow[j+1]=0.5*pow[j];
      }
      newkey=1;
   }
   isav=inp.r & IB32;
   if (isav) isav=1L;
   if (inp.l & IB32)
      inp.r=((inp.r ^ MASK) << 1) | IB1;
   else
      inp.r <<= 1;
   inp.l=(inp.l << 1) | isav;
   des(inp,key,&newkey,0,&jot);
   r4=0.0;
   for (j=1;j<=NACC;j++) {
      if (jot.r & IB1) r4 += pow[j];
      jot.r >>= 1;
   }
   return r4;
}

#undef IM
#undef IA
#undef IC
#undef NACC
#undef IB1
#undef IB3
#undef IB4
#undef IB32
#undef MASK
void rank(n,indx,irank)
int indx[],irank[],n;
{
   int j;

   for (j=1;j<=n;j++) irank[indx[j]]=j;
}
/*----------------------------------------------------------------------------*/

#define TINY 1.0e-25
#define FREERETURN {free_vector(d,1,n);free_vector(c,1,n);return;}

void ratint(xa,ya,n,x,y,dy)
float xa[],ya[],x,*y,*dy;
int n;
{
   int m,i,ns=1;
   float w,t,hh,h,dd,*c,*d,*vector();
   void nrerror(),free_vector();

   c=vector(1,n);
   d=vector(1,n);
   hh=fabs(x-xa[1]);
   for (i=1;i<=n;i++) {
      h=fabs(x-xa[i]);
      if (h == 0.0) {
         *y=ya[i];
         *dy=0.0;
         FREERETURN
      } else if (h < hh) {
         ns=i;
         hh=h;
      }
      c[i]=ya[i];
      d[i]=ya[i]+TINY;
   }
   *y=ya[ns--];
   for (m=1;m<n;m++) {
      for (i=1;i<=n-m;i++) {
         w=c[i+1]-d[i];
         h=xa[i+m]-x;
         t=(xa[i]-x)*d[i]/h;
         dd=t-c[i+1];
         if (dd == 0.0) nrerror("Error in routine RATINT");
         dd=w/dd;
         d[i]=c[i+1]*dd;
         c[i]=t*dd;
      }
      *y += (*dy=(2*ns < (n-m) ? c[ns+1] : d[ns--]));
   }
   FREERETURN
}

#undef TINY
#undef FREERETURN
/*----------------------------------------------------------------------------*/


#define JMAX 40

float rtbis(func,x1,x2,xacc)
float x1,x2,xacc;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int j;
   float dx,f,fmid,xmid,rtb;
   void nrerror();

   f=(*func)(x1);
   fmid=(*func)(x2);
   if (f*fmid >= 0.0) nrerror("Root must be bracketed for bisection in RTBIS");
   rtb = f < 0.0 ? (dx=x2-x1,x1) : (dx=x1-x2,x2);
   for (j=1;j<=JMAX;j++) {
      fmid=(*func)(xmid=rtb+(dx *= 0.5));
      if (fmid <= 0.0) rtb=xmid;
      if (fabs(dx) < xacc || fmid == 0.0) return rtb;
   }
   nrerror("Too many bisections in RTBIS");
   return NaNFloat; // 2016.3.26
}

#undef JMAX
/*----------------------------------------------------------------------------*/

#define MAXIT 30

float rtflsp(func,x1,x2,xacc)
float x1,x2,xacc;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int j;
   float fl,fh,xl,xh,swap,dx,del,f,rtf;
   void nrerror();

   fl=(*func)(x1);
   fh=(*func)(x2);
   if (fl*fh > 0.0) nrerror("Root must be bracketed in RTFLSP");
   if (fl < 0.0) {
      xl=x1;
      xh=x2;
   } else {
      xl=x2;
      xh=x1;
      swap=fl;
      fl=fh;
      fh=swap;
   }
   dx=xh-xl;
   for (j=1;j<=MAXIT;j++) {
      rtf=xl+dx*fl/(fl-fh);
      f=(*func)(rtf);
      if (f < 0.0) {
         del=xl-rtf;
         xl=rtf;
         fl=f;
      } else {
         del=xh-rtf;
         xh=rtf;
         fh=f;
      }
      dx=xh-xl;
      if (fabs(del) < xacc || f == 0.0) return rtf;
   }
   nrerror("Maximum number of iterations exceeded in RTFLSP");
   return NaNFloat; // 2016.3.26
}

#undef MAXIT
/*----------------------------------------------------------------------------*/

#define JMAX 20

float rtnewt(funcd,x1,x2,xacc)
float x1,x2,xacc;
void (*funcd)();   /* ANSI: void (*funcd)(float,float *,float *); */
{
   int j;
   float df,dx,f,rtn;
   void nrerror();

   rtn=0.5*(x1+x2);
   for (j=1;j<=JMAX;j++) {
      (*funcd)(rtn,&f,&df);
      dx=f/df;
      rtn -= dx;
      if ((x1-rtn)*(rtn-x2) < 0.0)
         nrerror("Jumped out of brackets in RTNEWT");
      if (fabs(dx) < xacc) return rtn;
   }
   nrerror("Maximum number of iterations exceeded in RTNEWT");
   return NaNFloat; // 2016.3.26
}

#undef JMAX
/*----------------------------------------------------------------------------*/

#define MAXIT 100

float rtsafe(funcd,x1,x2,xacc)
float x1,x2,xacc;
void (*funcd)();   /* ANSI: void (*funcd)(float,float *,float *); */
{
   int j;
   float df,dx,dxold,f,fh,fl;
   float swap,temp,xh,xl,rts;
   void nrerror();

   (*funcd)(x1,&fl,&df);
   (*funcd)(x2,&fh,&df);
   if (fl*fh >= 0.0) nrerror("Root must be bracketed in RTSAFE");
   if (fl < 0.0) {
      xl=x1;
      xh=x2;
   } else {
      xh=x1;
      xl=x2;
      swap=fl;
      fl=fh;
      fh=swap;
   }
   rts=0.5*(x1+x2);
   dxold=fabs(x2-x1);
   dx=dxold;
   (*funcd)(rts,&f,&df);
   for (j=1;j<=MAXIT;j++) {
      if ((((rts-xh)*df-f)*((rts-xl)*df-f) >= 0.0)
         || (fabs(2.0*f) > fabs(dxold*df))) {
         dxold=dx;
         dx=0.5*(xh-xl);
         rts=xl+dx;
         if (xl == rts) return rts;
      } else {
         dxold=dx;
         dx=f/df;
         temp=rts;
         rts -= dx;
         if (temp == rts) return rts;
      }
      if (fabs(dx) < xacc) return rts;
      (*funcd)(rts,&f,&df);
      if (f < 0.0) {
         xl=rts;
         fl=f;
      } else {
         xh=rts;
         fh=f;
      }
   }
   nrerror("Maximum number of iterations exceeded in RTSAFE");
   return NaNFloat; // 2016.3.26
}

#undef MAXIT
/*----------------------------------------------------------------------------*/

#define MAXIT 30

float rtsec(func,x1,x2,xacc)
float x1,x2,xacc;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int j;
   float fl,f,dx,swap,xl,rts;
   void nrerror();

   fl=(*func)(x1);
   f=(*func)(x2);
   if (fabs(fl) < fabs(f)) {
      rts=x1;
      xl=x2;
      swap=fl;
      fl=f;
      f=swap;
   } else {
      xl=x1;
      rts=x2;
   }
   for (j=1;j<=MAXIT;j++) {
      dx=(xl-rts)*f/(f-fl);
      xl=rts;
      fl=f;
      rts += dx;
      f=(*func)(rts);
      if (fabs(dx) < xacc || f == 0.0) return rts;
   }
   nrerror("Maximum number of iterations exceeded in RTSEC");
   return MkNaNFloat(rts); /* 20030612 */
}

#undef MAXIT
/*---------------------------------------------------*/

#define ISCR 60
#define JSCR 21
#define BLANK ' '
#define ZERO '-'
#define YY 'l'
#define XX '-'
#define FF 'x'

void scrsho(fx)
float (*fx)();   /* ANSI: float (*fx)(float); */
{
   int jz,j,i;
   float ysml,ybig,x2,x1,x,dyj,dx,y[ISCR+1];
   char scr[ISCR+1][JSCR+1];

   for (;;) {
      printf("\nEnter x1 x2 (x1=x2 to stop):\n");
      scanf("%lf %lf",&x1,&x2);
      if (x1 == x2) break;
      for (j=1;j<=JSCR;j++)
         scr[1][j]=scr[ISCR][j]=YY;
      for (i=2;i<=(ISCR-1);i++) {
         scr[i][1]=scr[i][JSCR]=XX;
         for (j=2;j<=(JSCR-1);j++)
            scr[i][j]=BLANK;
      }
      dx=(x2-x1)/(ISCR-1);
      x=x1;
      ysml=ybig=0.0;
      for (i=1;i<=ISCR;i++) {
         y[i]=(*fx)(x);
         if (y[i] < ysml)  ysml=y[i];
         if (y[i] > ybig)  ybig=y[i];
         x += dx;
      }
      if (ybig == ysml) ybig=ysml+1.0;
      dyj=(JSCR-1)/(ybig-ysml);
      jz=1-(int) (ysml*dyj);
      for (i=1;i<=ISCR;i++) {
         scr[i][jz]=ZERO;
         j=1+(int) ((y[i]-ysml)*dyj);
         scr[i][j]=FF;
      }
      printf(" %10.3f ",ybig);
      for (i=1;i<=ISCR;i++) printf("%c",scr[i][JSCR]);
      printf("\n");
      for (j=(JSCR-1);j>=2;j--) {
         printf("%12s"," ");
         for (i=1;i<=ISCR;i++) printf("%c",scr[i][j]);
         printf("\n");
      }
      printf(" %10.3f ",ysml);
      for (i=1;i<=ISCR;i++) printf("%c",scr[i][1]);
      printf("\n");
      printf("%8s %10.3f %44s %10.3f\n"," ",x1," ",x2);
   }
}

#undef ISCR
#undef JSCR
#undef BLANK
#undef ZERO
#undef YY
#undef XX
#undef FF
/*----------------------------------------------------------------------------*/

#define ALN2I 1.442695022
#define TINY 1.0e-5

void shell(n,arr)
float arr[];
int n;
{
   int nn,m,j,i,lognb2;
   float t;

   lognb2=(int)(log((double) n)*ALN2I+TINY); /* shik */
   m=n;
   for (nn=1;nn<=lognb2;nn++) {
      m >>= 1;
      for (j=m+1;j<=n;j++) {
         i=j-m;
         t=arr[j];
         while (i >= 1 && arr[i] > t) {
            arr[i+m]=arr[i];
            i -= m;
         }
         arr[i+m]=t;
      }
   }
}

#undef ALN2I
#undef TINY
/*----------------------------------------------------------------------------*/

void simp1(a,mm,ll,nll,iabf,kp,bmax)
float **a,*bmax;
int mm,ll[],nll,iabf,*kp;
{
   int k;
   float test;

   *kp=ll[1];
   *bmax=a[mm+1][*kp+1];
   for (k=2;k<=nll;k++) {
      if (iabf == 0)
         test=a[mm+1][ll[k]+1]-(*bmax);
      else
         test=fabs(a[mm+1][ll[k]+1])-fabs(*bmax);
      if (test > 0.0) {
         *bmax=a[mm+1][ll[k]+1];
         *kp=ll[k];
      }
   }
}
#define EPS 1.0e-6

void simp2(a,n,l2,nl2,ip,kp,q1)
int n,l2[],nl2,*ip,kp;
float **a,*q1;
{
   int k,ii,i;
   float qp,q0,q;

   *ip=0;
   for (i=1;i<=nl2;i++) {
      if (a[l2[i]+1][kp+1] < -EPS) {
         *q1 = -a[l2[i]+1][1]/a[l2[i]+1][kp+1];
         *ip=l2[i];
         for (i=i+1;i<=nl2;i++) {
            ii=l2[i];
            if (a[ii+1][kp+1] < -EPS) {
               q = -a[ii+1][1]/a[ii+1][kp+1];
               if (q < *q1) {
                  *ip=ii;
                  *q1=q;
               } else if (q == *q1) {
                  for (k=1;k<=n;k++) {
                     qp = -a[*ip+1][k+1]/a[*ip+1][kp+1];
                     q0 = -a[ii+1][k+1]/a[ii+1][kp+1];
                     if (q0 != qp) break;
                  }
                  if (q0 < qp) *ip=ii;
               }
            }
         }
      }
   }
}

#undef EPS
void simp3(a,i1,k1,ip,kp)
int i1,k1,ip,kp;
float **a;
{
   int kk,ii;
   float piv;

   piv=1.0/a[ip+1][kp+1];
   for (ii=1;ii<=i1+1;ii++)
      if (ii-1 != ip) {
         a[ii][kp+1] *= piv;
         for (kk=1;kk<=k1+1;kk++)
            if (kk-1 != kp)
               a[ii][kk] -= a[ip+1][kk]*a[ii][kp+1];
      }
   for (kk=1;kk<=k1+1;kk++)
      if (kk-1 != kp) a[ip+1][kk] *= -piv;
   a[ip+1][kp+1]=piv;
}
#define EPS 1.0e-6
#define FREEALL free_ivector(l3,1,m);free_ivector(l2,1,m);\
   free_ivector(l1,1,n+1);

void simplx(a,m,n,m1,m2,m3,icase,izrov,iposv)
int m,n,m1,m2,m3,*icase,izrov[],iposv[];
float **a;
{
   int i,ip,ir,is,k,kh,kp,m12,nl1,nl2;
   int *l1,*l2,*l3,*ivector();
   float q1,bmax;
   void simp1(),simp2(),simp3(),nrerror(),free_ivector();

   if (m != (m1+m2+m3)) nrerror("Bad input constraint counts in SIMPLX");
   l1=ivector(1,n+1);
   l2=ivector(1,m);
   l3=ivector(1,m);
   nl1=n;
   for (k=1;k<=n;k++) l1[k]=izrov[k]=k;
   nl2=m;
   for (i=1;i<=m;i++) {
      if (a[i+1][1] < 0.0) nrerror("Bad input tableau in SIMPLX");
      l2[i]=i;
      iposv[i]=n+i;
   }
   for (i=1;i<=m2;i++) l3[i]=1;
   ir=0;
   if (m2+m3) {
      ir=1;
      for (k=1;k<=(n+1);k++) {
         q1=0.0;
         for (i=m1+1;i<=m;i++) q1 += a[i+1][k];
         a[m+2][k] = -q1;
      }
      do {
         simp1(a,m+1,l1,nl1,0,&kp,&bmax);
         if (bmax <= EPS && a[m+2][1] < -EPS) {
            *icase = -1;
            FREEALL return;
         } else if (bmax <= EPS && a[m+2][1] <= EPS) {
            m12=m1+m2+1;
            if (m12 <= m) {
               for (ip=m12;ip<=m;ip++) {
                  if (iposv[ip] == (ip+n)) {
                     simp1(a,ip,l1,
                        nl1,1,&kp,&bmax);
                     if (bmax > 0.0)
                        goto one;
                  }
               }
            }
            ir=0;
            --m12;
            if (m1+1 <= m12)
               for (i=m1+1;i<=m12;i++)
                  if (l3[i-m1] == 1)
                     for (k=1;k<=n+1;k++)
                        a[i+1][k] = -a[i+1][k];
            break;
         }
         simp2(a,n,l2,nl2,&ip,kp,&q1);
         if (ip == 0) {
            *icase = -1;
            FREEALL return;
         }
one:      simp3(a,m+1,n,ip,kp);
         if (iposv[ip] >= (n+m1+m2+1)) {
            for (k=1;k<=nl1;k++)
               if (l1[k] == kp) break;
            --nl1;
            for (is=k;is<=nl1;is++) l1[is]=l1[is+1];
            a[m+2][kp+1] += 1.0;
            for (i=1;i<=m+2;i++) a[i][kp+1] = -a[i][kp+1];
         } else {
            if (iposv[ip] >= (n+m1+1)) {
               kh=iposv[ip]-m1-n;
               if (l3[kh]) {
                  l3[kh]=0;
                  a[m+2][kp+1] += 1.0;
                  for (i=1;i<=m+2;i++)
                     a[i][kp+1] = -a[i][kp+1];
               }
            }
         }
         is=izrov[kp];
         izrov[kp]=iposv[ip];
         iposv[ip]=is;
      } while (ir);
   }
   for (;;) {
      simp1(a,0,l1,nl1,0,&kp,&bmax);
      if (bmax <= 0.0) {
         *icase=0;
         FREEALL return;
      }
      simp2(a,n,l2,nl2,&ip,kp,&q1);
      if (ip == 0) {
         *icase=1;
         FREEALL return;
      }
      simp3(a,m,n,ip,kp);
      is=izrov[kp];
      izrov[kp]=iposv[ip];
      iposv[ip]=is;
   }
}

#undef EPS
#undef FREEALL
/*----------------------------------------------------------------------------*/


#define CA 0.0003

void sncndn(uu,emmc,sn,cn,dn)
float uu,emmc;
float *sn,*cn,*dn;
{
   float a,b,c,d,emc,u;
   float em[14],en[14];
   int i,ii,l,bo;

   emc=emmc;
   u=uu;
   if (emc) {
      bo=(emc < 0.0);
      if (bo) {
         d=1.0-emc;
         emc /= -1.0/d;
         u *= (d=sqrt(d));
      }
      a=1.0;
      *dn=1.0;
      for (i=1;i<=13;i++) {
         l=i;
         em[i]=a;
         en[i]=(emc=sqrt(emc));
         c=0.5*(a+emc);
         if (fabs(a-emc) <= CA*a) break;
         emc *= a;
         a=c;
      }
      u *= c;
      *sn=sin(u);
      *cn=cos(u);
      if (*sn) {
         a=(*cn)/(*sn);
         c *= a;
         for (ii=l;ii>=1;ii--) {
            b=em[ii];
            a *= c;
            c *= (*dn);
            *dn=(en[ii]+a)/(b+a);
            a=c/b;
         }
         a=1.0/sqrt(c*c+1.0);
         *sn=(*sn >= 0.0 ? a : -a);
         *cn=c*(*sn);
      }
      if (bo) {
         a=(*dn);
         *dn=(*cn);
         *cn=a;
         *sn /= d;
      }
   } else {
      *cn=1.0/cosh(u);
      *dn=(*cn);
      *sn=tanh(u);
   }
}

#undef CA

/*----------------------------------------------------------------------------*/

void sort(n,ra)
int n;
float ra[];
{
   int l,j,ir,i;
   float rra;

   l=(n >> 1)+1;
   ir=n;
   for (;;) {
      if (l > 1)
         rra=ra[--l];
      else {
         rra=ra[ir];
         ra[ir]=ra[1];
         if (--ir == 1) {
            ra[1]=rra;
            return;
         }
      }
      i=l;
      j=l << 1;
      while (j <= ir) {
         if (j < ir && ra[j] < ra[j+1]) ++j;
         if (rra < ra[j]) {
            ra[i]=ra[j];
            j += (i=j);
         }
         else j=ir+1;
      }
      ra[i]=rra;
   }
}
void sort2(n,ra,rb)
int n;
float ra[],rb[];
{
   int l,j,ir,i;
   float rrb,rra;

   l=(n >> 1)+1;
   ir=n;
   for (;;) {
      if (l > 1) {
         rra=ra[--l];
         rrb=rb[l];
      } else {
         rra=ra[ir];
         rrb=rb[ir];
         ra[ir]=ra[1];
         rb[ir]=rb[1];
         if (--ir == 1) {
            ra[1]=rra;
            rb[1]=rrb;
            return;
         }
      }
      i=l;
      j=l << 1;
      while (j <= ir)   {
         if (j < ir && ra[j] < ra[j+1]) ++j;
         if (rra < ra[j]) {
            ra[i]=ra[j];
            rb[i]=rb[j];
            j += (i=j);
         }
         else j=ir+1;
      }
      ra[i]=rra;
      rb[i]=rrb;
   }
}
void sort3(n,ra,rb,rc)
int n;
float ra[],rb[],rc[];
{
   int j,*iwksp,*ivector();
   float *wksp,*vector();
   void indexx(),free_vector(),free_ivector();

   iwksp=ivector(1,n);
   wksp=vector(1,n);
   indexx(n,ra,iwksp);
   for (j=1;j<=n;j++) wksp[j]=ra[j];
   for (j=1;j<=n;j++) ra[j]=wksp[iwksp[j]];
   for (j=1;j<=n;j++) wksp[j]=rb[j];
   for (j=1;j<=n;j++) rb[j]=wksp[iwksp[j]];
   for (j=1;j<=n;j++) wksp[j]=rc[j];
   for (j=1;j<=n;j++) rc[j]=wksp[iwksp[j]];
   free_vector(wksp,1,n);
   free_ivector(iwksp,1,n);
}

#ifdef EXTRACOMPILATION

#define EPS 1.0e-6
#define FREERETURN {free_vector(xj,1,n);free_vector(xi,1,n);\
   free_vector(h,1,n);free_vector(g,1,n);return;}

void sparse(b,n,x,rsq)
float b[],x[],*rsq;
int n;
{
   int j,iter,irst=0;
   float aden,anum,bsq,dgg,eps2,gam,gg,rp;
   float *g,*h,*xi,*xj,*vector();
   void asub(),atsub(),nrerror(),free_vector();

   g=vector(1,n);
   h=vector(1,n);
   xi=vector(1,n);
   xj=vector(1,n);
   eps2=n*EPS*EPS;
   for (;;) {
      ++irst;
      asub(x,xi,n);
      rp=bsq=0.0;
      for (j=1;j<=n;j++) {
         bsq += b[j]*b[j];
         xi[j] -= b[j];
         rp += xi[j]*xi[j];
      }
      atsub(xi,g,n);
      for (j=1;j<=n;j++)
         h[j] = g[j] = -g[j];
      for (iter=1;iter<=10*n;iter++) {
         asub(h,xi,n);
         anum=aden=0.0;
         for (j=1;j<=n;j++) {
            anum += g[j]*h[j];
            aden += xi[j]*xi[j];
         }
         if (aden == 0.0) nrerror("Very singular matrix in SPARSE");
         anum /= aden;
         for (j=1;j<=n;j++) {
            xi[j]=x[j];
            x[j] += anum*h[j];
         }
         asub(x,xj,n);
         *rsq=0.0;
         for (j=1;j<=n;j++) {
            xj[j] -= b[j];
            *rsq += xj[j]*xj[j];
         }
         if (*rsq == rp || *rsq <= bsq*eps2) FREERETURN
         if (*rsq > rp) {
            for (j=1;j<=n;j++) x[j]=xi[j];
            if (irst >= 3) FREERETURN
            break;
         }
         rp = *rsq;
         atsub(xj,xi,n);
         gg=dgg=0.0;
         for (j=1;j<=n;j++) {
            gg += g[j]*g[j];
            dgg += (xi[j]+g[j])*xi[j];
         }
         if (gg == 0.0) FREERETURN
         gam=dgg/gg;
         for (j=1;j<=n;j++) {
            g[j] = -xi[j];
            h[j]=g[j]+gam*h[j];
         }
      }
      nrerror("Too many interations in routine SPARSE");
   }
}

#undef EPS
#undef FREERETURN

#endif
/*----------------------------------------------------------------------------*/


void splie2(x1a,x2a,ya,m,n,y2a)
float x1a[],x2a[],**ya,**y2a;
int m,n;
{
   int j;
   void spline();

   for (j=1;j<=m;j++)
      spline(x2a,ya[j],n,1.0e30,1.0e30,y2a[j]);
}
void splin2(x1a,x2a,ya,y2a,m,n,x1,x2,y)
float x1a[],x2a[],**ya,**y2a,x1,x2,*y;
int m,n;
{
   int j;
   float *ytmp,*yytmp,*vector();
   void spline(),splint(),free_vector();

   ytmp=vector(1,n);
   yytmp=vector(1,n);
   for (j=1;j<=m;j++)
      splint(x2a,ya[j],y2a[j],n,x2,&yytmp[j]);
   spline(x1a,yytmp,m,1.0e30,1.0e30,ytmp);
   splint(x1a,yytmp,ytmp,m,x1,y);
   free_vector(yytmp,1,n);
   free_vector(ytmp,1,n);
}
void spline(x,y,n,yp1,ypn,y2)
float x[],y[],yp1,ypn,y2[];
int n;
{
   int i,k;
   float p,qn,sig,un,*u,*vector();
   void free_vector();

   u=vector(1,n-1);
   if (yp1 > 0.99e30)
      y2[1]=u[1]=0.0;
   else {
      y2[1] = -0.5;
      u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
   }
   for (i=2;i<=n-1;i++) {
      sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
      p=sig*y2[i-1]+2.0;
      y2[i]=(sig-1.0)/p;
      u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
      u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
   }
   if (ypn > 0.99e30)
      qn=un=0.0;
   else {
      qn=0.5;
      un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
   }
   y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
   for (k=n-1;k>=1;k--)
      y2[k]=y2[k]*y2[k+1]+u[k];
   free_vector(u,1,n-1);
}
void splint(xa,ya,y2a,n,x,y)
float xa[],ya[],y2a[],x,*y;
int n;
{
   int klo,khi,k;
   float h,b,a;
   void nrerror();

   klo=1;
   khi=n;
   while (khi-klo > 1) {
      k=(khi+klo) >> 1;
      if (xa[k] > x) khi=k;
      else klo=k;
   }
   h=xa[khi]-xa[klo];
   if (h == 0.0) nrerror("Bad XA input to routine SPLINT");
   a=(xa[khi]-x)/h;
   b=(x-xa[klo])/h;
   *y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
}
void svbksb(u,w,v,m,n,b,x)
float **u,w[],**v,b[],x[];
int m,n;
{
   int jj,j,i;
   float s,*tmp,*vector();
   void free_vector();

   tmp=vector(1,n);
   for (j=1;j<=n;j++) {
      s=0.0;
      if (w[j]) {
         for (i=1;i<=m;i++) s += u[i][j]*b[i];
         s /= w[j];
      }
      tmp[j]=s;
   }
   for (j=1;j<=n;j++) {
      s=0.0;
      for (jj=1;jj<=n;jj++) s += v[j][jj]*tmp[jj];
      x[j]=s;
   }
   free_vector(tmp,1,n);
}
/*----------------------------------------------------------------------------*/

static float at,bt,ct;
#define PYTHAG(a,b) ((at=fabs(a)) > (bt=fabs(b)) ? \
(ct=bt/at,at*sqrt(1.0+ct*ct)) : (bt ? (ct=at/bt,bt*sqrt(1.0+ct*ct)): 0.0))

#ifndef MY_maxarg /* !shik */
#define MY_maxarg 1 /* !shik */
static float maxarg1,maxarg2;
#endif /* !shik */
#define MAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
   (maxarg1) : (maxarg2))
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

void svdcmp(a,m,n,w,v)
float **a,*w,**v;
int m,n;
{
   int flag,i,its,j,jj,k,l,nm;
   float c,f,h,s,x,y,z;
   float anorm=0.0,g=0.0,scale=0.0;
   float *rv1,*vector();
   void nrerror(),free_vector();

   if (m < n) nrerror("SVDCMP: You must augment A with extra zero rows");
   rv1=vector(1,n);
   for (i=1;i<=n;i++) {
      l=i+1;
      rv1[i]=scale*g;
      g=s=scale=0.0;
      if (i <= m) {
         for (k=i;k<=m;k++) scale += fabs(a[k][i]);
         if (scale) {
            for (k=i;k<=m;k++) {
               a[k][i] /= scale;
               s += a[k][i]*a[k][i];
            }
            f=a[i][i];
            g = -SIGN(sqrt(s),f);
            h=f*g-s;
            a[i][i]=f-g;
            if (i != n) {
               for (j=l;j<=n;j++) {
                  for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
                  f=s/h;
                  for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
               }
            }
            for (k=i;k<=m;k++) a[k][i] *= scale;
         }
      }
      w[i]=scale*g;
      g=s=scale=0.0;
      if (i <= m && i != n) {
         for (k=l;k<=n;k++) scale += fabs(a[i][k]);
         if (scale) {
            for (k=l;k<=n;k++) {
               a[i][k] /= scale;
               s += a[i][k]*a[i][k];
            }
            f=a[i][l];
            g = -SIGN(sqrt(s),f);
            h=f*g-s;
            a[i][l]=f-g;
            for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
            if (i != m) {
               for (j=l;j<=m;j++) {
                  for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
                  for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
               }
            }
            for (k=l;k<=n;k++) a[i][k] *= scale;
         }
      }
      anorm=MAX(anorm,(fabs(w[i])+fabs(rv1[i])));
   }
   for (i=n;i>=1;i--) {
      if (i < n) {
         if (g) {
            for (j=l;j<=n;j++)
               v[j][i]=(a[i][j]/a[i][l])/g;
            for (j=l;j<=n;j++) {
               for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
               for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
            }
         }
         for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
      }
      v[i][i]=1.0;
      g=rv1[i];
      l=i;
   }
   for (i=n;i>=1;i--) {
      l=i+1;
      g=w[i];
      if (i < n)
         for (j=l;j<=n;j++) a[i][j]=0.0;
      if (g) {
         g=1.0/g;
         if (i != n) {
            for (j=l;j<=n;j++) {
               for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
               f=(s/a[i][i])*g;
               for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
            }
         }
         for (j=i;j<=m;j++) a[j][i] *= g;
      } else {
         for (j=i;j<=m;j++) a[j][i]=0.0;
      }
      ++a[i][i];
   }
   for (k=n;k>=1;k--) {
      for (its=1;its<=30;its++) {
         flag=1;
         for (l=k;l>=1;l--) {
            nm=l-1;
            if (fabs(rv1[l])+anorm == anorm) {
               flag=0;
               break;
            }
            if (fabs(w[nm])+anorm == anorm) break;
         }
         if (flag) {
            c=0.0;
            s=1.0;
            for (i=l;i<=k;i++) {
               f=s*rv1[i];
               if (fabs(f)+anorm != anorm) {
                  g=w[i];
                  h=PYTHAG(f,g);
                  w[i]=h;
                  h=1.0/h;
                  c=g*h;
                  s=(-f*h);
                  for (j=1;j<=m;j++) {
                     y=a[j][nm];
                     z=a[j][i];
                     a[j][nm]=y*c+z*s;
                     a[j][i]=z*c-y*s;
                  }
               }
            }
         }
         z=w[k];
         if (l == k) {
            if (z < 0.0) {
               w[k] = -z;
               for (j=1;j<=n;j++) v[j][k]=(-v[j][k]);
            }
            break;
         }
         if (its == 30) nrerror("No convergence in 30 SVDCMP iterations");
         x=w[l];
         nm=k-1;
         y=w[nm];
         g=rv1[nm];
         h=rv1[k];
         f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
         g=PYTHAG(f,1.0);
         f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
         c=s=1.0;
         for (j=l;j<=nm;j++) {
            i=j+1;
            g=rv1[i];
            y=w[i];
            h=s*g;
            g=c*g;
            z=PYTHAG(f,h);
            rv1[j]=z;
            c=f/z;
            s=h/z;
            f=x*c+g*s;
            g=g*c-x*s;
            h=y*s;
            y=y*c;
            for (jj=1;jj<=n;jj++) {
               x=v[jj][j];
               z=v[jj][i];
               v[jj][j]=x*c+z*s;
               v[jj][i]=z*c-x*s;
            }
            z=PYTHAG(f,h);
            w[j]=z;
            if (z) {
               z=1.0/z;
               c=f*z;
               s=h*z;
            }
            f=(c*g)+(s*y);
            x=(c*y)-(s*g);
            for (jj=1;jj<=m;jj++) {
               y=a[jj][j];
               z=a[jj][i];
               a[jj][j]=y*c+z*s;
               a[jj][i]=z*c-y*s;
            }
         }
         rv1[l]=0.0;
         rv1[k]=f;
         w[k]=x;
      }
   }
   free_vector(rv1,1,n);
}

#undef SIGN
#undef MAX
#undef PYTHAG
#define FREERETURN {free_vector(h,1,n);free_vector(g,1,n);return;}

void toeplz(r,x,y,n)
float r[],x[],y[];
int n;
{
   int j,k,m,m1,m2;
   float pp,pt1,pt2,qq,qt1,qt2,sd,sgd,sgn,shn,sxn;
   float *g,*h,*vector();
   void nrerror(),free_vector();

   g=vector(1,n);
   h=vector(1,n);
   if (r[n] == 0.0) FREERETURN
   x[1]=y[1]/r[n];
   if (n == 1) FREERETURN
   g[1]=r[n-1]/r[n];
   h[1]=r[n+1]/r[n];
   for (m=1;m<=n;m++) {
      m1=m+1;
      sxn = -y[m1];
      sd = -r[n];
      for (j=1;j<=m;j++) {
         sxn += r[n+m1-j]*x[j];
         sd += r[n+m1-j]*g[m-j+1];
      }
      if (sd == 0.0) nrerror("TOEPLZ-1 fails with singular principal minor");
      x[m1]=sxn/sd;
      for (j=1;j<=m;j++) x[j] -= x[m1]*g[m-j+1];
      if (m1 == n) FREERETURN
      sgn = -r[n-m1];
      shn = -r[n+m1];
      sgd = -r[n];
      for (j=1;j<=m;j++) {
         sgn += r[n+j-m1]*g[j];
         shn += r[n+m1-j]*h[j];
         sgd += r[n+j-m1]*h[m-j+1];
      }
      if (sd == 0.0 || sgd == 0.0) nrerror("TOEPLZ-2 singular principal minor");
      g[m1]=sgn/sgd;
      h[m1]=shn/sd;
      k=m;
      m2=(m+1) >> 1;
      pp=g[m1];
      qq=h[m1];
      for (j=1;j<=m2;j++) {
         pt1=g[j];
         pt2=g[k];
         qt1=h[j];
         qt2=h[k];
         g[j]=pt1-pp*qt2;
         g[k]=pt2-pp*qt1;
         h[j]=qt1-qq*pt2;
         h[k--]=qt2-qq*pt1;
           }
   }
   nrerror("TOEPLZ - should not arrive here!");
}

#undef FREERETURN
/*----------------------------------------------------------------------------*/

#define FUNC(x) ((*func)(x))

float trapzd(func,a,b,n)
float a,b;
float (*func)();   /* ANSI: float (*func)(float); */
int n;
{
   float x,tnm,sum,del;
   static float s;
   static int it;
   int j;

   if (n == 1) {
      it=1;
      return (s=0.5*(b-a)*(FUNC(a)+FUNC(b)));
   } else {
      tnm=it;
      del=(b-a)/tnm;
      x=a+0.5*del;
      for (sum=0.0,j=1;j<=it;j++,x+=del) sum += FUNC(x);
      it *= 2;
      s=0.5*(s+(b-a)*sum/tnm);
      return s;
   }
}
/*----------------------------------------------------------------------------*/

/* !shik
void tridag(a,b,c,r,u,n)
float a[],b[],c[],r[],u[];
int n;
{
   int j;
   float bet,*gam,*vector();
   void nrerror(),free_vector();

   gam=vector(1,n);
   if (b[1] == 0.0) nrerror("Error 1 in TRIDAG");
   u[1]=r[1]/(bet=b[1]);
   for (j=2;j<=n;j++) {
      gam[j]=c[j-1]/bet;
      bet=b[j]-a[j]*gam[j];
      if (bet == 0.0)   nrerror("Error 2 in TRIDAG");
      u[j]=(r[j]-a[j]*u[j-1])/bet;
   }
   for (j=(n-1);j>=1;j--)
      u[j] -= gam[j+1]*u[j+1];
   free_vector(gam,1,n);
}
*/
/*----------------------------------------------------------------------------*/

void vander(x,w,q,n)
float x[],w[],q[];
int n;
{
   int i,j,k,k1;
   float b,s,t,xx;
   float *c,*vector();
   void free_vector();

   c=vector(1,n);
   if (n == 1) w[1]=q[1];
   else {
      for (i=1;i<=n;i++) c[i]=0.0;
      c[n] = -x[1];
      for (i=2;i<=n;i++) {
         xx = -x[i];
         for (j=(n+1-i);j<=(n-1);j++) c[j] += xx*c[j+1];
         c[n] += xx;
      }
      for (i=1;i<=n;i++) {
         xx=x[i];
         t=b=1.0;
         s=q[n];
         k=n;
         for (j=2;j<=n;j++) {
            k1=k-1;
            b=c[k]+xx*b;
            s += q[k1]*b;
            t=xx*t+b;
            k=k1;
         }
         w[i]=s/t;
      }
   }
   free_vector(c,1,n);
}
/*----------------------------------------------------------------------------*/

#define FACTOR 1.6
#define NTRY 50

int zbrac(func,x1,x2)
float *x1,*x2;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int j;
   float f1,f2;
   void nrerror();

   if (*x1 == *x2) nrerror("Bad initial range in ZBRAC");
   f1=(*func)(*x1);
   f2=(*func)(*x2);
   for (j=1;j<=NTRY;j++) {
      if (f1*f2 < 0.0) return 1;
      if (fabs(f1) < fabs(f2))
         f1=(*func)(*x1 += FACTOR*(*x1-*x2));
      else
         f2=(*func)(*x2 += FACTOR*(*x2-*x1));
   }
   return 0;
}

#undef FACTOR
#undef NTRY
void zbrak(fx,x1,x2,n,xb1,xb2,nb)
float x1,x2,xb1[],xb2[];
float (*fx)();   /* ANSI: float (*fx)(float); */
int n,*nb;
{
   int nbb,i;
   float x,fp,fc,dx;

   nbb=(*nb);
   *nb=0;
   dx=(x2-x1)/n;
   fp=(*fx)(x=x1);
   for (i=1;i<=n;i++) {
      fc=(*fx)(x += dx);
      if (fc*fp < 0.0) {
         xb1[++(*nb)]=x-dx;
         xb2[*nb]=x;
      }
      fp=fc;
      if (nbb == (*nb)) return;
   }
}
/*----------------------------------------------------------------------------*/

#define ITMAX 100
#define EPS 3.0e-8

float zbrent(func,x1,x2,tol)
float x1,x2,tol;
float (*func)();   /* ANSI: float (*func)(float); */
{
   int iter;
   float a=x1,b=x2,c,d,e,min1,min2;
   float fa=(*func)(a),fb=(*func)(b),fc,p,q,r,s,tol1,xm;
   void nrerror();

   if (fb*fa > 0.0) nrerror("Root must be bracketed in ZBRENT");
   fc=fb;
   for (iter=1;iter<=ITMAX;iter++) {
      if (fb*fc > 0.0) {
         c=a;
         fc=fa;
         e=d=b-a;
      }
      if (fabs(fc) < fabs(fb)) {
         a=b;
         b=c;
         c=a;
         fa=fb;
         fb=fc;
         fc=fa;
      }
      tol1=2.0*EPS*fabs(b)+0.5*tol;
      xm=0.5*(c-b);
      if (fabs(xm) <= tol1 || fb == 0.0) return b;
      if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
         s=fb/fa;
         if (a == c) {
            p=2.0*xm*s;
            q=1.0-s;
         } else {
            q=fa/fc;
            r=fb/fc;
            p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
            q=(q-1.0)*(r-1.0)*(s-1.0);
         }
         if (p > 0.0)  q = -q;
         p=fabs(p);
         min1=3.0*xm*q-fabs(tol1*q);
         min2=fabs(e*q);
         if (2.0*p < (min1 < min2 ? min1 : min2)) {
            e=d;
            d=p/q;
         } else {
            d=xm;
            e=d;
         }
      } else {
         d=xm;
         e=d;
      }
      a=b;
      fa=fb;
      if (fabs(d) > tol1)
         b += d;
      else
         b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
      fb=(*func)(b);
   }
   nrerror("Maximum number of iterations exceeded in ZBRENT");
   return NaNFloat; // 2016.3.26
}

#undef ITMAX
#undef EPS
/*----------------------------------------------------------------------------*/
/* #include "complex.h" !shik */

#define EPS 2.0e-6
#define MAXM 100

void zroots(a,m,roots,polish)
fcomplex a[],roots[];
int m,polish;
{
   int jj,j,i;
   fcomplex x,b,c,ad[MAXM];
   void laguer();

   for (j=0;j<=m;j++) ad[j]=a[j];
   for (j=m;j>=1;j--) {
      x=Complex(0.0,0.0);
      laguer(ad,j,&x,EPS,0);
      if (fabs(x.i) <= (2.0*EPS*fabs(x.r))) x.i=0.0;
      roots[j]=x;
      b=ad[j];
      for (jj=j-1;jj>=0;jj--) {
         c=ad[jj];
         ad[jj]=b;
         b=Cadd(Cmul(x,b),c);
      }
   }
   if (polish)
      for (j=1;j<=m;j++)
         laguer(a,m,&roots[j],EPS,1);
   for (j=2;j<=m;j++) {
      x=roots[j];
      for (i=j-1;i>=1;i--) {
         if (roots[i].r <= x.r) break;
         roots[i+1]=roots[i];
      }
      roots[i+1]=x;
   }
}

#undef EPS
#undef MAXM

/*---11.0---------------------------------------------------------------------*/
/*---11.1---------------------------------------------------------------------*/

#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);\
   a[k][l]=h+s*(g-h*tau);

void jacobi(a,n,d,v,nrot)
float **a,d[],**v;
int n,*nrot;
{
   int j,iq,ip,i;
   float tresh,theta,tau,t,sm,s,h,g,c,*b,*z,*vector();
   void nrerror(),free_vector();

   b=vector(1,n);
   z=vector(1,n);
   for (ip=1;ip<=n;ip++) {
      for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
      v[ip][ip]=1.0;
   }
   for (ip=1;ip<=n;ip++) {
      b[ip]=d[ip]=a[ip][ip];
      z[ip]=0.0;
   }
   *nrot=0;
   for (i=1;i<=50;i++) {
      sm=0.0;
      for (ip=1;ip<=n-1;ip++) {
         for (iq=ip+1;iq<=n;iq++)
            sm += fabs(a[ip][iq]);
      }
      if (sm == 0.0) {
         free_vector(z,1,n);
         free_vector(b,1,n);
         return;
      }
      if (i < 4)
         tresh=0.2*sm/(n*n);
      else
         tresh=0.0;
      for (ip=1;ip<=n-1;ip++) {
         for (iq=ip+1;iq<=n;iq++) {
            g=100.0*fabs(a[ip][iq]);
            if (i > 4 && fabs(d[ip])+g == fabs(d[ip])
               && fabs(d[iq])+g == fabs(d[iq]))
               a[ip][iq]=0.0;
            else if (fabs(a[ip][iq]) > tresh) {
               h=d[iq]-d[ip];
               if (fabs(h)+g == fabs(h))
                  t=(a[ip][iq])/h;
               else {
                  theta=0.5*h/(a[ip][iq]);
                  t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                  if (theta < 0.0) t = -t;
               }
               c=1.0/sqrt(1+t*t);
               s=t*c;
               tau=s/(1.0+c);
               h=t*a[ip][iq];
               z[ip] -= h;
               z[iq] += h;
               d[ip] -= h;
               d[iq] += h;
               a[ip][iq]=0.0;
               for (j=1;j<=ip-1;j++) {
                  ROTATE(a,j,ip,j,iq)
               }
               for (j=ip+1;j<=iq-1;j++) {
                  ROTATE(a,ip,j,j,iq)
               }
               for (j=iq+1;j<=n;j++) {
                  ROTATE(a,ip,j,iq,j)
               }
               for (j=1;j<=n;j++) {
                  ROTATE(v,j,ip,j,iq)
               }
               ++(*nrot);
            }
         }
      }
      for (ip=1;ip<=n;ip++) {
         b[ip] += z[ip];
         d[ip]=b[ip];
         z[ip]=0.0;
      }
   }
   nrerror("Too many iterations in routine JACOBI");
}

#undef ROTATE

void eigsrt(d,v,n)
float d[],**v;
int n;
{
   int k,j,i;
   float p;

   for (i=1;i<n;i++) {
      p=d[k=i];
      for (j=i+1;j<=n;j++)
         if (d[j] >= p) p=d[k=j];
      if (k != i) {
         d[k]=d[i];
         d[i]=p;
         for (j=1;j<=n;j++) {
            p=v[j][i];
            v[j][i]=v[j][k];
            v[j][k]=p;
         }
      }
   }
}

/*---11.2---------------------------------------------------------------------*/

void tred2(a,n,d,e)
float **a,d[],e[];
int n;
{
   int l,k,j,i;
   float scale,hh,h,g,f;

   for (i=n;i>=2;i--) {
      l=i-1;
      h=scale=0.0;
      if (l > 1) {
         for (k=1;k<=l;k++)
            scale += fabs(a[i][k]);
         if (scale == 0.0)
            e[i]=a[i][l];
         else {
            for (k=1;k<=l;k++) {
               a[i][k] /= scale;
               h += a[i][k]*a[i][k];
            }
            f=a[i][l];
            g = f>0 ? -sqrt(h) : sqrt(h);
            e[i]=scale*g;
            h -= f*g;
            a[i][l]=f-g;
            f=0.0;
            for (j=1;j<=l;j++) {
            /* Next statement can be omitted if eigenvectors not wanted */
               a[j][i]=a[i][j]/h;
               g=0.0;
               for (k=1;k<=j;k++)
                  g += a[j][k]*a[i][k];
               for (k=j+1;k<=l;k++)
                  g += a[k][j]*a[i][k];
               e[j]=g/h;
               f += e[j]*a[i][j];
            }
            hh=f/(h+h);
            for (j=1;j<=l;j++) {
               f=a[i][j];
               e[j]=g=e[j]-hh*f;
               for (k=1;k<=j;k++)
                  a[j][k] -= (f*e[k]+g*a[i][k]);
            }
         }
      } else
         e[i]=a[i][l];
      d[i]=h;
   }
   /* Next statement can be omitted if eigenvectors not wanted */
   d[1]=0.0;
   e[1]=0.0;
   /* Contents of this loop can be omitted if eigenvectors not
         wanted except for statement d[i]=a[i][i]; */
   for (i=1;i<=n;i++) {
      l=i-1;
      if (d[i]) {
         for (j=1;j<=l;j++) {
            g=0.0;
            for (k=1;k<=l;k++)
               g += a[i][k]*a[k][j];
            for (k=1;k<=l;k++)
               a[k][j] -= g*a[k][i];
         }
      }
      d[i]=a[i][i];
      a[i][i]=1.0;
      for (j=1;j<=l;j++) a[j][i]=a[i][j]=0.0;
   }
}

/*---11.3---------------------------------------------------------------------*/

#define SIGN(a,b) ((b)<0 ? -fabs(a) : fabs(a))

void tqli(d,e,n,z)
float d[],e[],**z;
int n;
{
   int m,l,iter,i,k;
   float s,r,p,g,f,dd,c,b;
   void nrerror();

   for (i=2;i<=n;i++) e[i-1]=e[i];
   e[n]=0.0;
   for (l=1;l<=n;l++) {
      iter=0;
      do {
         for (m=l;m<=n-1;m++) {
            dd=fabs(d[m])+fabs(d[m+1]);
            if (fabs(e[m])+dd == dd) break;
         }
         if (m != l) {
            if (iter++ == 30) nrerror("Too many iterations in TQLI");
            g=(d[l+1]-d[l])/(2.0*e[l]);
            r=sqrt((g*g)+1.0);
            g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
            s=c=1.0;
            p=0.0;
            for (i=m-1;i>=l;i--) {
               f=s*e[i];
               b=c*e[i];
               if (fabs(f) >= fabs(g)) {
                  c=g/f;
                  r=sqrt((c*c)+1.0);
                  e[i+1]=f*r;
                  c *= (s=1.0/r);
               } else {
                  s=f/g;
                  r=sqrt((s*s)+1.0);
                  e[i+1]=g*r;
                  s *= (c=1.0/r);
               }
               g=d[i+1]-p;
               r=(d[i]-g)*s+2.0*c*b;
               p=s*r;
               d[i+1]=g+p;
               g=c*r-b;
               /* Next loop can be omitted if eigenvectors not wanted */
               for (k=1;k<=n;k++) {
                  f=z[k][i+1];
                  z[k][i+1]=s*z[k][i]+c*f;
                  z[k][i]=c*z[k][i]-s*f;
               }
            }
            d[l]=d[l]-p;
            e[l]=g;
            e[m]=0.0;
         }
      } while (m != l);
   }
}
#undef SIGN

/*---11.4---------------------------------------------------------------------*/
/*---11.5---------------------------------------------------------------------*/

#define RADIX 2.0

void balanc(a,n)
float **a;
int n;
{
   int last,j,i;
   float s,r,g,f,c,sqrdx;

   sqrdx=RADIX*RADIX;
   last=0;
   while (last == 0) {
      last=1;
      for (i=1;i<=n;i++) {
         r=c=0.0;
         for (j=1;j<=n;j++)
            if (j != i) {
               c += fabs(a[j][i]);
               r += fabs(a[i][j]);
            }
         if (c && r) {
            g=r/RADIX;
            f=1.0;
            s=c+r;
            while (c<g) {
               f *= RADIX;
               c *= sqrdx;
            }
            g=r*RADIX;
            while (c>g) {
               f /= RADIX;
               c /= sqrdx;
            }
            if ((c+r)/f < 0.95*s) {
               last=0;
               g=1.0/f;
               for (j=1;j<=n;j++) a[i][j] *= g;
               for (j=1;j<=n;j++) a[j][i] *= f;
            }
         }
      }
   }
}

#undef RADIX

#define SWAP(g,h) {y=(g);(g)=(h);(h)=y;}

void elmhes(a,n)
float **a;
int n;
{
   int m,j,i;
   float y,x;

   for (m=2;m<n;m++) {
      x=0.0;
      i=m;
      for (j=m;j<=n;j++) {
         if (fabs(a[j][m-1]) > fabs(x)) {
            x=a[j][m-1];
            i=j;
         }
      }
      if (i != m) {
         for (j=m-1;j<=n;j++) SWAP(a[i][j],a[m][j])
         for (j=1;j<=n;j++) SWAP(a[j][i],a[j][m])
      }
      if (x) {
         for (i=m+1;i<=n;i++) {
            if (y=a[i][m-1]) {
               y /= x;
               a[i][m-1]=y;
               for (j=m;j<=n;j++)
                  a[i][j] -= y*a[m][j];
               for (j=1;j<=n;j++)
                  a[j][m] += y*a[j][i];
            }
         }
      }
   }
}
#undef SWAP

/*---11.6---------------------------------------------------------------------*/

#define SIGN(a,b) ((b) > 0 ? fabs(a) : -fabs(a))

void hqr(a,n,wr,wi)
float **a,wr[],wi[];
int n;
{
   int nn,m,l,k,j,its,i,mmin;
   float z,y,x,w,v,u,t,s,r,q,p,anorm;
   void nrerror();

   anorm=fabs(a[1][1]);
   for (i=2;i<=n;i++)
      for (j=(i-1);j<=n;j++)
         anorm += fabs(a[i][j]);
   nn=n;
   t=0.0;
   while (nn >= 1) {
      its=0;
      do {
         for (l=nn;l>=2;l--) {
            s=fabs(a[l-1][l-1])+fabs(a[l][l]);
            if (s == 0.0) s=anorm;
            if (fabs(a[l][l-1]) + s == s) break;
         }
         x=a[nn][nn];
         if (l == nn) {
            wr[nn]=x+t;
            wi[nn--]=0.0;
         } else {
            y=a[nn-1][nn-1];
            w=a[nn][nn-1]*a[nn-1][nn];
            if (l == (nn-1)) {
               p=0.5*(y-x);
               q=p*p+w;
               z=sqrt(fabs(q));
               x += t;
               if (q >= 0.0) {
                  z=p+SIGN(z,p);
                  wr[nn-1]=wr[nn]=x+z;
                  if (z) wr[nn]=x-w/z;
                  wi[nn-1]=wi[nn]=0.0;
               } else {
                  wr[nn-1]=wr[nn]=x+p;
                  wi[nn-1]= -(wi[nn]=z);
               }
               nn -= 2;
            } else {
               if (its == 30) nrerror("Too many iterations in HQR");
               if (its == 10 || its == 20) {
                  t += x;
                  for (i=1;i<=nn;i++) a[i][i] -= x;
                  s=fabs(a[nn][nn-1])+fabs(a[nn-1][nn-2]);
                  y=x=0.75*s;
                  w = -0.4375*s*s;
               }
               ++its;
               for (m=(nn-2);m>=l;m--) {
                  z=a[m][m];
                  r=x-z;
                  s=y-z;
                  p=(r*s-w)/a[m+1][m]+a[m][m+1];
                  q=a[m+1][m+1]-z-r-s;
                  r=a[m+2][m+1];
                  s=fabs(p)+fabs(q)+fabs(r);
                  p /= s;
                  q /= s;
                  r /= s;
                  if (m == l) break;
                  u=fabs(a[m][m-1])*(fabs(q)+fabs(r));
                  v=fabs(p)*(fabs(a[m-1][m-1])+fabs(z)+fabs(a[m+1][m+1]));
                  if (u+v == v) break;
               }
               for (i=m+2;i<=nn;i++) {
                  a[i][i-2]=0.0;
                  if  (i != (m+2)) a[i][i-3]=0.0;
               }
               for (k=m;k<=nn-1;k++) {
                  if (k != m) {
                     p=a[k][k-1];
                     q=a[k+1][k-1];
                     r=0.0;
                     if (k != (nn-1)) r=a[k+2][k-1];
                     if (x=fabs(p)+fabs(q)+fabs(r)) {
                        p /= x;
                        q /= x;
                        r /= x;
                     }
                  }
                  if (s=SIGN(sqrt(p*p+q*q+r*r),p)) {
                     if (k == m) {
                        if (l != m)
                        a[k][k-1] = -a[k][k-1];
                     } else
                        a[k][k-1] = -s*x;
                     p += s;
                     x=p/s;
                     y=q/s;
                     z=r/s;
                     q /= p;
                     r /= p;
                     for (j=k;j<=nn;j++) {
                        p=a[k][j]+q*a[k+1][j];
                        if (k != (nn-1)) {
                           p += r*a[k+2][j];
                           a[k+2][j] -= p*z;
                        }
                        a[k+1][j] -= p*y;
                        a[k][j] -= p*x;
                     }
                     mmin = nn<k+3 ? nn : k+3;
                     for (i=l;i<=mmin;i++) {
                        p=x*a[i][k]+y*a[i][k+1];
                        if (k != (nn-1)) {
                           p += z*a[i][k+2];
                           a[i][k+2] -= p*r;
                        }
                        a[i][k+1] -= p*q;
                        a[i][k] -= p;
                     }
                  }
               }
            }
         }
      } while (l < nn-1);
   }
}

/*---11.7---------------------------------------------------------------------*/
/*---12.0---------------------------------------------------------------------*/
/*---12.1---------------------------------------------------------------------*/
/*---12.2---------------------------------------------------------------------*/

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void four1(data,nn,isign)
float data[];
int nn,isign;
{
   int n,mmax,m,j,istep,i;
   double wtemp,wr,wpr,wpi,wi,theta;
   float tempr,tempi;

   n=nn << 1;
   j=1;
   for (i=1;i<n;i+=2) {
      if (j > i) {
         SWAP(data[j],data[i]);
         SWAP(data[j+1],data[i+1]);
      }
      m=n >> 1;
      while (m >= 2 && j > m) {
         j -= m;
         m >>= 1;
      }
      j += m;
   }
   mmax=2;
   while (n > mmax) {
      istep=2*mmax;
      theta=6.28318530717959/(isign*mmax);
      wtemp=sin(0.5*theta);
      wpr = -2.0*wtemp*wtemp;
      wpi=sin(theta);
      wr=1.0;
      wi=0.0;
      for (m=1;m<mmax;m+=2) {
         for (i=m;i<=n;i+=istep) {
            j=i+mmax;
            tempr=wr*data[j]-wi*data[j+1];
            tempi=wr*data[j+1]+wi*data[j];
            data[j]=data[i]-tempr;
            data[j+1]=data[i+1]-tempi;
            data[i] += tempr;
            data[i+1] += tempi;
         }
         wr=(wtemp=wr)*wpr-wi*wpi+wr;
         wi=wi*wpr+wtemp*wpi+wi;
      }
      mmax=istep;
   }
}

#undef SWAP

/*---12.3---------------------------------------------------------------------*/

void twofft(data1,data2,fft1,fft2,n)
float data1[],data2[],fft1[],fft2[];
int n;
{
   int nn3,nn2,jj,j;
   float rep,rem,aip,aim;
   void four1();

   nn3=1+(nn2=2+n+n);
   for (j=1,jj=2;j<=n;j++,jj+=2) {
      fft1[jj-1]=data1[j];
      fft1[jj]=data2[j];
   }
   four1(fft1,n,1);
   fft2[1]=fft1[2];
   fft1[2]=fft2[2]=0.0;
   for (j=3;j<=n+1;j+=2) {
      rep=0.5*(fft1[j]+fft1[nn2-j]);
      rem=0.5*(fft1[j]-fft1[nn2-j]);
      aip=0.5*(fft1[j+1]+fft1[nn3-j]);
      aim=0.5*(fft1[j+1]-fft1[nn3-j]);
      fft1[j]=rep;
      fft1[j+1]=aim;
      fft1[nn2-j]=rep;
      fft1[nn3-j] = -aim;
      fft2[j]=aip;
      fft2[j+1] = -rem;
      fft2[nn2-j]=aip;
      fft2[nn3-j]=rem;
   }
}

void realft(data,n,isign)
float data[];
int n,isign;
{
   int i,i1,i2,i3,i4,n2p3;
   float c1=0.5,c2,h1r,h1i,h2r,h2i;
   double wr,wi,wpr,wpi,wtemp,theta;
   void four1();

   theta=3.141592653589793/(double) n;
   if (isign == 1) {
      c2 = -0.5;
      four1(data,n,1);
   } else {
      c2=0.5;
      theta = -theta;
   }
   wtemp=sin(0.5*theta);
   wpr = -2.0*wtemp*wtemp;
   wpi=sin(theta);
   wr=1.0+wpr;
   wi=wpi;
   n2p3=2*n+3;
   for (i=2;i<=n/2;i++) {
      i4=1+(i3=n2p3-(i2=1+(i1=i+i-1)));
      h1r=c1*(data[i1]+data[i3]);
      h1i=c1*(data[i2]-data[i4]);
      h2r = -c2*(data[i2]+data[i4]);
      h2i=c2*(data[i1]-data[i3]);
      data[i1]=h1r+wr*h2r-wi*h2i;
      data[i2]=h1i+wr*h2i+wi*h2r;
      data[i3]=h1r-wr*h2r+wi*h2i;
      data[i4] = -h1i+wr*h2i+wi*h2r;
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
   }
   if (isign == 1) {
      data[1] = (h1r=data[1])+data[2];
      data[2] = h1r-data[2];
   } else {
      data[1]=c1*((h1r=data[1])+data[2]);
      data[2]=c1*(h1r-data[2]);
      four1(data,n,-1);
   }
}

void sinft(y,n)
float y[];
int n;
{
   int j,m=n/2,n2=n+2;
   float sum,y1,y2;
   double theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;
   void realft();

   theta=3.14159265358979/(double) n;
   wtemp=sin(0.5*theta);
   wpr = -2.0*wtemp*wtemp;
   wpi=sin(theta);
   y[1]=0.0;
   for (j=2;j<=m+1;j++) {
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
      y1=wi*(y[j]+y[n2-j]);
      y2=0.5*(y[j]-y[n2-j]);
      y[j]=y1+y2;
      y[n2-j]=y1-y2;
   }
   realft(y,m,1);
   y[1]*=0.5;
   sum=y[2]=0.0;
   for (j=1;j<=n-1;j+=2) {
      sum += y[j];
      y[j]=y[j+1];
      y[j+1]=sum;
   }
}

void cosft(y,n,isign)
float y[];
int n,isign;
{
   int j,m,n2;
   float enf0,even,odd,sum,sume,sumo,y1,y2;
   double theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;
   void realft();

   theta=3.14159265358979/(double) n;
   wtemp=sin(0.5*theta);
   wpr = -2.0*wtemp*wtemp;
   wpi=sin(theta);
   sum=y[1];
   m=n >> 1;
   n2=n+2;
   for (j=2;j<=m;j++) {
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
      y1=0.5*(y[j]+y[n2-j]);
      y2=(y[j]-y[n2-j]);
      y[j]=y1-wi*y2;
      y[n2-j]=y1+wi*y2;
      sum += wr*y2;
   }
   realft(y,m,1);
   y[2]=sum;
   for (j=4;j<=n;j+=2) {
      sum += y[j];
      y[j]=sum;
   }
   if (isign == -1) {
      even=y[1];
      odd=y[2];
      for (j=3;j<=n-1;j+=2) {
         even += y[j];
         odd += y[j+1];
      }
      enf0=2.0*(even-odd);
      sumo=y[1]-enf0;
      sume=(2.0*odd/n)-sumo;
      y[1]=0.5*enf0;
      y[2] -= sume;
      for (j=3;j<=n-1;j+=2) {
         y[j] -= sumo;
         y[j+1] -= sume;
      }
   }
}

/*---12.4---------------------------------------------------------------------*/

void convlv(data,n,respns,m,isign,ans)
float data[],respns[],ans[];
int n,m,isign;
{
   int i,no2;
   float dum,mag2,*fft,*vector();
   void twofft(),realft(),nrerror(),free_vector();

   fft=vector(1,2*n);
   for (i=1;i<=(m-1)/2;i++)
      respns[n+1-i]=respns[m+1-i];
   for (i=(m+3)/2;i<=n-(m-1)/2;i++)
      respns[i]=0.0;
   twofft(data,respns,fft,ans,n);
   no2=n/2;
   for (i=2;i<=n+2;i+=2) {
      if (isign == 1) {
         ans[i-1]=(fft[i-1]*(dum=ans[i-1])-fft[i]*ans[i])/no2;
         ans[i]=(fft[i]*dum+fft[i-1]*ans[i])/no2;
      } else if (isign == -1) {
               if ((mag2=SQR(ans[i-1])+SQR(ans[i])) == 0.0)
            nrerror("Deconvolving at response zero in CONVLV");
         ans[i-1]=(fft[i-1]*(dum=ans[i-1])+fft[i]*ans[i])/mag2/no2;
         ans[i]=(fft[i]*dum-fft[i-1]*ans[i])/mag2/no2;
      } else nrerror("No meaning for ISIGN in CONVLV");
   }
   ans[2]=ans[n+1];
   realft(ans,no2,-1);
   free_vector(fft,1,2*n);
}

/*---12.5---------------------------------------------------------------------*/

void correl(data1,data2,n,ans)
float data1[],data2[],ans[];
int n;
{
   int no2,i;
   float dum,*fft,*vector();
   void twofft(),realft(),free_vector();

   fft=vector(1,2*n);
   twofft(data1,data2,fft,ans,n);
   no2=n/2;
   for (i=2;i<=n+2;i+=2) {
      ans[i-1]=(fft[i-1]*(dum=ans[i-1])+fft[i]*ans[i])/no2;
      ans[i]=(fft[i]*dum-fft[i-1]*ans[i])/no2;
   }
   ans[2]=ans[n+1];
   realft(ans,no2,-1);
   free_vector(fft,1,2*n);
}

/*---12.6---------------------------------------------------------------------*/
/*---12.7---------------------------------------------------------------------*/

#define WINDOW(j,a,b) (1.0-fabs((((j)-1)-(a))*(b)))       /* Parzen */
/* #define WINDOW(j,a,b) 1.0 */                           /* Square */
/* #define WINDOW(j,a,b) (1.0-SQR((((j)-1)-(a))*(b))) */  /* Welch  */

void spctrm(fp,p,m,k,ovrlap)
FILE *fp;
float p[];
int m,k,ovrlap;
{
   int mm,m44,m43,m4,kk,joffn,joff,j2,j;
   float w,facp,facm,*w1,*w2,sumw=0.0,den=0.0;
   float *vector();
   void four1(),free_vector();

   mm=m+m;
   m43=(m4=mm+mm)+3;
   m44=m43+1;
   w1=vector(1,m4);
   w2=vector(1,m);
   facm=m-0.5;
   facp=1.0/(m+0.5);
   for (j=1;j<=mm;j++) sumw += SQR(WINDOW(j,facm,facp));
   for (j=1;j<=m;j++) p[j]=0.0;
   if (ovrlap)
      for (j=1;j<=m;j++) fscanf(fp,"%lf",&w2[j]);
   for (kk=1;kk<=k;kk++) {
      for (joff = -1;joff<=0;joff++) {
         if (ovrlap) {
            for (j=1;j<=m;j++) w1[joff+j+j]=w2[j];
            for (j=1;j<=m;j++) fscanf(fp,"%lf",&w2[j]);
            joffn=joff+mm;
            for (j=1;j<=m;j++) w1[joffn+j+j]=w2[j];
         } else {
            for (j=joff+2;j<=m4;j+=2)
               fscanf(fp,"%lf",&w1[j]);
         }
      }
      for (j=1;j<=mm;j++) {
         j2=j+j;
         w=WINDOW(j,facm,facp);
         w1[j2] *= w;
         w1[j2-1] *= w;
      }
      four1(w1,mm,1);
      p[1] += (SQR(w1[1])+SQR(w1[2]));
      for (j=2;j<=m;j++) {
         j2=j+j;
         p[j] += (SQR(w1[j2])+SQR(w1[j2-1])
            +SQR(w1[m44-j2])+SQR(w1[m43-j2]));
      }
      den += sumw;
   }
   den *= m4;
   for (j=1;j<=m;j++) p[j] /= den;
   free_vector(w2,1,m);
   free_vector(w1,1,m4);
}

#undef WINDOW

/*---12.8---------------------------------------------------------------------*/

void memcof(data,n,m,pm,cof)
float data[],*pm,cof[];
int n,m;
{
   int k,j,i;
   float p=0.0,*wk1,*wk2,*wkm,*vector();
   void free_vector();

   wk1=vector(1,n);
   wk2=vector(1,n);
   wkm=vector(1,m);
   for (j=1;j<=n;j++) p += SQR(data[j]);
   *pm=p/n;
   wk1[1]=data[1];
   wk2[n-1]=data[n];
   for (j=2;j<=n-1;j++) {
      wk1[j]=data[j];
      wk2[j-1]=data[j];
   }
   for (k=1;k<=m;k++) {
      float num=0.0,denom=0.0;
      for (j=1;j<=(n-k);j++) {
         num += wk1[j]*wk2[j];
         denom += SQR(wk1[j])+SQR(wk2[j]);
      }
      cof[k]=2.0*num/denom;
      *pm *= (1.0-SQR(cof[k]));
      if (k != 1)
         for (i=1;i<=(k-1);i++)
            cof[i]=wkm[i]-cof[k]*wkm[k-i];
      if (k == m) {
         free_vector(wkm,1,m);
         free_vector(wk2,1,n);
         free_vector(wk1,1,n);
         return;
      }
      for (i=1;i<=k;i++) wkm[i]=cof[i];
      for (j=1;j<=(n-k-1);j++) {
         wk1[j] -= wkm[k]*wk2[j];
         wk2[j]=wk2[j+1]-wkm[k]*wk1[j+1];
      }
   }
}

float evlmem(fdt,cof,m,pm)
float fdt,cof[],pm;
int m;
{
   int i;
   float sumr=1.0,sumi=0.0;
   double wr=1.0,wi=0.0,wpr,wpi,wtemp,theta;

   theta=6.28318530717959*fdt;
   wpr=cos(theta);
   wpi=sin(theta);
   for (i=1;i<=m;i++) {
      wr=(wtemp=wr)*wpr-wi*wpi;
      wi=wi*wpr+wtemp*wpi;
      sumr -= cof[i]*wr;
      sumi -= cof[i]*wi;
   }
   return pm/(sumr*sumr+sumi*sumi);
}

/*---12.9---------------------------------------------------------------------*/
/*---12.10--------------------------------------------------------------------*/
/* #include "complex.h" !shik */

#define NPMAX 100
#define ZERO Complex(0.0,0.0)
#define ONE Complex(1.0,0.0)

void fixrts(d,npoles)
float d[];
int npoles;
{
   int i,j,polish;
   fcomplex a[NPMAX],roots[NPMAX];
   void zroots();

   a[npoles]=ONE;
   for (j=npoles-1;j>=0;j--)
      a[j]=Complex(-d[npoles-j],0.0);
   polish=1;
   zroots(a,npoles,roots,polish);
   for (j=1;j<=npoles;j++)
      if (Cabs(roots[j]) > 1.0)
         roots[j]=Cdiv(ONE,Conjg(roots[j]));
   a[0]=Csub(ZERO,roots[1]);
   a[1]=ONE;
   for (j=2;j<=npoles;j++) {
      a[j]=ONE;
      for (i=j;i>=2;i--)
         a[i-1]=Csub(a[i-2],Cmul(roots[j],a[i-1]));
      a[0]=Csub(ZERO,Cmul(roots[j],a[0]));
   }
   for (j=0;j<=npoles-1;j++)
      d[npoles-j] = -a[j].r;
}
#undef ZERO

void predic(data,ndata,d,npoles,future,nfut)
float data[],d[],future[];
int ndata,npoles,nfut;
{
   int k,j;
   float sum,discrp,*reg,*vector();
   void free_vector();

   reg=vector(1,npoles);
   for (j=1;j<=npoles;j++) reg[j]=data[ndata+1-j];
   for (j=1;j<=nfut;j++) {
      discrp=0.0;
      sum=discrp;
      for (k=1;k<=npoles;k++) sum += d[k]*reg[k];
      for (k=npoles;k>=2;k--) reg[k]=reg[k-1];
      future[j]=reg[1]=sum;
   }
   free_vector(reg,1,npoles);
}

/*---12.11--------------------------------------------------------------------*/

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void fourn(data,nn,ndim,isign)
float data[];
int nn[],ndim,isign;
{
   int i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
   int ibit,idim,k1,k2,n,nprev,nrem,ntot;
   float tempi,tempr;
   double theta,wi,wpi,wpr,wr,wtemp;

   ntot=1;
   for (idim=1;idim<=ndim;idim++)
      ntot *= nn[idim];
   nprev=1;
   for (idim=ndim;idim>=1;idim--) {
      n=nn[idim];
      nrem=ntot/(n*nprev);
      ip1=nprev << 1;
      ip2=ip1*n;
      ip3=ip2*nrem;
      i2rev=1;
      for (i2=1;i2<=ip2;i2+=ip1) {
         if (i2 < i2rev) {
            for (i1=i2;i1<=i2+ip1-2;i1+=2) {
               for (i3=i1;i3<=ip3;i3+=ip2) {
                  i3rev=i2rev+i3-i2;
                  SWAP(data[i3],data[i3rev]);
                  SWAP(data[i3+1],data[i3rev+1]);
               }
            }
         }
         ibit=ip2 >> 1;
         while (ibit >= ip1 && i2rev > ibit) {
            i2rev -= ibit;
            ibit >>= 1;
         }
         i2rev += ibit;
      }
      ifp1=ip1;
      while (ifp1 < ip2) {
         ifp2=ifp1 << 1;
         theta=isign*6.28318530717959/(ifp2/ip1);
         wtemp=sin(0.5*theta);
         wpr = -2.0*wtemp*wtemp;
         wpi=sin(theta);
         wr=1.0;
         wi=0.0;
         for (i3=1;i3<=ifp1;i3+=ip1) {
            for (i1=i3;i1<=i3+ip1-2;i1+=2) {
               for (i2=i1;i2<=ip3;i2+=ifp2) {
                  k1=i2;
                  k2=k1+ifp1;
                  tempr=wr*data[k2]-wi*data[k2+1];
                  tempi=wr*data[k2+1]+wi*data[k2];
                  data[k2]=data[k1]-tempr;
                  data[k2+1]=data[k1+1]-tempi;
                  data[k1] += tempr;
                  data[k1+1] += tempi;
               }
            }
            wr=(wtemp=wr)*wpr-wi*wpi+wr;
            wi=wi*wpr+wtemp*wpi+wi;
         }
         ifp1=ifp2;
      }
      nprev *= n;
   }
}

#undef SWAP


/*---13.0---------------------------------------------------------------------*/
/*---13.1---------------------------------------------------------------------*/

void moment(data,n,ave,adev,sdev,svar,skew,curt)
int n;
float data[],*ave,*adev,*sdev,*svar,*skew,*curt;
{
   int j;
   float s,p;
   void nrerror();

   if (n <= 1) nrerror("n must be at least 2 in MOMENT");
   s=0.0;
   for (j=1;j<=n;j++) s += data[j];
   *ave=s/n;
   *adev=(*svar)=(*skew)=(*curt)=0.0;
   for (j=1;j<=n;j++) {
      *adev += fabs(s=data[j]-(*ave));
      *svar += (p=s*s);
      *skew += (p *= s);
      *curt += (p *= s);
   }
   *adev /= n;
   *svar /= (n-1);
   *sdev=sqrt(*svar);
   if (*svar) {
      *skew /= (n*(*svar)*(*sdev));
      *curt=(*curt)/(n*(*svar)*(*svar))-3.0;
   } else nrerror("No skew/kurtosis when variance = 0 (in MOMENT)");
}

/*---13.2---------------------------------------------------------------------*/

void mdian1(x,n,xmed)
float x[],*xmed;
int n;
{
   int n2,n2p;
   void sort();

   sort(n,x);
   n2p=(n2=n/2)+1;
   *xmed=(n % 2 ? x[n2p] : 0.5*(x[n2]+x[n2p]));
}

#define BIG 1.0e30
#define AFAC 1.5
#define AMP 1.5

#define ITMAX 200 /* shik,940118 */

void mdian2(x,n,xmed)
int n;
float x[],*xmed;
{
   int i=0; /* shik,940118 */
   int np,nm,j;
   float xx,xp,xm,sumx,sum,eps,stemp,dum,ap,am,aa,a;
   int k=0; /* shik,940521 */

   a=0.5*(x[1]+x[n]);
   eps=fabs(x[n]-x[1]);
   am = -(ap=BIG);
   for (;;) {
      sum=sumx=0.0;
      np=nm=0;
      xm = -(xp=BIG);
      for (j=1;j<=n;j++) {
         xx=x[j];
         if (xx != a) {
            if (xx > a) {
               ++np;
               if (xx < xp) xp=xx;
            } else if (xx < a) {
               ++nm;
               if (xx > xm) xm=xx;
            }
            sum += dum=1.0/(eps+fabs(xx-a));
            sumx += xx*dum;
         } else
            k++; /* shik,940521 */
      }
      if (k==n) { /* shik,2K0622 */
         *xmed=a;
         return;
      }
      stemp=(sumx/sum)-a;
      if (np-nm >= 2) {
         am=a;
         aa =  stemp < 0.0 ? xp : xp+stemp*AMP;
         if (aa > ap) aa=0.5*(a+ap);
         eps=AFAC*fabs(aa-a);
         a=aa;
      } else if (nm-np >= 2) {
         ap=a;
         aa = stemp > 0.0 ? xm : xm+stemp*AMP;
         if (aa < am) aa=0.5*(a+am);
         eps=AFAC*fabs(aa-a);
         a=aa;
      } else {
R: /* shik,960307 */
         if (n-k<=1) { /* shik,940521 */
            *xmed=a;   /* shik,940521 */
            return;    /* shik,940521 */
         }             /* shik,940521 */
         if (n % 2 == 0) {
            *xmed = 0.5*(np == nm ? xp+xm : np > nm ? a+xp : xm+a);
         } else {
            *xmed = np == nm ? a : np > nm ? xp : xm;
         }
         return;
      }
      if (++i>=ITMAX) goto R; /* shik,940118 */
   }
}

#undef ITMAX /* shik,940118 */

#undef BIG
#undef AFAC
#undef AMP

/*---13.3---------------------------------------------------------------------*/
/*---13.4---------------------------------------------------------------------*/

void ttest(data1,n1,data2,n2,t,prob)
int n1,n2;
float data1[],data2[],*t,*prob;
{
   float var1,var2,svar,df,ave1,ave2;
   void avevar();
   float betai();

   avevar(data1,n1,&ave1,&var1);
   avevar(data2,n2,&ave2,&var2);
   df=n1+n2-2;
   svar=((n1-1)*var1+(n2-1)*var2)/df;
   *t=(ave1-ave2)/sqrt(svar*(1.0/n1+1.0/n2));
   *prob=betai(0.5*df,0.5,df/(df+(*t)*(*t)));
}

void avevar(data,n,ave,svar)
float data[],*ave,*svar;
int n;
{
   int j;
   float s;

   *ave=(*svar)=0.0;
   for (j=1;j<=n;j++) *ave += data[j];
   *ave /= n;
   for (j=1;j<=n;j++) {
      s=data[j]-(*ave);
      *svar += s*s;
   }
   *svar /= (n-1);
}

void tutest(data1,n1,data2,n2,t,prob)
float data1[],data2[],*t,*prob;
int n1,n2;
{
   float var1,var2,df,ave1,ave2;
   void avevar();
   float betai();

   avevar(data1,n1,&ave1,&var1);
   avevar(data2,n2,&ave2,&var2);
   *t=(ave1-ave2)/sqrt(var1/n1+var2/n2);
   df=SQR(var1/n1+var2/n2)/(SQR(var1/n1)/(n1-1)+SQR(var2/n2)/(n2-1));
   *prob=betai(0.5*df,0.5,df/(df+SQR(*t)));
}

void tptest(data1,data2,n,t,prob)
float data1[],data2[],*t,*prob;
int n;
{
   int j;
   float var1,var2,ave1,ave2,sd,df,cov=0.0;
   void avevar();
   float betai();

   avevar(data1,n,&ave1,&var1);
   avevar(data2,n,&ave2,&var2);
   for (j=1;j<=n;j++)
      cov += (data1[j]-ave1)*(data2[j]-ave2);
   cov /= df=n-1;
   sd=sqrt((var1+var2-2.0*cov)/n);
   *t=(ave1-ave2)/sd;
   *prob=betai(0.5*df,0.5,df/(df+(*t)*(*t)));
}

void ftest(data1,n1,data2,n2,f,prob)
float data1[],data2[],*f,*prob;
int n1,n2;
{
   float var1,var2,ave1,ave2,df1,df2;
   void avevar();
   float betai();

   avevar(data1,n1,&ave1,&var1);
   avevar(data2,n2,&ave2,&var2);
   if (var1 > var2) {
      *f=var1/var2;
      df1=n1-1;
      df2=n2-1;
   } else {
      *f=var2/var1;
      df1=n2-1;
      df2=n1-1;
   }
   *prob = 2.0*betai(0.5*df2,0.5*df1,df2/(df2+df1*(*f)));
   if (*prob > 1.0) *prob=2.0-*prob;
}

/*---13.5---------------------------------------------------------------------*/

void chsone(bins,ebins,nbins,knstrn,df,chsq,prob)
float bins[],ebins[],*df,*chsq,*prob;
int nbins,knstrn;
{
   int j;
   float temp;
   float gammq();
   void nrerror();

   *df=nbins-1-knstrn;
   *chsq=0.0;
   for (j=1;j<=nbins;j++) {
      if (ebins[j] <= 0.0) nrerror("Bad expected number in CHSONE");
      temp=bins[j]-ebins[j];
      *chsq += temp*temp/ebins[j];
   }
   *prob=gammq(0.5*(*df),0.5*(*chsq));
}

void chstwo(bins1,bins2,nbins,knstrn,df,chsq,prob)
float bins1[],bins2[],*df,*chsq,*prob;
int nbins,knstrn;
{
   int j;
   float temp;
   float gammq();

   *df=nbins-1-knstrn;
   *chsq=0.0;
   for (j=1;j<=nbins;j++)
      if (bins1[j] == 0.0 && bins2[j] == 0.0)
         *df -= 1.0;
      else {
         temp=bins1[j]-bins2[j];
         *chsq += temp*temp/(bins1[j]+bins2[j]);
      }
   *prob=gammq(0.5*(*df),0.5*(*chsq));
}

#ifndef MY_maxarg /* !shik */
#define MY_maxarg 1 /* !shik */
static float maxarg1,maxarg2;
#endif /* !shik */
#define MAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
   (maxarg1) : (maxarg2))

void ksone(data,n,func,d,prob)
float data[],*d,*prob;
float (*func)();   /* ANSI: float (*func)(float); */
int n;
{
   int j;
   float fo=0.0,fn,ff,en,dt;
   void sort();
   float probks();

   sort(n,data);
   en=n;
   *d=0.0;
   for (j=1;j<=n;j++) {
      fn=j/en;
      ff=(*func)(data[j]);
      dt = MAX(fabs(fo-ff),fabs(fn-ff));
      if (dt > *d) *d=dt;
      fo=fn;
   }
   *prob=probks(sqrt(en)*(*d));
}

#undef MAX

void kstwo(data1,n1,data2,n2,d,prob)
float data1[],data2[],*d,*prob;
int n1,n2;
{
   int j1=1,j2=1;
   float en1,en2,fn1=0.0,fn2=0.0,dt,d1,d2;
   void sort();
   float probks();

   en1=n1;
   en2=n2;
   *d=0.0;
   sort(n1,data1);
   sort(n2,data2);
   while (j1 <= n1 && j2 <= n2) {
      if ((d1=data1[j1]) <= (d2=data2[j2])) {
         fn1=(j1++)/en1;
      }
      if (d2 <= d1) {
         fn2=(j2++)/en2;
      }
      if ((dt=fabs(fn2-fn1)) > *d) *d=dt;
   }
   *prob=probks(sqrt(en1*en2/(en1+en2))*(*d));
}

#define EPS1 0.001
#define EPS2 1.0e-8

float probks(alam)
float alam;
{
   int j;
   float a2,fac=2.0,sum=0.0,term,termbf=0.0;

   a2 = -2.0*alam*alam;
   for (j=1;j<=100;j++) {
      term=fac*exp(a2*j*j);
      sum += term;
      if (fabs(term) <= EPS1*termbf || fabs(term) < EPS2*sum) return sum;
      fac = -fac;
      termbf=fabs(term);
   }
   return 0.0;
}

#undef EPS1
#undef EPS2

/*---13.6---------------------------------------------------------------------*/

#define TINY 1.0e-30

void cntab1(nn,ni,nj,chisq,df,prob,cramrv,ccc)
int **nn,ni,nj;
float *chisq,*df,*prob,*cramrv,*ccc;
{
   int nnj,nni,j,i,minij;
   float sum=0.0,expctd,*sumi,*sumj,temp,gammq(),*vector();
   void free_vector();

   sumi=vector(1,ni);
   sumj=vector(1,nj);
   nni=ni;
   nnj=nj;
   for (i=1;i<=ni;i++) {
      sumi[i]=0.0;
      for (j=1;j<=nj;j++) {
         sumi[i] += nn[i][j];
         sum += nn[i][j];
      }
      if (sumi[i] == 0.0) --nni;
   }
   for (j=1;j<=nj;j++) {
      sumj[j]=0.0;
      for (i=1;i<=ni;i++) sumj[j] += nn[i][j];
      if (sumj[j] == 0.0) --nnj;
   }
   *df=nni*nnj-nni-nnj+1;
   *chisq=0.0;
   for (i=1;i<=ni;i++) {
      for (j=1;j<=nj;j++) {
         expctd=sumj[j]*sumi[i]/sum;
         temp=nn[i][j]-expctd;
         *chisq += temp*temp/(expctd+TINY);
      }
   }
   *prob=gammq(0.5*(*df),0.5*(*chisq));
   minij = nni < nnj ? nni-1 : nnj-1;
   *cramrv=sqrt(*chisq/(sum*minij));
   *ccc=sqrt(*chisq/(*chisq+sum));
   free_vector(sumj,1,nj);
   free_vector(sumi,1,ni);
}

#undef TINY

#define TINY 1.0e-30

void cntab2(nn,ni,nj,h,hx,hy,hygx,hxgy,uygx,uxgy,uxy)
int ni,nj,**nn;
float *h,*hx,*hy,*hygx,*hxgy,*uygx,*uxgy,*uxy;
{
   int i,j;
   float sum=0.0,p,*sumi,*sumj,*vector();
   void free_vector();

   sumi=vector(1,ni);
   sumj=vector(1,nj);
   for (i=1;i<=ni;i++) {
      sumi[i]=0.0;
      for (j=1;j<=nj;j++) {
         sumi[i] += nn[i][j];
         sum += nn[i][j];
      }
   }
   for (j=1;j<=nj;j++) {
      sumj[j]=0.0;
      for (i=1;i<=ni;i++)
         sumj[j] += nn[i][j];
   }
   *hx=0.0;
   for (i=1;i<=ni;i++)
      if (sumi[i]) {
         p=sumi[i]/sum;
         *hx -= p*log(p);
      }
   *hy=0.0;
   for (j=1;j<=nj;j++)
      if (sumj[j]) {
         p=sumj[j]/sum;
         *hy -= p*log(p);
      }
   *h=0.0;
   for (i=1;i<=ni;i++)
      for (j=1;j<=nj;j++)
         if (nn[i][j]) {
            p=nn[i][j]/sum;
            *h -= p*log(p);
         }
   *hygx=(*h)-(*hx);
   *hxgy=(*h)-(*hy);
   *uygx=(*hy-*hygx)/(*hy+TINY);
   *uxgy=(*hx-*hxgy)/(*hx+TINY);
   *uxy=2.0*(*hx+*hy-*h)/(*hx+*hy+TINY);
   free_vector(sumj,1,nj);
   free_vector(sumi,1,ni);
}

#undef TINY

/*---13.7---------------------------------------------------------------------*/

#define TINY 1.0e-20
void pearsn(x,y,n,r,prob,z)
float x[],y[],*r,*prob,*z;
int n;
{
   int j;
   float yt,xt,t,df;
   float syy=0.0,sxy=0.0,sxx=0.0,ay=0.0,ax=0.0;
   float betai(),erfcc();

   for (j=1;j<=n;j++) {
      ax += x[j];
      ay += y[j];
   }
   ax /= n;
   ay /= n;
   for (j=1;j<=n;j++) {
      xt=x[j]-ax;
      yt=y[j]-ay;
      sxx += xt*xt;
      syy += yt*yt;
      sxy += xt*yt;
   }
   *r=sxy/sqrt(sxx*syy);
   *z=0.5*log((1.0+(*r)+TINY)/(1.0-(*r)+TINY));
   df=n-2;
   t=(*r)*sqrt(df/((1.0-(*r)+TINY)*(1.0+(*r)+TINY)));
   *prob=betai(0.5*df,0.5,df/(df+t*t));
/*   *prob=erfcc(fabs((*z)*sqrt(n-1.0))/1.4142136)   */
}
#undef TINY

/*---13.8---------------------------------------------------------------------*/

void spear(data1,data2,n,d,zd,probd,rs,probrs)
float data1[],data2[];
float *d,*zd,*probd,*rs,*probrs;
int n;
{
   int j;
   float vard,t,sg,sf,fac,en3n,en,df,aved,*wksp1,*wksp2;
   void sort2(),crank(),free_vector();
   float erfcc(),betai(),*vector();

   wksp1=vector(1,n);
   wksp2=vector(1,n);
   for (j=1;j<=n;j++) {
      wksp1[j]=data1[j];
      wksp2[j]=data2[j];
   }
   sort2(n,wksp1,wksp2);
   crank(n,wksp1,&sf);
   sort2(n,wksp2,wksp1);
   crank(n,wksp2,&sg);
         *d=0.0;
   for (j=1;j<=n;j++)
      *d += SQR(wksp1[j]-wksp2[j]);
   en=n;
   en3n=en*en*en-en;
   aved=en3n/6.0-(sf+sg)/12.0;
   fac=(1.0-sf/en3n)*(1.0-sg/en3n);
   vard=((en-1.0)*en*en*SQR(en+1.0)/36.0)*fac;
   *zd=(*d-aved)/sqrt(vard);
   *probd=erfcc(fabs(*zd)/1.4142136);
   *rs=(1.0-(6.0/en3n)*(*d+0.5*(sf+sg)))/fac;
   t=(*rs)*sqrt((en-2.0)/((*rs+1.0)*(1.0-(*rs))));
   df=en-2.0;
   *probrs=betai(0.5*df,0.5,df/(df+t*t));
   free_vector(wksp2,1,n);
   free_vector(wksp1,1,n);
}

void crank(n,w,s)
float w[],*s;
int n;
{
   int j=1,ji,jt;
   float t,rank;

   *s=0.0;
   while (j < n) {
      if (w[j+1] != w[j]) {
         w[j]=j;
         ++j;
      } else {
         for (jt=j+1;jt<=n;jt++)
            if (w[jt] != w[j]) break;
         rank=0.5*(j+jt-1);
         for (ji=j;ji<=(jt-1);ji++) w[ji]=rank;
         t=jt-j;
         *s += t*t*t-t;
         j=jt;
      }
   }
   if (j == n) w[n]=n;
}

void kendl1(data1,data2,n,tau,z,prob)
float data1[],data2[],*tau,*z,*prob;
int n;
{
   int n2=0,n1=0,k,j,is=0;
   float svar,aa,a2,a1;
   float erfcc();

   for (j=1;j<n;j++) {
      for (k=(j+1);k<=n;k++) {
         a1=data1[j]-data1[k];
         a2=data2[j]-data2[k];
         aa=a1*a2;
         if (aa) {
            ++n1;
            ++n2;
            aa > 0.0 ? ++is : --is;
         } else {
            if (a1) ++n1;
            if (a2) ++n2;
         }
      }
   }
   *tau=is/(sqrt((double) n1)*sqrt((double) n2));
   svar=(4.0*n+10.0)/(9.0*n*(n-1.0));
   *z=(*tau)/sqrt(svar);
   *prob=erfcc(fabs(*z)/1.4142136);
}

void kendl2(tab,i,j,tau,z,prob)
float **tab,*tau,*z,*prob;
int i,j;
{
   int nn,mm,m2,m1,lj,li,l,kj,ki,k;
   float svar,s=0.0,points,pairs,en2=0.0,en1=0.0;
   float erfcc();

   nn=i*j;
   points=tab[i][j];
   for (k=0;k<=nn-2;k++) {
      ki=(k/j);
      kj=k-j*ki;
      points += tab[ki+1][kj+1];
      for (l=k+1;l<=nn-1;l++) {
         li=l/j;
         lj=l-j*li;
         mm=(m1=li-ki)*(m2=lj-kj);
         pairs=tab[ki+1][kj+1]*tab[li+1][lj+1];
         if (mm) {
            en1 += pairs;
            en2 += pairs;
            s += (mm > 0 ? pairs : -pairs);
         } else {
            if (m1) en1 += pairs;
            if (m2) en2 += pairs;
         }
      }
   }
   *tau=s/sqrt(en1*en2);
   svar=(4.0*points+10.0)/(9.0*points*(points-1.0));
   *z=(*tau)/sqrt(svar);
   *prob=erfcc(fabs(*z)/1.4142136);
}

/*---13.9---------------------------------------------------------------------*/
/*
Smooths an array y of n data points, with a window whose full width is of order
pts neighboring points, a user supplied value. y is modified. y should be
dimensioned at least of length [1..mp],
where mp >= integral power of two >= n+2*pts.
*/
void smooft(y,n,pts)
float y[],pts;
int n;
{
   int nmin,m=2,mo2,k,j;
   float yn,y1,rn1,fac,cnst;
   void realft();

   nmin=n+(int) (2.0*pts+0.5);
   while (m < nmin) m *= 2;
   cnst=pts/m,cnst=cnst*cnst;
   y1=y[1];
   yn=y[n];
   rn1=1.0/(n-1);
   for (j=1;j<=n;j++)
      y[j] += (-rn1*(y1*(n-j)+yn*(j-1)));
   for (j=n+1;j<=m;j++) y[j]=0.0;
   mo2=m >> 1;
   realft(y,mo2,1);
   y[1] /= mo2;
   fac=1.0;
   for (j=1;j<mo2;j++) {
      k=2*j+1;
      if (fac) {
         if ( (fac=(1.0-cnst*j*j)/mo2) < 0.0) fac=0.0;
         y[k]=fac*y[k];
         y[k+1]=fac*y[k+1];
      } else  y[k+1]=y[k]=0.0;
   }
   if ( (fac=(1.0-0.25*pts*pts)/mo2) < 0.0) fac=0.0;
   y[2] *= fac;
   realft(y,mo2,-1);
   for (j=1;j<=n;j++)
      y[j] += rn1*(y1*(n-j)+yn*(j-1));
}

/*---14.0---------------------------------------------------------------------*/
/*---14.1---------------------------------------------------------------------*/
/*---14.2---------------------------------------------------------------------*/

void fit(x,y,ndata,sig,mwt,a,b,siga,sigb,chi2,q)
float x[],y[],sig[],*a,*b,*siga,*sigb,*chi2,*q;
int ndata,mwt;
{
   int i;
   float wt,t,sxoss,sx=0.0,sy=0.0,st2=0.0,ss,sigdat;
   float gammq();

   *b=0.0;
   if (mwt) {
      ss=0.0;
      for (i=1;i<=ndata;i++) {
         wt=1.0/SQR(sig[i]);
         ss += wt;
         sx += x[i]*wt;
         sy += y[i]*wt;
      }
   } else {
      for (i=1;i<=ndata;i++) {
         sx += x[i];
         sy += y[i];
      }
      ss=ndata;
   }
   sxoss=sx/ss;
   if (mwt) {
      for (i=1;i<=ndata;i++) {
         t=(x[i]-sxoss)/sig[i];
         st2 += t*t;
         *b += t*y[i]/sig[i];
      }
   } else {
      for (i=1;i<=ndata;i++) {
         t=x[i]-sxoss;
         st2 += t*t;
         *b += t*y[i];
      }
   }
   *b /= st2;
   *a=(sy-sx*(*b))/ss;
   *siga=sqrt((1.0+sx*sx/(ss*st2))/ss);
   *sigb=sqrt(1.0/st2);
   *chi2=0.0;
   if (mwt == 0) {
      for (i=1;i<=ndata;i++)
         *chi2 += SQR(y[i]-(*a)-(*b)*x[i]);
      *q=1.0;
      sigdat=sqrt((*chi2)/(ndata-2));
      *siga *= sigdat;
      *sigb *= sigdat;
   } else {
      for (i=1;i<=ndata;i++)
         *chi2 += SQR((y[i]-(*a)-(*b)*x[i])/sig[i]);
      *q=gammq(0.5*(ndata-2),0.5*(*chi2));
   }
}

/*---14.3---------------------------------------------------------------------*/

void lfit(x,y,sig,ndata,a,ma,lista,mfit,covar,chisq,funcs)
int ndata,ma,lista[],mfit;
float x[],y[],sig[],a[],**covar,*chisq;
void (*funcs)();   /* ANSI: void (*funcs)(float,float *,int); */
{
   int k,kk,j,ihit,i;
   float ym,wt,sum,sig2i,**beta,*afunc;
   void gaussj(),covsrt(),nrerror(),free_matrix(),free_vector();
   float **matrix(),*vector();

   beta=matrix(1,ma,1,1);
   afunc=vector(1,ma);
   kk=mfit+1;
   for (j=1;j<=ma;j++) {
      ihit=0;
      for (k=1;k<=mfit;k++)
         if (lista[k] == j) ihit++;
      if (ihit == 0)
         lista[kk++]=j;
      else if (ihit > 1) nrerror("Bad LISTA permutation in LFIT-1");
   }
   if (kk != (ma+1)) nrerror("Bad LISTA permutation in LFIT-2");
   for (j=1;j<=mfit;j++) {
      for (k=1;k<=mfit;k++) covar[j][k]=0.0;
      beta[j][1]=0.0;
   }
   for (i=1;i<=ndata;i++) {
      (*funcs)(x[i],afunc,ma);
      ym=y[i];
      if (mfit < ma)
         for (j=(mfit+1);j<=ma;j++)
            ym -= a[lista[j]]*afunc[lista[j]];
      sig2i=1.0/SQR(sig[i]);
      for (j=1;j<=mfit;j++) {
         wt=afunc[lista[j]]*sig2i;
         for (k=1;k<=j;k++)
            covar[j][k] += wt*afunc[lista[k]];
         beta[j][1] += ym*wt;
      }
   }
   if (mfit > 1)
      for (j=2;j<=mfit;j++)
         for (k=1;k<=j-1;k++)
            covar[k][j]=covar[j][k];
   gaussj(covar,mfit,beta,1);
   for (j=1;j<=mfit;j++) a[lista[j]]=beta[j][1];
   *chisq=0.0;
   for (i=1;i<=ndata;i++) {
      (*funcs)(x[i],afunc,ma);
      for (sum=0.0,j=1;j<=ma;j++) sum += a[j]*afunc[j];
      *chisq += SQR((y[i]-sum)/sig[i]);
   }
   covsrt(covar,ma,lista,mfit);
   free_vector(afunc,1,ma);
   free_matrix(beta,1,ma,1,1);
}

void covsrt(covar,ma,lista,mfit)
float **covar;
int ma,lista[],mfit;
{
   int i,j;
   float swap;

   for (j=1;j<ma;j++)
      for (i=j+1;i<=ma;i++) covar[i][j]=0.0;
   for (i=1;i<mfit;i++)
      for (j=i+1;j<=mfit;j++) {
         if (lista[j] > lista[i])
            covar[lista[j]][lista[i]]=covar[i][j];
         else
            covar[lista[i]][lista[j]]=covar[i][j];
      }
   swap=covar[1][1];
   for (j=1;j<=ma;j++) {
      covar[1][j]=covar[j][j];
      covar[j][j]=0.0;
   }
   covar[lista[1]][lista[1]]=swap;
   for (j=2;j<=mfit;j++) covar[lista[j]][lista[j]]=covar[1][j];
   for (j=2;j<=ma;j++)
      for (i=1;i<=j-1;i++) covar[i][j]=covar[j][i];
}

/* #define TOL 1.0e-5 */
#define TOL 1.0e-38 /* float min. suggested by Kim Jong Tae,(c)shik,940808 */

void svdfit(x,y,sig,ndata,a,ma,u,v,w,chisq,funcs)
float x[],y[],sig[],a[],**u,**v,w[],*chisq;
int ndata,ma;
void (*funcs)();   /* ANSI: void (*funcs)(float,float *,int); */
{
   int j,i;
   float wmax,tmp,thresh,sum,*b,*afunc,*vector();
   void svdcmp(),svbksb(),free_vector();

   b=vector(1,ndata);
   afunc=vector(1,ma);
   for (i=1;i<=ndata;i++) {
      (*funcs)(x[i],afunc,ma);
      tmp=1.0/sig[i];
      for (j=1;j<=ma;j++) u[i][j]=afunc[j]*tmp;
      b[i]=y[i]*tmp;
   }
   svdcmp(u,ndata,ma,w,v);
   wmax=0.0;
   for (j=1;j<=ma;j++)
      if (w[j] > wmax) wmax=w[j];
   thresh=TOL*wmax;
   for (j=1;j<=ma;j++)
      if (w[j] < thresh) w[j]=0.0;
   svbksb(u,w,v,ndata,ma,b,a);
   *chisq=0.0;
   for (i=1;i<=ndata;i++) {
      (*funcs)(x[i],afunc,ma);
      for (sum=0.0,j=1;j<=ma;j++) sum += a[j]*afunc[j];
      *chisq += (tmp=(y[i]-sum)/sig[i],tmp*tmp);
   }
   free_vector(afunc,1,ma);
   free_vector(b,1,ndata);
}

#undef TOL

void svdvar(v,ma,w,cvm)
float **v,w[],**cvm;
int ma;
{
   int k,j,i;
   float sum,*wti,*vector();
   void free_vector();

   wti=vector(1,ma);
   for (i=1;i<=ma;i++) {
      wti[i]=0.0;
      if (w[i]) wti[i]=1.0/(w[i]*w[i]);
   }
   for (i=1;i<=ma;i++) {
      for (j=1;j<=i;j++) {
         for (sum=0.0,k=1;k<=ma;k++) sum += v[i][k]*v[j][k]*wti[k];
         cvm[j][i]=cvm[i][j]=sum;
      }
   }
   free_vector(wti,1,ma);
}

void fpoly(x,p,np)
float x,p[];
int np;
{
   int j;

   p[1]=1.0;
   for (j=2;j<=np;j++) p[j]=p[j-1]*x;
}

void ifpoly(x,p,np) /* 950715,(c)Y.S.Kim */
float x,p[];
int np;
{
   int j;

   p[1]=1.0;
   for (j=2;j<=np;j++) p[j]=p[j-1]/x;
}

void fleg(x,pl,nl)
float x,pl[];
int nl;
{
   int j;
   float twox,f2,f1,d;

   pl[1]=1.0;
   pl[2]=x;
   if (nl > 2) {
      twox=2.0*x;
      f2=x;
      d=1.0;
      for (j=3;j<=nl;j++) {
         f1=d;
         d += 1.0;
         f2 += twox;
         pl[j]=(f2*pl[j-1]-f1*pl[j-2])/d;
      }
   }
}

/*---14.4---------------------------------------------------------------------*/

void mrqmin(x,y,sig,ndata,a,ma,lista,mfit,covar,alpha,chisq,funcs,alamda)
float x[],y[],sig[],a[],**covar,**alpha,*chisq,*alamda;
int ndata,ma,lista[],mfit;
void (*funcs)();
{
   int k,kk,j,ihit;
   static float *da,*atry,**oneda,*beta,ochisq;
   float *vector(),**matrix();
   void mrqcof(),gaussj(),covsrt(),nrerror(),free_matrix(),free_vector();

   if (*alamda < 0.0) {
      oneda=matrix(1,mfit,1,1);
      atry=vector(1,ma);
      da=vector(1,ma);
      beta=vector(1,ma);
      kk=mfit+1;
      for (j=1;j<=ma;j++) {
         ihit=0;
         for (k=1;k<=mfit;k++)
            if (lista[k] == j) ihit++;
         if (ihit == 0)
            lista[kk++]=j;
         else if (ihit > 1) nrerror("Bad LISTA permutation in MRQMIN-1");
      }
      if (kk != ma+1) nrerror("Bad LISTA permutation in MRQMIN-2");
      *alamda=0.001;
      mrqcof(x,y,sig,ndata,a,ma,lista,mfit,alpha,beta,chisq,funcs);
      ochisq=(*chisq);
   }
   for (j=1;j<=mfit;j++) {
      for (k=1;k<=mfit;k++) covar[j][k]=alpha[j][k];
      covar[j][j]=alpha[j][j]*(1.0+(*alamda));
      oneda[j][1]=beta[j];
   }
   gaussj(covar,mfit,oneda,1);
   for (j=1;j<=mfit;j++)
      da[j]=oneda[j][1];
   if (*alamda == 0.0) {
      covsrt(covar,ma,lista,mfit);
      free_vector(beta,1,ma);
      free_vector(da,1,ma);
      free_vector(atry,1,ma);
      free_matrix(oneda,1,mfit,1,1);
      return;
   }
   for (j=1;j<=ma;j++) atry[j]=a[j];
   for (j=1;j<=mfit;j++)
      atry[lista[j]] = a[lista[j]]+da[j];
   mrqcof(x,y,sig,ndata,atry,ma,lista,mfit,covar,da,chisq,funcs);
   if (*chisq < ochisq) {
      *alamda *= 0.1;
      ochisq=(*chisq);
      for (j=1;j<=mfit;j++) {
         for (k=1;k<=mfit;k++) alpha[j][k]=covar[j][k];
         beta[j]=da[j];
         a[lista[j]]=atry[lista[j]];
      }
   } else {
      *alamda *= 10.0;
      *chisq=ochisq;
   }
   return;
}

void mrqcof(x,y,sig,ndata,a,ma,lista,mfit,alpha,beta,chisq,funcs)
float x[],y[],sig[],a[],**alpha,beta[],*chisq;
int ndata,ma,lista[],mfit;
void (*funcs)();   /* ANSI: void (*funcs)(float,float *,float *,float *,int);
*/
{
   int k,j,i;
   float ymod,wt,sig2i,dy,*dyda,*vector();
   void free_vector();

   dyda=vector(1,ma);
   for (j=1;j<=mfit;j++) {
      for (k=1;k<=j;k++) alpha[j][k]=0.0;
      beta[j]=0.0;
   }
   *chisq=0.0;
   for (i=1;i<=ndata;i++) {
      (*funcs)(x[i],a,&ymod,dyda,ma);
      sig2i=1.0/(sig[i]*sig[i]);
      dy=y[i]-ymod;
      for (j=1;j<=mfit;j++) {
         wt=dyda[lista[j]]*sig2i;
         for (k=1;k<=j;k++)
            alpha[j][k] += wt*dyda[lista[k]];
         beta[j] += dy*wt;
      }
      (*chisq) += dy*dy*sig2i;
   }
   for (j=2;j<=mfit;j++)
      for (k=1;k<=j-1;k++) alpha[k][j]=alpha[j][k];
   free_vector(dyda,1,ma);
}

void fgauss(x,a,y,dyda,na)
float x,a[],*y,dyda[];
int na;
{
   int i;
   float fac,ex,arg;

   *y=0.0;
   for (i=1;i<=na-1;i+=3)
   {
      arg=(x-a[i+1])/a[i+2];
      ex=exp(-arg*arg);
      fac=a[i]*ex*2.0*arg;
      *y += a[i]*ex;
      dyda[i]=ex;
      dyda[i+1]=fac/a[i+2];
      dyda[i+2]=fac*arg/a[i+2];
   }
}

/*---14.5---------------------------------------------------------------------*/
/*---14.6---------------------------------------------------------------------*/

int ndatat=0;   /* defining declaration */
float *xt=0,*yt=0,aa=0.0,abdevt=0.0;   /* defining declaration */

void medfit(x,y,ndata,a,b,abdev)
float *x,*y,*a,*b,*abdev;
int ndata;
{
   int j;
   float bb,b1,b2,del,f,f1,f2,sigb,temp;
   float sx=0.0,sy=0.0,sxy=0.0,sxx=0.0,chisq=0.0;
   float rofunc();

   ndatat=ndata;
   xt=x;
   yt=y;
   for (j=1;j<=ndata;j++) {
      sx += x[j];
      sy += y[j];
      sxy += x[j]*y[j];
      sxx += x[j]*x[j];
   }
   del=ndata*sxx-sx*sx;
   aa=(sxx*sy-sx*sxy)/del;
   bb=(ndata*sxy-sx*sy)/del;
   for (j=1;j<=ndata;j++)
      chisq += (temp=y[j]-(aa+bb*x[j]),temp*temp);
   sigb=sqrt(chisq/del);
   b1=bb;
   f1=rofunc(b1);
   b2=bb+((f1 > 0.0) ? fabs(3.0*sigb) : -fabs(3.0*sigb));
   f2=rofunc(b2);
   while (f1*f2 > 0.0) {
      bb=2.0*b2-b1;
      b1=b2;
      f1=f2;
      b2=bb;
      f2=rofunc(b2);
   }
   sigb=0.01*sigb;
   while (fabs(b2-b1) > sigb) {
      bb=0.5*(b1+b2);
      if (bb == b1 || bb == b2) break;
      f=rofunc(bb);
      if (f*f1 >= 0.0) {
         f1=f;
         b1=bb;
      } else {
         f2=f;
         b2=bb;
      }
   }
   *a=aa;
   *b=bb;
   *abdev=abdevt/ndata;
}

extern int ndatat;   /* defined in MEDFIT */
extern float *xt,*yt,aa,abdevt;

float rofunc(b)
float b;
{
   int j,n1,nmh,nml;
   float *arr,d,sum=0.0,*vector();
   void sort(),free_vector();

   arr=vector(1,ndatat);
   n1=ndatat+1;
   nml=n1/2;
   nmh=n1-nml;
   for (j=1;j<=ndatat;j++) arr[j]=yt[j]-b*xt[j];
   sort(ndatat,arr);
   aa=0.5*(arr[nml]+arr[nmh]);
   abdevt=0.0;
   for (j=1;j<=ndatat;j++) {
      d=yt[j]-(b*xt[j]+aa);
      abdevt += fabs(d);
      sum += d > 0.0 ? xt[j] : -xt[j];
   }
   free_vector(arr,1,ndatat);
   return sum;
}

/*---15.0---------------------------------------------------------------------*/
/*---15.1---------------------------------------------------------------------*/

void rk4(y,dydx,n,x,h,yout,derivs)
float y[],dydx[],x,h,yout[];
void (*derivs)();   /* ANSI: void (*derivs)(float,float *,float *); */
int n;
{
   int i;
   float xh,hh,h6,*dym,*dyt,*yt,*vector();
   void free_vector();

   dym=vector(1,n);
   dyt=vector(1,n);
   yt=vector(1,n);
   hh=h*0.5;
   h6=h/6.0;
   xh=x+hh;
   for (i=1;i<=n;i++) yt[i]=y[i]+hh*dydx[i];
   (*derivs)(xh,yt,dyt);
   for (i=1;i<=n;i++) yt[i]=y[i]+hh*dyt[i];
   (*derivs)(xh,yt,dym);
   for (i=1;i<=n;i++) {
      yt[i]=y[i]+h*dym[i];
      dym[i] += dyt[i];
   }
   (*derivs)(x+h,yt,dyt);
   for (i=1;i<=n;i++)
      yout[i]=y[i]+h6*(dydx[i]+dyt[i]+2.0*dym[i]);
   free_vector(yt,1,n);
   free_vector(dyt,1,n);
   free_vector(dym,1,n);
}

float **y=0,*xx=0;   /* defining declaration */

void rkdumb(vstart,nvar,x1,x2,nstep,derivs)
int nvar,nstep;
float vstart[],x1,x2;
void (*derivs)();   /* ANSI: void (*derivs)(float,float *,float *); */
{
   int i,k;
   float x,h;
   float *v,*vout,*dv,*vector();
   void rk4(),nrerror(),free_vector();

   v=vector(1,nvar);
   vout=vector(1,nvar);
   dv=vector(1,nvar);
   for (i=1;i<=nvar;i++) {
      v[i]=vstart[i];
      y[i][1]=v[i];
   }
   xx[1]=x1;
   x=x1;
   h=(x2-x1)/nstep;
   for (k=1;k<=nstep;k++) {
      (*derivs)(x,v,dv);
      rk4(v,dv,nvar,x,h,vout,derivs);
      if (x+h == x) nrerror("Step size too small in routine RKDUMB");
      x += h;
      xx[k+1]=x;
      for (i=1;i<=nvar;i++) {
         v[i]=vout[i];
         y[i][k+1]=v[i];
      }
   }
   free_vector(dv,1,nvar);
   free_vector(vout,1,nvar);
   free_vector(v,1,nvar);
}

/*---15.2---------------------------------------------------------------------*/

#define PGROW -0.20
#define PSHRNK -0.25
#define FCOR 0.06666666      /* 1.0/15.0 */
#define SAFETY 0.9
#define ERRCON 6.0e-4

void rkqc(y,dydx,n,x,htry,eps,yscal,hdid,hnext,derivs)
float y[],dydx[],*x,htry,eps,yscal[],*hdid,*hnext;
void (*derivs)();   /* ANSI: void (*derivs)(float,float *,float *); */
int n;
{
   int i;
   float xsav,hh,h,temp,errmax;
   float *dysav,*ysav,*ytemp,*vector();
   void rk4(),nrerror(),free_vector();

   dysav=vector(1,n);
   ysav=vector(1,n);
   ytemp=vector(1,n);
   xsav=(*x);
   for (i=1;i<=n;i++) {
      ysav[i]=y[i];
      dysav[i]=dydx[i];
   }
   h=htry;
   for (;;) {
      hh=0.5*h;
      rk4(ysav,dysav,n,xsav,hh,ytemp,derivs);
      *x=xsav+hh;
      (*derivs)(*x,ytemp,dydx);
      rk4(ytemp,dydx,n,*x,hh,y,derivs);
      *x=xsav+h;
      if (*x == xsav) nrerror("Step size too small in routine RKQC");
      rk4(ysav,dysav,n,xsav,h,ytemp,derivs);
      errmax=0.0;
      for (i=1;i<=n;i++) {
         ytemp[i]=y[i]-ytemp[i];
         temp=fabs(ytemp[i]/yscal[i]);
         if (errmax < temp) errmax=temp;
      }
      errmax /= eps;
      if (errmax <= 1.0) {
         *hdid=h;
         *hnext=(errmax > ERRCON ?
            SAFETY*h*exp(PGROW*log(errmax)) : 4.0*h);
         break;
      }
      h=SAFETY*h*exp(PSHRNK*log(errmax));
   }
   for (i=1;i<=n;i++) y[i] += ytemp[i]*FCOR;
   free_vector(ytemp,1,n);
   free_vector(dysav,1,n);
   free_vector(ysav,1,n);
}

#undef PGROW
#undef PSHRNK
#undef FCOR
#undef SAFETY
#undef ERRCON

#define MAXSTP 10000
#define TINY 1.0e-30

int kmax=0,kount=0;  /* defining declaration */
float *xp=0,**yp=0,dxsav=0;  /* defining declaration */

void odeint(ystart,nvar,x1,x2,eps,h1,hmin,nok,nbad,derivs,rkqc)
float ystart[],x1,x2,eps,h1,hmin;
int nvar,*nok,*nbad;
void (*derivs)();   /* ANSI: void (*derivs)(float,float *,float *); */
void (*rkqc)();    /* ANSI: void (*rkqc)(float *,float *,int,float *,float,
            float,float *,float *,float *,void (*)()); */
{
   int nstp,i;
   float xsav,x,hnext,hdid,h;
   float *yscal,*y,*dydx,*vector();
   void nrerror(),free_vector();

   yscal=vector(1,nvar);
   y=vector(1,nvar);
   dydx=vector(1,nvar);
   x=x1;
   h=(x2 > x1) ? fabs(h1) : -fabs(h1);
   *nok = (*nbad) = kount = 0;
   for (i=1;i<=nvar;i++) y[i]=ystart[i];
   if (kmax > 0) xsav=x-dxsav*2.0;
   for (nstp=1;nstp<=MAXSTP;nstp++) {
      (*derivs)(x,y,dydx);
      for (i=1;i<=nvar;i++)
         yscal[i]=fabs(y[i])+fabs(dydx[i]*h)+TINY;
      if (kmax > 0) {
         if (fabs(x-xsav) > fabs(dxsav)) {
            if (kount < kmax-1) {
               xp[++kount]=x;
               for (i=1;i<=nvar;i++) yp[i][kount]=y[i];
               xsav=x;
            }
         }
      }
      if ((x+h-x2)*(x+h-x1) > 0.0) h=x2-x;
      (*rkqc)(y,dydx,nvar,&x,h,eps,yscal,&hdid,&hnext,derivs);
      if (hdid == h) ++(*nok); else ++(*nbad);
      if ((x-x2)*(x2-x1) >= 0.0) {
         for (i=1;i<=nvar;i++) ystart[i]=y[i];
         if (kmax) {
            xp[++kount]=x;
            for (i=1;i<=nvar;i++) yp[i][kount]=y[i];
         }
         free_vector(dydx,1,nvar);
         free_vector(y,1,nvar);
         free_vector(yscal,1,nvar);
         return;
      }
      if (fabs(hnext) <= hmin) {
         nrerror("Step size too small in ODEINT");
         return; /* 20030803 Y.Kim */
      }
      h=hnext;
   }
   nrerror("Too many steps in routine ODEINT");
}

#undef MAXSTP
#undef TINY

/*---15.3---------------------------------------------------------------------*/

void mmid(y,dydx,nvar,xs,htot,nstep,yout,derivs)
float y[],dydx[],xs,htot,yout[];
void (*derivs)();   /* ANSI: void (*derivs)(float,float *,float *); */
int nvar,nstep;
{
   int n,i;
   float x,swap,h2,h,*ym,*yn,*vector();
   void free_vector();

   ym=vector(1,nvar);
   yn=vector(1,nvar);
   h=htot/nstep;
   for (i=1;i<=nvar;i++) {
      ym[i]=y[i];
      yn[i]=y[i]+h*dydx[i];
   }
   x=xs+h;
   (*derivs)(x,yn,yout);
   h2=2.0*h;
   for (n=2;n<=nstep;n++) {
      for (i=1;i<=nvar;i++) {
         swap=ym[i]+h2*yout[i];
         ym[i]=yn[i];
         yn[i]=swap;
      }
      x += h;
      (*derivs)(x,yn,yout);
   }
   for (i=1;i<=nvar;i++)
      yout[i]=0.5*(ym[i]+yn[i]+h*yout[i]);
   free_vector(yn,1,nvar);
   free_vector(ym,1,nvar);
}

/*---15.4---------------------------------------------------------------------*/

#define IMAX 11
#define NUSE 7
#define SHRINK 0.95
#define GROW 1.2

float **dOfBSSTEP=0,*xOfBSSTEP=0;   /* defining declaration !shik */

void bsstep(y,dydx,nv,xx,htry,eps,yscal,hdid,hnext,derivs)
float y[],dydx[],*xx,htry,eps,yscal[],*hdid,*hnext;
void (*derivs)();
int nv;
{
   int i,j;
   float xsav,xest,h,errmax,temp;
   float *ysav,*dysav,*yseq,*yerr,*vector(),**matrix();
   static int nseq[IMAX+1]={0,2,4,6,8,12,16,24,32,48,64,96};
   void mmid(),rzextr(),nrerror(),free_matrix(),free_vector();

   ysav=vector(1,nv);
   dysav=vector(1,nv);
   yseq=vector(1,nv);
   yerr=vector(1,nv);
   xOfBSSTEP=vector(1,IMAX);
   dOfBSSTEP=matrix(1,nv,1,NUSE);
   h=htry;
   xsav=(*xx);
   for (i=1;i<=nv;i++) {
      ysav[i]=y[i];
      dysav[i]=dydx[i];
   }
   for (;;) {
      for (i=1;i<=IMAX;i++) {
         mmid(ysav,dysav,nv,xsav,h,nseq[i],yseq,derivs);
         xest=(temp=h/nseq[i],temp*temp);
         rzextr(i,xest,yseq,y,yerr,nv,NUSE);
         errmax=0.0;
         for (j=1;j<=nv;j++)
            if (errmax < fabs(yerr[j]/yscal[j]))
               errmax=fabs(yerr[j]/yscal[j]);
         errmax /= eps;
         if (errmax < 1.0) {
            *xx += h;
            *hdid=h;
            *hnext = i==NUSE? h*SHRINK : i==NUSE-1?
               h*GROW : (h*nseq[NUSE-1])/nseq[i];
            free_matrix(dOfBSSTEP,1,nv,1,NUSE);
            free_vector(xOfBSSTEP,1,IMAX);
            free_vector(yerr,1,nv);
            free_vector(yseq,1,nv);
            free_vector(dysav,1,nv);
            free_vector(ysav,1,nv);
            return;
         }
      }
      h *= 0.25;
      for (i=1;i<=(IMAX-NUSE)/2;i++) h /= 2.0;
      if ((*xx+h) == (*xx)) nrerror("Step size underflow in BSSTEP");
   }
}

#undef IMAX
#undef NUSE
#undef SHRINK
#undef GROW

extern float **dOfBSSTEP,*xOfBSSTEP;   /* defined in BSSTEP !shik */

void rzextr(iest,xest,yest,yz,dy,nv,nuse)
int iest,nv,nuse;
float xest,yest[],yz[],dy[];
{
   int m1,k,j;
   float yy,v,ddy,c,b1,b,*fx,*vector();
   void free_vector();

   fx=vector(1,nuse);
   xOfBSSTEP[iest]=xest;
   if (iest == 1)
      for (j=1;j<=nv;j++) {
         yz[j]=yest[j];
         dOfBSSTEP[j][1]=yest[j];
         dy[j]=yest[j];
      }
   else {
      m1=(iest < nuse ? iest : nuse);
      for (k=1;k<=m1-1;k++)
         fx[k+1]=xOfBSSTEP[iest-k]/xest;
      for (j=1;j<=nv;j++) {
         yy=yest[j];
         v=dOfBSSTEP[j][1];
         c=yy;
         dOfBSSTEP[j][1]=yy;
         for (k=2;k<=m1;k++) {
            b1=fx[k]*v;
            b=b1-c;
            if (b) {
               b=(c-v)/b;
               ddy=c*b;
               c=b1*b;
            } else
               ddy=v;
            if (k != m1) v=dOfBSSTEP[j][k];
            dOfBSSTEP[j][k]=ddy;
            yy += ddy;
         }
         dy[j]=ddy;
         yz[j]=yy;
      }
   }
   free_vector(fx,1,nuse);
}

extern float **dOfBSSTEP,*xOfBSSTEP;   /* defined in BSSTEP !shik */

void pzextr(iest,xest,yest,yz,dy,nv,nuse)
int iest,nv,nuse;
float xest,yest[],yz[],dy[];
{
   int m1,k1,j;
   float q,f2,f1,delta,*c,*vector();
   void free_vector();

   c=vector(1,nv);
   xOfBSSTEP[iest]=xest;
   for (j=1;j<=nv;j++) dy[j]=yz[j]=yest[j];
   if (iest == 1) {
      for (j=1;j<=nv;j++)
         dOfBSSTEP[j][1]=yest[j];
   } else {
      m1=(iest < nuse ? iest : nuse);
      for (j=1;j<=nv;j++) c[j]=yest[j];
      for (k1=1;k1<=m1-1;k1++) {
         delta=1.0/(xOfBSSTEP[iest-k1]-xest);
         f1=xest*delta;
         f2=xOfBSSTEP[iest-k1]*delta;
         for (j=1;j<=nv;j++) {
            q=dOfBSSTEP[j][k1];
            dOfBSSTEP[j][k1]=dy[j];
            delta=c[j]-q;
            dy[j]=f1*delta;
            c[j]=f2*delta;
            yz[j] += dy[j];
         }
      }
      for (j=1;j<=nv;j++) dOfBSSTEP[j][m1]=dy[j];
   }
   free_vector(c,1,nv);
}

/*---15.5---------------------------------------------------------------------*/
/*---15.6---------------------------------------------------------------------*/
/*---16.0---------------------------------------------------------------------*/
/*---16.1---------------------------------------------------------------------*/
//20031123 #ifdef EXTRACOMPLIATION

void shoot(nvar,v,delv,n2,x1,x2,eps,h1,hmin,f,dv,load,score,derivs)
int nvar,n2;
float v[],delv[],x1,x2,eps,h1,hmin,f[],dv[];
void (*load)(double,double*,double*),
     (*score)(double,double*,double*),
     (*derivs)(double,double*,double*); //20031124
{
   int nok,nbad,iv,i,*indx,*ivector();
   float sav,det,*y,**dfdv,**matrix(),*vector();
   void odeint(),ludcmp(),lubksb(),rkqc(),
      free_matrix(),free_vector(),free_ivector();
   //void derivs();
   //void load();   /* ANSI: void load(float,float *,float *); */
   //void score();   /* ANSI: void score(float,float *,float *); */

   y=vector(1,nvar);
   indx=ivector(1,nvar);
   dfdv=matrix(1,n2,1,n2);
   (*load)(x1,v,y);//load(x1,v,y);
   odeint(y,nvar,x1,x2,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
   (*score)(x2,y,f);//score(x2,y,f);
   for (iv=1;iv<=n2;iv++) {
      sav=v[iv];
      v[iv] += delv[iv];
      (*load)(x1,v,y);//load(x1,v,y);
      odeint(y,nvar,x1,x2,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
      (*score)(x2,y,dv);//score(x2,y,dv);
      for (i=1;i<=n2;i++)
         dfdv[i][iv]=(dv[i]-f[i])/delv[iv];
      v[iv]=sav;
   }
   for (iv=1;iv<=n2;iv++) dv[iv] = -f[iv];
   ludcmp(dfdv,n2,indx,&det);
   lubksb(dfdv,n2,indx,dv);
   for (iv=1;iv<=n2;iv++) v[iv] += dv[iv];
   free_matrix(dfdv,1,n2,1,n2);
   free_ivector(indx,1,nvar);
   free_vector(y,1,nvar);
}

//20031123 #endif
/*---16.2---------------------------------------------------------------------*/
#ifdef EXTRACOMPLIATION

void shootf(nvar,v1,v2,delv1,delv2,n1,n2,x1,x2,xf,eps,h1,hmin,f,dv1,dv2)
int nvar,n1,n2;
float v1[],v2[],delv1[],delv2[],x1,x2,xf,eps,h1,hmin,f[],dv1[],dv2[];
{
   int nok,nbad,j,iv,i,*indx,*ivector();
   void odeint(),ludcmp(),lubksb(),derivs(),
      rkqc(),free_matrix(),free_vector(),free_ivector();
   void load1();   /* ANSI: void load1(float,float *,float *); */
   void load2();   /* ANSI: void load2(float,float *,float *); */
   void score();   /* ANSI: void score(float,float *,float *); */
   float sav,det,*y,*f1,*f2,**dfdv,**matrix(),*vector();

   dfdv=matrix(1,nvar,1,nvar);
   y=vector(1,nvar);
   f1=vector(1,nvar);
   f2=vector(1,nvar);
   indx=ivector(1,nvar);
   load1(x1,v1,y);
   odeint(y,nvar,x1,xf,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
   score(xf,y,f1);
   load2(x2,v2,y);
   odeint(y,nvar,x2,xf,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
   score(xf,y,f2);
   j=0;
   for (iv=1;iv<=n2;iv++) {
      j++;
      sav=v1[iv];
      v1[iv] += delv1[iv];
      load1(x1,v1,y);
      odeint(y,nvar,x1,xf,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
      score(xf,y,f);
      for (i=1;i<=nvar;i++)
         dfdv[i][j]=(f[i]-f1[i])/delv1[iv];
      v1[iv]=sav;
   }
   for (iv=1;iv<=n1;iv++) {
      j++;
      sav=v2[iv];
      v2[iv] += delv2[iv];
      load2(x2,v2,y);
      odeint(y,nvar,x2,xf,eps,h1,hmin,&nok,&nbad,derivs,rkqc);
      score(xf,y,f);
      for (i=1;i<=nvar;i++)
         dfdv[i][j]=(f2[i]-f[i])/delv2[iv];
      v2[iv]=sav;
   }
   for (i=1;i<=nvar;i++) {
      f[i]=f1[i]-f2[i];
      f1[i]=(-f[i]);
   }
   ludcmp(dfdv,nvar,indx,&det);
   lubksb(dfdv,nvar,indx,f1);
   j=0;
   for (iv=1;iv<=n2;iv++) {
      v1[iv] += f1[++j];
      dv1[iv]=f1[j];
   }
   for (iv=1;iv<=n1;iv++) {
      v2[iv] += f1[++j];
      dv2[iv]=f1[j];
   }
   free_ivector(indx,1,nvar);
   free_vector(f2,1,nvar);
   free_vector(f1,1,nvar);
   free_vector(y,1,nvar);
   free_matrix(dfdv,1,nvar,1,nvar);
}

#endif
/*---16.3---------------------------------------------------------------------*/

void solvde(itmax,conv,slowc,scalv,indexv,ne,nb,m,y,c,s)
int itmax,ne,nb,m;
float conv,slowc,scalv[],**y,***c,**s;
int indexv[];
{
   int ic1,ic2,ic3,ic4,it,j,j1,j2,j3,j4,j5,j6,j7,j8,j9;
   int jc1,jcf,jv,k,k1,k2,km,kp,nvars,*kmax,*ivector();
   float err,errj,fac,vmax,vz,*ermax,*vector();
   void pinvs(),difeq(),red(),bksub(),nrerror(),free_vector(),
      free_ivector();

   kmax=ivector(1,ne);
   ermax=vector(1,ne);
   k1=1;
   k2=m;
   nvars=ne*m;
   j1=1;
   j2=nb;
   j3=nb+1;
   j4=ne;
   j5=j4+j1;
   j6=j4+j2;
   j7=j4+j3;
   j8=j4+j4;
   j9=j8+j1;
   ic1=1;
   ic2=ne-nb;
   ic3=ic2+1;
   ic4=ne;
   jc1=1;
   jcf=ic3;
   for (it=1;it<=itmax;it++) {
      k=k1;
      difeq(k,k1,k2,j9,ic3,ic4,indexv,ne,s,y);
      pinvs(ic3,ic4,j5,j9,jc1,k1,c,s);
      for (k=k1+1;k<=k2;k++) {
         kp=k-1;
         difeq(k,k1,k2,j9,ic1,ic4,indexv,ne,s,y);
         red(ic1,ic4,j1,j2,j3,j4,j9,ic3,jc1,jcf,kp,c,s);
         pinvs(ic1,ic4,j3,j9,jc1,k,c,s);
      }
      k=k2+1;
      difeq(k,k1,k2,j9,ic1,ic2,indexv,ne,s,y);
      red(ic1,ic2,j5,j6,j7,j8,j9,ic3,jc1,jcf,k2,c,s);
      pinvs(ic1,ic2,j7,j9,jcf,k2+1,c,s);
      bksub(ne,nb,jcf,k1,k2,c);
      err=0.0;
      for (j=1;j<=ne;j++) {
         jv=indexv[j];
         errj=vmax=0.0;
         km=0;
         for (k=k1;k<=k2;k++) {
            vz=fabs(c[j][1][k]);
            if (vz > vmax) {
                vmax=vz;
                km=k;
            }
            errj += vz;
         }
         err += errj/scalv[jv];
         ermax[j]=c[j][1][km]/scalv[jv];
         kmax[j]=km;
      }
      err /= nvars;
      fac=(err > slowc ? slowc/err : 1.0);
      for (jv=1;jv<=ne;jv++) {
         j=indexv[jv];
         for (k=k1;k<=k2;k++)
            y[j][k] -= fac*c[jv][1][k];
      }
      printf("\n%8s %9s %9s\n","Iter.","Error","FAC");
      printf("%6d %12.6f %11.6f\n",it,err,fac);
      printf("%8s %8s %14s\n","Var.","Kmax","Max. Error");
      for (j=1;j<=ne;j++)
         printf("%6d %9d %14.6f \n",indexv[j],kmax[j],ermax[j]);
      if (err < conv) {
         free_vector(ermax,1,ne);
         free_ivector(kmax,1,ne);
         return;
      }
   }
   nrerror("Too many iterations in SOLVDE");
}

void bksub(ne,nb,jf,k1,k2,c)
int ne,nb,jf,k1,k2;
float ***c;
{
   int nbf,im,kp,k,j,i;
   float xx;

   nbf=ne-nb;
   im=1;
   for (k=k2;k>=k1;k--) {
      if (k == k1) im=nbf+1;
      kp=k+1;
      for (j=1;j<=nbf;j++) {
         xx=c[j][jf][kp];
         for (i=im;i<=ne;i++)
            c[i][jf][k] -= c[i][j][k]*xx;
      }
   }
   for (k=k1;k<=k2;k++) {
      kp=k+1;
      for (i=1;i<=nb;i++) c[i][1][k]=c[i+nbf][jf][k];
      for (i=1;i<=nbf;i++) c[i+nb][1][k]=c[i][jf][kp];
   }
}

void pinvs(ie1,ie2,je1,jsf,jc1,k,c,s)
int ie1,ie2,je1,jsf,jc1,k;
float ***c,**s;
{
   int js1,jpiv,jp,je2,jcoff,j,irow,ipiv,id,icoff,i,*indxr,*ivector();
   float pivinv,piv,dum,big,*pscl,*vector();
   void nrerror(),free_vector(),free_ivector();

   indxr=ivector(ie1,ie2);
   pscl=vector(ie1,ie2);
   je2=je1+ie2-ie1;
   js1=je2+1;
   for (i=ie1;i<=ie2;i++) {
      big=0.0;
      for (j=je1;j<=je2;j++)
         if (fabs(s[i][j]) > big) big=fabs(s[i][j]);
      if (big == 0.0) nrerror("Singular matrix - row all 0, in PINVS");
      pscl[i]=1.0/big;
      indxr[i]=0;
   }
   for (id=ie1;id<=ie2;id++) {
      piv=0.0;
      for (i=ie1;i<=ie2;i++) {
         if (indxr[i] == 0) {
            big=0.0;
            for (j=je1;j<=je2;j++) {
               if (fabs(s[i][j]) > big) {
                  jp=j;
                  big=fabs(s[i][j]);
               }
            }
            if (big*pscl[i] > piv) {
               ipiv=i;
               jpiv=jp;
               piv=big*pscl[i];
            }
         }
      }
      if (s[ipiv][jpiv] == 0.0) nrerror("Singular matrix in routine PINVS");
      indxr[ipiv]=jpiv;
      pivinv=1.0/s[ipiv][jpiv];
      for (j=je1;j<=jsf;j++) s[ipiv][j] *= pivinv;
      s[ipiv][jpiv]=1.0;
      for (i=ie1;i<=ie2;i++) {
         if (indxr[i] != jpiv) {
            if (s[i][jpiv]) {
               dum=s[i][jpiv];
               for (j=je1;j<=jsf;j++)
                  s[i][j] -= dum*s[ipiv][j];
               s[i][jpiv]=0.0;
            }
         }
      }
   }
   jcoff=jc1-js1;
   icoff=ie1-je1;
   for (i=ie1;i<=ie2;i++) {
      irow=indxr[i]+icoff;
      for (j=js1;j<=jsf;j++) c[irow][j+jcoff][k]=s[i][j];
   }
   free_vector(pscl,ie1,ie2);
   free_ivector(indxr,ie1,ie2);
}

void red(iz1,iz2,jz1,jz2,jm1,jm2,jmf,ic1,jc1,jcf,kc,c,s)
float ***c,**s;
int iz1,iz2,jz1,jz2,jm1,jm2,jmf,ic1,jc1,jcf,kc;
{
   int loff,l,j,ic,i;
   float vx;

   loff=jc1-jm1;
   ic=ic1;
   for (j=jz1;j<=jz2;j++) {
      for (l=jm1;l<=jm2;l++) {
         vx=c[ic][l+loff][kc];
         for (i=iz1;i<=iz2;i++) s[i][l] -= s[i][j]*vx;
      }
      vx=c[ic][jcf][kc];
      for (i=iz1;i<=iz2;i++) s[i][jmf] -= s[i][j]*vx;
      ic += 1;
   }
}

/*---16.4---------------------------------------------------------------------*/

#define NE 3
#define M 41
#define NB 1
#define NSI NE
#define NYJ NE
#define NYK M
#define NCI NE
#define NCJ (NE-NB+1)
#define NCK (M+1)
#define NSJ (2*NE+1)

int mm=0,n=0,mpt=M;  /* defining declaration */
float h=0.0,c2=0.0,anorm=0.0,x[M+1];      /* defining declaration */
/* Program SFROID */
#undef NE
#undef M
#undef NB
#undef NSI
#undef NYJ
#undef NYK
#undef NCI
#undef NCJ
#undef NCK
#undef NSJ

extern int mm,n,mpt;   /* defined in SFROID */
extern float h,c2,anorm,x[];

void difeq(k,k1,k2,jsf,is1,isf,indexv,ne,s,y)
int k,k1,k2,jsf,is1,isf,indexv[],ne;
float **s,**y;
{
   float temp,temp1,temp2;

   if (k == k1) {
      if ((n+mm) % 2 == 1) {
         s[3][3+indexv[1]]=1.0;
         s[3][3+indexv[2]]=0.0;
         s[3][3+indexv[3]]=0.0;
         s[3][jsf]=y[1][1];
      } else {
         s[3][3+indexv[1]]=0.0;
         s[3][3+indexv[2]]=1.0;
         s[3][3+indexv[3]]=0.0;
         s[3][jsf]=y[2][1];
      }
   } else if (k > k2) {
      s[1][3+indexv[1]] = -(y[3][mpt]-c2)/(2.0*(mm+1.0));
      s[1][3+indexv[2]]=1.0;
      s[1][3+indexv[3]] = -y[1][mpt]/(2.0*(mm+1.0));
      s[1][jsf]=y[2][mpt]-(y[3][mpt]-c2)*y[1][mpt]/(2.0*(mm+1.0));
      s[2][3+indexv[1]]=1.0;
      s[2][3+indexv[2]]=0.0;
      s[2][3+indexv[3]]=0.0;
      s[2][jsf]=y[1][mpt]-anorm;
   } else {
      s[1][indexv[1]] = -1.0;
      s[1][indexv[2]] = -0.5*h;
      s[1][indexv[3]]=0.0;
      s[1][3+indexv[1]]=1.0;
      s[1][3+indexv[2]] = -0.5*h;
      s[1][3+indexv[3]]=0.0;
      temp1=x[k]+x[k-1];
      temp=h/(1.0-temp1*temp1*0.25);
      temp2=0.5*(y[3][k]+y[3][k-1])-c2*0.25*temp1*temp1;
      s[2][indexv[1]]=temp*temp2*0.5;
      s[2][indexv[2]] = -1.0-0.5*temp*(mm+1.0)*temp1;
      s[2][indexv[3]]=0.25*temp*(y[1][k]+y[1][k-1]);
      s[2][3+indexv[1]]=s[2][indexv[1]];
      s[2][3+indexv[2]]=2.0+s[2][indexv[2]];
      s[2][3+indexv[3]]=s[2][indexv[3]];
      s[3][indexv[1]]=0.0;
      s[3][indexv[2]]=0.0;
      s[3][indexv[3]] = -1.0;
      s[3][3+indexv[1]]=0.0;
      s[3][3+indexv[2]]=0.0;
      s[3][3+indexv[3]]=1.0;
      s[1][jsf]=y[1][k]-y[1][k-1]-0.5*h*(y[2][k]+y[2][k-1]);
      s[2][jsf]=y[2][k]-y[2][k-1]-temp*((x[k]+x[k-1])
         *0.5*(mm+1.0)*(y[2][k]+y[2][k-1])-temp2
         *0.5*(y[1][k]+y[1][k-1]));
      s[3][jsf]=y[3][k]-y[3][k-1];
   }
}

/*---16.5---------------------------------------------------------------------*/
/*---16.6---------------------------------------------------------------------*/
/*---17.0---------------------------------------------------------------------*/
/*---17.1---------------------------------------------------------------------*/
/*---17.2---------------------------------------------------------------------*/
/*---17.3---------------------------------------------------------------------*/
/*---17.4---------------------------------------------------------------------*/
/*---17.5---------------------------------------------------------------------*/

#define MAXITS 1000
#define EPS 1.e-5

void sor(a,b,c,d,e,f,u,jmax,rjac)
double **a,**b,**c,**d,**e,**f,**u,rjac;
int jmax;
{
   int n,l,j;
   double resid,omega,anormf,anorm;
   void nrerror();

   anormf=0.0;
   for (j=2;j<jmax;j++)
      for (l=2;l<jmax;l++)
         anormf += fabs(f[j][l]);
   omega=1.0;
   for (n=1;n<=MAXITS;n++) {
      anorm=0.0;
      for (j=2;j<jmax;j++)
         for (l=2;l<jmax;l++)
            if ((j+l)%2 == n%2) {
               resid=a[j][l]*u[j+1][l]
                  +b[j][l]*u[j-1][l]
                  +c[j][l]*u[j][l+1];
               resid += d[j][l]*u[j][l-1]
                  +e[j][l]*u[j][l]-f[j][l];
               anorm += fabs(resid);
               u[j][l] -= omega*resid/e[j][l];
            }
      omega=(n == 1 ? 1.0/(1.0-0.5*rjac*rjac) :
         1.0/(1.0-0.25*rjac*rjac*omega));
      if (n > 1 && anorm < EPS*anormf) return;
   }
   nrerror("Maximum number of iterations exceeded in SOR");
}

#undef MAXITS
#undef EPS

/*---17.6---------------------------------------------------------------------*/
#define JJ 50
#define KK 6
#define NRR 32  /* NRR=2 to the power (KK-1) */
#define MAXITS 100

void adi(a,b,c,d,e,f,g,u,jmax,k,alpha,beta,eps)
double **a,**b,**c,**d,**e,**f,**g,**u,alpha,beta,eps;
int jmax,k;
{
   int i,nr,nits,next,n,l,kits,k1,j,twopwr;
   double **psi,rfact,resid,disc,anormg,anorm,ab;
   double *aa,*bb,*cc,*rr,*uu,**s,*r,*alph,*bet;
   double **dmatrix(),*dvector();
   void free_dmatrix(),free_dvector(),nrerror(),tridag();

   if (jmax > JJ) nrerror("in ADI, increase JJ");
   if (k > KK-1)  nrerror("in ADI, increase KK");
   psi=dmatrix(1,JJ,1,JJ);
   s=dmatrix(1,NRR,1,KK);
   aa=dvector(1,JJ);
   bb=dvector(1,JJ);
   cc=dvector(1,JJ);
   rr=dvector(1,JJ);
   uu=dvector(1,JJ);
   r=dvector(1,NRR);
   alph=dvector(1,KK);
   bet=dvector(1,KK);
   k1=k+1;
   nr=1;
   for (i=1;i<=k;i++) nr *= 2;
   alph[1]=alpha;
   bet[1]=beta;
   for (j=1;j<=k;j++) {
      alph[j+1]=sqrt(alph[j]*bet[j]);
      bet[j+1]=0.5*(alph[j]+bet[j]);
   }
   s[1][1]=sqrt(alph[k1]*bet[k1]);
   for (j=1;j<=k;j++) {
      ab=alph[k1-j]*bet[k1-j];
      twopwr=1;
      for (i=1;i<=(j-1);i++) twopwr *= 2;
      for (n=1;n<=twopwr;n++) {
         disc=sqrt(s[n][j]*s[n][j]-ab);
         s[2*n][j+1]=s[n][j]+disc;
         s[2*n-1][j+1]=ab/s[2*n][j+1];
      }
   }
   for (n=1;n<=nr;n++) r[n]=s[n][k1];
   anormg=0.0;
   for (j=2;j<=jmax-1;j++) {
      for (l=2;l<=jmax-1;l++) {
         anormg += fabs(g[j][l]);
         psi[j][l] = -d[j][l]*u[j][l-1]
            +(r[1]-e[j][l])*u[j][l]-f[j][l]*u[j][l+1];
      }
   }
   nits=MAXITS/nr;
   for (kits=1;kits<=nits;kits++) {
      for (n=1;n<=nr;n++) {
         next = n == nr ? 1 : n+1;
         rfact=r[n]+r[next];
         for (l=2;l<=jmax-1;l++) {
            for (j=2;j<=jmax-1;j++) {
               aa[j-1]=a[j][l];
               bb[j-1]=b[j][l]+r[n];
               cc[j-1]=c[j][l];
               rr[j-1]=psi[j][l]-g[j][l];
            }
            tridag(aa,bb,cc,rr,uu,jmax-2);
            for (j=2;j<=jmax-1;j++)
               psi[j][l] = -psi[j][l]
                  +2.0*r[n]*uu[j-1];
         }
         for (j=2;j<=jmax-1;j++) {
            for (l=2;l<=jmax-1;l++) {
               aa[l-1]=d[j][l];
               bb[l-1]=e[j][l]+r[n];
               cc[l-1]=f[j][l];
               rr[l-1]=psi[j][l];
            }
            tridag(aa,bb,cc,rr,uu,jmax-2);
            for (l=2;l<=jmax-1;l++) {
               u[j][l]=uu[l-1];
               psi[j][l] = -psi[j][l]+rfact*uu[l-1];
            }
         }
      }
      anorm=0.0;
      for (j=2;j<=jmax-1;j++)
         for (l=2;l<=jmax-1;l++) {
            resid=a[j][l]*u[j-1][l]
               +(b[j][l]+e[j][l])*u[j][l];
            resid += c[j][l]*u[j+1][l]+d[j][l]*u[j][l-1]
               +f[j][l]*u[j][l+1]+g[j][l];
            anorm += fabs(resid);
         }
      if (anorm < (eps*anormg)) {
         free_dvector(bet,1,KK);
         free_dvector(alph,1,KK);
         free_dvector(r,1,NRR);
         free_dvector(uu,1,JJ);
         free_dvector(rr,1,JJ);
         free_dvector(cc,1,JJ);
         free_dvector(bb,1,JJ);
         free_dvector(aa,1,JJ);
         free_dmatrix(s,1,NRR,1,KK);
         free_dmatrix(psi,1,JJ,1,JJ);
         return;
      }
   }
   nrerror("in ADI, too many iterations");
}

/* Double precision version of TRIDAG */
void tridag(a,b,c,r,u,n)
double *a,*b,*c,*r,*u;
int n;
{
   int j;
   double bet,*gam,*dvector();
   void nrerror(),free_dvector();

   gam=dvector(1,n);
   if (b[1] == 0.0) nrerror("error 1 in TRIDAG");
   bet=b[1];
   u[1]=r[1]/bet;
   for (j=2;j<=n;j++) {
      gam[j]=c[j-1]/bet;
      bet=b[j]-a[j]*gam[j];
      if (bet == 0.0) nrerror("error 2 in TRIDAG");
      u[j]=(r[j]-a[j]*u[j-1])/bet;
   }
   for (j=n-1;j>=1;j--)
      u[j] -= gam[j+1]*u[j+1];
   free_dvector(gam,1,n);
}

#undef JJ
#undef KK
#undef NRR
#undef MAXITS

/*---Appendix D---------------------------------------------------------------*/

static char qLastErrorMessage[512];

void nrerror( pError )
char pError[];
{
   /*
   fprintf(stderr,"Numerical Recipes run-time error...\n");
   fprintf(stderr,"%s\n",pError);
   fprintf(stderr,"...now exiting to system...\n");
   exit(1);
   */
   sprintf(qLastErrorMessage,"Numerical Recipes run-time error:%s",pError);
}

const char *GetLastErrorMessageInNr()
{
   return qLastErrorMessage;
}

float *vector(nl,nh)
int nl,nh;
{
   float *v;

   v=(float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
   if (!v) nrerror("allocation failure in vector()");
   return v-nl;
}

int *ivector(nl,nh)
int nl,nh;
{
   int *v;

   v=(int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
   if (!v) nrerror("allocation failure in ivector()");
   return v-nl;
}

double *dvector(nl,nh)
int nl,nh;
{
   double *v;

   v=(double *)malloc((unsigned) (nh-nl+1)*sizeof(double));
   if (!v) nrerror("allocation failure in dvector()");
   return v-nl;
}

float **matrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
{
   int i;
   float **m;

   m=(float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
   if (!m) nrerror("allocation failure 1 in matrix()");
   m -= nrl;

   for(i=nrl;i<=nrh;i++) {
      m[i]=(float *) malloc((unsigned) (nch-ncl+1)*sizeof(float));
      if (!m[i]) nrerror("allocation failure 2 in matrix()");
      m[i] -= ncl;
   }
   return m;
}

double **dmatrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
{
   int i;
   double **m;

   m=(double **) malloc((unsigned) (nrh-nrl+1)*sizeof(double*));
   if (!m) nrerror("allocation failure 1 in dmatrix()");
   m -= nrl;

   for(i=nrl;i<=nrh;i++) {
      m[i]=(double *) malloc((unsigned) (nch-ncl+1)*sizeof(double));
      if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
      m[i] -= ncl;
   }
   return m;
}

int **imatrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
{
   int i,**m;

   m=(int **)malloc((unsigned) (nrh-nrl+1)*sizeof(int*));
   if (!m) nrerror("allocation failure 1 in imatrix()");
   m -= nrl;

   for(i=nrl;i<=nrh;i++) {
      m[i]=(int *)malloc((unsigned) (nch-ncl+1)*sizeof(int));
      if (!m[i]) nrerror("allocation failure 2 in imatrix()");
      m[i] -= ncl;
   }
   return m;
}

float **submatrix(a,oldrl,oldrh,oldcl,oldch,newrl,newcl)
float **a;
int oldrl,oldrh,oldcl,oldch,newrl,newcl;
{
   int i,j;
   float **m;

   m=(float **) malloc((unsigned) (oldrh-oldrl+1)*sizeof(float*));
   if (!m) nrerror("allocation failure in submatrix()");
   m -= newrl;

   for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+oldcl-newcl;

   return m;
}

void free_vector(v,nl,nh)
float *v;
int nl,nh;
{
   free((char*) (v+nl));
}

void free_ivector(v,nl,nh)
int *v,nl,nh;
{
   free((char*) (v+nl));
}

void free_dvector(v,nl,nh)
double *v;
int nl,nh;
{
   free((char*) (v+nl));
}

void free_matrix(m,nrl,nrh,ncl,nch)
float **m;
int nrl,nrh,ncl,nch;
{
   int i;

   for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
   free((char*) (m+nrl));
}

void free_dmatrix(m,nrl,nrh,ncl,nch)
double **m;
int nrl,nrh,ncl,nch;
{
   int i;

   for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
   free((char*) (m+nrl));
}

void free_imatrix(m,nrl,nrh,ncl,nch)
int **m;
int nrl,nrh,ncl,nch;
{
   int i;

   for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
   free((char*) (m+nrl));
}

void free_submatrix(b,nrl,nrh,ncl,nch)
float **b;
int nrl,nrh,ncl,nch;
{
   free((char*) (b+nrl));
}

float **convert_matrix(a,nrl,nrh,ncl,nch)
float *a;
int nrl,nrh,ncl,nch;
{
   int i,j,nrow,ncol;
   float **m;

   nrow=nrh-nrl+1;
   ncol=nch-ncl+1;
   m = (float **) malloc((unsigned) (nrow)*sizeof(float*));
   if (!m) nrerror("allocation failure in convert_matrix()");
   m -= nrl;
   for(i=0,j=nrl;i<=nrow-1;i++,j++) m[j]=a+ncol*i-ncl;
   return m;
}

void free_convert_matrix(b,nrl,nrh,ncl,nch)
float **b;
int nrl,nrh,ncl,nch;
{
   free((char*) (b+nrl));
}

/*---Appendix E---------------------------------------------------------------*/

/* typedef struct FCOMPLEX {float r,i;} fcomplex; !shik */

fcomplex Cadd(a,b)
fcomplex a,b;
{   fcomplex c;
   c.r=a.r+b.r;
   c.i=a.i+b.i;
   return c;
}

fcomplex Csub(a,b)
fcomplex a,b;
{   fcomplex c;
   c.r=a.r-b.r;
   c.i=a.i-b.i;
   return c;
}

fcomplex Cmul(a,b)
fcomplex a,b;
{   fcomplex c;
   c.r=a.r*b.r-a.i*b.i;
   c.i=a.i*b.r+a.r*b.i;
   return c;
}

fcomplex Complex(re,im)
float re,im;
{   fcomplex c;
   c.r=re;
   c.i=im;
   return c;
}

fcomplex Conjg(z)
fcomplex z;
{   fcomplex c;
   c.r=z.r;
   c.i = -z.i;
   return c;
}

fcomplex Cdiv(a,b)
fcomplex a,b;
{   fcomplex c;
   float r,den;
   if (fabs(b.r) >= fabs(b.i)) {
      r=b.i/b.r;
      den=b.r+r*b.i;
      c.r=(a.r+r*a.i)/den;
      c.i=(a.i-r*a.r)/den;
   } else {
      r=b.r/b.i;
      den=b.i+r*b.r;
      c.r=(a.r*r+a.i)/den;
      c.i=(a.i*r-a.r)/den;
   }
   return c;
}

float Cabs(z)
fcomplex z;
{   float x,y,ans,temp;
   x=fabs(z.r);
   y=fabs(z.i);
   if (x == 0.0)
      ans=y;
   else if (y == 0.0)
      ans=x;
   else if (x > y) {
      temp=y/x;
      ans=x*sqrt(1.0+temp*temp);
   } else {
      temp=x/y;
      ans=y*sqrt(1.0+temp*temp);
   }
   return ans;
}

fcomplex Csqrt(z)
fcomplex z;
{   fcomplex c;
   float x,y,w,r;
   if ((z.r == 0.0) && (z.i == 0.0)) {
      c.r=0.0;
      c.i=0.0;
      return c;
   } else {
      x=fabs(z.r);
      y=fabs(z.i);
      if (x >= y) {
         r=y/x;
         w=sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
      } else {
         r=x/y;
         w=sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
      }
      if (z.r >= 0.0) {
         c.r=w;
         c.i=z.i/(2.0*w);
      } else {
         c.i=(z.i >= 0) ? w : -w;
         c.r=z.i/(2.0*c.i);
      }
      return c;
   }
}

fcomplex RCmul(x,a)
float x;
fcomplex a;
{   fcomplex c;
   c.r=x*a.r;
   c.i=x*a.i;
   return c;
}

/*----------------------------------------------------------------------------*/
/* end ! 43261120(c)shik */

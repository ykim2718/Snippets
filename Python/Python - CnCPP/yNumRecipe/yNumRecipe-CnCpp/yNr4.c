/******************************************************************************

       File: yNr4.c
Description: 1980,DiDonato,Computation of the Integral of ++ (FORTRAN).f95
    Creator: A. R. Didonato, R. K Hageman
     Source: "Computation of the integral of the bivariate normal distribution
             over arbitrary polygons", June 1980, Naval Surface Weapons Center
       Date: June 1980
   Revision: Kim, Yongshik (copyRight)
     Update: 2016.1.13, 0403

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "yNumber.h"
#include "yNrecipe.h"
#include "yNr.h"
#include "yNr4.h"


#define DEBUG_PRINT_ON 1
#undef  BEBUG_PRINT_ON

// 1980,DiDonato,Computation of the Integral of ++ (FORTRAN).f95

static int P2( double *vX, double *vY, int vSize, int ICV, int IOP,
    double *Prob, double *Area, int *IND, int *KO );
static int SORT3( double *vX, double *vY, int vSize );
static int VALR2( double *vX, double *vY, int vSize, int IOP,
    double *Prob, double *Area, int *IND, int *KO );
static int VALR7( double *vX, double *vY, int vSize, int IOP,
    double *Prob, double *Area, int *IND );
static double SMP7 (double *X, double *Y, int NB);

/* 2016.3.31 */
double yZscore1d( double x, UVNParameter *n )
{
	return (x - n->mean) / n->stdev;
}

/* 2016.3.31 - 4.2 */
double *yZscore2d( double x, double y, BVNParameter *n )
{
	static double r[2];

    if (ABS(n->r)>0.999999999999) {
        r[0]=0.;
    } else {
        r[0] = ((x - n->m_x) / n->s_x - n->r*(y - n->m_y) / n->s_y)
        		/ sqrt(1 - SQUARE(n->r));
	}
	r[1] = (y - n->m_y) / n->s_y;

    printf("[yZscore2d] x=%lf, y=%lf\n",x,y);
    printf("[yZscore2d] n, m_x=%lf, s_x=%lf, m_y=%lf, s_y=%lf, r=%lf\n",
           n->m_x,n->s_x,n->m_y,n->s_y,n->r);
    printf("[yZscore2d] z[0]=%lf z[1]=%lf\n",r[0],r[1]);

	return r; /* r[0]=x, r[1]=y */
}

double yBVNCDFOCP(
    double *vXB0, double *vYB0, int vSize, BVNParameter *n,
    double *Area
    )
{
    double *r;

    for (int i=0;i<vSize;i++) {
        r=yZscore2d(vXB0[i],vYB0[i],n);
        vXB0[i]=r[0];
        vYB0[i]=r[1];
    }

    return yBVSNCDFOCP(vXB0,vYB0,vSize,Area);
}

/*
! Bivariate Normal Distribution CDF over Convex Polygon
! Yongshik Kim (copyRight) 2016.1.13 - 1.16
! Wrapper of subroutine P2()
! Page 1, General bivariate density function,
!           mean vector (m_w,m_z)
!           covariance matrix ((s_w^2,r*s_w*s_z),(r*s_z*s_w,s_z^2))
!         Linear transformation for circular symmetry about the origin
!           x=((w-m_w)/s_w-r*(z-m_z)s_z)/sqrt(1-r^2)
!           y=(z-m_z)/s_z
!           |r|<1
! Page 1, We specify a polygon by N+1 points, where the (N+1)st and first points
!         are the same.
*/
double yBVSNCDFOCP( double *vXB0, double *vYB0, int vSize, double *Area )
{

   double P;  // Value of P(II)
   double A;  // Area of II
   int ICV=0; // Simple polygon (N>1), calling VALR7, p.40
   int IOP=3; // 9 decimal digits of accuracy in P(II)
   int IND;   // Error indicator
   int KO;    // Winding number of II, only computed if ICV > 0 or ICV < 0, <>-2

   double *vXB1=vXB0-1;
   double *vYB1=vYB0-1;

   P2(vXB1,vYB1,vSize,ICV,IOP,&P,&A,&IND,&KO);
   *Area=A;
   return P;
}

void demo_Fig_33_on_page_52()
// Referring to the table on page 48
// Expectation: ICV=1,-1 P=0.941625 A=20.50 S_bar N=18
// Results: p=0.941624880 A=20.5
{

   double x [] = {
      -3.0, 0.0, 4.0, 0.0, 2.0, 0.0,-3.0,-2.0, 0.0, 4.0,
      -1.0,-2.0,-1.0, 1.0, 0.0, 2.0, 0.0,-2.0 };
   double y [] = {
      +0.0,-3.0, 0.0, 0.0, 2.0, 3.0, 0.0, 0.0,-1.0, 1.0,
      +1.0, 0.0, 1.0, 1.0, 0.0, 0.0,-1.0, 0.0 };
   double p,a;
   int icv=1; // Simple polygon (N>1), calling VALR7, p.40
   int iop=3; // 9 decimal digits of accuracy in P(II)
   int ind;   // Error indicator
   int ko;    // Winding number of II, only computed if ICV > 0 or ICV < 0, <>-2

   P2(x - 1, y - 1, noof(x), icv, iop, &p, &a, &ind, &ko);
   printf("demo_Fig_33_on_page_52() p=%lf a=%lf ind=%d ko=%d\n", p, a, ind, ko);

}

void demo_Fig_35_on_page_54()
// Expectation: ICV = 0 P = 0.127488 A = 62.00 S_bar N = 19
// Results : p = 0.127488256 A = 62.0
{

	double x[] = {
	   -5.0, 5.0, 5.0, -5.0, -5.0, 0.0, 5.0, 0.0, -3.0, 3.0,
	   +3.0, -3.0, -3.0, 0.0, 3.0, 0.0, -3.0, -3.0, -5.0 }; // ) !, -5.0 / )
	double y[] = {
	   -5.0, -5.0, 5.0, 5.0, 0.0, 5.0, 0.0, -5.0, -2.0, -2.0,
	   +2.0, 2.0, 0.0, 2.0, 0.0, -2.0, 0.0, -2.0, 0.0 }; // ) !, -5.0 / )
   double p,a;
   int icv=0;
   int iop=3;
   int ind,ko;
   
   P2(x - 1, y - 1, noof(x), icv, iop, &p, &a, &ind, &ko);
   printf("demo_Fig_35_on_page_54() p=%lf a=%lf ind=%d ko=%d\n", p, a, ind, ko);

}

void demo_Fig_40_on_page_59()
// Expectation: ICV = 1 P = 0.000000 A = 0.00 SI(0) N = 6
// Results : p = 0.000000e+00 A = 0.00
{

	double x[] = { -3.0, 3.0, 3.0, -3.0, -3.0, 3.0 };
	double y[] = { -3.0, -3.0, 3.0, -3.0, 3.0, 3.0 };
	double p, a;
	int icv = 1;
	int iop = 3;
	int ind, ko;

	P2(x - 1, y - 1, noof(x), icv, iop, &p, &a, &ind, &ko);
	printf("demo_Fig_40_on_page_59() p=%le a=%lf ind=%d ko=%d\n", p, a, ind, ko);

}

void demo_rectangle_9x9( int set )
{
	double //Y, No need to make the last point equal to the 1st point, cuz P2 and sub do it.
		x1[] = { 0.0, 0.0, 9.0, 9.0 }, // clock-wise
		y1[] = { 0.0, 9.0, 9.0, 0.0 },
		x2[] = { 0.0, -9.0, -9.0, 0.0 },
		y2[] = { 0.0, 0.0, 9.0, 9.0 },
		x3[] = { 0.0, 0.0, -9.0, -9.0 },
	    y3[] = { 0.0, -9.0, -9.0, 0.0 },
		x4[] = { 0.0, 9.0, 9.0, 0.0 },
		y4[] = { 0.0, 0.0, -9.0, -9.0 },
		x5[] = { 0.0, 9.0, 9.0, 0.0 }, // counterclock-wise
		y5[] = { 0.0, 0.0, 9.0, 9.0 },
		x6[] = { 0.0, 0.0, -9.0, -9.0 },
		y6[] = { 0.0, 9.0, 9.0, 0.0 },
		x7[] = { 0.0, -9.0, -9.0, 0.0 },
		y7[] = { 0.0, 0.0, -9.0, -9.0 },
		x8[] = { 0.0, 0.0, 9.0, 9.0 },
		y8[] = { 0.0, -9.0, -9.0, 0.0 };
	double *x, *y;
	const int icv = 0, iop = 3;
	double p, a;
	int n, ind, ko;

	switch (set) {
	case +1: x = x1; y = y1; n = noof(x1); break;
	case +2: x = x2; y = y2; n = noof(x2); break;
	case +3: x = x3; y = y3; n = noof(x3); break;
	case +4: x = x4; y = y4; n = noof(x4); break;
	case -1: x = x5; y = y5; n = noof(x5); break;
	case -2: x = x6; y = y6; n = noof(x6); break;
	case -3: x = x7; y = y7; n = noof(x7); break;
	case -4: x = x8; y = y8; n = noof(x8); break;
	default: return;
	}

	P2(x - 1, y - 1, n, icv, iop, &p, &a, &ind, &ko);
	printf("demo_rectangle_9x9(%d) p=%lf a=%lf ind=%d ko=%d\n", set, p, a, ind, ko);

}

/*
! Yongshik Kim (copyRight) 2016.1.13
//! Fortran 95 converted from Fortran IV of the original code

! COMPUTATION OF THE INTEGRAL OF THE BIVARIATE NORMAL DISTRIBUTION OVER ARBITRARY POLYGONS
! by A. R. DiDONATO and R. K. HAGEMAN
! June 1980, NAVAL SURFACE WEAPONS CENTER

! p.IV
! Integral of the Bivariate Normal Density Function (IBND)

! APPENDIX F
! PROGRAM LISTINGS IN FORTRAN IV
! P-2, VALR-2, SORT II, VALR-7. P-7, SORT 1, SORT 11. SMP-7
! (Flow charts on pages 40-45 and A-I 7 to A-I 9)

! F-1
! F-2 >> Missed

! P-2 is used for computing P(II) over an Arbitrary Polygon II*
! CALL: P-2 (x, y, N, P, ICV, IND, lOP, A, W),*
! where:
! x is the array of abscissas of the numbered points of II. x is dimensioned at N + 1.
! y is the array of ordinates of the numbered points of II. y is dimensioned at N + 1.
! N is the number of points specifying II, except if N = 1 when the IBND over an angular
!   region is computed. Three input points are needed when N = 1, given in counterclock-
!   wise order, with the vertex at point one, (see pages 25, 27).
! P is the location where the value of P(II) is returned.
!   [Page 2] If a simple polygon S is positively oriented, (PO), i.e., with its area on
!   the left as one traverses the boundary continuously, P(II) yields a positive result,
!   whereas if S is negatively oriented (NO), P(II) yields the same result with a minus sign.
! ICV must be set as an integer by the user according to the list below:
!   ICV = 0, II is simple, or of S type with no SAR(s) (see pages 12, 31). VALR-7 used alone.
!   ICV > 0, II is arbitrary. VALR-2 used alone.
!   ICV =-2, II is of S type with possible SAR(s).
!   ICV < 0, <> -2, II is arbitrary with PAR(s).
! IND is an error indicator. Normally, it is set to zero. If IND = 2, then PAR(s) have been
!   detected by either VALR-2 or VALR-7. For VALR-2, (ICV > 0, ICV < 0, <> -2) the result
!   for P(II) is acceptable. For VALR-7 (ICV = 0, -2) however, this result of IND = 2,
!   means the value for P(II) is most likely wrong, unless N = 1 VALR-7 is not to be used
!   alone where SAR(s) are a possibility, unless N = 1. If IND = 3, then N has not been
!   specified as an integer equal to one or greater than two. Such values of N are not
!   allowed.
! IOP is an accuracy parameter. It is set by the user to 1, 2. 3 for approximately 3, 6, or
!   9 decimal digits of accuracy in P(II).
! A is the location where A(II) is returned. |A| gives area of II, (see pages 9,26).
! W is the location where the winding number of II is returned. It is computed in VALR-2
!   and takes integer values (see pages 18, 19). W is defined as an integer variable. It is
!   initialized to one, and is only computed if ICV > 0 or ICV < 0, <>-2.

! F-3
*/

static int P2( double *vX, double *vY, int vSize, int ICV, int IOP,
    double *Prob, double *Area, int *IND, int *KO )
{
// SUBROUTINE P2(X,Y,NB,P,ICV,IND,IOP,A,KO)

   *Prob=0.; // Y, 2016.3.24-26
   *Area=0.; // Y, 2016.3.24-26
   *IND=*KO=0; // Y, 2016.3.24

   if (vSize!=2 || vSize>=1) goto _3031;
   *IND=3;
   return *IND ? 0:1;
_3031:
   *KO=1;
   if (ICV==0 || vSize==1) goto _3091;
   if (ICV>0) goto _3071;
   SORT3(vX,vY,vSize);  // See F-17
   if (vSize>2) goto _3061;
   return *IND ? 0:1;
_3061:
   if (ICV==-2) goto _3091;
_3071:
   VALR2(vX,vY,vSize,IOP,Prob,Area,IND,KO); // See F-6
   return *IND ? 0:1;
_3091:
   VALR7(vX,vY,vSize,IOP,Prob,Area,IND); // See F-21
   return *IND ? 0:1;

}

/*
! F-4

! SUBROUTINE VALR-2
! (FLOW CHART 2, page 41)
! VALR-2 is used to compute P(II) when II is arbitrary
! CALL: VALR-2 (x, y, N, P, IOP, A, IND, W),
! where:
! x is the array of abscissas of the numbered points of II. x is dimensioned at N + 1.
! y is the array of ordinates of the numbered points of II. y is dimensioned at N + 1.
! N is the number of points specifying II, except if N = 1 when the IBND over an angular
!   region is computed. Three input points are needed, when N = 1, given in counterclockwise
!   order, with the vertex at point one, (see pages 25, 27).
! P,A are the locations where the values of P(II) and A(II) are returned.
! IOP is an accuracy parameter. It is set by the user to 1, 2, or 3 for approximately 3, 6, or
!   9-decimal digits of accuracy in P(II).
! IND is an error indicator. Normally, it is set to zero. If IND = 2, it informs the user that H
!   contains a PAR. The value for P(II) is acceptable. If IND = 3, then N has not been
!   specified as an integer equal to one or greater than two. Such values of N are not
!   allowed.
! W is the location where the value of the winding number W for II is returned. W is an
!   integer variable.

! F-5
*/

static int VALR2( double *vX, double *vY, int vSize, int IOP,
    double *Prob, double *Area, int *IND, int *KO )
// SUBROUTINE VALR2(XX,YY,N,P,IOP,A,IND,KO)
{
#ifndef PI
   const double PI = 3.1415926535898;
#endif
   const double TWOPI = 6.28318530717958;
   const double ALNPI = 1.14472988584940;
   const double C1 = .282094791773877;
   const double C2 = .159154943091895;
   const double TAU = 7.E-14;
   const double TAUSQ = 4.9E-27;
   const double RTPII = .56418958354776;
   const double E[] = { 0, // [0]=0, to mimick starting index 1
      .885777518572895E+00,-.981151952778050E+00,
      .759305502082485E+00,-.353644980686977E+00,
      .695232092435207E-01};
   const double E2[] = { 0,
      .886226470016632E+00,-.999950714561036E+00,
      .885348820003892E+00,-.660611239043357E+00,
      .421821197160099E+00,-.222898055667208E+00,
      .905057384150449E-01,-.254906111884287E-01,
      .430895168984138E-02,-.323377239693247E-03};
   const double E3[] = { 0,
      .886226924931465E+00,-.999999899776252E+00,
      .886223733186722E+00,-.666626670510907E+00,
      .442851899328569E+00,-.265638206366025E+00,
      .145060043403014E+00,-.714909837799889E-01,
      .309199295521210E-01,-.112323532148441E-01,
      .324944543171185E-02,-.704260243309096E-03,
      .105787574480633E-03,-.971864864160461E-05,
      .408335517232165E-06};
   const double APH1 []= { 0, 2.02E-7,2.08E-13,2.71E-19 };
   const double APH2 [] = { 0, 1.22E-2,1.23E-4,1.34E-6 };
   const double APH4 [] = { 0, .6962E-1, .6990E-2, .7311E-3 };
   const double RSQ [] = { 0, 6.0516,12.60605,19.201924 };
   const double A3D8 [] = { 0, 0.28125E-4,0.285E-7,0.32625E-10 };
   const double CST [] = { 0, .5625E-4,.57E-7,.6512E-10 };

   double W,Z,U,V,PSI1,XK,YK,D1SQ,D2SQ,BGD1,BGD2,CEE,AJ0,B,CAPG,P1,
          CAPE,CAPH,F,AJ1,T,CAPV,CIRCM,SUM,YKM1,L,KOM;
   int K,M;

   int N=vSize;
   double *G=dvector(1,2);
   double *H=dvector(1,2);
   double *X=dvector(1,N+1);
   double *Y=dvector(1,N+1);
#define RETURN {free_dvector(G,1,2);free_dvector(H,1,2); \
                free_dvector(X,1,N+1);free_dvector(Y,1,N+1); \
                return *IND ? 0:1;}
   memcpy(&X[1],&vX[1],sizeof(double)*N);
   memcpy(&Y[1],&vY[1],sizeof(double)*N);
   *Prob=0.; // Y, 2016.3.25-26
   *Area=0; // Y, 2016.3.25
   *IND=*KO=0; // Y, 2016.3.25

   if (N!=2 && N>=1) goto _3011; // Y, check min. polygon corner N>=3 (triangle)
   *IND=3;

//! F-6

   RETURN;
_3011:
   KOM=0.;
   K=1;
   if (N!=1) goto _3021;
   W=X[2]-X[1];
   Z=Y[2]-Y[1];
   U=X[3]-X[1];
   V=Y[3]-Y[1];
   PSI1=V*W-U*Z;
   if (PSI1>=0.) goto _3041;
   *Prob=-1.;
   SWAP2(U,W,double);
   SWAP2(V,Z,double);
   goto _3041;
_3021:
   Y[N+1]=Y[1];
   X[N+1]=X[1];
   U=X[2]-X[1];
   V=Y[2]-Y[1];
   XK=X[1];
   YK=Y[1];
_3031:
   W=X[1]-X[N];
   Z=Y[1]-Y[N];
_3041:
   D1SQ=W*W+Z*Z;
   if (D1SQ>TAUSQ) goto _3051;
   if (N==1) goto _4011;
   N=N-1;
   if (N==2) return *IND ? 0:1;
   goto _3031;
_3051:
   D2SQ=U*U+V*V;
   if (D2SQ>TAUSQ) goto _3071;
   if (N==1) goto _4011;
_3061:
   K=K+1;
   U=X[K+1]-XK;
   V=Y[K+1]-YK;
   D2SQ=U*U+V*V;

//! F-7

   if (D2SQ<=TAUSQ) goto _3061;
   if (K==(N-1)) RETURN;
_3071:
   *Area=XK*(Y[K+1]-Y[N]);
   BGD1=sqrt(2.*D1SQ);
   BGD2=sqrt(2.*D2SQ);
_3081:
   PSI1=V*W-U*Z;
   CEE=U*W+V*Z;
   AJ0=atan2(PSI1,CEE);
#ifdef BEBUG_PRINT_ON
   printf("VALR2_3081 K=%d, AJ0(delta_theta_k)=%lf\n", K,AJ0);
#endif
   KOM=KOM+AJ0;
   L=0.;
   B=.5*(X[K]*X[K]+Y[K]*Y[K]);
   if (B>APH1[IOP]) goto _3111;
   CAPG=0.;
_3101:
   P1=AJ0/TWOPI-CAPG;
#ifdef BEBUG_PRINT_ON
   printf("VALR2_3101 K=%d, P1=%lf\n", K, P1);
#endif
   goto _3621;
_3111:
   G[1]=(W*X[K]+Z*Y[K])/BGD1;
   G[2]=(U*X[K]+V*Y[K])/BGD2;
   H[1]=(-Y[K]*W+X[K]*Z)/BGD1;
   H[2]=(-Y[K]*U+X[K]*V)/BGD2;
   if (ABS(PSI1)>(BGD1*BGD2*A3D8[IOP])) goto _3241;
   if (CEE<0.) goto _3131;
   if (ABS(AJ0)<=TAU) goto _3121;
   if (G[1]>=0.) goto _3121;
   goto _3241;
_3121:
   P1=0.;
   goto _3621;
_3131:
   if (ABS(PSI1)<=(.5*TAU*BGD1*BGD2)) *IND=2;
   if (PSI1<0.) goto _3171;
   P1=.5*erfc(H[2]);
   goto _3621;
_3171:
   P1=-.5*erfc(H[1]);
   goto _3621;
_3241:
   if (B<=APH2[IOP]) goto _3301;
   if (G[1]<0.) goto _3261;
   if (G[2]>=0.) goto _3471;
   G[2]=-G[2];
   H[2]=-H[2];
   if (ABS(H[2])<=APH4[IOP]) goto _3251;
   L=.5*erfc(-H[2]);
   goto _3461;

//! F-8

_3251:
   L=.5+RTPII*H[2];
   goto _3461;
_3255:
   L=.5-RTPII*H[1];
   goto _3461;
_3261:
   G[1]=-G[1];
   H[1]=-H[1];
   if (G[2]<0.) goto _3271;
   if (ABS(H[1])<=APH4[IOP]) goto _3255;
   L=.5*erfc(H[1]);
   goto _3461;
_3271:
   G[2]=-G[2];
   H[2]=-H[2];
   if (ABS(H[1])<=APH4[IOP]) goto _3291;
   if (ABS(H[2])<=APH4[IOP]) goto _3281;
   L=.5*(erfc(H[1])-erfc(H[2]));
   goto _3471;
_3281:
   L=RTPII*H[2]-.5*erf(H[1]);
   goto _3471;
_3291:
   if (ABS(H[2])<=APH4[IOP]) goto _3295;
   L=.5*erf(H[2])-RTPII*H[1];
   goto _3471;
_3295:
   L=RTPII*(H[2]-H[1]);
   goto _3471;
_3301:
   CAPG=C1*(H[2]-H[1])-C2*(G[2]*H[2]-G[1]*H[1]);
   goto _3101;
_3461:
   PSI1=-PSI1;
   if (PSI1<=0.) goto _3465;
   L=L-1.;
   AJ0=PI+AJ0;
   goto _3471;
_3465:
   AJ0=AJ0-PI;
_3471:
   if (B>=RSQ[IOP]) goto _3501;
   CAPE=AJ0;
   CAPH=.5*AJ0;
   M=1;
   F=0.;
   AJ1=H[2]-H[1];

//! F-9

   CIRCM=AJ1;
   if (IOP==3) goto _3681;
   if (IOP==2) goto _3701;
   SUM=E[M]*AJ1;
_3481:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E[M]*CAPV;
   if (M>=5) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3481;
_3491:
   P1=L+exp(-(B+ALNPI))*(CAPH-SUM);
#ifdef BEBUG_PRINT_ON
   printf("VALR2_3491 K=%d, P1=%lf\n", K, P1);
#endif
   goto _3621;
_3501:
   P1=L;
_3621:
   if (K!=N) goto _3651;
   if (N!=1) goto _3631;
   *Prob=ABS(*Prob+ABS(P1));
   RETURN;
_3631:
   *Prob=*Prob-P1;
   KOM=KOM/TWOPI;
   *Area=.5**Area;
   if (KOM<0.) goto _3641;
   *KO=(int)(KOM+.125);
   goto _3645;
_3641:
   *KO=(int)(KOM-.125);
_3645: //!Y, Exit if succeeded
   *Prob=*Prob+(double)*KO;
   RETURN;
_3651:
   W=U;
   Z=V;
   BGD1=BGD2;
   XK=X[K+1];
   YK=Y[K+1];
   YKM1=Y[K];
_3661:
   K=K+1;
   U=X[K+1]-XK;

//! F-10

   V=Y[K+1]-YK;
   D2SQ=U*U+V*V;
   if (D2SQ<=TAUSQ) goto _3661;
   BGD2=sqrt(2.*D2SQ);
   *Prob=*Prob-P1;
   *Area=*Area+XK*(Y[K+1]-YKM1);
   goto _3081;
_3681:
   SUM=E3[M]*AJ1;
_3691:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E3[M]*CAPV;
   if (M>=15) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3691;
_3701:
   SUM=E2[M]*AJ1;
_3711:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E2[M]*CAPV;
   if (M>=10) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3711;
_4011:
   *Prob=.5;
   *IND=1;
   RETURN;
#undef RETURN
}

/*
//! F-15

! SUBROUTINE SORT III
! (FLOW CHART 3, page 43)
! Subroutine SORT III Used to Eliminate SDP and/or SCP from II
! CALL: SORT III (x, y, N),
! where:
! x is the array of abscissas of the numbered points of the polygon II. The array is dimensioned
!   at N. Upon return to the calling program, P-2 (or P-7), the array of abscissas will be
!   reduced by the number of consecutive duplicate points SDP and SCP eliminated. The
!   array is compacted.*
! y is the array of ordinates of the numbered points of the polygon [I. The array is dimensioned
!   at N. Upon return to the calling program, P-2 (or P-7), the array of ordinatcs will be
!   reduced by the number of points deleted due to SDP and SCP. The array is CU.
! N is the number of points initially used to specify the polygon. Upon return to the calling
!   program, P-2 (or P-7), N will be reduced by the number of points that were eliminated.

//! F-16
*/

static int SORT3( double *vX, double *vY, int vSize )
//SUBROUTINE SORT3(X,Y,N)
{
   double U,V,D2,W,Z,D1,T,SN;
   int K,L,LM2,I1,I,KP1,I2;
   const double CST = 4.9E-27;

   double *X=vX;
   double *Y=vY;
   int N=vSize;

_3041:
   if (N<3) return 0;
   K=1;
   L=2;
_3051:
   U=X[1]-X[N];
   V=Y[1]-Y[N];
   D2=U*U+V*V;
   if (D2>CST) goto _3061;
   N=N-1;
   if (N>2) goto _3051;
   return 0;
_3061:
   W=X[L]-X[1];
   Z=Y[L]-Y[1];
   D1=W*W+Z*Z;
   if (D1>CST) goto _3071;
   L=L+1;
   goto _3061;
_3071:
   if (L==(K+1)) goto _3091;
   LM2=L-2;
   N=N-LM2;
   for (I=2; I<=N; I++) { // DO 3081 I=2,N
   I1=LM2+I;
   X[I]=X[I1];
   Y[I]=Y[I1];
   }
//_3081:
   L=2;
_3091:
   T=V*W-U*Z;
   SN=(4.*T*T)/(D1*D2);
   if (SN>CST) goto _3121;
_3111:
   L=L+1;
   if (L>N) goto _3341;
_3115:
   W=X[1]-X[1];
   Z=Y[1]-Y[1];
   D1=W*W+Z*Z;
   if (D1>CST) goto _3091;
   goto _3111;
_3121:
   if (L==2) goto _3141;
   LM2=L-2;

//! F-17

   N=N-LM2;
   for (I=1; I<=N; I++) { // DO 3131 I=1,N
   I1=LM2+I;
   X[I]=X[I1];
   Y[I]=Y[I1];
   }
//_3131:
   goto _3041;
_3141:
   K=2;
   L=3;
   goto _3161;
_3151:
   D1=D2;
   W=U;
   Z=V;
_3155:
   L=K+1;
_3161:
   U=X[L]-X[K];
   V=Y[L]-Y[K];
   D2=U*U+V*V;
   if (D2>CST) goto _3171;
_3165:
   L=L+1;
   if (L<=N) goto _3161;
   N=K;
   goto _3251;
_3171:
   if (L==(K+1)) goto _3191;
   N=N-((L-1)-K);
   KP1=K+1;
   I2=L-KP1;
   for (I=KP1; I<=N; I++) { // DO 3181 I=KP1,N
   I1=I2+I;
   X[I]=X[I1];
   Y[I]=Y[I1];
   }
//_3181:
   L=KP1;
_3191:
   T=V*W-U*Z;
   SN=(4.*T*T)/(D1*D2);
   if (SN>CST) goto _3221;
_3201:
   L=L+1;
   if (L>N) goto _3211;
   U=X[L]-X[K];
   V=Y[L]-Y[K];
   D2=U*U+V*V;

//! F-18

   if (D2>CST) goto _3191;
   goto _3201;
_3211:
   X[K]=X[N];
   Y[K]=Y[N];
   N=K;
   goto _3251;
_3221:
   if (L==(K+1)) goto _3241;
   I2=L-1-K;
   N=N-I2;
   LM2=L-2;
   for (I=K; I<=N; I++) { // DO 3231 I=K,N
   I1=I2+I;
   X[I]=X[I1];
   Y[I]=Y[I1];
   }
//_3231:
   W=X[K]-X[K-1];
   Z=Y[K]-Y[K-1];
   D1=W*W+Z*Z;
   if (D1>CST) goto _3155;
   K=K-1;
   if (K<2) goto _3041;
   W=X[K]-X[K-1];
   Z=Y[K]-Y[K-1];
   D1=W*W+Z*Z;
   L=K+1;
   goto _3165;
_3241:
   K=K+1;
   if (K<N) goto _3151;
   goto _3255;
_3251:
   U=X[N]-X[N-1];
   V=Y[N]-Y[N-1];
   D2=U*U+V*V;
   if (D2<=CST) goto _3261;
_3255:
   W=X[1]-X[N];
   Z=Y[1]-Y[N];
   D1=W*W+Z*Z;
   if (D1<=CST) goto _3261;
   T=V*W-U*Z;
   SN=(4.*T*T)/(D1*D2);
   if (SN>CST) goto _3351;
_3261:
   N=N-1;
   if (N>2) goto _3251;

//! F-19

   return 1;
_3341:
   N=2;
   return 1;
_3351:
   D2=D1;
   U=W;
   V=Z;
   W=X[2]-X[1];
   Z=Y[2]-Y[1];
   D1=W*W+Z*Z;
   T=V*W-U*Z;
   SN=(4.*T*T)/(D1*D2);
   if (SN>CST) return 1;
   L=3;
   goto _3115;;

}

/*
//! F-20

! SUBROUTINE VALR-7
! (FLOW CHART 4, page 44)
! Subroutine VALR-7 Used to Compute p (8), where S has no SAR(s), (See page 3 1)
! CALL: VALR-7 (x, y, M, p, IOP, a, IND),*
! where:
! x is the input array of abscissas for S. Dimensioned at M + 1.
! y is the input array of ordinates for S. Dimensioned at M + 1.
! M is the number of input points for S. When M = 1, IBND over an angular region is com-
!   puted. Three input points in counterclockwise order are used to specify the region with
!   the vertex at (1).
! p is the location where the function value for p(S) will be returned.
! IOP is set by the user to 1, 2, or 3 for approximately 3, 6, or 9-decimal-digit accuracy,
!   respectively, in p(S).
! a is the location where the value of the function a(S) is returned. The absolute value of
!   a gives the area of S.
! IND is an error indicator normally set to zero. If PAR(s) are detected by VALR-7, then
!   IND is set to two and the result for p(S) is most likely wrong, unless M = 1. See Flow
!   Chart 4-24, 20, 21, 22. VALR-7 should never be used alone if SAR(s) are a possibility,
!   unless M = 1. If M = 2 or M < 1, then IND = 3 and an EXIT is made. Such M are not
!   allowed.

//! F-21
*/

static int VALR7( double *vX, double *vY, int vSize, int IOP,
    double *Prob, double *Area, int *IND )
// SUBROUTINE VALR7(XX,YY,N,P,IOP,A,IND)
{

   const double TWOPI = 6.28318530717958;
   const double ALNPI = 1.14472988584940;
   const double C1 = .282094791773877;
   const double C2 = .159154943091895;
   const double TAU = 7.E-14;
   const double E[] = {0, // shift starting index to 1
      .885777518572895E+00, -.981151952778050E+00,
      .759305502082485E+00, -.353644980686977E+00,
      .695232092435207E-01};
   const double E2[] = {0,
      .886226470016632E+00, -.999950714561036E+00,
      .885348820003892E+00, -.660611239043357E+00,
      .421821197160099E+00, -.222898055667208E+00,
      .905057384150449E-01, -.254906111884287E-01,
      .430895168984138E-02, -.323377239093247E-03};
   const double E3[] = {0,
      .886226924931465E+00, -.999999899776252E+00,
      .886223733186722E+00, -.666626670510907E+00,
      .442851899328569E+00, -.265638206366025E+00,
      .145060043403014E+00, -.714909837799889E-01,
      .309199295521210E-01, -.112323532148441E-01,
      .324944543171185E-02, -.704260243309096E-03,
      .105787574480633E-03, -.971864864160461E-05,
      .408335517232165E-06};
   const double APH1 [] = {0, 2.02E-7,2.08E-13,2.71E-19};
   const double APH2 [] = {0, 1.22E-2,1.23E-4,1.34E-6};
   const double APH4 [] = {0, .6962E-1, .6990E-2, .7311E-3};
   const double RTPII = .56418958354776;
   const double RSQ [] = {0, 6.0516,12.60605,19.201924};
   const double CST [] = {0, .5625E-4,.57E-7,.6512E-10};

   double W,Z,U,V,PSI1,T1,T2,BGD1,BGD2,B,
          CAPG,PHIK,P1,SN,CN,AJ0,CAPE,CAPH,F,CIRCM,AJ1,SUM,T,CAPV,L;
   int K,M;

   int N=vSize;
   double *G=dvector(1,2);
   double *H=dvector(1,2);
   double *X=dvector(1,N+1);
   double *Y=dvector(1,N+1);
#define RETURN {free_dvector(G,1,2);free_dvector(H,1,2); \
                free_dvector(X,1,N+1);free_dvector(Y,1,N+1); \
                return *IND ? 0:1;}
   memcpy(&X[1],&vX[1],sizeof(double)*N);
   memcpy(&Y[1],&vY[1],sizeof(double)*N);
   *Prob=0.; // Y, 2016.3.25-26
   *Area=0.; // Y, 2016.3.25-26
   *IND=0; // Y, 2016.3.25

   if (N!=2 && N>=1) goto _3061;
   *IND=3;
   RETURN;
_3061:
   if (N!=1) goto _3071;

//! F-22

   K=1;
   W=X[2]-X[1];
   Z=Y[2]-Y[1];
   U=X[3]-X[1];
   V=Y[3]-Y[1];
   PSI1=V*W-U*Z;
   if (PSI1>=0.) goto _3081;
   *Prob=-1.;
   SWAP2(U,W,double);
   SWAP2(V,Z,double);
   goto _3081;
_3071:
   *Area=SMP7(X,Y,N); // ! Y, Calculate polygon area only at this step
   if (ABS(*Area)<=CST[IOP]) RETURN;
   K=1;
   W=X[1]-X[N];
   Z=Y[1]-Y[N];
   U=X[2]-X[1];
   V=Y[2]-Y[1];
   X[N+1]=X[1];
   Y[N+1]=Y[1];
_3081:
   BGD1=sqrt(2.*(W*W+Z*Z));
   BGD2=sqrt(2.*(U*U+V*V));
_3091:
   L=0.;
   B=.5*(X[K]*X[K]+Y[K]*Y[K]);
   if (B>APH1[IOP]) goto _3111;
   CAPG=0.;
_3101:
   T1=V*W-U*Z;
   T2=U*W+V*Z;
   PHIK=atan2(T1,T2);
   P1=PHIK/TWOPI-CAPG;
   goto _3621;
_3111:
   G[1]=(W*X[K]+Z*Y[K])/BGD1;
   G[2]=(U*X[K]+V*Y[K])/BGD2;
   H[1]=(-Y[K]*W+X[K]*Z)/BGD1;
   H[2]=(-Y[K]*U+X[K]*V)/BGD2;
   SN=(2.*(V*W-U*Z))/(BGD1*BGD2);
   if (ABS(SN)>CST[IOP]) goto _3241;
   CN=G[1]*G[2]+H[1]*H[2];

//! F-23

   if (CN<0.) goto _3131;
   if (ABS(SN)<=TAU) goto _3121;
   if (G[1]>=0.) goto _3121;
   goto _3241;
_3121:
   P1=0.;
   goto _3621;
_3131:
   if (ABS(SN)<=TAU) *IND=2;
   if (SN <0.) goto _3171;
   P1=.5*erfc(H[2]);
   goto _3621;
_3171:
   P1=-.5*erfc(H[1]);
   goto _3621;
_3241:
   if (B<=APH2[IOP]) goto _3301;
   SN=B*SN;
   if (G[1]<0.) goto _3261;
   if (G[2]>=0.) goto _3471;
   G[2]=-G[2];
   H[2]=-H[2];
   if (ABS(H[2])<=APH4[IOP]) goto _3251;
   L=.5*erfc(-H[2]);
   goto _3461;
_3251:
   L=.5+RTPII*H[2];
   goto _3461;
_3255:
   L=.5-RTPII*H[1];
   goto _3461;
_3261:
   G[1]=-G[1];
   H[1]=-H[1];
   if (G[2]<0.) goto _3271;
   if (ABS(H[1])<=APH4[IOP]) goto _3255;
   L=.5*erfc(H[1]);
   goto _3461;
_3271:
   G[2]=-G[2];
   H[2]=-H[2];
   if (ABS(H[1])<=APH4[IOP]) goto _3291;
   if (ABS(H[2])<=APH4[IOP]) goto _3281;
   L=.5*(erfc(H[1])-erfc(H[2]));
   goto _3471;
_3281:
   L=RTPII*H[2]-.5*erf(H[1]);
   goto _3471;

//! F-24

_3291:
   if (ABS(H[2])<=APH4[IOP]) goto _3295;
   L=.5*erf(H[2])-RTPII*H[1];
   goto _3471;
_3295:
   L=RTPII*(H[2]-H[1]);
   goto _3471;
_3301:
   CAPG=C1*(H[2]-H[1])-C2*(G[2]*H[2]-G[1]*H[1]);
   goto _3101;
_3461:
   SN=-SN;
   if (SN<=0.) goto _3471;
   L=L-1.;
_3471:
   if (B>=RSQ[IOP]) goto _3501;
   CN=G[1]*G[2]+H[1]*H[2];
   AJ0=atan2(SN,CN);
   CAPE=AJ0;
   CAPH=.5*AJ0;
   M=1;
   F=0.;
   AJ1=H[2]-H[1];
   CIRCM=AJ1;
   if (IOP==3) goto _3681;
   if (IOP==2) goto _3701;
   SUM=E[M]*AJ1;
_3481:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E[M]*CAPV;
   if (M>=5) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3481;
_3491:
   P1=L+exp(-(B+ALNPI))*(CAPH-SUM);
   goto _3621;
_3501:
   P1=L;
_3621:
   if (K!=N) goto _3651;
   if (N!=1) goto _3631;
   *Prob=ABS(*Prob+ABS(P1));

//! F-25

   RETURN;
_3631:
   *Prob=*Prob-P1;
   if (*Area<0.) goto _3641;
   *Prob=*Prob+1.;
   RETURN;
_3641:
   *Prob=*Prob-1.;
   RETURN;
_3651:
   K=K+1;
   W=U;
   Z=V;
   U=X[K+1]-X[K];
   V=Y[K+1]-Y[K];
   BGD1=BGD2;
   BGD2=sqrt(2.*(U*U+V*V));
   *Prob=*Prob-P1;
#ifdef BEBUG_PRINT_ON
   printf("VALR7_3651 Prob=%lf\n",*Prob);
#endif
   goto _3091;
_3681:
   SUM=E3[M]*AJ1;
_3691:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E3[M]*CAPV;
   if (M>=15) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3691;
_3701:
   SUM=E2[M]*AJ1;
_3711:
   M=M+1;
   H[2]=H[2]*G[2];
   H[1]=H[1]*G[1];
   T=H[2]-H[1];
   F=F+B;
   CAPV=(F*CAPE+T)/M;
   SUM=SUM+E2[M]*CAPV;
   if (M>=10) goto _3491;
   CAPE=CIRCM;
   CIRCM=CAPV;
   goto _3711;

#undef RETURN
}

/*
//! F-36

! SUBROUTINE SMP-7
! (No flow chart given)
! SMP-7 is Used to Compute the a-Function*
! CALL: SMP-7 (M, a, x, y),
! where:
! M is the number of input points specifying the polygon.
! a is the location to which the a-function is returned.
! x is the array of input abscissas. Dimensioned at M.
! y is the array of input ordinates. Dimensioned at M.

//! F-37
*/

static double SMP7 (double *X, double *Y, int NB)
// SUBROUTINE SMP7(NB,ANS,X,Y)
{

   double ANS;
   int NBM1,I;

   if (NB>3) goto _3151;
   ANS=.5*((X[2]-X[1])*(Y[3]-Y[1])-(X[3]-X[1])*(Y[2]-Y[1]));
   return ANS;
_3151:
   NBM1=NB-1;
   ANS=X[1]*(Y[2]-Y[NB])+X[NB]*(Y[1]-Y[NBM1]);
   for (I=2; I<=NBM1; I++){ // DO 3161 I=2,NBM1
   ANS=ANS+X[I]*(Y[I+1]-Y[I-1]);
   }
//_3161:
   ANS=.5*ANS;
   return ANS;

}

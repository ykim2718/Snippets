program yBVNCDFOCP_TEST

   implicit none
   interface
      real (kind=4) function yBVNCDFOCP(x,y,n)
         real (kind=4), dimension(1:n) :: x, y
         integer n
      end function
      real(4) function demo_Fig_33_on_page_52()
      end function
      real(4) function demo_Fig_35_on_page_54()
      end function
      real(4) function demo_Fig_40_on_page_59()
      end function
      real(4) function demo_rectangle_9x9(i)
         integer i ! 1,2,3,4,-1,-2,-3,-4
      end function
   end interface

   real(4) P
   p=demo_Fig_33_on_page_52()
   p=demo_Fig_35_on_page_54()
   p=demo_Fig_40_on_page_59()
   p=demo_rectangle_9x9(1)
   p=demo_rectangle_9x9(2)
   p=demo_rectangle_9x9(3)
   p=demo_rectangle_9x9(4)
   p=demo_rectangle_9x9(-1)
   p=demo_rectangle_9x9(-2)
   p=demo_rectangle_9x9(-3)
   p=demo_rectangle_9x9(-4)
   !print *, "yBVNCDFOCP_TEST()=",p

end program

real(4) function demo_Fig_33_on_page_52() ! referring to the table on page 48

   ! Expectation: ICV=1,-1 P=0.941625 A=20.50 S_bar N=18
   ! Results: p=0.941624880 A=20.5

   implicit none
   integer, parameter:: n = 18
   real(4) :: x(n) = (/ &
      & -3.0, 0.0, 4.0, 0.0, 2.0, 0.0,-3.0,-2.0, 0.0, 4.0, &
      & -1.0,-2.0,-1.0, 1.0, 0.0, 2.0, 0.0,-2.0/)
   real(4) :: y(n) = (/ &
      &  0.0,-3.0, 0.0, 0.0, 2.0, 3.0, 0.0, 0.0,-1.0, 1.0, &
      &  1.0, 0.0, 1.0, 1.0, 0.0, 0.0,-1.0, 0.0/)
   real(4) p,a
   integer ind,ko,icv,iop

   icv=1
   iop=3
   call P2(x,y,n,p,icv,ind,iop,a,ko)
   demo_Fig_33_on_page_52=p
   print *,"demo_Fig_33_on_page_52() p=",p,"a=",a,"ind=",ind, "ko=",ko

end function

real(4) function demo_Fig_35_on_page_54()

   ! Expectation: ICV=0 P=0.127488 A=62.00 S_bar N=19
   ! Results: p=0.127488256 A=62.0

   implicit none
   integer, parameter:: n = 19
   real(4) :: x(n) = (/ &
      & -5.0, 5.0, 5.0,-5.0,-5.0, 0.0, 5.0, 0.0,-3.0, 3.0, &
      & +3.0,-3.0,-3.0, 0.0, 3.0, 0.0,-3.0,-3.0,-5.0/) !,-5.0/)
   real(4) :: y(n) = (/ &
      & -5.0,-5.0, 5.0, 5.0, 0.0, 5.0, 0.0,-5.0,-2.0,-2.0, &
      &  2.0, 2.0, 0.0, 2.0, 0.0,-2.0, 0.0,-2.0, 0.0/) !,-5.0/)
   real(4) p,a
   integer ind,ko,icv,iop

   icv=0
   iop=3
   call P2(x,y,n,p,icv,ind,iop,a,ko)
   demo_Fig_35_on_page_54=p
   print *,"demo_Fig_35_on_page_54() p=",p,"a=",a,"ind=",ind, "ko=",ko

end function

real(4) function demo_Fig_40_on_page_59()

   ! Expectation: ICV=1 P=0.000000 A=0.00 SI(0) N=6
   ! Results: p=5.96e-8 ? A=0.00

   implicit none
   integer, parameter:: n = 6
   real(4) :: x(n) = (/-3.0, 3.0, 3.0,-3.0,-3.0, 3.0/)
   real(4) :: y(n) = (/-3.0,-3.0, 3.0,-3.0, 3.0, 3.0/)
   real(4) p,a
   integer ind,ko,icv,iop

   icv=1
   iop=3
   call P2(x,y,n,p,icv,ind,iop,a,ko)
   demo_Fig_40_on_page_59=p
   print *,"demo_Fig_40_on_page_59() p=",p,"a=",a,"ind=",ind, "ko=",ko

end function

real(4) function demo_rectangle_9x9(i)

   implicit none
   integer,parameter:: n = 4, icv = 0, iop = 3
   real(4),dimension(n):: x, y
   real(4) p,a
   integer i,ind,ko

   if (i.EQ.+1) goto 14 ! clock-wise
   if (i.EQ.+2) goto 24
   if (i.EQ.+3) goto 34
   if (i.EQ.+4) goto 44
   if (i.EQ.-1) goto 140 ! counter-clock-wise
   if (i.EQ.-2) goto 240
   if (i.EQ.-3) goto 340
   if (i.EQ.-4) goto 440
14 continue
   x(1:4) = (/ 0.0, 0.0, 9.0, 9.0 /) ! Y, Don't need to make the last point equal to the 1st point.
   y(1:4) = (/ 0.0, 9.0, 9.0, 0.0 /) ! Because P2 and sub-functions do it.
   goto 99
24 continue
   x(1:4) = (/ 0.0,-9.0,-9.0, 0.0 /)
   y(1:4) = (/ 0.0, 0.0, 9.0, 9.0 /)
   goto 99
34 continue
   x(1:4) = (/ 0.0, 0.0,-9.0,-9.0 /)
   y(1:4) = (/ 0.0,-9.0,-9.0, 0.0 /)
   goto 99
44 continue
   x(1:4) = (/ 0.0, 9.0, 9.0, 0.0 /)
   y(1:4) = (/ 0.0, 0.0,-9.0,-9.0 /)
   goto 99
140 continue
   x(1:4) = (/ 0.0, 9.0, 9.0, 0.0 /)
   y(1:4) = (/ 0.0, 0.0, 9.0, 9.0 /)
   goto 99
240 continue
   x(1:4) = (/ 0.0, 0.0,-9.0,-9.0 /)
   y(1:4) = (/ 0.0, 9.0, 9.0, 0.0 /)
   goto 99
340 continue
   x(1:4) = (/ 0.0,-9.0,-9.0, 0.0 /)
   y(1:4) = (/ 0.0, 0.0,-9.0,-9.0 /)
   goto 99
440 continue
   x(1:4) = (/ 0.0, 0.0, 9.0, 9.0 /)
   y(1:4) = (/ 0.0,-9.0,-9.0, 0.0 /)
99 continue

   call P2(x,y,n,p,icv,ind,iop,a,ko)
   demo_rectangle_9x9=p
   print *,"demo_rectangle_9x9()",i,"p=",p,"a=",a,"ind=",ind, "ko=",ko

end function

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
real (kind=4) function yBVNCDFOCP(X,Y,N)

   implicit none
   real (kind=4),dimension(1:N):: X,Y
   integer N
   real (kind=4) P   ! Value of P(II)
   real (kind=4) A   ! Area of II
   integer IND ! Error indicator
   integer KO  ! Winding number of II, only computed if ICV > 0 or ICV < 0, <>-2
   integer:: ICV=0 ! Simple polygon (N>1), calling VALR7, p.40
   integer:: IOP=3 ! 9 decimal digits of accuracy in P(II)

   call P2(X,Y,N,P,ICV,IND,IOP,A,KO)
   yBVNCDFOCP=P

   print *,"yBVNCDFOCP() P=",P,"A=",A,"IND=",IND, "KO=",KO

end

! Yongshik Kim (copyRight) 2016.1.13
! Fortran 95 converted from Fortran IV of the original code

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

SUBROUTINE P2(X,Y,NB,P,ICV,IND,IOP,A,KO)

   implicit none ! Y, turn off fortran legacy of implicit integer (i-n)
   real (kind=4), dimension(1:NB) :: X,Y ! Y !DIMENSION X(1),Y(1)
   real (kind=4) :: P,A ! Y
   integer :: NB,ICV,IND,IOP,KO,N ! Y

   IF (NB.NE.2.AND.NB.GE.1) GO TO 3031
   IND=3
   RETURN
3031 CONTINUE
   N=NB
   KO=1
   IF (ICV.EQ.0.OR.NB.EQ.1) GO TO 3091
   IF (ICV.GT.0) GO TO 3071
   CALL SORT3(X,Y,N)  ! See F-17
   IF (N.GT.2) GO TO 3061
   P=0.
   A=0.
   IND=0
   RETURN
3061 CONTINUE
   IF (ICV.EQ.-2) GO TO 3091
3071 CONTINUE
   CALL VALR2(X,Y,N,P,IOP,A,IND,KO) ! See F-6
   RETURN
3091 CONTINUE
   CALL VALR7(X,Y,N,P,IOP,A,IND) ! See F-21
   RETURN

END

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

SUBROUTINE VALR2(XX,YY,N,P,IOP,A,IND,KO)

   implicit none
   interface !Y
      real(4) function ERF1(x) ! erf(x)
         real(4) x
      end function
      real(4) function ERFC1(ind,x) ! erfc(x)
         integer ind
         real(4) x
      end function
   end interface
   real(4),dimension(N):: XX,YY !Y, !DIMENSION X(1),Y(1)
   real(4) P,A !Y
   integer N,IOP,IND,KO !Y

   real(4) PI,TWOPI,ALNPI,C1,C2,TAU,TAUSQ,RTPII,W,Z,U,V,PSI1,T1,XK,YK,D1SQ,D2SQ, & !Y
        & BGD1,BGD2,CEE,AJ0,B,CAPG,P1,CAPE,CAPH,F,AJ1,T,CAPV,CIRCM,SUM,YKM1
   integer I,K,M ! Y
   real(4),dimension(2):: G,H !Y, DIMENSION G(2),H(2),RSQ(4)
   real(4),dimension(4):: RSQ
   real(4),dimension(5):: E !Y, DIMENSION E(5),E2(10),E3(15)
   real(4),dimension(10):: E2
   real(4),dimension(15):: E3
   real(4),dimension(3):: APH1,APH2,CST,APH4,A3D8 !Y, DIMENSION APH1(3),APH2(3),CST(3)
                                                  !Y, DIMENSION APH4(3),A3D8(3)
   REAL L
   REAL KOM
   DATA PI/3.1415926535898/
   DATA TWOPI/6.28318530717958/
   DATA ALNPI/1.14472988584940/
   DATA C1/.282094791773877/
   DATA C2/.159154943091895/
   DATA TAU/7.E-14/
   DATA TAUSQ/4.9E-27/
   DATA (E(I),I=1,5)/ &
   & .885777518572895E+00,-.981151952778050E+00, &
   & .759305502082485E+00,-.353644980686977E+00, &
   & .695232092435207E-01/
   DATA (E2(I),I=1,10)/ &
   & .886226470016632E+00,-.999950714561036E+00, &
   & .885348820003892E+00,-.660611239043357E+00, &
   & .421821197160099E+00,-.222898055667208E+00, &
   & .905057384150449E-01,-.254906111884287E-01, &
   & .430895168984138E-02,-.323377239693247E-03/
   DATA (E3(I),I=1,15)/ &
   & .886226924931465E+00,-.999999899776252E+00, &
   & .886223733186722E+00,-.666626670510907E+00, &
   & .442851899328569E+00,-.265638206366025E+00, &
   & .145060043403014E+00,-.714909837799889E-01, &
   & .309199295521210E-01,-.112323532148441E-01, &
   & .324944543171185E-02,-.704260243309096E-03, &
   & .105787574480633E-03,-.971864864160461E-05, &
   & .408335517232165E-06/
   DATA (APH1(I),I=1,3)/ 2.02E-7,2.08E-13,2.71E-19/
   DATA (APH2(I),I=1,3)/ 1.22E-2,1.23E-4,1.34E-6/
   DATA (APH4(I),I=1,3)/ .6962E-1, .6990E-2, .7311E-3/
   DATA RTPII/.56418958354776/
   DATA (RSQ(I),I=1,3)/ 6.0516,12.60605,19.201924/
   DATA (A3D8(I),I=1,3)/ 0.28125E-4,0.285E-7,0.32625E-10/
   DATA (CST(I),I=1,3)/ .5625E-4,.57E-7,.6512E-10/

   real(4),dimension(N+1):: X,Y ! Y, 2016-1-27
   X(1:N)=XX(1:N) ! Y, 2016-1-27
   Y(1:N)=YY(1:N) ! Y, 2016-1-27
   print *, "VALR2()"

   IF (N.NE.2.AND.N.GE.1) GO TO 3011 !Y, check min. polygon corner N>=3 (triangle)
   IND=3

! F-6

   RETURN
3011 CONTINUE
   P=0.
   IND=0
   A=0.
   KOM=0.
   K=1
   IF (N.NE.1) GO TO 3021
   W=X(2)-X(1)
   Z=Y(2)-Y(1)
   U=X(3)-X(1)
   V=Y(3)-Y(1)
   PSI1=V*W-U*Z
   IF (PSI1.GE.0.) GO TO 3041
   P=-1.
   T1=W
   W=U
   U=T1
   T1=V
   V=Z
   Z=T1
   GO TO 3041
3021 CONTINUE
   Y(N+1)=Y(1)
   X(N+1)=X(1)
   U=X(2)-X(1)
   V=Y(2)-Y(1)
   XK=X(1)
   YK=Y(1)
3031 CONTINUE
   W=X(1)-X(N)
   Z=Y(1)-Y(N)
3041 CONTINUE
   D1SQ=W*W+Z*Z
   IF (D1SQ.GT.TAUSQ) GO TO 3051
   IF (N.EQ.1) GO TO 4011
   N=N-1
   IF (N.EQ.2) RETURN
   GO TO 3031
3051 CONTINUE
   D2SQ=U*U+V*V
   IF (D2SQ.GT.TAUSQ) GO TO 3071
   IF (N.EQ.1) GO TO 4011
3061 CONTINUE
   K=K+1
   U=X(K+1)-XK
   V=Y(K+1)-YK
   D2SQ=U*U+V*V

! F-7

   IF (D2SQ.LE.TAUSQ) GO TO 3061
   IF (K.EQ.(N-1)) RETURN
3071 CONTINUE
   A=XK*(Y(K+1)-Y(N))
   BGD1=SQRT(2.*D1SQ)
   BGD2=SQRT(2.*D2SQ)
3081 CONTINUE
   PSI1=V*W-U*Z
   CEE=U*W+V*Z
   AJ0=ATAN2(PSI1,CEE)
print *,"VALR2_3081 (36) K=",K,", AJ0(delta_theta_k)=",AJ0
   KOM=KOM+AJ0
   L=0.
   B=.5*(X(K)*X(K)+Y(K)*Y(K))
   IF (B.GT.APH1(IOP)) GO TO 3111
   CAPG=0.
3101 CONTINUE
   P1=AJ0/TWOPI-CAPG
print *,"VALR2_3101 (2) K=",K,", P1=",P1
   GO TO 3621
3111 CONTINUE
   G(1)=(W*X(K)+Z*Y(K))/BGD1
   G(2)=(U*X(K)+V*Y(K))/BGD2
   H(1)=(-Y(K)*W+X(K)*Z)/BGD1
   H(2)=(-Y(K)*U+X(K)*V)/BGD2
   IF (ABS(PSI1).GT.(BGD1*BGD2*A3D8(IOP))) GO TO 3241
   IF (CEE.LT.0.) GO TO 3131
   IF (ABS(AJ0).LE.TAU) GO TO 3121
   IF (G(1).GE.0.) GO TO 3121
   GO TO 3241
3121 CONTINUE
   P1=0.
   GO TO 3621
3131 CONTINUE
   IF (ABS(PSI1).LE.(.5*TAU*BGD1*BGD2)) IND=2
   IF (PSI1.LT.0.) GO TO 3171
   P1=.5*ERFC1(0,H(2))
   GO TO 3621
3171 CONTINUE
   P1=-.5*ERFC1(0,H(1))
   GO TO 3621
3241 CONTINUE
   IF (B.LE.APH2(IOP)) GO TO 3301
   IF (G(1).LT.0.) GO TO 3261
   IF (G(2).GE.0.) GO TO 3471
   G(2)=-G(2)
   H(2)=-H(2)
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3251
   L=.5*ERFC1(0,-H(2))
   GO To 3461

! F-8

3251 CONTINUE
   L=.5+RTPII*H(2)
   GO TO 3461
3255 CONTINUE
   L=.5-RTPII*H(1)
   GO TO 3461
3261 CONTINUE
   G(1)=-G(1)
   H(1)=-H(1)
   IF (G(2).LT.0.) GO TO 3271
   IF (ABS(H(1)).LE.APH4(IOP)) GO TO 3255
   L=.5*ERFC1(0,H(1))
   GO TO 3461
3271 CONTINUE
   G(2)=-G(2)
   H(2)=-H(2)
   IF (ABS(H(1)).LE.APH4(IOP)) GO TO 3291
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3281
   L=.5*(ERFC1(0,H(1))-ERFC1(0,H(2)))
   GO TO 3471
3281 CONTINUE
   L=RTPII*H(2)-.5*ERF1(H(1))
   GO TO 3471
3291 CONTINUE
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3295
   L=.5*ERF1(H(2))-RTPII*H(1)
   GO TO 3471
3295 CONTINUE
   L=RTPII*(H(2)-H(1))
   GO TO 3471
3301 CONTINUE
   CAPG=C1*(H(2)-H(1))-C2*(G(2)*H(2)-G(1)*H(1))
   GO TO 3101
3461 CONTINUE
   PSI1=-PSI1
   IF (PSI1.LE.0.) GO TO 3465
   L=L-1.
   AJ0=PI+AJ0
   GO TO 3471
3465 CONTINUE
   AJ0=AJ0-PI
3471 CONTINUE
   IF (B.GE.RSQ(IOP)) GO TO 3501
   CAPE=AJ0
   CAPH=.5*AJ0
   M=1
   F=0.
   AJ1=H(2)-H(1)

! F-9

   CIRCM=AJ1
   IF (IOP.EQ.3) GO TO 3681
   IF (IOP.EQ.2) GO TO 3701
   SUM=E(M)*AJ1
3481 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E(M)*CAPV
   IF (M.GE.5) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3481
3491 CONTINUE
   P1=L+EXP(-(B+ALNPI))*(CAPH-SUM)
print *,"VALR2_3491 (47) K=",K,", P1=",P1
   GO TO 3621
3501 CONTINUE
   P1=L
3621 CONTINUE
   IF (K.NE.N) GO TO 3651
   IF (N.NE.1) GO TO 3631
   P=ABS(P+ABS(P1))
   RETURN
3631 CONTINUE
   P=P-P1
   KOM=KOM/TWOPI
   A=.5*A
   IF (KOM.LT.0.) GO TO 3641
   KO=INT(KOM+.125)
   GO TO 3645
3641 CONTINUE
   KO=INT(KOM-.125)
3645 CONTINUE !Y, Exit if succeeded
   P=P+FLOAT(KO)
   RETURN
3651 CONTINUE
   W=U
   Z=V
   BGD1=BGD2
   XK=X(K+1)
   YK=Y(K+1)
   YKM1=Y(K)
3661 CONTINUE
   K=K+1
   U=X(K+1)-XK

! F-10

   V=Y(K+1)-YK
   D2SQ=U*U+V*V
   IF (D2SQ.LE.TAUSQ) GO TO 3661
   BGD2=SQRT(2.*D2SQ)
   P=P-P1
   A=A+XK*(Y(K+1)-YKM1)
   GO TO 3081
3681 CONTINUE
   SUM=E3(M)*AJ1
3691 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E3(M)*CAPV
   IF (M.GE.15) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3691
3701 CONTINUE
   SUM=E2(M)*AJ1
3711 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E2(M)*CAPV
   IF (M.GE.10) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3711
4011 CONTINUE
   P=.5
   IND=1
   RETURN

END

! F-11

FUNCTION ERF1(X)

   DIMENSION A(4),B(4),P(8),Q(8),R(5),S(5)
   DATA A/2.42667955230532E02, 2.19792616182942E01, &
   &      6.99638348861914E00,-3.56098437018154E-2/
   DATA B/2.15058875869861E02, 9.11649054045149E01, &
   &      1.50827976304078E01, 1.00000000000000E00/
   DATA P/3.00459261020162E02, 4.51918953711873E02, &
   &      3.39320816734344E02, 1.52989285046940E02, &
   &      4.31622272220567E01, 7.21175825088309E00, &
   &      5.64195517478974E-1,-1.36864857382717E-7/
   DATA Q/3.00459260956983E02, 7.90950925327898E02, &
   &      9.31354094850610E02, 6.38980264465631E02, &
   &      2.77585444743988E02, 7.70001529352295E01, &
   &      1.27827273196294E01, 1.00000000000000E00/
   DATA R/2.99610707703542E-3, 4.94730910623251E-2, &
   &      2.26956593539687E-1, 2.78661308609648E-1, &
   &      2.23192459734185E-2/
   DATA S/1.06209230528468E-2, 1.91308926107830E-1, &
   &      1.05167510706793E00, 1.98733201817135E00, &
   &      1.00000000000000E00/
   DATA C/5.64189583547756E-1/

   AX=ABS(X)
   X2=AX*AX
   IF (AX.GE.0.5) GO TO 20
   TOP=A(4)
   BOT=B(4)
   DO 10 I=1,3
   J=4-I
   TOP=A(J)+X2*TOP
10 BOT=B(J)+X2*BOT
   ERF1=X*TOP/BOT
   RETURN
20 IF (AX.GT.4.0) GO TO 30
   TOP=P(8)
   BOT=Q(8)
   DO 21 I=1,7
   J=8-I
   TOP=P(J)+AX*TOP
21 BOT=Q(J)+AX*BOT
   ERF1=1.-EXP(-X2)*TOP/BOT
   IF (X.LT.0.) ERF1=-ERF1
   RETURN
30 ERF1=1.
   IF (AX.GE.5.54) GO TO 32
   TOP=R(1)

! F-12

   BOT=S(1)
   DO 31 I=2,5
   TOP=R(I)+X2*TOP
31 BOT=S(I)+X2*BOT
   ERF1=C-TOP/(X2*BOT)
   ERF1=1.-EXP(-X2)*ERF1/AX
32 IF (X.LT.0.) ERF1=-ERF1
   RETURN

END

! F-13

FUNCTION ERFC1(IND,X)

   DIMENSION A(4),B(4),P(8),Q(8),R(5),S(5)
   DATA A/2.42667955230532E02, 2.19792616182942E01, &
   &      6.99638348861914E00,-3.56098437018154E-2/
   DATA B/2.15058875869861E02, 9.11649054045149E01, &
   &      1.50827976304078E01, 1.00000000000000E00/
   DATA P/3.00459261020162E02, 4.51918953711873E02, &
   &      3.39320816734344E02, 1.52989285046940E02, &
   &      4.31622272220567E01, 7.21175825088309E00, &
   &      5.64195517478974E-1,-1.36864857382717E-7/
   DATA Q/3.00459260956983E02, 7.90950925327898E02, &
   &      9.31354094850610E02, 6.38980264465631E02, &
   &      2.77585444743988E02, 7.70001529352295E01, &
   &      1.27827273196294E01, 1.00000000000000E00/
   DATA R/2.99610707703542E-3, 4.94730910623251E-2, &
   &      2.26956593539687E-1, 2.78661308609648E-1, &
   &      2.23192459734185E-2/
   DATA S/1.06209230528468E-2, 1.91308926107830E-1, &
   &      1.05167510706793E00, 1.98733201817135E00, &
   &      1.00000000000000E00/
   DATA C/5.64189583547756E-1/

   AX=ABS(X)
   X2=AX*AX
   IF (AX.GE.0.47) GO TO 20
   TOP=A(4)
   BOT=B(4)
   DO 10 I=1,3
   J=4-I
   TOP=A(J)+X2*TOP
10 BOT=B(J)+X2*BOT
   ERFC1=1.-X*TOP/BOT
   IF (IND.NE.0) ERFC1=EXP(X2)*ERFC1
   RETURN
20 IF (AX.GT.4.0) GO TO 30
   TOP=P(8)
   BOT=Q(8)
   DO 21 I=1,7
   J=8-I
   TOP=P(J)+AX*TOP
21 BOT=Q(J)+AX*BOT
   ERFC1=TOP/BOT
   IF (IND.EQ.0) GO TO 22
   IF (X.LT.0.0) ERFC1=2.*EXP(X2)-ERFC1
   RETURN
22 ERFC1=EXP(-X2)*ERFC1
   IF (X.LT.0.0) ERFC1=2.-ERFC1

! F-14

   RETURN
30 IF (X.LE.-5.33) GO TO 32
   TOP=R(1)
   BOT=S(1)
   DO 31 I=2,5
   TOP=R(I)+X2*TOP
31 BOT=S(I)+X2*BOT
   ERFC1=(C-TOP/(X2*BOT))/AX
   IF (IND.EQ.0) GO TO 22
   IF (X.LT.0.0) ERFC1=2.*EXP(X2)-ERFC1
   RETURN
32 ERFC1=2.
   IF (IND.NE.0) ERFC1=EXP(X2)*ERFC1
   RETURN

END

! F-15

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

! F-16

SUBROUTINE SORT3(X,Y,N)

   implicit none !Y
   real(4),dimension(N):: X,Y !Y !DIMENSION X(1),Y(1)
   integer N !Y
   real(4) CST,U,V,D2,W,Z,D1,T,SN !Y
   integer K,L,LM2,I1,I,KP1,I2 !Y
   DATA CST/4.9E-27/

3041 CONTINUE
   IF (N.LT.3) RETURN
   K=1
   L=2
3051 CONTINUE
   U=X(1)-X(N)
   V=Y(1)-Y(N)
   D2=U*U+V*V
   IF (D2.GT.CST) GO TO 3061
   N=N-1
   IF (N.GT.2) GO TO 3051
   RETURN
3061 CONTINUE
   W=X(L)-X(1)
   Z=Y(L)-Y(1)
   D1=W*W+Z*Z
   IF (D1.GT.CST) GO TO 3071
   L=L+1
   GO TO 3061
3071 CONTINUE
   IF (L.EQ.(K+1)) GO TO 3091
   LM2=L-2
   N=N-LM2
   DO 3081 I=2,N
   I1=LM2+I
   X(I)=X(I1)
   Y(I)=Y(I1)
3081 CONTINUE
   L=2
3091 CONTINUE
   T=V*W-U*Z
   SN=(4.*T*T)/(D1*D2)
   IF (SN.GT.CST) GO TO 3121
3111 CONTINUE
   L=L+1
   IF (L.GT.N) GO TO 3341
3115 CONTINUE
   W=X(1)-X(1)
   Z=Y(1)-Y(1)
   D1=W*W+Z*Z
   IF (D1.GT.CST) GO TO 3091
   GO TO 3111
3121 CONTINUE
   IF (L.EQ.2) GO TO 3141
   LM2=L-2

! F-17

   N=N-LM2
   DO 3131 I=1,N
   I1=LM2+I
   X(I)=X(I1)
   Y(I)=Y(I1)
3131 CONTINUE
   GO TO 3041
3141 CONTINUE
   K=2
   L=3
   GO TO 3161
3151 CONTINUE
   D1=D2
   W=U
   Z=V
3155 CONTINUE
   L=K+1
3161 CONTINUE
   U=X(L)-X(K)
   V=Y(L)-Y(K)
   D2=U*U+V*V
   IF (D2.GT.CST) GO TO 3171
3165 CONTINUE
   L=L+1
   IF (L.LE.N) GO TO 3161
   N=K
   GO TO 3251
3171 CONTINUE
   IF (L.EQ.(K+1)) GO TO 3191
   N=N-((L-1)-K)
   KP1=K+1
   I2=L-KP1
   DO 3181 I=KP1,N
   I1=I2+I
   X(I)=X(I1)
   Y(I)=Y(I1)
3181 CONTINUE
   L=KP1
3191 CONTINUE
   T=V*W-U*Z
   SN=(4.*T*T)/(D1*D2)
   IF (SN.GT.CST) GO TO 3221
3201 CONTINUE
   L=L+1
   IF (L.GT.N) GO TO 3211
   U=X(L)-X(K)
   V=Y(L)-Y(K)
   D2=U*U+V*V

! F-18

   IF (D2.GT.CST) GO TO 3191
   GO TO 3201
3211 CONTINUE
   X(K)=X(N)
   Y(K)=Y(N)
   N=K
   GO TO 3251
3221 CONTINUE
   IF (L.EQ.(K+1)) GO TO 3241
   I2=L-1-K
   N=N-I2
   LM2=L-2
   DO 3231 I=K,N
   I1=I2+I
   X(I)=X(I1)
   Y(I)=Y(I1)
3231 CONTINUE
   W=X(K)-X(K-1)
   Z=Y(K)-Y(K-1)
   D1=W*W+Z*Z
   IF (D1.GT.CST) GO TO 3155
   K=K-1
   IF (K.LT.2) GO TO 3041
   W=X(K)-X(K-1)
   Z=Y(K)-Y(K-1)
   D1=W*W+Z*Z
   L=K+1
   GO TO 3165
3241 CONTINUE
   K=K+1
   IF (K.LT.N) GO TO 3151
   GO TO 3255
3251 CONTINUE
   U=X(N)-X(N-1)
   V=Y(N)-Y(N-1)
   D2=U*U+V*V
   IF (D2.LE.CST) GO TO 3261
3255 CONTINUE
   W=X(1)-X(N)
   Z=Y(1)-Y(N)
   D1=W*W+Z*Z
   IF (D1.LE.CST) GO TO 3261
   T=V*W-U*Z
   SN=(4.*T*T)/(D1*D2)
   IF (SN.GT.CST) GO TO 3351
3261 CONTINUE
   N=N-1
   IF (N.GT.2) GO TO 3251

! F-19

   RETURN
3341 CONTINUE
   N=2
   RETURN
3351 CONTINUE
   D2=D1
   U=W
   V=Z
   W=X(2)-X(1)
   Z=Y(2)-Y(1)
   D1=W*W+Z*Z
   T=V*W-U*Z
   SN=(4.*T*T)/(D1*D2)
   IF (SN.GT.CST) RETURN
   L=3
   GO TO 3115

END

! F-20

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

! F-21

SUBROUTINE VALR7(XX,YY,N,P,IOP,A,IND)

   !implicit none
   real(4),dimension(N):: XX,YY ! Y, !DIMENSION X(1),Y(1)
   real(4) P,A,W,Z,U,V,PSI1,T1,T2,BGD1,BGD2,B ! Y
   real(4),dimension(4):: RSQ !Y !DIMENSION RSQ(4)
   real(4),dimension(2):: G,H !Y !DIMENSION G(2),H(2)
   real(4),dimension(5):: E !Y !DIMENSION E(5),E2(10),E3(15)
   real(4),dimension(10):: E2 !Y !DIMENSION E(5),E2(10),E3(15)
   real(4),dimension(15):: E3 !Y !DIMENSION E(5),E2(10),E3(15)
   real(4),dimension(3):: APH1,APH2,APH4,CST !Y !DIMENSION APH1(3),APH2(3),APH4(3),CST(3)
   real(4) TWOPI,ALNPI,C1,C2,TAU,RTPII,CAPG,PHIK,P1,SN,CN,AJ0,CAPE,CAPH,F,CIRCM,AJ1,SUM,T,CAPV !Y
   integer I,IND,K,M !Y
   REAL L
   DATA TWOPI/6.28318530717958/
   DATA ALNPI/1.14472988584940/
   DATA C1/.282094791773877/
   DATA C2/.159154943091895/
   DATA TAU/7.E-14/
   DATA (E(I),I=1,5)/ &
   & .885777518572895E+00, -.981151952778050E+00, &
   & .759305502082485E+00, -.353644980686977E+00, &
   & .695232092435207E-01/
   DATA (E2(I),I=1,10)/ &
   & .886226470016632E+00, -.999950714561036E+00, &
   & .885348820003892E+00, -.660611239043357E+00, &
   & .421821197160099E+00, -.222898055667208E+00, &
   & .905057384150449E-01, -.254906111884287E-01, &
   & .430895168984138E-02, -.323377239093247E-03/
   DATA (E3(I),I=1,15)/ &
   & .886226924931465E+00, -.999999899776252E+00, &
   & .886223733186722E+00, -.666626670510907E+00, &
   & .442851899328569E+00, -.265638206366025E+00, &
   & .145060043403014E+00, -.714909837799889E-01, &
   & .309199295521210E-01, -.112323532148441E-01, &
   & .324944543171185E-02, -.704260243309096E-03, &
   & .105787574480633E-03, -.971864864160461E-05, &
   & .408335517232165E-06/
   DATA (APH1(I),I=1,3)/ 2.02E-7,2.08E-13,2.71E-19/
   DATA (APH2(I),I=1,3)/ 1.22E-2,1.23E-4,1.34E-6/
   DATA (APH4(I),I=1,3)/.6962E-1, .6990E-2, .7311E-3/
   DATA RTPII/.56418958354776/
   DATA (RSQ(I),I=1,3)/ 6.0516,12.60605,19.201924/
   DATA (CST(I),I=1,3)/ .5625E-4,.57E-7,.6512E-10/

   real(4),dimension(N+1):: X,Y ! Y, 2016-1-27
   X(1:N)=XX(1:N) ! Y, 2016-1-27
   Y(1:N)=YY(1:N) ! Y, 2016-1-27
   print *, "VALR2()"


   IF (N.NE.2.AND.N.GE.1) GO TO 3061
   IND=3
   RETURN
3061 CONTINUE
   P=0.
   IND=0
   IF (N.NE.1) GO TO 3071

! F-22

   K=1
   A=0.
   W=X(2)-X(1)
   Z=Y(2)-Y(1)
   U=X(3)-X(1)
   V=Y(3)-Y(1)
   PSI1=V*W-U*Z
   IF (PSI1.GE.0.) GO TO 3081
   P=-1.
   T1=W
   W=U
   U=T1
   T1=V
   V=Z
   Z=T1
   GO TO 3081
3071 CONTINUE
   CALL SMP7(N,A,X,Y) ! Y, Calculate polygon area only at this step
   IF (ABS(A).LE.CST(IOP)) RETURN
   K=1
   W=X(1)-X(N)
   Z=Y(1)-Y(N)
   U=X(2)-X(1)
   V=Y(2)-Y(1)
   X(N+1)=X(1)
   Y(N+1)=Y(1)
3081 CONTINUE
   BGD1=SQRT(2.*(W*W+Z*Z))
   BGD2=SQRT(2.*(U*U+V*V))
3091 CONTINUE
   L=0.
   B=.5*(X(K)*X(K)+Y(K)*Y(K))
   IF (B.GT.APH1(IOP)) GO TO 3111
   CAPG=0.
3101 CONTINUE
   T1=V*W-U*Z
   T2=U*W+V*Z
   PHIK=ATAN2(T1,T2)
   P1=PHIK/TWOPI-CAPG
   GO TO 3621
3111 CONTINUE
   G(1)=(W*X(K)+Z*Y(K))/BGD1
   G(2)=(U*X(K)+V*Y(K))/BGD2
   H(1)=(-Y(K)*W+X(K)*Z)/BGD1
   H(2)=(-Y(K)*U+X(K)*V)/BGD2
   SN=(2.*(V*W-U*Z))/(BGD1*BGD2)
   IF (ABS(SN).GT.CST(IOP)) GO TO 3241
   CN=G(1)*G(2)+H(1)*H(2)

! F-23

   IF (CN.LT.0.) GO TO 3131
   IF (ABS(SN).LE.TAU) GO TO 3121
   IF (G(1).GE.0.) GO TO 3121
   GO TO 3241
3121 CONTINUE
   P1=0.
   GO TO 3621
3131 CONTINUE
   IF (ABS(SN).LE.TAU) IND=2
   IF (SN .LT.0.) GO TO 3171
   P1=.5*ERFC1(0,H(2))
   GO TO 3621
3171 CONTINUE
   P1=-.5*ERFC1(0,H(1))
   GO TO 3621
3241 CONTINUE
   IF (B.LE.APH2(IOP)) GO TO 3301
   SN=B*SN
   IF (G(1).LT.0.) GO TO 3261
   IF (G(2).GE.0.) GO TO 3471
   G(2)=-G(2)
   H(2)=-H(2)
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3251
   L=.5*ERFC1(0,-H(2))
   GO TO 3461
3251 CONTINUE
   L=.5+RTPII*H(2)
   GO TO 3461
3255 CONTINUE
   L=.5-RTPII*H(1)
   GO TO 3461
3261 CONTINUE
   G(1)=-G(1)
   H(1)=-H(1)
   IF (G(2).LT.0.) GO TO 3271
   IF (ABS(H(1)).LE.APH4(IOP)) GO TO 3255
   L=.5*ERFC1(0,H(1))
   GO TO 3461
3271 CONTINUE
   G(2)=-G(2)
   H(2)=-H(2)
   IF (ABS(H(1)).LE.APH4(IOP)) GO TO 3291
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3281
   L=.5*(ERFC1(0,H(1))-ERFC1(0,H(2)))
   GO TO 3471
3281 CONTINUE
   L=RTPII*H(2)-.5*ERF1(H(1))
   GO TO 3471

! F-24

3291 CONTINUE
   IF (ABS(H(2)).LE.APH4(IOP)) GO TO 3295
   L=.5*ERF1(H(2))-RTPII*H(1)
   GO TO 3471
3295 CONTINUE
   L=RTPII*(H(2)-H(1))
   GO TO 3471
3301 CONTINUE
   CAPG=C1*(H(2)-H(1))-C2*(G(2)*H(2)-G(1)*H(1))
   GO TO 3101
3461 CONTINUE
   SN=-SN
   IF (SN.LE.0.) GO TO 3471
   L=L-1.
3471 CONTINUE
   IF (B.GE.RSQ(IOP)) GO TO 3501
   CN=G(1)*G(2)+H(1)*H(2)
   AJ0=ATAN2(SN,CN)
   CAPE=AJ0
   CAPH=.5*AJ0
   M=1
   F=0.
   AJ1=H(2)-H(1)
   CIRCM=AJ1
   IF (IOP.EQ.3) GO TO 3681
   IF (IOP.EQ.2) GO TO 3701
   SUM=E(M)*AJ1
3481 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E(M)*CAPV
   IF (M.GE.5) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3481
3491 CONTINUE
   P1=L+EXP(-(B+ALNPI))*(CAPH-SUM)
   GO TO 3621
3501 CONTINUE
   P1=L
3621 CONTINUE
   IF (K.NE.N) GO TO 3651
   IF (N.NE.1) GO TO 3631
   P=ABS(P+ABS(P1))

! F-25

   RETURN
3631 CONTINUE
   P=P-P1
   IF (A.LT.0.) GO TO 3641
   P=P+1.
   RETURN
3641 CONTINUE
   P=P-1.
   RETURN
3651 CONTINUE
   K=K+1
   W=U
   Z=V
   U=X(K+1)-X(K)
   V=Y(K+1)-Y(K)
   BGD1=BGD2
   BGD2=SQRT(2.*(U*U+V*V))
   P=P-P1
   print *,"VALR7_3651 P=",P
   GO TO 3091
3681 CONTINUE
   SUM=E3(M)*AJ1
3691 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E3(M)*CAPV
   IF (M.GE.15) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3691
3701 CONTINUE
   SUM=E2(M)*AJ1
3711 CONTINUE
   M=M+1
   H(2)=H(2)*G(2)
   H(1)=H(1)*G(1)
   T=H(2)-H(1)
   F=F+B
   CAPV=(F*CAPE+T)/M
   SUM=SUM+E2(M)*CAPV
   IF (M.GE.10) GO TO 3491
   CAPE=CIRCM
   CIRCM=CAPV
   GO TO 3711

END

! F-26

! F-27

! F-28

SUBROUTINE P7(X,Y,NB,P,ICV,IND,IOP,A)

   !DIMENSION X(1),Y(1)
   real (kind=4), dimension(1:NB) :: X,Y ! Y
   IF (NB.NE.2.AND.NB.GE.1) GO TO 3031
   IND=3
   RETURN
3031 CONTINUE
   N=NB
   IF (N.EQ.1) GO TO 3041
   IF (ICV.EQ.0) GO TO 3041
   IF (ICV.EQ.1) GO TO 3061
   CALL SORT1(X,Y,N,P,ICV,IND,IOP,A)
   RETURN
3041 CONTINUE
   CALL VALR7(X,Y,N,P,IOP,A,IND)
   RETURN
3061 CONTINUE
   CALL SORT3(X,Y,N)
   IF (N.GT.2) GO TO 3071
   A=0.
   IND=0
   P=0.
   RETURN
3071 CONTINUE
   CALL VALR7(X,Y,N,P,IOP,A,IND)
   RETURN

END

! F-29

! F-30

! F-31

SUBROUTINE SORT1(X,Y,N,P,ICV,IND,IOP,A)
DIMENSION X(1),Y(1)
DATA CST/5.E-14/
P=0.
A=0.
IC=IABS(ICV)
IF (ABS(X(N)-X(1)).GT.CST) GO TO 2311
IF (ABS(Y(N)-Y(1)).GT.CST) GO TO 2311
GO TO 2321
2311 CONTINUE
N=N+1
2321 CONTINUE
X(N)=X(1)
Y(N)=Y(1)
JIST=2
I1=2
2331 CONTINUE
IF (ICV.GT.0) GO TO 2361
NUMP1=N+I  ! +1 ????
DO 2351 J1=J1ST,N
J=NUMP1-J1
JP1=J+1
DO 2341 K=JP1,N
IF (ABS(X(J)-X(K)).GT.CST) GO TO 2341
IF (ABS(Y(J)-Y(K)).GT.CST) GO TO 2341
IST=J
IEN=K
J1ST=N-K+I   ! +1` ????
IF (K.EQ.N) J1ST=2
LST=IST+1
GO TO 2531
2341 CONTINUE
2351 CONTINUE
2361 CONTINUE
DO 2521 I=I1,N
IM1=I-1
DO 2511 K1=1,IM1
K=I-K1
IF (ABS(X(I)-X(K)).GT.CST) GO TO 2511
IF (ABS(Y(I)-Y(K)).GT.CST) GO TO 2511
IST=K
IEN=I
I1=K
LST=IST
IF (K.NE.1) GO TO 2531
Il=2
LST=LST+1
GO TO 2531

! F-32

2511 CONTINUE
2521 CONTINUE
2531 CONTINUE
NUM1=IEN-IST
NSAV=NUM1
IF ( NUM1.LE.2 ) GO TO 2575
IF ( IC.EQ.2 ) GO TO 2565
CALL SORT2 ( X (IST),Y (IST),NUM1)
IF (NUM1.LT.3) GO TO 2575
2565 CONTINUE
CALL VALR7(X(IST),Y(IST),NUM1,SMP,IOP,SMA,IND)
IF (IND.EQ.2) RETURN
A=A+SMA
P=P+SMP
X(IST)=X(IEN)
Y(IST)=Y(IEN)
2575 CONTINUE
IF (IEN.NE.N) GO TO 2577
IF (IST.EQ.1) RETURN
X(IST)=X(N)
Y(IST)=Y(N)
N=IST
GO TO 2331
2577 CONTINUE
N=N-NSAV
DO 2581 L=LST,N
K=L+NSAV
X(L)=X(K)
Y(L)=Y(K)
2581 CONTINUE
GO TO 2331
END

! F-33

! F-34

SUBROUTINE SORT2(X,Y,N)
DIMENSION X(1),Y(1)
DATA CST/4.9E-27/
K=l
L=2
U=X(1)-X(N)
V=Y(1)-Y(N)
D2=U*U+V*V
3051 CONTINUE
W=X(1)-X(1)
Z=Y(1)-Y(1)
Dl=W*W+Z*Z
T=V*W-U*Z
SN=(4.*T*T)/(D1*D2)
IF (SN.GT.CST) GO TO 3071
L=L+1
IF (L.LT.N) GO TO 3051
N=2
RETURN
3071 CONTINUE
K=2
IF (L.NE.2) GO TO 3081
L=3
GO TO 3111
3081 CONTINUE
LM2=L-2
N=N-(LM2)
DO 3091 I=1,N
I1=LM2+I
X(I)=X(I1)
Y(I)=Y(I1)
3091 CONTINUE
3101 CONTINUE
L=K+1
W=X(K)-X(K-1)
Z=Y(K)-Y(K-1)
D1=W*W+Z*Z
3111 CONTINUE
U=X(L)-X(K)
V=Y(L)-Y(K)
D2=U*U+V*V
T=V*W-U*Z
SN=(4.*T*T)/(Dl*D2)
IF (SN.GT.CST) GO TO 3121
L=L+1
IF (L.LE.N) GO TO 3111
X(K)=X(N)
Y(K)=Y(N)

! F-35

N=K
GO TO 3151
3121 CONTINUE
IF (L.EQ.(K+I)) GO TO 3171   ! +1 ???
LM2=L-2
I3=LM2-(K-1)
N=N-13
DO 3131 I=K,N
I1=I3+I
X(I)=X(I1)
Y(I)=Y(I1)
3131 CONTINUE
K=K+1
IF (K.LT.N) GO TO 3101
3151 CONTINUE
U=X(N)-X(N-1)
V=Y(N)-Y(N-1)
D2=U*U+V*V
3161 CONTINUE
W=X(1)-X(N)
Z=Y(1)-Y(N)
D1=W*W+Z*Z
T=V*W-U*Z
SN=(4.*T*T)/(DI*D2)
IF (SN.LE.CST) GO TO 3165
RETURN
3165 CONTINUE
N=N-1
RETURN
3171 CONTINUE
K=K+1
IF (K.GE.N) GO TO 3161
DI=D2
W=U
Z=V
L=K+I   ! +1 ????
GO TO 3111
END

! F-36

! SUBROUTINE SMP-7
! (No flow chart given)
! SMP-7 is Used to Compute the a-Function*
! CALL: SMP-7 (M, a, x, y),
! where:
! M is the number of input points specifying the polygon.
! a is the location to which the a-function is returned.
! x is the array of input abscissas. Dimensioned at M.
! y is the array of input ordinates. Dimensioned at M.

! F-37

SUBROUTINE SMP7(NB,ANS,X,Y)

   implicit none ! Y
   real (kind=4), dimension(1:NB) :: X,Y ! Y !DIMENSION X(1),Y(1)
   real (kind=4) ::ANS ! Y
   integer :: NB,NBM1,I ! Y

   !print *,"SMP7() ",X,Y,NB

   IF (NB.GT.3) GO TO 3151
   ANS=.5*((X(2)-X(1))*(Y(3)-Y(1))-(X(3)-X(1))*(Y(2)-Y(1)))
   RETURN
3151 CONTINUE
   NBM1=NB-1
   ANS=X(1)*(Y(2)-Y(NB))+X(NB)*(Y(1)-Y(NBM1))
   DO 3161 I=2,NBM1
   ANS=ANS+X(I)*(Y(I+1)-Y(I-1))
   3161 CONTINUE
   ANS=.5*ANS
   RETURN

END

! F-38

! G-1

! G-2

! G-3

SUBROUTINE DZ(X,Y,N,ANS,A,IOP)
DIMENSION X(3),Y(3),U(3),V(3) ! DIMENSION X(1),Y(1),U(4),V(4)
A=0.
ANS=0.
IF (N.NE.1) GO TO 3031
CALL DZ1(X,Y,N,ANS,IOP,A)
RETURN
3031 CONTINUE
IF (N.LT.3) RETURN
L=3
U(1)=X(1)
U(2)=X(2)
U(3)=X(3)
V(1)=Y(1)
V(2)=Y(2)
V(3)=Y(3)
3041 CONTINUE
CALL DZ1(U,V,3,ANS1,IOP,Al)
A=A+A1
ANS=ANS+ANS1
3061 CONTINUE
L=L+1
IF (L.GT.N) RETURN
U(2)=U(3)
V(2)=V(3)
U(3)=X(L)
V(3)=Y(L)
GO TO 3041
END

! G-4

! SUBROUTINE DZ-1
! Computes P(delta j) for DZ
! CALL: DZ-1 (x,y,N,P,IOP,A)
! where:
! x is the array of abscissas of the points specifying a simple polygon S.
! y is the array of ordinates of the points specifying a simple polygon S.
!   x and y are dimensoned at N+1.
! N is the number of points specifying S.
! IOP is specified by the user.
!   IOP=1 for 3-decimal-digit accuracy for P(S).
!   IOP=2 for 6-decimal-digit accuracy for P(S).
!   IOP=3 for 9-decimal-digit accuracy for P(S).
! P,A are the locations where the values of P(S) adn A(S) are returned, respectively.

! G-5

SUBROUTINE DZ1(X,Y,N,ANS,IOP,A)
DIMENSION X(3),Y(3),H(2),APH1(3)  ! X(1),Y(1)
DATA(APH1(I),I=1,3)/ 2.02E-7,2.08E-13,2.72E-19/
DATA RT2/ 1.4142135623731/
DATA TWOPI/6.28318530717958/
K=1
ANS=0.
IF (N.NE.1) GO TO 3071
W=X(2)-X(1)
Z=Y(2)-Y(1)
U=X(3)-X(1)
V=Y(3)-Y(1)
PSI1=(V*W-U*Z)
IF (PSI1.GE.0.) GO TO 3081
ANS=+1.
T1=W
W=U
U=T1
T1=V
V=Z
Z=T1
GO TO 3081
3071 CONTINUE
X(N+1)=X(1)
Y(N+1)=Y(1)
CALL SMP7(N,A,X,Y)
IF (ABS(A).LE.0.6512E-10) RETURN
W=X(1)-X(N)
Z=Y(1)-Y(N)
U=X(2)-X(1)
V=Y(2)-Y(1)
3081 CONTINUE
BGD1=SQRT(2.*(W*W+Z*Z))
BGD2=SQRT(2.*(U*U+V*V))
3151 CONTINUE
B=.5*(X(K)*X(K)+Y(K)*Y(K))
IF (B.GT.APH1(IOP)) GO TO 3155
T1=V*W-U*Z
T2=U*W+V*Z
PHIK=ATAN2(T1,T2)
ANSl=PHIK/TWOPI
GO TO 3211
3155 CONTINUE
RTR=(2.*(W*V-U*Z))/(BGD1*BGD2)
H(1)=(-Y(K)*W+X(K)*Z)/BGD1
H(2)=(-Y(K)*U+X(K)*V)/BGD2
SGN=1.

! G-6

IF (RTR.GE.0.) GO TO 3161
RTR=-RTR
SGN=-1.
H(1)=H(2)
H(2)=T1
3161 CONTINUE
AM=-RT2*H(2)
AK=RT2*H(1)
RHO=(-2.*(W*U+V*Z))/(BGD1*BGD2)
IF (ABS(RHO).LT.(1.-1.E-13)) GO TO 3181
IF (RH0.LT.0.) GO TO 3171
T1=AM
IF (AK.LE.AM)T1=AK
T2=-T1/RT2
ANSl=.5*ERFC1(0,T2)
GO TO 3191
3171 CONTINUE
ANS1=0.
IF (AK.LE.-AM) GO TO 3191
T1=-AK/RT2
T2=AM/RT2
ANS1=.5*(ERFC1(0,T1)-ERFC1(0,T2))
GO TO 3191
3181 CONTINUE
CALL PLAN(AM,AK,RHO,ANS1,IOP,RTR)
3191 CONTINUE
ANS1=SGN*ANS1
3211 CONTINUE
IF (K.NE.N) GO TO 3651
IF (N.NE.1) GO TO 3631
ANS=ABS(ANS-ABS(ANS1))
RETURN
3631 CONTINUE
ANS=ANS-ANS1
IF (A.LT.0.) GO TO 3641
ANS=ANS+1.
RETURN
3641 CONTINUE
ANS=ANS-1.
RETURN
3651 CONTINUE
K=K+1
KP1=K+1
W=U
Z=V
U=X(KP1)-X(K)
V=Y(KP1)-Y(K)
! G-7
BGD1=BGD2
BGD2=SQRT(2.*(U*U+V*V))
ANS=ANS-ANS1
GO TO 3151
END
! G-8

SUBROUTINE PLAN(H,AK,R,ANS,IOP,RTR)
ANS=0.
IF ((H*AK*R).GT.0.) GO TO 3155
IF (H.GT.0.) GO TO 2031
IF (AK.GT.0.) GO TO 2021
IF (R.GT.0.) GO TO 2011
ANS=BPHI(H,AK,R,IOP,RTR)
RETURN
2011 CONTINUE
IF (AK.NE.0.) GO TO 2061
GO TO 2023
2021 CONTINUE
IF (R.LT.0.) GO TO 2041
2023 CONTINUE
ANS=EQ9(H,AK,R,IOP,RTR)
RETURN
2031 CONTINUE
IF (AK.EQ.0.) GO TO 2051
2035 CONTINUE
IF (AK.LT.0.) GO TO 2061
2041 CONTINUE
ANS=EQ7(H,AK,R,IOP,RTR)
RETURN
2051 CONTINUE
IF (R.GT.0.) GO TO 2061
GO TO 2041
2061 CONTINUE
ANS=EQ8(H,AK,R,IOP,RTR)
RETURN
3155 CONTINUE
ANS=EQ11(H,AK,R,IOP,RTR)
RETURN
END

! G-9

FUNCTION EQ7(H,AK,R,IOP,RTR)
DATA RT2/1.4142135623731/
T=-H/RT2
T1=-AK/RT2
EQ7=BPHI(-H,-AK,R,IOP,RTR)+.5*(ERFC1(0,T)+ERFC1(0,T1))-1.
RETURN
END

FUNCTION EQ8(H,AK,R,IOP,RTR)
DATA RT2/1.4142135623731/
T=-AK/RT2
EQ8=-BPHI(-H,AK,-R,IOP,RTR)+.5*ERFC1(0,T)
RETURN
END

FUNCTION EQ9(H,AK,R,IOP,RTR)
DATA RT2 /1.4142135623731/
T=-H/RT2
EQ9=-BPHI(H,-AK,-R,IOP,RTR)+.5*ERFC1(0,T)  ! ???????
RETURN
END

! G-10

FUNCTION EQ11(H,AK,R,IOP,RTR)
DATA RT2/1.4142135623731/
CST=SQRT(H*H-2.*R*H*AK+AK*AK)
T1=R*H-AK
C1=1.
T2=SIGN(C1,H)
T1=(T1*T2)/CST
T4=1.
T3=H*AK
T5=SIGN(T4,T3)
TDEL=(1.-T5)*.25
T3=R*AK-H
T2=SIGN(C1,AK)
T3=(T3*T2)/CST
RTR1=(RTR*ABS(H))/CST
RTR3=(RTR*ABS(AK))/CST
IF (H.GT.0.) GO TO 2031
IF (T1.GT.0.) GO TO 2023
T4=BPHI(H,0.,T1,IOP,RTR1)
GO TO 2051
2023 CONTINUE
T4=EQ9(H,0.,T1,IOP,RTR1)
GO TO 2051
2031 CONTINUE
IF (T1.LT.0.) GO TO 2041
T4=.5-BPHI(-H,0.,-T1,IOP,RTR1)
GO TO 2051
2041 CONTINUE
Cl=-H/RT2
T4=BPHI(-H,0.,T1,IP,RTR1)-.5*ERF1(C1)
2051 CONTINUE
IF (AK.GT.0.) GO TO 3031
IF (T3.GT.0.) GO TO 3023
T6=BPHI(AK,0.,T3,IOP,RTR3)
GO TO 3051
3023 CONTINUE
T6=EQ9(AK,0.,T3,IOP,RTR3)
GO TO 3051
3031 CONTINUE
IF (T3.LT.0.) GO TO 3041
T6=.5-BPHI(-AK,0.,-T3,IOP,RTR3)
GO TO 3051
3041 CONTINUE
C1=-AK/RT2
T6=BPHI(-AK,0.,T3,IOP,RTR3)-.5*ERF1(C1)
3051 CONTINUE
EQ11=T4+T6-TDEL

! G-11

RETURN
END

! G-12

FUNCTION BPHI(H,AK,R,IOP,RTR)
DIMENSION A(21),X(21),LLO(6),LHI(6)
DIMENSION EPS1(11)
DIMENSION EPS3(11)
DATA(A(I),I=1,8)/ &
&   4.46029770466658E-1, 3.96468266998335E-1, &
&   4.37288879877644E-2, 2.48406152028443E-1, &
&   3.92331066652399E-1, 2.11418193076057E-1, &
&   3.32466603513439E-2, 8.24853344515628E-4/
DATA(X(I),I=1,8)/ &
&   1.90554149798192E-1, 8.48251867544577E-1, &
&   1.79977657841573E+0, 1.00242151968216E-1, &
&   4.82813966046201E-1, 1.06094982152572E+0, &
&   1.77972941852026E+0, 2.66976035608766E+0/
DATA(A(I),I=9,16)/ &
&   1.34109188453360E-1, 2.68330754472640E-1, &
&   2.75953397988422E-1, 1.57448282618790E-1, &
&   4.48141099174625E-2, 5.36793575602526E-3, &
&   2.02063649132407E-4, 1.19259692659532E-6/
DATA(X(I),I=9,16)/ &
&   5.29786439318514E-2, 2.67398372167767E-1, &
&   6.16302884182402E-1, 1.06424631211623E+0, &
&   1.58885586227006E+0, 2.18392115309586E+0, &
&   2.86313388370808E+0, 3.68600716272440E+0/
DATA(EPS1(I),I=1,3) /-8.,-12.,-20./
DATA PI/ 3.14159265358979/
DATA(LLO(I),I=1,3) / 1,4,9/
DATA(LHI(I),I=1,3) / 3,8,16/
DATA RT2/ 1.4142135623731/
DATA(EPS3(I),I=1,3)/ 2.E-5,2.E-7,2.E-10/
ILO=LLO(IOP)
IHI=LHI(IOP)
EPS=EPS1(IOP)
CST=RT2*RTR
BPHI=0.
H1=H/CST
AK1=AK/CST
SUM=0.
DO 3361 I=ILO,IHI
SUM1=0.
DO 3351 J=ILO,IHI
T1=H1*(2.*X(I)-H1)+AKI*(2.*X(J)-AK1)+2.*R*(X(I)-H1)*(X(J)-AK1)
IF (T1.LT.EPS) GO TO 3351
SUM1=SUM1+EXP(TI)*A(J)
3351 CONTINUE
SUM=SUM+A(I)*SUM1
3361 CONTINUE

! G-13

BPHI=(SUM*RTR)/PI
RETURN
END

! G-14




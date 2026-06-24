/*******************************************************************************
 Y.Kim)
 1991 or 92 ?
*******************************************************************************/

#include <math.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"

extern int Echo();

#define SCALE_LIN    0 /* plot.h */
#define SCALE_LOG10  1 /* plot.h */
#define SCALE_SERIES 2 /* plot.h */
#define SCALE_NORM   3 /* plot.h */

#define USERLIST  double **MTRX=*MTX;                                         \
                  int INDEXROW=0,INDEXCOL=0;                                  \
                  double ROWSTEPVAL=0.0,COLSTEPVAL=0.0
#define USERLISTEND INDEXROW=INDEXCOL=(int)ROWSTEPVAL=(int)COLSTEPVAL
#define USERSTEP  ROWSTEPVAL=(DRH-DRL)/(NRH-NRL);                             \
                  COLSTEPVAL=(DCH-DCL)/(NCH-NCL);

#define XLOOPBEG  for(INDEXROW=NRL;INDEXROW<=NRH;INDEXROW++){
#define YLOOPBEG  for(INDEXCOL=NCL;INDEXCOL<=NCH;INDEXCOL++){
#define XLOOPEND  }
#define YLOOPEND  }
#define LOOPBEG   YLOOPBEG;XLOOPBEG;
#define LOOPEND   XLOOPEND;YLOOPEND;
#define NRLSKIP   if(INDEXROW==NRL) INDEXROW++;
#define NCLSKIP   if(INDEXCOL==NCL) INDEXCOL++;

#define XMTRX     (MTRX[INDEXROW][NCL])
#define YMTRX     (MTRX[INDEXROW][INDEXCOL])
#define CMTRX     (MTRX[INDEXROW][INDEXCOL])

/*----------------------------------------------------------------------------*/

#define kb  1.38e-23       /* [J/K]@Boltzmann's constant */
#define q   1.60218e-19    /* [C] Electronic charge */
#define e0  8.8542e-14*1e2 /* [F/m] vacuum permittivity */
#define esi 11.7*e0        /* [F/m] silicon permittivity */
#define eox 3.9*e0         /* [F/m] oxide permittivity */

/*----------------------------------------------------------------------------*/

static 
int GetMtxMinMax( m,minvec,maxvec,nrl,nrh,ncl,nch )
   double **m,*minvec,*maxvec;
   int nrl,nrh,ncl,nch;
{
   register int i,j;

   for (j=ncl;j<=nch;j++) 
      minvec[j]=maxvec[j]=m[nrl][j];

   for (j=ncl;j<=nch;j++) {
      for (i=nrl;i<=nrh;i++) {
         if (maxvec[j]<m[i][j]) maxvec[j]=m[i][j];
         if (m[i][j]<minvec[j]) minvec[j]=m[i][j];
      }
   }
   return TRUE;
}

/*
 * Mong-Song Liang and Chenming Hu,
 * "ELECTRON TRAPPING IN VERY THIN THERAML SILICON DIOXIDES"
 * Int. Electron Dev. Meeting,Technical Digest,396-99(1981)
 */
static
double Not_t( t,J,Xo )
   double t,J,Xo;
{
   static 
   double Nop=2e12,          /* [/cm2] */
          Sp=5e-20,          /* [cm2] */
          Sg=1e-20,          /* [cm2] */
          G=4e-8,            /* [/elec.cm2] */
          Noti=0.0;
   //double Nott,Ni,Nt,F=J/q*t;
   double F=J/q*t;

   static
   double St=6.1716e-22,     /* [cm2] capture cross section */
          Ntc=1.5539e12,     /* [#/cm2] trap site */
          Nti=0.0;
/* 
 * trap centroid 60A from gate
 *   St=1.421e-22;  
 *   Ntc=1.295e12;
 * trap centroid 50A from gate    
 *   St=6.1716e-22;  
 *   Ntc=1.5539e12;
 */

/*
   if (F!=0.0) {
      Ni=-Nop+G*q/(Sg*J);
      Nt=-Nop*pow10(-Sp*F)+G*(t+q/(Sg*J)*pow10(-Sg*F));
      Noti=Nott=Nt-Ni+Noti;
   } else 
      printf("error : Fluence=0.0 in NOT_T,1\n");
   return Nott;
*/

   St=1.5800e-21;
   Ntc=3.4393e12;

   if (F!=0.0) 
      Nti=(Ntc*Xo/1e-6)*(1.0-pow10(-St*F))+Nti;
   else 
      printf("error : Fluence=0.0 in NOT_T,2\n");
   return Nti;
}
/*
 * A. Bhttacharryya,
 * "MODELLING OF WRITE/ERASE AND CHARGE RETENSION CHARACTERISTICS
 *  OF FLOATING GATE EEPROM DEVICES",
 * Solid-State Electronics,27[10]899-906(1984)
 */
/*
 * Avinoam Kolodny, Sidney T.K. Nieh, Boaz Eitan and Joseph Shappir,
 * "ANALYSIS AND MODELING OF FLOATING-GATE EEPROM CELLS",
 * IEEE Transactions On Electron Devices,VOL.ED-33,NO.6,JUNE 1986
 */
int EEPROM( ARGUMENTS )
   ARGULIST
{
   USERLIST;
   int i,j;
   double drs,dcs;

   double Aw,Bw,Ae,Be;
   double Aflt,Agso,Agdo,Agbo;
   double Cflt,Cgso,Cgdo,Cgbo;
   double Cf,Cs,Cb,Cd,Ct,Ctw,Cte,Kw,Ke,Tc;
   double t,P,Xo,Ei,Et,Vg,Vd,Vto,Vti,Vth;

   double J,Eti,Nt,Ett;
   double J_,Jmax,Ftot;
   double cycle,Vtp0,Vte0,V;
   int    DP_FOUND,DE_FOUND,WC_FOUND,BV_FOUND;

   double DCL=1; /* ???? 20021015 */
   dcs=1; /* ??? 20031209 */

/*------------------------------------------------------------------*/
/*
   if (XSCALE) {
      DRH=log10(DRH);
      DRL=log10(DRL);
   }
   if (NRH-NRL)
      drs=(float)(DRH-DRL)/(NRH-NRL);
   else 
      drs=0.0;
   if (NCH-NCL-1)
      dcs=atof(SWEEP)/(NCH-NCL-1);
   else 
      dcs=0.0;
   for (i=NRL;i<=NRH;i++) {
      switch (XSCALE) {
      case SCALE_LIN :   MTRX[i][NCL]=DRL+(i-NRL)*drs;        break;
      case SCALE_LOG10 : MTRX[i][NCL]=pow10(DRL+(i-NRL)*drs); break;
      }
   }
*/
/*------------------------------------------------------------------*/

   Aw   = 4.19e-6;    /*-[1/(OHM*V)] */
   Bw   = 1.00e+8;    /*-[V/CM] */
   Ae   = 1.06e-2;    /*-[1/(OHM*V)] */
   Be   = 1.44e+8;    /*-[V/CM] */
   Aw   = 8.79e-6;
   Bw   = 9.49e+7;
   Ae   = 3.84e-3;
   Be   = 1.41e+8;

   Xo   = 1.00e-6;    /*-[CM] : tunnel tox */ 

   Agso = 0.320       /* [UM2] */;
   Agbo = 0.930       /* [UM2] */;
   Agdo = 0.650       /* [UM2] */;
   Aflt = 7.030       /* [UM2] */;
   P    = Agdo*1e-8   /*-[CM2] : injection area */;
   Cgso = 1.191e-15   /* [fF/UM2] */;
   Cgbo = 1.191e-15   /* [fF/UM2] */;
   Cgdo = 3.453e-15   /* [fF/UM2] */;
   Cflt = 1.259e-15   /* [fF/UM2] */;
   Cs   = Agso*Cgso   /* [F] */; /* 3.811e-16 */
   Cb   = Agbo*Cgbo   /* [F] */; /* 1.108e-15 */
   Cd   = Agdo*Cgdo   /*-[F] */; /* 2.244e-15 */
   Cf   = Aflt*Cflt   /*-[F] */; /* 8.851e-15 */
   Ct   = Cf+Cs+Cb+Cd /*-[F] */; /* 1.258e-14 */
   Kw   = Cf/Ct       /* progm coupling ratio */;
   Ke   = 1.0-Cd/Ct   /* erase coupling ratio */;
   Ctw  = Cf+Cs+Cb+Cd;
   Cte  = Cf+Cd;
   Kw   = Cf/Ctw;
   Ke   = 1.0-Cd/Cte;
   Echo("# Cs=%1.3e Cb=%1.3e Cd=%1.3e Cf=%1.3e\n",Cs,Cb,Cd,Cf); 
   Echo("# Ct=%1.3e P =%1.3e\n",Ct,P);
   Echo("# Ctw=%1.3e Cte=%1.3e\n",Ctw,Cte);
   Echo("# Kw =%1.3e Ke =%1.3e\n",Kw,Ke);

   Vg=Vd= 16.0;       /* [V] applied bias */
   Vto  = 0.7;        /* [V] natural vth */

/* #M#O#D#E#L###################################### */
#define EFFVD    (Vd-1.5)          /* 1.0 [V] : Deep Depletion */
                                   /* 0.5 [V] : Voltage Drop */
   switch (NOPTION) {
   case 1  : case 10 :
   /*----- EEPROM ARGUMENT -----*/
        Vti=-5.0 /* [V] */;
        Vg=DCL;
        YLOOPBEG; 
           NCLSKIP;
           Ei=1/Xo*Kw*(Vg-Vti+Vto); 
           Tc=(Ctw*Xo)/(P*Aw*Bw)*pow10(Bw/Ei);
           Echo("* Tc [pgm:Vti=%1.1f,Vg=%1.1f,Xo=%1.2e] = %1.3e\n",
                 Vti,Vg,Xo,Tc);
           XLOOPBEG; 
              t=XMTRX;
              Et=Bw/log10(pow10(Bw/Ei)+P*Aw*Bw*t/(Ctw*Xo));
              Vth=Vto+Vg-1/Kw*Xo*Et; 
              switch (NOPTION) {
                  case 1  : CMTRX=Vth;     break;
                  case 10 : CMTRX=Et;      break;
              }
           XLOOPEND;
           Vg+=dcs;
        YLOOPEND;
        break;

   case 2  : case 20 : case 21 : case 22 : case 23 : 
   /*----- EEPROM ERASE -----*/
        Vti=5.0 /* [V] */;
        switch (NOPTION) {
           case 2  : 
           case 20 : Vd=DCL;  
                     break;
           case 21 : 
           case 22 : 
           case 23 : Xo=DCL;
                     break;
        }

        YLOOPBEG; 
           NCLSKIP;
           Ei=1/Xo*Kw*(Ke/Kw*EFFVD+Vti+Vto);
           Eti=0.0;
           Tc=(Cte*Xo)/(P*Ae*Be)*pow10(Be/Ei);
           Echo("* Tc [ers:Vti=%1.1f,Vd=%1.1f,Xo=%1.2e] = %1.3e\n",
                 Vti,EFFVD,Xo,Tc);
           XLOOPBEG; 
              t=XMTRX;
              Et=Be/log10(pow10(Be/Ei)+P*Ae*Be*t/(Cte*Xo));
              J=Ae*SQR(Et)*pow10(-Be/Et);
              Vth=Vto-Ke/Kw*EFFVD+1/Kw*Xo*Et;
              J_=Ae*SQR(Et-Eti)*pow10(-Be/(Et-Eti));
              Eti=Ett=q*P/(Cte*Xo)*Not_t(t,J_,Xo)+Eti;
              switch (NOPTION) {
                  case 2  : CMTRX=Vth;     break;
                  case 20 : CMTRX=Et;      break;
                  case 21 : CMTRX=J*P/q;   break;
                  case 22 : CMTRX=Ett;     break;
                  case 23 : CMTRX=Et-Ett;  break;
              }
           XLOOPEND;
           switch (NOPTION) {
              case 2  : 
              case 20 : Vd+=dcs;
                        break;
              case 21 : 
              case 22 : 
              case 23 : Xo+=dcs;
                        break;
           }
        YLOOPEND;
        break;

   case 30 : 
   /*----- EEPROM REDUNDANCY -----*/
        t=1e-2;                    /* 10msec */
        Vg=16.0;
        Vd=16.0;
        Xo=DCL;
        Echo("# Vg=%2.1f Vd=%2.1f Time=%1.1e Tox=%1.2e\n",
              Vg,EFFVD,t,Xo);
#define MAXCYCLES 1e10             /* iteration */
#define QBDe      19.3/1.60218e-19 /* [#/cm2] */
        drs=1.0;
        for (i=NRL;i<=NRH;i++) {
           for (j=1;j<=9;j++) {
              MTRX[i++][NCL]=j*drs;
              if (i>NRH) break;
              if (drs!=1.0 && j==1) MTRX[i++][NCL]=1.5*drs;
              if (i>NRH) break;
              if (drs!=1.0 && j==2) MTRX[i++][NCL]=2.5*drs;
              if (i>NRH) break;
           } i--;
           drs*=10.0;
        }
        Echo("# REDUNDANCE\n");
        Echo("# [%d..%d][%d..%d]\n",
              NRL,NRH,
              NCL,NCH    /*(*YNO)[0] : NoOfBlock*/
              =1+(NCH-NCL)*(*YNO)[0]);
        YLOOPBEG;
           NCLSKIP;
           Vti=Vto;
           Eti=Ett=0.0;
           Ftot=Jmax=0.0;
           INDEXROW=NRL;
           DP_FOUND=DE_FOUND=FALSE;
           WC_FOUND=FALSE;
           BV_FOUND=FALSE;
           for (cycle=1.0;cycle<=MAXCYCLES;cycle+=1.0) {
              /*================== ARGUMENT ==================*/ 
              V=Vti;
              Ei=1/Xo*Kw*(Vg-Vti+Vto); 
              Et=Bw/log10(pow10(Bw/Ei)+P*Aw*Bw*t/(Ctw*Xo));
              if (!WC_FOUND) {
                 J=Aw*SQR(Et-Eti)*pow10(-Bw/(Et-Eti));   
J*=(1-1.43e-17*Ftot);
                 Nt=Not_t(t,J,Xo);
                 Ett=q*P*Nt/(Ctw*Xo)+Eti;
                 Jmax=MAX(J,Jmax);
                 Ftot+=ABS(J)*t/q;
              }
              Eti=Ett;
              Vti=Vth=Vto+Vg-1/Kw*Xo*(Et+Ett); 
              if (cycle==10.0) 
                 Vtp0=Vth;
              if (!DP_FOUND && cycle>10. && !dequ(1.,Vth/Vtp0,0.1)) {
                 Echo("# ARGUMENT 10%% Vth <%1.0f>\n",cycle);
                 DP_FOUND=TRUE;
              }
              if (!WC_FOUND && V>=Vth) {
                 Echo("# WIN COLLAPSE <PGM:%1.0f>\n",cycle);
                 Echo("# Et=%1.3e Ett=%1.3e,Et-Ett=%1.3e\n",Et,Ett,Et-Ett);
                 WC_FOUND=TRUE;
                 Echo("# Max Fluence=%1.4e[C/CM2]\n",Jmax/q*t);
                 Echo("# Tot Fluence=%1.4e[C/CM2,Ftot]\n",Ftot);
              }
              if (!BV_FOUND && Nt>QBDe) {
                 Echo("# BREAKDOWN <PGM:%1.0f>\n",cycle);
                 BV_FOUND=TRUE;
              }
              if (cycle==(float)MTRX[INDEXROW][NCL]) {
                 MTRX[INDEXROW][INDEXCOL+0]=Vth;
                 MTRX[INDEXROW][INDEXCOL+2]=Et;
              }
              /*================== ERASE ==================*/ 
              V=Vti;
              Ei=1/Xo*Kw*(Ke/Kw*EFFVD+Vti+Vto);
              Et=Be/log10(pow10(Be/Ei)+P*Ae*Be*t/(Cte*Xo));
              if (!WC_FOUND) {
                 J=Ae*SQR(Et-Eti)*pow10(-Be/(Et-Eti));   
J*=(1-1.43e-17*Ftot);
                 Nt=Not_t(t,J,Xo);
                 Ett=q*P*Nt/(Cte*Xo)+Eti;
                 Jmax=MAX(J,Jmax);
                 Ftot+=ABS(J)*t/q;
              }
              Eti=Ett;
              Vti=Vth=Vto-Ke/Kw*EFFVD+1/Kw*Xo*(Et+Ett);
              if (cycle==10.0) 
                 Vte0=Vth;
              if (!DE_FOUND && cycle>10. && !dequ(1.,Vth/Vte0,0.1)) {
                 Echo("# ERASE 10%% Vth <%1.0f>\n",cycle);
                 DE_FOUND=TRUE;
              }
              if (!WC_FOUND && V<=Vth) {
                 Echo("# WIN COLLAPSE <PGM:%1.0f>\n",cycle);
                 Echo("# Et=%1.3e Ett=%1.3e,Et-Ett=%1.3e\n",Et,Ett,Et-Ett);
                 WC_FOUND=TRUE;
                 Echo("# Max Fluence=%1.4e[C/CM2]\n",Jmax/q*t);
                 Echo("# Tot Fluence=%1.4e[C/CM2,Ftot]\n",Ftot);
              }
              if (!BV_FOUND && Nt>QBDe) {
                 Echo("# BREAKDOWN <ERS:%1.0f>\n",cycle);
                 BV_FOUND=TRUE;
              }
              if (cycle==(float)MTRX[INDEXROW][NCL]) {
                 MTRX[INDEXROW][INDEXCOL+1]=Vth;
                 MTRX[INDEXROW][INDEXCOL+3]=Et;
                 MTRX[INDEXROW][INDEXCOL+4]=Ett;
                 MTRX[INDEXROW][INDEXCOL+5]=J/q*t;
                 Echo("%+7.0f [#%2d],Nt=%1.5e,QBDe=%1.3e\n",
                       cycle,INDEXROW,Nt,QBDe);
                 INDEXROW++;
              }
              /*===========================================*/ 
              if (INDEXROW>NRH) break;
           }
           Xo+=dcs;
           INDEXCOL+=(*YNO)[0];
        YLOOPEND;
#undef  QBDe
#undef  MAXCYCLES 
        break;
   case 4 : 
        /*
         * data matrix [nrl..nrh][1..3]
         * ufun matrix [nrl..nrh][1..2]
        */
        INDEXCOL=2;
        Et=1.0; /* 0 -> 1 20030215 */
        XLOOPBEG; 
           MTRX[NRL][2]=Ae*SQR(Et)*pow10(-Be/Et);
           MTRX[INDEXROW][2]=Ae*SQR(XMTRX)*pow10(-Be/XMTRX);
        XLOOPEND; 
        break;
   default : errWarning("ERROR_usrfunc.c\n"
                       "submodel is invalid in EEPROM");
             return FALSE;
   }
   return TRUE;
#undef  EFFVD
   USERLISTEND;
/* #M#O#D#E#L###################################### */
}

/*
 * Mong-Song Liang and Chenming Hu,
 * "ELECTRON TRAPPING IN VERY THIN THERAML SILICON DIOXIDES"
 * Int. Electron Dev. Meeting,Technical Digest,396-99(1981)
 */
int TrapInThinOxide( ARGUMENTS )
   ARGULIST
{ 
   USERLIST;
   double Tox,No,Iccs,Aox,J,k,St,Ntc,Ntt;
   double *minvec,*maxvec;

   switch (NOPTION) {
      case 1  : /* Trap Generation Rate */
                /*
                 * DRL   : ccs current [A]
                 * DRH  : cap ox area [CM2]
                 * input -------
                 * [nrl..nrh][1] : time [SEC]
                 * [nrl..nrh][2] : vth  [V]
                 * output ------
                 * [nrl..nrh][1] : fluence   [/CM2]
                 * [nrl..nrh][2] : vth shift [V]
                 * [nrl..nrh][3] : gradient of vth shift
                 * [nrl..nrh][4] : vth shift fit
                 */
                minvec=dvector(NCL,NCH);
                maxvec=dvector(NCL,NCH);
                GetMtxMinMax(MTRX,minvec,maxvec,
	                   NRL,NRH,NCL,NCH);
                Echo("[col=%d] min=%1.2e, max=%1.2e\n",
                      INDEXCOL,minvec[INDEXCOL],maxvec[INDEXCOL]);
                /*===========================================*/ 
                Tox=100e-8;     /* [CM] */
                Iccs=4.5e-6;    /* [A] */
                Aox=4.5e-4;     /* [CM2] */
                /*===========================================*/ 
                St=6.1716e-22;  /* [CM2] */
                Ntc=1.5539e12;  /* [/CM2] */
                /*===========================================*/ 
                St=8.7900e-21;  /* [CM2] */
                Ntc=4.9107e12;  /* [/CM2] */
                Echo("Xo[M]=%1.3e J  [CM2]=%1.3e\n",Tox,Iccs/Aox/1.6e-19);
                Echo("St[ ]=%1.3e Ntc[   ]=%1.3e\n",St,Ntc);
                XLOOPBEG;
                   MTRX[INDEXROW][1]*=(Iccs/Aox)/1.6e-19;
                   MTRX[INDEXROW][2]-=minvec[2];
                XLOOPEND;
                free_dvector(minvec,NCL,NCH);
                free_dvector(maxvec,NCL,NCH);
                XLOOPBEG;
                   NRLSKIP;
                      MTRX[INDEXROW][3]=
                       (MTRX[INDEXROW+1][2]-MTRX[INDEXROW-1][2])/
                       (MTRX[INDEXROW+1][1]-MTRX[INDEXROW-1][1]);
                   if (INDEXROW==NRH) break;
                XLOOPEND;
                XLOOPBEG;
                      Ntt=Ntc*(1.0-pow10(-St*MTRX[INDEXROW][1]));
                      MTRX[INDEXROW][4]=
                         1.6e-19/(3.9*8.8542e-14)*50e-8*Ntt;
                XLOOPEND;
                break;
      case 2  : /* Capture Cross-Section */
      /* later */
                /*
                 * DRL   : ccs current [A]
                 * DRH  : cap ox area [CM2]
                 * 
                 * input -------
                 * [nrl..nrh][1] : time [SEC]
                 * [nrl..nrh][2] : vth  [V]
                 * output ------
                 * [nrl..nrh][1] : time              [SEC]
                 * [nrl..nrh][2] : vth               [V]
                 * [nrl..nrh][3] : fluence           [/CM2]
                 * [nrl..nrh][4] : 1.0-(vth shift)/k []
                 *  k=(tox/2)/(e0*eox)*q*No
                 */
                Tox=100e-8;    /* [CM] */
                No =1.554e12;  /* [/CM2] */
                Iccs=4.5e-6;   /* [A] */
                Aox=4.5e-4;    /* [CM2] */
                J=Iccs/Aox/1.6e-19;
                k=(Tox/2.0)/(3.9*8.8542e-14)*1.6e-19*No;
                Echo("Tox=%1.1e No=%1.3e Iccs=%1.1e Aox=%1.1e\n",
                      Tox,No,Iccs,Aox);
                Echo("J/q=%1.3e k=%1.3e\n",J,k);
                minvec=dvector(NCL,NCH);
                maxvec=dvector(NCL,NCH);
                GetMtxMinMax(MTRX,minvec,maxvec,
	                   NRL,NRH,NCL,NCH);
                XLOOPBEG;
                   MTRX[INDEXROW][3]=J*MTRX[INDEXROW][1];
                   MTRX[INDEXROW][4]=1.0-(MTRX[INDEXROW][2]-minvec[2])/k;
                XLOOPEND;
                free_dvector(minvec,NCL,NCH);
                free_dvector(maxvec,NCL,NCH);
                break;
      case 3  : /* Centroid Of Filled Traps */
                /*
                 * input -------
                 * [nrl..nrh][1] : current       [A]
                 * [nrl..nrh][2] : vth-before(+) [V]
                 * [nrl..nrh][3] : vth-before(-) [V]
                 * [nrl..nrh][4] : vth-after(+)  [V]
                 * [nrl..nrh][5] : vth-after(-)  [V]
                 * output ------
                 * [nrl..nrh][1] :
                 * [nrl..nrh][2] :
                 * [nrl..nrh][3] :
                 * [nrl..nrh][4] :
                 * [nrl..nrh][5] :
                 * [nrl..nrh][6] : vht-shift(+) [V]
                 * [nrl..nrh][7] : vht-shift(-) [V]
                 * [nrl..nrh][8] : centroid     [A]
                 */
                Aox=4.5e-4;    /* [CM2] */
                Echo("Aox=%1.3e\n",Aox);
                XLOOPBEG;
                   MTRX[INDEXROW][1]/=Aox;
                   MTRX[INDEXROW][6]=
                         MTRX[INDEXROW][4]-MTRX[INDEXROW][2];
                   MTRX[INDEXROW][7]=
                         MTRX[INDEXROW][5]-MTRX[INDEXROW][3];
                   MTRX[INDEXROW][7]=ABS(MTRX[INDEXROW][7]);
                   MTRX[INDEXROW][8]=MTRX[INDEXROW][7]*1e-6
                         /(MTRX[INDEXROW][6]+MTRX[INDEXROW][7]);
                XLOOPEND;
                break;
      default : errWarning("Submodel is invalid in TrapInThinOxide()");
                return FALSE;
   }

   Echo("\"%s\", [%d..%d][%d..%d]\n",TrapInThinOxide,NRL,NRH,NCL,NCH);

   return TRUE;
/*
   mtrxPrint(MTRX,NRL,NRH,NCL,NCH); 
*/
#undef  CAPAREA
   USERLISTEND;
}

/*
 * KHA
 */
int BandToBandTunneling( ARGUMENTS )
   ARGULIST
{
   USERLIST;
   double tox,xj,vd,vdsat,
          ln,nd,vdg,y,a,
          esat,l,ls_f1,ls_f2,ls_f3,ls_f4,ls_f5,lsat;
   double es,ey_f1,ey_f2,ey,ey_s,ef,lsat_s,ey_f3;
   double l1,l2,l3,l4,l5,ndo;
 
   LOOPBEG; NCLSKIP;
      tox=6.70e-06;
      xj=0.8e-04;
      vd=vdg=5;
      vdsat=0;
      ln=0.8e-04;
      nd=3e16;
      ndo=1e14;
      y=0.8e-04;
      a=5*pow(xj,-0.5)*pow(tox,-0.33);
      esat=3.5e4;

      vd=vdg=XMTRX;

      l=sqrt(esi*tox*xj/(eox*1.2));

      ls_f1=q*1.2*nd*l*l/esi;
      ls_f2=cosh(ln/l);
      ls_f3=1/(esat*l);
      ls_f4=ls_f3*(vd-vdsat+ls_f1*(ls_f2-1));
      ls_f5=l*asinh(ls_f4) ;
      lsat=ls_f5-ln;
 
      es=(vdg-1.2)/(3*tox);
 
      l1=(lsat+ln)/l;
      l2=ln/l;
      l3=cosh(l1);
      l4=q*1.2*ndo*l/(esat*esi);
      l5=l4*sinh(l2);
      lsat_s=-ln+l*acosh(l3-l5);
/*
      printf ("lsat     es\n" );
      printf ("%1.2e : %1.2e\n",lsat_s,es );
*/
      ey_f1=q*1.2*nd*l/esi;
      ey_f2=(y+lsat)/l;
      ey_f3=(-y+lsat_s)/l;
      if ( ABS(ln)<ABS(y) )  {
         ey_s=esat*(cosh(ey_f3));
         ef=ey_s;
      } else  {
         ey=esat*cosh(ey_f2)-sinh(y/l)*ey_f1;
         ef=ey;
      }
/*
      printf( "  nd         l       e/f\n");
      printf( "%1.2e : %1.2e : %1.2e\n",nd,y,ef );
*/
      YMTRX = ef;

   LOOPEND;
   USERLISTEND;
   return TRUE;
}
/******************************************************************************/
/*                           file name : semiconductor.h                      */
/*                         description : semiconductor calcus library         */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43360430                             */
/* 4336 0430-0502,0619,0821,0901,1122-1205,____,____,____,____,____,____,____ */
/* 4337 0207,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/
#ifndef semiconductor_header_INSTALLED
#define semiconductor_header_INSTALLED 1
/******************************************************************************/
#include "nrecipe.h"

/* Physical constants */

#define KKelvin 273.16 /* K = C + 273.16, Kelvin Temperature Constant */
#define VacPermittivity 8.85e-14 /* [F/cm] Vacuum dielectric constant, Vacuum permittivity. */
#define KBoltzman 1.38e-23 /* [J/K] Boltzman's constant. */
#define Qelectron 1.6e-19  /* [C] Electronic charge. */
#define RDCSilicon 11.7  /* [] Relative dielectric constant of silicon. */ 
#define RDCOxide 3.9   /* [] Relative dielectric constant of oxide. */
#define KPlanck 6.62e-34 /* [Js] */
#define KReducedPlanck 1.054e-34 /* KPlanck/2PI [Js] */
#define KAvogadro 6.02204e23 /* [/mol] */
#define MFreeElectron 9.1e-31 /* [Kg] */

/* Metal Work Function [V]
 * Ref: Sze p.396 Table 3.
 *      Mg 3.35  Al 4.1  Ni 4.55  Cu 4.7  Au 5.0  Ag 5.1
 */

/* Unit conversion */
#define cmoverA 1e-8 /* [cm/A] unit conversion of A to cm */
#define cmovernm 1e-7 /* [cm/nm] unit conversion of nm to cm */

/* Types */
typedef struct {
   enum { MT_DEMO,MT_PIECEWISE,MT_BERMAN,MT_NUMERICALPOISSON,MT_HANSCH
   } nMethod;
   /*   PIECEWISE : Classic C-V with analytical formulae.
        BERMAN : Classic C-V with Piecewise model and Berman correction.
        POISSON : Numerical computation of Poisson equation.
        HANSCH : Quantum correction with Hansch Model.
   */
   int bNType;          /* [Boolean] true(1) = n-type = n-Si = PMOS */
   int bHighFrequency;  /* If true, HF, or else, LF */
   int bDeepDepletion;  /* For the case of deep-depletion state in silicon substrate */
   double dKelvin;      /* [K] Kelvin degree */
   double dWgate;       /* [eV] Gate electrode work function */
   double dVfbShift;    /* [V] Flat-band voltage shift */
   double dTox;         /* [A] Gate oxide thicknesse */
   double dRDCox;       /* [] Relative dielectric constant of oxide */
   double dRDCsub;      /* [] Relative dielectric constant of substrate */
   double dNsub;        /* [#/cm3] Substrate concentration */
   double dHansch;      /* [cm] Hansch model factor : Therma wave length */
} MOSTAG;

/* MOS Matrix */
#define MOS_MATRIX_VS     1
#define MOS_MATRIX_US     2
#define MOS_MATRIX_UB     3
#define MOS_MATRIX_FS     4
#define MOS_MATRIX_QS     5
#define MOS_MATRIX_VG     6
#define MOS_MATRIX_VSVOLT 7
#define MOS_MATRIX_VOX    8
#define MOS_MATRIX_EOX    9
#define MOS_MATRIX_CSL    10
#define MOS_MATRIX_CTL    11
#define MOS_MATRIX_BERMAN 12
#define MOS_MATRIX_CSH    13
#define MOS_MATRIX_CTH    14
#define MOS_MATRIX_EFMEFS 15
#define MOS_MATRIX_EFMECS 16
#define MOS_MATRIX_EFMEVS 17
#define MOS_MATRIX_COLUMN 17

/* Function */

double GetThermalVoltage( /* [K] -> [V] */
       double dKelvin );
double GetExtrinsicDebyeLength( /* [K] -> [cm] [Nicollian p.63] */
       double dKelvin,double dRelativeDielectricConstant,double dNextrinsic );
double GetIntrinsicDebyeLength( /* [K] -> [cm]  [Nicollian p.55] */
       double dKelvin,double dRelativeDielectricConstant );
double GetIntrinsicDebyeCapacitance( /* [K] -> [F/cm2] */
       double dKelvin,double dRelativeDielectricConstant );
double GetSimpleMosCapacitance( /* [A] -> [F/cm2] */
       double dTox,double dRelativeDielectricConstant );
double GetSiBulkPotential(
       int bNtype,double dKelvin,double dNsub );
double GetSiBandGapEnergy( /* [K] -> [V] */
       double dKelvin );
double GetSiBandGapEnergyEx( /* [K] -> [V] */
       double dKelvin );
double GetSiIntrinsicCarrierConc( /* [K] -> [/cm^3] */ 
       double dKelvin );
double GetWorkFuncDiffToSiEf( /* [K],[eV],[],[/cm3] -> [V] */
       double dKelvin,double dGateWorkFunc,int bNtype,double dNsub );
int    IsNMOS( double dUb );
int    IsSurfaceStrongInversion( double dUb,double dVs/* =dUs-dUb */ );
int    IsSurfaceInversion( double dUb, double dVs/* =dUs-dUb */ ); 
int    GetFlatBandVoltageByHillard(
       VECTOR vVg,VECTOR vChf,int nLow,int nHigh,double *dVfb );

int    GetInterfaceTrapDensityByTerman( /* 20030901-0902 */
       int bNMOS,
       VECTOR vVgate/*[V]*/,VECTOR vCgtest/*[F/cm2]*/,VECTOR vCgideal/*[F/cm2]*/,
       VECTOR vVsideal/*[eV]*/,int nLow,int nHigh,
       VECTOR *pvDit/*[1/(cm2eV)]*/);

/******************************************************************************/
#endif /* semiconductor.h */

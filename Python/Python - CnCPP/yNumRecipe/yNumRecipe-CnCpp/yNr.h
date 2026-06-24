/******************************************************************************

       File: yNr.h
Description: Numerical Recipes in C
    Creator: ...
       Date: ...
   Revision: Kim, Yongshik (copyRight)
     Update: 43261120,
	         43320225,0720
Last Update: 20160325

*******************************************************************************/

#ifndef yNr_header_INSTALLED
#define yNr_header_INSTALLED 1

#include "yCore.h"
#define float double /* 931216,shik */
/******************************************************************************/

typedef struct FCOMPLEX {float r,i;} fcomplex;
typedef struct IMMENSE {unsigned long l,r;} immense;
typedef struct GREAT {unsigned short l,c,r;} great;

void adi _((double**,double**,double**,double**,
            double**,double**,double**,double**,
            int,int,double,double,double));
void amoeba _((float**,float*,int,float,float(*)(),int*));
void anneal _((float*,float*,int*,int));
void avevar _((float*,int,float*,float*));
void balanc _((float**,int));
void bcucof _((float*,float*,float*,float*,float,float,float**));
void bcuint _((float*,float*,float*,float*,float,
               float,float,float,float,float,float*,
               float*,float*));
float bessi _((int,float));
float bessi0 _((float));
float bessi1 _((float));
float bessj _((int,float));
float bessj0 _((float));
float bessj1 _((float));
float bessk _((int,float));
float bessk0 _((float));
float bessk1 _((float));
float bessy _((int,float));
float bessy0 _((float));
float bessy1 _((float));
float beta _((float,float));
float betacf _((float,float,float));
float betai _((float,float,float));
float bico _((int,int));
void bksub _((int,int,int,int,int,float***));
float bnldev _((float,int,int*));
float brent _((float,float,float,float(*)(),float,float*));
void bsstep _((float*,float*,int,float*,float,
              float,float*,float*,float*,void(*)()));
void caldat _((long,int*,int*,int*));
float cel _((float,float,float,float));
void chder _((float,float,float*,float*,int));
float chebev _((float,float,float*,int,float));
void chebft _((float,float,float*,int,float(*)()));
void chebpc _((float*,float*,int));
void chint _((float,float,float*,float*,int));
void chsone _((float*,float*,int,int,float*,
               float*,float*));
void chstwo _((float*,float*,int,int,float*,
               float*,float*));
void cntab1 _((int**,int,int,float*,float*,
               float*,float*,float*));
void cntab2 _((int**,int,int,float*,float*,
               float*,float*,float*,float*,float*,float*));
void convlv _((float*,int,float*,int,int,float*));
void correl _((float*,float*,int,float*));
void cosft _((float*,int,int));
void covsrt _((float**,int,int*,int));
void crank _((int,float*,float*));
float dbrent _((float,float,float,float(*)(),float(*)(),
                float,float*));
void ddpoly _((float*,int,float,float*,int));
void des  _((immense, immense,int*,int, immense *));
void ks _((immense,int, great *));
void cyfun _((unsigned long, great, unsigned long*));
float df1dim _((float));
void dfpmin _((float*,int,float,int*,float*,float(*)(),
               void(*)()));
void difeq _((int,int,int,int,int,int,int*,int,
              float**,float**));
void dlinmin _((float*,float*,int,float*,float(*)(),void(*)()));
void eclass _((int*,int,int*,int*,int));
void eclazz _((int*,int,int (*)()));
void eigsrt _((float*,float**,int));
float el2 _((float,float,float,float));
void elmhes _((float**,int));
#if _MSVSC_ == 6
float erf _((float)); 
float erfc _((float));
#endif
float erfcc _((float));
void eulsum _((float*,float,int,float*));
float evlmem _((float,float*,int,float));
float expdev _((int*));
float f1dim _((float));
float factln _((int));
float factrl _((int));
void fgauss _((float,float*,float*,float*,int));
void fit _((float*,float*,int,float*,int,float*,
            float*,float*,float*,float*,float*));
void fixrts _((float*,int));
void fleg _((float,float*,int));
void flmoon _((int,int, long*,float*));
void four1 _((float*,int,int));
void fourn _((float*,int*,int,int));
void fpoly _((float,float*,int));
void ifpoly _((float,float*,int)); /* 950715(by)Y.S.Kim */
void frprmn _((float*,int,float,int*,float*,float(*)(),
               void(*)()));
void ftest _((float*,int,float*,int,float*,float*));
float gamdev _((int,int*));
float gammln _((float));
float gammp _((float,float));
float gammq _((float,float));
float gasdev _((int*));
void gauleg _((double,double,double *,double *,int));
void gaussj _((float**,int,float**,int));
void gcf _((float*,float,float,float*));
float golden _((float,float,float,float(*)(),float,float*));
void gser _((float*,float,float,float*));
void hqr _((float**,int,float*,float*));
void hunt _((float*,int,float,int*));
void indexx _((int,float*,int*));
int irbit1 _((unsigned long int*));
int irbit2 _((unsigned long int*));
void jacobi _((float**,int,float*,float**,int*));
long julday _((int,int,int));
void kendl1 _((float*,float*,int,float*,float*,float*));
void kendl2 _((float**,int,int,float*,float*,float*));
void ksone _((float*,int,float(*)(),float*,float*));
void kstwo _((float*,int,float*,int,float*,float*));
void laguer _((fcomplex *,int, fcomplex *,float,int));
void lfit _((float*,float*,float*,int,float*,int,
             int*,int,float**,float*,void(*)()));
void linmin _((float*,float*,int,float*,float(*)()));
void locate _((float*,int,float,int*));
void lubksb _((float**,int,int*,float*));
void ludcmp _((float**,int,int*,float*));
void mdian1 _((float*,int,float*));
void mdian2 _((float*,int,float*));
void medfit _((float*,float*,int,float*,float*,float*));
void memcof _((float*,int,int,float*,float*));
float midexp _((float(*)(),float,float,int));
float midinf _((float(*)(),float,float,int));
float midpnt _((float(*)(),float,float,int));
float midsql _((float(*)(),float,float,int));
float midsqu _((float(*)(),float,float,int));
void mmid _((float*,float*,int,float,float,int,float*,void(*)()));
void mnbrak _((float*,float*,float*,float*,
               float*,float*,float(*)()));
void mnewt _((int,float*,int,float,float));
void moment _((float*,int,float*,float*,float*,
               float*,float*,float*));
void mprove _((float**,float**,int,int*,float*,float*));
void mrqcof _((float*,float*,float*,int,float*,int,
               int*,int,float**,float*,float*,void(*)()));
void mrqmin _((float*,float*,float*,int,float*,int,
               int*,int,float**,float**,float*,void(*)(),
               float*));
void odeint _((float*,int,float,float,float,float,
               float,int*,int*,void(*)(),void(*)()));
void pcshft _((float,float,float*,int));
void pearsn _((float*,float*,int,float*,float*,float*));
void piksr2 _((int,float*,float*));
void piksrt _((int,float*));
void pinvs _((int,int,int,int,int,int,float***,float**));
float plgndr _((int,int,float));
float poidev _((float,int*));
void polcoe _((float*,float*,int,float*));
void polcof _((float*,float*,int,float*));
void poldiv _((float*,int,float*,int,float*,float*));
void polin2 _((float*,float*,float**,int,int,float,
               float,float*,float*));
void polint _((float*,float*,int,float,float*,float*));
void powell _((float*,float**,int,float,int*,float*,float(*)()));
void predic _((float*,int,float*,int,float*,int));
float probks _((float));
void pzextr _((int,float,float*,float*,float*,int,int));
void qcksrt _((int,float*));
float qgaus _((float(*)(),float,float));
float qromb _((float(*)(),float,float));
float qromo _((float(*)(),float,float,float(*)()));
void qroot _((float*,int,float*,float*,float));
float qsimp _((float(*)(),float,float));
float qtrap _((float(*)(),float,float));
float quad3d _((float(*)(),float,float));
float ran0 _((int*));
float ran1 _((int*));
float ran2 _((long*));
float ran3 _((int*));
float ran4 _((int*));
void rank _((int,int*,int*));
void ratint _((float*,float*,int,float,float*,float*));
void realft _((float*,int,int));
void red _((int,int,int,int,int,int,int,int,int,int,
            int,float***,float**));
void rk4 _((float*,float*,int,float,float,float*,void(*)()));
void rkdumb _((float*,int,float,float,int,void(*)()));
void rkqc _((float*,float*,int,float*,float,float,
             float*,float*,float*,void(*)()));
float rofunc _((float));
float rtbis _((float(*)(),float,float,float));
float rtflsp _((float(*)(),float,float,float));
float rtnewt _((void(*)(),float,float,float));
float rtsafe _((void(*)(),float,float,float));
float rtsec _((float(*)(),float,float,float));
void rzextr _((int,float,float*,float*,float*,int,int));
void scrsho _((float(*)()));
void shell _((int,float*));
void shoot _((int,float*,float*,int,float,float,float,
              float,float,float*,float*,//));20031124
              void(*)(double,double*,double*),
              void(*)(double,double*,double*),
              void(*)(double,double*,double*)));
void shootf _((int,float*,float*,float*,float*,int,int,
               float,float,float,float,float,float,float*,
               float*,float*));
void simp1 _((float**,int,int*,int,int,int*,float*));
void simp2 _((float**,int,int*,int,int*,int,float*));
void simp3 _((float**,int,int,int,int));
void simplx _((float**,int,int,int,int,int,int*,int*,int*));
void sinft _((float*,int));
void smooft _((float*,int,float));
void sncndn _((float,float,float*,float*,float*));
void solvde _((int,float,float,float*,int*,int,int,
               int,float**,float***,float**));
void sor _((double**,double**,double**,double**,double**,
            double**,double**,int,double));
void sort _((int,float*));
void sort2 _((int,float*,float*));
void sort3 _((int,float*,float*,float*));
void sparse _((float*,int,float*,float*));
void spctrm _((FILE *,float*,int,int,int));
void spear _((float*,float*,int,float*,
              float*,float*,float*,float*));
void splie2 _((float*,float*,float**,int,int,float**));
void splin2 _((float*,float*,float**,float**,int,int,
               float,float,float*));
void spline _((float*,float*,int,float,float,float*));
void splint _((float*,float*,float*,int,float,float*));
void svbksb _((float**,float*,float**,int,int,float*,float*));
void svdcmp _((float**,int,int,float*,float**));
void svdfit _((float*,float*,float*,int,float*,int,
               float**,float**,float*,float*,void(*)()));
void svdvar _((float**,int,float*,float**));
void toeplz _((float*,float*,float*,int));
void tptest _((float*,float*,int,float*,float*));
void tqli _((float*,float*,int,float**));
float trapzd _((float(*)(),float,float,int));
void tred2 _((float**,int,float*,float*));
void tridag _((float*,float*,float*,float*,float*,int));
void ttest _((float*,int,float*,int,float*,float*));
void tutest _((float*,int,float*,int,float*,float*));
void twofft _((float*,float*,float*,float*,int));
void vander _((float*,float*,float*,int));
int zbrac _((float(*)(),float*,float*));
void zbrak _((float(*)(),float,float,int,float*,float*,int*));
float zbrent _((float(*)(),float,float,float));
void zroots _((fcomplex *,int, fcomplex *,int));

extern  fcomplex Cadd();
extern  fcomplex Csub();
extern  fcomplex Cmul();
extern  fcomplex Complex();
extern  fcomplex Conjg();
extern  fcomplex Cdiv();
extern  float    Cabs();
extern  fcomplex Csqrt();
extern  fcomplex RCmul();

float *vector _((int,int));
float **matrix _((int,int,int,int));
float **convert_matrix _((float*,int,int,int,int));
double *dvector _((int,int));
double **dmatrix _((int,int,int,int));
int *ivector _((int,int));
int **imatrix _((int,int,int,int));
float **submatrix _((float**,int,int,int,int,int,int));
void free_vector _((float*,int,int));
void free_dvector _((double*,int,int));
void free_ivector _((int*,int,int));
void free_matrix _((float**,int,int,int,int));
void free_dmatrix _((double**,int,int,int,int));
void free_imatrix _((int**,int,int,int,int));
void free_submatrix _((float**,int,int,int,int));
void free_convert_matrix _((float**,int,int,int,int));
void nrerror _((char*));

/*-(c)shik--------------------------------------------------------------------*/

void invmatrix _(());

/******************************************************************************/
#undef float /* 990720(c)shik */

#endif /* yNr.h */

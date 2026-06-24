/******************************************************************************/
/*                           file name : usrfunc.h                            */
/*                         description : user funcion libray                  */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43240412                             */
/* 4324 0412-1021,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 930918 __,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 1020,1031,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0410,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4330 0717-0811,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0511-0528,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4334 0419,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4335 1015,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0223,0429,0522,0904-0905,____,____,____,____,____,____,____,____,____ */
/* 4337 0612,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/
#ifndef usrfunc_header_INSTALLED
#define usrfunc_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"

#define SWAP_(a,b,type) {type tEmP=(a);(a)=(b);(b)=tEmP;}
#ifndef SQR_installed
#define SQR_installed
static double sqrarg;
#define SQR(a) (sqrarg=(a),sqrarg*sqrarg)
#endif

/******************************************************************************/

#define ARGUMENTS                                                              \
        /* input parameters */                                                 \
        MTX,MRL,MRH,MCL,MCH,                                                   \
        XTOTAL,XNO,YTOTAL,YNO,ZTOTAL,ZNO,NRL,NRH,NCL,NCH,                      \
        NOPTION,NSUBOPTION,XSCALE,YSCALE,ZSCALE,                               \
        ARGUMENT,ARGUMENT2,ARGUMENT3,ARGUMENT4,SWEEP,                          \
        /* output parameters */                                                \
        OUTTOT,OUTVEC,OUTTEXT
#define ARGULIST                                                               \
        double ***MTX;int *MRL,*MRH,*MCL,*MCH;                                 \
        int *XTOTAL,**XNO,*YTOTAL,**YNO,*ZTOTAL,**ZNO,NRL,NRH,NCL,NCH;         \
        int NOPTION,NSUBOPTION,XSCALE,YSCALE,ZSCALE;                           \
        char *ARGUMENT,*ARGUMENT2,*ARGUMENT3,*ARGUMENT4,*SWEEP;                \
        int *OUTTOT;double **OUTVEC;char **OUTTEXT;
#define ARGUMENTS4USER                                                         \
        /* input parameters */                                                 \
        &uMTX,&uMRL,&uMRH,&uMCL,&uMCH,                                         \
        &uXTOTAL,&uXNO,&uYTOTAL,&uYNO,&uZTOTAL,&uZNO,uNRL,uNRH,uNCL,uNCH,      \
        uNOPTION,uNSUBOPTION,uXSCALE,uYSCALE,uZSCALE,                          \
        uARGUMENT,uARGUMENT2,uARGUMENT3,uARGUMENT4,uSWEEP,                     \
        /* output parameters */                                                \
        &uOUTTOT,&uOUTVEC,&uOUTTEXT
#define ARGULIST4USER                                                          \
        double **uMTX=0;int uMRL=0,uMRH=0,uMCL=0,uMCH=0;                       \
        int uXTOTAL=0,*uXNO=0,uYTOTAL=0,*uYNO=0,uZTOTAL=0,*uZNO=0;             \
        int uNRL=0,uNRH=0,uNCL=0,uNCH=0;                                       \
        int uNOPTION=0,uNSUBOPTION=0,uXSCALE=0,uYSCALE=0,uZSCALE=0;            \
        char *uARGUMENT=0,*uARGUMENT2=0,*uARGUMENT3=0,*uARGUMENT4=0,*uSWEEP=0; \
        int uOUTTOT=0;double *uOUTVEC=0;char *uOUTTEXT=0;

/*----------------------------------------------------------------------------*/

#define dequ(d1,d2,margin)                                                     \
	((ABS((double)(d1)-(double)(d2))<(double)(margin)) ? 1:0)

typedef struct {
   const char *qName;
   const char *qSample;
   const char *qHelp;
} uFuncTableTag; /* prepared for communicating with dialog class. 43270612 */

/*---debug--------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

extern double icnorm _(( ));

/******************************************************************************/
#endif /* usrfunc.h */
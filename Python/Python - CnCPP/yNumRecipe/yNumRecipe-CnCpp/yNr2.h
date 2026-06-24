/******************************************************************************

       File: yNr2.h
Description: Numberical Recipes in C
 Originator: P.R.Bevington and D.K. Robinson
     Source: "Data Reduction and Error Analysis for the Physical Sciences,"
             3ed,2003
       Date: 43260609
   Revision: Kim, Yongshik
     Update: 43260610
Last Update: 2016.3.28

*******************************************************************************/

#ifndef yNr2_header_INSTALLED
#define yNr2_header_INSTALLED 1

/*
   nFitMethod:
  (0)GridSearch,(1)GradientSearch,(2)ChiSqExpansion,(3)FunctionExpansion
 */

int LinearAndNonlinearFit( /* Y.Kim */ /* [1..nTotal] */
   double vX[],double vY[],double vSig[],int nData,
   double vFitParameter[],double vFitParameterInc[],int nFitParameter,int nFitMethod,
   double *pChiSq,
   double (*pLinear)(int,double),
   double (*pNonLinear)(double,double*),
   void (*pEchoAtEachIteration)(int) //20031226
);

#endif /* yNr2.h */


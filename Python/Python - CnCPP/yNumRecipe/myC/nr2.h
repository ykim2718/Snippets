/******************************************************************************/
/*                                                                            */
/*                           file name : nr2.h                                */
/*                       originated by : P.R.Bevington and D.K. Robinson      */
/*   "Data Reduction and Error Analysis for the Physical Sciences,"3ed,2003   */
/*                            modifier : Kim,YongShik                         */
/*                       creating date : 43260609                             */
/*                             updated : 43260610                             */
/*                                                                            */
/******************************************************************************/

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

/******************************************************************************/
/* nr2.h */



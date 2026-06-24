/******************************************************************************/
/*                                                                            */
/*                           file name : nr2.cpp                              */
/*                       originated by : P.R.Bevington and D.K. Robinson      */
/*   "Data Reduction and Error Analysis for the Physical Sciences,"3ed,2003   */
/*                            modifier : Kim,YongShik                         */
/*                       creating date : 43260609                             */
/*                             updated : 43260611,0802                        */
/*                                                                            */
/******************************************************************************/
/*                         genutil.cpp + fitutil.cpp                          */
/******************************************************************************/

#include <stdio.h>
#include <fstream.h>
#include <iomanip.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "number.h"
#include "nrecipe.h"
#include "nr2.h"

static double ChiProb(double nFree,double chi2);
static double Chi2_Dens(double x, double h,double g); //See ChiProb for g.
static double Simpson(char functCode,int nIntervals,double loLim,double hiLim,double p1,double p2,double p3);   //2 calcs/interval
static double Gamma(double h); //Approximate Gamma function for integers and half-integers

static void InvertX();
static void StatisticalErrs();
static double CalcChiSq();		
static double LineFit();

static double PowerSeriesFunc(int k, double x);
static double LegendreFunc(int k, double x);
static double Expf(double x, double a);  
static double TwoExponentials(double x);

//Added for Chapt_7
static void MakeBeta();
static void MakeAlpha();
static double MatInv(); //invert a matrix
static void SquareByRow(); // multiply square matrix by linear matrix
static void	igMatrix();     

// added for Chapt_8
static void	Gridls(double *chiSqr);
static void	Gradls(double *chiSqr, double stepDown);
static void	ChiFit(double *chiSqr);
static void Marquardt(double *chiSqr,double chiCut,double lambda);
static void SigParab();
static double dXiSq_da(int j);
static double d2XiSq_da2(int j);
static double d2XiSq_dajk(int j, int k);

// added for Chapter_9
static double OneLorentz(int idummy,double x); // Calculate one peak on background
static double TwoLorentz(int idummy,double x); // Calculate two peaks on background
static double Lorentz(double x,double mean,double gamma);// Calculate the peak

//Input Output

static void FitOut(char outFile[],double chi2,char aErrorsFrom);
static void CalcGrad();

/*----------------------------------------------------------------------------*/

static double *g_vX,*g_vY,*g_vSig,*g_vParameter,*g_vParameterInc;
static double *g_yCalc,*g_y_0,*g_vsiga,*g_vda,*g_vbeta,**g_malpha,**g_mdYda;
static double (*LinearUserFunction)(int,double); //(int,double,double*) ??? Y.Kim
static double (*NonLinearUserFunction)(double,double*);
static int g_nParameter=0; /* Y.Kim, Number of parameters */
static int g_nData=0;      /* Y.Kim, Number of data coordinates */ 

int LinearAndNonlinearFit( /* Y.Kim */ /* [1..nTotal] */
   double vX[],double vY[],double vSig[],int nData,
   double vFitParameter[],double vFitParameterInc[],int nFitParameter,int nFitMethod,
   double *pChiSq,
   double (*pLinear)(int,double),
   double (*pNonLinear)(double,double*),
   void (*pEchoAtEachIteration)(int)
)
{
   double dChiCut=0.01,dChiSqr,dChiOld;
	double dStepDown=0.1; /* step down the gradient in Gradls */
	double dLambda=0.001; /* for Marquardt only */
   int nTrial;

   g_vX=vX;
	g_vY=vY;
	g_vSig=vSig;
   g_nData=nData;
   g_vParameter=vFitParameter;
   g_vParameterInc=vFitParameterInc;
   g_nParameter=nFitParameter;
   nFitMethod%=4;
   LinearUserFunction=pLinear;
   NonLinearUserFunction=pLinear ? 0:pNonLinear;

   g_yCalc=VCreate(1,nData);
   g_y_0=VCreate(1,nData);
   g_vsiga=VCreate(1,nFitParameter);
   g_vda=VCreate(1,nFitParameter);
   g_vbeta=VCreate(1,nFitParameter);
   g_malpha=MCreate(1,nFitParameter,1,nFitParameter);
   g_mdYda=MCreate(1,nData,1,nFitParameter);

	nTrial=0;
   dChiSqr=CalcChiSq();
   if (pEchoAtEachIteration) (*pEchoAtEachIteration)(nTrial); //20031227
	do	{
		dChiOld=dChiSqr;
		switch (nFitMethod) {
      case 0: Gridls(&dChiSqr);break;
      case 1: Gradls(&dChiSqr,dStepDown);break;
      case 2: ChiFit(&dChiSqr);break;
      case 3: Marquardt(&dChiSqr,dChiCut,dLambda);break;
		}			
		nTrial++;
      if (pEchoAtEachIteration) (*pEchoAtEachIteration)(nTrial); //20031226
	//} while (fabs(dChiOld-dChiSqr)>=dChiCut);
   } while (fabs(1-dChiSqr/dChiOld)>=dChiCut); /* 20030802 */
   /*
	switch (nFitMethod) {
   case 0: //'C' - Example 8.1 - vary chi^2 for parameter errors
           FitOut("RDecay-Grid Search.txt", dChiSqr, 'C');break;
   case 1: //'C' - Example 8.2 - vary chi^2 for parameter errors
           FitOut("RDecay-Grad Search.txt", dChiSqr, 'C');break;
   case 2: //Example 8.1 - parameter errors from Matrix Inversion
           FitOut("RDecay-Expnd Func.txt", dChiSqr, 'M');break;
   case 3: //Example 8.1 - parameter errors from Matrix Inversion
           FitOut("RDecay-Marqardt.txt", dChiSqr, 'M');break;
   }
   */

   VDestroy(g_yCalc,1,nData);
   VDestroy(g_y_0,1,nData);
   VDestroy(g_vsiga,1,nFitParameter);
   VDestroy(g_vda,1,nFitParameter);
   VDestroy(g_vbeta,1,nFitParameter);
   MDestroy(g_malpha,1,nFitParameter,1,nFitParameter);
   MDestroy(g_mdYda,1,nData,1,nFitParameter);

   *pChiSq=dChiSqr;
   return nTrial;
}

static double yFunction( double x )
{
	double y;
	int k;
   if (LinearUserFunction) {
		y=0.0;
      //Linear fitting of g_vParameter sum of g_vParameter[k]*f().
      //Beta and g_malpha require the individual f(x)'s.
		for (k=1;k<=g_nParameter;k++)
         y+=g_vParameter[k]*LinearUserFunction(k,x);
   } else
      //Non-linear fitting calculates g_vbeta and alphs from derivatives ofXi2 and of f(x)
		y=NonLinearUserFunction(x,g_vParameter);
   return(y);
}

static double CalcChiSq()
{
	int i;     
	double Xi2=0.;
   for (i=1;i<=g_nData;i++)
      g_yCalc[i]=yFunction(g_vX[i]);
	for (i=1;i<=g_nData;i++)
      Xi2+=SQUARE((g_vY[i]-g_yCalc[i])/g_vSig[i]);
	return(Xi2);
}

/******************************************************************************/
/* genutil.cpp */

//----Simpson's rule  args: funct selects the function, ... p1, and p2 are parameters of the function.
static double Simpson(char functCode,int nIntervals, double loLim, double hiLim, double p1, double p2, double p3)   //2 calcs/interval
{
	double (*SimpsonFunct)(double, double, double);
	double sum, x,dx,      t1,t2;
	int i;

	x = loLim;
	dx = (hiLim - loLim)/(2*nIntervals);
// --------------- Select function- must be in this list
	switch (functCode)
	{
		case 'X':
			SimpsonFunct = Chi2_Dens;
		break;
//		case 'G':
//		SimpsonFunct = Gauss_Dens;
//		break;
	}
	sum = SimpsonFunct(loLim, p1, p2) - SimpsonFunct(hiLim, p1, p2);
	for (i=1; i <= nIntervals; i++) 
	{
		x = x + 2*dx;

		t1 = SimpsonFunct(x-dx, p1, p2);
		t2 = SimpsonFunct(x,    p1 ,p2);
		sum = sum + 4*t1 + 2*t2;
//		cout << x << "   " << t2 << "  " << sum <<  endl;
		x = x;
	}
	sum = sum*dx/3;
	return(sum);
}

static double Power(double x, double para )	//x^para
{
	double tem;

	tem = exp(para*log(x));
	return(tem);
}

//-------------------------------- Chi^2 Density and Probability ---------------------------- 
static double Chi2_Dens(double x, double h, double g) //See ChiProb for g.
{
	double chiDens;
	
	if (x == 0.) 
		chiDens = 0.; 
	else
		chiDens = Power(x, h-1)*exp(-x/2.)/g;		//  x^(h-1) e^(-x/2);
	return(chiDens);
}

static double ChiProb(double nFree, double chi2)
{
	double	probTem,  
			cLim = 2,								// expansion limit for nFree = 1
			intFromLim = 0.157,						// integral from cLim to infInity for nFree = 1
			dx = 0.2,
			g; 				// determines accuracy of integration}
	int nIntervals = (int)(chi2/dx);		// number  of intervals for Simpson integral.  2 calculations per interval.
	double h =  nFree/2.;

	g = Gamma(h) * Power( 2, h);
	if (chi2 > 15*sqrt(nFree))  
	return(0.0);	// quick cutout  	
	if (nFree == 1)
	{
		if (chi2 < cLim)						// Integrate expansion of the function 
			probTem = 1.0-sqrt(chi2/2./PI)*(2. - chi2*(1./3. - chi2*(1.0/20. - chi2*(1./168. - chi2/1728.))));
		else
			// Subtract numerical integral from analytic intFromLim 
			probTem = intFromLim - Simpson('X',nIntervals,cLim,chi2,h, g, 0.);
		return(probTem);
	}
		if (nFree == 2) 
			probTem = exp(-chi2/2);				// Integrable for nFree = 2;
		else									// I.e., nFree > 2
			probTem = 1 - Simpson('X', nIntervals, 0, chi2, h, g, 0.);
	return(probTem);
}

static double Gamma(double h)  //Approximate Gamma function for integers and half-integers     
{ 

	double gamma;
//gamma  = sqrt(2*PI)*exp(-h)*[h^(h-1/2)]*[1 + 0.0833/h]  with h = nFree/2 }
	gamma = sqrt(2*PI)*exp(-h+(h-0.5)*log(h))*(1 + 0.0833/h);
//	gamma = sqrt(2*PI)*exp(-h)*Power(h, h-0.5) * (1 + 0.0833/h);
	return(gamma);
}

/******************************************************************************/
/* End of genutil.cpp */


/******************************************************************************/
/* fitutil.cpp <- Utilities for Least Squares Fitting */
 
//-----------------------  Analytic Fitting Functions --------------------------------------------
//		Functions must be of the form g_vParameter[1]*f1(g_vX) + g_vParameter[2]*f2(g_vX) + ...
//		The routines calculate individual; terms, f1, f2, ...
//		They are combined into g_vParameter single expression in in the finction FillYarray.

static double PowerSeriesFunc(int k, double x)		//
{
	double y;
	int i;
	y = 1;
	if (k > 1)
		for (i=2; i <= k; i++)  y = x * y;
	return(y);
}

//------------  Non-Linear Fitting Functions must be completely defined here--------------------

static double TwoExponentials( double x )	// Chapter 8
{
   double y;
	y=g_vParameter[1]+g_vParameter[2]*Expf(x,g_vParameter[4])+g_vParameter[3]*Expf(x,g_vParameter[5]);
	return(y);
}	

static double Expf(double x, double para ) 
{
   double z,arg;
   arg=fabs(x/para); //Note - does not allow positive exponentials
   z=(arg>60.) ? 0.:exp(-arg);
	return (z);
}

static double OneLorentz(int idummy, double x)				//Calculate one peak on background
{
	double yy;
	yy = g_vParameter[1] + g_vParameter[2]*x + g_vParameter[3]*SQUARE(x) + g_vParameter[4]*Lorentz(x, g_vParameter[5], g_vParameter[6]);
	return(yy);
}

static double TwoLorentz(int idummy, double x)				//Calculate two peaks on background
{
	double yy;
	yy = g_vParameter[1] + g_vParameter[2]*x + g_vParameter[3]*SQUARE(x) + g_vParameter[4]*Lorentz(x, g_vParameter[5], g_vParameter[6])	                               
		                              + g_vParameter[7]*Lorentz(x, g_vParameter[8], g_vParameter[9]);
	return(yy);
}

static double Lorentz(double x, double mean, double gamma)  // Calculate the peak
	{
		double Lor;
		Lor = gamma/(2/PI)/(SQUARE(x-mean) + SQUARE(gamma/2));
		return(Lor);
	}

//------------------------------- General Purpose Functions ----------------------------

static void StatisticalErrs()
{
	int i;
	for (i=1; i <= g_nData; i++) {
		g_vSig[i] = sqrt(g_vY[i]); 
	}
}

//-----------Self-contained routine to  fit g_vParameter Straight Line by Determinants  (Chapter 6) -----------
static double LineFit()
{
	int i;        //  NOTE    dev    : text;
	double    det, sumWt, sumX, sumY, sumX2, sumY2, sumXY, weight;
	sumWt = 0;  sumX  = 0;  sumY  = 0;
	sumX2 = 0;  sumY2 = 0;  sumXY = 0;
//------- accumulate weighted sums -----------
	for (i= 1; i <= g_nData; i++)
	{
		weight  = 1/SQUARE(g_vSig[i]);
		sumWt   = sumWt  + weight;
		sumX    = sumX   + weight * g_vX[i];
		sumY    = sumY   + weight * g_vY[i];
		sumX2   = sumX2  + weight * SQUARE(g_vX[i]);
		sumY2   = sumY2  + weight * SQUARE(g_vY[i]);
		sumXY   = sumXY  + weight * g_vX[i]*g_vY[i];
	}
 
// calculate the parameters - cut out if determinant is not > 0 }
	det =  sumWt * sumX2 - sumX * sumX;
	if (det > 0)
	{
		g_vParameter[1]     = (sumX2*sumY  - sumX*sumXY)/det;
		g_vParameter[2]     = (sumXY*sumWt - sumX*sumY) /det;
		g_vsiga[1]  = sqrt(sumX2/det);
		g_vsiga[2]  = sqrt(sumWt/det);
		return(det);
	}
	else
	return(-1);

}

// ----------------------- Matrix Fitting Routines added for CHAPTER 7 --------------------

// Set up the g_malpha and g_vbeta matrices for linear least-squares fitting.

static void MakeBeta() 
{	
	int i, j, k;   
	
   if (LinearUserFunction) {
//--------------------- Set up the g_vbeta matrices for linear fitting 
      for (k=1;k<=g_nParameter;k++) {
         g_vbeta[k]=0.;
         for (i=1;i<=g_nData;i++)
            g_vbeta[k]=g_vbeta[k]+
            g_vY[i]*LinearUserFunction(k,g_vX[i])/SQUARE(g_vSig[i]);
      }
   } else {
//-------------------- Set up the g_vbeta matrices for non-linear fitting - see Eq. 8.26	
      for (j = 1; j <= g_nParameter;j++) {
         g_vbeta[j] = -dXiSq_da(j)/2.;
      }
	}
}

static void MakeAlpha()               //Make the g_malpha matrices 
{
	int i,j,k;
    
	if (LinearUserFunction)
//--------------------- Set up the g_malpha matrices for linear fitting 
	{
		// cout << "Alpha Matrix" << endl;
		for (j = 1; j <= g_nParameter;j++)
		{
			// cout << " j" << j << endl;
			for (k = 1; k <= g_nParameter; k++)
			{
				g_malpha[j][k] = 0.;
				for (i = 1; i<=g_nData; i++)
				{	
					g_malpha[j][k] = g_malpha[j][k]+LinearUserFunction(j, g_vX[i])*LinearUserFunction(k, g_vX[i])/SQUARE(g_vSig[i]);
				}	 // g_vX[i]
			}   //k
		} //j
	
	} else {
//--------------------- Set up the g_malpha matrices for non-linear fitting 
		for (j = 1; j <= g_nParameter; j++) {
			g_malpha[j][j]=0.5*d2XiSq_da2(j);
			if (g_malpha[j][j]==0) {
            //cout << endl;
            //cout << "Diagonal element is zero," << endl;
				return;
			}
			if (j>1) {
				for (k = 1; k < j; k++) {
					g_malpha[j][k] =  0.5*d2XiSq_dajk(j,k);
					g_malpha[k][j] =  g_malpha[j][k];
				}  //for k
			}    //if j
		}      //for j
		for (j = 1; j <= g_nParameter; j++) {
			if (g_malpha[j][j] < 0.0) {
				g_malpha[j][j] = -g_malpha[j][j];
				if (j > 1) {
					for (k = 1; k < j; k++) {
						g_malpha[j][k] = 0;
						g_malpha[k][j] = 0;
					} //for k
				}   //if j
			}     //if g_malpha
		}       //for j
	}// if if (g_linearFn)
}

// ----------------------- invert g_vParameter matrix
static double MatInv()	
{
	int i, j, k, L, ik[10], jk[10];
	double aMax, save, det;
	
	det = 0;
//------------------------------------  find largest element 
	for (k = 1; k <= g_nParameter; k++)
	{
		aMax = 0;
FIND_AMAX:	
		for (i = k; i <= g_nParameter; i++)
		{
			for (j = k; j <= g_nParameter;j++)
			{
				if  (fabs(g_malpha[i][j]) > fabs(aMax)) 
				{
					aMax = g_malpha[i][j];
					ik[k] = i;
					jk[k] = j;
				}   //if
			}  //for j
		}  //for i
		if (aMax == 0)  return(det);  //with 0 determinant as signal
		det = 1;
// -------------------------------------- interchange rows and columns to put aMax in g_malpha[k,k]---
		i = ik[k];
		if (i < k) goto FIND_AMAX;
		else if (i > k) 
		{
			for (j = 1;j <= g_nParameter;j++)
			{
				save = g_malpha[k][j];
				g_malpha[k][j] = g_malpha[i][j];
				g_malpha[i][j] = -save;
			}	  //for j
		}  //else if 
		j = jk[k];
		if	(j < k) goto FIND_AMAX;
		else if (j > k)
		{
			for (i = 1; i <= g_nParameter; i++)
			{
				save = g_malpha[i][k];
				g_malpha[i][k] = g_malpha[i][j];
				g_malpha[i][j] = -save;
			}	 //for i
		}//else if j
// ---------------------------------------- accumulate elements of inverse matrix 
		for (i = 1; i <= g_nParameter; i++)
		{
			if (i != k) g_malpha[i][k] = -g_malpha[i][k]/aMax;
		}	//for i
		for (i = 1; i <= g_nParameter; i++)
		{
			for (j = 1; j <= g_nParameter;j++) 
			{
				if ((i != k) && (j != k)) g_malpha[i][j] = g_malpha[i][j] + g_malpha[i][k]*g_malpha[k][j];
			}	//for j
		}   //for i
		for (j = 1; j <= g_nParameter;j++)
		{
			if (j != k)  g_malpha[k][j] = g_malpha[k][j]/aMax;
		}           //for j
		g_malpha[k][k] = 1/aMax;
		det = det * aMax;
	} //for k
// ------------------------------------------ restore ordering of matrix 
	for (L = 1; L <= g_nParameter; L++)  
	{
		k = g_nParameter + 1 - L;
		j = ik[k];
		if (j > k) 
		{
			for (i = 1; i <= g_nParameter; i++) 
			{
				save        = g_malpha[i][k];
				g_malpha[i][k] = -g_malpha[i][j];
				g_malpha[i][j] = save;
			}  //for i
		}  //if j
		i = jk[k];
		if (i > k)
		{
			for (j = 1; j <= g_nParameter;j++)
			{
				save        =  g_malpha[k][j];
				g_malpha[k][j] = -g_malpha[i][j];
				g_malpha[i][j] =  save;
			} //for j
		} //if i
	}  //for L
	return(det);
}

static void SquareByRow() // multiply square matrix by row matrix
{
	int i,j;
	for (i=1;i<=g_nParameter;i++) {
      if(LinearUserFunction) {
			g_vParameter[i]=0.0;
			for (j=1;j<=g_nParameter;j++)
				g_vParameter[i]+=g_vbeta[j]*g_malpha[i][j];
      } else {
         g_vda[i]=0.0;
         for (j=1;j<=g_nParameter;j++)
            g_vda[i]+=g_vbeta[j]*g_malpha[i][j];
      }
   }
}

// ----Standard deviations calc'd from chiSq change of 1 (parabola fit at Xi2 minimum)
static void SigParab()
{
	int j;
   double chiSq1,chiSq2,chiSq3;

	for(j = 1; j<= g_nParameter; j++) {
		chiSq2 = CalcChiSq();
		g_vParameter[j]   = g_vParameter[j] + g_vParameterInc[j];
		chiSq3 = CalcChiSq();
		g_vParameter[j]   = g_vParameter[j] - 2*g_vParameterInc[j];
		chiSq1 = CalcChiSq();
		g_vParameter[j]   = g_vParameter[j] + g_vParameterInc[j];
		g_vsiga[j] = g_vParameterInc[j]*sqrt(2/(chiSq1-2*chiSq2+chiSq3));
	}
}
// ---standard deviations as sqrt of diagonal elements of eror matrix.
static void SigMatrix()
{
	int j;
	for (j = 1; j <= g_nParameter;j++)		

		g_vsiga[j] = sqrt(g_malpha[j][j]);
}

//-------------------------  Non-linear Fits ------------------------------------

//Numerical Derivatives------------------------------
// Can be replaced by analytic derivatives, if they can be calculated. 
// However, numerical calculation is general, and convenient.
static double dXiSq_da(int j)		//See Eq. 8.26 - this sums over nPts
{
	double  static XiSq0;
	double   XiSqPlus, dXiSqDa;

	if (j == 1)   
		XiSq0 = CalcChiSq();				//starting point-calculate it once
	g_vParameter[j] = g_vParameter[j] + g_vParameterInc[j];
	XiSqPlus  = CalcChiSq();
	g_vParameter[j] = g_vParameter[j] - g_vParameterInc[j];		//restore
	dXiSqDa   =  (XiSqPlus - XiSq0)/(g_vParameterInc[j]);
	return (dXiSqDa);
}

static double d2XiSq_da2(int j) // See Eq. 8.35  - this sums over nPts
{
	double tem; 
	int i;

   if (j == 1) {
      for (i=1; i<= g_nData; i++) 
         g_y_0[i]=yFunction(g_vX[i]); //Starting point-calculate it once
   }
	g_vParameter[j]+=g_vParameterInc[j];
	tem=0.0;
	for (i = 1; i <= g_nData; i++) {
      g_mdYda[i][j]=(yFunction(g_vX[i])-g_y_0[i])/g_vParameterInc[j]/g_vSig[i];
      tem=tem+SQUARE(g_mdYda[i][j]);
   }
   g_vParameter[j]-=g_vParameterInc[j];
   return(2*tem);
}

static double d2XiSq_dajk(int j, int k)	//See Eq. 8.35
{
	double tem = 0.0;
	int i;
	for (i = 1; i <= g_nData; i++) {
 		tem = tem + g_mdYda[i][j]*g_mdYda[i][k];
	}
	return(2*tem);
}

// ====================  Non-linear Fitting Routines ==================================
//---------------------------- GridSearch ---------------------------------------------

// Program 8.1:Non-linear least-squares fit by the grid-search method

static void Gridls(double *chiSqr)
{
//
	double delta;
	double save, delta1, del1, del2, aa, bb, cc, disc, g_malpha, x1, x2;
	int j;
   double chiSq1,chiSq2,chiSq3;

	//cout << "enter Grids, g_vX[1], g_vY[1] " <<g_vX[1] <<"  "<<g_vY[1]<<"  ";  cin >> j;

	chiSq2 = CalcChiSq();
// -find local minimum for each parameter- 
	for (j = 1; j <= g_nParameter;j++)
    {
		delta    = g_vParameterInc[j];
		g_vParameter[j]     = g_vParameter[j] + delta;
		chiSq3   = CalcChiSq();
		if (chiSq3 > chiSq2) 
		{                  //started in wrong direction
			delta  = -delta;
			g_vParameter[j]   =  g_vParameter[j] + delta;
			save   =  chiSq2;    //interchange 2 and 3 so 3 is lower
			chiSq2 =  chiSq3;
			chiSq3 =  save;
		}
// -Increment or decrement g_vParameter[j] until chi squared increases- 
		do
		{
			chiSq1 = chiSq2; //move back to prepare for quad fit
			chiSq2 = chiSq3;
			g_vParameter[j]   = g_vParameter[j] + delta;
			chiSq3 = CalcChiSq();
		}  while (chiSq3 < chiSq2);
   
// -Find minimum of parabola defined by last three points  -
		del1 = chiSq2 - chiSq1;
		del2 = chiSq3 - 2*chiSq2 + chiSq1;
		delta1 = delta * (del1/del2 + 1.5);
		g_vParameter[j] = g_vParameter[j]  - delta1;
		chiSq2 = CalcChiSq();    //	at new local minimum
// -Adjust delta for change of 2 from chiSq at minimum  -
		aa = del2/2;								//chiSq = aa*SQUARE(g_vParameter[j] + bb*g_vParameter[j] + cc
		bb = del1 - del2/2;
		cc = chiSq1-chiSq2;
		disc = SQUARE(bb) -4*aa*(cc-2);				//chiSqr difference=2
		if (disc > 0) 								//if not true, then probably not parabolic yet
		{
			disc = sqrt(disc) ;
			g_malpha = (-bb - disc)/(2*aa);
			x1 = g_malpha*delta +  g_vParameter[1] - 2*delta;		//	g_vParameter[j] at chiSq minimum+2
			disc = SQUARE(bb) - 4*aa*cc;
			if (disc > 0) 
				disc=sqrt(disc); 
			else 
				disc=0;		// elim round err
			g_malpha = (-bb - disc)/(2*aa);
			x2 = g_malpha*delta + g_vParameter[1] - 2*delta;		// at chiSq minimum
			delta = x1 - x2;
			g_vParameterInc[j] = delta;
		}
	}    // for j = 1 to m}
  *chiSqr = chiSq2;
}

//---------------------------- GradSearch ---------------------------------------------
//Program 8.2 Non-linear least-squares fit by gradient-search method}

static double grad[10];
static void Gradls(double *chiSqr, double stepDown)
// label  5;
{
	double stepSum,step1;
	double fract = 0.001;
	int   j;
   double chiSq1,chiSq2,chiSq3;

	CalcGrad();   //calculate the gradient
   chiSq2=CalcChiSq(); //Y.Kim,20030610
//-Evaluate chiSqr at new point and make sure chiSqr decreases-
	do
	{
		for (j = 1; j <= g_nParameter;j++)
			g_vParameter[j] = g_vParameter[j] + stepDown * grad[j]; //slide down
		chiSq3 = CalcChiSq();
		if (chiSq3 >= chiSq2)
		{                         //must have overshot minimum
			for (j = 1; j <= g_nParameter;j++)
				g_vParameter[j] = g_vParameter[j] - stepDown * grad[j]; //restore
			stepDown = stepDown/2;              //decrease stepSize
		}
	} while (chiSq3 > chiSq2);
	stepSum = 0;
// -- Increment parameters until chiSqr starts to increase -- 
	do
	{
		stepSum = stepSum + stepDown;   //counts total increment
		chiSq1 = chiSq2;
		chiSq2 = chiSq3;
		for (j = 1; j <= g_nParameter;j++) 
			g_vParameter[j] = g_vParameter[j] + stepDown * grad[j];
		chiSq3 = CalcChiSq();
	} while (chiSq3 <= chiSq2);
// -- Find minimum of parabola defined by last three points -- 
	step1=stepDown*((chiSq3-chiSq2)/(chiSq1-2*chiSq2+chiSq3)+0.5);
	for (j = 1; j <= g_nParameter;j++)
		g_vParameter[j] = g_vParameter[j] - step1 * grad[j];    //move to minimum
	*chiSqr = CalcChiSq();
	stepDown = stepSum;                 //start with this next time
}

static void CalcGrad()
{
	double fract = 0.001;
	int   j;
	double  dA, sum;
   double chiSq1,chiSq2;

	sum = 0.0;
	chiSq2 = CalcChiSq();

	for (j = 1; j <=  g_nParameter;j++)
  {
		dA  = fract * g_vParameterInc[j];     //differential element for gradent
		g_vParameter[j]    = g_vParameter[j] + dA;
		chiSq1  = CalcChiSq();
		g_vParameter[j]    = g_vParameter[j] - dA;
		grad[j] = chiSq2 - chiSq1;   //2*g_vda*grad
		sum     = sum + SQUARE(grad[j]);
  }
	for (j = 1; j <= g_nParameter;j++)
		grad[j] =  g_vParameterInc[j]*grad[j]/sqrt(sum); //step * grad
}

//----------------------------------- Expand Function -------------------------------------
//Program  8.3: Non-linear least-squares fit by expansion of the fitting function
 
static void ChiFit(double *chiSqr)			// double  det, chiSq1;
{
	int  j;
	double det;

	MakeBeta();
	MakeAlpha();
	det=MatInv();					// Invert matrix
	SquareByRow();				// Evalulate parameter increments
	for (j = 1; j <= g_nParameter;j++)
		g_vParameter[j] = g_vParameter[j] + g_vda[j];	// Increment to next solution. 
	*chiSqr=CalcChiSq();
	return;
}

// ------------------------------------- Marquard ---------------------------------------------
//Program 8.4: Non-linear least-squares fit by the gradient-expansion (Marquardt) method

static void Marquardt(double *chiSqr, double chiCut, double lambda)
{
	int j;
	double det,chiSq1;

TOP:
	MakeBeta();
	MakeAlpha();
	for (j=1;j<=g_nParameter;j++)
      g_malpha[j][j]=(1+lambda)*g_malpha[j][j];
	det=MatInv(); //Invert matrix 
   if (lambda>0) { //On final call, enter with lambda=0 to get the error matrix
		SquareByRow(); //Evaluate parameter increments 
		chiSq1=*chiSqr;
		for (j=1;j<=g_nParameter;j++) g_vParameter[j]+=g_vda[j]; //Incr to next solution
		*chiSqr=CalcChiSq();
		if (*chiSqr>(chiSq1+chiCut)) {
			for (j=1;j<=g_nParameter;j++) g_vParameter[j]-=g_vda[j]; //Return to prev solution
			*chiSqr=CalcChiSq();
			lambda=10*lambda; //and repeat the calc, with larger lambda
			goto TOP;
		}
		lambda=0.1*lambda;
	}
}

// --------------------------------  Output to Disk File -------------------------------------------

/*
static void FitOut(char outFile[], double chi2, char aErrorsFrom)
{
	int i, k, j ,nFree;
	double X2Prob, chi2PerDof;

	ofstream fOut(outFile);			// open file for output 
	fOut << setiosflags(ios::fixed |ios::showpoint);
	
	nFree=g_nData-g_nParameter;
	chi2PerDof=chi2/nFree;
	X2Prob=100*ChiProb(nFree,chi2);
	switch(aErrorsFrom) {
   case 'D':break; // already calculated in LineFit
   case 'C':SigParab();break; // vary chi^2 by 1
   case 'M':SigMatrix();break;// error Matrix
	}

	fOut
      <<endl
		<< " ChiSqr =" 
		<< setprecision(1)<<chi2 
		<< " for " 
		<< nFree 
		<<" deg of freedom," 
		<<" chiSqr/dof =" 
		<< setprecision(1)<<chi2PerDof 
		<< " Prob =" 
		<< setprecision(1)<< X2Prob
		<<"%"
		<< endl;
	fOut 
		<< " Fitted Parameters:  g_vParameter[i] +- sig-g_vParameter[i]"
		<< endl;
	for (i=1;i<=g_nParameter;i++)  	
		fOut 
			<<setprecision(4)<<setw(10) << g_vParameter[i]
			<<"  +-  "
			<<setw(10)<< g_vsiga[i]
			<< "  " 
			<< endl;
	fOut << endl; 	

	if (!(aErrorsFrom == 'M'))
		cout <<  endl <<" Output written to disk file " << outFile << endl;
	else {
		fOut << " Error Matrix" << endl;
		for (k = 1; k <= g_nParameter; k++) {
			for (j = 1; j <= g_nParameter;j++) { 
				fOut 
					<<"    "
					<< setprecision(8) <<setw(12) 
					<< g_malpha[k][j];
			}
			fOut << endl;
		}
		fOut << endl;
		cout << endl <<"Output written to disk file " << outFile << endl;
	}

// Tabulate data with fitted Y
	fOut << "      pt #             X(cm)      Y            dY         g_yCalc "<<endl;
	for (i=1;i<=g_nData;i++) {
      fOut 
         << setiosflags( ios::right )
         << setprecision(1)<<setw(10)<< i 
         << setprecision(4)
         << setw(16)<< g_vX[i] 
			<< setw(12)<< g_vY[i]
         << setw(12)<< g_vSig[i]
			<< setw(12)<< g_yCalc[i] 
			<< endl;
	}
	fOut.close();
}
*/

/******************************************************************************/
/* End of fitutil.cpp */

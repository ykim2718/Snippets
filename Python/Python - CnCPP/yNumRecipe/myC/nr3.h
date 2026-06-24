/******************************************************************************/
/*                                                                            */
/*                           File name : nr3.h                                */
/*                       Originated by : H.T. Lau                             */
/*           "A Numerical Library in C for Scientists and Engineers," 1995    */
/*                            Modifier : Kim,YongShik                         */
/*                       creating date : 43260719                             */
/*                             updated : ...                                  */
/* 4336 0720,1208,____,____,____,____,____,____,____,____,____,____,____,____ */
/*                                                                            */
/******************************************************************************/

void airy(double z,double *ai,double *aid,double *bi,double *bid,
          double *expon,int first);
void rk1(double *x, double a, double b, double *y, double ya,
			double (*fxy)(double, double), double e[], double d[], int fi);
void rk3(double *x, double a, double b, double *y, double ya,
			double *z, double za, double (*fxy)(double, double),
			double e[], double d[], int fi);

/******************************************************************************/
/* nr3.h */



/******************************************************************************

       File: yNr3.h
Description: "A Numerical Library in C for Scientists and Engineers," 1995 
    Creator: H.T. Lau
       Date: 1995
   Revision: Kim, Yongshik (copyRight)
     Update: 43260719,
	         4336 0720,1208
Last Update: 20160325

*******************************************************************************/

#ifndef yNr3_header_INSTALLED
#define yNr3_header_INSTALLED 1

void airy(double z,double *ai,double *aid,double *bi,double *bid,
        double *expon,int first);
void rk1(double *x, double a, double b, double *y, double ya,
	double (*fxy)(double, double), double e[], double d[], int fi);
void rk3(double *x, double a, double b, double *y, double ya,
	double *z, double za, double (*fxy)(double, double),
	double e[], double d[], int fi);

#endif /* yNr3.h */

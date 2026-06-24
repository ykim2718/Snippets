/******************************************************************************

       File: yNr4.h
Description: 1980,DiDonato,Computation of the Integral of ++ (FORTRAN).f95
    Creator: A. R. Didonato, R. K Hageman
	 Source: "Computation of the integral of the bivariate normal distribution
	         over arbitrary polygons", June 1980, Naval Surface Weapons Center
       Date: June 1980
   Revision: Kim, Yongshik (copyRight)
     Update: 2016.1.13
Last Update: 2016.3.25 - 0402

*******************************************************************************/

#ifndef yNr4_header_INSTALLED
#define yNr4_header_INSTALLED 1

#include "yNrecipe.h"

double yZscore1d( double x, UVNParameter *n );
//double (*yZscore2d( double x, double y, BVNParameter *n ))[2];
double *yZscore2d( double x, double y, BVNParameter *n );
double yBVNCDFOCP( double *vXB0, double *vYB0, int vSize, BVNParameter *n, double *Area );
double yBVSNCDFOCP( double *vXB0, double *vYB0, int vSize, double *Area );

void demo_Fig_33_on_page_52();
void demo_Fig_35_on_page_54();
void demo_Fig_40_on_page_59();
void demo_rectangle_9x9(int set);

#endif /* yNr4.h */

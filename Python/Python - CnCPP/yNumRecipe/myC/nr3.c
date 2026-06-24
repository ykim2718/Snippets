#include <math.h>

#define double double

/*----------------------------------------------------------------------------*/

void airy(double z, double *ai, double *aid, double *bi, double *bid,
			double *expon, int first)
{
	int n,l;
	double s,t,u,v,sc,tc,uc,vc,x,k1,k2,k3,k4,c,zt,si,co,expzt,sqrtz,wwl,
			pl,pl1,pl2,pl3;
	static double c1,c2,sqrt3,sqrt1opi,pio4,xx[11],ww[11];

	if (first) {
		sqrt3=1.73205080756887729;
		sqrt1opi=0.56418958354775629;
		pio4=0.78539816339744831;
		c1=0.355028053887817;
		c2=0.258819403792807;
		xx[1] =1.4083081072180964e1;
		xx[2] =1.0214885479197331e1;
		xx[3] =7.4416018450450930;
		xx[4] =5.3070943061781927;
		xx[5] =3.6340135029132462;
		xx[6] =2.3310652303052450;
		xx[7] =1.3447970842609268;
		xx[8] =6.4188858369567296e-1;
		xx[9] =2.0100345998121046e-1;
		xx[10]=8.0594359172052833e-3;
		ww[1] =3.1542515762964787e-14;
		ww[2] =6.6394210819584921e-11;
		ww[3] =1.7583889061345669e-8;
		ww[4] =1.3712392370435815e-6;
		ww[5] =4.4350966639284350e-5;
		ww[6] =7.1555010917718255e-4;
		ww[7] =6.4889566103335381e-3;
		ww[8] =3.6440415875773282e-2;
		ww[9] =1.4399792418590999e-1;
		ww[10]=8.1231141336261486e-1;
	}
	*expon=0.0;
	if (z >= -5.0 && z <= 8.0) {
		u=v=t=uc=vc=tc=1.0;
		s=sc=0.5;
		n=3;
		x=z*z*z;
		while (fabs(u)+fabs(v)+fabs(s)+fabs(t) > 1.0e-18) {
			u=u*x/(n*(n-1));
			v=v*x/(n*(n+1));
			s=s*x/(n*(n+2));
			t=t*x/(n*(n-2));
			uc += u;
			vc += v;
			sc += s;
			tc += t;
			n += 3;
		}
		*bi=sqrt3*(c1*uc+c2*z*vc);
		*bid=sqrt3*(c1*z*z*sc+c2*tc);
		if (z < 2.5) {
			*ai=c1*uc-c2*z*vc;
			*aid=c1*sc*z*z-c2*tc;
			return;
		}
	}
	k1=k2=k3=k4=0.0;
	sqrtz=sqrt(fabs(z));
	zt=0.666666666666667*fabs(z)*sqrtz;
	c=sqrt1opi/sqrt(sqrtz);
	if (z < 0.0) {
		z = -z;
		co=cos(zt-pio4);
		si=sin(zt-pio4);
		for (l=1; l<=10; l++) {
			wwl=ww[l];
			pl=xx[l]/zt;
			pl2=pl*pl;
			pl1=1.0+pl2;
			pl3=pl1*pl1;
			k1 += wwl/pl1;
			k2 += wwl*pl/pl1;
			k3 += wwl*pl*(1.0+pl*(2.0/zt+pl))/pl3;
			k4 += wwl*(-1.0-pl*(1.0+pl*(zt-pl))/zt)/pl3;
		}
		*ai=c*(co*k1+si*k2);
		*aid=0.25*(*ai)/z-c*sqrtz*(co*k3+si*k4);
		*bi=c*(co*k2-si*k1);
		*bid=0.25*(*bi)/z-c*sqrtz*(co*k4-si*k3);
	} else {
		if (z < 9.0)
			expzt=exp(zt);
		else {
			expzt=1.0;
			*expon=zt;
		}
		for (l=1; l<=10; l++) {
			wwl=ww[l];
			pl=xx[l]/zt;
			pl1=1.0+pl;
			pl2=1.0-pl;
			k1 += wwl/pl1;
			k2 += wwl*pl/(zt*pl1*pl1);
			k3 += wwl/pl2;
			k4 += wwl*pl/(zt*pl2*pl2);
		}
		*ai=0.5*c*k1/expzt;
		*aid=(*ai)*(-0.25/z-sqrtz)+0.5*c*sqrtz*k2/expzt;
		if (z >= 8.0) {
			*bi=c*k3*expzt;
			*bid=(*bi)*(sqrtz-0.25/z)-c*k4*sqrtz*expzt;
		}
	}
}

/*----------------------------------------------------------------------------*/

void rk1(double *x, double a, double b, double *y, double ya,
			double (*fxy)(double, double), double e[], double d[], int fi)
{
	int last,first,reject,test,ta,tb;
	double e1,e2,xl,yl,h,ind,hmin,absh,k0,k1,k2,k3,k4,k5,discr,tol,mu,
			mu1,fh,hl;

	if (fi) {
		d[3]=a;
		d[4]=ya;
	}
	d[1]=0.0;
	xl=d[3];
	yl=d[4];
	if (fi) d[2]=b-d[3];
	absh=h=fabs(d[2]);
	if (b-xl < 0.0) h = -h;
	ind=fabs(b-xl);
	hmin=ind*e[1]+e[2];
	e1=e[1]/ind;
	e2=e[2]/ind;
	first=1;
	test=1;
	if (fi) {
		last=1;
		test=0;
	}
	while (1) {
		if (test) {
			absh=fabs(h);
			if (absh < hmin) {
				h = (h > 0.0) ? hmin : -hmin;
				absh=hmin;
			}
			ta=(h >= b-xl);
			tb=(h >= 0.0);
			if ((ta && tb) || (!(ta || tb))) {
				d[2]=h;
				last=1;
				h=b-xl;
				absh=fabs(h);
			} else
				last=0;
		}
		test=1;
		*x=xl;
		*y=yl;
		k0=(*fxy)(*x,*y)*h;
		*x=xl+h/4.5;
		*y=yl+k0/4.5;
		k1=(*fxy)(*x,*y)*h;
		*x=xl+h/3.0;
		*y=yl+(k0+k1*3.0)/12.0;
		k2=(*fxy)(*x,*y)*h;
		*x=xl+h*0.5;
		*y=yl+(k0+k2*3.0)/8.0;
		k3=(*fxy)(*x,*y)*h;
		*x=xl+h*0.8;
		*y=yl+(k0*53.0-k1*135.0+k2*126.0+k3*56.0)/125.0;
		k4=(*fxy)(*x,*y)*h;
		*x = (last ? b : xl+h);
		*y=yl+(k0*133.0-k1*378.0+k2*276.0+k3*112.0+k4*25.0)/168.0;
		k5=(*fxy)(*x,*y)*h;
		discr=fabs(k0*21.0-k2*162.0+k3*224.0-k4*125.0+k5*42.0)/14.0;
		tol=fabs(k0)*e1+absh*e2;
		reject = discr > tol;
		mu=tol/(tol+discr)+0.45;
		if (reject) {
			if (absh <= hmin) {
				d[1] += 1.0;
				*y=yl;
				first=1;
				if (b == *x) break;
				xl = *x;
				yl = *y;
			} else
				h *= mu;
		} else {
			if (first) {
				first=0;
				hl=h;
				h *= mu;
			} else {
				fh=mu*h/hl+mu-mu1;
				hl=h;
				h *= fh;
			}
			mu1=mu;
			*y=yl+(-k0*63.0+k1*189.0-k2*36.0-k3*112.0+k4*50.0)/28.0;
			k5=(*fxy)(*x,*y)*hl;
			*y=yl+(k0*35.0+k2*162.0+k4*125.0+k5*14.0)/336.0;
			if (b == *x) break;
			xl = *x;
			yl = *y;
		}
	}
	if (!last) d[2]=h;
	d[3] = *x;
	d[4] = *y;
}

/*----------------------------------------------------------------------------*/
void rk3(double *x, double a, double b, double *y, double ya,
			double *z, double za, double (*fxy)(double, double),
			double e[], double d[], int fi)
{
	int last,first,reject,test,ta,tb;
	double e1,e2,e3,e4,xl,yl,zl,h,ind,hmin,hl,absh,k0,k1,k2,k3,k4,
			k5,discry,discrz,toly,tolz,mu,mu1,fhy,fhz;

	if (fi) {
		d[3]=a;
		d[4]=ya;
		d[5]=za;
	}
	d[1]=0.0;
	xl=d[3];
	yl=d[4];
	zl=d[5];
	if (fi) d[2]=b-d[3];
	absh=h=fabs(d[2]);
	if (b-xl < 0.0) h = -h;
	ind=fabs(b-xl);
	hmin=ind*e[1]+e[2];
	hl=ind*e[3]+e[4];
	if (hl < hmin) hmin=hl;
	e1=e[1]/ind;
	e2=e[2]/ind;
	e3=e[3]/ind;
	e4=e[4]/ind;
	first=reject=1;
	test=1;
	if (fi) {
		last=1;
		test=0;
	}
	while (1) {
		if (test) {
			absh=fabs(h);
			if (absh < hmin) {
				h = (h > 0.0) ? hmin : -hmin;
				absh=hmin;
			}
			ta=(h >= b-xl);
			tb=(h >= 0.0);
			if ((ta && tb) || (!(ta || tb))) {
				d[2]=h;
				last=1;
				h=b-xl;
				absh=fabs(h);
			} else
				last=0;
		}
		test=1;
		if (reject) {
			*x=xl;
			*y=yl;
			k0=(*fxy)(*x,*y)*h;
		} else
			k0=k5*h/hl;
		*x=xl+0.276393202250021*h;
		*y=yl+(zl*0.276393202250021+k0*0.038196601125011)*h;
		k1=(*fxy)(*x,*y)*h;
		*x=xl+0.723606797749979*h;
		*y=yl+(zl*0.723606797749979+k1*0.261803398874989)*h;
		k2=(*fxy)(*x,*y)*h;
		*x=xl+h*0.5;
		*y=yl+(zl*0.5+k0*0.046875+k1*0.079824155839840-
					k2*0.001699155839840)*h;
		k4=(*fxy)(*x,*y)*h;
		*x = (last ? b : xl+h);
		*y=yl+(zl+k0*0.309016994374947+k2*0.190983005625053)*h;
		k3=(*fxy)(*x,*y)*h;
		*y=yl+(zl+k0*0.083333333333333+k1*0.301502832395825+
					k2*0.115163834270842)*h;
		k5=(*fxy)(*x,*y)*h;
		discry=fabs((-k0*0.5+k1*1.809016994374947+
					k2*0.690983005625053-k4*2.0)*h);
		discrz=fabs((k0-k3)*2.0-(k1+k2)*10.0+k4*16.0+k5*4.0);
		toly=absh*(fabs(zl)*e1+e2);
		tolz=fabs(k0)*e3+absh*e4;
		reject=(discry > toly || discrz > tolz);
		fhy=discry/toly;
		fhz=discrz/tolz;
		if (fhz > fhy) fhy=fhz;
		mu=1.0/(1.0+fhy)+0.45;
		if (reject) {
			if (absh <= hmin) {
				d[1] += 1.0;
				*y=yl;
				*z=zl;
				first=1;
				if (b == *x) break;
				xl = *x;
				yl = *y;
				zl = *z;
			} else
				h *= mu;
		} else {
			if (first) {
				first=0;
				hl=h;
				h *= mu;
			} else {
				fhy=mu*h/hl+mu-mu1;
				hl=h;
				h *= fhy;
			}
			mu1=mu;
			*z=zl+(k0+k3)*0.083333333333333+
					(k1+k2)*0.416666666666667;
			if (b == *x) break;
			xl = *x;
			yl = *y;
			zl = *z;
		}
	}
	if (!last) d[2]=h;
	d[3] = *x;
	d[4] = *y;
	d[5] = *z;
}

/*----------------------------------------------------------------------------*/
/* n3.c */
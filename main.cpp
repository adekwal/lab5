#include <iostream>
#include <cstdlib>
#include <math.h>
#include "rk4.h"

/*
{1} dw/dt = - g/l * sin(a)
{2} da/dt = w
{3} a(t0) = a0
{4} w(t0) = w0
*/

void rhs_fun(double t, double* X, double* F);
void veuler(double t, double* X, double h, int n, void (*fun)(double, double*, double*), double* X1);
void vrk4(double t, double* X, double h, int n, void (*fun)(double, double*, double*), double* X1);
void energia(double t, double a, double w, double* F);

double PI = 4 * atan(1.);
double t0 = 0, tk = 10, a0 = 40, w0 = 0;//sekunda zero, sekunda koncowa, poczatkowy kat wychylenia [st], poczatkowa predkosc
double g = 9.80, l = 1, m = 5;
double h = 0.01; int n = 100;//krok calkowania, zmienna do deklaracji tablic

int main()
{
	double t = t0, a = a0, w = w0;//wartosci poczatkowe: 1) czasu, 2) kata, 3) predkosci

	double* F;
	F = (double*)malloc(n * sizeof(F));
	double* X;
	X = (double*)malloc(n * sizeof(X));
	double* X1;
	X1 = (double*)malloc(n * sizeof(X1));

	X[0] = a0*PI/180;//alfa [st] -> alfa [rad]
	X[1] = w;//omega



	rhs_fun(t, X, F); printf("%lf\t", F[0]); printf("%lf\n", F[1]);

	for (int i = 0; i < tk; i += h)
	{
		veuler(t, X, h, n, rhs_fun, X1); printf("%lf\t%lf\n", X[0], X[1]);
	}

	energia(t, a, w, F); printf("%lf\n", F[3]);

	return 0;
}

void rhs_fun(double t, double* X, double* F)//ta funkcja dziala dobrze
{
	F[0] = (-g / l) * sin(X[0]);
	F[1] = X[1];
}
void veuler(double t, double* X, double h, int n, void (*fun)(double, double*, double*), double* X1)
{
	double F[2];
	rhs_fun(t, X, F);
	
	X1[0] = X[0] + h * F[0];
	X1[1] = X[1] + h * F[1];
	X[0] = X1[0];
	X[1] = X1[1];
}
void vrk4(double t, double* X, double h, int n, void (*fun)(double, double*, double*), double* X1)
{

}
void energia(double t, double a, double w, double* F)
{
	F[3] = m * pow(l, 2) / 2 * pow(w, 2) + m * g * l * (1 - cos(a));
}
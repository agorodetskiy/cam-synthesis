#ifndef INTEGRATE
#define INTEGRATE

#include <math.h>
#include <phaseportret_rotating.h>
#include <camprofile.h>

double integrate(double (*f)(double), double a, double b);
double primitive(double (*f)(double), double x);
double integrate_primitive(double (*f)(double), double a, double b);
double primitive_2nd(double (*f)(double), double x);

#endif // INTEGRATE


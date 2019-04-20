#include "integrate.h"

double integrate(double (*f)(double), double a, double b)
{
    double e = 0.01;
    double step = 1;
    double summ_1, summ_2;
    double p;
    do
    {
        summ_1 = 0;
        summ_2 = 0;
        p = a;
        while(p < b)
        {
            summ_1 += ((*f)(p) + (*f)(p + step)) / 2 * step;
            p += step;
        }
        p = a;
        step /= 2;
        while(p < b)
        {
            summ_2 += ((*f)(p) + (*f)(p + step)) / 2 * step;
            p += step;
        }
        step /= 2;
    } while (fabs(summ_2 - summ_1) / 3 > e);
    return summ_2;
}
double primitive(double (*f)(double), double x)
{
    return integrate(f, 0, x);
}
double integrate_primitive(double (*f)(double), double a, double b)
{
    double e = 1;
    double step = 1;
    double summ_1, summ_2;
    double p;
    do
    {
        summ_1 = 0;
        summ_2 = 0;
        p = a;
        while(p < b)
        {
            summ_1 += (primitive(f, p) + primitive(f, p + step)) / 2 * step;
            p += step;
        }
        p = a;
        step /= 2;
        while(p < b)
        {
            summ_2 += (primitive(f, p) + primitive(f, p + step)) / 2 * step;
            p += step;
        }
        step /= 2;
    } while (fabs(summ_2 - summ_1) / 3 > e);
    return summ_2;
}
double primitive_2nd(double (*f)(double), double x)
{
    return integrate_primitive(f, 0, x);
}


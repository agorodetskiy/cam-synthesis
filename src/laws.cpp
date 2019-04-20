#include "laws.h"
#include "parameters.h"
#include <math.h>

void setChoice(sl &f_sl, vl &f_vl, sl &c_sl, vl &c_vl)
{
    switch(far_phase_law)
    {
    case 0:
        f_sl = shiftLaw_sin_sym;
        f_vl = velocityLaw_sin_sym;
        break;
    case 1:
        f_sl = shiftLaw_cos_sym;
        f_vl = velocityLaw_cos_sym;
        break;
    case 2:
        f_sl = shiftLaw_rect_sym;
        f_vl = velocityLaw_rect_sym;
        break;
    case 3:
        f_sl = shiftLaw_line_dec;
        f_vl = velocityLaw_line_dec;
        break;
    }
    switch(close_phase_law)
    {
    case 0:
        c_sl = shiftLaw_sin_sym;
        c_vl = velocityLaw_sin_sym;
        break;
    case 1:
        c_sl = shiftLaw_cos_sym;
        c_vl = velocityLaw_cos_sym;
        break;
    case 2:
        c_sl = shiftLaw_rect_sym;
        c_vl = velocityLaw_rect_sym;
        break;
    case 3:
        c_sl = shiftLaw_line_dec;
        c_vl = velocityLaw_line_dec;
        break;
    }
}

double shiftLaw(double degree, double (*f_ph_law)(double), double (*c_ph_law)(double))
{
    double shift = 0, k = 0;
    if(degree < f_phDegree)
    {
        k = degree / f_phDegree;
        shift = (*f_ph_law)(k);
    }
    else if(degree <= f_phDegree + fs_degree)
        shift = maxShift;
    else if(degree <= f_phDegree + fs_degree + c_phDegree)
    {
        degree = fabs(degree - (f_phDegree + fs_degree + c_phDegree));
        k = degree / c_phDegree;
        shift = (*c_ph_law)(k);
    }
    return shift;
}
double velocityLaw(double degree, double (*f_ph_law)(double, double, bool), double (*c_ph_law)(double, double, bool))
{
    double velocity = 0;
    if(degree < f_phDegree)
    {
        velocity = (*f_ph_law)(degree, f_phDegree, false);
    }
    else if(degree <= f_phDegree + fs_degree)
        velocity = 0;
    else if(degree <= f_phDegree + fs_degree + c_phDegree)
    {
        degree = fabs(degree - (f_phDegree + fs_degree + c_phDegree));
        velocity = (*c_ph_law)(degree, c_phDegree, true);
    }
    return velocity;
}
//----------------------------------------------------------------
double shiftLaw_sin_sym(double k)
{
    double shift = 0;

    if(k == 0.5)
        shift = 0.5 * maxShift;
    else shift = (2*pi*k - sin(2*pi*k)) / (2*pi) * maxShift;

    return shift;
}
double velocityLaw_sin_sym(double degree, double phase_degree, bool isClosing)
{
    double velocity = 0;
    double k = degree / phase_degree;
    if(k == 0.5)
        velocity = 2 * maxShift / (phase_degree * pi / 180);
    else velocity = (1 - cos(2*pi*k)) * maxShift / (phase_degree * pi / 180);

    if(isClosing)
        velocity = -velocity;

    return velocity;
}

double shiftLaw_rect_sym(double k)
{
    double shift = 0;

    if(k < 0.5)
        shift = 2*k*k * maxShift;
    else if(k == 0.5)
        shift = 0.5 * maxShift;
    else
        shift = -(1 - 4*k + 2*k*k) * maxShift;
    return shift;
}
double velocityLaw_rect_sym(double degree, double phase_degree, bool isClosing)
{
    double velocity = 0, correction = maxShift / (phase_degree * pi / 180);
    double k = degree / phase_degree;

    if(k < 0.5)
        velocity = 4*k * correction;
    else if(k == 0.5)
        velocity = 2 * correction;
    else velocity = 4*(1-k) * correction;

    if(isClosing)
        velocity = -velocity;

    return velocity;
}

double shiftLaw_cos_sym(double k)
{
    double shift = 0;

    if(k == 0.5)
        shift = 0.5 * maxShift;
    else
        shift = 1.0/2.0 *(1 - cos(pi*k)) * maxShift;
    return shift;
}
double velocityLaw_cos_sym(double degree, double phase_degree, bool isClosing)
{
    double velocity = 0, correction = maxShift / (phase_degree * pi / 180);
    double k = degree / phase_degree;

    if(k == 0.5)
        velocity = pi / 2.0 * correction;
    else velocity = pi / 2.0 * sin(pi*k) * correction;

    if(isClosing)
        velocity = -velocity;

    return velocity;
}

double shiftLaw_line_dec(double k)
{
    double shift = 0;

    if(k == 0.5)
        shift = 0.5 * maxShift;
    else
        shift = k*k * (3 - 2*k) * maxShift;
    return shift;
}
double velocityLaw_line_dec(double degree, double phase_degree, bool isClosing)
{
    double velocity = 0, correction = maxShift / (phase_degree * pi / 180);
    double k = degree / phase_degree;

    if(k == 0.5)
        velocity = 3.0/2.0 * correction;
    else velocity = 6*k * (1-k) * correction;

    if(isClosing)
        velocity = -velocity;

    return velocity;
}

/*
double shiftLaw_linear(double degree)
{
    double shift = 0;
    double lim1 = pr_degree;
    double lim2 = lim1 + fs_degree;
    double lim3 = lim2 + pr_degree;
    if(degree < lim1)
        shift = maxShift / lim1 * degree;
    else if (degree < lim2)
             shift = maxShift;
    else if(degree < lim3)
             shift = maxShift / (lim2 - lim3) * (degree - lim3);
    return shift;
}*/


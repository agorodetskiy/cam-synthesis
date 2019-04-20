#ifndef LAWS
#define LAWS

typedef double(*sl)(double);
typedef double(*vl)(double, double, bool);

struct motionLaws
{
    sl f_sl, c_sl;
    vl f_vl, c_vl;
};

void setChoice(sl &f_sl, vl &f_vl, sl &c_sl, vl &c_vl);

double shiftLaw(double degree, double (*f_ph_law)(double), double (*c_ph_law)(double));
double velocityLaw(double degree, double(*f_ph_law)(double, double, bool), double(*c_ph_law)(double, double, bool));



double shiftLaw_sin_sym(double k);
double velocityLaw_sin_sym(double degree, double phase_degree, bool isClosing);

double shiftLaw_rect_sym(double k);
double velocityLaw_rect_sym(double degree, double phase_degree, bool isClosing);

double shiftLaw_cos_sym(double k);
double velocityLaw_cos_sym(double degree, double phase_degree, bool isClosing);

double shiftLaw_line_dec(double k);
double velocityLaw_line_dec(double degree, double phase_degree, bool isClosing);

double shiftLaw_linear(double degree);

#endif // LAWS


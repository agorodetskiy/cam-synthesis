#ifndef PHASEPORTRET
#define PHASEPORTRET

#include <math.h>
#include "parameters.h"
#include "laws.h"
#include "camprofile.h"


point* makePhasePortret(double (*far_vL)(double, double, bool), double (*far_sL)(double), double (*close_vL)(double, double, bool), double (*close_sL)(double));

double makeLineFunc_toLeft(double x, point *arr, int index); // функция прямой через точку arr[index], агрумент p,
double makeLineFunc_toRight(double x, point *arr, int index); // функция прямой через точку arr[index], агрумент p,
void findExtrPoints(int &leftPointIndex, int &rightPointIndex, point *arr);
void findIntersection(point &intrscnPoint, point *arr); // находит точку пересечения касательных

void computeS0(double x_intrsc, double y_intrsc, point *arr);

void findKeyPoints(point &intrscnPoint, point *ppArr);


#endif // PHASEPORTRET


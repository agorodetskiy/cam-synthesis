#ifndef CAMPROFILE
#define CAMPROFILE

#include <math.h>
#include "parameters.h"
#include "laws.h"

struct point
{
    double x;
    double y;
    int fromLeftExtrPoint_index;
    int fromRightExtrPoint_index;
    double shift;
};

struct line
{
    double A;
    double B;
    double C;
    point someDot;
};

point* makeCamCentralProfile(sl f_sl, sl c_sl);
point* makeCamCentralProfile_Rot(sl f_sl, sl c_sl);

point* makeCamRealProfile(sl f_sl, sl c_sl);

point makeDirVect(line myLine);
point makeNormVect(line myLine);
point makeDirVect(point p1, point p2);
line makeLineFromVectNDot(point dirVect, point p1);
line lineThrough2Dots(point p1, point p2);
point parallelLinePoint(line myLine);
point findLinesIntrsc(line myLine1, line myLine2);
double pointDistance(point p);
void setRealPoint(point p1, point p2, point* realPointsArr, int i);
point* makeCamRealProfile(point* centralPointsArr, int size);

#endif // CAMPROFILE


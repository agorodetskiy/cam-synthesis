#include "camprofile.h"

point* makeCamCentralProfile(sl f_sl, sl c_sl)
{
    double shift = 0, r = 0;
    double degree_camRotation = 0, degree_centralProfile = 0, degree_correction = 0;
    point* arr = new point[360];
    for(int i = 0; i < 360; i++, degree_camRotation += 1)
    {
        shift = shiftLaw(degree_camRotation, f_sl, c_sl);
        r = sqrt(pow((s_0 + shift), 2) + pow(eccentricity, 2));
        degree_correction = (atan((s_0 + shift) / eccentricity) - atan(s_0 / eccentricity)) / pi * 180;
        degree_centralProfile = degree_camRotation - degree_correction;
        arr[i].x = r * cos(degree_centralProfile * pi / 180.0);
        arr[i].y = -r * sin(degree_centralProfile * pi / 180.0);
        arr[i].shift = shift;
    }
    return arr;
}
point* makeCamCentralProfile_Rot(sl f_sl, sl c_sl)
{
    double shift = 0, r = 0, phi_2i = 0, beta_i = 0;
    double psi_i, phi_1i, delta_i, psi_0;
    const double phi_20 = acos((pow(aw, 2) + pow(pusherLength, 2) - pow(minRadius, 2)) / (2 * pusherLength * aw));

    point* arr = new point[360];
    for(int i = 0; i < 360; i++)
    {
        shift = shiftLaw(i, f_sl, c_sl);
        beta_i = shift / pusherLength; // в радианах
        phi_2i = phi_20 + beta_i;
        r = sqrt(pow((aw), 2) + pow(pusherLength, 2) - 2*aw * pusherLength * cos(phi_2i));

        psi_0 = acos((pow(aw, 2) + pow(minRadius, 2) - pow(pusherLength, 2)) / (2 * aw * minRadius));
        delta_i = asin((pusherLength * sin(phi_2i)) / (r)) - psi_0;
        phi_1i = i;
        psi_i = phi_1i + delta_i;

        arr[i].x = r * cos(psi_i * pi / 180.0);
        arr[i].y = -r * sin(psi_i * pi / 180.0);
    }
    return arr;
}

point* makeCamRealProfile(sl f_sl, sl c_sl)
{
    double shift = 0, r = 0;
    double degree_camRotation = 0, degree_realProfile = 0;
    point* arr = new point[360];
    for(int i = 0; i < 360; i++, degree_camRotation += 1)
    {
        shift = shiftLaw(degree_camRotation, f_sl, c_sl);
        r = sqrt(pow((s_0 + shift - trundle_r), 2) + pow(eccentricity, 2));
        degree_realProfile = degree_camRotation;
        arr[i].x = r * cos(degree_realProfile * pi / 180.0);
        arr[i].y = -r * sin(degree_realProfile * pi / 180.0);
    }
    return arr;
}
point makeDirVect(line myLine)
{
    point tmp;
    tmp.x = -myLine.B;
    tmp.y = myLine.A;
    return tmp;
}
point makeNormVect(line myLine)
{
    point tmp;
    tmp.x = myLine.A;
    tmp.y = myLine.B;
    return tmp;
}

point makeDirVect(point p1, point p2)
{
    point dirVect;
    dirVect.x = p2.x - p1.x;
    dirVect.y = p2.y - p1.y;
    return dirVect;
}
line makeLineFromVectNDot(point dirVect, point p1)
{
    line tmp;

    tmp.A = dirVect.y;
    tmp.B = -dirVect.x;
    tmp.C = dirVect.x * p1.y - dirVect.y * p1.x;
    tmp.someDot = p1;

    return tmp;
}
line lineThrough2Dots(point p1, point p2)
{
    point dirVect = makeDirVect(p1, p2);
    line tmp = makeLineFromVectNDot(dirVect, p1);

    return tmp;
}

point parallelLinePoint(line myLine)
{
    point normVect = makeNormVect(myLine);
    double len = sqrt(pow(normVect.x, 2) + pow(normVect.y, 2));
    normVect.x = normVect.x / len * trundle_r;
    normVect.y = normVect.y / len * trundle_r;

    point p1, p2;
    p1.x = myLine.someDot.x + normVect.x;
    p1.y = myLine.someDot.y + normVect.y;
    p2.x = myLine.someDot.x - normVect.x;
    p2.y = myLine.someDot.y - normVect.y;

    return pointDistance(p1) < pointDistance(p2) ? p1 : p2;
}
line makeParallelLine(line myLine)
{
    point p1 = parallelLinePoint(myLine);
    point dirVect = makeDirVect(myLine);
    line tmp = makeLineFromVectNDot(dirVect, p1);

    return tmp;
}

point findLinesIntrsc(line myLine1, line myLine2)
{
    point p1;
    p1.y = (myLine2.A*myLine1.C - myLine1.A*myLine2.C) / (myLine1.A*myLine2.B - myLine2.A*myLine1.B);
    p1.x = (-myLine1.C - myLine1.B * p1.y) / myLine1.A;
    return p1;
}
double pointDistance(point p)
{
    return sqrt(p.x*p.x + p.y*p.y);
}
void setRealPoint(point p1, point p2, point* realPointsArr, int i)
{
    if (pointDistance(p1) < pointDistance(p2))
    {
        realPointsArr[i].x = p1.x;
        realPointsArr[i].y = p1.y;
    }
    else
    {
        realPointsArr[i].x = p2.x;
        realPointsArr[i].y = p2.y;
    }
}

point* makeCamRealProfile(point* centralPointsArr, int size)
{
    point* realPointsArr = new point[360];

    line myLine1, myLine2, saveFirstParLine;
    line parLine1, parLine2;

    point p1;

    myLine1 = lineThrough2Dots(centralPointsArr[0], centralPointsArr[1]);
    parLine1 = makeParallelLine(myLine1);
    saveFirstParLine = parLine1;

    for(int i = 1; i+1 < size; i++)
    {
        myLine2 = lineThrough2Dots(centralPointsArr[i], centralPointsArr[i+1]);
        parLine2 = makeParallelLine(myLine2);

        p1 = findLinesIntrsc(parLine1, parLine2);
        realPointsArr[i] = p1;

        parLine1 = parLine2;
    }

    myLine2 = lineThrough2Dots(centralPointsArr[size-1], centralPointsArr[0]);
    parLine2 = makeParallelLine(myLine2);
    p1 = findLinesIntrsc(parLine1, parLine2);
    realPointsArr[size-1] = p1;

    p1 = findLinesIntrsc(parLine2, saveFirstParLine);
    realPointsArr[0] = p1;

    return realPointsArr;
}
























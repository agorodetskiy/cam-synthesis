#include "phaseportret.h"

point* makePhasePortret(double (*far_vL)(double, double, bool), double (*far_sL)(double), double (*close_vL)(double, double, bool), double (*close_sL)(double))
{
    point *arr = new point[360];
    for(int i = 0; i < 360; i++)
    {
        arr[i].x = velocityLaw(i, far_vL, close_vL);
        arr[i].y = shiftLaw(i, far_sL, close_sL);

        if(rotationDirection == 1)
        {
            arr[i].x *= -1;
        }
    }
    return arr;
}

double makeLineFunc_toLeft(double x, point *arr, int index) // функция прямой через точку arr[index], агрумент p,
{                                                                  // угол откладывает снизу влево от вертикали
    double p = arr[index].x;
    double q = arr[index].y;
    double k = tan((90 - stressDegree) * pi / 180);
    double b = q - k*p; // q = k*p + b
    return k*x + b;
}
double makeLineFunc_toRight(double x, point *arr, int index) // функция прямой через точку arr[index], агрумент p,
{                                                                  // угол откладывает снизу вправо
    double p = arr[index].x;
    double q = arr[index].y;
    double k = tan((90 + stressDegree) * pi / 180);
    double b = q - k*p; // q = k*p + b
    return k*x + b;
}
void findExtrPoints(int &leftPointIndex, int &rightPointIndex, point *arr)
{
    leftPointIndex = 0;  //index
    rightPointIndex = 0;
    for(int i = 1; i < 360; i++)
    {
        if(makeLineFunc_toRight(0, arr, i) < makeLineFunc_toRight(0, arr, leftPointIndex))
            leftPointIndex = i;
        if(makeLineFunc_toLeft(0, arr, i) < makeLineFunc_toLeft(0, arr, rightPointIndex))
            rightPointIndex = i;
    }
}
void findIntersection(point &intrscnPoint, point *arr) // находит точку пересечения касательных
{
    int leftPointIndex = intrscnPoint.fromLeftExtrPoint_index;
    int rightPointIndex = intrscnPoint.fromRightExtrPoint_index;

    double x1 = arr[leftPointIndex].x;
    double x2 = arr[rightPointIndex].x;
    double y1 = arr[leftPointIndex].y;
    double y2 = arr[rightPointIndex].y;

    float k1 = tan((90.0 + stressDegree) * pi / 180.0);
    float k2 = tan((90.0 - stressDegree) * pi / 180.0);

    double b1 = y1 - k1*x1;
    double b2 = y2 - k2*x2;

    intrscnPoint.x = (b2-b1) / (k1-k2);
    intrscnPoint.y = makeLineFunc_toLeft(intrscnPoint.x, arr, rightPointIndex);
}
void computeS0(double x_intrsc, double y_intrsc, point *arr)
{
    int leftPointIndex = 0, rightPointIndex = 0;
    findExtrPoints(leftPointIndex, rightPointIndex, arr);

    if(eccentricity > x_intrsc)
    {
        s_0 = fabs(makeLineFunc_toRight(eccentricity, arr, leftPointIndex));
    }
    else if(eccentricity < x_intrsc)
    {
        s_0 = fabs(makeLineFunc_toLeft(eccentricity, arr, rightPointIndex));
    }
    else if(eccentricity == x_intrsc)
    {
        s_0 = fabs(y_intrsc);
    }
}
void findKeyPoints(point &intrscnPoint, point *ppArr)
{
    findExtrPoints(intrscnPoint.fromLeftExtrPoint_index, intrscnPoint.fromRightExtrPoint_index, ppArr);
    findIntersection(intrscnPoint, ppArr);

    if(isEccChecked)
    {
        computeS0(intrscnPoint.x, intrscnPoint.y, ppArr);
    }
    else
    {
        eccentricity = intrscnPoint.x;
        s_0 = fabs(intrscnPoint.y);
    }

    minRadius = sqrt(pow(eccentricity, 2) + pow(s_0, 2));
    trundle_r = trundle_k * minRadius;
}





















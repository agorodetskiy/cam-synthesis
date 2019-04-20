#ifndef PHASEPORTRET_ROTATING_H
#define PHASEPORTRET_ROTATING_H

#include <math.h>
#include "laws.h"
#include "camprofile.h"

struct phasePoint
{
    double x;
    double y;
    double shiftAngle;
    double velocity;
    double myStressDegree;
};

struct pointNode
{
    point node;
    pointNode* next;
};
struct pointsList
{
    pointNode* head;
    pointNode* tail;
};

pointsList* makeIntrscPointsList();
void findExtrVelocityPP(int &maxVelPP, int &minVelPP, phasePoint* ppArr, int size);
void determineTempOptions(phasePoint* ppArr, int size);
void findPpStressDegree(phasePoint *ppArr, int size);
point* makeStressDegreeArray(phasePoint *ppArr, int size);
void findExtrSdPpoints(int &minSdId, int &maxSdId, phasePoint *ppArr, int size);
void determineTrueOptions(point &intrscnPoint, phasePoint* ppArr, int size);

void addPointNode(point myPoint, pointsList *myList);

phasePoint* makePhasePortret_Rot(vl f_vl, sl f_sl, vl c_vl, sl c_sl);
double makeLineFunc_toLeft_Rot(double x, phasePoint *arr, int index); // функция прямой через точку arr[index], агрумент p,
double makeLineFunc_toRight_Rot(double x, phasePoint *arr, int index); // функция прямой через точку arr[index], агрумент p,

void linesIntrsc(point &intrscnPoint, phasePoint leftPoint, phasePoint rightPoint);

bool isPointForbidden(point &myPoint, phasePoint *ppArr, int size);
void initIntrscList(pointsList* myList, phasePoint* ppArr, int size);
point chooseIntrscPoint(pointsList* myList);

void findKeyPoints_Rot(int &leftExtrPointIndex, int &rightExtrPointIndex, point &intrscPoint, phasePoint *ppArr, int size);

#endif // PHASEPORTRET_ROTATING_H

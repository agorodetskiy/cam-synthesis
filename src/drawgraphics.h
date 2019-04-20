#ifndef DRAWGRAPHICS
#define DRAWGRAPHICS

#include "widget.h"
#include "ui_widget.h"
#include "integrate.h"
#include "phaseportret.h"
#include "phaseportret_rotating.h"
#include "camprofile.h"
#include "laws.h"

void drawMyGraphic(double (*f)(double), QGraphicsScene *scene, QPen pen);
void drawMyGraphicShift(double (*f1)(double), double (*f2)(double), QGraphicsScene *scene, QPen pen);
void drawMyGraphicVelocity(double (*f1)(double, double, bool), double (*f2)(double, double, bool), QGraphicsScene *scene, QPen pen);
void drawMyGraphicPoint(point *myArr, int size, QGraphicsScene *scene, QPen pen);
void drawMyGraphicStressDegree(phasePoint *ppArr, int size, QGraphicsScene *scene, QPen pen);

void drawMyGraphic_primitive(double (*f)(double), QGraphicsScene *scene, QPen pen);
void drawMyGraphic_primitive_2nd(double (*f)(double), QGraphicsScene *scene, QPen pen);

template <typename T>
void drawPhasePortret(double scale, T *arr, QGraphicsScene *scene, QPen pen)
{
    double x1, y1, x2, y2;
    for(int i = 0; i+1 < 360; i++)
    {
        x1 = arr[i].x * scale;
        y1 = arr[i].y * scale;
        x2 = arr[i+1].x * scale;
        y2 = arr[i+1].y * scale;
        scene->addLine(x1, -y1, x2, -y2, pen);
    }
    scene->addLine(x2, -y2, arr[0].x * scale, -arr[0].y * scale, pen); // соединить последнюю точку с первой
}
template <typename T>
void determineScale(double &scale, T *arr, int height, int width)
{
    double correction = 0.6;
    int xMax = 0, xMin = 0, yMax = 0, yMin = 0;
    for(int i = 1; i < 360; i++)
    {
        if(arr[i].x > arr[xMax].x)
            xMax = i;
        else if (arr[i].x < arr[xMin].x)
            xMin = i;

        if(arr[i].y > arr[yMax].y)
            yMax = i;
        else if (arr[i].y < arr[yMin].y)
            yMin = i;
    }
    double x_minVal = 0, x_maxVal = 0, y_minVal = 0, y_maxVal = 0;
    if(arr[xMin].x < x_minVal)
        x_minVal = arr[xMin].x;
    if(arr[xMax].x > x_maxVal)
        x_maxVal = arr[xMax].x;
    if(arr[yMin].y < y_minVal)
        y_minVal = arr[yMin].y;
    if(arr[yMax].y > y_maxVal)
        y_maxVal = arr[yMax].y;

    double xSize = x_maxVal - x_minVal;
    double ySize = y_maxVal - y_minVal;
    double xScale = width / xSize;
    double yScale = height / ySize;
    scale = (xScale < yScale ? xScale : yScale) * correction;
}
void drawTangents(double scale, point *ppArr, QGraphicsScene *scene, QPen pen);
void drawTangents_Rot(double scale, const point &intrscnPoint, const phasePoint *ppArr, QGraphicsScene *scene, QPen pen);

void drawCamProfile(double scale, point *arr, QGraphicsScene *scene, QPen pen);
void drawMark(double x, double y, double scale, QGraphicsScene *scene, QPen pen);
void drawMarkX(double x, double y, double scale, QGraphicsScene *scene, QPen pen);
void drawAxesAtPhasePortretRot(double scale, const point &intrscnPoint, const phasePoint *ppArr, QGraphicsScene *scene, QPen pen);
void drawAxesAtPhasePortret(double scale, const point &intrscnPoint, const point *ppArr, QGraphicsScene *scene, QPen pen);
void drawCircle(double scale, double x, double y, double radius, QGraphicsScene *scene, QPen pen);
void drawProgressivePusher(double scale, point* central_pArr, int size, QGraphicsScene *scene, QPen thickPen);
void drawRotatingPusher(double scale, point* centralPointsArr, int size, QGraphicsScene *scene, QPen pen);
int findClosestCirclePoint(point pusherCenter, point* centralPointsArr, int size);

void rotateClockwise(double degree, point *pointsArr, int size);
void rotateCounterClockwise(double degree, point *pointsArr, int size);

#endif // DRAWGRAPHICS


#include "drawgraphics.h"

void drawMyGraphic(double (*f)(double), QGraphicsScene *scene, QPen pen)
{
    double x1 = 0;
    double y1 = (*f)(x1);
    double x2, y2;
    for(int i = 1; i <= 360; i += 1.0)
    {
        x2 = i;
        y2 = (*f)(x2);
        scene->addLine(x1, -y1, x2, -y2, pen);
        x1 = x2;
        y1 = y2;
    }
}
void drawMyGraphicShift(sl f1, sl f2, QGraphicsScene *scene, QPen pen)
{
    double x1 = 0;
    double y1 = shiftLaw(x1, f1, f2);
    double x2, y2;
    for(int i = 1; i < 360; i += 1.0)
    {
        x2 = i;
        y2 = shiftLaw(x2, f1, f2);
        scene->addLine(x1, -y1, x2, -y2, pen);
        x1 = x2;
        y1 = y2;
    }
}
void drawMyGraphicVelocity(double (*f1)(double, double, bool), double (*f2)(double, double, bool), QGraphicsScene *scene, QPen pen)
{
    double x1 = 0;
    double y1 = velocityLaw(x1, f1, f2);
    double x2, y2;
    for(int i = 1; i <= 360; i += 1.0)
    {
        x2 = i;
        y2 = velocityLaw(x2, f1, f2);
        scene->addLine(x1, -y1, x2, -y2, pen);
        x1 = x2;
        y1 = y2;
    }
}
void drawMyGraphicPoint(point *myArr, int size, QGraphicsScene *scene, QPen pen)
{
    double x1, y1, x2, y2;
    x1 = myArr[0].x;
    y1 = myArr[0].y;
    for(int i = 1; i < size; i++)
    {
        x2 = myArr[i].x;
        y2 = myArr[i].y;
        scene->addLine(x1*100, -y1*100, x2*100, -y2*100, pen);
        x1 = x2;
        y1 = y2;
    }
}

void drawMyGraphicStressDegree(phasePoint *ppArr, int size, QGraphicsScene *scene, QPen pen)
{
    double x1, y1, x2, y2;
    x1 = 0;
    y1 = ppArr[0].myStressDegree;
    for(int i = 1; i < size; i++)
    {
        x2 = i;
        y2 = ppArr[i].myStressDegree;
        scene->addLine(x1, -y1*200, x2, -y2*200, pen);
        x1 = x2;
        y1 = y2;
    }
}

void drawMyGraphic_primitive(double (*f)(double), QGraphicsScene *scene, QPen pen)
{
    double x1 = 0;
    double y1 = primitive(f, x1);
    double x2, y2;
    for(int i = 1; i <= 360; i += 1.0)
    {
        x2 = i;
        y2 = primitive(f, x2);
        scene->addLine(x1, -y1, x2, -y2, pen);
        x1 = x2;
        y1 = y2;
    }
}
void drawMyGraphic_primitive_2nd(double (*f)(double), QGraphicsScene *scene, QPen pen)
{
    double x1 = 0;
    double y1 = primitive_2nd(f, x1);
    double x2, y2;
    for(int i = 1; i <= 360; i += 1.0)
    {
        x2 = i;
        y2 = primitive_2nd(f, x2);
        scene->addLine(x1, -y1, x2, -y2, pen);
        x1 = x2;
        y1 = y2;
    }
}

void drawTangents(double scale, point *ppArr, QGraphicsScene *scene, QPen pen)
{
    int leftExtrPointIndex = 0, rightExtrPointIndex = 0;
    findExtrPoints(leftExtrPointIndex, rightExtrPointIndex, ppArr);
    int x1, y1, x2, y2;

    x1 = ppArr[leftExtrPointIndex].x;
    y1 = ppArr[leftExtrPointIndex].y;
    x2 = eccentricity;
    y2 = -s_0;

    scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);

    x1 = ppArr[rightExtrPointIndex].x;
    y1 = ppArr[rightExtrPointIndex].y;
    x2 = eccentricity;
    y2 = -s_0;

    scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);

    drawMarkX(ppArr[leftExtrPointIndex].x, ppArr[leftExtrPointIndex].y, scale, scene, pen);
    drawMarkX(ppArr[rightExtrPointIndex].x, ppArr[rightExtrPointIndex].y, scale, scene, pen);
    drawMark(eccentricity, -s_0, scale, scene, pen);
}

void drawTangents_Rot(double scale, const point &intrscnPoint, const phasePoint *ppArr, QGraphicsScene *scene, QPen pen)
{
    int x1, y1, x2, y2;
    int leftExtrPointIndex = intrscnPoint.fromLeftExtrPoint_index;
    int rightExtrPointIndex = intrscnPoint.fromRightExtrPoint_index;

    x1 = ppArr[leftExtrPointIndex].x;
    y1 = ppArr[leftExtrPointIndex].y;
    x2 = intrscnPoint.x;
    y2 = intrscnPoint.y;

    scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);

    x1 = ppArr[rightExtrPointIndex].x;
    y1 = ppArr[rightExtrPointIndex].y;
    x2 = intrscnPoint.x;
    y2 = intrscnPoint.y;

    scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);

    drawMarkX(ppArr[leftExtrPointIndex].x, ppArr[leftExtrPointIndex].y, scale, scene, pen);
    drawMarkX(ppArr[rightExtrPointIndex].x, ppArr[rightExtrPointIndex].y, scale, scene, pen);
    drawMark(intrscnPoint.x, intrscnPoint.y, scale, scene, pen);
}

//void drawTangents_Rot(double scale, phasePoint *arr, QGraphicsScene *scene, QPen pen)
//{
//    int leftPoint = 0, rightPoint = 0;
//    findExtrPoints_Rot(leftPoint, rightPoint, arr);
//    drawMark(arr[leftPoint].x, arr[leftPoint].y, scale, scene, pen);
//    drawMark(arr[rightPoint].x, arr[rightPoint].y, scale, scene, pen);
//    int x1, y1, x2, y2;

//    int index = leftPoint;
//    for(int i = 0; i+1 < 360; i++)
//    {
//        x1 = arr[i].x;
//        y1 = makeLineFunc_toRight_Rot(x1, arr, index);
//        x2 = arr[i+1].x;
//        y2 = makeLineFunc_toRight_Rot(x2, arr, index);
//        scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);
//    }
//    index = rightPoint;
//    for(int i = 0; i+1 < 360; i++)
//    {
//        x1 = arr[i].x;
//        y1 = makeLineFunc_toLeft_Rot(x1, arr, index);
//        x2 = arr[i+1].x;
//        y2 = makeLineFunc_toLeft_Rot(x2, arr, index);
//        scene->addLine(x1*scale, -y1*scale, x2*scale, -y2*scale, pen);
//    }
//}

void drawCamProfile(double scale, point *arr, QGraphicsScene *scene, QPen pen)
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
void drawMark(double x, double y, double scale, QGraphicsScene *scene, QPen pen)
{
    scene->addLine(x * scale-10, -y * scale, x * scale+10, -y * scale, pen);
    scene->addLine(x * scale, -(y * scale+10), x * scale, -(y * scale-10), pen);
}
void drawMarkX(double x, double y, double scale, QGraphicsScene *scene, QPen pen)
{
    scene->addLine(x * scale-10, -(y * scale+10), x * scale+10, -(y * scale-10), pen);
    scene->addLine(x * scale-10, -(y * scale-10), x * scale+10, -(y * scale+10), pen);
}

void drawAxesAtPhasePortretRot(double scale, const point &intrscnPoint, const phasePoint *ppArr, QGraphicsScene *scene, QPen pen)
{
    scene->addLine(-30 * scale, 0, ppArr[intrscnPoint.fromRightExtrPoint_index].x*scale, 0, pen);
    scene->addLine(0, -minRadius * scale, 0, minRadius * scale, pen);

    QGraphicsTextItem *textX = scene->addText("x");
    textX->setPos(ppArr[intrscnPoint.fromRightExtrPoint_index].x * scale, 0);
    QGraphicsTextItem *textY = scene->addText("y");
    textY->setPos(5 * scale, -(minRadius + 10) * scale);

    QGraphicsTextItem *text = scene->addText("Polar system:\nAngle: Sb.\nRadius: Pusher length + Vqb.");
    text->setPos(ppArr[intrscnPoint.fromRightExtrPoint_index].x * scale / 5, 1.5*minRadius * scale);

}
void drawAxesAtPhasePortret(double scale, const point &intrscnPoint, const point *ppArr, QGraphicsScene *scene, QPen pen)
{
    int leftExtrPointIndex = intrscnPoint.fromLeftExtrPoint_index, rightExtrPointIndex = intrscnPoint.fromRightExtrPoint_index;

    scene->addLine(ppArr[leftExtrPointIndex].x * scale, 0, ppArr[rightExtrPointIndex].x * scale, 0, pen);
    scene->addLine(0, (s_0-30) * scale, 0, -(s_0/1.5) * scale, pen);

    QGraphicsTextItem *textX = scene->addText("Vqb");
    textX->setPos(ppArr[rightExtrPointIndex].x * scale, 5 * scale);

    QGraphicsTextItem *textY = scene->addText("Sb");
    textY->setPos(5 * scale, -(s_0/1.5 + 10) * scale);
}

void drawCircle(double scale, double x, double y, double radius, QGraphicsScene *scene, QPen pen)
{
    scene->addEllipse((x-radius)*scale, (y-radius)*scale, 2*radius*scale, 2*radius*scale, pen);
}

void drawProgressivePusher(double scale, point* centralPointsArr, int size, QGraphicsScene *scene, QPen thickPen)
{
    int closestPointId = 0;
    double lineAbscissa = eccentricity;// выяснить почему минус. ecc used для вычислений, а знак только на label?
    for(int i = 0; i < size; i++)
    {
        if(fabs(centralPointsArr[i].x - lineAbscissa) < fabs(centralPointsArr[closestPointId].x - lineAbscissa) &&
                centralPointsArr[i].y < 0)
        {
            closestPointId = i;
        }
    }
    double y = s_0+centralPointsArr[closestPointId].shift;

    drawCircle(scale, lineAbscissa, y, trundle_r, scene, thickPen);
    drawCircle(scale, lineAbscissa, y, trundle_r*0.1, scene, thickPen);

    scene->addLine(lineAbscissa*scale, (y+trundle_r*0.1)*scale, lineAbscissa*scale, (y+trundle_r*2.2)*scale, thickPen);
}

void drawRotatingPusher(double scale, point* centralPointsArr, int size, QGraphicsScene *scene, QPen pen)
{
    point pusherCenter;
    pusherCenter.x = -aw;
    pusherCenter.y = 0;

    int minDistPointId = findClosestCirclePoint(pusherCenter, centralPointsArr, size);

    drawCircle(scale, centralPointsArr[minDistPointId].x, -centralPointsArr[minDistPointId].y, trundle_r, scene, pen);
    drawCircle(scale, centralPointsArr[minDistPointId].x, -centralPointsArr[minDistPointId].y, trundle_r*0.1, scene, pen);

    QPen thinPen(Qt::black);
    drawMark(pusherCenter.x, pusherCenter.y, scale, scene, thinPen);
    scene->addLine(pusherCenter.x*scale, -pusherCenter.y*scale, centralPointsArr[minDistPointId].x*scale, -centralPointsArr[minDistPointId].y*scale, pen);
}
int findClosestCirclePoint(point pusherCenter, point* centralPointsArr, int size) //return id
{
    double dist = 0;

    int minDistPointId = 0;
    double min_dist = fabs(sqrt(pow(centralPointsArr[minDistPointId].x - pusherCenter.x, 2)
                           + pow(centralPointsArr[minDistPointId].y - pusherCenter.y, 2))
                      - aw);


    for(int i = 1; i < size; i++)
    {
        dist = fabs(sqrt(pow(centralPointsArr[i].x - pusherCenter.x, 2) + pow(centralPointsArr[i].y - pusherCenter.y, 2))
                - aw);
        if(dist < min_dist && centralPointsArr[i].y >= 0)
        {
            min_dist = dist;
            minDistPointId = i;
        }
    }

    return minDistPointId;
}

void rotateClockwise(double degree, point *pointsArr, int size)
{
    double theta = degree * pi / 180, x, y;
    for(int i = 0; i < size; i++)
    {
        x = pointsArr[i].x;
        y = pointsArr[i].y;
        pointsArr[i].x = x*cos(theta) + y*sin(theta);
        pointsArr[i].y = -x*sin(theta) + y*cos(theta);
    }
}
void rotateCounterClockwise(double degree, point *pointsArr, int size)
{
    double theta = degree * pi / 180, x, y;
    for(int i = 0; i < size; i++)
    {
        x = pointsArr[i].x;
        y = pointsArr[i].y;
        pointsArr[i].x = x*cos(theta) - y*sin(theta);
        pointsArr[i].y = x*sin(theta) + y*cos(theta);
    }
}



























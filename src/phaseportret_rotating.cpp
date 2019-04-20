#include "phaseportret_rotating.h"

pointsList* makeIntrscPointsList()
{
    pointsList* tmp = new pointsList;
    tmp->head = nullptr;
    tmp->tail = nullptr;
    return tmp;
}

void addPointNode(point myPoint, pointsList* myList)
{
    pointNode* tmp = new pointNode;
    tmp->node = myPoint;
    tmp->next = nullptr;
    if(myList->head == nullptr)
        myList->head = tmp;
    else
        myList->tail->next = tmp;
    myList->tail = tmp;
}
void removePointNode(pointNode* myNode, pointsList* myList)
{
    pointNode *tmp = myList->head, *targetNode = myNode, *deleteMePls;
    myNode = myNode->next;
    if(targetNode == myList->head)
    {
        myList->head = tmp->next;
        delete tmp;
        return;
    }
    while(tmp->next != targetNode)
        tmp = tmp->next;
    deleteMePls = tmp->next;
    if(deleteMePls == myList->tail)
    {
        tmp->next = nullptr;
        myList->tail = tmp;
    }
    else
        tmp->next = deleteMePls->next;

    delete deleteMePls;

}

phasePoint* makePhasePortret_Rot(vl f_vl, sl f_sl, vl c_vl, sl c_sl)
{
    phasePoint *arr = new phasePoint[360];
    double shiftAngle, shift, velocity, r;
    for(int i = 0; i < 360; i++)
    {
        shift = shiftLaw(i, f_sl, c_sl);
        shiftAngle = shift / pusherLength;

        velocity = velocityLaw(i, f_vl, c_vl);
        if(rotationDirection == 1)
        {
            velocity *= -1;
        }

        r = pusherLength + velocity;

        arr[i].x = r * cos(shiftAngle);
        arr[i].y = r * sin(shiftAngle);
        arr[i].shiftAngle = shiftAngle;
        arr[i].velocity = velocity;
    }
    return arr;
}
void findExtrVelocityPP(int &maxVelPP, int &minVelPP, phasePoint* ppArr, int size)
{
    maxVelPP = minVelPP = 0;
    for(int i = 1; i < size; i++)
    {
        if(ppArr[i].velocity > ppArr[maxVelPP].velocity)
            maxVelPP = i;
        if(ppArr[i].velocity < ppArr[minVelPP].velocity)
            minVelPP = i;
    }
}
void determineTempOptions(phasePoint* ppArr, int size)
{
    int maxVelPP, minVelPP;
    findExtrVelocityPP(maxVelPP, minVelPP, ppArr, size);

    point intrscnPoint;
    linesIntrsc(intrscnPoint, ppArr[minVelPP], ppArr[maxVelPP]);

    point center;
    center.x = pusherLength;
    center.y = 0;
    aw = sqrt(pow(intrscnPoint.x, 2) + pow(intrscnPoint.y, 2));
    minRadius = sqrt(pow(intrscnPoint.x - center.x, 2) + pow(intrscnPoint.y - center.y, 2));
}
void determineTrueOptions(point &intrscnPoint, phasePoint* ppArr, int size)
{
    int minSdid, maxSdid;
    findExtrSdPpoints(minSdid, maxSdid, ppArr, size);

    if(ppArr[minSdid].x < ppArr[maxSdid].x)
    {
        intrscnPoint.fromLeftExtrPoint_index = minSdid;
        intrscnPoint.fromRightExtrPoint_index = maxSdid;
    }
    else
    {
        intrscnPoint.fromLeftExtrPoint_index = maxSdid;
        intrscnPoint.fromRightExtrPoint_index = minSdid;
    }
    linesIntrsc(intrscnPoint, ppArr[intrscnPoint.fromLeftExtrPoint_index], ppArr[intrscnPoint.fromRightExtrPoint_index]);

    point center;
    center.x = pusherLength;
    center.y = 0;

    aw = sqrt(pow(intrscnPoint.x, 2) + pow(intrscnPoint.y, 2));
    minRadius = sqrt(pow(intrscnPoint.x - center.x, 2) + pow(intrscnPoint.y - center.y, 2));
    trundle_r = trundle_k * minRadius;
}

void findPpStressDegree(phasePoint *ppArr, int size)
{
    const double phi_20 = acos((pow(aw, 2) + pow(pusherLength, 2) - pow(minRadius, 2)) / (2 * pusherLength * aw));
    double beta_i, phi_2i;

    for(int i = 0; i < size; i++)
    {
        beta_i = ppArr[i].shiftAngle;
        phi_2i = phi_20 + beta_i;
        ppArr[i].myStressDegree = (ppArr[i].velocity + aw * cos(phi_2i) - pusherLength) / (aw * sin(phi_2i));
    }
}
point* makeStressDegreeArray(phasePoint *ppArr, int size)
{
    point *sdArr = new point[size];
    for(int i = 0; i < size; i++)
    {
        sdArr[i].x = i * pi / 180;
        sdArr[i].y = ppArr[i].myStressDegree;
    }
    return sdArr;
}
void findExtrSdPpoints(int &minSdId, int &maxSdId, phasePoint *ppArr, int size)
{
    minSdId = maxSdId = 0;
    for(int i = 1; i < size; i++)
    {
        if(ppArr[i].myStressDegree > ppArr[maxSdId].myStressDegree)
            maxSdId = i;
        if(ppArr[i].myStressDegree < ppArr[minSdId].myStressDegree)
            minSdId = i;
    }
}
double makeLineFunc_toLeft_Rot(double x, phasePoint *arr, int index) // функция прямой через точку arr[index], агрумент p,
{                                                                  // угол откладывает снизу влево от вертикали
    double p = arr[index].x;
    double q = arr[index].y;
    double k = tan((90 - stressDegree) * pi / 180 + arr[index].shiftAngle);
    double b = q - k*p; // q = k*p + b
    return k*x + b;
}
double makeLineFunc_toRight_Rot(double x, phasePoint *arr, int index) // функция прямой через точку arr[index], агрумент p,
{                                                                  // угол откладывает снизу вправо
    double p = arr[index].x;
    double q = arr[index].y;
    double k = tan((90 + stressDegree) * pi / 180 + arr[index].shiftAngle);
    double b = q - k*p; // q = k*p + b
    return k*x + b;
}
void linesIntrsc(point &intrscnPoint, phasePoint leftPoint, phasePoint rightPoint) // 1 - левая точка, 2 - правая точка
//находит точку пересечения прямых под углом давления, проходящих через заданные точки
{
    double x1 = leftPoint.x;
    double x2 = rightPoint.x;
    double y1 = leftPoint.y;
    double y2 = rightPoint.y;

    float k1 = tan((90.0 + stressDegree) * pi / 180.0 + leftPoint.shiftAngle); //leftPoint
    float k2 = tan((90.0 - stressDegree) * pi / 180.0 + rightPoint.shiftAngle); //rightPoint

    double b1 = y1 - k1*x1;
    double b2 = y2 - k2*x2;

    intrscnPoint.x = (b2-b1) / (k1-k2);
    intrscnPoint.y = k1 * intrscnPoint.x + b1;
}

bool isPointForbidden(point &myPoint, phasePoint *ppArr, int size)
{
    bool isForbidden = false;
    for(int i = 0; i < size; i++)
    {
        if(ppArr[i].velocity > 0 && makeLineFunc_toLeft_Rot(myPoint.x, ppArr, i) < myPoint.y)
        {
            isForbidden = true;
            break;
        }
        else
        if(ppArr[i].velocity < 0 && makeLineFunc_toRight_Rot(myPoint.x, ppArr, i) < myPoint.y)
        {
            isForbidden = true;
            break;
        }
    }
    return isForbidden;
}

//void initIntrscList(pointsList* myList, phasePoint* ppArr, int size) //phasePointsArr,   i - левая точка, j - правая точка
//{
//    point tmp;
//    for(int i = 0; i < size; i++) // циклы по фазовым точкам
//    {
//        if(!(ppArr[i].velocity < 0))
//            continue;

//        for(int j = 0; j < size; j++)
//        {
//            if(!(ppArr[j].velocity > 0))
//                continue;

//            tmp = linesIntrsc(ppArr[i], ppArr[j]);
//            if(isPointForbidden(tmp, ppArr, size) == false)
//            {
//                tmp.fromLeftExtrPoint_index = i;
//                tmp.fromRightExtrPoint_index = j;
//                addPointNode(tmp, myList);
//            }
//        }
//    }
//}

point chooseIntrscPoint(pointsList* myList)
//выбирает точку пересечения, в которой будет распологаться центр вращения кулачка
{
    point center, result;
    center.x = pusherLength;
    center.y = 0;
    double r, rMin;

    pointNode* tmp = myList->head;
    rMin = sqrt(pow(tmp->node.x - center.x, 2) + pow(tmp->node.y - center.y, 2));
    result.x = tmp->node.x;
    result.y = tmp->node.y;
    result.fromLeftExtrPoint_index = tmp->node.fromLeftExtrPoint_index;
    result.fromRightExtrPoint_index = tmp->node.fromRightExtrPoint_index;

    for(;tmp != nullptr; tmp = tmp->next)
    {
        r = sqrt(pow(tmp->node.x - center.x, 2) + pow(tmp->node.y - center.y, 2));
        if(r < rMin)
        {
            rMin = r;
            result.x = tmp->node.x;
            result.y = tmp->node.y;
            result.fromLeftExtrPoint_index = tmp->node.fromLeftExtrPoint_index;
            result.fromRightExtrPoint_index = tmp->node.fromRightExtrPoint_index;
        }
    }
    return result;
}

//void findKeyPoints_Rot(int &leftExtrPointIndex, int &rightExtrPointIndex, point &intrscPoint, phasePoint *ppArr, int size)
//{
//    pointsList* myList = makeIntrscPointsList();
//    initIntrscList(myList, ppArr, size);
//    intrscPoint = chooseIntrscPoint(myList);
//    leftExtrPointIndex = intrscPoint.fromLeftExtrPoint_index;
//    rightExtrPointIndex = intrscPoint.fromRightExtrPoint_index;


//    point center;
//    center.x = pusherLength;
//    center.y = 0;
//    aw = sqrt(pow(intrscPoint.x, 2) + pow(intrscPoint.y, 2));
//    minRadius = sqrt(pow(intrscPoint.x - center.x, 2) + pow(intrscPoint.y - center.y, 2));
//    trundle_r = trundle_k * minRadius;
//}































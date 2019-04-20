#include "widget.h"
#include "ui_widget.h"

#define SIZE 360

QGraphicsScene *scene = nullptr, *scene_2 = nullptr;
QPen pen(Qt::black);
QPen thickPen(Qt::black);
QTimer *timer;
static double scale = 1;

static point *centralPointsArr = nullptr, *realPointsArr = nullptr, *drawingPointsArr = nullptr;
static point *ppArr = nullptr;
static phasePoint *ppArray = nullptr;

void progressivePusherRunningFunction(motionLaws myMotionLaws, QGraphicsScene *scene, QGraphicsScene *scene_2)
{
    ppArr = makePhasePortret(myMotionLaws.f_vl, myMotionLaws.f_sl, myMotionLaws.c_vl, myMotionLaws.c_sl);
    point intrscnPoint;
    findKeyPoints(intrscnPoint, ppArr);

    double scale_2;
    determineScale(scale_2, ppArr, 480.0, 350.0);
    drawPhasePortret(scale_2, ppArr, scene_2, pen);
    drawTangents(scale_2, ppArr, scene_2, pen);
    drawAxesAtPhasePortret(scale_2, intrscnPoint, ppArr, scene_2, pen);

    centralPointsArr = makeCamCentralProfile(myMotionLaws.f_sl, myMotionLaws.c_sl);
    realPointsArr = makeCamRealProfile(centralPointsArr, SIZE);
    determineScale(scale, centralPointsArr, 480.0, 600.0);


    drawCamProfile(scale, centralPointsArr, scene , pen);
    drawCamProfile(scale, realPointsArr, scene, thickPen);
    drawCircle(scale, 0, 0, minRadius, scene, pen);

    drawProgressivePusher(scale, centralPointsArr, SIZE, scene, thickPen);

    drawMark(0, 0, scale, scene, pen);
}

void rotatingPusherRunningFunction(motionLaws myMotionLaws, QGraphicsScene *scene, QGraphicsScene *scene_2)
{
    ppArray = makePhasePortret_Rot(myMotionLaws.f_vl, myMotionLaws.f_sl, myMotionLaws.c_vl, myMotionLaws.c_sl);
    determineTempOptions(ppArray, SIZE);
    findPpStressDegree(ppArray, SIZE);

    point intrscnPoint;
    determineTrueOptions(intrscnPoint, ppArray, SIZE);
    double scale_2;
    determineScale(scale_2, ppArray, 480.0, 350.0);

    drawPhasePortret(scale_2, ppArray, scene_2, pen);
    drawTangents_Rot(scale_2, intrscnPoint, ppArray, scene_2, pen);
    drawAxesAtPhasePortretRot(scale_2, intrscnPoint, ppArray, scene_2, pen);

    centralPointsArr = makeCamCentralProfile_Rot(myMotionLaws.f_sl, myMotionLaws.c_sl);
    realPointsArr = makeCamRealProfile(centralPointsArr, SIZE);
    determineScale(scale, centralPointsArr, 480.0, 600.0);

    drawCamProfile(scale, centralPointsArr, scene , pen);
    drawCamProfile(scale, realPointsArr, scene, thickPen);
    drawCircle(scale, 0, 0, minRadius, scene, pen);

    drawRotatingPusher(scale, centralPointsArr, SIZE, scene, thickPen);

    drawMark(0, 0, scale, scene, pen);
}
void Widget::timerTick()
{
    if(rotationDirection == 0) // clockwise
    {
        rotateClockwise(3, centralPointsArr, SIZE);
        rotateClockwise(3, realPointsArr, SIZE);
    }
    else
    {
        rotateCounterClockwise(3, centralPointsArr, SIZE);
        rotateCounterClockwise(3, realPointsArr, SIZE);
    }
    scene->clear();

    drawCamProfile(scale, centralPointsArr, scene, pen);
    drawCamProfile(scale, realPointsArr, scene, thickPen);
    drawCircle(scale, 0, 0, minRadius, scene, pen);

    if(pusherType == 0)
    {
        drawProgressivePusher(scale, centralPointsArr, SIZE, scene, thickPen);
    }
    else
    {
        drawRotatingPusher(scale, centralPointsArr, SIZE, scene, thickPen);
    }


    drawMark(0, 0, scale, scene, pen);
}

void initRunningFunction(QGraphicsScene *scene, QGraphicsScene *scene_2)
{
    motionLaws myMotionLaws;
    setChoice(myMotionLaws.f_sl, myMotionLaws.f_vl, myMotionLaws.c_sl, myMotionLaws.c_vl);

    if(pusherType == 0) // progressive
       progressivePusherRunningFunction(myMotionLaws, scene, scene_2);
    else
        rotatingPusherRunningFunction(myMotionLaws, scene, scene_2);
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(10);
    thickPen.setWidth(2);

    QObject::connect(ui->goButton, SIGNAL(clicked()), this, SLOT(goHandler()));
    QObject::connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exportHandler()));
    QObject::connect(ui->button_animate, SIGNAL(clicked()), this, SLOT(triggerTimer()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

    ui->comboBox_far_phase->insertItem(0, "sin_sym");
    ui->comboBox_far_phase->insertItem(1, "cos_sym");
    ui->comboBox_far_phase->insertItem(2, "rect_sym");
    ui->comboBox_far_phase->insertItem(3, "line_dec");
    ui->comboBox_close_phase->insertItem(0, "sin_sym");
    ui->comboBox_close_phase->insertItem(1, "cos_sym");
    ui->comboBox_close_phase->insertItem(2, "rect_sym");
    ui->comboBox_close_phase->insertItem(3, "line_dec");
    ui->comboBox_rotation_direction->insertItem(0, "clockwise");
    ui->comboBox_rotation_direction->insertItem(1, "counter-clockwise");
    ui->comboBox_pusherType->insertItem(0, "progressive");
    ui->comboBox_pusherType->insertItem(1, "rotating");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::triggerTimer()
{
    if(!timer->isActive())
        timer->start();
    else
        timer->stop();
}

void Widget::goHandler()
{
    delete scene;
    delete scene_2;
    delete ppArr;
    delete ppArray;
    delete centralPointsArr;
    delete realPointsArr;
    delete drawingPointsArr;

    maxShift = ui->maxShiftlineEdit->text().toDouble();
    stressDegree = ui->stressDegreelineEdit->text().toDouble();
    if(ui->comboBox_pusherType->currentIndex() == 0)
        pusherType = 0;
    else
    {
        pusherType = 1;
        pusherLength = ui->lineEdit_pusher_length->text().toDouble();
    }
    trundle_k = ui->lineEdit_trundle_k->text().toDouble();
    f_phDegree = ui->f_phDegree_lineEdit->text().toDouble();
    c_phDegree = ui->c_phDegree_lineEdit->text().toDouble();
    fs_degree = ui->fs_degreelineEdit->text().toDouble();
    cs_degree = 360 - (f_phDegree + fs_degree + c_phDegree);
    if(ui->checkBox->isChecked())
    {
        eccentricity = ui->ecc_lineEdit->text().toDouble();
        isEccChecked = true;
    }
    else
        isEccChecked = false;

    far_phase_law = ui->comboBox_far_phase->currentIndex();
    close_phase_law = ui->comboBox_close_phase->currentIndex();
    rotationDirection = ui->comboBox_rotation_direction->currentIndex();

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    scene_2 = new QGraphicsScene(ui->graphicsView_2);
    ui->graphicsView_2->setScene(scene_2);
    initRunningFunction(scene, scene_2);

    ui->eccentricity_label->setText(QString::number((rotationDirection == 0) ? eccentricity : -eccentricity)); //знак в зависимости от направления вращ.
    ui->s_0_label->setText(QString::number(s_0));
    ui->minRadius_label->setText(QString::number(minRadius));
    ui->label_trundle_r->setText(QString::number(trundle_r));
    ui->label_aw->setText(QString::number(aw));
}

void Widget::exportHandler()
{
    QFile file("camProfileProduction.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream writeStream(&file);
    for(int i = 0; i < 360; i++)
    {
        writeStream << realPointsArr[i].x << ' ' << realPointsArr[i].y << '\n';
    }

    file.close();
}
























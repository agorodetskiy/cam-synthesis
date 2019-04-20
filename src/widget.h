#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFile>
#include <QTextStream>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QTime>

#include <math.h>
#include "parameters.h"
#include "laws.h"
#include "integrate.h"
#include "drawgraphics.h"
#include "phaseportret.h"
#include "phaseportret_rotating.h"
#include "camprofile.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    Ui::Widget *ui;
public slots:
    void exportHandler();
    void goHandler();
    void triggerTimer();
    void timerTick();
};

#endif // WIDGET_H

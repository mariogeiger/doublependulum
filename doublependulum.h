#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include "doublependulumthread.h"

class DoublePendulum : public QWidget
{
    Q_OBJECT
    
public:
    DoublePendulum(QWidget *parent = 0);
    ~DoublePendulum();

    void setParameters(qreal m1, qreal m2, qreal l1, qreal l2, qreal theta1, qreal theta2);

public slots:
    void reset();

private:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    DoublePendulumThread thr;
    QPainterPath path;
};

#endif // WIDGET_H

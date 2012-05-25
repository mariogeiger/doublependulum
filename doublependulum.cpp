#include "doublependulum.h"
#include <QPainter>
#include <cmath>

DoublePendulum::DoublePendulum(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 600);
    thr.start();
    startTimer(0);
}

DoublePendulum::~DoublePendulum()
{
    thr.stop();
    thr.wait();
}

void DoublePendulum::setParameters(qreal m1, qreal m2, qreal l1, qreal l2, qreal theta1, qreal theta2)
{
    thr.setParameters(m1, m2, l1, l2, theta1 * M_PI / 180.0, theta2 * M_PI / 180.0);
}

void DoublePendulum::reset()
{
    path = QPainterPath();
    thr.reset();
}

void DoublePendulum::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(1.0, -1.0);
    painter.scale(50, 50);

    painter.setPen(Qt::red);
    painter.drawPath(path);

    painter.setPen(Qt::black);

    qreal a1, a2;
    thr.getA1A2(&a1, &a2);

    QPointF p1(thr.getL1() * cos(a1), thr.getL1() * sin(a1));
    painter.drawLine(QPointF(0, 0), p1);

    painter.translate(p1);
    QPointF p2(thr.getL2() * cos(a2), thr.getL2() * sin(a2));
    painter.drawLine(QPointF(0, 0), p2);

    if (path.elementCount() == 0)
        path.moveTo(p1+p2);
    else
        path.lineTo(p1+p2);
}

void DoublePendulum::timerEvent(QTimerEvent *)
{
    update();
}

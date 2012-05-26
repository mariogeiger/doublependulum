#include "doublependulum.h"
#include <QPainter>
#include <cmath>

DoublePendulum::DoublePendulum(QWidget *parent)
    : QWidget(parent),
      thr(1.0e-6),
      thr2(10.0e-6)
{
    QPalette pal = palette();
    pal.setColor(backgroundRole(), Qt::gray);
    setPalette(pal);
    setAutoFillBackground(true);

    resize(600, 600);

    time.start();
    startTimer(0);
}

DoublePendulum::~DoublePendulum()
{
}

void DoublePendulum::setParameters(qreal m1, qreal m2, qreal l1, qreal l2, qreal theta1, qreal theta2)
{
    thr.setParameters(m1, m2, l1, l2, theta1 * M_PI / 180.0, theta2 * M_PI / 180.0);
    thr2.setParameters(m1, m2, l1, l2, theta1 * M_PI / 180.0, theta2 * M_PI / 180.0);
}

void DoublePendulum::reset()
{
    path = QPainterPath();
    thr.reset();
    thr2.reset();
}

void DoublePendulum::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(1.0, -1.0);
    painter.scale(50, 50);

    painter.setPen(Qt::red);
    painter.drawPath(path);

    painter.setPen(QPen(QBrush(Qt::black), 0.1));

    qreal a1, a2;
    thr.getA1A2(&a1, &a2);
//    qreal a1_, a2_;
//    thr2.getA1A2(&a1_, &a2_);
//    a1 -= a1_;
//    a2 -= a2_;

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
    qreal t = qreal(time.elapsed()) / 1000.0;
    qreal dt = t - lastTime;
    lastTime = t;

//    QTime t;
//    t.start();
    qDebug("dt = %f", dt);
    thr.move(dt);
//    thr2.move(dt);

//    qDebug("%d", t.elapsed());

    update();
}

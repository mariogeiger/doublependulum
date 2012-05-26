#ifndef SIMPHYTHREAD_H
#define SIMPHYTHREAD_H

#include <qglobal.h>

class DoublePendulumThread
{
public:
    explicit DoublePendulumThread(qreal dt = 500e-6);

    void getA1A2(qreal *_a1, qreal *_a2);

    qreal getL1() const;
    qreal getL2() const;

    void setParameters(qreal m1, qreal m2, qreal l1, qreal l2, qreal theta1, qreal theta2);
    void reset();

    void move(qreal dt);

private:
    qreal _a01, _a02;

    qreal _a1, _b1;
    qreal _a2, _b2;

    qreal _m1;
    qreal _m2;
    qreal _l1;
    qreal _l2;

    qreal _dt;
};

#endif // SIMPHYTHREAD_H

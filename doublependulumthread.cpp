#include "doublependulumthread.h"
#include <cmath>
#include <QTime>

DoublePendulumThread::DoublePendulumThread(QObject *parent) :
    QThread(parent),
    _a1(0.0), _b1(0.0),
    _a2(0.0), _b2(0.0),
    _m1(30.0),
    _m2(20.0),
    _l1(3.0),
    _l2(4.0)
{
}

void DoublePendulumThread::getA1A2(qreal *a1, qreal *a2)
{
    mutex.lock();
    *a1 = _a1;
    *a2 = _a2;
    mutex.unlock();
}

qreal DoublePendulumThread::getL1() const
{
    return _l1;
}

qreal DoublePendulumThread::getL2() const
{
    return _l2;
}

void DoublePendulumThread::setParameters(qreal m1, qreal m2, qreal l1, qreal l2, qreal theta1, qreal theta2)
{
    mutex.lock();
    _m1 = m1;
    _m2 = m2;
    _l1 = l1;
    _l2 = l2;
    mutex.unlock();
    _a01 = theta1;
    _a02 = theta2;
}

void DoublePendulumThread::reset()
{
    mutex.lock();
    _a1 = _a01;
    _a2 = _a02;
    _b1 = 0.0;
    _b2 = 0.0;
    mutex.unlock();
}

void DoublePendulumThread::stop()
{
    _stop = true;
}

void DoublePendulumThread::run()
{
    _stop = false;
    QTime time;
    while (!_stop) {
        time.start();
        qreal dt = 0.00025;
        qreal g = 9.81;
        qreal cosa2a1 = cos(_a2-_a1);
        qreal sina2a1 = sin(_a2-_a1);
        qreal cosa1 = cos(_a1);
        qreal cosa2 = cos(_a2);

        qreal c1=-(_l2*(g*(-6*cosa1*_m2-3*cosa1*_m1)+9*cosa2a1*sina2a1*_b1*_b1*_l1*_m2)
                   +6*sina2a1*_b2*_b2*_l2*_l2*_m2+9*cosa2*cosa2a1*g*_m2)
                /(_l1*_l2*(9*cosa2a1*cosa2a1*_m2-12*_m2-4*_m1));

        qreal c2=(_l2*(cosa2a1*g*(-18*cosa1*_m2-9*cosa1*_m1)+sina2a1*_b1*_b1*_l1*(36*_m2+12*_m1))
                  +cosa2*g*(36*_m2+12*_m1)+18*cosa2a1*sina2a1*_b2*_b2*_l2*_l2*_m2)
                /(_l2*_l2*(18*cosa2a1*cosa2a1*_m2-24*_m2-8*_m1));

        mutex.lock();
        _b1 += c1 * dt;
        _b2 += c2 * dt;
        _a1 += _b1 * dt;
        _a2 += _b2 * dt;
        mutex.unlock();
        usleep(250);
    }
}


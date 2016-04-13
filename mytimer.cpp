#include "mytimer.h"
#include <QtCore>
#include <QDebug>

MyTimer::MyTimer(QObject *parent) :
    QObject(parent)
{
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(MyTimeExpired()));
     timer->start(1000);
}

void MyTimer::MyTimeExpired()
{
    // this code will fire once every second.
    // This is when you should run the update functions.
    //qDebug() << "Timer Executed";

}

void MyTimer::someFunction()
{

}

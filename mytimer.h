#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QtCore>

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;

class MyTimer : public QObject
{
    Q_OBJECT
public:
    explicit MyTimer(QObject *parent = 0);
    QTimer *timer;
    void someFunction();
signals:

public slots:
    void MyTimeExpired();

};

#endif // MYTIMER_H

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "mySolarProject.h"
#include <QtGui>
#include <QtCore>
#include <QFile>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <ctime>
#include "i2c.hpp"
#include "psoccomm.hpp"
#include "uart.hpp"
#include "cccomm.hpp"
//#include <QString>
//#include <QDebug>
//#include <QTextStream>
//#include <QMessageBox>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}








/* // I found this online as a way to access GUI objects from another file. It might be the dirty way to do it.
w.findChild<QTextBrowser*>("FormElement")->setText("TEST");

where

    w is the MainWindow object
    QTextBrowser is type of the element you want to access
    "FormElement" is the name of the element you want to access
    (You can omitt it from parameter list if there is only one element of the given type. findChild will return it by default.)
    setText is the method you want to call.

*/


// battery voltage calculations = 11.96:(12.73-11.96)/13:12.73 in Matlab for 30%-100% for 30%(yellow), 20% yellow 10% Red Disconnect Load or at 30% (probably here.Don't want to use more than 40% really.)


/*
void Read(QString Filename)
{

    QFile mFile(Filename);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        //QMessageBox::information(this, "Error Message","could not open file for reading");
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() << mText;
    mFile.close();

}
*/


//QMessageBox myMessage = new QMessageBox(0);
//myMessage.information(this,"Error Message","could not open file for reading");
//Read(":/Icons/SunSolarPanels.jpg")

//w.findChild<QTextBrowser*>("FormElement")->setText("TEST");
//QPixmap pix(":/Icons/Battery/Battery17.png");
//QIcon icon(pix); // i was trying to figure out how to use code elsewhere to change teh gui. use signals and slots. i thihnk.
//w.findChild<QPushButton*>("")

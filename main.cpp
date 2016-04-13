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

#define ON      1
#define OFF     0

// Global Variables
int8_t gui_PowerButton_isOn    = OFF;
int8_t gui_SolarArrow_isOn     = OFF;
int8_t gui_ChargerArrow_isOn   = OFF;
int8_t gui_BatteryArrow_isOn   = OFF;
int8_t gui_LoadArrow_isOn      = OFF;
int8_t gui_ExternalArrow_isOn  = OFF;

float   solarPanelVoltage   = 100.0;
float   solarPanelCurrent   = 6.0;
float   chargeContrlVoltage = 14.4;
float   chargeContrlCurrent = 41.7;
float   batteryCurrent      = 30.0;
float   batteryVoltage      = 12.5;
float   batteryPercentage   = 80;
float   loadCurrent         = 11.7;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    //printf("Hello World\n");
    w.show();
    //printf("Next Line\n");

    //QMessageBox myMessage = new QMessageBox(0);
    //myMessage.information(this,"Error Message","could not open file for reading");
    //Read(":/Icons/SunSolarPanels.jpg")

    //w.findChild<QTextBrowser*>("FormElement")->setText("TEST");
    //QPixmap pix(":/Icons/Battery/Battery17.png");
    //QIcon icon(pix); // i was trying to figure out how to use code elsewhere to change teh gui. use signals and slots. i thihnk.
    //w.findChild<QPushButton*>("")



    return a.exec();
}

void set_Battery_Icon(float percentage)
{
    if(percentage > 99.99)
    {
        //QPixmap pix(":/Icons/Battery/Battery17.png");
    }

    //QIcon icon(pix);
   // MainWindow.ui->pb  ->setIcon(icon);
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

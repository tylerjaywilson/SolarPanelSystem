#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <ctime>
#include "psoccomm.hpp"
#include "cccomm.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer      *updateDispTimer;
    CCComm      chargeController;
    PSOCComm    psoc;
    int16_t Get_Battery_Percentage(float batteryVoltage);
    void    Set_Battery_Display(int16_t batteryPercentage);
    int8_t temp;

    void WarningText(QString);

    void ErrorText(QString);

    void NormalText(QString);

    void ImportantText(QString);


public slots:
    void on_pb_PowerButton_clicked();

    void on_pb_SolarDnArrow_clicked();

    void on_pb_ChargeControler_Arrow_clicked();

    void on_pb_Battery_Arrow_clicked();

    void on_pb_Power_Arrow_clicked();

    void MyTimerExpired();

private slots:
    void on_pb_External_Arrow_clicked();

    void on_pb_SunSolar_clicked();

    void WriteText2Box(QString);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>
#include "solarpanel_configpage.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <QString>
#include "cccomm.hpp"
#include "psoccomm.hpp"


/*
float   solarPanelVoltage   = 100.0;
float   solarPanelCurrent   = 6.0;
float   chargeContrlVoltage = 14.4;
float   chargeContrlCurrent = 41.7;
float   batteryCurrent      = 30.0;
float   batteryVoltage      = 12.5;
float   batteryPercentage   = 80;
float   loadCurrent         = 11.7;
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: white;");
    // set up class variables
    gui_PowerButton_isOn    = OFF;
    gui_SolarArrow_isOn     = OFF;
    gui_ChargerArrow_isOn   = OFF;
    gui_BatteryArrow_isOn   = OFF;
    gui_LoadArrow_isOn      = OFF;
    gui_ExternalArrow_isOn  = OFF;

    // 1 second timer setup
    updateDispTimer     = new QTimer(this);
    connect(updateDispTimer, SIGNAL(timeout()), this, SLOT(MyTimerExpired()));        // sets a signal/slot for when the 1 second timer expires
    updateDispTimer->start(1000);
    // hide extra display stuff
/*
    ui->lbl_SolarPanelVoltage->hide();
    ui->lbl_SolarPanelCurrent->hide();
    ui->lbl_ChargerVoltage->hide();
    ui->lbl_ChargerCurrent->hide();
    ui->lbl_LoadVoltage->hide();
    ui->lbl_LoadCurrent->hide();
    ui->lbl_BatteryCurrent->hide();
    ui->lbl_ExternalCurrent->hide();
    ui->lbl_SolarPanelVoltage_1->hide();
    ui->lbl_SolarPanelVoltage_2->hide();
    ui->lbl_SolarPanelVoltage_3->hide();
    ui->lbl_SolarPanelVoltage_4->hide();
 */
    ui->lbl_SolarPanelVoltage_5->hide();
    ui->lbl_SolarPanelVoltage_6->hide();
    ui->lbl_SolarPanelVoltage_7->hide();
    ui->lbl_SolarPanelVoltage_8->hide();

    NormalText("Welcome to the Solar Project.");
    NormalText("Designed and Created by Jonathan Fielding - Electrical Engineer");

// Initialize Offset and gain Parameters
    psoc.setBatteryVoltageGain( 15.689);
    psoc.setLoadVoltageGain(    15.730);
    psoc.setExternalVoltageGain(15.574);
    psoc.setBatteryCurrentOffset( -0.050);
    psoc.setLoadCurrentOffset(    -0.040);
    psoc.setExternalCurrentOffset(-0.040);
}

MainWindow::~MainWindow()
{
    delete ui;
}



// ****************************
// *     1 SECOND TIMER       *
// ****************************
void MainWindow::MyTimerExpired()   // this will fire every second or the time set in the variable timer.
{
    float voltage;
    float current;
    float power;

// ******* UPDATE CHARGE CONTROLLER
    chargeController.clearIsUpToDate();
        voltage = chargeController.getPVInputVoltage();
    ui->lbl_SolarPanelVoltage->setText(QString::number(voltage) + " V");
        current = chargeController.getChargingCurrent2();
    ui->lbl_SolarPanelCurrent->setText(QString::number(current) + " A"); // check to see if this is the correct value. DONE. CORRECT.
        current = chargeController.getChargingCurrent();
    ui->lbl_ChargerCurrent->setText(QString::number(current) + " A");
        power = chargeController.getChargingPower();
    ui->lbl_ChargeControllerPower->setText(QString::number(power) + " W");
        if(power > 0)
        {
            QPixmap pix(":/Icons/Arrow_s_Down.PNG");
            QIcon icon(pix);
            ui->pb_SolarDnArrow->setIcon(icon);
            QPixmap pix2(":/Icons/Arrow_s_Right.PNG");
            QIcon icon2(pix2);
            ui->pb_ChargeControler_Arrow->setIcon(icon2);
        }
        else
        {
            QPixmap pix(":/Icons/Arrow_s_straight.PNG");
            QIcon icon(pix);
            ui->pb_SolarDnArrow->setIcon(icon);
            QPixmap pix2(":/Icons/Arrow_s_Hstraight.PNG");
            QIcon icon2(pix2);
            ui->pb_ChargeControler_Arrow->setIcon(icon2);
        }

//****** UPDATE PSOC ********************
//BATTERY
    voltage = psoc.getBatteryVoltageAverage(); // **************** FIX THIS. AVERAGING ISN'T WORKING. THERES TOO MUCH VARIATION ON MEASUREMENTS.
        //voltage = chargeController.getBattVoltage();
    ui->lbl_BatteryVoltage->setText(QString::number(voltage, 'f', 2) + " V");
        current = psoc.getBatteryCurrentAverage() ;
    ui->lbl_BatteryCurrent->setText(QString::number(current, 'f', 2) + " A");
    ui->lbl_BatteryPower->setText(QString::number(voltage * current, 'f', 2) + " W");
        if(current < -1)
        {
            QPixmap pix(":/Icons/Arrow_s_Down.PNG");
            QIcon icon(pix);
            ui->pb_Battery_Arrow->setIcon(icon);
            ui->lbl_BatteryCharging->setText("Discharging");
        }
        else if (current > 1)
        {
            QPixmap pix(":/Icons/Arrow_s_Up.PNG");
            QIcon icon(pix);
            ui->pb_Battery_Arrow->setIcon(icon);
            ui->lbl_BatteryCharging->setText("Charging");
        }
        else
        {
            QPixmap pix(":/Icons/Arrow_s_straight.PNG");
            QIcon icon(pix);
            ui->pb_Battery_Arrow->setIcon(icon);
            ui->lbl_BatteryCharging->setText(" ");
        }
//LOAD
        current = psoc.getLoadCurrentAverage() *-1;
    ui->lbl_LoadCurrent->setText(QString::number(current, 'f', 2) + " A");
        voltage = psoc.getLoadVoltageAverage();
    ui->lbl_LoadVoltage->setText(QString::number(voltage, 'f', 2) + " V");
    ui->lbl_LoadPower->setText(QString::number(voltage * current, 'f', 2) + " W");
        if(current > 1)
        {
            QPixmap pix(":/Icons/Arrow_M_Right.PNG");
            QIcon icon(pix);
            ui->pb_Load_Arrow->setIcon(icon);
        }
        else
        {
            QPixmap pix(":/Icons/Arrow_M_HStraight.PNG");
            QIcon icon(pix);
            ui->pb_Load_Arrow->setIcon(icon);
        }

// EXTERNAL
        current = psoc.getExternalCurrentAverage() *-1;
    ui->lbl_ExternalCurrent->setText(QString::number(current, 'f', 2) + " A");
        voltage = psoc.getExternalVoltage();
    ui->lbl_ExternalVoltage->setText(QString::number(voltage, 'f', 2) + " V");
    ui->lbl_ExternalPower->setText(QString::number(voltage * current, 'f', 2) + " W");
        if(current > 1)
        {
            QPixmap pix(":/Icons/Arrow_s_Down.PNG");
            QIcon icon(pix);
            ui->pb_External_Arrow->setIcon(icon);
        }
        else if (current < -1)
        {
            QPixmap pix(":/Icons/Arrow_s_Up.PNG");
            QIcon icon(pix);
            ui->pb_External_Arrow->setIcon(icon);
        }
        else
        {
            QPixmap pix(":/Icons/Arrow_s_straight.PNG");
            QIcon icon(pix);
            ui->pb_External_Arrow->setIcon(icon);
        }
//SOLAR PANELS
    ui->lbl_SolarPanelVoltage_1->setText( QString::number( psoc.getSolPanel1Average(), 'f', 2 ) + " V");
    ui->lbl_SolarPanelVoltage_2->setText( QString::number( psoc.getSolPanel2Average(), 'f', 2 ) + " V");
    ui->lbl_SolarPanelVoltage_3->setText( QString::number( psoc.getSolPanel3Average(), 'f', 2 ) + " V");
    ui->lbl_SolarPanelVoltage_4->setText( QString::number( psoc.getSolPanel4Average(), 'f', 2 ) + " V");

//UPDATE BATTERY DISPLAY
     Set_Battery_Display( Get_Battery_Percentage( psoc.getBatteryVoltageAverage() ));
     //Set_Battery_Display( Get_Battery_Percentage( chargeController.getBattVoltage() ));
}


// ***************************************
// *     BATTERY DISPLAY FUNCTIONS       *
// ***************************************
int16_t MainWindow::Get_Battery_Percentage(float batteryVoltage)
{
    // the range of percentage is 110-10%
    int16_t percentage = 110;
    if(batteryVoltage < 13.20)
        percentage = 105;
    if(batteryVoltage < 12.87)
        percentage = 100;
    if(batteryVoltage < 12.73)
        percentage = 95;
    if(batteryVoltage < 12.68)
        percentage = 90;
    if(batteryVoltage < 12.62)
        percentage = 85;
    if(batteryVoltage < 12.56)
        percentage = 80;
    if(batteryVoltage < 12.50)
        percentage = 75;
    if(batteryVoltage < 12.44)
        percentage = 70;
    if(batteryVoltage < 12.37)
        percentage = 65;
    if(batteryVoltage < 12.31)
        percentage = 60;
    if(batteryVoltage < 12.24)
        percentage = 55;
    if(batteryVoltage < 12.17)
        percentage = 40;
    if(batteryVoltage < 12.10)
        percentage = 45;
    if(batteryVoltage < 12.03)
        percentage = 30;
    if(batteryVoltage < 11.81)
        percentage = 20;
    if(batteryVoltage < 11.66)
        percentage = 10;
return percentage;
}

void MainWindow::Set_Battery_Display(int16_t batteryPercentage)
{
    QString fileName;
    switch(batteryPercentage)
    {
        case 110:
            fileName = ":/Icons/Battery/Battery17.png";
            ui->lbl_BatteryPercentage->setText("+100%");
            break;
        case 105:
            fileName = ":/Icons/Battery/Battery16.png";
            ui->lbl_BatteryPercentage->setText("100%");
            break;
        case 100:
            fileName = ":/Icons/Battery/Battery15.png";
            ui->lbl_BatteryPercentage->setText("100%");
            break;
        case 95:
            fileName = ":/Icons/Battery/Battery14.png";
            ui->lbl_BatteryPercentage->setText("95%");
            break;
        case 90:
            fileName = ":/Icons/Battery/Battery13.png";
            ui->lbl_BatteryPercentage->setText("90%");
            break;
        case 85:
            fileName = ":/Icons/Battery/Battery12.png";
            ui->lbl_BatteryPercentage->setText("85%");
            break;
        case 80:
            fileName = ":/Icons/Battery/Battery11.png";
            ui->lbl_BatteryPercentage->setText("80%");
            break;
        case 75:
            fileName = ":/Icons/Battery/Battery10.png";
            ui->lbl_BatteryPercentage->setText("75%");
            break;
        case 70:
            fileName = ":/Icons/Battery/Battery9.png";
            ui->lbl_BatteryPercentage->setText("70%");
            break;
        case 65:
            fileName = ":/Icons/Battery/Battery8.png";
            ui->lbl_BatteryPercentage->setText("65%");
            break;
        case 60:
            fileName = ":/Icons/Battery/Battery7.png";
            ui->lbl_BatteryPercentage->setText("60%");
            break;
        case 55:
            fileName = ":/Icons/Battery/Battery6.png";
            ui->lbl_BatteryPercentage->setText("55%");
            break;
        case 50:
            fileName = ":/Icons/Battery/Battery5.png";
            ui->lbl_BatteryPercentage->setText("50%");
            break;
        case 45:
            fileName = ":/Icons/Battery/Battery4.png";
            ui->lbl_BatteryPercentage->setText("45%");
            break;
        case 40:
            fileName = ":/Icons/Battery/Battery3.png";
            ui->lbl_BatteryPercentage->setText("40%");
            break;
        case 30:
            fileName = ":/Icons/Battery/Battery2.png";
            ui->lbl_BatteryPercentage->setText("30%");
            break;
        case 20:
            fileName = ":/Icons/Battery/Battery1.png";
            ui->lbl_BatteryPercentage->setText("20%");
            break;
        case 10:
            fileName = ":/Icons/Battery/Battery1.png";
            ui->lbl_BatteryPercentage->setText("10%");
            break;
        default:
            fileName = ":/Icons/Battery/Battery1.png";
            ui->lbl_BatteryPercentage->setText("??");
            break;
    }
    QPixmap pix(fileName);
    QIcon icon(pix);
    ui->pb_Battery->setIcon(icon);
}

//**********************************
//*    DISPLAY TEXT FUNCTIONS      *
//**********************************
void MainWindow::WarningText(QString text)
{
    ui->textLoggerBox->setTextColor(QColor("dark orange"));
    WriteText2Box(text);
}
void MainWindow::ErrorText(QString text)
{
    ui->textLoggerBox->setTextColor(Qt::red);
    WriteText2Box(text);
}
void MainWindow::NormalText(QString text)
{
    ui->textLoggerBox->setTextColor(Qt::black);
    WriteText2Box(text);
}
void MainWindow::ImportantText(QString text)
{
    ui->textLoggerBox->setTextColor(Qt::blue);
    WriteText2Box(text);
}
void MainWindow::WriteText2Box(QString text)
{
    ui->textLoggerBox->append(text);
    QTextCursor c =  ui->textLoggerBox->textCursor();
    c.movePosition(QTextCursor::End);
    ui->textLoggerBox->setTextCursor(c);
}



//**********************************
//*    BUTTON PRESS FUNCTIONS      *
//**********************************

//  POWER BUTTON CLICK
void MainWindow::on_pb_PowerButton_clicked()
{
    if(gui_PowerButton_isOn)
    {
        gui_PowerButton_isOn = OFF;
        QPixmap pix(":/Icons/Off.png");
        QIcon icon(pix);
        ui->pb_PowerButton->setIcon(icon);

        QPixmap pix2(":/Icons/Bulb_Off.png");
        QIcon icon2(pix2);
        ui->pb_LightBulb->setIcon(icon2);

        //QMessageBox::information(this,"InfoBox", "0");
    }
    else
    {
        gui_PowerButton_isOn = ON;
        QPixmap pix(":/Icons/On.png");
        QIcon icon(pix);
        ui->pb_PowerButton->setIcon(icon);

        QPixmap pix2(":/Icons/Bulb_On.png");
        QIcon icon2(pix2);
        ui->pb_LightBulb->setIcon(icon2);
        //QMessageBox::information(this,"InfoBox", "1");
    }

}
// SUN SOLAR CLICK
void MainWindow::on_pb_SunSolar_clicked()
{
    SolarPanel_ConfigPage solar;
    solar.setModal(true);
    solar.exec();

}
// SOLAR TRACKER CLICK
void MainWindow::on_pb_SolarTrackerOnOff_clicked()
{
    if(gui_SolarTracker_isOn)
    {
        gui_SolarTracker_isOn = OFF;
        QPixmap pix(":/Icons/Off.png");
        QIcon icon(pix);
        ui->pb_SolarTrackerOnOff->setIcon(icon);
    }
    else
    {
        gui_SolarTracker_isOn = ON;
        QPixmap pix(":/Icons/On.png");
        QIcon icon(pix);
        ui->pb_SolarTrackerOnOff->setIcon(icon);
    }
}









// ********************************************************
// * This section below is all of the Arrow butons        *
// * to toggle on and off the voltage and current dislays *
// ********************************************************
void MainWindow::on_pb_SolarDnArrow_clicked()
{
    if(gui_SolarArrow_isOn)
    {
        gui_SolarArrow_isOn = OFF;
        ui->lbl_SolarPanelVoltage->hide();
        ui->lbl_SolarPanelCurrent->hide();
        ui->lbl_SolarPanelVoltage_1->hide();
        ui->lbl_SolarPanelVoltage_2->hide();
        ui->lbl_SolarPanelVoltage_3->hide();
        ui->lbl_SolarPanelVoltage_4->hide();
    }
    else
    {
        gui_SolarArrow_isOn = ON;
        ui->lbl_SolarPanelVoltage->show();
        ui->lbl_SolarPanelCurrent->show();
        ui->lbl_SolarPanelVoltage_1->show();
        ui->lbl_SolarPanelVoltage_2->show();
        ui->lbl_SolarPanelVoltage_3->show();
        ui->lbl_SolarPanelVoltage_4->show();
    }
}

void MainWindow::on_pb_ChargeControler_Arrow_clicked()
{
    if(gui_ChargerArrow_isOn)
    {
        gui_ChargerArrow_isOn = OFF;
        ui->lbl_ChargerCurrent->hide();
        //ui->lbl_ChargerVoltage->hide();
    }
    else
    {
        gui_ChargerArrow_isOn = ON;
        ui->lbl_ChargerCurrent->show();
        //ui->lbl_ChargerVoltage->show();
    }
}

void MainWindow::on_pb_Battery_Arrow_clicked()
{
    if(gui_BatteryArrow_isOn)
    {
        gui_BatteryArrow_isOn = OFF;
        ui->lbl_BatteryCurrent->hide();
    }
    else
    {
        gui_BatteryArrow_isOn = ON;
        ui->lbl_BatteryCurrent->show();
    }
}

void MainWindow::on_pb_Power_Arrow_clicked()
{
    if(gui_LoadArrow_isOn)
    {
        gui_LoadArrow_isOn = OFF;
        ui->lbl_LoadCurrent->hide();
        ui->lbl_LoadVoltage->hide();
    }
    else
    {
        gui_LoadArrow_isOn = ON;
        ui->lbl_LoadCurrent->show();
        ui->lbl_LoadVoltage->show();
    }
}

void MainWindow::on_pb_External_Arrow_clicked()
{
    if(gui_ExternalArrow_isOn)
    {
        gui_ExternalArrow_isOn = OFF;
        ui->lbl_ExternalCurrent->hide();
    }
    else
    {
        gui_ExternalArrow_isOn = ON;
        ui->lbl_ExternalCurrent->show();
    }
}



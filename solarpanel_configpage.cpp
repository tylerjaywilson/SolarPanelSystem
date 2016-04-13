#include "solarpanel_configpage.h"
#include "ui_solarpanel_configpage.h"
#include <QtGui>
#include <QtCore>
#include "i2c.hpp"
#include "psoccomm.hpp"
#include "uart.hpp"
#include "cccomm.hpp"

//QMessageBox::information(this,"title","you made it");  // good for debuging.

SolarPanel_ConfigPage::SolarPanel_ConfigPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolarPanel_ConfigPage)
{
    ui->setupUi(this);
}

SolarPanel_ConfigPage::~SolarPanel_ConfigPage()
{
    delete ui;
}


void SolarPanel_ConfigPage::on_pb_OpenCircuitVoltage_clicked()
{
    QMessageBox::information(this,"Definition", "O.C. = Open Circuit Voltage. Also Voc");
}

void SolarPanel_ConfigPage::on_pb_ShortCircuitCurrent_clicked()
{
    QMessageBox::information(this,"Definition", "S.C. = Spen Circuit Current. Also Isc");
}

void SolarPanel_ConfigPage::on_sbox_SeriesPanels_valueChanged(int series )
{

    int16_t parallel    = ui->sbox_ParallelPanels->value();
    int16_t watts      = ui->sbox_Panel_Wattage->value();
    int16_t OCvoltage = ui->sbox_OCVoltage->value();
    ui->lbl_NumTotalPanels->setText(QString::number(series * parallel));
    ui->lbl_MaxPower->setText(QString::number(series * parallel * watts));
    ui->lbl_MaxVoltage->setText(QString::number(series * OCvoltage));
}

void SolarPanel_ConfigPage::on_sbox_ParallelPanels_valueChanged(int parallel )
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    int16_t watts      = ui->sbox_Panel_Wattage->value();
    int16_t SCCurrent  = ui->sbox_SCCurrent->value();
    ui->lbl_NumTotalPanels->setText(QString::number(series * parallel));
    ui->lbl_MaxPower->setText(QString::number(series * parallel * watts));
    ui->lbl_MaxCurrent->setText(QString::number(parallel * SCCurrent));
}

void SolarPanel_ConfigPage::on_sbox_Panel_Wattage_valueChanged(int watts)
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    int16_t parallel    = ui->sbox_ParallelPanels->value();
    ui->lbl_MaxPower->setText(QString::number(series * parallel * watts));
}

void SolarPanel_ConfigPage::on_sbox_OCVoltage_valueChanged(int OCvoltage)
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    ui->lbl_MaxVoltage->setText(QString::number(series * OCvoltage));
}

void SolarPanel_ConfigPage::on_sbox_SCCurrent_valueChanged(int SCCurrent)
{
    int16_t parallel    = ui->sbox_ParallelPanels->value();
    ui->lbl_MaxCurrent->setText(QString::number(parallel * SCCurrent));
}

void SolarPanel_ConfigPage::on_sbox_Length_valueChanged(int length)
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    ui->lbl_TotalLength->setText(QString::number(series * length));
}

void SolarPanel_ConfigPage::on_sbox_Width_valueChanged(int width)
{
    int16_t parallel   = ui->sbox_ParallelPanels->value();
    ui->lbl_TotalWidth->setText(QString::number(parallel * width));
}

void SolarPanel_ConfigPage::on_sbox_Weight_valueChanged(int weight)
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    int16_t parallel   = ui->sbox_ParallelPanels->value();
    int16_t numPanels  = series * parallel;
    ui->lbl_TotalWeight->setText(QString::number(numPanels * weight));
}

void SolarPanel_ConfigPage::on_pb_CheckConfig_clicked()
{
    int16_t series     = ui->sbox_SeriesPanels->value();
    int16_t parallel   = ui->sbox_ParallelPanels->value();
    int16_t watts      = ui->sbox_Panel_Wattage->value();
    int16_t SCCurrent  = ui->sbox_SCCurrent->value();
    int16_t OCvoltage  = ui->sbox_OCVoltage->value();
    int32_t Power      = series * parallel * watts;
    int32_t Current    = parallel * SCCurrent;
    int32_t Voltage    = series * OCvoltage;
    //QString myString;
    int8_t error = 0;
// ******* Change this below later *******
    if(Power > 800){
        QMessageBox::warning(this,"Warning","Power input too high for Charge Controller!");
        error = 1;}
    if(Current > 50){
        QMessageBox::warning(this,"Warning","Current input too high for Charge Controller!");
        error = 1;}
    if(Voltage > 145){
        QMessageBox::warning(this,"Warning","Voltage input too high for Charge Controller!");
        error = 1;}
    if(!error){
        QMessageBox::information(this,"Notice","All paramters are within charge controller specs!");
        // add an enable of save button once successful and disable until no errors.
        }
}

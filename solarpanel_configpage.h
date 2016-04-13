#ifndef SOLARPANEL_CONFIGPAGE_H
#define SOLARPANEL_CONFIGPAGE_H

#include <QDialog>

namespace Ui {
    class SolarPanel_ConfigPage;
}

class SolarPanel_ConfigPage : public QDialog
{
    Q_OBJECT

public:
    explicit SolarPanel_ConfigPage(QWidget *parent = 0);
    ~SolarPanel_ConfigPage();

private slots:
    void on_pb_OpenCircuitVoltage_clicked();

    void on_pb_ShortCircuitCurrent_clicked();

    void on_sbox_SeriesPanels_valueChanged(int );

    void on_sbox_ParallelPanels_valueChanged(int );

    void on_sbox_Panel_Wattage_valueChanged(int );

    void on_sbox_OCVoltage_valueChanged(int );

    void on_sbox_SCCurrent_valueChanged(int );

    void on_sbox_Length_valueChanged(int );

    void on_sbox_Width_valueChanged(int );

    void on_sbox_Weight_valueChanged(int );

    void on_pb_CheckConfig_clicked();

private:
    Ui::SolarPanel_ConfigPage *ui;
};

#endif // SOLARPANEL_CONFIGPAGE_H

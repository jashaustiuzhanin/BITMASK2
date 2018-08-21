#ifndef DIALOGMODBUSPARAMS_H
#define DIALOGMODBUSPARAMS_H

#include <QDialog>
#include "tmodbusparams.h"

namespace Ui {
class DialogModbusParams;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DialogModbusParams : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogModbusParams(QWidget *parent = 0);
    ~DialogModbusParams();
    
    void SetData (TModbusParams *argpData);
    void GetData (TModbusParams *argpData);

private:
    Ui::DialogModbusParams *ui;
private slots:
    void SlotPulseUseFlagToggled ();
};
/*------------------------------------------------------------------*/
#endif // DIALOGMODBUSPARAMS_H

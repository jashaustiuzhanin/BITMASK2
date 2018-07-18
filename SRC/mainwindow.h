#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include "thexspinbox.h"
#include "tspinbox64.h"
#include "bmqspinbox.h"
#include "settings.h"

/*
class HexSpinbox : public QSpinBox
{
    virtual QString textFromValue (int val            ) const;
    virtual int     valueFromText (const QString &text) const;
};
*/


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

private:
    Ui::MainWindow *ui;

    int  Value;
    bool ShowInProcessFlag;

    TSettings Settings;

    typedef enum TFileState
    {
        filestateNOT_OPENED_NO_CHANGES      =  0,
        filestateNOT_OPENED_UNSAVED_CHANGES = 10,
        filestateOPENED_NO_CHANGES          =  1,
        filestateOPENED_UNSAVED_CHANGES     = 11,

        filestateStub = 0
    }
    TFileState;

    QString    CfgFileName ;
    TFileState CfgFileState;

    bool OpenCfgFile (QString FileName);
    bool SaveCfgFile (QString FileName);


private slots:
    void ShowValue ();
    void SlotMenuEnableDisable ();
    void ShowGroups ();

    void SlotOnSpnDecimal     ();
    void SlotOnSpnHexadecimal ();
    void SlotOnSpnBinary      ();

    void SlotOn32bitSpnBox ();

    void SlotOn32bitChkBox ();

    void SlotOnBitmaskClicked (int Row, int Column);
    void SlotOnBitmaskChkBox  ();

    void on_actVIEW_DEC_HEX_BIN_triggered();
    void on_actVIEW_32_bits_triggered();
    void on_actVIEW_Bitmask_triggered();
    void on_actFILE_Open_triggered();
    void on_actFILE_Quit_triggered();
    void on_actFILE_Save_triggered();
    void on_actFILE_Save_As_triggered();
    void on_actVIEW_MainToolbar_triggered();
};


#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QString HexSpinbox::textFromValue (int val            ) const
{
}
int     HexSpinbox::valueFromText (const QString &text) const
{
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ShowInProcessFlag = false;
    Value = 0;
    ShowValue ();

    QObject :: connect (ui->spnDecimal, SIGNAL(valueChanged(int)), this, SLOT(SlotOnSpnDecimal()));
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnSpnDecimal ()
{
    Value = ui->spnDecimal->value ();
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowValue ()
{
    QString tmp_str ;
    int     tmp_byte;

    // check for reentering in this function
    if (ShowInProcessFlag) return;
    ShowInProcessFlag = true;

    // fill decimal view
    ui->spnDecimal->setValue (Value);

    // fill hexadecimal view
    tmp_str = QString::number (Value, 16).toUpper();
    ui->edtHexadecimal->setText (tmp_str);

    // fill binary view
    tmp_str = QString::number (Value, 2 ).toUpper();
    ui->edtBinary->setText (tmp_str);

    // fill byte 0 bit-elements
    tmp_byte = (Value & 0x000000ff) >> 0;
    ui->chkByte0_00->setChecked (tmp_byte & 0x01);
    ui->chkByte0_01->setChecked (tmp_byte & 0x02);
    ui->chkByte0_02->setChecked (tmp_byte & 0x04);
    ui->chkByte0_03->setChecked (tmp_byte & 0x08);
    ui->chkByte0_04->setChecked (tmp_byte & 0x10);
    ui->chkByte0_05->setChecked (tmp_byte & 0x20);
    ui->chkByte0_06->setChecked (tmp_byte & 0x40);
    ui->chkByte0_07->setChecked (tmp_byte & 0x80);
    // fill byte 1 bit-elements
    tmp_byte = (Value & 0x0000ff00) >> 8;
    ui->chkByte1_08->setChecked (tmp_byte & 0x01);
    ui->chkByte1_09->setChecked (tmp_byte & 0x02);
    ui->chkByte1_10->setChecked (tmp_byte & 0x04);
    ui->chkByte1_11->setChecked (tmp_byte & 0x08);
    ui->chkByte1_12->setChecked (tmp_byte & 0x10);
    ui->chkByte1_13->setChecked (tmp_byte & 0x20);
    ui->chkByte1_14->setChecked (tmp_byte & 0x40);
    ui->chkByte1_15->setChecked (tmp_byte & 0x80);
    // fill byte 2 bit-elements
    tmp_byte = (Value & 0x00ff0000) >> 16;
    ui->chkByte2_16->setChecked (tmp_byte & 0x01);
    ui->chkByte2_17->setChecked (tmp_byte & 0x02);
    ui->chkByte2_18->setChecked (tmp_byte & 0x04);
    ui->chkByte2_19->setChecked (tmp_byte & 0x08);
    ui->chkByte2_20->setChecked (tmp_byte & 0x10);
    ui->chkByte2_21->setChecked (tmp_byte & 0x20);
    ui->chkByte2_22->setChecked (tmp_byte & 0x40);
    ui->chkByte2_23->setChecked (tmp_byte & 0x80);
    // fill byte 3 bit-elements
    tmp_byte = (Value & 0xff000000) >> 24;
    ui->chkByte3_24->setChecked (tmp_byte & 0x01);
    ui->chkByte3_25->setChecked (tmp_byte & 0x02);
    ui->chkByte3_26->setChecked (tmp_byte & 0x04);
    ui->chkByte3_27->setChecked (tmp_byte & 0x08);
    ui->chkByte3_28->setChecked (tmp_byte & 0x10);
    ui->chkByte3_29->setChecked (tmp_byte & 0x20);
    ui->chkByte3_30->setChecked (tmp_byte & 0x40);
    ui->chkByte3_31->setChecked (tmp_byte & 0x80);

/*
    // fill byte 0 hexchar-elements
    tmp_byte = (Value & 0x0000000f) >> 0;
    tmp_str = QString::number (tmp_byte, 16).toUpper();
    ui->spnByte0_HexRight->setValue (tmp_str);
    tmp_byte = (Value & 0x000000f0) >> 4;
    tmp_str = QString::number (tmp_byte, 16).toUpper();
    ui->spnByte0_HexLeft->setValue (tmp_str);
*/
    // release checking for reentering
    ShowInProcessFlag = false;
}
/*------------------------------------------------------------------*/

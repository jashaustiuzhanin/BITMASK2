#include "dlgmaskdatastyle.h"
#include "ui_dlgmaskdatastyle.h"
#include <QColorDialog>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DlgMaskDataStyle :: DlgMaskDataStyle(QWidget *parent) :
    QDialog(parent),
    ui (new Ui::DlgMaskDataStyle)
{
    ui->setupUi(this);

    ui->lblState0TitleTextFont->setVisible (false);
    ui->lblState1TitleTextFont->setVisible (false);
    ui->cmbState0TextFont     ->setVisible (false);
    ui->cmbState1TextFont     ->setVisible (false);
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DlgMaskDataStyle :: ~DlgMaskDataStyle ()
{
    delete ui;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: Repaint ()
{

    if ((BitNo >= 0) && (BitNo <= 31))
    {
        ui->lblTitle->setText (QString ("Mask data style for") + 
                               QString ("\nbit ") + QString::number (BitNo));
    }
    else
    {
        ui->lblTitle->setText (QString ("Mask data style for") +
                               QString ("\nselected bits"));
    }

    QString back_color_string;
    QString text_color_string;


    back_color_string = "rgb(";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState0.red   ()) + ", ";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState0.green ()) + ", ";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState0.blue  ()) + ")" ;
    ui->lblState0BackgroundColor->setStyleSheet (QString ("background-color: ") + back_color_string);

    text_color_string = "rgb(";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState0.red   ()) + ", ";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState0.green ()) + ", ";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState0.blue  ()) + ")" ;
    ui->lblState0TextColor->setStyleSheet (QString ("background-color: ") + text_color_string);

    ui->lblState0Example->setStyleSheet (QString ("background-color: ") + back_color_string + "; " + 
                                         QString ("color: "           ) + text_color_string + "; " );

    back_color_string = "rgb(";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState1.red   ()) + ", ";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState1.green ()) + ", ";
    back_color_string = back_color_string + QString::number (MaskData.BackColorState1.blue  ()) + ")" ;
    ui->lblState1BackgroundColor->setStyleSheet (QString ("background-color: ") + back_color_string);

    text_color_string = "rgb(";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState1.red   ()) + ", ";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState1.green ()) + ", ";
    text_color_string = text_color_string + QString::number (MaskData.TextColorState1.blue  ()) + ")" ;
    ui->lblState1TextColor->setStyleSheet (QString ("background-color: ") + text_color_string);

    ui->lblState1Example->setStyleSheet (QString ("background-color: ") + back_color_string + "; " + 
                                         QString ("color: "           ) + text_color_string + "; " );
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnState0BackgroundColor_clicked ()
{
    MaskData.BackColorState0 = QColorDialog :: getColor (MaskData.BackColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnState0TextColor_clicked ()
{
    MaskData.TextColorState0 = QColorDialog :: getColor (MaskData.TextColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnState1BackgroundColor_clicked ()
{
    MaskData.BackColorState1 = QColorDialog :: getColor (MaskData.BackColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnState1TextColor_clicked ()
{
    MaskData.TextColorState1 = QColorDialog :: getColor (MaskData.TextColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnOk_clicked ()
{
    accept ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DlgMaskDataStyle :: on_btnCancel_clicked ()
{
    reject ();
}
/*------------------------------------------------------------------*/

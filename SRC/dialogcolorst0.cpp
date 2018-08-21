#include "dialogcolorst0.h"
#include "ui_dialogcolorst0.h"
#include <QColorDialog>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorSt0 :: DialogColorSt0 (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColorSt0)
{
    ui->setupUi(this);

    ui->grpState0TextFont->setVisible (false);

    QObject :: connect (ui->rbtState0BackgroundColorDefault, SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackDefault_St0 ()));
    QObject :: connect (ui->rbtState0BackgroundColorByUser , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackByUser_St0  ()));
    QObject :: connect (ui->rbtState0TextColorDefault      , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextDefault_St0 ()));
    QObject :: connect (ui->rbtState0TextColorByUser       , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextByUser_St0  ()));
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorSt0 :: ~DialogColorSt0 ()
{
    delete ui;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema)
{
    BitNo       = argBitNo      ;
    MaskData    = argMaskData   ;
    ColorSchema = argColorSchema;
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: Repaint ()
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


    QColor back_color = CurrBackColorSt0 ();
    QColor text_color = CurrTextColorSt0 ();

    back_color_string = "rgb(";
    back_color_string = back_color_string + QString::number (back_color.red   ()) + ", ";
    back_color_string = back_color_string + QString::number (back_color.green ()) + ", ";
    back_color_string = back_color_string + QString::number (back_color.blue  ()) + ")" ;
    ui->lblState0BackgroundColor->setStyleSheet (QString ("background-color: ") + back_color_string);

    text_color_string = "rgb(";
    text_color_string = text_color_string + QString::number (text_color.red   ()) + ", ";
    text_color_string = text_color_string + QString::number (text_color.green ()) + ", ";
    text_color_string = text_color_string + QString::number (text_color.blue  ()) + ")" ;
    ui->lblState0TextColor->setStyleSheet (QString ("background-color: ") + text_color_string);

    ui->lblState0Example->setStyleSheet (QString ("background-color: ") + back_color_string + "; " + 
                                         QString ("color: "           ) + text_color_string + "; " );

    ui->rbtState0BackgroundColorDefault->setChecked (!MaskData.BackColorState0.isValid ());
    ui->rbtState0BackgroundColorByUser ->setChecked ( MaskData.BackColorState0.isValid ());

    ui->rbtState0TextColorDefault->setChecked (!MaskData.TextColorState0.isValid ());
    ui->rbtState0TextColorByUser ->setChecked ( MaskData.TextColorState0.isValid ());
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: on_btnState0BackgroundColor_clicked ()
{
    MaskData.BackColorState0 = QColorDialog :: getColor (MaskData.BackColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: on_btnState0TextColor_clicked ()
{
    MaskData.TextColorState0 = QColorDialog :: getColor (MaskData.TextColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorSt0 :: CurrTextColorSt0 ()
{
    QColor text_color_st0 = QColor ();
    text_color_st0 = MaskData.TextColorState0;
    if (!text_color_st0.isValid()   ) text_color_st0 = ColorSchema.TextColorSt0;
    return text_color_st0;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorSt0 :: CurrBackColorSt0 ()
{
    QColor back_color_st0 = QColor ();
    back_color_st0 = MaskData.BackColorState0;
    if (!back_color_st0.isValid()   ) back_color_st0 = ColorSchema.BackColorSt0;
    return back_color_st0;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/ /*
void DialogColorSt0 :: SlotRadioButtonsToggled ()
{
    bool repaint = false;

    if (ui->rbtState0BackgroundColorDefault->isChecked())
    {
        ui->lblState0BackgroundColor->setEnabled (false);
        ui->btnState0BackgroundColor->setEnabled (false);
        MaskData.BackColorState0 = QColor ();
        repaint = true;
    }
    else
    {
        ui->lblState0BackgroundColor->setEnabled (true );
        ui->btnState0BackgroundColor->setEnabled (true );
    }

    if (ui->rbtState0TextColorDefault->isChecked())
    {
        ui->lblState0TextColor->setEnabled (false);
        ui->btnState0TextColor->setEnabled (false);
        MaskData.TextColorState0 = QColor ();
        repaint = true;
    }
    else
    {
        ui->lblState0TextColor->setEnabled (true );
        ui->btnState0TextColor->setEnabled (true );
    }

    if (repaint) Repaint ();
} */
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: SlotRadioButtonsToggled_BackDefault_St0 ()
{
    if (ui->rbtState0BackgroundColorDefault->isChecked())
    {
        ui->lblState0BackgroundColor->setEnabled (false);
        ui->btnState0BackgroundColor->setEnabled (false);
        MaskData.BackColorState0 = QColor ();
        Repaint ();
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: SlotRadioButtonsToggled_BackByUser_St0 ()
{
    if (ui->rbtState0BackgroundColorByUser->isChecked())
    {
        ui->lblState0BackgroundColor->setEnabled (true );
        ui->btnState0BackgroundColor->setEnabled (true );
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: SlotRadioButtonsToggled_TextDefault_St0 ()
{
    if (ui->rbtState0TextColorDefault->isChecked())
    {
        ui->lblState0TextColor->setEnabled (false);
        ui->btnState0TextColor->setEnabled (false);
        MaskData.TextColorState0 = QColor ();
        Repaint ();
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt0 :: SlotRadioButtonsToggled_TextByUser_St0 ()
{
    if (ui->rbtState0TextColorByUser->isChecked())
    {
        ui->lblState0TextColor->setEnabled (true );
        ui->btnState0TextColor->setEnabled (true );
    }
}

/*------------------------------------------------------------------*/

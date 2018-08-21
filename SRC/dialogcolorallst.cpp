#include "dialogcolorallst.h"
#include "ui_dialogcolorallst.h"
#include <QColorDialog>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorAllSt :: DialogColorAllSt (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColorAllSt)
{
    ui->setupUi(this);

    ui->grpState0TextFont->setVisible (false);

    QObject :: connect (ui->rbtState0BackgroundColorDefault, SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackDefault_St0 ()));
    QObject :: connect (ui->rbtState0BackgroundColorByUser , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackByUser_St0  ()));
    QObject :: connect (ui->rbtState0TextColorDefault      , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextDefault_St0 ()));
    QObject :: connect (ui->rbtState0TextColorByUser       , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextByUser_St0  ()));

    ui->grpState1TextFont->setVisible (false);

    QObject :: connect (ui->rbtState1BackgroundColorDefault, SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackDefault_St1 ()));
    QObject :: connect (ui->rbtState1BackgroundColorByUser , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackByUser_St1  ()));
    QObject :: connect (ui->rbtState1TextColorDefault      , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextDefault_St1 ()));
    QObject :: connect (ui->rbtState1TextColorByUser       , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextByUser_St1  ()));
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorAllSt :: ~DialogColorAllSt ()
{
    delete ui;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema)
{
    BitNo       = argBitNo      ;
    MaskData    = argMaskData   ;
    ColorSchema = argColorSchema;
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: Repaint ()
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

    QColor back_color;
    QColor text_color;

    back_color = CurrBackColorSt0 ();
    text_color = CurrTextColorSt0 ();

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


    back_color = CurrBackColorSt1 ();
    text_color = CurrTextColorSt1 ();

    back_color_string = "rgb(";
    back_color_string = back_color_string + QString::number (back_color.red   ()) + ", ";
    back_color_string = back_color_string + QString::number (back_color.green ()) + ", ";
    back_color_string = back_color_string + QString::number (back_color.blue  ()) + ")" ;
    ui->lblState1BackgroundColor->setStyleSheet (QString ("background-color: ") + back_color_string);

    text_color_string = "rgb(";
    text_color_string = text_color_string + QString::number (text_color.red   ()) + ", ";
    text_color_string = text_color_string + QString::number (text_color.green ()) + ", ";
    text_color_string = text_color_string + QString::number (text_color.blue  ()) + ")" ;
    ui->lblState1TextColor->setStyleSheet (QString ("background-color: ") + text_color_string);

    ui->lblState1Example->setStyleSheet (QString ("background-color: ") + back_color_string + "; " + 
                                         QString ("color: "           ) + text_color_string + "; " );

    ui->rbtState1BackgroundColorDefault->setChecked (!MaskData.BackColorState1.isValid ());
    ui->rbtState1BackgroundColorByUser ->setChecked ( MaskData.BackColorState1.isValid ());

    ui->rbtState1TextColorDefault->setChecked (!MaskData.TextColorState1.isValid ());
    ui->rbtState1TextColorByUser ->setChecked ( MaskData.TextColorState1.isValid ());
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: on_btnState0BackgroundColor_clicked ()
{
    MaskData.BackColorState0 = QColorDialog :: getColor (MaskData.BackColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: on_btnState0TextColor_clicked ()
{
    MaskData.TextColorState0 = QColorDialog :: getColor (MaskData.TextColorState0, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: on_btnState1BackgroundColor_clicked ()
{
    MaskData.BackColorState1 = QColorDialog :: getColor (MaskData.BackColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: on_btnState1TextColor_clicked ()
{
    MaskData.TextColorState1 = QColorDialog :: getColor (MaskData.TextColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorAllSt :: CurrTextColorSt0 ()
{
    QColor text_color_st0 = QColor ();
    text_color_st0 = MaskData.TextColorState0;
    if (!text_color_st0.isValid()   ) text_color_st0 = ColorSchema.TextColorSt0;
    return text_color_st0;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorAllSt :: CurrBackColorSt0 ()
{
    QColor back_color_st0 = QColor ();
    back_color_st0 = MaskData.BackColorState0;
    if (!back_color_st0.isValid()   ) back_color_st0 = ColorSchema.BackColorSt0;
    return back_color_st0;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorAllSt :: CurrTextColorSt1 ()
{
    QColor text_color_st1 = QColor ();
    text_color_st1 = MaskData.TextColorState1;
    if (!text_color_st1.isValid()   ) text_color_st1 = ColorSchema.TextColorSt1;
    return text_color_st1;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorAllSt :: CurrBackColorSt1 ()
{
    QColor back_color_st1 = QColor ();
    back_color_st1 = MaskData.BackColorState1;
    if (!back_color_st1.isValid()   ) back_color_st1 = ColorSchema.BackColorSt1;
    return back_color_st1;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/ /*
void DialogColorAllSt :: SlotRadioButtonsToggled ()
{
    if (ui->rbtState0BackgroundColorDefault->isChecked())
    {
        ui->lblState0BackgroundColor->setEnabled (false);
        ui->btnState0BackgroundColor->setEnabled (false);
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
    }
    else
    {
        ui->lblState0TextColor->setEnabled (true );
        ui->btnState0TextColor->setEnabled (true );
    }

    if (ui->rbtState1BackgroundColorDefault->isChecked())
    {
        ui->lblState1BackgroundColor->setEnabled (false);
        ui->btnState1BackgroundColor->setEnabled (false);
    }
    else
    {
        ui->lblState1BackgroundColor->setEnabled (true );
        ui->btnState1BackgroundColor->setEnabled (true );
    }

    if (ui->rbtState1TextColorDefault->isChecked())
    {
        ui->lblState1TextColor->setEnabled (false);
        ui->btnState1TextColor->setEnabled (false);
    }
    else
    {
        ui->lblState1TextColor->setEnabled (true );
        ui->btnState1TextColor->setEnabled (true );
    }
} */
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_BackDefault_St0 ()
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
void DialogColorAllSt :: SlotRadioButtonsToggled_BackByUser_St0 ()
{
    if (ui->rbtState0BackgroundColorByUser->isChecked())
    {
        ui->lblState0BackgroundColor->setEnabled (true );
        ui->btnState0BackgroundColor->setEnabled (true );
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_TextDefault_St0 ()
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
void DialogColorAllSt :: SlotRadioButtonsToggled_TextByUser_St0 ()
{
    if (ui->rbtState0TextColorByUser->isChecked())
    {
        ui->lblState0TextColor->setEnabled (true );
        ui->btnState0TextColor->setEnabled (true );
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_BackDefault_St1 ()
{
    if (ui->rbtState1BackgroundColorDefault->isChecked())
    {
        ui->lblState1BackgroundColor->setEnabled (false);
        ui->btnState1BackgroundColor->setEnabled (false);
        MaskData.BackColorState1 = QColor ();
        Repaint ();
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_BackByUser_St1 ()
{
    if (ui->rbtState1BackgroundColorByUser->isChecked())
    {
        ui->lblState1BackgroundColor->setEnabled (true );
        ui->btnState1BackgroundColor->setEnabled (true );
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_TextDefault_St1 ()
{
    if (ui->rbtState1TextColorDefault->isChecked())
    {
        ui->lblState1TextColor->setEnabled (false);
        ui->btnState1TextColor->setEnabled (false);
        MaskData.TextColorState1 = QColor ();
        Repaint ();
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorAllSt :: SlotRadioButtonsToggled_TextByUser_St1 ()
{
    if (ui->rbtState1TextColorByUser->isChecked())
    {
        ui->lblState1TextColor->setEnabled (true );
        ui->btnState1TextColor->setEnabled (true );
    }
}

/*------------------------------------------------------------------*/

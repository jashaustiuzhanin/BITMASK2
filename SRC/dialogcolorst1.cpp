/***************************************************************************
**                                                                        **
**  Filename: dialogcolorst1.cpp                                          **
**  Last updated [dd/mm/yyyy]: 07/09/2018                                 **
**                                                                        **
**  This file is part of Bitmask project                                  **
**  (https://github.com/jashaustiuzhanin/BITMASK2).                       **
**  Bitmask is a simple tool to view boolean bit-values of 32-bit integer **
**  number by masks.                                                      **
**                                                                        **
**  Copyright (C) 2018 Jasha Ustiuzhanin                                  **
**                                                                        **
**  Bitmask is free software: you can redistribute it and/or modify       **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  Bitmask is distributed in the hope that it will be useful,            **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with Bitmask package (in the file COPYING).                     **
**  If not, see <https://www.gnu.org/licenses/>.                          **
**                                                                        **
****************************************************************************/

#include "dialogcolorst1.h"
#include "ui_dialogcolorst1.h"
#include <QColorDialog>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorSt1 :: DialogColorSt1 (QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColorSt1)
{
    ui->setupUi(this);

    ui->grpState1TextFont->setVisible (false);

    QObject :: connect (ui->rbtState1BackgroundColorDefault, SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackDefault_St1 ()));
    QObject :: connect (ui->rbtState1BackgroundColorByUser , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_BackByUser_St1  ()));
    QObject :: connect (ui->rbtState1TextColorDefault      , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextDefault_St1 ()));
    QObject :: connect (ui->rbtState1TextColorByUser       , SIGNAL(toggled(bool)), this, SLOT(SlotRadioButtonsToggled_TextByUser_St1  ()));
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
DialogColorSt1 :: ~DialogColorSt1 ()
{
    delete ui;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt1 :: SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema)
{
    BitNo       = argBitNo      ;
    MaskData    = argMaskData   ;
    ColorSchema = argColorSchema;
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt1 :: Repaint ()
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


    QColor back_color = CurrBackColorSt1 ();
    QColor text_color = CurrTextColorSt1 ();

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
void DialogColorSt1 :: on_btnState1BackgroundColor_clicked ()
{
    MaskData.BackColorState1 = QColorDialog :: getColor (MaskData.BackColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt1 :: on_btnState1TextColor_clicked ()
{
    MaskData.TextColorState1 = QColorDialog :: getColor (MaskData.TextColorState1, this);
    Repaint ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorSt1 :: CurrTextColorSt1 ()
{
    QColor text_color_st1 = QColor ();
    text_color_st1 = MaskData.TextColorState1;
    if (!text_color_st1.isValid()   ) text_color_st1 = ColorSchema.TextColorSt1;
    return text_color_st1;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor DialogColorSt1 :: CurrBackColorSt1 ()
{
    QColor back_color_st1 = QColor ();
    back_color_st1 = MaskData.BackColorState1;
    if (!back_color_st1.isValid()   ) back_color_st1 = ColorSchema.BackColorSt1;
    return back_color_st1;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/ /*
void DialogColorSt1 :: SlotRadioButtonsToggled ()
{
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
void DialogColorSt1 :: SlotRadioButtonsToggled_BackDefault_St1 ()
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
void DialogColorSt1 :: SlotRadioButtonsToggled_BackByUser_St1 ()
{
    if (ui->rbtState1BackgroundColorByUser->isChecked())
    {
        ui->lblState1BackgroundColor->setEnabled (true );
        ui->btnState1BackgroundColor->setEnabled (true );
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void DialogColorSt1 :: SlotRadioButtonsToggled_TextDefault_St1 ()
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
void DialogColorSt1 :: SlotRadioButtonsToggled_TextByUser_St1 ()
{
    if (ui->rbtState1TextColorByUser->isChecked())
    {
        ui->lblState1TextColor->setEnabled (true );
        ui->btnState1TextColor->setEnabled (true );
    }
}

/*------------------------------------------------------------------*/

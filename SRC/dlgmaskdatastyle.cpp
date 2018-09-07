/***************************************************************************
**                                                                        **
**  Filename: dlgmaskdatastyle.cpp                                        **
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

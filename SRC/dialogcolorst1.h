/***************************************************************************
**                                                                        **
**  Filename: dialogcolorst1.h                                            **
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

#ifndef DIALOGCOLORST1_H
#define DIALOGCOLORST1_H

#include <QDialog>
#include "maskdata.h"
#include "colorschema.h"

namespace Ui {
class DialogColorSt1;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DialogColorSt1 : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogColorSt1(QWidget *parent = 0);
    ~DialogColorSt1();

    void SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema);
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DialogColorSt1 *ui;

    int               BitNo      ;
    TMaskDataOfOneBit MaskData   ;
    TColorSchema      ColorSchema;

    void Repaint ();

    QColor CurrBackColorSt1 ();
    QColor CurrTextColorSt1 ();
private slots:

    void on_btnState1BackgroundColor_clicked();
    void on_btnState1TextColor_clicked();
//  void SlotRadioButtonsToggled ();
    void SlotRadioButtonsToggled_BackDefault_St1 ();
    void SlotRadioButtonsToggled_BackByUser_St1  ();
    void SlotRadioButtonsToggled_TextDefault_St1 ();
    void SlotRadioButtonsToggled_TextByUser_St1  ();

};

#endif // DIALOGCOLORST1_H

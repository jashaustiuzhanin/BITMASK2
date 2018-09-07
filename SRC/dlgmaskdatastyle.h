/***************************************************************************
**                                                                        **
**  Filename: dlgmaskdatastyle.h                                          **
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

#ifndef DLGMASKDATASTYLE_H
#define DLGMASKDATASTYLE_H

#include <QDialog>

#include "maskdata.h"

namespace Ui {
class DlgMaskDataStyle;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DlgMaskDataStyle : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgMaskDataStyle (QWidget *parent = 0);
   ~DlgMaskDataStyle ();

    void SetData (int argBitNo, TMaskDataOfOneBit &argMaskData) {BitNo = argBitNo; MaskData = argMaskData; Repaint ();}
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DlgMaskDataStyle *ui;

    int               BitNo   ;
    TMaskDataOfOneBit MaskData;

    void Repaint ();

private slots:

    void on_btnState0BackgroundColor_clicked();
    void on_btnState0TextColor_clicked();
    void on_btnState1BackgroundColor_clicked();
    void on_btnState1TextColor_clicked();
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};
/*------------------------------------------------------------------*/

#endif // DLGMASKDATASTYLE_H

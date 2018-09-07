/***************************************************************************
**                                                                        **
**  Filename: dialogmodbusparams.h                                        **
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

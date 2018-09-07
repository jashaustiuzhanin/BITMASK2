/***************************************************************************
**                                                                        **
**  Filename: dialogmodbusparams.cpp                                      **
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

#include "dialogmodbusparams.h"
#include "ui_dialogmodbusparams.h"

DialogModbusParams::DialogModbusParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModbusParams)
{
    ui->setupUi(this);

    ui->spnIPAddrA->setValue (127);
    ui->spnIPAddrB->setValue (  0);
    ui->spnIPAddrC->setValue (  0);
    ui->spnIPAddrD->setValue (  1);

    ui->spnIPPort->setValue (502);

    ui->spnMBNode->setValue (255);

    ui->spnValueRegNo->setValue (0);
    ui->spnPulseRegNo->setValue (0);

    QObject :: connect (ui->chkUsePulse, SIGNAL(toggled(bool)), this, SLOT(SlotPulseUseFlagToggled()));

    ui->chkUsePulse->setChecked (false);
}

DialogModbusParams::~DialogModbusParams()
{
    delete ui;
}

void DialogModbusParams :: SlotPulseUseFlagToggled ()
{
    bool pulse_enabled = ui->chkUsePulse->isChecked();
    ui->lblTitlePulseRegNo->setEnabled (pulse_enabled);
    ui->spnPulseRegNo     ->setEnabled (pulse_enabled);
}

void DialogModbusParams :: SetData (TModbusParams *argpData)
{
    int ip_addr_a, ip_addr_b, ip_addr_c, ip_addr_d;
    int ip_port;

    argpData->GetServerIPCfg (ip_addr_a, ip_addr_b, ip_addr_c, ip_addr_d, ip_port);

    ui->spnIPAddrA->setValue (ip_addr_a);
    ui->spnIPAddrB->setValue (ip_addr_b);
    ui->spnIPAddrC->setValue (ip_addr_c);
    ui->spnIPAddrD->setValue (ip_addr_d);

    ui->spnIPPort->setValue (ip_port);

    ui->spnMBNode->setValue (argpData->GetServerMBNode());

    ui->spnValueRegNo->setValue (argpData->GetValueRegNo());
    ui->spnPulseRegNo->setValue (argpData->GetPulseRegNo());

    ui->chkUsePulse->setChecked (argpData->GetPulseRegNo() >= 0);
    SlotPulseUseFlagToggled ();
}

void DialogModbusParams :: GetData (TModbusParams *argpData)
{
    int ip_addr_a, ip_addr_b, ip_addr_c, ip_addr_d;
    int ip_port;

    ip_addr_a = ui->spnIPAddrA->value ();
    ip_addr_b = ui->spnIPAddrB->value ();
    ip_addr_c = ui->spnIPAddrC->value ();
    ip_addr_d = ui->spnIPAddrD->value ();

    ip_port = ui->spnIPPort->value ();

    argpData->SetServerIPCfg (ip_addr_a, ip_addr_b, ip_addr_c, ip_addr_d, ip_port);


    argpData->SetServerMBNode(ui->spnMBNode->value ());

    argpData->SetValueRegNo(ui->spnValueRegNo->value ());
    argpData->SetPulseRegNo(ui->spnPulseRegNo->value ());

    if (!ui->chkUsePulse->isChecked()) argpData->SetPulseRegNo(-1);
}

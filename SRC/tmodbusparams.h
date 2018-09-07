/***************************************************************************
**                                                                        **
**  Filename: tmodbusparams.h                                             **
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

#ifndef TMODBUSPARAMS_H
#define TMODBUSPARAMS_H

#include <QtCore>


class TModbusParams
{
public:
    explicit TModbusParams ();

    void SetDefault ();

    bool SetServerIPCfg (int  AddrA, int  AddrB, int  AddrC, int  AddrD, int  Port = 502);
    void GetServerIPCfg (int &AddrA, int &AddrB, int &AddrC, int &AddrD, int &Port);
    QString GetServerIPCfgStr (bool WithPort);
    bool SetIPCfgByStr  (QString IPCfgString );
    bool SetIPAddrByStr (QString IPAddrString);
    bool SetIPPort (int Port);
    int  GetIPPort (        ) {return ServerPort;}

    bool SetServerMBNode (int Node) 
    {
        if (Node <   0) return false;
        if (Node > 255) return false;
        ServerMBNode = Node;
        return true;
    }
    int  GetServerMBNode () {return ServerMBNode;}

    void SetValueRegNo (int RegNo) {ValueRegNo = RegNo;}
    int  GetValueRegNo (         ) {return  ValueRegNo;}

    void SetPulseRegNo (int RegNo) {PulseRegNo = RegNo;}
    int  GetPulseRegNo (         ) {return  PulseRegNo;}

    bool operator == (TModbusParams Other);
    bool operator != (TModbusParams Other);

private:

    int ServerIPAddrA;
    int ServerIPAddrB;
    int ServerIPAddrC;
    int ServerIPAddrD;

    int ServerPort;

    int ServerMBNode;

    int ValueRegNo;
    int PulseRegNo;
};

#endif // TMODBUSPARAMS_H

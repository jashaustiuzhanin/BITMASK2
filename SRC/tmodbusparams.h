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

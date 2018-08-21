#include "tmodbusparams.h"
#include <QStringList>

TModbusParams :: TModbusParams ()
{
    SetDefault ();
}

void TModbusParams :: SetDefault ()
{
    ServerIPAddrA = 127;
    ServerIPAddrB =   0;
    ServerIPAddrC =   0;
    ServerIPAddrD =   1;

    ServerPort    = 502;

    ServerMBNode  = 255;

    ValueRegNo = -1; // -1 - unused parameter
    PulseRegNo = -1; // -1 - unused parameter
}

bool TModbusParams :: SetServerIPCfg (int  AddrA, int  AddrB, int  AddrC, int  AddrD, int  Port)
{
    if (AddrA <   0) return false;
    if (AddrA > 255) return false;
    if (AddrB <   0) return false;
    if (AddrB > 255) return false;
    if (AddrC <   0) return false;
    if (AddrC > 255) return false;
    if (AddrD <   0) return false;
    if (AddrD > 255) return false;

    if (Port <     0) return false;
    if (Port > 32767) return false;

    ServerIPAddrA = AddrA;
    ServerIPAddrB = AddrB;
    ServerIPAddrC = AddrC;
    ServerIPAddrD = AddrD;

    ServerPort = Port;

    return true ;
}
void TModbusParams :: GetServerIPCfg (int &AddrA, int &AddrB, int &AddrC, int &AddrD, int &Port)
{
    AddrA = ServerIPAddrA;
    AddrB = ServerIPAddrB;
    AddrC = ServerIPAddrC;
    AddrD = ServerIPAddrD;

    Port = ServerPort;

    return;
}

QString TModbusParams :: GetServerIPCfgStr (bool WithPort)
{
    QString s = "";
    s = s + QString::number (ServerIPAddrA) + ".";
    s = s + QString::number (ServerIPAddrB) + ".";
    s = s + QString::number (ServerIPAddrC) + ".";
    s = s + QString::number (ServerIPAddrD)      ;

    if (WithPort)
    {
        s = s + " : " + QString::number (ServerPort);
    }

    return s;
}
bool TModbusParams :: SetIPCfgByStr  (QString IPCfgString )
{

    // разделение строки с адресом на участки, состоящие
    // из цифр и разделённые точками и другими знаками
    QString     s  = IPCfgString;
    QStringList sl;
    QString     ss = "";

    for (int i=0; i<s.size(); i++)
    {
        if (false ||
            (s[i] == QChar('.' )) ||
            (s[i] == QChar('\t')) ||
            (s[i] == QChar(':' )) ||
            (s[i] == QChar(' ' )) ||
            (s[i] == QChar(',' )) ||
            false)
        {
            if (ss.size() > 0) sl.append (ss);
            ss = "";
        }
        else if ((s[i] >= QChar('0')) && (s[i] <= QChar('9')))
        {
            ss = ss.append (s[i]);
        }
        else return false;
    }
    sl.append (ss);

    // если количество участков меньше 4, то составить IP-адрес невозможно
    if (sl.count() < 4) return false;

    // перевод элементов адреса из текста в числа
    bool ok;
    int addr_a = sl[0].toInt(&ok, 10); if (!ok) return false;
    int addr_b = sl[1].toInt(&ok, 10); if (!ok) return false;
    int addr_c = sl[2].toInt(&ok, 10); if (!ok) return false;
    int addr_d = sl[3].toInt(&ok, 10); if (!ok) return false;

    ok = SetServerIPCfg (addr_a, addr_b, addr_c, addr_d, ServerPort);
    if (!ok) return false;

    if (sl.count() >= 5)
    {
        int port = sl[4].toInt(&ok, 10); if (!ok) return false;
        ok = SetIPPort (port);
    }

    return true ;
}

bool TModbusParams :: SetIPAddrByStr (QString IPAddrString)
{

    // разделение строки с адресом на участки, состоящие
    // из цифр и разделённые точками и другими знаками
    QString     s  = IPAddrString;
    QStringList sl;
    QString     ss = "";

    for (int i=0; i<s.size(); i++)
    {
        if (false ||
            (s[i] == QChar('.' )) ||
            (s[i] == QChar('\t')) ||
            (s[i] == QChar(':' )) ||
            (s[i] == QChar(' ' )) ||
            (s[i] == QChar(',' )) ||
            false)
        {
            if (ss.size() > 0) sl.append (ss);
            ss = "";
        }
        else if ((s[i] >= QChar('0')) && (s[i] <= QChar('9')))
        {
            ss = ss.append (s[i]);
        }
        else return false;
    }
    sl.append (ss);

    // если количество участков меньше 4, то составить IP-адрес невозможно
    if (sl.count() < 4) return false;

    // перевод элементов адреса из текста в числа
    bool ok;
    int addr_a = sl[0].toInt(&ok, 10); if (!ok) return false;
    int addr_b = sl[1].toInt(&ok, 10); if (!ok) return false;
    int addr_c = sl[2].toInt(&ok, 10); if (!ok) return false;
    int addr_d = sl[3].toInt(&ok, 10); if (!ok) return false;

    ok = SetServerIPCfg (addr_a, addr_b, addr_c, addr_d, ServerPort);
    if (!ok) return false;

    return true ;
}

bool TModbusParams :: SetIPPort (int Port)
{
    if (Port <     0) return false;
    if (Port > 32767) return false;

    ServerPort = Port;

    return true ;
}

bool TModbusParams :: operator == (TModbusParams Other)
{
    if (this->ServerIPAddrA != Other.ServerIPAddrA) return false;
    if (this->ServerIPAddrB != Other.ServerIPAddrB) return false;
    if (this->ServerIPAddrC != Other.ServerIPAddrC) return false;
    if (this->ServerIPAddrD != Other.ServerIPAddrD) return false;

    if (this->ServerPort   != Other.ServerPort  ) return false;

    if (this->ServerMBNode != Other.ServerMBNode) return false;

    if (this->ValueRegNo   != Other.ValueRegNo  ) return false;
    if (this->PulseRegNo   != Other.PulseRegNo  ) return false;

    return true;
}

bool TModbusParams :: operator != (TModbusParams Other)
{
    bool is_equal = (operator == (Other));
    return !is_equal;
}

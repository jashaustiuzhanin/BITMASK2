/***************************************************************************
**                                                                        **
**  Filename: settings.h                                                  **
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

#ifndef SETTINGS_H
#define SETTINGS_H

#include "maskdata.h"
#include "colorschema.h"
#include "tmodbusparams.h"

/* глобальный список доступных цветовых схем */
extern QVector <TColorSchema> ColorSchemas;

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class TSettingsData
{
  public:

    TSettingsData () {SetDefault ();}

    void SetDefault ();

    bool SaveToXML   (QString FileName);
    bool ReadFromXML (QString FileName);


    // собственно данные настроек

    bool Visible_GroupDecHexBin;
    bool Visible_Group32Bits   ;
    bool Visible_GroupBitmask  ;

    bool Visible_Group32Bits_Hex;
    bool Visible_GroupBitmask_StColorColumns;

    bool Visible_MainToolBar;

    TMaskDataOfOneBit MaskDataOfBit [32];

    QString ColorSchemaName;

    TModbusParams ModbusParams;

  private:

    bool ReadFromXML_GroupDecHexBin (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_Group32Bits    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_GroupBitmask   (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_MainToolBar    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_ColorSchema    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_ModbusParams   (QXmlStreamReader *pXmlReader);

    bool SaveToXML_GroupDecHexBin   (QXmlStreamWriter *pXmlWriter);
    bool SaveToXML_Group32Bits      (QXmlStreamWriter *pXmlWriter);
    bool SaveToXML_GroupBitmask     (QXmlStreamWriter *pXmlWriter);
    bool SaveToXML_MainToolBar      (QXmlStreamWriter *pXmlWriter);
    bool SaveToXML_ColorSchema      (QXmlStreamWriter *pXmlWriter);
    bool SaveToXMl_ModbusParams     (QXmlStreamWriter *pXmlWriter);
};


#include <QtCore>
#include <QObject>
#include <QColor>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class TSettings : public QObject
{
  Q_OBJECT

  // ---------------------------------------------------------------
  public:

    TSettings () {}

    bool IsChanged ();
    bool SaveToXML   (QString FileName);
    bool ReadFromXML (QString FileName);

    // -- Get-methods -- 
    bool GetVisible_GroupDecHexBin  () {return CurrentData.Visible_GroupDecHexBin ;}
    bool GetVisible_Group32Bits     () {return CurrentData.Visible_Group32Bits    ;}
    bool GetVisible_GroupBitmask    () {return CurrentData.Visible_GroupBitmask   ;}

    bool GetVisible_Group32Bits_Hex () {return CurrentData.Visible_Group32Bits_Hex;}
    bool GetVisible_GroupBitmask_StColorColumns () {return CurrentData.Visible_GroupBitmask_StColorColumns;}


    bool GetVisible_MainToolBar     () {return CurrentData.Visible_MainToolBar    ;}

    QColor GetTextColorSt0 (int BitNo) {return GetColor (BitNo, "Text", 0);}
    QColor GetTextColorSt1 (int BitNo) {return GetColor (BitNo, "Text", 1);}
    QColor GetBackColorSt0 (int BitNo) {return GetColor (BitNo, "Back", 0);}
    QColor GetBackColorSt1 (int BitNo) {return GetColor (BitNo, "Back", 1);}

    QString GetText        (int BitNo) {return GetText_p (BitNo);}

    QString GetColorSchemaName      () {return CurrentData.ColorSchemaName        ;}

    void    GetModbusServerIPCfg    (int &AddrA, int &AddrB, int &AddrC, int &AddrD, int &Port)
    {
        CurrentData.ModbusParams.GetServerIPCfg (AddrA, AddrB, AddrC, AddrD, Port);
    }
    QString GetModbusServerIPCfgStr (bool WithPort) {return CurrentData.ModbusParams.GetServerIPCfgStr (WithPort);}
    int     GetModbusServerMBNode   ()              {return CurrentData.ModbusParams.GetServerMBNode ();}
    int     GetModbusValueRegNo     ()              {return CurrentData.ModbusParams.GetValueRegNo   ();}
    int     GetModbusPulseRegNo     ()              {return CurrentData.ModbusParams.GetPulseRegNo   ();}
//  int     GetModbusServerPort     ()              {return CurrentData.ModbusParams.GetIPPort       ();}
    int     GetModbusIPPort         ()              {return CurrentData.ModbusParams.GetIPPort       ();}

    TModbusParams * GetModbusParams () {return &(CurrentData.ModbusParams);}


    // -- Set-methods -- 
    void SetVisible_GroupDecHexBin  (bool Val) {CurrentData.Visible_GroupDecHexBin  = Val; emit SignalTouched();}
    void SetVisible_Group32Bits     (bool Val) {CurrentData.Visible_Group32Bits     = Val; emit SignalTouched();}
    void SetVisible_GroupBitmask    (bool Val) {CurrentData.Visible_GroupBitmask    = Val; emit SignalTouched();}
                                     
    void SetVisible_Group32Bits_Hex (bool Val) {CurrentData.Visible_Group32Bits_Hex = Val; emit SignalTouched();}
    bool SetVisible_GroupBitmask_StColorColumns (bool Val) {CurrentData.Visible_GroupBitmask_StColorColumns = Val; emit SignalTouched(); return true;}

    void SetVisible_MainToolBar     (bool Val) {CurrentData.Visible_MainToolBar     = Val; emit SignalTouched();}

    void SetTextColorSt0 (int BitNo, QColor  Val) {SetColor (BitNo, "Text", 0, Val);}
    void SetTextColorSt1 (int BitNo, QColor  Val) {SetColor (BitNo, "Text", 1, Val);}
    void SetBackColorSt0 (int BitNo, QColor  Val) {SetColor (BitNo, "Back", 0, Val);}
    void SetBackColorSt1 (int BitNo, QColor  Val) {SetColor (BitNo, "Back", 1, Val);}

    void SetText         (int BitNo, QString Val) {SetText_p (BitNo, Val);}

    void SetColorSchemaName      (QString Val) {CurrentData.ColorSchemaName         = Val; emit SignalTouched();}

    bool SetModbusServerIPCfg (int  AddrA, int  AddrB, int  AddrC, int  AddrD, int  Port = 502)
    {
        return CurrentData.ModbusParams.SetServerIPCfg (AddrA, AddrB, AddrC, AddrD, Port);
    }
    bool SetModbusIPCfgByStr   (QString IPCfgString ) {return CurrentData.ModbusParams.SetIPCfgByStr   (IPCfgString );}
    bool SetModbusIPAddrByStr  (QString IPAddrString) {return CurrentData.ModbusParams.SetIPAddrByStr  (IPAddrString);}
    bool SetModbusIPPort       (int Port )            {return CurrentData.ModbusParams.SetIPPort       (Port        );}
    bool SetModbusServerMBNode (int Node )            {return CurrentData.ModbusParams.SetServerMBNode (Node        );}
    void SetModbusValueRegNo   (int RegNo)            {       CurrentData.ModbusParams.SetValueRegNo (RegNo);         }
    void SetModbusPulseRegNo   (int RegNo)            {       CurrentData.ModbusParams.SetPulseRegNo (RegNo);         }


    void SetVoid () {CurrentData.SetDefault(); NoChangedData.SetDefault();}

  // ---------------------------------------------------------------
  signals:

    void SignalTouched ();


  // ---------------------------------------------------------------
  private:

    TSettingsData CurrentData  ;
    TSettingsData NoChangedData;

    QColor GetColor (int BitNo, QString Element, int BitState)
    {
        if (BitNo <   0) return QColor ();
        if (BitNo >= 32) return QColor ();

        TMaskDataOfOneBit mdata = CurrentData.MaskDataOfBit[BitNo];
        if      (Element == "Text") return (BitState) ? mdata.TextColorState1 : mdata.TextColorState0;
        else if (Element == "Back") return (BitState) ? mdata.BackColorState1 : mdata.BackColorState0;
        else                        return QColor ();
    }

    QString GetText_p      (int BitNo) 
    {
        if (BitNo <   0) return QString ();
        if (BitNo >= 32) return QString ();
        return CurrentData.MaskDataOfBit[BitNo].Text;
    }

    void SetColor (int BitNo, QString Element, int BitState, QColor Val)
    {
        if (BitNo <   0) return;
        if (BitNo >= 32) return;

        TMaskDataOfOneBit *pmdata = &(CurrentData.MaskDataOfBit[BitNo]);
        if      (Element == "Text") (BitState) ? pmdata->TextColorState1 = Val : pmdata->TextColorState0 = Val;
        else if (Element == "Back") (BitState) ? pmdata->BackColorState1 = Val : pmdata->BackColorState0 = Val;
        else                        return;

        emit SignalTouched ();
    }

    void SetText_p      (int BitNo, QString Val)
    {
        if (BitNo <   0) return;
        if (BitNo >= 32) return;
        CurrentData.MaskDataOfBit[BitNo].Text = Val;

        emit SignalTouched ();
    }

};
/*------------------------------------------------------------------*/


#endif // SETTINGS_H

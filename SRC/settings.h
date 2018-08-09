#ifndef SETTINGS_H
#define SETTINGS_H

#include "maskdata.h"
#include "colorschema.h"

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

    bool Visible_MainToolBar;

    TMaskDataOfOneBit MaskDataOfBit [32];

    QString ColorSchemaName;

  private:

    bool ReadFromXML_GroupDecHexBin (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_Group32Bits    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_GroupBitmask   (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_MainToolBar    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_ColorSchema    (QXmlStreamReader *xml_writer);

    bool SaveToXML_GroupDecHexBin   (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_Group32Bits      (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_GroupBitmask     (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_MainToolBar      (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_ColorSchema      (QXmlStreamWriter *xml_writer);

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

    bool GetVisible_MainToolBar     () {return CurrentData.Visible_MainToolBar    ;}

    QColor GetTextColorSt0 (int BitNo) {return GetColor (BitNo, "Text", 0);}
    QColor GetTextColorSt1 (int BitNo) {return GetColor (BitNo, "Text", 1);}
    QColor GetBackColorSt0 (int BitNo) {return GetColor (BitNo, "Back", 0);}
    QColor GetBackColorSt1 (int BitNo) {return GetColor (BitNo, "Back", 1);}

    QString GetText        (int BitNo) {return GetText_p (BitNo);}

    // -- Set-methods -- 
    void SetVisible_GroupDecHexBin  (bool Val) {CurrentData.Visible_GroupDecHexBin  = Val; emit SignalTouched();}
    void SetVisible_Group32Bits     (bool Val) {CurrentData.Visible_Group32Bits     = Val; emit SignalTouched();}
    void SetVisible_GroupBitmask    (bool Val) {CurrentData.Visible_GroupBitmask    = Val; emit SignalTouched();}
                                     
    void SetVisible_Group32Bits_Hex (bool Val) {CurrentData.Visible_Group32Bits_Hex = Val; emit SignalTouched();}

    void SetVisible_MainToolBar     (bool Val) {CurrentData.Visible_MainToolBar     = Val; emit SignalTouched();}

    void SetTextColorSt0 (int BitNo, QColor  Val) {SetColor (BitNo, "Text", 0, Val);}
    void SetTextColorSt1 (int BitNo, QColor  Val) {SetColor (BitNo, "Text", 1, Val);}
    void SetBackColorSt0 (int BitNo, QColor  Val) {SetColor (BitNo, "Back", 0, Val);}
    void SetBackColorSt1 (int BitNo, QColor  Val) {SetColor (BitNo, "Back", 1, Val);}

    void SetText         (int BitNo, QString Val) {SetText_p (BitNo, Val);}


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

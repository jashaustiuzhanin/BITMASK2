#ifndef SETTINGS_H
#define SETTINGS_H

#include "maskdata.h"

class TSettings
{
  public:

    TSettings () {SetDefault ();}

    bool Visible_GroupDecHexBin;
    bool Visible_Group32Bits   ;
    bool Visible_GroupBitmask  ;

    bool Visible_Group32Bits_Hex;

    TMaskDataOfOneBit MaskDataOfBit [32];

    bool SaveToXML   (QString FileName);
    bool ReadFromXML (QString FileName);

  private:

    void SetDefault ();

    bool ReadFromXML_GroupDecHexBin (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_Group32Bits    (QXmlStreamReader *pXmlReader);
    bool ReadFromXML_GroupBitmask   (QXmlStreamReader *pXmlReader);

    bool SaveToXML_GroupDecHexBin   (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_Group32Bits      (QXmlStreamWriter *pXmlReader);
    bool SaveToXML_GroupBitmask     (QXmlStreamWriter *pXmlReader);

};


#endif // SETTINGS_H

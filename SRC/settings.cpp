#include <QtCore>
#include <QColor>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>

#include "settings.h"

/*------------------------------------------------------------------*/
void TSettings :: SetDefault ()
{
    Visible_GroupDecHexBin = true ;
    Visible_Group32Bits    = true ;
    Visible_GroupBitmask   = false;

    Visible_Group32Bits_Hex = true;

    for (int i=0; i<32; i++)
    {
        MaskDataOfBit [i].BackColorState0 = QColor (Qt::lightGray);
        MaskDataOfBit [i].TextColorState0 = QColor (Qt::darkGray );
        MaskDataOfBit [i].BackColorState1 = QColor (Qt::darkGreen);
        MaskDataOfBit [i].TextColorState1 = QColor (Qt::white    );

        MaskDataOfBit [i].Text = "";
    }
}

/*------------------------------------------------------------------*/
bool TSettings :: SaveToXML   (QString FileName)
{
    bool  tmp_result;

    if ((FileName == "") || (FileName == 0) || (FileName == QString())) return false;

    /* Открываем файл для Записи с помощью пути, указанного в filename */
    QFile file (FileName);
    file.open (QIODevice::WriteOnly);

    /* Создаем объект, с помощью которого осуществляется запись в файл XML */
    QXmlStreamWriter xml_writer   (&file);
    xml_writer.setAutoFormatting  (true);            // Устанавливается автоформатирование текста
    xml_writer.writeStartDocument ();                // Запускается запись в документ
    xml_writer.writeStartElement  ("BitmaskCfg");    // Записывается первый элемент с его именем

    // сохраняются настройки группы DecHexBin
    {
        tmp_result = SaveToXML_GroupDecHexBin (&xml_writer);
        if (!tmp_result) {file.close (); return false;}
    }
    // сохраняются настройки группы 32 bits
    {
        tmp_result = SaveToXML_Group32Bits (&xml_writer);
        if (!tmp_result) {file.close (); return false;}
    }
    // сохраняются настройки группы Bitmask
    {
        tmp_result = SaveToXML_GroupBitmask (&xml_writer);
        if (!tmp_result) {file.close (); return false;}
    }

    /* Закрывается тег первого элемента */
    xml_writer.writeEndElement ();
    /* Завершается запись в алемент */
    xml_writer.writeEndDocument ();
    file.close ();   // Закрывается файл

    return true;
}

/*------------------------------------------------------------------*/
bool TSettings :: ReadFromXML (QString FileName)
{
    if ((FileName == "") || (FileName == 0) || (FileName == QString())) return false;

    QFile file (FileName);
    bool  tmp_result;

    /* открытие читаемого XML-файла */
    tmp_result = file.open (QFile::ReadOnly | QFile::Text);

    if (!tmp_result)
    {
        QMessageBox::warning (0,
                              "File error!",
                              QString ("Can't open file ") + FileName,
                              QMessageBox::Ok);
        return false;
    }

    /* Создаётся объект, с помощью которого осуществляется чтение из файла */
    QXmlStreamReader xml_reader;
    xml_reader.setDevice (&file);
    xml_reader.readNext ();   // Переход к первому элементу в файле

    /* Цикл до тех пор, пока не будет достигнут конец документа */
    while (!xml_reader.atEnd ())
    {
        /* Проверка, является ли данный элемент началом тега */
        if (xml_reader.isStartElement ())
        {
            // Найден тег начала данных, содержащих настройки группы DecHexBin
            if (xml_reader.name () == "GroupDecHexBin")
            {
                // считываются настройки группы DecHexBin
                tmp_result = ReadFromXML_GroupDecHexBin (&xml_reader);
                if (!tmp_result) {file.close (); return false;}
            }

            // Найден тег начала данных, содержащих настройки группы 32 bits
            if (xml_reader.name () == "Group32Bits")
            {
                // считываются настройки группы 32 bits
                tmp_result = ReadFromXML_Group32Bits    (&xml_reader);
                if (!tmp_result) {file.close (); return false;}
            }

            // Найден тег начала данных, содержащих настройки группы Bitmask
            if (xml_reader.name () == "GroupBitmask")
            {
                // считываются настройки группы 32 bits
                tmp_result = ReadFromXML_GroupBitmask   (&xml_reader);
                if (!tmp_result) {file.close (); return false;}
            }


        } // end if isStartElement

        xml_reader.readNext (); // Переход к следующему элементу XML-файла
    }


    file.close (); // Закрытие файла


#ifdef __DELETED_FRAGMENT__
        /* Проверка, является ли данный элемент началом тега */
        if (xml_reader.isStartElement ())
        {
            bool already_found = true;

            // Считывается тег первого элемента
            if (xml_reader.name () == "BitmaskParams")
            {
            }

            // Считывается тег с именем файла, содержащего отчёт
            else if (xml_reader.name () == "ReportFilePath")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {ReportFilePath = (attr.value().toString ());}
                }
            }
            // Считывается тег с названием организации
            else if (xml_reader.name () == "OrganizationName")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {OrganizationName = (attr.value().toString ());}
                }
            }
            // Считывается тег с именем файла, содержащего логотип
            else if (xml_reader.name () == "LogoImagePath")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {LogoImagePath = (attr.value().toString ());}
                }
            }
            // Считывается тег с Названием документа отчёта
            else if (xml_reader.name () == "Title1")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Title1 = (attr.value().toString ());}
                }
            }
            // Считывается тег с дополнительным заголовком
            else if (xml_reader.name () == "Title2")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Title2 = (attr.value().toString ());}
                }
            }
            // Считывается тег с Надписью над таблицей
            else if (xml_reader.name () == "TableOverHat")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {TableOverHat = (attr.value().toString ());}
                }
            }

            // Считывается тег со значением поля Шахта, скважина, глубина и т.д.
            else if (xml_reader.name () == "Shachta")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Shachta = (attr.value().toString ());}
                }
            }


            // Считывается тег со значением поля Подпись 1
            else if (xml_reader.name () == "Podpis1")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Podpis1 = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля Подпись 2
            else if (xml_reader.name () == "Podpis2")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Podpis2 = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля Подпись 3
            else if (xml_reader.name () == "Podpis3")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Podpis3 = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля Телефон 1
            else if (xml_reader.name () == "Tel1")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Tel1 = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля Телефон 2
            else if (xml_reader.name () == "Tel2")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Tel2 = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля EMail
            else if (xml_reader.name () == "EMail")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {EMail = (attr.value().toString ());}
                }
            }
            // Считывается тег со значением поля Site
            else if (xml_reader.name () == "Site")
            {
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                foreach (const QXmlStreamAttribute &attr, xml_reader.attributes())
                {
                    // получение значений, когда найдены нужные атрибуты
                    if (attr.name().toString() == "value") {Site = (attr.value().toString ());}
                }
            }


        }
#endif /*__DELETED_FRAGMENT__*/

    return true;
}

/*------------------------------------------------------------------*/
/*               считываются настройки группы DecHexBin             */
/*------------------------------------------------------------------*/
bool TSettings :: ReadFromXML_GroupDecHexBin (QXmlStreamReader *pXmlReader)
{
    bool exit_flag = false;

    // считываются все атрибуты и перебираются для считывания тех, которые нужны
    foreach (const QXmlStreamAttribute &attr, pXmlReader->attributes())
    {
        // получение значений, когда найдены нужные атрибуты
        if (attr.name().toString() == "show") {Visible_GroupDecHexBin = (attr.value().toString () == "true");}
    }

    return true;
}
/*------------------------------------------------------------------*/
/*               считываются настройки группы 32 Bits               */
/*------------------------------------------------------------------*/
bool TSettings :: ReadFromXML_Group32Bits (QXmlStreamReader *pXmlReader)
{
    bool exit_flag = false;

    // считываются все атрибуты и перебираются для считывания тех, которые нужны
    foreach (const QXmlStreamAttribute &attr, pXmlReader->attributes())
    {
        // получение значений, когда найдены нужные атрибуты
        if (attr.name().toString() == "show"    ) {Visible_Group32Bits     = (attr.value().toString () == "true");}
        if (attr.name().toString() == "hex_show") {Visible_Group32Bits_Hex = (attr.value().toString () == "true");}
    }

#ifdef __DELETED_FRAGMENT__
#endif /*__DELETED_FRAGMENT__*/

    return true;
}
/*------------------------------------------------------------------*/
/*               считываются настройки группы Bitmask               */
/*------------------------------------------------------------------*/
bool TSettings :: ReadFromXML_GroupBitmask (QXmlStreamReader *pXmlReader)
{
    bool exit_flag = false;

    // считываются все атрибуты и перебираются для считывания тех, которые нужны
    foreach (const QXmlStreamAttribute &attr, pXmlReader->attributes())
    {
        // получение значений, когда найдены нужные атрибуты
        if (attr.name().toString() == "show") {Visible_GroupBitmask = (attr.value().toString () == "true");}
    }

    /* Цикл до тех пор, пока не будет достигнут конец тега GroupBitmask или конец документа */
    while (!exit_flag)
    {
        /* Проверка, является ли данный элемент началом тега */
        if (pXmlReader->isStartElement ())
        {
            QString tag_str     = pXmlReader->name().toString();
            int     tag_str_len = tag_str.size ();

            // Найден тег, содержащий значение параметра "BitXX"
            if (tag_str.left(3) == "Bit")
            {
                // определяется номер бита, к которому относится тег
                int     idx         = -1;
                bool    idx_good    = false;
                QString idx_str     = "";

                if      (tag_str_len == 4) {idx_str = tag_str.right (1);} // Bit#
                else if (tag_str_len == 5) {idx_str = tag_str.right (2);} // Bit##
                else                       {idx_str = "";               } // incorrect
                idx = idx_str.toInt(&idx_good, 10);
                
                // считываются все атрибуты и перебираются для выделения тех, которые нужны
                if ((idx >= 0) && (idx < 32) && (idx_good))
                {
                    foreach (const QXmlStreamAttribute &attr, pXmlReader->attributes())
                    {
                        // получение значений, когда найдены нужные атрибуты
                        if (attr.name().toString() == "text" ) {MaskDataOfBit[idx].Text = attr.value().toString();}
                    }
//                  exp_data.ExpData.append (rec);
                }
            }

        } // end if isStartElement

        if ((pXmlReader->isEndElement ()) && (pXmlReader->name () == "GroupBitmask")) exit_flag = true;
        if (pXmlReader->atEnd ()                                                    ) exit_flag = true;

        if (!exit_flag) pXmlReader->readNext (); // Переход к следующему элементу XML-файла
    }

    return true;
}
/*------------------------------------------------------------------*/
/*              Записываются настройки группы DecHexBin             */
/*------------------------------------------------------------------*/
bool TSettings :: SaveToXML_GroupDecHexBin (QXmlStreamWriter *pXmlWriter)
{
    // создаётся общий тег
    pXmlWriter->writeStartElement ("GroupDecHexBin");

    // записываются атрибуты общего тега
    pXmlWriter->writeAttribute    ("show", (Visible_GroupDecHexBin ? "true" : "false"));

    // общий тег закрывается
    pXmlWriter->writeEndElement   ();


    return true;
}
/*------------------------------------------------------------------*/
/*              Записываются настройки группы 32 Bits               */
/*------------------------------------------------------------------*/
bool TSettings :: SaveToXML_Group32Bits (QXmlStreamWriter *pXmlWriter)
{
    // создаётся общий тег
    pXmlWriter->writeStartElement ("Group32Bits");

    // записываются атрибуты общего тега
    pXmlWriter->writeAttribute    ("show"    , (Visible_Group32Bits     ? "true" : "false"));
    pXmlWriter->writeAttribute    ("hex_show", (Visible_Group32Bits_Hex ? "true" : "false"));

    // общий тег закрывается
    pXmlWriter->writeEndElement   ();

    return true;
}
/*------------------------------------------------------------------*/
/*              Записываются настройки группы Bitmask               */
/*------------------------------------------------------------------*/
bool TSettings :: SaveToXML_GroupBitmask (QXmlStreamWriter *pXmlWriter)
{
    // создаётся общий тег
    pXmlWriter->writeStartElement ("GroupBitmask");

    // записываются атрибуты общего тега
    pXmlWriter->writeAttribute    ("show", (Visible_GroupBitmask ? "true" : "false"));


    // записываются параметры тегов BitXX
    for (int i=0; i<32; i++)
    {
        pXmlWriter->writeStartElement ("Bit" + QString::number(i));
        pXmlWriter->writeAttribute    ("text", MaskDataOfBit[i].Text);
        pXmlWriter->writeEndElement   ();
    }

    // общий тег закрывается
    pXmlWriter->writeEndElement   ();


    return true;
}
/*------------------------------------------------------------------*/


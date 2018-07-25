#include <QtCore>
#include <QWidget>

#include "colorschema.h"

/* глобальный список доступных цветовых схем */
extern QVector <TColorSchema> ColorSchemas;

void ColorSchemas_Init ()
{
    ColorSchemas.clear ();

    TColorSchema cs;

    /* -- ColorSchema "Standart" -- */

    cs.Name = "Standart";
    ColorSchemas.append (cs);


    /* -- ColorSchema "jasha" -- */

    cs.Name = "jasha";
    cs.StyleSheetString = "";
    cs.StyleSheetString = cs.StyleSheetString + 
    "QWidget{\n"
    "    background-color: rgb(0, 44, 255);\n"
    "    font: 8pt \"PT Mono\";\n"
    "    color: rgb(255, 200, 200);\n"
    "}";
    cs.StyleSheetString = cs.StyleSheetString + 
    "QMenuBar::item {\n"
    "    background-color: rgb(0, 44, 255);\n"
    "    font: 8pt \"PT Mono\";\n"
    "    color: rgb(255, 200, 200);\n"
    "}";
    cs.StyleSheetString = cs.StyleSheetString + 
    "QMenu::item:selected{\n"
    "    background-color: rgb(0, 0, 128);\n"
    "    font: 8pt \"PT Mono\";\n"
    "    color: rgb(255, 200, 200);\n"
    "}";
    cs.StyleSheetString = cs.StyleSheetString + 
    "QHeaderView::section {\n"
    "    background-color: rgb(0, 0, 128);\n"
    "    font: 8pt \"PT Mono\";\n"
    "    color: rgb(255, 200, 200);\n"
    "}";
    cs.BackColorSt0 = QColor (0, 44, 255);
    cs.BackColorSt1 = QColor (0,  0, 128);
    
    ColorSchemas.append (cs);
}

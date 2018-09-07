/***************************************************************************
**                                                                        **
**  Filename: colorschemas_init.cpp                                       **
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

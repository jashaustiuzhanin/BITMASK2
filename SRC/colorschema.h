/***************************************************************************
**                                                                        **
**  Filename: colorschema.h                                               **
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

#ifndef COLORSCHEMA_H
#define COLORSCHEMA_H

#include <QtCore>
#include <QApplication>
#include <QWidget>
#include <QColor>

class TColorSchema
{
  public:

    TColorSchema () {SetDefault ();}

    QString Name;

    QString StyleSheetString;

    QColor  TextColorSt0;
    QColor  BackColorSt0;
    QColor  TextColorSt1;
    QColor  BackColorSt1;

    void SetDefault ()
    {
        Name = "noname";

        StyleSheetString = "";

        QPalette app_palette = QApplication::palette ();
        TextColorSt0 = app_palette.color (QPalette::WindowText     );
        BackColorSt0 = app_palette.color (QPalette::Base           );
        TextColorSt1 = app_palette.color (QPalette::HighlightedText);
        BackColorSt1 = app_palette.color (QPalette::Highlight      );
    }

};

#endif // COLORSCHEMA_H

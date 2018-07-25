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

#ifndef DIALOGCOLORST1_H
#define DIALOGCOLORST1_H

#include <QDialog>
#include "maskdata.h"
#include "colorschema.h"

namespace Ui {
class DialogColorSt1;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DialogColorSt1 : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogColorSt1(QWidget *parent = 0);
    ~DialogColorSt1();

    void SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema);
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DialogColorSt1 *ui;

    int               BitNo      ;
    TMaskDataOfOneBit MaskData   ;
    TColorSchema      ColorSchema;

    void Repaint ();

    QColor CurrBackColorSt1 ();
    QColor CurrTextColorSt1 ();
private slots:

    void on_btnState1BackgroundColor_clicked();
    void on_btnState1TextColor_clicked();
//  void SlotRadioButtonsToggled ();
    void SlotRadioButtonsToggled_BackDefault_St1 ();
    void SlotRadioButtonsToggled_BackByUser_St1  ();
    void SlotRadioButtonsToggled_TextDefault_St1 ();
    void SlotRadioButtonsToggled_TextByUser_St1  ();

};

#endif // DIALOGCOLORST1_H

#ifndef DIALOGCOLORALLST_H
#define DIALOGCOLORALLST_H

#include <QDialog>
#include "maskdata.h"
#include "colorschema.h"

namespace Ui {
class DialogColorAllSt;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DialogColorAllSt : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogColorAllSt(QWidget *parent = 0);
    ~DialogColorAllSt();

    void SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema);
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DialogColorAllSt *ui;

    int               BitNo      ;
    TMaskDataOfOneBit MaskData   ;
    TColorSchema      ColorSchema;

    void Repaint ();

    QColor CurrBackColorSt0 ();
    QColor CurrTextColorSt0 ();
    QColor CurrBackColorSt1 ();
    QColor CurrTextColorSt1 ();

private slots:

    void on_btnState0BackgroundColor_clicked();
    void on_btnState0TextColor_clicked();
    void on_btnState1BackgroundColor_clicked();
    void on_btnState1TextColor_clicked();
//  void SlotRadioButtonsToggled ();
    void SlotRadioButtonsToggled_BackDefault_St0 ();
    void SlotRadioButtonsToggled_BackByUser_St0  ();
    void SlotRadioButtonsToggled_TextDefault_St0 ();
    void SlotRadioButtonsToggled_TextByUser_St0  ();
    void SlotRadioButtonsToggled_BackDefault_St1 ();
    void SlotRadioButtonsToggled_BackByUser_St1  ();
    void SlotRadioButtonsToggled_TextDefault_St1 ();
    void SlotRadioButtonsToggled_TextByUser_St1  ();

};
/*------------------------------------------------------------------*/

#endif // DIALOGCOLORALLST_H

#ifndef DIALOGCOLORST0_H
#define DIALOGCOLORST0_H

#include <QDialog>
#include "maskdata.h"
#include "colorschema.h"

namespace Ui {
class DialogColorSt0;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DialogColorSt0 : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogColorSt0(QWidget *parent = 0);
    ~DialogColorSt0();

    void SetData (int argBitNo, const TMaskDataOfOneBit &argMaskData, const TColorSchema &argColorSchema);
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DialogColorSt0 *ui;

    int               BitNo      ;
    TMaskDataOfOneBit MaskData   ;
    TColorSchema      ColorSchema;

    void Repaint ();

    QColor CurrBackColorSt0 ();
    QColor CurrTextColorSt0 ();

private slots:

    void on_btnState0BackgroundColor_clicked();
    void on_btnState0TextColor_clicked();
//  void on_btnState1BackgroundColor_clicked();
//  void on_btnState1TextColor_clicked();
//  void on_btnOk_clicked();
//  void on_btnCancel_clicked();
    void SlotRadioButtonsToggled_BackDefault_St0 ();
    void SlotRadioButtonsToggled_BackByUser_St0  ();
    void SlotRadioButtonsToggled_TextDefault_St0 ();
    void SlotRadioButtonsToggled_TextByUser_St0  ();

};
/*------------------------------------------------------------------*/

#endif // DIALOGCOLORST0_H

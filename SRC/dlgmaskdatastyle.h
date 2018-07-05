#ifndef DLGMASKDATASTYLE_H
#define DLGMASKDATASTYLE_H

#include <QDialog>

#include "maskdata.h"

namespace Ui {
class DlgMaskDataStyle;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
class DlgMaskDataStyle : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgMaskDataStyle (QWidget *parent = 0);
   ~DlgMaskDataStyle ();

    void SetData (int argBitNo, TMaskDataOfOneBit &argMaskData) {BitNo = argBitNo; MaskData = argMaskData; Repaint ();}
    TMaskDataOfOneBit GetData () {return MaskData;}

private:
    Ui::DlgMaskDataStyle *ui;

    int               BitNo   ;
    TMaskDataOfOneBit MaskData;

    void Repaint ();

private slots:

    void on_btnState0BackgroundColor_clicked();
    void on_btnState0TextColor_clicked();
    void on_btnState1BackgroundColor_clicked();
    void on_btnState1TextColor_clicked();
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};
/*------------------------------------------------------------------*/

#endif // DLGMASKDATASTYLE_H

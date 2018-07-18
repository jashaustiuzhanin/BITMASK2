#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgmaskdatastyle.h"
#include <QFileDialog>

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*
QString HexSpinbox::textFromValue (int val            ) const
{
}
int     HexSpinbox::valueFromText (const QString &text) const
{
}
*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
MainWindow :: MainWindow (QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi (this);

    setWindowTitle ("BitMask 2.0");
    setWindowIcon  (QIcon (":/PICS/bitmask20.png"));

    ui->spnDecimal    ->SetMode (BMQSpinBox::modeDECIMAL    );
    ui->spnDecimal    ->SetBitsCount_32 ();
    ui->spnHexadecimal->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnHexadecimal->SetBitsCount_32 ();
    ui->spnBinary     ->SetMode (BMQSpinBox::modeBINARY     );
    ui->spnBinary     ->SetBitsCount_32 ();

    ui->spnByte0_HexRight->SetBitsCount_04 ();
    ui->spnByte0_HexLeft ->SetBitsCount_04 ();
    ui->spnByte1_HexRight->SetBitsCount_04 ();
    ui->spnByte1_HexLeft ->SetBitsCount_04 ();
    ui->spnByte2_HexRight->SetBitsCount_04 ();
    ui->spnByte2_HexLeft ->SetBitsCount_04 ();
    ui->spnByte3_HexRight->SetBitsCount_04 ();
    ui->spnByte3_HexLeft ->SetBitsCount_04 ();

    ui->spnByte0_HexRight->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte0_HexLeft ->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte1_HexRight->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte1_HexLeft ->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte2_HexRight->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte2_HexLeft ->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte3_HexRight->SetMode (BMQSpinBox::modeHEXADECIMAL);
    ui->spnByte3_HexLeft ->SetMode (BMQSpinBox::modeHEXADECIMAL);

    ShowInProcessFlag = false;
    Value = 0;
    ShowValue ();

    CfgFileName  = "";
    CfgFileState = filestateNOT_OPENED_NO_CHANGES;

    QStringList headers_colors;
    QStringList headers;
    headers << "0-col";
    headers << "1-col";
    headers << "bit";
    headers << "state";
    headers << "name";
    ui->tblBitmask->setColumnCount ( 5); // Указываем число колонок
//  ui->tblBitmask->setRowCount    (32); // Указываем число колонок
    ui->tblBitmask->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tblBitmask->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tblBitmask->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->tblBitmask->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tblBitmask->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
//  ui->tblBitmask->hideColumn(0);
    // скрываем вертикальный заголовок
    ui->tblBitmask->verticalHeader()->setHidden (true);
    // делаем первые два столбца минимальной ширины
    ui->tblBitmask->horizontalHeader()->resizeSection (0, 40);
    ui->tblBitmask->horizontalHeader()->resizeSection (1, 40);

    // инициализация цветов отображения битовых масок значениями по умолчанию
    for (int i = 0; i<32; i++)
    {
        Settings.MaskDataOfBit[i].BackColorState0 = Qt::gray;
        Settings.MaskDataOfBit[i].TextColorState0 = Qt::black;
        Settings.MaskDataOfBit[i].BackColorState1 = Qt::darkBlue;
        Settings.MaskDataOfBit[i].TextColorState1 = Qt::white;
    }

    /* Выполняем заполнение QTableWidget записями с помощью цикла */
    for (int i = 0; i<32; i++)
    {
        // Вставляем строку
        ui->tblBitmask->insertRow(i);
        // заполняем колонку с номером бита
        ui->tblBitmask->setItem (i, 2, new QTableWidgetItem (QString::number(i)));

#ifdef __DELETED_FRAGMENT__
        // Создаём элемент, который будет выполнять роль чекбокса
        QTableWidgetItem *item = new QTableWidgetItem ();
        item->data (Qt::CheckStateRole);
       /* Проверяем, на статус нечетности, если нечетное устройство, то
        * выставляем состояние чекбокса в Checked, иначе в Unchecked
       if(query.value(1).toInt() == 1){
           item->setCheckState(Qt::Checked);
       } else {
           item->setCheckState(Qt::Unchecked);
       }
        * */
        item->setCheckState(Qt::Unchecked);
        // Устанавливаем чекбокс в нужную колонку
        ui->tblBitmask->setItem (i, 3, item);
/*
       // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
       ui->tblBitmask->setItem(i,2, new QTableWidgetItem(query.value(2).toString()));
       ui->tblBitmask->setItem(i,3, new QTableWidgetItem(query.value(3).toString()));
       ui->tblBitmask->setItem(i,4, new QTableWidgetItem(query.value(4).toString()));
*/
#endif /*__DELETED_FRAGMENT__*/
        // Создаём виджет, который будет содержать в себе чекбокс
        QWidget * checkbox_widget = new QWidget ();
        QCheckBox *checkbox = new QCheckBox ();      // объявляем и инициализируем чекбокс
        QHBoxLayout *layout_checkbox = new QHBoxLayout (checkbox_widget); // создаём слой с привязкой к виджету
        layout_checkbox->addWidget (checkbox);            // Устанавливаем чекбокс в слой
        layout_checkbox->setAlignment (Qt::AlignCenter);  // Отцентровываем чекбокс
        layout_checkbox->setContentsMargins (0,0,0,0);    // Устанавливаем нулевые отступы
#ifdef __DELETED_FRAGMENT__
        /* Проверяем, на статус нечетности, если нечетное устройство, то
         * выставляем состояние чекбокса в Checked, иначе в Unchecked
        if(query.value(1).toInt() == 1){
            checkBox->setChecked(true);
        } else {
            checkBox->setChecked(false);
        }
        * */
#endif /*__DELETED_FRAGMENT__*/
        checkbox->setChecked (false);

        QObject::connect (checkbox, SIGNAL(clicked()), this, SLOT(SlotOnBitmaskChkBox()));

        // Устанавливаем чекбокс в третью колонку (при счете с 0)
        ui->tblBitmask->setCellWidget (i, 3, checkbox_widget);

        QTableWidgetItem *p_item0;
        QTableWidgetItem *p_item1;
        QTableWidgetItem *p_item4;
        p_item0 = new QTableWidgetItem (QString("*"));
        p_item0->setBackground (QBrush(Settings.MaskDataOfBit[i].BackColorState0));
        p_item0->setForeground (QBrush(Settings.MaskDataOfBit[i].TextColorState0));
        ui->tblBitmask->setItem (i, 0, p_item0);
        p_item1 = new QTableWidgetItem (QString("*"));
        p_item1->setBackground (QBrush(Settings.MaskDataOfBit[i].BackColorState1));
        p_item1->setForeground (QBrush(Settings.MaskDataOfBit[i].TextColorState1));
        ui->tblBitmask->setItem (i, 1, p_item1);
        p_item4 = new QTableWidgetItem (QString(""));
        ui->tblBitmask->setItem (i, 4, p_item4);
    }
 
    // Ресайзим колонки по содержимому
    ui->tblBitmask->resizeColumnsToContents();

    // делаем таблицу Bitmask непрокручиваемой
    ui->tblBitmask->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    QFont font = ui->tblBitmask->font ();
    font.setPointSize (8);
    ui->tblBitmask->setFont (font);
    QFontMetrics fm (ui->tblBitmask->font());
    int h = fm.height() + 2;
    ui->tblBitmask->verticalHeader()->setDefaultSectionSize (h);
    ui->tblBitmask->setMinimumHeight (h*32 + ui->tblBitmask->horizontalHeader()->height()+4);
    ui->tblBitmask->setSelectionMode (QAbstractItemView::NoSelection);


//  QObject :: connect (ui->spnDecimal    , SIGNAL(valueChanged(int)), this, SLOT(SlotOnSpnDecimal    ()));
//  QObject :: connect (ui->spnHexadecimal, SIGNAL(valueChanged(   )), this, SLOT(SlotOnSpnHexadecimal()));
//  QObject :: connect (ui->spnHexadecimal, SIGNAL(SignalIsNewValueSource(BMQSpinBox::TValue)), this, SLOT(SlotOnSpnHexadecimal()));
    QObject :: connect (ui->spnDecimal    , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOnSpnDecimal    ()));
    QObject :: connect (ui->spnHexadecimal, SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOnSpnHexadecimal()));
    QObject :: connect (ui->spnBinary     , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOnSpnBinary     ()));

    QObject :: connect (ui->spnByte0_HexRight, SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte0_HexLeft , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte1_HexRight, SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte1_HexLeft , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte2_HexRight, SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte2_HexLeft , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte3_HexRight, SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));
    QObject :: connect (ui->spnByte3_HexLeft , SIGNAL(SignalIsNewValueSource()), this, SLOT(SlotOn32bitSpnBox()));

    QObject :: connect (ui->chkByte0_00, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_01, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_02, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_03, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_04, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_05, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_06, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte0_07, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_08, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_09, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_10, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_11, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_12, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_13, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_14, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte1_15, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_16, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_17, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_18, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_19, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_20, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_21, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_22, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte2_23, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_24, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_25, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_26, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_27, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_28, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_29, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_30, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));
    QObject :: connect (ui->chkByte3_31, SIGNAL(clicked()), this, SLOT(SlotOn32bitChkBox()));

    QObject :: connect (ui->tblBitmask, SIGNAL(cellClicked(int,int)), this, SLOT(SlotOnBitmaskClicked(int,int)));

    adjustSize ();

    SlotMenuEnableDisable ();
    ShowGroups ();
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnSpnDecimal ()
{
//  Value = ui->spnDecimal->value ();
    Value = (unsigned long int) ui->spnDecimal->value ();
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnSpnHexadecimal ()
{
    Value = (unsigned long int) ui->spnHexadecimal->value ();
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnSpnBinary ()
{
    Value = (unsigned long int) ui->spnBinary->value ();
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOn32bitSpnBox ()
{
    int value = 0;
    value = value | ui->spnByte3_HexLeft ->value ();
    value = value << 4;
    value = value | ui->spnByte3_HexRight->value ();
    value = value << 4;
    value = value | ui->spnByte2_HexLeft ->value ();
    value = value << 4;
    value = value | ui->spnByte2_HexRight->value ();
    value = value << 4;
    value = value | ui->spnByte1_HexLeft ->value ();
    value = value << 4;
    value = value | ui->spnByte1_HexRight->value ();
    value = value << 4;
    value = value | ui->spnByte0_HexLeft ->value ();
    value = value << 4;
    value = value | ui->spnByte0_HexRight->value ();

    Value = value;
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOn32bitChkBox ()
{
    int value = 0;
    value = value | (ui->chkByte3_31->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_30->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_29->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_28->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_27->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_26->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_25->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte3_24->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_23->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_22->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_21->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_20->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_19->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_18->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_17->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte2_16->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_15->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_14->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_13->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_12->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_11->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_10->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_09->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte1_08->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_07->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_06->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_05->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_04->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_03->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_02->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_01->isChecked () ? 0x00000001 : 0x00000000);
    value = value << 1;
    value = value | (ui->chkByte0_00->isChecked () ? 0x00000001 : 0x00000000);

    Value = value;
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnBitmaskClicked (int Row, int Column)
{
    qDebug () << "----- 1 ----- : row=" << Row << ", Column=" << Column;

    // если клик был произведён на столбце с выбором цвета для состояния 0,
    // то производим выбор цвета
    if (Column == 0)
    {
/*
        QColor color = QColorDialog::getColor (MaskDataOfBit[Row].BackColorState0, this);
        MaskDataOfBit[Row].BackColorState0 = color;
        ShowValue ();
*/
        DlgMaskDataStyle *p_dlg = new DlgMaskDataStyle (this);
        int dlg_result;
        p_dlg->SetData (Row, Settings.MaskDataOfBit[Row]);
        dlg_result = p_dlg->exec ();
        if (dlg_result == QDialog::Accepted) Settings.MaskDataOfBit[Row] = p_dlg->GetData ();
        ShowValue ();
    }
    // если клик был произведён на столбце с выбором цвета для состояния 1,
    // то производим выбор цвета
    else if (Column == 1)
    {
/*
        QColor color = QColorDialog::getColor (MaskDataOfBit[Row].BackColorState0, this);
        MaskDataOfBit[Row].BackColorState0 = color;
*/
        DlgMaskDataStyle *p_dlg = new DlgMaskDataStyle (this);
        int dlg_result;
        p_dlg->SetData (Row, Settings.MaskDataOfBit[Row]);
        dlg_result = p_dlg->exec ();
        if (dlg_result == QDialog::Accepted) Settings.MaskDataOfBit[Row] = p_dlg->GetData ();
        ShowValue ();
    }

    // если клик был произведён в столбце tblBitmask с checkbox-ами,
    // то, значит, значение Value нужно пересчитать
    else if (Column == 3)
    {
/*
        QTableWidgetItem *p_clicked_item = ui->tblBitmask->item (Row, 3);
qDebug () << "----- 2 ----- : check state" << p_clicked_item->checkState();
        if (p_clicked_item->checkState() == Qt::Checked) p_clicked_item->setCheckState (Qt::Unchecked);
        else                                             p_clicked_item->setCheckState (Qt::Checked  );
qDebug () << "----- 3 ----- : check state" << p_clicked_item->checkState();

        int value = 0;

        // show status of checkboxes in Bitmask group
        for (int i=31; i>=0; i--)
        {
            QTableWidgetItem *p_item = ui->tblBitmask->item (i, 3);
            if (!p_item) continue;

qDebug () << "----- 4 ----- : i=" << i << ", check state" << p_item->checkState();

            value = value | ((p_item->checkState() == Qt::Checked) ? 0x00000001 : 0x00000000);
            if (i>0) value = value << 1;
        }

        Value = value;
        ShowValue ();
*/
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnBitmaskChkBox ()
{
    int value = 0;

    // show status of checkboxes in Bitmask group
    for (int i=31; i>=0; i--)
    {
        // Забираем виджет из ячейки
        QWidget *item = ui->tblBitmask->cellWidget (i, 3);
        // Забираем виджет из слоя и кастуем его в QCheckBox
        QCheckBox *checkbox = qobject_cast <QCheckBox*> (item->layout()->itemAt(0)->widget());

        value = value | ((checkbox->isChecked()) ? 0x00000001 : 0x00000000);
        if (i>0) value = value << 1;
    }

    Value = value;
    ShowValue ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowValue ()
{
    QString tmp_str ;
    int     tmp_byte;

    // check for reentering in this function
    if (ShowInProcessFlag) return;
    ShowInProcessFlag = true;

    // fill decimal view
    ui->spnDecimal->setValue (Value);

    // fill hexadecimal view
    ui->spnHexadecimal->setValue (Value);

    // fill binary view
    ui->spnBinary->setValue (Value);

    // fill byte 0 bit-elements
    tmp_byte = (Value & 0x000000ff) >> 0;
    ui->chkByte0_00->setChecked (tmp_byte & 0x01);
    ui->chkByte0_01->setChecked (tmp_byte & 0x02);
    ui->chkByte0_02->setChecked (tmp_byte & 0x04);
    ui->chkByte0_03->setChecked (tmp_byte & 0x08);
    ui->chkByte0_04->setChecked (tmp_byte & 0x10);
    ui->chkByte0_05->setChecked (tmp_byte & 0x20);
    ui->chkByte0_06->setChecked (tmp_byte & 0x40);
    ui->chkByte0_07->setChecked (tmp_byte & 0x80);
    // fill byte 1 bit-elements
    tmp_byte = (Value & 0x0000ff00) >> 8;
    ui->chkByte1_08->setChecked (tmp_byte & 0x01);
    ui->chkByte1_09->setChecked (tmp_byte & 0x02);
    ui->chkByte1_10->setChecked (tmp_byte & 0x04);
    ui->chkByte1_11->setChecked (tmp_byte & 0x08);
    ui->chkByte1_12->setChecked (tmp_byte & 0x10);
    ui->chkByte1_13->setChecked (tmp_byte & 0x20);
    ui->chkByte1_14->setChecked (tmp_byte & 0x40);
    ui->chkByte1_15->setChecked (tmp_byte & 0x80);
    // fill byte 2 bit-elements
    tmp_byte = (Value & 0x00ff0000) >> 16;
    ui->chkByte2_16->setChecked (tmp_byte & 0x01);
    ui->chkByte2_17->setChecked (tmp_byte & 0x02);
    ui->chkByte2_18->setChecked (tmp_byte & 0x04);
    ui->chkByte2_19->setChecked (tmp_byte & 0x08);
    ui->chkByte2_20->setChecked (tmp_byte & 0x10);
    ui->chkByte2_21->setChecked (tmp_byte & 0x20);
    ui->chkByte2_22->setChecked (tmp_byte & 0x40);
    ui->chkByte2_23->setChecked (tmp_byte & 0x80);
    // fill byte 3 bit-elements
    tmp_byte = (Value & 0xff000000) >> 24;
    ui->chkByte3_24->setChecked (tmp_byte & 0x01);
    ui->chkByte3_25->setChecked (tmp_byte & 0x02);
    ui->chkByte3_26->setChecked (tmp_byte & 0x04);
    ui->chkByte3_27->setChecked (tmp_byte & 0x08);
    ui->chkByte3_28->setChecked (tmp_byte & 0x10);
    ui->chkByte3_29->setChecked (tmp_byte & 0x20);
    ui->chkByte3_30->setChecked (tmp_byte & 0x40);
    ui->chkByte3_31->setChecked (tmp_byte & 0x80);

    // fill byte 0 hexchar-elements
    tmp_byte = (Value & 0x0000000f) >>  0;
    ui->spnByte0_HexRight->setValue (tmp_byte);
    tmp_byte = (Value & 0x000000f0) >>  4;
    ui->spnByte0_HexLeft ->setValue (tmp_byte);
    tmp_byte = (Value & 0x00000f00) >>  8;
    ui->spnByte1_HexRight->setValue (tmp_byte);
    tmp_byte = (Value & 0x0000f000) >> 12;
    ui->spnByte1_HexLeft ->setValue (tmp_byte);
    tmp_byte = (Value & 0x000f0000) >> 16;
    ui->spnByte2_HexRight->setValue (tmp_byte);
    tmp_byte = (Value & 0x00f00000) >> 20;
    ui->spnByte2_HexLeft ->setValue (tmp_byte);
    tmp_byte = (Value & 0x0f000000) >> 24;
    ui->spnByte3_HexRight->setValue (tmp_byte);
    tmp_byte = (Value & 0xf0000000) >> 28;
    ui->spnByte3_HexLeft ->setValue (tmp_byte);

    // show status of checkboxes in Bitmask group
//  QCheckBox *p_checkbox;
    int mask = 0x00000001;
    for (int i=0; i<32; i++)
    {
        bool val_flag = (Value & mask) ? true : false;
        mask = mask << 1;

#ifdef __DELETED_FRAGMENT__
//      p_checkbox = qobject_cast <QCheckBox *> (ui->tblBitmask->cellWidget (i, 3));
//      if (!p_checkbox) continue;
//      p_checkbox->setChecked (val_flag);

        QTableWidgetItem *p_item = ui->tblBitmask->item (i, 3);
        if (!p_item) continue;
        p_item->setCheckState (val_flag ? Qt::Checked : Qt::Unchecked);
#endif /*__DELETED_FRAGMENT__*/

        // Забираем виджет из ячейки
        QWidget *item = ui->tblBitmask->cellWidget (i, 3);
        if (!item) continue;
        // Забираем виджет из слоя и кастуем его в QCheckBox
        QCheckBox *checkbox = qobject_cast <QCheckBox*> (item->layout()->itemAt(0)->widget());
        if (!checkbox) continue;

        checkbox->setChecked (val_flag);

        // Раскраска ячейки с текстом маски в зависимости от состояния бита
        QTableWidgetItem *item4 = ui->tblBitmask->item (i, 4);
        if (!item4) continue;
        if (val_flag) 
        {
            item4->setBackground (QBrush (Settings.MaskDataOfBit[i].BackColorState1));
            item4->setForeground (QBrush (Settings.MaskDataOfBit[i].TextColorState1));
        }
        else
        {
            item4->setBackground (QBrush (Settings.MaskDataOfBit[i].BackColorState0));
            item4->setForeground (QBrush (Settings.MaskDataOfBit[i].TextColorState0));
        }

        // Раскраска ячеек с выбранными цветами лля окрашивания
        QTableWidgetItem *item0 = ui->tblBitmask->item (i, 0);
        if (!item0) continue;
        item0->setBackground (QBrush (Settings.MaskDataOfBit[i].BackColorState0));
        item0->setForeground (QBrush (Settings.MaskDataOfBit[i].TextColorState0));
        QTableWidgetItem *item1 = ui->tblBitmask->item (i, 1);
        if (!item1) continue;
        item1->setBackground (QBrush (Settings.MaskDataOfBit[i].BackColorState1));
        item1->setForeground (QBrush (Settings.MaskDataOfBit[i].TextColorState1));

    }

    // release checking for reentering
    ShowInProcessFlag = false;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotMenuEnableDisable ()
{
    ui->actFILE_Quit->setEnabled (true );

    if      (CfgFileState == filestateNOT_OPENED_NO_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (false);
//      ui->actFILE_Save_As->setEnabled (true );
    }
    if      (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (true );
    }
    else if (CfgFileState == filestateOPENED_NO_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (true );
    }
    else if (CfgFileState == filestateOPENED_UNSAVED_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (true );
        ui->actFILE_Save_As->setEnabled (true );
    }

    ui->actVIEW_DEC_HEX_BIN->setChecked (ui->grpDEC_HEX_BIN->isVisible ());
    ui->actVIEW_32_bits    ->setChecked (ui->grp32_bits    ->isVisible ());
    ui->actVIEW_Bitmask    ->setChecked (ui->grpBitmask    ->isVisible ());
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowGroups ()
{
    ui->spnByte0_HexLeft ->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte0_HexRight->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte1_HexLeft ->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte1_HexRight->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte2_HexLeft ->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte2_HexRight->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte3_HexLeft ->setVisible (Settings.Visible_Group32Bits_Hex);
    ui->spnByte3_HexRight->setVisible (Settings.Visible_Group32Bits_Hex);

    ui->grpDEC_HEX_BIN->setVisible (Settings.Visible_GroupDecHexBin);
    ui->grp32_bits    ->setVisible (Settings.Visible_Group32Bits   );
    ui->grpBitmask    ->setVisible (Settings.Visible_GroupBitmask  );
    adjustSize ();

    // !!!ATT!!! temporary block for right working of adjustSize
    bool temp = ui->tbrMainToolbar->isVisible();
    ui->tbrMainToolbar->setVisible (!temp);
    adjustSize ();
    ui->tbrMainToolbar->setVisible ( temp);
    adjustSize ();
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_DEC_HEX_BIN_triggered ()
{
    Settings.Visible_GroupDecHexBin = !Settings.Visible_GroupDecHexBin;
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_32_bits_triggered ()
{
    Settings.Visible_Group32Bits = !Settings.Visible_Group32Bits;
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_Bitmask_triggered ()
{
    Settings.Visible_GroupBitmask = !Settings.Visible_GroupBitmask;
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*         Считывание настроек отчёта из файла формата XML          */
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Open_triggered()
{
    bool tmp_result = false;

    // Выбор имени для файла из которого будут считываться параметры отчёта
    QString filename = QFileDialog::getOpenFileName
                       (
                           this,
                           QString::fromUtf8 ("Выбрать файл для считывания параметров отчёта"),
                           QDir::currentPath (),
                           "XML (*.xml);;All files (*.*)"
                       );
    if ((filename == "") || (filename == 0) || (filename == QString())) return;

    tmp_result = Settings.ReadFromXML (filename);

    if (!tmp_result) return;

    CfgFileName  = filename;
    CfgFileState = filestateOPENED_NO_CHANGES;

    ShowValue  ();
    ShowGroups ();
    SlotMenuEnableDisable ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Save_triggered()
{
    CfgFileState = filestateOPENED_NO_CHANGES;
    SlotMenuEnableDisable ();
}
/*------------------------------------------------------------------*/
/*           Сохранение настроек отчёта в файл формата XML          */
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Save_As_triggered()
{
    bool tmp_result = false;

    // Выбор имени для файла, в который будут сохраняться параметры отчёта
    QString filename = QFileDialog::getSaveFileName
                       (
                           this,
                           QString::fromUtf8 ("Выбрать файл для сохранения параметров отчёта"),
                           QDir::currentPath (),
                           "XML (*.xml);;All files (*.*)"
                       );
    if ((filename == "") || (filename == 0) || (filename == QString())) return;

    tmp_result = Settings.SaveToXML (filename);

    CfgFileName  = filename;
    CfgFileState = filestateOPENED_NO_CHANGES;

    ShowValue  ();
    ShowGroups ();
    SlotMenuEnableDisable ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_MainToolbar_triggered()
{
    if (ui->tbrMainToolbar->isVisible()) ui->tbrMainToolbar->setVisible (false);
    else                                 ui->tbrMainToolbar->setVisible (true );
    SlotMenuEnableDisable ();
    adjustSize ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Quit_triggered()
{
    if      (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES)
    {
    }
    else if (CfgFileState == filestateOPENED_UNSAVED_CHANGES)
    {
    }
    else    close ();
}
/*------------------------------------------------------------------*/


#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>


/*------------------------------------------------------------------*/
bool MainWindow :: OpenCfgFile (QString FileName)
{
    bool read_result = false;
    QString filename;

    filename = QFileDialog :: getOpenFileName
               (
                   this, 
                   QString::fromUtf8 ("Open Bitmask config-file"),
                   QDir::currentPath (),
                   "Xml (*.xml);;All files (*.*)"
               );
    if (filename == "") return false;
    if (filename ==  0) return false;

    read_result = Settings.ReadFromXML (filename);
    if (!read_result) return false;

    CfgFileName  = filename;
    CfgFileState = filestateOPENED_NO_CHANGES;

    return true;
}



/*------------------------------------------------------------------*/
bool MainWindow :: SaveCfgFile (QString FileName)
{
    if ((FileName == "") || (FileName == 0) || (FileName == QString())) return false;

    /* Открываем файл для Записи с помощью пути, указанного в filename */
    QFile file (FileName);
    file.open (QIODevice::WriteOnly);


    file.close ();   // Закрывается файл

    return true;
}
/*------------------------------------------------------------------*/


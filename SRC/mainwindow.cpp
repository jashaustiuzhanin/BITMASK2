/***************************************************************************
**                                                                        **
**  Filename: mainwindow.cpp                                              **
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgmaskdatastyle.h"
#include "dialogcolorallst.h"
#include "dialogcolorst0.h"
#include "dialogcolorst1.h"
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QKeyEvent>
#include <QMessageBox>
#include "version.h"
#include <QTimer>
#include "dialogmodbusparams.h"

/*------------------------------------------------------------------*/
/* Данные: параметры для обмена с контроллером по протоколу Modbus  */
/*------------------------------------------------------------------*/
static int cycle_counter_1_10 = 1;
/*
static modbus_t *MODBUS_ctx         = NULL;
static int       MODBUS_res_connect = -1;
static int       MODBUS_res_read    = -1;
static int       MODBUS_res_write   = -1;
static uint16_t  MODBUS_tab_reg [64];
*/
static int       DelayByModbusFlag = 0; /* флаг задержки циклического исполнения из-за ожидания выполнения операции Modbus */

static int MODBUS_CONNECT_ATTEMPTED = 0;

static QTimer *pModbusTimer;

/* ----- MODBUS: connect to the modbus-server ----- */
//int MODBUS_connect_to_server ();
/* ----- Function: получение IP-адреса в виде строки ----- */
//char * IPAddrAsString (int *IPAddrParts);
/* ----- MODBUS: Чтение и разбор пакета Block 1 - Пульса PLC и времени цикла ----- */
//void MODBUS_Block01_ReadPulse ();
/* ----- MODBUS: Чтение и разбор пакета Block 2 - сигналов для модулей DO16 №4, 5 и 6 ----- */
//void MODBUS_Block02_ReadData ();

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

/* глобальный список доступных цветовых схем */
QVector <TColorSchema> ColorSchemas;
/* реализовано в colorschemas_init.cpp */
void ColorSchemas_Init ();

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

    MainTitle = "BitMask 2.0";
    setWindowTitle (MainTitle);
    setWindowIcon  (QIcon (":/PICS/bitmask20.png"));

    // отображение сообщения в статусной строке
    pStatusLabel = new QLabel (this);
    this->statusBar ()->addPermanentWidget (pStatusLabel);

    pValSrcLabel = new QLabel (this);
    pPulseLabel  = new QLabel (this);
    this->statusBar()->addWidget (pValSrcLabel);
    this->statusBar()->addWidget (pPulseLabel );
    pValSrcLabel->setText ("manual");
    pPulseLabel ->setText ("");

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
    ValSrc = valsrcMANUAL;

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
//  ui->tblBitmask->setSelectionMode(QAbstractItemView::SingleSelection);
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

    // инициализация цветовых схем
    ColorSchemas_Init ();
//  ColorSchema = ColorSchemas.at (0);
    SetColorSchemaByName ("Standart");

    // инициализация цветов отображения битовых масок значениями по умолчанию
/*
    for (int i = 0; i<32; i++)
    {
        Settings.MaskDataOfBit[i].BackColorState0 = Qt::gray;
        Settings.MaskDataOfBit[i].TextColorState0 = Qt::black;
        Settings.MaskDataOfBit[i].BackColorState1 = Qt::darkBlue;
        Settings.MaskDataOfBit[i].TextColorState1 = Qt::white;
    }
*/
//  ColorSchema.SetDefault ();

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
        p_item0->setBackground (QBrush(CurrBackColorSt0(i)));
        p_item0->setForeground (QBrush(CurrTextColorSt0(i)));
        ui->tblBitmask->setItem (i, 0, p_item0);
        p_item1 = new QTableWidgetItem (QString("*"));
        p_item1->setBackground (QBrush(CurrBackColorSt1(i)));
        p_item1->setForeground (QBrush(CurrTextColorSt1(i)));
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
//  ui->tblBitmask->setSelectionMode (QAbstractItemView::NoSelection);
    for (int bit=0; bit<32; bit++)
    {
        ui->tblBitmask->item(bit, 2)->setFlags(Qt::NoItemFlags        |
                                               Qt::ItemIsSelectable   |
//                                             Qt::ItemIsEditable     |
//                                             Qt::ItemIsDragEnabled  |
//                                             Qt::ItemIsDropEnabled  |
//                                             Qt::ItemIsUserCheckable|
                                               Qt::ItemIsEnabled      |
//                                             Qt::ItemIsAutoTristate |
//                                             Qt::ItemIsTristate     |
//                                             Qt::ItemNeverHasChildren|
//                                             Qt::ItemIsUserTristate |
                                               Qt::NoItemFlags        );
        ui->tblBitmask->item(bit, 4)->setFlags(Qt::NoItemFlags        |
//                                             Qt::ItemIsSelectable   |
                                               Qt::ItemIsEditable     |
                                               Qt::ItemIsDragEnabled  |
                                               Qt::ItemIsDropEnabled  |
                                               Qt::ItemIsUserCheckable|
                                               Qt::ItemIsEnabled      |
//                                             Qt::ItemIsAutoTristate |
//                                             Qt::ItemIsTristate     |
//                                             Qt::ItemNeverHasChildren|
//                                             Qt::ItemIsUserTristate |
                                               Qt::NoItemFlags        );
    }

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

//  QObject :: connect (ui->tblBitmask, SIGNAL(cellClicked(int,int)), this, SLOT(SlotOnBitmaskClicked(int,int)));
    QObject :: connect (ui->tblBitmask, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(SlotOnBitmaskClicked(int,int)));

    QObject :: connect (ui->tblBitmask, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(SlotOnBitmaskText()));

    QObject :: connect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

    QObject :: connect (ui->tblBitmask->selectionModel(), SIGNAL(selectionChanged(const QItemSelection, const QItemSelection)), this, SLOT(SlotBitmaskSelectionChanged()));

    MODBUS_ctx         = NULL;
    MODBUS_res_connect = -1;
    MODBUS_res_read    = -1;
    MODBUS_res_write   = -1;

    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowValue ();
    ShowGroups ();
    ShowStatus ();

    QRect r = geometry ();
    Q_UNUSED (r)
//  r.setHeight (10);
//  r.setWidth  (10);
//  setGeometry (r.left(), r.top(), 10, 10);

//  adjustSize ();
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

    TMaskDataOfOneBit mdata;
    mdata.TextColorState0 = Settings.GetTextColorSt0 (Row);
    mdata.BackColorState0 = Settings.GetBackColorSt0 (Row);
    mdata.TextColorState1 = Settings.GetTextColorSt1 (Row);
    mdata.BackColorState1 = Settings.GetBackColorSt1 (Row);

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
        p_dlg->SetData (Row, mdata);
        dlg_result = p_dlg->exec ();
        if (dlg_result == QDialog::Accepted)
        {
//          Settings.MaskDataOfBit[Row] = p_dlg->GetData ();
            mdata = p_dlg->GetData ();
            Settings.SetTextColorSt0 (Row, mdata.TextColorState0);
            Settings.SetBackColorSt0 (Row, mdata.BackColorState0);
            Settings.SetTextColorSt1 (Row, mdata.TextColorState1);
            Settings.SetBackColorSt1 (Row, mdata.BackColorState1);
        }
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
        p_dlg->SetData (Row, mdata);
        dlg_result = p_dlg->exec ();
        if (dlg_result == QDialog::Accepted)
        {
//          Settings.MaskDataOfBit[Row] = p_dlg->GetData ();
            mdata = p_dlg->GetData ();
            Settings.SetTextColorSt0 (Row, mdata.TextColorState0);
            Settings.SetBackColorSt0 (Row, mdata.BackColorState0);
            Settings.SetTextColorSt1 (Row, mdata.TextColorState1);
            Settings.SetBackColorSt1 (Row, mdata.BackColorState1);
        }
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
void MainWindow :: SlotOnBitmaskText ()
{
    if (ShowInProcessFlag) return;

    for (int i=0; i<32; i++)
    {
        QString text = ui->tblBitmask->item(i, 4)->text();
//      Settings.MaskDataOfBit[i].Text = text;
//      Settings.SetText (i, text);
        if (text != Settings.GetText (i)) Settings.SetText (i, text);
    }
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowColorSchema ()
{
    this->setStyleSheet (ColorSchema.StyleSheetString);
    this->repaint ();
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
        // и отображение текста
        QTableWidgetItem *item4 = ui->tblBitmask->item (i, 4);
        if (!item4) continue;

        QColor text_color_st0 = CurrTextColorSt0 (i);
        QColor back_color_st0 = CurrBackColorSt0 (i);
        QColor text_color_st1 = CurrTextColorSt1 (i);
        QColor back_color_st1 = CurrBackColorSt1 (i);

        if (val_flag) 
        {
            item4->setBackground (QBrush (back_color_st1));
            item4->setForeground (QBrush (text_color_st1));
        }
        else
        {
            item4->setBackground (QBrush (back_color_st0));
            item4->setForeground (QBrush (text_color_st0));
        }
        QObject :: disconnect (ui->tblBitmask, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(SlotOnBitmaskText()));
//      item4->setText (Settings.MaskDataOfBit[i].Text);
        item4->setText (Settings.GetText (i));
//qDebug () << "Bit" << i << ": item4 text = " << item4->text() << ", Settings text = " << Settings.MaskDataOfBit[i].Text;
qDebug () << "Bit" << i << ": item4 text = " << item4->text() << ", Settings text = " << Settings.GetText (i);
        QObject :: connect    (ui->tblBitmask, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(SlotOnBitmaskText()));

        // Раскраска ячеек с выбранными цветами лля окрашивания
        QTableWidgetItem *item0 = ui->tblBitmask->item (i, 0);
        if (!item0) continue;
        item0->setBackground (QBrush (back_color_st0));
        item0->setForeground (QBrush (text_color_st0));
        QTableWidgetItem *item1 = ui->tblBitmask->item (i, 1);
        if (!item1) continue;
        item1->setBackground (QBrush (back_color_st1));
        item1->setForeground (QBrush (text_color_st1));

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
//      ui->actFILE_Save_As->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (true );
        ui->actFILE_Close  ->setEnabled (false);
    }
    if      (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (true );
        ui->actFILE_Close  ->setEnabled (false);
    }
    else if (CfgFileState == filestateOPENED_NO_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (false);
        ui->actFILE_Save_As->setEnabled (true );
        ui->actFILE_Close  ->setEnabled (true );
    }
    else if (CfgFileState == filestateOPENED_UNSAVED_CHANGES)
    {
        ui->actFILE_Open   ->setEnabled (true );
        ui->actFILE_Save   ->setEnabled (true );
        ui->actFILE_Save_As->setEnabled (true );
        ui->actFILE_Close  ->setEnabled (true );
    }

    SlotBitmaskSelectionChanged ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowGroups ()
{
    // !!!ATT!!! temporary block for right working of adjustSize
//  bool temp = ui->tbrMainToolbar->isVisible();
//  ui->tbrMainToolbar->setVisible (!temp);
    ui->tbrMainToolbar->setVisible (true );
/*
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
*/
    ui->spnByte0_HexLeft ->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte0_HexRight->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte1_HexLeft ->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte1_HexRight->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte2_HexLeft ->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte2_HexRight->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte3_HexLeft ->setVisible (Settings.GetVisible_Group32Bits_Hex());
    ui->spnByte3_HexRight->setVisible (Settings.GetVisible_Group32Bits_Hex());

    ui->grpDEC_HEX_BIN->setVisible (Settings.GetVisible_GroupDecHexBin());
    ui->grp32_bits    ->setVisible (Settings.GetVisible_Group32Bits   ());
    ui->grpBitmask    ->setVisible (Settings.GetVisible_GroupBitmask  ());

    ui->tbrMainToolbar->setVisible (true );
    adjustSize ();

    // !!!ATT!!! temporary block for right working of adjustSize
//  ui->tbrMainToolbar->setVisible ( temp);
    ui->tbrMainToolbar->setVisible (false);
    adjustSize ();
    resize(sizeHint());
    ui->tbrMainToolbar->setVisible (Settings.GetVisible_MainToolBar());

    ui->actVIEW_DEC_HEX_BIN->setChecked (ui->grpDEC_HEX_BIN->isVisible ());
    ui->actVIEW_32_bits    ->setChecked (ui->grp32_bits    ->isVisible ());
    ui->actVIEW_Bitmask    ->setChecked (ui->grpBitmask    ->isVisible ());

    ui->actVIEW_32_bits_HEX_fields->setChecked (ui->spnByte0_HexLeft->isVisible());
    ui->actVIEW_Bitmask_St_Color_Columns->setChecked (Settings.GetVisible_GroupBitmask_StColorColumns());

    if (Settings.GetVisible_GroupBitmask_StColorColumns())
    {
        ui->tblBitmask->setColumnHidden (0, false);
        ui->tblBitmask->setColumnHidden (1, false);
    }
    else
    {
        ui->tblBitmask->setColumnHidden (0, true );
        ui->tblBitmask->setColumnHidden (1, true );
    }
//  resize(sizeHint());
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ShowStatus ()
{
    // отображение "*" перед основным текстом в заголовке если есть
    // несохранённые изменения
    QString tmp_str;
    tmp_str = MainTitle;

    if ((CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES) || 
        (CfgFileState == filestateOPENED_UNSAVED_CHANGES    )  )
    {
        tmp_str = "* " + MainTitle;
    }
//  setWindowTitle (MainTitle);
    setWindowTitle (tmp_str);

    // отображение имени открытого файла в строке статуса
    tmp_str = "";
    if ((CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES) || 
        (CfgFileState == filestateOPENED_UNSAVED_CHANGES    )  )
    {
        tmp_str = "unsaved changes. ";
    }
    if ((CfgFileState == filestateOPENED_NO_CHANGES         ) || 
        (CfgFileState == filestateOPENED_UNSAVED_CHANGES    )  )
    {
        tmp_str = tmp_str + " file \"" + CfgFileName + "\" is opened";
    }
    else
    {
        tmp_str = tmp_str + " no file opened";
    }
    pStatusLabel->setText (tmp_str);
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QSize MainWindow :: sizeHint ()
{
    QSize s;
    s.setHeight (10);
    s.setWidth  (10);
    return s;
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QColor MainWindow :: CurrTextColorSt0 (int BitNo)
{
    QColor text_color_st0 = QColor ();
//  if ((BitNo >= 0) && (BitNo < 32)) text_color_st0 = Settings.MaskDataOfBit[BitNo].TextColorState0;
    text_color_st0 = Settings.GetTextColorSt0 (BitNo);
    if (!text_color_st0.isValid()   ) text_color_st0 = ColorSchema.TextColorSt0;
    return text_color_st0;
}
QColor MainWindow :: CurrBackColorSt0 (int BitNo)
{
    QColor back_color_st0 = QColor ();
//  if ((BitNo >= 0) && (BitNo < 32)) back_color_st0 = Settings.MaskDataOfBit[BitNo].BackColorState0;
    back_color_st0 = Settings.GetBackColorSt0 (BitNo);
    if (!back_color_st0.isValid()   ) back_color_st0 = ColorSchema.BackColorSt0;
    return back_color_st0;
}
QColor MainWindow :: CurrTextColorSt1 (int BitNo)
{
    QColor text_color_st1 = QColor ();
//  if ((BitNo >= 0) && (BitNo < 32)) text_color_st1 = Settings.MaskDataOfBit[BitNo].TextColorState1;
    text_color_st1 = Settings.GetTextColorSt1 (BitNo);
    if (!text_color_st1.isValid()   ) text_color_st1 = ColorSchema.TextColorSt1;
    return text_color_st1;
}
QColor MainWindow :: CurrBackColorSt1 (int BitNo)
{
    QColor back_color_st1 = QColor ();
//  if ((BitNo >= 0) && (BitNo < 32)) back_color_st1 = Settings.MaskDataOfBit[BitNo].BackColorState1;
    back_color_st1 = Settings.GetBackColorSt1 (BitNo);
    if (!back_color_st1.isValid()   ) back_color_st1 = ColorSchema.BackColorSt1;
    return back_color_st1;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_DEC_HEX_BIN_triggered ()
{
//  Settings.Visible_GroupDecHexBin = !Settings.Visible_GroupDecHexBin;
    Settings.SetVisible_GroupDecHexBin (!Settings.GetVisible_GroupDecHexBin());
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_32_bits_triggered ()
{
//  Settings.Visible_Group32Bits = !Settings.Visible_Group32Bits;
    Settings.SetVisible_Group32Bits (!Settings.GetVisible_Group32Bits());
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actVIEW_Bitmask_triggered ()
{
//  Settings.Visible_GroupBitmask = !Settings.Visible_GroupBitmask;
    Settings.SetVisible_GroupBitmask (!Settings.GetVisible_GroupBitmask());
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_32_bits_HEX_fields_triggered()
{
//  Settings.Visible_Group32Bits_Hex = !Settings.Visible_Group32Bits_Hex;
    Settings.SetVisible_Group32Bits_Hex (!Settings.GetVisible_Group32Bits_Hex());
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_Bitmask_St_Color_Columns_triggered()
{
    Settings.SetVisible_GroupBitmask_StColorColumns (!Settings.GetVisible_GroupBitmask_StColorColumns());
    ShowGroups ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_Color_Standart_triggered()
{
//  ColorSchema = ColorSchemas.at (0);
//  ShowColorSchema ();
    SetColorSchemaByName ("Standart");
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_Color_jasha_triggered()
{
//  ColorSchema = ColorSchemas.at (1);
//  ShowColorSchema ();
    SetColorSchemaByName ("jasha");
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actVIEW_MainToolbar_triggered()
{
//  if (ui->tbrMainToolbar->isVisible()) ui->tbrMainToolbar->setVisible (false);
//  else                                 ui->tbrMainToolbar->setVisible (true );
    Settings.SetVisible_MainToolBar (!Settings.GetVisible_MainToolBar());
    ShowGroups ();
    SlotMenuEnableDisable ();
    adjustSize ();
}
/*------------------------------------------------------------------*/
/*            Считывание настроек из файла формата XML              */
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Open_triggered()
{
    bool tmp_result = false;

    // ----- Предварительные действия перед открытием файла в зависимости от текущего состояния ----- 


    tmp_result = SaveCurrSettingsBeforeNextAction (" open file");
    if (!tmp_result) return;


    // ----- Открытие файла с настройками ----- 

    // Выбор имени для файла из которого будут считываться параметры отчёта
    QString filename = QFileDialog::getOpenFileName
                       (
                           this,
                           QString::fromUtf8 ("Выбрать файл для считывания параметров отчёта"),
                           QDir::currentPath (),
                           "XML (*.xml);;All files (*.*)"
                       );
    if ((filename == "") || (filename == 0) || (filename == QString())) return;
    
    // считывание файла по выбранному имени
    tmp_result = Settings.ReadFromXML (filename);
    
    if (!tmp_result) return;
    
    CfgFileName  = filename;
    CfgFileState = filestateOPENED_NO_CHANGES;
    
    // перерисовка с новыми настройками
    ShowValue  ();
    ShowGroups ();
    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowStatus ();

    // ----- DEBUG ----- 
    for (int i=0; i<32; i++)
    {
//      qDebug () << "After ReadXML: Bit" << i << ": Settings text = " << Settings.MaskDataOfBit[i].Text;
        qDebug () << "After ReadXML: Bit" << i << ": Settings text = " << Settings.GetText (i);
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Save_triggered()
{
    bool tmp_result = false;
    QString filename_to_save = CfgFileName;

    // сохранение текущих настроек если имя файла ещё не задано
    if ((filename_to_save == ""       ) || (filename_to_save == 0     ) || 
        (filename_to_save == QString()) || (filename_to_save.isEmpty())  )
    {
        return on_actFILE_Save_As_triggered ();
    }
    // собственно сохранение текущих настроек в файл с выбранным именем
    tmp_result = Settings.SaveToXML (filename_to_save);
    if (!tmp_result)
    {
        QMessageBox :: warning (this, "Warning", "File save error!");
        return;
    }
    CfgFileName  = filename_to_save;
    CfgFileState = filestateOPENED_NO_CHANGES;

    ShowValue  ();
    ShowGroups ();
    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowStatus ();
}
/*------------------------------------------------------------------*/
/*           Сохранение настроек отчёта в файл формата XML          */
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Save_As_triggered()
{
    bool tmp_result = false;
    QString filename_to_save = CfgFileName;

    // Выбор имени для файла, в который будут сохранены текущие настройки
    filename_to_save = QFileDialog :: getSaveFileName
                       (
                           this,
                           QString::fromUtf8 ("Select filename to save current changes"),
                           QDir::currentPath (),
                           "XML (*.xml);;All files (*.*)"
                       );
    // сохранение текущих настроек
    if ((filename_to_save == ""       ) || (filename_to_save == 0     ) || 
        (filename_to_save == QString()) || (filename_to_save.isEmpty())  ) return;
    // собственно сохранение текущих настроек в файл с выбранным именем
    tmp_result = Settings.SaveToXML (filename_to_save);
    if (!tmp_result)
    {
        QMessageBox :: warning (this, "Warning", "File save error!");
        return;
    }
    CfgFileName  = filename_to_save;
    CfgFileState = filestateOPENED_NO_CHANGES;

    ShowValue  ();
    ShowGroups ();
    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowStatus ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Quit_triggered()
{
    bool tmp_result = false;

    // ----- Предварительные действия перед закрытием программы в зависимости от текущего состояния ----- 

    tmp_result = SaveCurrSettingsBeforeNextAction (" close application");
    if (!tmp_result) return;

    // ----- MODBUS: отключение связи -----

    // !!!ATT!!! сделать отключение связи по Modbus

    // ----- Закрытие программы ----- 

    close ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actFILE_Close_triggered()
{
    bool tmp_result = false;

    // ----- Предварительные действия перед закрытием файла настроек в зависимости от текущего состояния ----- 

    tmp_result = SaveCurrSettingsBeforeNextAction (" close file");
    if (!tmp_result) return;

    // ----- "закрытие файла настроек" - применение "пустых" настроек по умолчанию ----- 

    Settings.SetVoid ();

    CfgFileName  = "";
    CfgFileState = filestateNOT_OPENED_NO_CHANGES;
    
    // перерисовка с новыми настройками
    ShowValue  ();
    ShowGroups ();
    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowStatus ();
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotOnSettingsTouched ()
{
    if (Settings.IsChanged())
    {
        if      (CfgFileState == filestateNOT_OPENED_NO_CHANGES) CfgFileState = filestateNOT_OPENED_UNSAVED_CHANGES;
        else if (CfgFileState == filestateOPENED_NO_CHANGES    ) CfgFileState = filestateOPENED_UNSAVED_CHANGES    ;
    }
    else
    {
        if      (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES) CfgFileState = filestateNOT_OPENED_NO_CHANGES;
        else if (CfgFileState == filestateOPENED_UNSAVED_CHANGES    ) CfgFileState = filestateOPENED_NO_CHANGES    ;
    }
    ShowValue  ();
    ShowGroups ();
    ShowColorSchema ();
    SlotMenuEnableDisable ();
    ShowStatus ();
}
/*------------------------------------------------------------------*/

/*
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>
*/

/*------------------------------------------------------------------*/
/*
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


*/
/*------------------------------------------------------------------*/
/*
bool MainWindow :: SaveCfgFile (QString FileName)
{
    if ((FileName == "") || (FileName == 0) || (FileName == QString())) return false;

    // Открываем файл для Записи с помощью пути, указанного в filename
    QFile file (FileName);
    file.open (QIODevice::WriteOnly);


    file.close ();   // Закрывается файл

    return true;
}
*/

/*------------------------------------------------------------------*/
// !!!ATT!!! this fragment based on code from link:
// http://qaru.site/questions/337587/selected-rowsline-in-qtableview-copy-to-qclipboard

void MainWindow :: keyPressEvent (QKeyEvent * event)
{
    if(event->matches(QKeySequence::Copy) )
    {
//      copy();
    }
    else if(event->matches(QKeySequence::Paste) )
    {
//      paste();
        PasteFromBuffer ();
    }
    else
    {
        QMainWindow :: keyPressEvent (event);
    }
}
/*------------------------------------------------------------------*/
// !!!ATT!!! this fragment based on code from link:
// http://qaru.site/questions/337587/selected-rowsline-in-qtableview-copy-to-qclipboard
void MainWindow :: PasteFromBuffer ()
{
    int     line_no   = -1;
    QString line_text = "";

    line_no = ui->tblBitmask->selectionModel()->currentIndex().row();
    if (line_no <   0) line_no = 0;
    if (line_no >= 32) line_no = 0;

    QString buf_text = qApp->clipboard()->text();
    int     buf_pos   =  0;
    int     buf_size  =  buf_text.size();

    bool exit_flag = false;
    while (!exit_flag)
    {
        if (buf_pos >= buf_size)
        {
            // end of buffer
//          ui->tblBitmask->item(line_no, 4)->setText (line_text);
            Settings.SetText (line_no, line_text);
            exit_flag = true;
        }
        else if (buf_text.at(buf_pos) == QChar('\n'))
        {
            // end of line
//          ui->tblBitmask->item(line_no, 4)->setText (line_text);
            Settings.SetText (line_no, line_text);
            line_text = "";
            line_no   ++  ;
            if (line_no >= 32)           exit_flag = true;
            if (buf_pos >= (buf_size-1)) exit_flag = true; // защита от лишнего \n перед концом буфера
        }
        else
        {
            line_text = line_text.append (buf_text.at(buf_pos));
        }
        buf_pos ++ ;
    }
}
/*------------------------------------------------------------------*/
bool MainWindow :: SaveCurrSettingsBeforeNextAction (QString InformTextTail)
{
    // проверка необходимости сохранения настроек перед
    // тем как произвести дальнейшие действия (открытие
    // другого файла с настройками, закрытие приложения
    // и т.д.)
    // возвращается признак возможности продолжения
    // дальнейших действий. Если пользовал выбрал отме-
    // ну или произошла ошибка при сохранении, то даль-
    // нейшие действия продолжать нельзя - возвращается
    // false. Иначе, если сохранение прошло успешно или
    // вообще не потребовалось, возвращается true.

    QString filename_to_save = CfgFileName;
    QMessageBox::StandardButton reply;
    QMessageBox msg;
    bool tmp_result;
    int  dlg_result;

    if (0) return true;

    else if (CfgFileState == filestateNOT_OPENED_NO_CHANGES) return true;
    else if (CfgFileState == filestateOPENED_NO_CHANGES    ) return true;
    else if (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES)
    {
        // Предварительный запрос: сохранить ли имеющиеся изменения настроек в файле
        reply = QMessageBox :: question (this, QString::fromUtf8("Attention"),
                                         QString::fromUtf8("You have usaved changes in settings.\nDo You want to save current settings before") + InformTextTail + "?",
                                         QMessageBox::Yes | QMessageBox::Ignore | QMessageBox::Cancel);
        if (0) return true ;
        else if (reply == QMessageBox::Cancel) return false;
        else if (reply == QMessageBox::Ignore) return true ;
        else if (reply == QMessageBox::Yes   ) goto CHOICE_FILE_NAME;
    }
    else if (CfgFileState == filestateOPENED_UNSAVED_CHANGES)
    {
        // Предварительный запрос: сохранить ли имеющиеся изменения настроек в файле
        msg.setWindowTitle ("Attention");
        msg.setInformativeText ("You have usaved changes in settings.\nDo You want to save current settings before" + InformTextTail + "?");
        msg.setIcon (QMessageBox::Question);
        msg.setStandardButtons (QMessageBox::Save);
        msg.addButton (QString("Save As"), QMessageBox::AcceptRole);
        msg.addButton (QMessageBox::Ignore);
        msg.addButton (QMessageBox::Cancel);
/*
        reply = QMessageBox :: question (this, QString::fromUtf8("Attention"),
                                         QString::fromUtf8("You have usaved changes in settings.\nDo You want to save current settings before open file?"),
//                                       QMessageBox::Save | QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
                                         msg.standardButtons());
*/
        dlg_result = msg.exec ();
        reply = (QMessageBox::StandardButton) dlg_result;

        if (0);
        else if (reply == QMessageBox::Cancel) return false;
        else if (reply == QMessageBox::Ignore) return true ;
        else if (reply == QMessageBox::Save  ) goto SAVING;
        else                                   goto CHOICE_FILE_NAME;
    }
CHOICE_FILE_NAME:

    // Выбор имени для файла, в который будут сохранены текущие настройки
    filename_to_save = QFileDialog :: getSaveFileName
                       (
                           this,
                           QString::fromUtf8 ("Select filename to save current changes"),
                           QDir::currentPath (),
                           "XML (*.xml);;All files (*.*)"
                       );
    goto SAVING;

SAVING:

    // сохранение текущих настроек
    if ((filename_to_save == ""       ) || (filename_to_save == 0     ) || 
        (filename_to_save == QString()) || (filename_to_save.isEmpty())  ) return false;
    // собственно сохранение текущих настроек в файл с выбранным именем
    tmp_result = Settings.SaveToXML (filename_to_save);
    if (!tmp_result)
    {
        QMessageBox :: warning (this, "Warning", "File save error!");
        return false;
    }
    CfgFileName  = filename_to_save;
    if (CfgFileState == filestateOPENED_UNSAVED_CHANGES    ) CfgFileState = filestateOPENED_NO_CHANGES    ;
    if (CfgFileState == filestateNOT_OPENED_UNSAVED_CHANGES) CfgFileState = filestateNOT_OPENED_NO_CHANGES;

    return true;
}

/*------------------------------------------------------------------*/
void MainWindow :: SetColorSchemaByName (QString Name)
{
    ColorSchema.SetDefault ();
    for (int i=0; i<ColorSchemas.count(); i++)
    {
        if (ColorSchemas[i].Name == Name) 
        {
            ColorSchema = ColorSchemas[i];
            break;
        }
    }
    Settings.SetColorSchemaName (Name);
}
/*------------------------------------------------------------------*/
void MainWindow::on_actHELP_About_triggered()
{
    QMessageBox :: about (this, "About",
                          VER_PRODUCTNAME_STR
                          "\n" VER_FILE_DESCRIPTION_STR
                          "\n" "Version: " VER_FILE_VERSION_STR
                          "\n" "Build date: " __DATE__ ", " __TIME__
                          "\n" VER_COPYRIGHT_STR
                          "\n"
                          "\n" "For work with Modbus used \"libmodbus\" -"
                          "\n" "a groovy modbus library by"
                          "\n" "Stéphane Raimbault <stephane.raimbault@gmail.com>"
                          "\n" "Tobias Doerffel <tobias.doerffel@gmail.com>"
                          "\n" "Florian Forster <ff@octo.it>");
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actEDIT_Choice_Color_AllSt_triggered()
{
#ifdef __DELETED_FRAGMENT__

    QModelIndexList selection = ui->tblBitmask->selectionModel()->selectedRows();
    TMaskDataOfOneBit mdata;
    int row_for_title = -1;

    // определяем количество выделенных бит (строк)
    int count = selection.count();
    if (count < 1) return;
    // если выделена только одна строка, то считываются её текущие
    // цветовые настройки
    if (count == 1)
    {
        int row = ui->tblBitmask->selectionModel()->currentIndex().row();
        if ((row >= 0) && (row < 32))
        {
            mdata.TextColorState0 = Settings.GetTextColorSt0 (row);
            mdata.BackColorState0 = Settings.GetBackColorSt0 (row);
            mdata.TextColorState1 = Settings.GetTextColorSt1 (row);
            mdata.BackColorState1 = Settings.GetBackColorSt1 (row);

            row_for_title = row;
        }
    }
    // иначе берутся пустые цветовые настройки
    else
    {
        mdata.TextColorState0 = QColor ();
        mdata.BackColorState0 = QColor ();
        mdata.TextColorState1 = QColor ();
        mdata.BackColorState1 = QColor ();
    }

    DlgMaskDataStyle *p_dlg = new DlgMaskDataStyle (this);
    int dlg_result;
    p_dlg->SetData (row_for_title, mdata);
    dlg_result = p_dlg->exec ();
    if (dlg_result == QDialog::Accepted)
    {
        mdata = p_dlg->GetData ();

        QObject :: disconnect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        for (int i=0; i<count; i++)
        {
            int row = selection.at(i).row();
            if (row <   0) continue;
            if (row >= 32) continue;

            Settings.SetTextColorSt0 (row, mdata.TextColorState0);
            Settings.SetBackColorSt0 (row, mdata.BackColorState0);
            Settings.SetTextColorSt1 (row, mdata.TextColorState1);
            Settings.SetBackColorSt1 (row, mdata.BackColorState1);
        }

        QObject :: connect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        SlotOnSettingsTouched();
    }
    ShowValue ();

#endif /*__DELETED_FRAGMENT__*/

    QModelIndexList selection = ui->tblBitmask->selectionModel()->selectedRows();
    TMaskDataOfOneBit mdata;
    int row_for_title = -1;

    // определяем количество выделенных бит (строк)
    int count = selection.count();
    if (count < 1) return;
    // если выделена только одна строка, то считываются её текущие
    // цветовые настройки
    if (count == 1)
    {
        int row = ui->tblBitmask->selectionModel()->currentIndex().row();
        if ((row >= 0) && (row < 32))
        {
            mdata.TextColorState0 = Settings.GetTextColorSt0 (row);
            mdata.BackColorState0 = Settings.GetBackColorSt0 (row);
            mdata.TextColorState1 = Settings.GetTextColorSt1 (row);
            mdata.BackColorState1 = Settings.GetBackColorSt1 (row);

            row_for_title = row;
        }
    }
    // иначе берутся пустые цветовые настройки
    else
    {
        mdata.TextColorState0 = QColor ();
        mdata.BackColorState0 = QColor ();
        mdata.TextColorState1 = QColor ();
        mdata.BackColorState1 = QColor ();
    }

    DialogColorAllSt *p_dlg = new DialogColorAllSt (this);
    int dlg_result;
    p_dlg->SetData (row_for_title, mdata, ColorSchema);
    dlg_result = p_dlg->exec ();
    if (dlg_result == QDialog::Accepted)
    {
        mdata = p_dlg->GetData ();

        QObject :: disconnect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        for (int i=0; i<count; i++)
        {
            int row = selection.at(i).row();
            if (row <   0) continue;
            if (row >= 32) continue;

            Settings.SetTextColorSt0 (row, mdata.TextColorState0);
            Settings.SetBackColorSt0 (row, mdata.BackColorState0);
            Settings.SetTextColorSt1 (row, mdata.TextColorState1);
            Settings.SetBackColorSt1 (row, mdata.BackColorState1);
        }

        QObject :: connect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        SlotOnSettingsTouched();
    }
    ShowValue ();

}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actEDIT_Choice_Color_St0_triggered()
{
    QModelIndexList selection = ui->tblBitmask->selectionModel()->selectedRows();
    TMaskDataOfOneBit mdata;
    int row_for_title = -1;

    // определяем количество выделенных бит (строк)
    int count = selection.count();
    if (count < 1) return;
    // если выделена только одна строка, то считываются её текущие
    // цветовые настройки
    if (count == 1)
    {
        int row = ui->tblBitmask->selectionModel()->currentIndex().row();
        if ((row >= 0) && (row < 32))
        {
            mdata.TextColorState0 = Settings.GetTextColorSt0 (row);
            mdata.BackColorState0 = Settings.GetBackColorSt0 (row);
            mdata.TextColorState1 = Settings.GetTextColorSt1 (row);
            mdata.BackColorState1 = Settings.GetBackColorSt1 (row);

            row_for_title = row;
        }
    }
    // иначе берутся пустые цветовые настройки
    else
    {
        mdata.TextColorState0 = QColor ();
        mdata.BackColorState0 = QColor ();
        mdata.TextColorState1 = QColor ();
        mdata.BackColorState1 = QColor ();
    }

    DialogColorSt0 *p_dlg = new DialogColorSt0 (this);
    int dlg_result;
    p_dlg->SetData (row_for_title, mdata, ColorSchema);
    dlg_result = p_dlg->exec ();
    if (dlg_result == QDialog::Accepted)
    {
        mdata = p_dlg->GetData ();

        QObject :: disconnect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        for (int i=0; i<count; i++)
        {
            int row = selection.at(i).row();
            if (row <   0) continue;
            if (row >= 32) continue;

            Settings.SetTextColorSt0 (row, mdata.TextColorState0);
            Settings.SetBackColorSt0 (row, mdata.BackColorState0);
//          Settings.SetTextColorSt1 (row, mdata.TextColorState1);
//          Settings.SetBackColorSt1 (row, mdata.BackColorState1);
        }

        QObject :: connect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        SlotOnSettingsTouched();
    }
    ShowValue ();

}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actEDIT_Choice_Color_St1_triggered()
{
    QModelIndexList selection = ui->tblBitmask->selectionModel()->selectedRows();
    TMaskDataOfOneBit mdata;
    int row_for_title = -1;

    // определяем количество выделенных бит (строк)
    int count = selection.count();
    if (count < 1) return;
    // если выделена только одна строка, то считываются её текущие
    // цветовые настройки
    if (count == 1)
    {
        int row = ui->tblBitmask->selectionModel()->currentIndex().row();
        if ((row >= 0) && (row < 32))
        {
            mdata.TextColorState0 = Settings.GetTextColorSt0 (row);
            mdata.BackColorState0 = Settings.GetBackColorSt0 (row);
            mdata.TextColorState1 = Settings.GetTextColorSt1 (row);
            mdata.BackColorState1 = Settings.GetBackColorSt1 (row);

            row_for_title = row;
        }
    }
    // иначе берутся пустые цветовые настройки
    else
    {
        mdata.TextColorState0 = QColor ();
        mdata.BackColorState0 = QColor ();
        mdata.TextColorState1 = QColor ();
        mdata.BackColorState1 = QColor ();
    }

    DialogColorSt1 *p_dlg = new DialogColorSt1 (this);
    int dlg_result;
    p_dlg->SetData (row_for_title, mdata, ColorSchema);
    dlg_result = p_dlg->exec ();
    if (dlg_result == QDialog::Accepted)
    {
        mdata = p_dlg->GetData ();

        QObject :: disconnect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        for (int i=0; i<count; i++)
        {
            int row = selection.at(i).row();
            if (row <   0) continue;
            if (row >= 32) continue;

//          Settings.SetTextColorSt0 (row, mdata.TextColorState0);
//          Settings.SetBackColorSt0 (row, mdata.BackColorState0);
            Settings.SetTextColorSt1 (row, mdata.TextColorState1);
            Settings.SetBackColorSt1 (row, mdata.BackColorState1);
        }

        QObject :: connect (&Settings, SIGNAL(SignalTouched()), this, SLOT(SlotOnSettingsTouched()));

        SlotOnSettingsTouched();
    }
    ShowValue ();

}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotBitmaskSelectionChanged ()
{
    // определяем количество выделенных бит (строк)
    int count = ui->tblBitmask->selectionModel()->selectedRows().count();
    if (count < 1)
    {
        ui->actEDIT_Choice_Color_St0  ->setEnabled (false);
        ui->actEDIT_Choice_Color_St1  ->setEnabled (false);
        ui->actEDIT_Choice_Color_AllSt->setEnabled (false);
    }
    else
    {
        ui->actEDIT_Choice_Color_St0  ->setEnabled (true );
        ui->actEDIT_Choice_Color_St1  ->setEnabled (true );
        ui->actEDIT_Choice_Color_AllSt->setEnabled (true );
    }

}

/*==================================================================*/
/*                              MODBUS                              */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actMODBUS_Start_triggered()
{
    SlotModbusStart ();
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow::on_actMODBUS_Stop_triggered()
{
    SlotModbusStop  ();
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: on_actMODBUS_Settings_triggered ()
{
    DialogModbusParams *p_dlg = new DialogModbusParams (this);
    p_dlg->SetData (Settings.GetModbusParams());
    int dlg_result;
    dlg_result = p_dlg->exec ();
    if (dlg_result == QDialog::Accepted)
    {
        p_dlg->GetData (Settings.GetModbusParams());
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotModbusStart ()
{
    ValSrc = valsrcMODBUS;
//  MODBUS_connect_to_server ();
    ModbusConnectToServer ();
    pModbusTimer = new QTimer (this);
    QObject :: connect (pModbusTimer, SIGNAL(timeout()), this, SLOT(SlotCycleDataRead ()));
    pModbusTimer->start ( 250);
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotModbusStop  ()
{
    pModbusTimer->stop ();
    delete pModbusTimer;
    pModbusTimer = 0;
    if (MODBUS_ctx != NULL) {modbus_close (MODBUS_ctx); modbus_free (MODBUS_ctx); MODBUS_ctx = NULL;}

    ValSrc = valsrcMANUAL;
    pValSrcLabel->setText ("manual");
    pPulseLabel ->setText ("");
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: SlotCycleDataRead ()
{
    /* иначе, если используется настоящий внешний контроллер,  */ /* MODBUS TCP */
    /* то его сигналы и другие параметры считываются по Modbus */
    if (ValSrc == valsrcMODBUS)
    {
        DelayByModbusFlag = 1;

        pValSrcLabel->setText (QString("MB ") + Settings.GetModbusServerIPCfgStr(true) + 
                               QString(", reg ") + QString::number(Settings.GetModbusValueRegNo()));
        pPulseLabel ->setText ("");

        /* если связь с контроллером через сервер Modbus установлена, то производится обработка Modbus-пакетов */
        if ((MODBUS_ctx != NULL) && (MODBUS_res_connect != -1))
        {
//          modbus_set_slave (MODBUS_ctx, PLC_ModbusConfig.MBNodeAddr);
		    modbus_set_slave (MODBUS_ctx, Settings.GetModbusServerMBNode());
        
            if ( ((cycle_counter_1_10 >= 1) && (cycle_counter_1_10 <=  4)) ||
                 ((cycle_counter_1_10 >= 6) && (cycle_counter_1_10 <=  9))  )
            {
            /* MODBUS: Чтение и разбор пакета Block 1 - Пульса PLC и времени цикла */
//          MODBUS_Block01_ReadPulse ();
            ModbusReadPulse ();
            if (Settings.GetModbusPulseRegNo () >= 0) pPulseLabel->setText (QString("pulse ") + QString::number(ModbusServerPulse));

            /* MODBUS: Чтение и разбор пакета Block 2 - сигналов для модулей DO16 №4, 5 и 6 */
//          MODBUS_Block02_ReadData ();
            ModbusReadValue ();
            ShowValue ();
            }

        }
        /* иначе, если связь не установлена, то один раз производится попытка установки связи */
        else if ((!MODBUS_CONNECT_ATTEMPTED) || (cycle_counter_1_10 == 10))
        {
            /* MODBUS: connect to the modbus-server */
//          MODBUS_connect_to_server ();
            ModbusConnectToServer ();

            /* устанавливается признак того, что попытка соединения уже производилась */
            MODBUS_CONNECT_ATTEMPTED = 1;
        }

        DelayByModbusFlag = 0;
    }

}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
int  MainWindow :: ModbusConnectToServer ()
{
    int result = 0;

    if (MODBUS_ctx != NULL) modbus_free (MODBUS_ctx);
    
//  MODBUS_ctx = modbus_new_tcp ("192.168.56.101", 502);
//  MODBUS_ctx = modbus_new_tcp (IPAddrAsString (PLC_ModbusConfig.IPAddrPart), PLC_ModbusConfig.Port);
    MODBUS_ctx = modbus_new_tcp (Settings.GetModbusServerIPCfgStr(false).toLatin1(), Settings.GetModbusIPPort());
        
    if (MODBUS_ctx == NULL) {result = 0; return result;}
    
    MODBUS_res_connect = modbus_connect (MODBUS_ctx);
    if (MODBUS_res_connect == -1)
    {
        char s[500];
        strcpy (s, modbus_strerror ((int)MODBUS_ctx));
        s[499] = '\0x00';
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ModbusReadValue ()
{
    int value_reg_no = Settings.GetModbusValueRegNo ();
    if (value_reg_no >= 0)
    {
        MODBUS_res_read = modbus_read_registers (MODBUS_ctx, value_reg_no, 2, MODBUS_tab_reg);
        Value = MODBUS_tab_reg [0];
    }
    else
    {
//      Value = 0;
    }
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
void MainWindow :: ModbusReadPulse ()
{
    int pulse_reg_no = Settings.GetModbusPulseRegNo ();
    if (pulse_reg_no >= 0)
    {
        MODBUS_res_read = modbus_read_registers (MODBUS_ctx, pulse_reg_no, 2, MODBUS_tab_reg);
        ModbusServerPulse = MODBUS_tab_reg [0];
    }
    else
    {
//      ModbusServerPulse = 0;
    }
}


#ifdef __DELETED_FRAGMENT__

/*------------------------------------------------------------------*/
/*                   считывание данных по Modbus                    */
/*------------------------------------------------------------------*/
void MODBUS_Block01_ReadPulse ()
{
/*
    int begin_reg_idx, size;
    
    // чтение пульса контроллера по Modbus и времени цикла
    begin_reg_idx = PLC_ModbusConfig.CommonData_BeginRegIdx;
    size          = PLC_ModbusConfig.CommonData_Size       ;
    MODBUS_res_read = modbus_read_registers (MODBUS_ctx, (begin_reg_idx+0), size, MODBUS_tab_reg);
    if (MODBUS_res_read != -1)
    {
        PULSE     = MODBUS_tab_reg [0];
        CycleTime = MODBUS_tab_reg [1];
    }
    else
    {
        char s[500];
//      strcpy (s, modbus_strerror (MODBUS_ctx));
//      s[499] = '\0x00';
        s[499] = '\0';
    }
*/
}
void MODBUS_Block02_ReadData ()
{
    int begin_reg_idx, size;
/*
    // чтение сигналов для модулей №4, 5 и 6 - DO16
    begin_reg_idx = PLC_ModbusConfig.DOData_BeginRegIdx;
    size          = PLC_ModbusConfig.DOData_Size       ;
    MODBUS_res_read = modbus_read_registers (MODBUS_ctx, (begin_reg_idx+0), size, MODBUS_tab_reg);
    if (MODBUS_res_read != -1)
    {
        int first_mod_idx = 4;
        int mod_idx_offset = 0;
        int chan_idx = 0;
        IMIT_TIOSignalAddr addr;
        int data = 0x0000;
        int mask = 0x0001;
         
        for (mod_idx_offset=0; mod_idx_offset<=2; mod_idx_offset++)
        {
            data = MODBUS_tab_reg [mod_idx_offset];
            addr.ModIdx = first_mod_idx + mod_idx_offset;
            mask = 0x0001;
            for (chan_idx=1; chan_idx<=16; chan_idx++)
            {
                addr.ChanIdx = chan_idx;
                IMIT_IOSignalSetValDiscret (addr, ((data & mask) ? 1 : 0));
                mask = mask << 1;
            }
        }
    }
    else
    {
        char s[500];
        strcpy (s, modbus_strerror ((int)MODBUS_ctx));
        s[499] = '\0x00';
    }
*/
    MODBUS_res_read = modbus_read_registers (MODBUS_ctx, 1, 2, MODBUS_tab_reg);
}
/*------------------------------------------------------------------*/
/*              MODBUS: connect to the modbus-server                */
/*------------------------------------------------------------------*/
int MODBUS_connect_to_server ()
{
    int result = 0;

    if (MODBUS_ctx != NULL) modbus_free (MODBUS_ctx);
    
    MODBUS_ctx = modbus_new_tcp ("192.168.56.101", 502);
//  MODBUS_ctx = modbus_new_tcp (IPAddrAsString (PLC_ModbusConfig.IPAddrPart), PLC_ModbusConfig.Port);
//  MODBUS_ctx = modbus_new_tcp (Settings., 502);
        
    if (MODBUS_ctx == NULL) {result = 0; return result;}
    
    MODBUS_res_connect = modbus_connect (MODBUS_ctx);
    if (MODBUS_res_connect == -1)
    {
        char s[500];
        strcpy (s, modbus_strerror ((int)MODBUS_ctx));
        s[499] = '\0x00';
        result = 0;
        return result;
    }
    result = 1;
    return result;
}
#endif /*__DELETED_FRAGMENT__*/


/*------------------------------------------------------------------*/









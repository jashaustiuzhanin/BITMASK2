/***************************************************************************
**                                                                        **
**  Filename: bmqspinbox.cpp                                              **
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

#ifdef __DELETED_FRAGMENT__
#endif /*__DELETED_FRAGMENT__*/

#include <math.h>
#include "bmqspinbox.h"

/*------------------------------------------------------------------*/
/* Конструктор                                                      */
/*------------------------------------------------------------------*/
BMQSpinBox :: BMQSpinBox (QWidget *parent) : QAbstractSpinBox (parent)
{
    SetMode (BMQSpinBox::modeDECIMAL);

    SetBitsCount_32 ();

    QLineEdit *p_edit = this->lineEdit();
//  QObject::connect (p_edit, SIGNAL(textChanged(const QString &)), this, SLOT (SlotOnChanged()));
    QObject::connect (p_edit, SIGNAL(textChanged(const QString &)), this, SLOT (SlotTextChanged(const QString &)));

    IsNewValueSource = true ;

    setValue ((TValue) 0);

    setCorrectionMode (QAbstractSpinBox::CorrectToPreviousValue);
}

/*------------------------------------------------------------------*/
/* Задание нового значения (снаружи)                                */
/*------------------------------------------------------------------*/
bool BMQSpinBox :: setValue  (TValue argValue)
{
    TValue val = argValue;

    Q_UNUSED (val)

    if (!IsInRange (argValue)) return false;

    // установка нового текста, которая вызовет срабатывание слота SlotTextChanged
    IsNewValueSource = false;
    lineEdit()->setText (textFromValue (argValue));
    IsNewValueSource = true ;
    return true;
}

/*------------------------------------------------------------------*/
/* Обработка изменения текста SpinBox-а с вычислением нового зна-   */
/* чения                                                            */
/*------------------------------------------------------------------*/
void BMQSpinBox :: SlotTextChanged (const QString & argString)
{
    TValue val;

    val = valueFromText (argString);
#ifdef isnan
    if (     isnan (val)) return;
#else
    if (std::isnan (val)) return;
#endif

    if (val != Value)
    {
        Value = val;
//      emit valueChanged ();
//      emit SignalIsNewValueSource (Value);
        if (IsNewValueSource) emit SignalIsNewValueSource ();
    }
}

/*------------------------------------------------------------------*/
/* Обработка изменения текста SpinBox-а с вычислением нового зна-   */
/* чения                                                            */
/*------------------------------------------------------------------*/
void BMQSpinBox :: stepBy   (int Steps)
{
    TValue new_val;
    TValue one_step = (TValue) 1;
     
     new_val = Value + one_step * Steps;

    SlotTextChanged (textFromValue (new_val));
}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QString BMQSpinBox :: textFromValue (TValue value) const
{
    QString result = "";

    if (Mode == modeDECIMAL)
    {
        result = QString::number (value, 10).toUpper();
    }
    else if (Mode == modeHEXADECIMAL)
    {
        result = QString::number (value, 16).toUpper();
    }
    else if (Mode == modeBINARY)
    {
        result = QString::number (value,  2).toUpper();
    }
    else
    {
        result = QString::number (value, 10).toUpper();
    }
    return result;
}
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
BMQSpinBox::TValue  BMQSpinBox :: valueFromText (const QString &text) const
{
    bool ok;
    TValue val;

    if (Mode == modeDECIMAL)
    {
        val = text.toULong (&ok, 10);
    }
    else if (Mode == modeHEXADECIMAL)
    {
        val = text.toULong (&ok, 16);
    }
    else if (Mode == modeBINARY)
    {
        val = text.toULong (&ok, 2);
    }
    else
    {
        val = text.toULong (&ok, 10);
    }

    if (!ok) return (BMQSpinBox::TValue) NAN;

    if (!IsInRange (val)) return (BMQSpinBox::TValue) NAN;
    
    return val;

}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
QValidator::State BMQSpinBox :: validate (QString &input, int &pos) const
{
//  return QValidator::Acceptable;

    QString copy (input);

    if (copy.startsWith ("0x")) copy.remove(0, 2);
    pos -= copy.size() - copy.trimmed().size();
    copy = copy.trimmed();

    if (copy.isEmpty()) return QValidator::Intermediate;

//  input = QString("0x") + copy.toUpper();
    input = copy.toUpper();

    TValue val;

    val = valueFromText (copy);
#ifdef isnan
    if (     isnan (val)) return QValidator::Invalid   ;
    else                  return QValidator::Acceptable;
#else
    if (std::isnan (val)) return QValidator::Invalid   ;
    else                  return QValidator::Acceptable;
#endif
}

/*------------------------------------------------------------------*/

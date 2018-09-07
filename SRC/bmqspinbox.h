/***************************************************************************
**                                                                        **
**  Filename: bmqspinbox.h                                                **
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

#ifndef BMQSPINBOX_H
#define BMQSPINBOX_H

#include <QtCore>
#include <QObject>
#ifdef HAVE_QT5
#include <QtWidgets>
#endif
#include <QLineEdit>
#include <QSpinBox>



#ifdef __DELETED_FRAGMENT__
#endif /*__DELETED_FRAGMENT__*/



class BMQSpinBox : public QAbstractSpinBox
{

Q_OBJECT

public:

    explicit BMQSpinBox (QWidget *parent = 0);
   ~BMQSpinBox () {}

    /// @enum DigitType: тип системы исчисления (10-чная, 16-ричная, двоичная)
    typedef enum DigitType
    {
        modeDECIMAL     = 0,    ///< SpinBox использует десятичную систему представления чисел
        modeHEXADECIMAL = 1,    ///< SpinBox использует шестнадцатиричную систему представления чисел
        modeBINARY      = 2,    ///< SpinBox использует двоичную систему представления чисел
        
        modeStub = 0
    }
    TDigitType;

    typedef unsigned long int TValue;


    void SetMode (TDigitType argMode)
    {
        Mode = argMode;
    }


//  TValue value     () const       {TValue val = valueFromText (text()); return val;}
//  void   setValue  (TValue value) {lineEdit()->setText (textFromValue (value));}
    TValue value     () const       {return Value;}
    bool   setValue  (TValue argValue);
/*
    TValue hexValue() const
    {
        return value ();
    }

    void setHexValue (TValue value)
    {
        setValue (value);
    }
*/
    void setRange (TValue Min, TValue Max) {RangeMin = Min; RangeMax = Max;}

    void SetBitsCount_32 ()
    {
        BitsCount = 32;
        SetBitRange ();
    }

    void SetBitsCount_16 ()
    {
        BitsCount = 16;
        SetBitRange ();
    }

    void SetBitsCount_08 ()
    {
        BitsCount = 8;
        SetBitRange ();
    }

    void SetBitsCount_04 ()
    {
        BitsCount = 4;
        SetBitRange ();
    }

protected:
/*
    QString textFromValue (TValue value) const
    {
        return QString::number(value, 16).toUpper();
    }

    TValue valueFromText (const QString &text) const
    {
        return (text.toULong (0, 16));
    }
*/
    QString textFromValue (TValue value) const;
    TValue  valueFromText (const QString &text) const;

    QValidator::State validate (QString &input, int &pos) const;

private:

//  bool m_only16Bits;

    TDigitType Mode ;

    TValue     Value   ;
    TValue     RangeMin;
    TValue     RangeMax;

    int BitsCount;

    void SetBitRange ()
    {
        if      (BitsCount == 32) setRange (0, 0xFFFFFFFF);
        else if (BitsCount == 16) setRange (0, 0x0000FFFF);
        else if (BitsCount ==  8) setRange (0, 0x000000FF);
        else if (BitsCount ==  4) setRange (0, 0x0000000F);
        else                      setRange (INT_MIN, INT_MAX);
    }

    bool IsInRange (TValue argValue) const {return ((argValue >= RangeMin) && (argValue <= RangeMax));}

    bool IsNewValueSource;

    StepEnabled stepEnabled () const {return (StepUpEnabled | StepDownEnabled); }

private slots:

//  void SlotOnChanged () {emit valueChanged ();}
    void SlotTextChanged (const QString &);

    void stepBy   (int steps);

signals:

//  void valueChanged ();
//  void SignalIsNewValueSource (TValue);
    void SignalIsNewValueSource ();

};



#ifdef __DELETED_FRAGMENT__
class THexSpinBox : public QSpinBox
{

Q_OBJECT

public:

//  explicit THexSpinBox (QWidget *parent = 0) : QSpinBox(parent)
    THexSpinBox (QWidget *parent = 0) : QSpinBox(parent)
    {
        setPrefix ("0x");
//      setDisplayIntegerBase (16);
        SetBitsCount_32 ();
    }

    unsigned int hexValue() const
    {
        return u (value());
    }

    void setHexValue (unsigned int value)
    {
        setValue (i(value));
    }

    void SetBitsCount_32 ()
    {
        BitsCount = 32;
        SetBitRange ();
    }

    void SetBitsCount_16 ()
    {
        BitsCount = 16;
        SetBitRange ();
    }

    void SetBitsCount_08 ()
    {
        BitsCount = 8;
        SetBitRange ();
    }

    void SetBitsCount_04 ()
    {
        BitsCount = 4;
        SetBitRange ();
    }

protected:

    QString textFromValue (int value) const
    {
        return QString::number(u(value), 16).toUpper();
    }

    int valueFromText (const QString &text) const
    {
        return i(text.toUInt(0, 16));
    }

    QValidator::State validate (QString &input, int &pos) const
    {
//      return QValidator::Acceptable;

        QString copy (input);
        if (copy.startsWith ("0x"))
            copy.remove(0, 2);
        pos -= copy.size() - copy.trimmed().size();
        copy = copy.trimmed();
        if (copy.isEmpty())
            return QValidator::Intermediate;
        input = QString("0x") + copy.toUpper();
        bool okay;
        unsigned int val = copy.toUInt(&okay, 16);
        if (!okay || 
            ((BitsCount == 32) && (val > 0xFFFFFFFF)) ||
            ((BitsCount == 16) && (val > 0x0000FFFF)) ||
            ((BitsCount ==  8) && (val > 0x000000FF)) ||
            ((BitsCount ==  4) && (val > 0x0000000F)) ||
            false
           )
            return QValidator::Invalid;
        return QValidator::Acceptable;
    }

private:

//  bool m_only16Bits;

    int BitsCount;
    void SetBitRange ()
    {
        if      (BitsCount == 32)
            setRange(0, 0xFFFFFFFF);
        else if (BitsCount == 16)
            setRange(0, 0xFFFF);
        else if (BitsCount ==  8)
            setRange(0, 0xFF);
        else if (BitsCount ==  4)
            setRange(0, 0xF);
        else
            setRange(INT_MIN, INT_MAX);
    }

    inline unsigned int u (int i) const
    {
        return *reinterpret_cast <unsigned int *> (&i);
    }

    inline int i (unsigned int u) const
    {
        return *reinterpret_cast <int *> (&u);
    }

};
#endif /*__DELETED_FRAGMENT__*/



#endif // BMQSPINBOX_H

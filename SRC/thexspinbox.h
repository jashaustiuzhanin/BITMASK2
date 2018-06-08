#ifndef THEXSPINBOX_H
#define THEXSPINBOX_H

#include <QLineEdit>
#include <QSpinBox>



#ifdef __DELETED_FRAGMENT__
#endif /*__DELETED_FRAGMENT__*/


#ifdef __DELETED_FRAGMENT__
class THexSpinBox : public QSpinBox
{
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

class THexSpinBox : public QAbstractSpinBox
{
public:
    THexSpinBox (QWidget *parent) : QAbstractSpinBox (parent)
    {
        SetBitsCount_32 ();

        QLineEdit *p_edit = this->lineEdit();
        QObject::connect (p_edit, SIGNAL(textChanged(const QString &)), this, SLOT (SlotOnChanged()));
    }

    unsigned long int hexValue() const
    {
//      return u ( value () );
        return value ();
    }

    void setHexValue (unsigned long int value)
    {
//      setValue (i(value));
        setValue (value);
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

    unsigned long int value     () const                  {unsigned long int val = valueFromText (text()); return val;}
    void              setValue  (unsigned long int value) {lineEdit()->setText (textFromValue (value));}

    void setRange (long int Min, long int Max) {RangeMin = Min; RangeMax = Max;}

signals:

    void valueChanged ();

protected:

    QString textFromValue (unsigned long int value) const
    {
//      return QString::number(u(value), 16).toUpper();
        return QString::number(value, 16).toUpper();
    }

    unsigned long int valueFromText (const QString &text) const
    {
//      return i(text.toUInt(0, 16));
        return (text.toULong (0, 16));
    }

    QValidator::State validate (QString &input, int &pos) const
    {
//      return QValidator::Acceptable;

        QString copy (input);
        if (copy.startsWith ("0x")) copy.remove(0, 2);
        pos -= copy.size() - copy.trimmed().size();
        copy = copy.trimmed();
        if (copy.isEmpty()) return QValidator::Intermediate;

//      input = QString("0x") + copy.toUpper();
        input = copy.toUpper();
        bool okay;
        unsigned long int val = copy.toULong (&okay, 16);
        if (!okay || (val < RangeMin) || (val > RangeMax))
        {
            return QValidator::Invalid;
        }
        return QValidator::Acceptable;
    }

private:

//  bool m_only16Bits;

    void SetBitRange ()
    {
        if      (BitsCount == 32) setRange (0, 0xFFFFFFFF);
        else if (BitsCount == 16) setRange (0, 0x0000FFFF);
        else if (BitsCount ==  8) setRange (0, 0x000000FF);
        else if (BitsCount ==  4) setRange (0, 0x0000000F);
        else                      setRange (INT_MIN, INT_MAX);
    }

/*
    inline unsigned long int u (long int i) const
    {
        return *reinterpret_cast <unsigned long int *> (&i);
    }

    inline long int i (unsigned long int u) const
    {
        return *reinterpret_cast <long int *> (&u);
    }
*/
    unsigned long int Value;
    unsigned long int RangeMin;
    unsigned long int RangeMax;

    int BitsCount;

  private slots:

    void SlotOnChanged ()
    {
        emit valueChanged ();
    }

};



#endif // THEXSPINBOX_H

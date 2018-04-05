#ifndef THEXSPINBOX_H
#define THEXSPINBOX_H

#include <QSpinBox>

class THexSpinBox : public QSpinBox
{
    Q_OBJECT

public:

    explicit THexSpinBox (QWidget *parent = 0) : QSpinBox(parent)
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

#endif // THEXSPINBOX_H

#ifndef TSPINBOX64_H
#define TSPINBOX64_H

#include <QSpinBox>

// https://stackoverflow.com/questions/26581444/qspinbox-with-unsigned-int-for-hex-input

class TSpinBox64 : public QSpinBox
{
//  Q_OBJECT
public:

    TSpinBox64 (bool only16Bits, QWidget *parent = 0) : QSpinBox(parent), m_only16Bits(only16Bits)
    {
        setPrefix ("0x");
//      setDisplayIntegerBase (16);
        if (only16Bits)
            setRange(0, 0xFFFF);
        else
            setRange(INT_MIN, INT_MAX);
    }

    unsigned int hexValue() const
    {
        return u (value());
    }

    void setHexValue (unsigned int value)
    {
        setValue (i(value));
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
        if (copy.startsWith ("16#"))
            copy.remove(0, 3);
        pos -= copy.size() - copy.trimmed().size();
        copy = copy.trimmed();
        if (copy.isEmpty())
            return QValidator::Intermediate;
        input = QString("0x") + copy.toUpper();
        bool okay;
        unsigned long int val = copy.toLong (&okay, 16);
        if (!okay || (m_only16Bits && val > 0xFFFFFFFF))
            return QValidator::Invalid;
        return QValidator::Acceptable;
    }

private:

    bool m_only16Bits;

    inline unsigned int u (int i) const
    {
        return *reinterpret_cast <unsigned int *> (&i);
    }

    inline int i (unsigned int u) const
    {
        return *reinterpret_cast <int *> (&u);
    }

    inline unsigned long int u (long int l) const
    {
        return *reinterpret_cast <unsigned long int *> (&l);
    }

    inline long int l (unsigned long int u) const
    {
        return *reinterpret_cast <long int *> (&u);
    }
};

#endif // TSPINBOX64_H

/*
class TSpinBox64 : public QSpinBox
{
    Q_OBJECT
public:
    explicit TSpinBox64(QObject *parent = 0);
    
signals:
    
public slots:

private:
    qint64 Value64;    
};

*/

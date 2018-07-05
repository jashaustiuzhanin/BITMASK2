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
    if (std::isnan (val)) return;

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
    if (std::isnan (val)) return QValidator::Invalid   ;
    else                  return QValidator::Acceptable;
}

/*------------------------------------------------------------------*/

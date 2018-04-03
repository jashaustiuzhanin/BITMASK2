#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>

class HexSpinbox : public QSpinBox
{
    virtual QString textFromValue (int val            ) const;
    virtual int     valueFromText (const QString &text) const;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

private:
    Ui::MainWindow *ui;

    int  Value;
    bool ShowInProcessFlag;

private slots:
    void ShowValue ();

    void SlotOnSpnDecimal ();

};


#endif // MAINWINDOW_H

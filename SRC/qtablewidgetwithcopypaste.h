// source from link:
// http://qaru.site/questions/337587/selected-rowsline-in-qtableview-copy-to-qclipboard

// QTableWidget with support for copy and paste added
// Here copy and paste can copy/paste the entire grid of cells
#ifndef QTABLEWIDGETWITHCOPYPASTE_H
#define QTABLEWIDGETWITHCOPYPASTE_H

#include <QTableWidget>
#include <QKeyEvent>
#include <QWidget>

class QTableWidgetWithCopyPaste : public QTableWidget
{
    Q_OBJECT
public:
  QTableWidgetWithCopyPaste(int rows, int columns, QWidget *parent = 0) :
      QTableWidget(rows, columns, parent)
  {}

  QTableWidgetWithCopyPaste(QWidget *parent = 0) :
  QTableWidget(parent)
  {}

private:
  void copy();
  void paste();

public slots:
  void keyPressEvent(QKeyEvent * event);
};

#endif // QTABLEWIDGETWITHCOPYPASTE_H



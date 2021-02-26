// destwindow.hh
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_DESTWINDOW_HH__
#define __QTVIEWER_DESTWINDOW_HH__

#include <QWidget>
#include <QSharedMemory>
#include <QTextEdit>

class DestWindow : public QWidget {
  Q_OBJECT

public:
  explicit DestWindow(QWidget * parent = nullptr);
  ~DestWindow();

private:
  void detach();

private:
  QSharedMemory shared_memory_;
  QTextEdit *text_;
};

#endif // __QTVIEWER_DESTWINDOW_HH
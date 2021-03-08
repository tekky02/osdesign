// timewindow.hh
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_TIMEWINDOW_HH__
#define __QTVIEWER_TIMEWINDOW_HH__

#include <QWidget>
#include <QSharedMemory>
#include <QTextEdit>

class TimeWindow : public QWidget {
  Q_OBJECT

public:
  explicit TimeWindow(QWidget * parent = nullptr);
  ~TimeWindow();

private slots:
  void show_time() noexcept;

private:
  QTextEdit *text_;
};

#endif // __QTVIEWER_TIMEWINDOW_HH
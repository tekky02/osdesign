// mainwindow.hh.
// created by tekky on 2021.2.19.
// Copyright(c) 2021 tekky.

#ifndef __QTVIEWER_MAINWINDOW_HH__
#define __QTVIEWER_MAINWINDOW_HH__

#include <QMainWindow>

class MainWindow : public QMainWindow {
  QOBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:

private:
  // member here...
};

#endif // __QTVIEWER_MAINWINDOW_HH__

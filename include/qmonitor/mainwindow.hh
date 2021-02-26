// mainwindow.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_MAINWINDOW_HH__
#define __QMONITOR_MAINWINDOW_HH__

class MainWindow : public QMainWindow {
  QOBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  // public solts here...

private:
  // private member here...
};

#endif // __QMONITOR_MAINWINDOW_HH__

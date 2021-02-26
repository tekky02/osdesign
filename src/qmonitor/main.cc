// main.cc.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#include <QApplication>

#include "qmonitor/mainwindow.hh"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}

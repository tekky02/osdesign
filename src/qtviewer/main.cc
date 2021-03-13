// main.cc
// created by tekky on 2021.2.19.
// Copyright ©  2021 tekky. All rights reserved.

#include <QApplication>

#include "qtviewer/mainwindow.hh"

int main(int argc, char *argv[]) {
  QApplication a{argc, argv};

  MainWindow w;
  w.show();

  return a.exec();
}

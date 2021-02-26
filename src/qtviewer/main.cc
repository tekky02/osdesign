// main.cc
// created by tekky on 2021.2.19.
// Copyright(c) 2021 tekky.

#include <QApplication>

#include "qtviewer/viewer.h"

int main(int argc, char *argv[]) {
  QApplication a{argc, argv};
  MainWindow w;
  w.show();

  return a.exec();
}

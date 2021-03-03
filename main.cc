// main.cc
// created by tekky on 2021.3.3.
// Copyright ©  2021 tekky. All rights reserved.

#include <QApplication>
#include <iostream>

#include "mainwindow.hh"

int main(int argc, char *argv[]) {
  QApplication a{argc, argv};

  if (argc != 2) {
    std::cerr << "Too few arguments.\nUsage: ./qviewer <titleName>.\n"
              << "Note: first character should not be a '@'." << std::endl;
    std::abort();
  }

  MainWindow w{argv[1]};
  w.show();

  return a.exec();
}

// sourcewindow.cc.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/sourcewindow.hh"

#include <QApplication>
#include <QGridLayout>

SourceWindow::SourceWindow(QWidget *parent) : QWidget(parent) {
  this->setWindowTitle("source");

  // wait until there is something to read.
  text_ = new QTextEdit(this);
  auto layout = new QGridLayout(this);
  layout->addWidget(text_, 0, 0);
}

SourceWindow::~SourceWindow() {}

// executable
int main(int argc, char **argv) {
  QApplication app{argc, argv};

  SourceWindow w;
  w.show();

  return app.exec();
}
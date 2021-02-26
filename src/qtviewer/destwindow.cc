// destwindow.cc.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/destwindow.hh"

#include <QApplication>
#include <QGridLayout>

DestWindow::DestWindow(QWidget *parent)
    : QWidget(parent), shared_memory_("QtViewer") {
  this->setWindowTitle("destination");

  text_ = new QTextEdit(this);
  auto layout = new QGridLayout(this);
  layout->addWidget(text_, 0, 0);
}

DestWindow::~DestWindow() {}

// executable
int main(int argc, char **argv) {
  QApplication app{argc, argv};

  DestWindow w;
  w.show();

  return app.exec();
}
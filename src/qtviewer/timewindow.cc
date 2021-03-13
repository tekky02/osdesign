// timewindow.cc.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/timewindow.hh"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTime>

TimeWindow::TimeWindow(QWidget *parent) : QWidget{parent} {
  this->setWindowTitle("Current time");

  show_time();
}

TimeWindow::~TimeWindow() {}

void TimeWindow::show_time() noexcept {
  auto layout = new QGridLayout(this);

  auto show_time_btn = new QPushButton("&Show time", this);
  layout->addWidget(show_time_btn, 0, 0);

  auto time_label = new QLabel(this);
  layout->addWidget(time_label);
  connect(show_time_btn, &QPushButton::clicked, this, [time_label]() {
    time_label->setText("Current time is: " + QTime::currentTime().toString());
  });
}

// executable
int main(int argc, char **argv) {
  QApplication app{argc, argv};

  TimeWindow w;
  w.show();

  return app.exec();
}
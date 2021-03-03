// mainwindow.cc.
// created by tekky on 2021.3.3.
// Copyright © 2arguments21 tekky. All rights reserved.

#include "mainwindow.hh"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QProcess>
#include <QPushButton>
#include <QTime>

MainWindow::MainWindow(const char *name, QWidget *parent) : QWidget(parent) {
  this->setWindowTitle(name);

  if (name[0] != '@') {
    add_push_button();
  } else if (name[1] == '1') { // child1 show time.
    show_time();
  } else if (name[1] == '2') { // child2 show image.
    show_image();
  }
}

MainWindow::~MainWindow() {}

void MainWindow::on_run_button_clicked() noexcept {
  QStringList arguments;

  arguments << "@1_child";
  child1_ = new QProcess(this);
  child1_->start("./qviewer", arguments);

  arguments.clear();
  arguments << "@2_child";
  child2_ = new QProcess(this);
  child2_->start("./qviewer", arguments);
}

void MainWindow::on_quit_button_clicked() noexcept {
  // terminate all child before quit
  child1_->terminate();
  child2_->terminate();

  this->close();
}

void MainWindow::add_push_button() noexcept {
  auto layout = new QGridLayout(this);

  // add run button widget
  run_button_ = new QPushButton("&Run", this);
  layout->addWidget(run_button_, 0, 0);
  connect(run_button_, &QPushButton::clicked, this,
          &MainWindow::on_run_button_clicked);

  // add quit button widget
  quit_button_ = new QPushButton("&Quit", this);
  layout->addWidget(quit_button_, 1, 0);
  connect(quit_button_, &QPushButton::clicked, this,
          &MainWindow::on_quit_button_clicked);
}

void MainWindow::show_time() noexcept {
  auto layout = new QGridLayout(this);

  auto show_time_btn = new QPushButton("&Show time", this);
  layout->addWidget(show_time_btn, 0, 0);

  auto time_label = new QLabel(this);
  layout->addWidget(time_label);
  connect(show_time_btn, &QPushButton::clicked, this, [time_label]() {
    time_label->setText(QTime::currentTime().toString());
  });
}

void MainWindow::show_image() noexcept {
  auto layout = new QGridLayout(this);
  auto load_img = new QPushButton("&Load image", this);
  layout->addWidget(load_img, 0, 0);
  auto image_label = new QLabel(this);
  layout->addWidget(image_label);

  connect(load_img, &QPushButton::clicked, this, [image_label, this]() {
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
                                                 tr("Image Files (*.png)"));
    QPixmap image{fileName};
    image_label->setPixmap(image);
  });
}
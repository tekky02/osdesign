// mainwindow.cc.
// created by tekky on 2021.2.19.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/mainwindow.hh"

#include <iostream>
#include <string>

#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}, memory_attached_{false}, shared_memory_{"QtViewer"} {
  this->setWindowTitle("qtviewer");

  QStringList arguments;

  auto layout = new QGridLayout(this);

  send_button_ = new QPushButton("&Send", this);
  layout->addWidget(send_button_, 0, 0);
  connect(send_button_, &QPushButton::clicked, this,
          &MainWindow::on_send_button_clicked);

  quit_button_ = new QPushButton("&Quit", this);
  layout->addWidget(quit_button_, 0, 1);
  connect(quit_button_, &QPushButton::clicked, this,
          &MainWindow::on_quit_button_clicked);

  text_ = new QTextEdit(this);
  // text_->setReadOnly(true);
  layout->addWidget(text_, 1, 0, 1, 2);

  image_viewer_ = new QProcess(this);
  image_viewer_->start("./imagewindow", arguments);

  buffer_ = new QProcess(this);
  buffer_->start("./bufferwindow", arguments);

  time_viewer_ = new QProcess(this);
  time_viewer_->start("./timewindow", arguments);
}

MainWindow::~MainWindow() { detach_shared_memory(); }

void MainWindow::on_send_button_clicked() noexcept {
  auto message = text_->toPlainText();
  auto data = message.toLocal8Bit();
  int size = data.size();

  // try to create shared memory while run button clicked the first time.
  create_shared_memory();

  shared_memory_.lock();
  char *to = (char *)shared_memory_.data();
  const char *from = data.data();
  memcpy(to, from, qMin(shared_memory_.size(), size));
  shared_memory_.unlock();
}

void MainWindow::on_quit_button_clicked() noexcept {
  // terminate all child process before quit.
  buffer_->terminate();
  time_viewer_->terminate();
  image_viewer_->terminate();

  this->close();
}

void MainWindow::create_shared_memory() noexcept {
  if (memory_attached_) {
    return;
  }

  // create shared memory
  if (!shared_memory_.create(shared_memory_size_)) {
    QMessageBox::critical(this, tr("error"),
                          tr("Unable to create shared memory"));
    on_quit_button_clicked();
  }
  memory_attached_ = true;
}

void MainWindow::detach_shared_memory() noexcept {
  if (!memory_attached_) {
    return;
  }

  // detach shared memory
  if (!shared_memory_.detach()) {
    QMessageBox::critical(this, tr("error"),
                          tr("Error while try to detach shared memory"));
    on_quit_button_clicked();
  }
  memory_attached_ = false;
}
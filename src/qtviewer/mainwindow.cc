// mainwindow.cc.
// created by tekky on 2arguments21.2.19.
// Copyright © 2arguments21 tekky. All rights reserved.

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
    : QWidget(parent), shared_memory_("QtViewer") {
  this->setWindowTitle("qtviewer");

  QStringList arguments;

  auto layout = new QGridLayout(this);

  run_button_ = new QPushButton("&Run", this);
  layout->addWidget(run_button_, 0, 0);
  connect(run_button_, &QPushButton::clicked, this,
          &MainWindow::on_run_button_clicked);

  quit_button_ = new QPushButton("&Quit", this);
  layout->addWidget(quit_button_, 1, 0);
  connect(quit_button_, &QPushButton::clicked, this,
          &MainWindow::on_quit_button_clicked);

  text_ = new QTextEdit(this);
  layout->addWidget(text_, 0, 1);

  // source_ = new QProcess(this);
  // source_->start("./sourcewindow", arguments);

  buffer_ = new QProcess(this);
  buffer_->start("./bufferwindow", arguments);

  destination_ = new QProcess(this);
  destination_->start("./destwindow", arguments);
}

MainWindow::~MainWindow() {}

void MainWindow::on_run_button_clicked() noexcept {
  auto fileName = QFileDialog::getOpenFileName(this, tr("Open Text"), "/home",
                                               tr("Text Files (*.txt)"));
  // hide current window.
  // this->setVisible(false); // FIXME: fix exit bug
  QFile file{fileName};
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(this, tr("error"),
                          tr("Unable to open file %1.").arg(fileName));
    close();
    return;
  }

  QBuffer buffer;
  buffer.open(QBuffer::ReadWrite);

  QDataStream out{&buffer};

  // read content of the opened file, write to sourcewindow
  QTextStream in{&file};
  QString str;
  while (!in.atEnd()) {
    str = in.readLine();
    std::cout << "[cout]: " << str.toUtf8().constData() << std::endl;
    out << str << "\n";
  }

  int size = buffer.size();
  if (!shared_memory_.create(size)) {
    QMessageBox::critical(this, tr("mainwindow"),
                          tr("Unable to create shared memory"));
    on_quit_button_clicked();
  }

  shared_memory_.lock();
  char *to = (char *)shared_memory_.data();
  const char *from = buffer.data().data();
  memcpy(to, from, qMin(shared_memory_.size(), size));
  shared_memory_.unlock();

  buffer.close();
}

void MainWindow::on_quit_button_clicked() noexcept {
  // source_->terminate();
  buffer_->terminate();
  destination_->terminate();

  this->close();
}

void MainWindow::detach() {
  if (!shared_memory_.detach()) {
    std::cerr << "error while detach shared memory\n";
  }
}
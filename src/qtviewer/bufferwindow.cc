// bufferwindow.cc.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/bufferwindow.hh"

#include <QApplication>
#include <QBuffer>
#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>

BufferWindow::BufferWindow(QWidget *parent)
    : QWidget(parent), shared_memory_("QtViewer") {
  this->setWindowTitle("buffer");

  text_ = new QTextEdit(this);
  text_->setReadOnly(true);
  auto layout = new QGridLayout(this);
  layout->addWidget(text_, 0, 0);

  auto show = new QPushButton("Show", this);
  layout->addWidget(show, 1, 0);
  connect(show, &QPushButton::clicked, this,
          &BufferWindow::copy_from_shared_memory);
}

BufferWindow::~BufferWindow() {}

void BufferWindow::copy_from_shared_memory() {
  if (!shared_memory_.attach()) {
    QMessageBox::critical(this, tr("error"),
                          tr("Unable to attach shared memory"));
    close();
    return;
  }

  shared_memory_.lock();
  const char *message = (char *)shared_memory_.constData();
  shared_memory_.unlock();
  text_->setText(message);
  shared_memory_.detach();
}

// executable
int main(int argc, char **argv) {
  QApplication app{argc, argv};

  BufferWindow w;
  w.show();

  return app.exec();
}
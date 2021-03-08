// imagewindow.cc.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#include "qtviewer/imagewindow.hh"

#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent) {
  this->setWindowTitle("Image viewer");

  // wait until there is something to read.
  show_image();
}

ImageWindow::~ImageWindow() {}

void ImageWindow::show_image() noexcept {
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

// executable
int main(int argc, char **argv) {
  QApplication app{argc, argv};

  ImageWindow w;
  w.show();

  return app.exec();
}
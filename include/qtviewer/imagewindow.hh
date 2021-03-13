// imagewindow.hh
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_IMAGEWINDOW_HH__
#define __QTVIEWER_IMAGEWINDOW_HH__

#include <QTextEdit>
#include <QWidget>

class ImageWindow : public QWidget {
  Q_OBJECT

public:
  explicit ImageWindow(QWidget *parent = nullptr);
  ~ImageWindow();

private slots:
  void show_image() noexcept;
};

#endif // _QTVIEWER_IMAGEWINDOW_HH__
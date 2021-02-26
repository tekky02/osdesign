// sourcewindow.hh
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_SOURCEWINDOW_HH__
#define __QTVIEWER_SOURCEWINDOW_HH__

#include <QWidget>
#include <QTextEdit>

class SourceWindow : public QWidget {
  Q_OBJECT

public:
  explicit SourceWindow(QWidget* parent = nullptr);
  ~SourceWindow();

private:
  friend class MainWindow;

private:
  QString filename_; // name of source file.
  QTextEdit *text_;
};

#endif // _QTVIEWER_SOURCEWINDOW_HH__
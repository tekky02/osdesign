// bufferwindow.hh
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_BUFFERWINDOW_HH__
#define __QTVIEWER_BUFFERWINDOW_HH__


#include <QSharedMemory>
#include <QWidget>
#include <QTextEdit>

class BufferWindow : public QWidget {
  Q_OBJECT
  
public:
  explicit BufferWindow(QWidget *parent = nullptr);
  ~BufferWindow();

private:
  void detach();
  void copy_from_shared_memory();

public slots:

private:
  QSharedMemory shared_memory_;
  QTextEdit *text_;
};

#endif // __QTVIEWER_BUFFERWINDOW_HH__
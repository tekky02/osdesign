// mainwindow.hh.
// created by tekky on 2021.2.19.
// Copyright(c) 2021 tekky. All rights reserved.

#ifndef __QTVIEWER_MAINWINDOW_HH__
#define __QTVIEWER_MAINWINDOW_HH__

#include <QMainWindow>
#include <QWidget>
#include <QProcess>
#include <QPushButton>
#include <QSharedMemory>
#include <QTextEdit>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void detach_shared_memory() noexcept;
  void create_shared_memory() noexcept;

public slots:
  void on_send_button_clicked() noexcept;
  void on_quit_button_clicked() noexcept;

private:
  static constexpr size_t shared_memory_size_ = 1024;

private:
  bool memory_attached_;
  QSharedMemory shared_memory_;
  QTextEdit *text_;
  QProcess *buffer_;
  QProcess *image_viewer_;
  QProcess *time_viewer_;
  QPushButton *send_button_;
  QPushButton *quit_button_;
};

#endif // __QTVIEWER_MAINWINDOW_HH__

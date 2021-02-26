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
  void detach();

public slots:
  void on_run_button_clicked() noexcept;
  void on_quit_button_clicked() noexcept;

private:
  // QProcess *source_;
  QSharedMemory shared_memory_;
  QTextEdit *text_;
  QProcess *buffer_;
  QProcess *destination_;
  QPushButton *run_button_;
  QPushButton *quit_button_;
};

#endif // __QTVIEWER_MAINWINDOW_HH__

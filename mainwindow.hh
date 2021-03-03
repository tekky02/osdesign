// mainwindow.hh.
// created by tekky on 2021.3.3.
// Copyright(c) 2021 tekky. All rights reserved.

#ifndef __QVIEWER_MAINWINDOW_HH__
#define __QVIEWER_MAINWINDOW_HH__

#include <QProcess>
#include <QPushButton>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(const char *name, QWidget *parent = nullptr);
  ~MainWindow();
  void add_push_button() noexcept;

private:
  void show_time() noexcept;
  void show_image() noexcept;

private slots:
  void on_run_button_clicked() noexcept;
  void on_quit_button_clicked() noexcept;

private:
  QProcess *child1_;
  QProcess *child2_;
  QPushButton *run_button_;
  QPushButton *quit_button_;
};

#endif // __QTVIEWER_MAINWINDOW_HH__

// mainwindow.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_MAINWINDOW_HH__
#define __QMONITOR_MAINWINDOW_HH__

#include <QTabWidget>
#include <QWidget>

#include "qmonitor/cpu.hh"
#include "qmonitor/memory.hh"
#include "qmonitor/process.hh"
#include "qmonitor/system.hh"

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_reboot_button_clicked();
  void on_shutdown_button_clicked();

private:
  QTabWidget *tab_viewer_;
  SystemInfo *system_info_;
  CpuStatus *cpu_status_;
  MemoryStatus *memory_status_;
  ProcessStatus *process_status_;
};

#endif // __QMONITOR_MAINWINDOW_HH__

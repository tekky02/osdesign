// memory.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_MEMORY_HH__
#define __QMONITOR_MEMORY_HH__

#include <memory>

#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QPieSeries>

#include "qmonitor/basic.hh"

class MemoryStatus : public QWidget {
  Q_OBJECT

public:
  explicit MemoryStatus(QWidget *parent = nullptr);
  ~MemoryStatus();

public slots:
  void on_data_updated();

private slots:
  void memory_status_update();
  void display_memory_status();

private:
  std::unique_ptr<MemoryInfo> memory_info_;
  std::unique_ptr<QtCharts::QPieSeries> p_series_;
};

#endif // __QMONITOR_MEMORY_HH__

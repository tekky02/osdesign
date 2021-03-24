// cpu.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_CPU_HH__
#define __QMONITOR_CPU_HH__

#include <memory>
#include <vector>

#include <QStringList>
#include <QWidget>
#include <QtCharts/QBarSet>

#include "qmonitor/basic.hh"

class CpuStatus : public QWidget {
  Q_OBJECT

public:
  explicit CpuStatus(QWidget *parent = nullptr, std::size_t size = 1);
  ~CpuStatus();

public slots:
  double on_cpu_status_update();

private:
  double calculate_cpu_utilization(const QStringList &list, std::size_t index);

private:
  bool flag = false;
  std::vector<QtCharts::QBarSet *> individual_cpu_status_;
  std::vector<CpuStat> cpu_info_;
};

#endif // __QMONITOR_CPU_HH__

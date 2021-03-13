// cpu.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_CPU_HH__
#define __QMONITOR_CPU_HH__

#include <QWidget>
#include <memory>

#include "qmonitor/basic.hh"

class CpuStatus : public QWidget {
  Q_OBJECT

public:
  explicit CpuStatus(QWidget *parent = nullptr);
  ~CpuStatus();

public slots:
  double on_cpu_status_update();

private:
  bool flag = false;
  std::unique_ptr<CpuStat> cpu_info_;
};

#endif // __QMONITOR_CPU_HH__

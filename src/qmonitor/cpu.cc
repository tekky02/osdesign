// cpu.cc.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/cpu.hh"

#include <QTimer>
#include <fstream>
#include <iostream>
#include <string>

CpuStatus::CpuStatus(QWidget *parent)
    : QWidget{parent}, cpu_info_{new CpuStat} {}

CpuStatus::~CpuStatus() {}

double CpuStatus::on_cpu_status_update() {
  std::ifstream fin;
  fin.open("/proc/stat");

  std::string line;
  QStringList list;
  std::getline(fin, line);
  for (int i = 0; i < line.size(); i++) {
    if (std::isdigit(line[i])) {
      list = QString(line.substr(i, line.size() - i).c_str()).split(" ");
      break;
    }
  }
  fin.close();

  bool ok;
  CpuStat current{};
  for (int i = 0; i < current.time.size(); i++) {
    current.time[i] = list[i].toLong(&ok);
  }

  if (!flag) {
    *cpu_info_ = current;
    flag = true;
  }

  uint64_t diff = 0;
  for (int i = 0; i < 7; i++) {
    diff += current.time[i] - cpu_info_->time[i];
  }

  uint64_t idel_diff = current.time[3] - cpu_info_->time[3];

  *cpu_info_ = current;

  if (diff == 0) {
    return 0;
  }

  double usage = 1 - 1.0 * idel_diff / diff;

  //   std::cout << "diff: " << diff << "\tidel_diff: " << idel_diff
  //             << "\tLoad: " << usage * 100 << "%\n";
  return usage;
}
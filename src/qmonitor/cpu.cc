// cpu.cc.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/cpu.hh"

#include <fstream>
#include <iostream>
#include <string>

#include <QStringList>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;

CpuStatus::CpuStatus(QWidget *parent, std::size_t size)
    : QWidget{parent}, cpu_info_{size + 1} {
  auto layout = new QVBoxLayout(this);

  auto chart = new QChart();
  auto series = new QBarSeries();
  individual_cpu_status_.resize(size);
  std::for_each(individual_cpu_status_.begin(), individual_cpu_status_.end(),
                [id = 0, series, this](auto &item) mutable {
                  auto label = "CPU" + QString::number(id++);
                  item = new QtCharts::QBarSet(label, this);
                  item->append(0);
                  series->append(item);
                });

  chart->addSeries(series);
  chart->setTitle("CPU utilization");
  chart->setAnimationOptions(QChart::SeriesAnimations);
  auto chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QStringList categories;
  categories << "Individual";
  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(categories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(0, 100);
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);

  layout->addWidget(chartView);
}

CpuStatus::~CpuStatus() {}

double CpuStatus::calculate_cpu_utilization(const QStringList &list,
                                            std::size_t index) {
  if (index >= cpu_info_.size()) {
    throw std::runtime_error("index out of array");
  }
  bool ok;
  CpuStat current{};
  for (int i = 0; i < current.time.size(); i++) {
    current.time[i] = list[i].toLong(&ok);
  }

  if (!flag) {
    cpu_info_[index] = current;
    flag = true;
  }

  uint64_t diff = 0;
  for (int i = 0; i < 7; i++) {
    diff += current.time[i] - cpu_info_[index].time[i];
  }

  uint64_t idel_diff = current.time[3] - cpu_info_[index].time[3];

  cpu_info_[index] = current;

  if (diff == 0) {
    return 0;
  }

  double usage = 1 - 1.0 * idel_diff / diff;

  return usage;
}

double CpuStatus::on_cpu_status_update() {
  std::ifstream fin;
  fin.open("/proc/stat");

  std::string line;
  QStringList list;
  double usage = 0;
  for (int id = 0; id < cpu_info_.size(); id++) {
    std::getline(fin, line);
    for (int i = 0; i < line.size(); i++) {
      if (std::isdigit(line[i])) {
        list = QString(line.substr(i, line.size() - i).c_str()).split(" ");
        double temp = calculate_cpu_utilization(list, id);
        if (id != 0) {
          individual_cpu_status_[id - 1]->replace(0, usage / temp * 100);
        } else {
          usage = temp;
        }
        break;
      }
    }
  }
  fin.close();
  return usage;
}
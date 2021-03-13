// memory.cc.
// created by tekky on 2021.3.9.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/memory.hh"

#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <fstream>

using namespace QtCharts;

MemoryStatus::MemoryStatus(QWidget *parent)
    : QWidget{parent}, memory_info_{new MemoryInfo} {

  //   layout_ = new QVBoxLayout(this);
  on_data_updated();
}

MemoryStatus::~MemoryStatus() {}

void MemoryStatus::memory_status_update() {
  std::ifstream fin;
  fin.open("/proc/meminfo");
  std::string mem_total;
  std::string mem_free;

  std::getline(fin, mem_total);
  std::getline(fin, mem_free);
  fin.close();

  for (int i = 0; i < mem_total.size(); i++) {
    if (std::isdigit(mem_total[i])) {
      memory_info_->memory_size =
          std::stoi(mem_total.substr(i, mem_total.size() - i - 3));
    }
  }

  for (int i = 0; i < mem_free.size(); i++) {
    if (std::isdigit(mem_free[i])) {
      memory_info_->memory_free =
          std::stoi(mem_free.substr(i, mem_free.size() - i - 3));
    }
  }
  //   QStringList list = QString(mem_total.c_str()).split(" ");
  //   qDebug() << "list size = " << list.size();
}

void MemoryStatus::display_memory_status() {
  QPieSeries *series = new QPieSeries();
  series->append("Total Memory", memory_info_->memory_size);
  series->append("Memory Used",
                 memory_info_->memory_size - memory_info_->memory_free);
  //![1]

  //![2]
  QPieSlice *slice = series->slices().at(1);
  slice->setExploded();
  slice->setLabelVisible(true);
  slice->setPen(QPen(Qt::darkGreen, 2));
  slice->setBrush(Qt::green);

  auto slice_use = series->slices().at(0);
  slice->setLabelVisible(true);
  //![2]

  //![3]
  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Memory Utilization");
  chart->legend()->hide();
  //![3]

  //![4]
  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  //![4]
  auto layout = new QVBoxLayout();
  layout->addWidget(chartView);
  //   if (layout() != nullptr) {
  //     auto old = layout();
  //     auto item = old->takeAt(0);
  //     old->removeItem(item);
  //     delete old;
  //   }
  setLayout(layout);
}

void MemoryStatus::on_data_updated() {
  memory_status_update();
  display_memory_status();
}
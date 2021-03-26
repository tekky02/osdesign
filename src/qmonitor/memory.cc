// memory.cc.
// created by tekky on 2021.3.9.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/memory.hh"

#include <fstream>

#include <QColor>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

using namespace QtCharts;

MemoryStatus::MemoryStatus(QWidget *parent)
    : QWidget{parent}, memory_info_{new MemoryInfo}, p_series_{new QPieSeries} {

  display_memory_status();
  on_data_updated();
}

MemoryStatus::~MemoryStatus() {}

void MemoryStatus::memory_status_update() {
  std::ifstream fin;
  fin.open("/proc/meminfo");
  std::string mem_total;
  std::string mem_free;
  std::string mem_avi;

  std::getline(fin, mem_total);
  std::getline(fin, mem_free);
  std::getline(fin, mem_avi);
  fin.close();

  for (int i = 0; i < mem_total.size(); i++) {
    if (std::isdigit(mem_total[i])) {
      memory_info_->memory_size =
          std::stoi(mem_total.substr(i, mem_total.size() - i - 3));
      break;
    }
  }

  for (int i = 0; i < mem_avi.size(); i++) {
    if (std::isdigit(mem_avi[i])) {
      memory_info_->memory_free =
          std::stoi(mem_avi.substr(i, mem_avi.size() - i - 3));
      break;
    }
  }

  memory_info_->memory_used =
      memory_info_->memory_size - memory_info_->memory_free;
}

void MemoryStatus::display_memory_status() {
  p_series_->append("Memory Free", memory_info_->memory_free);
  p_series_->append("Memory Used", memory_info_->memory_used);

  auto slice = p_series_->slices().at(1);
  slice->setExploded();
  slice->setLabelVisible(true);
  slice->setBrush(QColor(57, 197, 187));

  auto slice_free = p_series_->slices().at(0);
  slice_free->setLabelVisible(true);
  slice_free->setBrush(QColor(255, 165, 0));

  QChart *chart = new QChart();
  chart->addSeries(p_series_.get());
  chart->setTitle("Memory Utilization");
  chart->legend()->hide();

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
}

void MemoryStatus::on_data_updated() {
  memory_status_update();

  p_series_->slices().at(0)->setValue(memory_info_->memory_free);
  p_series_->slices().at(1)->setValue(memory_info_->memory_used);
}
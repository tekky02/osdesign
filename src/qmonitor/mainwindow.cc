// mainwindow.cc.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky.

#include "qmonitor/mainwindow.hh"

#include "qmonitor/authorinfo.hh"
#include "qmonitor/cpu.hh"
#include "qmonitor/memory.hh"
#include "qmonitor/process.hh"
#include "qmonitor/system.hh"

#include <QDebug>
#include <QGridLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QTableWidget>
#include <QTime>
#include <QWidget>

#include "resources.h"

MainWindow::MainWindow(QWidget *parent) : QWidget{parent} {
  // this->resize(800, 400);
  auto layout = new QGridLayout(this);

  auto menu_bar = new QMenuBar();
  auto help_menu = new QMenu("&Help");
  help_menu->addAction("&About", this, &MainWindow::about,
                       Qt::CTRL + Qt::Key_A);

  cpu_status_ = new CpuStatus(this);
  memory_status_ = new MemoryStatus(this);

  tab_viewer_ = new QTabWidget();
  tab_viewer_->setTabShape(QTabWidget::Triangular);
  // setUpdatesEnabled(false);
  tab_viewer_->tabBar()->setExpanding(true);
  tab_viewer_->addTab(new SystemInfo(), tr("SystemInfo"));
  tab_viewer_->addTab(new ProcessStatus(), tr("Process"));
  tab_viewer_->addTab(cpu_status_, tr("CPU"));
  tab_viewer_->addTab(memory_status_, tr("Memory"));
  tab_viewer_->addTab(new AuthorInfo(), tr("About"));

  // layout->addWidget(menu_bar, 0, 0);
  layout->addWidget(tab_viewer_, 0, 0, 1, 2);

  reboot_button_ = new QPushButton("Reboot");
  connect(reboot_button_, &QPushButton::clicked, this,
          &MainWindow::on_reboot_button_clicked);

  shutdown_button_ = new QPushButton("Shutdown");
  connect(shutdown_button_, &QPushButton::clicked, this,
          &MainWindow::on_shutdown_button_clicked);

  layout->addWidget(reboot_button_, 1, 0);
  layout->addWidget(shutdown_button_, 1, 1);

  auto status_bar = new QStatusBar(this);
  layout->addWidget(status_bar, 2, 0, 2, 2);

  // auto status_bar_layout = new QHBoxLayout(status_bar);

  // TODO: add current time to dock status bar.
  current_time_ = new QLabel;
  // status_bar_layout->addWidget(current_time_, Qt::AlignRight);

  status_bar->addWidget(current_time_);

  // qDebug() << "Usage: "
  //          << QString::number(cpu_status_->on_cpu_status_update() * 100);
  auto cpu_status = new QLabel();
  status_bar->addWidget(cpu_status);

  auto timer = new QTimer();
  connect(timer, &QTimer::timeout, this, [this, cpu_status]() {
    current_time_->setText("Current Time: " + QTime::currentTime().toString());
    cpu_status->setText(
        "CPU Load: " +
        QString::number(cpu_status_->on_cpu_status_update() * 100) + "%");
    // memory_status_->on_data_updated();
  });

  timer->start(1000);
}

MainWindow::~MainWindow() {}

void MainWindow::about() noexcept {
  QMessageBox::information(nullptr, "About", tk::resources::About);
}

void MainWindow::on_reboot_button_clicked() {
  QMessageBox::warning(nullptr, "reboot", "Are you sure?");
}

void MainWindow::on_shutdown_button_clicked() {
  QMessageBox::warning(nullptr, "shutdown", "Are you sure?");
}
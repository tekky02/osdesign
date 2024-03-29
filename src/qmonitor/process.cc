// process.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

// #define DEBUG 1

#include "qmonitor/process.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include <QAction>
#include <QGridLayout>
#include <QLineEdit>
#include <QMenu>
#include <QMutexLocker>
#include <QStandardItemModel>

#include "qmonitor/utils.hpp"

ProcessStatus::ProcessStatus(QWidget *parent) : QTreeView{parent} {
  parse_process_directory();
  display_process_status();
}

ProcessStatus::~ProcessStatus() {}

void ProcessStatus::parse_process_directory() noexcept {
  namespace fs = std::filesystem;

  for (const auto &entry : fs::directory_iterator("/proc")) {
    auto file_name = entry.path().stem().string();
    if (std::isdigit(file_name[0])) {
      parse_status(file_name);
    }
  }

#ifdef DEBUG
  std::cout << "=========================================\n";
  debug_message();
#endif
}

void ProcessStatus::remove_killed_process() noexcept {
  namespace fs = std::filesystem;
  std::erase_if(process_, [](const auto &item) {
    const auto &[pid, process] = item;
    return !fs::exists("/proc/" + pid);
  });
}

// FIXME: sometimes the process crash.
void ProcessStatus::on_data_updated() noexcept {
  QMutexLocker lock{&this->process_mux_};
  this->setSortingEnabled(false);

  remove_killed_process();
  parse_process_directory();

  for (int i = model()->rowCount() - 1; i >= 0; i--) {
    auto pid = model()
                   ->data(model()->index(i, ProcessStatus::Columns::Pid))
                   .toString();
    if (!process_.contains(pid.toInt())) {
      model()->removeRow(i);
    } else {
      const auto &item = process_[pid.toInt()];
      this->update_item(i, ProcessStatus::Columns::Name, item.name);
      this->update_item(i, ProcessStatus::Columns::Pid, item.pid);
      this->update_item(i, ProcessStatus::Columns::PPid, item.ppid);
      this->update_item(i, ProcessStatus::Columns::Memory, item.mem_used);
      this->update_item(i, ProcessStatus::Columns::Priority, item.priority);
    }
  }

  auto current_row = this->model()->rowCount();
  for (const auto &[pid, item] : process_) {
    if (get_row_index_by_pid(QString::number(pid)) == -1) {
      if (item.name == "baloo_file_extr") {
        continue;
      }
      // std::cout << p++ << ": new process name = "
      //           << item.name.toLocal8Bit().constData() << std::endl;
      this->add_item(current_row, ProcessStatus::Columns::Name, item.name);
      this->add_item(current_row, ProcessStatus::Columns::Pid, item.pid);
      this->add_item(current_row, ProcessStatus::Columns::PPid, item.ppid);
      this->add_item(current_row, ProcessStatus::Columns::Memory,
                     item.mem_used);
      this->add_item(current_row, ProcessStatus::Columns::Priority,
                     item.priority);
      current_row++;
    }
  }

  this->setSortingEnabled(true);
}

void ProcessStatus::display_process_status() noexcept {

  auto model = new QStandardItemModel(this);

  QStringList horizontalHeader;
  horizontalHeader << "Name of Process"
                   << "Pid"
                   << "PPid"
                   << "Memory (KB)"
                   << "Priority";

  model->setHorizontalHeaderLabels(horizontalHeader);
  this->setModel(model);

  for (int i = 0; i < ProcessStatus::Columns::columns_count; i++) {
    this->resizeColumnToContents(i);
  }

  // insert process.
  this->setSortingEnabled(false);
  auto current_row = model->rowCount();
  for (const auto &[pid, item] : process_) {
    this->add_item(current_row, ProcessStatus::Columns::Name, item.name);
    this->add_item(current_row, ProcessStatus::Columns::Pid, item.pid);
    this->add_item(current_row, ProcessStatus::Columns::PPid, item.ppid);
    this->add_item(current_row, ProcessStatus::Columns::Memory, item.mem_used);
    this->add_item(current_row, ProcessStatus::Columns::Priority,
                   item.priority);
    current_row++;
  }

  this->setSortingEnabled(true);
}

void ProcessStatus::parse_status(const std::string &pid) noexcept {
  static const std::regex name{"^Name:\\s+(\\w+.*)$"};
  static const std::regex ppid{"^PPid:\\s+(\\d+)$"};
  static const std::regex vmsize{"^VmSize:\\s+(\\d+).*$"};
  // not care things after SigQ...
  static const std::regex stop{"^SigQ:.*$"};

  std::smatch match;
  ProcessInfo process{};

  process.pid = std::stoi(pid);
  std::string file_name = "/proc/" + pid + "/status";

  std::ifstream fin;
  fin.open(file_name);
  std::string line;

  while (!fin.eof()) {
    std::getline(fin, line);
    if (std::regex_search(line.cbegin(), line.cend(), match, name)) {
      process.name = match[1].str().c_str();
    } else if (std::regex_search(line.cbegin(), line.cend(), match, ppid)) {
      process.ppid = std::stoi(match[1]);
    } else if (std::regex_search(line.cbegin(), line.cend(), match, vmsize)) {
      process.mem_used = std::stoi(match[1]);
    } else if (std::regex_search(line.cbegin(), line.cend(), match, stop)) {
      break;
    }
  }
  fin.close();
  this->process_[process.pid] = process;
}

void ProcessStatus::debug_message() noexcept {
  for (const auto &[pid, item] : process_) {
    std::cout << "name: " << item.name.toLocal8Bit().constData() << "\t"
              << "pid: " << item.pid << "\t"
              << "ppid: " << item.ppid << "\t"
              << "memory: " << item.mem_used << "\n";
  }
}

void ProcessStatus::kill_process() {
  auto selected_index = currentIndex();
  auto pid_index =
      selected_index.sibling(selected_index.row(), ProcessStatus::Columns::Pid);
  auto pid_str = this->model()->data(pid_index).toString();

  auto command = ("kill " + pid_str).toLocal8Bit().constData();
  utils::exec(command);
}

void ProcessStatus::add_item(int row, int col, const QVariant &data) {
  auto item = new QStandardItem();
  item->setData(data, Qt::DisplayRole);
  item->setTextAlignment(Qt::AlignHCenter);

  static_cast<QStandardItemModel *>(this->model())->setItem(row, col, item);
}

void ProcessStatus::update_item(int row, int col, const QVariant &data) {
  this->model()->setData(this->model()->index(row, col), data, Qt::DisplayRole);
}

void ProcessStatus::mousePressEvent(QMouseEvent *event) {
  QTreeView::mousePressEvent(event); // execute base class method first

  auto row = indexAt(event->pos()).row();

  if (event->button() == Qt::RightButton && row != -1) {
    QMenu contex_menu{tr("Contex menu"), this};

    auto name = model()
                    ->data(model()->index(row, ProcessStatus::Columns::Name))
                    .toString();
    auto pid = model()
                   ->data(model()->index(row, ProcessStatus::Columns::Pid))
                   .toString();

    auto action = new QAction("Kill " + name + " (pid = " + pid + ")", this);
    connect(action, &QAction::triggered, this, &ProcessStatus::kill_process);

    contex_menu.addAction(action);
    contex_menu.exec(mapToGlobal(event->pos()));
  }
}

// void ProcessStatus::data_updated() {

// }

int ProcessStatus::get_row_index_by_pid(const QString &pid) {

  for (std::size_t i = 0; i < model()->rowCount(); i++) {
    auto row_index = model()
                         ->data(model()->index(i, ProcessStatus::Columns::Pid))
                         .toString();
    if (pid == row_index) {
      return i;
    }
  }
  return -1;
}
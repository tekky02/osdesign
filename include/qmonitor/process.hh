// process.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_PROCESS_HH__
#define __QMONITOR_PROCESS_HH__

#include <QMouseEvent>
#include <QTreeView>
#include <QWidget>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "qmonitor/basic.hh"

class ProcessStatus : public QTreeView {
  Q_OBJECT

public:
  explicit ProcessStatus(QWidget *parent = nullptr);
  ~ProcessStatus();

protected:
  void mousePressEvent(QMouseEvent *event) override;

private slots:
  void display_process_status() noexcept;
  void kill_process();
  int get_row_index_by_pid(const QString &pid);
  // void on_data_updated();

private:
  void parse_status(const std::string &pid) noexcept;
  void parse_process_directory() noexcept;
  void add_item(int row, int col, const QVariant &data);
  void debug_message() noexcept;

private:
  enum Columns : int { Name, Pid, PPid, Memory, Priority, columns_count };

private:
  // std::vector<ProcessInfo> process_;
  std::unordered_map<uint32_t, ProcessInfo> process_;
  // QListWidget *table_viewer_;
};

#endif // __QMONITOR_PROCESS_HH__

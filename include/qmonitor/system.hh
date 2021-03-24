// system.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __QMONITOR_SYSTEM_HH__
#define __QMONITOR_SYSTEM_HH__

#include <memory>

#include <QWidget>

#include "qmonitor/basic.hh"

class SystemInfo : public QWidget {
  Q_OBJECT

public:
  explicit SystemInfo(QWidget *parent = nullptr);
  ~SystemInfo();
  std::size_t processor_count() const;

private:
  void parse_info_from_proc(); // load information from /proc
  void display_information() noexcept;

private:
  std::shared_ptr<BasicInfo> basic_info_;
};

#endif // __QMONITOR_SYSTEM_HH__

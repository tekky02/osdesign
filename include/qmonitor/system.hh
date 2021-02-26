// created by tekky on 2021.2.20.
// Copyright(c) 2021 tekky.
// system.hh

#ifndef __QMONITOR_SYSTEM_HH__
#define __QMONITOR_SYSTEM_HH__

class SystemInfo {
public:
  SystemInfo();
  ~SystemInfo();
  void loadInfo(); // load information from /proc

private:
  QString os_name_;
  QString kernel_name_;
  QString kernel_release_;
  QString kernel_version_;
  QString host_name_;
  QString user_name_;
  QString cpu_name_;
  QString memory_size_;
  QTime   uptime_;
};

#endif // __QMONITOR_SYSTEM_HH__


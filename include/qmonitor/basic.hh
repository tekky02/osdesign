// basic.hh.
// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.
// @brief: basic information of the system.

#ifndef __QMONITOR_BASIC_HH__
#define __QMONITOR_BASIC_HH__

#include <QTime>
#include <array>

struct Point {
  uint32_t x;
  uint32_t y;
};

// cpu information
struct CpuStat {
  // uint64_t user_time;
  // uint64_t neg_nice_time;
  // uint64_t system_time;
  // uint64_t idle_time;
  // uint64_t iowait_time;
  // uint64_t irq_time;
  // uint64_t softirq_time;
  std::array<uint64_t, 8> time;
};

// memory information, size in KB.
struct MemoryInfo {
  std::size_t memory_size;
  std::size_t memory_used;
  std::size_t memory_free;
  std::size_t memory_swap_size;
  std::size_t memory_swap_free;
};

struct ProcessInfo {
  QString name;
  uint32_t pid;
  uint32_t ppid;
  uint32_t mem_used;
  uint32_t priority;
};

struct BasicInfo {
  std::string os_type;
  std::string os_release;
  std::string kernel_version;
  std::string kernel_release;
  std::string processor_model_name;
  std::string host_name;
  std::size_t processor_count;
  std::size_t memory_size;
  QTime uptime;
};

#endif // __QMONITOR_BASIC_HH__

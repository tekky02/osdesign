// created by tekky on 2021.2.20.
// Copyright © 2021 tekky. All rights reserved.
// @brief: basic information of the system.

#ifndef __QMONITOR_BASIC_HH__
#define __QMONITOR_BASIC_HH__

struct CpuInfo {
  size_t cpu_processor_count;
  size_t cpu_cache_size; 
  double cpu_clock_speed;
  QString cpu_module_name;
  QString cpu_address_size;
};

// memory information, detail in KB.
struct MemoryInfo {
  size_t memory_size;
  size_t memory_used;
  size_t memory_free;
  size_t memory_swap_size;
  size_t memory_swap_free;
};

struct MachineInfo {
};

#endif // __QMONITOR_BASIC_HH__

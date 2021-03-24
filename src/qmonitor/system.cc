// system.cc.
// created by tekky on 2021.3.8.
// Copyright © 2021 tekky. All rights reserved.

#include "qmonitor/system.hh"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <QBuffer>
#include <QGridLayout>
#include <QLabel>

#include "qmonitor/utils.hpp"

SystemInfo::SystemInfo(QWidget *parent)
    : QWidget{parent}, basic_info_{new BasicInfo} {
  parse_info_from_proc();
  display_information();
}

SystemInfo::~SystemInfo() {}

std::size_t SystemInfo::processor_count() const {
  return basic_info_->processor_count;
}

void SystemInfo::display_information() noexcept {
  auto layout = new QGridLayout(this);

  std::stringstream out;
  out << "<b>Host Name:</b> " << basic_info_->host_name
      << "<br><b>OS Type:</b> " << basic_info_->os_type
      << "<br><b>OS Release:</b> " << basic_info_->os_release
      << "<br><b>Kernel Version:</b> " << basic_info_->kernel_version
      << "<br><b>Kernel Release:</b> " << basic_info_->kernel_release
      << "<br><b>Model Name:</b> " << basic_info_->processor_model_name
      << "<br><b>Processor Count:</b> " << basic_info_->processor_count
      << "<br><b>Memory Installed:</b> "
      << basic_info_->memory_size * 1.0 / (1024 * 1024) << "GB";

  auto detail = new QLabel(out.str().c_str());
  layout->addWidget(detail);
}

void SystemInfo::parse_info_from_proc() {

  // regex expression to get prosessor numbers.
  auto cpu_count = utils::exec("grep ^processor /proc/cpuinfo | wc -l");
  //   std::cout << "parse_result: " << cpu_count << "\n";
  basic_info_->processor_count = std::stoi(cpu_count);

  basic_info_->processor_model_name =
      utils::exec("grep 'model name' /proc/cpuinfo | head -n 1 | cut -d "
                  "':' -f 2 | cut -b 2-");

  basic_info_->kernel_version = utils::exec("cat /proc/sys/kernel/osrelease");

  basic_info_->os_type = utils::exec("cat /proc/sys/kernel/ostype");

  basic_info_->os_release = utils::exec("cat /proc/sys/kernel/osrelease");

  basic_info_->memory_size = std::stoi(utils::exec(
      "head -n1 /proc/meminfo | grep -o '[0-9].*$' | cut -d ' ' -f 1"));

  basic_info_->host_name = utils::exec("cat /proc/sys/kernel/hostname");

  int seconds = std::stoi(utils::exec("cat /proc/uptime | cut -d ' ' -f 1"));

#ifdef DEBUG
  std::ofstream fout;
  fout.open("/tmp/qmonitor", std::ios::out);
  fout << "cpu count: " << basic_info_->processor_count << "\n"
       << "processor model name: " << basic_info_->processor_model_name << "\n"
       << "kernel_version: " << basic_info_->kernel_version << "\n"
       << "os type: " << basic_info_->os_type << "\n"
       << "os release: " << basic_info_->os_release << "\n"
       << "memory size: " << basic_info_->memory_size
       << "hostname: " << basic_info_->host_name << std::endl;
  fout.close();
#endif
}
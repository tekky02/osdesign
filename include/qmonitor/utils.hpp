// utils.hpp.
// created by tekky on 2021.3.8.

#ifndef __QMONITOR_UTILS_HPP__
#define __QMONITOR_UTILS_HPP__

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace {
namespace utils {

std::string exec(const std::string &cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

} // namespace utils
} // namespace

#endif // __QMONITOR_UTILS_HPP__
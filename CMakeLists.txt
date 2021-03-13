cmake_minimum_required(VERSION 3.10...3.19)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
  message(FATAL_ERROR "in-source build is not allowed!!!\nplease build the project in some directory like 'build'")
endif()

project(osdesign VERSION 0.1 LANGUAGES C CXX)

option(BUILD_COPIER CACHE ON)
option(BUILD_QTVIEWER CACHE OFF)
option(BUILD_QMONITOR CACHE OFF)
option(BUILD_UNIT_TEST CACHE OFF)

include(GNUInstallDirs)

if(BUILD_COPIER)
  add_subdirectory(src/copier)
endif()

if(BUILD_QTVIEWER)
  add_subdirectory(src/qtviewer)
endif()

if(BUILD_QMONITOR)
  add_subdirectory(src/qmonitor)
endif()

if(BUILD_UNIT_TEST)
  add_subdirectory(extern/googletest EXLUDE_FROM_ALL)
  add_subdirectory(test)
endif()


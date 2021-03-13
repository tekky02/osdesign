cmake_minimum_required(VERSION 3.10...3.19)

project(qmonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

configure_file(authorinfo.html authorinfo.html.out)
file(READ ${CMAKE_CURRENT_BINARY_DIR}/authorinfo.html.out Resources_AuthorInfo)
configure_file(resources.h.in resources.h)

list(APPEND CXX_SOURCES 
     main.cc 
     mainwindow.cc
     ${CMAKE_CURRENT_BINARY_DIR}/resources.h
     ${CMAKE_SOURCE_DIR}/include/qmonitor/mainwindow.hh
     authorinfo.cc
     ${CMAKE_SOURCE_DIR}/include/qmonitor/authorinfo.hh
     system.cc
     ${CMAKE_SOURCE_DIR}/include/qmonitor/system.hh
     cpu.cc
     ${CMAKE_SOURCE_DIR}/include/qmonitor/cpu.hh
     process.cc
     ${CMAKE_SOURCE_DIR}/include/qmonitor/process.hh
     memory.cc
     ${CMAKE_SOURCE_DIR}/include/qmonitor/memory.hh)

add_executable(${PROJECT_NAME} ${CXX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Charts)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")


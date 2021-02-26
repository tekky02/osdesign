cmake_minimum_required(VERSION 3.10...3.19)

project(qmonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 REQUIRED)

list(APPEND CXX_SOURCES main.cc mainwindow.cc)

add_executable(${PROJECT_NAME} ${CXX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")


cmake_minimum_required(VERSION 3.10...3.19)

project(qviewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/sample.png ${CMAKE_BINARY_DIR}/sample.png COPYONLY)

list(APPEND CXX_SOURCES
     main.cc
     mainwindow.cc
     mainwindow.hh)

add_executable(${PROJECT_NAME} ${CXX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(FILES ${CMAKE_SOURCE_DIR}/sample.png DESTINATION "${CMAKE_BINARY_DIR}/bin")


cmake_minimum_required(VERSION 3.10...3.19)

project(qtviewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

list(APPEND CXX_SOURCES
     main.cc
     mainwindow.cc
     ${CMAKE_SOURCE_DIR}/include/qtviewer/mainwindow.hh)

add_executable(${PROJECT_NAME} ${CXX_SOURCES})

add_executable(bufferwindow 
               bufferwindow.cc
               ${CMAKE_SOURCE_DIR}/include/qtviewer/bufferwindow.hh)

add_executable(imagewindow
               imagewindow.cc
               ${CMAKE_SOURCE_DIR}/include/qtviewer/imagewindow.hh)

add_executable(timewindow
               timewindow.cc
               ${CMAKE_SOURCE_DIR}/include/qtviewer/timewindow.hh)


target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)

target_include_directories(bufferwindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(bufferwindow PRIVATE Qt5::Widgets)

target_include_directories(imagewindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(imagewindow PRIVATE Qt5::Widgets)

target_include_directories(timewindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(timewindow PRIVATE Qt5::Widgets)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS imagewindow RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS bufferwindow RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS timewindow   RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")


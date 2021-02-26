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

add_executable(sourcewindow
               sourcewindow.cc
               ${CMAKE_SOURCE_DIR}/include/qtviewer/sourcewindow.hh)

add_executable(destwindow
               destwindow.cc
               ${CMAKE_SOURCE_DIR}/include/qtviewer/destwindow.hh)


target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)

target_include_directories(bufferwindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(bufferwindow PRIVATE Qt5::Widgets)

target_include_directories(sourcewindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(sourcewindow PRIVATE Qt5::Widgets)

target_include_directories(destwindow PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(destwindow PRIVATE Qt5::Widgets)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS sourcewindow RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS bufferwindow RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
install(TARGETS destwindow   RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")


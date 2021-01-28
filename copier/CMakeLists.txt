cmake_minimum_required(VERSION 3.10...3.19)

project(copier VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(copier copier.c)

add_executable(copy main.c)

target_include_directories(copier PRIVATE
                           "${CMAKE_SOURCE_DIR}/include")
target_include_directories(copy PRIVATE 
						   "${CMAKE_SOURCE_DIR}/include"
						   )
target_link_libraries(copy PRIVATE copier)

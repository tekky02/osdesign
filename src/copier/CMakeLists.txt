cmake_minimum_required(VERSION 3.10...3.19)

project(copier VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_CLANG_TIDY
	clang-tidy;
	-checks=*;)

if(NOT DEFINED CMAKE_BUILD_TYPE OR ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug"))
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -g -fno-omit-frame-pointer")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()

add_library(copier copier.c)

add_executable(copy main.c)

target_include_directories(copier PRIVATE
                           "${CMAKE_SOURCE_DIR}/include")
target_include_directories(copy PRIVATE 
						   "${CMAKE_SOURCE_DIR}/include"
						   )
target_link_libraries(copy PRIVATE copier)

install(TARGETS copy 
		RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")

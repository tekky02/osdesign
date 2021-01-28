cmake_minimum_required(VERSION 3.10...3.19)

project(unit_test VERSION 0.1 LANGUAGES C CXX)

list(APPEND TEST_FILES unittest/copier/copier_test.cc)

add_executable(${PROJECT_NAME} ${TEST_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main copier)

target_include_directories(${PROJECT_NAME} 
		                   PRIVATE
                           "${CMAKE_SOURCE_DIR}/include"
                           "${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include"
						   )

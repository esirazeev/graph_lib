cmake_minimum_required(VERSION 3.16.3)
project(gtest.out)

#compiler and linker options
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall")

# gtests
include_directories(.)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(gtest.out tests/unit_test_graph.cpp gtest.out tests/unit_test_graph_algorithms.cpp)
target_link_libraries(gtest.out ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

#run gtest after build
add_custom_command (
  TARGET gtest.out POST_BUILD
  COMMENT "\nRunning google tests"
  COMMAND gtest.out
)

#install bins into bin folder
install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)

cmake_minimum_required(VERSION 3.16.3)
cmake_policy(SET CMP0016 NEW)

project(CCSDS VERSION 0.0.0 DESCRIPTION "CCSDSParser")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/CCSDSParser)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(tests)






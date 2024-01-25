cmake_minimum_required(VERSION 3.16.3)
cmake_policy(SET CMP0016 NEW)

project(Main VERSION 1.0.0 DESCRIPTION "creating main execitable")


include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(src)

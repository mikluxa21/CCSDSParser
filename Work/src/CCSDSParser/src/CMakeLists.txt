cmake_minimum_required(VERSION 3.16.3)
cmake_policy(SET CMP0016 NEW)
project(main)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} sub::lib)

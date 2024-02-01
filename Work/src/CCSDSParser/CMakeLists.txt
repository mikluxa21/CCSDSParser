cmake_minimum_required(VERSION 3.16.3)

project(headers)
add_library(${PROJECT_NAME} src/CCSDS.cpp src/VCDU.cpp src/Interface.cpp)
add_library(sub::lib ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
#add_subdirectory(src)


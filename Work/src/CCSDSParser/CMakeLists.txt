cmake_minimum_required(VERSION 3.16.3)

project(CCSDS VERSION 1.0.0 DESCRIPTION "optional cmakelists")

add_library(libCCSDS CCSDS.h src/CCSDS.cpp)
add_library(libVCDU VCDU.h src/VCDU.cpp)
add_library(libInterface Interface.h src/Interface.cpp)
target_link_libraries(libVCDU PRIVATE libCCSDS)
target_link_libraries(libInterface PRIVATE libVCDU)

add_subdirectory(src)

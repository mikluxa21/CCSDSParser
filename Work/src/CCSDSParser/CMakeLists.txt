cmake_minimum_required(VERSION 3.16.3)

project(CCSDS VERSION 1.0.0 DESCRIPTION "optional cmakelists")

add_library(libCCSDS CCSDS.h src/CCSDS.cpp)
add_library(libVCDU src/VCDU.cpp VCDU.h)
add_library(libInterface src/Interface.cpp Interface.h)
target_link_libraries(libVCDU PUBLIC libCCSDS)
target_link_libraries(libInterface PUBLIC libVCDU)

add_subdirectory(src)

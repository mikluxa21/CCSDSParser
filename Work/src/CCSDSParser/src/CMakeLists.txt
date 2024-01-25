set(SRC CCSDS.cpp VCDU.cpp Interface.cpp)

add_library(lib ${SRC})

set(main main.cpp)

add_executable(main ${main})

target_link_libraries(main lib)

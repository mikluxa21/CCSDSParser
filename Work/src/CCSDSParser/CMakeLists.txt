set(HDRS CCSDS.h
         VCDU.h
         Interface.h
         )

set(SRCS src/CCSDS.cpp
         src/VCDU.cpp
         src/Interface.cpp
         )

add_library(ccsds_parser OBJECT ${SRCS} ${HDRS})

add_executable(main src/main.cpp)
target_link_libraries(main ccsds_parser)

set(TEST_NAME ccsds_test)

add_executable(${TEST_NAME} tests.cpp)
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TEST_NAME} gtest gtest_main pthread ccsds_parser)

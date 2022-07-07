cmake_minimum_required(VERSION 3.13)

find_package(GTest CONFIG REQUIRED)

FILE(GLOB_RECURSE IWANNA_TEST_SOURCE
        ${PROJECT_SOURCE_DIR}/test/**/*.cpp
        ${PROJECT_SOURCE_DIR}/test/**/*.h
        ${PROJECT_SOURCE_DIR}/test/*.cpp
        ${PROJECT_SOURCE_DIR}/test/*.h
        )
FILE(GLOB_RECURSE IWANNA_SOURCE
        ${PROJECT_SOURCE_DIR}/src/**/*.cpp
        ${PROJECT_SOURCE_DIR}/src/**/*.ui
        ${PROJECT_SOURCE_DIR}/src/**/*.h
        )
message(STATUS "find test sources: ${IWANNA_TEST_SOURCE} ${IWANNA_SOURCE}")
add_executable(iwanna_test ${IWANNA_TEST_SOURCE} ${IWANNA_SOURCE})
target_link_libraries(iwanna_test Qt5::Widgets GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(iwanna_test)

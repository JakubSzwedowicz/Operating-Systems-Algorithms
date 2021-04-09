if (test)
    enable_testing()

    set(TEST_INCLUDES_DIR "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}" "${INCLUDES_DIR}")

    add_executable(TEST_HARD_DRIVE Test_Hard_Drive.cpp)
    add_executable(TEST_OPERATING_SYSTEM Test_Operating_System_SSTF.cpp)

    add_library(ALL_TESTS INTERFACE)
    target_link_libraries(ALL_TESTS INTERFACE TEST_HARD_DRIVE TEST_OPERATING_SYSTEM)
    target_include_directories(ALL_TESTS INTERFACE ${TEST_INCLUDES_DIR})

    target_link_libraries(TEST_HARD_DRIVE gtest gtest_main HARD_DRIVE)
    target_link_libraries(TEST_OPERATING_SYSTEM gtest gtest_main OPERATING_SYSTEM)

    add_test(NAME TEST_HARD_DRIVE COMMAND TEST_HARD_DRIVE)
    add_test(NAME TEST_OPERATING_SYSTEM COMMAND TEST_OPERATING_SYSTEM)

endif ()
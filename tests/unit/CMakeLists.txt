add_executable(habit_test habit.cc)
target_link_libraries(habit_test GTest::gtest_main)

# TODO: make habit_tracker a statically linked library so that I don't have to
# keep targetting the cpp files
target_include_directories(habit_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(habit_test PRIVATE "${CMAKE_SOURCE_DIR}/src/habit.cpp"
                                  "${CMAKE_SOURCE_DIR}/src/goal.cpp")

include(GoogleTest)
gtest_discover_tests(habit_test)

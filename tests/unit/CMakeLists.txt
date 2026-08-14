
add_executable(habit_test habit.cc)
target_link_libraries(habit_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(habit_test)

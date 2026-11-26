add_library(habit_core STATIC goal.cpp habit.cpp tui.cpp)
target_include_directories(habit_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_sources(habit-tracker PRIVATE main.cpp)
target_link_libraries(habit-tracker PRIVATE habit_core)

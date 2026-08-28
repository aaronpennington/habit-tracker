target_include_directories(habit-tracker PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources(habit-tracker PRIVATE main.cpp goal.cpp habit.cpp)

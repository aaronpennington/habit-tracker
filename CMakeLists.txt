cmake_minimum_required(VERSION 3.15)

project(habit-tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)

enable_testing()

# include cmake folder
add_subdirectory(cmake)

set(PROJECT_SOURCES
  src/main.cpp
  src/goal.cpp
  src/habit.cpp
)

add_executable(habit-tracker ${PROJECT_SOURCES})

add_subdirectory(src)

# third-party libraries
add_subdirectory(third-party)

# Unit tests
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.15)

project(habit-tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)

enable_testing()

# include cmake folder
add_subdirectory(cmake)

add_executable(habit-tracker)

# third-party libraries
add_subdirectory(third-party)

add_subdirectory(src)

# Unit tests
add_subdirectory(tests)

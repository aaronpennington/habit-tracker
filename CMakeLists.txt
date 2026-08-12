cmake_minimum_required(VERSION 3.15)

project(habit-tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include cmake folder
add_subdirectory(cmake)

add_executable(habit-tracker)
add_subdirectory(src)

include(FetchContent)

# SQLite library
message("Building SQLiteCpp...")
add_subdirectory(SQLiteCpp)
target_link_libraries(habit_core PUBLIC SQLiteCpp sqlite3 pthread dl)

# googletest library
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 063de7e9578f82b369302001269680b4b1553359 # release-1.18.0
)
FetchContent_MakeAvailable(googletest)

# FTXUI
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  GIT_TAG v7.0.3)
FetchContent_MakeAvailable(ftxui)

target_link_libraries(habit_core PUBLIC ftxui::ftxui)

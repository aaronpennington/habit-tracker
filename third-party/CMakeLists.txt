include(FetchContent)

# SQLite library
message("Building SQLiteCpp...")
add_subdirectory(SQLiteCpp)
target_link_libraries(habit-tracker SQLiteCpp sqlite3 pthread dl)

# googletest library
# TODO: Make googletest target EXCLUDE_FROM_ALL in build
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        063de7e9578f82b369302001269680b4b1553359 # release-1.18.0
)
FetchContent_MakeAvailable(googletest)

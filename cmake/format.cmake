# Format all c++ files using clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
  message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")

  file(GLOB_RECURSE _CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp"
       "${CMAKE_SOURCE_DIR}/src/*.hpp" "${CMAKE_SOURCE_DIR}/include/*.h")

  add_custom_target(
    clangformat
    COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${_CPP_FILES}
    COMMENT "Formatting cpp files..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
  message(WARNING "clang-format executable not found.")
endif()

# Format all cmake files using cmake-format
if(WIN32)
  set(CMAKE_FORMAT_EXE "${CMAKE_SOURCE_DIR}/.venv/Scripts/cmake-format.exe")
else()
  set(CMAKE_FORMAT_EXE "${CMAKE_SOURCE_DIR}/.venv/bin/cmake-format")
endif()

if(CMAKE_FORMAT_EXE)
  message(STATUS "Found cmake-format: ${CMAKE_FORMAT_EXE}")

  # search for cmake files, excluding third-party directory
  file(
    GLOB_RECURSE
    _CMAKE_FILES
    "${CMAKE_SOURCE_DIR}/CMakeLists.txt"
    "${CMAKE_SOURCE_DIR}/src/CMakeLists.txt"
    "${CMAKE_SOURCE_DIR}/cmake/CMakeLists.txt"
    "${CMAKE_SOURCE_DIR}/cmake/*.cmake")

  add_custom_target(
    cmakeformat
    COMMAND ${CMAKE_FORMAT_EXE} -i ${_CMAKE_FILES}
    COMMENT "Formatting cmake files..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
  message(WARNING "cmake-format executable not found.")
endif()

add_custom_target(format COMMAND ${CMAKE_COMMAND} -E echo "Formatting...")
add_dependencies(format clangformat cmakeformat)

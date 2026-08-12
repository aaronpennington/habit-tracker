# Format all files using clang-format

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
  message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")

  file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
  )

  add_custom_target(format
      COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${SOURCES}
      COMMENT "Formatting..."
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
else()
  message(WARNING "clang-format executable not found.")
endif()

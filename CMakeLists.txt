cmake_minimum_required (VERSION 3.27)

set(CMAKE_CXX_STANDARD 23) 

project ("adventofcode2023" LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare( fmt
GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
GIT_TAG f5e54359df4c26b6230fc61d38aa294581393084
)
FetchContent_MakeAvailable(fmt)

file(GLOB TEST_INPUT_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/input/*.txt)
file(COPY ${TEST_INPUT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/input)

add_subdirectory("utility")
add_subdirectory("day01")
add_subdirectory("day02")
add_subdirectory("day03")
add_subdirectory("day04")
add_subdirectory("day05")
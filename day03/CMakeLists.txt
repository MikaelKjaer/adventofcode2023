#Day 03 problem

add_executable(day03 "main.cpp")
target_include_directories(day03 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_link_libraries(day03 adventofcode_utility_library fmt::fmt-header-only)
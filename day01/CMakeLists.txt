#Day 01 problem

add_executable(day01 "main.cpp")
target_include_directories(day01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_link_libraries(day01 adventofcode_utility_library fmt::fmt-header-only)
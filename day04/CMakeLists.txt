#Day 04 problem

add_executable(day04 "main.cpp")
target_include_directories(day04 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_link_libraries(day04 adventofcode_utility_library fmt::fmt-header-only)
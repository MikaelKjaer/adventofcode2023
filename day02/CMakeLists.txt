#Day 02 problem

add_executable(day02 "main.cpp")
target_include_directories(day02 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_link_libraries(day02 adventofcode_utility_library fmt::fmt-header-only)
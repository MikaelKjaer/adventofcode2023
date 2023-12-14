#Day 05 problem

add_executable(day05 "main.cpp")
target_include_directories(day05 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_link_libraries(day05 adventofcode_utility_library fmt::fmt-header-only)
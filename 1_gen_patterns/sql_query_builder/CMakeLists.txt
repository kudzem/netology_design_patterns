cmake_minimum_required(VERSION 3.10])
project(cpp_builder_pattern)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_executable(pg "sql_query_builder_test.cpp" "sql_select_query_builder.h" "advanced_sql_query_builder.h")
cmake_minimum_required(VERSION 4.0.3)

project(Practice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
add_executable(c_practice src/main.c)
add_executable(cpp_practice src/main.cpp)
set_target_properties(c_practice PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/)
set_target_properties(cpp_practice PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/)

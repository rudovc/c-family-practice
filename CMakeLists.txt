cmake_minimum_required(VERSION 4.0.3)

project(Practice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
add_executable(practice src/main.c)
set_target_properties(practice PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/)

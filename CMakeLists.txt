cmake_minimum_required(VERSION 4.0.3)

project(Practice)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror"
)
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror"
)
set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror")
set(CMAKE_C_FLAGS_DEBUG
    "${CMAKE_C_FLAGS_DEBUG}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror")
add_executable(c_practice src/main.c)
add_executable(cpp_practice src/main.cpp)
set_target_properties(c_practice PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/)
set_target_properties(cpp_practice PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/)

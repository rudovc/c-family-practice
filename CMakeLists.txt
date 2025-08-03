cmake_minimum_required(VERSION 4.0.3)

project(Practice)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror -g -O0"
)
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror -g -O0"
)
set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror -g -O0")
set(CMAKE_C_FLAGS_DEBUG
    "${CMAKE_C_FLAGS_DEBUG}\
  -fsanitize=address\
  -fno-omit-frame-pointer\
  -Wall -Werror -g -O0")
add_executable(c_practice
  src/c/main.c
  src/c/lib/heaparray.c
  src/c/lib/input.c
  src/c/lib/arena.c
  src/c/lib/maybe.c
  src/c/lib/error.c
)
add_executable(cpp_practice src/cpp/main.cpp)
set_target_properties(c_practice
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/
    UNITY_BUILD ON)
set_target_properties(cpp_practice PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY out/
    UNITY_BUILD ON)
target_include_directories(c_practice PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/c")
target_include_directories(cpp_practice PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")

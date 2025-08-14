cmake_minimum_required(VERSION 4.0.3)

project(Practice.exe)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_SYSTEM_VERSION AMD64)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_SYSROOT /usr/x86_64-w64-mingw32/)
set(CMAKE_LINKER_TYPE LLD)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}\
  -fno-omit-frame-pointer\
  -Wall")

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
  -fno-omit-frame-pointer\
  -Wall"
)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}\
    -I /usr/x86_64-w64-mingw32/include"
    )
# -L /usr/x86_64-w64-mingw32/lib\
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
    -I /usr/x86_64-w64-mingw32/include"
    )


set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}\
  -fno-omit-frame-pointer\
  -Wall -g -O0")
set(CMAKE_C_FLAGS_DEBUG
    "${CMAKE_C_FLAGS_DEBUG}\
  -fno-omit-frame-pointer\
  -Wall -g -O0")

set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}\
    -I /usr/x86_64-w64-mingw32/include\
    ")
# -L /usr/x86_64-w64-mingw32/lib\
set(CMAKE_C_FLAGS_DEBUG
    "${CMAKE_C_FLAGS_DEBUG}\
    -I /usr/x86_64-w64-mingw32/include\
    ")
# -L /usr/x86_64-w64-mingw32/lib\
add_executable(c_practice.exe
  ../../src/c/main.c
  ../../src/c/lib/heaparray.c
  ../../src/c/lib/input.c
  ../../src/c/lib/arena.c
  ../../src/c/lib/maybe.c
  ../../src/c/lib/error.c
  ../../src/c/lib/str.c
)
# add_executable(cpp_practice.exe ../../src/cpp/main.cpp)
set_target_properties(c_practice.exe
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY out/
    UNITY_BUILD ON)
# set_target_properties(cpp_practice.exe PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY out/
#     UNITY_BUILD ON)
target_include_directories(c_practice.exe PRIVATE
    "../../src/c")
set_source_files_properties("../../src/c*"
    PROPERTIES COMPILE_FLAGS "-Werror"
    )
# target_include_directories(cpp_practice.exe PRIVATE
#     "../../src/cpp")


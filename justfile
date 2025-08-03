clean:
    rm -rf ./CMakeCache.txt && rm -rf ./CMakeFiles/
build:
    cmake --build . --config Debug
configure:
    cmake -D CMAKE_BUILD_TYPE="Debug" -D CMAKE_CXX_COMPILER="clang++" -D CMAKE_C_COMPILER="clang" .
runc:
    ./out/c_practice
runcpp:
    ./out/c_practice
format:
    find ./src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | xargs clang-format -i

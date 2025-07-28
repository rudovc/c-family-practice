build:
    cmake --build .
configure:
    cmake -D CMAKE_CXX_COMPILER="clang++" -D CMAKE_C_COMPILER="clang" .

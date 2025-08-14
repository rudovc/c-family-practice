clean:
    rm -rf build/linux/CMakeCache.txt && rm -rf build/linux/CMakeFiles/

clean-windows:
    rm -rf build/windows/CMakeCache.txt && rm -rf build/windows/CMakeFiles/

build:
    cd build/linux && cmake --build . --config Debug

configure:
    cd build/linux && cmake .

build-win:
    cd build/windows && cmake --build . --config Debug -v

configure-win:
    cd build/windows && cmake .

runc:
    ./out/c_practice

runcpp:
    ./out/c_practice

format:
    find ./src/ -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | xargs clang-format -i

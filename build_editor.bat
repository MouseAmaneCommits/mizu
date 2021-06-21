@echo OFF

cmake -G "MinGW Makefiles" -S editor -B editor/build
cd editor
cd build
mingw32-make
cd ..
cd ..
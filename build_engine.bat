cmake -G "MinGW Makefiles" -S engine -B engine/build
cd engine
cd build
mingw32-make
cd ..
cd ..
cmake -G "MinGW Makefiles" -S testbed -B testbed/build
cd testbed
cd build
mingw32-make
cd ..
cd ..
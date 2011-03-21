* To build:
mkdir build && cd build
cmake ..
make

* Run with:
./jconsole

* If you had unmet optional dependencies and want to
  update the Makefile after getting them, run:
rm CMakeCache.txt
cmake ..

* Cross-compile with:
mkdir build.x && cd build.x
cmake .. -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_C_COMPILER=arm-none-linux-gnueabi-gcc

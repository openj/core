* To build and install:
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install

* Run with:
jconsole

* If you had unmet optional dependencies and want to
  update the Makefile after getting them, run:
rm CMakeCache.txt
cmake -DCMAKE_INSTALL_PREFIX=/usr ..

* Cross-compile with:
mkdir build.x && cd build.x
cmake .. -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_C_COMPILER=arm-none-linux-gnueabi-gcc
make

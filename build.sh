#!/bin/bash

cd external
wget https://www.ijg.org/files/jpegsrc.v9c.tar.gz
tar xvf jpegsrc.v9c.tar.gz
cd jpeg-9c/
wget https://raw.githubusercontent.com/stohrendorf/libjpeg-cmake/master/jconfig.h.in
wget https://raw.githubusercontent.com/stohrendorf/libjpeg-cmake/master/CMakeLists.txt
cd ..
rm -rf jpegsrc.v9c.tar.gz
cd ..
mkdir build
cd build
cmake ..
make -j$(nproc)

mkdir build
cd build
cmake -G Ninja -B . ..
ninja
cd ..
echo "Binary built to $(pwd)/build/bin"

echo "setting up git hooks"
cp ./.hooks/pre-commit ./.git/hooks

echo "setting up build environment"
mkdir build
cd build
cmake .. -G Ninja -DMAKE_BUILD_TYPE=Debug
ninja
cd ..
echo "Binary built to $(pwd)/build"

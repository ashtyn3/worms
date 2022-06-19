echo "setting up git hooks"
cp ./.hooks/pre-commit ./.git/hooks

echo "setting up build environment"
meson setup build
cd build
ninja
cd ..
echo "Binary built to $(pwd)/build"

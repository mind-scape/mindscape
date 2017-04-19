# Remove existing build directory
echo "Removing build dir"
rm -rf build/

# Creating build directory
echo "Creating build file"
mkdir build

# Enter build and run Cmake
echo "Running cmake"
cd build/ && cmake ..

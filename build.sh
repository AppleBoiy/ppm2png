#!/bin/bash

# Create the build directory if it does not exist
if [ ! -d build ]; then
    mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to configure the project
cmake ..

# Build the project
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable created: build/ppm_to_png"
else
    echo "Build failed."
    exit 1
fi

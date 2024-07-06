cmake_minimum_required(VERSION 3.10)

project(ppm_to_png)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PNG REQUIRED)

# specify the include directories
set(PNG_INCLUDE_DIRS /opt/homebrew/Cellar/libpng/1.6.43/include)

include_directories(${PNG_INCLUDE_DIRS} include)

# display the include directories
message(STATUS "PNG_INCLUDE_DIRS: ${PNG_INCLUDE_DIRS}")

add_executable(ppm_to_png src/main.cpp src/ppm_to_png.cpp)

target_link_libraries(ppm_to_png ${PNG_LIBRARIES})

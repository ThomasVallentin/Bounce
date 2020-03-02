# cmake_minimum_required(VERSION <specify CMake version here>)
project(bounceRenderer)

# C++ version
set(CMAKE_CXX_STANDARD 17)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Setting files
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Creating .exe
add_executable(bounceRenderer main.cpp ${SOURCES_FILES})

# LIB
# add_library(bounceRenderer ${SOURCES_FILES})
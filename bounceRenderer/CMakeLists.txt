# cmake_minimum_required(VERSION <specify CMake version here>)
project(bounceRenderer)

# C++ version
set(CMAKE_CXX_STANDARD 17)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Setting files
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Creating app
add_executable(bounceRenderer ${SOURCES_FILES})
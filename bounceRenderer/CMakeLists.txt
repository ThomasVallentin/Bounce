# cmake_minimum_required(VERSION <specify CMake version here>)
project(bounceRenderer)

# C++ version
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Setting files
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Creating .exe
add_executable(bounceRenderer main.cpp ${SOURCES_FILES})

# == LIB ======================================================================
project(bounceRendererLib)

# C++ version
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_library(bounceRendererLib ${SOURCES_FILES})
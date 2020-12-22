# cmake_minimum_required(VERSION <specify CMake version here>)
project(bounceRenderer)

# C++ version
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Setting files
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

file(GLOB_RECURSE VCPKG_LIBS C:/REPOSITORIES/vcpkg/installed/x64-windows/lib/*.lib)
set(VCPKG_INCLUDE_DIR C:/REPOSITORIES/vcpkg/installed/x64-windows/include)


message(${SOURCES_FILES})
# Creating .exe
add_executable(bounceRenderer main.cpp ${SOURCES_FILES})

target_include_directories(bounceRenderer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${VCPKG_INCLUDE_DIR})
target_link_libraries(bounceRenderer ${VCPKG_LIBS})


# == LIB ======================================================================
project(bounceRendererLib)

# C++ version
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Output path
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

add_library(bounceRendererLib ${SOURCES_FILES})

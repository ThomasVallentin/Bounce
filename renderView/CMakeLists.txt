# cmake_minimum_required(VERSION <specify CMake version here>)
project(bounceRenderView)

# C++ version
set(CMAKE_CXX_STANDARD 11)

# Ensure OpenGL exists
find_package(OpenGL REQUIRED)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_220
        D:/REPO/Bounce/bounceRenderer/bin/libbounceRendererLib.a
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
)

# Build external libraries
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Getting all cpp and hpp files
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*)

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.2.0/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.3.2/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/external/mingw-std-threads-master
                    D:/REPO/Bounce/bounceRenderer/include)

# Build render view executable
add_executable(bounceRenderView ${SOURCES_FILES})

target_link_libraries(bounceRenderView ${ALL_LIBS} )

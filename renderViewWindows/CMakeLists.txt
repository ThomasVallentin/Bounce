cmake_minimum_required(VERSION 3.15)
project(renderViewWindows)

set(CMAKE_CXX_STANDARD 14)

# Output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Libraries
link_libraries("D:/Windows Kits/10/Lib/10.0.18362.0/um/x64/Gdi32.Lib")
link_libraries(D:/REPOSITORIES/Bounce/bounceRenderer/bin/libbounceRenderer.a)
# link_libraries("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x64/Gdi32.Lib")
# link_libraries("D:/REPO/Bounce/bounceRenderer/bin/libbounceRenderer.a")

# Setting files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(D:/REPOSITORIES/Bounce/bounceRenderer/include)
# include_directories(D:/REPO/Bounce/bounceRenderer/include/)

add_executable(renderViewWindows ${SOURCE_FILES})

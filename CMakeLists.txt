set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake
CACHE STRING "Vcpkg toolchain file")

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/bounceRenderer)

#add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/renderView)

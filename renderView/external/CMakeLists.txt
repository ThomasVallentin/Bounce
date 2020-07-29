include_directories(
		glfw-3.3.2/include/GLFW/
		glew-2.2.0/include/
)

### GLFW ###

add_subdirectory (glfw-3.3.2)

### GLEW ###

set(GLEW_SOURCE glew-2.2.0/src/glew.c)

add_library(GLEW_220 STATIC ${GLEW_SOURCE} ${GLEW_INCLUDE})

target_link_libraries(GLEW_220 ${OPENGL_LIBRARY} ${EXTRA_LIBS})

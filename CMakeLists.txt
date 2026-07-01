cmake_minimum_required(VERSION 3.16)

project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)

add_executable(OpenGLTest
    src/main.cpp
	src/shader.cpp
	src/texture.cpp
	src/camera.cpp
	src/materials/gold.cpp
	src/materials/pearl.cpp
	src/stb_image.cpp
    src_glad/glad.c
)

target_include_directories(OpenGLTest PRIVATE include)

target_link_libraries(OpenGLTest
    glfw
)

target_link_libraries(OpenGLTest
    "-framework OpenGL"
)

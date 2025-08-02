cmake_minimum_required(VERSION 3.10)
project(familiars-engine VERSION 0.1.0 LANGUAGES C CXX)

add_executable(familiars-engine src/main.c)

# GLFW
find_package(glfw3 3.4 REQUIRED)
target_link_libraries(familiars-engine glfw)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(familiars-engine OpenGL::GL)



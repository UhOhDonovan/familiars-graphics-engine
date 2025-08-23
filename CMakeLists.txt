cmake_minimum_required(VERSION 3.10)
project(familiars-engine VERSION 0.1.0 LANGUAGES C CXX)

add_executable(familiars-engine src/main.c src/glad.c src/shader.c src/stb_image.c)

# GLFW
find_package(glfw3 3.4 REQUIRED)
target_link_libraries(familiars-engine glfw)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLAD
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(familiars-engine ${MATH_LIBRARY})
endif()

target_link_libraries(familiars-engine OpenGL::GL)



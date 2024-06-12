cmake_minimum_required(VERSION 3.28)
project(cuber)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_executable(cuber main.cpp
        Cube.cpp
        Cube.h
        Camera.cpp
        Camera.h
        Shader.cpp
        Shader.h
)

target_link_libraries(cuber
        glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}/
        libglew_static
        glm::glm
)
target_include_directories(cuber PUBLIC ${GLEW_INCLUDES})
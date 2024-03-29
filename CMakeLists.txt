cmake_minimum_required(VERSION 3.10)
project(SO2)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(SO2 main.cpp)
target_link_libraries(SO2 ${OPENGL_LIBRARIES} glfw)

cmake_minimum_required(VERSION 3.10)
project(SO2)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(SO2 main.cpp
        raft/Raft.cpp
        raft/Raft.h
        board/Board.cpp
        board/Board.h
        car/Car.cpp
        car/Car.h
        shared/SharedResources.h
)
target_link_libraries(SO2 ${OPENGL_LIBRARIES} glfw)

cmake_minimum_required(VERSION 3.19)
project(task_name)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_executable(task_name main.cpp src/Differentiator.cpp src/FileManager.cpp src/BinaryIterator.cpp)
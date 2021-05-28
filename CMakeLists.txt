cmake_minimum_required(VERSION 3.19)
project(Graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graph main.cpp Graph.cpp Graph.h GraphMatrix.cpp GraphMatrix.h GraphList.cpp GraphList.h Utility/Utility.h GraphExamples.cpp GraphExamples.h)
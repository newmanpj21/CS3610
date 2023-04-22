cmake_minimum_required(VERSION 3.25)
project(Project5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project5
        ./source/main.cpp source/weightedGraphType.cpp source/weightedGraphType.h)
cmake_minimum_required(VERSION 3.8)
project(myqueue CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(myqueue STATIC queue.cpp queue.h)

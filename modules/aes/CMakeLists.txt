cmake_minimum_required(VERSION 3.8)
project(aes C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(aes STATIC aes.cpp aes.h)

target_include_directories(aes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

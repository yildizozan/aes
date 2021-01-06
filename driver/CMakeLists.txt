cmake_minimum_required(VERSION 3.8)
project(driver C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(driver main.cpp)

target_link_libraries(driver PRIVATE aes)
cmake_minimum_required(VERSION 3.8)
project(aes C)

set(CMAKE_C_STANDARD 99)

add_executable(md5 main.c)

install (TARGETS md5 RUNTIME DESTINATION bin)
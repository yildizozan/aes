cmake_minimum_required(VERSION 3.8)
project(aes)

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(aesctl)
add_subdirectory(driver)

add_subdirectory(modules)

add_subdirectory(third_party)
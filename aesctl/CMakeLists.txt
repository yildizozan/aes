cmake_minimum_required(VERSION 3.8)
project(aes CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(aesctl main.cpp)

target_link_libraries(aesctl PRIVATE aes gflags::gflags)

install (TARGETS aesctl RUNTIME DESTINATION bin)
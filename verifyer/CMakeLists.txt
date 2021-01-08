cmake_minimum_required(VERSION 3.8)
project(aes CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(verifyer main.cpp)

target_link_libraries(verifyer PRIVATE aes gflags::gflags)

install (TARGETS verifyer RUNTIME DESTINATION bin)
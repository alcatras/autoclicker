cmake_minimum_required(VERSION 3.3)
project(autoclicker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE main.cpp devices/utils devices/VirtualDevice devices/VirtualMouse)

add_executable(autoclicker ${SOURCE})
cmake_minimum_required(VERSION 2.8.4)
project(lil_vm)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c vm.c vm.h)
add_executable(lil_vm ${SOURCE_FILES})

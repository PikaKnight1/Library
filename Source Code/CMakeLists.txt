cmake_minimum_required(VERSION 3.17)
project(NowaBiblioteka)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(NowaBiblioteka main.cpp book.cpp book.h fileOperations.h fileOperations.cpp menu.h menu.cpp)
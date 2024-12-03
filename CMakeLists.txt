cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 23)
project(LibrarySystem LANGUAGES CXX)

set(SOURCES main.cpp)
include_directories(./include)

add_executable(LibrarySystem main.cpp src/Models/Book.cpp)
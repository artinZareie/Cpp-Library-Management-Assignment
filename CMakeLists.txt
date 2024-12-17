cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 23)
project(LibrarySystem LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)

set(SOURCES main.cpp)
include_directories(./include)

add_executable(
    LibrarySystem 
    main.cpp 
    src/Models/Book.cpp 
    # src/Models/DatabaseDriver.cpp
    # src/Models/FileDbDriver.cpp 
    src/Models/User.cpp
    src/Models/Library.cpp
)

target_compile_options(LibrarySystem PUBLIC -fsanitize=undefined)
target_link_options(LibrarySystem PUBLIC -fsanitize=undefined)
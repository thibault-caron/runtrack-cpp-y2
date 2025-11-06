cmake_minimum_required(VERSION 3.10)

project(RUNTRACK_CPP_Y2 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable from source files
add_executable(hello.exe
    src/day01/main.cpp
    src/day01/day01.cpp)

add_executable(day02.exe
    src/day02/day02.cpp
    src/day02/terrestrial.cpp
    src/day02/aquatic.cpp
    src/day02/penguin.cpp
    )
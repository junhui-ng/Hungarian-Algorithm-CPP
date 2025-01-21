cmake_minimum_required(VERSION 3.10)
project(HungarianAlgorithm)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Specify the path to the header files
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/hungarian.cpp
)

# Add an executable target to build
add_executable(hungarian_algo ${SOURCES})

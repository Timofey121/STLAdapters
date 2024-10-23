cmake_minimum_required(VERSION 3.20)
project(STLAdapters)

set(CMAKE_CXX_STANDARD 20)

add_executable(STLAdapters
        bin/main.cpp
        lib/ranges.h
        lib/Adapters/Transform.h
        lib/Adapters/Filter.h
        lib/Adapters/Take.h
        lib/Adapters/Drop.h
        lib/Adapters/Reverse.h
        lib/Adapters/Keys.h
        lib/Adapters/Values.h
        lib/Adapters/Concept.h
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-Wpedantic")

target_include_directories(STLAdapters PRIVATE bin lib)

enable_testing()
add_subdirectory(tests)
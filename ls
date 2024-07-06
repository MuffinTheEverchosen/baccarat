cmake_minimum_required(VERSION 3.15)

project(Course)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(main ${SOURCES})


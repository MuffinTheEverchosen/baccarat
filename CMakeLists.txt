cmake_minimum_required(VERSION 3.15)

project(Baccart)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(game ${SOURCES})


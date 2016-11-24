cmake_minimum_required(VERSION 3.6)
project(Threaded_Tree)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=iso9899:1990 -pedantic") # Original ANSI C standard

set(SOURCE_FILES ThreadedTree.c)
add_executable(Threaded_Tree ${SOURCE_FILES})
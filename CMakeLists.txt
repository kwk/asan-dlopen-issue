cmake_minimum_required(VERSION 2.8)
project(asan-dlopen-issue C)

set(CMAKE_C_FLAGS "-g")

# Build library that must be loaded with dlopen
add_library(mylib MODULE mylib.c mylib.h)

# Build executable that loads the library with dlopen
add_executable(myprog myprog.c blacklist.txt)
set_target_properties(myprog PROPERTIES COMPILE_FLAGS "-fsanitize=address -fsanitize-blacklist=${CMAKE_SOURCE_DIR}/blacklist.txt")
set_target_properties(myprog PROPERTIES LINK_FLAGS    "-fsanitize=address -fsanitize-blacklist=${CMAKE_SOURCE_DIR}/blacklist.txt")
target_link_libraries(myprog)

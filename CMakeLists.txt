cmake_minimum_required(VERSION 2.8)
project(asan-dlopen-issue C)

set(CMAKE_C_FLAGS "-g")

# Build library that must be loaded with dlopen
add_library(mylib MODULE mylib.c mylib.h)

# Build executable that loads the library with dlopen
add_executable(myprog myprog.c suppressions.txt)
set_target_properties(myprog PROPERTIES COMPILE_FLAGS "-fsanitize=leak -fno-omit-frame-pointer")
set_target_properties(myprog PROPERTIES LINK_FLAGS    "-fsanitize=leak -fno-omit-frame-pointer")
target_link_libraries(myprog)

# Create run file 
configure_file(run.sh.in run.sh)

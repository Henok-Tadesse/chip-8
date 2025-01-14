cmake_minimum_required(VERSION 3.10)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

#Add the library
add_library(chip8Def SHARED lib/chip-8.cpp include/Chip-8.h)

target_compile_options(chip8Def PRIVATE -g)

add_executable(Chip8 main.cpp)

#Link the executable with the library
target_link_libraries(Chip8 chip8Def)

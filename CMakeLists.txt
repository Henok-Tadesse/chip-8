cmake_minimum_required(VERSION 3.10)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# Set the prefix path for SDL2 and SDL2_image
set(CMAKE_PREFIX_PATH "/Library/Frameworks" ${CMAKE_PREFIX_PATH})

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add include directories for your project
include_directories(include)

# Create the chip8Def shared library
add_library(chip8Def SHARED lib/chip-8.cpp include/Chip-8.h)

# Add compile options for the shared library
target_compile_options(chip8Def PRIVATE -g)

# Link chip8Def with SDL2 and SDL2_image (if needed)
target_link_libraries(chip8Def PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

# Create the executable for your project
add_executable(Chip8 main.cpp)

# Add compile options for the executable
target_compile_options(Chip8 PRIVATE
    -ggdb3
    -O0
    -Wall
)

# Link the executable with the shared library and SDL2 libraries
target_link_libraries(Chip8 PRIVATE chip8Def)

# Link SDL2 and SDL2_image
target_link_libraries(Chip8 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

# Specify frameworks for macOS
if(APPLE)
    target_link_libraries(Chip8 PRIVATE
        "-framework SDL2"
        "-framework SDL2_image"
    )
    link_directories("/Library/Frameworks")
endif()

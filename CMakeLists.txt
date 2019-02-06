cmake_minimum_required(VERSION 3.0)
project(base C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(base "${SOURCE}" src/globals_structs_const.h src/map_g.c src/map_g.h src/init.c src/init.h)

include_directories("/usr/include/SDL2")
target_link_libraries(base m SDL2 SDL2_gfx)
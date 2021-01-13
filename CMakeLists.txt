cmake_minimum_required(VERSION 3.10)
project(Game)

# autocomplete with clang & linting in vim (needed by YCM plugin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# build program
add_executable(game game.cpp)

# link to sdl2
target_link_libraries(game ${SDL2_LIBRARIES})

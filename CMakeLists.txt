cmake_minimum_required(VERSION 3.10)
project(Game)

# autocomplete with YCM & debug with gdb
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")

# copy assets folder
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# find sdl2-gfx library in /usr/local/lib/
list(APPEND CMAKE_PREFIX_PATH "/usr/local")
find_library(LIB_SDL2_GFX SDL2_gfx)

# program requires sdl2 & its extensions
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image SDL2_ttf SDL2_mixer)
file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(game ${SRC})
target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIRS} include)
target_link_libraries(game ${SDL2_LIBRARIES} ${LIB_SDL2_GFX})

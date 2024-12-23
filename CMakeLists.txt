cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE sources include/*.hpp src/*.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

project(battleship)
add_executable(battleship)
target_sources(battleship PRIVATE ${sources})
target_include_directories(battleship PRIVATE include)
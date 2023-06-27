cmake_minimum_required(VERSION 3.22)
project(DiscretePlanning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package (SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_library(gridworld grid_world.h grid_world.cpp)
target_link_libraries(gridworld 
                        sfml-audio 
                        sfml-graphics 
                        sfml-network 
                        sfml-system
                        sfml-window)

add_library(algo forward_search.h forward_search.cpp)
target_link_libraries(algo) 


add_executable(test test.cpp)
target_link_libraries(test gridworld algo)
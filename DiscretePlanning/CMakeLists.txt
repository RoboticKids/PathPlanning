cmake_minimum_required(VERSION 3.22)
project(DiscretePlanning)

add_compile_options(-std=c++17)


find_package (SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

#we add the executable of the program
add_executable (grid_world grid_world.cpp)
target_link_libraries(grid_world 
                        PRIVATE 
                            sfml-audio 
                            sfml-graphics 
                            sfml-network 
                            sfml-system
                            sfml-window)
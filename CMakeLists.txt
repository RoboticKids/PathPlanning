cmake_minimum_required(VERSION 3.24.1)

project(GridTest)

# Build executable
add_executable(${PROJECT_NAME} grid_test.cpp)

# Build a library
add_subdirectory(world)

# Link into executable before build
target_link_libraries(${PROJECT_NAME} world)
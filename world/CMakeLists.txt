project(world)

add_library(${PROJECT_NAME} grid.cpp)

target_link_libraries(${PROJECT_NAME} -lsfml-graphics -lsfml-window -lsfml-system)
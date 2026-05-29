cmake_minimum_required(VERSION 4.2)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(conway)
add_executable(conway main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(conway PRIVATE OpenGL::OpenGL)
target_link_libraries(conway PRIVATE ${GLUT_LIBRARIES})

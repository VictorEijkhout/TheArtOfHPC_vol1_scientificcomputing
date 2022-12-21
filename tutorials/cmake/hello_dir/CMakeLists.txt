cmake_minimum_required(VERSION 3.0.0)
project(hello_world_project)

include_directories(include)
file(GLOB SOURCES "*/*.c")
file(GLOB HEADERS "*/*.h")
add_executable(hello_world hello.c ${SOURCES} )

install(TARGETS hello_world DESTINATION "./")

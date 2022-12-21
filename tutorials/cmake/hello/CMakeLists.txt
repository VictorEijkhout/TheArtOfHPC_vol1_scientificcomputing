cmake_minimum_required(VERSION 3.0.0)
project(hello_world_project)
add_executable(hello_world hello.c)
install(TARGETS hello_world DESTINATION "./")

# cmake file inspired by
# https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

cmake_minimum_required(VERSION 3.5)
project(arias_demo VERSION 1.0.0 LANGUAGES CXX)

add_library(arias_demo src/utils.cpp)

target_include_directories(arias_demo
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(arias_demo PRIVATE -Werror)
target_compile_features(arias_demo PRIVATE cxx_std_17)

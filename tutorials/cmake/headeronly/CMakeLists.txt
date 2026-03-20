cmake_minimum_required( VERSION 3.14 )
project( headeronly VERSION 1.0 )

add_library( header_only_lib INTERFACE )
target_include_directories(header_only_lib INTERFACE
    include
)
## also possible:
##    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
##    $<INSTALL_INTERFACE:include>

add_executable( program test/program.cpp)
target_include_directories( program PRIVATE include )
target_link_libraries( program PRIVATE header_only_lib)

install( TARGETS program DESTINATION test )
install( DIRECTORY include DESTINATION . )


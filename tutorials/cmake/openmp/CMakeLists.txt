cmake_minimum_required( VERSION 3.12 )
project( ompprogram VERSION 1.0 )

find_package(OpenMP)
if(OpenMP_CXX_FOUND) 
else()
	message( FATAL_ERROR "Could not find OpenMP" )
endif()

add_executable( program program.cxx )
target_link_libraries( program
    PUBLIC OpenMP::OpenMP_CXX)

install( TARGETS program DESTINATION . )

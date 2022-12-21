cmake_minimum_required( VERSION 3.12 )
project( cmakeprogram VERSION 1.0 )

add_executable( program program.cxx )
add_library( auxlib STATIC
	     aux1.cxx aux2.cxx aux.h )
target_link_libraries( program PRIVATE auxlib )
install( TARGETS program DESTINATION . )

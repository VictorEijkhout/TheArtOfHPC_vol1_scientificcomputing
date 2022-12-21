cmake_minimum_required( VERSION 3.12 )
project( cmakeprogram VERSION 1.0 )

add_executable( program program.cxx )
add_library( auxlib 
	     aux.cxx aux.h )
target_link_libraries( program PUBLIC auxlib )
install( TARGETS program auxlib DESTINATION . )

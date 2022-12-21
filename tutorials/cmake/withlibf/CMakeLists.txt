cmake_minimum_required( VERSION 3.12 )
project( cmakeprogram VERSION 1.0 )
enable_language( Fortran )

add_executable( program program.F90 )
add_library( auxlib 
	     aux.F90 )
target_link_libraries( program PUBLIC auxlib )
install( TARGETS program auxlib DESTINATION . )

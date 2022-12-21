cmake_minimum_required( VERSION 3.12 )
project( cmakegood1b VERSION 1.0 )

add_executable( good1b good1b.cxx )
add_library( sayhello SHARED
	     g1b.cxx g1b.h )
target_link_libraries( good1b PRIVATE sayhello )
install( TARGETS good1b DESTINATION . )

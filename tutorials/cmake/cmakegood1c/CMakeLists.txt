cmake_minimum_required( VERSION 3.12 )
project( cmakegood1c VERSION 1.0 )

add_subdirectory( helloproject )
add_subdirectory( program )
install( TARGETS good1b DESTINATION bin )

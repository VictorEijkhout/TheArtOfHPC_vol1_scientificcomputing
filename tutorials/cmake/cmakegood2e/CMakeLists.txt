cmake_minimum_required( VERSION 3.12 )
project( cmakegood2e VERSION 1.0 )

add_subdirectory( program )
add_subdirectory( library )

install( TARGETS good1a DESTINATION . )

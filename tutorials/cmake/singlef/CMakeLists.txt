cmake_minimum_required( VERSION 3.13 )
project( singleprogram VERSION 1.0 )
enable_language( Fortran )

add_executable( program program.F90 )
install( TARGETS program DESTINATION . )

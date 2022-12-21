cmake_minimum_required( VERSION 3.12 )
project( cmakegood1a VERSION 1.0 )

add_executable( good1a good1a.cxx )
install( TARGETS good1a DESTINATION . )

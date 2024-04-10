cmake_minimum_required( VERSION 3.12 )
project( singleprogram VERSION 1.0 )

add_executable( program )
target_sources( program PRIVATE program.cxx )
install( TARGETS program DESTINATION . )

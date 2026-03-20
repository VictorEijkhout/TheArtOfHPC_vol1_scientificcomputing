cmake_minimum_required( VERSION 3.13 )
project( fmtlibmod VERSION 1.0 )

add_executable( program program.cxx )
find_package( fmt )
target_link_libraries( program PUBLIC fmt::fmt )

install( TARGETS program DESTINATION . )

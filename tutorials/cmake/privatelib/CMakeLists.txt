cmake_minimum_required( VERSION 3.12 )
project( cmakeprogram VERSION 1.0 )

add_executable( program )
target_sources( program PRIVATE program.cxx )

add_library( auxlib )
target_sources( auxlib PRIVATE aux.cxx aux.h )

target_link_libraries( program PRIVATE auxlib )

install( TARGETS program DESTINATION . )

cmake_minimum_required( VERSION 3.13 )
project( cmakeprogram VERSION 1.0 )

add_executable( program )
target_sources( program PRIVATE program.cxx )

add_library( auxlib STATIC )
target_include_directories( program PRIVATE lib )
target_sources( auxlib PRIVATE
    lib/aux1.cxx lib/aux2.cxx lib/aux.h )

target_link_libraries( program PRIVATE auxlib )
install( TARGETS program DESTINATION . )

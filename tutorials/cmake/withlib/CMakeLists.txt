cmake_minimum_required( VERSION 3.12 )
project( cmakeprogram VERSION 1.0 )

add_executable( program )
target_sources( program PRIVATE program.cxx )

add_library( auxlib STATIC )
target_sources( auxlib PRIVATE lib/aux.cxx lib/aux.h )

target_link_libraries( program PUBLIC auxlib )
target_include_directories( program PRIVATE lib )

install( TARGETS program DESTINATION bin )
install( TARGETS auxlib DESTINATION lib )
install( FILES lib/aux.h DESTINATION include )

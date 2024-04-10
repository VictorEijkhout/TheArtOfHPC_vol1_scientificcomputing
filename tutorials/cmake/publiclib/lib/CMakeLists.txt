cmake_minimum_required( VERSION 3.14 )
project( auxlib )

add_library( auxlib SHARED )
target_sources( auxlib PRIVATE aux.cxx aux.h )
target_include_directories(
    auxlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
install( TARGETS auxlib DESTINATION lib )
install( FILES aux.h DESTINATION include )

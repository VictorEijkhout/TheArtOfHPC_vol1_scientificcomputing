cmake_minimum_required( VERSION 3.14 )
project( cmakeprogram VERSION 1.0 )

set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

add_executable( program program.cxx )
add_subdirectory( lib )
target_include_directories(
	auxlib PUBLIC "${CMAKE_CURRECT_SOURCE_DIR}" )
target_link_libraries(
	program PUBLIC auxlib )

install( TARGETS program DESTINATION . )

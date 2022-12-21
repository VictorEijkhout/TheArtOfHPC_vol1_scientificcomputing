cmake_minimum_required( VERSION 3.12 )
project( pkgconfiglib VERSION 1.0 )

# with environment variables
# set( AUX_INCLUDE_DIR $ENV{TACC_AUX_INC} )
# set( AUX_LIBRARY_DIR $ENV{TACC_AUX_LIB} )

# with cmake -D options
option( AUX_INCLUDE_DIR "include dir for auxlib" )
option( AUX_LIBRARY_DIR   "lib dir for auxlib" )

add_executable( program program.cxx )
target_include_directories(
	program PUBLIC
	${AUX_INCLUDE_DIR} )
target_link_libraries( program PUBLIC auxlib )
target_link_directories(
	program PUBLIC
	${AUX_LIBRARY_DIR} )
install( TARGETS program DESTINATION . )

cmake_minimum_required( VERSION 3.12 )
project( pkgconfiglib VERSION 1.0 )

## https://www.intel.com/content/www/us/en/develop/documentation/onemkl-linux-developer-guide/top/getting-started/cmake-config-for-onemkl.html

find_package( MKL CONFIG REQUIRED )

add_executable( program program.cxx )
target_compile_options(
	program PUBLIC
	$<TARGET_PROPERTY:MKL::MKL,INTERFACE_COMPILE_OPTIONS> )
target_include_directories(
	program PUBLIC
	$<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES> )
target_link_libraries(
	program PUBLIC 
	$<LINK_ONLY:MKL::MKL>)

install( TARGETS program DESTINATION . )

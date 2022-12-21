cmake_minimum_required( VERSION 3.12 )
project( pkgconfiglib VERSION 1.0 )

find_package( PkgConfig REQUIRED )
pkg_check_modules( OPTS REQUIRED cxxopts )
message( STATUS "cxxopts includes: ${OPTS_INCLUDE_DIRS}" )

add_executable( program program.cxx )
target_include_directories(
	program PUBLIC
	${OPTS_INCLUDE_DIRS})

install( TARGETS program DESTINATION . )

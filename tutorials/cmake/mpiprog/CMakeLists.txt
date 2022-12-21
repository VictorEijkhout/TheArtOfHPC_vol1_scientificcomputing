cmake_minimum_required( VERSION 3.12 )
project( pkgconfiglib VERSION 1.0 )

find_package( PkgConfig REQUIRED )
pkg_check_modules( MPI REQUIRED mpich )
message( STATUS "mpi includes: ${MPI_INCLUDE_DIRS}" )

add_executable( program program.cxx )
target_include_directories(
	program PUBLIC
	${MPI_INCLUDE_DIRS} )
target_link_directories(
	program PUBLIC
	${MPI_LIBRARY_DIRS} )
target_link_libraries(
	program PUBLIC mpich )

install( TARGETS program DESTINATION . )

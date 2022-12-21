cmake_minimum_required( VERSION 3.12 )
project( pkgconfiglib VERSION 1.0 )

find_package( PkgConfig REQUIRED )
pkg_check_modules( PETSC REQUIRED petsc )
message( STATUS "PETSc includes: ${PETSC_INCLUDE_DIRS}" )
message( STATUS "PETSc libraries: ${PETSC_LIBRARY_DIRS}" )

add_executable( program program.cxx )
target_include_directories(
	program PUBLIC
	${PETSC_INCLUDE_DIRS} )
target_link_directories(
	program PUBLIC
	${PETSC_LIBRARY_DIRS} )
target_link_libraries(
	program PUBLIC petsc )

install( TARGETS program DESTINATION . )

project( prolib )

add_library( prolib SHARED aux.cxx aux.h )
target_include_directories(
	prolib PUBLIC
	${FMTLIB_INCLUDE_DIRS})
target_link_directories(
	prolib PUBLIC
	${FMTLIB_LIBRARY_DIRS})
target_link_libraries(
	prolib PUBLIC fmt )

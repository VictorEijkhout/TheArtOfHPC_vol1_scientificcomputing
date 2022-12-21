project( program2e VERSION 1.0 )

add_executable
	( do2e do2e.cxx )

target_link_libraries
	( do2e PRIVATE lib2e )



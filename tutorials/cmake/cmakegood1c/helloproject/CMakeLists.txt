add_library( sayhello SHARED
	     src/hello/g1c.cxx
	     src/hello/g1c.h )

target_include_directories( sayhello PUBLIC
			    "${CMAKE_CURRENT_SOURCE_DIR}/src" )
target_compile_definitions( sayhello PUBLIC
			    GOOD_VERSION="1c" )

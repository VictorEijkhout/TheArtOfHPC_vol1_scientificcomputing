project( program2e VERSION 1.0 )

add_library
	( lib2e
	  src/good2e.cxx
	  src/good2e.hpp
	  )

target_include_directories
	( lib2e
	  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
	  )

target_compile_definitions
	( lib2e
	  PUBLIC LIB2E_VERSION=2.14
	  )


cmake_minimum_required( VERSION 3.12 )
project( singleprogram VERSION 1.0 )

add_executable( program program.cxx )
#target_compile_features( program INTERFACE cxx_std_20 )
set_target_properties( program PROPERTIES CXX_STANDARD 20 )

install( TARGETS program DESTINATION . )

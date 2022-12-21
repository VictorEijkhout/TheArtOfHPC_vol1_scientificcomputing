cmake_minimum_required( VERSION 3.12 )
project( cmakegood2b VERSION 1.0 )

message( NOTICE "Making project ${PROJECT_NAME}, version ${PROJECT_VERSION}")

message( NOTICE "commandline variable: ${MYVAR}" )

if ( MYVAR MATCHES "value$" )
    message( NOTICE "Variable ended in 'value'" )
else()
    message( NOTICE "Variable was otherwise" )
endif()


add_executable( good2b good2b.cxx )
install( TARGETS good2b DESTINATION . )

cmake_minimum_required( VERSION 3.12 )
project( cmakegood2a VERSION 1.0 )

message( NOTICE "Making project ${PROJECT_NAME}, version ${PROJECT_VERSION}")


add_executable( good1a good1a.cxx )
install( TARGETS good1a DESTINATION . )

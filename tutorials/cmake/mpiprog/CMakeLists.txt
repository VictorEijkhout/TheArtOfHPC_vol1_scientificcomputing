cmake_minimum_required( VERSION 3.12 )
project( cxxprogram VERSION 1.0 )

add_executable( ${PROJECT_NAME} ${PROJECT_NAME}.cxx )
find_package( MPI )
target_include_directories(
	${PROJECT_NAME} PUBLIC
	${MPI_C_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(
	${PROJECT_NAME} PUBLIC 
	${MPI_C_LIBRARIES} )

install( TARGETS ${PROJECT_NAME} DESTINATION . )

function(print_variables)
	message(STATUS "Var: {PROJECT_NAME}, value ${PROJECT_NAME}")
	message(STATUS "Var: {PROJECT_VERSION}, value ${PROJECT_VERSION}")
	message(STATUS "Var: {PROJECT_SOURCE_DIR}, value ${PROJECT_SOURCE_DIR}")
	message(STATUS "Var: {PROJECT_BINARY_DIR}, value ${PROJECT_BINARY_DIR}")
	message(STATUS "Var: {CMAKE_SOURCE_DIR}, value ${CMAKE_SOURCE_DIR}")
	message(STATUS "Var: {CMAKE_BINARY_DIR}, value ${CMAKE_BINARY_DIR}")
	message(STATUS "Var: {CMAKE_CURRENT_SOURCE_DIR}, value ${CMAKE_CURRENT_SOURCE_DIR}")
	message(STATUS "Var: {CMAKE_CURRENT_BINARY_DIR}, value ${CMAKE_CURRENT_BINARY_DIR}")
	message(STATUS "Var: {CMAKE_CURRENT_LIST_FILE}, value ${CMAKE_CURRENT_LIST_FILE}")
	message(STATUS "Var: {CMAKE_CURRENT_LIST_DIR}, value ${CMAKE_CURRENT_LIST_DIR}")
endfunction()

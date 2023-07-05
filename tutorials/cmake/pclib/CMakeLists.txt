cmake_minimum_required( VERSION 3.14 )
project( pclib VERSION 1.0 )

set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

add_executable( program program.cxx )
add_subdirectory( lib )
target_include_directories(
	auxlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
target_link_libraries(
	program PUBLIC auxlib )

install( TARGETS program DESTINATION . EXPORT installroot )

# generate pc file for pkg-config
set( libtarget auxlib )
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    @ONLY)
  
# https://discourse.cmake.org/t/how-to-generate-pc-pkg-config-file-supporting-prefix-of-the-cmake-install/4109/7

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION share/pkgconfig
)

# kinda sorta. This install .cmake files.
## install( TARGETS program DESTINATION . EXPORT installroot )
## install( EXPORT installroot DESTINATION lib/pkgconfig )


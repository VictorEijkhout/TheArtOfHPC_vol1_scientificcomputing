cmake_minimum_required(VERSION 3.13)
enable_testing()
project(oneMKL_Example LANGUAGES C)
find_package(MKL CONFIG REQUIRED)
#message(STATUS "${MKL_IMPORTED_TARGETS}") #Provides available list of targets based on input
add_executable(myapp app.c)

target_compile_options(myapp PUBLIC $<TARGET_PROPERTY:MKL::MKL_C,INTERFACE_COMPILE_OPTIONS>)
target_include_directories(myapp PUBLIC $<TARGET_PROPERTY:MKL::MKL_C,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(myapp PUBLIC $<LINK_ONLY:MKL::MKL_C>)

add_test(NAME mytest COMMAND myapp)
if(MKL_ENV)
  set_tests_properties(mytest PROPERTIES ENVIRONMENT "${MKL_ENV}")
endif()

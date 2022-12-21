cmake_minimum_required(VERSION 3.14)
project( hellof VERSION 0.1.0 LANGUAGES C CXX)

#
# declare the support library
# and the location of the header files
#
add_library(funlib
  funlib/fun.cxx
  include/fun.h
)
target_include_directories(funlib PUBLIC include)

target_compile_options(funlib PRIVATE -O2 )

#
# declare the executable
# and the libraries it needs to build
#
add_executable(hello
  hello.cxx
)
# target_include_directories(hello
#   PUBLIC
#   include
# )
target_link_libraries(hello
  PRIVATE
  funlib
)

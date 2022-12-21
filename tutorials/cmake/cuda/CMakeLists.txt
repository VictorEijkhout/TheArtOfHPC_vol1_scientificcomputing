cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(cmake_and_cuda)

enable_language(CUDA)
if ( NOT DEFINED CMAKE_CUDA_ARCHITECTURES )
  set ( CMAKE_CUDA_ARCHITECTURES 70 )
endif()

add_executable(main main.cxx)
add_subdirectory(kernels)

# set_property(TARGET main 
#              PROPERTY CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(main kernels)


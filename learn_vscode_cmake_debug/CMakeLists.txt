project(hello)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread" )

set(src_list hello.cpp)
message(STATUS "this is binary dir " ${PROJECT_BINARY_DIR})
message(STATUS "this is source dir " ${PROJECT_SOURCE_DIR})
add_executable(hellohello ${src_list})
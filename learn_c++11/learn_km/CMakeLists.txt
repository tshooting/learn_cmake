project(learn_km)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread" )

# set(src_list GraphMatch_KM.cpp)
add_executable(graph_matcher graph_matcher.cpp)

add_executable(GraphMatch GraphMatch_KM.cpp)
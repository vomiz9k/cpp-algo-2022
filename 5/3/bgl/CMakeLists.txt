cmake_minimum_required(VERSION 3.16)

project(mst_edges)

# find_package(Boost 1.45.0 COMPONENTS *boost libraries here*)
FIND_PACKAGE(Boost COMPONENTS program_options graph REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME ON)



# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     add_executable(progname file1.cxx file2.cxx)
#     target_link_libraries(progname ${Boost_LIBRARIES})
# endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(
    mst_edges
    ${mst_edges_SOURCE_DIR}/main.cpp
)

set_target_properties(mst_edges PROPERTIES OUTPUT_NAME "mst_edges.out")

TARGET_LINK_LIBRARIES(mst_edges ${Boost_LIBRARIES})
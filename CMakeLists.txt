cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
include(AppendCompilerFlags)

project(k3-tree_sdsl)
set(PROJECT_VENDOR "Fernando Silva Coira")
set(CMAKE_PROJECT_NAME "k3-tree_sdsl")
set(PROJECT_CONTACT "fernando.silva@udc.es")
set(CMAKE_INSTALL_PREFIX /home/fernando/software)

set(CMAKE_BUILD_TYPE "Release")

# Set output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# C++11 compiler Check
if(NOT CMAKE_CXX_COMPILER_VERSION) # work around for cmake versions smaller than 2.8.10
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE CMAKE_CXX_COMPILER_VERSION)
endif()
if(CMAKE_CXX_COMPILER MATCHES ".*clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()
if( (CMAKE_COMPILER_IS_GNUCXX AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.7) OR
(CMAKE_COMPILER_IS_CLANGXX AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.2))
    message(FATAL_ERROR "Your C++ compiler does not support C++11. Please install g++ 4.7 (or greater) or clang 3.2 (or greater)")
else()
    message(STATUS "Compiler is recent enough to support C++11.")
endif()
if( CMAKE_COMPILER_IS_GNUCXX )
    append_cxx_compiler_flags("-std=c++11 -Wall -Wextra " "GCC" CMAKE_CXX_FLAGS)
    append_cxx_compiler_flags("-msse4.2 -O3 -ffast-math -funroll-loops -fno-omit-frame-pointer -g" "GCC" CMAKE_CXX_FLAGS_RELEASE)
else()
    append_cxx_compiler_flags("-std=c++11" "CLANG" CMAKE_CXX_FLAGS)
    append_cxx_compiler_flags("-stdlib=libc++" "CLANG" CMAKE_CXX_FLAGS)
    append_cxx_compiler_flags("-msse4.2 -O3  -ffast-math -funroll-loops -DNDEBUG" "CLANG" CMAKE_CXX_FLAGS_RELEASE)
endif()
include(CheckSSE)
FindSSE ()
if( SSE4_2_FOUND )
    if( CMAKE_COMPILER_IS_GNUCXX )
        append_cxx_compiler_flags("-msse4.2" "GCC" CMAKE_CXX_FLAGS)
    else()
        append_cxx_compiler_flags("-msse4.2" "CLANG" CMAKE_CXX_FLAGS)
    endif()
    message(STATUS "CPU does support SSE4.2.")
else()
    message(STATUS "CPU does NOT support SSE4.2")
endif()

add_subdirectory(external/sdsl-lite)
add_subdirectory(external/LASlib)

include_directories("${PROJECT_SOURCE_DIR}/external/googletest/include"
        ${CMAKE_HOME_DIRECTORY}/include
        ${CMAKE_BINARY_DIR}/external/sdsl-lite/include
        ${CMAKE_BINARY_DIR}/external/sdsl-lite/external/libdivsufsort/include/
        ${CMAKE_HOME_DIRECTORY}/external/googletest/include
        ${CMAKE_HOME_DIRECTORY}/external/sdsl-lite/external/FastPFor/headers/
        ${PROJECT_SOURCE_DIR}/external/
        ${PROJECT_SOURCE_DIR}/external/LASlib/
        ${STXXL_INCLUDE_DIRS}
        ${gtest_SOURCE_DIR}/include
        )

# Set source files
set(SOURCES
        include/others/k3_tree_no_opt.hpp
        include/others/k3_tree_LIDAR.hpp
        include/others/conceptual_node.hpp
        include/k3_tree.hpp
        include/k3_tree_points.hpp
        include/k3_tree_level.hpp
        include/LIDAR/k3_tree_LIDAR.hpp
        include/LIDAR/k3_tree_LIDAR_points.hpp
        include/k3_tree_base.hpp
    )


############
#  ENCODE  #
############

# Encode
add_executable(k3_tree_encode src/k3_tree_encode.cpp ${SOURCES} )
target_link_libraries(k3_tree_encode sdsl divsufsort divsufsort64)

# Encode LIDAR
add_executable(k3_tree_LIDAR_encode src/LIDAR/k3_tree_LIDAR_encode.cpp ${SOURCES} )
target_link_libraries(k3_tree_LIDAR_encode sdsl divsufsort divsufsort64 las)


############
# QUERIES  #
############

# Query GET
add_executable(k3_tree_get src/k3_tree_get.cpp ${SOURCES} )
target_link_libraries(k3_tree_get sdsl divsufsort divsufsort64 las)

# Query Thresh
add_executable(k3_tree_thresh src/map_algebra/threshold.cpp ${SOURCES} )
target_link_libraries(k3_tree_thresh sdsl divsufsort divsufsort64 las)

# Query GET REGION
add_executable(k3_tree_get_region src/k3_tree_get_region.cpp ${SOURCES} )
target_link_libraries(k3_tree_get_region sdsl divsufsort divsufsort64 las)

# Query GET LIDAR Attr
add_executable(k3_tree_LIDAR_get src/LIDAR/k3_tree_LIDAR_get.cpp ${SOURCES} )
target_link_libraries(k3_tree_LIDAR_get sdsl divsufsort divsufsort64 las)


# Query GET REGION LIDAR Attr
add_executable(k3_tree_LIDAR_get_region src/LIDAR/k3_tree_LIDAR_get_region.cpp ${SOURCES} )
target_link_libraries(k3_tree_LIDAR_get_region sdsl divsufsort divsufsort64 las)

# Query GET REGION + intensity LIDAR Attr
add_executable(k3_tree_LIDAR_get_region_int src/LIDAR/k3_tree_LIDAR_get_region_int.cpp ${SOURCES} )
target_link_libraries(k3_tree_LIDAR_get_region_int sdsl divsufsort divsufsort64 las)

############
#   UTIL   #
############

# Create random data
add_executable(create_random_data src/test/create_random_file.cpp include/util/file.hpp)
target_link_libraries(create_random_data sdsl divsufsort divsufsort64)

# Create get queries
add_executable(create_get_queries src/test/create_get_queries.cpp ${SOURCES})
target_link_libraries(create_get_queries sdsl divsufsort divsufsort64 las)

# Create region queries
add_executable(create_get_region_queries src/test/create_get_region_queries.cpp ${SOURCES})
target_link_libraries(create_get_region_queries sdsl divsufsort divsufsort64 las)

############
#   TEST   #
############

# TEST - Get region
add_executable(test_get_region src/test/test_get_region.cpp ${SOURCES})
target_link_libraries(test_get_region sdsl divsufsort divsufsort64)

# TEST - k3-tree LIDAR
add_executable(test_k3_tree_LIDAR src/test/test_k3_tree_LIDAR.cpp ${SOURCES})
target_link_libraries(test_k3_tree_LIDAR sdsl divsufsort divsufsort64 las)

cmake_minimum_required(VERSION 2.8.4)
project (LASzip)
set(PROJECT_VENDOR "Fernando Silva")
set(CMAKE_PROJECT_NAME "LASzip")
set(PROJECT_CONTACT "fernando.silva@udc.es")
set(CMAKE_INSTALL_PREFIX /home/fsilva/software)
set(CMAKE_COMPILER_IS_GNUCXX)

# definitions for VC++
#add_definitions( -DCOMPILE_AS_DLL  -D_CRT_SECURE_NO_WARNINGS )
#add_definitions( -DUNORDERED )

include_directories(src/)

# Set source files
set(SOURCES
        src/arithmeticdecoder.cpp
        src/arithmeticencoder.cpp
        src/arithmeticmodel.cpp
        src/integercompressor.cpp
        #src/lasindex.cpp
        src/lasinterval.cpp
        src/lasquadtree.cpp
        src/lasreaditemcompressed_v1.cpp
        src/lasreaditemcompressed_v2.cpp
        src/lasreaditemcompressed_v3.cpp
        src/lasreaditemcompressed_v4.cpp
        src/lasreadpoint.cpp
        src/lasunzipper.cpp
        src/laswriteitemcompressed_v1.cpp
        src/laswriteitemcompressed_v2.cpp
        src/laswriteitemcompressed_v3.cpp
        src/laswriteitemcompressed_v4.cpp
        src/laswritepoint.cpp
        src/laszip.cpp
        src/laszipper.cpp
        src/laszip_dll.cpp
        )
# Flags
set(CMAKE_CXX_FLAGS " -Wall -m64 ")
set(CMAKE_CXX_FLAGS_RELEASE " -std=c++11 -O9")
set(CMAKE_CXX_FLAGS_DEBUG " -std=c++11 -O9 ")
#set(CMAKE_CXX_FLAGS_DEBUG " -std=c++0x -g3 -DDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG " -std=c++0x -pg ")

# set default compilation and show details for debug build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif (NOT CMAKE_BUILD_TYPE)



# Create the library
add_library(laszip STATIC ${SOURCES})
install(TARGETS laszip DESTINATION lib)
install(DIRECTORY "includes" DESTINATION includes/laszip)

#install(TARGETS las
#        LIBRARY DESTINATION lib)
#install(DIRECTORY inc/ DESTINATION include/LASlib
#FILES_MATCHING PATTERN "*.hpp")
#install(DIRECTORY ../LASzip/src/ DESTINATION include/LASzip
#        FILES_MATCHING PATTERN "*.hpp")

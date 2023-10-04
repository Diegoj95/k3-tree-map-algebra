cmake_minimum_required(VERSION 2.8.4)
project (LASlib)
set(PROJECT_VENDOR "Fernando Silva")
set(CMAKE_PROJECT_NAME "LASlib")
set(PROJECT_CONTACT "fernando.silva@udc.es")
set(CMAKE_INSTALL_PREFIX /home/fsilva/software)
set(CMAKE_COMPILER_IS_GNUCXX)

# definitions for VC++
add_definitions( -DCOMPILE_AS_DLL  -D_CRT_SECURE_NO_WARNINGS )
add_definitions( -DUNORDERED )

include_directories(inc/)
include_directories(../LASzip/src)

# Set source files
set(SOURCES
        src/lasreader.cpp
        src/laswriter.cpp
        src/lasreader_las.cpp
        src/lasreader_bin.cpp
        src/lasreader_qfit.cpp
        src/lasreader_shp.cpp
        src/lasreader_asc.cpp
        src/lasreader_bil.cpp
        src/lasreader_dtm.cpp
        src/lasreader_txt.cpp
        src/lasreadermerged.cpp
        src/lasreaderbuffered.cpp
        src/lasreaderstored.cpp
        src/lasreaderpipeon.cpp
        src/laswriter_las.cpp
        src/laswriter_bin.cpp
        src/laswriter_qfit.cpp
        src/laswriter_wrl.cpp
        src/laswriter_txt.cpp
        src/laswritercompatible.cpp
        src/laswaveform13reader.cpp
        src/laswaveform13writer.cpp
        src/lasutility.cpp
        src/lasfilter.cpp
        src/lastransform.cpp
        src/fopen_compressed.cpp
        ../LASzip/src/laszip.cpp
        ../LASzip/src/lasreadpoint.cpp
        ../LASzip/src/lasreaditemcompressed_v1.cpp
        ../LASzip/src/lasreaditemcompressed_v2.cpp
        ../LASzip/src/lasreaditemcompressed_v3.cpp
        ../LASzip/src/lasreaditemcompressed_v4.cpp
        ../LASzip/src/laswritepoint.cpp
        ../LASzip/src/laswriteitemcompressed_v1.cpp
        ../LASzip/src/laswriteitemcompressed_v2.cpp
        ../LASzip/src/laswriteitemcompressed_v3.cpp
        ../LASzip/src/laswriteitemcompressed_v4.cpp
        ../LASzip/src/integercompressor.cpp
        ../LASzip/src/arithmeticdecoder.cpp
        ../LASzip/src/arithmeticencoder.cpp
        ../LASzip/src/arithmeticmodel.cpp
        ../LASzip/src/lasindex.cpp
        ../LASzip/src/lasquadtree.cpp
        ../LASzip/src/lasinterval.cpp
        )
# Flags
set(CMAKE_CXX_FLAGS " -Wall -m64  -DCOMPILE_AS_DLL  -D_CRT_SECURE_NO_WARNINGS")
set(CMAKE_CXX_FLAGS_RELEASE "  -DCOMPILE_AS_DLL  -D_CRT_SECURE_NO_WARNINGS -std=c++11 -O9")
set(CMAKE_CXX_FLAGS_DEBUG "  -DCOMPILE_AS_DLL  -D_CRT_SECURE_NO_WARNINGS -std=c++11 -O9 ")
#set(CMAKE_CXX_FLAGS_DEBUG " -std=c++0x -g3 -DDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG " -std=c++0x -pg ")

# set default compilation and show details for debug build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif (NOT CMAKE_BUILD_TYPE)


# Add lasZip library
include_directories(../LASzip/src)

# Create the library
add_library(las STATIC ${SOURCES})
install(TARGETS las DESTINATION lib)
install(DIRECTORY "includes" DESTINATION includes/las)

#install(TARGETS las
#        LIBRARY DESTINATION lib)
#install(DIRECTORY inc/ DESTINATION include/LASlib
#FILES_MATCHING PATTERN "*.hpp")
#install(DIRECTORY ../LASzip/src/ DESTINATION include/LASzip
#        FILES_MATCHING PATTERN "*.hpp")

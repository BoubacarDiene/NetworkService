##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to prepare googletest and googlemock;
#         and add subdirectories containing unit tests
#
##

#################################################################
#                          Frameworks                           #
#################################################################

# Add script to make googletest and googlemock available
#
# FIXME: Gmock can't compile with flags used in this project:
#     error: conversion to 'long unsigned int' from 'int' may
#     change the sign of the result [-Werror=sign-conversion]
#
# Add "-Wno-error=sign-conversion" to make the build pass.
set(CMAKE_CXX_FLAGS -Wno-error=sign-conversion)
include(${CMAKE_SOURCE_DIR}/cmake/frameworks/googletest.cmake)

#################################################################
#                           Test files                          #
#################################################################

# Make test files list globally available for clang-format and
# clang-tidy tools
execute_process(
    COMMAND find ${CMAKE_SOURCE_DIR}/test
            -iname "*.h" -o -iname "*.hpp" -o -iname "*.cpp"
    OUTPUT_VARIABLE CXX_TEST_FILES)

string(REPLACE "\n" ";" CXX_TEST_FILES ${CXX_TEST_FILES})

set(ALL_CXX_TEST_FILES "${CXX_TEST_FILES}"
    CACHE INTERNAL "All *.cpp, *.h and *.hpp files of the project"
    FORCE)

#################################################################
#                       Subdirectories                          #
#################################################################

add_subdirectory(utils)

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
#                         Frameworks                            #
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
#                       Subdirectories                          #
#################################################################

add_subdirectory(utils)

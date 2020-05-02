##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build the core part of the service
#         and export all public interfaces
#
##

#################################################################
#                            Target                             #
#################################################################

# Make target name globally available for dependencies
set(TARGET_SERVICE ${CMAKE_PROJECT_NAME}-core
    CACHE STRING "Name of target to build the core service"
    FORCE)

# Build the core service as a static library
#
# Note:
#   The empty quotes are necessary because add_library() requires
#   a list of sources files which I add below using target_sources
add_library(${TARGET_SERVICE} STATIC "")

#################################################################
#                          Sources                              #
#################################################################

target_sources(${TARGET_SERVICE}
    PRIVATE
        NetworkService.cpp
    PUBLIC
        NetworkService.h
)

#################################################################
#                       Subdirectories                          #
#################################################################

# plugins directory contains public interfaces that src/plugins/*
# must implement
add_subdirectory(plugins)

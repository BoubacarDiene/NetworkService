##
#
# \file Root CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to check cmake version, set build type,
#         add subdirectories containing CMakeLists.txt file,
#         define common compilation flags and macros that might
#         be useful to build executable and libraries if any
#
# mkdir build && cd build
# cmake .. -DCMAKE_INSTALL_PREFIX=./out
#          -DCMAKE_BUILD_TYPE=<Debug = default | Release>
#          -DCONFIG_LOADER=<json = default | mock>
#          -DLOGS_OUTPUT=<std = default>
# make && make install
#
#
# \note
#     -DCONFIG_LOADER=mock can be used to test the service with
#     the mock version of the config loader. "json" is the default
#     value
#
#     -DLOGS_OUTPUT=std can be used to output logs messages to
#     the standard output. It's the default value
##

cmake_minimum_required(VERSION 3.17.2)

#################################################################
#                          Project                              #
#################################################################

# General informations
# Notes:
# - version = <year>.<month>.<patch>
# - The project's name will be used to name the executable
project(networkservice
    VERSION 20.05.00
    LANGUAGES CXX
    DESCRIPTION "A native service to allow performing network\
                 commands more securely by using related tools\
                 (ip, iptables, ebtables, nftables, ...)"
    HOMEPAGE_URL "https://github.com/BoubacarDiene/NetworkService"
)

# A name for the generated executable file
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})

# Compilation options
#
# Note: CMAKE_MODULE_PATH could be set to add our cmake directory
#       into CMake's search path. Doing so, "compilation-options"
#       only would be sufficient ...but CMake would need to search
#       for the file
include(${CMAKE_SOURCE_DIR}/cmake/compilation-options.cmake)

#################################################################
#                       Subdirectories                          #
#################################################################

# Directory containing source code and everything necessary to
# build it
add_subdirectory(src)

# Directory containing Doxyfile.in and everything necessary to
# generate and install documentation
add_subdirectory(doc)

#################################################################
#                         Code quality                          #
#################################################################

# Clang: Code formatting
include(${CMAKE_SOURCE_DIR}/cmake/tools/clang-format.cmake)

# Clang: Static analysis and linting
include(${CMAKE_SOURCE_DIR}/cmake/tools/clang-tidy.cmake)

# Graphviz: Dependency graph
include(${CMAKE_SOURCE_DIR}/cmake/tools/dependency-graph.cmake)

# Git hooks
include(${CMAKE_SOURCE_DIR}/cmake/git/pre-commit-hook.cmake)

# Create a command to avoid running doc, dependency-graph, clang-format
# and clang-tidy commands one by one
add_custom_target(analysis
    DEPENDS doc dependency-graph clang-format clang-tidy)

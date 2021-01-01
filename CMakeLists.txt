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
#          -DCMAKE_BUILD_TYPE=<Debug | Release = default>
#          -DCONFIG_LOADER=<json = default | fake>
#          -DLOGS_OUTPUT=<std = default>
#          -DENABLE_UNIT_TESTING=<ON | OFF = default>
#          -DEXECUTABLE_NAME=<networkservice = default>
# make && make install
#
#
# \note
#     -DCONFIG_LOADER=fake can be used to test the service with
#     the fake version of the config loader. "json" is the default
#     value
#
#     -DLOGS_OUTPUT=std can be used to output logs messages to
#     the standard output. It's the default value
##

cmake_minimum_required(VERSION 3.18.2)

#################################################################
#                          Project                              #
#################################################################

# General informations
# Notes:
# - version = <year>.<month>.<patch>
# - The project's name will be used to name the executable
project(networkservice
    VERSION 21.01.01
    LANGUAGES CXX
    DESCRIPTION "A native service to allow performing network\
                 commands more securely by using related tools\
                 (ip, iptables, ebtables, nftables, ...)"
    HOMEPAGE_URL "https://github.com/BoubacarDiene/NetworkService"
)

# Options
# Allow to enable/disable unit testing
option(ENABLE_UNIT_TESTING "Build unit tests" OFF)

# Where to retrieve network configuration from?
set(CONFIG_LOADER "json"
    CACHE STRING "Network configuration's source")

# Where to send logs?
set(LOGS_OUTPUT "std"
    CACHE STRING "Which logger to use?")

# A name for the generated executable file
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME}
    CACHE STRING "Name of the generated executable")

# Compilation options
#
# Note: CMAKE_MODULE_PATH could be set to add our cmake directory
#       into CMake's search path. Doing so, "compilation-options"
#       only would be sufficient ...but CMake would need to search
#       for the file
include(${CMAKE_SOURCE_DIR}/cmake/compilation-options.cmake)

#################################################################
#                     Search directories                        #
#################################################################

include_directories(SYSTEM third_party)
include_directories(src)

#################################################################
#                       Subdirectories                          #
#################################################################

# Add directory containing source code and everything necessary
# to generate executable
add_subdirectory(src)

# Add directory containing Doxyfile.in and everything necessary
# to generate and install documentation
add_subdirectory(doc)

# Enable testing and add directory containing unit tests
if (ENABLE_UNIT_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

#################################################################
#                         Code quality                          #
#################################################################

include(${CMAKE_SOURCE_DIR}/cmake/code-quality.cmake)

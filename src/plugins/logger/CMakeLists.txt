##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build the logger plugin
#
##

#################################################################
#                            Target                             #
#################################################################

# Make target name globally available for dependencies
set(TARGET_PLUGINS_LOGGER ${CMAKE_PROJECT_NAME}-plugins-logger
    CACHE STRING "Name of target to build the logger plugin"
    FORCE)

# Build the logger plugin as a static library
#
# Note:
#   The empty quotes are necessary because add_library() requires
#   a list of sources files which I add below using target_sources
add_library(${TARGET_PLUGINS_LOGGER} STATIC "")

#################################################################
#                          Sources                              #
#################################################################

target_sources(${TARGET_PLUGINS_LOGGER}
    PRIVATE
        StdLogger.cpp
    PUBLIC
        Logger.h
)
